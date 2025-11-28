/**************************************************************************************************
file:       g_ListKey
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot
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
#define DATA_PTR(LITEM)    ((Gp *) &(LITEM[1]))

static G_ListKeyItem *_ClocAndSetListItem(G_ListKey       * const list, Gkey const * const key, Gp const * const value);

static G_ListKeyItem *_LinearSearch(      G_ListKey const * const list, Gkey const * const key, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_ListKeyAdd
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyAdd(G_ListKey * const list, Gkey const * const key, 
   Gp const * const value)
{
   G_ListKeyItem *litem;

   genter;

   greturnNullIf(!list->isSorted);

   if (list->count == 0)
   {
      litem = g_ListKeyAddBegin(list, key, value);
   }
   else
   {
      // Find the position.
      litem = _LinearSearch(list, key, gbTRUE);

      // Add the new item.
      litem = g_ListKeyItemAdd(list, litem, key, value);
   }

   // We are still sorted.
   list->isSorted = gbTRUE;

   // Return the item.
   greturn litem;
}

/**************************************************************************************************
func: g_ListKeyAddBegin
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyAddBegin(G_ListKey * const list, Gkey const * const key, 
   Gp const * const value)
{
   G_ListKeyItem *litem;

   genter;

   greturnNullIf(!list);

   litem = _ClocAndSetListItem(list, key, value);
   greturnNullIf(!litem);

   g_ListKeyAddBegin_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: g_ListKeyAddEnd
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyAddEnd(G_ListKey * const list, Gkey const * const key, 
   Gp const * const value)
{
   G_ListKeyItem *litem;

   genter;

   greturnNullIf(!list);

   litem = _ClocAndSetListItem(list, key, value);
   greturnNullIf(!litem);

   g_ListKeyAddEnd_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: g_ListKeyCloc
**************************************************************************************************/
grlAPI G_ListKey *g_ListKeyCloc_(Gsize const typeSize, Char const * const typeName,
   Gb const isPointerType, GrlCompareFunc const compareFunc)
{
   G_ListKey *list;

   genter;

   greturnNullIf(typeSize <= 0);

   list = gmemClocType(G_ListKey);
   greturnNullIf(!list);

   if (!g_ListKeyClocContent_(
         list, 
         typeSize,
         typeName,
         isPointerType,
         compareFunc))
   {
      g_ListKeyDloc(list);
      greturn NULL;
   }

   greturn list;
}

