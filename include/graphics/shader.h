/**
 * @file graphics/shader.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_SHADER_H_INCLUDED
#define GRAPHICS_SHADER_H_INCLUDED

#include <string>

#include <graphics/opengl.h>

/**
 * Abstract base class for OpenGL shaders. Implements functionality common to
 * all OpenGL shader objects.
 */
class Shader
{
public:
    /**
     * Destructor.
     */
    virtual ~Shader();

    /**
     * Gets the shader Id.
     *
     * @return Shader Id.
     */
    GLuint id() const;

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
     * Compiles this shader object. A shader can be used only after it has been
     * successfully compiled. Calling this member function will overwrite the
     * current info log string.
     *
     * @return <code>true</code>, if the compile attempt was successful,
     * <code>false</code> otherwise.
     *
     * @see infoLog() const
     */
    bool compile();

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
    explicit Shader(GLenum type);

private:
    GLuint id_; ///< Shader Id.

    // prevent copying
    Shader(const Shader&);
    Shader& operator =(const Shader&);
};

#endif // #ifndef GRAPHICS_SHADER_H_INCLUDED
