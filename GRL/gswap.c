/**************************************************************************************************
file:       gswap
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
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
type:
**************************************************************************************************/
//lint -e754
typedef union
{
   Gn1 b[2];
   Gi2 i;
   Gn2 n;
} Gswap2; //lint !e960 !e9018

typedef union
{
   Gn1 b[4];
   Gi4 i;
   Gn4 n;
   Gr4 r;
} Gswap4; //lint !e960 !e9018

typedef union
{
   Gn1 b[8];
   Gi8 i;
   Gn8 n;
   Gr8 r;
} Gswap8; //lint !e960 !e9018

/**************************************************************************************************
type:
**************************************************************************************************/
static Gb _isBigEndian = gbTRUE;

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gswap*

swap from network to system.
**************************************************************************************************/
grlAPI Gp *gswap2(Gp * const value)
{
   Gswap2 *a,
           b;

   genter;

   greturnIf(_isBigEndian, value);

   a = (Gswap2 *) value;

   b.n = 
      ((((Gn2) a->b[0]) << 8) +
        ((Gn2) a->b[1])); //lint !e734

   a->n = b.n;

   greturn value;
}

grlAPI Gp *gswap4(Gp * const value)
{
   Gswap4 *a,
           b;

   genter;

   greturnIf(_isBigEndian, value);

   a = (Gswap4 *) value;

   b.n = 
      ((((Gn4) a->b[0]) << 24) +
       (((Gn4) a->b[1]) << 16) +
       (((Gn4) a->b[2]) << 8)  +
        ((Gn4) a->b[3]));

   a->n = b.n;

   greturn value;
}

grlAPI Gp *gswap8(Gp * const value)
{
   Gswap8 *a,
           b;

   genter;

   greturnIf(_isBigEndian, value);

   a = (Gswap8 *) value;

   b.n = 
      ((((Gn8) a->b[0]) << 56) +
       (((Gn8) a->b[1]) << 48) +
       (((Gn8) a->b[2]) << 40) +
       (((Gn8) a->b[3]) << 32) +
       (((Gn8) a->b[4]) << 24) +
       (((Gn8) a->b[5]) << 16) +
       (((Gn8) a->b[6]) << 8)  +
        ((Gn8) a->b[7]));

   a->n = b.n;

   greturn value;
}

/**************************************************************************************************
func: gswapIsNeeded
**************************************************************************************************/
grlAPI Gb gswapIsNeeded(void)
{
   genter;

   greturn !_isBigEndian;
}

/**************************************************************************************************
func: gswapStart
**************************************************************************************************/
grlAPI Gb gswapStart(void)
{
   Gswap4 a;

   a.n = 1;

   // High byte is 1 in little endian order.
   if (a.b[0] == 1)
   {
      _isBigEndian = gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gswapStop
**************************************************************************************************/
grlAPI void gswapStop(void)
{
   // Nothing.
}
