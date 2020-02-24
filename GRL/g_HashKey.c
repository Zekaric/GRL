/******************************************************************************
file:       g_HashKey
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

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

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
local:
prototype:
******************************************************************************/
static Gb _Find(G_HashKey const * const hash, Gkey const * const key, G_ListKey ** const binList, G_ListKeyItem ** const binItem);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: g_HashKeyAdd
******************************************************************************/
grlAPI Gb g_HashKeyAdd(G_HashKey * const hash, Gkey const * const key, Gp const * const value)
{
   G_ListKey     *binList;
   G_ListKeyItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !value);

   // New item
   if (_Find(hash, key, &binList, &binItem))
   {
      greturn gbFALSE;
   }

   // Get the hashed row.
   binItem = g_ListKeyAddEnd(binList, key, value);
   if (!binItem)
   {
      debugHalt("ListAddEnd failed");
      greturn gbFALSE;
   }

   hash->count++;

   greturn gbTRUE;
}

/******************************************************************************
func: g_HashKeyCreate_
******************************************************************************/
grlAPI G_HashKey *g_HashKeyCreate_(Gsize const typeSize, Char const * const typeName, 
   Char const * const typeNameSub, Gb const isPointerType, GhashSize const hashSize)
{
   G_HashKey *hash;

   genter;

   greturnNullIf(
      !typeName    ||
      !typeNameSub ||
      typeSize < 0);

   // Create the hash table.
   hash = gmemCreateType(G_HashKey);
   greturnNullIf(!hash);

   if (!g_HashKeyCreateContent_(
         hash,
         typeSize,
         typeName,
         typeNameSub,
         isPointerType,
         hashSize))
   {
      g_HashKeyDestroy(hash);
      greturn NULL;
   }

   greturn hash;
}

/******************************************************************************
func: g_HashKeyCreateContent
******************************************************************************/
grlAPI Gb g_HashKeyCreateContent_(G_HashKey * const hash, Gsize const typeSize, 
   Char const * const typeName, Char const * const typeNameSub, 
   Gb const isPointerType, GhashSize const hashSize)
{
   Gindex index;

   genter;

   // Initialize
   hash->baseName      = "G_HashKey";
   hash->typeName      = typeName;
   hash->typeNameSub   = typeNameSub;
   hash->typeSize      = typeSize;
   hash->isPointerType = (isPointerType) ? gbTRUE : gbFALSE;
   hash->binArray      = gmemCreateTypeArray(G_ListKey *, (Gcount) hashSize); //lint !e930
   hash->binCount      = hashSize;
   if (!hash->binArray)
   {
      gmemDestroy(hash);
      greturn gbFALSE;
   }

   // Initialize the Array
   index = (Gindex) (hashSize - 1);
   loop
   {
      hash->binArray[index] = g_ListKeyCreate_(
         typeSize,
         "G_HashKeyBinList",
         typeNameSub,
         isPointerType,
         gpCompare);

      breakIf(index == 0);
      index--;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_HashKeyDestroy
******************************************************************************/
grlAPI void g_HashKeyDestroy(G_HashKey * const hash)
{
   genter;

   greturnVoidIf(!hash);

   g_HashKeyDestroyContent(hash);

   gmemDestroy(hash);

   greturn;
}

/******************************************************************************
func: g_HashKeyDestroy
******************************************************************************/
grlAPI void g_HashKeyDestroyContent(G_HashKey * const hash)
{
   Gi4 index;

   genter;

   greturnVoidIf(!hash);

   forCount(index, hash->binCount)
   {
      g_ListKeyDestroy(hash->binArray[index]);
   }
   gmemDestroy(hash->binArray);

   hash->binArray = NULL;

   greturn;
}

/******************************************************************************
func: g_HashKeyErase
******************************************************************************/
grlAPI Gb g_HashKeyErase(G_HashKey * const hash, Gkey const * const key)
{
   G_ListKey     *binList;
   G_ListKeyItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !key);

   greturnFalseIf(!_Find(hash, key, &binList, &binItem));

   // remove the item from the list.
   g_ListKeyItemErase(binList, binItem);

   hash->count--;

   greturn gbTRUE;
}

/******************************************************************************
func: g_HashKeyFind
******************************************************************************/
grlAPI Gp *g_HashKeyFind(G_HashKey const * const hash, Gkey const * const key)
{
   G_ListKey     *binList;
   G_ListKeyItem *binItem;

   genter;

   greturnNullIf(
      !hash ||
      !key);

   // Get the key's location
   greturnNullIf(!_Find(hash, key, &binList, &binItem));

   greturn g_ListKeyItemGet(binItem);
}

/******************************************************************************
func: g_HashKeyFlush
******************************************************************************/
grlAPI void g_HashKeyFlush(G_HashKey * const hash)
{
   Gi4          index;
   G_ListKey   *binList;

   genter;

   greturnVoidIf(!hash);

   forCount(index, hash->binCount)
   {
      binList = hash->binArray[index];

      g_ListKeyFlush(binList);
   }

   hash->count = 0;

   greturn;
}

/******************************************************************************
func: g_HashKeyForEach
******************************************************************************/
grlAPI Gb g_HashKeyForEach(G_HashKey const * const hash, GrlForEachKeyFunc const func)
{
   Gi4              index;
   const G_ListKey *binList;

   genter;

   greturnFalseIf(
      !hash ||
      !func);

   forCount(index, hash->binCount)
   {
      binList = hash->binArray[index];

      greturnFalseIf(!g_ListKeyForEach(binList, func));
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_HashKeyGetCount
******************************************************************************/
grlAPI Gcount g_HashKeyGetCount(G_HashKey const * const hash)
{
   genter;

   greturn0If(!hash);

   greturn hash->count;
}

/******************************************************************************
func: g_HashKeyUpdate
******************************************************************************/
grlAPI Gb g_HashKeyUpdate(G_HashKey const * const hash, Gkey const * const key,
   Gp const * const value)
{
   G_ListKey     *binList;
   G_ListKeyItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !key);

   // New item
   greturnFalseIf(!_Find(hash, key, &binList, &binItem));

   // reseting existing item
   if (value)
   {
      g_ListKeyItemUpdate(binList, binItem, value);
   }

   greturn gbTRUE;
}

/******************************************************************************
Lib Local functions
******************************************************************************/
/******************************************************************************
func: _Find
******************************************************************************/
static Gb _Find(G_HashKey const * const hash, Gkey const * const key, 
   G_ListKey ** const binList, G_ListKeyItem ** const binItem)
{
   Gi4             index;
   G_ListKey      *bList;
   G_ListKeyItem  *bItem;

   genter;

   *binItem = NULL;

   // Get the hash table idx for the name.
   index = (Gi4) (gpHash(key) % hash->binCount);

   // Get the array at that location.
   bList    = hash->binArray[index];
   *binList = bList;

   // search the bin
   bItem    = g_ListKeyFind(bList, key);
   *binItem = bItem;

   greturnFalseIf(!bItem);

   greturn gbTRUE;
}
