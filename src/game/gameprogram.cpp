/**
 * @file game/gameprogram.cpp
 * @author Marko Silokunnas
 */

#include "gameprogram.h"

#include <cstring>

#include <iostream>

// TODO: REALLY quick & dirty
#include <geometry/math.h>
#include <geometry/transform2.h>
#include <graphics/color3.h>
#include <graphics/color4.h>
#include <graphics/meshnode.h>
#include <graphics/cameranode.h>
#include <graphics/groupnode.h>
#include <graphics/drawparams.h>
#include <graphics/predrawparams.h>
#include <graphics/renderqueue.h>
#include <graphics/runtimeassert.h>
#include <graphics/modelreader.h>
#include <graphics/visibilitytest.h>

#include <graphics/material.h>
#include <graphics/floatvariable.h>
#include <graphics/sampler2dvariable.h>
#include <graphics/vec3variable.h>

#include <geometry/sphere.h>

GameProgram::GameProgram()
:   configuration(),
    mixer_(),
    renderer_(0),
    ship(NULL),
    testObject(NULL),
    camera_(0),
    rootNode_(0),
    drawExtents_(false),
    drawShadowVolumes_(false),
    diffuseMipmappingOn(true),
    glowMipmappingOn(true),
    normalMipmappingOn(false),
    specularMipmappingOn(true),
    rotateLights(false),
    anisotropicFilteringOn(true),
    programManager_(),
    meshManager_(),
    textureManager_(),
    shadowVertexFormat_(0),
    shadowVertexBuffer_(0)
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

    renderer_ = new Renderer(width, height);
    renderer_->setClearColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));
    renderer_->setClearDepth(1.0);
    renderer_->setClearStencil(0);

    shadowVertexFormat_ = new VertexFormat(1);
    shadowVertexFormat_->setAttribute(
        0,
        VertexAttribute::Type::Float3,
        VertexAttribute::Usage::Position
    );
    shadowVertexFormat_->compile();

    shadowVertexBuffer_ = new VertexBuffer(
        24,
        sizeof(Vector3),
        0,
        VertexBuffer::Usage::Dynamic
    );


    // init textures

    Texture* texture = new Texture();
    texture->loadImage("data/textures/diffuse.tga");
    texture->generateMipmap();
    textureManager_.loadResource("diffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/specular.tga");
    texture->generateMipmap();
    textureManager_.loadResource("specular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/glow.tga");
    texture->generateMipmap();
    textureManager_.loadResource("glow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/normal.tga");
    texture->generateMipmap();
    textureManager_.loadResource("normal", texture);

    texture = new Texture();
    texture->loadImage("data/textures/particle.tga");
    texture->generateMipmap();
    textureManager_.loadResource("particle", texture);

    // init scene

    rootNode_ = new GroupNode();


    // init camera

    camera_ = new CameraNode();
    camera_->setPerspectiveProjection(45.0f, aspectRatio, 1.0f, 1000.0f);

    testObject = new GameObject();
    testObject->setGraphicalPresentation( camera_ );
    testObject->attachController( &testController );


//    camera_->setOrthographicProjection(
//        -150.0f * aspectRatio, 150.0f * aspectRatio,
//        -150.0f, 150.0f,
//        -250.0f, 250.0f
//    );

    // for testing the frustum culling
