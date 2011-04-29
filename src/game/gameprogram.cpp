/**
 * @file game/gameprogram.cpp
 * @author Marko Silokunnas
 */

#include "gameprogram.h"

#include "effects.h"

#include <cstdlib>

#include <geometry/linesegment3.h>
#include <geometry/math.h>

#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>
#include <graphics/nodes/pointlightnode.h>
#include <graphics/drawparams.h>
#include <graphics/runtimeassert.h>
#include <graphics/modelreader.h>

#include <graphics/device.h>
#include <graphics/effect.h>
#include <graphics/pass.h>
#include <graphics/technique.h>
#include <graphics/parameters/parameter.h>

#include <graphics/nodecontrollers/lightfadeoutcontroller.h>
#include <graphics/nodecontrollers/suicidecontroller.h>

#include <graphics/nodevisitors/pointlitgeometryquery.h>
#include <graphics/nodevisitors/segmentmeshintersectionquery.h>
#include <graphics/nodevisitors/visibleextentsquery.h>
#include <graphics/nodevisitors/visiblegeometryquery.h>
#include <graphics/nodevisitors/visiblelightsquery.h>

void constructOctTree(Node*, int, int);

void subdivide(
    Node* const subtree,
    const Extents3& subdivisionExtents,
    const int maxDivisions,
    const int minNodeCount)
{
    GRAPHICS_RUNTIME_ASSERT(minNodeCount > 0);

    std::vector<Node*> enclosedNodes;

    for (int i = 0; i < subtree->numChildren(); ++i)
    {
        Node* const child = subtree->child(i);
        const Extents3 childExtents = child->subtreeExtents();

        if (subdivisionExtents.contains(childExtents))
        {
            enclosedNodes.push_back(child);
        }
    }

    if (static_cast<int>(enclosedNodes.size()) >= minNodeCount)
    {
        Node* const subdivision = new Node;

        for (size_t i = 0; i < enclosedNodes.size(); ++i)
        {
            subtree->detachChild(enclosedNodes[i]);
            subdivision->attachChild(enclosedNodes[i]);
        }

        subtree->attachChild(subdivision);
    }

    // recursion
    for (int i = 0; i < subtree->numChildren(); ++i)
    {
        constructOctTree(subtree->child(i), maxDivisions - 1, minNodeCount);
    }
}

