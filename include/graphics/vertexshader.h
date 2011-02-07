/**
 * @file graphics/vertexshader.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VERTEXSHADER_H_INCLUDED
#define GRAPHICS_VERTEXSHADER_H_INCLUDED

#include <graphics/shader.h>

/**
 * Represents an OpenGL vertex shader.
 */
class VertexShader : public Shader
{
public:
    /**
     * Destructor.
     */
    virtual ~VertexShader();

    /**
     * Default constructor.
     */
    VertexShader();

private:
    // prevent copying
    VertexShader(const VertexShader&);
    VertexShader& operator =(const VertexShader&);
};

#endif // #ifndef GRAPHICS_VERTEXSHADER_H_INCLUDED
