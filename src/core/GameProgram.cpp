/**
 *  @file core/GameProgram.cpp
 *  @author Marko Silokunnas
 */

#include <core/GameProgram.h>

#ifdef __linux__
#include "GL/glew.h"
#include "SDL/SDL.h"
#endif

#ifdef WIN32
//todo: add #includes for windows as well!
#endif

#include <iostream>

GameProgram::GameProgram() {
	running         = true;
    deltaTicks      = 0;
    deltaTime       = 0;
}

bool GameProgram::init() {
    std::cout << "Initializing game engine...";

	//TODO: read these from a configuration file.
	int width       = 800;
	int height      = 600;
	int flags       = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

	//if( SDL_Init( SDL_INIT_VIDEO) < 0 ) {
	if( SDL_VideoInit( NULL, 0 ) ) {
		std::cerr << "Video initialization failed: " << SDL_GetError();
		std::cerr << std::endl;
		return false;
	}

	/* Request an OpenGL 3.3 context */
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//TODO: request the depth value from the driver instead of hardcoding it.
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* create the window, don't give a crap about the window's position */
	mainwindow = SDL_CreateWindow(	"TESTING",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									width,
									height,
									flags );
	if( !mainwindow ) {
		std::cerr << "Unable to create window!" << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	maincontext = SDL_GL_CreateContext(mainwindow);
	SDL_GL_SetSwapInterval(1);

    std::cout << "game engine initialization succesfull!" << std::endl;

	return true;
}


void GameProgram::handleEvent( SDL_Event* event ) {
	switch( event->type ) {
		case SDL_QUIT:
			running = false;
		break;
		case SDL_KEYDOWN:
			handleKeyPresses( event->key.keysym );
		break;
		default:
		break;
	}
}

void GameProgram::handleKeyPresses( SDL_keysym keysym ) {
	switch( keysym.sym ) {
	case SDLK_ESCAPE:
		running = false;
		break;
	default:
		break;
	}
}

int GameProgram::execute() {

	if( init() == false ) {
		return -1;
	}

	SDL_Event event;
    deltaTicks          = 0;
    deltaTime           = 0;
    uint currentTicks = 0;
    uint lastTicks    = 0;

    std::cout << "Entering main loop..." << std::endl;
	while( running ) {
        currentTicks = SDL_GetTicks();

	    deltaTicks = currentTicks-lastTicks;
	    deltaTime = (float)deltaTicks/1000.0;

        std::cout << "FPS: " << 1.0/((float)deltaTicks/1000.0) << std::endl;

		while( SDL_PollEvent( &event ) ) {
			handleEvent( &event );
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

void GameProgram::render() {
    static float red = 0.0;
    static float green = 0.0;
    static float blue = 1.0;
    static uint ticks = 0;

    ticks += deltaTicks;

	if( ticks >=  1000 ) {
	    ticks = 0;
	    if( red == 0 && blue == 1.0 ) {
            red = 1.0;
            green = 0.0;
            blue = 0.0;
	    }
	    else if( green == 0 && red == 1.0 ) {
            red = 0.0;
            green = 1.0;
            blue = 0.0;
	    }
	    else if( blue == 0 ) {
            red = 0.0;
            green = 0.0;
            blue = 1.0;
	    }
	}

	glClearColor( red, green, blue, 1.0 );
	glClear ( GL_COLOR_BUFFER_BIT );

	SDL_GL_SwapWindow(mainwindow);
}

void GameProgram::cleanup() {
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
	SDL_Quit();
}

void GameProgram::tick( float deltaTime ) {
    /*
     * TODO: give this function some sort of basic functionality, or
     *       turn this function into a pure virtual function.
     */

}

GameProgram::~GameProgram() {
}
