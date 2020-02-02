/******************************************************************************
file:       g_List
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot
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
#define DATA_PTR(LITEM)    ((Gp *) &(LITEM[1]))

static G_ListItem *_CreateAndSetListItem( G_List       * const list, Gp const * const value);

static G_ListItem *_LinearSearch(         G_List const * const list, Gp const * const value, Gb const findLocation);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: g_ListAdd
******************************************************************************/
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

/******************************************************************************
func: g_ListAddBegin
******************************************************************************/
grlAPI G_ListItem *g_ListAddBegin(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   greturnIf(!list, NULL);

   litem = _CreateAndSetListItem(list, value);
   greturnIf(!litem, NULL);

   g_ListAddBegin_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/******************************************************************************
func: g_ListAddEnd
******************************************************************************/
grlAPI G_ListItem *g_ListAddEnd(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   greturnIf(!list, NULL);

   litem = _CreateAndSetListItem(list, value);
   greturnIf(!litem, NULL);

   g_ListAddEnd_Add(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/******************************************************************************
func: g_ListCreate_
******************************************************************************/
grlAPI G_List *g_ListCreate_(Gsize const typeSize, Char const * const typeName,
   Char const * const typeNameSub, GrlCompareFunc const compareFunc)
{
   G_List *list;

   genter;

   greturnIf(
         typeSize <= 0 ||
         !typeName     ||
         !typeNameSub,
      NULL);

   list = gmemCreateType(G_List);
   greturnIf(!list, NULL);

   if (!g_ListCreateContent_(list, typeSize, typeName, typeNameSub, compareFunc))
   {
      g_ListDestroy(list);
      greturn NULL;
   }

   greturn list;
}

/******************************************************************************
func: g_ListCreateContent_
******************************************************************************/
grlAPI Gb g_ListCreateContent_(G_List * const list, Gsize const typeSize,
   Char const * const typeName, Char const * const typeNameSub,
   GrlCompareFunc const compareFunc)
{
   genter;

   greturnIf(
         typeSize <= 0 ||
         !typeName     ||
         !typeNameSub,
      gbFALSE);

   list->typeName    = typeName;
   list->typeNameSub = typeNameSub;
   list->typeSize    = typeSize;
   list->compareFunc = compareFunc;

   if (list->compareFunc)
   {
      list->isSorted = gbTRUE;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_ListDestroy
******************************************************************************/
grlAPI void g_ListDestroy(G_List * const list)
{
   genter;

   greturnVoidIf(!list);

   g_ListDestroyContent(list);
   gmemDestroy(list);

   greturn;
}

/******************************************************************************
func: g_ListDestroyContent
******************************************************************************/
grlAPI void g_ListDestroyContent(G_List * const list)
{
   G_ListItem *lcurr,
              *lnext;

   genter;

   greturnVoidIf(!list);

   lcurr = list->head;
   loop
   {
      breakIf(lcurr == NULL);

      lnext = lcurr->next;
      gmemDestroy(lcurr);
      lcurr = lnext;
   }

   list->head    = 
      list->tail = NULL;
   list->count   = 0;

   greturn;
}

/******************************************************************************
func: g_ListErase
******************************************************************************/
grlAPI Gb g_ListErase(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   litem = _LinearSearch(list, value, gbFALSE);
   greturnIf(!litem, gbFALSE);

   g_ListItemErase(list, litem);

   greturn gbTRUE;
}

/******************************************************************************
func: g_ListEraseBegin
******************************************************************************/
grlAPI Gb g_ListEraseBegin(G_List * const list)
{
   G_ListItem *litem;

   genter;

   greturnIf(
         !list ||
         !list->head,
      gbFALSE);

   litem      = list->head;
   list->head = litem->next;

   gmemDestroy(litem);

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

/******************************************************************************
func: g_ListEraseEnd
******************************************************************************/
grlAPI Gb g_ListEraseEnd(G_List * const list)
{
   G_ListItem *litem;

   genter;

   greturnIf(
         !list ||
         !list->tail,
      gbFALSE);

   litem      = list->tail;
   list->tail = litem->prev;

   gmemDestroy(litem);

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

/******************************************************************************
func: g_ListFind
******************************************************************************/
grlAPI G_ListItem *g_ListFind(G_List const * const list, Gp const * const value)
{
   G_ListItem *result;

   genter;
   
   result = _LinearSearch(list, value, gbFALSE);

   greturn result;
}

/******************************************************************************
func: g_ListFlush
******************************************************************************/
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

/******************************************************************************
func: g_ListForEach
******************************************************************************/
grlAPI Gb g_ListForEach(G_List const * const list, GrlForEachFunc const func)
{
   G_ListItem const *litem,
                    *litemNext;

   genter;

   greturnIf(
         !list ||
         !func,
      gbFALSE);

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

/******************************************************************************
func: g_ListGetBegin
******************************************************************************/
grlAPI G_ListItem *g_ListGetBegin(G_List const * const list)
{
   genter;

   greturnIf(!list, NULL);

   greturn list->head;
}

/******************************************************************************
func: g_ListGetCount
******************************************************************************/
grlAPI Gcount g_ListGetCount(G_List const * const list)
{
   genter;

   greturnIf(!list, 0);

   greturn list->count;
}

/******************************************************************************
func: g_ListGetEnd
******************************************************************************/
grlAPI G_ListItem *g_ListGetEnd(G_List const * const list)
{
   genter;

   greturnIf(!list, NULL);

   greturn list->tail;
}

/******************************************************************************
func: g_ListItemAdd
******************************************************************************/
grlAPI G_ListItem *g_ListItemAdd(G_List * const list, G_ListItem * const litem,
   Gp const * const value)
{
   G_ListItem *nitem;

   genter;

   greturnIf(!list, NULL);

   nitem = _CreateAndSetListItem(list, value);
   greturnIf(!nitem, NULL);

   g_ListItemAdd_Add(list, litem, nitem);

   list->isSorted = gbFALSE;

   greturn nitem;
}

/******************************************************************************
func: g_ListItemErase
******************************************************************************/
grlAPI G_ListItem *g_ListItemErase(G_List * const list, G_ListItem * const litem)
{
   G_ListItem *nextItem;

   genter;

   greturnIf(
         !list ||
         !litem,
      NULL);

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

      gmemDestroy(litem);

      list->count--;
   }

   greturn nextItem;
}

/******************************************************************************
func: g_ListItemGet
******************************************************************************/
grlAPI Gp *g_ListItemGet(G_ListItem const * const litem)
{
   genter;

   greturnIf(!litem, NULL);

   greturn DATA_PTR(litem);
}

/******************************************************************************
func: g_ListItemGetNext
******************************************************************************/
grlAPI G_ListItem *g_ListItemGetNext(G_ListItem const * const litem)
{
   genter;

   greturnIf(!litem, NULL);

   greturn litem->next;
}

/******************************************************************************
func: g_ListItemGetPrev
******************************************************************************/
grlAPI G_ListItem *g_ListItemGetPrev(G_ListItem const * const litem)
{
   genter;

   greturnIf(!litem, NULL);

   greturn litem->prev;
}

/******************************************************************************
func: g_ListItemUpdate
******************************************************************************/
grlAPI void g_ListItemUpdate(G_List * const list, G_ListItem * const litem, Gp const * const value)
{
   genter;

   greturnVoidIf(!litem);

   gmemCopyOver(value, list->typeSize, DATA_PTR(litem));

   list->isSorted = gbFALSE;

   greturn;
}

/******************************************************************************
Like Module Local: 
function:
******************************************************************************/
/******************************************************************************
func: g_ListAddBegin_Add
******************************************************************************/
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

/******************************************************************************
func: g_ListAddEnd_Add
******************************************************************************/
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

/******************************************************************************
func: g_ListItemAdd_Add
******************************************************************************/
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

/******************************************************************************
func: g_ListItem_Create
******************************************************************************/
grlAPI G_ListItem *g_ListItem_Create(G_List const * const list)
{
   G_ListItem *result;

   genter;
   
   result = (G_ListItem *) gmemCreate("G_ListItem", gsizeof(G_ListItem) + list->typeSize);

   greturn result;
}

/******************************************************************************
local: 
function:
******************************************************************************/
/******************************************************************************
func: _CreateAndSetListItem
******************************************************************************/
static G_ListItem *_CreateAndSetListItem(G_List * const list, Gp const * const value)
{
   G_ListItem *litem;

   genter;

   litem = g_ListItem_Create(list);
   greturnNullIf(!litem);

   g_ListItemUpdate(list, litem, value);

   greturn litem;
}

/******************************************************************************
func: _LinearSearch
******************************************************************************/
static G_ListItem *_LinearSearch(G_List const * const list, Gp const * const value, Gb const findLocation)
{
   G_ListItem *litem;
   Gcompare    compare;

   genter;

   greturnIf(
         !list              ||
         !list->compareFunc ||
         list->count == 0   ||
         !value,
      NULL);

   litem = g_ListGetBegin(list);

   loop
   {
      breakIf(!litem);

      compare = list->compareFunc(value, DATA_PTR(litem));
      breakIf(compare == gcompareEQUAL);

      // List is sorted, no point comparing beyond this point.
      if (list->isSorted && compare == gcompareLESS_THAN)
      {
         greturnIf(findLocation, litem->prev);
         greturn NULL;
      }

      litem = litem->next;
   }

   greturnIf(findLocation, list->tail);
   greturn litem;
}