// automatic oct-tree construction, makes an oct-tree bounding volume hierarchy
// of a subtree
void constructOctTree(
    Node* const subtree,
    const int maxDivisions,
    const int minNodeCount)
{
    GRAPHICS_RUNTIME_ASSERT(minNodeCount > 0);

    if (maxDivisions == 0)
    {
        return;
    }

    const Extents3 extents = subtree->subtreeExtents();
    const Vector3 min = extents.min;
    const Vector3 max = extents.max;
    const Vector3 mid = (min + max) / 2.0f;

    subdivide(subtree, Extents3(Vector3(min.x, min.y, min.z), Vector3(mid.x, mid.y, mid.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(mid.x, min.y, min.z), Vector3(max.x, mid.y, mid.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(mid.x, mid.y, min.z), Vector3(max.x, max.y, mid.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(min.x, mid.y, min.z), Vector3(mid.x, max.y, mid.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(min.x, min.y, mid.z), Vector3(mid.x, mid.y, max.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(mid.x, min.y, mid.z), Vector3(max.x, mid.y, max.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(mid.x, mid.y, mid.z), Vector3(max.x, max.y, max.z)), maxDivisions, minNodeCount);
    subdivide(subtree, Extents3(Vector3(min.x, mid.y, mid.z), Vector3(mid.x, max.y, max.z)), maxDivisions, minNodeCount);
}

GameProgram::GameProgram()
:   configuration(),
    mixer_(),
    device_(0),
    ship(NULL),
    testObject(NULL),
    camera_(0),
    rootNode_(0),
    drawShadows_(false),
    drawExtents_(false),
    drawShadowVolumes_(false),
    rotateLights(false),
    programManager_(),
    meshManager_(),
    textureManager_(),
    vertexBufferManager_(),
    extentsVertexFormat_(0),
    meshVertexFormat_(0),
    shadowVertexFormat_(0),
    shadowVertexBuffer_(0),
    dgnsTextureMeshEffect_(0),
    noTextureMeshEffect_(0),
    extentsEffect_(0),
    shadowEffect_(0),
    particleEffect_(0)
{
    running         = true;
    deltaTicks      = 0;
    deltaTime       = 0;
    cameraSpeedX    = 0;
    cameraSpeedY    = 0;
    cameraSpeedZ    = 0;
}

int GameProgram::execute()
{
	if( init() == false ) {
		return -1;
	}

    glewInit();

    device_ = new Device(width, height);
    device_->setClearColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
    device_->setClearDepth(1.0);
    device_->setClearStencil(0);



    // init vertex formats

    // vertex format for Vector3
    extentsVertexFormat_ = new VertexFormat(1);
    extentsVertexFormat_->setAttribute(0, VertexAttribute::Type::Float3, "position");
    extentsVertexFormat_->compile();

    // vertex format for Mesh::Vertex
    meshVertexFormat_ = new VertexFormat(4);
    meshVertexFormat_->setAttribute(0, VertexAttribute::Type::Float3, "position");
    meshVertexFormat_->setAttribute(1, VertexAttribute::Type::Float3, "normal");
    meshVertexFormat_->setAttribute(2, VertexAttribute::Type::Float3, "tangent");
    meshVertexFormat_->setAttribute(3, VertexAttribute::Type::Float2, "texCoord");
    meshVertexFormat_->compile();

    particleVertexFormat_ = new VertexFormat(3);
    particleVertexFormat_->setAttribute(0, VertexAttribute::Type::Float3, "position");
    particleVertexFormat_->setAttribute(1, VertexAttribute::Type::Float4, "color");
    particleVertexFormat_->setAttribute(2, VertexAttribute::Type::Float1, "pointSize");
    particleVertexFormat_->compile();

    // vertex format for Vector3
    shadowVertexFormat_ = new VertexFormat(1);
    shadowVertexFormat_->setAttribute(0, VertexAttribute::Type::Float3, "position");
    shadowVertexFormat_->compile();



    shadowVertexBuffer_ = new VertexBuffer(
        sizeof(Vector3),
        24,
        0,
        VertexBuffer::Usage::Dynamic
    );


    // init textures

    Texture* texture = new Texture();
    texture->loadImage("data/textures/diffuse.tga");
    texture->generateMipmap();
    texture->activateAnisotropicFiltering();
    texture->setFilters(Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR);
    textureManager_.loadResource("diffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/specular.tga");
    texture->generateMipmap();
    texture->activateAnisotropicFiltering();
    texture->setFilters(Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR);
    textureManager_.loadResource("specular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/glow.tga");
    texture->generateMipmap();
    texture->activateAnisotropicFiltering();
    texture->setFilters(Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR);
    textureManager_.loadResource("glow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/normal.tga");
    texture->generateMipmap();
    texture->activateAnisotropicFiltering();
    texture->setFilters(Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR);
    textureManager_.loadResource("normal", texture);

    texture = new Texture();
    texture->loadImage("data/textures/particle.tga");
    texture->generateMipmap();
    texture->setFilters(Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR);
    textureManager_.loadResource("particle", texture);



    // init scene

    rootNode_ = new Node();


    // init camera

    camera_ = new CameraNode();
    camera_->setPerspectiveProjection(45.0f, aspectRatio, 1.0f, 1000.0f);

    testObject = new GameObject();
    testObject->setGraphicalPresentation( camera_ );
    testObject->attachController( &testController );


    // TODO: quick & dirty
    initEffects();
    test();


	SDL_Event event;
    deltaTicks          = 0;
    deltaTime           = 0;
    Uint32 currentTicks = 0;
    Uint32 lastTicks    = 0;
    int deltaX          = 0;
    int deltaY          = 0;

    configuration.readConfiguration("config.ini");

    if( mouseBoundToScreen )
    {
        mouse.setMouseMode( Mouse::MOUSE_BOUND );
        mouse.setMouseBindPoint( width/2, height/2 );
        mouse.moveMouse( width/2, height/2 );
    }

    // init audio
    // default frequency is usually 22050 Hz
    // default format is AUDIO_U16SYS
    // 2 for stereo channels
    // 1024 is a viable buffer size for 22kHz, tweak this if skippy / laggy
    mixer_.init( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024 );
    mixer_.loadMusic( "data/sounds/radio.ogg", "radio" );
    mixer_.loadChunk( "data/sounds/tub.ogg", "tub" );

    std::cout << "Entering main loop..." << std::endl;

	while( running ) {
        currentTicks = SDL_GetTicks();

	    deltaTicks = currentTicks - lastTicks;
	    deltaTime = deltaTicks / 1000.0f;

		while( SDL_PollEvent( &event ) ) {
			onEvent( event );
		}

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_ESCAPE))
        {
            running = false;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F1))
        {
            rotateLights = !rotateLights;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F2))
        {
            drawExtents_ = !drawExtents_;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F3))
        {
            drawShadows_ = !drawShadows_;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F4))
        {
            drawShadowVolumes_ = !drawShadowVolumes_;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F5))
        {
            mouseBoundToScreen = !mouseBoundToScreen;
        }

        static float fireDelay = 0.0f;
        static int barrel = 0;

        if (fireDelay > 0.0f)
        {
            fireDelay -= deltaTime;
        }

        if (keyboard.keyIsDown(Keyboard::KEY_SPACE) && fireDelay <= 0.0f)
        {
            //fireDelay = 1.0f / 30.0f;
            fireDelay = 1.0f / 50.0f;
            barrel = (barrel + 1) % 2;

            const Transform3 t = camera_->worldTransform();
            Vector3 spawnOffset;

            if (barrel == 0)
            {
                spawnOffset = -4.0f * t.rotation.row(0) - 3.0f * t.rotation.row(1);
            }
            else
            {
                spawnOffset = 4.0f * t.rotation.row(0) - 3.0f * t.rotation.row(1);
            }

            const float direction = 2.0f * Math::pi() * std::rand() / RAND_MAX;
            const float length = 0.025f * std::rand() / RAND_MAX;
            const Vector3 velocityOffset = length * Vector3(Math::cos(direction), Math::sin(direction), 0.0f) * t.rotation;

            // ignore multibarrel emitting
            spawnOffset = Vector3::zero();

            Bullet* const bullet = new Bullet;
            bullet->active = true;
            bullet->life = 2.0f;
            bullet->shape.center = t.translation + spawnOffset;
            bullet->shape.radius = 2.0f;
            //bullet->velocity = -1000.0f * t.rotation.row(2);
            bullet->velocity = -500.0f * (t.rotation.row(2) + velocityOffset);

            if (mouse.mouseButtonIsDown(Mouse::MOUSEBUTTON_RIGHT))
            {
                bullet->color = Vector4(0.25f, 1.0f, 0.5f, 1.0f);
            }
            else
            {
                bullet->color = Vector4(1.0f, 0.5f, 0.25f, 1.0f);
            }

            bullets_.push_back(bullet);
        }

        // see keyboardcontroller.h for a TODO related to member 'speed'
        static const float speed = 50.0f;
        testController.setSpeed( speed );

        deltaX = mouse.getMouseX();
        deltaY = mouse.getMouseY();

        const float rotationFactor = 0.005f;

        if( deltaX != 0 && mouseBoundToScreen )
        {
            camera_->rotateBy(Matrix3x3::yRotation(deltaX * -rotationFactor));
        }

        if( deltaY != 0 && mouseBoundToScreen )
        {
            camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaY * -rotationFactor));
        }

		tick( deltaTime );

		keyboard.updateKeyboardState();
		mouse.updateMouse();
		testObject->update( deltaTime );

		render();
		lastTicks = currentTicks;
	}

    std::cout << "Leaving main loop." << std::endl;

    mixer_.close();
	cleanup();
	std::cout << "bye!" << std::endl;

	return 0;
}

