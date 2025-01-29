/**************************************************************************************************

file:       gtrace
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
These are simple trace routines.  Meant to make life simple in
hunting down problems in debug and production code.

The trace routines are tiny, fast and simple.  If left in the
code they should not add much overhead if at all.  Care should
still be used to not use trace functions in very hi use routines.

Example:
In the following code, trace will actually do something if the
environment variable called Gumby is set to something.  Gumby should
be set to a file where the trace output is to be sent.

Gtrace *_trace  = NULL;
/ / Required or none of the gentry() macros will have gtraceEnter() calls.
#define GTRACE _trace
...
_trace = gtraceStart("Gumby");
...
int gumby(void) {
   genter();
   gtraceMessage(_trace, "gumby writes a message");
   ...
   greturn gbTRUE;
}
...
gtraceStop(_trace);
**************************************************************************************************/

/**************************************************************************************************
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
**************************************************************************************************/

#if !defined(GTRACEH)
#define      GTRACEH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
GTRACE_ENABLED defined in grlconfig.h
**************************************************************************************************/
#if GTRACE_IS_ON == 1

/**************************************************************************************************
constant:
**************************************************************************************************/
#if defined(GRL_EXPORTS) || !defined(GRL_DLL)
#define GTRACE ___gtraceTrace___
#endif

typedef enum
{
   gtraceLevelNONE       = 0x00000000,
   gtraceLevelALL        = 0xffffffffU,
   gtraceLevelENTER_EXIT = 0x10000000,
   gtraceLevelNOTICE     = 0x20000000,
   gtraceLevelWARNING    = 0x40000000,
   gtraceLevelERROR      = 0x80000000U
} GtraceLevel;

/**************************************************************************************************
variable:
**************************************************************************************************/
extern grlAPI GtraceLevel ___gtraceLevel___;

/**************************************************************************************************
Functions
**************************************************************************************************/
grlAPI Gb      gtraceEnter(     void);
grlAPI void    gtraceExit(      void);

grlAPI void    gtraceMessage(   GtraceLevel level, char *message);

grlAPI Gb      gtraceStart(     GtraceLevel level, char *filename);
       Gb      gtraceStartGrl(  void);
grlAPI void    gtraceStop(      void);
       void    gtraceStopGrl(   void);

/* LOCAL: PRIVATE TO GTRACE FUNCTIONS ******************************/
grlAPI Gb      gtraceMessage_(  Char const * const file, Char const * const function, Gindex const line, Char const * const message);


/**************************************************************************************************
macro:
**************************************************************************************************/
#define gtraceEnter() \
   ((___gtraceLevel___ & gtraceLevelENTER_EXIT) ? \
      gtraceMessage_(__FILE__, __FUNCTION__, __LINE__, " {") :\
      gbFALSE)

#define gtraceExit() \
   if (___gtraceLevel___ & gtraceLevelENTER_EXIT) {\
      gtraceMessage_(__FILE__, __FUNCTION__, __LINE__, " }");\
   }

#define gtraceMessage(LEVEL, X) \
   if (___gtraceLevel___ & LEVEL) {\
      gtraceMessage_(__FILE__, __FUNCTION__, __LINE__, X);\
   }

#else
// GTRACE not used.

typedef void Gtrace;

/*lint -save -e960 -e961 -e9026 */
#define gtraceEnter()               gbFALSE;
#define gtraceExit()

#define gtraceMessage(LEVEL, MSG)   // Do nothing

#define gtraceStart(LEVEL)          gbTRUE
#define gtraceStop()
/*lint -restore */

#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
