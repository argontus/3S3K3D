#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "geometry/transform2.h"
#include <list>

class Node;
class Controller;
class GameProgram;


class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        virtual void update( float deltaTime );

        /**
         * Callback function to call when the object intersects with another
         * object. Default implementation does nothing.
         *
         * @param otherObject pointer to the object that this object intersetcts
         *                    with.
         */
        virtual void onEnter( GameObject* otherObject );

        /**
         * Callback function to call when the object leaves the area of an
         * another object. Default implementation does nothing.
         *
         * @param otherObject pointer to the object which is no longer
         *                    intersecting with this object.
         */
        virtual void onLeave( GameObject* otherObject );

        /**
         * Getter for graphical presentation
         *
         * @return Node* pointer to graphical presentation of the object
         */
        inline Node* getGraphicalPresentation() const
        {
            return graphicalPresentation;
        }

        /**
         * Getter for local transformation
         *
         * @return Transform2 local transform of the object
         */
        inline Transform2 getLocalTransformation() const
        {
            return localTransformation;
        }

        /**
         * Getter for world transformation
         *
         * @return Transform2 world transform of the object
         */
        inline Transform2 getWorldTransformation() const
        {
            return worldTransformation;
        }

        /**
         * Getter for parent pointer
         *
         * @return GameObject* pointer to parent that owns this object
         */
        inline GameObject* getParent() const { return parent; }

        /**
         * Getter for GameProgram backpointer
         *
         * @return GameProgram* backpointer to the program that owns this object
         */
        inline GameProgram* getGameProgram() { return gameProgram; }

        void setGameProgram( GameProgram* newGameprogram );
        void setGraphicalPresentation( Node* newGraphicalPresentation );
        void setLocalTransformation( Transform2 newTransformation );
        void setWorldTransformation( Transform2 newTransformation );
        void setParent( GameObject* parent );

        /**
         * Attach a child to the object. Ownership of the child is now
         * transferred to this object. The child will be freed in when the
         * destructor of this object is called.
         *
         * @param child child to attach to this object.
         */
        void attachChild( GameObject* child );

        /**
         * Detach a child from the object. Note that only a pointer to the child
         * is removed, the actual memory is not freed here. Make sure you
         * remember to free the child afterwards!
         *
         * @param child child to remove
         */
        void detachChild( GameObject* child );

        /**
         * Same as detachChild(), but frees the memory of the child object
         * as well.
         *
         * @param child child to destroy
         */
        void destroyChild( GameObject* child );

        /**
         * Attach controller. When a controller is attached to a game object,
         * the ownership of the controller is given to the game object. All
         * controllers owned by the game object will be released in the object's
         * destructor.
         *
         * @param controller controller to attach
         */
        void attachController( Controller* controller );

        /**
         * Detach controller. When a controller is detached from the game
         * object, it's ownership of the controller is relieved.
         *
         * @param controller controller to detach
         */
        void detachController( Controller* controller );

        /**
         * Detach and delete the controller
         *
         * @param controller controller to detach
         */
        void destroyController( Controller* controller );

    protected:

    private:
    /**
     * Graphical presentation of the object
     */
    Node* graphicalPresentation;

    //TODO: add trigger area
    //TODO: add local and world bounding area for trigger area

    /**
     * Object's local 2D transformation
     */
    Transform2 localTransformation;

    /**
     * Object's world 2D transformation
     */
    Transform2 worldTransformation;

    /**
     * Controllers attached to this object. All of the controllers will be
     * updated on a call to update()
     */
    std::list<Controller*> controllers;

    /**
     * Children owned by this object.
     */
    std::list<GameObject*> children;

    /**
     * Backpointer to GameProgram that own's this object
     */
    GameProgram* gameProgram;

    /**
     * Pointer to parent object of the object.
     */
    GameObject* parent;

};

#endif // GAMEOBJECT_H
