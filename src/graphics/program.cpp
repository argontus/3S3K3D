/**
 * @file graphics/program.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/program.h>

#include <vector>

#include <graphics/fragmentshader.h>
#include <graphics/opengl.h>
#include <graphics/vertexshader.h>

Program::~Program()
{
    // this will automatically detach any attached shader objects
    glDeleteProgram(id_);
}

Program::Program()
:   id_(glCreateProgram()),
    vertexShader_(0),
    fragmentShader_(0)
{
    // ...
}

uint32_t Program::id() const
{
    return id_;
}

void Program::setVertexShader(VertexShader* const p)
{
    vertexShader_ = p;
}

VertexShader* Program::vertexShader() const
{
    return vertexShader_;
}

bool Program::hasVertexShader() const
{
    return vertexShader_ != 0;
}

void Program::setFragmentShader(FragmentShader* const p)
{
    fragmentShader_ = p;
}

FragmentShader* Program::fragmentShader() const
{
    return fragmentShader_;
}

bool Program::hasFragmentShader() const
{
    return fragmentShader_ != 0;
}

void Program::bindAttribLocation(
    const uint32_t index,
    const std::string& name)
{
    glBindAttribLocation(id_, index, name.c_str());
}

int32_t Program::attribLocation(const std::string& name) const
{
    return glGetAttribLocation(id_, name.c_str());
}

void Program::bindFragDataLocation(
    const uint32_t index,
    const std::string& name)
{
    glBindFragDataLocation(id_, index, name.c_str());
}

int32_t Program::fragDataLocation(const std::string& name) const
{
    return glGetFragDataLocation(id_, name.c_str());
}

void Program::link()
{
    // synchronize states of the referenced OpenGL program object and this
    // object
    detachShaders();
    attachShaders();

    glLinkProgram(id_);
}

bool Program::linkStatus() const
{
    // fetch the link status
    GLint status = GL_FALSE;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);

    return status == GL_TRUE;
}

void Program::validate()
{
    glValidateProgram(id_);
}

bool Program::validateStatus() const
{
    // fetch the validation status
    GLint status = GL_FALSE;
    glGetProgramiv(id_, GL_VALIDATE_STATUS, &status);

    return status == GL_TRUE;
}

const std::string Program::infoLog() const
{
    // fetch the required character buffer size
    GLint size = 0;
    glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &size);

    // fetch the NUL-terminated info log to a character buffer
    std::vector<GLchar> buffer(size);
    glGetProgramInfoLog(id_, size, 0, buffer.data());

    return std::string(buffer.data());
}

int32_t Program::uniformLocation(const std::string& name) const
{
    return glGetUniformLocation(id_, name.c_str());
}

void Program::setUniform1f(
    const std::string& name,
    const float v0)
{
    glUniform1f(uniformLocation(name), v0);
}

void Program::setUniform2f(
    const std::string& name,
    const float v0,
    const float v1)
{
    glUniform2f(uniformLocation(name), v0, v1);
}

void Program::setUniform3f(
    const std::string& name,
    const float v0,
    const float v1,
    const float v2)
{
    glUniform3f(uniformLocation(name), v0, v1, v2);
}

void Program::setUniform4f(
    const std::string& name,
    const float v0,
    const float v1,
    const float v2,
    const float v3)
{
    glUniform4f(uniformLocation(name), v0, v1, v2, v3);
}

void Program::setUniform1fv(
    const std::string& name,
    const int count,
    const float* const src)
{
    glUniform1fv(uniformLocation(name), count, src);
}

void Program::setUniform2fv(
    const std::string& name,
    const int count,
    const float* const src)
{
    glUniform2fv(uniformLocation(name), count, src);
}

void Program::setUniform3fv(
    const std::string& name,
    const int count,
    const float* const src)
{
    glUniform3fv(uniformLocation(name), count, src);
}

void Program::setUniform4fv(
    const std::string& name,
    const int count,
    const float* const src)
{
    glUniform4fv(uniformLocation(name), count, src);
}

void Program::setUniformMatrix2x2fv(
    const std::string& name,
    const int count,
    const bool transpose,
    const float* const src)
{
    glUniformMatrix2fv(uniformLocation(name), count, transpose, src);
}

void Program::setUniformMatrix3x3fv(
    const std::string& name,
    const int count,
    const bool transpose,
    const float* const src)
{
    glUniformMatrix3fv(uniformLocation(name), count, transpose, src);
}

void Program::setUniformMatrix4x4fv(
    const std::string& name,
    const int count,
    const bool transpose,
    const float* const src)
{
    glUniformMatrix4fv(uniformLocation(name), count, transpose, src);
}

void Program::attachShaders()
{
    if (hasVertexShader())
    {
        // attach registered vertex shader
        glAttachShader(id_, vertexShader_->id());
    }

    if (hasFragmentShader())
    {
        // attach registered fragment shader
        glAttachShader(id_, fragmentShader_->id());
    }
}

void Program::detachShaders()
{
    // fetch the required shader id buffer size
    GLint size = 0;
    glGetProgramiv(id_, GL_ATTACHED_SHADERS, &size);

    // fetch the shader ids to a buffer
    std::vector<GLuint> buffer(size);
    glGetAttachedShaders(id_, size, 0, buffer.data());

    // detach all shader objects
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        glDetachShader(id_, buffer[i]);
    }
}
