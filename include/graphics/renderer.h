/**
 * @file graphics/renderer.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERER_H_INCLUDED
#define GRAPHICS_RENDERER_H_INCLUDED

// no forward declarations, just include everything

#include <geometry/matrix3x3.h>
#include <geometry/matrix4x4.h>

#include <graphics/blendstate.h>
#include <graphics/cullstate.h>
#include <graphics/depthstate.h>
#include <graphics/indexbuffer.h>
#include <graphics/program.h>
#include <graphics/rectanglei.h>
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

            // TODO: add more if needed, remember to update Renderer
            // implementation
        };
    };

    /**
     * Gets the GLSL uniform variable name for model-view matrix that the
     * implementation assumes.
     *
     * @return GLSL uniform variable name for model-view matrix that the
     * implementation assumes.
     */
    static const char* modelViewMatrixName();

    /**
     * Gets the GLSL uniform variable name for projection matrix that the
     * implementation assumes.
     *
     * @return GLSL uniform variable name for projection matrix that the
     * implementation assumes.
     */
    static const char* projectionMatrixName();

    /**
     * Gets the GLSL uniform variable name for normal matrix that the
     * implementation assumes.
     *
     * @return GLSL uniform variable name for normal matrix that the
     * implementation assumes.
     */
    static const char* normalMatrixName();

    /**
     * Destructor.
     */
    ~Renderer();

    /**
     * Constructor.
     *
     * @param width Default framebuffer width in pixels, must be > 0.
     * @param height Default framebuffer height in pixels, must be > 0.
     */
    Renderer(int width, int height);

    // TODO: camera management, shader uniform management, fill mode
    // management, framebuffer management, viewport management, ...

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

    void setModelViewMatrix(const Matrix4x4& modelViewMatrix);
    const Matrix4x4 modelViewMatrix() const;

    void setProjectionMatrix(const Matrix4x4& projectionMatrix);
    const Matrix4x4 projectionMatrix() const;

    void setNormalMatrix(const Matrix3x3& normalMatrix);
    const Matrix3x3 normalMatrix() const;

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

    // these are probably not needed
    // TODO: void setScissorState(ScissorState* scissorState); ?
    // TODO: ScissorState* scissorState() const; ?

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
     * Specify whether red, green, blue and alpha can or cannot be written into
     * the framebuffer.
     *
     * @param r Enable red component writes?
     * @param g Enable green component writes?
     * @param b Enable blue component writes?
     * @param a Enable alpha component writes?
     */
    void setColorMask(bool r, bool g, bool b, bool a);
    // TODO: void getColorMask(bool* r, bool* g, bool* b, bool* a); ?

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

    // TODO: the active scissor state and buffer writemasks affect this
    // operation, document it
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
    void clearBuffers(bool color, bool depth, bool stencil);

    // TODO: the active scissor state and buffer writemasks affect this
    // operation, document it
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
    void clearBuffers(
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

    // TODO: renderPrimitives function that takes a pointer to vertex data in
    // client memory?

private:
    enum { MaxTextureUnits = 32 };

    // There must be an active program when this functions is called. If a
    // uniform variable with the specified name does not exist, this function
    // does nothing. 'name' cannot be a null pointer.
    void setUniform(const char* name, const Matrix3x3& value);
    void setUniform(const char* name, const Matrix4x4& value);

    void bindVertexBuffer(VertexBuffer* vertexBuffer);
    void unbindVertexBuffer();

    int defaultWidth_;  ///< Width of the default framebuffer in pixels.
    int defaultHeight_; ///< Height of the default framebuffer in pixels.

    Matrix4x4 modelViewMatrix_;     ///< Model-view matrix.
    Matrix4x4 projectionMatrix_;    ///< Projection matrix.
    Matrix3x3 normalMatrix_;        ///< Normal matrix.

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
