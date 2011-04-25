/**
 * @file graphics/effect.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/effect.h>

#include <graphics/technique.h>
#include <graphics/runtimeassert.h>

Effect::~Effect()
{
    deleteTechniques();
}

Effect::Effect(const std::string& name, const int numTechniques)
:   name_(name),
    techniques_(static_cast<size_t>(numTechniques), 0) // fill with null ptrs
{
    // ...
}

Effect::Effect(const Effect& other)
:   name_(other.name_),
    techniques_(other.techniques_.size(), 0) // fill with null ptrs
{
    try
    {
        for (size_t i = 0; i < other.techniques_.size(); ++i)
        {
            techniques_[i] = other.techniques_[i]->clone();
        }
    }
    catch (...)
    {
        // deallocate the techniques that had been cloned before the exception
        // was thrown and rethrow
        deleteTechniques();
        throw;
    }
}

const std::string Effect::name() const
{
    return name_;
}

Effect* Effect::clone() const
{
    return new Effect(*this);
}

void Effect::setTechnique(const int index, Technique* const technique)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTechniques());
    GRAPHICS_RUNTIME_ASSERT(technique != 0);
    GRAPHICS_RUNTIME_ASSERT(techniques_[index] == 0);
    techniques_[index] = technique;
}

Technique* Effect::technique(const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTechniques());
    return techniques_[index];
}

const Technique* Effect::technique(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTechniques());
    return techniques_[index];
}

Technique* Effect::technique(const std::string& name)
{
    // call the const version
    return const_cast<Technique*>(const_cast<const Effect*>(this)->technique(name));
}

const Technique* Effect::technique(const std::string& name) const
{
    for (size_t i = 0; i < techniques_.size(); ++i)
    {
        if (techniques_[i]->name() == name)
        {
            return techniques_[i];
        }
    }

    GRAPHICS_RUNTIME_ASSERT(false);
    return 0;
}

int Effect::numTechniques() const
{
    return techniques_.size();
}

void Effect::deleteTechniques()
{
    for (size_t i = 0; i < techniques_.size(); ++i)
    {
        delete techniques_[i];
    }
}
