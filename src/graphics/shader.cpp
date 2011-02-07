/**
 * @file graphics/shader.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/shader.h>

#include <fstream>
#include <vector>

#include <GL/glew.h>

#include <graphics/runtimeassert.h>

Shader::~Shader()
{
    glDeleteShader(id_);
}

uint32_t Shader::id() const
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

    // fetch the source text to a character buffer
    std::vector<GLchar> buffer(size);
    glGetShaderSource(id_, size, 0, buffer.data());

    return std::string(buffer.data());
}

void Shader::compile()
{
    glCompileShader(id_);
}

bool Shader::compileStatus() const
{
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

    // fetch the info log to a character buffer
    std::vector<GLchar> buffer(size);
    glGetShaderInfoLog(id_, size, 0, buffer.data());

    return std::string(buffer.data());
}

Shader::Shader(const Type::Enum type)
:   id_(0)
{
    switch (type)
    {
        case Type::FragmentShader:
            id_ = glCreateShader(GL_FRAGMENT_SHADER);
            break;

        case Type::VertexShader:
            id_ = glCreateShader(GL_VERTEX_SHADER);
            break;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            break;
    }
}

const std::string readSourceText(const std::string& path)
{
    std::ifstream inputStream;
    inputStream.open(path.c_str(), std::ios::in);

    if (inputStream.is_open() == false)
    {
        // TODO: quick & dirty, decide how errors should be reported
        GRAPHICS_RUNTIME_ASSERT(false);

        return std::string();
    }

    std::string text;
    char c;

    while (inputStream.get(c))
    {
        text += c;
    }

    return text;
}
