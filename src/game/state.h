#ifndef STATE_H
#define STATE_H

#include <vector>
#include "gameprogram.h"
#include <graphics/node.h>
#include "gamescene.h"

/**
 * @file game/state.h
 * @author Marko Silokunnas
 *
 * Pure virtual class representing a state in a finite state machine.
 *
 */
class State
{
    public:
        State( GameProgram* backpointer );
        ~State();

        /**
         * Called once in frame to update the objects owned by the state
         */
        virtual void update( float deltaTime ) = 0;

        /**
         * Getter for the root node. Needed for rendering tha geometry of the
         * state
         */
        inline Node* getRootNode() const { return rootNode; }

        /**
         * Sets the scene that contains the objects in this state.
         * @param scene a pointer to a GameScene object.
         */
         inline void setScene( GameScene* scene ) { this->scene = scene; }

         /**
          * Gets the scene that contains the objects in this state.
          * @return scene a GameScene object.
          */
          inline GameScene* getScene() const { return scene; }

    protected:
        /**
         * backpointer to the GameProgram that own's this state
         */
        GameProgram* owner;

        /**
         * Root node of the state. Used to draw geometry of the state.
         */
        Node* rootNode;

        /**
         * Scene that plays in this state.
         */
        GameScene* scene;


    private:
};

#endif // STATE_H
