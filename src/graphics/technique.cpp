/**
 * @file graphics/technique.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/technique.h>

#include <graphics/pass.h>
#include <graphics/runtimeassert.h>

Technique::~Technique()
{
    deletePasses();
}

Technique::Technique(const std::string& name, const int numPasses)
:   name_(name),
    passes_(static_cast<size_t>(numPasses), 0) // fill with null ptrs
{
    // ...
}

Technique::Technique(const Technique& other)
:   name_(other.name_),
    passes_(other.passes_.size(), 0) // fill with null ptrs
{
    try
    {
        for (size_t i = 0; i < other.passes_.size(); ++i)
        {
            passes_[i] = other.passes_[i]->clone();
        }
    }
    catch (...)
    {
        // deallocate the passes that had been cloned before the exception was
        // thrown and rethrow
        deletePasses();
        throw;
    }
}

const std::string Technique::name() const
{
    return name_;
}

Technique* Technique::clone() const
{
    return new Technique(*this);
}

void Technique::setPass(const int index, Pass* const pass)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numPasses());
    GRAPHICS_RUNTIME_ASSERT(pass != 0);
    GRAPHICS_RUNTIME_ASSERT(passes_[index] == 0);
    passes_[index] = pass;
}

Pass* Technique::pass(const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numPasses());
    return passes_[index];
}

const Pass* Technique::pass(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numPasses());
    return passes_[index];
}

Pass* Technique::pass(const std::string& name)
{
    // call the const version
    return const_cast<Pass*>(const_cast<const Technique*>(this)->pass(name));
}

const Pass* Technique::pass(const std::string& name) const
{
    for (size_t i = 0; i < passes_.size(); ++i)
    {
        if (passes_[i]->name() == name)
        {
            return passes_[i];
        }
    }

    GRAPHICS_RUNTIME_ASSERT(false);
    return 0;
}

int Technique::numPasses() const
{
    return passes_.size();
}

void Technique::deletePasses()
{
    for (size_t i = 0; i < passes_.size(); ++i)
    {
        delete passes_[i];
    }
}
