/**
 * @file graphics/renderer.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/renderer.h>

#include <cstring>

#include <sstream>

#include <graphics/runtimeassert.h>

Renderer::~Renderer()
{
    // ...
}

Renderer::Renderer()
:   indexBuffer_(0),
    program_(0),
    vertexBuffer_(0),
    vertexFormat_(0),
    indexBufferType_(0)
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
    // TODO: fetch and return the actual number of texture units
    return MaxTextureUnits;
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

GLenum Renderer::indexBufferType(const IndexBuffer::Format::Enum format)
{
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

GLenum Renderer::vertexAttributeType(const VertexAttribute::Type::Enum type)
{
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

        const GLint location = glGetAttribLocation(
            program_->id(),
            attribute.name().c_str()
        );

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
