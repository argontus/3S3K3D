/**
 * @file graphics/indexbuffer.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/indexbuffer.h>

#include <graphics/runtimeassert.h>

namespace {

// TODO: move these to a separate compilation unit?

int bufferElementSize(const IndexBuffer::Format::Enum format)
{
    switch (format)
    {
        case IndexBuffer::Format::UnsignedByte:
            return 1;

        case IndexBuffer::Format::UnsignedShort:
            return 2;

        case IndexBuffer::Format::UnsignedInt:
            return 4;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLbitfield bufferAccessMask(const IndexBuffer::Access::Enum access)
{
    switch (access)
    {
        case IndexBuffer::Access::ReadOnly:
            return GL_MAP_READ_BIT;

        case IndexBuffer::Access::ReadWrite:
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;

        case IndexBuffer::Access::WriteOnly:
            // TODO: This could be more efficient if used with
            // GL_MAP_INVALIDATE_RANGE_BIT but it doesn't seem to work with
            // index arrays, GLuint and Usage::Static.
            return GL_MAP_WRITE_BIT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
    }
}

GLenum bufferUsage(const IndexBuffer::Usage::Enum usage)
{
    switch (usage)
    {
        case IndexBuffer::Usage::Dynamic:
            return GL_DYNAMIC_DRAW;

        case IndexBuffer::Usage::Static:
            return GL_STATIC_DRAW;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return GL_DYNAMIC_DRAW;
    }
}

/**
 * Gets the Id of the active index buffer.
 *
 * @return Id of the active index buffer.
 */
GLuint activeIndexBufferId()
{
    GLuint id = 0;

    // fetch the id of the active buffer
    glGetIntegerv(
        GL_ELEMENT_ARRAY_BUFFER_BINDING,
        reinterpret_cast<GLint*>(&id)
    );

    return id;
}

} // namespace

IndexBuffer::~IndexBuffer()
{
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    if (id_ == activeIndexBufferId())
    {
        // this is the active buffer, unbind it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == 0);
    }

    glDeleteBuffers(1, &id_);
}

IndexBuffer::IndexBuffer(
    const Format::Enum format,
    const int numElements,
    const void* const data,
    const Usage::Enum usage)
:   elementSize_(0),
    numElements_(0),
    id_(0),
    previousId_(0),
    format_(Format::UnsignedByte),
    usage_(usage)
{
    GRAPHICS_RUNTIME_ASSERT(numElements > 0);

    glGenBuffers(1, &id_);
    GRAPHICS_RUNTIME_ASSERT(id_ != 0);

    // this works if id_ and usage_ have been set
    update(format, numElements, data);

    // calling update should have updated these
    GRAPHICS_RUNTIME_ASSERT(elementSize_ == bufferElementSize(format));
    GRAPHICS_RUNTIME_ASSERT(numElements_ == numElements);
    GRAPHICS_RUNTIME_ASSERT(format_ == format);
}

void IndexBuffer::update(
    const Format::Enum format,
    const int numElements,
    const void* const data)
{
    GRAPHICS_RUNTIME_ASSERT(numElements > 0);

    const int elementSize = bufferElementSize(format);

    // TODO: use an IndexBufferBinding class for managing the buffer binding?

    // fetch the id of the currently bound buffer
    const GLuint previousId = activeIndexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId)
    {
        // the given buffer is not bound, bind it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == id_);
    }

    // if data is a null pointer, no data is copied to the buffer
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        numElements * elementSize,
        data,
        bufferUsage(usage_)
    );

    if (id_ != previousId)
    {
        // restore previous buffer binding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, previousId);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == previousId);
    }

    elementSize_ = elementSize;
    numElements_ = numElements;
    format_ = format;
}

void* IndexBuffer::lock(const Access::Enum access)
{
    GRAPHICS_RUNTIME_ASSERT(isLocked() == false);

    // lock the entire buffer
    return lock(0, numElements(), access);
}

void* IndexBuffer::lock(
    const int offset,
    const int count,
    const Access::Enum access)
{
    GRAPHICS_RUNTIME_ASSERT(isLocked() == false);

    // store id of the currently bound buffer so that it can be restored when
    // unlocking this buffer
    previousId_ = activeIndexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId_)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == id_);
    }

    // returns a null pointer on error
    void* const data = glMapBufferRange(
        GL_ELEMENT_ARRAY_BUFFER,
        offset,
        count * elementSize_,
        bufferAccessMask(access)
    );

    GRAPHICS_RUNTIME_ASSERT(data != 0);
    return data;
}

void IndexBuffer::unlock()
{
    GRAPHICS_RUNTIME_ASSERT(isLocked());
    GRAPHICS_RUNTIME_ASSERT(id_ == activeIndexBufferId());

    // returns GL_FALSE on error, GL_TRUE on success
    const GLboolean result = glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    GRAPHICS_RUNTIME_ASSERT(result == GL_TRUE);

    if (id_ != previousId_)
    {
        // restore previous binding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, previousId_);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == previousId_);
    }
}

bool IndexBuffer::isLocked() const
{
    // TODO: use an IndexBufferBinding class for managing the buffer binding?

    // fetch the id of the currently bound buffer
    const GLuint previousId = activeIndexBufferId();

    // make sure this buffer is bound
    if (id_ != previousId)
    {
        // the given buffer is not bound, bind it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == id_);
    }

    GLint isMapped = GL_FALSE;

    glGetBufferParameteriv(
        GL_ELEMENT_ARRAY_BUFFER,
        GL_BUFFER_MAPPED,
        &isMapped
    );

    if (id_ != previousId)
    {
        // restore previous buffer binding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, previousId);
        GRAPHICS_RUNTIME_ASSERT(activeIndexBufferId() == previousId);
    }

    return isMapped;
}

int IndexBuffer::elementSize() const
{
    return elementSize_;
}

int IndexBuffer::numElements() const
{
    return numElements_;
}

GLuint IndexBuffer::id() const
{
    return id_;
}

IndexBuffer::Format::Enum IndexBuffer::format() const
{
    return format_;
}

IndexBuffer::Usage::Enum IndexBuffer::usage() const
{
    return usage_;
}
