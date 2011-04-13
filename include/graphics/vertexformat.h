/**
 * @file graphics/vertexformat.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXFORMAT_H_INCLUDED
#define GRAPHICS_VERTEXFORMAT_H_INCLUDED

#include <graphics/vertexattribute.h>

/**
 * Describes a vertex format.
 */
class VertexFormat
{
public:
    /**
     * Destructor.
     */
    ~VertexFormat();

    /**
     * Constructor.
     *
     * @param numAttributes Number of attributes, must be > 0.
     */
    explicit VertexFormat(int numAttributes);

    /**
     * Sets the type and usage tag of a specified attribute. This vertex format
     * must be (re)compiled by calling <code>compile()</code> after an
     * attribute has been modified.
     *
     * @param index Attribute index, must be between [0,
     * <code>numAttributes()</code>).
     * @param type Attribute type.
     * @param usage Attribute usage.
     *
     * @see compile()
     */
    void setAttribute(
        int index,
        VertexAttribute::Type::Enum type,
        VertexAttribute::Usage::Enum usage);

    /**
     * Gets a specified vertex attribute.
     *
     * @param index Attribute index, must be between [0,
     * <code>numAttributes()</code>).
     */
    const VertexAttribute& attribute(int index) const;

    /**
     * Gets the number of attributes.
     *
     * @return Number of attributes.
     */
    int numAttributes() const;

    /**
     * Gets the vertex stride in bytes. Vertex stride is the number of bytes
     * between two consecutive vertices in a vertex buffer. The return value is
     * valid only if this vertex format has been compiled and no attributes
     * have been modified after the last compilation.
     *
     * @return Vertex stride in bytes.
     *
     * @see compile()
     */
    int stride() const;

    /**
     * Compiles this vertex format. Compiling will calculate the vertex stride
     * and attribute offsets. A vertex format must be compiled after all
     * attributes have been initialized and recompiled if attributes are
     * modified after a compilation.
     */
    void compile();

private:
    VertexAttribute* attributes_;   ///< Vertex attributes.
    int numAttributes_;             ///< Number of vertex attributes.
    int stride_;                    ///< Vertex stride in bytes.

    // prevent copying
    VertexFormat(const VertexFormat&);
    VertexFormat& operator =(const VertexFormat&);
};

#endif // #ifndef GRAPHICS_VERTEXFORMAT_H_INCLUDED
