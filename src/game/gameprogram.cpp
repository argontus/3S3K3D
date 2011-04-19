/**
 * @file game/gameprogram.cpp
 * @author Marko Silokunnas
 */

#include "gameprogram.h"

#include <iostream>

#include <graphics/opengl.h>

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
#include "state.h"
#include "introstate.h"
#include "mainmenustate.h"
#include "gamestate.h"
#include "gamemenustate.h"
#include "creditsstate.h"

GameProgram::GameProgram()
:
    mixer_(),
    ship(NULL),
    //testObject(NULL),
    testMenuObject1(NULL),
    testMenuObject2(NULL),
    testMenuObject3(NULL),
    testMenuObject4(NULL),
    camera_(0),
    rootNode_(0),
    drawExtents_(true),
    diffuseMipmappingOn(false),
    glowMipmappingOn(false),
    normalMipmappingOn(false),
    specularMipmappingOn(false),
    rotateLights(false),
    anisotropicFilteringOn(false),
    vertexShaderManager_(),
    fragmentShaderManager_(),
    programManager_(),
    meshManager_(),
    textureManager_(),
    currentState(NULL)


{
    running         = true;
    deltaTicks      = 0;
    deltaTime       = 0;

    changeState(STATE_INTRO);
}

int GameProgram::execute()
{
	if( init() == false ) {
		return -1;
	}

    glewInit();


    // init shader stuff

    // TODO: A helper class for managing shader loading would be nice. Loading
    // shader programs should be as simple as: "I want a shader program called
    // 'default' that uses vertex and fragment shaders
    // 'data/shaders/default.vs' and 'data/shaders/default.fs'". The shader
    // object loading and compilation should happen automatically if they are
    // not already loaded. The shader program manager could own vertex and
    // fragment shader object managers and handle the shader object loading and
    // compilation internally.

    VertexShader* vertexShader = new VertexShader();
    vertexShader->setSourceText(readSourceText("data/shaders/default.vs"));
    vertexShader->compile();
    //const std::string info = vertexShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(vertexShader->compileStatus());
    vertexShaderManager_.loadResource("default", vertexShader);

    vertexShader = new VertexShader();
    vertexShader->setSourceText(readSourceText("data/shaders/extents.vs"));
    vertexShader->compile();
    GRAPHICS_RUNTIME_ASSERT(vertexShader->compileStatus());
    vertexShaderManager_.loadResource("extents", vertexShader);

    vertexShader = new VertexShader();
    vertexShader->setSourceText(readSourceText("data/shaders/test.vs"));
    vertexShader->compile();
    //const std::string info = vertexShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(vertexShader->compileStatus());
    vertexShaderManager_.loadResource("test", vertexShader);

    vertexShader = new VertexShader();
    vertexShader->setSourceText(readSourceText("data/shaders/unlit.vs"));
    vertexShader->compile();
    //const std::string info = vertexShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(vertexShader->compileStatus());
    vertexShaderManager_.loadResource("unlit", vertexShader);

    vertexShader = new VertexShader();
    vertexShader->setSourceText(readSourceText("data/shaders/shadow.vs"));
    vertexShader->compile();
    //const std::string info = vertexShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(vertexShader->compileStatus());
    vertexShaderManager_.loadResource("shadow", vertexShader);

    FragmentShader* fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/default.fs"));
    fragmentShader->compile();
    //const std::string info = fragmentShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("default", fragmentShader);

    fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/extents.fs"));
    fragmentShader->compile();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("extents", fragmentShader);

    fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/test.fs"));
    fragmentShader->compile();
    //const std::string info = fragmentShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("test", fragmentShader);

    fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/unlit.fs"));
    fragmentShader->compile();
    //const std::string info = fragmentShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("unlit", fragmentShader);

    fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/shadow.fs"));
    fragmentShader->compile();
    //const std::string info = fragmentShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("shadow", fragmentShader);

    // program for drawing mesh nodes
    Program* program = new Program();
    program->setVertexShader(vertexShaderManager_.getResource("default"));
    program->setFragmentShader(fragmentShaderManager_.getResource("default"));
    program->link();
    GRAPHICS_RUNTIME_ASSERT(program->linkStatus());
    programManager_.loadResource("default", program);

    // program for drawing node extents
    program = new Program();
    program->setVertexShader(vertexShaderManager_.getResource("extents"));
    program->setFragmentShader(fragmentShaderManager_.getResource("extents"));
    program->link();
    GRAPHICS_RUNTIME_ASSERT(program->linkStatus());
    programManager_.loadResource("extents", program);

    // program for lit render passes
    program = new Program();
    program->setVertexShader(vertexShaderManager_.getResource("test"));
    program->setFragmentShader(fragmentShaderManager_.getResource("test"));
    program->link();
    GRAPHICS_RUNTIME_ASSERT(program->linkStatus());
    programManager_.loadResource("test", program);

    // program for unlit render passes
    program = new Program();
    program->setVertexShader(vertexShaderManager_.getResource("unlit"));
    program->setFragmentShader(fragmentShaderManager_.getResource("unlit"));
    program->link();
    GRAPHICS_RUNTIME_ASSERT(program->linkStatus());
    programManager_.loadResource("unlit", program);

    // program for shadow render passes
    program = new Program();
    program->setVertexShader(vertexShaderManager_.getResource("shadow"));
    program->setFragmentShader(fragmentShaderManager_.getResource("shadow"));
    program->link();
    GRAPHICS_RUNTIME_ASSERT(program->linkStatus());
    programManager_.loadResource("shadow", program);


    // init textures

    Texture* texture = new Texture();
    texture->loadImage("data/textures/ship2.tga");
    texture->generateMipmap();
    textureManager_.loadResource("diffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/ship2SpC.tga");
    texture->generateMipmap();
    textureManager_.loadResource("specular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/ship2SL.tga");
    texture->generateMipmap();
    textureManager_.loadResource("glow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/ship2Nor.tga");
    texture->generateMipmap();
    textureManager_.loadResource("normal", texture);

    // init scene

    rootNode_ = new GroupNode();

    // init camera

    camera_ = new CameraNode();
    camera_->setPerspectiveProjection(45.0f, aspectRatio, 1.0f, 2000.0f);


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
            changeState( STATE_CREDITS );
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

        if( keyboard.keyWasPressedInThisFrame( Keyboard::KEY_P ) )
        {
            addState(STATE_GAMEMENU);
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
		if( currentState == NULL )
        {
            std::cerr << "ERROR! OH SHI-!" << std::endl;
            running = false;
        }
		currentState->update( deltaTime );

		keyboard.updateKeyboardState();

		mouse.updateMouse();
		//testObject->update( deltaTime );
        testMenuObject1->update( deltaTime );
        testMenuObject2->update( deltaTime );
        testMenuObject3->update( deltaTime );
        testMenuObject4->update( deltaTime );

		render( currentState->getRootNode() );
		lastTicks = currentTicks;
	}

    std::cout << "Leaving main loop." << std::endl;

    mixer_.close();
	cleanup();
	std::cout << "bye!" << std::endl;

	return 0;
}

