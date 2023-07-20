/******************************************************************************
file:       Gb
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

#if !defined(GBH)
#define      GBH

/******************************************************************************
Gb containers.
******************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gb                  *p;
} GbArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gb                   value;
} GbArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GbArrayKeyCell      *p;
} GbArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GbListItem GbListItem;
struct GbListItem
{
   GbListItem          *next,
                           *prev;
   Gb                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GbListItem          *head,
                           *tail;
} GbList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GbListKeyItem GbListKeyItem;
struct GbListKeyItem
{
   GbListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gb                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GbListKeyItem       *head,
                           *tail;
} GbListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GbList            **binArray;
   GhashSize               binCount;
} GbHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GbListKey         **binArray;
   GhashSize               binCount;
} GbHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GbTree     GbTree;
typedef struct GbTreeItem GbTreeItem;
struct GbTreeItem
{
   GbTree              *owner;
   GbTreeItem          *parent;
   GbTreeItem          *childLeft;
   GbTreeItem          *childRight;
   GheapN                   heapValue;
   Gb                   value;
};

struct GbTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GbTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GbTreeKey     GbTreeKey;
typedef struct GbTreeKeyItem GbTreeKeyItem;
struct GbTreeKeyItem
{
   GbTreeKey           *owner;
   GbTreeKeyItem       *parent;
   GbTreeKeyItem       *childLeft;
   GbTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gb                   value;
};

struct GbTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GbTreeKeyItem       *root;
};

#define gbArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gbArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gbArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gbArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gbArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gbArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gbArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gbArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GbArray *)             g_ArrayCreate(                                "GbArray", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gbArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GbArray", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gbArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gbArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gbArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gbArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gbArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gbArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gbArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gbArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gbArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gbArrayGet(                ARRAY)                                            ((Gb *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gbArrayGetAt(              ARRAY, INDEX)                                     ((Gb *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gbArrayGetBegin(           ARRAY)                                            ((Gb *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gbArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gbArrayGetEnd(             ARRAY)                                            ((Gb *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gbArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gbArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gbArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gbArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gbArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gbArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gbArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gbArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gbArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gbArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gbArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gbArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gbArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GbArray *)             g_ArrayKeyCreate(                                "GbArrayKey", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gbArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GbArrayKey", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gbArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gbArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gbArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gbArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gbArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gbArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gbArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gbArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gbArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gbArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gb *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gbArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gbArrayKeyGetBegin(        ARRAY)                                            ((Gb *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gbArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gbArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gbArrayKeyGetEnd(          ARRAY)                                            ((Gb *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gbArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gbArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gbArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gbArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gbArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gbArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gbArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gbListAdd(                 LIST, VALUE)                                       (GbListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gbListAddBegin(            LIST, VALUE)                                       (GbListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gbListAddEnd(              LIST, VALUE)                                       (GbListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gbListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GbList *)              g_ListCreate(                               "GbList", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gbListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GbList", Gb, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gbListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gbListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gbListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gbListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gbListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gbListFind(                LIST, VALUE)                                       (GbListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gbListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gbListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gbListGetBegin(            LIST)                                              (GbListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gbListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gbListGetEnd(              LIST)                                              (GbListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gbListItemAdd(             LIST, LITEM, VALUE)                                (GbListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gbListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gbListItemGet(                   LITEM)                                      ((Gb *)                  g_ListItemGet(             (G_List *) LIST, (G_ListItem *) LITEM))
#define gbListItemGetNext(               LITEM)                                       (GbListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gbListItemGetPrev(               LITEM)                                       (GbListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gbListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gbListKeyAdd(              LIST, KEY, VALUE)                                  (GbListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gbListKeyAddBegin(         LIST, KEY, VALUE)                                  (GbListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gbListKeyAddEnd(           LIST, KEY, VALUE)                                  (GbListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gbListKeyCreate(                 COMPARE_FUNC)                                (GbList *)              g_ListKeyCreate(                               "GbListKey", Gb, gbFALSE, COMPARE_FUNC)
#define gbListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GbListKey", Gb, gbFALSE, COMPARE_FUNC)
#define gbListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gbListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gbListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gbListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gbListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gbListKeyFind(             LIST, KEY)                                         (GbListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gbListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gbListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gbListKeyGetBegin(         LIST)                                              (GbListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gbListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gbListKeyGetEnd(           LIST)                                              (GbListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gbListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GbListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gbListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gbListKeyItemGet(                LITEM)                                      ((Gb *)                  g_ListKeyItemGet(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM))
#define gbListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gbListKeyItemGetNext(            LITEM)                                       (GbListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gbListKeyItemGetPrev(            LITEM)                                       (GbListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gbListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gbListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gbHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gbHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GbHash *)              g_HashCreate(                               "GbHash", Gb, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gbHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GbHash", Gb, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gbHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gbHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gbHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gbHashFind(                HASH, VALUE)                                      ((Gb *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gbHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gbHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gbHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gbHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gbHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gbHashKeyCreate(                 HASHSIZE)                                    (GbHashKey *)           g_HashKeyCreate(                               "GbHashKey", Gb, gbFALSE, HASHSIZE)
#define gbHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GbHashKey", Gb, gbFALSE, HASHSIZE)
#define gbHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gbHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gbHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gbHashKeyFind(             HASH, KEY)                                        ((Gb *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gbHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gbHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gbHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gbHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gbTreeAdd(                 TREE, VALUE)                                       (GbTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gbTreeCreate(                    COMPARE_FUNC)                                (GbTree *)              g_TreeCreate(                               "GbTree", Gb, gbFALSE, COMPARE_FUNC)
#define gbTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GbTree", Gb, gbFALSE, COMPARE_FUNC)
#define gbTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gbTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gbTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gbTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gbTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gbTreeFind(                TREE, VALUE)                                       (GbTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gbTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gbTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gbTreeGetBegin(            TREE)                                              (GbTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gbTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gbTreeGetEnd(              TREE)                                              (GbTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gbTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gbTreeItemGet(                   TITEM)                                      ((Gb *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gbTreeItemGetNext(               TITEM)                                       (GbTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gbTreeItemGetPrev(               TITEM)                                       (GbTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gbTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gbTreeKeyAdd(              TREE, KEY, VALUE)                                  (GbTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gbTreeKeyCreate(                 COMPARE_FUNC)                                (GbTreeKey *)           g_TreeKeyCreate(                               "GbTreeKey", Gb, gbFALSE, COMPARE_FUNC)
#define gbTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GbTreeKey", Gb, gbFALSE, COMPARE_FUNC)
#define gbTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gbTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gbTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gbTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gbTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gbTreeKeyFind(             TREE, KEY)                                         (GbTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gbTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gbTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gbTreeKeyGetBegin(         TREE)                                              (GbTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gbTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gbTreeKeyGetEnd(           TREE)                                              (GbTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gbTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gbTreeKeyItemGet(                TITEM)                                      ((Gb *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gbTreeKeyItemGetNext(            TITEM)                                       (GbTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gbTreeKeyItemGetPrev(            TITEM)                                       (GbTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gbTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
