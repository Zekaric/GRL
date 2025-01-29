/**************************************************************************************************
file:       gvec2
author:     Robbert de Groot
copyright:  2001-2009, Robbert de Groot

description:
Functions based on using a 2D point.
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) !!!!YEAR!!!!, Robbert de Groot
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
func: gvec2Distance
**************************************************************************************************/
grlAPI Gr gvec2Distances(const Gvec2s * const pa, const Gvec2s * const pb)
{
   Gvec2s diff;
   Gr     result;

   genter;

   gvec2Minuss(pa, pb, &diff);

   result = gvec2Lengths(&diff);

   greturn result;
}

grlAPI Gr gvec2Distance(const Gvec2 * const pa, const Gvec2 * const pb)
{
   Gvec2 diff;
   Gr    result;

   genter;

   gvec2Minus(pa, pb, &diff);

   result = gvec2Length(&diff);

   greturn result;
}

/**************************************************************************************************
func: gvec2Length
**************************************************************************************************/
grlAPI Gr gvec2Lengths(const Gvec2s * const p)
{
   Gr result;

   genter;

   result = sqrt(
      ((Gr8) p->a) * ((Gr8) p->a) + 
      ((Gr8) p->b) * ((Gr8) p->b));

   greturn result;
}

grlAPI Gr gvec2Length(const Gvec2 * const p)
{
   Gr result;

   genter;
   
   result = sqrt(p->a * p->a + p->b * p->b);

   greturn result;
}

/**************************************************************************************************
func: gvec2Minus
**************************************************************************************************/
grlAPI void gvec2Minuss(const Gvec2s * const pa, const Gvec2s * const pb, Gvec2s * const result)
{
   genter;
   result->a = pa->a - pb->a;
   result->b = pa->b - pb->b;
   greturn;
}

grlAPI void gvec2Minus(const Gvec2 * const pa, const Gvec2 * const pb, Gvec2 * const result)
{
   genter;
   result->a = pa->a - pb->a;
   result->b = pa->b - pb->b;
   greturn;
}

/**************************************************************************************************
func: gvec2Normalize
**************************************************************************************************/
grlAPI void gvec2Normalizes(const Gvec2s * const p, Gvec2s * const result)
{
   Gr value;

   genter;

   value = gvec2Lengths(p);

   result->a = (Gr4) (p->a / value);
   result->b = (Gr4) (p->b / value);

   greturn;
}

grlAPI void gvec2Normalize(const Gvec2 * const p, Gvec2 * const result)
{
   Gr value;

   genter;

   value = gvec2Length(p);

   result->a = p->a / value;
   result->b = p->b / value;

   greturn;
}

/**************************************************************************************************
func: gvec2Plus
**************************************************************************************************/
grlAPI void gvec2Pluss(const Gvec2s * const pa, const Gvec2s * const pb, Gvec2s * const result)
{
   genter;

   result->a = pa->a + pb->a;
   result->b = pa->b + pb->b;

   greturn;
}

grlAPI void gvec2Plus(const Gvec2 * const pa, const Gvec2 * const pb, Gvec2 * const result)
{
   genter;

   result->a = pa->a + pb->a;
   result->b = pa->b + pb->b;

   greturn;
}

/**************************************************************************************************
func: gvec2Scale
**************************************************************************************************/
grlAPI void gvec2Scales(const Gvec2s * const p, const Gr value, Gvec2s * const result)
{
   genter;

   result->a = (Gr4) (p->a * value);
   result->b = (Gr4) (p->b * value);

   greturn;
}

grlAPI void gvec2Scale(const Gvec2 * const p, const Gr value, Gvec2 * const result)
{
   genter;

   result->a = p->a * value;
   result->b = p->b * value;

   greturn;
}
