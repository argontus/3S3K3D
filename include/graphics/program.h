/**
 * @file graphics/program.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PROGRAM_H_INCLUDED
#define GRAPHICS_PROGRAM_H_INCLUDED

#include <string>

#include <graphics/opengl.h>

class FragmentShader;
class VertexShader;

/**
 * Represents an OpenGL program.
 */
class Program
{
public:
    /**
     * Destructor.
     */
    ~Program();

    /**
     * Default constructor.
     */
    Program();

    /**
     * Gets the program Id.
     *
     * @return Program Id.
     */
    GLuint id() const;

    /**
     * Registers a vertex shader. If <code>p</code> is a null pointer, the
     * current vertex shader is unregistered. This program must be linked
     * before any changes take effect.
     *
     * @param p Vertex shader to register.
     *
     * @see link()
     */
    void setVertexShader(VertexShader* p);

    /**
     * Gets the registered vertex shader. If this program does not have a
     * registered vertex shader, the return value is a null pointer.
     *
     * @return Registered vertex shader.
     */
    VertexShader* vertexShader() const;

    /**
     * Registers a fragment shader. If <code>p</code> is a null pointer, the
     * current fragment shader is unregistered. This program must be linked
     * before any changes take effect.
     *
     * @param p Fragment shader to register.
     *
     * @see link()
     */
    void setFragmentShader(FragmentShader* p);

    /**
     * Gets the registered fragment shader. If this program does not have a
     * registered fragment shader, the return value is a null pointer.
     *
     * @return Registered fragment shader.
     */
    FragmentShader* fragmentShader() const;

    /**
     * Links this program. A program can be used only after it has been
     * successfully linked. Calling this member function will overwrite the
     * current info log string.
     *
     * @see infoLog() const
     *
     * @return <code>true</code>, if the link attempt was successful,
     * <code>false</code> otherwise.
     */
    bool link();

    /**
     * Gets the info log string.
     *
     * @return Info log string.
     */
    const std::string infoLog() const;

private:
    /**
     * Attaches all registered shaders to the stored OpenGL program object.
     */
    void attachShaders();

    /**
     * Detaches all attached shader objects from the stored OpenGL program
     * object.
     */
    void detachShaders();

    GLuint id_;                         ///< Program Id.
    VertexShader* vertexShader_;        ///< Registered vertex shader.
    FragmentShader* fragmentShader_;    ///< Registered fragment shader.

    // prevent copying
    Program(const Program&);
    Program& operator =(const Program&);
};

#endif // #ifndef GRAPHICS_PROGRAM_H_INCLUDED
