/**
 * @file graphics/staticassert.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_STATICASSERT_H_INCLUDED
#define GRAPHICS_STATICASSERT_H_INCLUDED

/**
 * Static (compile-time) assertion macro. Triggers the assertion if
 * <code>cond</code> evaluates to <code>false</code>.
 *
 * @param cond A boolean expression.
 */
#define GRAPHICS_STATIC_ASSERT(cond) typedef int GraphicsStaticAssert_[ (cond) ? 1 : -1 ]

#endif // #ifndef GRAPHICS_STATICASSERT_H_INCLUDED
