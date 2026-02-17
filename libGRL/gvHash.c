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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static Gb _Find(GvHash const * const hash, Gv const value, GvList ** const binList, GvListItem ** const binItem);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gvHashAdd
**************************************************************************************************/
grlAPI Gb gvHashAdd(GvHash * const hash, Gv const value)
{
   GvList     *binList;
   GvListItem *binItem;

   genter;

   greturnFalseIf(!hash);

   // New item
   greturnFalseIf(_Find(hash, value, &binList, &binItem));

   // Get the hashed row.
   binItem = gvListAddEnd(binList, value);
   if (!binItem)
   {
      debugHalt("ListAddEnd failed");
      greturn gbFALSE;
   }

   hash->count++;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvHashCloc
**************************************************************************************************/
grlAPI GvHash *gvHashCloc_(Char const * const typeName, GrlCompareFunc const compareFunc,
   GrlHashFunc const hashFunc, GhashSize const hashSize)
{
   GvHash *hash;

   genter;

   greturnNullIf(
      !hashFunc    ||
      !compareFunc ||
      !hashFunc    ||
      hashSize == 0);

   // Cloc the hash table.
   hash = gmemClocType(GvHash);
   greturnNullIf(!hash);

   if (!gvHashClocContent_(hash, typeName, compareFunc, hashFunc, hashSize))
   {
      gvHashDloc(hash);
      greturn NULL;
   }

   greturn hash;
}

/**************************************************************************************************
func: gvHashClocContent
**************************************************************************************************/
grlAPI Gb gvHashClocContent_(GvHash * const hash, Char const * const typeName,
   GrlCompareFunc const compareFunc, GrlHashFunc const hashFunc, GhashSize const hashSize)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !hash        ||
      !compareFunc ||
      !hashFunc    ||
      hashSize == 0);

   // Initialize
   GTYPE_SET(hash, typeName);

   hash->hashFunc      = hashFunc;
   hash->compareFunc   = compareFunc;
   hash->binArray      = gmemClocTypeArray(GvList, (Gcount) hashSize); 
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
      gvListClocContent_(&hash->binArray[index], (Char *) "GHashBinList", compareFunc);

      breakIf(index == 0);
      index--;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvHashDloc
**************************************************************************************************/
grlAPI void gvHashDloc(GvHash * const hash)
{
   genter;

   greturnIf(!hash);

   gvHashDlocContent(hash);

   gmemDloc(hash);

   greturn;
}

/**************************************************************************************************
func: gvHashDloc
**************************************************************************************************/
grlAPI void gvHashDlocContent(GvHash * const hash)
{
   Gi4 index;

   genter;

   greturnIf(!hash);

   forCount(index, hash->binCount)
   {
      gvListDlocContent(&hash->binArray[index]);
   }
   gmemDloc(hash->binArray);

   hash->binArray = NULL;

   greturn;
}

/**************************************************************************************************
func: gvHashErase
**************************************************************************************************/
grlAPI Gb gvHashErase(GvHash * const hash, Gv const value)
{
   GvList     *binList;
   GvListItem *binItem;

   genter;

   greturnFalseIf(!hash);

   greturnFalseIf(!_Find(hash, value, &binList, &binItem));

   // remove the item from the list.
   gvListItemErase(binList, binItem);

   hash->count--;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvHashFind
**************************************************************************************************/
grlAPI Gv gvHashFind(GvHash const * const hash, Gv const value)
{
   Gv          zero = { 0 };
   GvList     *binList;
   GvListItem *binItem;

   genter;

   greturnValIf(!hash, zero);

   // Get the key's location
   greturnValIf(!_Find(hash, value, &binList, &binItem), zero);

   greturn gvListItemGet(binItem);
}

/**************************************************************************************************
func: gvHashFlush
**************************************************************************************************/
grlAPI void gvHashFlush(GvHash * const hash)
{
   Gi4 index;

   genter;

   greturnIf(!hash);

   forCount(index, hash->binCount)
   {
      gvListFlush(&hash->binArray[index]);
   }

   hash->count = 0;

   greturn;
}

/**************************************************************************************************
func: gvHashForEach
**************************************************************************************************/
grlAPI Gb gvHashForEach(GvHash const * const hash, GrlForEachFunc const func)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !hash ||
      !func);

   forCount(index, hash->binCount)
   {
      greturnFalseIf(!gvListForEach(&hash->binArray[index], func));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvHashGetCount
**************************************************************************************************/
grlAPI Gcount gvHashGetCount(GvHash const * const hash)
{
   genter;

   greturn0If(!hash);

   greturn hash->count;
}

/**************************************************************************************************
func: gvHashUpdate
**************************************************************************************************/
grlAPI Gb gvHashUpdate(GvHash const * const hash, Gv const value)
{
   GvList     *binList;
   GvListItem *binItem;

   genter;

   greturnFalseIf(!hash);

   // New item
   greturnFalseIf(!_Find(hash, value, &binList, &binItem));

   // reseting existing item
   gvListItemUpdate(binList, binItem, value);

   greturn gbTRUE;
}

/**************************************************************************************************
Lib Local functions
**************************************************************************************************/
/**************************************************************************************************
func: _Find
**************************************************************************************************/
static Gb _Find(GvHash const * const hash, Gv const value, GvList ** const binList,
   GvListItem ** const binItem)
{
   Gi4          index;
   GvList      *bList;
   GvListItem  *bItem;

   genter;

   *binItem = NULL;

   // Get the hash table idx for the name.
   index = (Gi4) ((hash->hashFunc)(&value) % hash->binCount);

   // Get the array at that location.
   bList    = &hash->binArray[index];
   *binList = bList;

   // search the bin
   bItem    = gvListFind(bList, value);
   *binItem = bItem;

   greturn (bItem != NULL);
}
