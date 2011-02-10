/**
 * @file game/gameprogram.h
 * @author Marko Silokunnas
 */

#ifndef GAMEPROGRAM_H_
#define GAMEPROGRAM_H_

#include <SDL/SDL.h>
#include "gamewindow.h"

#include <graphics/resourcemanager.h>
#include <graphics/vertexshader.h>
#include <graphics/fragmentshader.h>
#include <graphics/shaderprogram.h>

// TODO: quick & dirty
class CameraNode;
class GroupNode;
class Vector3Array;
class ColorArray;
class IndexArray;

typedef ResourceManager<VertexShader> VertexShaderManager;
typedef ResourceManager<FragmentShader> FragmentShaderManager;
typedef ResourceManager<ShaderProgram> ShaderProgramManager;

/**
 * The 'main' class of the game. Does event handling for keyboard and mouse
 * events. Contains the main loop of the game as well.
 */
class GameProgram : public GameWindow {
public:
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

	/*
	 * Called when user presses key on the keyboard.
	 *
	 * @param keyboardEvent keyboard event to handle.
	 */
	virtual void onKeyDown( const SDL_KeyboardEvent& keyboardEvent );

private:
	bool running;
	Uint32 deltaTicks; /* ticks between last frame and current frame */
	float deltaTime;
	static const Uint32 ticksPerSecond = 1000;

    // TODO: quick & dirty
    CameraNode* camera_;
    GroupNode* rootNode_;
    Vector3Array* vertexArray_;
    Vector3Array* normalArray_;
    ColorArray* colorArray_;
    ColorArray* redColorArray_;
    ColorArray* blueColorArray_;
    IndexArray* indexArray_;
    bool drawExtents_;

    VertexShaderManager vertexShaderManager_;
    FragmentShaderManager fragmentShaderManager_;
    ShaderProgramManager shaderProgramManager_;
};

#endif /* GAMEPROGRAM_H_ */
