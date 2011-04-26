/**
 * @file graphics/device.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/device.h>

#include <cstring>

#include <sstream>

#include <graphics/runtimeassert.h>

namespace {

// TODO: move these to a separate compilation unit?

/**
 * Constructs the mask parameter for <code>glClear(GLbitfield)</code>
 * indicating the buffers to be cleared.
 *
 * @param color Clear color buffer?
 * @param depth Clear depth buffer?
 * @param stencil Clear stencil buffer?
 *
 * @return Mask parameter for <code>glClear(GLbitfield)</code> indicating
 * the buffers to be cleared.
 */
GLbitfield clearMask(const bool color, const bool depth, const bool stencil)
{
    GLbitfield mask = 0;

    if (color)
    {
        mask |= GL_COLOR_BUFFER_BIT;
    }

    if (depth)
    {
        mask |= GL_DEPTH_BUFFER_BIT;
    }

    if (stencil)
    {
        mask |= GL_STENCIL_BUFFER_BIT;
    }

    return mask;
}

GLenum blendEquation(const BlendState::Equation::Enum equation)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (equation)
    {
        case BlendState::Equation::Add:
            return GL_FUNC_ADD;

        case BlendState::Equation::Subtract:
            return GL_FUNC_SUBTRACT;

        case BlendState::Equation::ReverseSubtract:
            return GL_FUNC_REVERSE_SUBTRACT;

        case BlendState::Equation::Min:
            return GL_MIN;

        case BlendState::Equation::Max:
            return GL_MAX;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum blendFunc(const BlendState::SrcFactor::Enum srcFactor)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (srcFactor)
    {
        case BlendState::SrcFactor::Zero:
            return GL_ZERO;

        case BlendState::SrcFactor::One:
            return GL_ONE;

        case BlendState::SrcFactor::SrcColor:
            return GL_SRC_COLOR;

        case BlendState::SrcFactor::OneMinusSrcColor:
            return GL_ONE_MINUS_SRC_COLOR;

        case BlendState::SrcFactor::DstColor:
            return GL_DST_COLOR;

        case BlendState::SrcFactor::OneMinusDstColor:
            return GL_ONE_MINUS_DST_COLOR;

        case BlendState::SrcFactor::SrcAlpha:
            return GL_SRC_ALPHA;

        case BlendState::SrcFactor::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;

        case BlendState::SrcFactor::DstAlpha:
            return GL_DST_ALPHA;

        case BlendState::SrcFactor::OneMinusDstAlpha:
            return GL_ONE_MINUS_DST_ALPHA;

        case BlendState::SrcFactor::ConstantColor:
            return GL_CONSTANT_COLOR;

        case BlendState::SrcFactor::OneMinusConstantColor:
            return GL_ONE_MINUS_CONSTANT_COLOR;

        case BlendState::SrcFactor::ConstantAlpha:
            return GL_CONSTANT_ALPHA;

        case BlendState::SrcFactor::OneMinusConstantAlpha:
            return GL_ONE_MINUS_CONSTANT_ALPHA;

        case BlendState::SrcFactor::SrcAlphaSaturate:
            return GL_SRC_ALPHA_SATURATE;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum blendFunc(const BlendState::DstFactor::Enum dstFactor)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (dstFactor)
    {
        case BlendState::DstFactor::Zero:
            return GL_ZERO;

        case BlendState::DstFactor::One:
            return GL_ONE;

        case BlendState::DstFactor::SrcColor:
            return GL_SRC_COLOR;

        case BlendState::DstFactor::OneMinusSrcColor:
            return GL_ONE_MINUS_SRC_COLOR;

        case BlendState::DstFactor::DstColor:
            return GL_DST_COLOR;

        case BlendState::DstFactor::OneMinusDstColor:
            return GL_ONE_MINUS_DST_COLOR;

        case BlendState::DstFactor::SrcAlpha:
            return GL_SRC_ALPHA;

        case BlendState::DstFactor::OneMinusSrcAlpha:
            return GL_ONE_MINUS_SRC_ALPHA;

        case BlendState::DstFactor::DstAlpha:
            return GL_DST_ALPHA;

        case BlendState::DstFactor::OneMinusDstAlpha:
            return GL_ONE_MINUS_DST_ALPHA;

        case BlendState::DstFactor::ConstantColor:
            return GL_CONSTANT_COLOR;

        case BlendState::DstFactor::OneMinusConstantColor:
            return GL_ONE_MINUS_CONSTANT_COLOR;

        case BlendState::DstFactor::ConstantAlpha:
            return GL_CONSTANT_ALPHA;

        case BlendState::DstFactor::OneMinusConstantAlpha:
            return GL_ONE_MINUS_CONSTANT_ALPHA;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum depthFunc(const DepthState::CompareFunc::Enum compareFunc)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (compareFunc)
    {
        case DepthState::CompareFunc::Never:
            return GL_NEVER;

        case DepthState::CompareFunc::Less:
            return GL_LESS;

        case DepthState::CompareFunc::LessEqual:
            return GL_LEQUAL;

        case DepthState::CompareFunc::Equal:
            return GL_EQUAL;

        case DepthState::CompareFunc::Greater:
            return GL_GREATER;

        case DepthState::CompareFunc::GreaterEqual:
            return GL_GEQUAL;

        case DepthState::CompareFunc::NotEqual:
            return GL_NOTEQUAL;

        case DepthState::CompareFunc::Always:
            return GL_ALWAYS;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum indexBufferType(const IndexBuffer::Format::Enum format)
{
    // TODO: optimize by using a lookup table?

    switch (format)
    {
        case IndexBuffer::Format::UnsignedByte:
            return GL_UNSIGNED_BYTE;

        case IndexBuffer::Format::UnsignedShort:
            return GL_UNSIGNED_SHORT;

        case IndexBuffer::Format::UnsignedInt:
            return GL_UNSIGNED_INT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum primitiveType(const Device::PrimitiveType::Enum type)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (type)
    {
        case Device::PrimitiveType::Points:
            return GL_POINTS;

        case Device::PrimitiveType::Lines:
            return GL_LINES;

        case Device::PrimitiveType::Triangles:
            return GL_TRIANGLES;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum stencilAction(const StencilState::Action::Enum action)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (action)
    {
        case StencilState::Action::Keep:
            return GL_KEEP;

        case StencilState::Action::Zero:
            return GL_ZERO;

        case StencilState::Action::Replace:
            return GL_REPLACE;

        case StencilState::Action::Increment:
            return GL_INCR;

        case StencilState::Action::IncrementWrap:
            return GL_INCR_WRAP;

        case StencilState::Action::Decrement:
            return GL_DECR;

        case StencilState::Action::DecrementWrap:
            return GL_DECR_WRAP;

        case StencilState::Action::Invert:
            return GL_INVERT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum stencilFunc(const StencilState::CompareFunc::Enum compareFunc)
{
    // TODO: optimize by using a lookup table or by setting the enumeration
    // values to corresponding OpenGL enumeration values?

    switch (compareFunc)
    {
        case StencilState::CompareFunc::Never:
            return GL_NEVER;

        case StencilState::CompareFunc::Less:
            return GL_LESS;

        case StencilState::CompareFunc::LessEqual:
            return GL_LEQUAL;

        case StencilState::CompareFunc::Equal:
            return GL_EQUAL;

        case StencilState::CompareFunc::Greater:
            return GL_GREATER;

        case StencilState::CompareFunc::GreaterEqual:
            return GL_GEQUAL;

        case StencilState::CompareFunc::NotEqual:
            return GL_NOTEQUAL;

        case StencilState::CompareFunc::Always:
            return GL_ALWAYS;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum vertexAttributeType(const VertexAttribute::Type::Enum type)
{
    // TODO: optimize by using a lookup table?

    switch (type)
    {
        case VertexAttribute::Type::Float1:
        case VertexAttribute::Type::Float2:
        case VertexAttribute::Type::Float3:
        case VertexAttribute::Type::Float4:
            return GL_FLOAT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

} // namespace

Device::~Device()
{
    // ...
}

Device::Device(const int width, const int height)
:   defaultWidth_(width),
    defaultHeight_(height),
    program_(0),
    vertexFormat_(0),
    vertexBuffer_(0),
    indexBuffer_(0),
    indexBufferType_(0),
    blendState_(0),
    depthState_(0),
    rasterizerState_(0),
    stencilState_(0),
    textures_(static_cast<size_t>(numTextureUnits()), 0) // fill with null ptrs
{
    GRAPHICS_RUNTIME_ASSERT(width > 0);
    GRAPHICS_RUNTIME_ASSERT(height > 0);

    setBlendState(BlendState::disabled());
    setDepthState(DepthState::disabled());
    setRasterizerState(RasterizerState::cullClockwise());
    setStencilState(StencilState::disabled());
}

int Device::width() const
{
    // TODO: should return the width of the active framebuffer, update this
    // function if framebuffer management is added
    return defaultWidth_;
}

int Device::height() const
{
    // TODO: should return the height of the active framebuffer, update this
    // function if framebuffer management is added
    return defaultHeight_;
}

void Device::setProgram(Program* const program)
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);
    //GRAPHICS_RUNTIME_ASSERT(numActiveTextureUnits() == 0);

    if (program_ == program)
    {
        // nothing to do
        return;
    }

    program_ = program;

    if (program_ == 0)
    {
        // unbind the active program
        glUseProgram(0);
    }
    else
    {
        // bind the given program
        glUseProgram(program_->id());
    }
}

Program* Device::program() const
{
    return program_;
}

void Device::setVertexFormat(VertexFormat* const vertexFormat)
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);
    vertexFormat_ = vertexFormat;
}

VertexFormat* Device::vertexFormat() const
{
    return vertexFormat_;
}

void Device::setVertexBuffer(VertexBuffer* const vertexBuffer)
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);
    GRAPHICS_RUNTIME_ASSERT(vertexFormat_ != 0);

    if (vertexBuffer_ == vertexBuffer)
    {
        // nothing to do
        return;
    }

    if (vertexBuffer_ != 0 && vertexBuffer != 0)
    {
        // we are binding a new buffer and the last one is still bound, unbind
        // the active buffer before binding the new one
        unbindVertexBuffer();
        bindVertexBuffer(vertexBuffer);
    }
    else if (vertexBuffer == 0)
    {
        // unbind the active vertex buffer
        unbindVertexBuffer();
    }
    else
    {
        // bind the given vertex buffer
        bindVertexBuffer(vertexBuffer);
    }
}

VertexBuffer* Device::vertexBuffer() const
{
    return vertexBuffer_;
}

void Device::setIndexBuffer(IndexBuffer* const indexBuffer)
{
    if (indexBuffer_ == indexBuffer)
    {
        // nothing to do
        return;
    }

    if (indexBuffer == 0)
    {
        // unbind the active index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        // bind the given index buffer and update element type
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id());
        indexBufferType_ = indexBufferType(indexBuffer->format());
    }

    indexBuffer_ = indexBuffer;
}

IndexBuffer* Device::indexBuffer() const
{
    return indexBuffer_;
}

void Device::setBlendState(const BlendState* const blendState)
{
    GRAPHICS_RUNTIME_ASSERT(blendState != 0);

    if (blendState_ == blendState)
    {
        // TODO: this assumes that the active blend state has not been
        // modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (blendState->enabled == false)
    {
        // disable blending
        glDisable(GL_BLEND);
    }
    else
    {
        // enable blending
        glEnable(GL_BLEND);

        // set color and alpha blend equations
        glBlendEquationSeparate(
            blendEquation(blendState->colorEquation),
            blendEquation(blendState->alphaEquation)
        );

        // set source and destination color and alpha factors
        glBlendFuncSeparate(
            blendFunc(blendState->srcColorFactor),
            blendFunc(blendState->dstColorFactor),
            blendFunc(blendState->srcAlphaFactor),
            blendFunc(blendState->dstAlphaFactor)
        );

        // set blend color
        glBlendColor(
            blendState->blendColor.r,
            blendState->blendColor.g,
            blendState->blendColor.b,
            blendState->blendColor.a
        );
    }

    blendState_ = blendState;
}

const BlendState* Device::blendState() const
{
    return blendState_;
}

void Device::setDepthState(const DepthState* const depthState)
{
    GRAPHICS_RUNTIME_ASSERT(depthState != 0);

    if (depthState_ == depthState)
    {
        // TODO: this assumes that the active depth buffer test state has not
        // been modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (depthState->enabled == false)
    {
        // disable depth buffer test
        glDisable(GL_DEPTH_TEST);
    }
    else
    {
        // enable depth buffer test
        glEnable(GL_DEPTH_TEST);

        // set comparison function
        glDepthFunc(depthFunc(depthState->compareFunc));

        // specify if depth buffer writes are enabled
        glDepthMask(depthState->writeEnabled);

        // defaults are fine for glDepthRange
    }

    depthState_ = depthState;
}

const DepthState* Device::depthState() const
{
    return depthState_;
}

void Device::setRasterizerState(const RasterizerState* const rasterizerState)
{
    GRAPHICS_RUNTIME_ASSERT(rasterizerState != 0);

    if (rasterizerState_ == rasterizerState)
    {
        // TODO: this assumes that the active stencil test state has not been
        // modified, is this assumption ok?

        // nothing to do
        return;
    }

    // this is the default, set it just in case someone has modified it with a
    // direct OpenGL function call
    glFrontFace(GL_CCW);

    // set cull mode
    switch (rasterizerState->cullMode)
    {
        case RasterizerState::CullMode::CullClockwise:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            break;

        case RasterizerState::CullMode::CullCounterClockwise:
            glEnable(GL_CULL_FACE);
            glCullFace(GL_FRONT);
            break;

        case RasterizerState::CullMode::CullNone:
            glDisable(GL_CULL_FACE);
            break;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            break;
    }

    // set fill mode
    switch (rasterizerState->fillMode)
    {
        case RasterizerState::FillMode::Solid:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;

        case RasterizerState::FillMode::WireFrame:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            break;
    }

    rasterizerState_ = rasterizerState;
}

const RasterizerState* Device::rasterizerState() const
{
    return rasterizerState_;
}

void Device::setStencilState(const StencilState* const stencilState)
{
    GRAPHICS_RUNTIME_ASSERT(stencilState != 0);

    if (stencilState_ == stencilState)
    {
        // TODO: this assumes that the active stencil test state has not been
        // modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (stencilState->enabled == false)
    {
        // disable stencil test
        glDisable(GL_STENCIL_TEST);
    }
    else
    {
        // enable stencil test
        glEnable(GL_STENCIL_TEST);

        // specify back face function
        glStencilFuncSeparate(
            GL_BACK,
            stencilFunc(stencilState->backFace.compareFunc),
            stencilState->backFace.reference,
            stencilState->backFace.mask
        );

        // specify front face function
        glStencilFuncSeparate(
            GL_FRONT,
            stencilFunc(stencilState->frontFace.compareFunc),
            stencilState->frontFace.reference,
            stencilState->frontFace.mask
        );

        // specify write masks
        glStencilMaskSeparate(GL_BACK, stencilState->backFace.writeMask);
        glStencilMaskSeparate(GL_FRONT, stencilState->frontFace.writeMask);

        // specify back face actions
        glStencilOpSeparate(
            GL_BACK,
            stencilAction(stencilState->backFace.stencilFailAction),
            stencilAction(stencilState->backFace.depthFailAction),
            stencilAction(stencilState->backFace.depthPassAction)
        );

        // specify front face actions
        glStencilOpSeparate(
            GL_FRONT,
            stencilAction(stencilState->frontFace.stencilFailAction),
            stencilAction(stencilState->frontFace.depthFailAction),
            stencilAction(stencilState->frontFace.depthPassAction)
        );
    }

    stencilState_ = stencilState;
}

const StencilState* Device::stencilState() const
{
    return stencilState_;
}

void Device::setTexture(const int index, Texture* const texture)
{
    //GRAPHICS_RUNTIME_ASSERT(program_ != 0);
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTextureUnits());

    if (textures_[index] == texture)
    {
        // nothing to do
        return;
    }

    // activate the specified texture unit
    glActiveTexture(GL_TEXTURE0 + index);

    if (texture == 0)
    {
        // disable the specified texture unit
        glDisable(GL_TEXTURE_2D);
    }
    else
    {
        // enable the specified texture unit and bind the given texture to it
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureHandle());
    }

    textures_[index] = texture;
}

Texture* Device::texture(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTextureUnits());
    return textures_[index];
}

int Device::numTextureUnits() const
{
    GLint result = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &result);

    // OpenGL specification says that the number of texture units must be at
    // least 2
    GRAPHICS_RUNTIME_ASSERT(result >= 2);

    return result;
}

int Device::numActiveTextureUnits() const
{
    int count = 0;

    for (int i = 0; i < numTextureUnits(); ++i)
    {
        if (textures_[i] != 0)
        {
            ++count;
        }
    }

    return count;
}

void Device::setClearColor(const Color4& clearColor)
{
    // glClearColor will silently clamp the parameters between [0, 1]
    glClearColor(
        clearColor.r,
        clearColor.g,
        clearColor.b,
        clearColor.a
    );
}

void Device::setClearDepth(const float clearDepth)
{
    // glClearDepth will silently clamp the parameter between [0, 1]
    glClearDepth(clearDepth);
}

void Device::setClearStencil(const uint32_t clearStencil)
{
    // glClearStencil will silently mask the parameter with 2^m-1 where m is
    // the number of bits in the stencil buffer
    glClearStencil(clearStencil);
}

void Device::clearBuffers(
    const bool color,
    const bool depth,
    const bool stencil)
{
    // glClear is affected by various settings, including the scissor test and
    // the buffer writemasks. If a buffer is not present, then a glClear
    // directed at that buffer has no effect.
    glClear(clearMask(color, depth, stencil));
}

void Device::clearBuffers(
    const bool color,
    const bool depth,
    const bool stencil,
    const RectangleI& area)
{
    GRAPHICS_RUNTIME_ASSERT(area.x >= 0);
    GRAPHICS_RUNTIME_ASSERT(area.y >= 0);
    GRAPHICS_RUNTIME_ASSERT(area.width >= 0);
    GRAPHICS_RUNTIME_ASSERT(area.height >= 0);
    GRAPHICS_RUNTIME_ASSERT(area.x + area.width <= width());
    GRAPHICS_RUNTIME_ASSERT(area.y + area.height <= height());

    // TODO: this does not restore previous scissor state, update this function
    // if scissor state management is added

    glEnable(GL_SCISSOR_TEST);

    // specify scissor rectangle, glClear will only affect pixels that lie
    // within the scissor rectangle
    glScissor(area.x, area.y, area.width, area.height);

    // glClear is affected by various settings, including the scissor test and
    // the buffer writemasks. If a buffer is not present, then a glClear
    // directed at that buffer has no effect.
    glClear(clearMask(color, depth, stencil));

    glDisable(GL_SCISSOR_TEST);
}

void Device::drawPrimitives(const PrimitiveType::Enum type)
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);
    GRAPHICS_RUNTIME_ASSERT(vertexFormat_ != 0);
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);

    if (indexBuffer_ != 0)
    {
        // there is an active index buffer, use indexed rendering

        // glDrawElements uses the currently bound GL_ELEMENT_ARRAY_BUFFER as
        // the index array if the last parameter is a null pointer
        glDrawElements(
            primitiveType(type),
            indexBuffer_->numElements(),
            indexBufferType_,
            0
        );
    }
    else
    {
        // there is no active index buffer, use non-indexed rendering

        glDrawArrays(
            primitiveType(type),
            0,
            vertexBuffer_->numElements()
        );
    }
}