void GameProgram::render()
{
    // TODO: make sure the stencil writemasks are ~0
    // HACK: make sure depth buffer write mask is GL_TRUE
    device_->setDepthState(DepthState::lessEqual());

    device_->clear(true, true, true);
    //renderer_->setProjectionMatrix(camera_->projectionMatrix());


    // TODO: REALLY quick & dirty

    static VisibleExtentsQuery visibleExtentsQuery;
    static VisibleGeometryQuery visibleGeometryQuery;


    // predraw step

    visibleGeometryQuery.reset();
    visibleGeometryQuery.init(*camera_);

    rootNode_->accept(&visibleGeometryQuery);

    DrawParams drawParams;
    drawParams.device = device_;
    drawParams.viewMatrix = camera_->viewMatrix();
    drawParams.projectionMatrix = camera_->projectionMatrix();
    drawParams.viewRotation = transpose(camera_->worldTransform().rotation);

    // begin ambient render pass

    const Vector3 ambientLightColor(0.25f, 0.25f, 0.25f);

    for (int i = 0; i < visibleGeometryQuery.numMeshNodes(); ++i)
    {
        MeshNode* const p = visibleGeometryQuery.meshNode(i);
        GRAPHICS_RUNTIME_ASSERT(p->vertexBuffer() != 0);

        const Transform3 t = p->worldTransform();

        const Matrix4x4 worldMatrix = toMatrix4x4(t);
        const Matrix4x4 modelViewMatrix = worldMatrix * drawParams.viewMatrix;
        const Matrix3x3 normalMatrix = t.rotation * drawParams.viewRotation;

        // TODO: quick & dirty
        Pass* const pass = p->effect()->technique("ambientLight")->pass(0);
        pass->parameter("modelViewMatrix")->setValue(modelViewMatrix);
        pass->parameter("projectionMatrix")->setValue(drawParams.projectionMatrix);
        pass->parameter("normalMatrix")->setValue(normalMatrix);
        pass->parameter("ambientLightColor")->setValue(ambientLightColor);
        pass->bind(drawParams.device);

        drawParams.device->setVertexFormat(meshVertexFormat_);
        drawParams.device->setVertexBuffer(p->vertexBuffer());
        drawParams.device->drawPrimitives(Device::PrimitiveType::Triangles);

        // TODO: are these needed?
        drawParams.device->setVertexBuffer(0);
        drawParams.device->setVertexFormat(0);
    }

    // end ambient render pass

    static VisibleLightsQuery visibleLightsQuery;
    visibleLightsQuery.reset();
    visibleLightsQuery.init(*camera_);

    rootNode_->accept(&visibleLightsQuery);

    // for each light
    for (int lightIndex = 0; lightIndex < visibleLightsQuery.numPointLightNodes(); ++lightIndex)
    {
    const PointLightNode* const pointLight = visibleLightsQuery.pointLightNode(lightIndex);

    const Vector3 lightWorldPosition = pointLight->worldTransform().translation;
    const Vector3 lightViewPosition = transform(lightWorldPosition, inverse(camera_->worldTransform()));
    const Vector3 lightColor = pointLight->lightColor();
    const float lightRange = pointLight->lightRange();;

    // light effect sphere
    const Sphere effectSphere(lightWorldPosition, lightRange);

    if (drawShadows_)
    {
    // static to maintain capacity
    static std::vector<Vector3> shadowVertices;
    shadowVertices.clear();

    static PointLitGeometryQuery pointLitGeometryQuery;
    pointLitGeometryQuery.reset();
    pointLitGeometryQuery.init(effectSphere);
    rootNode_->accept(&pointLitGeometryQuery);

    // generate shadow geometry for this light
    //for (size_t i = 0; i < meshNodes_.size(); ++i)
    for (int i = 0; i < pointLitGeometryQuery.numMeshNodes(); ++i)
    {
        const MeshNode* const meshNode = pointLitGeometryQuery.meshNode(i);

        if (intersect(meshNode->extents(), effectSphere) == false)
        {
            // the geometry node is not within the light effect sphere, next
            continue;
        }

        const Transform3 transform = meshNode->worldTransform();
        const Mesh* mesh = meshNode->mesh();

        for (int iFace = 0; iFace < mesh->numFaces(); ++iFace)
        {
            const Mesh::Vertex& vertex0 = mesh->vertex(3 * iFace + 0);
            const Mesh::Vertex& vertex1 = mesh->vertex(3 * iFace + 1);
            const Mesh::Vertex& vertex2 = mesh->vertex(3 * iFace + 2);

            const Vector3 n = vertex0.normal * transform.rotation;

            // vertex positions in world space
            Vector3 p0 = ::transform(vertex0.position, transform);
            Vector3 p1 = ::transform(vertex1.position, transform);
            Vector3 p2 = ::transform(vertex2.position, transform);

            // vectors from light source to vertices
            const Vector3 d0 = p0 - lightWorldPosition;
            const Vector3 d1 = p1 - lightWorldPosition;
            const Vector3 d2 = p2 - lightWorldPosition;

            const float length0 = length(d0);
            const float length1 = length(d1);
            const float length2 = length(d2);

            // minimum distance from light source to the vertices
            const float minDistance = Math::min(Math::min(length0, length1), length2);

            // TODO: looks ok in most cases but actually this is not enough,
            // make it so that the triangle centroid would be extruded to the
            // light effect sphere boundary
            const float projectionDistance = lightRange - minDistance;

            if (projectionDistance <= 0.0f)
            {
                // the triangle vertices are not within the light effect range,
                // ignore it
                continue;
            }

            // unit length direction vectors from light source to vertices
            // TODO: these do not avoid division by zero
            const Vector3 lightV0 = d0 / length0;
            const Vector3 lightV1 = d1 / length1;
            const Vector3 lightV2 = d2 / length2;

            if (dot(lightV0, n) >= 0.0f)
            {
                // the signs do not differ, this is not a front facing triangle,
                // ignore it
                continue;
            }

            const Vector3 s0 = p0 + projectionDistance * lightV0;
            const Vector3 s1 = p1 + projectionDistance * lightV1;
            const Vector3 s2 = p2 + projectionDistance * lightV2;

            // TODO: use OpenGL polygon offset instead of this
            const float offset = 0.1f;

            p0 = p0 + offset * lightV0;
            p1 = p1 + offset * lightV1;
            p2 = p2 + offset * lightV2;

            // TODO: test if indexed rendering is faster

            // front cap
            shadowVertices.push_back(p0);
            shadowVertices.push_back(p1);
            shadowVertices.push_back(p2);

            // back cap
            shadowVertices.push_back(s0);
            shadowVertices.push_back(s2);
            shadowVertices.push_back(s1);

            shadowVertices.push_back(p0);
            shadowVertices.push_back(s0);
            shadowVertices.push_back(s1);

            shadowVertices.push_back(p0);
            shadowVertices.push_back(s1);
            shadowVertices.push_back(p1);

            shadowVertices.push_back(p1);
            shadowVertices.push_back(s1);
            shadowVertices.push_back(s2);

            shadowVertices.push_back(p1);
            shadowVertices.push_back(s2);
            shadowVertices.push_back(p2);

            shadowVertices.push_back(p2);
            shadowVertices.push_back(s2);
            shadowVertices.push_back(s0);

            shadowVertices.push_back(p2);
            shadowVertices.push_back(s0);
            shadowVertices.push_back(p0);
        }
    }

    // begin shadow pass ------------------------------------------------------

    if (shadowVertices.empty() == false)
    {
        // load the shadow geometry to a vertex buffer
        shadowVertexBuffer_->update(
            shadowVertexBuffer_->elementSize(),
            shadowVertices.size(),
            &shadowVertices[0]
        );

        // TODO: make sure the stencil buffer writemasks are ~0
        // clear stencil buffer
        device_->clear(false, false, true);

        Pass* const pass = shadowEffect_->technique("singlePass")->pass(0);
        pass->parameter("modelViewMatrix")->setValue(drawParams.viewMatrix);
        pass->parameter("projectionMatrix")->setValue(drawParams.projectionMatrix);
        pass->bind(drawParams.device);

        device_->setVertexFormat(shadowVertexFormat_);
        device_->setVertexBuffer(shadowVertexBuffer_);
        device_->drawPrimitives(Device::PrimitiveType::Triangles);
        device_->setVertexBuffer(0);
        device_->setVertexFormat(0);

        //if (drawShadowVolumes_ && lightIndex == 0)
        if (drawShadowVolumes_)
        {
            Pass* const pass = shadowEffect_->technique("wireframe")->pass(0);
            pass->parameter("modelViewMatrix")->setValue(drawParams.viewMatrix);
            pass->parameter("projectionMatrix")->setValue(drawParams.projectionMatrix);
            pass->bind(drawParams.device);

            device_->setVertexFormat(shadowVertexFormat_);
            device_->setVertexBuffer(shadowVertexBuffer_);
            device_->drawPrimitives(Device::PrimitiveType::Triangles);
            device_->setVertexBuffer(0);
            device_->setVertexFormat(0);
        }
    }

    // end shadow pass --------------------------------------------------------
    }

    // lit render pass
    for (int i = 0; i < visibleGeometryQuery.numMeshNodes(); ++i)
    {
        // render only if the geometry node is within the light effect sphere
        if (intersect(visibleGeometryQuery.meshNode(i)->extents(), effectSphere))
        {
            MeshNode* const p = visibleGeometryQuery.meshNode(i);

            GRAPHICS_RUNTIME_ASSERT(p->vertexBuffer() != 0);

            const Transform3 t = p->worldTransform();

            const Matrix4x4 worldMatrix = toMatrix4x4(t);
            const Matrix4x4 modelViewMatrix = worldMatrix * drawParams.viewMatrix;
            const Matrix3x3 normalMatrix = t.rotation * drawParams.viewRotation;

            // TODO: quick & dirty
            Pass* const pass = p->effect()->technique("pointLight")->pass(0);
            pass->parameter("modelViewMatrix")->setValue(modelViewMatrix);
            pass->parameter("projectionMatrix")->setValue(drawParams.projectionMatrix);
            pass->parameter("normalMatrix")->setValue(normalMatrix);
            pass->parameter("lightPosition")->setValue(lightViewPosition);
            pass->parameter("lightColor")->setValue(lightColor);
            pass->parameter("lightRange")->setValue(lightRange);
            pass->bind(drawParams.device);

            drawParams.device->setVertexFormat(meshVertexFormat_);
            drawParams.device->setVertexBuffer(p->vertexBuffer());
            drawParams.device->drawPrimitives(Device::PrimitiveType::Triangles);

            // TODO: are these needed?
            drawParams.device->setVertexBuffer(0);
            drawParams.device->setVertexFormat(0);
        }
    }

    } // for each light

    static float lightRotation = 0.0f;

    if (rotateLights)
    {
        lightRotation = Math::mod(lightRotation + deltaTime * 0.075f, 2.0f * Math::pi());

        // child(0) should be the lights group
        //rootNode_->child(0)->setRotation(Matrix3x3::yRotation(lightRotation));
        rootNode_->setRotation(Matrix3x3::yRotation(lightRotation));
    }
/*
    // quick & dirty box rotation for testing the extents updates with lazy
    // evaluation
    for (int i = 0; i < rootNode_->numChildren(); ++i)
    {
        rootNode_->child(i)->rotateBy(Matrix3x3::yRotation(-0.0025f * (i * i + 1) * deltaTime));
    }
*/
    // begin quick & dirty billboard sprite test ------------------------------

    const Matrix3x3 cameraRotation = camera_->worldTransform().rotation;

    for (size_t i = 0; i < bullets_.size(); ++i)
    {
        const Vector3 center = bullets_[i]->shape.center;
        const float radius = bullets_[i]->shape.radius;
        const Vector4 particleColor = bullets_[i]->color;

        const Vector3 xOffset = cameraRotation.row(0) * radius * 0.5f;
        const Vector3 yOffset = cameraRotation.row(1) * radius * 0.5f;

        ParticleVertex vertices[] = {
            ParticleVertex(center - xOffset - yOffset, particleColor, Vector2(0.0f, 0.0f)),
            ParticleVertex(center + xOffset - yOffset, particleColor, Vector2(1.0f, 0.0f)),
            ParticleVertex(center + xOffset + yOffset, particleColor, Vector2(1.0f, 1.0f)),
            ParticleVertex(center - xOffset + yOffset, particleColor, Vector2(0.0f, 1.0f))
        };

        GLshort indices[] = {
            0, 1, 2,
            0, 2, 3
        };

        VertexFormat particleVertexFormat(3);
        particleVertexFormat.setAttribute(0, VertexAttribute::Type::Float3, "position");
        particleVertexFormat.setAttribute(1, VertexAttribute::Type::Float4, "color");
        particleVertexFormat.setAttribute(2, VertexAttribute::Type::Float2, "texCoord");
        particleVertexFormat.compile();

        VertexBuffer particleVertexBuffer(
            sizeof(vertices[0]),
            sizeof(vertices) / sizeof(vertices[0]),
            vertices,
            VertexBuffer::Usage::Static
        );

        IndexBuffer particleIndexBuffer(
            IndexBuffer::Format::UnsignedShort,
            sizeof(indices) / sizeof(indices[0]),
            indices,
            IndexBuffer::Usage::Static
        );

        Pass* const pass = particleEffect_->technique(0)->pass(0);
        pass->parameter("viewProjectionMatrix")->setValue(drawParams.viewMatrix * drawParams.projectionMatrix);
        pass->bind(drawParams.device);

        drawParams.device->setVertexFormat(&particleVertexFormat);
        drawParams.device->setVertexBuffer(&particleVertexBuffer);
        drawParams.device->setIndexBuffer(&particleIndexBuffer);
        drawParams.device->drawPrimitives(Device::PrimitiveType::Triangles);

        // TODO: are these needed?
        drawParams.device->setIndexBuffer(0);
        drawParams.device->setVertexBuffer(0);
        drawParams.device->setVertexFormat(0);
    }

    // end quick & dirty billboard sprite test --------------------------------

    if (drawExtents_)
    {
        visibleExtentsQuery.init(*camera_);
        visibleExtentsQuery.reset();
        rootNode_->accept(&visibleExtentsQuery);

        Pass* const pass = extentsEffect_->technique(0)->pass(0);
        pass->parameter("modelViewMatrix")->setValue(drawParams.viewMatrix);
        pass->parameter("projectionMatrix")->setValue(drawParams.projectionMatrix);
        pass->bind(drawParams.device);

        for (int i = 0; i < visibleExtentsQuery.numExtents(); ++i)
        {
            drawExtents(visibleExtentsQuery.extents(i), drawParams);
        }
    }

    SDL_GL_SwapBuffers();
}

