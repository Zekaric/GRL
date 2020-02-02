/******************************************************************************
file:       Gi
author:     Robbert de Groot
copyright:  2020, Robbert de Groot
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

#if !defined(GIH)
#define      GIH

/******************************************************************************
Gi containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi                  *p;
} GiArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi                   value;
} GiArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GiArrayKeyCell      *p;
} GiArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GiListItem GiListItem;
struct GiListItem
{
   GiListItem          *next,
                           *prev;
   Gi                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GiListItem          *head,
                           *tail;
} GiList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GiListKeyItem GiListKeyItem;
struct GiListKeyItem
{
   GiListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gi                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GiListKeyItem       *head,
                           *tail;
} GiListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GiList            **binArray;
   GhashSize               binCount;
} GiHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GiListKey         **binArray;
   GhashSize               binCount;
} GiHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GiTree     GiTree;
typedef struct GiTreeItem GiTreeItem;
struct GiTreeItem
{
   GiTree              *owner;
   GiTreeItem          *parent;
   GiTreeItem          *childLeft;
   GiTreeItem          *childRight;
   GheapN                   heapValue;
   Gi                   value;
};

struct GiTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GiTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GiTreeKey     GiTreeKey;
typedef struct GiTreeKeyItem GiTreeKeyItem;
struct GiTreeKeyItem
{
   GiTreeKey           *owner;
   GiTreeKeyItem       *parent;
   GiTreeKeyItem       *childLeft;
   GiTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi                   value;
};

struct GiTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GiTreeKeyItem       *root;
};

#define giArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define giArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define giArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define giArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define giArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GiArray *)         g_ArrayCreate(                                GiArray, Gi, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define giArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, GiArray, Gi, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define giArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define giArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define giArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define giArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define giArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define giArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define giArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define giArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define giArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define giArrayGet(                ARRAY)                                             (Gi *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define giArrayGetAt(              ARRAY, INDEX)                                      (Gi *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define giArrayGetBegin(           ARRAY)                                             (Gi *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define giArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define giArrayGetEnd(             ARRAY)                                             (Gi *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define giArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define giArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define giArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define giArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define giArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define giArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define giArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define giArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define giArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define giArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define giArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define giArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define giArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GiArray *)         g_ArrayKeyCreate(                 GiArray, Gi, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define giArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GiArray, Gi, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define giArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define giArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define giArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define giArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define giArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define giArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define giArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define giArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define giArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define giArrayKeyGetAt(           ARRAY, INDEX)                                      (Gi *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define giArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define giArrayKeyGetBegin(        ARRAY)                                             (Gi *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetEnd(          ARRAY)                                             (Gi *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define giArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define giArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define giArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define giArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define giArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define giListAdd(                 LIST, VALUE)                                       (GiListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define giListAddBegin(            LIST, VALUE)                                       (GiListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define giListAddEnd(              LIST, VALUE)                                       (GiListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define giListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GiList *)          g_ListCreate(                               GiList, Gi, OPTIONAL_COMPARE_FUNC)
#define giListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, GiList, Gi, OPTIONAL_COMPARE_FUNC)
#define giListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define giListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define giListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define giListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define giListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define giListFind(                LIST, VALUE)                                       (GiListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define giListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define giListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define giListGetBegin(            LIST)                                              (GiListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define giListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define giListGetEnd(              LIST)                                              (GiListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define giListItemAdd(             LIST, LITEM, VALUE)                                (GiListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define giListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define giListItemGet(                   LITEM)                                       (Gi *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define giListItemGetNext(               LITEM)                                       (GiListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define giListItemGetPrev(               LITEM)                                       (GiListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define giListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define giListKeyAdd(              LIST, KEY, VALUE)                                  (GiListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyAddBegin(         LIST, KEY, VALUE)                                  (GiListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyAddEnd(           LIST, KEY, VALUE)                                  (GiListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyCreate(                 COMPARE_FUNC)                                (GiList *)          g_ListKeyCreate(                               GiListKey, Gi, COMPARE_FUNC)
#define giListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, GiListKey, Gi, COMPARE_FUNC)
#define giListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define giListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define giListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define giListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define giListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define giListKeyFind(             LIST, KEY)                                         (GiListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define giListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define giListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define giListKeyGetBegin(         LIST)                                              (GiListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define giListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define giListKeyGetEnd(           LIST)                                              (GiListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define giListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GiListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define giListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define giListKeyItemGet(                LITEM)                                       (Gi *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define giListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define giListKeyItemGetNext(            LITEM)                                       (GiListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define giListKeyItemGetPrev(            LITEM)                                       (GiListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define giListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define giListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define giHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define giHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GiHash *)          g_HashCreate(                               GiHash, Gi, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define giHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, GiHash, Gi, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define giHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define giHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define giHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define giHashFind(                HASH, VALUE)                                       (Gi *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define giHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define giHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define giHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define giHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define giHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define giHashKeyCreate(                 HASHSIZE)                                    (GiHashKey *)       g_HashKeyCreate(                               GiHashKey, Gi, HASHSIZE)
#define giHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, GiHashKey, Gi, HASHSIZE)
#define giHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define giHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define giHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define giHashKeyFind(             HASH, KEY)                                         (Gi *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define giHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define giHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define giHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define giHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define giTreeAdd(                 TREE, VALUE)                                       (GiTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeCreate(                    COMPARE_FUNC)                                (GiTree *)          g_TreeCreate(                    GiTree, Gi, COMPARE_FUNC)
#define giTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, GiTree, Gi, COMPARE_FUNC)
#define giTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define giTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define giTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define giTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define giTreeFind(                TREE, VALUE)                                       (GiTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define giTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define giTreeGetBegin(            TREE)                                              (GiTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define giTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define giTreeGetEnd(              TREE)                                              (GiTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define giTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define giTreeItemGet(                   TITEM)                                       (Gi *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define giTreeItemGetNext(               TITEM)                                       (GiTreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define giTreeItemGetPrev(               TITEM)                                       (GiTreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define giTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define giTreeKeyAdd(              TREE, KEY, VALUE)                                  (GiTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define giTreeKeyCreate(                 COMPARE_FUNC)                                (GiTreeKey *)       g_TreeKeyCreate(                 GiTreeKey, Gi, COMPARE_FUNC)
#define giTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GiTreeKey, Gi, COMPARE_FUNC)
#define giTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define giTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define giTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define giTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define giTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define giTreeKeyFind(             TREE, KEY)                                         (GiTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define giTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define giTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define giTreeKeyGetBegin(         TREE)                                              (GiTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define giTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define giTreeKeyGetEnd(           TREE)                                              (GiTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define giTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemGet(                TITEM)                                       (Gi *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemGetNext(            TITEM)                                       (GiTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemGetPrev(            TITEM)                                       (GiTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gi1 containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi1                  *p;
} Gi1Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi1                   value;
} Gi1ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gi1ArrayKeyCell      *p;
} Gi1ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gi1ListItem Gi1ListItem;
struct Gi1ListItem
{
   Gi1ListItem          *next,
                           *prev;
   Gi1                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi1ListItem          *head,
                           *tail;
} Gi1List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gi1ListKeyItem Gi1ListKeyItem;
struct Gi1ListKeyItem
{
   Gi1ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gi1                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi1ListKeyItem       *head,
                           *tail;
} Gi1ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gi1List            **binArray;
   GhashSize               binCount;
} Gi1Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gi1ListKey         **binArray;
   GhashSize               binCount;
} Gi1HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gi1Tree     Gi1Tree;
typedef struct Gi1TreeItem Gi1TreeItem;
struct Gi1TreeItem
{
   Gi1Tree              *owner;
   Gi1TreeItem          *parent;
   Gi1TreeItem          *childLeft;
   Gi1TreeItem          *childRight;
   GheapN                   heapValue;
   Gi1                   value;
};

struct Gi1Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi1TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gi1TreeKey     Gi1TreeKey;
typedef struct Gi1TreeKeyItem Gi1TreeKeyItem;
struct Gi1TreeKeyItem
{
   Gi1TreeKey           *owner;
   Gi1TreeKeyItem       *parent;
   Gi1TreeKeyItem       *childLeft;
   Gi1TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi1                   value;
};

struct Gi1TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi1TreeKeyItem       *root;
};

#define gi1ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi1ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi1ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi1ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi1ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gi1ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi1ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi1ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi1Array *)         g_ArrayCreate(                                Gi1Array, Gi1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi1ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gi1Array, Gi1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi1ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gi1ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gi1ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi1ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gi1ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gi1ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gi1ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi1ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gi1ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gi1ArrayGet(                ARRAY)                                             (Gi1 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gi1ArrayGetAt(              ARRAY, INDEX)                                      (Gi1 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gi1ArrayGetBegin(           ARRAY)                                             (Gi1 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gi1ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gi1ArrayGetEnd(             ARRAY)                                             (Gi1 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gi1ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gi1ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gi1ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gi1ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gi1ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gi1ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi1ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gi1ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi1ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi1ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi1ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi1ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi1ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi1Array *)         g_ArrayKeyCreate(                 Gi1Array, Gi1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi1ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gi1Array, Gi1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi1ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gi1ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi1ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gi1ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gi1ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gi1 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gi1ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gi1ArrayKeyGetBegin(        ARRAY)                                             (Gi1 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyGetEnd(          ARRAY)                                             (Gi1 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gi1ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gi1ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gi1ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi1ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gi1ListAdd(                 LIST, VALUE)                                       (Gi1ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gi1ListAddBegin(            LIST, VALUE)                                       (Gi1ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gi1ListAddEnd(              LIST, VALUE)                                       (Gi1ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gi1ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gi1List *)          g_ListCreate(                               Gi1List, Gi1, OPTIONAL_COMPARE_FUNC)
#define gi1ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gi1List, Gi1, OPTIONAL_COMPARE_FUNC)
#define gi1ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gi1ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gi1ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gi1ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gi1ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gi1ListFind(                LIST, VALUE)                                       (Gi1ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gi1ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gi1ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gi1ListGetBegin(            LIST)                                              (Gi1ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gi1ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gi1ListGetEnd(              LIST)                                              (Gi1ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gi1ListItemAdd(             LIST, LITEM, VALUE)                                (Gi1ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gi1ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gi1ListItemGet(                   LITEM)                                       (Gi1 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gi1ListItemGetNext(               LITEM)                                       (Gi1ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gi1ListItemGetPrev(               LITEM)                                       (Gi1ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gi1ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gi1ListKeyAdd(              LIST, KEY, VALUE)                                  (Gi1ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi1ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gi1ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi1ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gi1ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi1ListKeyCreate(                 COMPARE_FUNC)                                (Gi1List *)          g_ListKeyCreate(                               Gi1ListKey, Gi1, COMPARE_FUNC)
#define gi1ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gi1ListKey, Gi1, COMPARE_FUNC)
#define gi1ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gi1ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gi1ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gi1ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gi1ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gi1ListKeyFind(             LIST, KEY)                                         (Gi1ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gi1ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gi1ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gi1ListKeyGetBegin(         LIST)                                              (Gi1ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gi1ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gi1ListKeyGetEnd(           LIST)                                              (Gi1ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gi1ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gi1ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gi1ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gi1ListKeyItemGet(                LITEM)                                       (Gi1 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gi1ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gi1ListKeyItemGetNext(            LITEM)                                       (Gi1ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gi1ListKeyItemGetPrev(            LITEM)                                       (Gi1ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gi1ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gi1ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gi1HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gi1HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gi1Hash *)          g_HashCreate(                               Gi1Hash, Gi1, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi1HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gi1Hash, Gi1, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi1HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gi1HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gi1HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gi1HashFind(                HASH, VALUE)                                       (Gi1 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gi1HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gi1HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gi1HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gi1HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gi1HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gi1HashKeyCreate(                 HASHSIZE)                                    (Gi1HashKey *)       g_HashKeyCreate(                               Gi1HashKey, Gi1, HASHSIZE)
#define gi1HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gi1HashKey, Gi1, HASHSIZE)
#define gi1HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gi1HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gi1HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gi1HashKeyFind(             HASH, KEY)                                         (Gi1 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gi1HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gi1HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gi1HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gi1HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gi1TreeAdd(                 TREE, VALUE)                                       (Gi1TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gi1TreeCreate(                    COMPARE_FUNC)                                (Gi1Tree *)          g_TreeCreate(                    Gi1Tree, Gi1, COMPARE_FUNC)
#define gi1TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gi1Tree, Gi1, COMPARE_FUNC)
#define gi1TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gi1TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gi1TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gi1TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gi1TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gi1TreeFind(                TREE, VALUE)                                       (Gi1TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gi1TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gi1TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gi1TreeGetBegin(            TREE)                                              (Gi1TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gi1TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gi1TreeGetEnd(              TREE)                                              (Gi1TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gi1TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gi1TreeItemGet(                   TITEM)                                       (Gi1 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gi1TreeItemGetNext(               TITEM)                                       (Gi1TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gi1TreeItemGetPrev(               TITEM)                                       (Gi1TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gi1TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gi1TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gi1TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gi1TreeKeyCreate(                 COMPARE_FUNC)                                (Gi1TreeKey *)       g_TreeKeyCreate(                 Gi1TreeKey, Gi1, COMPARE_FUNC)
#define gi1TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gi1TreeKey, Gi1, COMPARE_FUNC)
#define gi1TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gi1TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gi1TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gi1TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gi1TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gi1TreeKeyFind(             TREE, KEY)                                         (Gi1TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gi1TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gi1TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gi1TreeKeyGetBegin(         TREE)                                              (Gi1TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gi1TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gi1TreeKeyGetEnd(           TREE)                                              (Gi1TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gi1TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gi1TreeKeyItemGet(                TITEM)                                       (Gi1 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gi1TreeKeyItemGetNext(            TITEM)                                       (Gi1TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gi1TreeKeyItemGetPrev(            TITEM)                                       (Gi1TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gi1TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gi2 containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi2                  *p;
} Gi2Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi2                   value;
} Gi2ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gi2ArrayKeyCell      *p;
} Gi2ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gi2ListItem Gi2ListItem;
struct Gi2ListItem
{
   Gi2ListItem          *next,
                           *prev;
   Gi2                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi2ListItem          *head,
                           *tail;
} Gi2List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gi2ListKeyItem Gi2ListKeyItem;
struct Gi2ListKeyItem
{
   Gi2ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gi2                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi2ListKeyItem       *head,
                           *tail;
} Gi2ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gi2List            **binArray;
   GhashSize               binCount;
} Gi2Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gi2ListKey         **binArray;
   GhashSize               binCount;
} Gi2HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gi2Tree     Gi2Tree;
typedef struct Gi2TreeItem Gi2TreeItem;
struct Gi2TreeItem
{
   Gi2Tree              *owner;
   Gi2TreeItem          *parent;
   Gi2TreeItem          *childLeft;
   Gi2TreeItem          *childRight;
   GheapN                   heapValue;
   Gi2                   value;
};

struct Gi2Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi2TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gi2TreeKey     Gi2TreeKey;
typedef struct Gi2TreeKeyItem Gi2TreeKeyItem;
struct Gi2TreeKeyItem
{
   Gi2TreeKey           *owner;
   Gi2TreeKeyItem       *parent;
   Gi2TreeKeyItem       *childLeft;
   Gi2TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi2                   value;
};

struct Gi2TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi2TreeKeyItem       *root;
};

#define gi2ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi2ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi2ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi2ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi2ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gi2ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi2ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi2ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi2Array *)         g_ArrayCreate(                                Gi2Array, Gi2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi2ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gi2Array, Gi2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi2ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gi2ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gi2ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi2ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gi2ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gi2ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gi2ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi2ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gi2ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gi2ArrayGet(                ARRAY)                                             (Gi2 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gi2ArrayGetAt(              ARRAY, INDEX)                                      (Gi2 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gi2ArrayGetBegin(           ARRAY)                                             (Gi2 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gi2ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gi2ArrayGetEnd(             ARRAY)                                             (Gi2 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gi2ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gi2ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gi2ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gi2ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gi2ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gi2ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi2ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gi2ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi2ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi2ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi2ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi2ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi2ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi2Array *)         g_ArrayKeyCreate(                 Gi2Array, Gi2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi2ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gi2Array, Gi2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi2ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gi2ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi2ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gi2ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gi2ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gi2 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gi2ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gi2ArrayKeyGetBegin(        ARRAY)                                             (Gi2 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyGetEnd(          ARRAY)                                             (Gi2 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gi2ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gi2ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gi2ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi2ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gi2ListAdd(                 LIST, VALUE)                                       (Gi2ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gi2ListAddBegin(            LIST, VALUE)                                       (Gi2ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gi2ListAddEnd(              LIST, VALUE)                                       (Gi2ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gi2ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gi2List *)          g_ListCreate(                               Gi2List, Gi2, OPTIONAL_COMPARE_FUNC)
#define gi2ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gi2List, Gi2, OPTIONAL_COMPARE_FUNC)
#define gi2ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gi2ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gi2ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gi2ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gi2ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gi2ListFind(                LIST, VALUE)                                       (Gi2ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gi2ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gi2ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gi2ListGetBegin(            LIST)                                              (Gi2ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gi2ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gi2ListGetEnd(              LIST)                                              (Gi2ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gi2ListItemAdd(             LIST, LITEM, VALUE)                                (Gi2ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gi2ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gi2ListItemGet(                   LITEM)                                       (Gi2 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gi2ListItemGetNext(               LITEM)                                       (Gi2ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gi2ListItemGetPrev(               LITEM)                                       (Gi2ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gi2ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gi2ListKeyAdd(              LIST, KEY, VALUE)                                  (Gi2ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi2ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gi2ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi2ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gi2ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi2ListKeyCreate(                 COMPARE_FUNC)                                (Gi2List *)          g_ListKeyCreate(                               Gi2ListKey, Gi2, COMPARE_FUNC)
#define gi2ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gi2ListKey, Gi2, COMPARE_FUNC)
#define gi2ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gi2ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gi2ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gi2ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gi2ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gi2ListKeyFind(             LIST, KEY)                                         (Gi2ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gi2ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gi2ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gi2ListKeyGetBegin(         LIST)                                              (Gi2ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gi2ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gi2ListKeyGetEnd(           LIST)                                              (Gi2ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gi2ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gi2ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gi2ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gi2ListKeyItemGet(                LITEM)                                       (Gi2 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gi2ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gi2ListKeyItemGetNext(            LITEM)                                       (Gi2ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gi2ListKeyItemGetPrev(            LITEM)                                       (Gi2ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gi2ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gi2ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gi2HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gi2HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gi2Hash *)          g_HashCreate(                               Gi2Hash, Gi2, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi2HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gi2Hash, Gi2, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi2HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gi2HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gi2HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gi2HashFind(                HASH, VALUE)                                       (Gi2 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gi2HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gi2HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gi2HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gi2HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gi2HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gi2HashKeyCreate(                 HASHSIZE)                                    (Gi2HashKey *)       g_HashKeyCreate(                               Gi2HashKey, Gi2, HASHSIZE)
#define gi2HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gi2HashKey, Gi2, HASHSIZE)
#define gi2HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gi2HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gi2HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gi2HashKeyFind(             HASH, KEY)                                         (Gi2 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gi2HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gi2HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gi2HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gi2HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gi2TreeAdd(                 TREE, VALUE)                                       (Gi2TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gi2TreeCreate(                    COMPARE_FUNC)                                (Gi2Tree *)          g_TreeCreate(                    Gi2Tree, Gi2, COMPARE_FUNC)
#define gi2TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gi2Tree, Gi2, COMPARE_FUNC)
#define gi2TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gi2TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gi2TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gi2TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gi2TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gi2TreeFind(                TREE, VALUE)                                       (Gi2TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gi2TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gi2TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gi2TreeGetBegin(            TREE)                                              (Gi2TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gi2TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gi2TreeGetEnd(              TREE)                                              (Gi2TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gi2TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gi2TreeItemGet(                   TITEM)                                       (Gi2 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gi2TreeItemGetNext(               TITEM)                                       (Gi2TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gi2TreeItemGetPrev(               TITEM)                                       (Gi2TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gi2TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gi2TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gi2TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gi2TreeKeyCreate(                 COMPARE_FUNC)                                (Gi2TreeKey *)       g_TreeKeyCreate(                 Gi2TreeKey, Gi2, COMPARE_FUNC)
#define gi2TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gi2TreeKey, Gi2, COMPARE_FUNC)
#define gi2TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gi2TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gi2TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gi2TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gi2TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gi2TreeKeyFind(             TREE, KEY)                                         (Gi2TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gi2TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gi2TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gi2TreeKeyGetBegin(         TREE)                                              (Gi2TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gi2TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gi2TreeKeyGetEnd(           TREE)                                              (Gi2TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gi2TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gi2TreeKeyItemGet(                TITEM)                                       (Gi2 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gi2TreeKeyItemGetNext(            TITEM)                                       (Gi2TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gi2TreeKeyItemGetPrev(            TITEM)                                       (Gi2TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gi2TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gi4 containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi4                  *p;
} Gi4Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi4                   value;
} Gi4ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gi4ArrayKeyCell      *p;
} Gi4ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gi4ListItem Gi4ListItem;
struct Gi4ListItem
{
   Gi4ListItem          *next,
                           *prev;
   Gi4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi4ListItem          *head,
                           *tail;
} Gi4List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gi4ListKeyItem Gi4ListKeyItem;
struct Gi4ListKeyItem
{
   Gi4ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gi4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi4ListKeyItem       *head,
                           *tail;
} Gi4ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gi4List            **binArray;
   GhashSize               binCount;
} Gi4Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gi4ListKey         **binArray;
   GhashSize               binCount;
} Gi4HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gi4Tree     Gi4Tree;
typedef struct Gi4TreeItem Gi4TreeItem;
struct Gi4TreeItem
{
   Gi4Tree              *owner;
   Gi4TreeItem          *parent;
   Gi4TreeItem          *childLeft;
   Gi4TreeItem          *childRight;
   GheapN                   heapValue;
   Gi4                   value;
};

struct Gi4Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi4TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gi4TreeKey     Gi4TreeKey;
typedef struct Gi4TreeKeyItem Gi4TreeKeyItem;
struct Gi4TreeKeyItem
{
   Gi4TreeKey           *owner;
   Gi4TreeKeyItem       *parent;
   Gi4TreeKeyItem       *childLeft;
   Gi4TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi4                   value;
};

struct Gi4TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi4TreeKeyItem       *root;
};

#define gi4ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi4ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi4ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi4ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi4ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gi4ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi4ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi4ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi4Array *)         g_ArrayCreate(                                Gi4Array, Gi4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi4ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gi4Array, Gi4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi4ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gi4ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gi4ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi4ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gi4ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gi4ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gi4ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi4ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gi4ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gi4ArrayGet(                ARRAY)                                             (Gi4 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gi4ArrayGetAt(              ARRAY, INDEX)                                      (Gi4 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gi4ArrayGetBegin(           ARRAY)                                             (Gi4 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gi4ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gi4ArrayGetEnd(             ARRAY)                                             (Gi4 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gi4ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gi4ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gi4ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gi4ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gi4ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gi4ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi4ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gi4ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi4ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi4ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi4ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi4ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi4ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi4Array *)         g_ArrayKeyCreate(                 Gi4Array, Gi4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi4ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gi4Array, Gi4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi4ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gi4ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi4ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gi4ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gi4ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gi4 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gi4ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gi4ArrayKeyGetBegin(        ARRAY)                                             (Gi4 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyGetEnd(          ARRAY)                                             (Gi4 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gi4ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gi4ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gi4ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi4ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gi4ListAdd(                 LIST, VALUE)                                       (Gi4ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gi4ListAddBegin(            LIST, VALUE)                                       (Gi4ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gi4ListAddEnd(              LIST, VALUE)                                       (Gi4ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gi4ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gi4List *)          g_ListCreate(                               Gi4List, Gi4, OPTIONAL_COMPARE_FUNC)
#define gi4ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gi4List, Gi4, OPTIONAL_COMPARE_FUNC)
#define gi4ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gi4ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gi4ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gi4ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gi4ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gi4ListFind(                LIST, VALUE)                                       (Gi4ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gi4ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gi4ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gi4ListGetBegin(            LIST)                                              (Gi4ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gi4ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gi4ListGetEnd(              LIST)                                              (Gi4ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gi4ListItemAdd(             LIST, LITEM, VALUE)                                (Gi4ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gi4ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gi4ListItemGet(                   LITEM)                                       (Gi4 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gi4ListItemGetNext(               LITEM)                                       (Gi4ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gi4ListItemGetPrev(               LITEM)                                       (Gi4ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gi4ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gi4ListKeyAdd(              LIST, KEY, VALUE)                                  (Gi4ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi4ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gi4ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi4ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gi4ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi4ListKeyCreate(                 COMPARE_FUNC)                                (Gi4List *)          g_ListKeyCreate(                               Gi4ListKey, Gi4, COMPARE_FUNC)
#define gi4ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gi4ListKey, Gi4, COMPARE_FUNC)
#define gi4ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gi4ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gi4ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gi4ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gi4ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gi4ListKeyFind(             LIST, KEY)                                         (Gi4ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gi4ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gi4ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gi4ListKeyGetBegin(         LIST)                                              (Gi4ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gi4ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gi4ListKeyGetEnd(           LIST)                                              (Gi4ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gi4ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gi4ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gi4ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gi4ListKeyItemGet(                LITEM)                                       (Gi4 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gi4ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gi4ListKeyItemGetNext(            LITEM)                                       (Gi4ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gi4ListKeyItemGetPrev(            LITEM)                                       (Gi4ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gi4ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gi4ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gi4HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gi4HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gi4Hash *)          g_HashCreate(                               Gi4Hash, Gi4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi4HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gi4Hash, Gi4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi4HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gi4HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gi4HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gi4HashFind(                HASH, VALUE)                                       (Gi4 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gi4HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gi4HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gi4HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gi4HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gi4HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gi4HashKeyCreate(                 HASHSIZE)                                    (Gi4HashKey *)       g_HashKeyCreate(                               Gi4HashKey, Gi4, HASHSIZE)
#define gi4HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gi4HashKey, Gi4, HASHSIZE)
#define gi4HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gi4HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gi4HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gi4HashKeyFind(             HASH, KEY)                                         (Gi4 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gi4HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gi4HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gi4HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gi4HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gi4TreeAdd(                 TREE, VALUE)                                       (Gi4TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gi4TreeCreate(                    COMPARE_FUNC)                                (Gi4Tree *)          g_TreeCreate(                    Gi4Tree, Gi4, COMPARE_FUNC)
#define gi4TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gi4Tree, Gi4, COMPARE_FUNC)
#define gi4TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gi4TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gi4TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gi4TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gi4TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gi4TreeFind(                TREE, VALUE)                                       (Gi4TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gi4TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gi4TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gi4TreeGetBegin(            TREE)                                              (Gi4TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gi4TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gi4TreeGetEnd(              TREE)                                              (Gi4TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gi4TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gi4TreeItemGet(                   TITEM)                                       (Gi4 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gi4TreeItemGetNext(               TITEM)                                       (Gi4TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gi4TreeItemGetPrev(               TITEM)                                       (Gi4TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gi4TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gi4TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gi4TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gi4TreeKeyCreate(                 COMPARE_FUNC)                                (Gi4TreeKey *)       g_TreeKeyCreate(                 Gi4TreeKey, Gi4, COMPARE_FUNC)
#define gi4TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gi4TreeKey, Gi4, COMPARE_FUNC)
#define gi4TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gi4TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gi4TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gi4TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gi4TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gi4TreeKeyFind(             TREE, KEY)                                         (Gi4TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gi4TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gi4TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gi4TreeKeyGetBegin(         TREE)                                              (Gi4TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gi4TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gi4TreeKeyGetEnd(           TREE)                                              (Gi4TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gi4TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gi4TreeKeyItemGet(                TITEM)                                       (Gi4 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gi4TreeKeyItemGetNext(            TITEM)                                       (Gi4TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gi4TreeKeyItemGetPrev(            TITEM)                                       (Gi4TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gi4TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gi8 containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi8                  *p;
} Gi8Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi8                   value;
} Gi8ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gi8ArrayKeyCell      *p;
} Gi8ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gi8ListItem Gi8ListItem;
struct Gi8ListItem
{
   Gi8ListItem          *next,
                           *prev;
   Gi8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi8ListItem          *head,
                           *tail;
} Gi8List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gi8ListKeyItem Gi8ListKeyItem;
struct Gi8ListKeyItem
{
   Gi8ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gi8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gi8ListKeyItem       *head,
                           *tail;
} Gi8ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gi8List            **binArray;
   GhashSize               binCount;
} Gi8Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gi8ListKey         **binArray;
   GhashSize               binCount;
} Gi8HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gi8Tree     Gi8Tree;
typedef struct Gi8TreeItem Gi8TreeItem;
struct Gi8TreeItem
{
   Gi8Tree              *owner;
   Gi8TreeItem          *parent;
   Gi8TreeItem          *childLeft;
   Gi8TreeItem          *childRight;
   GheapN                   heapValue;
   Gi8                   value;
};

struct Gi8Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi8TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gi8TreeKey     Gi8TreeKey;
typedef struct Gi8TreeKeyItem Gi8TreeKeyItem;
struct Gi8TreeKeyItem
{
   Gi8TreeKey           *owner;
   Gi8TreeKeyItem       *parent;
   Gi8TreeKeyItem       *childLeft;
   Gi8TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi8                   value;
};

struct Gi8TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gi8TreeKeyItem       *root;
};

#define gi8ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi8ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi8ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi8ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gi8ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gi8ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi8ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi8ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi8Array *)         g_ArrayCreate(                                Gi8Array, Gi8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi8ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gi8Array, Gi8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gi8ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gi8ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gi8ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi8ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gi8ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gi8ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gi8ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gi8ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gi8ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gi8ArrayGet(                ARRAY)                                             (Gi8 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gi8ArrayGetAt(              ARRAY, INDEX)                                      (Gi8 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gi8ArrayGetBegin(           ARRAY)                                             (Gi8 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gi8ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gi8ArrayGetEnd(             ARRAY)                                             (Gi8 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gi8ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gi8ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gi8ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gi8ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gi8ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gi8ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi8ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gi8ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi8ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gi8ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi8ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gi8ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gi8ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gi8Array *)         g_ArrayKeyCreate(                 Gi8Array, Gi8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi8ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gi8Array, Gi8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gi8ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gi8ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gi8ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gi8ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gi8ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gi8 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gi8ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gi8ArrayKeyGetBegin(        ARRAY)                                             (Gi8 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyGetEnd(          ARRAY)                                             (Gi8 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gi8ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gi8ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gi8ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gi8ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gi8ListAdd(                 LIST, VALUE)                                       (Gi8ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gi8ListAddBegin(            LIST, VALUE)                                       (Gi8ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gi8ListAddEnd(              LIST, VALUE)                                       (Gi8ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gi8ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gi8List *)          g_ListCreate(                               Gi8List, Gi8, OPTIONAL_COMPARE_FUNC)
#define gi8ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gi8List, Gi8, OPTIONAL_COMPARE_FUNC)
#define gi8ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gi8ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gi8ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gi8ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gi8ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gi8ListFind(                LIST, VALUE)                                       (Gi8ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gi8ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gi8ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gi8ListGetBegin(            LIST)                                              (Gi8ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gi8ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gi8ListGetEnd(              LIST)                                              (Gi8ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gi8ListItemAdd(             LIST, LITEM, VALUE)                                (Gi8ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gi8ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gi8ListItemGet(                   LITEM)                                       (Gi8 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gi8ListItemGetNext(               LITEM)                                       (Gi8ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gi8ListItemGetPrev(               LITEM)                                       (Gi8ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gi8ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gi8ListKeyAdd(              LIST, KEY, VALUE)                                  (Gi8ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi8ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gi8ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi8ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gi8ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gi8ListKeyCreate(                 COMPARE_FUNC)                                (Gi8List *)          g_ListKeyCreate(                               Gi8ListKey, Gi8, COMPARE_FUNC)
#define gi8ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gi8ListKey, Gi8, COMPARE_FUNC)
#define gi8ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gi8ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gi8ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gi8ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gi8ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gi8ListKeyFind(             LIST, KEY)                                         (Gi8ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gi8ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gi8ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gi8ListKeyGetBegin(         LIST)                                              (Gi8ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gi8ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gi8ListKeyGetEnd(           LIST)                                              (Gi8ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gi8ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gi8ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gi8ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gi8ListKeyItemGet(                LITEM)                                       (Gi8 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gi8ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gi8ListKeyItemGetNext(            LITEM)                                       (Gi8ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gi8ListKeyItemGetPrev(            LITEM)                                       (Gi8ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gi8ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gi8ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gi8HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gi8HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gi8Hash *)          g_HashCreate(                               Gi8Hash, Gi8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi8HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gi8Hash, Gi8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gi8HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gi8HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gi8HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gi8HashFind(                HASH, VALUE)                                       (Gi8 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gi8HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gi8HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gi8HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gi8HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gi8HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gi8HashKeyCreate(                 HASHSIZE)                                    (Gi8HashKey *)       g_HashKeyCreate(                               Gi8HashKey, Gi8, HASHSIZE)
#define gi8HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gi8HashKey, Gi8, HASHSIZE)
#define gi8HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gi8HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gi8HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gi8HashKeyFind(             HASH, KEY)                                         (Gi8 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gi8HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gi8HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gi8HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gi8HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gi8TreeAdd(                 TREE, VALUE)                                       (Gi8TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gi8TreeCreate(                    COMPARE_FUNC)                                (Gi8Tree *)          g_TreeCreate(                    Gi8Tree, Gi8, COMPARE_FUNC)
#define gi8TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gi8Tree, Gi8, COMPARE_FUNC)
#define gi8TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gi8TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gi8TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gi8TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gi8TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gi8TreeFind(                TREE, VALUE)                                       (Gi8TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gi8TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gi8TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gi8TreeGetBegin(            TREE)                                              (Gi8TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gi8TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gi8TreeGetEnd(              TREE)                                              (Gi8TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gi8TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gi8TreeItemGet(                   TITEM)                                       (Gi8 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gi8TreeItemGetNext(               TITEM)                                       (Gi8TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gi8TreeItemGetPrev(               TITEM)                                       (Gi8TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gi8TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gi8TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gi8TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gi8TreeKeyCreate(                 COMPARE_FUNC)                                (Gi8TreeKey *)       g_TreeKeyCreate(                 Gi8TreeKey, Gi8, COMPARE_FUNC)
#define gi8TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gi8TreeKey, Gi8, COMPARE_FUNC)
#define gi8TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gi8TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gi8TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gi8TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gi8TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gi8TreeKeyFind(             TREE, KEY)                                         (Gi8TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gi8TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gi8TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gi8TreeKeyGetBegin(         TREE)                                              (Gi8TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gi8TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gi8TreeKeyGetEnd(           TREE)                                              (Gi8TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gi8TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gi8TreeKeyItemGet(                TITEM)                                       (Gi8 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gi8TreeKeyItemGetNext(            TITEM)                                       (Gi8TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gi8TreeKeyItemGetPrev(            TITEM)                                       (Gi8TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gi8TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
