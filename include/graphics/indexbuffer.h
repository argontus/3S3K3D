/**
 * @file graphics/indexbuffer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_INDEXBUFFER_H_INCLUDED
#define GRAPHICS_INDEXBUFFER_H_INCLUDED

#include <graphics/opengl.h>

/**
 * Represents an OpenGL index buffer.
 */
class IndexBuffer
{
public:
    struct Access
    {
        enum Enum
        {
            ReadOnly,
            WriteOnly,
            ReadWrite
        };
    };

    struct Format
    {
        enum Enum
        {
            UnsignedByte,
            UnsignedShort,
            UnsignedInt
        };
    };

    struct Usage
    {
        enum Enum
        {
            Dynamic,
            Static
        };
    };

    /**
     * Destructor.
     */
    ~IndexBuffer();

    // TODO: comments
    IndexBuffer(
        int numElements,
        const void* data,
        Format::Enum format,
        Usage::Enum usage);

    /**
     * Locks the whole index buffer. Remember to call <code>unlock()</code>
     * once done accessing the buffer contents. Only one index buffer can be
     * locked at a time, nested locks are not allowed.
     *
     * @param access Access policy.
     *
     * @return Pointer to the buffer data. This remains valid until this buffer
     * is unlocked.
     *
     * @see unlock()
     */
    void* lock(Access::Enum access);

    /**
     * Locks a range of elements from the index buffer. Remember to call
     * <code>unlock()</code> once done accessing the buffer contents. Only one
     * index buffer can be locked at a time, nested locks are not allowed.
     *
     * @param offset Offset from the beginning of the index buffer as elements.
     * @param count Number of elements to lock.
     * @param access Access policy.
     *
     * @return Pointer to the buffer data. This remains valid until this buffer
     * is unlocked.
     *
     * @see unlock()
     */
    void* lock(int offset, int count, Access::Enum access);

    /**
     * Unlocks a previously locked index buffer.
     */
    void unlock();

    // TODO: bool isLocked() const;

    /**
     * Gets the number of elements.
     *
     * @return Number of elements.
     */
    int numElements() const;

    /**
     * Gets the size of a single index in bytes.
     *
     * @return Size of a single index in bytes.
     */
    int elementSize() const;

    /**
     * Gets the index buffer Id.
     *
     * @return Index buffer Id.
     */
    GLuint id() const;

    /**
     * Gets the index buffer format.
     *
     * @return Index buffer format.
     */
    Format::Enum format() const;

    /**
     * Gets the index buffer usage hint.
     *
     * @return Index buffer usage hint.
     */
    Usage::Enum usage() const;

private:
    static int elementSize(Format::Enum format);
    static GLbitfield convert(Access::Enum access);
    static GLenum convert(Usage::Enum usage);
    static GLuint activeId();

    int numElements_;       ///< Number of elements.
    int elementSize_;       ///< Element size in bytes.
    GLuint id_;             ///< Buffer id.
    GLuint previousId_;     ///< Used in buffer locking implementation.
    Format::Enum format_;   ///< Index format.
    Usage::Enum usage_;     ///< Usage hint.

    // prevent copying
    IndexBuffer(const IndexBuffer&);
    IndexBuffer& operator =(const IndexBuffer&);
};

#endif // #ifndef GRAPHICS_INDEXBUFFER_H_INCLUDED
