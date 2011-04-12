/**
 * @file graphics/vec3variable.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VEC3VARIABLE_H_INCLUDED
#define GRAPHICS_VEC3VARIABLE_H_INCLUDED

#include <graphics/variable.h>

#include <geometry/vector3.h>

class Vec3Variable : public Variable
{
public:
    virtual ~Vec3Variable();

    Vec3Variable(const std::string& name, const Vector3& value);

    /**
     * @name Variable Interface
     */
    //@{
    virtual void bind() const;
    //@}

private:
    Vector3 value_;

    // prevent copying
    Vec3Variable(const Vec3Variable&);
    Vec3Variable& operator =(const Vec3Variable&);
};

#endif // #ifndef GRAPHICS_VEC3VARIABLE_H_INCLUDED
