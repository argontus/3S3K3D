/**
 * @file graphics/culltestsettings.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_CULLTESTSETTINGS_H_INCLUDED
#define GRAPHICS_CULLTESTSETTINGS_H_INCLUDED

/**
 * Enumeration wrapper for possible cull faces.
 */
struct CullFace
{
    /**
     * Possible cull faces.
     */
    enum Enum
    {
        /**
         * Cull back facing polygons.
         */
        Back,

        /**
         * Cull front facing polygons.
         */
        Front
    };
};

/**
 * Describes cull test settings.
 */
class CullTestSettings
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    CullTestSettings();

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(CullTestSettings& other);

    /**
     * Is culling enabled?
     */
    bool enabled;

    /**
     * Which polygon faces are culled?
     */
    CullFace::Enum cullFace;
};

#endif // #ifndef GRAPHICS_CULLTESTSETTINGS_H_INCLUDED
