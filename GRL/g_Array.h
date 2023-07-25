/******************************************************************************
file:         G_Array
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrrays.
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

#if !defined(G_ARRAYH)
#define      G_ARRAYH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
type:
******************************************************************************/
typedef struct G_Array
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gn1                     *p;
} G_Array;

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_ArrayCreate(              TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, IS_NULL_ENDING) (G_Array *) gleakCreate((Gp *) g_ArrayCreate_(              gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING), (IS_NULL_ENDING)), gsizeof(G_Array))
#define g_ArrayCreateContent(ARRAY, TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, IS_NULL_ENDING)                                g_ArrayCreateContent_(ARRAY, gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING), (IS_NULL_ENDING))
//lint -restore

grlAPI Gb          g_ArrayAdd(            G_Array       * const a,                     Gp const * const value);
grlAPI Gb          g_ArrayAddAt(          G_Array       * const a, Gindex const index, Gp const * const value);
grlAPI Gb          g_ArrayAddBegin(       G_Array       * const a,                     Gp const * const value);
grlAPI Gb          g_ArrayAddEnd(         G_Array       * const a,                     Gp const * const value);

grlAPI Gb          g_ArrayClear(          G_Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          g_ArrayCopy(           G_Array       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          g_ArrayCopyFrom(       G_Array       * const aDst, Gindex const indexDst, G_Array const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI G_Array    *g_ArrayCreate_(                                 Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing, Gb const isNullEnding);
grlAPI Gb          g_ArrayCreateContent_( G_Array       * const a, Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing, Gb const isNullEnding);

grlAPI void        g_ArrayDestroy(        G_Array       * const a);
grlAPI void        g_ArrayDestroyContent( G_Array const * const a);

grlAPI Gb          g_ArrayErase(          G_Array       * const a, Gp const * const value);
grlAPI Gb          g_ArrayEraseAt(        G_Array       * const a, Gcount const count, Gindex const index);
grlAPI void        g_ArrayEraseBegin(     G_Array       * const a);
grlAPI void        g_ArrayEraseEnd(       G_Array       * const a);

grlAPI Gindex      g_ArrayFind(           G_Array const * const a, Gp const * const value);
grlAPI void        g_ArrayFlush(          G_Array       * const a);
grlAPI Gb          g_ArrayForEach(        G_Array const * const a, GrlForEachFunc const func);

grlAPI Gp         *g_ArrayGet(            G_Array const * const a);
grlAPI Gp         *g_ArrayGetAt(          G_Array const * const a, Gindex const index);
grlAPI Gp         *g_ArrayGetBegin(       G_Array const * const a);
grlAPI Gcount      g_ArrayGetCount(       G_Array const * const a);
grlAPI Gp         *g_ArrayGetEnd(         G_Array const * const a);
grlAPI Gsize       g_ArrayGetSize(        G_Array const * const a);

grlAPI Gb          g_ArraySetCount(       G_Array       * const a, Gcount const value);
grlAPI Gb          g_ArraySort(           G_Array       * const a);
grlAPI Gb          g_ArraySwap(           G_Array       * const a, Gindex const indexA, Gindex const indexB);

grlAPI Gb          g_ArrayUpdateAt(       G_Array       * const a, Gindex const index, Gp const * const value);

       Gcount      g_ArrayVectorSize(     Gb const isVectorSizing, Gcount const size);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
