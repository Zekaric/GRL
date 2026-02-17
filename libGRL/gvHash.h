/**************************************************************************************************
file:       gvHash
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
GvHash and name table to mimic Galaxy vname and vdict functionality
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

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
/**************************************************************************************************
type: GhashSize

The size of the GvHash table when created.  Convenient prime
numbers.

Enumeration
**************************************************************************************************/
typedef enum
{
   ghashSize10   = 11,
   ghashSize20   = 23,
   ghashSize30   = 31,
   ghashSize40   = 41,
   ghashSize50   = 53,
   ghashSize60   = 61,
   ghashSize70   = 71,
   ghashSize80   = 83,
   ghashSize90   = 89,
   ghashSize100  = 101,
   ghashSize200  = 211,
   ghashSize300  = 307,
   ghashSize400  = 401,
   ghashSize500  = 503,
   ghashSize600  = 601,
   ghashSize700  = 701,
   ghashSize800  = 809,
   ghashSize900  = 907,
   ghashSize1K   = 1009,
   ghashSize2K   = 2039,
   ghashSize4K   = 4093,
   ghashSize8K   = 8191,
   ghashSize10K  = 16381,
   ghashSize30K  = 32749,
   ghashSize60K  = 65521,
   ghashSize100K = 131071,
   ghashSize200K = 262139,
   ghashSize500K = 524287,
   ghashSize1M   = 1048573,
   ghashSize2M   = 2097143,
   ghashSize4M   = 4194301,
   ghashSize8M   = 8388593,
   ghashSize10M  = 16777213,
   ghashSize30M  = 33554393,
   ghashSize60M  = 67108859,
   ghashSize100M = 134217689,
   ghashSize200M = 268435399,
   ghashSize500M = 536870909,
   ghashSize1G   = 1073741789,
   ghashSize2G   = 2147483647
} GhashSize;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc        hashFunc;
   GrlCompareFunc     compareFunc;
   GvList            *binArray;
   GhashSize          binCount;
} GvHash;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gvHashCloc(             TYPE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)   gleakClocType(gvHashCloc_(               (Char *) TYPE, (COMPARE_FUNC), (HASH_FUNC), (HASHSIZE)), GvHash)
#define gvHashClocContent(HASH, TYPE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                 gvHashClocContent_(  HASH, (Char *) TYPE, (COMPARE_FUNC), (HASH_FUNC), (HASHSIZE))

grlAPI Gb       gvHashAdd(             GvHash       * const hash, Gv const value);

grlAPI GvHash  *gvHashCloc_(                                      Char const * const typeName, GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc, GhashSize const hashSize);
grlAPI Gb       gvHashClocContent_(    GvHash       * const hash, Char const * const typeName, GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc, GhashSize const hashSize);

grlAPI void     gvHashDloc(            GvHash       * const hash);
grlAPI void     gvHashDlocContent(     GvHash       * const hash);

grlAPI Gb       gvHashErase(           GvHash       * const hash, Gv const value);

grlAPI Gv       gvHashFind(            GvHash const * const hash, Gv const value);
grlAPI void     gvHashFlush(           GvHash       * const hash);
grlAPI Gb       gvHashForEach(         GvHash const * const hash, GrlForEachFunc const func);

grlAPI Gcount   gvHashGetCount(        GvHash const * const hash);

grlAPI Gb       gvHashUpdate(          GvHash const * const hash, Gv const value);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
