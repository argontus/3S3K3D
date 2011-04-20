/**
 * @file graphics/modelreader.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/modelreader.h>

#include <cstring>

#include <lib3ds/lib3ds.h>

#include <graphics/groupnode.h>
#include <graphics/meshnode.h>
#include <graphics/runtimeassert.h>

ModelReader::~ModelReader()
{
    // ...
}

ModelReader::ModelReader()
:   meshManager_(0),
    meshPrefix_()
{
    // ...
}

void ModelReader::setMeshManager(MeshManager* const p)
{
    meshManager_ = p;
}

MeshManager* ModelReader::meshManager() const
{
    return meshManager_;
}

Node* ModelReader::read(const std::string& path)
{
    GRAPHICS_RUNTIME_ASSERT(meshManager_ != 0);

    // open the model file
    Lib3dsFile* const file = lib3ds_file_open(path.c_str());

    if( file == NULL )
        std::cout << path << std::endl;
    // TODO: decide how errors should be reported
    GRAPHICS_RUNTIME_ASSERT(file != 0);

    // set mesh prefix to model file path
    meshPrefix_ = path;

    readMeshes(file, path);
    // TODO: read materials
    // TODO: read lights

    Node* root = 0;

    if (file->nodes == 0)
    {
        GroupNode* const group = new GroupNode();

        // the .3ds file contains only mesh data, generate nodes
        for (int i = 0; i < file->nmeshes; ++i)
        {
            const std::string name = meshPrefix_ + file->meshes[i]->name;
            Mesh* const mesh = meshManager_->getResource(name);

            MeshNode* const meshNode = new MeshNode();
            meshNode->setMesh(mesh);
            meshNode->updateModelExtents();

            group->attachChild(meshNode);
        }

        root = group;
    }
    else
    {
        root = readModel(file);
    }

    // free resources
    lib3ds_file_free(file);

    return root;
}

void ModelReader::readMeshes(const Lib3dsFile* const p, const std::string& prefix)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    GRAPHICS_RUNTIME_ASSERT(meshManager_ != 0);

    for (int i = 0; i < p->nmeshes; ++i)
    {
        readMesh(p->meshes[i], prefix);
    }
}

void ModelReader::readMesh(const Lib3dsMesh* const p, const std::string& prefix)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    GRAPHICS_RUNTIME_ASSERT(meshManager_ != 0);

    const int numFaces = p->nfaces;
    const int numVertices = p->nvertices;

    if (numFaces < 1)
    {
        return;
    }

    Mesh* const mesh = new Mesh(numFaces);

    // for each face in the mesh
    for (int i = 0; i < numFaces; ++i)
    {
        const int i0 = p->faces[i].index[0];
        const int i1 = p->faces[i].index[1];
        const int i2 = p->faces[i].index[2];

        // if one of these is triggered, the mesh data is corrupted
        GRAPHICS_RUNTIME_ASSERT(i0 >= 0 && i0 < numVertices);
        GRAPHICS_RUNTIME_ASSERT(i1 >= 0 && i1 < numVertices);
        GRAPHICS_RUNTIME_ASSERT(i2 >= 0 && i2 < numVertices);

        mesh->vertices()[i * 3 + 0] = Vector3(p->vertices[i0][0], p->vertices[i0][1], p->vertices[i0][2]);
        mesh->vertices()[i * 3 + 1] = Vector3(p->vertices[i1][0], p->vertices[i1][1], p->vertices[i1][2]);
        mesh->vertices()[i * 3 + 2] = Vector3(p->vertices[i2][0], p->vertices[i2][1], p->vertices[i2][2]);

        if (p->texcos != 0)
        {
            mesh->texCoords()[i * 3 + 0] = Vector2(p->texcos[i0][0], p->texcos[i0][1]);
            mesh->texCoords()[i * 3 + 1] = Vector2(p->texcos[i1][0], p->texcos[i1][1]);
            mesh->texCoords()[i * 3 + 2] = Vector2(p->texcos[i2][0], p->texcos[i2][1]);
        }
        else
        {
            mesh->texCoords()[i * 3 + 0] = Vector2(0.0f, 0.0f);
            mesh->texCoords()[i * 3 + 1] = Vector2(0.0f, 0.0f);
            mesh->texCoords()[i * 3 + 2] = Vector2(0.0f, 0.0f);
        }
    }

    // TODO: material, texture coordinates

    const char* const meshName = p->name;

    mesh->generateFlatNormals();
    meshManager_->loadResource(prefix + meshName, mesh);
}

Node* ModelReader::readModel(const Lib3dsFile* const file)
{
    // TODO: create a group node only if it has multiple child nodes
    GroupNode* const root = new GroupNode();

    const Lib3dsNode* p = file->nodes;

    while (p != 0)
    {
        Node* const node = readNode(p);

        if (node != 0)
        {
            root->attachChild(node);
        }

        p = p->next;
    }

    return root;
}

Node* ModelReader::readNode(const Lib3dsNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    //GRAPHICS_RUNTIME_ASSERT(isNodeTypeSupported(p));

    if (p->childs != 0)
    {
        // p is a group node
        GroupNode* const group = new GroupNode();

        if (p->type == LIB3DS_NODE_MESH_INSTANCE && std::strcmp(p->name, "$$$DUMMY") != 0)
        {
            Node* const meshNode = readMeshNode(p);

            if (meshNode != 0)
            {
                group->attachChild(meshNode);
            }
        }

        const Lib3dsNode* child = p->childs;

        while (child != 0)
        {
            Node* const node = readNode(child);

            if (node != 0)
            {
                group->attachChild(node);
            }

            child = child->next;
        }

        if (group->hasChildren() == false)
        {
            delete group;
            return 0;
        }

        return group;
    }

    if (p->type == LIB3DS_NODE_MESH_INSTANCE && std::strcmp(p->name, "$$$DUMMY") != 0)
    {
        return readMeshNode(p);
    }

    return 0;
}

Node* ModelReader::readMeshNode(const Lib3dsNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    GRAPHICS_RUNTIME_ASSERT(p->type == LIB3DS_NODE_MESH_INSTANCE);
    GRAPHICS_RUNTIME_ASSERT(std::strcmp(p->name, "$$$DUMMY") != 0);

    const char* const meshName = p->name;

    Mesh* mesh = meshManager_->getResource(meshPrefix_ + meshName);

    //GRAPHICS_RUNTIME_ASSERT(mesh != 0);
    if (mesh == 0)
    {
        return 0;
    }

    MeshNode* meshNode = new MeshNode();
    // TODO: transform
    meshNode->setMesh(mesh);
    meshNode->updateModelExtents();

    return meshNode;
}

int ModelReader::countChildren(const Lib3dsNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);

    if (p->childs == 0)
    {
        return 0;
    }

    return countSiblings(p->childs) + 1;
}

int ModelReader::countSiblings(const Lib3dsNode* p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);

    int count = 0;
    p = p->next;

    while (p != 0)
    {
        ++count;
        p = p->next;
    }

    return count;
}

int ModelReader::countSupportedChildren(const Lib3dsNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);

    if (p->childs == 0)
    {
        return 0;
    }

    int count = countSupportedSiblings(p->childs);

    if (isNodeTypeSupported(p->childs))
    {
        ++count;
    }

    return count;
}

int ModelReader::countSupportedSiblings(const Lib3dsNode* p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);

    int count = 0;
    p = p->next;

    while (p != 0)
    {
        if (isNodeTypeSupported(p))
        {
            ++count;
        }

        p = p->next;
    }

    return count;
}

bool ModelReader::isNodeTypeSupported(const Lib3dsNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);

    switch (p->type)
    {
        case LIB3DS_NODE_AMBIENT_COLOR:     return false;
        case LIB3DS_NODE_MESH_INSTANCE:     return true;
        case LIB3DS_NODE_CAMERA:            return false;
        case LIB3DS_NODE_CAMERA_TARGET:     return false;
        case LIB3DS_NODE_OMNILIGHT:         return false;
        case LIB3DS_NODE_SPOTLIGHT:         return false;
        case LIB3DS_NODE_SPOTLIGHT_TARGET:  return false;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return false;
    }
}
