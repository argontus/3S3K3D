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

        Mouse();
        virtual ~Mouse();

        virtual int getMouseDeltaX() const = 0;
        virtual int getMouseDeltaY() const = 0;

        virtual int getMouseX() const = 0;
        virtual int getMouseY() const = 0;

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
         * Sets current mouse X and Y positions as previous positions in order
         * to calculate the delta values properly.
         *
         * Must be called once in a frame.
         */
        virtual void updateMouse() = 0;

        /**
         * Gets the number of supported mouse buttons.
         */
        static int getNumberOfMouseButtons();

        /**
         * Binds the mouse to a point on the screen.
         * Everytime updateMouse() is called the mouse cursor is set to point
         * defined as the bind point.
         */
        virtual void bindMouse();

        /**
         * Releases the mouse bind.
         */
        virtual void releaseMouse();

        /**
         * Set mouse bind point X coordinate.
         */
        virtual void setMouseBindPointX( const int x );

        /**
         * Set mouse bind point Y coordinate.
         */
        virtual void setMouseBindPointY( const int y );

        /**
         * Getter for mouseBoundToPoint
         */
        virtual inline bool isMouseBoundToPoint() const
        {
            return mouseBoundToPoint;
        }

        /**
         * Getter for mouseBindPointX.
         */
        virtual inline int getMouseBindPointX() const
        {
            return mouseBindPointX;
        }

        /**
         * Getter for mouseBindPointY.
         */
        virtual inline int getMouseBindPointY() const
        {
            return mouseBindPointY;
        }

    protected:
        /**
         * Current X position of the mouse pointer.
         */
        int currentMouseX;

        /**
         * Current Y position of the mouse pointer.
         */
        int currentMouseY;

        /**
         * X position of the mouse pointer in the last frame.
         */
        int previousMouseX;

        /**
         * Y position of the mouse pointer in the last frame.
         */
        int previousMouseY;

        /**
         * Is mouse bound to a point on the screen.
         */
        bool mouseBoundToPoint;

        /**
         * X coordinate of the mouse bound point.
         */
        int mouseBindPointX;

        /**
         * Y coordinate of the mouse bound point
         */
        int mouseBindPointY;

        /**
         * Number of maximum mouse buttons supported by this class.
         * Set to three by default( left, middle and right buttons ).
         */
        static const int numberOfMouseButtons = 3;
    private:
};

#endif // MOUSE_H
