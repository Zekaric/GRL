/**************************************************************************************************
file:         GvTree
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

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct GvTree     GvTree;
typedef struct GvTreeItem GvTreeItem;

struct GvTreeItem
{
   GvTree            *owner;
   GvTreeItem        *parent;
   GvTreeItem        *childLeft;
   GvTreeItem        *childRight;
   GheapN             heapValue;
   Gv                 v;
};

struct GvTree
{
   GCONTAINER_VAR;

   GrlCompareFunc     compareFunc;
   GvTreeItem        *root;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gvTreeCloc(             TYPE, COMPARE_FUNC)   gleakClocType(gvTreeCloc_(               (Char *) TYPE, (COMPARE_FUNC)), GvTree)
#define gvTreeClocContent(TREE, TYPE, COMPARE_FUNC)                 gvTreeClocContent_(  TREE, (Char *) TYPE, (COMPARE_FUNC))

grlAPI GvTreeItem *gvTreeAdd(             GvTree       * const tree, Gv const value);

grlAPI GvTree     *gvTreeCloc_(                                      Char const * const typeName, GrlCompareFunc const compareFunc);
grlAPI Gb          gvTreeClocContent_(    GvTree       * const tree, Char const * const typeName, GrlCompareFunc const compareFunc);

grlAPI void        gvTreeDloc(            GvTree       * const tree);
grlAPI void        gvTreeDlocContent(     GvTree       * const tree);

grlAPI Gb          gvTreeErase(           GvTree       * const tree, Gv const value);
grlAPI Gb          gvTreeEraseBegin(      GvTree       * const tree);
grlAPI Gb          gvTreeEraseEnd(        GvTree       * const tree);

grlAPI GvTreeItem *gvTreeFind(            GvTree const * const tree, Gv const value);
grlAPI void        gvTreeFlush(           GvTree       * const tree);
grlAPI Gb          gvTreeForEach(         GvTree const * const tree, GrlForEachFunc const func);

grlAPI GvTreeItem *gvTreeGetBegin(        GvTree const * const tree);
grlAPI Gcount      gvTreeGetCount(        GvTree const * const tree);
grlAPI GvTreeItem *gvTreeGetEnd(          GvTree const * const tree);

// GvTreeItem functions
grlAPI Gv          gvTreeItemGet(         GvTreeItem const * const treeItem);
grlAPI GvTreeItem *gvTreeItemGetNext(     GvTreeItem const * const treeItem);
grlAPI GvTreeItem *gvTreeItemGetPrev(     GvTreeItem const * const treeItem);

#if defined(_DEBUG)
grlAPI Gs         *gvTreeDump(               GvTree const * const tree);
#else
#define            gvTreeDump(TREE) NULL
#endif

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
