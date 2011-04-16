/**
 * @file graphics/indexbuffer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_INDEXBUFFER_H_INCLUDED
#define GRAPHICS_INDEXBUFFER_H_INCLUDED

// TODO: get rid of this include?
#include <graphics/opengl.h>

// TODO: this class has a lot in common with VertexBuffer, move common
// implementation to a base class?
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

    /**
     * Constructor.
     *
     * @param format Index format.
     * @param numElements Number of elements to allocate.
     * @param data Data to copy to the buffer. If this is a null pointer, the
     * buffer contents are not initialized. If this is not a null pointer, the
     * pointed data must contain <code>numElements</code> indices and their
     * type must match <code>format</code>.
     * @param usage Usage hint.
     */
    IndexBuffer(
        Format::Enum format,
        int numElements,
        const void* data,
        Usage::Enum usage);

    /**
     * Updates the buffer contents.
     *
     * @param format Index format.
     * @param numElements Number of elements to allocate.
     * @param data Data to copy to the buffer. If this is a null pointer, the
     * buffer contents are not initialized. If this is not a null pointer, the
     * pointed data must contain <code>numElements</code> indices and their
     * type must match <code>format</code>.
     */
    void update(Format::Enum format, int numElements, const void* data);

    /**
     * Locks this buffer. Remember to call <code>unlock()</code> once done
     * accessing the buffer contents. Only one index buffer can be locked at a
     * time, nested locks are not allowed.
     *
     * @param access Access policy.
     *
     * @return Pointer to the buffer data. This remains valid until this buffer
     * is unlocked.
     *
     * @see unlock()
     * @see isLocked() const
     */
    void* lock(Access::Enum access);

    /**
     * Locks a range of elements from this buffer. Remember to call
     * <code>unlock()</code> once done accessing the buffer contents. Only one
     * index buffer can be locked at a time, nested locks are not allowed.
     *
     * @param offset Offset from the beginning of this buffer as elements.
     * @param count Number of elements to lock.
     * @param access Access policy.
     *
     * @return Pointer to the buffer data. This remains valid until this buffer
     * is unlocked.
     *
     * @see unlock()
     * @see isLocked() const
     */
    void* lock(int offset, int count, Access::Enum access);

    /**
     * Unlocks this buffer. This buffer must be locked when this function is
     * called.
     *
     * @see lock(Access::Enum)
     * @see isLocked() const
     */
    void unlock();

    /**
     * Gets a boolean value indicating whether or not this buffer is locked.
     *
     * @return <code>true</code> if this buffer is locked, <code>false</code>
     * otherwise.
     */
    bool isLocked() const;

    /**
     * Gets the size of a single element in bytes.
     *
     * @return Size of a single element in bytes.
     */
    int elementSize() const;

    /**
     * Gets the number of elements.
     *
     * @return Number of elements.
     */
    int numElements() const;

    /**
     * Gets the buffer Id.
     *
     * @return Buffer Id.
     */
    GLuint id() const;

    /**
     * Gets the index format.
     *
     * @return Index format.
     */
    Format::Enum format() const;

    /**
     * Gets the usage hint.
     *
     * @return Usage hint.
     */
    Usage::Enum usage() const;

private:
    int elementSize_;       ///< Element size in bytes.
    int numElements_;       ///< Number of elements.
    GLuint id_;             ///< Buffer id.
    GLuint previousId_;     ///< Used in buffer locking implementation.
    Format::Enum format_;   ///< Index format.
    Usage::Enum usage_;     ///< Usage hint.

    // prevent copying
    IndexBuffer(const IndexBuffer&);
    IndexBuffer& operator =(const IndexBuffer&);
};

#endif // #ifndef GRAPHICS_INDEXBUFFER_H_INCLUDED
