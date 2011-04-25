/**
 * @file graphics/technique.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_TECHNIQUE_H_INCLUDED
#define GRAPHICS_TECHNIQUE_H_INCLUDED

#include <string>
#include <vector>

class Pass;

// TODO: has a lot in common with Effect and Pass classes
class Technique
{
public:
    ~Technique();

    Technique(const std::string& name, int numPasses);
    Technique(const Technique& other);

    const std::string name() const;

    Technique* clone() const;

    void setPass(int index, Pass* pass);

    Pass* pass(int index);
    const Pass* pass(int index) const;

    Pass* pass(const std::string& name);
    const Pass* pass(const std::string& name) const;

    int numPasses() const;

private:
    void deletePasses();

    std::string name_;
    std::vector<Pass*> passes_;

    // hide the assignment operator
    Technique& operator =(const Technique&);
};

#endif // #ifndef GRAPHICS_TECHNIQUE_H_INCLUDED
