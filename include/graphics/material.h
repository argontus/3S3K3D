/**
 * @file graphics/material.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MATERIAL_H_INCLUDED
#define GRAPHICS_MATERIAL_H_INCLUDED

#include <vector>

class Program;
class Variable;

/**
 * Represents a material for rendering geometry.
 */
class Material
{
public:
    /**
     * Destructor.
     */
    ~Material();

    /**
     * Default constructor.
     */
    Material();

    /**
     * Sets the active program.
     *
     * @param program The program to set.
     */
    void setProgram(Program* program);

    Program* program() const;

    /**
     * Adds <code>variable</code> to <code>*this</code>. <code>variable</code>
     * must have been allocated via a C++ <code>new</code> expression.
     * <code>*this</code> takes ownership of <code>variable</code>.
     *
     * @param variable The variable to add, cannot be a null pointer.
     */
    void addVariable(Variable* variable);

    void bind() const;
    void unbind() const;

    // returns true on success
    bool link();

    // for internal use
    int generateTextureUnitIndex();

private:
    Program* program_;                  ///< Program.
    std::vector<Variable*> variables_;  ///< Variables.
    int numTextureUnits_;               ///< Number of assigned texture units.

    // prevent copying
    Material(const Material&);
    Material& operator =(const Material&);
};

#endif // #ifndef GRAPHICS_MATERIAL_H_INCLUDED
