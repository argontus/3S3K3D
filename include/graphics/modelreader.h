/**
 * @file graphics/modelreader.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MODELREADER_H_INCLUDED
#define GRAPHICS_MODELREADER_H_INCLUDED

#include <string>

#include <graphics/mesh.h>
#include <graphics/resourcemanager.h>
#include <graphics/vertexbuffer.h>

struct Lib3dsFile;
struct Lib3dsMesh;
struct Lib3dsNode;

class Effect;
class Node;

typedef ResourceManager<Mesh> MeshManager;
typedef ResourceManager<VertexBuffer> VertexBufferManager;

// TODO: provide a common interface for model readers?
// TODO: review and refactor the implementation before adding more features
/**
 * Model reader for .3ds files.
 */
class ModelReader
{
public:
    /**
     * Destructor.
     */
    ~ModelReader();

    /**
     * Constructor.
     *
     * @param meshManager Assumes ownership of any loaded meshes, cannot be a
     * null pointer.
     * @param vertexBufferManager Assumes ownership of any loaded vertex
     * buffers, cannot be a null pointer.
     */
    ModelReader(
        MeshManager* meshManager,
        VertexBufferManager* vertexBufferManager);

    // TODO: decide how errors should be reported
    /**
     * Reads a node hierarchy from a .3ds file.
     *
     * @param path Path to the .3ds file.
     * @param effect Effect to set for any loaded mesh nodes.
     *
     * @return Pointer to the root node of the created node hierarchy.
     *
     * @warning The returned object is allocated via a C++ <code>new</code>
     * expression. The caller is responsible for deleting it.
     */
    Node* read(const std::string& path, const Effect& effect);

private:
    /**
     * Reads all meshes from a given .3ds file structure. The active mesh
     * manager takes ownership of the read meshes.
     *
     * @param p Pointer to a .3ds file structure, cannot be a null pointer.
     * @param prefix Mesh name prefix for the read meshes.
     */
    void readMeshes(const Lib3dsFile* p, const std::string& prefix);

    /**
     * Reads a mesh from a given .3ds mesh structure. The active mesh manager
     * takes ownership of the read mesh.
     *
     * @param p Pointer to a .3ds mesh structure, cannot be a null pointer.
     * @param prefix Mesh name prefix for the read mesh.
     */
    void readMesh(const Lib3dsMesh* p, const std::string& prefix);

    Node* readModel(const Lib3dsFile* file);
    Node* readNode(const Lib3dsNode* p);
    Node* readMeshNode(const Lib3dsNode* p);

    static int countChildren(const Lib3dsNode* p);
    static int countSiblings(const Lib3dsNode* p);
    static int countSupportedChildren(const Lib3dsNode* p);
    static int countSupportedSiblings(const Lib3dsNode* p);
    static bool isNodeTypeSupported(const Lib3dsNode* p);

    MeshManager* meshManager_;                  ///< Mesh manager.
    VertexBufferManager* vertexBufferManager_;  ///< Vertex buffer manager.
    std::string meshPrefix_;                    ///< Prefix for mesh names.
    const Effect* effect_;                      ///< Effect for mesh nodes.

    // prevent copying
    ModelReader(const ModelReader&);
    ModelReader& operator =(const ModelReader&);
};

#endif // #ifndef GRAPHICS_MODELREADER_H_INCLUDED
