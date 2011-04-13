/**
 * @file graphics/renderer.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/renderer.h>

#include <cstring>

#include <algorithm>
#include <sstream>

#include <graphics/runtimeassert.h>

Renderer::~Renderer()
{
    // ...
}

Renderer::Renderer()
:   program_(0),
    vertexFormat_(0),
    vertexBuffer_(0),
    indexBuffer_(0),
    indexBufferType_(0),
    blendState_(0),
    cullState_(0),
    depthState_(0),
    stencilState_(0)
{
    // set all texture pointers to null pointers
    std::memset(textures_, 0, sizeof(textures_));
}

void Renderer::setProgram(Program* const program)
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);
    GRAPHICS_RUNTIME_ASSERT(numActiveTextureUnits() == 0);

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

Program* Renderer::program() const
{
    return program_;
}

void Renderer::setVertexFormat(VertexFormat* const vertexFormat)
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);
    vertexFormat_ = vertexFormat;
}

VertexFormat* Renderer::vertexFormat() const
{
    return vertexFormat_;
}

void Renderer::setVertexBuffer(VertexBuffer* const vertexBuffer)
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

VertexBuffer* Renderer::vertexBuffer() const
{
    return vertexBuffer_;
}

void Renderer::setIndexBuffer(IndexBuffer* const indexBuffer)
{
    if (indexBuffer_ == indexBuffer)
    {
        // nothing to do
        return;
    }

    indexBuffer_ = indexBuffer;

    if (indexBuffer_ == 0)
    {
        // unbind the active index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        // bind the given index buffer and update element type
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_->id());
        indexBufferType_ = indexBufferType(indexBuffer_->format());
    }
}

IndexBuffer* Renderer::indexBuffer() const
{
    return indexBuffer_;
}

void Renderer::setBlendState(BlendState* const blendState)
{
    if (blendState_ == blendState)
    {
        // TODO: this assumes that the active blend state has not been
        // modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (blendState == 0)
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

BlendState* Renderer::blendState() const
{
    return blendState_;
}

void Renderer::setCullState(CullState* const cullState)
{
    if (cullState_ == cullState)
    {
        // TODO: this assumes that the active cull state has not been modified,
        // is this assumption ok?

        // nothing to do
        return;
    }

    if (cullState == 0)
    {
        // disable culling
        glDisable(GL_CULL_FACE);
    }
    else
    {
        // enable culling
        glEnable(GL_CULL_FACE);

        // specify which polygon faces should be culled, this assumes that CCW
        // polygons are interpreted as front facing
        glCullFace(cullFace(cullState->cullFace));
    }

    cullState_ = cullState;
}

CullState* Renderer::cullState() const
{
    return cullState_;
}

void Renderer::setDepthState(DepthState* const depthState)
{
    if (depthState_ == depthState)
    {
        // TODO: this assumes that the active depth buffer test state has not
        // been modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (depthState == 0)
    {
        // disable depth buffer test
        glDisable(GL_DEPTH_TEST);
        // TODO: is glDepthMask(GL_FALSE) needed for completely disabling depth
        // buffer operations?
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

DepthState* Renderer::depthState() const
{
    return depthState_;
}

void Renderer::setStencilState(StencilState* const stencilState)
{
    if (stencilState_ == stencilState)
    {
        // TODO: this assumes that the active stencil test state has not been
        // modified, is this assumption ok?

        // nothing to do
        return;
    }

    if (stencilState_ == 0)
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

StencilState* Renderer::stencilState() const
{
    return stencilState_;
}

void Renderer::setTexture(const int index, Texture* const texture)
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTextureUnits());

    if (textures_[index] == texture)
    {
        // nothing to do
        return;
    }

    textures_[index] = texture;

    if (texture == 0)
    {
        // disable the texture unit
        glActiveTexture(GL_TEXTURE0 + index);
        glDisable(GL_TEXTURE_2D);
        // TODO: is glBindTexture(GL_TEXTURE_2D, 0) needed?
    }
    else
    {
        // the C++ way of saying variableName = "texture" + index
        std::stringstream ss;
        ss << "texture" << index;
        const std::string variableName = ss.str();

        // glGetUniformLocation returns -1 on error
        const GLint location = glGetUniformLocation(
            program_->id(),
            variableName.c_str()
        );

        GRAPHICS_RUNTIME_ASSERT(location != -1);

        // map the texture unit to the corresponding uniform variable, enable
        // the texture unit and bind the given texture to it
        glUniform1i(location, index);
        glActiveTexture(GL_TEXTURE0 + index);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture->getTextureHandle());
    }
}

Texture* Renderer::texture(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numTextureUnits());
    return textures_[index];
}

int Renderer::numTextureUnits() const
{
    GLint a = 0;
    GLint b = 0;

    glGetIntegerv(GL_MAX_TEXTURE_COORDS, &a);
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &b);

    // OpenGL specification says that the number of texture units must be at
    // least 2. The implementation assumes that the number of texture units is
    // at most MaxTextureUnits.
    GRAPHICS_RUNTIME_ASSERT(std::max(a, b) >= 2);
    GRAPHICS_RUNTIME_ASSERT(std::max(a, b) <= MaxTextureUnits);

    return std::max(a, b);
}

int Renderer::numActiveTextureUnits() const
{
    int count = 0;

    for (int i = 0; i < MaxTextureUnits; ++i)
    {
        if (textures_[i] != 0)
        {
            ++count;
        }
    }

    return count;
}

void Renderer::setColorMask(
    const bool r,
    const bool g,
    const bool b,
    const bool a)
{
    glColorMask(r, g, b, a);
}

void Renderer::renderPrimitives(const PrimitiveType::Enum type)
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

void Renderer::renderPrimitives(
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

GLenum Renderer::blendEquation(const BlendState::Equation::Enum equation)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::blendFunc(const BlendState::SrcFactor::Enum srcFactor)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::blendFunc(const BlendState::DstFactor::Enum dstFactor)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::cullFace(const CullState::CullFace::Enum face)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

    switch (face)
    {
        case CullState::CullFace::Back:
            return GL_BACK;

        case CullState::CullFace::Front:
            return GL_FRONT;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum Renderer::depthFunc(const DepthState::CompareFunc::Enum compareFunc)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::indexBufferType(const IndexBuffer::Format::Enum format)
{
    // TODO: use a lookup table?

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

GLenum Renderer::primitiveType(const PrimitiveType::Enum type)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

    switch (type)
    {
        case PrimitiveType::Points:
            return GL_POINTS;

        case PrimitiveType::Lines:
            return GL_LINES;

        case PrimitiveType::Triangles:
            return GL_TRIANGLES;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return 0;
    }
}

GLenum Renderer::stencilAction(const StencilState::Action::Enum action)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::stencilFunc(const StencilState::CompareFunc::Enum compareFunc)
{
    // TODO: use a lookup table or set enumeration values to corresponding
    // OpenGL enumeration values?

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

GLenum Renderer::vertexAttributeType(const VertexAttribute::Type::Enum type)
{
    // TODO: use a lookup table?

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

void Renderer::bindVertexBuffer(VertexBuffer* const vertexBuffer)
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ == 0);

    // bind the given vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->id());

    // intitialize and enable all attribute arrays
    for (int i = 0; i < vertexFormat_->numAttributes(); ++i)
    {
        const VertexAttribute& attribute = vertexFormat_->attribute(i);

        // glGetAttribLocation returns -1 on error
        const GLint location = glGetAttribLocation(
            program_->id(),
            attribute.name().c_str()
        );

        GRAPHICS_RUNTIME_ASSERT(location != -1);

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

    vertexBuffer_ = vertexBuffer;
}

void Renderer::unbindVertexBuffer()
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);

    // unbind the active vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // disable all attribute arrays
    for (int i = 0; i < vertexFormat_->numAttributes(); ++i)
    {
        // TODO: store the locations when binding the vertex buffer?
        const GLint location = glGetAttribLocation(
            program_->id(),
            vertexFormat_->attribute(i).name().c_str()
        );

        glDisableVertexAttribArray(location);
    }

    vertexBuffer_ = 0;
}
