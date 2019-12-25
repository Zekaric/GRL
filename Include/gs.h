/******************************************************************************
file:         Gs
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrrays.
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

#if !defined(GSH)
#define      GSH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
type:
******************************************************************************/
typedef struct G_Array Gs;

/******************************************************************************
function:
******************************************************************************/
#define gsAdd(                ARRAY,        VALUE)                                                  g_ArrayAdd(                ARRAY,        VALUE) 
#define gsAddAt(              ARRAY, INDEX, VALUE)                                                  g_ArrayAddAt(              ARRAY, INDEX, VALUE) 
#define gsAddBegin(           ARRAY,        VALUE)                                                  g_ArrayAddBegin(           ARRAY,        VALUE) 
#define gsAddEnd(             ARRAY,        VALUE)                                                  g_ArrayAddEnd(             ARRAY,        VALUE) 
#define gsClear(              ARRAY, COUNT, INDEX)                                                  g_ArrayClear(              ARRAY, COUNT, INDEX) 
#define gsCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gsCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC) 
#define gsCreate(             )                                                  (Gs *)             g_ArrayCreate(                    Gs, Gc2, NULL, gbTRUE, gbTRUE)
#define gsCreateContent(      ARRAY)                                                                g_ArrayCreateContent(      ARRAY, Gs, Gc2, NULL, gbTRUE, gbTRUE)
#define gsDestroy(            ARRAY)                                                                g_ArrayDestroy(            ARRAY) 
#define gsDestroyContent(     ARRAY)                                                                g_ArrayDestroyContent(     ARRAY) 
#define gsErase(              ARRAY, VALUE)                                                         g_ArrayErase(              ARRAY, VALUE) 
#define gsEraseAt(            ARRAY, COUNT, INDEX)                                                  g_ArrayEraseAt(            ARRAY, COUNT, INDEX) 
#define gsEraseBegin(         ARRAY)                                                                g_ArrayEraseBegin(         ARRAY) 
#define gsEraseEnd(           ARRAY)                                                                g_ArrayEraseEnd(           ARRAY) 
#define gsFind(               ARRAY, VALUE)                                                         g_ArrayFind(               ARRAY, VALUE) 
#define gsFlush(              ARRAY)                                                                g_ArrayFlush(              ARRAY) 
#define gsForEach(            ARRAY, FUNC)                                                          g_ArrayForEach(            ARRAY, FUNC) 
#define gsGet(                ARRAY)                                             (Gc2 *)            g_ArrayGet(                ARRAY) 
#define gsGetAt(              ARRAY, INDEX)                                      (Gc2 *)            g_ArrayGetAt(              ARRAY, INDEX) 
#define gsGetBegin(           ARRAY)                                             (Gc2 *)            g_ArrayGetBegin(           ARRAY) 
#define gsGetCount(           ARRAY)                                                                g_ArrayGetCount(           ARRAY) 
#define gsGetEnd(             ARRAY)                                             (Gc2 *)            g_ArrayGetEnd(             ARRAY) 
#define gsGetSize(            ARRAY)                                                                g_ArrayGetSize(            ARRAY) 
#define gsSetCount(           ARRAY, VALUE)                                                         g_ArraySetCount(           ARRAY, VALUE) 
#define gsSort(               ARRAY)                                                                g_ArraySort(               ARRAY) 
#define gsSwap(               ARRAY, INDEXA, INDEXB)                                                g_ArraySwap(               ARRAY, INDEXA, INDEXB) 
#define gsUpdateAt(           ARRAY, INDEX, VALUE)                                                  g_ArrayUpdateAt(           ARRAY, INDEX, VALUE) 

grlAPI void gsDestroyFunc(Gs * const s);

/******************************************************************************
prototype:
******************************************************************************/
/******************************************************************************
Gs containers.
******************************************************************************/
typedef G_Array         GsArray;
typedef G_ArrayKey      GsArrayKey;   
typedef G_Hash          GsHash;    
typedef G_HashKey       GsHashKey;                                                                   
typedef G_List          GsList; 
typedef G_ListItem      GsListItem;   
typedef G_ListKey       GsListKey; 
typedef G_ListKeyItem   GsListKeyItem;   
typedef G_Tree          GsTree;
typedef G_TreeItem      GsTreeItem;
typedef G_TreeKey       GsTreeKey;
typedef G_TreeKeyItem   GsTreeKeyItem;

