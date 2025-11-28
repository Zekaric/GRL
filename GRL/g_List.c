/**************************************************************************************************
file:       g_List
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

static G_ListItem *_ClocAndSetListItem(G_List       * const list, Gp const * const value);

static G_ListItem *_LinearSearch(      G_List const * const list, Gp const * const value, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_ListAdd
**************************************************************************************************/
grlAPI G_ListItem *g_ListAdd(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   if (list->count == 0)
   {
      litem = g_ListAddBegin(list, value);
   }
   else
   {
      // Find the position.
      litem = _LinearSearch(list, value, gbTRUE);

      // Add the new item.
      litem = g_ListItemAdd(list, litem, value);
   }

   // Return the item.
   greturn litem;
}

/**************************************************************************************************
func: g_ListAddBegin
**************************************************************************************************/
grlAPI G_ListItem *g_ListAddBegin(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = _ClocAndSetListItem(list, value);
   greturnNullIf(!litem);

   g_ListAddBegin_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: g_ListAddEnd
**************************************************************************************************/
grlAPI G_ListItem *g_ListAddEnd(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = _ClocAndSetListItem(list, value);
   greturnNullIf(!litem);

   g_ListAddEnd_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: g_ListCloc
**************************************************************************************************/
grlAPI G_List *g_ListCloc_(Gsize const typeSize, Char const * const typeName,
   Gb const isPointerType, GrlCompareFunc const compareFunc)
{
   G_List *list;

   genter;

   greturnNullIf(typeSize <= 0);

   list = gmemClocType(G_List);
   greturnNullIf(!list);

   if (!g_ListClocContent_(  
         list,
         typeSize,
         typeName,
         isPointerType,
         compareFunc))
   {
      g_ListDloc(list);
      greturn NULL;
   }

   greturn list;
}

/**************************************************************************************************
func: g_ListClocContent_
**************************************************************************************************/
grlAPI Gb g_ListClocContent_(G_List * const list, Gsize const typeSize,
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
func: g_ListDloc
**************************************************************************************************/
grlAPI void g_ListDloc(G_List * const list)
{
   genter;

   greturnIf(!list);

   g_ListDlocContent(list);
   gmemDloc(list);

   greturn;
}

/**************************************************************************************************
func: g_ListDlocContent
**************************************************************************************************/
grlAPI void g_ListDlocContent(G_List * const list)
{
   G_ListItem *lcurr,
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
func: g_ListErase
**************************************************************************************************/
grlAPI Gb g_ListErase(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   litem = _LinearSearch(list, value, gbFALSE);
   greturnFalseIf(!litem);

   g_ListItemErase(list, litem);

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListEraseBegin
**************************************************************************************************/
grlAPI Gb g_ListEraseBegin(G_List * const list)
{
   G_ListItem *litem;

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
func: g_ListEraseEnd
**************************************************************************************************/
grlAPI Gb g_ListEraseEnd(G_List * const list)
{
   G_ListItem *litem;

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
func: g_ListFind
**************************************************************************************************/
grlAPI G_ListItem *g_ListFind(G_List const * const list, Gp const * const value)
{
   G_ListItem *result;

   genter;

   result = _LinearSearch(list, value, gbFALSE);

   greturn result;
}

/**************************************************************************************************
func: g_ListFlush
**************************************************************************************************/
grlAPI void g_ListFlush(G_List * const list)
{
   genter;

   loop
   {
      breakIf(list->count == 0);
      g_ListEraseEnd(list);
   }

   greturn;
}

/**************************************************************************************************
func: g_ListForEach
**************************************************************************************************/
grlAPI Gb g_ListForEach(G_List const * const list, GrlForEachFunc const func)
{
   G_ListItem const *litem,
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

      func(DATA_PTR(litem));

      litem = litemNext;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: g_ListGetBegin
**************************************************************************************************/
grlAPI G_ListItem *g_ListGetBegin(G_List const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->head;
}

/**************************************************************************************************
func: g_ListGetCount
**************************************************************************************************/
grlAPI Gcount g_ListGetCount(G_List const * const list)
{
   genter;

   greturn0If(!list);

   greturn list->count;
}

/**************************************************************************************************
func: g_ListGetEnd
**************************************************************************************************/
grlAPI G_ListItem *g_ListGetEnd(G_List const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->tail;
}

/**************************************************************************************************
func: g_ListItemAdd
**************************************************************************************************/
grlAPI G_ListItem *g_ListItemAdd(G_List * const list, G_ListItem * const litem,
   Gp const * const value)
{
   G_ListItem *nitem;

   genter;

   greturnNullIf(!list);

   nitem = _ClocAndSetListItem(list, value);
   greturnNullIf(!nitem);

   g_ListItemAdd_Add(list, litem, nitem);

   list->isSorted = gbFALSE;

   greturn nitem;
}

/**************************************************************************************************
func: g_ListItemErase
**************************************************************************************************/
grlAPI G_ListItem *g_ListItemErase(G_List * const list, G_ListItem * const litem)
{
   G_ListItem *nextItem;

   genter;

   greturnNullIf(
      !list ||
      !litem);

   nextItem = litem->next;

   if      (!litem->prev)
   {
      g_ListEraseBegin(list); //lint !e534
   }
   else if (!litem->next)
   {
      g_ListEraseEnd(list); //lint !e534
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
func: g_ListItemGet
**************************************************************************************************/
grlAPI Gp *g_ListItemGet(G_ListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn DATA_PTR(litem);
}

/**************************************************************************************************
func: g_ListItemGetNext
**************************************************************************************************/
grlAPI G_ListItem *g_ListItemGetNext(G_ListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->next;
}

/**************************************************************************************************
func: g_ListItemGetPrev
**************************************************************************************************/
grlAPI G_ListItem *g_ListItemGetPrev(G_ListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->prev;
}

/**************************************************************************************************
func: g_ListItemUpdate
**************************************************************************************************/
grlAPI void g_ListItemUpdate(G_List * const list, G_ListItem * const litem, Gp const * const value)
{
   genter;

   greturnIf(!litem);

   gmemCopyOver(DATA_PTR(litem), list->typeSize, value);

   list->isSorted = gbFALSE;

   greturn;
}

/**************************************************************************************************
Like Module Local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: g_ListAddBegin_Add
**************************************************************************************************/
grlAPI void g_ListAddBegin_Add(G_List * const list, G_ListItem * const litem)
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
func: g_ListAddEnd_Add
**************************************************************************************************/
grlAPI void g_ListAddEnd_Add(G_List * const list, G_ListItem * const litem)
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
func: g_ListItemAdd_Add
**************************************************************************************************/
grlAPI void g_ListItemAdd_Add(G_List * const list, G_ListItem * const litem, G_ListItem * const nitem)
{
   genter;

   if (!litem)
   {
      g_ListAddBegin_Add(list, nitem);
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
func: g_ListItem_Cloc
**************************************************************************************************/
grlAPI G_ListItem *g_ListItem_Cloc(G_List const * const list)
{
   G_ListItem *result;

   genter;

   result = (G_ListItem *) gmemCloc("G_ListItem", gsizeof(G_ListItem) + list->typeSize);

   greturn result;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ClocAndSetListItem
**************************************************************************************************/
static G_ListItem *_ClocAndSetListItem(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   litem = g_ListItem_Cloc(list);
   greturnNullIf(!litem);

   g_ListItemUpdate(list, litem, value);

   greturn litem;
}

/**************************************************************************************************
func: _LinearSearch
**************************************************************************************************/
static G_ListItem *_LinearSearch(G_List const * const list, Gp const * const value, Gb const findLocation)
{
   G_ListItem *litem;
   Gcompare    compare;

   genter;

   greturnNullIf(
      !list              ||
      !list->compareFunc ||
      list->count == 0   ||
      !value);

   litem = g_ListGetBegin(list);

   loop
   {
      breakIf(!litem);

      compare = list->compareFunc(value, DATA_PTR(litem));
      breakIf(compare == gcompareEQUAL);

      // List is sorted, no point comparing beyond this point.
      if (list->isSorted && compare == gcompareLESS_THAN)
      {
         greturnValIf(findLocation, litem->prev);

         greturn NULL;
      }

      litem = litem->next;
   }

   greturnValIf(findLocation, list->tail);

   greturn litem;
}
