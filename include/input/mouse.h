#ifndef MOUSE_H
#define MOUSE_H

/**
 * @file input/mouse.h
 * @author Marko Silokunnas
 *
 * Defines an abstract layer that is used to communicate with a mouse regardless
 * of the underlying API.
 */
class Mouse
{
    public:

        enum MOUSEBUTTONS {
            MOUSEBUTTON_LEFT,
            MOUSEBUTTON_MIDDLE,
            MOUSEBUTTON_RIGHT
        };

        enum MOUSEMODE {
            MOUSE_RELATIVE,
            MOUSE_NORMAL,
            MOUSE_BOUND
        };

        Mouse();
        virtual ~Mouse();

        virtual int getMouseX() const { return mouseX; }
        virtual int getMouseY() const { return mouseY; }

        /**
         * Current state of a mouse button.
         *
         * @param mouseButton button which state we want to ask
         * @param bool returns true if the button is down, false otherwise.
         */
        virtual bool mouseButtonIsDown(MOUSEBUTTONS mouseButton) const = 0;

        /**
         * State of the button in previous frame.
         *
         * @param mouseButton button which state we want to ask.
         * @return bool returns true if button was down, false otherwise.
         */
        virtual bool mouseButtonWasDown(MOUSEBUTTONS mouseButton) const = 0;

        /**
         * Tells whether or not the mouse button was pressed down in this frame.
         *
         * @param mouseButton button which we're interested in.
         * @return bool returns true if the button was pressed down in this
         *         frame, false otherwise.
         */
        virtual bool mouseButtonPressedInThisFrame(
                                            MOUSEBUTTONS mouseButton) const = 0;


        /**
         * Tells whether or not the mouse button was released in this frame.
         *
         * @param mouseButton button which we're interested in
         * @return returns true if the mouse button was released in this frame,
         *         false otherwise.
         */
        virtual bool mouseButtonReleasedInThisFrame(
                                            MOUSEBUTTONS mouseButton) const = 0;


        /**
         * Sets current state of the mouse as it's previous state.
         *
         * Must be called once in a frame.
         */
        virtual void updateMouse() = 0;

        /**
         * Gets the number of supported mouse buttons.
         */
        static int getNumberOfMouseButtons();

        /**
         * Sets mouse mode. MOUSE_RELATIVE means that the x and y coordinates
         * of the mouse are returned as relative to their previous positions
         * (delta values). MOUSE_FIXED means that the coordinates are fixed
         * coordinates inside the window.
         *
         * @param mode mode of the mouse.
         */
        virtual void setMouseMode( MOUSEMODE mode );

        /**
         * Makes mouse pointer visible
         */
        virtual void showMousePointer() = 0;

        /**
         * Makes mouse pointer visible
         */
        virtual void hideMousePointer() = 0;

        /**
         * Moves the mouse pointer to the specified coordinates.
         *
         * @param x x coordinate of the mouse.
         * @param y y coordinate of the mouse.
         */
        virtual void moveMouse( int x, int y ) = 0;

        virtual void setMouseBindPoint(int x, int y );

    protected:
        /**
         * Current X position of the mouse pointer.
         */
        int mouseX;

        /**
         * Current Y position of the mouse pointer.
         */
        int mouseY;

        int mouseBindPointX;
        int mouseBindPointY;

        /**
         * Current mode of the mouse
         */
        MOUSEMODE mouseMode;

        /**
         * Number of maximum mouse buttons supported by this class.
         * Set to three by default( left, middle and right buttons ).
         */
        static const int numberOfMouseButtons = 3;
    private:
};

#endif // MOUSE_H
