/******************************************************************************
file:       g_HashKey
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
G_HashKey and name table to mimic Galaxy vname and vdict functionality
******************************************************************************/

/******************************************************************************
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
******************************************************************************/

#if !defined(G_HASHKEYH)
#define      G_HASHKEYH

/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   GCONTAINER_VAR

   G_ListKey        **binArray;
   GhashSize          binCount;
} G_HashKey;

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_HashKeyCreate(TYPE, TYPE_SUB, HASHSIZE) \
   ((G_HashKey *)  gleakCreate(g_HashKeyCreate_(gsizeof(TYPE_SUB), #TYPE, #TYPE_SUB, (HASHSIZE)), gsizeof(G_HashKey)))
//lint -restore

grlAPI Gb          g_HashKeyAdd(             G_HashKey       * const hash, Gkey const * const key, Gp const * const value);

grlAPI G_HashKey  *g_HashKeyCreate_(                                       Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GhashSize const hashSize);
grlAPI Gb          g_HashKeyCreateContent(   G_HashKey       * const hash, Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GhashSize const hashSize);

grlAPI void        g_HashKeyDestroy(         G_HashKey       * const hash);
grlAPI void        g_HashKeyDestroyContent(  G_HashKey       * const hash);

grlAPI Gb          g_HashKeyErase(           G_HashKey       * const hash, Gkey const * const key);

grlAPI Gp         *g_HashKeyFind(            G_HashKey const * const hash, Gkey const * const key);
grlAPI void        g_HashKeyFlush(           G_HashKey       * const hash);
grlAPI Gb          g_HashKeyForEach(         G_HashKey const * const hash, GrlForEachKeyFunc const func);

grlAPI Gcount      g_HashKeyGetCount(        G_HashKey const * const hash);

grlAPI Gb          g_HashKeyUpdate(          G_HashKey const * const hash, Gkey const * const key, Gp const * const value);

#endif
