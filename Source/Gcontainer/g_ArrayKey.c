/******************************************************************************
file:         G_ArrayKey
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
dynamic array.
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

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

/******************************************************************************
local:
prototype:
******************************************************************************/
static Gindex _BinarySearch(G_ArrayKey const * const a, Gkey const * const value, Gb const findLocation);
static Gindex _LinearSearch(G_ArrayKey const * const a, Gkey const * const value, Gb const findLocation);

/******************************************************************************
global:
function:
******************************************************************************/
grlAPI Gb g_ArrayKeyAdd(G_ArrayKey * const a, Gkey const * const key, Gp const * const value)
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
      index  = _BinarySearch(a, key, gbTRUE);
      
      result = g_ArrayKeyAddAt(a, gABS(index), key, value);
      
      // AddAt turns this off but sort order has not been
      // violated so turn it back on.
      a->isSorted = gbTRUE; //lint !e641
      
      greturn result;
   }

   // if the array is not sorted or no longer sorted then just append.
   result = g_ArrayKeyAddEnd(a, key, value);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyAddAt
******************************************************************************/
grlAPI Gb g_ArrayKeyAddAt(G_ArrayKey * const a, Gindex const index, Gkey const * const key, 
   Gp const * const value)
{
   Gsize  size;
   Gn1   *ps,
         *pd;

   genter;

   greturnFalseIf(
      !a ||
      index < 0);

   if (!g_ArrayKeySetCount(a, gMAX(index, a->count) + 1))
   {
      debugHalt("g_ArrayKeySetCount failed");
      greturn gbFALSE;
   }

   // Use of this function marks the array as unsorted.
   a->isSorted = gbFALSE; //lint !e641

   size = (a->typeSize + gsizeof(Gkey *));
   ps   = &(a->p[index * size]);
   // if the index is somewhere inside the array then move the other elements
   // out of the way.
   if (index < a->count - 1)
   {
      pd = &(a->p[(index + 1) * size]);

      greturnFalseIf(!gmemCopyOver(ps, size * ((a->count - index) - 1), pd)); 
   }

   if (value)
   {
      greturnFalseIf(!gmemCopyOver(key,   sizeof(Gkey *), ps));
      greturnFalseIf(!gmemCopyOver(value, size,           ps + gsizeof(Gkey *))); 
   }
   else
   {
      gmemClear(ps, size);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_ArrayKeyAddBegin
******************************************************************************/
grlAPI Gb g_ArrayKeyAddBegin(G_ArrayKey * const a, Gkey const * const key, Gp const * const value)
{
   Gb result;
   
   genter;
   
   result = g_ArrayKeyAddAt(a, 0, key, value);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyAddEnd
******************************************************************************/
grlAPI Gb g_ArrayKeyAddEnd(G_ArrayKey * const a, Gkey const * const key, Gp const * const value)
{
   Gb result;

   genter;
   
   result = g_ArrayKeyAddAt(a, g_ArrayKeyGetCount(a), key, value);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyClear
******************************************************************************/
grlAPI Gb g_ArrayKeyClear(G_ArrayKey * const a, Gcount const count, Gindex const index)
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
   size = (a->typeSize + gsizeof(Gkey *));

   gmemClearAt(a->p, ctemp * size, index * size);

   greturn gbTRUE;
}

/******************************************************************************
func: g_ArrayKeyCopy
******************************************************************************/
grlAPI Gb g_ArrayKeyCopy(G_ArrayKey * const a, Gcount const count, Gindex const indexSrc,
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

   size = (a->typeSize + gsizeof(Gkey *));

   result = gmemCopy(a->p, ctemp * size, indexSrc * size, indexDst * size);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyCopyFrom
******************************************************************************/
grlAPI Gb g_ArrayKeyCopyFrom(G_ArrayKey * const aDst, Gindex const indexDst, 
   G_ArrayKey const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gb     result;
   Gsize  size;
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnIf(aDst == aSrc, g_ArrayKeyCopy(aDst, count, indexSrc, indexDst));

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

   size = (aDst->typeSize + gsizeof(Gkey *));

   // Use of this function marks the array as unsorted.
   aDst->isSorted = gbFALSE; //lint !e641

   result = gmemCopyOverAt(aSrc->p, ctemp * size, indexSrc * size, aDst->p, indexDst * size);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyCreate_
******************************************************************************/
grlAPI G_ArrayKey *g_ArrayKeyCreate_(Gsize const typeSize, Char const * const typeName,
   Char const * const typeNameSub, GrlCompareFunc const compareFunc,
   Gb const isVectorSizing)
{
   G_ArrayKey *a;

   genter;

   greturnNullIf(
      !typeName    ||
      !typeNameSub ||
      typeSize <= 0);

   a = gmemCreateType(G_ArrayKey);
   greturnNullIf(!a);

   if (!g_ArrayKeyCreateContent_(
         a,
         typeSize,
         typeName,
         typeNameSub,
         compareFunc,
         isVectorSizing))
   {
      g_ArrayKeyDestroy(a);
      greturn NULL;
   }

   greturn a;
}

/******************************************************************************
func: g_ArrayKeyCreateContent
******************************************************************************/
grlAPI Gb g_ArrayKeyCreateContent_(G_ArrayKey * const a, Gsize const typeSize, 
   Char const * const typeName, Char const * const typeNameSub, 
   GrlCompareFunc const compareFunc, Gb const isVectorSizing)
{
   genter;

   greturnFalseIf(
      !a           ||
      !typeName    ||
      !typeNameSub ||
      typeSize <= 0);

   a->baseName       = "G_ArrayKey"; //lint !e916 !e64
   a->typeName       = typeName;
   a->typeNameSub    = typeNameSub;
   a->compareFunc    = compareFunc;
   a->isVectorSizing = (isVectorSizing) ? gbTRUE : gbFALSE;
   a->typeSize       = typeSize;
   a->count          = 0;
   a->countTotal     = g_ArrayVectorSize((Gb) a->isVectorSizing, a->count);

   if (compareFunc)
   {
      a->isSorted = gbTRUE; //lint !e641
   }

   // count can be 0;
   a->p = (Gn1 *) gleakCreate(
      gmemCreate_(typeName, a->countTotal * (a->typeSize + gsizeof(Gkey *))),
      a->countTotal);
   if (!a->p)
   {
      gmemDestroy(a);
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_ArrayKeyDestroy
******************************************************************************/
grlAPI void g_ArrayKeyDestroy(G_ArrayKey * const a)
{
   genter;

   greturnVoidIf(!a);

   g_ArrayKeyDestroyContent(a);
   gmemDestroy(a);

   greturn;
}

/******************************************************************************
func: g_ArrayKeyDestroyContent
******************************************************************************/
grlAPI void g_ArrayKeyDestroyContent(G_ArrayKey const * const a)
{
   genter;

   greturnVoidIf(!a);

   gmemDestroy(a->p);

   greturn;
}

/******************************************************************************
func: g_ArrayKeyErase
******************************************************************************/
grlAPI Gb g_ArrayKeyErase(G_ArrayKey * const a, Gp const * const value)
{
   Gb     result;
   Gindex index;

   genter;

   index = g_ArrayKeyFind(a, value);
   if (index != GindexERROR)
   {
      result = g_ArrayKeyEraseAt(a, 1, index);

      greturn result;
   }

   greturn gbFALSE;
}

/******************************************************************************
func: g_ArrayKeyEraseAt
******************************************************************************/
grlAPI Gb g_ArrayKeyEraseAt(G_ArrayKey * const a, Gcount const count, Gindex const index)
{
   Gsize  size;
   Gcount ctemp;

   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count < 0 ||
      index < 0 || a->count <= index);

   size  = a->typeSize + gsizeof(Gkey *);
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
            (a->count - (index + ctemp)) * size,
                        (index + ctemp)  * size,
                         index           * size))
      {
         debugHalt("g_ArrayKeyemCopy failed");
      }
   }

   gmemClearAt(
      a->p,
      ctemp              * size,
      (a->count - ctemp) * size);
   
   if (!g_ArrayKeySetCount(a, a->count - ctemp))
   {
      debugHalt("g_ArrayKeySetCount failed");
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_ArrayKeyEraseBegin
******************************************************************************/
grlAPI void g_ArrayKeyEraseBegin(G_ArrayKey * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   g_ArrayKeyEraseAt(a, 1, 0); //lint !e534

   greturn;
}

/******************************************************************************
func: g_ArrayKeyEraseEnd
******************************************************************************/
grlAPI void g_ArrayKeyEraseEnd(G_ArrayKey * const a)
{
   genter;

   // shrinking the array shouldn't cause harm.
   g_ArrayKeyEraseAt(a, 1, g_ArrayKeyGetCount(a) - 1); //lint !e534

   greturn;
}

/******************************************************************************
func: g_ArrayKeyFind
******************************************************************************/
grlAPI Gindex g_ArrayKeyFind(G_ArrayKey const * const a, Gkey const * const key)
{
   Gindex result;

   genter;

   greturnIf(
         !a              ||
         !a->compareFunc ||
         a->count == 0   ||
         !key,
      GindexERROR);

   if (a->isSorted)
   {
      result = _BinarySearch(a, key, gbFALSE);

      greturn result;
   }

   result = _LinearSearch(a, key, gbFALSE);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyFlush
******************************************************************************/
grlAPI void g_ArrayKeyFlush(G_ArrayKey * const a)
{
   genter;

   greturnVoidIf(!a);

   g_ArrayKeySetCount(a, 0); //lint !e534

   if (a->compareFunc)
   {
      a->isSorted = gbTRUE; //lint !e641
   }

   greturn;
}

/******************************************************************************
func: g_ArrayKeyForEach
******************************************************************************/
grlAPI Gb g_ArrayKeyForEach(G_ArrayKey const * const a, GrlForEachKeyFunc const func)
{
   Gsize        size;
   Gi4          index;
   Gkey const  *key;
   Gp          *value;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   size = a->typeSize + gsizeof(Gkey *);

   forCount(index, a->count)
   {
      key   = (Gkey const *) &(a->p[index * size]);
      value = (Gp *) &(a->p[index * size + gsizeof(Gkey *)]);
      func(key, value);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_ArrayKeyGet
******************************************************************************/
grlAPI Gp *g_ArrayKeyGet(G_ArrayKey const * const a)
{
   genter;

   greturnNullIf(!a);

   greturn a->p;
}

/******************************************************************************
func: g_ArrayKeyGetAt
******************************************************************************/
grlAPI Gp *g_ArrayKeyGetAt(G_ArrayKey const * const a, Gindex const index)
{
   genter;

   greturnNullIf(
      !a        ||
      index < 0 || a->count <= index);

   greturn &(a->p[index * (a->typeSize + gsizeof(Gkey *)) + gsizeof(Gkey *)]);
}

/******************************************************************************
func: g_ArrayKeyGetAtKey
******************************************************************************/
grlAPI Gkey const *g_ArrayKeyGetAtKey(G_ArrayKey const * const a, Gindex const index)
{
   genter;

   greturnNullIf(
      !a        ||
      index < 0 || a->count <= index);

   greturn &(a->p[index * (a->typeSize + gsizeof(Gkey *))]);
}

/******************************************************************************
func: g_ArrayKeyGetBegin
******************************************************************************/
grlAPI Gp *g_ArrayKeyGetBegin(G_ArrayKey const * const a)
{
   Gp *result;

   genter;
   
   result = g_ArrayKeyGetAt(a, 0);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyGetBeginKey
******************************************************************************/
grlAPI Gkey const *g_ArrayKeyGetBeginKey(G_ArrayKey const * const a)
{
   Gkey const *result;

   genter;
   
   result = g_ArrayKeyGetAtKey(a, 0);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyGetCount
******************************************************************************/
grlAPI Gcount g_ArrayKeyGetCount(G_ArrayKey const * const a)
{
   genter;

   greturnIf(!a, 0);

   greturn a->count;
}

/******************************************************************************
func: g_ArrayKeyGetSize
******************************************************************************/
grlAPI Gsize g_ArrayKeyGetSize(G_ArrayKey const * const a)
{
   genter;

   greturnIf(!a, 0);

   greturn a->typeSize;
}

/******************************************************************************
func: g_ArrayKeyGetEnd
******************************************************************************/
grlAPI Gp *g_ArrayKeyGetEnd(G_ArrayKey const * const a)
{
   Gp *result;

   genter;
   
   result = g_ArrayKeyGetAt(a, a->count - 1);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeyGetEndKey
******************************************************************************/
grlAPI Gkey const *g_ArrayKeyGetEndKey(G_ArrayKey const * const a)
{
   Gkey const *result;

   genter;
   
   result = g_ArrayKeyGetAtKey(a, a->count - 1);

   greturn result;
}

/******************************************************************************
func: g_ArrayKeySetCount
******************************************************************************/
grlAPI Gb g_ArrayKeySetCount(G_ArrayKey * const a, Gcount const value)
{
   Gsize  size;
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

   size       = a->typeSize + gsizeof(Gkey *);
   countTotal = g_ArrayVectorSize((Gb) a->isVectorSizing, value);

   result = gbTRUE;
   if (countTotal != a->countTotal)
   {
      p      = gmemCreate(a->typeName, countTotal * size);

      result = gmemCopyOver(a->p, gMIN(value, a->count) * size, p);

      gmemDestroy(a->p);
      a->p = (Gn1 *) p;
   }

   a->count      = value;
   a->countTotal = countTotal;

   greturn result;
}

/******************************************************************************
func: g_ArrayKeySort
******************************************************************************/
grlAPI Gb g_ArrayKeySort(G_ArrayKey * const a)
{
   Gheap heap;

   genter;

   greturnFalseIf(
      !a ||
      !a->compareFunc);

   heap = gheapSetData(
      a->count,
      (Gp *) a,
      (GrlGetFunc)  g_ArrayKeyGetAtKey, //lint !e960 !e929
      (GrlSwapFunc) g_ArrayKeySwap, //lint !e960 !e929
      a->compareFunc);

   a->isSorted = gheapSort(&heap); //lint !e641

   greturn (Gb) a->isSorted;  //lint !e930
}

/******************************************************************************
func: g_ArrayKeySwap
******************************************************************************/
grlAPI Gb g_ArrayKeySwap(G_ArrayKey * const a, Gindex const indexA, Gindex const indexB)
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

   size = (a->typeSize + gsizeof(Gkey *));
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

/******************************************************************************
func: g_ArrayKeyUpdateAt
******************************************************************************/
grlAPI Gb g_ArrayKeyUpdateAt(G_ArrayKey * const a, Gindex const index, Gp const * const value)
{
   Gsize  size;
   Gn1   *p;

   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count <= index);

   size = a->typeSize;

   p = &(a->p[index * (size + gsizeof(Gkey *)) + gsizeof(Gkey *)]);
   greturnFalseIf(!gmemCopyOver(value, size, p)); //lint !e960 !e9005

   greturn gbTRUE;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _BinarySearch

Binary search for the item or location where the item should be inserted.
******************************************************************************/
static Gindex _BinarySearch(G_ArrayKey const * const a, Gkey const * const key, Gb const findLocation)
{
   Gindex    hi,
             lo,
             index;
   Gp const *data;
   Gcompare  compare;

   genter;

   if (a->count == 0)
   {
      greturnIf(findLocation, 0);
      greturn -1;
   }

   hi = a->count - 1;
   lo = 0;
   loop
   {
      // Find the mid point.
      index = (hi + lo) / 2;

      // Compare.  If equal then return the index.
      data = g_ArrayKeyGetAtKey(a, index);

      compare = a->compareFunc(key, data);
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
   
   greturn -1;
}

/******************************************************************************
func: _LinearSearch
******************************************************************************/
static Gindex _LinearSearch(G_ArrayKey const * const a, Gkey const * const key, Gb const findLocation)
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
      greturn -1;
   }

   // Linear search for the item.
   forCount(index, a->count)
   {
      data = g_ArrayKeyGetAtKey(a, index);

      compare = a->compareFunc(key, data);
      greturnIf(compare == gcompareEQUAL, index);

      greturnIf(
            findLocation &&
            compare == gcompareGREATER_THAN,
         -(index - 1));
   }

   greturnIf(findLocation, -(a->count));

   greturn -1;
}
