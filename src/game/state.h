#ifndef STATE_H
#define STATE_H

#include <vector>
#include "gameprogram.h"
#include <graphics/groupnode.h>

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
        State( GameProgram* backpointer = NULL );
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

    protected:
        /**
         * backpointer to the GameProgram that own's this state
         */
        GameProgram* owner;

        /**
         * Root node of the state. Used to draw geometry of the state.
         */
        GroupNode* rootNode;


    private:
};

#endif // STATE_H