void drawExtents(const Node* node, const DrawParams& params);

void GameProgram::render(Node* rootNode_)
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
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

    drawParams.program = programManager_.getResource("unlit");
    glUseProgram(drawParams.program->id());

    const GLint _diffuseMapLocation = glGetUniformLocation(drawParams.program->id(), "diffuseMap");
    const GLint _specularMapLocation = glGetUniformLocation(drawParams.program->id(), "specularMap");
    const GLint _glowMapLocation = glGetUniformLocation(drawParams.program->id(), "glowMap");
    const GLint _normalMapLocation = glGetUniformLocation(drawParams.program->id(), "normalMap");

    glUniform1i(_diffuseMapLocation, 0);
    glUniform1i(_specularMapLocation, 1);
    glUniform1i(_glowMapLocation, 2);
    glUniform1i(_normalMapLocation, 3);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    textureManager_.getResource("diffuse")->bindTexture();

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    textureManager_.getResource("specular")->bindTexture();

    glActiveTexture(GL_TEXTURE2);
    glEnable(GL_TEXTURE_2D);
    textureManager_.getResource("glow")->bindTexture();

    glActiveTexture(GL_TEXTURE3);
    glEnable(GL_TEXTURE_2D);
    textureManager_.getResource("normal")->bindTexture();

    // unlit render pass
    renderQueue.draw(drawParams);

    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE2);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE3);
    glDisable(GL_TEXTURE_2D);

    // ...


    // shadow pass
