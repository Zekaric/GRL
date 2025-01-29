/**************************************************************************************************
file:       Gguid
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
GUID is the Globally Unique Identifier structure.  This code wraps some of the
madness.
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
func: gguidIsEqual
**************************************************************************************************/
Gb gguidIsEqual(Gguid const a, Gguid const b)
{
   genter;

   greturnFalseIf(a.n[0] != b.n[0]);
   greturnFalseIf(a.n[1] != b.n[1]);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gguidMake
**************************************************************************************************/
Gguid gguidMake(void)
{
   Gguid guid;

   genter;

#if defined(grlWINDOWS)
   {
      GUID newId;
      CoCreateGuid(&newId);

      guid.b[ 0] = (newId.Data1 >> 24) & 0xFF;
      guid.b[ 1] = (newId.Data1 >> 16) & 0xFF;
      guid.b[ 2] = (newId.Data1 >>  8) & 0xFF;
      guid.b[ 3] = (newId.Data1 >>  0) & 0xFF;

      guid.b[ 4] = (newId.Data2 >>  8) & 0xFF;
      guid.b[ 5] = (newId.Data2 >>  0) & 0xFF;

      guid.b[ 6] = (newId.Data3 >>  8) & 0xFF;
      guid.b[ 7] = (newId.Data3 >>  0) & 0xFF;

      gmemCopyOverTypeArray(newId.Data4, Gn1, 8, &(guid.b[8]));
   }
#endif

#if defined(grlOSX) // Not tested
   {
      auto newId = CFUUIDCloc(NULL);
      auto bytes = CFUUIDGetUUIDBytes(newId);
      CFRelease(newId);

      bytes.byte0,
         bytes.byte1,
         bytes.byte2,
         bytes.byte3,
         bytes.byte4,
         bytes.byte5,
         bytes.byte6,
         bytes.byte7,
         bytes.byte8,
         bytes.byte9,
         bytes.byte10,
         bytes.byte11,
         bytes.byte12,
         bytes.byte13,
         bytes.byte14,
         bytes.byte15
   }
#endif

#if defined(grlLINUX) // Todo
   {
      uuid_t id;
      uuid_generate(id);
   }
#endif

   greturn guid;
}

/**************************************************************************************************
func: gguidMakeFromA
**************************************************************************************************/
Gguid gguidMakeFromA(Char const * const string)
{
   Gguid guid;

   genter;

   string;

   gmemClearType(&guid, Gguid);

   greturn guid;
}
