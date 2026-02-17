/**************************************************************************************************
file:       Gv2
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
grlAPI Gcompare   gv2CompareI(Gv2 const * const va, Gv2 const * const vb);
grlAPI Gcompare   gv2CompareN(Gv2 const * const va, Gv2 const * const vb);

grlAPI GhashN     gv2Hash(    Gv2 const * const v);

#define gv2GetB(V)       (V).b
#define gv2GetI(V)       (V).i
#define gv2GetN(V)       (V).n
#define gv2pGetB(V)      (V)->b
#define gv2pGetI(V)      (V)->i
#define gv2pGetN(V)      (V)->n

#define gv2SetB(V, VAL)  ((V).b = VAL, (V))
#define gv2SetI(V, VAL)  ((V).i = VAL, (V))
#define gv2SetN(V, VAL)  ((V).n = VAL, (V))
#define gv2pSetB(V, VAL) ((V)->b = VAL, (V))
#define gv2pSetI(V, VAL) ((V)->i = VAL, (V))
#define gv2pSetN(V, VAL) ((V)->n = VAL, (V))

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
