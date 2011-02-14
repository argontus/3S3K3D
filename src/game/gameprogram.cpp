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
    vertexShaderManager_(),
    fragmentShaderManager_(),
    shaderProgramManager_(),
    meshManager_()
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

    FragmentShader* fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/default.fs"));
    fragmentShader->compile();
    const std::string info = fragmentShader->infoLog();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("default", fragmentShader);

    fragmentShader = new FragmentShader();
    fragmentShader->setSourceText(readSourceText("data/shaders/extents.fs"));
    fragmentShader->compile();
    GRAPHICS_RUNTIME_ASSERT(fragmentShader->compileStatus());
    fragmentShaderManager_.loadResource("extents", fragmentShader);

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
    }

    std::cout << "Entering main loop..." << std::endl;
	while( running ) {
        currentTicks = SDL_GetTicks();

	    deltaTicks = currentTicks - lastTicks;
	    deltaTime = deltaTicks / 1000.0f;

		while( SDL_PollEvent( &event ) ) {
			onEvent( event );
		}

        if (keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F1))
        {
            drawExtents_ = !drawExtents_;
        }

        // quick&dirty, write a function for these or something
        static const float speed = 40.0f;

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

        if( deltaX != 0 )
        {
            camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(1), deltaX * -rotationFactor));

        }

        if( deltaY != 0 )
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

    ShaderProgram* shaderProgram = shaderProgramManager_.getResource("default");
    glUseProgram(shaderProgram->id());

    DrawParams drawParams;
    drawParams.viewMatrix = camera_->worldToViewMatrix();
    drawParams.projectionMatrix = camera_->projectionMatrix();
    drawParams.worldToViewRotation = transpose(camera_->worldTransform().rotation());
    drawParams.shaderProgram = shaderProgram;
    drawParams.cameraToWorld = camera_->worldTransform();


    // draw step

    renderQueue.sort();
    renderQueue.draw(drawParams);

    if (drawExtents_)
    {
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
        SDL_WarpMouse( width/2, height/2 );
    }
/*
    if( cameraSpeedX != 0 )
    {
        camera_->translateBy( camera_->rotation().row(0) * cameraSpeedX );
    }

    if( cameraSpeedY != 0 )
    {
        camera_->translateBy( Vector3::yAxis() * cameraSpeedY );
    }

    if( cameraSpeedZ != 0 )
    {
        camera_->translateBy( camera_->rotation().row(2) * cameraSpeedZ );
    }
    */
}

void GameProgram::onQuit()
{
    running = false;
}
/*
void GameProgram::onKeyDown( const SDL_KeyboardEvent& keyboardEvent )
{
    const float cameraSpeed = 1.0f;

    switch( keyboardEvent.keysym.sym )
    {
        case SDLK_ESCAPE:
            running = false;
            break;

        case SDLK_a:
            //camera_->translateBy(deltaTime * translationFactor * -camera_->rotation().row(0));
            cameraSpeedX = -cameraSpeed;
            break;

        case SDLK_s:
            //camera_->translateBy(deltaTime * translationFactor * camera_->rotation().row(2));
            cameraSpeedZ = cameraSpeed;
            break;

        case SDLK_d:
            //camera_->translateBy(deltaTime * translationFactor * camera_->rotation().row(0));
             cameraSpeedX = cameraSpeed;
            break;

        case SDLK_w:
            //camera_->translateBy(deltaTime * translationFactor * -camera_->rotation().row(2));
            cameraSpeedZ = -cameraSpeed;
            break;

        case SDLK_q:
            //camera_->translateBy(deltaTime * translationFactor * -Vector3::yAxis());
            break;

        case SDLK_e:
            //camera_->translateBy(deltaTime * translationFactor * Vector3::yAxis());
            break;

        case SDLK_LEFT:
            //camera_->rotateBy(Matrix3x3::yRotation(deltaTime * rotationFactor));
            break;

        case SDLK_RIGHT:
            //camera_->rotateBy(Matrix3x3::yRotation(deltaTime * -rotationFactor));
            break;

        case SDLK_UP:
            //camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaTime * rotationFactor));
            break;

        case SDLK_DOWN:
            //camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaTime * -rotationFactor));
            break;
        case SDLK_F2:
            if( mouseBoundToScreen )
                releaseMouse();
            else
                bindMouse();

            break;
        case SDLK_F1:
            drawExtents_ = !drawExtents_;
            break;

        default:
            break;
    }
}
*/

/*
void GameProgram::onKeyUp( const SDL_KeyboardEvent& keyboardEvent )
{
 switch( keyboardEvent.keysym.sym )
    {
        case SDLK_ESCAPE:
            running = false;
            break;

        case SDLK_a:
        case SDLK_d:
            cameraSpeedX = 0.0f;
            break;

        case SDLK_q:
        case SDLK_e:
            cameraSpeedY = 0.0f;
            break;

        case SDLK_s:
        case SDLK_w:
            cameraSpeedZ = 0.0f;
            break;

        default:
            break;
    }

}
*/

/*
void GameProgram::onMouseMoved( const SDL_MouseMotionEvent& mouseMotionEvent )
{
    const int deltaX = mouseMotionEvent.x-width/2;
    const int deltaY = mouseMotionEvent.y-height/2;
    const float rotationFactor = 0.0025;

    if( deltaX != 0 )
    {
        camera_->rotateBy(Matrix3x3::yRotation(deltaX * -rotationFactor));
    }

    if( deltaY != 0 ) {
        camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaY * -rotationFactor));
    }
}
*/

void GameProgram::test()
{
    ModelReader modelReader;
    modelReader.setMeshManager(&meshManager_);

    Node* p = 0;


    // heavy geometry with tanks

    p = modelReader.read("data/models/abrams_tank.3ds");
    p->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
    p->setRotation(Matrix3x3::xRotation(-Math::halfPi()));
    p->setScaling(0.15f);

    const int count = 6;
    const float offset = 75.0f;
    const float displacement = -(offset * (count - 1)) / 2.0f;

    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count; ++j)
        {
            if (i != 0 || j != 0)
            {
                p = p->clone();
            }

            p->setTranslation(Vector3(displacement + i * offset, 0.0f, displacement + j * offset));
            rootNode_->attachChild(p);
        }
    }

    p = modelReader.read("data/models/platform.3ds");
    p->setTranslation(Vector3(0.0f, -472.0f, 0.0f));
    p->setRotation(Matrix3x3::xRotation(-Math::halfPi()));
    p->setScaling(3.0f);
    rootNode_->attachChild(p);

    camera_->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
}

GameProgram::~GameProgram()
{
    delete rootNode_;
    delete camera_;
}
