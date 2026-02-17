/**************************************************************************************************
file:       gkvList
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

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct GkvListItem GkvListItem;
struct GkvListItem
{
   GkvListItem    *next,
                  *prev;
   Gkv             kv;
};

typedef struct GkvList GkvList;
struct GkvList
{
   GCONTAINER_VAR;

   GrlCompareFunc  compareFunc;
   Gb              isSorted;
   GkvListItem    *head,
                  *tail;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gkvListCloc(             TYPE, COMPARE_FUNC)   gleakClocType(gkvListCloc_(               (Char *) TYPE, (COMPARE_FUNC)), GkvList)
#define gkvListClocContent(LIST, TYPE, COMPARE_FUNC)                 gkvListClocContent_(  LIST, (Char *) TYPE, (COMPARE_FUNC))

grlAPI GkvListItem   *gkvListAdd(            GkvList       * const list, Gk const * const key, Gv const value);
grlAPI GkvListItem   *gkvListAddBegin(       GkvList       * const list, Gk const * const key, Gv const value);
grlAPI GkvListItem   *gkvListAddEnd(         GkvList       * const list, Gk const * const key, Gv const value);

grlAPI GkvList       *gkvListCloc_(                                      Char const * const typeName, GrlCompareFunc const compareFunc);
grlAPI Gb             gkvListClocContent_(   GkvList       * const list, Char const * const typeName, GrlCompareFunc const compareFunc);

grlAPI void           gkvListDloc(           GkvList       * const list);
grlAPI void           gkvListDlocContent(    GkvList       * const list);

grlAPI Gb             gkvListErase(          GkvList       * const list, Gk const * const key);
grlAPI Gb             gkvListEraseBegin(     GkvList       * const list);
grlAPI Gb             gkvListEraseEnd(       GkvList       * const list);

grlAPI GkvListItem   *gkvListFind(           GkvList const * const list, Gk const * const key);
grlAPI void           gkvListFlush(          GkvList       * const list);
grlAPI Gb             gkvListForEach(        GkvList const * const list, GrlForEachKeyFunc const func);

grlAPI GkvListItem   *gkvListGetBegin(       GkvList const * const list);
grlAPI Gcount         gkvListGetCount(       GkvList const * const list);
grlAPI GkvListItem   *gkvListGetEnd(         GkvList const * const list);

// GkvListItem functions
grlAPI GkvListItem   *gkvListItemAdd(        GkvList       * const list, GkvListItem       * const litem, Gk const * const key, Gv const value);

grlAPI GkvListItem   *gkvListItemErase(      GkvList       * const list, GkvListItem       * const litem);

grlAPI Gv             gkvListItemGet(                                    GkvListItem const * const litem);
grlAPI Gk const      *gkvListItemGetKey(                                 GkvListItem const * const litem);
grlAPI GkvListItem   *gkvListItemGetNext(                                GkvListItem const * const litem);
grlAPI GkvListItem   *gkvListItemGetPrev(                                GkvListItem const * const litem);

grlAPI Gb             gkvListItemUpdate(                                 GkvListItem       * const litem, Gv const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
