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

#if !defined(GVEC3H)
#define      GVEC3H

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   Gn4    a,
          b,
          c;
} Gvec3n;

typedef struct
{
   Gr4    a,
          b,
          c;
} Gvec3s;

typedef struct
{
   Gr     a,
          b,
          c;
} Gvec3;

/**************************************************************************************************
function:
**************************************************************************************************/
grlAPI void  gvec3Cross(         Gvec3 const * const pa, Gvec3 const * const pb, Gvec3 * const result);
grlAPI Gr    gvec3Distance(      Gvec3 const * const pa, Gvec3 const * const pb);
grlAPI Gr    gvec3Dot(           Gvec3 const * const pa, Gvec3 const * const pb);
grlAPI Gb    gvec3IsCoincident(  Gvec3 const * const pa, Gvec3 const * const pb, Gr const tolerance);
grlAPI Gr    gvec3Length(        Gvec3 const * const p);
grlAPI void  gvec3Minus(         Gvec3 const * const pa, Gvec3 const * const pb, Gvec3 * const result);
grlAPI void  gvec3Normalize(     Gvec3 const * const p,                          Gvec3 * const result);
grlAPI void  gvec3Plus(          Gvec3 const * const pa, Gvec3 const * const pb, Gvec3 * const result);
grlAPI void  gvec3Right(         Gvec3 const * const p,                          Gvec3 * const right);
grlAPI void  gvec3Scale(         Gvec3 const * const p,  Gr const value,         Gvec3 * const result);
grlAPI Gvec3 gvec3Zero(          void);

// single precision (depricated)
grlAPI void  gvec3Crosss(        Gvec3s const * const pa, Gvec3s const * const pb, Gvec3s * const result);
grlAPI Gr    gvec3Distances(     Gvec3s const * const pa, Gvec3s const * const pb);
grlAPI Gr    gvec3Dots(          Gvec3s const * const pa, Gvec3s const * const pb);
grlAPI Gb    gvec3IsCoincidents( Gvec3s const * const pa, Gvec3s const * const pb, Gr const tolerance);
grlAPI Gr    gvec3Lengths(       Gvec3s const * const p);
grlAPI void  gvec3Minuss(        Gvec3s const * const pa, Gvec3s const * const pb, Gvec3s * const result);
grlAPI void  gvec3Normalizes(    Gvec3s const * const p,                           Gvec3s * const result);
grlAPI void  gvec3Pluss(         Gvec3s const * const pa, Gvec3s const * const pb, Gvec3s * const result);
grlAPI void  gvec3Rights(        Gvec3s const * const p,                           Gvec3s * const right);
grlAPI void  gvec3Scales(        Gvec3s const * const p,  Gr const value,          Gvec3s * const result);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
