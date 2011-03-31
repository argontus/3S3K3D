/**
 * @file graphics/program.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PROGRAM_H_INCLUDED
#define GRAPHICS_PROGRAM_H_INCLUDED

#include <stdint.h>

#include <string>

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
    uint32_t id() const;

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
     * Gets a boolean value indicating whether or not this program has a
     * registered vertex shader. The return value is equivalent to
     * <code>vertexShader() != 0</code>.
     *
     * @return <code>true</code>, if this program has a registered vertex
     * shader, <code>false</code> otherwise.
     */
    bool hasVertexShader() const;

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
     * Gets a boolean value indicating whether or not this program has a
     * registered fragment shader. The return value is equivalent to
     * <code>fragmentShader() != 0</code>.
     *
     * @return <code>true</code>, if this program has a registered fragment
     * shader, <code>false</code> otherwise.
     */
    bool hasFragmentShader() const;

    /**
     * @name Vertex Attribute Bindings
     */
    //@{
    // TODO: comments
    void bindAttribLocation(uint32_t index, const std::string& name);
    int32_t attribLocation(const std::string& name) const;
    //@}

    /**
     * @name Fragment Data Bindings
     */
    //@{
    // TODO: comments
    void bindFragDataLocation(uint32_t index, const std::string& name);
    int32_t fragDataLocation(const std::string& name) const;
    //@}

    /**
     * Links this program. Calling this member function will overwrite the
     * current info log string.
     *
     * @see linkStatus() const
     * @see infoLog() const
     */
    void link();

    /**
     * Gets a boolean value indicating whether or not the last link attempt was
     * successful. A program can be used only after it has been successfully
     * linked.
     *
     * @return <code>true</code>, if the last link attempt was successful,
     * <code>false</code> otherwise.
     */
    bool linkStatus() const;

    /**
     * Validates this program. Calling this member function will overwrite the
     * current info log string.
     *
     * @see validateStatus() const
     * @see infoLog() const
     */
    void validate();

    /**
     * Gets a boolean value indicating whether or not the last validation
     * attempt was successful. If validation is successful, this program is
     * guaranteed to execute given the OpenGL state at the time of the
     * validation. Otherwise, this program is guaranteed to not execute.
     *
     * @return <code>true</code>, if the last validation attempt was
     * successful, <code>false</code> otherwise.
     */
    bool validateStatus() const;

    /**
     * Gets the info log string.
     *
     * @return Info log string.
     */
    const std::string infoLog() const;

    /**
     * @name Default Uniform Block Variables
     */
    //@{
    /**
     * Gets the location Id of the uniform variable matching a given uniform
     * variable name.
     *
     * @param name Uniform variable name.
     *
     * @return Location Id of the uniform variable matching the given uniform
     * variable name.
     */
    int32_t uniformLocation(const std::string& name) const;

    void setUniform1f(const std::string& name, float v0);
    void setUniform2f(const std::string& name, float v0, float v1);
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void setUniform1fv(const std::string& name, int count, const float* src);
    void setUniform2fv(const std::string& name, int count, const float* src);
    void setUniform3fv(const std::string& name, int count, const float* src);
    void setUniform4fv(const std::string& name, int count, const float* src);

    void setUniformMatrix2x2fv(const std::string& name, int count, bool transpose, const float* src);
    void setUniformMatrix3x3fv(const std::string& name, int count, bool transpose, const float* src);
    void setUniformMatrix4x4fv(const std::string& name, int count, bool transpose, const float* src);

    // TODO: texture samplers
    //@}

    // TODO: named uniform block variables
    // TODO: vertex attribute queries
    // TODO: uniform variable queries

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

    uint32_t id_;                       ///< Program Id.
    VertexShader* vertexShader_;        ///< Registered vertex shader.
    FragmentShader* fragmentShader_;    ///< Registered fragment shader.

    // prevent copying
    Program(const Program&);
    Program& operator =(const Program&);
};

#endif // #ifndef GRAPHICS_PROGRAM_H_INCLUDED
