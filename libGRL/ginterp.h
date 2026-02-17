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
   Gi4 incOne,
       incBoth,
       x1,
       x2,
       xstart,
       xend,
       xdelta,
       xinc,
       y1,
       y2,
       ystart,
       yend,
       ydelta,
       yinc,
       delta;
   Gb  isDone,
       isHalfDone,
       isFlipped;
} GinterpI;

/**************************************************************************************************
prototype:
**************************************************************************************************/
grlAPI void  ginterpIGetNext(    GinterpI       * const i);
grlAPI Gi4   ginterpIGetX1(      GinterpI const * const i);
grlAPI Gi4   ginterpIGetX2(      GinterpI const * const i);
grlAPI Gi4   ginterpIGetY1(      GinterpI const * const i);
grlAPI Gi4   ginterpIGetY2(      GinterpI const * const i);

grlAPI Gb    ginterpIIsDone(     GinterpI const * const i);
grlAPI Gb    ginterpIIsDoneHalf( GinterpI const * const i);

grlAPI Gb    ginterpISet(        GinterpI * const i, Gi4 const xstart, Gi4 const ystart, Gi4 const xend, Gi4 const yend);
grlAPI Gb    ginterpISkip(       GinterpI * const i, Gi4 const count);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