// TODO: quick & dirty, this does not belong here
void GameProgram::drawExtents(const Extents3& extents, const DrawParams& params)
{
    const Vector3 min = extents.min;
    const Vector3 max = extents.max;

    const Vector3 vertices[] = {
        Vector3(min.x, min.y, max.z),
        Vector3(max.x, min.y, max.z),
        Vector3(max.x, max.y, max.z),
        Vector3(min.x, max.y, max.z),
        Vector3(max.x, min.y, min.z),
        Vector3(min.x, min.y, min.z),
        Vector3(min.x, max.y, min.z),
        Vector3(max.x, max.y, min.z)
    };

    VertexBuffer vertexBuffer(
        sizeof(vertices[0]),
        sizeof(vertices) / sizeof(vertices[0]),
        vertices,
        VertexBuffer::Usage::Static
    );

    const GLushort indices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        0, 5,
        1, 4,
        2, 7,
        3, 6,
        4, 5,
        5, 6,
        6, 7,
        7, 4
    };

    IndexBuffer indexBuffer(
        IndexBuffer::Format::UnsignedShort,
        sizeof(indices) / sizeof(indices[0]),
        indices,
        IndexBuffer::Usage::Static
    );

    device_->setVertexFormat(extentsVertexFormat_);
    device_->setVertexBuffer(&vertexBuffer);
    device_->setIndexBuffer(&indexBuffer);

    device_->drawPrimitives(Device::PrimitiveType::Lines);

    device_->setIndexBuffer(0);
    device_->setVertexBuffer(0);
    device_->setVertexFormat(0);
}

