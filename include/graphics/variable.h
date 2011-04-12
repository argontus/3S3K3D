/**
 * @file graphics/variable.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VARIABLE_H_INCLUDED
#define GRAPHICS_VARIABLE_H_INCLUDED

#include <string>

#include <graphics/opengl.h>

class Material;

class Variable
{
public:
    /**
     * Destructor.
     */
    virtual ~Variable();

    const std::string name() const;

    GLint location() const;

    virtual void bind() const = 0;
    virtual void unbind() const;

    // returns true on success
    virtual bool link(Material* material);

protected:
    /**
     * Constructor.
     *
     * @param name Variable name.
     */
    explicit Variable(const std::string& name);

private:
    std::string name_;  ///< Variable name.
    GLint location_;    ///< Variable location index.

    // prevent copying
    Variable(const Variable&);
    Variable& operator =(const Variable&);
};

#endif // #ifndef GRAPHICS_VARIABLE_H_INCLUDED
