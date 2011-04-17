/**
 * @file graphics/vertexbuffer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXBUFFER_H_INCLUDED
#define GRAPHICS_VERTEXBUFFER_H_INCLUDED

// TODO: get rid of this include?
#include <graphics/opengl.h>

// TODO: this class has a lot in common with IndexBuffer, move common
// implementation to a base class?
/**
 * Represents an OpenGL vertex buffer.
 */
class VertexBuffer
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
    ~VertexBuffer();

    /**
     * Constructor.
     *
     * @param elementSize Size of a single element in bytes.
     * @param numElements Number of elements to allocate.
     * @param data Data to copy to the buffer. If this is a null pointer, the
     * buffer contents are not initialized. If this is not a null pointer, the
     * pointed data must contain <code>numElements</code> vertices and their
     * size must match <code>elementSize</code>.
     * @param usage Usage hint.
     */
    VertexBuffer(
        int elementSize,
        int numElements,
        const void* data,
        Usage::Enum usage);

    /**
     * Updates the buffer contents.
     *
     * @param elementSize Size of a single element in bytes.
     * @param numElements Number of elements to allocate.
     * @param data Data to copy to the buffer. If this is a null pointer, the
     * buffer contents are not initialized. If this is not a null pointer, the
     * pointed data must contain <code>numElements</code> vertices and their
     * size must match <code>elementSize</code>.
     */
    void update(int elementSize, int numElements, const void* data);

    // TODO: partial buffer update with glBufferSubData

    /**
     * Locks this buffer. Remember to call <code>unlock()</code> once done
     * accessing the buffer contents. Only one vertex buffer can be locked at a
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
     * vertex buffer can be locked at a time, nested locks are not allowed.
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
     * Gets the usage hint.
     *
     * @return Usage hint.
     */
    Usage::Enum usage() const;

private:
    int elementSize_;   ///< Element size in bytes.
    int numElements_;   ///< Number of elements.
    GLuint id_;         ///< Buffer id.
    GLuint previousId_; ///< Used in buffer locking implementation.
    Usage::Enum usage_; ///< Usage hint.

    // prevent copying
    VertexBuffer(const VertexBuffer&);
    VertexBuffer& operator =(const VertexBuffer&);
};

#endif // #ifndef GRAPHICS_VERTEXBUFFER_H_INCLUDED