//////
//////    drawParams.program = programManager_.getResource("shadow");
//////    glUseProgram(drawParams.program->id());
//////
//////    glUniformMatrix4fv(
//////        glGetUniformLocation(drawParams.program->id(), "modelViewMatrix"),
//////        1,
//////        false,
//////        drawParams.viewMatrix.data()
//////    );
//////
//////    glUniformMatrix4fv(
//////        glGetUniformLocation(drawParams.program->id(), "projectionMatrix"),
//////        1,
//////        false,
//////        drawParams.projectionMatrix.data()
//////    );
//////
//////    for (size_t i = 0; i < geometryNodes_.size(); ++i)
//////    {
//////        const Transform3 transform = geometryNodes_[i]->worldTransform();
//////        const Mesh* mesh = static_cast<MeshNode*>(geometryNodes_[i])->mesh();
//////
//////        for (int iFace = 0; iFace < mesh->numFaces(); ++iFace)
//////        {
//////            const Vector3 n = mesh->normals()[3 * iFace] * transform.rotation;
//////
//////            Vector3 v0 = ::transform(mesh->vertices()[3 * iFace + 0], transform);
//////            Vector3 v1 = ::transform(mesh->vertices()[3 * iFace + 1], transform);
//////            Vector3 v2 = ::transform(mesh->vertices()[3 * iFace + 2], transform);
//////
//////            // TODO: these do not avoid division by zero
//////            const Vector3 lightV0 = normalize(v0 - lightPosition_);
//////            const Vector3 lightV1 = normalize(v1 - lightPosition_);
//////            const Vector3 lightV2 = normalize(v2 - lightPosition_);
//////
//////            // if the signs do not differ, this is not a front face
//////            if (dot(lightV0, n) >= 0.0f)
//////            {
//////                continue;
//////            }
//////
//////            // not quite but close enough
//////            const float infinity = 250.0f;
//////
//////            const Vector3 s0 = v0 + infinity * lightV0;
//////            const Vector3 s1 = v1 + infinity * lightV1;
//////            const Vector3 s2 = v2 + infinity * lightV2;
//////
//////            const float offset = 0.1f;
//////
//////            v0 = v0 + offset * lightV0;
//////            v1 = v1 + offset * lightV1;
//////            v2 = v2 + offset * lightV2;
//////
//////            const Vector3 coords[] = {
//////                v0, v1, v2, // front cap
//////                s0, s2, s1, // back cap
//////                v0, s0, s1,
//////                v0, s1, v1,
//////                v1, s1, s2,
//////                v1, s2, v2,
//////                v2, s2, s0,
//////                v2, s0, v0
//////            };
//////
//////            const GLint coordLocation = glGetAttribLocation(drawParams.program->id(), "coord");
//////            glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, coords->data());
//////            glEnableVertexAttribArray(coordLocation);
//////
//////            // disable color and depth buffer writes
//////            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
//////            glDepthMask(GL_FALSE);
//////
//////            //glDisable(GL_CULL_FACE);
//////
//////            glEnable(GL_STENCIL_TEST);
//////            glStencilFunc(GL_ALWAYS, 0x00, 0xFF);
//////
//////            glStencilOpSeparate(
//////                GL_BACK,    // set stencil settings for back-facing polygons
//////                GL_KEEP,    // stencil fail operation, has no effect
//////                GL_INCR,    // depth fail operation, increment stencil value
//////                GL_KEEP     // depth pass operation, do nothing
//////            );
//////
//////            glStencilOpSeparate(
//////                GL_FRONT,   // set stencil settings for front-facing polygons
//////                GL_KEEP,    // stencil fail operation, has no effect
//////                GL_DECR,    // depth fail operation, decrement stencil value
//////                GL_KEEP     // depth pass operation, do nothing
//////            );
//////
//////            glCullFace(GL_FRONT);
//////            glDrawArrays(GL_TRIANGLES, 0, 24);
//////
//////            glCullFace(GL_BACK);
//////            glDrawArrays(GL_TRIANGLES, 0, 24);
//////
//////            // restore render state
//////            glDisable(GL_STENCIL_TEST);
//////            //glEnable(GL_CULL_FACE);
//////            glDepthMask(GL_TRUE);
//////            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//////
//////            glDisableVertexAttribArray(coordLocation);
//////        }
//////    }
//////
//////    // ...
//////
//////    drawParams.program = programManager_.getResource("test");
//////    glUseProgram(drawParams.program->id());
//////
//////    // ...
//////
//////    const GLint lightPositionsLocation = glGetUniformLocation(drawParams.program->id(), "lightPositions");
//////    const GLint lightColorsLocation = glGetUniformLocation(drawParams.program->id(), "lightColors");
//////    const GLint lightRangesLocation = glGetUniformLocation(drawParams.program->id(), "lightRanges");
//////    const GLint numLightsLocation = glGetUniformLocation(drawParams.program->id(), "numLights");
///////*
//////    const GLint diffuseMapLocation = glGetUniformLocation(drawParams.program->id(), "diffuseMap");
//////    const GLint specularMapLocation = glGetUniformLocation(drawParams.program->id(), "specularMap");
//////    const GLint glowMapLocation = glGetUniformLocation(drawParams.program->id(), "glowMap");
//////    const GLint normalMapLocation = glGetUniformLocation(drawParams.program->id(), "normalMap");
//////*/
//////    lightPosition_.x = 150.0f * Math::cos(Math::radians(0.0f));
//////    lightPosition_.y = 0.0f;
//////    lightPosition_.z = 150.0f * Math::sin(Math::radians(0.0f));
//////
//////    Vector3 lightPositions[] = {
//////        Vector3(150.0f * Math::cos(Math::radians(0.0f)), 0.0f, 150.0f * Math::sin(Math::radians(0.0f))),
//////        Vector3(150.0f * Math::cos(Math::radians(120.0f)), 0.0f, 150.0f * Math::sin(Math::radians(120.0f))),
//////        Vector3(150.0f * Math::cos(Math::radians(240.0f)), 0.0f, 150.0f * Math::sin(Math::radians(240.0f)))
//////    };
//////
//////    static float lightRotation = 0.0f;
//////
//////    const Transform3 t(
//////        Vector3::zero(),
//////        Matrix3x3::yRotation(lightRotation),
//////        1.0f
//////    );
//////
//////    transform(lightPositions, lightPositions + 3, lightPositions, t);
//////
//////    lightPosition_ = lightPositions[0];
//////
//////    transform(lightPositions, lightPositions + 3, lightPositions, inverse(camera_->worldTransform()));
//////
//////    const Vector3 lightColors[] = {
//////        Vector3(2.00f, 2.00f, 2.00f),
//////        Vector3(0.50f, 2.00f, 0.50f),
//////        Vector3(0.50f, 0.50f, 2.00f)
//////    };
//////
//////    const float lightRanges[] = {
//////        750.0f,
//////        250.0f,
//////        250.0f
//////    };
//////
//////    glUniform3fv(lightPositionsLocation, 3, lightPositions->data());
//////    glUniform3fv(lightColorsLocation, 3, lightColors->data());
//////    glUniform1fv(lightRangesLocation, 3, lightRanges);
//////    glUniform1i(numLightsLocation, 1);  // number of active lights
///////*
//////    glUniform1i(diffuseMapLocation, 0);
//////    glUniform1i(specularMapLocation, 1);
//////    glUniform1i(glowMapLocation, 2);
//////    glUniform1i(normalMapLocation, 3);
//////*/
//////    // ...
//////
//////    if( diffuseMipmappingOn )
//////    {
//////        textureManager_.getResource("diffuse")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
//////    }
//////    else
//////    {
//////        textureManager_.getResource("diffuse")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
//////    }
//////
//////    if( glowMipmappingOn )
//////    {
//////        textureManager_.getResource("glow")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
//////    }
//////    else
//////    {
//////        textureManager_.getResource("glow")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
//////    }
//////
//////    if( normalMipmappingOn )
//////    {
//////        textureManager_.getResource("normal")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
//////    }
//////    else
//////    {
//////        textureManager_.getResource("normal")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
//////    }
//////
//////    if( specularMipmappingOn )
//////    {
//////        textureManager_.getResource("specular")->setFilters( Texture::FILTER_LINEAR_MIPMAP_LINEAR, Texture::FILTER_LINEAR_MIPMAP_LINEAR );
//////    }
//////    else
//////    {
//////        textureManager_.getResource("specular")->setFilters( Texture::FILTER_NEAREST, Texture::FILTER_NEAREST );
//////    }
//////    if( anisotropicFilteringOn )
//////    {
//////        textureManager_.getResource("diffuse")->activateAnisotropicFiltering();
//////    }
//////    else
//////    {
//////        textureManager_.getResource("diffuse")->disableAnisotropicFiltering();
//////    }
///////*
//////    glActiveTexture(GL_TEXTURE0);
//////    glEnable(GL_TEXTURE_2D);
//////    textureManager_.getResource("diffuse")->bindTexture();
//////
//////    glActiveTexture(GL_TEXTURE1);
//////    glEnable(GL_TEXTURE_2D);
//////    textureManager_.getResource("specular")->bindTexture();
//////
//////    glActiveTexture(GL_TEXTURE2);
//////    glEnable(GL_TEXTURE_2D);
//////    textureManager_.getResource("glow")->bindTexture();
//////
//////    glActiveTexture(GL_TEXTURE3);
//////    glEnable(GL_TEXTURE_2D);
//////    textureManager_.getResource("normal")->bindTexture();
//////*/
//////    glDepthFunc(GL_LEQUAL);
//////
//////    //GLint stencilBits;
//////    //glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
//////
//////    glEnable(GL_STENCIL_TEST);
//////    glStencilFunc(GL_EQUAL, 0x00, 0xFF);
//////    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//////
//////    // lit render pass, should be done for each light source
//////    renderQueue.draw(drawParams);
//////
//////    glDisable(GL_STENCIL_TEST);
///////*
//////    glActiveTexture(GL_TEXTURE0);
//////    glDisable(GL_TEXTURE_2D);
//////
//////    glActiveTexture(GL_TEXTURE1);
//////    glDisable(GL_TEXTURE_2D);
//////
//////    glActiveTexture(GL_TEXTURE2);
//////    glDisable(GL_TEXTURE_2D);
//////
//////    glActiveTexture(GL_TEXTURE3);
//////    glDisable(GL_TEXTURE_2D);
//////*/
//////    if (rotateLights)
//////    {
//////        //lightRotation = Math::wrapTo2Pi(lightRotation + deltaTime * 0.125f);
//////        lightRotation = Math::mod(lightRotation + deltaTime * 0.125f, 2.0f * Math::pi());
//////    }

    if (drawExtents_)
    {
        glDepthFunc(GL_LEQUAL);

        drawParams.program = programManager_.getResource("extents");
        glUseProgram(drawParams.program->id());

        for (int i = 0; i < renderQueue.numGeometryNodes(); ++i)
        {
            drawExtents(renderQueue.geometryNode(i), drawParams);
        }

        for (int i = 0; i < renderQueue.numGroupNodes(); ++i)
        {
            drawExtents(renderQueue.groupNode(i), drawParams);
        }
    }

    SDL_GL_SwapBuffers();
}

