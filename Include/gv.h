/******************************************************************************
file:       gv
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
A simple array.  A simple one dimensional array of generic data
pointers, ints or naturals.
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

#if !defined(GVALUEH)
#define      GVALUEH

/******************************************************************************
const:
******************************************************************************/
#define gvTYPE_I "Gv:I"
#define gvTYPE_N "Gv:N"
#define gvTYPE_P "Gv:P"
#define gvTYPE_R "Gv:R"
#define gvTYPE_V "Gv"

// type defined in gconst.h

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9026
grlAPI Gcompare    gpCompare(       Gp const * const valueA, Gp const * const valueB);

// gv is a simple light data holder.  Use carfully.
grlAPI Gcompare    gvCompareI(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareN(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareP(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareR(      Gv const * const valueA, Gv const * const valueB);

grlAPI Gv         *gvCreate(        void);
grlAPI Gb          gvCreateContent( Gv       * const v);

grlAPI void        gvDestroy(       Gv       * const v);
grlAPI void        gvDestroyContent(Gv       * const v);

grlAPI Gv          gvFromI(         Gip  const value);
grlAPI Gv          gvFromN(         Gnp  const value);
grlAPI Gv          gvFromP(         Gp * const value);
grlAPI Gv          gvFromR(         Grp  const value);
grlAPI Gv          gvFromS(         Gs * const value);

grlAPI Gip         gvGetI(          Gv const * const v);
grlAPI Gnp         gvGetN(          Gv const * const v);
grlAPI Gp         *gvGetP(          Gv const * const v);
grlAPI Grp         gvGetR(          Gv const * const v);
grlAPI Gs         *gvGetS(          Gv const * const v);

grlAPI GhashN      gvHash(          Gv const * const value);
grlAPI GhashN      gvHashS(         Gv const * const value);

grlAPI Gb          gvSetI(          Gv       * const v, Gip  const value);
grlAPI Gb          gvSetN(          Gv       * const v, Gnp  const value);
grlAPI Gb          gvSetP(          Gv       * const v, Gp * const value);
grlAPI Gb          gvSetR(          Gv       * const v, Grp  const value);
grlAPI Gb          gvSetS(          Gv       * const v, Gs * const value);

// This is a helper for g[type]ForEachP() functions
grlAPI void        _GvEachP(        Gv *v, GrlForEachFunc const func);

//lint -restore

`container Gv

#endif
