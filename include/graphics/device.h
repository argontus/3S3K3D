/**
 * @file graphics/device.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DEVICE_H_INCLUDED
#define GRAPHICS_DEVICE_H_INCLUDED

#include <vector>

// no forward declarations, just include everything

#include <graphics/blendstate.h>
#include <graphics/depthstate.h>
#include <graphics/indexbuffer.h>
#include <graphics/program.h>
#include <graphics/rasterizerstate.h>
#include <graphics/rectanglei.h>
#include <graphics/stencilstate.h>
#include <graphics/texture.h>
#include <graphics/vertexbuffer.h>
#include <graphics/vertexformat.h>

/**
 * Helper class for managing OpenGL render state.
 */
class Device
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

            // TODO: add more if needed, remember to update the implementation
        };
    };

    /**
     * Destructor.
     */
    ~Device();

    /**
     * Constructor.
     *
     * @param width Default framebuffer width in pixels, must be > 0.
     * @param height Default framebuffer height in pixels, must be > 0.
     */
    Device(int width, int height);

    // TODO: framebuffer management, viewport management

    // this must be called if the default framebuffer is resized
    // width and height must be > 0
    // TODO: resize(int width, int height); ?

    /**
     * Gets the width of the active framebuffer in pixels.
     *
     * @return Width of the active framebuffer in pixels.
     */
    int width() const;

    /**
     * Gets the height of the active framebuffer in pixels.
     *
     * @return Height of the active framebuffer in pixels.
     */
    int height() const;

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

    void setBlendState(const BlendState* blendState);
    const BlendState* blendState() const;

    void setDepthState(const DepthState* depthState);
    const DepthState* depthState() const;

    void setRasterizerState(const RasterizerState* rasterizerState);
    const RasterizerState* rasterizerState() const;

    // these are probably not needed
    // TODO: void setScissorState(const ScissorState* scissorState); ?
    // TODO: const ScissorState* scissorState() const; ?

    void setStencilState(const StencilState* stencilState);
    const StencilState* stencilState() const;

    // TODO: texture unit specific sampler state management

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
     * Sets the color buffer clear value.
     *
     * @param clearColor Color buffer clear value, the components are silently
     * clamped between [0, 1].
     */
    void setClearColor(const Color4& clearColor);
    // TODO: const Color4 clearColor() const; ?

    /**
     * Sets the depth buffer clear value.
     *
     * @param clearDepth Depth buffer clear value, this is silently clamped
     * between [0, 1].
     */
    void setClearDepth(float clearDepth);
    // TODO: float clearDepth() const; ?

    /**
     * Sets the stencil buffer clear value.
     *
     * @param clearStencil Stencil buffer clear value, this is silently masked
     * with 2^m-1, where m is the number of bits in the stencil buffer.
     */
    void setClearStencil(uint32_t clearStencil);
    // TODO: uint32_t clearStencil() const; ?

    // TODO: this should ignore color, depth and stencil buffer writemasks
    // TODO: use a bitmask instead of 3 boolean values?
    /**
     * Clears the specified buffers to their clear values. If a buffer is not
     * present, then a clear operation directed at that buffer has no effect.
     *
     * @param color Clear color buffer?
     * @param depth Clear depth buffer?
     * @param stencil Clear stencil buffer?
     *
     * @see setClearColor(const Color4&)
     * @see setClearDepth(float)
     * @see setClearStencil(uint32_t)
     */
    void clear(bool color, bool depth, bool stencil);

    // TODO: this should ignore color, depth and stencil buffer writemasks
    // TODO: use a bitmask instead of 3 boolean values?
    /**
     * Clears a specified area of the specified buffers to their clear values.
     * <code>area</code> is given in right handed coordinate system, i.e.,
     * <code>area.x</code> and <code>area.y</code> specify the bottom left
     * pixel of the area and <code>area.x + area.width - 1</code> and
     * <code>area.y + area.height - 1</code> specify the top right pixel of the
     * area. If a buffer is not present, then a clear operation directed at
     * that buffer has no effect.
     *
     * @param color Clear color buffer?
     * @param depth Clear depth buffer?
     * @param stencil Clear stencil buffer?
     * @param area Describes the area to clear, must be within the active
     * framebuffer dimensions.
     *
     * @see setClearColor(const Color4&)
     * @see setClearDepth(float)
     * @see setClearStencil(uint32_t)
     */
    void clear(
        bool color,
        bool depth,
        bool stencil,
        const RectangleI& area);

    // there must be an active program when this function is called
    // there must be an active vertex format when this function is called
    // there must be an active vertex buffer when this function is called
    void drawPrimitives(PrimitiveType::Enum type);

    // there must be an active program when this function is called
    // there must be an active vertex format when this function is called
    // there must be an active vertex buffer when this function is called
    // the specified range [offset, offset + count) must be valid
    void drawPrimitives(PrimitiveType::Enum type, int offset, int count);

    // TODO: separate functions for indexed primitives

    // TODO: drawUserPrimitives function that takes a pointer to vertex data in
    // client memory?

private:
    void bindVertexBuffer(VertexBuffer* vertexBuffer);
    void unbindVertexBuffer();

    int defaultWidth_;  ///< Width of the default framebuffer in pixels.
    int defaultHeight_; ///< Height of the default framebuffer in pixels.

    Program* program_;                          ///< Active program.
    VertexFormat* vertexFormat_;                ///< Active vertex format.
    VertexBuffer* vertexBuffer_;                ///< Active vertex buffer.
    IndexBuffer* indexBuffer_;                  ///< Active index buffer.
    GLenum indexBufferType_;                    ///< Index buffer element type.
    const BlendState* blendState_;              ///< Active blend state.
    const DepthState* depthState_;              ///< Active depth state.
    const RasterizerState* rasterizerState_;    ///< Active rasterizer state.
    const StencilState* stencilState_;          ///< Active stencil state.
    std::vector<Texture*> textures_;            ///< Active textures.

    // prevent copying
    Device(const Device&);
    Device& operator =(const Device&);
};

#endif // #ifndef GRAPHICS_DEVICE_H_INCLUDED
