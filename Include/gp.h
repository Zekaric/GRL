/******************************************************************************
file:       gp
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
Generic pointer containers
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

#if !defined(GPH)
#define      GPH

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
Gp containers.
******************************************************************************/
typedef G_Array         GpArray;
typedef G_ArrayKey      GpArrayKey;   
typedef G_Hash          GpHash;    
typedef G_HashKey       GpHashKey;                                                                   
typedef G_List          GpList; 
typedef G_ListItem      GpListItem;   
typedef G_ListKey       GpListKey; 
typedef G_ListKeyItem   GpListKeyItem;   
typedef G_Tree          GpTree;
typedef G_TreeItem      GpTreeItem;
typedef G_TreeKey       GpTreeKey;
typedef G_TreeKeyItem   GpTreeKeyItem;

#define gpArrayAdd(                ARRAY,        VALUE)                                                  g_ArrayAdd(                ARRAY,        VALUE) 
#define gpArrayAddAt(              ARRAY, INDEX, VALUE)                                                  g_ArrayAddAt(              ARRAY, INDEX, VALUE) 
#define gpArrayAddBegin(           ARRAY,        VALUE)                                                  g_ArrayAddBegin(           ARRAY,        VALUE) 
#define gpArrayAddEnd(             ARRAY,        VALUE)                                                  g_ArrayAddEnd(             ARRAY,        VALUE) 
#define gpArrayClear(              ARRAY, COUNT, INDEX)                                                  g_ArrayClear(              ARRAY, COUNT, INDEX) 
#define gpArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gpArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayCopyFrom(           ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gpArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpArray *)        g_ArrayCreate(                    GpArray, Gp *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayCreateContent(      ARRAY, GpArray, Gp *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpArrayDestroy(            ARRAY)                                                                g_ArrayDestroy(            ARRAY) 
#define gpArrayDestroyContent(     ARRAY)                                                                g_ArrayDestroyContent(     ARRAY) 
#define gpArrayErase(              ARRAY, VALUE)                                                         g_ArrayErase(              ARRAY, VALUE) 
#define gpArrayEraseAt(            ARRAY, COUNT, INDEX)                                                  g_ArrayEraseAt(            ARRAY, COUNT, INDEX) 
#define gpArrayEraseBegin(         ARRAY)                                                                g_ArrayEraseBegin(         ARRAY) 
#define gpArrayEraseEnd(           ARRAY)                                                                g_ArrayEraseEnd(           ARRAY) 
#define gpArrayFind(               ARRAY, VALUE)                                                         g_ArrayFind(               ARRAY, VALUE) 
#define gpArrayFlush(              ARRAY)                                                                g_ArrayFlush(              ARRAY) 
#define gpArrayForEach(            ARRAY, FUNC)                                                          g_ArrayForEach(            ARRAY, FUNC) 
#define gpArrayGet(                ARRAY)                                             (Gp **)            g_ArrayGet(                ARRAY) 
#define gpArrayGetAt(              ARRAY, INDEX)                                    *((Gp **)            g_ArrayGetAt(              ARRAY, INDEX))
#define gpArrayGetBegin(           ARRAY)                                           *((Gp **)            g_ArrayGetBegin(           ARRAY))
#define gpArrayGetCount(           ARRAY)                                                                g_ArrayGetCount(           ARRAY) 
#define gpArrayGetEnd(             ARRAY)                                           *((Gp **)            g_ArrayGetEnd(             ARRAY))
#define gpArrayGetSize(            ARRAY)                                                                g_ArrayGetSize(            ARRAY) 
#define gpArraySetCount(           ARRAY, VALUE)                                                         g_ArraySetCount(           ARRAY, VALUE) 
#define gpArraySort(               ARRAY)                                                                g_ArraySort(               ARRAY) 
#define gpArraySwap(               ARRAY, INDEXA, INDEXB)                                                g_ArraySwap(               ARRAY, INDEXA, INDEXB) 
#define gpArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                  g_ArrayUpdateAt(           ARRAY, INDEX, VALUE) 
#define gpArrayKeyAdd(             ARRAY,        KEY, VALUE)                                             g_ArrayKeyAdd(             ARRAY,        KEY, VALUE) 
#define gpArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                             g_ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE) 
#define gpArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddBegin(        ARRAY,        KEY, VALUE) 
#define gpArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                             g_ArrayKeyAddEnd(          ARRAY,        KEY, VALUE) 
#define gpArrayKeyClear(           ARRAY, COUNT, INDEX)                                                  g_ArrayKeyClear(           ARRAY, COUNT, INDEX) 
#define gpArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gpArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ASRC, COUNT, INDEXSRC) 
#define gpArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpArray *)        g_ArrayKeyCreate(                 GpArray, Gp *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayKeyCreateContent(   ARRAY, GpArray, Gp *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpArrayKeyDestroy(         ARRAY)                                                                g_ArrayKeyDestroy(         ARRAY) 
#define gpArrayKeyDestroyContent(  ARRAY)                                                                g_ArrayKeyDestroyContent(  ARRAY) 
#define gpArrayKeyErase(           ARRAY, KEY)                                                           g_ArrayKeyErase(           ARRAY, KEY) 
#define gpArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                  g_ArrayKeyEraseAt(         ARRAY, COUNT, INDEX) 
#define gpArrayKeyEraseBegin(      ARRAY)                                                                g_ArrayKeyEraseBegin(      ARRAY) 
#define gpArrayKeyEraseEnd(        ARRAY)                                                                g_ArrayKeyEraseEnd(        ARRAY) 
#define gpArrayKeyFind(            ARRAY, KEY)                                                           g_ArrayKeyFind(            ARRAY, KEY) 
#define gpArrayKeyFlush(           ARRAY)                                                                g_ArrayKeyFlush(           ARRAY) 
#define gpArrayKeyForEach(         ARRAY, FUNC)                                                          g_ArrayKeyForEach(         ARRAY, FUNC) 
#define gpArrayKeyGetAt(           ARRAY, INDEX)                                    *((Gp **)            g_ArrayKeyGetAt(           ARRAY, INDEX))
#define gpArrayKeyGetAtKey(        ARRAY, INDEX)                                                         g_ArrayKeyGetAtKey(        ARRAY, INDEX) 
#define gpArrayKeyGetBegin(        ARRAY)                                           *((Gp **)            g_ArrayKeyGetBegin(        ARRAY))
#define gpArrayKeyGetBeginKey(     ARRAY)                                                                g_ArrayKeyGetBeginKey(     ARRAY) 
#define gpArrayKeyGetCount(        ARRAY)                                                                g_ArrayKeyGetCount(        ARRAY) 
#define gpArrayKeyGetEnd(          ARRAY)                                           *((Gp **)            g_ArrayKeyGetEnd(          ARRAY))
#define gpArrayKeyGetEndKey(       ARRAY)                                                                g_ArrayKeyGetEndKey(       ARRAY) 
#define gpArrayKeyGetSize(         ARRAY)                                                                g_ArrayKeyGetSize(         ARRAY) 
#define gpArrayKeySetCount(        ARRAY, VALUE)                                                         g_ArrayKeySetCount(        ARRAY, VALUE) 
#define gpArrayKeySort(            ARRAY)                                                                g_ArrayKeySort(            ARRAY) 
#define gpArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                g_ArrayKeySwap(            ARRAY, INDEXA, INDEXB) 
#define gpArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                  g_ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE) 
#define gpArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                    g_ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY) 
#define gpHashAdd(                 HASH, VALUE)                                                          g_HashAdd(                 HASH, VALUE)
#define gpHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GpHash *)         g_HashCreate(                    GpHash, Gp *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                              g_HashCreateContent(       HASH, GpHash, Gp *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpHashDestroy(             HASH)                                                                 g_HashDestroy(             HASH)
#define gpHashDestroyContent(      HASH)                                                                 g_HashDestroyContent(      HASH)
#define gpHashErase(               HASH, VALUE)                                                          g_HashErase(               HASH, VALUE)
#define gpHashFind(                HASH, VALUE)                                     *((Gp **)            g_HashFind(                HASH, VALUE))
#define gpHashFlush(               HASH)                                                                 g_HashFlush(               HASH)
#define gpHashForEach(             HASH, FUNC)                                                           g_HashForEach(             HASH, FUNC)
#define gpHashGetCount(            HASH)                                                                 g_HashGetCount(            HASH)
#define gpHashUpdate(              HASH, VALUE)                                                          g_HashUpdate(              HASH, VALUE)
#define gpHashKeyAdd(              HASH, KEY, VALUE)                                                     g_HashKeyAdd(              HASH, KEY, VALUE)
#define gpHashKeyCreate(                 HASHSIZE)                                    (GpHashKey *)      g_HashKeyCreate(                 GpHashKey, Gp *, HASHSIZE)
#define gpHashKeyCreateContent(    HASH, HASHSIZE)                                                       g_HashKeyCreateContent(    HASH, GpHashKey, Gp *, HASHSIZE)
#define gpHashKeyDestroy(          HASH)                                                                 g_HashKeyDestroy(          HASH)
#define gpHashKeyDestroyContent(   HASH)                                                                 g_HashKeyDestroyContent(   HASH)
#define gpHashKeyErase(            HASH, KEY)                                                            g_HashKeyErase(            HASH, KEY)
#define gpHashKeyFind(             HASH, KEY)                                       *((Gp **)            g_HashKeyFind(             HASH, KEY))
#define gpHashKeyFlush(            HASH)                                                                 g_HashKeyFlush(            HASH)
#define gpHashKeyForEach(          HASH, FUNC)                                                           g_HashKeyForEach(          HASH, FUNC)
#define gpHashKeyGetCount(         HASH)                                                                 g_HashKeyGetCount(         HASH)
#define gpHashKeyUpdate(           HASH, KEY, VALUE)                                                     g_HashKeyUpdate(           HASH, KEY, VALUE)
#define gpListAdd(                 LIST, VALUE)                                       (GpListItem *)     g_ListAdd(                 LIST, VALUE)
#define gpListAddBegin(            LIST, VALUE)                                       (GpListItem *)     g_ListAddBegin(            LIST, VALUE)
#define gpListAddEnd(              LIST, VALUE)                                       (GpListItem *)     g_ListAddEnd(              LIST, VALUE)
#define gpListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GpList *)         g_ListCreate(                    GpList, Gp *, OPTIONAL_COMPARE_FUNC)
#define gpListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                          g_ListCreateContent(       LIST, GpList, Gp *, OPTIONAL_COMPARE_FUNC)
#define gpListDestroy(             LIST)                                                                 g_ListDestroy(             LIST)
#define gpListDestroyContent(      LIST)                                                                 g_ListDestroyContent(      LIST)
#define gpListErase(               LIST, VALUE)                                                          g_ListErase(               LIST, VALUE)
#define gpListEraseBegin(          LIST)                                                                 g_ListEraseBegin(          LIST)
#define gpListEraseEnd(            LIST)                                                                 g_ListEraseEnd(            LIST)
#define gpListFind(                LIST, VALUE)                                       (GpListItem *)     g_ListFind(                LIST, VALUE)
#define gpListFlush(               LIST)                                                                 g_ListFlush(               LIST)
#define gpListForEach(             LIST, FUNC)                                                           g_ListForEach(             LIST, FUNC)
#define gpListGetBegin(            LIST)                                              (GpListItem *)     g_ListGetBegin(            LIST)
#define gpListGetCount(            LIST)                                                                 g_ListGetCount(            LIST)
#define gpListGetEnd(              LIST)                                              (GpListItem *)     g_ListGetEnd(              LIST)
#define gpListItemAdd(             LIST, LITEM, VALUE)                                (GpListItem *)     g_ListItemAdd(             LIST, LITEM, VALUE)
#define gpListItemErase(           LIST, LITEM)                                                          g_ListItemErase(           LIST, LITEM)
#define gpListItemGet(                   LITEM)                                     *((Gp **)            g_ListItemGet(                   LITEM))
#define gpListItemGetNext(               LITEM)                                       (GpListItem *)     g_ListItemGetNext(               LITEM)
#define gpListItemGetPrev(               LITEM)                                       (GpListItem *)     g_ListItemGetPrev(               LITEM)
#define gpListItemUpdate(          LIST, LITEM, VALUE)                                                   g_ListItemUpdate(          LIST, LITEM, VALUE)
#define gpListKeyAdd(              LIST, KEY, VALUE)                                  (GpListKeyItem *)  g_ListKeyAdd(              LIST, KEY, VALUE)
#define gpListKeyAddBegin(         LIST, KEY, VALUE)                                  (GpListKeyItem *)  g_ListKeyAddBegin(         LIST, KEY, VALUE)
#define gpListKeyAddEnd(           LIST, KEY, VALUE)                                  (GpListKeyItem *)  g_ListKeyAddEnd(           LIST, KEY, VALUE)
#define gpListKeyCreate(                 COMPARE_FUNC)                                (GpList *)         g_ListKeyCreate(                 GpListKey, Gp *, COMPARE_FUNC)
#define gpListKeyCreateContent(    LIST, COMPARE_FUNC)                                                   g_ListKeyCreateContent(    LIST, GpListKey, Gp *, COMPARE_FUNC)
#define gpListKeyDestroy(          LIST)                                                                 g_ListKeyDestroy(          LIST)
#define gpListKeyDestroyContent(   LIST)                                                                 g_ListKeyDestroyContent(   LIST)
#define gpListKeyErase(            LIST, KEY)                                                            g_ListKeyErase(            LIST, KEY)
#define gpListKeyEraseBegin(       LIST)                                                                 g_ListKeyEraseBegin(       LIST)
#define gpListKeyEraseEnd(         LIST)                                                                 g_ListKeyEraseEnd(         LIST)
#define gpListKeyFind(             LIST, KEY)                                         (GpListKeyItem *)  g_ListKeyFind(             LIST, KEY)
#define gpListKeyFlush(            LIST)                                                                 g_ListKeyFlush(            LIST)
#define gpListKeyForEach(          LIST, FUNC)                                                           g_ListKeyForEach(          LIST, FUNC)
#define gpListKeyGetBegin(         LIST)                                              (GpListKeyItem *)  g_ListKeyGetBegin(         LIST)
#define gpListKeyGetCount(         LIST)                                                                 g_ListKeyGetCount(         LIST)
#define gpListKeyGetEnd(           LIST)                                              (GpListKeyItem *)  g_ListKeyGetEnd(           LIST)
#define gpListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GpListKeyItem *)  g_ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)
#define gpListKeyItemErase(        LIST, LITEM)                                                          g_ListKeyItemErase(        LIST, LITEM)
#define gpListKeyItemGet(          LIST, LITEM)                                     *((Gp **)            g_ListKeyItemGet(          LIST, LITEM))
#define gpListKeyItemGetKey(       LIST, LITEM)                                                          g_ListKeyItemGetKey(       LIST, LITEM)
#define gpListKeyItemGetNext(      LIST, LITEM)                                       (GpListKeyItem *)  g_ListKeyItemGetNext(      LIST, LITEM)
#define gpListKeyItemGetPrev(      LIST, LITEM)                                       (GpListKeyItem *)  g_ListKeyItemGetPrev(      LIST, LITEM)
#define gpListKeyItemUpdate(       LIST, LITEM, VALUE)                                                   g_ListKeyItemUpdate(       LIST, LITEM, VALUE)
#define gpListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                     g_ListKeyItemUpdateKey(    LIST, LITEM, KEY)
#define gpTreeAdd(                 TREE, VALUE)                                       (GpTreeItem *)     g_TreeAdd(                 TREE, VALUE)
#define gpTreeCreate(                    COMPARE_FUNC)                                (GpTree *)         g_TreeCreate(                    GpTree, Gp *, COMPARE_FUNC)
#define gpTreeCreateContent(       TREE, COMPARE_FUNC)                                                   g_TreeCreateContent(       TREE, GpTree, Gp *, COMPARE_FUNC)
#define gpTreeDestroy(             TREE)                                                                 g_TreeDestroy(             TREE)
#define gpTreeDestroyContent(      TREE)                                                                 g_TreeDestroyContent(      TREE)
#define gpTreeErase(               TREE, VALUE)                                                          g_TreeErase(               TREE, VALUE)
#define gpTreeEraseBegin(          TREE)                                                                 g_TreeEraseBegin(          TREE)
#define gpTreeEraseEnd(            TREE)                                                                 g_TreeEraseEnd(            TREE)
#define gpTreeFind(                TREE, VALUE)                                       (GpTreeItem *)     g_TreeFind(                TREE, VALUE)
#define gpTreeFlush(               TREE)                                                                 g_TreeFlush(               TREE)
#define gpTreeForEach(             TREE, FUNC)                                                           g_TreeForEach(             TREE, FUNC)
#define gpTreeGetBegin(            TREE)                                              (GpTreeItem *)     g_TreeGetBegin(            TREE)
#define gpTreeGetCount(            TREE)                                                                 g_TreeGetCount(            TREE)
#define gpTreeGetEnd(              TREE)                                              (GpTreeItem *)     g_TreeGetEnd(              TREE)
#define gpTreeItemDestroy(         TREE, TITEM)                                                          g_TreeItemDestroy(         TREE, TITEM)
#define gpTreeItemGet(                   TITEM)                                     *((Gp **)            g_TreeItemGet(                   TITEM))
#define gpTreeItemGetNext(               TITEM)                                       (GpTreeItem *)     g_TreeItemGetNext(               TITEM)
#define gpTreeItemGetPrev(               TITEM)                                       (GpTreeItem *)     g_TreeItemGetPrev(               TITEM)
#define gpTreeItemUpdate(          TREE, TITEM, VALUE)                                                   g_TreeItemUpdate(          TREE, TITEM, VALUE)
#define gpTreeKeyAdd(              TREE, KEY, VALUE)                                  (GpTreeKeyItem *)  g_TreeKeyAdd(              TREE, KEY, VALUE)
#define gpTreeKeyCreate(                 COMPARE_FUNC)                                (GpTreeKey *)      g_TreeKeyCreate(                 GpTreeKey, Gp *, COMPARE_FUNC)
#define gpTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                   g_TreeKeyCreateContent(    TREE, GpTreeKey, Gp *, COMPARE_FUNC)
#define gpTreeKeyDestroy(          TREE)                                                                 g_TreeKeyDestroy(          TREE)
#define gpTreeKeyDestroyContent(   TREE)                                                                 g_TreeKeyDestroyContent(   TREE)
#define gpTreeKeyErase(            TREE, KEY)                                                            g_TreeKeyErase(            TREE, KEY)
#define gpTreeKeyEraseBegin(       TREE)                                                                 g_TreeKeyEraseBegin(       TREE)
#define gpTreeKeyEraseEnd(         TREE)                                                                 g_TreeKeyEraseEnd(         TREE)
#define gpTreeKeyFind(             TREE, KEY)                                         (GpTreeKeyItem *)  g_TreeKeyFind(             TREE, KEY)
#define gpTreeKeyFlush(            TREE)                                                                 g_TreeKeyFlush(            TREE)
#define gpTreeKeyForEach(          TREE, FUNC)                                                           g_TreeKeyForEach(          TREE, FUNC)
#define gpTreeKeyGetBegin(         TREE)                                              (GpTreeKeyItem *)  g_TreeKeyGetBegin(         TREE)
#define gpTreeKeyGetCount(         TREE)                                                                 g_TreeKeyGetCount(         TREE)
#define gpTreeKeyGetEnd(           TREE)                                              (GpTreeKeyItem *)  g_TreeKeyGetEnd(           TREE)
#define gpTreeKeyItemDestroy(      TREE, TITEM)                                                          g_TreeKeyItemDestroy(      TREE, TITEM)
#define gpTreeKeyItemGet(                TITEM)                                     *((Gp **)            g_TreeKeyItemGet(                TITEM))
#define gpTreeKeyItemGetNext(            TITEM)                                       (GpTreeKeyItem *)  g_TreeKeyItemGetNext(            TITEM)
#define gpTreeKeyItemGetPrev(            TITEM)                                       (GpTreeKeyItem *)  g_TreeKeyItemGetPrev(            TITEM)
#define gpTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                   g_TreeKeyItemUpdate(       TREE, TITEM, VALUE)

#endif
