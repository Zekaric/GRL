/**************************************************************************************************
file:       glock
author:     Robbert de Groot
copyright:  2009-2012, Robbert de Groot

description:
critical section lock routines.
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: glockCloc
**************************************************************************************************/
grlAPI void glockClocContent(Glock * const lock)
{
#if grlWINDOWS == 1
   InitializeCriticalSection(lock);
#else
#endif
}

/**************************************************************************************************
func: glockDlocContent
**************************************************************************************************/
grlAPI void glockDlocContent(Glock * const lock)
{
#if grlWINDOWS == 1
   DeleteCriticalSection(lock);
#else
#endif
}

/**************************************************************************************************
func: glockEnter
**************************************************************************************************/
grlAPI void glockEnter(Glock * const lock)
{
#if grlWINDOWS == 1
   EnterCriticalSection(lock);
#else
#endif
}

/**************************************************************************************************
func: glockExit
**************************************************************************************************/
grlAPI void glockExit(Glock * const lock)
{
#if grlWINDOWS == 1
   LeaveCriticalSection(lock);
#else
#endif
}
