/**************************************************************************************************
file:       g_Hash
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gb _Find(G_Hash const * const hash, Gp const * const value, G_List ** const binList, G_ListItem ** const binItem);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_HashAdd
**************************************************************************************************/
grlAPI Gb g_HashAdd(G_Hash * const hash, Gp const * const value)
{
   G_List     *binList;
   G_ListItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !value);

   // New item
   if (_Find(hash, value, &binList, &binItem))
   {
      greturn gbFALSE;
   }

   // Get the hashed row.
   binItem = g_ListAddEnd(binList, value);
   if (!binItem)
   {
      debugHalt("ListAddEnd failed");
      greturn gbFALSE;
   }

   hash->count++;

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_HashCloc
**************************************************************************************************/
grlAPI G_Hash *g_HashCloc_(Gsize const typeSize, Char const * const typeName,
   Gb const isPointerType, GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc,
   GhashSize const hashSize)
{
   G_Hash *hash;

   genter;

   greturnNullIf(
      !hashFunc    ||
      !compareFunc ||
      typeSize < 0);

   // Create the hash table.
   hash = gmemClocType(G_Hash);
   greturnNullIf(!hash);

   if (!g_HashClocContent_(
         hash,
         typeSize,
         typeName,
         isPointerType,
         compareFunc,
         hashFunc,
         hashSize))
   {
      g_HashDloc(hash);
      greturn NULL;
   }

   greturn hash;
}

/**************************************************************************************************
func: g_HashClocContent
**************************************************************************************************/
grlAPI Gb g_HashClocContent_(G_Hash * const hash, Gsize const typeSize,
   Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc,
   GrlHashFunc const hashFunc, GhashSize const hashSize)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !hash ||
      typeSize <= 0);

   // Initialize
   typeName;
   GTYPE_SET(hash, typeName);

   hash->typeSize      = typeSize;
   hash->isPointerType = isPointerType;
   hash->hashFunc      = hashFunc;
   hash->compareFunc   = compareFunc;
   hash->binArray      = gmemClocTypeArray(G_List *, (Gcount) hashSize); //lint !e930
   hash->binCount      = hashSize;
   if (!hash->binArray)
   {
      gmemDloc(hash);
      greturn gbFALSE;
   }

   // Initialize the Array
   index = (Gindex) (hashSize - 1);
   loop
   {
      hash->binArray[index] = g_ListCloc_(
         typeSize,
         "GHashBinList",
         isPointerType,
         compareFunc);

      breakIf(index == 0);
      index--;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_HashDloc
**************************************************************************************************/
grlAPI void g_HashDloc(G_Hash * const hash)
{
   genter;

   greturnVoidIf(!hash);

   g_HashDlocContent(hash);

   gmemDloc(hash);

   greturn;
}

/**************************************************************************************************
func: g_HashDloc
**************************************************************************************************/
grlAPI void g_HashDlocContent(G_Hash * const hash)
{
   Gi4 index;

   genter;

   greturnVoidIf(!hash);

   forCount(index, hash->binCount)
   {
      g_ListDloc(hash->binArray[index]);
   }
   gmemDloc(hash->binArray);

   hash->binArray = NULL;

   greturn;
}

/**************************************************************************************************
func: g_HashErase
**************************************************************************************************/
grlAPI Gb g_HashErase(G_Hash * const hash, Gp const * const value)
{
   G_List     *binList;
   G_ListItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !value);

   greturnFalseIf(!_Find(hash, value, &binList, &binItem));

   // remove the item from the list.
   g_ListItemErase(binList, binItem);

   hash->count--;

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_HashFind
**************************************************************************************************/
grlAPI Gp *g_HashFind(G_Hash const * const hash, Gp const * const value)
{
   G_List     *binList;
   G_ListItem *binItem;

   genter;

   greturnNullIf(
      !hash ||
      !value);

   // Get the key's location
   greturnNullIf(!_Find(hash, value, &binList, &binItem));

   greturn g_ListItemGet(binItem);
}

/**************************************************************************************************
func: g_HashFlush
**************************************************************************************************/
grlAPI void g_HashFlush(G_Hash * const hash)
{
   Gi4     index;
   G_List *binList;

   genter;

   greturnVoidIf(!hash);

   forCount(index, hash->binCount)
   {
      binList = hash->binArray[index];

      g_ListFlush(binList);
   }

   hash->count = 0;

   greturn;
}

/**************************************************************************************************
func: g_HashForEach
**************************************************************************************************/
grlAPI Gb g_HashForEach(G_Hash const * const hash, GrlForEachFunc const func)
{
   Gi4           index;
   const G_List *binList;

   genter;

   greturnFalseIf(
      !hash ||
      !func);

   forCount(index, hash->binCount)
   {
      binList = hash->binArray[index];

      greturnFalseIf(!g_ListForEach(binList, func));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_HashGetCount
**************************************************************************************************/
grlAPI Gcount g_HashGetCount(G_Hash const * const hash)
{
   genter;

   greturn0If(!hash);

   greturn hash->count;
}

/**************************************************************************************************
func: g_HashUpdate
**************************************************************************************************/
grlAPI Gb g_HashUpdate(G_Hash const * const hash, Gp const * const value)
{
   G_List     *binList;
   G_ListItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !value);

   // New item
   greturnFalseIf(!_Find(hash, value, &binList, &binItem));

   // reseting existing item
   if (value)
   {
      g_ListItemUpdate(binList, binItem, value);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
Lib Local functions
**************************************************************************************************/
/**************************************************************************************************
func: _Find
**************************************************************************************************/
static Gb _Find(G_Hash const * const hash, Gp const * const value,
   G_List ** const binList, G_ListItem ** const binItem)
{
   Gi4          index;
   G_List      *bList;
   G_ListItem  *bItem;

   genter;

   *binItem = NULL;

   // Get the hash table idx for the name.
   index = (Gi4) ((hash->hashFunc)(value) % hash->binCount);

   // Get the array at that location.
   bList    = hash->binArray[index];
   *binList = bList;

   // search the bin
   bItem    = g_ListFind(bList, value);
   *binItem = bItem;

   greturnFalseIf(!bItem);

   greturn gbTRUE;
}
