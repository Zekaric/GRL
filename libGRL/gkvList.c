/**************************************************************************************************
file:       gkvList
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
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static void           _AddBegin( GkvList       * const list, GkvListItem       * const litem);
static void           _AddEnd(   GkvList       * const list, GkvListItem       * const litem);

static void           _ItemAdd(  GkvList       * const list, GkvListItem       * const litem, GkvListItem * const nitem);

static GkvListItem   *_Search(   GkvList const * const list, Gk const * const key, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gkvListAdd
**************************************************************************************************/
grlAPI GkvListItem *gkvListAdd(GkvList * const list, Gk const * const key, Gv const value)
{
   GkvListItem *litem;

   genter;

   greturnNullIf(!list->isSorted);

   if (list->count == 0)
   {
      litem = gkvListAddBegin(list, key, value);
   }
   else
   {
      // Find the position.
      litem = _Search(list, key, gbTRUE);

      // Add the new item.
      litem = gkvListItemAdd(list, litem, key, value);
   }

   // We are still sorted.
   list->isSorted = gbTRUE;

   // Return the item.
   greturn litem;
}

/**************************************************************************************************
func: gkvListAddBegin
**************************************************************************************************/
grlAPI GkvListItem *gkvListAddBegin(GkvList * const list, Gk const * const key, Gv const value)
{
   GkvListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = gmemClocType(GkvListItem);
   greturnNullIf(!litem);

   gkvSetK(litem->kv, key);
   gkvSetV(litem->kv, value);

   _AddBegin(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: gkvListAddEnd
**************************************************************************************************/
grlAPI GkvListItem *gkvListAddEnd(GkvList * const list, Gk const * const key, Gv const value)
{
   GkvListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = gmemClocType(GkvListItem);
   greturnNullIf(!litem);

   gkvSetK(litem->kv, key);
   gkvSetV(litem->kv, value);

   _AddEnd(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: gkvListCloc
**************************************************************************************************/
grlAPI GkvList *gkvListCloc_(Char const * const typeName, GrlCompareFunc const compareFunc)
{
   GkvList *list;

   genter;

   list = gmemClocType(GkvList);
   greturnNullIf(!list);

   if (!gkvListClocContent_(list, typeName, compareFunc))
   {
      gkvListDloc(list);
      greturn NULL;
   }

   greturn list;
}

/**************************************************************************************************
func: gkvListClocContent
**************************************************************************************************/
grlAPI Gb gkvListClocContent_(GkvList * const list, Char const * const typeName,
   GrlCompareFunc const compareFunc)
{
   genter;

   greturnFalseIf(!list);

   typeName;
   GTYPE_SET(list, typeName);

   list->compareFunc = compareFunc;

   if (list->compareFunc)
   {
      list->isSorted = gbTRUE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvListDloc
**************************************************************************************************/
grlAPI void gkvListDloc(GkvList * const list)
{
   genter;

   greturnIf(!list);

   gkvListDlocContent(list);
   gmemDloc(list);

   greturn;
}

/**************************************************************************************************
func: gkvListDlocContent
**************************************************************************************************/
grlAPI void gkvListDlocContent(GkvList * const list)
{
   GkvListItem *lcurr,
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
func: gkvListErase
**************************************************************************************************/
grlAPI Gb gkvListErase(GkvList * const list, Gk const * const key)
{
   GkvListItem *litem;

   genter;

   litem = _Search(list, key, gbFALSE);
   greturnFalseIf(!litem);

   gkvListItemErase(list, litem);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvListEraseBegin
**************************************************************************************************/
grlAPI Gb gkvListEraseBegin(GkvList * const list)
{
   GkvListItem *litem;

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
func: gkvListEraseEnd
**************************************************************************************************/
grlAPI Gb gkvListEraseEnd(GkvList * const list)
{
   GkvListItem *litem;

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
func: gkvListFind
**************************************************************************************************/
grlAPI GkvListItem *gkvListFind(GkvList const * const list, Gk const * const key)
{
   genter;

   greturn _Search(list, key, gbFALSE);
}

/**************************************************************************************************
func: gkvListFlush
**************************************************************************************************/
grlAPI void gkvListFlush(GkvList * const list)
{
   genter;

   loop
   {
      breakIf(list->count == 0);
      gkvListEraseEnd(list);
   }

   greturn;
}

/**************************************************************************************************
func: gkvListForEach
**************************************************************************************************/
grlAPI Gb gkvListForEach(GkvList const * const list, GrlForEachKeyFunc const func)
{
   GkvListItem const *litem,
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

      func(gkvGetK(litem->kv), &gkvGetV(litem->kv));

      litem = litemNext;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvListGetBegin
**************************************************************************************************/
grlAPI GkvListItem *gkvListGetBegin(GkvList const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->head;
}

/**************************************************************************************************
func: gkvListGetCount
**************************************************************************************************/
grlAPI Gcount gkvListGetCount(GkvList const * const list)
{
   genter;

   greturn0If(!list);

   greturn list->count;
}

/**************************************************************************************************
func: gkvListGetEnd
**************************************************************************************************/
grlAPI GkvListItem *gkvListGetEnd(GkvList const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->tail;
}

/**************************************************************************************************
func: gkvListItemAdd
**************************************************************************************************/
grlAPI GkvListItem *gkvListItemAdd(GkvList * const list, GkvListItem * const litem,
   Gk const * const key, Gv const value)
{
   GkvListItem *nitem;

   genter;

   greturnNullIf(!list);

   nitem = gmemClocType(GkvListItem);
   greturnNullIf(!nitem);

   gkvSetK(nitem->kv, key);
   gkvSetV(nitem->kv, value);

   _ItemAdd(list, litem, nitem);

   list->isSorted = gbFALSE;

   greturn nitem;
}

/**************************************************************************************************
func: gkvListItemErase
**************************************************************************************************/
grlAPI GkvListItem *gkvListItemErase(GkvList * const list, GkvListItem * const litem)
{
   GkvListItem *nextItem;

   genter;

   greturnNullIf(
      !list ||
      !litem);

   nextItem = litem->next;

   if      (!litem->prev)
   {
      gkvListEraseBegin(list); 
   }
   else if (!litem->next)
   {
      gkvListEraseEnd(list); 
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
func: gkvListItemGet
**************************************************************************************************/
grlAPI Gv gkvListItemGet(GkvListItem const * const litem)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(!litem, zero);

   greturn gkvGetV(litem->kv);
}

/**************************************************************************************************
func: gkvListItemGetKey
**************************************************************************************************/
grlAPI Gk const *gkvListItemGetKey(GkvListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn gkvGetK(litem->kv);
}

/**************************************************************************************************
func: gkvListItemGetNext
**************************************************************************************************/
grlAPI GkvListItem *gkvListItemGetNext(GkvListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->next;
}

/**************************************************************************************************
func: gkvListItemGetPrev
**************************************************************************************************/
grlAPI GkvListItem *gkvListItemGetPrev(GkvListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->prev;
}

/**************************************************************************************************
func: gkvListItemUpdate
**************************************************************************************************/
grlAPI Gb gkvListItemUpdate(GkvListItem * const litem, Gv const value)
{
   genter;

   greturnFalseIf(!litem);

   gkvSetV(litem->kv, value);

   greturn gbTRUE;
}

#if 0
/**************************************************************************************************
func: gkvListItemUpdateKey
**************************************************************************************************/
grlAPI Gb gkvListItemUpdateKey(GkvList * const list, GkvListItem *const litem,
   Gk const * const key)
{
   genter;

   greturnFalseIf(!litem || !key);

   gkvSetK(litem->kv, key);

   greturn gbTRUE;
}
#endif

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _AddBegin
**************************************************************************************************/
void _AddBegin(GkvList * const list, GkvListItem * const litem)
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
func: _AddEnd
**************************************************************************************************/
void _AddEnd(GkvList * const list, GkvListItem * const litem)
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
func: _ItemAdd
**************************************************************************************************/
void _ItemAdd(GkvList * const list, GkvListItem * const litem,
   GkvListItem * const nitem)
{
   genter;

   if (!litem)
   {
      _AddBegin(list, nitem);
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
func: _Search
**************************************************************************************************/
static GkvListItem *_Search(GkvList const * const list, Gk const * const key,
   Gb const findLocation)
{
   GkvListItem  *litem;
   Gcompare        compare;

   genter;

   greturnNullIf(
      !list              ||
      list->count == 0   ||
      !key);

   litem = gkvListGetBegin(list);

   loop
   {
      breakIf(!litem);

      compare = list->compareFunc(key, gkvGetK(litem->kv));
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
