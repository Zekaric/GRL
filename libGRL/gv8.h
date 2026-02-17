/**************************************************************************************************
file:       Gv8
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
#define gv8CompareI      gvCompareI
#define gv8CompareN      gvCompareN
#define gv8CompareR      gvCompareR
#define gv8CompareS      gvCompareS

#define gv8Hash          gvHash

#define gv8GetB(V)       gvGetB(V)
#define gv8GetI(V)       gvGetI(V)
#define gv8GetN(V)       gvGetN(V)
#define gv8GetP(V)       gvGetP(V)
#define gv8GetR(V)       gvGetR(V)
#define gv8GetS(V)       gvGetS(V)
#define gv8pGetB(V)      gvpGetB(V)
#define gv8pGetI(V)      gvpGetI(V)
#define gv8pGetN(V)      gvpGetN(V)
#define gv8pGetP(V)      gvpGetP(V)
#define gv8pGetR(V)      gvpGetR(V)
#define gv8pGetS(V)      gvpGetS(V)

#define gv8SetB(V, VAL)  gvSetB(V, VAL)
#define gv8SetI(V, VAL)  gvSetI(V, VAL)
#define gv8SetN(V, VAL)  gvSetN(V, VAL)
#define gv8SetP(V, VAL)  gvSetP(V, VAL)
#define gv8SetR(V, VAL)  gvSetR(V, VAL)
#define gv8SetS(V, VAL)  gvSetS(V, VAL)
#define gv8pSetB(V, VAL) gvpSetB(V, VAL)
#define gv8pSetI(V, VAL) gvpSetI(V, VAL)
#define gv8pSetN(V, VAL) gvpSetN(V, VAL)
#define gv8pSetP(V, VAL) gvpSetP(V, VAL)
#define gv8pSetR(V, VAL) gvpSetR(V, VAL)
#define gv8pSetS(V, VAL) gvpSetS(V, VAL)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
