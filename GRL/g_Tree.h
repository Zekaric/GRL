/******************************************************************************
file:         G_Tree
author:       Robbert de Groot
copyright:    2011-2011, Robbert de Groot

description:
Data structure for a tree representation.
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

#if !defined(G_Tree_HEADER)
#define      G_Tree_HEADER

/******************************************************************************
include:
******************************************************************************/

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
type:
******************************************************************************/
typedef struct G_Tree     G_Tree;
typedef struct G_TreeItem G_TreeItem;

struct G_TreeItem
{
   G_Tree            *owner;
   G_TreeItem        *parent;
   G_TreeItem        *childLeft;
   G_TreeItem        *childRight;
   GheapN             heapValue;
};

struct G_Tree
{
   GCONTAINER_VAR

   GrlCompareFunc     compareFunc;
   G_TreeItem        *root;
};

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_TreeCreate(             TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC) (G_Tree *) gleakCreate((Gp *) g_TreeCreate_(             gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (COMPARE_FUNC)), gsizeof(G_Tree)) 
#define g_TreeCreateContent(TREE, TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC)                               g_TreeCreateContent_(TREE, gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (COMPARE_FUNC))
//lint -restore

grlAPI G_TreeItem *g_TreeAdd(             G_Tree       * const tree, Gp const * const value);

grlAPI G_Tree     *g_TreeCreate_(                                    Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc);
grlAPI Gb          g_TreeCreateContent_(  G_Tree       * const tree, Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc);

grlAPI void        g_TreeDestroy(         G_Tree       * const tree);
grlAPI void        g_TreeDestroyContent(  G_Tree       * const tree);

grlAPI Gb          g_TreeErase(           G_Tree       * const tree, Gp const * const value);
grlAPI Gb          g_TreeEraseBegin(      G_Tree       * const tree);
grlAPI Gb          g_TreeEraseEnd(        G_Tree       * const tree);

grlAPI G_TreeItem *g_TreeFind(            G_Tree const * const tree, Gp const * const value);
grlAPI void        g_TreeFlush(           G_Tree       * const tree);
grlAPI Gb          g_TreeForEach(         G_Tree const * const tree, GrlForEachFunc const func);

grlAPI G_TreeItem *g_TreeGetBegin(        G_Tree const * const tree);
grlAPI Gcount      g_TreeGetCount(        G_Tree const * const tree);
grlAPI G_TreeItem *g_TreeGetEnd(          G_Tree const * const tree);

// G_TreeItem functions
grlAPI G_TreeItem *g_TreeItemDestroy(     G_Tree       * const tree, G_TreeItem * const treeItem);

grlAPI Gp         *g_TreeItemGet(         G_TreeItem const * const treeItem);
grlAPI G_TreeItem *g_TreeItemGetNext(     G_TreeItem const * const treeItem);
grlAPI G_TreeItem *g_TreeItemGetPrev(     G_TreeItem const * const treeItem);

grlAPI void        g_TreeItemUpdate(      G_Tree       * const tree, G_TreeItem * const treeItem, Gp const * const value);

#if defined(_DEBUG)
//grlAPI Gs       *g_TreeDump(               G_Tree const * const tree);
#else
//#define         g_TreeDump(TREE) NULL
#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
