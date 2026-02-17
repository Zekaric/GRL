/**************************************************************************************************
file:         GkvArray
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
The base for a key value dynamic arrrays.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2011, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gkv                     *p;
} GkvArray;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gkvArrayCloc(              TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    gleakClocType(gkvArrayCloc_(             (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), GkvArrayKey)
#define gkvArrayClocContent(ARRAY, TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                  gkvArrayClocContent(ARRAY, (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))

grlAPI Gb          gkvArrayAdd(           GkvArray       * const a,                     Gk const * const key, Gv const value);
grlAPI Gb          gkvArrayAddAt(         GkvArray       * const a, Gindex const index, Gk const * const key, Gv const value);
grlAPI Gb          gkvArrayAddBegin(      GkvArray       * const a,                     Gk const * const key, Gv const value);
grlAPI Gb          gkvArrayAddEnd(        GkvArray       * const a,                     Gk const * const key, Gv const value);

grlAPI Gb          gkvArrayClear(         GkvArray       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gkvArrayCopy(          GkvArray       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gkvArrayCopyFrom(      GkvArray       * const aDst, Gindex const indexDst, GkvArray const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI GkvArray   *gkvArrayCloc_(                                   Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          gkvArrayClocContent_(  GkvArray       * const a, Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);

grlAPI void        gkvArrayDloc(          GkvArray       * const a);
grlAPI void        gkvArrayDlocContent(   GkvArray const * const a);

grlAPI Gb          gkvArrayErase(         GkvArray       * const a, Gk const * const key);
grlAPI Gb          gkvArrayEraseAt(       GkvArray       * const a, Gcount const count, Gindex const index);
grlAPI void        gkvArrayEraseBegin(    GkvArray       * const a);
grlAPI void        gkvArrayEraseEnd(      GkvArray       * const a);

grlAPI Gindex      gkvArrayFind(          GkvArray const * const a, Gk const * const key);
grlAPI void        gkvArrayFlush(         GkvArray       * const a);
grlAPI Gb          gkvArrayForEach(       GkvArray const * const a, GrlForEachKeyFunc const func);
grlAPI Gb          gkvArrayForEachDown(   GkvArray const * const a, GrlForEachKeyFunc const func);

grlAPI Gkv const  *gkvArrayGet(           GkvArray const * const a);
grlAPI Gv          gkvArrayGetAt(         GkvArray const * const a, Gindex const index);
grlAPI Gk const   *gkvArrayGetAtKey(      GkvArray const * const a, Gindex const index);
grlAPI Gv          gkvArrayGetBegin(      GkvArray const * const a);
grlAPI Gk const   *gkvArrayGetBeginKey(   GkvArray const * const a);
grlAPI Gcount      gkvArrayGetCount(      GkvArray const * const a);
grlAPI Gv          gkvArrayGetEnd(        GkvArray const * const a);
grlAPI Gk const   *gkvArrayGetEndKey(     GkvArray const * const a);

grlAPI Gb          gkvArraySetCount(      GkvArray       * const a, Gcount const value);
grlAPI Gb          gkvArraySort(          GkvArray       * const a);
grlAPI Gb          gkvArraySwap(          GkvArray       * const a, Gindex const indexA, Gindex const indexB);

grlAPI Gb          gkvArrayUpdateAt(      GkvArray       * const a, Gindex const index, Gv const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