void GameProgram::tick(const float dt)
{
    // update scene
    rootNode_->update(dt);



    // update bullets

    BulletVector::iterator iter = bullets_.begin();

    while (iter != bullets_.end())
    {
        Bullet* const p = *iter;

        if (p->active == false)
        {
            ++iter;
            continue;
        }

        p->life -= dt;

        if (p->life <= 0.0f)
        {
            // TODO: it would be more accurate to test collisions for the
            // remaining lifetime

            delete p;
            iter = bullets_.erase(iter);
        }
        else
        {
            const Vector3 gravity(0.0f, -50.0f, 0.0f);

            const Vector3 startPoint = p->shape.center;
            const Vector3 endPoint = startPoint + p->velocity * dt;
            //const Vector3 endPoint = startPoint + normalize(startPoint + p->velocity * dt - startPoint);
            const LineSegment3 segment(startPoint, endPoint);

            p->shape.center = endPoint;
            p->velocity += gravity * dt;

            static SegmentMeshIntersectionQuery query;
            query.init(segment);
            rootNode_->accept(&query);
/*
            static PointLitGeometryQuery query;
            query.reset();
            query.init(p->shape);
            rootNode_->accept(&query);

            // TODO: would go boom if this would destroy all intersecting
            // mesh nodes and the mesh node list contains a child and a
            // parent and the parent is deleted first...

            if (query.numMeshNodes() > 0)
            {
                // TODO: destroys only the first (random) intersection
                MeshNode* const firstIntersection = query.meshNode(0);
                firstIntersection->parent()->detachChild(firstIntersection);
                delete firstIntersection;

                delete p;
                iter = bullets_.erase(iter);
            }
            else
            {
                ++iter;
            }
*/
            if (query.meshNode() != 0)
            {
                MeshNode* const meshNode = query.meshNode();

                // HACK: bullets either destroy or stick based on their color
                if (p->color.y > 0.75f)
                {
                    meshNode->parent()->detachChild(meshNode);
                    delete meshNode;
                }
                else
                {
                    const Vector3 direction = normalize(endPoint - startPoint);
                    const Vector3 offset = -0.1f * direction;

                    const Vector3 worldSpaceIntersection = mix(startPoint, endPoint, query.tEnter()) + offset;
                    const Vector3 modelSpaceIntersection = transformByInverse(worldSpaceIntersection, meshNode->worldTransform());

                    const Vector3 lightColor = Vector3(p->color.x, p->color.y, p->color.z);

                    PointLightNode* const pointLightNode = new PointLightNode();
                    pointLightNode->setTranslation(modelSpaceIntersection);
                    pointLightNode->setLightColor(lightColor);
                    pointLightNode->setLightRange(5.0f);
                    pointLightNode->attachController(new LightFadeOutController(5.0f, lightColor));
                    //pointLightNode->attachController(new SuicideController(1.0f));
                    meshNode->attachChild(pointLightNode);
                }

                delete p;
                iter = bullets_.erase(iter);

//                p->active = false;
//                p->shape.center = worldSpaceIntersection;
//                ++iter;
            }
            else
            {
                ++iter;
            }
        }
    }

    return;

    const float kx = 75.0f;
    const float ky = 37.5f;
    const float kz = 75.0f;

    static const Transform3 transforms[] = {
        Transform3(Vector3( -kx, -ky,   kz), Matrix3x3::yRotation(-0.50f * Math::pi()), 1.0f),
        Transform3(Vector3(0.0f, -ky,   kz), Matrix3x3::yRotation(-0.50f * Math::pi()), 1.0f),

        Transform3(Vector3(  kx, -ky,   kz), Matrix3x3::yRotation( 0.00f * Math::pi()), 1.0f),
        Transform3(Vector3(  kx, -ky, 0.0f), Matrix3x3::yRotation( 0.00f * Math::pi()), 1.0f),

        Transform3(Vector3(  kx, -ky,  -kz), Matrix3x3::yRotation( 0.50f * Math::pi()), 1.0f),
        Transform3(Vector3( -kx, -ky,  -kz), Matrix3x3::yRotation( 0.50f * Math::pi()), 1.0f),

        // ascend
        Transform3(Vector3( -kx, -ky,  -kz), Matrix3x3::yRotation(-0.75f * Math::pi()), 1.0f),
        Transform3(Vector3( -kx,  ky,  -kz), Matrix3x3::yRotation(-0.75f * Math::pi()), 1.0f),

        Transform3(Vector3( -kx,  ky,   kz), Matrix3x3::yRotation(-0.50f * Math::pi()), 1.0f),
        Transform3(Vector3(0.0f,  ky,   kz), Matrix3x3::yRotation(-0.50f * Math::pi()), 1.0f),

        Transform3(Vector3(  kx,  ky,   kz), Matrix3x3::yRotation( 0.00f * Math::pi()), 1.0f),
        Transform3(Vector3(  kx,  ky, 0.0f), Matrix3x3::yRotation( 0.00f * Math::pi()), 1.0f),

        Transform3(Vector3(  kx,  ky,  -kz), Matrix3x3::yRotation( 0.50f * Math::pi()), 1.0f),
        Transform3(Vector3( -kx,  ky,  -kz), Matrix3x3::yRotation( 0.50f * Math::pi()), 1.0f),

        // descend
        Transform3(Vector3(-kx,  ky,  -kz), Matrix3x3::yRotation(-0.75f * Math::pi()), 1.0f),
        Transform3(Vector3(-kx, -ky,  -kz), Matrix3x3::yRotation(-0.75f * Math::pi()), 1.0f)
    };

    const int numFrames = sizeof(transforms) / sizeof(Transform3);
    const float frameTime = 4.0f;

    static int frame = 0;
    static float t = 0.0f;

    t += dt;

    while (t > frameTime)
    {
        frame = (frame + 1) % numFrames;
        t -= frameTime;
    }

    const float scaledT = t / frameTime;

    const int nextFrame = (frame + 1) % numFrames;
    const Transform3 transform = slerp(transforms[frame], transforms[nextFrame], scaledT);

    camera_->setTransform(transform);
}