//    ProjectionSettings s = camera_->projectionSettings();
//    std::swap(s.left, s.right);
//    std::swap(s.bottom, s.top);
//    std::swap(s.near, s.far);
//    camera_->setProjectionSettings(s);

    // TODO: quick & dirty
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

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_ESCAPE))
        {
            running = false;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F1))
        {
            drawExtents_ = !drawExtents_;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F2))
        {
            diffuseMipmappingOn = !diffuseMipmappingOn;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F3))
        {
            glowMipmappingOn = !glowMipmappingOn;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F4))
        {
            normalMipmappingOn = !normalMipmappingOn;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F5))
        {
            specularMipmappingOn = !specularMipmappingOn;
        }

        if(keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F6))
        {
            rotateLights = !rotateLights;
        }

        if( keyboard.keyWasPressedInThisFrame( Keyboard::KEY_F7 ) )
        {
            anisotropicFilteringOn = !anisotropicFilteringOn;
        }


        if( keyboard.keyWasPressedInThisFrame( Keyboard::KEY_F8 ) )
        {
            mouseBoundToScreen = !mouseBoundToScreen;
        }

        if( keyboard.keyWasPressedInThisFrame( Keyboard::KEY_F12 ) )
        {
            drawShadowVolumes_ = !drawShadowVolumes_;
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

        if( mouse.mouseButtonPressedInThisFrame( Mouse::MOUSEBUTTON_LEFT ) )
        {
            std::cout << "left mouse button pressed!" << std::endl;
        }
        if( mouse.mouseButtonPressedInThisFrame( Mouse::MOUSEBUTTON_RIGHT ) )
        {
            std::cout << "right mouse button pressed!" << std::endl;
        }
        if( mouse.mouseButtonPressedInThisFrame( Mouse::MOUSEBUTTON_MIDDLE ) )
        {
            std::cout << "middle mouse button pressed!" << std::endl;
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
    if( diffuseMipmappingOn )
    {
        textureManager_.getResource("diffuse")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
    }
    else
    {
        textureManager_.getResource("diffuse")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
    }

    if( glowMipmappingOn )
    {
        textureManager_.getResource("glow")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
    }
    else
    {
        textureManager_.getResource("glow")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
    }

    if( normalMipmappingOn )
    {
        textureManager_.getResource("normal")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
    }
    else
    {
        textureManager_.getResource("normal")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
    }

    if( specularMipmappingOn )
    {
        textureManager_.getResource("specular")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
    }
    else
    {
        textureManager_.getResource("specular")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
    }

    if( anisotropicFilteringOn )
    {
        textureManager_.getResource("diffuse")->activateAnisotropicFiltering();
    }
    else
    {
        textureManager_.getResource("diffuse")->disableAnisotropicFiltering();
    }

    // TODO: get rid of all direct OpenGL calls

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // these are the defaults
    //glDepthRange(0.0, 1.0);
    //glClearDepth(1.0);

    glEnable(GL_CULL_FACE);

    // TODO: Is there a bug in Renderer implementation or is this a driver bug?
    //
    // OpenGL specification says that buffer writemasks affect glClear and that
    // if color channel writes have been disabled with glColorMask, no change
    // is made to the disabled components of any pixel in any of the color
    // buffers, regardless of the drawing operation attempted.
    //
    // With EVGA GeForce GTX470 on Windows7 the left border of the screen
    // starts flickering if one or more color channel writes are disabled. To
    // my understanding, the left border should preserve maximum color values
    // for the disabled channels without flickering since all color buffer
    // channels are initially cleared to their maximum values below.

    // these are for producing the flickering bug descibed above
    //renderer_->setClearColor(Color4(1.0f, 1.0f, 1.0f, 0.0f));
    //renderer_->clearBuffers(true, false, false, RectangleI(0, 0, width / 32, height));
    //renderer_->setClearColor(Color4(0.0f, 0.0f, 0.0f, 0.0f));

    // set, for example, enableBlue to false to produce the flickering bug
    // descibed above

    // specify which color buffer channels can be written to
    const bool enableRed = true;
    const bool enableGreen = true;
    const bool enableBlue = true;
    const bool enableAlpha = true;

    renderer_->setColorMask(enableRed, enableGreen, enableBlue, enableAlpha);
    renderer_->clearBuffers(true, true, false);


    // TODO: REALLY quick & dirty

    static RenderQueue renderQueue;
    static VisibilityTest visibilityTest;


    // predraw step

    renderQueue.clear();
    visibilityTest.init(*camera_);

    PredrawParams predrawParams;
    predrawParams.setRenderQueue(&renderQueue);
    predrawParams.setVisibilityTest(&visibilityTest);

    // setting the second parameter to false disables frustum culling
    rootNode_->predraw(predrawParams, true);
    renderQueue.sort();


    // unlit render pass

    DrawParams drawParams;
    drawParams.viewMatrix = camera_->worldToViewMatrix();
    // TODO: load projection matrix directly to the shader?
    drawParams.projectionMatrix = camera_->projectionMatrix();
    drawParams.worldToViewRotation = transpose(camera_->worldTransform().rotation);
    drawParams.cameraToWorld = camera_->worldTransform();
    drawParams.renderer = renderer_;

    drawParams.program = programManager_.load("data/shaders/unlit.vs", "data/shaders/unlit.fs");

    Material unlitMaterial;
    unlitMaterial.setProgram(drawParams.program);
    unlitMaterial.addVariable(new Vec3Variable("ambient", Vector3(0.1f, 0.1f, 0.1f)));
    unlitMaterial.addVariable(new Sampler2DVariable("diffuseMap", textureManager_.getResource("diffuse")));
    unlitMaterial.addVariable(new Sampler2DVariable("glowMap", textureManager_.getResource("glow")));

    if (unlitMaterial.link() == false)
    {
        GRAPHICS_RUNTIME_ASSERT(false);
    }

    unlitMaterial.bind();

    // unlit render pass
    renderQueue.draw(drawParams);

    unlitMaterial.unbind();

    // ...

    const float step = Math::pi() * 2.0 / 5.0;

    Vector3 lightPositions[] = {
        Vector3(150.0f * Math::cos(0 * step), -75.0f, 150.0f * Math::sin(0 * step)),
        Vector3(150.0f * Math::cos(1 * step), -37.5f, 150.0f * Math::sin(1 * step)),
        Vector3(150.0f * Math::cos(2 * step),   0.0f, 150.0f * Math::sin(2 * step)),
        Vector3(150.0f * Math::cos(3 * step),  37.5f, 150.0f * Math::sin(3 * step)),
        Vector3(150.0f * Math::cos(4 * step),  75.0f, 150.0f * Math::sin(4 * step))
    };

    const Color3 lightColors[] = {
        Color3(1.00f, 0.25f, 0.25f),
        Color3(0.75f, 0.75f, 0.25f),
        Color3(0.25f, 1.00f, 0.25f),
        Color3(0.25f, 0.75f, 0.75f),
        Color3(0.25f, 0.25f, 1.00f)
    };

    const float lightRanges[] = {
        175.0f,
        175.0f,
        175.0f,
        175.0f,
        175.0f
    };

    const int numLights = sizeof(lightPositions) / sizeof(lightPositions[0]);

    Vector3 worldLightPositions[numLights];
    Vector3 viewLightPositions[numLights];

    static float lightRotation = 0.0f;

    const Transform3 t(
        Vector3::zero(),
        Matrix3x3::yRotation(lightRotation),
        1.0f
    );

    transform(lightPositions, lightPositions + numLights, worldLightPositions, t);
    transform(worldLightPositions, worldLightPositions + numLights, viewLightPositions, inverse(camera_->worldTransform()));

    // for each light
    for (int lightIndex = 0; lightIndex < numLights; ++lightIndex)
    {
    // light effect sphere
    const Sphere effectSphere(worldLightPositions[lightIndex], lightRanges[lightIndex]);

    // TODO: check if the light effect sphere intersects the view frustum

    // static to maintain capacity
    static std::vector<Vector3> shadowVertices;
    shadowVertices.clear();

    // generate shadow geometry for this light
    for (size_t i = 0; i < geometryNodes_.size(); ++i)
    {
        if (intersect(geometryNodes_[i]->worldExtents(), effectSphere) == false)
        {
            // the geometry node is not within the light effect sphere, next
            continue;
        }

        const Transform3 transform = geometryNodes_[i]->worldTransform();
        const Mesh* mesh = static_cast<MeshNode*>(geometryNodes_[i])->mesh();

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
            const Vector3 d0 = p0 - worldLightPositions[lightIndex];
            const Vector3 d1 = p1 - worldLightPositions[lightIndex];
            const Vector3 d2 = p2 - worldLightPositions[lightIndex];

            const float length0 = length(d0);
            const float length1 = length(d1);
            const float length2 = length(d2);

            // minimum distance from light source to the vertices
            const float minDistance = Math::min(Math::min(length0, length1), length2);

            // TODO: looks ok in most cases but actually this is not enough,
            // make it so that the triangle centroid would be extruded to the
            // light effect sphere boundary
            const float projectionDistance = lightRanges[lightIndex] - minDistance;

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

    // clear the stencil buffer
    renderer_->clearBuffers(false, false, true);

    drawParams.program = programManager_.load("data/shaders/shadow.vs", "data/shaders/shadow.fs");

    renderer_->setProgram(drawParams.program);
    renderer_->setVertexFormat(shadowVertexFormat_);

    glUniformMatrix4fv(glGetUniformLocation(drawParams.program->id(), "viewMatrix"), 1, false, drawParams.viewMatrix.data());
    glUniformMatrix4fv(glGetUniformLocation(drawParams.program->id(), "projectionMatrix"), 1, false, drawParams.projectionMatrix.data());

    const GLint coordLocation = glGetAttribLocation(drawParams.program->id(), "position");
    glEnableVertexAttribArray(coordLocation);

    // HACK: fast vertex buffer update
    glBindBuffer(GL_ARRAY_BUFFER, shadowVertexBuffer_->id());
    glBufferData(
        GL_ARRAY_BUFFER,
        shadowVertices.size() * shadowVertexBuffer_->elementSize(),
        &shadowVertices[0],
        GL_DYNAMIC_DRAW
    );
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, 0);
/*
    glVertexAttribPointer(
        coordLocation,
        3,
        GL_FLOAT,
        false,
        0,
        &shadowVertices[0]
    );
*/
    // disable color buffer writes
    renderer_->setColorMask(false, false, false, false);

    // disable depth buffer writes
    glDepthMask(GL_FALSE);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 0, ~0);

    glStencilOpSeparate(
        GL_BACK,    // set stencil settings for back-facing polygons
        GL_KEEP,    // stencil fail operation, has no effect
        GL_INCR,    // depth fail operation, increment stencil value
        GL_KEEP     // depth pass operation, do nothing
    );

    glStencilOpSeparate(
        GL_FRONT,   // set stencil settings for front-facing polygons
        GL_KEEP,    // stencil fail operation, has no effect
        GL_DECR,    // depth fail operation, decrement stencil value
        GL_KEEP     // depth pass operation, do nothing
    );

    glCullFace(GL_FRONT);
    glDrawArrays(GL_TRIANGLES, 0, shadowVertices.size());

    glCullFace(GL_BACK);
    glDrawArrays(GL_TRIANGLES, 0, shadowVertices.size());

    // restore render state
    glDisable(GL_STENCIL_TEST);
    glDepthMask(GL_TRUE);

    renderer_->setColorMask(
        enableRed,
        enableGreen,
        enableBlue,
        enableAlpha);

    //if (drawShadowVolumes_ && lightIndex == 0)
    if (drawShadowVolumes_)
    {
        // render shadow volumes
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLES, 0, shadowVertices.size());
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_CULL_FACE);
    }

    // HACK: fast vertex buffer update
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisableVertexAttribArray(coordLocation);

    renderer_->setVertexFormat(0);
    renderer_->setProgram(0);

    // end shadow pass --------------------------------------------------------

    drawParams.program = programManager_.load("data/shaders/lit.vs", "data/shaders/lit.fs");

    Material litMaterial;
    litMaterial.setProgram(drawParams.program);
    litMaterial.addVariable(new FloatVariable("specularExponent", 128.0f));
    litMaterial.addVariable(new Sampler2DVariable("diffuseMap", textureManager_.getResource("diffuse")));
    litMaterial.addVariable(new Sampler2DVariable("specularMap", textureManager_.getResource("specular")));
    litMaterial.addVariable(new Sampler2DVariable("normalMap", textureManager_.getResource("normal")));

    if (litMaterial.link() == false)
    {
        GRAPHICS_RUNTIME_ASSERT(false);
    }

    litMaterial.bind();

    // ...

    const GLint lightPositionLocation = glGetUniformLocation(drawParams.program->id(), "lightPosition");
    const GLint lightColorLocation = glGetUniformLocation(drawParams.program->id(), "lightColor");
    const GLint lightRangeLocation = glGetUniformLocation(drawParams.program->id(), "lightRange");

    glUniform3fv(lightPositionLocation, 1, viewLightPositions[lightIndex].data());
    glUniform3fv(lightColorLocation, 1, lightColors[lightIndex].data());
    glUniform1f(lightRangeLocation, lightRanges[lightIndex]);

    // ...

    glDepthFunc(GL_LEQUAL);

    //GLint stencilBits;
    //glGetIntegerv(GL_STENCIL_BITS, &stencilBits);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 0x00, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    // lit render pass
    //renderQueue.draw(drawParams);
    for (int i = 0; i < renderQueue.numGeometryNodes(); ++i)
    {
        // render only if the geometry node is within the light effect sphere
        if (intersect(renderQueue.geometryNode(i)->worldExtents(), effectSphere))
        {
            renderQueue.geometryNode(i)->draw(drawParams);
        }
    }

    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);

    litMaterial.unbind();

    } // for each light

    if (rotateLights)
    {
        lightRotation = Math::mod(lightRotation + deltaTime * 0.1f, 2.0f * Math::pi());
    }

    // quick & dirty point sprite test

    drawParams.program = programManager_.load("data/shaders/particle.vs", "data/shaders/particle.fs");

    VertexFormat vertexFormat(3);
    vertexFormat.setAttribute(0, VertexAttribute::Type::Float3, VertexAttribute::Usage::Position);
    vertexFormat.setAttribute(1, VertexAttribute::Type::Float4, VertexAttribute::Usage::Color);
    vertexFormat.setAttribute(2, VertexAttribute::Type::Float1, VertexAttribute::Usage::PointSize);
    vertexFormat.compile();

    float components[numLights * 8];

    for (int i = 0; i < numLights; ++i)
    {
        float* const data = components + i * 8;

        // position
        data[0] = worldLightPositions[i].x;
        data[1] = worldLightPositions[i].y;
        data[2] = worldLightPositions[i].z;

        // color
        data[3] = lightColors[i].r;
        data[4] = lightColors[i].g;
        data[5] = lightColors[i].b;
        data[6] = 1.0f;

        // size
        data[7] = 4.0f;
    }

    VertexBuffer vertexBuffer(
        sizeof(components) / (sizeof(float) * 8),
        sizeof(float) * 8,
        components,
        VertexBuffer::Usage::Static
    );

    BlendState blendState;
    blendState.setEquation(BlendState::Equation::Add);
    blendState.setSrcFactor(BlendState::SrcFactor::SrcAlpha);
    blendState.setDstFactor(BlendState::DstFactor::One);

    DepthState depthState;
    depthState.writeEnabled = false;
    depthState.compareFunc = DepthState::CompareFunc::Less;

    renderer_->setProgram(drawParams.program);
    renderer_->setVertexFormat(&vertexFormat);
    renderer_->setVertexBuffer(&vertexBuffer);
    renderer_->setBlendState(&blendState);
    renderer_->setDepthState(&depthState);
    renderer_->setTexture(0, textureManager_.getResource("particle"));

    const GLint modelViewMatrixLocation = glGetUniformLocation(drawParams.program->id(), "viewMatrix");
    const GLint projectionMatrixLocation = glGetUniformLocation(drawParams.program->id(), "projectionMatrix");
    glUniformMatrix4fv(modelViewMatrixLocation, 1, false, drawParams.viewMatrix.data());
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, drawParams.projectionMatrix.data());

    // TODO: this is deprecated
    glEnable(GL_POINT_SPRITE);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    renderer_->renderPrimitives(Renderer::PrimitiveType::Points);

    // TODO: this is deprecated
    glDisable(GL_POINT_SPRITE);

    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);

    renderer_->setTexture(0, 0);
    renderer_->setDepthState(0);
    renderer_->setBlendState(0);
    renderer_->setVertexBuffer(0);
    renderer_->setVertexFormat(0);
    renderer_->setProgram(0);

    // end of quick & dirty point sprite test

    // needed because not all depth buffer test settings are managed using
    // renderer_
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    if (drawExtents_)
    {
        glDepthFunc(GL_LEQUAL);

        drawParams.program = programManager_.load("data/shaders/extents.vs", "data/shaders/extents.fs");
        renderer_->setProgram(drawParams.program);

        for (int i = 0; i < renderQueue.numGeometryNodes(); ++i)
        {
            drawExtents(renderQueue.geometryNode(i), drawParams);
        }

        for (int i = 0; i < renderQueue.numGroupNodes(); ++i)
        {
            drawExtents(renderQueue.groupNode(i), drawParams);
        }

        renderer_->setProgram(0);
    }

    SDL_GL_SwapBuffers();
}

