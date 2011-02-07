/**
 * @file graphics/fragmentshader.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_FRAGMENTSHADER_H_INCLUDED
#define GRAPHICS_FRAGMENTSHADER_H_INCLUDED

#include <graphics/shader.h>

/**
 * Represents an OpenGL fragment shader.
 */
class FragmentShader : public Shader
{
public:
    /**
     * Destructor.
     */
    virtual ~FragmentShader();

    /**
     * Default constructor.
     */
    FragmentShader();

private:
    // prevent copying
    FragmentShader(const FragmentShader&);
    FragmentShader& operator =(const FragmentShader&);
};

#endif // #ifndef GRAPHICS_FRAGMENTSHADER_H_INCLUDED
