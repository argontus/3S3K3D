#ifndef CONTROLLER_H
#define CONTROLLER_H

class GameObject;

/**
 * Pure virtual class defining a controller. A controller can be used to control
 * a game object. Controller can modify the game object's transformations etc.
 */
class Controller
{
    public:
        Controller();
        virtual ~Controller();

        virtual void update() = 0;

        /**
         * returns the object that this controller is currently attached to
         *
         * @return GameObject* pointer to the object that this controller is
         *                     currently attached to.
         */
        inline GameObject* getObjectAttachedTo() const
        {
            return objectAttachedTo;
        }

        /**
         * Setter for the 'objectAttachedTo' member variable
         *
         * @param object object to attach this controller to.
         */
        void setObjectAttachedTo(GameObject* object);
    protected:
    private:
        GameObject* objectAttachedTo;

};

#endif // CONTROLLER_H