// TODO: quick & dirty, this does not belong here
void GameProgram::drawExtents(const Node* node, const DrawParams& params)
{
    const Extents3 extents = node->worldExtents();

    const Vector3 min = extents.min;
    const Vector3 max = extents.max;

    VertexFormat vertexFormat(1);
    vertexFormat.setAttribute(0, VertexAttribute::Type::Float3, VertexAttribute::Usage::Position);
    vertexFormat.compile();

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

    const int vertexSize = sizeof(Vector3);

    VertexBuffer vertexBuffer(
        sizeof(vertices) / vertexSize,
        vertexSize,
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
        sizeof(indices) / sizeof(indices[0]),
        indices,
        IndexBuffer::Format::UnsignedShort,
        IndexBuffer::Usage::Static
    );

    const Matrix4x4 mvpMatrix = params.viewMatrix * params.projectionMatrix;

    const GLint mvpMatrixLocation = glGetUniformLocation(params.program->id(), "viewProjectionMatrix");
    glUniformMatrix4fv(mvpMatrixLocation, 1, false, mvpMatrix.data());

    renderer_->setVertexFormat(&vertexFormat);
    renderer_->setVertexBuffer(&vertexBuffer);
    renderer_->setIndexBuffer(&indexBuffer);

    renderer_->renderPrimitives(Renderer::PrimitiveType::Lines);

    renderer_->setIndexBuffer(0);
    renderer_->setVertexBuffer(0);
    renderer_->setVertexFormat(0);
}

