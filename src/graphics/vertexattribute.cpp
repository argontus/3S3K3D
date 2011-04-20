/**
 * @file graphics/vertexattribute.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/vertexattribute.h>

#include <graphics/runtimeassert.h>

VertexAttribute::VertexAttribute()
:   offset_(0),
    type_(Type::Float3),
    name_()
{
    // ...
}

void VertexAttribute::setOffset(const int offset)
{
    GRAPHICS_RUNTIME_ASSERT(offset >= 0);
    offset_ = offset;
}

int VertexAttribute::offset() const
{
    return offset_;
}

void VertexAttribute::setType(const Type::Enum type)
{
    type_ = type;
}

VertexAttribute::Type::Enum VertexAttribute::type() const
{
    return type_;
}

void VertexAttribute::setName(const std::string& name)
{
    name_ = name;
}

const std::string& VertexAttribute::name() const
{
    return name_;
}

int VertexAttribute::numComponents() const
{
    // TODO: optimize by using a lookup table?

    switch (type_)
    {
        case Type::Float1:  return 1;
        case Type::Float2:  return 2;
        case Type::Float3:  return 3;
        case Type::Float4:  return 4;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

int VertexAttribute::size() const
{
    // TODO: optimize by using a lookup table?

    switch (type_)
    {
        case Type::Float1:  return 4;
        case Type::Float2:  return 8;
        case Type::Float3:  return 12;
        case Type::Float4:  return 16;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}
