/******************************************************************************
file:       G_config
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
Some library wide flags in one location.
******************************************************************************/

/******************************************************************************
BSD 2-Clause License

Copyright (c) 2000, Robbert de Groot
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

// I have and PCLint from time to time.  When you see something like this it is
// to quiet some PCLint error/warnings that I deam to be ok and not needing to
// the changed or fixed.  I don't know what these ones mean off the top of my
// head but suffice to say I have looked into them.
/*lint -save -e960 -e961 -e9026 */

#if !defined(G_CONFIGH)
#define      G_CONFIGH

// GRL was initially developed to be a DLL.  After a while I found DLLs were 
// just being a pain when it comes to distribution of the exe.  So I have more
// recently adopted sticking to static libraries as it makes my life slightly
// less annoying.
#if !defined(GRL_DLL)
#  define      grlAPI
#else
#  if defined(GRL_EXPORTS)
#     define   grlAPI __declspec(dllexport)
#  else
#     define   grlAPI __declspec(dllimport)
#  endif
#endif

// Expecting that GRL could be used in a C++ project so properly wrapping the
// code in these C++ blocks.  
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
constant:
******************************************************************************/

// Flags when in debug.
#if defined(_DEBUG)

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

// When allocating memory with gmem routines I include a pointer to a type 
// string.  Every so often this can be handy when debuggin.
#define GMEM_INCLUDES_TYPE_STRING   1

// Flags wen in relese.
#else

#define GCHECK_MEMORY_IS_ON         0
#define GTRACE_IS_ON                0
#define GMEM_INCLUDES_TYPE_STRING   0

#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
