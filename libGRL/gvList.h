/**************************************************************************************************
file:       gvList
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
Base for double linked list.
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

#pragma once

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct GvListItem GvListItem;
struct GvListItem
{
   GvListItem        *next,
                     *prev;
   Gv                 v;
};

typedef struct GvList GvList;
struct GvList
{
   GCONTAINER_VAR;

   GrlCompareFunc     compareFunc;
   Gb                 isSorted;
   GvListItem        *head,
                     *tail;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gvListCloc(             TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC)   gleakClocType(gvListCloc_(               gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC)), GvList)
#define gvListClocContent(LIST, TYPE, TYPE_SUB, IS_POINTER_TYPE, OPTIONAL_COMPARE_FUNC)                 gvListClocContent_(  LIST, gsizeof(TYPE_SUB), (Char *) TYPE, IS_POINTER_TYPE, (OPTIONAL_COMPARE_FUNC))

grlAPI GvListItem *gvListAdd(             GvList       * const list, Gv const value);
grlAPI GvListItem *gvListAddBegin(        GvList       * const list, Gv const value);
grlAPI GvListItem *gvListAddEnd(          GvList       * const list, Gv const value);

grlAPI GvList     *gvListCloc_(                                      Char const * const typeName, GrlCompareFunc const compareFunc);
grlAPI Gb          gvListClocContent_(    GvList       * const list, Char const * const typeName, GrlCompareFunc const compareFunc);

grlAPI void        gvListDloc(            GvList       * const list);
grlAPI void        gvListDlocContent(     GvList       * const list);

grlAPI Gb          gvListErase(           GvList       * const list, Gv const value);
grlAPI Gb          gvListEraseBegin(      GvList       * const list);
grlAPI Gb          gvListEraseEnd(        GvList       * const list);

grlAPI GvListItem *gvListFind(            GvList const * const list, Gv const value);
grlAPI void        gvListFlush(           GvList       * const list);
grlAPI Gb          gvListForEach(         GvList const * const list, GrlForEachFunc const func);

grlAPI GvListItem *gvListGetBegin(        GvList const * const list);
grlAPI Gcount      gvListGetCount(        GvList const * const list);
grlAPI GvListItem *gvListGetEnd(          GvList const * const list);

// GvListItem functions
grlAPI GvListItem *gvListItemAdd(         GvList       * const list, GvListItem       * const litem, Gv const value);

grlAPI GvListItem *gvListItemErase(       GvList       * const list, GvListItem       * const litem);

grlAPI Gv          gvListItemGet(                                    GvListItem const * const litem);
grlAPI GvListItem *gvListItemGetNext(                                GvListItem const * const litem);
grlAPI GvListItem *gvListItemGetPrev(                                GvListItem const * const litem);

grlAPI Gb          gvListItemUpdate(      GvList       * const list, GvListItem       * const litem, Gv const value);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
