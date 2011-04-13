/**
 * @file graphics/vertexformat.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/vertexformat.h>

#include <graphics/runtimeassert.h>

VertexFormat::~VertexFormat()
{
    delete [] attributes_;
}

VertexFormat::VertexFormat(const int numAttributes)
:   attributes_(new VertexAttribute[numAttributes]),
    numAttributes_(numAttributes),
    stride_(0)
{
    GRAPHICS_RUNTIME_ASSERT(numAttributes > 0);
}

void VertexFormat::setAttribute(
    const int index,
    const VertexAttribute::Type::Enum type,
    const VertexAttribute::Usage::Enum usage)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numAttributes_);
    attributes_[index] = VertexAttribute(type, usage);
}

const VertexAttribute& VertexFormat::attribute(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numAttributes_);
    return attributes_[index];
}

int VertexFormat::numAttributes() const
{
    return numAttributes_;
}

int VertexFormat::stride() const
{
    // zero stride indicates that the vertex format has not been compiled
    GRAPHICS_RUNTIME_ASSERT(stride_ > 0);
    return stride_;
}

void VertexFormat::compile()
{
    stride_ = 0;

    for (int i = 0; i < numAttributes_; ++i)
    {
        attributes_[i].setOffset(stride_);
        stride_ += attributes_[i].size();
    }

    // TODO: make sure there are no duplicate attributes?
}
