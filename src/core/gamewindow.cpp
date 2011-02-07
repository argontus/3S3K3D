/**
 *  @file core/gamewindow.cpp
 *  @author Marko Silokunnas
 */

#include <core/gamewindow.h>

#include <SDL/SDL.h>
#include <graphics/opengl.h>
#include <iostream>

GameWindow::GameWindow()
{
    aspectRatio = 0;
}

GameWindow::~GameWindow()
{
    //dtor
}

bool GameWindow::init()
{
    std::cout << "Initializing game engine...";

	//TODO: read these from a configuration file.
	int width       = 800;
	int height      = 600;
	int flags       = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_RESIZABLE;

	if( SDL_Init( SDL_INIT_VIDEO) < 0 ) {
	//if( SDL_VideoInit( NULL, 0 ) ) {
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

	resizeWindow(width, height);

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

void GameWindow::cleanup()
{
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
	SDL_Quit();
}

void GameWindow::resizeWindow( const int width, const int height )
{
    glViewport( 0, 0, width, height );
    aspectRatio = (float)width/height;
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

        case SDL_WINDOWEVENT:
            onWindowEvent( event.window );
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

void GameWindow::onWindowEvent( const SDL_WindowEvent& windowEvent )
{
    switch( windowEvent.event  )
    {
        case SDL_WINDOWEVENT_RESIZED:
            onWindowResize( windowEvent.data1, windowEvent.data2 );
        break;

        case SDL_WINDOWEVENT_FOCUS_GAINED:
           onFocusGained();
        break;

        case SDL_WINDOWEVENT_FOCUS_LOST:
            onFocusLost();
        break;

        case SDL_WINDOWEVENT_CLOSE:
            onQuit();
        break;

        case SDL_WINDOWEVENT_MAXIMIZED:
            onWindowMaximized();
        break;

        case SDL_WINDOWEVENT_MINIMIZED:
            onWindowMinimized();
        break;

        default:
        break;
    }
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
