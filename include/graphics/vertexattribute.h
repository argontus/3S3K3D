/**
 * @file graphics/vertexattribute.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED
#define GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED

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
            PointSize,
            TexCoord,
            Color

            // TODO: add more if needed
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    VertexAttribute();

    /**
     * Sets the attribute offset.
     *
     * @param offset Attribute offset in bytes, cannot be negative.
     */
    void setOffset(int offset);

    /**
     * Gets the attribute offset.
     *
     * @return Attribute offset in bytes.
     */
    int offset() const;

    /**
     * Sets the attribute type.
     *
     * @param type Attribute type.
     */
    void setType(Type::Enum type);

    /**
     * Gets the attribute type.
     *
     * @return Attribute type.
     */
    Type::Enum type() const;

    /**
     * Sets the attribute usage.
     *
     * @param usage Attribute usage.
     */
    void setUsage(Usage::Enum usage);

    /**
     * Gets the attribute usage.
     *
     * @return Attribute usage.
     */
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

    /**
     * Gets the attribute name. Attribute name is the name of the corresponding
     * GLSL vertex shader input parameter. The attribute usage cannot be
     * <code>Usage::Unused</code> when this funtion is called.
     *
     * @return Attribute name.
     */
    const char* name() const;

private:
    int offset_;        ///< Offset in bytes.
    Type::Enum type_;   ///< Type.
    Usage::Enum usage_; ///< Usage.
};

#endif // #ifndef GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED
