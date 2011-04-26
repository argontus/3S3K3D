/**
 * @file graphics/rasterizerstate.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RASTERIZERSTATE_H_INCLUDED
#define GRAPHICS_RASTERIZERSTATE_H_INCLUDED

class RasterizerState
{
public:
    struct CullMode
    {
        enum Enum
        {
            CullClockwise,
            CullCounterClockwise,
            CullNone
        };
    };

    struct FillMode
    {
        enum Enum
        {
            Solid,
            WireFrame
        };
    };

    static const RasterizerState* cullClockwise();
    static const RasterizerState* cullCounterClockwise();
    static const RasterizerState* cullNone();
    static const RasterizerState* wireFrame();

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    RasterizerState();
    RasterizerState(CullMode::Enum cullMode, FillMode::Enum fillMode);

    CullMode::Enum cullMode;
    FillMode::Enum fillMode;

    // TODO: depth bias with glPolygonOffset(...),
    // glEnable(GL_POLYGON_OFFSET_FILL) and glEnable(GL_POLYGON_OFFSET_LINE)
};

#endif // #ifndef GRAPHICS_RASTERIZERSTATE_H_INCLUDED
