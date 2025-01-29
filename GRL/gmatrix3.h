/**************************************************************************************************
file:       gmatrix3
author:     Robbert de Groot
copyright:  2001-2009, Robbert de Groot

description:
Functions for 4x4 matrices.
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

#if !defined(GMATRIX3H)
#define      GMATRIX3H

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
   Gr value[16];
} Gmatrix3;

/**************************************************************************************************
Functions
**************************************************************************************************/
grlAPI void gmatrix3Clean(                         Gmatrix3 const * const mi,  Gmatrix3 * const mo);
grlAPI void gmatrix3Copy(                          Gmatrix3 const * const src, Gmatrix3 * const dst);

grlAPI void gmatrix3Minus(                         Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m);

grlAPI void gmatrix3Negate(                        Gmatrix3 const * const m1, Gmatrix3 * const m);

grlAPI void gmatrix3Plus(                          Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m);
grlAPI void gmatrix3Product(                       Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m);
grlAPI void gmatrix3ProductGvec3(                  Gmatrix3 const * const m, Gvec3 const * const in, Gvec3 * const out);
grlAPI void gmatrix3ProductGvec3List(              Gmatrix3 const * const m, Gcount const pcount, Gvec3 const * const in, Gvec3 * const out);

grlAPI void gmatrix3SetFromUnitVectorsLocalToWorld(Gmatrix3       * const m, Gvec3 const * const x, Gvec3 const * const y, Gvec3 const * const z);
grlAPI void gmatrix3SetFromUnitVectorsWorldToLocal(Gmatrix3       * const m, Gvec3 const * const x, Gvec3 const * const y, Gvec3 const * const z);
grlAPI void gmatrix3SetIdentity(                   Gmatrix3       * const m);
grlAPI void gmatrix3SetRotation(                   Gmatrix3       * const m, GmathAxis const axis, Gr const angle);
grlAPI void gmatrix3SetScale(                      Gmatrix3       * const m, Gr const x, Gr const y, Gr const z);
grlAPI void gmatrix3SetTranslation(                Gmatrix3       * const m, Gr const x, Gr const y, Gr const z);

grlAPI void gmatrix3Transpose(                     Gmatrix3 const * const in, Gmatrix3 * const out);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