void GameProgram::onQuit()
{
    running = false;
}

// dx, dy, and dz are half-widths on x, y and z axes, respectively
Mesh* createBox(const float dx, const float dy, const float dz)
{
    const Vector3 positions[] = {
        Vector3(-dx, -dy,  dz),
        Vector3( dx, -dy,  dz),
        Vector3( dx,  dy,  dz),
        Vector3(-dx,  dy,  dz),
        Vector3(-dx, -dy, -dz),
        Vector3( dx, -dy, -dz),
        Vector3( dx,  dy, -dz),
        Vector3(-dx,  dy, -dz)
    };

    const Vector2 texCoords[] = {
        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f)
    };

    const int indices[] = {
        0, 1, 2,
        0, 2, 3,
        5, 4, 7,
        5, 7, 6,
        4, 0, 3,
        4, 3, 7,
        1, 5, 6,
        1, 6, 2,
        4, 5, 1,
        4, 1, 0,
        3, 2, 6,
        3, 6, 7
    };

    Mesh* const mesh = new Mesh(12);
    Mesh::Vertex* const vertices = mesh->vertices();

    for (int i = 0; i < 36; ++i)
    {
        vertices[i].position = positions[indices[i]];

        switch (i % 6)
        {
            case 0: vertices[i].texCoord = texCoords[0]; break;
            case 1: vertices[i].texCoord = texCoords[1]; break;
            case 2: vertices[i].texCoord = texCoords[2]; break;
            case 3: vertices[i].texCoord = texCoords[0]; break;
            case 4: vertices[i].texCoord = texCoords[2]; break;
            case 5: vertices[i].texCoord = texCoords[3]; break;

            default:
                GRAPHICS_RUNTIME_ASSERT(false);
                break;
        }
    }

    mesh->generateNormalsAndTangents();
    return mesh;
}

