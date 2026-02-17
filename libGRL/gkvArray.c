/**************************************************************************************************
file:         GkvArray
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
dynamic array.
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gindex _BinarySearch(GkvArray const * const a, Gk const * const value, Gb const findLocation);
static Gindex _LinearSearch(GkvArray const * const a, Gk const * const value, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gkvArrayAdd
**************************************************************************************************/
grlAPI Gb gkvArrayAdd(GkvArray * const a, Gk const * const key, Gv const value)
{
   Gindex index;
   Gb     result;

   genter;

   greturnFalseIf(
      !a     ||
      !key   ||
      !a->isSorted);

   // Find the location to put the new value in.
   index  = _BinarySearch(a, key, gbTRUE);

   result = gkvArrayAddAt(a, gABS(index), key, value);

   // AddAt turns this off but sort order has not been violated so turn it back on.
   a->isSorted = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: gkvArrayAddAt
**************************************************************************************************/
grlAPI Gb gkvArrayAddAt(GkvArray * const a, Gindex const index, Gk const * const key,
   Gv const value)
{
   Gkv   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a   ||
      !key ||
      index < 0);

   if (!gkvArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("gkvArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   ps = &(a->p[index]);
   if (index < a->count - 1)
   {
      pd = &(a->p[index + 1]);

      greturnFalseIf(!gmemCopyOverTypeArray(pd, Gkv, (a->count - index) - 1, ps));
   }

   gkvpSetK(ps, key);
   gkvpSetV(ps, value);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayAddBegin
**************************************************************************************************/
grlAPI Gb gkvArrayAddBegin(GkvArray * const a, Gk const * const key, Gv const value)
{
   genter;

   greturn gkvArrayAddAt(a, 0, key, value);
}

/**************************************************************************************************
func: gkvArrayAddEnd
**************************************************************************************************/
grlAPI Gb gkvArrayAddEnd(GkvArray * const a, Gk const * const key, Gv const value)
{
   genter;

   greturn gkvArrayAddAt(a, gkvArrayGetCount(a), key, value);
}

/**************************************************************************************************
func: gkvArrayClear
**************************************************************************************************/
grlAPI Gb gkvArrayClear(GkvArray * const a, Gcount const count, Gindex const index)
{
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count < 0 ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // Can't null out more than what we have in the buffer.
   ctemp = count;
   if (index + count >= a->count)
   {
      ctemp = a->count - index;
   }

   gmemClearTypeArrayAt(a->p, Gkv, ctemp, index);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayCopy
**************************************************************************************************/
grlAPI Gb gkvArrayCopy(GkvArray * const a, Gcount const count, Gindex const indexSrc,
   Gindex const indexDst)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count    < 0 ||
      indexSrc < 0 || a->count <  indexSrc ||
      indexDst < 0 || a->count <= indexDst);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   ctemp = count;
   if (indexSrc + count >= a->count)
   {
      ctemp = a->count - indexSrc;
   }
   if (indexDst + count >= a->count)
   {
      ctemp = a->count - indexDst;
   }

   result = gmemCopyTypeArray(a->p, Gkv, ctemp, indexSrc, indexDst);

   greturn result;
}

/**************************************************************************************************
func: gkvArrayCopyFrom
**************************************************************************************************/
grlAPI Gb gkvArrayCopyFrom(GkvArray * const aDst, Gindex const indexDst,
   GkvArray const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gkvArrayCopy(aDst, count, indexSrc, indexDst));

   greturnFalseIf(
      count    < 0 ||
      indexDst < 0 || aDst->count <  indexDst ||
      indexSrc < 0 || aSrc->count <= indexSrc);

   ctemp = count;
   if (indexSrc + count >= aSrc->count)
   {
      ctemp = aSrc->count - indexSrc;
   }
   if (indexDst + count >= aDst->count)
   {
      ctemp = aDst->count - indexDst;
   }

   // Use of this function marks the array as unsorted.
   aDst->isSorted = gbFALSE;

   result = gmemCopyOverTypeArrayAt(aDst->p, Gkv, ctemp, indexDst, aSrc->p, indexSrc);

   greturn result;
}

/**************************************************************************************************
func: gkvArrayCloc_
**************************************************************************************************/
grlAPI GkvArray *gkvArrayCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   GkvArray *a;

   genter;

   a = gmemClocType(GkvArray);
   greturnNullIf(!a);

   if (!gkvArrayClocContent_(a, typeName, compareFunc, isVectorSizing))
   {
      gkvArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

/**************************************************************************************************
func: gkvArrayClocContent
**************************************************************************************************/
grlAPI Gb gkvArrayClocContent_(GkvArray * const a, Char const * const typeName,
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(!a);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->count          = 0;
   a->countTotal     = gvArrayVectorSize((Gb) a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   // count can be 0;
   // We are using raw gmemCloc_ so that we can set the type name.
   a->p = (Gkv *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * gsizeof(Gkv)),
                          a->countTotal * gsizeof(Gkv));
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayDloc
**************************************************************************************************/
grlAPI void gkvArrayDloc(GkvArray * const a)
{
   genter;

   greturnIf(!a);

   gkvArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

/**************************************************************************************************
func: gkvArrayDlocContent
**************************************************************************************************/
grlAPI void gkvArrayDlocContent(GkvArray const * const a)
{
   genter;

   greturnIf(!a);

   gmemDloc(a->p);

   greturn;
}

/**************************************************************************************************
func: gkvArrayErase
**************************************************************************************************/
grlAPI Gb gkvArrayErase(GkvArray * const a, Gk const * const key)
{
   Gb     result;
   Gindex index;

   genter;

   index = gkvArrayFind(a, key);
   if (index != GindexERROR)
   {
      result = gkvArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

/**************************************************************************************************
func: gkvArrayEraseAt
**************************************************************************************************/
grlAPI Gb gkvArrayEraseAt(GkvArray * const a, Gcount const count, Gindex const index)
{
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count < 0 ||
      index < 0 || a->count <= index);

   ctemp = count;

   // Adjust the count
   if (index + ctemp >= a->count)
   {
      ctemp = a->count - index;
   }

   if ((index + ctemp) != a->count)
   {
      // Shuffle elements down.
      if (!gmemCopyTypeArray(a->p, Gkv, a->count - (index + ctemp), index + ctemp, index))
      {
         debugHalt("gkvArrayemCopy failed");
      }
   }

   gmemClearTypeArrayAt(a->p,Gkv, ctemp, a->count - ctemp);

   if (!gkvArraySetCount(a, a->count - ctemp))
   {
      debugHalt("gkvArraySetCount failed");
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayEraseBegin
**************************************************************************************************/
grlAPI void gkvArrayEraseBegin(GkvArray * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   gkvArrayEraseAt(a, 1, 0);

   greturn;
}

/**************************************************************************************************
func: gkvArrayEraseEnd
**************************************************************************************************/
grlAPI void gkvArrayEraseEnd(GkvArray * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   gkvArrayEraseAt(a, 1, gkvArrayGetCount(a) - 1);

   greturn;
}

/**************************************************************************************************
func: gkvArrayFind
**************************************************************************************************/
grlAPI Gindex gkvArrayFind(GkvArray const * const a, Gk const * const key)
{
   genter;

   greturnValIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0   ||
         !key,
      GindexERROR);

   if (a->isSorted)
   {
      greturn _BinarySearch(a, key, gbFALSE);
   }

   greturn _LinearSearch(a, key, gbFALSE);
}

/**************************************************************************************************
func: gkvArrayFlush
**************************************************************************************************/
grlAPI void gkvArrayFlush(GkvArray * const a)
{
   genter;

   greturnIf(!a);

   gkvArraySetCount(a, 0);

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   greturn;
}

/**************************************************************************************************
func: gkvArrayForEach
**************************************************************************************************/
grlAPI Gb gkvArrayForEach(GkvArray const * const a, GrlForEachKeyFunc const func)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      func(gkvGetK(a->p[index]), &gkvGetV(a->p[index]));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayForEachDown

Perform the for each in reverse over the array.  This is for those times when you are removing items
from the array or similar order is necessary.
**************************************************************************************************/
grlAPI Gb gkvArrayForEachDown(GkvArray const * const a, GrlForEachKeyFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count)
   {
      func(gkvGetK(a->p[index]), &gkvGetV(a->p[index]));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayGet
**************************************************************************************************/
grlAPI Gkv const *gkvArrayGet(GkvArray const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

/**************************************************************************************************
func: gkvArrayGetAt
**************************************************************************************************/
grlAPI Gv gkvArrayGetAt(GkvArray const * const a, Gindex const index)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(
         !a ||
         index < 0 || a->count <= index,
      zero);

   greturn gkvGetV(a->p[index]);
}

/**************************************************************************************************
func: gkvArrayGetAtKey
**************************************************************************************************/
grlAPI Gk const *gkvArrayGetAtKey(GkvArray const * const a, Gindex const index)
{
   genter;

   greturnNullIf(
      !a ||
      index < 0 || a->count <= index);

   greturn gkvGetK(a->p[index]);
}

/**************************************************************************************************
func: gkvArrayGetBegin
**************************************************************************************************/
grlAPI Gv gkvArrayGetBegin(GkvArray const * const a)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(
         !a ||
         a->count == 0,
      zero);

   greturn gkvGetV(a->p[0]);
}

/**************************************************************************************************
func: gkvArrayGetBeginKey
**************************************************************************************************/
grlAPI Gk const *gkvArrayGetBeginKey(GkvArray const * const a)
{
   genter;

   greturnNullIf(
      !a ||
      a->count == 0);

   greturn gkvGetK(a->p[0]);
}

/**************************************************************************************************
func: gkvArrayGetCount
**************************************************************************************************/
grlAPI Gcount gkvArrayGetCount(GkvArray const * const a)
{
   genter;

   greturn0If(!a);

   greturn a->count;
}

/**************************************************************************************************
func: gkvArrayGetEnd
**************************************************************************************************/
grlAPI Gv gkvArrayGetEnd(GkvArray const * const a)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(
         !a ||
         a->count == 0,
      zero);

   greturn gkvGetV(a->p[a->count - 1]);
}

/**************************************************************************************************
func: gkvArrayGetEndKey
**************************************************************************************************/
grlAPI Gk const *gkvArrayGetEndKey(GkvArray const * const a)
{
   genter;

   greturnNullIf(
      !a ||
      a->count == 0);

   greturn gkvGetK(a->p[a->count - 1]);
}

/**************************************************************************************************
func: gkvArraySetCount
**************************************************************************************************/
grlAPI Gb gkvArraySetCount(GkvArray * const a, Gcount const value)
{
   Gcount countTotal;
   Gkv   *p;
   Gb     result;

   genter;

   greturnFalseIf(
      !a ||
      value < 0);

   if (a->count < value)
   {
      // Use of this function may unsort the array.
      a->isSorted = gbFALSE;
   }

   countTotal = gvArrayVectorSize((Gb) a->isVectorSizing, value);

   result = gbTRUE;
   if (countTotal != a->countTotal)
   {
      p      = gmemCloc(GTYPE_GET(a), countTotal * gsizeof(Gkv));

      result = gmemCopyOverTypeArray(p, Gkv, gMIN(value, a->count), a->p);

      gmemDloc(a->p);
      a->p = p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

/**************************************************************************************************
func: gkvArraySort
**************************************************************************************************/
grlAPI Gb gkvArraySort(GkvArray * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      a,
      (GrlGetFunc)  gkvArrayGetAtKey,
      (GrlSwapFunc) gkvArraySwap,
      a->compareFunc);

   a->isSorted = gheapSort(&heap);

   greturn a->isSorted;
}

/**************************************************************************************************
func: gkvArraySwap
**************************************************************************************************/
grlAPI Gb gkvArraySwap(GkvArray * const a, Gindex const indexA, Gindex const indexB)
{
   Gkv    data;

   genter;

   greturnFalseIf(
      !a         ||
      indexA < 0 || a->count <= indexA ||
      indexB < 0 || a->count <= indexB);

      // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   data         = a->p[indexA];
   a->p[indexA] = a->p[indexB];
   a->p[indexB] = data;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvArrayUpdateAt
**************************************************************************************************/
grlAPI Gb gkvArrayUpdateAt(GkvArray * const a, Gindex const index, Gv const value)
{
   genter;

   greturnFalseIf(
      !a ||
      index < 0 || a->count <= index);

   gkvSetV(a->p[index], value);

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _BinarySearch

Binary search for the item or location where the item should be inserted.
**************************************************************************************************/
static Gindex _BinarySearch(GkvArray const * const a, Gk const * const key, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gp const *data;
   Gcompare  compare;

   genter;

   if (a->count == 0)
   {
      greturn0If(findLocation);

      greturn GindexERROR;
   }

   hi = a->count - 1;
   lo = 0;
   loop
   {
      // Find the mid point.
      index = (hi + lo) / 2;

      // Compare.  If equal then return the index.
      data = gkvArrayGetAtKey(a, index);

      compare = a->compareFunc(key, data);
      greturnValIf(compare == gcompareEQUAL, index);

      // Hi and lo are the same.  We are done.
      breakIf(hi == lo);

      // Find the next item to compare with.
      if (compare == gcompareLESS_THAN)
      {
         hi = gMAX(lo, index - 1);
      }
      else
      {
         lo = gMIN(hi, index + 1);
      }
   }

   if (findLocation)
   {
      greturnValIf(compare == gcompareLESS_THAN, -index)

      greturn -(index + 1);
   }

   greturn GindexERROR;
}

/**************************************************************************************************
func: _LinearSearch
**************************************************************************************************/
static Gindex _LinearSearch(GkvArray const * const a, Gk const * const key, Gb const findLocation)
{
   Gindex    index;
   Gp const *data;
   Gcompare  compare;

   genter;

   // If we are findind a location and there isn't a compare function then
   // return the last index.
   if (a->count       == 0 ||
       a->compareFunc == NULL)
   {
      greturnValIf(findLocation, -(a->count));

      greturn GindexERROR;
   }

   // Linear search for the item.
   forCount(index, a->count)
   {
      data = gkvArrayGetAtKey(a, index);

      compare = a->compareFunc(key, data);
      greturnValIf(compare == gcompareEQUAL, index);

      greturnValIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnValIf(findLocation, -(a->count));

   greturn GindexERROR;
}
