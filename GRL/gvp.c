/******************************************************************************
file:       Gvp
author:     Robbert de Groot
copyright:  2020, Robbert de Groot
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

#include "precompiled.h"

/******************************************************************************
global
function
******************************************************************************/
/******************************************************************************
func: gvpCompareI
******************************************************************************/
grlAPI Gcompare gvpCompareI(Gvp const * const va, Gvp const * const vb)
{
   genter;
   greturnIf(va->i < vb->i, gcompareLESS_THAN);
   greturnIf(va->i > vb->i, gcompareGREATER_THAN);
   greturn                  gcompareEQUAL;
}

/******************************************************************************
func: gvpCompareN
******************************************************************************/
grlAPI Gcompare gvpCompareN(Gvp const * const va, Gvp const * const vb)
{
   genter;
   greturnIf(va->n < vb->n, gcompareLESS_THAN);
   greturnIf(va->n > vb->n, gcompareGREATER_THAN);
   greturn                  gcompareEQUAL;
}

/******************************************************************************
func: gvpCompareR
******************************************************************************/
grlAPI Gcompare gvpCompareR(Gvp const * const va, Gvp const * const vb)
{
   genter;
   greturnIf(va->r < vb->r, gcompareLESS_THAN);
   greturnIf(va->r > vb->r, gcompareGREATER_THAN);
   greturn                  gcompareEQUAL;
}

/******************************************************************************
func: gvpCompareS
******************************************************************************/
grlAPI Gcompare gvpCompareS(Gvp const * const va, Gvp const * const vb)
{
   genter;
   greturn gsCompareBase(va->s, vb->s);
}

/******************************************************************************
func: gvpHash
******************************************************************************/
grlAPI GhashN gvpHash(Gvp const * const v)
{
   genter;
   greturn (GhashN) (v->n & GhashNMAX);
}
