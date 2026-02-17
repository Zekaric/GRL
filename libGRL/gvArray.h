/**************************************************************************************************
file:         GvArray
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrays of pointers.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

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
typedef struct GvArray
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv                      *p;
} GvArray;

typedef struct Gv1Array
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv1                     *p;
} Gv1Array;

typedef struct Gv2Array
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv2                     *p;
} Gv2Array;

typedef struct Gv4Array
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv4                     *p;
} Gv4Array;

typedef GvArray Gv8Array;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gvArrayCloc(               TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)   gleakClocType(gvArrayCloc_(                 (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), GvArray)
#define gvArrayClocContent( ARRAY, TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                 gvArrayClocContent_(   ARRAY, (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))
#define gv1ArrayCloc(              TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)   gleakClocType(gv1ArrayCloc_(                (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), Gv1Array)
#define gv1ArrayClocContent(ARRAY, TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                 gv1ArrayClocContent_(  ARRAY, (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))
#define gv2ArrayCloc(              TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)   gleakClocType(gv2ArrayCloc_(                (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), Gv2Array)
#define gv2ArrayClocContent(ARRAY, TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                 gv2ArrayClocContent_(  ARRAY, (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))
#define gv4ArrayCloc(              TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)   gleakClocType(gv4ArrayCloc_(                (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING)), Gv4Array)
#define gv4ArrayClocContent(ARRAY, TYPE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                 gv4ArrayClocContent_(  ARRAY, (Char *) TYPE, (OPTIONAL_COMPARE_FUNC), (IS_VECTOR_SIZING))

grlAPI Gcount      gvArrayVectorSize(      Gb const isVectorSizing, Gcount const size);

grlAPI Gb          gvArrayAdd(             GvArray        * const a,                     Gv const value);
grlAPI Gb          gvArrayAddAt(           GvArray        * const a, Gindex const index, Gv const value);
grlAPI Gb          gvArrayAddBegin(        GvArray        * const a,                     Gv const value);
grlAPI Gb          gvArrayAddEnd(          GvArray        * const a,                     Gv const value);
grlAPI Gb          gvArrayClear(           GvArray        * const a, Gcount const count, Gindex const index);
grlAPI Gb          gvArrayCopy(            GvArray        * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gvArrayCopyFrom(        GvArray        * const aDst, Gindex const indexDst, GvArray const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI GvArray    *gvArrayCloc_(                                     Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          gvArrayClocContent_(    GvArray        * const a, Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI void        gvArrayDloc(            GvArray        * const a);
grlAPI void        gvArrayDlocContent(     GvArray  const * const a);
grlAPI Gb          gvArrayErase(           GvArray        * const a, Gv const value);
grlAPI Gb          gvArrayEraseAt(         GvArray        * const a, Gcount const count, Gindex const index);
grlAPI Gb          gvArrayEraseBegin(      GvArray        * const a, Gcount const count);
grlAPI Gb          gvArrayEraseEnd(        GvArray        * const a, Gcount const count);
grlAPI Gindex      gvArrayFind(            GvArray  const * const a, Gv const value);
grlAPI void        gvArrayFlush(           GvArray        * const a);
grlAPI Gb          gvArrayForEach(         GvArray  const * const a, GrlForEachFunc const func);
grlAPI Gb          gvArrayForEachDown(     GvArray  const * const a, GrlForEachFunc const func);
grlAPI Gv const   *gvArrayGet(             GvArray  const * const a);
grlAPI Gv          gvArrayGetAt(           GvArray  const * const a, Gindex const index);
grlAPI Gv          gvArrayGetBegin(        GvArray  const * const a);
grlAPI Gcount      gvArrayGetCount(        GvArray  const * const a);
grlAPI Gv          gvArrayGetEnd(          GvArray  const * const a);
grlAPI Gb          gvArraySetCount(        GvArray        * const a, Gcount const value);
grlAPI Gb          gvArraySort(            GvArray        * const a);
grlAPI Gb          gvArraySwap(            GvArray        * const a, Gindex const indexA, Gindex const indexB);
grlAPI Gb          gvArrayUpdateAt(        GvArray        * const a, Gindex const index, Gv const value);

grlAPI Gb          gv1ArrayAdd(            Gv1Array       * const a,                     Gv1 const value);
grlAPI Gb          gv1ArrayAddAt(          Gv1Array       * const a, Gindex const index, Gv1 const value);
grlAPI Gb          gv1ArrayAddBegin(       Gv1Array       * const a,                     Gv1 const value);
grlAPI Gb          gv1ArrayAddEnd(         Gv1Array       * const a,                     Gv1 const value);
grlAPI Gb          gv1ArrayClear(          Gv1Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv1ArrayCopy(           Gv1Array       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gv1ArrayCopyFrom(       Gv1Array       * const aDst, Gindex const indexDst, Gv1Array const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI Gv1Array   *gv1ArrayCloc_(                                    Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          gv1ArrayClocContent_(   Gv1Array       * const a, Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI void        gv1ArrayDloc(           Gv1Array       * const a);
grlAPI void        gv1ArrayDlocContent(    Gv1Array const * const a);
grlAPI Gb          gv1ArrayErase(          Gv1Array       * const a, Gv1 const value);
grlAPI Gb          gv1ArrayEraseAt(        Gv1Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv1ArrayEraseBegin(     Gv1Array       * const a, Gcount const count);
grlAPI Gb          gv1ArrayEraseEnd(       Gv1Array       * const a, Gcount const count);
grlAPI Gindex      gv1ArrayFind(           Gv1Array const * const a, Gv1 const value);
grlAPI void        gv1ArrayFlush(          Gv1Array       * const a);
grlAPI Gb          gv1ArrayForEach(        Gv1Array const * const a, GrlForEachFunc const func);
grlAPI Gb          gv1ArrayForEachDown(    Gv1Array const * const a, GrlForEachFunc const func);
grlAPI Gv1 const  *gv1ArrayGet(            Gv1Array const * const a);
grlAPI Gv1         gv1ArrayGetAt(          Gv1Array const * const a, Gindex const index);
grlAPI Gv1         gv1ArrayGetBegin(       Gv1Array const * const a);
grlAPI Gcount      gv1ArrayGetCount(       Gv1Array const * const a);
grlAPI Gv1         gv1ArrayGetEnd(         Gv1Array const * const a);
grlAPI Gb          gv1ArraySetCount(       Gv1Array       * const a, Gcount const value);
grlAPI Gb          gv1ArraySort(           Gv1Array       * const a);
grlAPI Gb          gv1ArraySwap(           Gv1Array       * const a, Gindex const indexA, Gindex const indexB);
grlAPI Gb          gv1ArrayUpdateAt(       Gv1Array       * const a, Gindex const index, Gv1 const value);

grlAPI Gb          gv2ArrayAdd(            Gv2Array       * const a,                     Gv2 const value);
grlAPI Gb          gv2ArrayAddAt(          Gv2Array       * const a, Gindex const index, Gv2 const value);
grlAPI Gb          gv2ArrayAddBegin(       Gv2Array       * const a,                     Gv2 const value);
grlAPI Gb          gv2ArrayAddEnd(         Gv2Array       * const a,                     Gv2 const value);
grlAPI Gb          gv2ArrayClear(          Gv2Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv2ArrayCopy(           Gv2Array       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gv2ArrayCopyFrom(       Gv2Array       * const aDst, Gindex const indexDst, Gv2Array const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI Gv2Array   *gv2ArrayCloc_(                                    Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          gv2ArrayClocContent_(   Gv2Array       * const a, Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI void        gv2ArrayDloc(           Gv2Array       * const a);
grlAPI void        gv2ArrayDlocContent(    Gv2Array const * const a);
grlAPI Gb          gv2ArrayErase(          Gv2Array       * const a, Gv2 const value);
grlAPI Gb          gv2ArrayEraseAt(        Gv2Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv2ArrayEraseBegin(     Gv2Array       * const a, Gcount const count);
grlAPI Gb          gv2ArrayEraseEnd(       Gv2Array       * const a, Gcount const count);
grlAPI Gindex      gv2ArrayFind(           Gv2Array const * const a, Gv2 const value);
grlAPI void        gv2ArrayFlush(          Gv2Array       * const a);
grlAPI Gb          gv2ArrayForEach(        Gv2Array const * const a, GrlForEachFunc const func);
grlAPI Gb          gv2ArrayForEachDown(    Gv2Array const * const a, GrlForEachFunc const func);
grlAPI Gv2 const  *gv2ArrayGet(            Gv2Array const * const a);
grlAPI Gv2         gv2ArrayGetAt(          Gv2Array const * const a, Gindex const index);
grlAPI Gv2         gv2ArrayGetBegin(       Gv2Array const * const a);
grlAPI Gcount      gv2ArrayGetCount(       Gv2Array const * const a);
grlAPI Gv2         gv2ArrayGetEnd(         Gv2Array const * const a);
grlAPI Gb          gv2ArraySetCount(       Gv2Array       * const a, Gcount const value);
grlAPI Gb          gv2ArraySort(           Gv2Array       * const a);
grlAPI Gb          gv2ArraySwap(           Gv2Array       * const a, Gindex const indexA, Gindex const indexB);
grlAPI Gb          gv2ArrayUpdateAt(       Gv2Array       * const a, Gindex const index, Gv2 const value);

grlAPI Gb          gv4ArrayAdd(            Gv4Array       * const a,                     Gv4 const value);
grlAPI Gb          gv4ArrayAddAt(          Gv4Array       * const a, Gindex const index, Gv4 const value);
grlAPI Gb          gv4ArrayAddBegin(       Gv4Array       * const a,                     Gv4 const value);
grlAPI Gb          gv4ArrayAddEnd(         Gv4Array       * const a,                     Gv4 const value);
grlAPI Gb          gv4ArrayClear(          Gv4Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv4ArrayCopy(           Gv4Array       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gv4ArrayCopyFrom(       Gv4Array       * const aDst, Gindex const indexDst, Gv4Array const * const aSrc, Gcount const count, Gindex const indexSrc);
grlAPI Gv4Array   *gv4ArrayCloc_(                                    Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI Gb          gv4ArrayClocContent_(   Gv4Array       * const a, Char const * const typeName, GrlCompareFunc const compareFunc, Gb const isVectorSizing);
grlAPI void        gv4ArrayDloc(           Gv4Array       * const a);
grlAPI void        gv4ArrayDlocContent(    Gv4Array const * const a);
grlAPI Gb          gv4ArrayErase(          Gv4Array       * const a, Gv4 const value);
grlAPI Gb          gv4ArrayEraseAt(        Gv4Array       * const a, Gcount const count, Gindex const index);
grlAPI Gb          gv4ArrayEraseBegin(     Gv4Array       * const a, Gcount const count);
grlAPI Gb          gv4ArrayEraseEnd(       Gv4Array       * const a, Gcount const count);
grlAPI Gindex      gv4ArrayFind(           Gv4Array const * const a, Gv4 const value);
grlAPI void        gv4ArrayFlush(          Gv4Array       * const a);
grlAPI Gb          gv4ArrayForEach(        Gv4Array const * const a, GrlForEachFunc const func);
grlAPI Gb          gv4ArrayForEachDown(    Gv4Array const * const a, GrlForEachFunc const func);
grlAPI Gv4 const  *gv4ArrayGet(            Gv4Array const * const a);
grlAPI Gv4         gv4ArrayGetAt(          Gv4Array const * const a, Gindex const index);
grlAPI Gv4         gv4ArrayGetBegin(       Gv4Array const * const a);
grlAPI Gcount      gv4ArrayGetCount(       Gv4Array const * const a);
grlAPI Gv4         gv4ArrayGetEnd(         Gv4Array const * const a);
grlAPI Gb          gv4ArraySetCount(       Gv4Array       * const a, Gcount const value);
grlAPI Gb          gv4ArraySort(           Gv4Array       * const a);
grlAPI Gb          gv4ArraySwap(           Gv4Array       * const a, Gindex const indexA, Gindex const indexB);
grlAPI Gb          gv4ArrayUpdateAt(       Gv4Array       * const a, Gindex const index, Gv4 const value);

#define gv8ArrayAdd           gvArrayAdd
#define gv8ArrayAddAt         gvArrayAddAt
#define gv8ArrayAddBegin      gvArrayAddBegin
#define gv8ArrayAddEnd        gvArrayAddEnd
#define gv8ArrayClear         gvArrayClear
#define gv8ArrayCopy          gvArrayCopy
#define gv8ArrayCopyFrom      gvArrayCopyFrom
#define gv8ArrayCloc_         gvArrayCloc_
#define gv8ArrayClocContent_  gvArrayClocContent_
#define gv8ArrayDloc          gvArrayDloc
#define gv8ArrayDlocContent   gvArrayDlocContent
#define gv8ArrayErase         gvArrayErase
#define gv8ArrayEraseAt       gvArrayEraseAt
#define gv8ArrayEraseBegin    gvArrayEraseBegin
#define gv8ArrayEraseEnd      gvArrayEraseEnd
#define gv8ArrayFind          gvArrayFind
#define gv8ArrayFlush         gvArrayFlush
#define gv8ArrayForEach       gvArrayForEach
#define gv8ArrayForEachDown   gvArrayForEachDown
#define gv8ArrayGet           gvArrayGet
#define gv8ArrayGetAt         gvArrayGetAt
#define gv8ArrayGetBegin      gvArrayGetBegin
#define gv8ArrayGetCount      gvArrayGetCount
#define gv8ArrayGetEnd        gvArrayGetEnd
#define gv8ArraySetCount      gvArraySetCount
#define gv8ArraySort          gvArraySort
#define gv8ArraySwap          gvArraySwap
#define gv8ArrayUpdateAt      gvArrayUpdateAt

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
