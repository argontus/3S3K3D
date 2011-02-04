/**
 * @file graphics/runtimeassert.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RUNTIMEASSERT_H_INCLUDED
#define GRAPHICS_RUNTIMEASSERT_H_INCLUDED

#include <cassert>

/**
 * @def GRAPHICS_RUNTIME_ASSERT(cond)
 *
 * Runtime assertion macro. Triggers the assertion if <code>cond</code>
 * evaluates to <code>false</code>. This evaluates to a no-op if
 * <code>NDEBUG</code> macro is defined.
 *
 * @param cond A boolean expression.
 */

#ifdef NDEBUG
#   define GRAPHICS_RUNTIME_ASSERT(cond) (void)sizeof(cond)
#else
#   define GRAPHICS_RUNTIME_ASSERT(cond) assert(cond)
#endif

#endif // #ifndef GRAPHICS_RUNTIMEASSERT_H_INCLUDED
