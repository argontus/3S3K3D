/**
 * @file graphics/nodecontrollers/nodecontroller.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODECONTROLLERS_NODECONTROLLER_H_INCLUDED
#define GRAPHICS_NODECONTROLLERS_NODECONTROLLER_H_INCLUDED

class Node;

class NodeController
{
public:
    struct UpdateMessage
    {
        enum Enum
        {
            None,
            Die,
            KillMe
        };
    };

    virtual ~NodeController() {}

    virtual NodeController* clone() const = 0;

    // TODO: Type Node* may need to be casted to a pointer to a derived type,
    // use some other method for passing the node being controlled?
    virtual UpdateMessage::Enum update(Node* node, float dt) = 0;

protected:
    NodeController() {}
    NodeController(const NodeController& other) {}

private:
    // hide the assignment operator
    NodeController& operator =(const NodeController&);
};

#endif // #ifndef GRAPHICS_NODECONTROLLERS_NODECONTROLLER_H_INCLUDED
