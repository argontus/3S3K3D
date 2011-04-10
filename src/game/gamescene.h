/**
 * @file game/gamescene.h
 * @author Juhani Alanko
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>

class GameObject;
class State;

class GameScene
{
    public:
        GameScene( State* parentState);
        virtual ~GameScene();


        /**
         * Add a GameObject into the scene. GameScene handles
         * the freeing of the object.
         * @param object a GameObject to add into the scene.
         */
        void addObject( GameObject* object );


        /**
         * Remove a GameObject from the scene. Also frees it from
         * the memory.
         * @param object a GameObject to remove from the scene.
         */
        void removeObject( GameObject* object );


        /**
         * Updates the scene in the following order:
         * 1. update all game objects
         * 2. find intersections & compare to previous frame
         * 3. invoke events
         * 4. invoke onLeave events
         * 5. trash disposal
         * @param deltaTime a scaling frame time value.
         */
        virtual void update( float deltaTime );


        /**
         * Getter for GameProgram backpointer
         *
         * @return GameProgram* backpointer to the program that owns the scene
         */
        inline State* getState() { return state_; }

    private:
        /**
         * Contains the GameObjects assigned to this scene.
         */
        std::vector<GameObject*>        gameObjects_;

        /**
         * Backpointer to the state that owns this scene.
         */
        State*                          state_;
};

#endif // GAMESCENE_H
