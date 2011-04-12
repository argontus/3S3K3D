/**
 * @file graphics/sampler2dvariable.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_SAMPLER2DVARIABLE_H_INCLUDED
#define GRAPHICS_SAMPLER2DVARIABLE_H_INCLUDED

#include <graphics/variable.h>

class Texture;

class Sampler2DVariable : public Variable
{
public:
    virtual ~Sampler2DVariable();

    Sampler2DVariable(const std::string& name, Texture* texture);

    /**
     * @name Variable Interface
     */
    //@{
    virtual void bind() const;
    virtual void unbind() const;
    virtual bool link(Material* material);
    //@}

private:
    Texture* texture_;
    int textureUnit_;

    // prevent copying
    Sampler2DVariable(const Sampler2DVariable&);
    Sampler2DVariable& operator =(const Sampler2DVariable&);
};

#endif // #ifndef GRAPHICS_SAMPLER2DVARIABLE_H_INCLUDED
