/**
 * @file graphics/variables/floatvariable.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VARIABLES_FLOATVARIABLE_H_INCLUDED
#define GRAPHICS_VARIABLES_FLOATVARIABLE_H_INCLUDED

#include <graphics/variables/variable.h>

class FloatVariable : public Variable
{
public:
    virtual ~FloatVariable();

    FloatVariable(const std::string& name, float value);

    /**
     * @name Variable Interface
     */
    //@{
    virtual void bind() const;
    //@}

private:
    float value_;

    // prevent copying
    FloatVariable(const FloatVariable&);
    FloatVariable& operator =(const FloatVariable&);
};

#endif // #ifndef GRAPHICS_VARIABLES_FLOATVARIABLE_H_INCLUDED
