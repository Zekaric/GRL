/******************************************************************************
file:       Gn
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

#if !defined(GNH)
#define      GNH

/******************************************************************************
Gn containers.
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
   Gn                  *p;
} GnArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn                   value;
} GnArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GnArrayKeyCell      *p;
} GnArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GnListItem GnListItem;
struct GnListItem
{
   GnListItem          *next,
                           *prev;
   Gn                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GnListItem          *head,
                           *tail;
} GnList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GnListKeyItem GnListKeyItem;
struct GnListKeyItem
{
   GnListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gn                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GnListKeyItem       *head,
                           *tail;
} GnListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GnList            **binArray;
   GhashSize               binCount;
} GnHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GnListKey         **binArray;
   GhashSize               binCount;
} GnHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GnTree     GnTree;
typedef struct GnTreeItem GnTreeItem;
struct GnTreeItem
{
   GnTree              *owner;
   GnTreeItem          *parent;
   GnTreeItem          *childLeft;
   GnTreeItem          *childRight;
   GheapN                   heapValue;
   Gn                   value;
};

struct GnTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GnTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GnTreeKey     GnTreeKey;
typedef struct GnTreeKeyItem GnTreeKeyItem;
struct GnTreeKeyItem
{
   GnTreeKey           *owner;
   GnTreeKeyItem       *parent;
   GnTreeKeyItem       *childLeft;
   GnTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn                   value;
};

struct GnTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GnTreeKeyItem       *root;
};

#define gnArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gnArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gnArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gnArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gnArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GnArray *)         g_ArrayCreate(                                GnArray, Gn, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gnArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, GnArray, Gn, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gnArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gnArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gnArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gnArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gnArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gnArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gnArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gnArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gnArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gnArrayGet(                ARRAY)                                             (Gn *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gnArrayGetAt(              ARRAY, INDEX)                                      (Gn *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gnArrayGetBegin(           ARRAY)                                             (Gn *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gnArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gnArrayGetEnd(             ARRAY)                                             (Gn *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gnArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gnArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gnArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gnArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gnArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gnArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gnArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gnArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gnArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gnArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gnArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gnArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gnArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GnArray *)         g_ArrayKeyCreate(                 GnArray, Gn, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gnArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GnArray, Gn, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gnArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gnArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gnArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gnArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gnArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gnArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gnArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gnArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gnArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gnArrayKeyGetAt(           ARRAY, INDEX)                                      (Gn *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gnArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gnArrayKeyGetBegin(        ARRAY)                                             (Gn *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetEnd(          ARRAY)                                             (Gn *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gnArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gnArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gnArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gnArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gnArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gnListAdd(                 LIST, VALUE)                                       (GnListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gnListAddBegin(            LIST, VALUE)                                       (GnListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gnListAddEnd(              LIST, VALUE)                                       (GnListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gnListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GnList *)          g_ListCreate(                               GnList, Gn, OPTIONAL_COMPARE_FUNC)
#define gnListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, GnList, Gn, OPTIONAL_COMPARE_FUNC)
#define gnListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gnListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gnListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gnListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gnListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gnListFind(                LIST, VALUE)                                       (GnListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gnListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gnListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gnListGetBegin(            LIST)                                              (GnListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gnListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gnListGetEnd(              LIST)                                              (GnListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gnListItemAdd(             LIST, LITEM, VALUE)                                (GnListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gnListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gnListItemGet(                   LITEM)                                       (Gn *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gnListItemGetNext(               LITEM)                                       (GnListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gnListItemGetPrev(               LITEM)                                       (GnListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gnListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gnListKeyAdd(              LIST, KEY, VALUE)                                  (GnListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyAddBegin(         LIST, KEY, VALUE)                                  (GnListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyAddEnd(           LIST, KEY, VALUE)                                  (GnListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyCreate(                 COMPARE_FUNC)                                (GnList *)          g_ListKeyCreate(                               GnListKey, Gn, COMPARE_FUNC)
#define gnListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, GnListKey, Gn, COMPARE_FUNC)
#define gnListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gnListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gnListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gnListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gnListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gnListKeyFind(             LIST, KEY)                                         (GnListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gnListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gnListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gnListKeyGetBegin(         LIST)                                              (GnListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gnListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gnListKeyGetEnd(           LIST)                                              (GnListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gnListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GnListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gnListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gnListKeyItemGet(                LITEM)                                       (Gn *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gnListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gnListKeyItemGetNext(            LITEM)                                       (GnListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gnListKeyItemGetPrev(            LITEM)                                       (GnListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gnListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gnListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gnHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gnHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GnHash *)          g_HashCreate(                               GnHash, Gn, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gnHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, GnHash, Gn, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gnHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gnHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gnHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gnHashFind(                HASH, VALUE)                                       (Gn *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gnHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gnHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gnHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gnHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gnHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gnHashKeyCreate(                 HASHSIZE)                                    (GnHashKey *)       g_HashKeyCreate(                               GnHashKey, Gn, HASHSIZE)
#define gnHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, GnHashKey, Gn, HASHSIZE)
#define gnHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gnHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gnHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gnHashKeyFind(             HASH, KEY)                                         (Gn *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gnHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gnHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gnHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gnHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gnTreeAdd(                 TREE, VALUE)                                       (GnTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeCreate(                    COMPARE_FUNC)                                (GnTree *)          g_TreeCreate(                    GnTree, Gn, COMPARE_FUNC)
#define gnTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, GnTree, Gn, COMPARE_FUNC)
#define gnTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gnTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gnTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gnTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gnTreeFind(                TREE, VALUE)                                       (GnTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gnTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gnTreeGetBegin(            TREE)                                              (GnTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gnTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gnTreeGetEnd(              TREE)                                              (GnTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gnTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gnTreeItemGet(                   TITEM)                                       (Gn *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gnTreeItemGetNext(               TITEM)                                       (GnTreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gnTreeItemGetPrev(               TITEM)                                       (GnTreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gnTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gnTreeKeyAdd(              TREE, KEY, VALUE)                                  (GnTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gnTreeKeyCreate(                 COMPARE_FUNC)                                (GnTreeKey *)       g_TreeKeyCreate(                 GnTreeKey, Gn, COMPARE_FUNC)
#define gnTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GnTreeKey, Gn, COMPARE_FUNC)
#define gnTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gnTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gnTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gnTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gnTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gnTreeKeyFind(             TREE, KEY)                                         (GnTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gnTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gnTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gnTreeKeyGetBegin(         TREE)                                              (GnTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gnTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gnTreeKeyGetEnd(           TREE)                                              (GnTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gnTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemGet(                TITEM)                                       (Gn *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemGetNext(            TITEM)                                       (GnTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemGetPrev(            TITEM)                                       (GnTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gn1 containers.
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
   Gn1                  *p;
} Gn1Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn1                   value;
} Gn1ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gn1ArrayKeyCell      *p;
} Gn1ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gn1ListItem Gn1ListItem;
struct Gn1ListItem
{
   Gn1ListItem          *next,
                           *prev;
   Gn1                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn1ListItem          *head,
                           *tail;
} Gn1List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gn1ListKeyItem Gn1ListKeyItem;
struct Gn1ListKeyItem
{
   Gn1ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gn1                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn1ListKeyItem       *head,
                           *tail;
} Gn1ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gn1List            **binArray;
   GhashSize               binCount;
} Gn1Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gn1ListKey         **binArray;
   GhashSize               binCount;
} Gn1HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gn1Tree     Gn1Tree;
typedef struct Gn1TreeItem Gn1TreeItem;
struct Gn1TreeItem
{
   Gn1Tree              *owner;
   Gn1TreeItem          *parent;
   Gn1TreeItem          *childLeft;
   Gn1TreeItem          *childRight;
   GheapN                   heapValue;
   Gn1                   value;
};

struct Gn1Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn1TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gn1TreeKey     Gn1TreeKey;
typedef struct Gn1TreeKeyItem Gn1TreeKeyItem;
struct Gn1TreeKeyItem
{
   Gn1TreeKey           *owner;
   Gn1TreeKeyItem       *parent;
   Gn1TreeKeyItem       *childLeft;
   Gn1TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn1                   value;
};

struct Gn1TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn1TreeKeyItem       *root;
};

#define gn1ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn1ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gn1ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn1ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn1ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn1Array *)         g_ArrayCreate(                                Gn1Array, Gn1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn1ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gn1Array, Gn1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn1ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gn1ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gn1ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn1ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gn1ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gn1ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gn1ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn1ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gn1ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gn1ArrayGet(                ARRAY)                                             (Gn1 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gn1ArrayGetAt(              ARRAY, INDEX)                                      (Gn1 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gn1ArrayGetBegin(           ARRAY)                                             (Gn1 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gn1ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gn1ArrayGetEnd(             ARRAY)                                             (Gn1 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gn1ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gn1ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gn1ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gn1ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gn1ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gn1ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn1ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gn1ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn1ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn1ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn1ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn1ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn1ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn1Array *)         g_ArrayKeyCreate(                 Gn1Array, Gn1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn1ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gn1Array, Gn1, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn1ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gn1ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn1ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gn1ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gn1ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gn1 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gn1ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gn1ArrayKeyGetBegin(        ARRAY)                                             (Gn1 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyGetEnd(          ARRAY)                                             (Gn1 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gn1ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gn1ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gn1ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn1ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gn1ListAdd(                 LIST, VALUE)                                       (Gn1ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gn1ListAddBegin(            LIST, VALUE)                                       (Gn1ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gn1ListAddEnd(              LIST, VALUE)                                       (Gn1ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gn1ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gn1List *)          g_ListCreate(                               Gn1List, Gn1, OPTIONAL_COMPARE_FUNC)
#define gn1ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gn1List, Gn1, OPTIONAL_COMPARE_FUNC)
#define gn1ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gn1ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gn1ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gn1ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gn1ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gn1ListFind(                LIST, VALUE)                                       (Gn1ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gn1ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gn1ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gn1ListGetBegin(            LIST)                                              (Gn1ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gn1ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gn1ListGetEnd(              LIST)                                              (Gn1ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gn1ListItemAdd(             LIST, LITEM, VALUE)                                (Gn1ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gn1ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gn1ListItemGet(                   LITEM)                                       (Gn1 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gn1ListItemGetNext(               LITEM)                                       (Gn1ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gn1ListItemGetPrev(               LITEM)                                       (Gn1ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gn1ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gn1ListKeyAdd(              LIST, KEY, VALUE)                                  (Gn1ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn1ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gn1ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn1ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gn1ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn1ListKeyCreate(                 COMPARE_FUNC)                                (Gn1List *)          g_ListKeyCreate(                               Gn1ListKey, Gn1, COMPARE_FUNC)
#define gn1ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gn1ListKey, Gn1, COMPARE_FUNC)
#define gn1ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gn1ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gn1ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gn1ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gn1ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gn1ListKeyFind(             LIST, KEY)                                         (Gn1ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gn1ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gn1ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gn1ListKeyGetBegin(         LIST)                                              (Gn1ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gn1ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gn1ListKeyGetEnd(           LIST)                                              (Gn1ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gn1ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gn1ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gn1ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gn1ListKeyItemGet(                LITEM)                                       (Gn1 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gn1ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gn1ListKeyItemGetNext(            LITEM)                                       (Gn1ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gn1ListKeyItemGetPrev(            LITEM)                                       (Gn1ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gn1ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gn1ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gn1HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gn1HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gn1Hash *)          g_HashCreate(                               Gn1Hash, Gn1, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn1HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gn1Hash, Gn1, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn1HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gn1HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gn1HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gn1HashFind(                HASH, VALUE)                                       (Gn1 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gn1HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gn1HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gn1HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gn1HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gn1HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gn1HashKeyCreate(                 HASHSIZE)                                    (Gn1HashKey *)       g_HashKeyCreate(                               Gn1HashKey, Gn1, HASHSIZE)
#define gn1HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gn1HashKey, Gn1, HASHSIZE)
#define gn1HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gn1HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gn1HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gn1HashKeyFind(             HASH, KEY)                                         (Gn1 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gn1HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gn1HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gn1HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gn1HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gn1TreeAdd(                 TREE, VALUE)                                       (Gn1TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gn1TreeCreate(                    COMPARE_FUNC)                                (Gn1Tree *)          g_TreeCreate(                    Gn1Tree, Gn1, COMPARE_FUNC)
#define gn1TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gn1Tree, Gn1, COMPARE_FUNC)
#define gn1TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gn1TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gn1TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gn1TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gn1TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gn1TreeFind(                TREE, VALUE)                                       (Gn1TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gn1TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gn1TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gn1TreeGetBegin(            TREE)                                              (Gn1TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gn1TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gn1TreeGetEnd(              TREE)                                              (Gn1TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gn1TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gn1TreeItemGet(                   TITEM)                                       (Gn1 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gn1TreeItemGetNext(               TITEM)                                       (Gn1TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gn1TreeItemGetPrev(               TITEM)                                       (Gn1TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gn1TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gn1TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gn1TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gn1TreeKeyCreate(                 COMPARE_FUNC)                                (Gn1TreeKey *)       g_TreeKeyCreate(                 Gn1TreeKey, Gn1, COMPARE_FUNC)
#define gn1TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gn1TreeKey, Gn1, COMPARE_FUNC)
#define gn1TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gn1TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gn1TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gn1TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gn1TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gn1TreeKeyFind(             TREE, KEY)                                         (Gn1TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gn1TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gn1TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gn1TreeKeyGetBegin(         TREE)                                              (Gn1TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gn1TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gn1TreeKeyGetEnd(           TREE)                                              (Gn1TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gn1TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gn1TreeKeyItemGet(                TITEM)                                       (Gn1 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gn1TreeKeyItemGetNext(            TITEM)                                       (Gn1TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gn1TreeKeyItemGetPrev(            TITEM)                                       (Gn1TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gn1TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gn2 containers.
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
   Gn2                  *p;
} Gn2Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn2                   value;
} Gn2ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gn2ArrayKeyCell      *p;
} Gn2ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gn2ListItem Gn2ListItem;
struct Gn2ListItem
{
   Gn2ListItem          *next,
                           *prev;
   Gn2                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn2ListItem          *head,
                           *tail;
} Gn2List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gn2ListKeyItem Gn2ListKeyItem;
struct Gn2ListKeyItem
{
   Gn2ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gn2                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn2ListKeyItem       *head,
                           *tail;
} Gn2ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gn2List            **binArray;
   GhashSize               binCount;
} Gn2Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gn2ListKey         **binArray;
   GhashSize               binCount;
} Gn2HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gn2Tree     Gn2Tree;
typedef struct Gn2TreeItem Gn2TreeItem;
struct Gn2TreeItem
{
   Gn2Tree              *owner;
   Gn2TreeItem          *parent;
   Gn2TreeItem          *childLeft;
   Gn2TreeItem          *childRight;
   GheapN                   heapValue;
   Gn2                   value;
};

struct Gn2Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn2TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gn2TreeKey     Gn2TreeKey;
typedef struct Gn2TreeKeyItem Gn2TreeKeyItem;
struct Gn2TreeKeyItem
{
   Gn2TreeKey           *owner;
   Gn2TreeKeyItem       *parent;
   Gn2TreeKeyItem       *childLeft;
   Gn2TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn2                   value;
};

struct Gn2TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn2TreeKeyItem       *root;
};

#define gn2ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn2ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn2ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn2ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn2ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gn2ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn2ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn2ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn2Array *)         g_ArrayCreate(                                Gn2Array, Gn2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn2ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gn2Array, Gn2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn2ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gn2ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gn2ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn2ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gn2ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gn2ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gn2ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn2ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gn2ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gn2ArrayGet(                ARRAY)                                             (Gn2 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gn2ArrayGetAt(              ARRAY, INDEX)                                      (Gn2 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gn2ArrayGetBegin(           ARRAY)                                             (Gn2 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gn2ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gn2ArrayGetEnd(             ARRAY)                                             (Gn2 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gn2ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gn2ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gn2ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gn2ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gn2ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gn2ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn2ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gn2ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn2ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn2ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn2ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn2ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn2ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn2Array *)         g_ArrayKeyCreate(                 Gn2Array, Gn2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn2ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gn2Array, Gn2, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn2ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gn2ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn2ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gn2ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gn2ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gn2 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gn2ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gn2ArrayKeyGetBegin(        ARRAY)                                             (Gn2 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyGetEnd(          ARRAY)                                             (Gn2 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gn2ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gn2ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gn2ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn2ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gn2ListAdd(                 LIST, VALUE)                                       (Gn2ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gn2ListAddBegin(            LIST, VALUE)                                       (Gn2ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gn2ListAddEnd(              LIST, VALUE)                                       (Gn2ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gn2ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gn2List *)          g_ListCreate(                               Gn2List, Gn2, OPTIONAL_COMPARE_FUNC)
#define gn2ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gn2List, Gn2, OPTIONAL_COMPARE_FUNC)
#define gn2ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gn2ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gn2ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gn2ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gn2ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gn2ListFind(                LIST, VALUE)                                       (Gn2ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gn2ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gn2ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gn2ListGetBegin(            LIST)                                              (Gn2ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gn2ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gn2ListGetEnd(              LIST)                                              (Gn2ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gn2ListItemAdd(             LIST, LITEM, VALUE)                                (Gn2ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gn2ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gn2ListItemGet(                   LITEM)                                       (Gn2 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gn2ListItemGetNext(               LITEM)                                       (Gn2ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gn2ListItemGetPrev(               LITEM)                                       (Gn2ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gn2ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gn2ListKeyAdd(              LIST, KEY, VALUE)                                  (Gn2ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn2ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gn2ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn2ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gn2ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn2ListKeyCreate(                 COMPARE_FUNC)                                (Gn2List *)          g_ListKeyCreate(                               Gn2ListKey, Gn2, COMPARE_FUNC)
#define gn2ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gn2ListKey, Gn2, COMPARE_FUNC)
#define gn2ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gn2ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gn2ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gn2ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gn2ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gn2ListKeyFind(             LIST, KEY)                                         (Gn2ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gn2ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gn2ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gn2ListKeyGetBegin(         LIST)                                              (Gn2ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gn2ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gn2ListKeyGetEnd(           LIST)                                              (Gn2ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gn2ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gn2ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gn2ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gn2ListKeyItemGet(                LITEM)                                       (Gn2 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gn2ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gn2ListKeyItemGetNext(            LITEM)                                       (Gn2ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gn2ListKeyItemGetPrev(            LITEM)                                       (Gn2ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gn2ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gn2ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gn2HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gn2HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gn2Hash *)          g_HashCreate(                               Gn2Hash, Gn2, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn2HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gn2Hash, Gn2, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn2HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gn2HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gn2HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gn2HashFind(                HASH, VALUE)                                       (Gn2 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gn2HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gn2HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gn2HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gn2HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gn2HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gn2HashKeyCreate(                 HASHSIZE)                                    (Gn2HashKey *)       g_HashKeyCreate(                               Gn2HashKey, Gn2, HASHSIZE)
#define gn2HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gn2HashKey, Gn2, HASHSIZE)
#define gn2HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gn2HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gn2HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gn2HashKeyFind(             HASH, KEY)                                         (Gn2 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gn2HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gn2HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gn2HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gn2HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gn2TreeAdd(                 TREE, VALUE)                                       (Gn2TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gn2TreeCreate(                    COMPARE_FUNC)                                (Gn2Tree *)          g_TreeCreate(                    Gn2Tree, Gn2, COMPARE_FUNC)
#define gn2TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gn2Tree, Gn2, COMPARE_FUNC)
#define gn2TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gn2TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gn2TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gn2TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gn2TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gn2TreeFind(                TREE, VALUE)                                       (Gn2TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gn2TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gn2TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gn2TreeGetBegin(            TREE)                                              (Gn2TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gn2TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gn2TreeGetEnd(              TREE)                                              (Gn2TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gn2TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gn2TreeItemGet(                   TITEM)                                       (Gn2 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gn2TreeItemGetNext(               TITEM)                                       (Gn2TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gn2TreeItemGetPrev(               TITEM)                                       (Gn2TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gn2TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gn2TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gn2TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gn2TreeKeyCreate(                 COMPARE_FUNC)                                (Gn2TreeKey *)       g_TreeKeyCreate(                 Gn2TreeKey, Gn2, COMPARE_FUNC)
#define gn2TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gn2TreeKey, Gn2, COMPARE_FUNC)
#define gn2TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gn2TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gn2TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gn2TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gn2TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gn2TreeKeyFind(             TREE, KEY)                                         (Gn2TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gn2TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gn2TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gn2TreeKeyGetBegin(         TREE)                                              (Gn2TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gn2TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gn2TreeKeyGetEnd(           TREE)                                              (Gn2TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gn2TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gn2TreeKeyItemGet(                TITEM)                                       (Gn2 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gn2TreeKeyItemGetNext(            TITEM)                                       (Gn2TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gn2TreeKeyItemGetPrev(            TITEM)                                       (Gn2TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gn2TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gn4 containers.
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
   Gn4                  *p;
} Gn4Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn4                   value;
} Gn4ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gn4ArrayKeyCell      *p;
} Gn4ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gn4ListItem Gn4ListItem;
struct Gn4ListItem
{
   Gn4ListItem          *next,
                           *prev;
   Gn4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn4ListItem          *head,
                           *tail;
} Gn4List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gn4ListKeyItem Gn4ListKeyItem;
struct Gn4ListKeyItem
{
   Gn4ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gn4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn4ListKeyItem       *head,
                           *tail;
} Gn4ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gn4List            **binArray;
   GhashSize               binCount;
} Gn4Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gn4ListKey         **binArray;
   GhashSize               binCount;
} Gn4HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gn4Tree     Gn4Tree;
typedef struct Gn4TreeItem Gn4TreeItem;
struct Gn4TreeItem
{
   Gn4Tree              *owner;
   Gn4TreeItem          *parent;
   Gn4TreeItem          *childLeft;
   Gn4TreeItem          *childRight;
   GheapN                   heapValue;
   Gn4                   value;
};

struct Gn4Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn4TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gn4TreeKey     Gn4TreeKey;
typedef struct Gn4TreeKeyItem Gn4TreeKeyItem;
struct Gn4TreeKeyItem
{
   Gn4TreeKey           *owner;
   Gn4TreeKeyItem       *parent;
   Gn4TreeKeyItem       *childLeft;
   Gn4TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn4                   value;
};

struct Gn4TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn4TreeKeyItem       *root;
};

#define gn4ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn4ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn4ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn4ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn4ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gn4ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn4ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn4ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn4Array *)         g_ArrayCreate(                                Gn4Array, Gn4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn4ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gn4Array, Gn4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn4ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gn4ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gn4ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn4ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gn4ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gn4ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gn4ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn4ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gn4ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gn4ArrayGet(                ARRAY)                                             (Gn4 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gn4ArrayGetAt(              ARRAY, INDEX)                                      (Gn4 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gn4ArrayGetBegin(           ARRAY)                                             (Gn4 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gn4ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gn4ArrayGetEnd(             ARRAY)                                             (Gn4 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gn4ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gn4ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gn4ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gn4ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gn4ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gn4ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn4ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gn4ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn4ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn4ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn4ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn4ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn4ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn4Array *)         g_ArrayKeyCreate(                 Gn4Array, Gn4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn4ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gn4Array, Gn4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn4ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gn4ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn4ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gn4ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gn4ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gn4 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gn4ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gn4ArrayKeyGetBegin(        ARRAY)                                             (Gn4 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyGetEnd(          ARRAY)                                             (Gn4 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gn4ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gn4ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gn4ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn4ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gn4ListAdd(                 LIST, VALUE)                                       (Gn4ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gn4ListAddBegin(            LIST, VALUE)                                       (Gn4ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gn4ListAddEnd(              LIST, VALUE)                                       (Gn4ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gn4ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gn4List *)          g_ListCreate(                               Gn4List, Gn4, OPTIONAL_COMPARE_FUNC)
#define gn4ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gn4List, Gn4, OPTIONAL_COMPARE_FUNC)
#define gn4ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gn4ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gn4ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gn4ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gn4ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gn4ListFind(                LIST, VALUE)                                       (Gn4ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gn4ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gn4ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gn4ListGetBegin(            LIST)                                              (Gn4ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gn4ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gn4ListGetEnd(              LIST)                                              (Gn4ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gn4ListItemAdd(             LIST, LITEM, VALUE)                                (Gn4ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gn4ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gn4ListItemGet(                   LITEM)                                       (Gn4 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gn4ListItemGetNext(               LITEM)                                       (Gn4ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gn4ListItemGetPrev(               LITEM)                                       (Gn4ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gn4ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gn4ListKeyAdd(              LIST, KEY, VALUE)                                  (Gn4ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn4ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gn4ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn4ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gn4ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn4ListKeyCreate(                 COMPARE_FUNC)                                (Gn4List *)          g_ListKeyCreate(                               Gn4ListKey, Gn4, COMPARE_FUNC)
#define gn4ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gn4ListKey, Gn4, COMPARE_FUNC)
#define gn4ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gn4ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gn4ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gn4ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gn4ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gn4ListKeyFind(             LIST, KEY)                                         (Gn4ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gn4ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gn4ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gn4ListKeyGetBegin(         LIST)                                              (Gn4ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gn4ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gn4ListKeyGetEnd(           LIST)                                              (Gn4ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gn4ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gn4ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gn4ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gn4ListKeyItemGet(                LITEM)                                       (Gn4 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gn4ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gn4ListKeyItemGetNext(            LITEM)                                       (Gn4ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gn4ListKeyItemGetPrev(            LITEM)                                       (Gn4ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gn4ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gn4ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gn4HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gn4HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gn4Hash *)          g_HashCreate(                               Gn4Hash, Gn4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn4HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gn4Hash, Gn4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn4HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gn4HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gn4HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gn4HashFind(                HASH, VALUE)                                       (Gn4 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gn4HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gn4HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gn4HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gn4HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gn4HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gn4HashKeyCreate(                 HASHSIZE)                                    (Gn4HashKey *)       g_HashKeyCreate(                               Gn4HashKey, Gn4, HASHSIZE)
#define gn4HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gn4HashKey, Gn4, HASHSIZE)
#define gn4HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gn4HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gn4HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gn4HashKeyFind(             HASH, KEY)                                         (Gn4 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gn4HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gn4HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gn4HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gn4HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gn4TreeAdd(                 TREE, VALUE)                                       (Gn4TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gn4TreeCreate(                    COMPARE_FUNC)                                (Gn4Tree *)          g_TreeCreate(                    Gn4Tree, Gn4, COMPARE_FUNC)
#define gn4TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gn4Tree, Gn4, COMPARE_FUNC)
#define gn4TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gn4TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gn4TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gn4TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gn4TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gn4TreeFind(                TREE, VALUE)                                       (Gn4TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gn4TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gn4TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gn4TreeGetBegin(            TREE)                                              (Gn4TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gn4TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gn4TreeGetEnd(              TREE)                                              (Gn4TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gn4TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gn4TreeItemGet(                   TITEM)                                       (Gn4 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gn4TreeItemGetNext(               TITEM)                                       (Gn4TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gn4TreeItemGetPrev(               TITEM)                                       (Gn4TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gn4TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gn4TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gn4TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gn4TreeKeyCreate(                 COMPARE_FUNC)                                (Gn4TreeKey *)       g_TreeKeyCreate(                 Gn4TreeKey, Gn4, COMPARE_FUNC)
#define gn4TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gn4TreeKey, Gn4, COMPARE_FUNC)
#define gn4TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gn4TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gn4TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gn4TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gn4TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gn4TreeKeyFind(             TREE, KEY)                                         (Gn4TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gn4TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gn4TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gn4TreeKeyGetBegin(         TREE)                                              (Gn4TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gn4TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gn4TreeKeyGetEnd(           TREE)                                              (Gn4TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gn4TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gn4TreeKeyItemGet(                TITEM)                                       (Gn4 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gn4TreeKeyItemGetNext(            TITEM)                                       (Gn4TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gn4TreeKeyItemGetPrev(            TITEM)                                       (Gn4TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gn4TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gn8 containers.
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
   Gn8                  *p;
} Gn8Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn8                   value;
} Gn8ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gn8ArrayKeyCell      *p;
} Gn8ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gn8ListItem Gn8ListItem;
struct Gn8ListItem
{
   Gn8ListItem          *next,
                           *prev;
   Gn8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn8ListItem          *head,
                           *tail;
} Gn8List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gn8ListKeyItem Gn8ListKeyItem;
struct Gn8ListKeyItem
{
   Gn8ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gn8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gn8ListKeyItem       *head,
                           *tail;
} Gn8ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gn8List            **binArray;
   GhashSize               binCount;
} Gn8Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gn8ListKey         **binArray;
   GhashSize               binCount;
} Gn8HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gn8Tree     Gn8Tree;
typedef struct Gn8TreeItem Gn8TreeItem;
struct Gn8TreeItem
{
   Gn8Tree              *owner;
   Gn8TreeItem          *parent;
   Gn8TreeItem          *childLeft;
   Gn8TreeItem          *childRight;
   GheapN                   heapValue;
   Gn8                   value;
};

struct Gn8Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn8TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gn8TreeKey     Gn8TreeKey;
typedef struct Gn8TreeKeyItem Gn8TreeKeyItem;
struct Gn8TreeKeyItem
{
   Gn8TreeKey           *owner;
   Gn8TreeKeyItem       *parent;
   Gn8TreeKeyItem       *childLeft;
   Gn8TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn8                   value;
};

struct Gn8TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gn8TreeKeyItem       *root;
};

#define gn8ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn8ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn8ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn8ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn8ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gn8ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn8ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn8ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn8Array *)         g_ArrayCreate(                                Gn8Array, Gn8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn8ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gn8Array, Gn8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn8ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gn8ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gn8ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn8ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gn8ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gn8ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gn8ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn8ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gn8ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gn8ArrayGet(                ARRAY)                                             (Gn8 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gn8ArrayGetAt(              ARRAY, INDEX)                                      (Gn8 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gn8ArrayGetBegin(           ARRAY)                                             (Gn8 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gn8ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gn8ArrayGetEnd(             ARRAY)                                             (Gn8 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gn8ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gn8ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gn8ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gn8ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gn8ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gn8ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn8ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gn8ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn8ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gn8ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn8ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn8ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn8ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn8Array *)         g_ArrayKeyCreate(                 Gn8Array, Gn8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn8ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gn8Array, Gn8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gn8ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gn8ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gn8ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gn8ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gn8ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gn8 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gn8ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gn8ArrayKeyGetBegin(        ARRAY)                                             (Gn8 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyGetEnd(          ARRAY)                                             (Gn8 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gn8ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gn8ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gn8ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn8ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gn8ListAdd(                 LIST, VALUE)                                       (Gn8ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gn8ListAddBegin(            LIST, VALUE)                                       (Gn8ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gn8ListAddEnd(              LIST, VALUE)                                       (Gn8ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gn8ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gn8List *)          g_ListCreate(                               Gn8List, Gn8, OPTIONAL_COMPARE_FUNC)
#define gn8ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gn8List, Gn8, OPTIONAL_COMPARE_FUNC)
#define gn8ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gn8ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gn8ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gn8ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gn8ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gn8ListFind(                LIST, VALUE)                                       (Gn8ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gn8ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gn8ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gn8ListGetBegin(            LIST)                                              (Gn8ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gn8ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gn8ListGetEnd(              LIST)                                              (Gn8ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gn8ListItemAdd(             LIST, LITEM, VALUE)                                (Gn8ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gn8ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gn8ListItemGet(                   LITEM)                                       (Gn8 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gn8ListItemGetNext(               LITEM)                                       (Gn8ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gn8ListItemGetPrev(               LITEM)                                       (Gn8ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gn8ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gn8ListKeyAdd(              LIST, KEY, VALUE)                                  (Gn8ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn8ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gn8ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn8ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gn8ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gn8ListKeyCreate(                 COMPARE_FUNC)                                (Gn8List *)          g_ListKeyCreate(                               Gn8ListKey, Gn8, COMPARE_FUNC)
#define gn8ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gn8ListKey, Gn8, COMPARE_FUNC)
#define gn8ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gn8ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gn8ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gn8ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gn8ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gn8ListKeyFind(             LIST, KEY)                                         (Gn8ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gn8ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gn8ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gn8ListKeyGetBegin(         LIST)                                              (Gn8ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gn8ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gn8ListKeyGetEnd(           LIST)                                              (Gn8ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gn8ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gn8ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gn8ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gn8ListKeyItemGet(                LITEM)                                       (Gn8 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gn8ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gn8ListKeyItemGetNext(            LITEM)                                       (Gn8ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gn8ListKeyItemGetPrev(            LITEM)                                       (Gn8ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gn8ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gn8ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gn8HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gn8HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gn8Hash *)          g_HashCreate(                               Gn8Hash, Gn8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn8HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gn8Hash, Gn8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gn8HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gn8HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gn8HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gn8HashFind(                HASH, VALUE)                                       (Gn8 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gn8HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gn8HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gn8HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gn8HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gn8HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gn8HashKeyCreate(                 HASHSIZE)                                    (Gn8HashKey *)       g_HashKeyCreate(                               Gn8HashKey, Gn8, HASHSIZE)
#define gn8HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gn8HashKey, Gn8, HASHSIZE)
#define gn8HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gn8HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gn8HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gn8HashKeyFind(             HASH, KEY)                                         (Gn8 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gn8HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gn8HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gn8HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gn8HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gn8TreeAdd(                 TREE, VALUE)                                       (Gn8TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gn8TreeCreate(                    COMPARE_FUNC)                                (Gn8Tree *)          g_TreeCreate(                    Gn8Tree, Gn8, COMPARE_FUNC)
#define gn8TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gn8Tree, Gn8, COMPARE_FUNC)
#define gn8TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gn8TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gn8TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gn8TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gn8TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gn8TreeFind(                TREE, VALUE)                                       (Gn8TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gn8TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gn8TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gn8TreeGetBegin(            TREE)                                              (Gn8TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gn8TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gn8TreeGetEnd(              TREE)                                              (Gn8TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gn8TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gn8TreeItemGet(                   TITEM)                                       (Gn8 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gn8TreeItemGetNext(               TITEM)                                       (Gn8TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gn8TreeItemGetPrev(               TITEM)                                       (Gn8TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gn8TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gn8TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gn8TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gn8TreeKeyCreate(                 COMPARE_FUNC)                                (Gn8TreeKey *)       g_TreeKeyCreate(                 Gn8TreeKey, Gn8, COMPARE_FUNC)
#define gn8TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gn8TreeKey, Gn8, COMPARE_FUNC)
#define gn8TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gn8TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gn8TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gn8TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gn8TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gn8TreeKeyFind(             TREE, KEY)                                         (Gn8TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gn8TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gn8TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gn8TreeKeyGetBegin(         TREE)                                              (Gn8TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gn8TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gn8TreeKeyGetEnd(           TREE)                                              (Gn8TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gn8TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gn8TreeKeyItemGet(                TITEM)                                       (Gn8 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gn8TreeKeyItemGetNext(            TITEM)                                       (Gn8TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gn8TreeKeyItemGetPrev(            TITEM)                                       (Gn8TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gn8TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif

