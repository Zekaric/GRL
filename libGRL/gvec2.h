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

#pragma once

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
   Gr4    a,
          b;
} Gvec2s;

typedef struct
{
   Gr     a,
          b;
} Gvec2;

/**************************************************************************************************
Types
**************************************************************************************************/
grlAPI Gr    gvec2Distance( Gvec2 const * const pa, Gvec2 const * const pb);
grlAPI Gr    gvec2Length(   Gvec2 const * const p);
grlAPI void  gvec2Minus(    Gvec2 const * const pa, Gvec2 const * const pb, Gvec2 * const result);
grlAPI void  gvec2Normalize(Gvec2 const * const p,                          Gvec2 * const result);
grlAPI void  gvec2Plus(     Gvec2 const * const pa, Gvec2 const * const pb, Gvec2 * const result);
grlAPI void  gvec2Scale(    Gvec2 const * const p,  Gr const value,         Gvec2 * const result);

// single precision (depricated)
grlAPI Gr    gvec2Distances( Gvec2s const * const pa, Gvec2s const * const pb);
grlAPI Gr    gvec2Lengths(   Gvec2s const * const p);
grlAPI void  gvec2Minuss(    Gvec2s const * const pa, Gvec2s const * const pb, Gvec2s * const result);
grlAPI void  gvec2Normalizes(Gvec2s const * const p,  Gvec2s * const result);
grlAPI void  gvec2Pluss(     Gvec2s const * const pa, Gvec2s const * const pb, Gvec2s * const result);
grlAPI void  gvec2Scales(    Gvec2s const * const p,  Gr const value,          Gvec2s * const result);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
