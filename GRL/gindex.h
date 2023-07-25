/******************************************************************************
file:       Gindex
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

#if !defined(GINDEXH)
#define      GINDEXH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gcompare gindexCompare(Gindex const * const indexA, Gindex const * const indexB);

/******************************************************************************
Gindex containers.
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
   Gindex                  *p;
} GindexArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gindex                   value;
} GindexArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GindexArrayKeyCell      *p;
} GindexArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GindexListItem GindexListItem;
struct GindexListItem
{
   GindexListItem          *next,
                           *prev;
   Gindex                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GindexListItem          *head,
                           *tail;
} GindexList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GindexListKeyItem GindexListKeyItem;
struct GindexListKeyItem
{
   GindexListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gindex                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GindexListKeyItem       *head,
                           *tail;
} GindexListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GindexList            **binArray;
   GhashSize               binCount;
} GindexHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GindexListKey         **binArray;
   GhashSize               binCount;
} GindexHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GindexTree     GindexTree;
typedef struct GindexTreeItem GindexTreeItem;
struct GindexTreeItem
{
   GindexTree              *owner;
   GindexTreeItem          *parent;
   GindexTreeItem          *childLeft;
   GindexTreeItem          *childRight;
   GheapN                   heapValue;
   Gindex                   value;
};

struct GindexTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GindexTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GindexTreeKey     GindexTreeKey;
typedef struct GindexTreeKeyItem GindexTreeKeyItem;
struct GindexTreeKeyItem
{
   GindexTreeKey           *owner;
   GindexTreeKeyItem       *parent;
   GindexTreeKeyItem       *childLeft;
   GindexTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gindex                   value;
};

struct GindexTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GindexTreeKeyItem       *root;
};

#define gindexArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gindexArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gindexArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gindexArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gindexArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gindexArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gindexArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gindexArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GindexArray *)         g_ArrayCreate(                                "GindexArray", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gindexArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GindexArray", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gindexArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gindexArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gindexArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gindexArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gindexArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gindexArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gindexArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gindexArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gindexArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gindexArrayGet(                ARRAY)                                            ((Gindex *)              g_ArrayGet(                (G_Array *) ARRAY))
#define gindexArrayGetAt(              ARRAY, INDEX)                                     ((Gindex *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gindexArrayGetBegin(           ARRAY)                                            ((Gindex *)              g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gindexArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gindexArrayGetEnd(             ARRAY)                                            ((Gindex *)              g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gindexArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gindexArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gindexArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gindexArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gindexArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gindexArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gindexArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gindexArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gindexArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gindexArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gindexArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gindexArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gindexArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GindexArray *)         g_ArrayKeyCreate(                                "GindexArrayKey", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gindexArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GindexArrayKey", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gindexArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gindexArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gindexArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gindexArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gindexArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gindex *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gindexArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gindexArrayKeyGetBegin(        ARRAY)                                            ((Gindex *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gindexArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyGetEnd(          ARRAY)                                            ((Gindex *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gindexArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gindexArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gindexArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gindexArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gindexArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gindexArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gindexArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gindexListAdd(                 LIST, VALUE)                                       (GindexListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gindexListAddBegin(            LIST, VALUE)                                       (GindexListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gindexListAddEnd(              LIST, VALUE)                                       (GindexListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gindexListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GindexList *)          g_ListCreate(                               "GindexList", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gindexListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GindexList", Gindex, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gindexListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gindexListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gindexListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gindexListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gindexListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gindexListFind(                LIST, VALUE)                                       (GindexListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gindexListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gindexListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gindexListGetBegin(            LIST)                                              (GindexListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gindexListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gindexListGetEnd(              LIST)                                              (GindexListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gindexListItemAdd(             LIST, LITEM, VALUE)                                (GindexListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gindexListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gindexListItemGet(                   LITEM)                                      ((Gindex *)              g_ListItemGet(                              (G_ListItem *) LITEM))
#define gindexListItemGetNext(               LITEM)                                       (GindexListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gindexListItemGetPrev(               LITEM)                                       (GindexListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gindexListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gindexListKeyAdd(              LIST, KEY, VALUE)                                  (GindexListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gindexListKeyAddBegin(         LIST, KEY, VALUE)                                  (GindexListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gindexListKeyAddEnd(           LIST, KEY, VALUE)                                  (GindexListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gindexListKeyCreate(                 COMPARE_FUNC)                                (GindexList *)          g_ListKeyCreate(                               "GindexListKey", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GindexListKey", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gindexListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gindexListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gindexListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gindexListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gindexListKeyFind(             LIST, KEY)                                         (GindexListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gindexListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gindexListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gindexListKeyGetBegin(         LIST)                                              (GindexListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gindexListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gindexListKeyGetEnd(           LIST)                                              (GindexListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gindexListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GindexListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gindexListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gindexListKeyItemGet(                LITEM)                                      ((Gindex *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gindexListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gindexListKeyItemGetNext(            LITEM)                                       (GindexListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gindexListKeyItemGetPrev(            LITEM)                                       (GindexListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gindexListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gindexListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gindexHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gindexHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GindexHash *)          g_HashCreate(                               "GindexHash", Gindex, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gindexHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GindexHash", Gindex, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gindexHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gindexHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gindexHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gindexHashFind(                HASH, VALUE)                                      ((Gindex *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gindexHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gindexHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gindexHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gindexHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gindexHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gindexHashKeyCreate(                 HASHSIZE)                                    (GindexHashKey *)       g_HashKeyCreate(                               "GindexHashKey", Gindex, gbFALSE, HASHSIZE)
#define gindexHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GindexHashKey", Gindex, gbFALSE, HASHSIZE)
#define gindexHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gindexHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gindexHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gindexHashKeyFind(             HASH, KEY)                                        ((Gindex *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gindexHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gindexHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gindexHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gindexHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gindexTreeAdd(                 TREE, VALUE)                                       (GindexTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gindexTreeCreate(                    COMPARE_FUNC)                                (GindexTree *)          g_TreeCreate(                               "GindexTree", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GindexTree", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gindexTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gindexTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gindexTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gindexTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gindexTreeFind(                TREE, VALUE)                                       (GindexTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gindexTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gindexTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gindexTreeGetBegin(            TREE)                                              (GindexTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gindexTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gindexTreeGetEnd(              TREE)                                              (GindexTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gindexTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gindexTreeItemGet(                   TITEM)                                      ((Gindex *)              g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gindexTreeItemGetNext(               TITEM)                                       (GindexTreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gindexTreeItemGetPrev(               TITEM)                                       (GindexTreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gindexTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gindexTreeKeyAdd(              TREE, KEY, VALUE)                                  (GindexTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gindexTreeKeyCreate(                 COMPARE_FUNC)                                (GindexTreeKey *)       g_TreeKeyCreate(                               "GindexTreeKey", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GindexTreeKey", Gindex, gbFALSE, COMPARE_FUNC)
#define gindexTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gindexTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gindexTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gindexTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gindexTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gindexTreeKeyFind(             TREE, KEY)                                         (GindexTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gindexTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gindexTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gindexTreeKeyGetBegin(         TREE)                                              (GindexTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gindexTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gindexTreeKeyGetEnd(           TREE)                                              (GindexTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gindexTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gindexTreeKeyItemGet(                TITEM)                                      ((Gindex *)              g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gindexTreeKeyItemGetNext(            TITEM)                                       (GindexTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gindexTreeKeyItemGetPrev(            TITEM)                                       (GindexTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gindexTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
