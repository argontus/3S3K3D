/**
 * @file graphics/vertexbuffer.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/vertexbuffer.h>

#include <graphics/runtimeassert.h>

VertexBuffer::~VertexBuffer()
{
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    if (id_ == activeId())
    {
        // this is the active buffer, unbind it
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        GRAPHICS_RUNTIME_ASSERT(activeId() == 0);
    }

    glDeleteBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(
    const int numElements,
    const int elementSize,
    const void* const data,
    const Usage::Enum usage)
:   numElements_(numElements),
    elementSize_(elementSize),
    id_(0),
    previousId_(0),
    usage_(usage)
{
    GRAPHICS_RUNTIME_ASSERT(numElements > 0);
    GRAPHICS_RUNTIME_ASSERT(elementSize > 0);

    glGenBuffers(1, &id_);
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    // fetch the id of the currently bound buffer
    const GLuint previousId = activeId();

    // make sure this buffer is bound
    if (id_ != previousId)
    {
        // the given buffer is not bound, bind it
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeId() == id_);
    }

    glBufferData(
        GL_ARRAY_BUFFER,
        numElements_ * elementSize_,
        data,
        convert(usage)
    );

    if (id_ != previousId)
    {
        // restore previous buffer binding so that constructing a vertex buffer
        // does not have any size effects
        glBindBuffer(GL_ARRAY_BUFFER, previousId);
        GRAPHICS_RUNTIME_ASSERT(activeId() == previousId);
    }
}

void* VertexBuffer::lock(const Access::Enum access)
{
    // lock the entire buffer
    return lock(0, numElements(), access);
}

void* VertexBuffer::lock(
    const int offset,
    const int count,
    const Access::Enum access)
{
    // store id of the currently bound buffer so that it can be restored when
    // unlocking this buffer
    previousId_ = activeId();

    // make sure this buffer is bound
    if (id_ != previousId_)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeId() == id_);
    }

    // returns a null pointer on error
    void* const data = glMapBufferRange(
        GL_ARRAY_BUFFER,
        offset,
        count * elementSize_,
        convert(access)
    );

    GRAPHICS_RUNTIME_ASSERT(data != 0);
    return data;
}

void VertexBuffer::unlock()
{
    GRAPHICS_RUNTIME_ASSERT(id_ == activeId());

    // returns GL_FALSE on error, GL_TRUE on success
    const GLboolean result = glUnmapBuffer(GL_ARRAY_BUFFER);
    GRAPHICS_RUNTIME_ASSERT(result == GL_TRUE);

    if (id_ != previousId_)
    {
        // restore previous binding
        glBindBuffer(GL_ARRAY_BUFFER, previousId_);
        GRAPHICS_RUNTIME_ASSERT(activeId() == previousId_);
    }
}

int VertexBuffer::numElements() const
{
    return numElements_;
}

int VertexBuffer::elementSize() const
{
    return elementSize_;
}

GLuint VertexBuffer::id() const
{
    return id_;
}

VertexBuffer::Usage::Enum VertexBuffer::usage() const
{
    return usage_;
}

GLbitfield VertexBuffer::convert(const Access::Enum access)
{
    switch (access)
    {
        case Access::ReadOnly:
            return GL_MAP_READ_BIT;

        case Access::ReadWrite:
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;

        case Access::WriteOnly:
            // TODO: This could be more efficient if used with
            // GL_MAP_INVALIDATE_RANGE_BIT but it doesn't seem to work with
            // index arrays, GLuint and Usage::Static.
            return GL_MAP_WRITE_BIT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
    }
}

GLenum VertexBuffer::convert(const Usage::Enum usage)
{
    switch (usage)
    {
        case Usage::Dynamic:
            return GL_DYNAMIC_DRAW;

        case Usage::Static:
            return GL_STATIC_DRAW;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_DYNAMIC_DRAW;
    }
}

GLuint VertexBuffer::activeId()
{
    GLuint id = 0;

    // fetch the id of the active buffer
    glGetIntegerv(
        GL_ARRAY_BUFFER_BINDING,
        reinterpret_cast<GLint*>(&id)
    );

    return id;
}
