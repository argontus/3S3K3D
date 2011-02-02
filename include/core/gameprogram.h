/**
 *  @file core/GameProgram.h
 *  @author Marko Silokunnas
 *
 */

#ifndef GAMEPROGRAM_H_
#define GAMEPROGRAM_H_

#include <SDL/SDL.h>

/**
 * The 'main' class of the game. Contains initializations(window, OpenGL, SDL)
 * and event handling for keyboard and mouse events. Contains the main loop
 * of the game as well.
 */
class GameProgram {
public:
	GameProgram();

	/**
	 *
	 * Initialize SDL, window and OpenGL.
	 * Read configuration file at some point as well
	 *
	 * @return bool returns true if initialization is successful, otherwise
	 * 			    return false.
	 */
	bool init();

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
	 * This function is called before exiting the program. Makes sure that the
	 * program frees all of it's memory etc.
	 */
	void cleanup();

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
	  *
	  */

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

private:
	bool running;
	SDL_WindowID mainwindow; /* window handle */
	SDL_GLContext maincontext; /* opengl context handle */
	Uint32 deltaTicks; /* ticks between last frame and current frame */
	float deltaTime;
	static const Uint32 ticksPerSecond = 1000;
};

#endif /* GAMEPROGRAM_H_ */