void GameProgram::test()
{
    Mesh* const boxMesh = createBox(0.5f, 0.5f, 0.5f);
    meshManager_.loadResource("box", boxMesh);

    VertexBuffer* const boxVertexBuffer = new VertexBuffer(
        sizeof(Mesh::Vertex),
        boxMesh->numVertices(),
        boxMesh->vertices(),
        VertexBuffer::Usage::Static
    );

    vertexBufferManager_.loadResource("box", boxVertexBuffer);

    // add some point lights

    Node* const lightGroup = new Node;

    const float angleStep = Math::pi() * 2.0 / 5.0;
    const float heightStep = 75.0f;
    const float radius = 150.0f;
    const float range = 200.0f;

    PointLightNode* pointLightNode = new PointLightNode();
    pointLightNode->setTranslation(Vector3(radius * Math::cos(0 * angleStep), -2 * heightStep, radius * Math::sin(0 * angleStep)));
    pointLightNode->setLightColor(Vector3(1.00f, 0.25f, 0.25f));
    pointLightNode->setLightRange(range);

    MeshNode* const pointLightMesh = new MeshNode();
    pointLightMesh->setScaling(1.0f);
    pointLightMesh->setMesh(boxMesh);
    pointLightMesh->setVertexBuffer(boxVertexBuffer);
    pointLightMesh->updateModelExtents();
    pointLightMesh->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        pointLightNode->lightColor(),
        Vector3(0.0f, 0.0f, 0.0f),
        128.0f)
    );

    pointLightNode->attachChild(pointLightMesh);
    lightGroup->attachChild(pointLightNode);
/*
    pointLightNode = pointLightNode->clone();
    pointLightNode->setTranslation(Vector3(radius * Math::cos(1 * angleStep), -1 * heightStep, radius * Math::sin(1 * angleStep)));
    pointLightNode->setLightColor(Vector3(0.75f, 0.75f, 0.25f));
    pointLightNode->setLightRange(range);
    static_cast<MeshNode*>(pointLightNode->child(0))->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        pointLightNode->lightColor(),
        Vector3(0.0f, 0.0f, 0.0f),
        128.0f)
    );
    lightGroup->attachChild(pointLightNode);
*/
    pointLightNode = pointLightNode->clone();
    pointLightNode->setTranslation(Vector3(radius * Math::cos(2 * angleStep), 0 * heightStep, radius * Math::sin(2 * angleStep)));
    pointLightNode->setLightColor(Vector3(0.25f, 1.00f, 0.25f));
    pointLightNode->setLightRange(range);
    static_cast<MeshNode*>(pointLightNode->child(0))->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        pointLightNode->lightColor(),
        Vector3(0.0f, 0.0f, 0.0f),
        128.0f)
    );
    lightGroup->attachChild(pointLightNode);
