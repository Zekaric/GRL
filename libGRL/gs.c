/**************************************************************************************************
file:         Gs
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
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gsAddAt
**************************************************************************************************/
grlAPI Gb gsAddAt(Gs * const a, Gindex const index, Gchar const value)
{
   genter;

   // Remove the null-terminator.
   a->count -= 1;

   greturnFalseIf(!gv4ArrayAddAt(a, index, gv4FromChar(value)));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsAddBegin
**************************************************************************************************/
grlAPI Gb gsAddBegin(Gs * const a, Gchar const value)
{
   genter;

   greturn gsAddAt(a, 0, value);
}

/**************************************************************************************************
func: gsAddEnd
**************************************************************************************************/
grlAPI Gb gsAddEnd(Gs * const a, Gchar const value)
{
   genter;

   // Overwrite the null-terminator.
   gv4SetN(a->p[a->count - 1], value);

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsCloc_
**************************************************************************************************/
grlAPI Gs *gsCloc_(void)
{
   Gv4Array *a;

   genter;

   a = gv4ArrayCloc_((Char *) "Gs", NULL, gbTRUE);
   greturnNullIf(!a);

   // Add the null-terminator.
   if (!gv4ArrayAddEnd(a, gv4FromChar(0)))
   {
      gv4ArrayDloc(a);
      greturn NULL;
   }

   greturn (Gs *) a;
}

/**************************************************************************************************
func: gsClocContent
**************************************************************************************************/
grlAPI Gb gsClocContent(Gs * const a)
{
   genter;

   greturnFalseIf(!gv4ArrayClocContent(a, "Gs", NULL, gbTRUE));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsCopy
**************************************************************************************************/
grlAPI Gb gsCopy(Gs * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst)
{
   genter;

   // Remove the null-terminator.
   a->count -= 1;

   greturnFalseIf(!gv4ArrayCopy(a, count, indexSrc, indexDst));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsCopyFrom
**************************************************************************************************/
grlAPI Gb gsCopyFrom(Gs * const aDst, Gindex const indexDst,
   Gs const * const aSrc, Gcount const count, Gindex const indexSrc)
{
   Gcount ctemp;

   genter;

   greturnFalseIf(
      !aDst ||
      !aSrc);

   greturnTrueIf(count == 0);

   greturnValIf(aDst == aSrc, gsCopy(aDst, count, indexSrc, indexDst));

   greturnFalseIf(
      count    < 0 ||
      indexDst < 0 || aDst->count - 1 <  indexDst ||
      indexSrc < 0 || aSrc->count - 1 <= indexSrc);

   // Remove the null-terminator.
   aDst->count -= 1;

   ctemp = count;
   if (indexSrc + count >= aSrc->count)
   {
      ctemp = aSrc->count - 1 - indexSrc;
   }
   if (indexDst + count >= aDst->count)
   {
      ctemp = aDst->count     - indexDst;
   }

   greturnFalseIf(!gmemCopyOverTypeArrayAt(aDst->p, Gv4, ctemp, indexDst, aSrc->p, indexSrc));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(aDst, gv4FromChar(0));
}

/**************************************************************************************************
func: gsDloc
**************************************************************************************************/
grlAPI void gsDloc(Gs * const a)
{
   genter;

   gv4ArrayDloc(a);

   greturn;
}

/**************************************************************************************************
func: gsDlocContent
**************************************************************************************************/
grlAPI void gsDlocContent(Gs const * const a)
{
   genter;

   gv4ArrayDlocContent(a);

   greturn;
}

/**************************************************************************************************
func: gsDlocContainer
**************************************************************************************************/
grlAPI void gsDlocContainer(Gv const * const v)
{
   genter;

   gsDloc(gvpGetS(v));

   greturn;
}

/**************************************************************************************************
func: gsEraseAt
**************************************************************************************************/
grlAPI Gb gsEraseAt(Gs * const a, Gcount const count, Gindex const index)
{
   genter;

   greturnFalseIf(!a);

   greturnTrueIf(count == 0);

   greturnFalseIf(
      count < 0 ||
      index < 0 || a->count - 1 <= index);

   // Remove the null-terminator.
   a->count -= 1;

   greturnFalseIf(!gv4ArrayEraseAt(a, count, index));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsEraseBegin
**************************************************************************************************/
grlAPI Gb gsEraseBegin(Gs * const a, Gcount const count)
{
   genter;

   // Remove the null-terminator.
   a->count -= 1;

   // shrinking the array shouldn't cause harm.
   greturnFalseIf(!gv4ArrayEraseAt(a, count, 0));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsEraseEnd
**************************************************************************************************/
grlAPI Gb gsEraseEnd(Gs * const a, Gcount const count)
{
   genter;

   // Remove the null-terminator.
   a->count -= 1;

   // shrinking the array shouldn't cause harm.
   greturnFalseIf(!gv4ArrayEraseAt(a, count, a->count - 1));

   // Add the null-terminator.
   greturn gv4ArrayAddEnd(a, gv4FromChar(0));
}

/**************************************************************************************************
func: gsFind
**************************************************************************************************/
grlAPI Gindex gsFind(Gs const * const a, Gchar const value)
{
   genter;

   greturn gv4ArrayFind(a, gv4FromChar(value));
}

/**************************************************************************************************
func: gsFlush
**************************************************************************************************/
grlAPI void gsFlush(Gs * const a)
{
   genter;

   greturnIf(!a);

   // Remove everything but one character for the null-terminator.
   gv4ArraySetCount(a, 1);

   // Set the null-terminator.
   a->p[0].n = 0;

   greturn;
}

/**************************************************************************************************
func: gsForEach
**************************************************************************************************/
grlAPI Gb gsForEach(Gs const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCount(index, a->count - 1)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsForEachDown

Perform the for each in reverse over the array.  This is for those times when you are removing items
from the array or similar order is necessary.
**************************************************************************************************/
grlAPI Gb gsForEachDown(Gs const * const a, GrlForEachFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !a ||
      !func);

   forCountDown(index, a->count - 1)
   {
      func(&a->p[index]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsGet
**************************************************************************************************/
grlAPI Gchar const *gsGet(Gs const * const a)
{
   genter;

   greturn (Gchar const *) a->p;
}

/**************************************************************************************************
func: gsGetAt
**************************************************************************************************/
grlAPI Gchar gsGetAt(Gs const * const a, Gindex const index)
{
   genter;

   greturn gv4ArrayGetAt(a, index).n;
}

/**************************************************************************************************
func: gsGetBegin
**************************************************************************************************/
grlAPI Gchar gsGetBegin(Gs const * const a)
{
   genter;

   greturn a->p[0].n;
}

/**************************************************************************************************
func: gsGetCount
**************************************************************************************************/
grlAPI Gcount gsGetCount(Gs const * const a)
{
   genter;

   // Subtract one for the null-terminator.
   greturn a->count - 1;
}

/**************************************************************************************************
func: gsGetEnd
**************************************************************************************************/
grlAPI Gchar gsGetEnd(Gs const * const a)
{
   genter;

   greturn0If(a->count == 1);

   // null-terminator is at count - 1, so last real item is at count - 2.
   greturn gv4ArrayGetAt(a, a->count - 2).n;
}

/**************************************************************************************************
func: gsSetCount
**************************************************************************************************/
grlAPI Gb gsSetCount(Gs * const a, Gcount const value)
{
   genter;

   greturnFalseIf(!gv4ArraySetCount(a, value + 1));

   // Ensure the null-terminator.
   a->p[a->count - 1].n = 0;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsSwap
**************************************************************************************************/
grlAPI Gb gsSwap(Gs * const a, Gindex const indexA, Gindex const indexB)
{
   Gv4 data;

   genter;

   greturnFalseIf(
      !a         ||
      indexA < 0 || a->count - 1 <= indexA ||
      indexB < 0 || a->count - 1 <= indexB);

   data         = a->p[indexA];
   a->p[indexA] = a->p[indexB];
   a->p[indexB] = data;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsUpdateAt
**************************************************************************************************/
grlAPI Gb gsUpdateAt(Gs * const a, Gindex const index, Gchar const value)
{
   genter;

   greturnFalseIf(
      !a        ||
      index < 0 || a->count - 1 <= index);

   gv4SetN(a->p[index], value);

   greturn gbTRUE;
}
