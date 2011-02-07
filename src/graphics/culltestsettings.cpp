/**
 * @file graphics/culltestsettings.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/culltestsettings.h>

#include <algorithm>

CullTestSettings::CullTestSettings()
:   enabled(false),
    cullFace(CullFace::Back)
{
    // ...
}

void CullTestSettings::swap(CullTestSettings& other)
{
    std::swap(enabled, other.enabled);
    std::swap(cullFace, other.cullFace);
}
