/**************************************************************************************************
file:         G_Array
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
#include "precompiled.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gindex _BinarySearch(  G_Array const * const a, Gp const * const value, Gb const findLocation);

static Gindex _LinearSearch(  G_Array const * const a, Gp const * const value, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_ArrayAdd
**************************************************************************************************/
grlAPI Gb g_ArrayAdd(G_Array * const a, Gp const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   greturnFalseIf(
      !a ||
      !value);

   if (a->isSorted)
   {
      // Find the location to put the new value in.
      index  = _BinarySearch(a, value, gbTRUE);

      result = g_ArrayAddAt(a, gABS(index), value);

      // AddAt turns this off but sort order has not been
      // violated so turn it back on.
      a->isSorted = gbTRUE; //lint !e641

      greturn result;
   }

   // if the array is not sorted or no longer sorted then just append.
   result = g_ArrayAddEnd(a, value);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayAddAt
**************************************************************************************************/
grlAPI Gb g_ArrayAddAt(G_Array * const a, Gindex const index, Gp const * const value)
{
   Gsize  size;
   Gn1   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!g_ArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("g_ArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   size = a->typeSize;
   ps   = &(a->p[index * size]);
   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      pd = &(a->p[(index + 1) * size]);

      greturnFalseIf(!gmemCopyOver(pd, size * ((a->count - index) - 1), ps));
   }

   if (a->isPointerType)
   {
      greturnFalseIf(!gmemCopyOver(ps, size, &value));
   }
   else
   {
      if (value)
      {
         greturnFalseIf(!gmemCopyOver(ps, size, value));
      }
      else
      {
         gmemClear(ps, a->typeSize);
      }
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayAddBegin
**************************************************************************************************/
grlAPI Gb g_ArrayAddBegin(G_Array * const a, Gp const * const value)
{
   Gb result;

   genter;

   result = g_ArrayAddAt(a, 0, value);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayAddEnd
**************************************************************************************************/
grlAPI Gb g_ArrayAddEnd(G_Array * const a, Gp const * const value)
{
   Gb result;

   genter;

   result = g_ArrayAddAt(a, g_ArrayGetCount(a), value);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayClear
**************************************************************************************************/
grlAPI Gb g_ArrayClear(G_Array * const a, Gcount const count, Gindex const index)
{
   Gsize  size;
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count < 0 ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   // Can't null out more than what we have in the buffer.
   ctemp = count;
   if (index + count >= a->count)
   {
      ctemp = a->count - index;
   }
   size = a->typeSize;

   gmemClearAt(a->p, ctemp * size, index * size);

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayCopy
**************************************************************************************************/
grlAPI Gb g_ArrayCopy(G_Array * const a, Gcount const count, Gindex const indexSrc,
   Gindex const indexDst)
{
   Gb     result;
   Gsize  size;
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count    < 0 ||
      indexSrc < 0 || a->count <  indexSrc ||
      indexDst < 0 || a->count <= indexDst);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   ctemp = count;
   if (indexSrc + count >= a->count)
   {
      ctemp = a->count - indexSrc;
   }
   if (indexDst + count >= a->count)
   {
      ctemp = a->count - indexDst;
   }

   size = a->typeSize;

   result = gmemCopy(
      a->p,
      ctemp    * size,
      indexSrc * size,
      indexDst * size);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayCopyFrom
**************************************************************************************************/
grlAPI Gb g_ArrayCopyFrom(G_Array * const aDst, Gindex const indexDst,
   G_Array const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gsize  size;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnIf(aDst == aSrc, g_ArrayCopy(aDst, count, indexSrc, indexDst));

   greturnFalseIf(
      count    < 0 ||
      indexDst < 0 || aDst->count <  indexDst ||
      indexSrc < 0 || aSrc->count <= indexSrc ||
      aDst->typeSize != aSrc->typeSize);

   ctemp = count;
   if (indexSrc + count >= aSrc->count)
   {
      ctemp = aSrc->count - indexSrc;
   }
   if (indexDst + count >= aDst->count)
   {
      ctemp = aDst->count - indexDst;
   }

   size = aDst->typeSize;

   // Use of this function marks the array as unsorted.
   aDst->isSorted = gbFALSE; //lint !e641

   result = gmemCopyOverAt(
      aDst->p,
      ctemp    * size,
      indexDst * size,
      aSrc->p,
      indexSrc * size);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayCloc_
**************************************************************************************************/
grlAPI G_Array *g_ArrayCloc_(Gsize const typeSize, Char const * const typeName,
   Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing,
   Gb const isNullEnding)
{
   G_Array *a;

   genter;

   greturnNullIf(typeSize <= 0);

   a = gmemClocType(G_Array);
   greturnNullIf(!a);

   if (!g_ArrayClocContent_(
         a,
         typeSize,
         typeName,
         isPointerType,
         compareFunc,
         isVectorSizing,
         isNullEnding))
   {
      g_ArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

/**************************************************************************************************
func: g_ArrayClocContent
**************************************************************************************************/
grlAPI Gb g_ArrayClocContent_(G_Array * const a, Gsize const typeSize, Char const * const typeName,
   Gb const isPointerType, GrlCompareFunc const compareFunc, Gb const isVectorSizing,
   Gb const isNullEnding)
{
   genter;

   greturnFalseIf(
      !a ||
      typeSize <= 0);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isPointerType  = (isPointerType)  ? gbTRUE : gbFALSE;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->isNullEnding   = (isNullEnding)   ? gbTRUE : gbFALSE;
   a->typeSize       = typeSize;
   a->count          = 0;
   a->countTotal     = g_ArrayVectorSize(
      (Gb) a->isVectorSizing,
      (Gcount) (a->count + isNullEnding)); //lint !e641

   if (compareFunc)
   {
      a->isSorted = gbTRUE; //lint !e641
   }

   // count can be 0;
   a->p = (Gn1 *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * a->typeSize),
      a->countTotal);
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayDloc
**************************************************************************************************/
grlAPI void g_ArrayDloc(G_Array * const a)
{
   genter;

   greturnVoidIf(!a);

   g_ArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

/**************************************************************************************************
func: g_ArrayDlocContent
**************************************************************************************************/
grlAPI void g_ArrayDlocContent(G_Array const * const a)
{
   genter;

   greturnVoidIf(!a);

   gmemDloc(a->p);

   greturn;
}

/**************************************************************************************************
func: g_ArrayErase
**************************************************************************************************/
grlAPI Gb g_ArrayErase(G_Array * const a, Gp const * const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = g_ArrayFind(a, value);
   if (index != GindexERROR)
   {
      result = g_ArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

/**************************************************************************************************
func: g_ArrayEraseAt
**************************************************************************************************/
grlAPI Gb g_ArrayEraseAt(G_Array * const a, Gcount const count, Gindex const index)
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
      if (!gmemCopy(
            a->p,
            (a->count - (index + ctemp)) * a->typeSize,
                        (index + ctemp)  * a->typeSize,
                         index           * a->typeSize))
      {
         debugHalt("g_ArrayemCopy failed");
      }
   }

   gmemClearAt(
      a->p,
      a->typeSize * ctemp,
      (a->count - ctemp) * a->typeSize);

   if (!g_ArraySetCount(a, a->count - ctemp))
   {
      debugHalt("g_ArraySetCount failed");
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayEraseBegin
**************************************************************************************************/
grlAPI void g_ArrayEraseBegin(G_Array * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   g_ArrayEraseAt(a, 1, 0); //lint !e534

   greturn;
}

/**************************************************************************************************
func: g_ArrayEraseEnd
**************************************************************************************************/
grlAPI void g_ArrayEraseEnd(G_Array * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   g_ArrayEraseAt(a, 1, g_ArrayGetCount(a) - 1); //lint !e534

   greturn;
}

/**************************************************************************************************
func: g_ArrayFind
**************************************************************************************************/
grlAPI Gindex g_ArrayFind(G_Array const * const a, Gp const * const value)
{
   Gindex result;

   genter;

   greturnIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0   ||
         !value,
      GindexERROR);

   if (a->isSorted)
   {
      result = _BinarySearch(a, value, gbFALSE);

      greturn result;
   }

   result = _LinearSearch(a, value, gbFALSE);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayFlush
**************************************************************************************************/
grlAPI void g_ArrayFlush(G_Array * const a)
{
   genter;

   greturnVoidIf(!a);

   g_ArraySetCount(a, 0); //lint !e534

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE; //lint !e641
   }

   greturn;
}

/**************************************************************************************************
func: g_ArrayForEach
**************************************************************************************************/
grlAPI Gb g_ArrayForEach(G_Array const * const a, GrlForEachFunc const func)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      if (a->isPointerType)
      {
         // The data is a pointer so we can send that along instead of a poitner
         // to the data.
         func(*((Gp **) &(a->p[index * a->typeSize])));
      }
      else
      {
         func(  (Gp *)  &(a->p[index * a->typeSize]));
      }
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayGet
**************************************************************************************************/
grlAPI Gp *g_ArrayGet(G_Array const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

/**************************************************************************************************
func: g_ArrayGetAt
**************************************************************************************************/
grlAPI Gp *g_ArrayGetAt(G_Array const * const a, Gindex const index)
{
   Gp *result;

   genter;

   greturnNullIf(
      !a        ||
      index < 0 || a->count <= index);

   if (a->isPointerType)
   {
      result = *((Gp**) &(a->p[index * a->typeSize]));
   }
   else
   {
      result = (Gp *) &(a->p[index * a->typeSize]);
   }

   greturn result;
}

/**************************************************************************************************
func: g_ArrayGetBegin
**************************************************************************************************/
grlAPI Gp *g_ArrayGetBegin(G_Array const * const a)
{
   Gp *result;

   genter;

   result = g_ArrayGetAt(a, 0);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayGetCount
**************************************************************************************************/
grlAPI Gcount g_ArrayGetCount(G_Array const * const a)
{
   genter;

   greturnIf(!a, 0);

   greturn a->count;
}

/**************************************************************************************************
func: g_ArrayGetEnd
**************************************************************************************************/
grlAPI Gp *g_ArrayGetEnd(G_Array const * const a)
{
   Gp *result;

   genter;

   result = g_ArrayGetAt(a, a->count - 1);

   greturn result;
}

/**************************************************************************************************
func: g_ArrayGetSize
**************************************************************************************************/
grlAPI Gsize g_ArrayGetSize(G_Array const * const a)
{
   genter;

   greturnIf(!a, 0);

   greturn a->typeSize;
}

/**************************************************************************************************
func: g_ArraySetCount
**************************************************************************************************/
grlAPI Gb g_ArraySetCount(G_Array * const a, Gcount const value)
{
   Gcount countTotal;
   Gp    *p;
   Gb     result;

   genter;

   greturnFalseIf(
      !a ||
      value < 0);

   if (a->count < value)
   {
      // Use of this function may unsort the array.
      a->isSorted = gbFALSE; //lint !e641
   }

   countTotal = g_ArrayVectorSize((Gb) a->isVectorSizing, value + a->isNullEnding);

   result = gbTRUE;
   if (countTotal != a->countTotal)
   {
      p      = gmemCloc(GTYPE_GET(a), countTotal * a->typeSize);

      result = gmemCopyOver(p, gMIN(value, a->count) * a->typeSize, a->p);

      gmemDloc(a->p);
      a->p = (Gn1 *) p;
   }

   // Ensure the value is null terminated.
   if (a->isNullEnding)
   {
      // Null out the last element.
      gmemSet(a->p + value * a->typeSize, a->typeSize, 0);
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

/**************************************************************************************************
func: g_ArraySort
**************************************************************************************************/
grlAPI Gb g_ArraySort(G_Array * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      (Gp *) a,
      (GrlGetFunc)  g_ArrayGetAt, //lint !e960 !e929
      (GrlSwapFunc) g_ArraySwap, //lint !e960 !e929
      a->compareFunc);

   a->isSorted = gheapSort(&heap); //lint !e641

   greturn (Gb) a->isSorted;  //lint !e930
}

/**************************************************************************************************
func: g_ArraySwap
**************************************************************************************************/
grlAPI Gb g_ArraySwap(G_Array * const a, Gindex const indexA, Gindex const indexB)
{
   Gindex index;
   Gsize  size;
   Gn1    data;
   Gn1   *pa,
         *pb;

   genter;

   greturnFalseIf(
      !a         ||
      indexA < 0 || a->count <= indexA ||
      indexB < 0 || a->count <= indexB);

      // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   size = a->typeSize;
   pa   = &(a->p[indexA * size]);
   pb   = &(a->p[indexB * size]);
   forCount(index, (Gindex) size)
   {
      data      = pa[index];
      pa[index] = pb[index];
      pb[index] = data;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ArrayUpdateAt
**************************************************************************************************/
grlAPI Gb g_ArrayUpdateAt(G_Array * const a, Gindex const index, Gp const * const value)
{
   Gsize  size;
   Gn1   *p;

   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

      // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   size = a->typeSize;

   p = &(a->p[index * size]);

   if (a->isPointerType)
   {
      greturnFalseIf(!gmemCopyOver(p, size, &value));
   }
   else
   {
      greturnFalseIf(!gmemCopyOver(p, size,  value));
   }

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
static Gindex _BinarySearch(G_Array const * const a, Gp const * const value, Gb const findLocation)
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
      data = g_ArrayGetAt(a, index);

      compare = a->compareFunc(value, data);
      greturnIf(compare == gcompareEQUAL, index);

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
      greturnIf(compare == gcompareLESS_THAN, -index)
      greturn -(index + 1);
   }

   greturn GindexERROR;
}

/**************************************************************************************************
func: _LinearSearch
**************************************************************************************************/
static Gindex _LinearSearch(G_Array const * const a, Gp const * const value, Gb const findLocation)
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
      greturnIf(findLocation, -(a->count));

      greturn GindexERROR;
   }

   // Linear search for the item.
   forCount(index, a->count)
   {
      data = g_ArrayGetAt(a, index);

      compare = a->compareFunc(value, data);
      greturnIf(compare == gcompareEQUAL, index);

      greturnIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnIf(findLocation, -(a->count));

   greturn GindexERROR;
}

/**************************************************************************************************
func: _ArrayVectorSize
**************************************************************************************************/
Gcount g_ArrayVectorSize(Gb const isVectorSizing, Gcount const size)
{
   Gcount y,
          step;

   genter;

   greturnIf(!isVectorSizing, gMAX(1, size));

   step =
      y = 4;

   loop
   {
      // 001*
      greturnIf(y > size, y);

      // 010*
      y += step;
      greturnIf(y > size, y);

      // 011*
      y += step;
      greturnIf(y > size, y);

      // 100*
      y += step;
      greturnIf(y > size, y);

      // 101*
      y += step;
      greturnIf(y > size, y);

      // 110*
      y += step;
      greturnIf(y > size, y);

      // 111*
      y += step;
      greturnIf(y > size, y);

      // Jump up a level.
      y   += step;
      step = step << 1;

      // Should never hit this but still.  (year 2012)
      breakIf(step == 0x10000000000000);
   }

   greturn 0;
}
