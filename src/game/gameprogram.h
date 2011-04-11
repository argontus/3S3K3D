/**
 * @file game/gameprogram.h
 * @author Marko Silokunnas
 */

#ifndef GAMEPROGRAM_H_
#define GAMEPROGRAM_H_

#include <SDL/SDL.h>
#include "gamewindow.h"
#include "gameobject.h"
#include "keyboardcontroller.h"
#include "menukeyboardcontroller.h"
#include "menuobject.h"

#include "configuration/configuration.h"

#include "sound/mixer.h"

#include <graphics/resourcemanager.h>
#include <graphics/vertexshader.h>
#include <graphics/fragmentshader.h>
#include <graphics/program.h>
#include <graphics/mesh.h>
#include <geometry/vector3.h>
#include <graphics/texture.h>

#include <graphics/geometrynode.h>

// TODO: quick & dirty
class CameraNode;
class GroupNode;
class Vector3Array;
class ColorArray;
class IndexArray;
class Node;
class State;

typedef ResourceManager<VertexShader> VertexShaderManager;
typedef ResourceManager<FragmentShader> FragmentShaderManager;
typedef ResourceManager<Program> ProgramManager;
typedef ResourceManager<Mesh> MeshManager;
typedef ResourceManager<Texture> TextureManager;

/**
 * The 'main' class of the game. Does event handling for keyboard and mouse
 * events. Contains the main loop of the game as well.
 */
class GameProgram : public GameWindow {
public:

    enum STATES {
        STATE_INTRO,
        STATE_MAINMENU,
        STATE_GAME,
        STATE_GAMEMENU,
        STATE_CREDITS,
        STATE_QUIT
    };

	GameProgram();

	/**
	 *
	 * Starts executing the main loop of the program.
	 *
	 * @return int returns 0 on clean exit and non-zero on forced exit (eg. an
	 * 			error occured. )
	 */
	int execute();

	/**
	 *
	 * Renders the scene
	 *
	 */
	void render();

	/**
	 *
	 * Event handling. TODO: write a better comment :P
	 *
	 * @param event event to handle
	 */
	void handleEvent( const SDL_Event* const event );

	/**
	 *
	 * handles key presses.
	 *
	 * @param keysym keysym of the pressed key
	 */
	void handleKeyPresses( const SDL_keysym keysym );

	/**
	 *
	 * one 'tick' in the game simulation
	 * @param deltaTime frame independent modifier for movement of
     *                        objects
	 */
	 virtual void tick( const float deltaTime );

	/**
	 *
	 * destructor
	 */
	virtual ~GameProgram();

	/**
	 *
	 * getter for member variable 'running'
	 *
	 * @return bool
	 */
	inline bool isRunning() const { return running; };

	/**
	 *
	 * setter for member variable 'running'
	 *
	 * @param value new value for the member variable.
	 */
	void setRunning( bool value ) { this->running = value; }

    /*
     * Exits the main loop and calls SDL_Quit()
     */
	virtual void onQuit();

    /**
     * Initializes and sets state defined by the parameter as the current
     * state. Fades into the state.
     */
	virtual void changeState( STATES state );

	/**
	 * Initializes and sets the state defined by the parameter as the current
	 * state instantly.
	 */
	virtual void addState( STATES state );

	/**
	 * Goes back to previous state by popping the topmost state from the states
	 * stack. If the stack is empty after tha pop, the program will quit
	 */
	virtual void previousState();

	/**
	 * Initilizes a new state and returns a pointer to it
	 */
    virtual State* InitNewState(STATES state);

	/*
	 * Called when user presses key on the keyboard.
	 *
	 * @param keyboardEvent keyboard event to handle.
	 */
	//virtual void onKeyDown( const SDL_KeyboardEvent& keyboardEvent );

    //virtual void onKeyUp( const SDL_KeyboardEvent& keyboardEvent );

	//virtual void onMouseMoved( const SDL_MouseMotionEvent& mouseMotionEvent );

private:
    void test();

	Configuration configuration;
	Mixer mixer_;
	Node* ship;
	Node* menu1;
	Node* menu2;
	Node* menu3;
	Node* menu4;
    //GameObject* testObject;
    MenuObject* testMenuObject1;
    MenuObject* testMenuObject2;
    MenuObject* testMenuObject3;
    MenuObject* testMenuObject4;
    KeyboardController testController;
    CameraNode* camera_;
    GroupNode* rootNode_;
    bool drawExtents_;
    bool diffuseMipmappingOn;
    bool glowMipmappingOn;
    bool normalMipmappingOn;
    bool specularMipmappingOn;
    bool rotateLights;
    bool anisotropicFilteringOn;
    VertexShaderManager vertexShaderManager_;
    FragmentShaderManager fragmentShaderManager_;
    ProgramManager programManager_;
    MeshManager meshManager_;
    TextureManager textureManager_;

    MenuKeyboardController menuController1;
    MenuKeyboardController menuController2;
    MenuKeyboardController menuController3;
    MenuKeyboardController menuController4;

    /**
     * State stack.
     */
    std::vector<State*> states;

    State* currentState;

	bool running;
	Uint32 deltaTicks; /* ticks between last frame and current frame */
	float deltaTime;
	static const Uint32 ticksPerSecond = 1000;

    // TODO: quick & dirty



    Vector3 lightPosition_;

    std::vector<GeometryNode*> geometryNodes_;


};

#endif /* GAMEPROGRAM_H_ */
