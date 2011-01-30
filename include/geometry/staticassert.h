/**
 * @file geometry/staticassert.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_STATICASSERT_H_INCLUDED
#define GEOMETRY_STATICASSERT_H_INCLUDED

/**
 * Static (compile-time) assertion macro. Triggers the assertion if
 * <code>cond</code> evaluates to <code>false</code>.
 *
 * @param cond A boolean expression.
 */
#define GEOMETRY_STATIC_ASSERT(cond) typedef int GeometryStaticAssert_[ (cond) ? 1 : -1 ]

#endif // #ifndef GEOMETRY_STATICASSERT_H_INCLUDED
