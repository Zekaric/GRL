/**************************************************************************************************
file:       G_config
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
Some library wide flags in one location.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2000, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

// I have and PCLint from time to time.  When you see something like this it is
// to quiet some PCLint error/warnings that I deam to be ok and not needing to
// the changed or fixed.  I don't know what these ones mean off the top of my
// head but suffice to say I have looked into them.

#pragma once

// GRL was initially developed to be a DLL.  After a while I found DLLs were
// just being a pain when it comes to distribution of the exe.  So I have more
// recently adopted sticking to static libraries as it makes my life slightly
// less annoying.
#if defined(LIBGRL_STATIC)
#  define      grlAPI
#else
#  if defined(LIBGRL_EXPORTS)
#     define   grlAPI __declspec(dllexport)
#  else // LIBGRL_IMPORTS
#     define   grlAPI __declspec(dllimport)
#  endif
#endif

// Expecting that GRL could be used in a C++ project so properly wrapping the
// code in these C++ blocks.
/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/

// Flags when in debug.
#if defined(_DEBUG)

// GTYPE_NAME_IS_ON is used for memory leaking.  At the start of the type or
// container there are strings of 16 characters.  This string should be unique
// so that when the first few byte of the structure are displayed in the leak
// report we should know what type was leaking.
#define GTYPE_NAME_IS_ON            1

// CHECK_MEMORY_IS_ON is used in conjunction with debugCheckMemory() macro below.
// This is basically to check the heap if it got corrupted in any way.  Used
// to track down memory corruption locations.
// 0 = No heap checking
// 1 = Heap checking
#define GCHECK_MEMORY_IS_ON         0

// TRACE_IS_ON is used to track the flow of the CPU through the code.  I do not
// use this option much, it was an idea but it can and will produce way too
// much output.
// 0 = No function tracing
// 1 = Function tracing
#define GTRACE_IS_ON                0

// If we are on a little endian machine we need to byte swap to get into big endian.  GRL assumes
// Big Endian
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define grlSWAP_NEEDED 1
#else
#define grlSWAP_NEEDED 0
#endif

// Flags when building a release.
#else

#define GTYPE_NAME_IS_ON            0
#define GCHECK_MEMORY_IS_ON         0
#define GTRACE_IS_ON                0

#endif

#if GTYPE_NAME_IS_ON == 1

#define GTYPE_SET(VAR, TYPE)                                            \
{                                                                       \
   Gindex __gtype_set_index__ = 0;                                      \
   forCount(__gtype_set_index__, 16)                                    \
   {                                                                    \
      GTYPE_GET(VAR)[__gtype_set_index__] = TYPE[__gtype_set_index__];  \
      breakIf((TYPE)[__gtype_set_index__] == 0);                        \
   }                                                                    \
   while(__gtype_set_index__ < 16)                                      \
   {                                                                    \
      GTYPE_GET(VAR)[__gtype_set_index__++] = 0;                        \
   }                                                                    \
}

#define GTYPE_GET(VAR)              VAR->typeName

#define GTYPE_VAR                   Char typeName[16];

#else

#define GTYPE_SET(VAR, TYPE)
#define GTYPE_GET(VAR)              NULL
#define GTYPE_VAR

#endif

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
