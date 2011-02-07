/**
 * @file graphics/shader.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_SHADER_H_INCLUDED
#define GRAPHICS_SHADER_H_INCLUDED

#include <stdint.h>

#include <string>

/**
 * Abstract base class for OpenGL shaders. Implements functionality common to
 * all OpenGL shader objects.
 */
class Shader
{
public:
    /**
     * Enumeration wrapper for possible shader type tags.
     */
    struct Type
    {
        /**
         * Possible shader type tags.
         */
        enum Enum
        {
            FragmentShader, ///< Type tag for <code>FragmentShader</code>.
            VertexShader    ///< Type tag for <code>VertexShader</code>.
        };
    };

    /**
     * Destructor.
     */
    virtual ~Shader();

    /**
     * Gets the shader Id.
     *
     * @return Shader Id.
     */
    uint32_t id() const;

    /**
     * Sets the shader source text.
     *
     * @param sourceText Shader source text.
     */
    void setSourceText(const std::string& sourceText);

    /**
     * Gets the shader source text.
     *
     * @return Shader source text.
     */
    const std::string sourceText() const;

    /**
     * Compiles this shader object. Calling this member function will overwrite
     * the current info log string.
     *
     * @see compileStatus() const
     * @see infoLog() const
     */
    void compile();

    /**
     * Gets a boolean value indicating whether or not the last compile attempt
     * was successful. A shader can be used only after it has been successfully
     * compiled.
     *
     * @return <code>true</code>, if the last compile attempt was successful,
     * <code>false</code> otherwise.
     */
    bool compileStatus() const;

    /**
     * Gets the info log string.
     *
     * @return Info log string.
     */
    const std::string infoLog() const;

protected:
    /**
     * Constructor.
     *
     * @param type Shader type.
     */
    explicit Shader(Type::Enum type);

private:
    uint32_t id_;   ///< Shader Id.

    // prevent copying
    Shader(const Shader&);
    Shader& operator =(const Shader&);
};

// TODO: decide how errors should be reported
/**
 * Helper function for reading text file contents.
 *
 * @param path A relative or absolute path for the file to open. The file is
 * interpreted as ASCII encoded text file.
 *
 * @return Contents of the specified file.
 */
const std::string readSourceText(const std::string& path);

#endif
