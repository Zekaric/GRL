/******************************************************************************
file:       g_ListKey
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
Base for double linked list.
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

#if !defined(G_LISTKEYH)
#define      G_LISTKEYH

/******************************************************************************
type:
******************************************************************************/
typedef struct G_ListKeyItem G_ListKeyItem;
struct G_ListKeyItem
{
   G_ListKeyItem     *next,
                     *prev;
   Gkey const        *key;
};

typedef struct G_ListKey G_ListKey;
struct G_ListKey
{
   GCONTAINER_VAR

   GrlCompareFunc     compareFunc;
   Gb                 isSorted;
   G_ListKeyItem     *head,
                     *tail;
};

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_ListKeyCreate(TYPE, TYPE_SUB) \
   ((G_ListKey *) gleakCreate((Gp *) g_ListKeyCreate_(gsizeof(TYPE_SUB), #TYPE, #TYPE_SUB), gsizeof(G_ListKey)))
//lint -restore

grlAPI G_ListKeyItem *g_ListKeyAdd(             G_ListKey       * const list, Gkey const * const key, Gp const * const value);
grlAPI G_ListKeyItem *g_ListKeyAddBegin(        G_ListKey       * const list, Gkey const * const key, Gp const * const value);
grlAPI G_ListKeyItem *g_ListKeyAddEnd(          G_ListKey       * const list, Gkey const * const key, Gp const * const value);

grlAPI G_ListKey     *g_ListKeyCreate_(                                       Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GrlCompareFunc const compareFunc);
grlAPI Gb             g_ListKeyCreateContent(   G_ListKey       * const list, Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GrlCompareFunc const compareFunc);

grlAPI void           g_ListKeyDestroy(         G_ListKey       * const list);
grlAPI void           g_ListKeyDestroyContent(  G_ListKey       * const list);

grlAPI Gb             g_ListKeyErase(           G_ListKey       * const list, Gkey const * const key);
grlAPI Gb             g_ListKeyEraseBegin(      G_ListKey       * const list);
grlAPI Gb             g_ListKeyEraseEnd(        G_ListKey       * const list);

grlAPI G_ListKeyItem *g_ListKeyFind(            G_ListKey const * const list, Gkey const * const key);
grlAPI void           g_ListKeyFlush(           G_ListKey       * const list);
grlAPI Gb             g_ListKeyForEach(         G_ListKey const * const list, GrlForEachKeyFunc const func);

grlAPI G_ListKeyItem *g_ListKeyGetBegin(        G_ListKey const * const list);
grlAPI Gcount         g_ListKeyGetCount(        G_ListKey const * const list);
grlAPI G_ListKeyItem *g_ListKeyGetEnd(          G_ListKey const * const list);

// G_ListKeyItem functions
grlAPI G_ListKeyItem *g_ListKeyItemAdd(         G_ListKey       * const list, G_ListKeyItem * const litem, Gkey const * const key, Gp const * const value);

grlAPI G_ListKeyItem *g_ListKeyItemErase(       G_ListKey       * const list, G_ListKeyItem * const litem);

grlAPI Gp            *g_ListKeyItemGet(         G_ListKeyItem const * const litem);
grlAPI Gkey const    *g_ListKeyItemGetKey(      G_ListKeyItem const * const litem);
grlAPI G_ListKeyItem *g_ListKeyItemGetNext(     G_ListKeyItem const * const litem);
grlAPI G_ListKeyItem *g_ListKeyItemGetPrev(     G_ListKeyItem const * const litem);

grlAPI void           g_ListKeyItemUpdate(      G_ListKey       * const list, G_ListKeyItem * const litem, Gp const * const value);
grlAPI void           g_ListKeyItemUpdateKey(   G_ListKey       * const list, G_ListKeyItem * const litem, Gkey const * const key);

// Locally called for any g_ListKey* routines an not to be used elsewhere.
grlAPI void           g_ListKeyAddBegin_Add(    G_ListKey       * const list, G_ListKeyItem * const litem);
grlAPI void           g_ListKeyAddEnd_Add(      G_ListKey       * const list, G_ListKeyItem * const litem);

grlAPI void           g_ListKeyItemAdd_Add(     G_ListKey       * const list, G_ListKeyItem * const litem, G_ListKeyItem * const nitem);
grlAPI G_ListKeyItem *g_ListKeyItem_Create(     G_ListKey const * const list);

#endif
