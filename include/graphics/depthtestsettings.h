/**
 * @file graphics/depthtestsettings.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DEPTHTESTSETTINGS_H_INCLUDED
#define GRAPHICS_DEPTHTESTSETTINGS_H_INCLUDED

/**
 * Enumeration wrapper for possible depth test comparison functions.
 */
struct DepthTestCompareFunc
{
    /**
     * Possible depth test comparison functions.
     */
    enum Enum
    {
        /**
         * Never passes.
         */
        Never,

        /**
         * Always passes.
         */
        Always,

        /**
         * Passes if the incoming depth value is less than the stored depth
         * value.
         */
        Less,

        /**
         * Passes if the incoming depth value is less than or equal to the
         * stored depth value.
         */
        LessEqual,

        /**
         * Passes if the incoming depth value is greater than the stored depth
         * value.
         */
        Greater,

        /**
         * Passes if the incoming depth value is greater than or equal to the
         * stored depth value.
         */
        GreaterEqual,

        /**
         * Passes if the incoming depth value is equal to the stored depth
         * value.
         */
        Equal,

        /**
         * Passes if the incoming depth value is not equal to the stored depth
         * value.
         */
        NotEqual
    };
};

/**
 * Describes depth buffer test settings.
 */
class DepthTestSettings
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    DepthTestSettings();

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(DepthTestSettings& other);

    /**
     * Is depth buffering enabled?
     */
    bool enabled;

    /**
     * Comparison function for depth buffer comparisons.
     */
    DepthTestCompareFunc::Enum compareFunc;
};

#endif // #ifndef GRAPHICS_DEPTHTESTSETTINGS_H_INCLUDED
