/**
 * @file graphics/predrawparams.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/predrawparams.h>

#include <algorithm>

PredrawParams::PredrawParams()
:   renderQueue(0),
    visibleGroups(0)
{
    // ...
}

void PredrawParams::swap(PredrawParams& other)
{
    std::swap(renderQueue, other.renderQueue);
    std::swap(visibleGroups, other.visibleGroups);
}
