/**************************************************************************************************
file:         G_ArrayKey
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrrays.
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

#if !defined(G_ARRAYKEYH)
#define      G_ARRAYKEYH

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
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gn1                     *p;
} G_ArrayKey;

/**************************************************************************************************
prototype:
**************************************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_ArrayKeyCloc(              TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING) (G_ArrayKey *) gleakCloc((Gp *) g_ArrayKeyCloc_(             gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), gsizeof(G_ArrayKeyKey))
#define g_ArrayKeyClocContent(ARRAY, TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                                 g_ArrayKeyClocContent(ARRAY, gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))
//lint -restore

grlAPI Gb          g_ArrayKeyAdd(            G_ArrayKey       * const a,                     Gkey const * const key, Gp const * const value);
grlAPI Gb          g_ArrayKeyAddAt(          G_ArrayKey       * const a, Gindex const index, Gkey const * const key, Gp const * const value);
grlAPI Gb          g_ArrayKeyAddBegin(       G_ArrayKey       * const a,                     Gkey const * const key, Gp const * const value);
grlAPI Gb          g_ArrayKeyAddEnd(         G_ArrayKey       * const a,                     Gkey const * const key, Gp const * const value);

grlAPI Gb          g_ArrayKeyClear(          G_ArrayKey       * const a, Gcount const count, Gindex const index);
grlAPI Gb          g_ArrayKeyCopy(           G_ArrayKey       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          g_ArrayKeyCopyFrom(       G_ArrayKey       * const aDst, Gindex const indexDst, G_ArrayKey const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI G_ArrayKey *g_ArrayKeyCloc_(                                      Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          g_ArrayKeyClocContent_(   G_ArrayKey       * const a, Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing);

grlAPI void        g_ArrayKeyDloc(           G_ArrayKey       * const a);
grlAPI void        g_ArrayKeyDlocContent(    G_ArrayKey const * const a);

grlAPI Gb          g_ArrayKeyErase(          G_ArrayKey       * const a, Gkey const * const key);
grlAPI Gb          g_ArrayKeyEraseAt(        G_ArrayKey       * const a, Gcount const count, Gindex const index);
grlAPI void        g_ArrayKeyEraseBegin(     G_ArrayKey       * const a);
grlAPI void        g_ArrayKeyEraseEnd(       G_ArrayKey       * const a);

grlAPI Gindex      g_ArrayKeyFind(           G_ArrayKey const * const a, Gkey const * const key);
grlAPI void        g_ArrayKeyFlush(          G_ArrayKey       * const a);
grlAPI Gb          g_ArrayKeyForEach(        G_ArrayKey const * const a, GrlForEachKeyFunc const func);

grlAPI Gp         *g_ArrayKeyGet(            G_ArrayKey const * const a);
grlAPI Gp         *g_ArrayKeyGetAt(          G_ArrayKey const * const a, Gindex const index);
grlAPI Gkey const *g_ArrayKeyGetAtKey(       G_ArrayKey const * const a, Gindex const index);
grlAPI Gp         *g_ArrayKeyGetBegin(       G_ArrayKey const * const a);
grlAPI Gkey const *g_ArrayKeyGetBeginKey(    G_ArrayKey const * const a);
grlAPI Gcount      g_ArrayKeyGetCount(       G_ArrayKey const * const a);
grlAPI Gp         *g_ArrayKeyGetEnd(         G_ArrayKey const * const a);
grlAPI Gkey const *g_ArrayKeyGetEndKey(      G_ArrayKey const * const a);
grlAPI Gsize       g_ArrayKeyGetSize(        G_ArrayKey const * const a);

grlAPI Gb          g_ArrayKeySetCount(       G_ArrayKey       * const a, Gcount const value);
grlAPI Gb          g_ArrayKeySort(           G_ArrayKey       * const a);
grlAPI Gb          g_ArrayKeySwap(           G_ArrayKey       * const a, Gindex const indexA, Gindex const indexB);

grlAPI Gb          g_ArrayKeyUpdateAt(       G_ArrayKey       * const a, Gindex const index, Gp const * const value);
grlAPI Gb          g_ArrayKeyUpdateAtKey(    G_ArrayKey       * const a, Gindex const index, Gkey const * const key);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
#pragma once
