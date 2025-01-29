/**************************************************************************************************
file:         g_TreeKey
author:       Robbert de Groot
copyright:    2011-2011, Robbert de Groot

description:
Data structure for a tree representation.
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

#if !defined(G_TreeKey_HEADER)
#define      G_TreeKey_HEADER

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
typedef struct G_TreeKey     G_TreeKey;
typedef struct G_TreeKeyItem G_TreeKeyItem;

struct G_TreeKeyItem
{
   G_TreeKey            *owner;
   G_TreeKeyItem        *parent;
   G_TreeKeyItem        *childLeft;
   G_TreeKeyItem        *childRight;
   GheapN                heapValue;
   Gkey const           *key;
};

struct G_TreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc        compareFunc;
   G_TreeKeyItem        *root;
};

/**************************************************************************************************
prototype:
**************************************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_TreeKeyCloc(             TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC) (g_TreeKey *) gleakCloc((Gp *) g_TreeKeyCloc_(               gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (COMPARE_FUNC)), gsizeof(g_TreeKey))
#define g_TreeKeyClocContent(TREE, TYPE, TYPE_SUB, IS_POINTER_TYPE, COMPARE_FUNC)                                g_TreeKeyClocContent_(  TREE, gsizeof(TYPE_SUB), TYPE, IS_POINTER_TYPE, (COMPARE_FUNC))
//lint -restore

grlAPI G_TreeKeyItem *g_TreeKeyAdd(             G_TreeKey       * const tree, Gkey const * const key, Gp const * const value);

grlAPI G_TreeKey     *g_TreeKeyCloc_(                                         Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc);
grlAPI Gb             g_TreeKeyClocContent_(    G_TreeKey       * const tree, Gsize const typeSize, Char const * const typeName, Gb const isPointerType, GrlCompareFunc const compareFunc);

grlAPI void           g_TreeKeyDloc(            G_TreeKey       * const tree);
grlAPI void           g_TreeKeyDlocContent(     G_TreeKey       * const tree);

grlAPI Gb             g_TreeKeyErase(           G_TreeKey       * const tree, Gkey const * const key);
grlAPI Gb             g_TreeKeyEraseBegin(      G_TreeKey       * const tree);
grlAPI Gb             g_TreeKeyEraseEnd(        G_TreeKey       * const tree);

grlAPI G_TreeKeyItem *g_TreeKeyFind(            G_TreeKey const * const tree, Gkey const * const key);
grlAPI void           g_TreeKeyFlush(           G_TreeKey       * const tree);
grlAPI Gb             g_TreeKeyForEach(         G_TreeKey const * const tree, GrlForEachKeyFunc const func);

grlAPI G_TreeKeyItem *g_TreeKeyGetBegin(        G_TreeKey const * const tree);
grlAPI Gcount         g_TreeKeyGetCount(        G_TreeKey const * const tree);
grlAPI G_TreeKeyItem *g_TreeKeyGetEnd(          G_TreeKey const * const tree);

// g_TreeKeyItem functions
grlAPI G_TreeKeyItem *g_TreeKeyItemDloc(        G_TreeKey       * const tree, G_TreeKeyItem * const treeItem);

grlAPI Gp            *g_TreeKeyItemGet(         G_TreeKeyItem const * const treeItem);
grlAPI G_TreeKeyItem *g_TreeKeyItemGetNext(     G_TreeKeyItem const * const treeItem);
grlAPI G_TreeKeyItem *g_TreeKeyItemGetPrev(     G_TreeKeyItem const * const treeItem);

grlAPI void           g_TreeKeyItemUpdate(      G_TreeKey       * const tree, G_TreeKeyItem * const treeItem, Gp const * const value);

#if defined(_DEBUG)
//grlAPI Gs          *g_TreeKeyDump(              G_TreeKey const * const tree);
#else
//#define             g_TreeKeyDump(TREE) NULL
#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