#define gsArrayAdd(                ARRAY,        VALUE)                                                  g_ArrayAdd(                ARRAY,        VALUE) 
#define gsArrayAddAt(              ARRAY, INDEX, VALUE)                                                  g_ArrayAddAt(              ARRAY, INDEX, VALUE) 
#define gsArrayAddBegin(           ARRAY,        VALUE)                                                  g_ArrayAddBegin(           ARRAY,        VALUE) 
#define gsArrayAddEnd(             ARRAY,        VALUE)                                                  g_ArrayAddEnd(             ARRAY,        VALUE) 
#define gsArrayClear(              ARRAY, COUNT, INDEX)                                                  g_ArrayClear(              ARRAY, COUNT, INDEX) 
#define gsArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gsArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayCopyFrom(           ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gsArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GsArray *)        g_ArrayCreate(                    GsArray, Gs *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gsArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayCreateContent(      ARRAY, GsArray, Gs *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gsArrayDestroy(            ARRAY)                                                                g_ArrayDestroy(            ARRAY) 
#define gsArrayDestroyContent(     ARRAY)                                                                g_ArrayDestroyContent(     ARRAY) 
#define gsArrayErase(              ARRAY, VALUE)                                                         g_ArrayErase(              ARRAY, VALUE) 
#define gsArrayEraseAt(            ARRAY, COUNT, INDEX)                                                  g_ArrayEraseAt(            ARRAY, COUNT, INDEX) 
#define gsArrayEraseBegin(         ARRAY)                                                                g_ArrayEraseBegin(         ARRAY) 
#define gsArrayEraseEnd(           ARRAY)                                                                g_ArrayEraseEnd(           ARRAY) 
#define gsArrayFind(               ARRAY, VALUE)                                                         g_ArrayFind(               ARRAY, VALUE) 
#define gsArrayFlush(              ARRAY)                                                                g_ArrayFlush(              ARRAY) 
#define gsArrayForEach(            ARRAY, FUNC)                                                          g_ArrayForEach(            ARRAY, FUNC) 
#define gsArrayGet(                ARRAY)                                             (Gs **)            g_ArrayGet(                ARRAY) 
#define gsArrayGetAt(              ARRAY, INDEX)                                    *((Gs **)            g_ArrayGetAt(              ARRAY, INDEX))
#define gsArrayGetBegin(           ARRAY)                                           *((Gs **)            g_ArrayGetBegin(           ARRAY))
#define gsArrayGetCount(           ARRAY)                                                                g_ArrayGetCount(           ARRAY) 
#define gsArrayGetEnd(             ARRAY)                                           *((Gs **)            g_ArrayGetEnd(             ARRAY))
#define gsArrayGetSize(            ARRAY)                                                                g_ArrayGetSize(            ARRAY) 
#define gsArraySetCount(           ARRAY, VALUE)                                                         g_ArraySetCount(           ARRAY, VALUE) 
#define gsArraySort(               ARRAY)                                                                g_ArraySort(               ARRAY) 
#define gsArraySwap(               ARRAY, INDEXA, INDEXB)                                                g_ArraySwap(               ARRAY, INDEXA, INDEXB) 
#define gsArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                  g_ArrayUpdateAt(           ARRAY, INDEX, VALUE) 
#define gsArrayKeyAdd(             ARRAY,        KEY, VALUE)                                             g_ArrayKeyAdd(             ARRAY,        KEY, VALUE) 
#define gsArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                             g_ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE) 
#define gsArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddBegin(        ARRAY,        KEY, VALUE) 
#define gsArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddEnd(          ARRAY,        KEY, VALUE) 
#define gsArrayKeyClear(           ARRAY, COUNT, INDEX)                                                  g_ArrayKeyClear(           ARRAY, COUNT, INDEX) 
#define gsArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gsArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gsArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GsArray *)        g_ArrayKeyCreate(                 GsArray, Gs *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gsArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayKeyCreateContent(   ARRAY, GsArray, Gs *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gsArrayKeyDestroy(         ARRAY)                                                                g_ArrayKeyDestroy(         ARRAY) 
#define gsArrayKeyDestroyContent(  ARRAY)                                                                g_ArrayKeyDestroyContent(  ARRAY) 
#define gsArrayKeyErase(           ARRAY, KEY)                                                           g_ArrayKeyErase(           ARRAY, KEY) 
#define gsArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                  g_ArrayKeyEraseAt(         ARRAY, COUNT, INDEX) 
#define gsArrayKeyEraseBegin(      ARRAY)                                                                g_ArrayKeyEraseBegin(      ARRAY) 
#define gsArrayKeyEraseEnd(        ARRAY)                                                                g_ArrayKeyEraseEnd(        ARRAY) 
#define gsArrayKeyFind(            ARRAY, KEY)                                                           g_ArrayKeyFind(            ARRAY, KEY) 
#define gsArrayKeyFlush(           ARRAY)                                                                g_ArrayKeyFlush(           ARRAY) 
#define gsArrayKeyForEach(         ARRAY, FUNC)                                                          g_ArrayKeyForEach(         ARRAY, FUNC) 
#define gsArrayKeyGetAt(           ARRAY, INDEX)                                    *((Gs **)            g_ArrayKeyGetAt(           ARRAY, INDEX))
#define gsArrayKeyGetAtKey(        ARRAY, INDEX)                                                         g_ArrayKeyGetAtKey(        ARRAY, INDEX) 
#define gsArrayKeyGetBegin(        ARRAY)                                           *((Gs **)            g_ArrayKeyGetBegin(        ARRAY))
#define gsArrayKeyGetBeginKey(     ARRAY)                                                                g_ArrayKeyGetBeginKey(     ARRAY) 
#define gsArrayKeyGetCount(        ARRAY)                                                                g_ArrayKeyGetCount(        ARRAY) 
#define gsArrayKeyGetEnd(          ARRAY)                                           *((Gs **)            g_ArrayKeyGetEnd(          ARRAY))
#define gsArrayKeyGetEndKey(       ARRAY)                                                                g_ArrayKeyGetEndKey(       ARRAY) 
#define gsArrayKeyGetSize(         ARRAY)                                                                g_ArrayKeyGetSize(         ARRAY) 
#define gsArrayKeySetCount(        ARRAY, VALUE)                                                         g_ArrayKeySetCount(        ARRAY, VALUE) 
#define gsArrayKeySort(            ARRAY)                                                                g_ArrayKeySort(            ARRAY) 
#define gsArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                g_ArrayKeySwap(            ARRAY, INDEXA, INDEXB) 
#define gsArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                  g_ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE) 
#define gsArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                    g_ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY) 
#define gsHashAdd(                 HASH, VALUE)                                                          g_HashAdd(                 HASH, VALUE)
#define gsHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GsHash *)         g_HashCreate(                    GsHash, Gs *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gsHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                              g_HashCreateContent(       HASH, GsHash, Gs *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gsHashDestroy(             HASH)                                                                 g_HashDestroy(             HASH)
#define gsHashDestroyContent(      HASH)                                                                 g_HashDestroyContent(      HASH)
#define gsHashErase(               HASH, VALUE)                                                          g_HashErase(               HASH, VALUE)
#define gsHashFind(                HASH, VALUE)                                     *((Gs **)            g_HashFind(                HASH, VALUE))
#define gsHashFlush(               HASH)                                                                 g_HashFlush(               HASH)
#define gsHashForEach(             HASH, FUNC)                                                           g_HashForEach(             HASH, FUNC)
#define gsHashGetCount(            HASH)                                                                 g_HashGetCount(            HASH)
#define gsHashUpdate(              HASH, VALUE)                                                          g_HashUpdate(              HASH, VALUE)
#define gsHashKeyAdd(              HASH, KEY, VALUE)                                                     g_HashKeyAdd(              HASH, KEY, VALUE)
#define gsHashKeyCreate(                 HASHSIZE)                                    (GsHashKey *)      g_HashKeyCreate(                 GsHashKey, Gs *, HASHSIZE)
#define gsHashKeyCreateContent(    HASH, HASHSIZE)                                                       g_HashKeyCreateContent(    HASH, GsHashKey, Gs *, HASHSIZE)
#define gsHashKeyDestroy(          HASH)                                                                 g_HashKeyDestroy(          HASH)
#define gsHashKeyDestroyContent(   HASH)                                                                 g_HashKeyDestroyContent(   HASH)
#define gsHashKeyErase(            HASH, KEY)                                                            g_HashKeyErase(            HASH, KEY)
#define gsHashKeyFind(             HASH, KEY)                                       *((Gs **)            g_HashKeyFind(             HASH, KEY))
#define gsHashKeyFlush(            HASH)                                                                 g_HashKeyFlush(            HASH)
#define gsHashKeyForEach(          HASH, FUNC)                                                           g_HashKeyForEach(          HASH, FUNC)
#define gsHashKeyGetCount(         HASH)                                                                 g_HashKeyGetCount(         HASH)
#define gsHashKeyUpdate(           HASH, KEY, VALUE)                                                     g_HashKeyUpdate(           HASH, KEY, VALUE)
#define gsListAdd(                 LIST, VALUE)                                       (GsListItem *)     g_ListAdd(                 LIST, VALUE)
#define gsListAddBegin(            LIST, VALUE)                                       (GsListItem *)     g_ListAddBegin(            LIST, VALUE)
#define gsListAddEnd(              LIST, VALUE)                                       (GsListItem *)     g_ListAddEnd(              LIST, VALUE)
#define gsListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GsList *)         g_ListCreate(                    GsList, Gs *, OPTIONAL_COMPARE_FUNC)
#define gsListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                          g_ListCreateContent(       LIST, GsList, Gs *, OPTIONAL_COMPARE_FUNC)
#define gsListDestroy(             LIST)                                                                 g_ListDestroy(             LIST)
#define gsListDestroyContent(      LIST)                                                                 g_ListDestroyContent(      LIST)
#define gsListErase(               LIST, VALUE)                                                          g_ListErase(               LIST, VALUE)
#define gsListEraseBegin(          LIST)                                                                 g_ListEraseBegin(          LIST)
#define gsListEraseEnd(            LIST)                                                                 g_ListEraseEnd(            LIST)
#define gsListFind(                LIST, VALUE)                                       (GsListItem *)     g_ListFind(                LIST, VALUE)
#define gsListFlush(               LIST)                                                                 g_ListFlush(               LIST)
#define gsListForEach(             LIST, FUNC)                                                           g_ListForEach(             LIST, FUNC)
#define gsListGetBegin(            LIST)                                              (GsListItem *)     g_ListGetBegin(            LIST)
#define gsListGetCount(            LIST)                                                                 g_ListGetCount(            LIST)
#define gsListGetEnd(              LIST)                                              (GsListItem *)     g_ListGetEnd(              LIST)
#define gsListItemAdd(             LIST, LITEM, VALUE)                                (GsListItem *)     g_ListItemAdd(             LIST, LITEM, VALUE)
#define gsListItemErase(           LIST, LITEM)                                                          g_ListItemErase(           LIST, LITEM)
#define gsListItemGet(                   LITEM)                                     *((Gs **)            g_ListItemGet(                   LITEM))
#define gsListItemGetNext(               LITEM)                                       (GsListItem *)     g_ListItemGetNext(               LITEM)
#define gsListItemGetPrev(               LITEM)                                       (GsListItem *)     g_ListItemGetPrev(               LITEM)
#define gsListItemUpdate(          LIST, LITEM, VALUE)                                                   g_ListItemUpdate(          LIST, LITEM, VALUE)
#define gsListKeyAdd(              LIST, KEY, VALUE)                                  (GsListKeyItem *)  g_ListKeyAdd(              LIST, KEY, VALUE)
#define gsListKeyAddBegin(         LIST, KEY, VALUE)                                  (GsListKeyItem *)  g_ListKeyAddBegin(         LIST, KEY, VALUE)
#define gsListKeyAddEnd(           LIST, KEY, VALUE)                                  (GsListKeyItem *)  g_ListKeyAddEnd(           LIST, KEY, VALUE)
#define gsListKeyCreate(                 COMPARE_FUNC)                                (GsList *)         g_ListKeyCreate(                 GsListKey, Gs *, COMPARE_FUNC)
#define gsListKeyCreateContent(    LIST, COMPARE_FUNC)                                                   g_ListKeyCreateContent(    LIST, GsListKey, Gs *, COMPARE_FUNC)
#define gsListKeyDestroy(          LIST)                                                                 g_ListKeyDestroy(          LIST)
#define gsListKeyDestroyContent(   LIST)                                                                 g_ListKeyDestroyContent(   LIST)
#define gsListKeyErase(            LIST, KEY)                                                            g_ListKeyErase(            LIST, KEY)
#define gsListKeyEraseBegin(       LIST)                                                                 g_ListKeyEraseBegin(       LIST)
#define gsListKeyEraseEnd(         LIST)                                                                 g_ListKeyEraseEnd(         LIST)
#define gsListKeyFind(             LIST, KEY)                                         (GsListKeyItem *)  g_ListKeyFind(             LIST, KEY)
#define gsListKeyFlush(            LIST)                                                                 g_ListKeyFlush(            LIST)
#define gsListKeyForEach(          LIST, FUNC)                                                           g_ListKeyForEach(          LIST, FUNC)
#define gsListKeyGetBegin(         LIST)                                              (GsListKeyItem *)  g_ListKeyGetBegin(         LIST)
#define gsListKeyGetCount(         LIST)                                                                 g_ListKeyGetCount(         LIST)
#define gsListKeyGetEnd(           LIST)                                              (GsListKeyItem *)  g_ListKeyGetEnd(           LIST)
#define gsListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GsListKeyItem *)  g_ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)
#define gsListKeyItemErase(        LIST, LITEM)                                                          g_ListKeyItemErase(        LIST, LITEM)
#define gsListKeyItemGet(          LIST, LITEM)                                     *((Gs **)            g_ListKeyItemGet(          LIST, LITEM))
#define gsListKeyItemGetKey(       LIST, LITEM)                                                          g_ListKeyItemGetKey(       LIST, LITEM)
#define gsListKeyItemGetNext(      LIST, LITEM)                                       (GsListKeyItem *)  g_ListKeyItemGetNext(      LIST, LITEM)
#define gsListKeyItemGetPrev(      LIST, LITEM)                                       (GsListKeyItem *)  g_ListKeyItemGetPrev(      LIST, LITEM)
#define gsListKeyItemUpdate(       LIST, LITEM, VALUE)                                                   g_ListKeyItemUpdate(       LIST, LITEM, VALUE)
#define gsListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                     g_ListKeyItemUpdateKey(    LIST, LITEM, KEY)
#define gsTreeAdd(                 TREE, VALUE)                                       (GsTreeItem *)     g_TreeAdd(                 TREE, VALUE)
#define gsTreeCreate(                    COMPARE_FUNC)                                (GsTree *)         g_TreeCreate(                    GsTree, Gs *, COMPARE_FUNC)
#define gsTreeCreateContent(       TREE, COMPARE_FUNC)                                                   g_TreeCreateContent(       TREE, GsTree, Gs *, COMPARE_FUNC)
#define gsTreeDestroy(             TREE)                                                                 g_TreeDestroy(             TREE)
#define gsTreeDestroyContent(      TREE)                                                                 g_TreeDestroyContent(      TREE)
#define gsTreeErase(               TREE, VALUE)                                                          g_TreeErase(               TREE, VALUE)
#define gsTreeEraseBegin(          TREE)                                                                 g_TreeEraseBegin(          TREE)
#define gsTreeEraseEnd(            TREE)                                                                 g_TreeEraseEnd(            TREE)
#define gsTreeFind(                TREE, VALUE)                                       (GsTreeItem *)     g_TreeFind(                TREE, VALUE)
#define gsTreeFlush(               TREE)                                                                 g_TreeFlush(               TREE)
#define gsTreeForEach(             TREE, FUNC)                                                           g_TreeForEach(             TREE, FUNC)
#define gsTreeGetBegin(            TREE)                                              (GsTreeItem *)     g_TreeGetBegin(            TREE)
#define gsTreeGetCount(            TREE)                                                                 g_TreeGetCount(            TREE)
#define gsTreeGetEnd(              TREE)                                              (GsTreeItem *)     g_TreeGetEnd(              TREE)
#define gsTreeItemDestroy(         TREE, TITEM)                                                          g_TreeItemDestroy(         TREE, TITEM)
#define gsTreeItemGet(                   TITEM)                                     *((Gs **)            g_TreeItemGet(                   TITEM))
#define gsTreeItemGetNext(               TITEM)                                       (GsTreeItem *)     g_TreeItemGetNext(               TITEM)
#define gsTreeItemGetPrev(               TITEM)                                       (GsTreeItem *)     g_TreeItemGetPrev(               TITEM)
#define gsTreeItemUpdate(          TREE, TITEM, VALUE)                                                   g_TreeItemUpdate(          TREE, TITEM, VALUE)
#define gsTreeKeyAdd(              TREE, KEY, VALUE)                                  (GsTreeKeyItem *)  g_TreeKeyAdd(              TREE, KEY, VALUE)
#define gsTreeKeyCreate(                 COMPARE_FUNC)                                (GsTreeKey *)      g_TreeKeyCreate(                 GsTreeKey, Gs *, COMPARE_FUNC)
#define gsTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                   g_TreeKeyCreateContent(    TREE, GsTreeKey, Gs *, COMPARE_FUNC)
#define gsTreeKeyDestroy(          TREE)                                                                 g_TreeKeyDestroy(          TREE)
#define gsTreeKeyDestroyContent(   TREE)                                                                 g_TreeKeyDestroyContent(   TREE)
#define gsTreeKeyErase(            TREE, KEY)                                                            g_TreeKeyErase(            TREE, KEY)
#define gsTreeKeyEraseBegin(       TREE)                                                                 g_TreeKeyEraseBegin(       TREE)
#define gsTreeKeyEraseEnd(         TREE)                                                                 g_TreeKeyEraseEnd(         TREE)
#define gsTreeKeyFind(             TREE, KEY)                                         (GsTreeKeyItem *)  g_TreeKeyFind(             TREE, KEY)
#define gsTreeKeyFlush(            TREE)                                                                 g_TreeKeyFlush(            TREE)
#define gsTreeKeyForEach(          TREE, FUNC)                                                           g_TreeKeyForEach(          TREE, FUNC)
#define gsTreeKeyGetBegin(         TREE)                                              (GsTreeKeyItem *)  g_TreeKeyGetBegin(         TREE)
#define gsTreeKeyGetCount(         TREE)                                                                 g_TreeKeyGetCount(         TREE)
#define gsTreeKeyGetEnd(           TREE)                                              (GsTreeKeyItem *)  g_TreeKeyGetEnd(           TREE)
#define gsTreeKeyItemDestroy(      TREE, TITEM)                                                          g_TreeKeyItemDestroy(      TREE, TITEM)
#define gsTreeKeyItemGet(                TITEM)                                     *((Gs **)            g_TreeKeyItemGet(                TITEM))
#define gsTreeKeyItemGetNext(            TITEM)                                       (GsTreeKeyItem *)  g_TreeKeyItemGetNext(            TITEM)
#define gsTreeKeyItemGetPrev(            TITEM)                                       (GsTreeKeyItem *)  g_TreeKeyItemGetPrev(            TITEM)
#define gsTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                   g_TreeKeyItemUpdate(       TREE, TITEM, VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