void Device::drawPrimitives(
    const PrimitiveType::Enum type,
    const int offset,
    const int count)
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);
    GRAPHICS_RUNTIME_ASSERT(vertexFormat_ != 0);
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);
    GRAPHICS_RUNTIME_ASSERT(offset >= 0);
    GRAPHICS_RUNTIME_ASSERT(count >= 0);

    if (indexBuffer_ != 0)
    {
        // there is an active index buffer, use indexed rendering

        // make sure the specified range is valid
        GRAPHICS_RUNTIME_ASSERT(offset + count <= indexBuffer_->numElements());

        // glDrawRangeElements uses the currently bound GL_ELEMENT_ARRAY_BUFFER
        // as the index array if the last parameter is a null pointer
        glDrawRangeElements(
            primitiveType(type),
            offset,
            count - 1,
            count,
            indexBufferType_,
            0
        );
    }
    else
    {
        // there is no active index buffer, use non-indexed rendering

        // make sure the specified range is valid
        GRAPHICS_RUNTIME_ASSERT(offset + count <= vertexBuffer_->numElements());

        glDrawArrays(
            primitiveType(type),
            offset,
            count
        );
    }
}

void Device::bindVertexBuffer(VertexBuffer* const vertexBuffer)
{
    // this function assumes that there is no active vertex buffer
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);

    // bind the given vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->id());

    // intitialize and enable all attribute arrays
    for (int i = 0; i < vertexFormat_->numAttributes(); ++i)
    {
        const VertexAttribute& attribute = vertexFormat_->attribute(i);

        if (attribute.name().empty() == false)
        {
            // glGetAttribLocation returns -1 on error
            const GLint location = glGetAttribLocation(
                program_->id(),
                attribute.name().c_str()
            );

            if (location != -1)
            {
                glVertexAttribPointer(
                    location,
                    attribute.numComponents(),
                    vertexAttributeType(attribute.type()),
                    false,
                    vertexFormat_->stride(),
                    reinterpret_cast<const GLvoid*>(attribute.offset())
                );

                glEnableVertexAttribArray(location);
            }
        }
    }

    vertexBuffer_ = vertexBuffer;
}

void Device::unbindVertexBuffer()
{
    // this function assumes that there is an active vertex buffer
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);

    // unbind the active vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // disable all attribute arrays
    for (int i = 0; i < vertexFormat_->numAttributes(); ++i)
    {
        const VertexAttribute& attribute = vertexFormat_->attribute(i);

        if (attribute.name().empty() == false)
        {
            // TODO: optimize by storing the locations when binding the vertex
            // buffer?

            // glGetAttribLocation returns -1 on error
            const GLint location = glGetAttribLocation(
                program_->id(),
                attribute.name().c_str()
            );

            if (location != -1)
            {
                glDisableVertexAttribArray(location);
            }
        }
    }

    vertexBuffer_ = 0;
}
