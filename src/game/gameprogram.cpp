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
#include <geometry/vector3array.h>
#include <graphics/color.h>
#include <graphics/colorarray.h>
#include <graphics/indexarray.h>
#include <graphics/meshnode.h>
#include <graphics/cameranode.h>
#include <graphics/groupnode.h>
#include <graphics/drawparams.h>
#include <graphics/predrawparams.h>
#include <graphics/renderqueue.h>
#include <graphics/runtimeassert.h>
#include <graphics/modelreader.h>
#include <graphics/visibilitytest.h>

GameProgram::GameProgram()
:   camera_(0),
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
    shaderProgramManager_(),
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

    // shader program for drawing mesh nodes
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->setVertexShader(vertexShaderManager_.getResource("default"));
    shaderProgram->setFragmentShader(fragmentShaderManager_.getResource("default"));
    shaderProgram->link();
    GRAPHICS_RUNTIME_ASSERT(shaderProgram->linkStatus());
    shaderProgramManager_.loadResource("default", shaderProgram);

    // shader program for drawing node extents
    shaderProgram = new ShaderProgram();
    shaderProgram->setVertexShader(vertexShaderManager_.getResource("extents"));
    shaderProgram->setFragmentShader(fragmentShaderManager_.getResource("extents"));
    shaderProgram->link();
    GRAPHICS_RUNTIME_ASSERT(shaderProgram->linkStatus());
    shaderProgramManager_.loadResource("extents", shaderProgram);

    // shader program for drawing node extents
    shaderProgram = new ShaderProgram();
    shaderProgram->setVertexShader(vertexShaderManager_.getResource("test"));
    shaderProgram->setFragmentShader(fragmentShaderManager_.getResource("test"));
    shaderProgram->link();
    GRAPHICS_RUNTIME_ASSERT(shaderProgram->linkStatus());
    shaderProgramManager_.loadResource("test", shaderProgram);

    // shader program for unlit render passes
    shaderProgram = new ShaderProgram();
    shaderProgram->setVertexShader(vertexShaderManager_.getResource("unlit"));
    shaderProgram->setFragmentShader(fragmentShaderManager_.getResource("unlit"));
    shaderProgram->link();
    GRAPHICS_RUNTIME_ASSERT(shaderProgram->linkStatus());
    shaderProgramManager_.loadResource("unlit", shaderProgram);

    // shader program for shadow render passes
    shaderProgram = new ShaderProgram();
    shaderProgram->setVertexShader(vertexShaderManager_.getResource("shadow"));
    shaderProgram->setFragmentShader(fragmentShaderManager_.getResource("shadow"));
    shaderProgram->link();
    GRAPHICS_RUNTIME_ASSERT(shaderProgram->linkStatus());
    shaderProgramManager_.loadResource("shadow", shaderProgram);


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

    configuration.readConfiguration("config.ini");

    if( mouseBoundToScreen )
    {
        mouse.bindMouse();
        mouse.setMouseBindPointX( width/2 );
        mouse.setMouseBindPointY( height/2 );
        centerMouse();
    }

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
            drawExtents_ = !drawExtents_;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F2))
        {
            diffuseMipmappingOn = !diffuseMipmappingOn;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F3))
        {
            glowMipmappingOn = !glowMipmappingOn;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F4))
        {
            normalMipmappingOn = !normalMipmappingOn;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F5))
        {
            specularMipmappingOn = !specularMipmappingOn;
        }

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F6))
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

        // quick&dirty, write a function for these or something
        static const float speed = 50.0f;

		if( keyboard.keyIsDown( Keyboard::KEY_D ) )
		{
            camera_->translateBy( deltaTime * camera_->rotation().row(0) * speed );
		}
		else if( keyboard.keyIsDown( Keyboard::KEY_A ) )
        {
            camera_->translateBy( deltaTime * camera_->rotation().row(0) * -speed );
        }

        if( keyboard.keyIsDown( Keyboard::KEY_Q) )
        {
            camera_->translateBy(deltaTime * -speed * camera_->rotation().row(1));
        }
        else if( keyboard.keyIsDown( Keyboard::KEY_E ) )
        {
            camera_->translateBy(deltaTime * speed * camera_->rotation().row(1));
        }

        if( keyboard.keyIsDown( Keyboard::KEY_W) )
        {
            camera_->translateBy(deltaTime * -speed * camera_->rotation().row(2));
        }
        else if( keyboard.keyIsDown( Keyboard::KEY_S ) )
        {
            camera_->translateBy(deltaTime * speed * camera_->rotation().row(2));
        }



        int deltaX;
        int deltaY;

        deltaX = mouse.getMouseDeltaX();
        deltaY = mouse.getMouseDeltaY();

        const float rotationFactor = 0.005;

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
            std::cout << "ŕight mouse button pressed!" << std::endl;
        }
        if( mouse.mouseButtonPressedInThisFrame( Mouse::MOUSEBUTTON_MIDDLE ) )
        {
            std::cout << "middle mouse button pressed!" << std::endl;
        }

		tick( deltaTime );

		keyboard.updateKeyboardState();

		if( mouseBoundToScreen )
		{
		    bindMouse();
		    mouse.bindMouse();
		}
		else
		{
		    releaseMouse();
		    mouse.releaseMouse();
		}
		mouse.updateMouse();

		render();
		lastTicks = currentTicks;

	}

    std::cout << "Leaving main loop." << std::endl;

	cleanup();
	std::cout << "bye!" << std::endl;

	return 0;
}