// TODO: quick & dirty, this does not belong here
void drawExtents(const Node* node, const DrawParams& params)
{
    const Extents3 extents = node->worldExtents();

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

    const uint32_t indices[] = {
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

    const Matrix4x4 mvpMatrix = params.viewMatrix * params.projectionMatrix;

    const GLint mvpMatrixLocation = glGetUniformLocation(params.program->id(), "mvp_matrix");
    glUniformMatrix4fv(mvpMatrixLocation, 1, false, mvpMatrix.data());

    const GLint coordLocation = glGetAttribLocation(params.program->id(), "coord");
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, vertices->data());
    glEnableVertexAttribArray(coordLocation);

    glDrawElements(
        GL_LINES,
        24,
        GL_UNSIGNED_INT,
        indices
    );

    glDisableVertexAttribArray(coordLocation);
}

void GameProgram::tick( const float deltaTime )
{
    // empty on purpose
}

void GameProgram::onQuit()
{
    running = false;
}

// dx, dy, and dz are half-widths on x-, y- and z-axes, respectively
Mesh* GameProgram::createBox(const float dx, const float dy, const float dz)
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
    ModelReader modelReader;
    modelReader.setMeshManager(&meshManager_);

    Mesh* const boxMesh = createBox(0.5f, 0.5f, 0.5f);
    meshManager_.loadResource("box", boxMesh);

    GroupNode* groupNode = new GroupNode();

    const float scaling = 0.1f;

    menu1 = modelReader.read("data/models/menuitem.3DS");
    menu1->setScaling(scaling);

    menu2 = modelReader.read("data/models/menuitem.3DS");
    menu2->setScaling(scaling);

    menu3 = modelReader.read("data/models/menuitem.3DS");
    menu3->setScaling(scaling);

    menu4 = modelReader.read("data/models/menuitem.3DS");
    menu4->setScaling(scaling);



    //ship->setMesh(boxMesh);
    //ship->updateModelExtents();

    //const int count = 6;
    //const float offset = 2.5f * scaling;
    //const float displacement = -(offset * (count - 1)) / 2.0f;


    menu1->setTranslation(Vector3(0.0f, 20.0f, -50.0f));
    menu2->setTranslation(Vector3(0.0f, 0.0f, -50.0f));
    menu3->setTranslation(Vector3(0.0f, -20.0f, -50.0f));
    menu4->setTranslation(Vector3(0.0f, -40.0f, -50.0f));

    groupNode->attachChild(menu1);
    groupNode->attachChild(menu2);
    groupNode->attachChild(menu3);
    groupNode->attachChild(menu4);

    rootNode_->attachChild(groupNode);

    testMenuObject1 = new MenuObject( this );
    testMenuObject1->setGraphicalPresentation( menu1 );
    testMenuObject1->attachController( &menuController1 );

    testMenuObject2 = new MenuObject( this );
    testMenuObject2->setGraphicalPresentation( menu2 );
    testMenuObject2->attachController( &menuController2 );

    testMenuObject3 = new MenuObject( this );
    testMenuObject3->setGraphicalPresentation( menu3 );
    testMenuObject3->attachController( &menuController3 );

    testMenuObject4 = new MenuObject( this );
    testMenuObject4->setGraphicalPresentation( menu4 );
    testMenuObject4->attachController( &menuController4 );

    testMenuObject1->setType(MenuObject::TYPE_NEWGAME);
    testMenuObject2->setType(MenuObject::TYPE_OPTIONS);
    testMenuObject3->setType(MenuObject::TYPE_CREDITS);
    testMenuObject4->setType(MenuObject::TYPE_EXIT);

    testMenuObject1->setDown(testMenuObject2);

    testMenuObject2->setUp(testMenuObject1);
    testMenuObject2->setDown(testMenuObject3);

    testMenuObject3->setUp(testMenuObject2);
    testMenuObject3->setDown(testMenuObject4);

    testMenuObject4->setUp(testMenuObject3);

    testMenuObject1->setActive(true);


