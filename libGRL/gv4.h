/**************************************************************************************************
file:       Gv4
author:     Robbert de Groot
copyright:  2020, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2020, Robbert de Groot

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
prototype
**************************************************************************************************/
grlAPI Gcompare   gv4CompareI(   Gv4 const * const va, Gv4 const * const vb);
grlAPI Gcompare   gv4CompareN(   Gv4 const * const va, Gv4 const * const vb);
grlAPI Gcompare   gv4CompareR(   Gv4 const * const va, Gv4 const * const vb);

grlAPI Gv4        gv4FromChar(   Gchar  const letter);
grlAPI Gv4        gv4FromIndex(  Gindex const index);

grlAPI GhashN     gv4Hash(       Gv4 const * const v);

#define gv4GetChar( V)        (V).c
#define gv4GetB(    V)        (V).b
#define gv4GetI(    V)        (V).i
#define gv4GetN(    V)        (V).n
#define gv4GetR(    V)        (V).r
#define gv4pGetChar(V)        (V)->c
#define gv4pGetB(   V)        (V)->b
#define gv4pGetI(   V)        (V)->i
#define gv4pGetN(   V)        (V)->n
#define gv4pGetR(   V)        (V)->r

#define gv4SetChar( V, VAL)   ((V).c  = VAL, (V))
#define gv4SetB(    V, VAL)   ((V).b  = VAL, (V))
#define gv4SetI(    V, VAL)   ((V).i  = VAL, (V))
#define gv4SetN(    V, VAL)   ((V).n  = VAL, (V))
#define gv4SetR(    V, VAL)   ((V).r  = VAL, (V))
#define gv4pSetChar(V, VAL)   ((V)->c = VAL, (V))
#define gv4pSetB(   V, VAL)   ((V)->b = VAL, (V))
#define gv4pSetI(   V, VAL)   ((V)->i = VAL, (V))
#define gv4pSetN(   V, VAL)   ((V)->n = VAL, (V))
#define gv4pSetR(   V, VAL)   ((V)->r = VAL, (V))

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
