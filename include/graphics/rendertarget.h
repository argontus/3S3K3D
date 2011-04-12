/**
 * @file graphics/rendertarget.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERTARGET_H_INCLUDED
#define GRAPHICS_RENDERTARGET_H_INCLUDED

#include <vector>

#include <graphics/viewport.h>

/**
 * Abstract base class for all render targets.
 */
class RenderTarget
{
public:
    /**
     * Destructor.
     */
    virtual ~RenderTarget();

    /**
     * Updates the contents of this render target.
     *
     * @warning This render target must be properly initialized before calling
     * this member function.
     */
    virtual void update() = 0;

    /**
     * Sets the draw order index.
     *
     * @param drawOrder The draw order index to set.
     */
    void setDrawOrder(int drawOrder);

    /**
     * Gets the draw order index.
     *
     * @return The draw order index.
     */
    int drawOrder() const;

    // TODO: viewport management

protected:
    /**
     * Default constructor.
     */
    RenderTarget();

private:
    int drawOrder_;                     ///< Draw order index.
    std::vector<Viewport> viewports_;   ///< Viewports.

    // prevent copying
    RenderTarget(const RenderTarget&);
    RenderTarget& operator=(const RenderTarget&);
};

#endif // #ifndef GRAPHICS_RENDERTARGET_H_INCLUDED
