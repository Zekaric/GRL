/**************************************************************************************************
file:       gkvHash
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
GkvHash and name table to mimic Galaxy vname and vdict functionality
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
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gb _Find(GkvHash const * const hash, Gk const * const key, GkvList ** const binList, GkvListItem ** const binItem);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gkvHashAdd
**************************************************************************************************/
grlAPI Gb gkvHashAdd(GkvHash * const hash, Gk const * const key, Gv const value)
{
   GkvList     *binList;
   GkvListItem *binItem;

   genter;

   greturnFalseIf(!hash);

   // New item
   if (_Find(hash, key, &binList, &binItem))
   {
      greturn gbFALSE;
   }

   // Get the hashed row.
   binItem = gkvListAddEnd(binList, key, value);
   if (!binItem)
   {
      debugHalt("ListAddEnd failed");
      greturn gbFALSE;
   }

   hash->count++;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvHashCloc
**************************************************************************************************/
grlAPI GkvHash *gkvHashCloc_(Char const * const typeName, GhashSize const hashSize)
{
   GkvHash *hash;

   genter;

   // Cloc the hash table.
   hash = gmemClocType(GkvHash);
   greturnNullIf(!hash);

   if (!gkvHashClocContent_(hash, typeName, hashSize))
   {
      gkvHashDloc(hash);
      greturn NULL;
   }

   greturn hash;
}

/**************************************************************************************************
func: gkvHashClocContent
**************************************************************************************************/
grlAPI Gb gkvHashClocContent_(GkvHash * const hash, Char const * const typeName,
   GhashSize const hashSize)
{
   Gindex index;

   genter;

   greturnFalseIf(!hash);

   // Initialize
   typeName;
   GTYPE_SET(hash, typeName);

   hash->binArray = gmemClocTypeArray(GkvList, (Gcount) hashSize);
   hash->binCount = hashSize;
   if (!hash->binArray)
   {
      gmemDloc(hash);
      greturn gbFALSE;
   }

   // Initialize the Array
   index = (Gindex) (hashSize - 1);
   loop
   {
      gkvListClocContent_(&hash->binArray[index], (Char *) "GkvHashBinList", gpCompare);

      breakIf(index == 0);
      index--;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvHashDloc
**************************************************************************************************/
grlAPI void gkvHashDloc(GkvHash * const hash)
{
   genter;

   greturnIf(!hash);

   gkvHashDlocContent(hash);

   gmemDloc(hash);

   greturn;
}

/**************************************************************************************************
func: gkvHashDloc
**************************************************************************************************/
grlAPI void gkvHashDlocContent(GkvHash * const hash)
{
   Gi4 index;

   genter;

   greturnIf(!hash);

   forCount(index, hash->binCount)
   {
      gkvListDlocContent(&hash->binArray[index]);
   }
   gmemDloc(hash->binArray);

   hash->binArray = NULL;

   greturn;
}

/**************************************************************************************************
func: gkvHashErase
**************************************************************************************************/
grlAPI Gb gkvHashErase(GkvHash * const hash, Gk const * const key)
{
   GkvList     *binList;
   GkvListItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !key);

   greturnFalseIf(!_Find(hash, key, &binList, &binItem));

   // remove the item from the list.
   gkvListItemErase(binList, binItem);

   hash->count--;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvHashFind
**************************************************************************************************/
grlAPI Gv gkvHashFind(GkvHash const * const hash, Gk const * const key)
{
   Gv           zero = { 0 };
   GkvList     *binList;
   GkvListItem *binItem;

   genter;

   greturnValIf(
         !hash ||
         !key,
      zero);

   // Get the key's location
   greturnValIf(!_Find(hash, key, &binList, &binItem), zero);

   greturn gkvListItemGet(binItem);
}

/**************************************************************************************************
func: gkvHashFlush
**************************************************************************************************/
grlAPI void gkvHashFlush(GkvHash * const hash)
{
   Gindex index;

   genter;

   greturnIf(!hash);

   forCount(index, hash->binCount)
   {
      gkvListFlush(&hash->binArray[index]);
   }

   hash->count = 0;

   greturn;
}

/**************************************************************************************************
func: gkvHashForEach
**************************************************************************************************/
grlAPI Gb gkvHashForEach(GkvHash const * const hash, GrlForEachKeyFunc const func)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !hash ||
      !func);

   forCount(index, hash->binCount)
   {
      greturnFalseIf(!gkvListForEach(&hash->binArray[index], func));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvHashGetCount
**************************************************************************************************/
grlAPI Gcount gkvHashGetCount(GkvHash const * const hash)
{
   genter;

   greturn0If(!hash);

   greturn hash->count;
}

/**************************************************************************************************
func: gkvHashUpdate
**************************************************************************************************/
grlAPI Gb gkvHashUpdate(GkvHash const * const hash, Gk const * const key, Gv const value)
{
   GkvList     *binList;
   GkvListItem *binItem;

   genter;

   greturnFalseIf(
      !hash ||
      !key);

   // New item
   greturnFalseIf(!_Find(hash, key, &binList, &binItem));

   // reseting existing item
   gkvListItemUpdate(binItem, value);

   greturn gbTRUE;
}

/**************************************************************************************************
Lib Local functions
**************************************************************************************************/
/**************************************************************************************************
func: _Find
**************************************************************************************************/
static Gb _Find(GkvHash const * const hash, Gk const * const key, GkvList ** const binList,
   GkvListItem ** const binItem)
{
   Gindex        index;
   GkvList      *bList;
   GkvListItem  *bItem;

   genter;

   *binItem = NULL;

   // Get the hash table idx for the name.
   index = (Gi4) (gpHash(key) % hash->binCount);

   // Get the array at that location.
   bList    = &hash->binArray[index];
   *binList = bList;

   // search the bin
   bItem    = gkvListFind(bList, key);
   *binItem = bItem;

   greturn (bItem != NULL);
}
