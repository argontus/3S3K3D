/**
 * @file graphics/depthstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/depthstate.h>

DepthState::DepthState()
:   writeEnabled(true),
    compareFunc(CompareFunc::Less)
{
    // ...
}
