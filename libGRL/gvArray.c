/**************************************************************************************************
file:         GvArray
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
dynamic array.
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gindex _BinarySearch(  GvArray  const * const a, Gv  const value, Gb const findLocation);
static Gindex _BinarySearch1( Gv1Array const * const a, Gv1 const value, Gb const findLocation);
static Gindex _BinarySearch2( Gv2Array const * const a, Gv2 const value, Gb const findLocation);
static Gindex _BinarySearch4( Gv4Array const * const a, Gv4 const value, Gb const findLocation);

static Gindex _LinearSearch(  GvArray  const * const a, Gv  const value, Gb const findLocation);
static Gindex _LinearSearch1( Gv1Array const * const a, Gv1 const value, Gb const findLocation);
static Gindex _LinearSearch2( Gv2Array const * const a, Gv2 const value, Gb const findLocation);
static Gindex _LinearSearch4( Gv4Array const * const a, Gv4 const value, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gvArrayVectorSize
**************************************************************************************************/
grlAPI Gcount gvArrayVectorSize(Gb const isVectorSizing, Gcount const size)
{
   Gcount y,
          step;

   genter;

   greturnValIf(!isVectorSizing, gMAX(1, size));

   step =
      y = 4;

   loop
   {
      // 001*
      greturnValIf(y > size, y);

      // 010*
      y += step;
      greturnValIf(y > size, y);

      // 011*
      y += step;
      greturnValIf(y > size, y);

      // 100*
      y += step;
      greturnValIf(y > size, y);

      // 101*
      y += step;
      greturnValIf(y > size, y);

      // 110*
      y += step;
      greturnValIf(y > size, y);

      // 111*
      y += step;
      greturnValIf(y > size, y);

      // Jump up a level.
      y   += step;
      step = step << 1;

      // Should never hit this but still.  (year 2012)
      breakIf(step == 0x10000000000000);
   }

   greturn 0;
}

/**************************************************************************************************
func: gvArrayAdd
**************************************************************************************************/
grlAPI Gb gvArrayAdd(GvArray * const a, Gv const value)
{
   Gindex index;
   Gb     result;

   genter;

   // Expecting a sorted array for this function.
   greturnFalseIf(
      !a ||
      !a->isSorted);

   // Find the location to put the new value in.
   index  = _BinarySearch(a, value, gbTRUE);

   result = gvArrayAddAt(a, gABS(index), value);

   // AddAt turns this off but sort order has not been violated so turn it back on.
   a->isSorted = gbTRUE;

   greturn result;
}

grlAPI Gb gv1ArrayAdd(Gv1Array * const a, Gv1 const value)
{
   Gindex index;
   Gb     result;

   genter;

   // Expecting a sorted array for this function.
   greturnFalseIf(
      !a ||
      !a->isSorted);

   // Find the location to put the new value in.
   index  = _BinarySearch1(a, value, gbTRUE);

   result = gv1ArrayAddAt(a, gABS(index), value);

   // AddAt turns this off but sort order has not been
   // violated so turn it back on.
   a->isSorted = gbTRUE;

   greturn result;
}

grlAPI Gb gv2ArrayAdd(Gv2Array * const a, Gv2 const value)
{
   Gindex index;
   Gb     result;

   genter;

   // Expecting a sorted array for this function.
   greturnFalseIf(
      !a ||
      !a->isSorted);

   // Find the location to put the new value in.
   index  = _BinarySearch2(a, value, gbTRUE);

   result = gv2ArrayAddAt(a, gABS(index), value);

   // AddAt turns this off but sort order has not been
   // violated so turn it back on.
   a->isSorted = gbTRUE;

   greturn result;
}