//    MeshNode* meshNode = new MeshNode();
//    meshNode->setMesh(boxMesh);
//    meshNode->setTranslation(Vector3(0.0f, 0.0f, -50.0f));
//    meshNode->setScaling(50.0f);

//    ModelReader modelReader;
//    modelReader.setMeshManager(&meshManager_);
//
//    Node* p = 0;
//
//    // heavy geometry with tanks
//
//    p = modelReader.read("data/models/abrams_tank.3ds");
//    p->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
//    p->setRotation(Matrix3x3::xRotation(-Math::halfPi()));
//    p->setScaling(0.15f);
//
//    const int count = 6;
//    const float offset = 75.0f;
//    const float displacement = -(offset * (count - 1)) / 2.0f;
//
//    for (int i = 0; i < count; ++i)
//    {
//        for (int j = 0; j < count; ++j)
//        {
//            if (i != 0 || j != 0)
//            {
//                p = p->clone();
//            }
//
//            p->setTranslation(Vector3(displacement + i * offset, 0.0f, displacement + j * offset));
//            rootNode_->attachChild(p);
//        }
//    }
//
//    p = modelReader.read("data/models/platform.3ds");
//    p->setTranslation(Vector3(0.0f, -472.0f, 0.0f));
//    p->setRotation(Matrix3x3::xRotation(-Math::halfPi()));
//    p->setScaling(3.0f);
//    rootNode_->attachChild(p);
//
//    p = modelReader.read("data/models/ship2.3ds");
//    p->setTranslation(Vector3(0.0f, 25.0f, 0.0f));
//    p->setRotation(Matrix3x3::xRotation(-Math::halfPi()));
//    //p->setScaling(3.0f);
//    rootNode_->attachChild(p);

    camera_->setTranslation(Vector3(0.0f, 0.0f, 50.0f));
    camera_->setRotation(Matrix3x3::identity());
    //camera_->setTranslation(Vector3(-0.5f * offset, -0.5f * offset, 0.0f));
}

