/******************************************************************************

file:       gtrace
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

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

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

#if GTRACE_IS_ON == 1

/******************************************************************************
global:
variable:
******************************************************************************/
grlAPI GtraceLevel ___gtraceLevel___ = gtraceLevelNONE;

/******************************************************************************
local:
variable:
******************************************************************************/
static Glock  _lock;
static char  *_fileNameA   = NULL;

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gtraceMessage_

Write a message to a trace file.

param:
tracer
   Gtrace *
   in
   The trace information.

file, function, line
   char *, char *, int
   in, in
   The file and line of the trace function call.

message
   char *
   in
   The message of the call.
******************************************************************/
grlAPI Gb gtraceMessage_(char *file, char *function, int line, char *message)
{
   char  string[1024];
   FILE *f;

   returnIf(!_fileNameA, gbFALSE);

   glockEnter(&_lock);

   f = fopen(_fileNameA, "a");
   if (!f)
   {
      glockExit(&_lock);
      return gbFALSE;
   }

   sprintf(string, "(%s, %s, %5d, %s)\n", file, function, line, message);
   fputs(string, f);

   fclose(f);

   glockExit(&_lock);

   return gbTRUE;
}

/******************************************************************************
func: gtraceStart

Start up the routines.
******************************************************************************/
grlAPI Gb gtraceStart(GtraceLevel level, char *fileName)
{
   _fileNameA        = fileName;
   ___gtraceLevel___ = level;

   return gbTRUE;
}

Gb gtraceStartGrl(void)
{
   glockCreateContent(&_lock);

   return gbTRUE;
}

/******************************************************************************
func: gtraceStop

Clean up.
******************************************************************************/
grlAPI void gtraceStop(void)
{
   ___gtraceLevel___ = gtraceLevelNONE;

   return;
}

void gtraceStopGrl(void)
{
   glockDestroyContent(&_lock);

   return;
}

#endif
