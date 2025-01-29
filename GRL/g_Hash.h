/**************************************************************************************************
file:       g_Hash
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
G_Hash and name table to mimic Galaxy vname and vdict functionality
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) 2000, Robbert de Groot
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************************************/

#if !defined(G_HASHH)
#define      G_HASHH

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

The size of the G_Hash table when created.  Convenient prime
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
   GCONTAINER_VAR

   GrlHashFunc        hashFunc;
   GrlCompareFunc     compareFunc;
   G_List           **binArray;
   GhashSize          binCount;
} G_Hash;

/**************************************************************************************************
prototype:
**************************************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_HashCloc(             TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC, HASH_FUNC, HASHSIZE) ((G_Hash *)  gleakCloc((Gp *) g_HashCloc_(               gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (COMPARE_FUNC), (HASH_FUNC), (HASHSIZE)), gsizeof(G_Hash)))
#define g_HashClocContent(HASH, TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                               g_HashClocContent_(  HASH, gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (COMPARE_FUNC), (HASH_FUNC), (HASHSIZE))
//lint -restore

grlAPI Gb       g_HashAdd(             G_Hash       * const hash, Gp const * const value);

grlAPI G_Hash  *g_HashCloc_(                                      Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc, GhashSize const hashSize);
grlAPI Gb       g_HashClocContent_(    G_Hash       * const hash, Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc, GhashSize const hashSize);

grlAPI void     g_HashDloc(            G_Hash       * const hash);
grlAPI void     g_HashDlocContent(     G_Hash       * const hash);

grlAPI Gb       g_HashErase(           G_Hash       * const hash, Gp const * const value);

grlAPI Gp      *g_HashFind(            G_Hash const * const hash, Gp const * const value);
grlAPI void     g_HashFlush(           G_Hash       * const hash);
grlAPI Gb       g_HashForEach(         G_Hash const * const hash, GrlForEachFunc const func);

grlAPI Gcount   g_HashGetCount(        G_Hash const * const hash);

grlAPI Gb       g_HashUpdate(          G_Hash const * const hash, Gp const * const value);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
