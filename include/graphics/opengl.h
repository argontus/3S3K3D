#ifndef GRAPHICS_OPENGL_H_INCLUDED
#define GRAPHICS_OPENGL_H_INCLUDED

#ifdef WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define _STDCALL_SUPPORTED
#define _M_IX86
#include <windows.h>

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifdef near
#undef near
#endif

#ifdef far
#undef far
#endif

#endif // #ifdef WIN32

#include <GL/glew.h>
#include <GL/wglew.h>

#endif // #ifndef GRAPHICS_OPENGL_H_INCLUDED
