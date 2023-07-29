/******************************************************************************
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

#if !defined(GRLH)
#define      GRLH

/******************************************************************************
include:
******************************************************************************/
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
//lint -save -e829
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
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <wchar.h>
#include <math.h>
//lint -restore

// includes are in order of dependence.  

#include "g_config.h"

#include "g_base.h"

// Data containers ////////////////////////////////////////////////////////////
#include "g_Container.h"

#include "g_Array.h"          // depends on g_Container
#include "g_ArrayKey.h"
#include "g_List.h"           
#include "g_ListKey.h"
#include "g_Tree.h"
#include "g_TreeKey.h"

#include "g_Hash.h"           // depends on g_List
#include "g_HashKey.h"        // depends on g_ListKey
///////////////////////////////////////////////////////////////////////////////

// Memory handling ////////////////////////////////////////////////////////////
#include "gleak.h"

#include "gmem.h"             // depends on gleak

#include "gswap.h"
///////////////////////////////////////////////////////////////////////////////

// Base Types /////////////////////////////////////////////////////////////////
#include "gb.h"
#include "gn.h"
#include "gi.h"
#include "gr.h"
#include "gp.h"
#include "gv.h"
#include "gv1.h"
#include "gv2.h"
#include "gv4.h"
#include "gv8.h"
#include "gvp.h"
#include "gvData.h"

#include "gcount.h"
#include "gindex.h"

#include "gc.h"
#include "gs.h"

#include "gsFunction.h"       // depends on gs
#include "gsKey.h"            // depends on gs gsHash

#include "gguid.h"
///////////////////////////////////////////////////////////////////////////////

#include "gbit.h"
#include "gbuf.h"             // depends on Gn.h
#include "gheap.h"            // Used in g_Array but not the header file.
#include "glock.h"
#include "gosversion.h"
#include "grandom.h"
#include "gtemp.h"
#include "gthread.h"
#include "gtime.h"
#include "gtrace.h"

#include "gprofile.h"         // depends on gtime

#include "gcon.h"             // depends on gs, gsFunction
#include "gpath.h"            // depends on gs, gsFunction

#include "gdir.h"             // depends on gpath
#include "gfile.h"            // depends on gc gs gpath

#include "gfilePref.h"        // depends on gfile
#include "gfileRat.h"         // depends on gfile

#include "gmath.h"

#if 0 // Currently disabled because they have not be moved over from my private repo yet.
#include "gmemCompressFast.h" //
#include "gmemCompressZip.h"  //

#include "ginterp.h"

#include "glockQueue.h"


#include "gthreadArray.h"  // depends on g_Array

#include "grex.h"          // depends on gs
#include "gregex.h"        // depends on gs

#include "gbin.h"          // depends on gc gs
#include "gpinPin.h"       // depends on gc gs


//#include "gdirArray.h"     // depends on gdir gpArray

#include "gfileData.h"     // depends on gfile
#include "gpin.h"          // depends on gc gs gpinpin
#include "grub.h"          // depends on gfile

#include "gpref.h"         // depends on gc gs gfile gssHash
#include "GprefBin.h"      // depends on gfile
#include "grob.h"          // depends on grub

#include "gsUtil.h"        // depends on gfile gpref gvv gsArray gsHash gssHash

#include "gnet.h"          // depends on gs

#include "gnetWeb.h"       // depends on gnet

#endif

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/
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

#endif
