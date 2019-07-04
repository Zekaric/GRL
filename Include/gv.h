/******************************************************************************
file:       gv
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
A simple array.  A simple one dimensional array of generic data
pointers, ints or naturals.
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

#if !defined(GVH)
#define      GVH

/******************************************************************************
const:
******************************************************************************/
#define gvTYPE_I "Gv:I"
#define gvTYPE_N "Gv:N"
#define gvTYPE_P "Gv:P"
#define gvTYPE_R "Gv:R"
#define gvTYPE_V "Gv"

// type defined in gconst.h

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9026
grlAPI Gcompare    gpCompare(       Gp const * const valueA, Gp const * const valueB);

// gv is a simple light data holder.  Use carfully.
grlAPI Gcompare    gvCompareI(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareN(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareP(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareR(      Gv const * const valueA, Gv const * const valueB);

grlAPI Gv         *gvCreate(        void);
grlAPI Gb          gvCreateContent( Gv       * const v);

grlAPI void        gvDestroy(       Gv       * const v);
grlAPI void        gvDestroyContent(Gv       * const v);

grlAPI Gv          gvFromI(         Gip  const value);
grlAPI Gv          gvFromN(         Gnp  const value);
grlAPI Gv          gvFromP(         Gp * const value);
grlAPI Gv          gvFromR(         Grp  const value);
grlAPI Gv          gvFromS(         Gs * const value);

grlAPI Gip         gvGetI(          Gv const * const v);
grlAPI Gnp         gvGetN(          Gv const * const v);
grlAPI Gp         *gvGetP(          Gv const * const v);
grlAPI Grp         gvGetR(          Gv const * const v);
grlAPI Gs         *gvGetS(          Gv const * const v);

grlAPI GhashN      gvHash(          Gv const * const value);
grlAPI GhashN      gvHashS(         Gv const * const value);

grlAPI Gb          gvSetI(          Gv       * const v, Gip  const value);
grlAPI Gb          gvSetN(          Gv       * const v, Gnp  const value);
grlAPI Gb          gvSetP(          Gv       * const v, Gp * const value);
grlAPI Gb          gvSetR(          Gv       * const v, Grp  const value);
grlAPI Gb          gvSetS(          Gv       * const v, Gs * const value);

// This is a helper for g[type]ForEachP() functions
grlAPI void        _GvEachP(        Gv *v, GrlForEachFunc const func);

//lint -restore

/******************************************************************************
Gv containers.
******************************************************************************/
typedef G_Array         GvArray;
typedef G_ArrayKey      GvArrayKey;   
typedef G_Hash          GvHash;    
typedef G_HashKey       GvHashKey;                                                                   
typedef G_List          GvList; 
typedef G_ListItem      GvListItem;   
typedef G_ListKey       GvListKey; 
typedef G_ListKeyItem   GvListKeyItem;   
typedef G_Tree          GvTree;
typedef G_TreeItem      GvTreeItem;
typedef G_TreeKey       GvTreeKey;
typedef G_TreeKeyItem   GvTreeKeyItem;

#define gvArrayAdd(                ARRAY,        VALUE)                                                  g_ArrayAdd(                ARRAY,        VALUE) 
#define gvArrayAddAt(              ARRAY, INDEX, VALUE)                                                  g_ArrayAddAt(              ARRAY, INDEX, VALUE) 
#define gvArrayAddBegin(           ARRAY,        VALUE)                                                  g_ArrayAddBegin(           ARRAY,        VALUE) 
#define gvArrayAddEnd(             ARRAY,        VALUE)                                                  g_ArrayAddEnd(             ARRAY,        VALUE) 
#define gvArrayClear(              ARRAY, COUNT, INDEX)                                                  g_ArrayClear(              ARRAY, COUNT, INDEX) 
#define gvArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayCopyFrom(           ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gvArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvArray *)        g_ArrayCreate(                    GvArray, Gv, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayCreateContent(      ARRAY, GvArray, Gv, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvArrayDestroy(            ARRAY)                                                                g_ArrayDestroy(            ARRAY) 
#define gvArrayDestroyContent(     ARRAY)                                                                g_ArrayDestroyContent(     ARRAY) 
#define gvArrayErase(              ARRAY, VALUE)                                                         g_ArrayErase(              ARRAY, VALUE) 
#define gvArrayEraseAt(            ARRAY, COUNT, INDEX)                                                  g_ArrayEraseAt(            ARRAY, COUNT, INDEX) 
#define gvArrayEraseBegin(         ARRAY)                                                                g_ArrayEraseBegin(         ARRAY) 
#define gvArrayEraseEnd(           ARRAY)                                                                g_ArrayEraseEnd(           ARRAY) 
#define gvArrayFind(               ARRAY, VALUE)                                                         g_ArrayFind(               ARRAY, VALUE) 
#define gvArrayFlush(              ARRAY)                                                                g_ArrayFlush(              ARRAY) 
#define gvArrayForEach(            ARRAY, FUNC)                                                          g_ArrayForEach(            ARRAY, FUNC) 
#define gvArrayGet(                ARRAY)                                             (Gv *)             g_ArrayGet(                ARRAY) 
#define gvArrayGetAt(              ARRAY, INDEX)                                      (Gv *)             g_ArrayGetAt(              ARRAY, INDEX) 
#define gvArrayGetBegin(           ARRAY)                                             (Gv *)             g_ArrayGetBegin(           ARRAY) 
#define gvArrayGetCount(           ARRAY)                                                                g_ArrayGetCount(           ARRAY) 
#define gvArrayGetEnd(             ARRAY)                                             (Gv *)             g_ArrayGetEnd(             ARRAY) 
#define gvArrayGetSize(            ARRAY)                                                                g_ArrayGetSize(            ARRAY) 
#define gvArraySetCount(           ARRAY, VALUE)                                                         g_ArraySetCount(           ARRAY, VALUE) 
#define gvArraySort(               ARRAY)                                                                g_ArraySort(               ARRAY) 
#define gvArraySwap(               ARRAY, INDEXA, INDEXB)                                                g_ArraySwap(               ARRAY, INDEXA, INDEXB) 
#define gvArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                  g_ArrayUpdateAt(           ARRAY, INDEX, VALUE) 
#define gvArrayKeyAdd(             ARRAY,        KEY, VALUE)                                             g_ArrayKeyAdd(             ARRAY,        KEY, VALUE) 
#define gvArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                             g_ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE) 
#define gvArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddBegin(        ARRAY,        KEY, VALUE) 
#define gvArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddEnd(          ARRAY,        KEY, VALUE) 
#define gvArrayKeyClear(           ARRAY, COUNT, INDEX)                                                  g_ArrayKeyClear(           ARRAY, COUNT, INDEX) 
#define gvArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gvArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvArray *)        g_ArrayKeyCreate(                 GvArray, Gv, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayKeyCreateContent(   ARRAY, GvArray, Gv, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvArrayKeyDestroy(         ARRAY)                                                                g_ArrayKeyDestroy(         ARRAY) 
#define gvArrayKeyDestroyContent(  ARRAY)                                                                g_ArrayKeyDestroyContent(  ARRAY) 
#define gvArrayKeyErase(           ARRAY, KEY)                                                           g_ArrayKeyErase(           ARRAY, KEY) 
#define gvArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                  g_ArrayKeyEraseAt(         ARRAY, COUNT, INDEX) 
#define gvArrayKeyEraseBegin(      ARRAY)                                                                g_ArrayKeyEraseBegin(      ARRAY) 
#define gvArrayKeyEraseEnd(        ARRAY)                                                                g_ArrayKeyEraseEnd(        ARRAY) 
#define gvArrayKeyFind(            ARRAY, KEY)                                                           g_ArrayKeyFind(            ARRAY, KEY) 
#define gvArrayKeyFlush(           ARRAY)                                                                g_ArrayKeyFlush(           ARRAY) 
#define gvArrayKeyForEach(         ARRAY, FUNC)                                                          g_ArrayKeyForEach(         ARRAY, FUNC) 
#define gvArrayKeyGetAt(           ARRAY, INDEX)                                      (Gv *)             g_ArrayKeyGetAt(           ARRAY, INDEX) 
#define gvArrayKeyGetAtKey(        ARRAY, INDEX)                                                         g_ArrayKeyGetAtKey(        ARRAY, INDEX) 
#define gvArrayKeyGetBegin(        ARRAY)                                             (Gv *)             g_ArrayKeyGetBegin(        ARRAY) 
#define gvArrayKeyGetBeginKey(     ARRAY)                                                                g_ArrayKeyGetBeginKey(     ARRAY) 
#define gvArrayKeyGetCount(        ARRAY)                                                                g_ArrayKeyGetCount(        ARRAY) 
#define gvArrayKeyGetEnd(          ARRAY)                                             (Gv *)             g_ArrayKeyGetEnd(          ARRAY) 
#define gvArrayKeyGetEndKey(       ARRAY)                                                                g_ArrayKeyGetEndKey(       ARRAY) 
#define gvArrayKeyGetSize(         ARRAY)                                                                g_ArrayKeyGetSize(         ARRAY) 
#define gvArrayKeySetCount(        ARRAY, VALUE)                                                         g_ArrayKeySetCount(        ARRAY, VALUE) 
#define gvArrayKeySort(            ARRAY)                                                                g_ArrayKeySort(            ARRAY) 
#define gvArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                g_ArrayKeySwap(            ARRAY, INDEXA, INDEXB) 
#define gvArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                  g_ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE) 
#define gvArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                    g_ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY) 
#define gvHashAdd(                 HASH, VALUE)                                                          g_HashAdd(                 HASH, VALUE)
#define gvHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GvHash *)         g_HashCreate(                    GvHash, Gv, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                              g_HashCreateContent(       HASH, GvHash, Gv, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvHashDestroy(             HASH)                                                                 g_HashDestroy(             HASH)
#define gvHashDestroyContent(      HASH)                                                                 g_HashDestroyContent(      HASH)
#define gvHashErase(               HASH, VALUE)                                                          g_HashErase(               HASH, VALUE)
#define gvHashFind(                HASH, VALUE)                                       (Gv *)             g_HashFind(                HASH, VALUE)
#define gvHashFlush(               HASH)                                                                 g_HashFlush(               HASH)
#define gvHashForEach(             HASH, FUNC)                                                           g_HashForEach(             HASH, FUNC)
#define gvHashGetCount(            HASH)                                                                 g_HashGetCount(            HASH)
#define gvHashUpdate(              HASH, VALUE)                                                          g_HashUpdate(              HASH, VALUE)
#define gvHashKeyAdd(              HASH, KEY, VALUE)                                                     g_HashKeyAdd(              HASH, KEY, VALUE)
#define gvHashKeyCreate(                 HASHSIZE)                                    (GvHashKey *)      g_HashKeyCreate(                 GvHashKey, Gv, HASHSIZE)
#define gvHashKeyCreateContent(    HASH, HASHSIZE)                                                       g_HashKeyCreateContent(    HASH, GvHashKey, Gv, HASHSIZE)
#define gvHashKeyDestroy(          HASH)                                                                 g_HashKeyDestroy(          HASH)
#define gvHashKeyDestroyContent(   HASH)                                                                 g_HashKeyDestroyContent(   HASH)
#define gvHashKeyErase(            HASH, KEY)                                                            g_HashKeyErase(            HASH, KEY)
#define gvHashKeyFind(             HASH, KEY)                                         (Gv *)             g_HashKeyFind(             HASH, KEY)
#define gvHashKeyFlush(            HASH)                                                                 g_HashKeyFlush(            HASH)
#define gvHashKeyForEach(          HASH, FUNC)                                                           g_HashKeyForEach(          HASH, FUNC)
#define gvHashKeyGetCount(         HASH)                                                                 g_HashKeyGetCount(         HASH)
#define gvHashKeyUpdate(           HASH, KEY, VALUE)                                                     g_HashKeyUpdate(           HASH, KEY, VALUE)
#define gvListAdd(                 LIST, VALUE)                                       (GvListItem *)     g_ListAdd(                 LIST, VALUE)
#define gvListAddBegin(            LIST, VALUE)                                       (GvListItem *)     g_ListAddBegin(            LIST, VALUE)
#define gvListAddEnd(              LIST, VALUE)                                       (GvListItem *)     g_ListAddEnd(              LIST, VALUE)
#define gvListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GvList *)         g_ListCreate(                    GvList, Gv, OPTIONAL_COMPARE_FUNC)
#define gvListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                          g_ListCreateContent(       LIST, GvList, Gv, OPTIONAL_COMPARE_FUNC)
#define gvListDestroy(             LIST)                                                                 g_ListDestroy(             LIST)
#define gvListDestroyContent(      LIST)                                                                 g_ListDestroyContent(      LIST)
#define gvListErase(               LIST, VALUE)                                                          g_ListErase(               LIST, VALUE)
#define gvListEraseBegin(          LIST)                                                                 g_ListEraseBegin(          LIST)
#define gvListEraseEnd(            LIST)                                                                 g_ListEraseEnd(            LIST)
#define gvListFind(                LIST, VALUE)                                       (GvListItem *)     g_ListFind(                LIST, VALUE)
#define gvListFlush(               LIST)                                                                 g_ListFlush(               LIST)
#define gvListForEach(             LIST, FUNC)                                                           g_ListForEach(             LIST, FUNC)
#define gvListGetBegin(            LIST)                                              (GvListItem *)     g_ListGetBegin(            LIST)
#define gvListGetCount(            LIST)                                                                 g_ListGetCount(            LIST)
#define gvListGetEnd(              LIST)                                              (GvListItem *)     g_ListGetEnd(              LIST)
#define gvListItemAdd(             LIST, LITEM, VALUE)                                (GvListItem *)     g_ListItemAdd(             LIST, LITEM, VALUE)
#define gvListItemErase(           LIST, LITEM)                                                          g_ListItemErase(           LIST, LITEM)
#define gvListItemGet(                   LITEM)                                       (Gv *)             g_ListItemGet(                   LITEM)
#define gvListItemGetNext(               LITEM)                                       (GvListItem *)     g_ListItemGetNext(               LITEM)
#define gvListItemGetPrev(               LITEM)                                       (GvListItem *)     g_ListItemGetPrev(               LITEM)
#define gvListItemUpdate(          LIST, LITEM, VALUE)                                                   g_ListItemUpdate(          LIST, LITEM, VALUE)
#define gvListKeyAdd(              LIST, KEY, VALUE)                                  (GvListKeyItem *)  g_ListKeyAdd(              LIST, KEY, VALUE)
#define gvListKeyAddBegin(         LIST, KEY, VALUE)                                  (GvListKeyItem *)  g_ListKeyAddBegin(         LIST, KEY, VALUE)
#define gvListKeyAddEnd(           LIST, KEY, VALUE)                                  (GvListKeyItem *)  g_ListKeyAddEnd(           LIST, KEY, VALUE)
#define gvListKeyCreate(                 COMPARE_FUNC)                                (GvList *)         g_ListKeyCreate(                 GvListKey, Gv, COMPARE_FUNC)
#define gvListKeyCreateContent(    LIST, COMPARE_FUNC)                                                   g_ListKeyCreateContent(    LIST, GvListKey, Gv, COMPARE_FUNC)
#define gvListKeyDestroy(          LIST)                                                                 g_ListKeyDestroy(          LIST)
#define gvListKeyDestroyContent(   LIST)                                                                 g_ListKeyDestroyContent(   LIST)
#define gvListKeyErase(            LIST, KEY)                                                            g_ListKeyErase(            LIST, KEY)
#define gvListKeyEraseBegin(       LIST)                                                                 g_ListKeyEraseBegin(       LIST)
#define gvListKeyEraseEnd(         LIST)                                                                 g_ListKeyEraseEnd(         LIST)
#define gvListKeyFind(             LIST, KEY)                                         (GvListKeyItem *)  g_ListKeyFind(             LIST, KEY)
#define gvListKeyFlush(            LIST)                                                                 g_ListKeyFlush(            LIST)
#define gvListKeyForEach(          LIST, FUNC)                                                           g_ListKeyForEach(          LIST, FUNC)
#define gvListKeyGetBegin(         LIST)                                              (GvListKeyItem *)  g_ListKeyGetBegin(         LIST)
#define gvListKeyGetCount(         LIST)                                                                 g_ListKeyGetCount(         LIST)
#define gvListKeyGetEnd(           LIST)                                              (GvListKeyItem *)  g_ListKeyGetEnd(           LIST)
#define gvListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GvListKeyItem *)  g_ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)
#define gvListKeyItemErase(        LIST, LITEM)                                                          g_ListKeyItemErase(        LIST, LITEM)
#define gvListKeyItemGet(          LIST, LITEM)                                       (Gv *)             g_ListKeyItemGet(          LIST, LITEM)
#define gvListKeyItemGetKey(       LIST, LITEM)                                                          g_ListKeyItemGetKey(       LIST, LITEM)
#define gvListKeyItemGetNext(      LIST, LITEM)                                       (GvListKeyItem *)  g_ListKeyItemGetNext(      LIST, LITEM)
#define gvListKeyItemGetPrev(      LIST, LITEM)                                       (GvListKeyItem *)  g_ListKeyItemGetPrev(      LIST, LITEM)
#define gvListKeyItemUpdate(       LIST, LITEM, VALUE)                                                   g_ListKeyItemUpdate(       LIST, LITEM, VALUE)
#define gvListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                     g_ListKeyItemUpdateKey(    LIST, LITEM, KEY)
#define gvTreeAdd(                 TREE, VALUE)                                       (GvTreeItem *)     g_TreeAdd(                 TREE, VALUE)
#define gvTreeCreate(                    COMPARE_FUNC)                                (GvTree *)         g_TreeCreate(                    GvTree, Gv, COMPARE_FUNC)
#define gvTreeCreateContent(       TREE, COMPARE_FUNC)                                                   g_TreeCreateContent(       TREE, GvTree, Gv, COMPARE_FUNC)
#define gvTreeDestroy(             TREE)                                                                 g_TreeDestroy(             TREE)
#define gvTreeDestroyContent(      TREE)                                                                 g_TreeDestroyContent(      TREE)
#define gvTreeErase(               TREE, VALUE)                                                          g_TreeErase(               TREE, VALUE)
#define gvTreeEraseBegin(          TREE)                                                                 g_TreeEraseBegin(          TREE)
#define gvTreeEraseEnd(            TREE)                                                                 g_TreeEraseEnd(            TREE)
#define gvTreeFind(                TREE, VALUE)                                       (GvTreeItem *)     g_TreeFind(                TREE, VALUE)
#define gvTreeFlush(               TREE)                                                                 g_TreeFlush(               TREE)
#define gvTreeForEach(             TREE, FUNC)                                                           g_TreeForEach(             TREE, FUNC)
#define gvTreeGetBegin(            TREE)                                              (GvTreeItem *)     g_TreeGetBegin(            TREE)
#define gvTreeGetCount(            TREE)                                                                 g_TreeGetCount(            TREE)
#define gvTreeGetEnd(              TREE)                                              (GvTreeItem *)     g_TreeGetEnd(              TREE)
#define gvTreeItemDestroy(         TREE, TITEM)                                                          g_TreeItemDestroy(         TREE, TITEM)
#define gvTreeItemGet(                   TITEM)                                       (Gv *)             g_TreeItemGet(                   TITEM)
#define gvTreeItemGetNext(               TITEM)                                       (GvTreeItem *)     g_TreeItemGetNext(               TITEM)
#define gvTreeItemGetPrev(               TITEM)                                       (GvTreeItem *)     g_TreeItemGetPrev(               TITEM)
#define gvTreeItemUpdate(          TREE, TITEM, VALUE)                                                   g_TreeItemUpdate(          TREE, TITEM, VALUE)
#define gvTreeKeyAdd(              TREE, KEY, VALUE)                                  (GvTreeKeyItem *)  g_TreeKeyAdd(              TREE, KEY, VALUE)
#define gvTreeKeyCreate(                 COMPARE_FUNC)                                (GvTreeKey *)      g_TreeKeyCreate(                 GvTreeKey, Gv, COMPARE_FUNC)
#define gvTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                   g_TreeKeyCreateContent(    TREE, GvTreeKey, Gv, COMPARE_FUNC)
#define gvTreeKeyDestroy(          TREE)                                                                 g_TreeKeyDestroy(          TREE)
#define gvTreeKeyDestroyContent(   TREE)                                                                 g_TreeKeyDestroyContent(   TREE)
#define gvTreeKeyErase(            TREE, KEY)                                                            g_TreeKeyErase(            TREE, KEY)
#define gvTreeKeyEraseBegin(       TREE)                                                                 g_TreeKeyEraseBegin(       TREE)
#define gvTreeKeyEraseEnd(         TREE)                                                                 g_TreeKeyEraseEnd(         TREE)
#define gvTreeKeyFind(             TREE, KEY)                                         (GvTreeKeyItem *)  g_TreeKeyFind(             TREE, KEY)
#define gvTreeKeyFlush(            TREE)                                                                 g_TreeKeyFlush(            TREE)
#define gvTreeKeyForEach(          TREE, FUNC)                                                           g_TreeKeyForEach(          TREE, FUNC)
#define gvTreeKeyGetBegin(         TREE)                                              (GvTreeKeyItem *)  g_TreeKeyGetBegin(         TREE)
#define gvTreeKeyGetCount(         TREE)                                                                 g_TreeKeyGetCount(         TREE)
#define gvTreeKeyGetEnd(           TREE)                                              (GvTreeKeyItem *)  g_TreeKeyGetEnd(           TREE)
#define gvTreeKeyItemDestroy(      TREE, TITEM)                                                          g_TreeKeyItemDestroy(      TREE, TITEM)
#define gvTreeKeyItemGet(                TITEM)                                       (Gv *)             g_TreeKeyItemGet(                TITEM)
#define gvTreeKeyItemGetNext(            TITEM)                                       (GvTreeKeyItem *)  g_TreeKeyItemGetNext(            TITEM)
#define gvTreeKeyItemGetPrev(            TITEM)                                       (GvTreeKeyItem *)  g_TreeKeyItemGetPrev(            TITEM)
#define gvTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                   g_TreeKeyItemUpdate(       TREE, TITEM, VALUE)

#endif
