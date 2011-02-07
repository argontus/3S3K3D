/**
 * @file graphics/depthtestsettings.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/depthtestsettings.h>

#include <algorithm>

DepthTestSettings::DepthTestSettings()
:   enabled(false),
    compareFunc(DepthTestCompareFunc::Less)
{
    // ...
}

void DepthTestSettings::swap(DepthTestSettings& other)
{
    std::swap(enabled, other.enabled);
    std::swap(compareFunc, other.compareFunc);
}
