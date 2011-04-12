/**
 * @file graphics/vertexattribute.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/vertexattribute.h>

#include <graphics/runtimeassert.h>

VertexAttribute::VertexAttribute()
:   offset_(0),
    type_(Type::Float3),
    usage_(Usage::Coord)
{
    // ...
}

VertexAttribute::VertexAttribute(const Type::Enum type, const Usage::Enum usage)
:   offset_(0),
    type_(type),
    usage_(usage)
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

void VertexAttribute::setUsage(const Usage::Enum usage)
{
    usage_ = usage;
}

VertexAttribute::Usage::Enum VertexAttribute::usage() const
{
    return usage_;
}

int VertexAttribute::numComponents() const
{
    // TODO: use a lookup table?

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
    // TODO: use a lookup table?

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

const std::string VertexAttribute::name() const
{
    // TODO: use a lookup table?

    switch (usage_)
    {
        case Usage::Coord:      return "coord";
        case Usage::Normal:     return "normal";
        case Usage::Tangent:    return "tangent";
        case Usage::Binormal:   return "binormal";
        case Usage::PointSize:  return "pointSize";
        case Usage::TexCoord:   return "texCoord";
        case Usage::Color:      return "color";

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return "";
    }
}
