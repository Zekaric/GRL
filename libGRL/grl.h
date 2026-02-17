/**************************************************************************************************
file:       GRL
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
GRL - Groot's Runtime Library.

A kitchen sink library to speed up 'C' development by providing missing or
easier APIs for common programming things.

Usage:
Start up GRL.  Called as one of the first things your program will do.

   if (!grlStart())
   {
      // GRL failed to start.  Shutdown as nothing will work.
   }

Clean up.  Called as one of the last things your program will do.

   grlStop();

On stop you will get a leak report in the output window in Visual Studio.

Compiling:
You need to properly set at compile time

   grlWINDOWS, grlOSX, or grlLINUX

and

   grl32, or grl64

Compile time defines when using this library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

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

#pragma once

/**************************************************************************************************
include:
**************************************************************************************************/

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   #define grlWINDOWS            1
   #ifdef _WIN64
      #define grl64              1
   #else
      #define grl32              1
   #endif

#elif __APPLE__
   //#include <TargetConditionals.h>
   #if TARGET_IPHONE_SIMULATOR
      // iOS, tvOS, or watchOS Simulator
      // Not supported
      #define grlAPPLE_IOS       1
   #elif TARGET_OS_MACCATALYST
      // Mac's Catalyst (ports iOS API into Mac, like UIKit).
   #elif TARGET_OS_IPHONE
      // iOS, tvOS, or watchOS Simulator
      // Not supported
      #define grlAPPLE_IOS       1
   #elif TARGET_OS_MAC
      #define grlAPPLE_OSX       1
   #else
      #error "Unknown Apple platform"
   #endif
   // Assuming all are 64 bit
   #define grl64                 1

#elif __ANDROID__
   // Not supported
   #define grlANDROID            1

#elif __linux__
   #define grlNIX                1
   #if __x86_64__ || __ppc64__
      #define grl64              1
   #else
      #define grl32              1
   #endif

#elif __unix__ // all unices not caught above
   // Unix
   #define grlNIX                1

#else
#   error "Unknown compiler"

#endif

#if !defined(grl64) && !defined(grl32)
#error "grl64 or grl32 not defined.  Need to set as compiler flag."
#endif

#if !defined(grlWINDOWS) && !defined(grlAPPLE_OSX) && !defined(grlNIX)
#error "grlWINDOWS, grlAPPLE_OSX, or grlNIX not defined.  Need to set as compiler flag."
#endif


#if defined(grlWINDOWS) // I defined this, compile time define.

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <Ws2tcpip.h>

#include <windows.h>
#include <ObjBase.h>

#if defined(_DEBUG)
#include <crtdbg.h>
#endif

// I don't know what to do with these headers yet.
#include <io.h>
#include <errno.h>
#include <process.h>
#include <share.h>

#else
#include <wchar.h>
#include <wctype.h>
#endif

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>

#define _USE_MATH_DEFINES
#include <math.h>

// Leveraging a lot of help from SDL3 for cross platform features.
#include <SDL3\SDL.h>

// includes are in order of dependence.

#include "g_config.h"

#include "g_base.h"

// Memory handling ////////////////////////////////////////////////////////////////////////////////
#include "gleak.h"

#include "gswap.h"

#include "gmem.h"             // depends on gleak

// Base Types /////////////////////////////////////////////////////////////////////////////////////
#include "gkv.h"

#include "gv.h"
#include "gv1.h"
#include "gv2.h"
#include "gv4.h"
#include "gv8.h"
#include "gvData.h"

#include "gindex.h"

#include "gchar.h"

#include "gguid.h"

#include "gbit.h"


// Data containers ////////////////////////////////////////////////////////////////////////////////
#include "gvContainer.h"

#include "gvArray.h"          // depends on gvContainer, gheap
#include "gvList.h"           // depends on gvContainer
#include "gvTree.h"           // depends on gvContainer

#include "gkvArray.h"         // depends on gvContainer
#include "gkvList.h"          // depends on gvContainer
#include "gkvTree.h"          // depends on gvContainer

#include "gvHash.h"           // depends on gvContainer, gvList
#include "gkvHash.h"          // depends on gvContainer, gkvList

// Semi-Base Types ////////////////////////////////////////////////////////////////////////////////
#include "gs.h"               // depends on gvArray

#include "gsFunction.h"       // depends on gs
#include "gsKey.h"            // depends on gs gsHash

#include "gbuf.h"             // depends on Gn.h, gvArray

#include "gatomic.h"
#include "glock.h"
#include "grandom.h"
#include "gtemp.h"
#include "gthread.h"
#include "gtime.h"
#include "gtrace.h"

#include "gprofile.h"         // depends on gtime

// File System ////////////////////////////////////////////////////////////////////////////////////
#include "gpath.h"            // depends on gs

#include "gdir.h"             // depends on gpath, gtime
#include "gfile.h"            // depends on gc, gs, gpath

// IO /////////////////////////////////////////////////////////////////////////////////////////////
#include "giorat.h"           // depends on Gfile only at the moment because it is intended that it
                              // is only ever a file based format.
#include "giorub.h"           // depends on Gfile only

#include "gioRob.h"           // depends on gioRub

#include "gio.h"              // depends on Gs and Gfile

#include "giogod.h"           // depends on Gio
#include "giojson.h"
#include "giopref.h"

// Base Functions /////////////////////////////////////////////////////////////////////////////////
#include "gheap.h"

#include "ginterp.h"

#include "gmath.h"

#include "gsUtil.h"           // depends on gs, gpath

#if 0 // Currently disabled because they have not be moved over from my private repo yet.
#include "gmemCompressFast.h" //
#include "gmemCompressZip.h"  //

#include "glockQueue.h"


#include "grex.h"          // depends on gs
#include "gregex.h"        // depends on gs

#include "gbin.h"          // depends on gc gs
#include "gpinPin.h"       // depends on gc gs


#include "gfileData.h"     // depends on gfile


#include "gpin.h"          // depends on gc gs gpinpin

#include "gnet.h"          // depends on gs

#include "gnetWeb.h"       // depends on gnet

#endif

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
grlAPI Gpath   *grlGetExePath(   void);

grlAPI Gb       grlIsStarted(    void);

grlAPI Gb       grlSetExePath(   Gpath * const path);
grlAPI Gb       grlStart(        void);
grlAPI void     grlStop(         void);

grlAPI Gb       gguidIsEqual(    Gguid const a, Gguid const b);
grlAPI Gguid    gguidMake(       void);
grlAPI Gguid    gguidMakeFromA(  Char const * const string);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
