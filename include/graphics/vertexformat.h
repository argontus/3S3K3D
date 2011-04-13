/**
 * @file graphics/vertexformat.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXFORMAT_H_INCLUDED
#define GRAPHICS_VERTEXFORMAT_H_INCLUDED

#include <graphics/vertexattribute.h>

class VertexFormat
{
public:
    ~VertexFormat();

    // numAttributes must be > 0
    explicit VertexFormat(int numAttributes);

    void setAttribute(
        int index,
        VertexAttribute::Type::Enum type,
        VertexAttribute::Usage::Enum usage);

    const VertexAttribute& attribute(int index) const;

    int numAttributes() const;
    int stride() const;

    // the vertex format must be (re)compiled if attributes are modified
    void compile();

private:
    VertexAttribute* attributes_;
    int numAttributes_;
    int stride_;

    // prevent copying
    VertexFormat(const VertexFormat&);
    VertexFormat& operator =(const VertexFormat&);
};

#endif // #ifndef GRAPHICS_VERTEXFORMAT_H_INCLUDED