void GameProgram::changeState( STATES state )
{
    State* tmpState = NULL;

    if( states.size() > 0 )
    {
        tmpState = states.back();
        states.pop_back();
    }

    if( tmpState != NULL )
    {
        delete tmpState;
    }

    tmpState = InitNewState( state );

    if( tmpState == NULL )
    {
        running = false;
        return;
    }

    states.push_back( tmpState );
    currentState = tmpState;
}

void GameProgram::addState( STATES state )
{
    State* tmpState = InitNewState( state );

    if( tmpState == NULL )
    {
        running = false;
        return;
    }

    states.push_back( tmpState );
    currentState = tmpState;
}

void GameProgram::previousState()
{
    /*
     * we can only go to a previous state if we have atleast 2 states in the
     * state stack.
     */
    if( states.size() <= 1 )
    {
        // quit the application
        running = false;
    }

    State* tmpState = states.back();
    delete tmpState;
    states.pop_back();

    currentState = states.back();
}

State* GameProgram::InitNewState(STATES state)
{
    State* tmpState = NULL;
    switch( state )
    {
        case STATE_INTRO:
            tmpState = new IntroState(this);
        break;

        case STATE_MAINMENU:
            tmpState = new MainMenuState(this);
        break;

        case STATE_GAME:
            tmpState = new GameState(this);
        break;

        case STATE_GAMEMENU:
            tmpState = new GameMenuState(this);
        break;

        case STATE_CREDITS:
            tmpState = new CreditsState(this);
        break;

        case STATE_QUIT:
            tmpState = NULL;
        break;
    }

    return tmpState;
}

GameProgram::~GameProgram()
{
    delete rootNode_;
    delete camera_;

    std::vector<State*>::iterator stateIterator = states.begin();
    while( stateIterator != states.end() )
    {
        delete *stateIterator;
        stateIterator++;
    }
}

