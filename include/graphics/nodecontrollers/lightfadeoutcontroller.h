/**
 * @file graphics/nodecontrollers/lightfadeoutcontroller.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODECONTROLLERS_LIGHTFADEOUTCONTROLLER_H_INCLUDED
#define GRAPHICS_NODECONTROLLERS_LIGHTFADEOUTCONTROLLER_H_INCLUDED

#include <geometry/vector3.h>

#include <graphics/nodecontrollers/nodecontroller.h>

class LightFadeOutController : public NodeController
{
public:
    virtual ~LightFadeOutController();

    LightFadeOutController(float life, const Vector3& color);

    /**
     * @name NodeController Interface
     */
    //@{
    virtual LightFadeOutController* clone() const;
    virtual UpdateMessage::Enum update(Node* node, float dt);
    //@}

protected:
    LightFadeOutController(const LightFadeOutController& other);

private:
    float life_;    ///< Remaining lifetime for the node.
    float lifeMax_; ///< Lifetime for the node at the beginning.
    Vector3 color_; ///< Light color at the beginning.

    // hide the assignment operator
    LightFadeOutController& operator =(const LightFadeOutController&);
};

#endif // #ifndef GRAPHICS_NODECONTROLLERS_LIGHTFADEOUTCONTROLLER_H_INCLUDED
