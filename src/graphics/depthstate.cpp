/**
 * @file graphics/depthstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/depthstate.h>

const DepthState* DepthState::disabled()
{
    static bool initialized = false;
    static DepthState state;

    if (initialized == false)
    {
        state.enabled = false;
        state.writeEnabled = false;
        state.compareFunc = CompareFunc::Never;

        initialized = true;
    }

    return &state;
}

const DepthState* DepthState::lessEqual()
{
    static bool initialized = false;
    static DepthState state;

    if (initialized == false)
    {
        state.enabled = true;
        state.writeEnabled = true;
        state.compareFunc = CompareFunc::LessEqual;

        initialized = true;
    }

    return &state;
}

const DepthState* DepthState::lessEqualReadOnly()
{
    static bool initialized = false;
    static DepthState state;

    if (initialized == false)
    {
        state.enabled = true;
        state.writeEnabled = false;
        state.compareFunc = CompareFunc::LessEqual;

        initialized = true;
    }

    return &state;
}

DepthState::DepthState()
:   enabled(true),
    writeEnabled(true),
    compareFunc(CompareFunc::LessEqual)
{
    // ...
}
