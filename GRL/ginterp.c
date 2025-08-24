/**************************************************************************************************
file:       ginterp
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
prototype:
**************************************************************************************************/
/**************************************************************************************************
func: ginterpIGetNext

Get the next iteration across x.
**************************************************************************************************/
grlAPI void ginterpIGetNext(GinterpI * const i)
{
   genter;

   // Iterating over y
   if (i->isFlipped)
   {
      if (i->y1 == i->yend)
      {
         i->isDone = gbTRUE;
         greturn;
      }

      if (i->delta <= 0)
      {
         i->delta += i->incOne;
         i->y1    += i->yinc;

         if (i->isHalfDone ||
             i->y1 + i->yinc == i->y2)
         {
            i->isHalfDone = gbTRUE;
            greturn;
         }

         i->y2    -= i->yinc;
      }
      else
      {
         i->delta += i->incBoth;
         i->y1    += i->yinc;
         i->x1    += i->xinc;

         if (i->isHalfDone ||
             i->y1 + i->yinc == i->y2)
         {
            i->isHalfDone = gbTRUE;
            greturn;
         }

         i->y2    -= i->yinc;
         i->x2    -= i->xinc;
      }

      if      (i->y1 + i->yinc == i->y2)
      {
         i->isHalfDone = gbTRUE;
      }
      else if (i->y1 == i->yend)
      {
         i->isDone = gbTRUE;
         greturn;
      }
      else
      {
         // Nothing
      }
   }
   // Iterating over x
   else
   {
      if (i->x1 == i->xend)
      {
         i->isDone = gbTRUE;
         greturn;
      }

      if (i->delta <= 0)
      {
         i->delta += i->incOne;
         i->x1    += i->xinc;

         if (i->isHalfDone ||
             i->x1 + i->xinc == i->x2)
         {
            i->isHalfDone = gbTRUE;
            greturn;
         }

         i->x2    -= i->xinc;
      }
      else
      {
         i->delta += i->incBoth;
         i->x1    += i->xinc;
         i->y1    += i->yinc;

         if (i->isHalfDone ||
             i->x1 + i->xinc == i->x2)
         {
            i->isHalfDone = gbTRUE;
            greturn;
         }

         i->x2    -= i->xinc;
         i->y2    -= i->yinc;
      }

      if      (i->x1 + i->xinc == i->x2)
      {
         i->isHalfDone = gbTRUE;
      }
      else if (i->x1 == i->xend)
      {
         i->isDone = gbTRUE;
         greturn;
      }
      else
      {
         // nothing
      }
   }

   greturn;
}

/**************************************************************************************************
func: ginterpIGetX
**************************************************************************************************/
grlAPI Gi4 ginterpIGetX1(GinterpI const * const i)
{
   genter;

   greturn i->x1;
}

grlAPI Gi4 ginterpIGetX2(GinterpI const * const i)
{
   genter;

   greturn i->x2;
}

/**************************************************************************************************
func: ginterpIGetY
**************************************************************************************************/
grlAPI Gi4 ginterpIGetY1(GinterpI const * const i)
{
   genter;

   greturn i->y1;
}

grlAPI Gi4 ginterpIGetY2(GinterpI const * const i)
{
   genter;

   greturn i->y2;
}

/**************************************************************************************************
func: ginterpIIsDone

No more iterations.
**************************************************************************************************/
grlAPI Gb ginterpIIsDone(GinterpI const * const i)
{
   genter;

   greturn i->isDone;
}

/**************************************************************************************************
func: ginterpIIsDoneHalf

If you are working from both ends towards the middle then this flag will be
set when the two meet 1 unit apart.
**************************************************************************************************/
grlAPI Gb ginterpIIsDoneHalf(GinterpI const * const i)
{
   genter;

   greturn i->isDone;
}

/**************************************************************************************************
func: ginterpISet

Set up the structure for interpolating y accross x.
**************************************************************************************************/
grlAPI Gb ginterpISet(GinterpI * const i, Gi4 const xstart, Gi4 const ystart,
   Gi4 const xend, Gi4 const yend)
{
   genter;

   i->x1        =
      i->xstart = xstart;
   i->x2        =
      i->xend   = xend;

   i->y1        =
      i->ystart = ystart;
   i->y2        =
      i->yend   = yend;

   i->xdelta = gABS(xend - xstart);
   i->ydelta = gABS(yend - ystart);

   i->xinc = 1;
   if (xstart > xend)
   {
       i->xinc = -1;
   }

   i->yinc = 1;
   if (ystart > yend)
   {
      i->yinc = -1;
   }

   if (i->ydelta > i->xdelta)
   {
      i->isFlipped = gbTRUE;
      i->incOne    = 2 * i->xdelta;
      i->incBoth   = 2 * (i->xdelta - i->ydelta);
      i->delta     = 2 * i->xdelta - i->ydelta;
   }
   else
   {
      i->isFlipped = gbFALSE;
      i->incOne    = 2 * i->ydelta;
      i->incBoth   = 2 * (i->ydelta - i->xdelta);
      i->delta     = 2 * i->ydelta - i->xdelta;
   }

   i->isDone        =
      i->isHalfDone = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: ginterpISkip

Skip over a few iterations.
**************************************************************************************************/
grlAPI Gb ginterpISkip(GinterpI * const i, Gi4 const count)
{
   Gi4 ctemp;

   genter;

   ctemp = count;

   for (; ctemp > 0; ctemp--)
   {
      ginterpIGetNext(i);
   }

   greturn gbTRUE;
}
