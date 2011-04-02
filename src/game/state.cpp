#include "state.h"

State::State( GameProgram* backpointer )
 : owner( backpointer )
{
    rootNode = new GroupNode();
}

State::~State()
{
    delete rootNode;
}

