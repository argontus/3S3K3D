/**
 * @file graphics/vertexattribute.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED
#define GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED

#include <string>

/**
 * Describes a vertex attribute.
 */
class VertexAttribute
{
public:
    /**
     * Enumeration wrapper for possible vertex attribute types.
     */
    struct Type
    {
        /**
         * Possible vertex attribute types.
         */
        enum Enum
        {
            Float1,
            Float2,
            Float3,
            Float4

            // TODO: add more if needed
        };
    };

    /**
     * Enumeration wrapper for possible vertex attribute usage tags.
     */
    struct Usage
    {
        /**
         * Possible vertex attribute usage tags.
         */
        enum Enum
        {
            Unused,
            Position,
            Normal,
            Tangent,
            Binormal,
            PointSize,
            TexCoord,
            Color

            // TODO: add more if needed
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    VertexAttribute();
    VertexAttribute(Type::Enum type, Usage::Enum usage);

    // offset must be >= 0
    void setOffset(int offset);

    int offset() const;

    void setType(Type::Enum type);
    Type::Enum type() const;

    void setUsage(Usage::Enum usage);
    Usage::Enum usage() const;

    /**
     * Gets the number of components. For example, <code>vec4</code>
     * (<code>Type::Float4</code>) has 4 components of type <code>float</code>.
     *
     * @return Number of components.
     */
    int numComponents() const;

    /**
     * Gets the size in bytes.
     *
     * @return Size in bytes.
     */
    int size() const;

    // TODO: the return value could be const char*
    // usage cannot be Usage::Unused
    const std::string name() const;

private:
    int offset_;        ///< Offset in bytes.
    Type::Enum type_;   ///< Type.
    Usage::Enum usage_; ///< Usage.
};

#endif // #ifndef GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED
