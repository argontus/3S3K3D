/**
 * @file graphics/vertexbuffer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXBUFFER_H_INCLUDED
#define GRAPHICS_VERTEXBUFFER_H_INCLUDED

#include <graphics/opengl.h>

// TODO: this class has a lot in common with IndexBuffer, move common
// implementation to a base class?
// TODO: comments
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

    ~VertexBuffer();

    VertexBuffer(
        int numElements,
        int elementSize,
        const void* data,
        Usage::Enum usage);

    void* lock(Access::Enum access);
    void* lock(int offset, int count, Access::Enum access);

    void unlock();

    // TODO: bool isLocked() const;

    int numElements() const;
    int elementSize() const;

    GLuint id() const;

    Usage::Enum usage() const;

private:
    static GLbitfield convert(Access::Enum access);
    static GLenum convert(Usage::Enum usage);
    static GLuint activeId();

    int numElements_;   ///< Number of elements.
    int elementSize_;   ///< Element size in bytes.
    GLuint id_;         ///< Buffer id.
    GLuint previousId_; ///< Used in buffer locking implementation.
    Usage::Enum usage_; ///< Usage hint.

    // prevent copying
    VertexBuffer(const VertexBuffer&);
    VertexBuffer& operator =(const VertexBuffer&);
};

#endif // #ifndef GRAPHICS_VERTEXBUFFER_H_INCLUDED
