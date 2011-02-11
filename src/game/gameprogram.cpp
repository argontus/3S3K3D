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

GameProgram::GameProgram()
:   camera_(0),
    rootNode_(0),
    vertexArray_(0),
    colorArray_(0),
    redColorArray_(0),
    blueColorArray_(0),
    indexArray_(0),
    drawExtents_(false),
    vertexShaderManager_(),
    fragmentShaderManager_(),
    shaderProgramManager_()
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


    // init mesh stuff

    //vertexArray_ = new Vector3Array(8);
    //(*vertexArray_)[0].set(-1.0f, -1.0f,  1.0f);
    //(*vertexArray_)[1].set( 1.0f, -1.0f,  1.0f);
    //(*vertexArray_)[2].set( 1.0f,  1.0f,  1.0f);
    //(*vertexArray_)[3].set(-1.0f,  1.0f,  1.0f);
    //(*vertexArray_)[4].set( 1.0f, -1.0f, -1.0f);
    //(*vertexArray_)[5].set(-1.0f, -1.0f, -1.0f);
    //(*vertexArray_)[6].set(-1.0f,  1.0f, -1.0f);
    //(*vertexArray_)[7].set( 1.0f,  1.0f, -1.0f);

    //colorArray_ = new ColorArray(8);
    //(*colorArray_)[0].set(0.0f, 0.0f, 1.0f, 1.0f);
    //(*colorArray_)[1].set(1.0f, 0.0f, 1.0f, 1.0f);
    //(*colorArray_)[2].set(1.0f, 1.0f, 1.0f, 1.0f);
    //(*colorArray_)[3].set(0.0f, 1.0f, 1.0f, 1.0f);
    //(*colorArray_)[4].set(1.0f, 0.0f, 0.0f, 1.0f);
    //(*colorArray_)[5].set(0.0f, 0.0f, 0.0f, 1.0f);
    //(*colorArray_)[6].set(0.0f, 1.0f, 0.0f, 1.0f);
    //(*colorArray_)[7].set(1.0f, 1.0f, 0.0f, 1.0f);

    //indexArray_ = new IndexArray(36);
    //// front
    //(*indexArray_)[ 0] = 0;
    //(*indexArray_)[ 1] = 1;
    //(*indexArray_)[ 2] = 2;
    //(*indexArray_)[ 3] = 0;
    //(*indexArray_)[ 4] = 2;
    //(*indexArray_)[ 5] = 3;
    //// back
    //(*indexArray_)[ 6] = 4;
    //(*indexArray_)[ 7] = 5;
    //(*indexArray_)[ 8] = 6;
    //(*indexArray_)[ 9] = 4;
    //(*indexArray_)[10] = 6;
    //(*indexArray_)[11] = 7;
    //// bottom
    //(*indexArray_)[12] = 1;
    //(*indexArray_)[13] = 0;
    //(*indexArray_)[14] = 5;
    //(*indexArray_)[15] = 1;
    //(*indexArray_)[16] = 5;
    //(*indexArray_)[17] = 4;
    //// top
    //(*indexArray_)[18] = 3;
    //(*indexArray_)[19] = 2;
    //(*indexArray_)[20] = 7;
    //(*indexArray_)[21] = 3;
    //(*indexArray_)[22] = 7;
    //(*indexArray_)[23] = 6;
    //// left
    //(*indexArray_)[24] = 5;
    //(*indexArray_)[25] = 0;
    //(*indexArray_)[26] = 3;
    //(*indexArray_)[27] = 5;
    //(*indexArray_)[28] = 3;
    //(*indexArray_)[29] = 6;
    //// right
    //(*indexArray_)[30] = 1;
    //(*indexArray_)[31] = 4;
    //(*indexArray_)[32] = 7;
    //(*indexArray_)[33] = 1;
    //(*indexArray_)[34] = 7;
    //(*indexArray_)[35] = 2;

    vertexArray_ = new Vector3Array(24);
    // front
    (*vertexArray_)[ 0].set(-1.0f, -1.0f,  1.0f);
    (*vertexArray_)[ 1].set( 1.0f, -1.0f,  1.0f);
    (*vertexArray_)[ 2].set( 1.0f,  1.0f,  1.0f);
    (*vertexArray_)[ 3].set(-1.0f,  1.0f,  1.0f);
    // back
    (*vertexArray_)[ 4].set( 1.0f, -1.0f, -1.0f);
    (*vertexArray_)[ 5].set(-1.0f, -1.0f, -1.0f);
    (*vertexArray_)[ 6].set(-1.0f,  1.0f, -1.0f);
    (*vertexArray_)[ 7].set( 1.0f,  1.0f, -1.0f);
    // bottom
    (*vertexArray_)[ 8] = (*vertexArray_)[5];
    (*vertexArray_)[ 9] = (*vertexArray_)[4];
    (*vertexArray_)[10] = (*vertexArray_)[1];
    (*vertexArray_)[11] = (*vertexArray_)[0];
    // top
    (*vertexArray_)[12] = (*vertexArray_)[3];
    (*vertexArray_)[13] = (*vertexArray_)[2];
    (*vertexArray_)[14] = (*vertexArray_)[7];
    (*vertexArray_)[15] = (*vertexArray_)[6];
    // left
    (*vertexArray_)[16] = (*vertexArray_)[5];
    (*vertexArray_)[17] = (*vertexArray_)[0];
    (*vertexArray_)[18] = (*vertexArray_)[3];
    (*vertexArray_)[19] = (*vertexArray_)[6];
    // right
    (*vertexArray_)[20] = (*vertexArray_)[1];
    (*vertexArray_)[21] = (*vertexArray_)[4];
    (*vertexArray_)[22] = (*vertexArray_)[7];
    (*vertexArray_)[23] = (*vertexArray_)[2];

    normalArray_ = new Vector3Array(24);
    // front
    (*normalArray_)[ 0] =
    (*normalArray_)[ 1] =
    (*normalArray_)[ 2] =
    (*normalArray_)[ 3] = Vector3::zAxis();
    // back
    (*normalArray_)[ 4] =
    (*normalArray_)[ 5] =
    (*normalArray_)[ 6] =
    (*normalArray_)[ 7] = -Vector3::zAxis();
    // bottom
    (*normalArray_)[ 8] =
    (*normalArray_)[ 9] =
    (*normalArray_)[10] =
    (*normalArray_)[11] = -Vector3::yAxis();
    // top
    (*normalArray_)[12] =
    (*normalArray_)[13] =
    (*normalArray_)[14] =
    (*normalArray_)[15] = Vector3::yAxis();
    // left
    (*normalArray_)[16] =
    (*normalArray_)[17] =
    (*normalArray_)[18] =
    (*normalArray_)[19] = -Vector3::xAxis();
    // right
    (*normalArray_)[20] =
    (*normalArray_)[21] =
    (*normalArray_)[22] =
    (*normalArray_)[23] = Vector3::xAxis();

    colorArray_ = new ColorArray(24);
    colorArray_->fill(Color(1.0f, 1.0f, 1.0f, 1.0f));

    redColorArray_ = new ColorArray(24);
    redColorArray_->fill(Color(1.0f, 0.0f, 0.0f, 1.0f));

    blueColorArray_ = new ColorArray(24);
    blueColorArray_->fill(Color(0.0f, 0.0f, 1.0f, 1.0f));

    indexArray_ = new IndexArray(36);
    // front
    (*indexArray_)[ 0] = 0;
    (*indexArray_)[ 1] = 1;
    (*indexArray_)[ 2] = 2;
    (*indexArray_)[ 3] = 0;
    (*indexArray_)[ 4] = 2;
    (*indexArray_)[ 5] = 3;
    // back
    (*indexArray_)[ 6] = 4;
    (*indexArray_)[ 7] = 5;
    (*indexArray_)[ 8] = 6;
    (*indexArray_)[ 9] = 4;
    (*indexArray_)[10] = 6;
    (*indexArray_)[11] = 7;
    // bottom
    (*indexArray_)[12] = 8;
    (*indexArray_)[13] = 9;
    (*indexArray_)[14] = 10;
    (*indexArray_)[15] = 8;
    (*indexArray_)[16] = 10;
    (*indexArray_)[17] = 11;
    // top
    (*indexArray_)[18] = 12;
    (*indexArray_)[19] = 13;
    (*indexArray_)[20] = 14;
    (*indexArray_)[21] = 12;
    (*indexArray_)[22] = 14;
    (*indexArray_)[23] = 15;
    // left
    (*indexArray_)[24] = 16;
    (*indexArray_)[25] = 17;
    (*indexArray_)[26] = 18;
    (*indexArray_)[27] = 16;
    (*indexArray_)[28] = 18;
    (*indexArray_)[29] = 19;
    // right
    (*indexArray_)[30] = 20;
    (*indexArray_)[31] = 21;
    (*indexArray_)[32] = 22;
    (*indexArray_)[33] = 20;
    (*indexArray_)[34] = 22;
    (*indexArray_)[35] = 23;


    // init camera

    camera_ = new CameraNode();
    camera_->setTranslation(Vector3(0.0f, 0.0f, 32.0f));
    camera_->setPerspectiveProjection(45.0f, aspectRatio, 1.0f, 1000.0f);
    //camera_->setTranslation(Vector3(512.0f, 0.0f, 512.0f));
    //camera_->rotateBy(Matrix3x3::yRotation(Math::pi() / 4.0f));
    //camera_->setOrthographicProjection(-400.0f, 400.0f, -300.0f, 300.0f, 0.0f, 1000.0f);


    // init scene

    rootNode_ = new GroupNode();

    GroupNode* group = new GroupNode();

    MeshNode* mesh = new MeshNode();
    mesh->setVertexArray(vertexArray_);
    mesh->setNormalArray(normalArray_);
    mesh->setColorArray(redColorArray_);
    mesh->setIndexArray(indexArray_);
    mesh->updateModelExtents();
    //mesh->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
    //mesh->setRotation(Matrix3x3::identity());
    mesh->setScaling(1.75f);
    mesh->setRotationLocked(true);
    //mesh->setScalingLocked(true);
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setColorArray(colorArray_);
    mesh->setTranslation(Vector3(-4.0f, 0.0f, 0.0f));
    mesh->setScaling(1.0f);
    mesh->setRotationLocked(false);
    //mesh->setScalingLocked(false);
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setTranslation(Vector3(4.0f, 0.0f, 0.0f));
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setTranslation(Vector3(0.0f, -4.0f, 0.0f));
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setTranslation(Vector3(0.0f, 4.0f, 0.0f));
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setColorArray(blueColorArray_);
    mesh->setTranslation(Vector3(0.0f, 0.0f, -4.0f));
    group->attachChild(mesh);

    mesh = mesh->clone();
    mesh->setTranslation(Vector3(0.0f, 0.0f, 4.0f));
    group->attachChild(mesh);

    GroupNode* bigGroup = new GroupNode();

    group->setScaling(2.0f);
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(-16.0f, 0.0f, 0.0f));
    group->setScaling(1.0f);
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(16.0f, 0.0f, 0.0f));
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(0.0f, -16.0f, 0.0f));
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(0.0f, 16.0f, 0.0f));
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(0.0f, 0.0f, -16.0f));
    bigGroup->attachChild(group);

    group = group->clone();
    group->setTranslation(Vector3(0.0f, 0.0f, 16.0f));
    bigGroup->attachChild(group);

    GroupNode* hugeGroup = new GroupNode();

    bigGroup->setScaling(2.0f);
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(-64.0f, 0.0f, 0.0f));
    bigGroup->setScaling(1.0f);
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(64.0f, 0.0f, 0.0f));
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(0.0f, -64.0f, 0.0f));
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(0.0f, 64.0f, 0.0f));
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(0.0f, 0.0f, -64.0f));
    hugeGroup->attachChild(bigGroup);

    bigGroup = bigGroup->clone();
    bigGroup->setTranslation(Vector3(0.0f, 0.0f, 64.0f));
    hugeGroup->attachChild(bigGroup);

    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(-256.0f, 0.0f, 0.0f));
    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(256.0f, 0.0f, 0.0f));
    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(0.0f, -256.0f, 0.0f));
    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(0.0f, 256.0f, 0.0f));
    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(0.0f, 0.0f, -256.0f));
    rootNode_->attachChild(hugeGroup);

    hugeGroup = hugeGroup->clone();
    hugeGroup->setTranslation(Vector3(0.0f, 0.0f, 256.0f));
    rootNode_->attachChild(hugeGroup);

	SDL_Event event;
    deltaTicks          = 0;
    deltaTime           = 0;
    Uint32 currentTicks = 0;
    Uint32 lastTicks    = 0;

    std::cout << "Entering main loop..." << std::endl;

	while( running ) {
        currentTicks = SDL_GetTicks();

	    deltaTicks = currentTicks - lastTicks;
	    deltaTime = deltaTicks / 1000.0f;

        //std::cout << "FPS: " << 1.0/deltaTime << std::endl;

		while( SDL_PollEvent( &event ) ) {
			onEvent( event );
		}

		tick( deltaTime );

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

    RenderQueue& renderQueue = RenderQueue::instance();
    std::vector<const GroupNode*> visibleGroups;

    PredrawParams predrawParams;
    predrawParams.renderQueue = &renderQueue;
    predrawParams.visibleGroups = &visibleGroups;

    rootNode_->rotateBy(Matrix3x3::xRotation(deltaTime * 0.1f));
    rootNode_->rotateBy(Matrix3x3::yRotation(deltaTime * 0.1f));
    Matrix3x3 rotation = rootNode_->rotation();
    rotation.orthogonalize();
    rootNode_->setRotation(rotation);
    //rootNode_->setRotation(Matrix3x3::xRotation(Math::pi() / 2.0f));
    //rootNode_->setTranslation(Vector3(0.0f, 0.0f, 0.0f));
    //rootNode_->setScaling(1.0f);

    for (int i = 1; i < rootNode_->numChildren(); ++i)
    {
        Node* const node = rootNode_->child(i);

        switch (i)
        {
            case 1:
                node->rotateBy(Matrix3x3::xRotation(deltaTime * 0.25f));
                node->rotateBy(Matrix3x3::yRotation(deltaTime * 0.25f));
                break;

            case 2:
                node->rotateBy(Matrix3x3::xRotation(deltaTime * -0.25f));
                node->rotateBy(Matrix3x3::zRotation(deltaTime * 0.25f));
                break;

            case 3:
                node->rotateBy(Matrix3x3::yRotation(deltaTime * 0.25f));
                node->rotateBy(Matrix3x3::zRotation(deltaTime * 0.25f));
                break;

            case 4:
                node->rotateBy(Matrix3x3::yRotation(deltaTime * -0.25f));
                node->rotateBy(Matrix3x3::xRotation(deltaTime * 0.25f));
                break;

            case 5:
                node->rotateBy(Matrix3x3::zRotation(deltaTime * 0.25f));
                node->rotateBy(Matrix3x3::xRotation(deltaTime * 0.25f));
                break;

            case 6:
                node->rotateBy(Matrix3x3::zRotation(deltaTime * -0.25f));
                node->rotateBy(Matrix3x3::yRotation(deltaTime * 0.25f));
                break;

            default:
                break;
        }

        Matrix3x3 rotation = node->rotation();
        rotation.orthogonalize();
        node->setRotation(rotation);
    }

    // predraw step
    rootNode_->predraw(predrawParams);

    ShaderProgram* shaderProgram = shaderProgramManager_.getResource("default");

    // TODO: make this a member of ShaderProgram?
    glUseProgram(shaderProgram->id());

    DrawParams drawParams;
    drawParams.viewMatrix = camera_->worldToViewMatrix();
    drawParams.projectionMatrix = camera_->projectionMatrix();
    drawParams.worldToViewRotation = transpose(camera_->worldTransform().rotation());
    //drawParams.viewMatrix = Matrix4x4::identity();
    //drawParams.projectionMatrix = Matrix4x4::identity();
    drawParams.shaderProgram = shaderProgram;
    drawParams.cameraToWorld = camera_->worldTransform();

    // draw step
    predrawParams.renderQueue->sort();
    predrawParams.renderQueue->draw(drawParams);

    //glUseProgram(shaderProgram2.id());

    if (drawExtents_)
    {
        drawParams.shaderProgram = shaderProgramManager_.getResource("extents");
        glUseProgram(drawParams.shaderProgram->id());

        for (size_t i = 0; i < visibleGroups.size(); ++i)
        {
            //drawExtents(visibleGroups[i], drawParams);
            drawExtents(visibleGroups[i], drawParams);
        }

        for (int i = 0; i < renderQueue.size(); ++i)
        {
            drawExtents(renderQueue[i], drawParams);
        }
    }

    predrawParams.renderQueue->clear();

    // ...

    SDL_GL_SwapBuffers();
}

