/**
 *  @file core/GameProgram.h
 *  @author Marko Silokunnas
 *
 */

#ifndef GAMEPROGRAM_H_
#define GAMEPROGRAM_H_

#include <SDL/SDL.h>

class GameProgram {
public:
	GameProgram();

	/**
	 * init
	 *
	 * Initialize SDL, window and OpenGL.
	 * Read configuration file at some point as well
	 *
	 * @return	bool returns true if initialization is successful, otherwise
	 * 			return false.
	 */
	bool init();

	/**
	 * execute
	 *
	 * Starts executing the main loop of the program.
	 *
	 * @return	returns 0 on clean exit and non-zero on forced exit (eg. an
	 * 			error occured. )
	 */
	int execute();

	/**
	 * render
	 *
	 * Renders the scene
	 *
	 */
	void render();

	/**
	 * cleanup
	 *
	 * This function is called before exiting the program. Makes sure that the
	 * program frees all of it's memory etc.
	 */
	void cleanup();

	/**
	 * handleEvent
	 *
	 * Event handling. TODO: write a better comment :P
	 *
	 * @param event event to handle
	 */
	void handleEvent( SDL_Event* event );

	/**
	 * handleKeyPresses
	 *
	 * handles key presses.
	 *
	 * @param SDL_keysym* keysym of the pressed key
	 */
	void handleKeyPresses( SDL_keysym keysym );

	/**
	 * tick
	 *
	 * one 'tick' in the game simulation
	 * @param float deltaTime frame independent modifier for movement of
     *                        objects
	 */
	 virtual void tick( float deltaTime );

	 /**
	  *
	  *
	  */

	/**
	 * ~GameProgram
	 *
	 * destructor
	 */
	virtual ~GameProgram();

	/**
	 * isRunning
	 *
	 * getter for member variable 'running'
	 *
	 * @return bool
	 */
	inline bool isRunning() const { return running; };

	/**
	 * setRunning
	 *
	 * setter for member variable 'running'
	 *
	 * @param bool new value for the member variable.
	 */
	void setRunning( bool value ) { this->running = value; }

private:
	bool running;
	SDL_WindowID mainwindow; /* window handle */
	SDL_GLContext maincontext; /* opengl context handle */
	uint deltaTicks; /* ticks between last frame and current frame */
	float deltaTime;
	static const uint ticksPerSecond = 1000;
};

#endif /* GAMEPROGRAM_H_ */
