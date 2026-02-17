/**************************************************************************************************
file:         G_Container
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
The base for a dynamic arrrays.
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

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
// This type is for debugging pursposes.  So you can cast any of the containers to this
// to see what the container actually is.
#define GCONTAINER_VAR                       \
   GTYPE_VAR                                 \
   Gcount                   count

typedef struct
{
   GCONTAINER_VAR;
} GvContainer;

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
