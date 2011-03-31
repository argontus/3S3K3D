/**
 * @file game/gamewindow.cpp
 * @author Marko Silokunnas
 */

#include "gamewindow.h"

#include <SDL/SDL.h>
#include <graphics/opengl.h>
#include <iostream>

GameWindow::GameWindow()
 : aspectRatio(0),
   width(0),
   height(0),
   mouseVisible(false),
   fullscreen(false),
   mouseBoundToScreen(true)
{
}

GameWindow::~GameWindow()
{
    //dtor
}

bool GameWindow::init()
{
    std::cout << "Initializing game engine...";

	//TODO: read these from a configuration file.
	width       = 1280; // 1280
	height      = 800;  // 800
	int flags   = SDL_HWACCEL | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;

	if( fullscreen )
	{
	    flags = flags | SDL_FULLSCREEN;
	}

	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		std::cerr << "SDL initialization failed: " << SDL_GetError();
		std::cerr << std::endl;
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//TODO: request the depth value from the driver instead of hardcoding it.
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // this is needed for the depth fail shadow volume algorithm
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    if( (mainwindow = SDL_SetVideoMode( width, height, 32, flags )) == NULL )
    {
		std::cerr << "SDL initialization failed: " << SDL_GetError();
		std::cerr << std::endl;
		return false;
	}

	SDL_ShowCursor( mouseVisible );

	resizeWindow(width, height);

    std::cout << "game engine initialization succesfull!" << std::endl;

	return true;
}

void GameWindow::cleanup()
{
    SDL_FreeSurface(mainwindow);
	SDL_Quit();
}

void GameWindow::resizeWindow( const int width, const int height )
{
    glViewport( 0, 0, width, height );
    aspectRatio = (float)width/height;
    this->width = width;
    this->height = height;
}

void GameWindow::onEvent( const SDL_Event& event )
{
	switch( event.type )
	{
        case SDL_QUIT:
            onQuit();
        break;

        case SDL_KEYDOWN:
            onKeyDown( event.key );
        break;

        case SDL_KEYUP:
            onKeyUp( event.key );
        break;

        case SDL_MOUSEMOTION:
            onMouseMoved( event.motion );
        break;

        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown( event.button );
        break;

        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp( event.button );
        break;
	}
}

void GameWindow::onWindowResize( const int width, const int height )
{
    resizeWindow( width, height );
}


void GameWindow::onFocusGained()
{
    // does nothing by default
}

void GameWindow::onFocusLost()
{
    // does nothing by default
}

void GameWindow::onKeyDown( const SDL_KeyboardEvent& keyboardEvent )
{
    // does nothing by default
}

void GameWindow::onKeyUp( const SDL_KeyboardEvent& keyboardEvent )
{
    // does nothing by default
}

void GameWindow::onWindowMinimized()
{
    // does nothing by default
}

void GameWindow::onWindowMaximized()
{
    // does nothing by default
}

void GameWindow::onMouseMoved( const SDL_MouseMotionEvent& mouseMotionEvent )
{
   // does nothing by default
}

void GameWindow::onMouseButtonDown(const SDL_MouseButtonEvent& mouseButtonEvent)
{
   // does nothing by default
}

void GameWindow::onMouseButtonUp(const SDL_MouseButtonEvent& mouseButtonEvent)
{
    // does nothing by default
}

void GameWindow::centerMouse()
{
    SDL_WarpMouse( width/2, height/2 );
}
