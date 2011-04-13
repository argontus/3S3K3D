/**
 * @file graphics/renderer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERER_H_INCLUDED
#define GRAPHICS_RENDERER_H_INCLUDED

// no forward declarations, just include everything
#include <graphics/blendstate.h>
#include <graphics/cullstate.h>
#include <graphics/depthstate.h>
#include <graphics/indexbuffer.h>
#include <graphics/program.h>
#include <graphics/stencilstate.h>
#include <graphics/texture.h>
#include <graphics/vertexbuffer.h>
#include <graphics/vertexformat.h>

/**
 * Helper class for managing OpenGL render state.
 */
class Renderer
{
public:
    /**
     * Enumeration wrapper for possible primitive types.
     */
    struct PrimitiveType
    {
        /**
         * Possible primitive types.
         */
        enum Enum
        {
            Points,
            Lines,
            Triangles

            // TODO: add more if needed
        };
    };

    /**
     * Destructor.
     */
    ~Renderer();

    /**
     * Default constructor.
     */
    Renderer();

    // TODO: camera management, stencil state management, ...

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

    void setBlendState(BlendState* blendState);
    BlendState* blendState() const;

    void setCullState(CullState* cullState);
    CullState* cullState() const;

    void setDepthState(DepthState* depthState);
    DepthState* depthState() const;

    void setStencilState(StencilState* stencilState);
    StencilState* stencilState() const;

    // there must be an active program when this function is called
    // index must be between [0, numTextureUnits())
    void setTexture(int index, Texture* texture);
    // index must be between [0, numTextureUnits())
    Texture* texture(int index) const;

    /**
     * Gets the number of texture units.
     *
     * @return Number of texture units.
     */
    int numTextureUnits() const;

    /**
     * Gets the number of active texture units.
     *
     * @return Number of active texture units.
     */
    int numActiveTextureUnits() const;

    /**
     * Specify whether red, green, blue and alpha can or cannot be wrtitten
     * into the frame buffer.
     *
     * @param r Enable red component writes?
     * @param g Enable green component writes?
     * @param b Enable blue component writes?
     * @param a Enable alpha component writes?
     */
    void setColorMask(bool r, bool g, bool b, bool a);

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

    static GLenum blendEquation(BlendState::Equation::Enum equation);
    static GLenum blendFunc(BlendState::SrcFactor::Enum srcFactor);
    static GLenum blendFunc(BlendState::DstFactor::Enum dstFactor);
    static GLenum cullFace(CullState::CullFace::Enum face);
    static GLenum depthFunc(DepthState::CompareFunc::Enum compareFunc);
    static GLenum indexBufferType(IndexBuffer::Format::Enum format);
    static GLenum primitiveType(PrimitiveType::Enum type);
    static GLenum stencilAction(StencilState::Action::Enum action);
    static GLenum stencilFunc(StencilState::CompareFunc::Enum compareFunc);
    static GLenum vertexAttributeType(VertexAttribute::Type::Enum type);

    void bindVertexBuffer(VertexBuffer* vertexBuffer);
    void unbindVertexBuffer();

    // TODO: make these pointers to const?
    Program* program_;                      ///< Active program.
    VertexFormat* vertexFormat_;            ///< Active vertex format.
    VertexBuffer* vertexBuffer_;            ///< Active vertex buffer.
    IndexBuffer* indexBuffer_;              ///< Active index buffer.
    GLenum indexBufferType_;                ///< Index buffer element type.
    BlendState* blendState_;                ///< Active blend state.
    CullState* cullState_;                  ///< Active cull state.
    DepthState* depthState_;                ///< Active depth state.
    StencilState* stencilState_;            ///< Active stencil state.
    Texture* textures_[MaxTextureUnits];    ///< Active textures.

    // prevent copying
    Renderer(const Renderer&);
    Renderer& operator =(const Renderer&);
};

#endif // #ifndef GRAPHICS_RENDERER_H_INCLUDED
