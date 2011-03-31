/**
 * @file geometry/shape/compositeshape.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/shape/compositeshape.h>

#include <geometry/extents2.h>
#include <geometry/runtimeassert.h>

#include <geometry/shape/primitiveshape.h>

CompositeShape::~CompositeShape()
{
    clear();
}

CompositeShape::CompositeShape()
:   primitives_()
{
    // ...
}

CompositeShape::CompositeShape(const CompositeShape& other)
:   primitives_()
{
    try
    {
        for (int i = 0; i < other.numPrimitives(); ++i)
        {
            addPrimitive(other.primitive(i));
        }
    }
    catch (...)
    {
        // deallocate all cloned primitive shapes and rethrow
        clear();
        throw;
    }
}

void CompositeShape::addPrimitive(const PrimitiveShape& p)
{
    PrimitiveShape* const clone = p.clone();

    try
    {
        primitives_.push_back(clone);
    }
    catch (...)
    {
        // deallocate the cloned primitive shape and rethrow
        delete clone;
        throw;
    }
}

int CompositeShape::numPrimitives() const
{
    return primitives_.size();
}

const PrimitiveShape& CompositeShape::primitive(const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < numPrimitives());
    return *primitives_[index];
}

void CompositeShape::clear()
{
    for (size_t i = 0; i < primitives_.size(); ++i)
    {
        delete primitives_[i];
    }

    primitives_.clear();
}

CompositeShape* CompositeShape::clone() const
{
    return new CompositeShape(*this);
}

const Extents2 CompositeShape::extents() const
{
    Extents2 e;

    for (int i = 0; i < numPrimitives(); ++i)
    {
        e.enclose(primitive(i).extents());
    }

    return e;
}
