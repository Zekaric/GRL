/**************************************************************************************************
file:       Gv
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
grlAPI Gcompare   gvCompareI( Gv const * const va, Gv const * const vb);
grlAPI Gcompare   gvCompareN( Gv const * const va, Gv const * const vb);
grlAPI Gcompare   gvCompareR( Gv const * const va, Gv const * const vb);
grlAPI Gcompare   gvCompareS( Gv const * const va, Gv const * const vb);

grlAPI Gv         gvFromIndex(Gindex const value);
grlAPI Gv         gvFromP(    Gp * const value);

grlAPI GhashN     gvHash(     Gv const * const v);

#define gvGetB( V)      (V).b
#define gvGetI( V)      (V).i
#define gvGetN( V)      (V).n
#define gvGetP( V)      (V).p
#define gvGetR( V)      (V).r
#define gvGetS( V)      (V).s
#define gvpGetB(V)      (V)->b
#define gvpGetI(V)      (V)->i
#define gvpGetN(V)      (V)->n
#define gvpGetP(V)      (V)->p
#define gvpGetR(V)      (V)->r
#define gvpGetS(V)      (V)->s

#define gvSetB( V, VAL) ((V).b  = VAL, (V))
#define gvSetI( V, VAL) ((V).i  = VAL, (V))
#define gvSetN( V, VAL) ((V).n  = VAL, (V))
#define gvSetP( V, VAL) ((V).p  = VAL, (V))
#define gvSetR( V, VAL) ((V).r  = VAL, (V))
#define gvSetS( V, VAL) ((V).s  = VAL, (V))
#define gvpSetB(V, VAL) ((V)->b = VAL, (V))
#define gvpSetI(V, VAL) ((V)->i = VAL, (V))
#define gvpSetN(V, VAL) ((V)->n = VAL, (V))
#define gvpSetP(V, VAL) ((V)->p = VAL, (V))
#define gvpSetR(V, VAL) ((V)->r = VAL, (V))
#define gvpSetS(V, VAL) ((V)->s = VAL, (V))

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
