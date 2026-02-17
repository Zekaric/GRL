/**************************************************************************************************
file:       gtime
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
base time functions
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

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
constant:
**************************************************************************************************/
typedef enum
{
   GtimeDST_UNKNOWN = -1,
   GtimeDST_INACTIVE,
   GtimeDST_ACTIVE
} GtimeDST;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gi Gtime;

/**************************************************************************************************
prototype:
**************************************************************************************************/
grlAPI Gtime gtimeGet(     void);
grlAPI Gb    gtimeGetTime( Gtime const timeValue, Gb const isLocalTime, Gi4 * const year, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second, Gi4 * const nanoSecond);

// Start and Stop called in grlStart and grtStop
       Gb    gtimeStart(   void);
       void  gtimeStop(    void);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
