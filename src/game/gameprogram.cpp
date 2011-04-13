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
#include <graphics/color.h>
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

GameProgram::GameProgram()
:   configuration(),
    mixer_(),
    renderer_(),
    ship(NULL),
    testObject(NULL),
    camera_(0),
    rootNode_(0),
    drawExtents_(true),
    diffuseMipmappingOn(false),
    glowMipmappingOn(false),
    normalMipmappingOn(false),
    specularMipmappingOn(false),
    rotateLights(false),
    anisotropicFilteringOn(false),
    programManager_(),
    meshManager_(),
    textureManager_()
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



    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // these are the defaults
    //glDepthRange(0.0, 1.0);
    //glClearDepth(1.0);

    glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

    Vector3 lightPositions[] = {
        Vector3(150.0f * Math::cos(Math::radians(0.0f)), -75.0f, 150.0f * Math::sin(Math::radians(0.0f))),
        Vector3(150.0f * Math::cos(Math::radians(120.0f)), 0.0f, 150.0f * Math::sin(Math::radians(120.0f))),
        Vector3(150.0f * Math::cos(Math::radians(240.0f)), 75.0f, 150.0f * Math::sin(Math::radians(240.0f)))
    };

    const Vector3 lightColors[] = {
        Vector3(1.0f, 0.5f, 0.5f),
        Vector3(0.5f, 1.0f, 0.5f),
        Vector3(0.5f, 0.5f, 1.0f)
    };

    const float lightRanges[] = {
        250.0f,
        250.0f,
        250.0f
    };

    const int numLights = 3;

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

    glClear(GL_STENCIL_BUFFER_BIT);

    // shadow pass

    drawParams.program = programManager_.load("data/shaders/shadow.vs", "data/shaders/shadow.fs");
    glUseProgram(drawParams.program->id());

    glUniformMatrix4fv(
        glGetUniformLocation(drawParams.program->id(), "viewMatrix"),
        1,
        false,
        drawParams.viewMatrix.data()
    );

    glUniformMatrix4fv(
        glGetUniformLocation(drawParams.program->id(), "projectionMatrix"),
        1,
        false,
        drawParams.projectionMatrix.data()
    );

    for (size_t i = 0; i < geometryNodes_.size(); ++i)
    {
        const Transform3 transform = geometryNodes_[i]->worldTransform();
        const Mesh* mesh = static_cast<MeshNode*>(geometryNodes_[i])->mesh();

        for (int iFace = 0; iFace < mesh->numFaces(); ++iFace)
        {
            const Vector3 n = mesh->normals()[3 * iFace] * transform.rotation;

            Vector3 v0 = ::transform(mesh->vertices()[3 * iFace + 0], transform);
            Vector3 v1 = ::transform(mesh->vertices()[3 * iFace + 1], transform);
            Vector3 v2 = ::transform(mesh->vertices()[3 * iFace + 2], transform);

            // TODO: these do not avoid division by zero
            const Vector3 lightV0 = normalize(v0 - worldLightPositions[lightIndex]);
            const Vector3 lightV1 = normalize(v1 - worldLightPositions[lightIndex]);
            const Vector3 lightV2 = normalize(v2 - worldLightPositions[lightIndex]);

            // if the signs do not differ, this is not a front face
            if (dot(lightV0, n) >= 0.0f)
            {
                continue;
            }

            // not quite but close enoughfor this demo, increasing this will
            // decrease fps
            const float infinity = 150.0f;

            const Vector3 s0 = v0 + infinity * lightV0;
            const Vector3 s1 = v1 + infinity * lightV1;
            const Vector3 s2 = v2 + infinity * lightV2;

            const float offset = 0.1f;

            v0 = v0 + offset * lightV0;
            v1 = v1 + offset * lightV1;
            v2 = v2 + offset * lightV2;

            const Vector3 coords[] = {
                v0, v1, v2, // front cap
                s0, s2, s1, // back cap
                v0, s0, s1,
                v0, s1, v1,
                v1, s1, s2,
                v1, s2, v2,
                v2, s2, s0,
                v2, s0, v0
            };

            const GLint coordLocation = glGetAttribLocation(drawParams.program->id(), "position");
            glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, coords->data());
            glEnableVertexAttribArray(coordLocation);

            // disable color buffer writes
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

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
            glDrawArrays(GL_TRIANGLES, 0, 24);

            glCullFace(GL_BACK);
            glDrawArrays(GL_TRIANGLES, 0, 24);

            // restore render state
            glDisable(GL_STENCIL_TEST);
            glDepthMask(GL_TRUE);
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
/*
            if (lightIndex == 0)
            {
                // render shadow volumes
                glDisable(GL_CULL_FACE);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glDrawArrays(GL_TRIANGLES, 0, 24);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_CULL_FACE);
            }
*/
            glDisableVertexAttribArray(coordLocation);
        }
    }

    // ...

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
    renderQueue.draw(drawParams);

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
        data[3] = lightColors[i].x;
        data[4] = lightColors[i].y;
        data[5] = lightColors[i].z;
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

    renderer_.setProgram(drawParams.program);
    renderer_.setVertexFormat(&vertexFormat);
    renderer_.setVertexBuffer(&vertexBuffer);
    renderer_.setBlendState(&blendState);
    renderer_.setDepthState(&depthState);
    renderer_.setTexture(0, textureManager_.getResource("particle"));

    const GLint modelViewMatrixLocation = glGetUniformLocation(drawParams.program->id(), "viewMatrix");
    const GLint projectionMatrixLocation = glGetUniformLocation(drawParams.program->id(), "projectionMatrix");
    glUniformMatrix4fv(modelViewMatrixLocation, 1, false, drawParams.viewMatrix.data());
    glUniformMatrix4fv(projectionMatrixLocation, 1, false, drawParams.projectionMatrix.data());

    // TODO: this is deprecated
    glEnable(GL_POINT_SPRITE);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    renderer_.renderPrimitives(Renderer::PrimitiveType::Points);

    // TODO: this is deprecated
    glDisable(GL_POINT_SPRITE);

    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);

    renderer_.setTexture(0, 0);
    renderer_.setDepthState(0);
    renderer_.setBlendState(0);
    renderer_.setVertexBuffer(0);
    renderer_.setVertexFormat(0);
    renderer_.setProgram(0);

    // end of quick & dirty point sprite test

    // needed because not all depth buffer test settings are managed using
    // renderer_
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    if (drawExtents_)
    {
        glDepthFunc(GL_LEQUAL);

        drawParams.program = programManager_.load("data/shaders/extents.vs", "data/shaders/extents.fs");
        renderer_.setProgram(drawParams.program);

        for (int i = 0; i < renderQueue.numGeometryNodes(); ++i)
        {
            drawExtents(renderQueue.geometryNode(i), drawParams);
        }

        for (int i = 0; i < renderQueue.numGroupNodes(); ++i)
        {
            drawExtents(renderQueue.groupNode(i), drawParams);
        }

        renderer_.setProgram(0);
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

    renderer_.setVertexFormat(&vertexFormat);
    renderer_.setVertexBuffer(&vertexBuffer);
    renderer_.setIndexBuffer(&indexBuffer);

    renderer_.renderPrimitives(Renderer::PrimitiveType::Lines);

    renderer_.setIndexBuffer(0);
    renderer_.setVertexBuffer(0);
    renderer_.setVertexFormat(0);
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

// dx, dy, and dz are half-widths on x-, y- and z-axes, respectively
Mesh* createBox(const float dx, const float dy, const float dz)
{
    const Vector3 min(-dx, -dy, -dz);
    const Vector3 max( dx,  dy,  dz);

    Vector3 _coords[] = {
        Vector3(min.x, min.y, max.z),
        Vector3(max.x, min.y, max.z),
        Vector3(max.x, max.y, max.z),
        Vector3(min.x, max.y, max.z),
        Vector3(min.x, min.y, min.z),
        Vector3(max.x, min.y, min.z),
        Vector3(max.x, max.y, min.z),
        Vector3(min.x, max.y, min.z)
    };

    Vector2 _texCoords[] = {
        Vector2(0.0f, 0.0f),
        Vector2(1.0f, 0.0f),
        Vector2(1.0f, 1.0f),
        Vector2(0.0f, 1.0f)
    };

    std::vector<Vector3> coords(36);
    // front
    coords[ 0] = _coords[0];
    coords[ 1] = _coords[1];
    coords[ 2] = _coords[2];
    coords[ 3] = _coords[0];
    coords[ 4] = _coords[2];
    coords[ 5] = _coords[3];
    // back
    coords[ 6] = _coords[5];
    coords[ 7] = _coords[4];
    coords[ 8] = _coords[7];
    coords[ 9] = _coords[5];
    coords[10] = _coords[7];
    coords[11] = _coords[6];
    // left
    coords[12] = _coords[4];
    coords[13] = _coords[0];
    coords[14] = _coords[3];
    coords[15] = _coords[4];
    coords[16] = _coords[3];
    coords[17] = _coords[7];
    // right
    coords[18] = _coords[1];
    coords[19] = _coords[5];
    coords[20] = _coords[6];
    coords[21] = _coords[1];
    coords[22] = _coords[6];
    coords[23] = _coords[2];
    // bottom
    coords[24] = _coords[4];
    coords[25] = _coords[5];
    coords[26] = _coords[1];
    coords[27] = _coords[4];
    coords[28] = _coords[1];
    coords[29] = _coords[0];
    // top
    coords[30] = _coords[3];
    coords[31] = _coords[2];
    coords[32] = _coords[6];
    coords[33] = _coords[3];
    coords[34] = _coords[6];
    coords[35] = _coords[7];

    std::vector<Vector2> texCoords(36);
    // front
    texCoords[ 0] = _texCoords[0];
    texCoords[ 1] = _texCoords[1];
    texCoords[ 2] = _texCoords[2];
    texCoords[ 3] = _texCoords[0];
    texCoords[ 4] = _texCoords[2];
    texCoords[ 5] = _texCoords[3];
    // back
    texCoords[ 6] = _texCoords[0];
    texCoords[ 7] = _texCoords[1];
    texCoords[ 8] = _texCoords[2];
    texCoords[ 9] = _texCoords[0];
    texCoords[10] = _texCoords[2];
    texCoords[11] = _texCoords[3];
    // left
    texCoords[12] = _texCoords[0];
    texCoords[13] = _texCoords[1];
    texCoords[14] = _texCoords[2];
    texCoords[15] = _texCoords[0];
    texCoords[16] = _texCoords[2];
    texCoords[17] = _texCoords[3];
    // right
    texCoords[18] = _texCoords[0];
    texCoords[19] = _texCoords[1];
    texCoords[20] = _texCoords[2];
    texCoords[21] = _texCoords[0];
    texCoords[22] = _texCoords[2];
    texCoords[23] = _texCoords[3];
    // bottom
    texCoords[24] = _texCoords[0];
    texCoords[25] = _texCoords[1];
    texCoords[26] = _texCoords[2];
    texCoords[27] = _texCoords[0];
    texCoords[28] = _texCoords[2];
    texCoords[29] = _texCoords[3];
    // top
    texCoords[30] = _texCoords[0];
    texCoords[31] = _texCoords[1];
    texCoords[32] = _texCoords[2];
    texCoords[33] = _texCoords[0];
    texCoords[34] = _texCoords[2];
    texCoords[35] = _texCoords[3];

    // create a mesh with 12 faces
    Mesh* p = new Mesh(12);

    p->setVertices(coords);
    p->setTexCoords(texCoords);
    p->generateFlatNormals();

    return p;
}

void GameProgram::test()
{
    Mesh* const boxMesh = createBox(0.5f, 0.5f, 0.5f);
    meshManager_.loadResource("box", boxMesh);

    GroupNode* groupNode = new GroupNode();

    const float scaling = 17.5f;

    MeshNode* meshNode = new MeshNode();
    meshNode->setScaling(scaling);
    meshNode->setMesh(boxMesh);
    meshNode->updateModelExtents();

    const int count = 6;
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

    camera_->setTranslation(Vector3(0.0f, 0.0f, 50.0f));
    camera_->setRotation(Matrix3x3::identity());
}

GameProgram::~GameProgram()
{
    delete rootNode_;
    delete camera_;
}
