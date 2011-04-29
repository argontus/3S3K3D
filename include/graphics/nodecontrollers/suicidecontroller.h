/**
 * @file graphics/nodecontrollers/suicidecontroller.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODECONTROLLERS_SUICIDECONTROLLER_H_INCLUDED
#define GRAPHICS_NODECONTROLLERS_SUICIDECONTROLLER_H_INCLUDED

#include <graphics/nodecontrollers/nodecontroller.h>

class SuicideController : public NodeController
{
public:
    virtual ~SuicideController();

    explicit SuicideController(float life);

    /**
     * @name NodeController Interface
     */
    //@{
    virtual SuicideController* clone() const;
    virtual UpdateMessage::Enum update(Node* node, float dt);
    //@}

protected:
    SuicideController(const SuicideController& other);

private:
    float life_;    ///< Remaining lifetime for the node.

    // hide the assignment operator
    SuicideController& operator =(const SuicideController&);
};

#endif // #ifndef GRAPHICS_NODECONTROLLERS_SUICIDECONTROLLER_H_INCLUDED