grlAPI Gb gv4ArrayAdd(Gv4Array * const a, Gv4 const value)
{
   Gindex index;
   Gb     result;

   genter;

   // Expecting a sorted array for this function.
   greturnFalseIf(
      !a ||
      !a->isSorted);

   // Find the location to put the new value in.
   index  = _BinarySearch4(a, value, gbTRUE);

   result = gv4ArrayAddAt(a, gABS(index), value);

   // AddAt turns this off but sort order has not been
   // violated so turn it back on.
   a->isSorted = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: gvArrayAddAt
**************************************************************************************************/
grlAPI Gb gvArrayAddAt(GvArray * const a, Gindex const index, Gv const value)
{
   Gv *ps,
      *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!gvArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("gvArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      ps = &(a->p[index]);
      pd = &(a->p[index + 1]);

      greturnFalseIf(!gmemCopyOverTypeArray(pd, Gv, (a->count - index) - 1, ps));
   }

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayAddAt(Gv1Array * const a, Gindex const index, Gv1 const value)
{
   Gv1   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!gv1ArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("gvArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      ps = &(a->p[index]);
      pd = &(a->p[index + 1]);

      greturnFalseIf(!gmemCopyOverTypeArray(pd, Gv1, (a->count - index) - 1, ps));
   }

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayAddAt(Gv2Array * const a, Gindex const index, Gv2 const value)
{
   Gv2   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!gv2ArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("gvArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      ps = &(a->p[index]);
      pd = &(a->p[index + 1]);

      greturnFalseIf(!gmemCopyOverTypeArray(pd, Gv2, (a->count - index) - 1, ps));
   }

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayAddAt(Gv4Array * const a, Gindex const index, Gv4 const value)
{
   Gv4   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!gv4ArraySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("gvArraySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      ps = &(a->p[index]);
      pd = &(a->p[index + 1]);

      greturnFalseIf(!gmemCopyOverTypeArray(pd, Gv4, (a->count - index) - 1, ps));
   }

   a->p[index] = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayAddBegin
**************************************************************************************************/
grlAPI Gb gvArrayAddBegin(GvArray * const a, Gv const value)
{
   genter;

   greturn gvArrayAddAt(a, 0, value);
}

grlAPI Gb gv1ArrayAddBegin(Gv1Array * const a, Gv1 const value)
{
   genter;

   greturn gv1ArrayAddAt(a, 0, value);
}

grlAPI Gb gv2ArrayAddBegin(Gv2Array * const a, Gv2 const value)
{
   genter;

   greturn gv2ArrayAddAt(a, 0, value);
}

grlAPI Gb gv4ArrayAddBegin(Gv4Array * const a, Gv4 const value)
{
   genter;

   greturn gv4ArrayAddAt(a, 0, value);
}

/**************************************************************************************************
func: gvArrayAddEnd
**************************************************************************************************/
grlAPI Gb gvArrayAddEnd(GvArray * const a, Gv const value)
{
   genter;

   greturn gvArrayAddAt(a, gvArrayGetCount(a), value);
}

grlAPI Gb gv1ArrayAddEnd(Gv1Array * const a, Gv1 const value)
{
   genter;

   greturn gv1ArrayAddAt(a, gv1ArrayGetCount(a), value);
}

grlAPI Gb gv2ArrayAddEnd(Gv2Array * const a, Gv2 const value)
{
   genter;

   greturn gv2ArrayAddAt(a, gv2ArrayGetCount(a), value);
}

grlAPI Gb gv4ArrayAddEnd(Gv4Array * const a, Gv4 const value)
{
   genter;

   greturn gv4ArrayAddAt(a, gv4ArrayGetCount(a), value);
}

/**************************************************************************************************
func: gvArrayClear
**************************************************************************************************/
grlAPI Gb gvArrayClear(GvArray * const a, Gcount const count, Gindex const index)
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

   gmemClearTypeArrayAt(a->p, Gv, ctemp, index);

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayClear(Gv1Array * const a, Gcount const count, Gindex const index)
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

   gmemClearTypeArrayAt(a->p, Gv1, ctemp, index);

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayClear(Gv2Array * const a, Gcount const count, Gindex const index)
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

   gmemClearTypeArrayAt(a->p, Gv2, ctemp, index);

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayClear(Gv4Array * const a, Gcount const count, Gindex const index)
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

   gmemClearTypeArrayAt(a->p, Gv4, ctemp, index);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayCopy
**************************************************************************************************/
grlAPI Gb gvArrayCopy(GvArray * const a, Gcount const count, Gindex const indexSrc,
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

   result = gmemCopyTypeArray(a->p, Gv, ctemp, indexSrc, indexDst);

   greturn result;
}

grlAPI Gb gv1ArrayCopy(Gv1Array * const a, Gcount const count, Gindex const indexSrc,
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

   result = gmemCopyTypeArray(a->p, Gv1, ctemp, indexSrc, indexDst);

   greturn result;
}

grlAPI Gb gv2ArrayCopy(Gv2Array * const a, Gcount const count, Gindex const indexSrc,
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

   result = gmemCopyTypeArray(a->p, Gv2, ctemp, indexSrc, indexDst);

   greturn result;
}

grlAPI Gb gv4ArrayCopy(Gv4Array * const a, Gcount const count, Gindex const indexSrc,
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

   result = gmemCopyTypeArray(a->p, Gv4, ctemp, indexSrc, indexDst);

   greturn result;
}

/**************************************************************************************************
func: gvArrayCopyFrom
**************************************************************************************************/
grlAPI Gb gvArrayCopyFrom(GvArray * const aDst, Gindex const indexDst,
   GvArray const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gvArrayCopy(aDst, count, indexSrc, indexDst));

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

   result = gmemCopyOverTypeArrayAt(aDst->p, Gv, ctemp, indexDst, aSrc->p, indexSrc);

   greturn result;
}

grlAPI Gb gv1ArrayCopyFrom(Gv1Array * const aDst, Gindex const indexDst,
   Gv1Array const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gv1ArrayCopy(aDst, count, indexSrc, indexDst));

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

   result = gmemCopyOverTypeArrayAt(aDst->p, Gv1, ctemp, indexDst, aSrc->p, indexSrc);

   greturn result;
}

grlAPI Gb gv2ArrayCopyFrom(Gv2Array * const aDst, Gindex const indexDst,
   Gv2Array const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gv2ArrayCopy(aDst, count, indexSrc, indexDst));

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

   result = gmemCopyOverTypeArrayAt(aDst->p, Gv2, ctemp, indexDst, aSrc->p, indexSrc);

   greturn result;
}

grlAPI Gb gv4ArrayCopyFrom(Gv4Array * const aDst, Gindex const indexDst,
   Gv4Array const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gv4ArrayCopy(aDst, count, indexSrc, indexDst));

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

   result = gmemCopyOverTypeArrayAt(aDst->p, Gv4, ctemp, indexDst, aSrc->p, indexSrc);

   greturn result;
}

/**************************************************************************************************
func: gvArrayCloc_
**************************************************************************************************/
grlAPI GvArray *gvArrayCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   GvArray *a;

   genter;

   a = gmemClocType(GvArray);
   greturnNullIf(!a);

   if (!gvArrayClocContent_(a, typeName, compareFunc, isVectorSizing))
   {
      gvArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

grlAPI Gv1Array *gv1ArrayCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   Gv1Array *a;

   genter;

   a = gmemClocType(Gv1Array);
   greturnNullIf(!a);

   if (!gv1ArrayClocContent_(a, typeName, compareFunc, isVectorSizing))
   {
      gv1ArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

grlAPI Gv2Array *gv2ArrayCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   Gv2Array *a;

   genter;

   a = gmemClocType(Gv2Array);
   greturnNullIf(!a);

   if (!gv2ArrayClocContent_(a, typeName, compareFunc, isVectorSizing))
   {
      gv2ArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

grlAPI Gv4Array *gv4ArrayCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   Gv4Array *a;

   genter;

   a = gmemClocType(Gv4Array);
   greturnNullIf(!a);

   if (!gv4ArrayClocContent_(a, typeName, compareFunc, isVectorSizing))
   {
      gv4ArrayDloc(a);
      greturn NULL;
   }

   greturn a;
}

/**************************************************************************************************
func: gvArrayClocContent
**************************************************************************************************/
grlAPI Gb gvArrayClocContent_(GvArray * const a, Char const * const typeName,
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(!a);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->count          = 0;
   a->countTotal     = gvArrayVectorSize(a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   // count can be 0;
   // We are using raw gmemCloc_ so that we can set the type name.
   a->p = (Gv *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * gsizeof(Gv)),
                          a->countTotal * gsizeof(Gv));
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayClocContent_(Gv1Array * const a, Char const * const typeName,
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(!a);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->count          = 0;
   a->countTotal     = gvArrayVectorSize(a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   // count can be 0;
   a->p = (Gv1 *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * gsizeof(Gv1)),
                          a->countTotal * gsizeof(Gv1));
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayClocContent_(Gv2Array * const a, Char const * const typeName,
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(!a);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->count          = 0;
   a->countTotal     = gvArrayVectorSize(a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   // count can be 0;
   a->p = (Gv2 *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * gsizeof(Gv2)),
                          a->countTotal * gsizeof(Gv2));
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayClocContent_(Gv4Array * const a, Char const * const typeName,
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(!a);

   GTYPE_SET(a, typeName);

   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->count          = 0;
   a->countTotal     = gvArrayVectorSize(a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   // count can be 0;
   a->p = (Gv4 *) gleakCloc(
      gmemCloc_(typeName, a->countTotal * gsizeof(Gv4)),
                          a->countTotal * gsizeof(Gv4));
   if (!a->p)
   {
      gmemDloc(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayDloc
**************************************************************************************************/
grlAPI void gvArrayDloc(GvArray * const a)
{
   genter;

   greturnIf(!a);

   gvArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

grlAPI void gv1ArrayDloc(Gv1Array * const a)
{
   genter;

   greturnIf(!a);

   gv1ArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

grlAPI void gv2ArrayDloc(Gv2Array * const a)
{
   genter;

   greturnIf(!a);

   gv2ArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

grlAPI void gv4ArrayDloc(Gv4Array * const a)
{
   genter;

   greturnIf(!a);

   gv4ArrayDlocContent(a);
   gmemDloc(a);

   greturn;
}

/**************************************************************************************************
func: gvArrayDlocContent
**************************************************************************************************/
grlAPI void gvArrayDlocContent(GvArray const * const a)
{
   genter;

   greturnIf(!a);

   gmemDloc(a->p);

   greturn;
}

grlAPI void gv1ArrayDlocContent(Gv1Array const * const a)
{
   genter;

   greturnIf(!a);

   gmemDloc(a->p);

   greturn;
}

grlAPI void gv2ArrayDlocContent(Gv2Array const * const a)
{
   genter;

   greturnIf(!a);

   gmemDloc(a->p);

   greturn;
}

grlAPI void gv4ArrayDlocContent(Gv4Array const * const a)
{
   genter;

   greturnIf(!a);

   gmemDloc(a->p);

   greturn;
}

/**************************************************************************************************
func: gvArrayErase
**************************************************************************************************/
grlAPI Gb gvArrayErase(GvArray * const a, Gv const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = gvArrayFind(a, value);
   if (index != GindexERROR)
   {
      result = gvArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

grlAPI Gb gv1ArrayErase(Gv1Array * const a, Gv1 const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = gv1ArrayFind(a, value);
   if (index != GindexERROR)
   {
      result = gv1ArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

grlAPI Gb gv2ArrayErase(Gv2Array * const a, Gv2 const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = gv2ArrayFind(a, value);
   if (index != GindexERROR)
   {
      result = gv2ArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

grlAPI Gb gv4ArrayErase(Gv4Array * const a, Gv4 const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = gv4ArrayFind(a, value);
   if (index != GindexERROR)
   {
      result = gv4ArrayEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

/**************************************************************************************************
func: gvArrayEraseAt
**************************************************************************************************/
grlAPI Gb gvArrayEraseAt(GvArray * const a, Gcount const count, Gindex const index)
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
   if (count == GcountMAX ||
       index + ctemp >= a->count)
   {
      ctemp = a->count - index;
   }

   if ((index + ctemp) != a->count)
   {
      // Shuffle elements down.
      if (!gmemCopyTypeArray(a->p, Gv, a->count - (index + ctemp), index + ctemp, index))
      {
         debugHalt("gvArrayemCopy failed");
      }
   }

   gmemClearTypeArrayAt(a->p, Gv, ctemp, a->count - ctemp);

   if (!gvArraySetCount(a, a->count - ctemp))
   {
      debugHalt("gvArraySetCount failed");
   }

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayEraseAt(Gv1Array * const a, Gcount const count, Gindex const index)
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
   if (count == GcountMAX ||
       index + ctemp >= a->count)
   {
      ctemp = a->count - index;
   }

   if ((index + ctemp) != a->count)
   {
      // Shuffle elements down.
      if (!gmemCopyTypeArray(a->p, Gv1, a->count - (index + ctemp), index + ctemp, index))
      {
         debugHalt("gvArrayemCopy failed");
      }
   }

   gmemClearTypeArrayAt(a->p, Gv1, ctemp, a->count - ctemp);

   if (!gv1ArraySetCount(a, a->count - ctemp))
   {
      debugHalt("gv1ArraySetCount failed");
   }

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayEraseAt(Gv2Array * const a, Gcount const count, Gindex const index)
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
   if (count == GcountMAX ||
       index + ctemp >= a->count)
   {
      ctemp = a->count - index;
   }

   if ((index + ctemp) != a->count)
   {
      // Shuffle elements down.
      if (!gmemCopyTypeArray(a->p, Gv2, a->count - (index + ctemp), index + ctemp, index))
      {
         debugHalt("gvArrayemCopy failed");
      }
   }

   gmemClearTypeArrayAt(a->p, Gv2, ctemp, a->count - ctemp);

   if (!gv2ArraySetCount(a, a->count - ctemp))
   {
      debugHalt("gv2ArraySetCount failed");
   }

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayEraseAt(Gv4Array * const a, Gcount const count, Gindex const index)
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
   if (count == GcountMAX ||
       index + ctemp >= a->count)
   {
      ctemp = a->count - index;
   }

   if ((index + ctemp) != a->count)
   {
      // Shuffle elements down.
      if (!gmemCopyTypeArray(a->p, Gv4, a->count - (index + ctemp), index + ctemp, index))
      {
         debugHalt("gvArrayemCopy failed");
      }
   }

   gmemClearTypeArrayAt(a->p, Gv4, ctemp, a->count - ctemp);

   if (!gv4ArraySetCount(a, a->count - ctemp))
   {
      debugHalt("gvArraySetCount failed");
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayEraseBegin
**************************************************************************************************/
grlAPI Gb gvArrayEraseBegin(GvArray * const a, Gcount const count)
{
   genter;

   greturn gvArrayEraseAt(a, count, 0);
}

grlAPI Gb gv1ArrayEraseBegin(Gv1Array * const a, Gcount const count)
{
   genter;

   greturn gv1ArrayEraseAt(a, count, 0);
}

grlAPI Gb gv2ArrayEraseBegin(Gv2Array * const a, Gcount const count)
{
   genter;

   greturn gv2ArrayEraseAt(a, count, 0);
}

grlAPI Gb gv4ArrayEraseBegin(Gv4Array * const a, Gcount const count)
{
   genter;

   greturn gv4ArrayEraseAt(a, count, 0);
}

/**************************************************************************************************
func: gvArrayEraseEnd
**************************************************************************************************/
grlAPI Gb gvArrayEraseEnd(GvArray * const a, Gcount const count)
{
   genter;

   greturn gvArrayEraseAt(a, count, gvArrayGetCount(a) - 1);
}

grlAPI Gb gv1ArrayEraseEnd(Gv1Array * const a, Gcount const count)
{
   genter;

   greturn gv1ArrayEraseAt(a, count, gv1ArrayGetCount(a) - 1);
}

grlAPI Gb gv2ArrayEraseEnd(Gv2Array * const a, Gcount const count)
{
   genter;

   greturn gv2ArrayEraseAt(a, count, gv2ArrayGetCount(a) - 1);
}

grlAPI Gb gv4ArrayEraseEnd(Gv4Array * const a, Gcount const count)
{
   genter;

   greturn gv4ArrayEraseAt(a, count, gv4ArrayGetCount(a) - 1);
}

/**************************************************************************************************
func: gvArrayFind
**************************************************************************************************/
grlAPI Gindex gvArrayFind(GvArray const * const a, Gv const value)
{
   genter;

   greturnValIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0,
      GindexERROR);

   if (a->isSorted)
   {
      greturn _BinarySearch(a, value, gbFALSE);
   }

   greturn _LinearSearch(a, value, gbFALSE);
}

grlAPI Gindex gv1ArrayFind(Gv1Array const * const a, Gv1 const value)
{
   genter;

   greturnValIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0,
      GindexERROR);

   if (a->isSorted)
   {
      greturn _BinarySearch1(a, value, gbFALSE);
   }

   greturn _LinearSearch1(a, value, gbFALSE);
}

grlAPI Gindex gv2ArrayFind(Gv2Array const * const a, Gv2 const value)
{
   genter;

   greturnValIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0,
      GindexERROR);

   if (a->isSorted)
   {
      greturn _BinarySearch2(a, value, gbFALSE);
   }

   greturn _LinearSearch2(a, value, gbFALSE);
}

grlAPI Gindex gv4ArrayFind(Gv4Array const * const a, Gv4 const value)
{
   genter;

   greturnValIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0,
      GindexERROR);

   if (a->isSorted)
   {
      greturn _BinarySearch4(a, value, gbFALSE);
   }

   greturn _LinearSearch4(a, value, gbFALSE);
}

/**************************************************************************************************
func: gvArrayFlush
**************************************************************************************************/
grlAPI void gvArrayFlush(GvArray * const a)
{
   genter;

   greturnIf(!a);

   gvArraySetCount(a, 0);

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   greturn;
}

grlAPI void gv1ArrayFlush(Gv1Array * const a)
{
   genter;

   greturnIf(!a);

   gv1ArraySetCount(a, 0);

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   greturn;
}

grlAPI void gv2ArrayFlush(Gv2Array * const a)
{
   genter;

   greturnIf(!a);

   gv2ArraySetCount(a, 0);

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   greturn;
}

grlAPI void gv4ArrayFlush(Gv4Array * const a)
{
   genter;

   greturnIf(!a);

   gv4ArraySetCount(a, 0);

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE;
   }

   greturn;
}

/**************************************************************************************************
func: gvArrayForEach
**************************************************************************************************/
grlAPI Gb gvArrayForEach(GvArray const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayForEach(Gv1Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayForEach(Gv2Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayForEach(Gv4Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayForEachDown

Perform the for each in reverse over the array.  This is for those times when you are removing items
from the array or similar order is necessary.
**************************************************************************************************/
grlAPI Gb gvArrayForEachDown(GvArray const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayForEachDown(Gv1Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayForEachDown(Gv2Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayForEachDown(Gv4Array const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvArrayGet
**************************************************************************************************/
grlAPI Gv const *gvArrayGet(GvArray const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

grlAPI Gv1 const *gv1ArrayGet(Gv1Array const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

grlAPI Gv2 const *gv2ArrayGet(Gv2Array const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

grlAPI Gv4 const *gv4ArrayGet(Gv4Array const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

/**************************************************************************************************
func: gvArrayGetAt
**************************************************************************************************/
grlAPI Gv gvArrayGetAt(GvArray const * const a, Gindex const index)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(
         !a        ||
         index < 0 || a->count <= index,
      zero);

   greturn a->p[index];
}

grlAPI Gv1 gv1ArrayGetAt(Gv1Array const * const a, Gindex const index)
{
   Gv1 zero = { 0 };

   genter;

   greturnValIf(
         !a        ||
         index < 0 || a->count <= index,
      zero);

   greturn a->p[index];
}

grlAPI Gv2 gv2ArrayGetAt(Gv2Array const * const a, Gindex const index)
{
   Gv2 zero = { 0 };

   genter;

   greturnValIf(
         !a        ||
         index < 0 || a->count <= index,
      zero);

   greturn a->p[index];
}

grlAPI Gv4 gv4ArrayGetAt(Gv4Array const * const a, Gindex const index)
{
   Gv4 zero = { 0 };

   genter;

   greturnValIf(
         !a        ||
         index < 0 || a->count <= index,
      zero);

   greturn a->p[index];
}

/**************************************************************************************************
func: gvArrayGetBegin
**************************************************************************************************/
grlAPI Gv gvArrayGetBegin(GvArray const * const a)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      zero);

   greturn a->p[0];
}

grlAPI Gv1 gv1ArrayGetBegin(Gv1Array const * const a)
{
   Gv1 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[0];
}

grlAPI Gv2 gv2ArrayGetBegin(Gv2Array const * const a)
{
   Gv2 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[0];
}

grlAPI Gv4 gv4ArrayGetBegin(Gv4Array const * const a)
{
   Gv4 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[0];
}

/**************************************************************************************************
func: gvArrayGetCount
**************************************************************************************************/
grlAPI Gcount gvArrayGetCount(GvArray const * const a)
{
   genter;

   greturnValIf(!a, 0);

   greturn a->count;
}

grlAPI Gcount gv1ArrayGetCount(Gv1Array const * const a)
{
   genter;

   greturnValIf(!a, 0);

   greturn a->count;
}

grlAPI Gcount gv2ArrayGetCount(Gv2Array const * const a)
{
   genter;

   greturnValIf(!a, 0);

   greturn a->count;
}

grlAPI Gcount gv4ArrayGetCount(Gv4Array const * const a)
{
   genter;

   greturnValIf(!a, 0);

   greturn a->count;
}

/**************************************************************************************************
func: gvArrayGetEnd
**************************************************************************************************/
grlAPI Gv gvArrayGetEnd(GvArray const * const a)
{
   Gv v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[a->count - 1];
}

grlAPI Gv1 gv1ArrayGetEnd(Gv1Array const * const a)
{
   Gv1 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[a->count - 1];
}

grlAPI Gv2 gv2ArrayGetEnd(Gv2Array const * const a)
{
   Gv2 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[a->count - 1];
}

grlAPI Gv4 gv4ArrayGetEnd(Gv4Array const * const a)
{
   Gv4 v = { 0 };

   genter;

   greturnValIf(
         !a        ||
         a->count == 0,
      v);

   greturn a->p[a->count - 1];
}

/**************************************************************************************************
func: gvArraySetCount
**************************************************************************************************/
grlAPI Gb gvArraySetCount(GvArray * const a, Gcount const value)
{
   Gcount countTotal;
   Gv    *p;
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
      p      = gmemCloc(GTYPE_GET(a), countTotal * gsizeof(Gv));

      result = gmemCopyOverTypeArray(p, Gv, gMIN(value, a->count), a->p);

      gmemDloc(a->p);
      a->p = p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

grlAPI Gb gv1ArraySetCount(Gv1Array * const a, Gcount const value)
{
   Gcount countTotal;
   Gv1   *p;
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
      p      = gmemCloc(GTYPE_GET(a), countTotal * gsizeof(Gv1));

      result = gmemCopyOverTypeArray(p, Gv1, gMIN(value, a->count), a->p);

      gmemDloc(a->p);
      a->p = p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

grlAPI Gb gv2ArraySetCount(Gv2Array * const a, Gcount const value)
{
   Gcount countTotal;
   Gv2   *p;
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
      p      = gmemCloc(GTYPE_GET(a), countTotal * gsizeof(Gv2));

      result = gmemCopyOverTypeArray(p, Gv2, gMIN(value, a->count), a->p);

      gmemDloc(a->p);
      a->p = p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

grlAPI Gb gv4ArraySetCount(Gv4Array * const a, Gcount const value)
{
   Gcount countTotal;
   Gv4   *p;
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
      p      = gmemCloc(GTYPE_GET(a), countTotal * gsizeof(Gv4));

      result = gmemCopyOverTypeArray(p, Gv4, gMIN(value, a->count), a->p);

      gmemDloc(a->p);
      a->p = p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

/**************************************************************************************************
func: gvArraySort
**************************************************************************************************/
grlAPI Gb gvArraySort(GvArray * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      a,
      (GrlGetFunc)  gvArrayGetAt,
      (GrlSwapFunc) gvArraySwap,
      a->compareFunc);

   a->isSorted = gheapSort(&heap);

   greturn a->isSorted;
}

grlAPI Gb gv1ArraySort(Gv1Array * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      a,
      (GrlGetFunc)  gv1ArrayGetAt,
      (GrlSwapFunc) gv1ArraySwap,
      a->compareFunc);

   a->isSorted = gheapSort(&heap);

   greturn a->isSorted;
}

grlAPI Gb gv2ArraySort(Gv2Array * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      a,
      (GrlGetFunc)  gv2ArrayGetAt,
      (GrlSwapFunc) gv2ArraySwap,
      a->compareFunc);

   a->isSorted = gheapSort(&heap);

   greturn a->isSorted;
}

grlAPI Gb gv4ArraySort(Gv4Array * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      a,
      (GrlGetFunc)  gv4ArrayGetAt,
      (GrlSwapFunc) gv4ArraySwap,
      a->compareFunc);

   a->isSorted = gheapSort(&heap);

   greturn a->isSorted;
}

/**************************************************************************************************
func: gvArraySwap
**************************************************************************************************/
grlAPI Gb gvArraySwap(GvArray * const a, Gindex const indexA, Gindex const indexB)
{
   Gv data;

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

grlAPI Gb gv1ArraySwap(Gv1Array * const a, Gindex const indexA, Gindex const indexB)
{
   Gv1 data;

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

grlAPI Gb gv2ArraySwap(Gv2Array * const a, Gindex const indexA, Gindex const indexB)
{
   Gv2 data;

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

grlAPI Gb gv4ArraySwap(Gv4Array * const a, Gindex const indexA, Gindex const indexB)
{
   Gv4 data;

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
func: gvArrayUpdateAt
**************************************************************************************************/
grlAPI Gb gvArrayUpdateAt(GvArray * const a, Gindex const index, Gv const value)
{
   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv1ArrayUpdateAt(Gv1Array * const a, Gindex const index, Gv1 const value)
{
   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv2ArrayUpdateAt(Gv2Array * const a, Gindex const index, Gv2 const value)
{
   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   a->p[index] = value;

   greturn gbTRUE;
}

grlAPI Gb gv4ArrayUpdateAt(Gv4Array * const a, Gindex const index, Gv4 const value)
{
   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE;

   a->p[index] = value;

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
static Gindex _BinarySearch(GvArray const * const a, Gv const value, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gv        data;
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
      data = gvArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
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

static Gindex _BinarySearch1(Gv1Array const * const a, Gv1 const value, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gv1       data;
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
      data = gv1ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
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

static Gindex _BinarySearch2(Gv2Array const * const a, Gv2 const value, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gv2       data;
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
      data = gv2ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
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

static Gindex _BinarySearch4(Gv4Array const * const a, Gv4 const value, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gv4       data;
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
      data = gv4ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
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
static Gindex _LinearSearch(GvArray const * const a, Gv const value, Gb const findLocation)
{
   Gindex    index;
   Gv        data;
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
      data = gvArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
      greturnValIf(compare == gcompareEQUAL, index);

      greturnValIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnValIf(findLocation, -(a->count));

   greturn GindexERROR;
}

static Gindex _LinearSearch1(Gv1Array const * const a, Gv1 const value, Gb const findLocation)
{
   Gindex    index;
   Gv1       data;
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
      data = gv1ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
      greturnValIf(compare == gcompareEQUAL, index);

      greturnValIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnValIf(findLocation, -(a->count));

   greturn GindexERROR;
}

static Gindex _LinearSearch2(Gv2Array const * const a, Gv2 const value, Gb const findLocation)
{
   Gindex    index;
   Gv2       data;
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
      data = gv2ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
      greturnValIf(compare == gcompareEQUAL, index);

      greturnValIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnValIf(findLocation, -(a->count));

   greturn GindexERROR;
}

static Gindex _LinearSearch4(Gv4Array const * const a, Gv4 const value, Gb const findLocation)
{
   Gindex    index;
   Gv4       data;
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
      data = gv4ArrayGetAt(a, index);

      compare = a->compareFunc(&value, &data);
      greturnValIf(compare == gcompareEQUAL, index);

      greturnValIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnValIf(findLocation, -(a->count));

   greturn GindexERROR;
}
