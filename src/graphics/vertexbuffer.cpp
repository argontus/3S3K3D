/**
 * @file graphics/vertexbuffer.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/vertexbuffer.h>

#include <graphics/runtimeassert.h>

namespace {

// TODO: move these to a separate compilation unit?

GLbitfield bufferAccessMask(const VertexBuffer::Access::Enum access)
{
    switch (access)
    {
        case VertexBuffer::Access::ReadOnly:
            return GL_MAP_READ_BIT;

        case VertexBuffer::Access::ReadWrite:
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;

        case VertexBuffer::Access::WriteOnly:
            // TODO: This could be more efficient if used with
            // GL_MAP_INVALIDATE_RANGE_BIT but it doesn't seem to work with
            // index arrays, GLuint and Usage::Static.
            return GL_MAP_WRITE_BIT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
    }
}

GLenum bufferUsage(const VertexBuffer::Usage::Enum usage)
{
    switch (usage)
    {
        case VertexBuffer::Usage::Dynamic:
            return GL_DYNAMIC_DRAW;

        case VertexBuffer::Usage::Static:
            return GL_STATIC_DRAW;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_DYNAMIC_DRAW;
    }
}

GLuint activeVertexBufferId()
{
    GLuint id = 0;

    // fetch the id of the active buffer
    glGetIntegerv(
        GL_ARRAY_BUFFER_BINDING,
        reinterpret_cast<GLint*>(&id)
    );

    return id;
}

} // namespace

VertexBuffer::~VertexBuffer()
{
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    if (id_ == activeVertexBufferId())
    {
        // this is the active buffer, unbind it
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == 0);
    }

    glDeleteBuffers(1, &id_);
}

VertexBuffer::VertexBuffer(
    const int elementSize,
    const int numElements,
    const void* const data,
    const Usage::Enum usage)
:   elementSize_(0),
    numElements_(0),
    id_(0),
    previousId_(0),
    usage_(usage)
{
    GRAPHICS_RUNTIME_ASSERT(elementSize > 0);
    GRAPHICS_RUNTIME_ASSERT(numElements > 0);

    glGenBuffers(1, &id_);
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    // this works if id_ and usage_ have been set
    update(elementSize, numElements, data);

    // calling update should have updated these
    GRAPHICS_RUNTIME_ASSERT(elementSize_ == elementSize);
    GRAPHICS_RUNTIME_ASSERT(numElements_ == numElements);
}

void VertexBuffer::update(
    const int elementSize,
    const int numElements,
    const void* const data)
{
    GRAPHICS_RUNTIME_ASSERT(elementSize > 0);
    GRAPHICS_RUNTIME_ASSERT(numElements > 0);

    // TODO: use a VertexBufferBinding class for managing the buffer binding?

    // fetch the id of the currently bound buffer
    const GLuint previousId = activeVertexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId)
    {
        // the given buffer is not bound, bind it
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == id_);
    }

    // if data is a null pointer, no data is copied to the buffer
    glBufferData(
        GL_ARRAY_BUFFER,
        numElements * elementSize,
        data,
        bufferUsage(usage_)
    );

    if (id_ != previousId)
    {
        // restore previous buffer binding
        glBindBuffer(GL_ARRAY_BUFFER, previousId);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == previousId);
    }

    elementSize_ = elementSize;
    numElements_ = numElements;
}

void* VertexBuffer::lock(const Access::Enum access)
{
    GRAPHICS_RUNTIME_ASSERT(isLocked() == false);

    // lock the entire buffer
    return lock(0, numElements(), access);
}

void* VertexBuffer::lock(
    const int offset,
    const int count,
    const Access::Enum access)
{
    GRAPHICS_RUNTIME_ASSERT(isLocked() == false);

    // store id of the currently bound buffer so that it can be restored when
    // unlocking this buffer
    previousId_ = activeVertexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId_)
    {
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == id_);
    }

    // returns a null pointer on error
    void* const data = glMapBufferRange(
        GL_ARRAY_BUFFER,
        offset,
        count * elementSize_,
        bufferAccessMask(access)
    );

    GRAPHICS_RUNTIME_ASSERT(data != 0);
    return data;
}

void VertexBuffer::unlock()
{
    GRAPHICS_RUNTIME_ASSERT(isLocked());
    GRAPHICS_RUNTIME_ASSERT(id_ == activeVertexBufferId());

    // returns GL_FALSE on error, GL_TRUE on success
    const GLboolean result = glUnmapBuffer(GL_ARRAY_BUFFER);
    GRAPHICS_RUNTIME_ASSERT(result == GL_TRUE);

    if (id_ != previousId_)
    {
        // restore previous binding
        glBindBuffer(GL_ARRAY_BUFFER, previousId_);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == previousId_);
    }
}

bool VertexBuffer::isLocked() const
{
    // TODO: use a VertexBufferBinding class for managing the buffer binding?

    // fetch the id of the currently bound buffer
    const GLuint previousId = activeVertexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId)
    {
        // the given buffer is not bound, bind it
        glBindBuffer(GL_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == id_);
    }

    GLint isMapped = GL_FALSE;

    glGetBufferParameteriv(
        GL_ARRAY_BUFFER,
        GL_BUFFER_MAPPED,
        &isMapped
    );

    if (id_ != previousId)
    {
        // restore previous buffer binding
        glBindBuffer(GL_ARRAY_BUFFER, previousId);
        GRAPHICS_RUNTIME_ASSERT(activeVertexBufferId() == previousId);
    }

    return isMapped;
}

int VertexBuffer::elementSize() const
{
    return elementSize_;
}

int VertexBuffer::numElements() const
{
    return numElements_;
}

GLuint VertexBuffer::id() const
{
    return id_;
}

VertexBuffer::Usage::Enum VertexBuffer::usage() const
{
    return usage_;
}
