#include "state.h"
#include "graphics/groupnode.h"

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

