/**
 * @file graphics/effect.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_EFFECT_H_INCLUDED
#define GRAPHICS_EFFECT_H_INCLUDED

#include <string>
#include <vector>

class Technique;

// TODO: has a lot in common with Pass and Technique classes
class Effect
{
public:
    ~Effect();

    Effect(const std::string& name, int numTechniques);
    Effect(const Effect& other);

    const std::string name() const;

    Effect* clone() const;

    void setTechnique(int index, Technique* technique);

    Technique* technique(int index);
    const Technique* technique(int index) const;

    Technique* technique(const std::string& name);
    const Technique* technique(const std::string& name) const;

    int numTechniques() const;

private:
    void deleteTechniques();

    std::string name_;
    std::vector<Technique*> techniques_;

    // hide the assignment operator
    Effect& operator =(const Effect&);
};

#endif // #ifndef GRAPHICS_EFFECT_H_INCLUDED
