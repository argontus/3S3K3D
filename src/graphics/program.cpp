/**
 * @file graphics/program.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/program.h>

#include <vector>

#include <graphics/fragmentshader.h>
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

GLuint Program::id() const
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

void Program::setFragmentShader(FragmentShader* const p)
{
    fragmentShader_ = p;
}

FragmentShader* Program::fragmentShader() const
{
    return fragmentShader_;
}

bool Program::link()
{
    // synchronize states of the referenced OpenGL program object and this
    // object
    detachShaders();
    attachShaders();

    glLinkProgram(id_);

    // fetch the link status
    GLint status = GL_FALSE;
    glGetProgramiv(id_, GL_LINK_STATUS, &status);

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

void Program::attachShaders()
{
    if (vertexShader() != 0)
    {
        // attach registered vertex shader
        glAttachShader(id_, vertexShader_->id());
    }

    if (fragmentShader() != 0)
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
