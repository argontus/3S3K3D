/**
 * @file graphics/shader.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/shader.h>

#include <vector>

#include <graphics/opengl.h>
#include <graphics/runtimeassert.h>

Shader::~Shader()
{
    glDeleteShader(id_);
}

GLuint Shader::id() const
{
    return id_;
}

void Shader::setSourceText(const std::string& sourceText)
{
    const GLchar* p = sourceText.c_str();
    glShaderSource(id_, 1, &p, 0);
}

const std::string Shader::sourceText() const
{
    // fetch the required character buffer size
    GLint size = 0;
    glGetShaderiv(id_, GL_SHADER_SOURCE_LENGTH, &size);

    // fetch the NUL-terminated source text to a character buffer
    std::vector<GLchar> buffer(size);
    glGetShaderSource(id_, size, 0, buffer.data());

    return std::string(buffer.data());
}

bool Shader::compile()
{
    glCompileShader(id_);

    // fetch the compile status
    GLint status = GL_FALSE;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &status);

    return status == GL_TRUE;
}

const std::string Shader::infoLog() const
{
    // fetch the required character buffer size
    GLint size = 0;
    glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &size);

    // fetch the NUL-terminated info log to a character buffer
    std::vector<GLchar> buffer(size);
    glGetShaderInfoLog(id_, size, 0, buffer.data());

    return std::string(buffer.data());
}

Shader::Shader(const GLenum type)
:   id_(glCreateShader(type))
{
    // ...
}
