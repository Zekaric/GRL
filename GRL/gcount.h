/******************************************************************************
file:       Gcount
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

#if !defined(GCOUNTH)
#define      GCOUNTH

/******************************************************************************
Gcount containers.
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
   Gcount                  *p;
} GcountArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gcount                   value;
} GcountArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GcountArrayKeyCell      *p;
} GcountArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GcountListItem GcountListItem;
struct GcountListItem
{
   GcountListItem          *next,
                           *prev;
   Gcount                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GcountListItem          *head,
                           *tail;
} GcountList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GcountListKeyItem GcountListKeyItem;
struct GcountListKeyItem
{
   GcountListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gcount                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GcountListKeyItem       *head,
                           *tail;
} GcountListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GcountList            **binArray;
   GhashSize               binCount;
} GcountHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GcountListKey         **binArray;
   GhashSize               binCount;
} GcountHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GcountTree     GcountTree;
typedef struct GcountTreeItem GcountTreeItem;
struct GcountTreeItem
{
   GcountTree              *owner;
   GcountTreeItem          *parent;
   GcountTreeItem          *childLeft;
   GcountTreeItem          *childRight;
   GheapN                   heapValue;
   Gcount                   value;
};

struct GcountTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GcountTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GcountTreeKey     GcountTreeKey;
typedef struct GcountTreeKeyItem GcountTreeKeyItem;
struct GcountTreeKeyItem
{
   GcountTreeKey           *owner;
   GcountTreeKeyItem       *parent;
   GcountTreeKeyItem       *childLeft;
   GcountTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gcount                   value;
};

struct GcountTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GcountTreeKeyItem       *root;
};

#define gcountArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gcountArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gcountArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gcountArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gcountArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gcountArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gcountArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gcountArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GcountArray *)         g_ArrayCreate(                                GcountArray, Gcount, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gcountArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, GcountArray, Gcount, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gcountArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gcountArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gcountArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gcountArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gcountArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gcountArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gcountArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gcountArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gcountArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gcountArrayGet(                ARRAY)                                             (Gcount *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gcountArrayGetAt(              ARRAY, INDEX)                                      (Gcount *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gcountArrayGetBegin(           ARRAY)                                             (Gcount *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gcountArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gcountArrayGetEnd(             ARRAY)                                             (Gcount *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gcountArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gcountArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gcountArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gcountArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gcountArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gcountArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gcountArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gcountArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gcountArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gcountArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gcountArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gcountArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gcountArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GcountArray *)         g_ArrayKeyCreate(                 GcountArray, Gcount, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gcountArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GcountArray, Gcount, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gcountArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gcountArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gcountArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gcountArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gcountArrayKeyGetAt(           ARRAY, INDEX)                                      (Gcount *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gcountArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gcountArrayKeyGetBegin(        ARRAY)                                             (Gcount *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyGetEnd(          ARRAY)                                             (Gcount *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gcountArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gcountArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gcountArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gcountArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gcountArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gcountArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gcountListAdd(                 LIST, VALUE)                                       (GcountListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gcountListAddBegin(            LIST, VALUE)                                       (GcountListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gcountListAddEnd(              LIST, VALUE)                                       (GcountListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gcountListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GcountList *)          g_ListCreate(                               GcountList, Gcount, OPTIONAL_COMPARE_FUNC)
#define gcountListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, GcountList, Gcount, OPTIONAL_COMPARE_FUNC)
#define gcountListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gcountListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gcountListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gcountListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gcountListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gcountListFind(                LIST, VALUE)                                       (GcountListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gcountListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gcountListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gcountListGetBegin(            LIST)                                              (GcountListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gcountListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gcountListGetEnd(              LIST)                                              (GcountListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gcountListItemAdd(             LIST, LITEM, VALUE)                                (GcountListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gcountListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gcountListItemGet(                   LITEM)                                       (Gcount *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gcountListItemGetNext(               LITEM)                                       (GcountListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gcountListItemGetPrev(               LITEM)                                       (GcountListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gcountListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gcountListKeyAdd(              LIST, KEY, VALUE)                                  (GcountListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gcountListKeyAddBegin(         LIST, KEY, VALUE)                                  (GcountListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gcountListKeyAddEnd(           LIST, KEY, VALUE)                                  (GcountListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gcountListKeyCreate(                 COMPARE_FUNC)                                (GcountList *)          g_ListKeyCreate(                               GcountListKey, Gcount, COMPARE_FUNC)
#define gcountListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, GcountListKey, Gcount, COMPARE_FUNC)
#define gcountListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gcountListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gcountListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gcountListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gcountListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gcountListKeyFind(             LIST, KEY)                                         (GcountListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gcountListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gcountListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gcountListKeyGetBegin(         LIST)                                              (GcountListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gcountListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gcountListKeyGetEnd(           LIST)                                              (GcountListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gcountListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GcountListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gcountListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gcountListKeyItemGet(                LITEM)                                       (Gcount *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gcountListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gcountListKeyItemGetNext(            LITEM)                                       (GcountListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gcountListKeyItemGetPrev(            LITEM)                                       (GcountListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gcountListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gcountListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gcountHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gcountHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GcountHash *)          g_HashCreate(                               GcountHash, Gcount, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gcountHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, GcountHash, Gcount, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gcountHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gcountHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gcountHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gcountHashFind(                HASH, VALUE)                                       (Gcount *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gcountHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gcountHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gcountHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gcountHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gcountHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gcountHashKeyCreate(                 HASHSIZE)                                    (GcountHashKey *)       g_HashKeyCreate(                               GcountHashKey, Gcount, HASHSIZE)
#define gcountHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, GcountHashKey, Gcount, HASHSIZE)
#define gcountHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gcountHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gcountHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gcountHashKeyFind(             HASH, KEY)                                         (Gcount *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gcountHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gcountHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gcountHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gcountHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gcountTreeAdd(                 TREE, VALUE)                                       (GcountTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gcountTreeCreate(                    COMPARE_FUNC)                                (GcountTree *)          g_TreeCreate(                    GcountTree, Gcount, COMPARE_FUNC)
#define gcountTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, GcountTree, Gcount, COMPARE_FUNC)
#define gcountTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gcountTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gcountTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gcountTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gcountTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gcountTreeFind(                TREE, VALUE)                                       (GcountTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gcountTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gcountTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gcountTreeGetBegin(            TREE)                                              (GcountTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gcountTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gcountTreeGetEnd(              TREE)                                              (GcountTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gcountTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gcountTreeItemGet(                   TITEM)                                       (Gcount *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gcountTreeItemGetNext(               TITEM)                                       (GcountTreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gcountTreeItemGetPrev(               TITEM)                                       (GcountTreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gcountTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gcountTreeKeyAdd(              TREE, KEY, VALUE)                                  (GcountTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gcountTreeKeyCreate(                 COMPARE_FUNC)                                (GcountTreeKey *)       g_TreeKeyCreate(                 GcountTreeKey, Gcount, COMPARE_FUNC)
#define gcountTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GcountTreeKey, Gcount, COMPARE_FUNC)
#define gcountTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gcountTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gcountTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gcountTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gcountTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gcountTreeKeyFind(             TREE, KEY)                                         (GcountTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gcountTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gcountTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gcountTreeKeyGetBegin(         TREE)                                              (GcountTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gcountTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gcountTreeKeyGetEnd(           TREE)                                              (GcountTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gcountTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gcountTreeKeyItemGet(                TITEM)                                       (Gcount *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gcountTreeKeyItemGetNext(            TITEM)                                       (GcountTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gcountTreeKeyItemGetPrev(            TITEM)                                       (GcountTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gcountTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
