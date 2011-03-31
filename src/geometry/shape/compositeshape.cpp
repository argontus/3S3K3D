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
    for (size_t i = 0; i < primitives_.size(); ++i)
    {
        delete primitives_[i];
    }
}

CompositeShape::CompositeShape()
:   primitives_()
{
    // ...
}

CompositeShape::CompositeShape(const CompositeShape& other)
:   primitives_(other.primitives_)
{
    // ...
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

CompositeShape* CompositeShape::clone() const
{
    return new CompositeShape(*this);
}

const Extents2 CompositeShape::extents() const
{
    Extents2 e;

    for (size_t i = 0; i < primitives_.size(); ++i)
    {
        e.enclose(primitives_[i]->extents());
    }

    return e;
}
