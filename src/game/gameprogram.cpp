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
    drawExtents_(false),
    diffuseMipmappingOn(true),
    glowMipmappingOn(true),
    normalMipmappingOn(false),
    specularMipmappingOn(false),
    rotateLights(false),
    anisotropicFilteringOn(false),
    vertexShaderManager_(),
    fragmentShaderManager_(),
    programManager_(),
    meshManager_(),
    textureManager_(),
    currentState(NULL),
    nextState(NULL)
{
    running         = true;
    deltaTicks      = 0;
    deltaTime       = 0;
}

int GameProgram::execute()
{
	if( init() == false ) {
		return -1;
	}

    glewInit();
    changeState(STATE_INTRO);


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
            addState( STATE_QUIT );
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

        if( keyboard.keyWasPressedInThisFrame( Keyboard::KEY_F11 ))
        {
            scriptEngine.executeScript("data/scripts/helloworld.lua");
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
            running = false;
            break;
        }
		currentState->update( deltaTime );

		keyboard.updateKeyboardState();

		//mouse.updateMouse();

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

    // unlit render pass
    renderQueue.draw(drawParams);


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
        nextState = NULL;
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

