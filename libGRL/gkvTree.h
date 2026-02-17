/**************************************************************************************************
file:         GkvTree
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
Data structure for a tree representation.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2011, Robbert de Groot

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

/**************************************************************************************************
include:
**************************************************************************************************/

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct GkvTree     GkvTree;
typedef struct GkvTreeItem GkvTreeItem;

struct GkvTreeItem
{
   GkvTree           *owner;
   GkvTreeItem       *parent;
   GkvTreeItem       *childLeft;
   GkvTreeItem       *childRight;
   GheapN             heapValue;
   Gkv                kv;
};

struct GkvTree
{
   GCONTAINER_VAR;

   GrlCompareFunc     compareFunc;
   GkvTreeItem       *root;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gkvTreeCloc(             TYPE, COMPARE_FUNC)   gleakClocType(gkvTreeCloc_(               (Char *) TYPE, (COMPARE_FUNC)), gkvTree)
#define gkvTreeClocContent(TREE, TYPE, COMPARE_FUNC)                 gkvTreeClocContent_(  TREE, (Char *) TYPE, (COMPARE_FUNC))

grlAPI GkvTreeItem   *gkvTreeAdd(             GkvTree       * const tree, Gk const * const key, Gv const value);

grlAPI GkvTree       *gkvTreeCloc_(                                       Char const * const typeName, GrlCompareFunc const compareFunc);
grlAPI Gb             gkvTreeClocContent_(    GkvTree       * const tree, Char const * const typeName, GrlCompareFunc const compareFunc);

grlAPI void           gkvTreeDloc(            GkvTree       * const tree);
grlAPI void           gkvTreeDlocContent(     GkvTree       * const tree);

grlAPI Gb             gkvTreeErase(           GkvTree       * const tree, Gk const * const key);
grlAPI Gb             gkvTreeEraseBegin(      GkvTree       * const tree);
grlAPI Gb             gkvTreeEraseEnd(        GkvTree       * const tree);

grlAPI GkvTreeItem   *gkvTreeFind(            GkvTree const * const tree, Gk const * const key);
grlAPI void           gkvTreeFlush(           GkvTree       * const tree);
grlAPI Gb             gkvTreeForEach(         GkvTree const * const tree, GrlForEachKeyFunc const func);

grlAPI GkvTreeItem   *gkvTreeGetBegin(        GkvTree const * const tree);
grlAPI Gcount         gkvTreeGetCount(        GkvTree const * const tree);
grlAPI GkvTreeItem   *gkvTreeGetEnd(          GkvTree const * const tree);

// gkvTreeItem functions
grlAPI Gv             gkvTreeItemGet(         GkvTreeItem const * const treeItem);
grlAPI Gk const      *gkvTreeItemGetKey(      GkvTreeItem const * const treeItem);
grlAPI GkvTreeItem   *gkvTreeItemGetNext(     GkvTreeItem const * const treeItem);
grlAPI GkvTreeItem   *gkvTreeItemGetPrev(     GkvTreeItem const * const treeItem);

grlAPI Gb             gkvTreeItemUpdate(      GkvTreeItem       * const treeItem, Gv const value);

#if defined(_DEBUG)
grlAPI Gs            *gkvTreeDump(              GkvTree const * const tree);
#else
#define               gkvTreeDump(TREE) NULL
#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
