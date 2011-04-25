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
            // TODO: rename these to Float, Vec2, Vec3 and Vec4?
            Float1,
            Float2,
            Float3,
            Float4

            // TODO: add more if needed, remember to update Device
            // implementation
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    VertexAttribute();

    /**
     * Sets the attribute offset. Only <code>VertexFormat::compile()</code>
     * should call this member function.
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
     * Sets the attribute name.
     *
     * @param name Attribute name, empty string indicates an unused attribute.
     */
    void setName(const std::string& name);

    /**
     * Gets the attribute name. Attribute name is the name of the corresponding
     * GLSL vertex shader input parameter.
     *
     * @return Attribute name, empty string indicates an unused attribute.
     */
    const std::string& name() const;

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

private:
    int offset_;        ///< Offset in bytes.
    Type::Enum type_;   ///< Type.
    std::string name_;  ///< Name, empty string indicates an unused attribute.
};

#endif // #ifndef GRAPHICS_VERTEXATTRIBUTE_H_INCLUDED