/*
    pointLightNode = pointLightNode->clone();
    pointLightNode->setTranslation(Vector3(radius * Math::cos(3 * angleStep), 1 * heightStep, radius * Math::sin(3 * angleStep)));
    pointLightNode->setLightColor(Vector3(0.25f, 0.75f, 0.75f));
    pointLightNode->setLightRange(range);
    static_cast<MeshNode*>(pointLightNode->child(0))->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        pointLightNode->lightColor(),
        Vector3(0.0f, 0.0f, 0.0f),
        128.0f)
    );
    lightGroup->attachChild(pointLightNode);
*/
    pointLightNode = pointLightNode->clone();
    pointLightNode->setTranslation(Vector3(radius * Math::cos(4 * angleStep), 2 * heightStep, radius * Math::sin(4 * angleStep)));
    pointLightNode->setLightColor(Vector3(0.25f, 0.25f, 1.00f));
    pointLightNode->setLightRange(range);
    static_cast<MeshNode*>(pointLightNode->child(0))->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        pointLightNode->lightColor(),
        Vector3(0.0f, 0.0f, 0.0f),
        128.0f)
    );
    lightGroup->attachChild(pointLightNode);

    rootNode_->attachChild(lightGroup);



    // create some boxes

    Node* boxGroup = new Node;
    const float scaling = 17.5f;

    const int count = 10;
    //const float offset = 2.5f * scaling;
    const float offset = 2.5f * 15.0f;
    const float displacement = -(offset * (count - 1)) / 2.0f;

    for (int x = 0; x < count; ++x)
    {
        for (int y = 0; y < count; ++y)
        {
            for (int z = 0; z < count; ++z)
            {
                MeshNode* const meshNode = new MeshNode();
                meshNode->setScaling(scaling);
                meshNode->setMesh(boxMesh);
                meshNode->setVertexBuffer(boxVertexBuffer);
                meshNode->updateModelExtents();

                if (x == 0 && y == 0)
                {
                    meshNode->setEffect(createNoTextureMeshEffect(
                        &programManager_,
                        Vector3(1.0f, 1.0f, 1.0f),
                        Vector3(1.0f, 1.0f, 1.0f),
                        Vector3(0.75f, 0.0f, 0.0f),
                        Vector3(1.0f, 1.0f, 1.0f),
                        128.0f)
                    );
                }
                else
                {
                    const int fix = y % 2 + z % 2;

                    if ((y * count + x + fix) % 2 == 0)
                    {
                        meshNode->setEffect(noTextureMeshEffect_->clone());
                    }
                    else
                    {
                        meshNode->setEffect(dgnsTextureMeshEffect_->clone());
                    }
                }

                meshNode->setTranslation(Vector3(
                    displacement + x * offset,
                    displacement + y * offset,
                    displacement + z * offset
                ));

                boxGroup->attachChild(meshNode);
            }
        }
    }

    constructOctTree(boxGroup, -1, 2);
    rootNode_->attachChild(boxGroup);



    // load a model
/*
    ModelReader modelReader(&meshManager_, &vertexBufferManager_);

    Effect* const effect = createNoTextureMeshEffect(
        &programManager_,
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        128.0f
    );

    Node* const model = modelReader.read("data/models/tank.3DS", *effect);
    model->setTranslation(Vector3(-350.0f, 25.0f, 0.0f));
    model->setRotation(Matrix3x3::xRotation(-Math::pi() / 2.0f));
    model->setScaling(1.0f);

//    Node* const model = modelReader.read("data/models/ionic_temple.3DS", *effect);
//    model->setTranslation(Vector3(0.0f, -175.0f, 0.0f));
//    model->setRotation(Matrix3x3::xRotation(Math::pi()));
//    model->setScaling(20.0f);

//    Node* const model = modelReader.read("data/models/ship2.3DS", *effect);
//    model->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
//    model->setRotation(Matrix3x3::xRotation(Math::pi() / 2.0f));
//    model->setScaling(2.0f);

    constructOctTree(model, -1, 2);
    rootNode_->attachChild(model);

    delete effect;
*/

/*
    Mesh* const triangleMesh = new Mesh(1);
    triangleMesh->vertex(0).position = Vector3(0.0f, 0.0f, 0.0f);
    triangleMesh->vertex(1).position = Vector3(1.0f, 0.0f, 0.0f);
    triangleMesh->vertex(2).position = Vector3(0.0f, 1.0f, 0.0f);
    triangleMesh->generateNormalsAndTangents();

    meshManager_.loadResource("triangle", triangleMesh);

    VertexBuffer* const triangleVertexBuffer = new VertexBuffer(
        sizeof(Mesh::Vertex),
        triangleMesh->numVertices(),
        triangleMesh->vertices(),
        VertexBuffer::Usage::Static
    );

    vertexBufferManager_.loadResource("triangle", triangleVertexBuffer);

    MeshNode* const meshNode = new MeshNode();
    meshNode->setRotation(Matrix3x3::yRotation(Math::pi() / 4.0f));
    meshNode->setScaling(50.0f);
    meshNode->setMesh(boxMesh);
    meshNode->setVertexBuffer(boxVertexBuffer);
    //meshNode->setMesh(triangleMesh);
    //meshNode->setVertexBuffer(triangleVertexBuffer);
    meshNode->updateModelExtents();
    meshNode->setEffect(createNoTextureMeshEffect(
        &programManager_,
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(0.75f, 0.0f, 0.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        128.0f
    ));
    //lightGroup->attachChild(meshNode);
    rootNode_->attachChild(meshNode);
*/


    camera_->setTranslation(Vector3(-75.0f - 37.5f / 2.0f, 0.0f, 150.0f));
    camera_->setRotation(Matrix3x3::identity());
}

GameProgram::~GameProgram()
{
    delete device_;
    delete rootNode_;
    delete camera_;

    delete extentsVertexFormat_;
    delete meshVertexFormat_;
    delete particleVertexFormat_;
    delete shadowVertexFormat_;

    delete shadowVertexBuffer_;

    delete dgnsTextureMeshEffect_;
    delete noTextureMeshEffect_;
    delete extentsEffect_;
    delete shadowEffect_;
    delete particleEffect_;
}

void GameProgram::initEffects()
{
    dgnsTextureMeshEffect_ = createDGNSTextureMeshEffect(
        &programManager_,
        textureManager_.getResource("diffuse"),
        textureManager_.getResource("glow"),
        textureManager_.getResource("normal"),
        textureManager_.getResource("specular"),
        128.0f
    );

    noTextureMeshEffect_ = createNoTextureMeshEffect(
        &programManager_,
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(1.0f, 1.0f, 1.0f),
        128.0f
    );

    extentsEffect_ = createExtentsEffect(&programManager_);
    shadowEffect_ = createShadowEffect(&programManager_);

    particleEffect_ = createParticleEffect(
        &programManager_,
        textureManager_.getResource("particle")
    );
}