/**************************************************************************************************
func: g_ListKeyClocContent
**************************************************************************************************/
grlAPI Gb g_ListKeyClocContent_(G_ListKey * const list, Gsize const typeSize,
   Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc)
{
   genter;

   greturnFalseIf(
      !list ||
      typeSize <= 0);

   typeName;
   GTYPE_SET(list, typeName);

   list->typeSize      = typeSize;
   list->isPointerType = isPointerType;
   list->compareFunc   = compareFunc;

   if (list->compareFunc)
   {
      list->isSorted = gbTRUE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListKeyDloc
**************************************************************************************************/
grlAPI void g_ListKeyDloc(G_ListKey * const list)
{
   genter;

   greturnIf(!list);

   g_ListKeyDlocContent(list);
   gmemDloc(list);

   greturn;
}

/**************************************************************************************************
func: g_ListKeyDlocContent
**************************************************************************************************/
grlAPI void g_ListKeyDlocContent(G_ListKey * const list)
{
   G_ListKeyItem  *lcurr,
                  *lnext;

   genter;

   greturnIf(!list);

   lcurr = list->head;
   loop
   {
      breakIf(lcurr == NULL);

      lnext = lcurr->next;
      gmemDloc(lcurr);
      lcurr = lnext;
   }

   list->head    = 
      list->tail = NULL;
   list->count   = 0;

   greturn;
}

/**************************************************************************************************
func: g_ListKeyErase
**************************************************************************************************/
grlAPI Gb g_ListKeyErase(G_ListKey * const list, Gkey const * const key)
{
   G_ListKeyItem *litem;

   genter;

   litem = _LinearSearch(list, key, gbFALSE);
   greturnFalseIf(!litem);

   g_ListKeyItemErase(list, litem);

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListKeyEraseBegin
**************************************************************************************************/
grlAPI Gb g_ListKeyEraseBegin(G_ListKey * const list)
{
   G_ListKeyItem *litem;

   genter;

   greturnFalseIf(
      !list ||
      !list->head);

   litem      = list->head;
   list->head = litem->next;

   gmemDloc(litem);

   if (!list->head)
   {
      list->tail = NULL;
   }
   else
   {
      list->head->prev = NULL;
   }

   list->count--;

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListKeyEraseEnd
**************************************************************************************************/
grlAPI Gb g_ListKeyEraseEnd(G_ListKey * const list)
{
   G_ListKeyItem *litem;

   genter;

   greturnFalseIf(
      !list ||
      !list->tail);

   litem      = list->tail;
   list->tail = litem->prev;

   gmemDloc(litem);

   if (!list->tail)
   {
      list->head = NULL;
   }
   else
   {
      list->tail->next = NULL;
   }

   list->count--;

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListKeyFind
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyFind(G_ListKey const * const list, Gkey const * const key)
{
   G_ListKeyItem *result;

   genter;
   
   result = _LinearSearch(list, key, gbFALSE);

   greturn result;
}

/**************************************************************************************************
func: g_ListKeyFlush
**************************************************************************************************/
grlAPI void g_ListKeyFlush(G_ListKey * const list)
{
   genter;

   loop
   {
      breakIf(list->count == 0);
      g_ListKeyEraseEnd(list);
   }

   greturn;
}

/**************************************************************************************************
func: g_ListKeyForEach
**************************************************************************************************/
grlAPI Gb g_ListKeyForEach(G_ListKey const * const list, GrlForEachKeyFunc const func)
{
   G_ListKeyItem const  *litem,
                        *litemNext;

   genter;

   greturnFalseIf(
      !list ||
      !func);

   litem = list->head;

   loop
   {
      breakIf(!litem);
      litemNext = litem->next;

      func(litem->key, DATA_PTR(litem));

      litem = litemNext;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListKeyGetBegin
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyGetBegin(G_ListKey const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->head;
}

/**************************************************************************************************
func: g_ListKeyGetCount
**************************************************************************************************/
grlAPI Gcount g_ListKeyGetCount(G_ListKey const * const list)
{
   genter;

   greturn0If(!list);

   greturn list->count;
}

/**************************************************************************************************
func: g_ListKeyGetEnd
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyGetEnd(G_ListKey const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->tail;
}

/**************************************************************************************************
func: g_ListKeyItemAdd
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyItemAdd(G_ListKey * const list, G_ListKeyItem * const litem,
   Gkey const * const key, Gp const * const value)
{
   G_ListKeyItem *nitem;

   genter;

   greturnNullIf(!list);

   nitem = _ClocAndSetListItem(list, key, value);
   greturnNullIf(!nitem);

   g_ListKeyItemAdd_Add(list, litem, nitem);

   list->isSorted = gbFALSE;

   greturn nitem;
}

/**************************************************************************************************
func: g_ListKeyItemErase
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyItemErase(G_ListKey * const list, G_ListKeyItem * const litem)
{
   G_ListKeyItem *nextItem;

   genter;

   greturnNullIf(
      !list ||
      !litem);

   nextItem = litem->next;

   if      (!litem->prev)
   {
      g_ListKeyEraseBegin(list); //lint !e534
   }
   else if (!litem->next)
   {
      g_ListKeyEraseEnd(list); //lint !e534
   }
   else
   {
      nextItem->prev    = litem->prev;
      litem->prev->next = nextItem;

      gmemDloc(litem);

      list->count--;
   }

   greturn nextItem;
}

/**************************************************************************************************
func: g_ListKeyItemGet
**************************************************************************************************/
grlAPI Gp *g_ListKeyItemGet(G_ListKeyItem const * const litem)
{
   Gp *p;

   genter;

   greturnNullIf(!litem);

   p = DATA_PTR(litem);

   greturn p;
}

/**************************************************************************************************
func: g_ListKeyItemGetKey
**************************************************************************************************/
grlAPI Gp const *g_ListKeyItemGetKey(G_ListKeyItem const * const litem)
{
   Gp const *p;

   genter;

   greturnNullIf(!litem);

   p = litem->key;

   greturn p;
}

/**************************************************************************************************
func: g_ListKeyItemGetNext
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyItemGetNext(G_ListKeyItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->next;
}

/**************************************************************************************************
func: g_ListKeyItemGetPrev
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyItemGetPrev(G_ListKeyItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->prev;
}

/**************************************************************************************************
func: g_ListKeyItemUpdate
**************************************************************************************************/
grlAPI void g_ListKeyItemUpdate(G_ListKey * const list, G_ListKeyItem * const litem,
   Gp const * const value)
{
   Gn1  *data;

   genter;

   greturnIf(!litem);

   data = (Gn1 *) DATA_PTR(litem);
   gmemCopyOver(data, list->typeSize, value);

   greturn;
}

/**************************************************************************************************
func: g_ListKeyItemUpdateKey
**************************************************************************************************/
grlAPI void g_ListKeyItemUpdateKey(G_ListKey * const list, G_ListKeyItem *const litem,
   Gkey const * const key)
{
   genter;

   greturnIf(!litem || !key);

   litem->key = key;

   list->isSorted = gbFALSE;

   greturn;
}

/**************************************************************************************************
Like Module Local: 
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_ListKeyAddBegin_Add
**************************************************************************************************/
grlAPI void g_ListKeyAddBegin_Add(G_ListKey * const list, G_ListKeyItem * const litem)
{
   genter;

   litem->next = list->head;
   if (list->head)
   {
      list->head->prev = litem;
   }
   list->head = litem;
   if (!list->tail)
   {
      list->tail = litem;
   }

   list->count++;

   greturn;
}

/**************************************************************************************************
func: g_ListKeyAddEnd_Add
**************************************************************************************************/
grlAPI void g_ListKeyAddEnd_Add(G_ListKey * const list, G_ListKeyItem * const litem)
{
   genter;

   // add to the list.
   litem->prev = list->tail;
   if (list->tail)
   {
      list->tail->next = litem;
   }
   list->tail = litem;
   if (!list->head)
   {
      list->head = litem;
   }

   list->count++;

   greturn;
}

/**************************************************************************************************
func: g_ListKeyItemAdd_Add
**************************************************************************************************/
grlAPI void g_ListKeyItemAdd_Add(G_ListKey * const list, G_ListKeyItem * const litem,
   G_ListKeyItem * const nitem)
{
   genter;

   if (!litem)
   {
      g_ListKeyAddBegin_Add(list, nitem);
      greturn;
   }

   nitem->next = litem->next;
   nitem->prev = litem;

   litem->next = nitem;

   if (nitem->next)
   {
      nitem->next->prev = nitem;
   }
   else
   {
      list->tail = nitem;
   }

   list->count++;

   greturn;
}

/**************************************************************************************************
func: g_ListKeyItem_Cloc
**************************************************************************************************/
grlAPI G_ListKeyItem *g_ListKeyItem_Cloc(G_ListKey const * const list)
{
   G_ListKeyItem *result;

   genter;
   
   result = (G_ListKeyItem *) gmemCloc(
      "G_ListKeyItem",
      gsizeof(G_ListKeyItem) + gsizeof(Gp *) + list->typeSize);

   greturn result;
}

/**************************************************************************************************
local: 
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ClocAndSetListItem
**************************************************************************************************/
static G_ListKeyItem *_ClocAndSetListItem(G_ListKey * const list, Gkey const * const key, 
   Gp const * const value)
{
   G_ListKeyItem *litem;

   genter;

   litem = g_ListKeyItem_Cloc(list);
   greturnNullIf(!litem);

   litem->key = key;
   g_ListKeyItemUpdate(list, litem, value);

   greturn litem;
}

/**************************************************************************************************
func: _LinearSearch
**************************************************************************************************/
static G_ListKeyItem *_LinearSearch(G_ListKey const * const list, Gkey const * const key,
   Gb const findLocation)
{
   G_ListKeyItem  *litem;
   Gcompare        compare;

   genter;

   greturnNullIf(
      !list              ||
      list->count == 0   ||
      !key);

   litem = g_ListKeyGetBegin(list);

   loop
   {
      breakIf(!litem);

      compare = list->compareFunc(key, litem->key);
      breakIf(compare == gcompareEQUAL);

      // List is sorted, no point comparing beyond this point.
      if (list->isSorted &&
          compare == gcompareLESS_THAN)
      {
         greturnValIf(findLocation, litem->prev);

         greturn NULL;
      }

      litem = litem->next;
   }

   greturnValIf(findLocation, list->tail);

   greturn litem;
}
