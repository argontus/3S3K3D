#include "state.h"

State::State( GameProgram* backpointer )
 :  owner( backpointer ),
    scene( NULL )
{
    rootNode = new GroupNode();
}

State::~State()
{
    delete rootNode;
    rootNode = NULL;
    if( scene != NULL )
    {
        delete scene;
        scene = NULL;
    }
}