// TODO: quick & dirty
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
    SDL_WarpMouse( width/2, height/2 );
}

void GameProgram::onQuit()
{
    running = false;
}

void GameProgram::onKeyDown( const SDL_KeyboardEvent& keyboardEvent )
{
    const float translationFactor = 50.0f;
    const float rotationFactor = 1.0f;

    switch( keyboardEvent.keysym.sym )
    {
        case SDLK_ESCAPE:
            running = false;
            break;

        case SDLK_a:
            camera_->translateBy(deltaTime * translationFactor * -camera_->rotation().row(0));
            break;

        case SDLK_s:
            camera_->translateBy(deltaTime * translationFactor * camera_->rotation().row(2));
            break;

        case SDLK_d:
            camera_->translateBy(deltaTime * translationFactor * camera_->rotation().row(0));
            break;

        case SDLK_w:
            camera_->translateBy(deltaTime * translationFactor * -camera_->rotation().row(2));
            break;

        case SDLK_q:
            camera_->translateBy(deltaTime * translationFactor * -Vector3::yAxis());
            break;

        case SDLK_e:
            camera_->translateBy(deltaTime * translationFactor * Vector3::yAxis());
            break;

        case SDLK_LEFT:
            camera_->rotateBy(Matrix3x3::yRotation(deltaTime * rotationFactor));
            break;

        case SDLK_RIGHT:
            camera_->rotateBy(Matrix3x3::yRotation(deltaTime * -rotationFactor));
            break;

        case SDLK_UP:
            camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaTime * rotationFactor));
            break;

        case SDLK_DOWN:
            camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaTime * -rotationFactor));
            break;

        case SDLK_F1:
            drawExtents_ = !drawExtents_;
            break;

        default:
            break;
    }
}

void GameProgram::onMouseMoved( const SDL_MouseMotionEvent& mouseMotionEvent )
{
    const int deltaX = mouseMotionEvent.x-width/2;
    const int deltaY = mouseMotionEvent.y-height/2;
    const float rotationFactor = 0.005f;

    if( deltaX != 0 )
    {
        camera_->rotateBy(Matrix3x3::yRotation(deltaX * -rotationFactor));
    }

    if( deltaY != 0 ) {
        camera_->rotateBy(Matrix3x3::rotation(camera_->rotation().row(0), deltaY * -rotationFactor));
    }
}

GameProgram::~GameProgram()
{
    delete camera_;
    delete rootNode_;
    delete vertexArray_;
    delete colorArray_;
    delete redColorArray_;
    delete blueColorArray_;
    delete indexArray_;
}
