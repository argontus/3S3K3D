/**
 * @file graphics/renderer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERER_H_INCLUDED
#define GRAPHICS_RENDERER_H_INCLUDED

#include <graphics/indexbuffer.h>
#include <graphics/program.h>
#include <graphics/texture.h>
#include <graphics/vertexbuffer.h>
#include <graphics/vertexformat.h>

class Renderer
{
public:
    struct PrimitiveType
    {
        enum Enum
        {
            Points,
            Lines,
            Triangles

            // TODO: add more if needed
        };
    };

    ~Renderer();

    Renderer();

    // TODO: camera management, ...

    // there can be no active vertex buffer when this function is called
    // there can be no active textures when this function is called
    void setProgram(Program* program);
    Program* program() const;

    // there can be no active vertex buffer when this function is called
    void setVertexFormat(VertexFormat* vertexFormat);
    VertexFormat* vertexFormat() const;

    // there must be an active program when this function is called
    // there must be an active vertex format when this function is called
    void setVertexBuffer(VertexBuffer* vertexBuffer);
    VertexBuffer* vertexBuffer() const;

    void setIndexBuffer(IndexBuffer* indexBuffer);
    IndexBuffer* indexBuffer() const;

    // there must be an active program when this function is called
    // index must be between [0, numTextureUnits())
    void setTexture(int index, Texture* texture);
    Texture* texture(int index) const;
    int numTextureUnits() const;
    int numActiveTextureUnits() const;

    // there must be an active program when this function is called
    // there must be an active vertex format when this function is called
    // there must be an active vertex buffer when this function is called
    void renderPrimitives(PrimitiveType::Enum type);

    // there must be an active program when this function is called
    // there must be an active vertex format when this function is called
    // there must be an active vertex buffer when this function is called
    // the specified range [offset, offset + count) must be valid
    void renderPrimitives(PrimitiveType::Enum type, int offset, int count);

private:
    enum { MaxTextureUnits = 32 };

    static GLenum indexBufferType(IndexBuffer::Format::Enum format);
    static GLenum primitiveType(PrimitiveType::Enum type);
    static GLenum vertexAttributeType(VertexAttribute::Type::Enum type);

    void bindVertexBuffer(VertexBuffer* vertexBuffer);
    void unbindVertexBuffer();

    IndexBuffer* indexBuffer_;              ///< Active index buffer.
    Program* program_;                      ///< Active program.
    VertexBuffer* vertexBuffer_;            ///< Active vertex buffer.
    VertexFormat* vertexFormat_;            ///< Active vertex format.
    GLenum indexBufferType_;                ///< Index buffer element type.
    Texture* textures_[MaxTextureUnits];    ///< Active textures.

    // prevent copying
    Renderer(const Renderer&);
    Renderer& operator =(const Renderer&);
};

#endif // #ifndef GRAPHICS_RENDERER_H_INCLUDED
