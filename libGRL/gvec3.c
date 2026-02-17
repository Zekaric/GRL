/**************************************************************************************************
file:       Gvec3
author:     Robbert de Groot
copyright:  2001-2009, Robbert de Groot

description:
Functions based on using a 3D point.
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
#include "pch.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gvec3Cross
**************************************************************************************************/
grlAPI void gvec3Crosss(const Gvec3s * const pa, const Gvec3s * const pb, Gvec3s * const result)
{
   Gvec3s ptemp;

   genter;

   ptemp.a = ((pa->b * pb->c) - (pa->c * pb->b));
   ptemp.b = ((pa->c * pb->a) - (pa->a * pb->c));
   ptemp.c = ((pa->a * pb->b) - (pa->b * pb->a));

   *result = ptemp;
   greturn;
}

grlAPI void gvec3Cross(const Gvec3 * const pa, const Gvec3 * const pb, Gvec3 * const result)
{
   Gvec3 ptemp;

   genter;

   ptemp.a = ((pa->b * pb->c) - (pa->c * pb->b));
   ptemp.b = ((pa->c * pb->a) - (pa->a * pb->c));
   ptemp.c = ((pa->a * pb->b) - (pa->b * pb->a));

   *result = ptemp;
   greturn;
}

/**************************************************************************************************
func: gvec3Distance
**************************************************************************************************/
grlAPI Gr gvec3Distances(const Gvec3s * const pa, const Gvec3s * const pb)
{
   Gvec3s diff;
   Gr     result;

   genter;

   gvec3Minuss(pa, pb, &diff);

   result = gvec3Lengths(&diff);

   greturn result;
}

grlAPI Gr gvec3Distance(const Gvec3 * const pa, const Gvec3 * const pb)
{
   Gvec3 diff;
   Gr    result;

   genter;

   gvec3Minus(pa, pb, &diff);

   result = gvec3Length(&diff);

   greturn result;
}

/**************************************************************************************************
func: gvec3Dot
**************************************************************************************************/
grlAPI Gr gvec3Dots(const Gvec3s * const pa, const Gvec3s * const pb)
{
   Gr result;

   genter;

   result = (Gr)(pa->a * pb->a + pa->b * pb->b + pa->c * pb->c); 

   greturn result;
}

grlAPI Gr gvec3Dot(const Gvec3 * const pa, const Gvec3 * const pb)
{
   Gr result;

   genter;

   result = (pa->a * pb->a + pa->b * pb->b + pa->c * pb->c);

   greturn result;
}

/**************************************************************************************************
func: gvec3IsCoincident
**************************************************************************************************/
grlAPI Gb gvec3IsCoincidents(Gvec3s const * const pa, Gvec3s const * const pb, Gr const tolerance)
{
   Gr distance;

   genter;

   distance = gvec3Distances(pa, pb);

   greturnTrueIf(distance < tolerance);

   greturn gbFALSE;
}

grlAPI Gb gvec3IsCoincident(Gvec3 const * const pa, Gvec3 const * const pb, Gr const tolerance)
{
   Gr distance;

   genter;

   distance = gvec3Distance(pa, pb);

   greturnTrueIf(distance < tolerance);

   greturn gbFALSE;
}

/**************************************************************************************************
func: gvec3Lengths(s)
**************************************************************************************************/
grlAPI Gr gvec3Lengths(const Gvec3s * const p)
{
   Gr result;

   genter;

   result = sqrt(
      ((Gr8) p->a) * ((Gr8) p->a) +
      ((Gr8) p->b) * ((Gr8) p->b) +
      ((Gr8) p->c) * ((Gr8) p->c));

   greturn result;
}

grlAPI Gr gvec3Length(const Gvec3 * const p)
{
   Gr result;

   genter;
   
   result = sqrt(p->a * p->a + p->b * p->b + p->c * p->c);

   greturn result;
}

/**************************************************************************************************
func: gvec3Minus
**************************************************************************************************/
grlAPI void gvec3Minuss(const Gvec3s * const pa, const Gvec3s * const pb, Gvec3s * const result)
{
   genter;
   result->a = pa->a - pb->a;
   result->b = pa->b - pb->b;
   result->c = pa->c - pb->c;
   greturn;
}

grlAPI void gvec3Minus(const Gvec3 * const pa, const Gvec3 * const pb, Gvec3 * const result)
{
   genter;
   result->a = pa->a - pb->a;
   result->b = pa->b - pb->b;
   result->c = pa->c - pb->c;
   greturn;
}

/**************************************************************************************************
func: gvec3Normalize
**************************************************************************************************/
grlAPI void gvec3Normalizes(const Gvec3s * const p, Gvec3s * const result)
{
   Gr value;

   genter;

   value = gvec3Lengths(p);

   result->a = (Gr4) (p->a / value);
   result->b = (Gr4) (p->b / value);
   result->c = (Gr4) (p->c / value);
   greturn;
}

grlAPI void gvec3Normalize(const Gvec3 * const p, Gvec3 * const result)
{
   Gr value;

   genter;

   value = gvec3Length(p);

   result->a = p->a / value;
   result->b = p->b / value;
   result->c = p->c / value;
   greturn;
}

/**************************************************************************************************
func: gvec3Plus
**************************************************************************************************/
grlAPI void gvec3Pluss(const Gvec3s * const pa, const Gvec3s * const pb, Gvec3s * const result)
{
   genter;
   result->a = pa->a + pb->a;
   result->b = pa->b + pb->b;
   result->c = pa->c + pb->c;
   greturn;
}

grlAPI void gvec3Plus(const Gvec3 * const pa, const Gvec3 * const pb, Gvec3 * const result)
{
   genter;
   result->a = pa->a + pb->a;
   result->b = pa->b + pb->b;
   result->c = pa->c + pb->c;
   greturn;
}

/**************************************************************************************************
func: gvec3Right
**************************************************************************************************/
grlAPI void gvec3Rights(const Gvec3s * const p, Gvec3s * const right)
{
   genter;
   if (gABS(p->a) + gABS(p->b) < gmathFLOAT_TOLERANCE) 
   {
      right->a    =
         right->b =
         right->c = 0.f;
      greturn;
   }

   right->a =  p->b;
   right->b = -p->a;
   right->c =  0.f;

   gvec3Normalizes(right, right);
   greturn;
}

grlAPI void gvec3Right(const Gvec3 * const p, Gvec3 * const right)
{
   genter;
   if (gABS(p->a) + gABS(p->b) < gmathDOUBLE_TOLERANCE) 
   {
      right->a    =
         right->b =
         right->c = 0.;
      greturn;
   }

   right->a =  p->b;
   right->b = -p->a;
   right->c =  0.;

   gvec3Normalize(right, right);
   greturn;
}

/**************************************************************************************************
func: gvec3Scale
**************************************************************************************************/
grlAPI void gvec3Scales(const Gvec3s * const p, const Gr value, Gvec3s * const result)
{
   genter;
   result->a = (Gr4) (p->a * value);
   result->b = (Gr4) (p->b * value);
   result->c = (Gr4) (p->c * value);
   greturn;
}

grlAPI void gvec3Scale(const Gvec3 * const p, const Gr value, Gvec3 * const result)
{
   genter;
   result->a = p->a * value;
   result->b = p->b * value;
   result->c = p->c * value;
   greturn;
}

/**************************************************************************************************
func: gvec3Zero
**************************************************************************************************/
grlAPI Gvec3 gvec3Zero(void)
{
   static Gvec3 zero = {0,0,0};

   return zero;
}