void drawExtents(const Node* node, const DrawParams& params);

void GameProgram::render()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthRange(0.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearStencil(0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


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
    drawParams.worldToViewRotation = transpose(camera_->worldTransform().rotation());
    drawParams.cameraToWorld = camera_->worldTransform();

    drawParams.shaderProgram = shaderProgramManager_.getResource("unlit");
    glUseProgram(drawParams.shaderProgram->id());

    const GLint _diffuseMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "diffuseMap");
    const GLint _specularMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "specularMap");
    const GLint _glowMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "glowMap");
    const GLint _normalMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "normalMap");

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

    drawParams.shaderProgram = shaderProgramManager_.getResource("shadow");
    glUseProgram(drawParams.shaderProgram->id());

    drawParams.shaderProgram->setUniformMatrix4x4fv(
        "modelViewMatrix",
        1,
        false,
        drawParams.viewMatrix.data()
    );

    drawParams.shaderProgram->setUniformMatrix4x4fv(
        "projectionMatrix",
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
            const Vector3 n = product(mesh->normals()[3 * iFace], transform.rotation());

            Vector3 v0 = transform.applyForward(mesh->vertices()[3 * iFace + 0]);
            Vector3 v1 = transform.applyForward(mesh->vertices()[3 * iFace + 1]);
            Vector3 v2 = transform.applyForward(mesh->vertices()[3 * iFace + 2]);

            // TODO: these do not avoid division by zero
            const Vector3 lightV0 = normalize(v0 - lightPosition_);
            const Vector3 lightV1 = normalize(v1 - lightPosition_);
            const Vector3 lightV2 = normalize(v2 - lightPosition_);

            // if the signs do not differ, this is not a front face
            if (dot(lightV0, n) >= 0.0f)
            {
                continue;
            }

            // not quite but close enough
            const float infinity = 250.0f;

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

            const GLint coordLocation = drawParams.shaderProgram->attribLocation("coord");
            glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, coords->data());
            glEnableVertexAttribArray(coordLocation);

            // disable color and depth buffer writes
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);

            //glDisable(GL_CULL_FACE);

            glEnable(GL_STENCIL_TEST);
            glStencilFunc(GL_ALWAYS, 0x00, 0xFF);

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
            //glEnable(GL_CULL_FACE);
            glDepthMask(GL_TRUE);
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

            glDisableVertexAttribArray(coordLocation);
        }
    }

    // ...

    drawParams.shaderProgram = shaderProgramManager_.getResource("test");
    glUseProgram(drawParams.shaderProgram->id());

    // ...

    const GLint lightPositionsLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "lightPositions");
    const GLint lightColorsLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "lightColors");
    const GLint lightRangesLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "lightRanges");
    const GLint numLightsLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "numLights");
    const GLint diffuseMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "diffuseMap");
    const GLint specularMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "specularMap");
    const GLint glowMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "glowMap");
    const GLint normalMapLocation = glGetUniformLocation(drawParams.shaderProgram->id(), "normalMap");

    lightPosition_.set(150.0f * Math::cos(Math::degToRad(0.0f)), 0.0f, 150.0f * Math::sin(Math::degToRad(0.0f)));

    Vector3 lightPositions[] = {
        Vector3(150.0f * Math::cos(Math::degToRad(0.0f)), 0.0f, 150.0f * Math::sin(Math::degToRad(0.0f))),
        Vector3(150.0f * Math::cos(Math::degToRad(120.0f)), 0.0f, 150.0f * Math::sin(Math::degToRad(120.0f))),
        Vector3(150.0f * Math::cos(Math::degToRad(240.0f)), 0.0f, 150.0f * Math::sin(Math::degToRad(240.0f)))
    };

    static float lightRotation = 0.0f;

    Transform3::yRotation(lightRotation).applyForward(lightPositions, lightPositions + 3, lightPositions);

    lightPosition_ = lightPositions[0];

    camera_->worldTransform().applyInverse(lightPositions, lightPositions + 3, lightPositions);

    const Vector3 lightColors[] = {
        Vector3(2.00f, 2.00f, 2.00f),
        Vector3(0.50f, 2.00f, 0.50f),
        Vector3(0.50f, 0.50f, 2.00f)
    };

    const float lightRanges[] = {
        250.0f,
        250.0f,
        250.0f
    };

    glUniform3fv(lightPositionsLocation, 3, lightPositions->data());
    glUniform3fv(lightColorsLocation, 3, lightColors->data());
    glUniform1fv(lightRangesLocation, 3, lightRanges);
    glUniform1i(numLightsLocation, 1);  // number of active lights

    glUniform1i(diffuseMapLocation, 0);
    glUniform1i(specularMapLocation, 1);
    glUniform1i(glowMapLocation, 2);
    glUniform1i(normalMapLocation, 3);

    // ...

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

    glDepthFunc(GL_LEQUAL);

    //GLint stencilBits;
    //glGetIntegerv(GL_STENCIL_BITS, &stencilBits);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 0x00, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // lit render pass, should be done for each light source
    renderQueue.draw(drawParams);

    glDisable(GL_STENCIL_TEST);

    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE2);
    glDisable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE3);
    glDisable(GL_TEXTURE_2D);

    if (rotateLights)
    {
        lightRotation = Math::wrapTo2Pi(lightRotation + deltaTime * 0.125f);
    }

    if (drawExtents_)
    {
        glDepthFunc(GL_LEQUAL);

        drawParams.shaderProgram = shaderProgramManager_.getResource("extents");
        glUseProgram(drawParams.shaderProgram->id());

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

    const Matrix4x4 mvpMatrix = product(params.viewMatrix, params.projectionMatrix);

    const GLint mvpMatrixLocation = params.shaderProgram->uniformLocation("mvp_matrix");
    glUniformMatrix4fv(mvpMatrixLocation, 1, false, mvpMatrix.data());

    const GLint coordLocation = params.shaderProgram->attribLocation("coord");
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
    if( mouseBoundToScreen )
    {
        centerMouse();
    }
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

    Vector3Array coords(36);
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

    Vector2Array texCoords(36);
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

    const float scaling = 15.0f;

    MeshNode* meshNode = new MeshNode();
    meshNode->setScaling(scaling);
    meshNode->setMesh(boxMesh);
    meshNode->updateModelExtents();

    const int count = 6;
    const float offset = 2.5f * scaling;
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

    camera_->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
    //camera_->setTranslation(Vector3(-0.5f * offset, -0.5f * offset, 0.0f));
}

GameProgram::~GameProgram()
{
    delete rootNode_;
    delete camera_;
}

void GameProgram::bindMouse()
{
    mouseBoundToScreen = true;
    mouseVisible = false;
    SDL_ShowCursor( mouseVisible );
}

void GameProgram::releaseMouse()
{
    mouseBoundToScreen = false;
    mouseVisible = true;
    SDL_ShowCursor( mouseVisible );
}
