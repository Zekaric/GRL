/**************************************************************************************************
file:       gvList
author:     Robbert de Groot
copyright:  2002, Robbert de Groot
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
static void        _AddBegin( GvList       * const list, GvListItem       * const litem);
static void        _AddEnd(   GvList       * const list, GvListItem       * const litem);

static void        _ItemAdd(  GvList       * const list, GvListItem       * const litem, GvListItem * const nitem);

static GvListItem *_Search(   GvList const * const list, Gv const value, Gb const findLocation);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gvListAdd
**************************************************************************************************/
grlAPI GvListItem *gvListAdd(GvList * const list, Gv const value)
{
   GvListItem *litem;

   genter;

   greturnNullIf(
      !list ||
      !list->isSorted);

   if (list->count == 0)
   {
      litem = gvListAddBegin(list, value);
   }
   else
   {
      // Find the position.
      litem = _Search(list, value, gbTRUE);

      // Add the new item.
      litem = gvListItemAdd(list, litem, value);
   }

   list->isSorted = gbTRUE;

   // Return the item.
   greturn litem;
}

/**************************************************************************************************
func: gvListAddBegin
**************************************************************************************************/
grlAPI GvListItem *gvListAddBegin(GvList * const list, Gv const value)
{
   GvListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = gmemClocType(GvListItem);
   greturnNullIf(!litem);

   litem->v = value;

   _AddBegin(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: gvListAddEnd
**************************************************************************************************/
grlAPI GvListItem *gvListAddEnd(GvList * const list, Gv const value)
{
   GvListItem *litem;

   genter;

   greturnNullIf(!list);

   litem = gmemClocType(GvListItem);
   greturnNullIf(!litem);

   litem->v = value;

   _AddEnd(list, litem);

   list->isSorted = gbFALSE;

   greturn litem;
}

/**************************************************************************************************
func: gvListCloc
**************************************************************************************************/
grlAPI GvList *gvListCloc_(Char const * const typeName, GrlCompareFunc const compareFunc)
{
   GvList *list;

   genter;

   list = gmemClocType(GvList);
   greturnNullIf(!list);

   if (!gvListClocContent_(list, typeName, compareFunc))
   {
      gvListDloc(list);
      greturn NULL;
   }

   greturn list;
}

/**************************************************************************************************
func: gvListClocContent_
**************************************************************************************************/
grlAPI Gb gvListClocContent_(GvList * const list, Char const * const typeName,
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
func: gvListDloc
**************************************************************************************************/
grlAPI void gvListDloc(GvList * const list)
{
   genter;

   greturnIf(!list);

   gvListDlocContent(list);
   gmemDloc(list);

   greturn;
}

/**************************************************************************************************
func: gvListDlocContent
**************************************************************************************************/
grlAPI void gvListDlocContent(GvList * const list)
{
   GvListItem *lcurr,
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
func: gvListErase
**************************************************************************************************/
grlAPI Gb gvListErase(GvList * const list, Gv const value)
{
   GvListItem *litem;

   genter;

   litem = _Search(list, value, gbFALSE);
   greturnFalseIf(!litem);

   gvListItemErase(list, litem);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvListEraseBegin
**************************************************************************************************/
grlAPI Gb gvListEraseBegin(GvList * const list)
{
   GvListItem *litem;

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
func: gvListEraseEnd
**************************************************************************************************/
grlAPI Gb gvListEraseEnd(GvList * const list)
{
   GvListItem *litem;

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
func: gvListFind
**************************************************************************************************/
grlAPI GvListItem *gvListFind(GvList const * const list, Gv const value)
{
   genter;

   greturn _Search(list, value, gbFALSE);
}

/**************************************************************************************************
func: gvListFlush
**************************************************************************************************/
grlAPI void gvListFlush(GvList * const list)
{
   genter;

   loop
   {
      breakIf(list->count == 0);
      gvListEraseEnd(list);
   }

   if (list->compareFunc)
   {
      list->isSorted = gbTRUE;
   }

   greturn;
}

/**************************************************************************************************
func: gvListForEach
**************************************************************************************************/
grlAPI Gb gvListForEach(GvList const * const list, GrlForEachFunc const func)
{
   GvListItem const *litem,
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

      func((Gp *) &litem->v);

      litem = litemNext;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvListGetBegin
**************************************************************************************************/
grlAPI GvListItem *gvListGetBegin(GvList const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->head;
}

/**************************************************************************************************
func: gvListGetCount
**************************************************************************************************/
grlAPI Gcount gvListGetCount(GvList const * const list)
{
   genter;

   greturn0If(!list);

   greturn list->count;
}

/**************************************************************************************************
func: gvListGetEnd
**************************************************************************************************/
grlAPI GvListItem *gvListGetEnd(GvList const * const list)
{
   genter;

   greturnNullIf(!list);

   greturn list->tail;
}

/**************************************************************************************************
func: gvListItemAdd
**************************************************************************************************/
grlAPI GvListItem *gvListItemAdd(GvList * const list, GvListItem * const litem, Gv const value)
{
   GvListItem *nitem;

   genter;

   greturnNullIf(!list);

   nitem = gmemClocType(GvListItem);
   greturnNullIf(!nitem);

   nitem->v = value;

   _ItemAdd(list, litem, nitem);

   list->isSorted = gbFALSE;

   greturn nitem;
}

/**************************************************************************************************
func: gvListItemErase
**************************************************************************************************/
grlAPI GvListItem *gvListItemErase(GvList * const list, GvListItem * const litem)
{
   GvListItem *nextItem;

   genter;

   greturnNullIf(
      !list ||
      !litem);

   nextItem = litem->next;

   if      (!litem->prev)
   {
      gvListEraseBegin(list);
   }
   else if (!litem->next)
   {
      gvListEraseEnd(list);
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
func: gvListItemGet
**************************************************************************************************/
grlAPI Gv gvListItemGet(GvListItem const * const litem)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(!litem, zero);

   greturn litem->v;
}

/**************************************************************************************************
func: gvListItemGetNext
**************************************************************************************************/
grlAPI GvListItem *gvListItemGetNext(GvListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->next;
}

/**************************************************************************************************
func: gvListItemGetPrev
**************************************************************************************************/
grlAPI GvListItem *gvListItemGetPrev(GvListItem const * const litem)
{
   genter;

   greturnNullIf(!litem);

   greturn litem->prev;
}

/**************************************************************************************************
func: gvListItemUpdate
**************************************************************************************************/
grlAPI Gb gvListItemUpdate(GvList * const list, GvListItem * const litem, Gv const value)
{
   genter;

   greturnFalseIf(!litem);

   litem->v       = value;
   list->isSorted = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _AddBegin
**************************************************************************************************/
void _AddBegin(GvList * const list, GvListItem * const litem)
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
void _AddEnd(GvList * const list, GvListItem * const litem)
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
void _ItemAdd(GvList * const list, GvListItem * const litem, GvListItem * const nitem)
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
static GvListItem *_Search(GvList const * const list, Gv const value, Gb const findLocation)
{
   GvListItem *litem;
   Gcompare    compare;

   genter;

   greturnNullIf(
      !list              ||
      !list->compareFunc ||
      list->count == 0);

   litem = gvListGetBegin(list);

   loop
   {
      breakIf(!litem);

      compare = list->compareFunc(&value, &litem->v);
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
