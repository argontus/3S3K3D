/**
 *  @file core/gameprogram.cpp
 *  @author Marko Silokunnas
 */

#include <core/gameprogram.h>

#ifdef __linux__
#include "GL/glew.h"
#endif

#ifdef WIN32
#include <gl/gl.h>
#endif

#include <iostream>

GameProgram::GameProgram() {
	running         = true;
    deltaTicks      = 0;
    deltaTime       = 0;
}

int GameProgram::execute()
{
	if( init() == false ) {
		return -1;
	}

	SDL_Event event;
    deltaTicks          = 0;
    deltaTime           = 0;
    Uint32 currentTicks = 0;
    Uint32 lastTicks    = 0;

    std::cout << "Entering main loop..." << std::endl;

	while( running ) {
        currentTicks = SDL_GetTicks();

	    deltaTicks = currentTicks-lastTicks;
	    deltaTime = (float)deltaTicks/1000.0;

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

void GameProgram::render()
{
    static float red = 0.0;
    static float green = 0.0;
    static float blue = 1.0;
    static Uint32 ticks = 0;

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

void GameProgram::tick( const float deltaTime )
{
    // does nothing for now
}

void GameProgram::onQuit()
{
    running = false;
}

void GameProgram::onKeyboardEvent( const SDL_KeyboardEvent& keyboardEvent )
{

	switch( keyboardEvent.keysym.sym )
	{
        case SDLK_ESCAPE:
            running = false;
            break;
        default:
            break;
	}
}


GameProgram::~GameProgram()
{
}