void GameProgram::tick( const float deltaTime )
{
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

    t += deltaTime;

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

    GroupNode* groupNode = new GroupNode();

    const float scaling = 17.5f;

    // TODO: quick & dirty
    static VertexBuffer vertexBuffer(
        boxMesh->numVertices(),
        sizeof(Mesh::Vertex),
        boxMesh->vertices(),
        VertexBuffer::Usage::Static
    );

    MeshNode* meshNode = new MeshNode();
    meshNode->setScaling(scaling);
    meshNode->setMesh(boxMesh);
    meshNode->setVertexBuffer(&vertexBuffer);
    meshNode->updateModelExtents();

    const int count = 10;
    //const float offset = 2.5f * scaling;
    const float offset = 2.5f * 15.0f;
    const float displacement = -(offset * (count - 1)) / 2.0f;

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            if (i != 0 || j != 0)
            {
                meshNode = meshNode->clone();
            }

            meshNode->setTranslation(Vector3(displacement + i * offset, 0.0f, displacement + j * offset));
            groupNode->attachChild(meshNode);
            geometryNodes_.push_back(meshNode);
        }
    }

    for (int i = 0; i < count; ++i)
    {
        if (i != 0)
        {
            groupNode = groupNode->clone();
        }

        groupNode->setTranslation(Vector3(0.0f, displacement + i * offset, 0.0f));
        rootNode_->attachChild(groupNode);

        for (int j = 0; j < groupNode->numChildren(); ++j)
        {
            geometryNodes_.push_back(static_cast<GeometryNode*>(groupNode->child(j)));
        }
    }

    //camera_->setTranslation(Vector3(150.0f, -75.0f, 0.0f));
    //camera_->setRotation(Matrix3x3::yRotation(Math::pi() / 2.0));
    camera_->setTranslation(Vector3(0.0f, 0.0f, 150.0f));
    camera_->setRotation(Matrix3x3::identity());
}

GameProgram::~GameProgram()
{
    delete renderer_;
    delete rootNode_;
    delete camera_;
    delete shadowVertexFormat_;
    delete shadowVertexBuffer_;
}
