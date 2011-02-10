/**
 * @file game/gamwindow.h
 * @author Marko Silokunnas
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL/SDL.h>

/**
 * Pure virtual class representing a game window. Contains basic functionality
 * for resizing a window and receiving events. Handling single events
 * can be achieved by overloading the function responsible for that event
 * in the inherited class.
 */
class GameWindow
{
    public:
        GameWindow();
        virtual ~GameWindow();

        /**
         *
         * Initializes SDL, window and OpenGL.
         * Will read configuration file at some point as well
         *
         * @return bool returns true if initialization is successful, otherwise
         * 			    return false.
         */
        bool init();

        /**
         *
         * This function is called before exiting the program. Makes sure that
         * the program frees all of it's memory etc.
         */
        void cleanup();

        /**
         * Calculates window's aspect ratio and resets glViewport according to
         * new window size.
         */
        void resizeWindow( const int width, const int height );

        /**
         * Main handler for SDL events. Calls appropriate function based on
         * event type. (eg. onWindowEvent for SDL_WindowEvents)
         */
        void onEvent( const SDL_Event& event );

        /**
         * Called whenever the window changes size. Calls resizeWindow by
         * default. It's recommended to call resizeWindow in the overloading
         * function as well
         */
        virtual void onWindowResize( const int width, const int height );

        /**
         * Handles window events
         *
         * @param windowEvent window event to handle
         */
        //virtual void onWindowEvent( const SDL_WindowEvent& windowEvent );

        /**
         * Called whenever user presses a key down.
         *
         * @param keyboardEvent keyboard event to process. Contains info on
         *        which key was pressed.
         */
        virtual void onKeyDown( const SDL_KeyboardEvent& keyboardEvent );

        /**
         * Called whenever user releases a key that is pressed down
         *
         * @param keyboardEvent keyboard event to process. Contains info on
         *        on which key was released.
         */
         virtual void onKeyUp( const SDL_KeyboardEvent& keyboardEvent );

        /**
         * Pure virtual event handler for quit events.
         */
        virtual void onQuit() = 0;

        /**
         * Called whenever window gains focus
         */
        virtual void onFocusGained();

        /**
         * Called whenever window loses focus
         */
        virtual void onFocusLost();

        /**
         * Called whenever window is minimized.
         */
        virtual void onWindowMinimized();

        /**
         * Called whenever window is maximized.
         */
        virtual void onWindowMaximized();

        /**
         * Called whenever mouse is moved
         *
         * @param mouseMotionEvent mouse movement event
         */
        virtual void onMouseMoved(const SDL_MouseMotionEvent& mouseMotionEvent);

        /**
         * Called whenever one of the mouse buttons is pressed
         *
         * @param mouseButtonEvent mouse button event
         */
         virtual void onMouseButtonDown(
                                const SDL_MouseButtonEvent& mouseButtonEvent
                                       );

        /**
         * Called whenever one of the mouse buttons is released
         *
         * @param mouseButtonEvent mouse button event
         */
         virtual void onMouseButtonUp(
                                const SDL_MouseButtonEvent& mouseButtonEvent
                                     );

    protected:
        //SDL_WindowID mainwindow; /* window handle */
        //SDL_GLContext maincontext; /* opengl context handle */
        SDL_Surface* mainwindow;
        float aspectRatio;
};

#endif // GAMEWINDOW_H
