/******************************************************************************
file:       Gr
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

#if !defined(GRH)
#define      GRH

/******************************************************************************
Gr containers.
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
   Gr                  *p;
} GrArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gr                   value;
} GrArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GrArrayKeyCell      *p;
} GrArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GrListItem GrListItem;
struct GrListItem
{
   GrListItem          *next,
                           *prev;
   Gr                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GrListItem          *head,
                           *tail;
} GrList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GrListKeyItem GrListKeyItem;
struct GrListKeyItem
{
   GrListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gr                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GrListKeyItem       *head,
                           *tail;
} GrListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GrList            **binArray;
   GhashSize               binCount;
} GrHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrListKey         **binArray;
   GhashSize               binCount;
} GrHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GrTree     GrTree;
typedef struct GrTreeItem GrTreeItem;
struct GrTreeItem
{
   GrTree              *owner;
   GrTreeItem          *parent;
   GrTreeItem          *childLeft;
   GrTreeItem          *childRight;
   GheapN                   heapValue;
   Gr                   value;
};

struct GrTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GrTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GrTreeKey     GrTreeKey;
typedef struct GrTreeKeyItem GrTreeKeyItem;
struct GrTreeKeyItem
{
   GrTreeKey           *owner;
   GrTreeKeyItem       *parent;
   GrTreeKeyItem       *childLeft;
   GrTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gr                   value;
};

struct GrTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GrTreeKeyItem       *root;
};

#define grArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define grArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define grArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define grArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define grArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GrArray *)         g_ArrayCreate(                                GrArray, Gr, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define grArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, GrArray, Gr, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define grArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define grArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define grArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define grArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define grArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define grArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define grArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define grArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define grArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define grArrayGet(                ARRAY)                                             (Gr *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define grArrayGetAt(              ARRAY, INDEX)                                      (Gr *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define grArrayGetBegin(           ARRAY)                                             (Gr *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define grArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define grArrayGetEnd(             ARRAY)                                             (Gr *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define grArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define grArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define grArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define grArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define grArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define grArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define grArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define grArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define grArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define grArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define grArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define grArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define grArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GrArray *)         g_ArrayKeyCreate(                 GrArray, Gr, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define grArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GrArray, Gr, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define grArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define grArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define grArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define grArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define grArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define grArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define grArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define grArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define grArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define grArrayKeyGetAt(           ARRAY, INDEX)                                      (Gr *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define grArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define grArrayKeyGetBegin(        ARRAY)                                             (Gr *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetEnd(          ARRAY)                                             (Gr *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define grArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define grArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define grArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define grArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define grArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define grListAdd(                 LIST, VALUE)                                       (GrListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define grListAddBegin(            LIST, VALUE)                                       (GrListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define grListAddEnd(              LIST, VALUE)                                       (GrListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define grListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GrList *)          g_ListCreate(                               GrList, Gr, OPTIONAL_COMPARE_FUNC)
#define grListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, GrList, Gr, OPTIONAL_COMPARE_FUNC)
#define grListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define grListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define grListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define grListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define grListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define grListFind(                LIST, VALUE)                                       (GrListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define grListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define grListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define grListGetBegin(            LIST)                                              (GrListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define grListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define grListGetEnd(              LIST)                                              (GrListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define grListItemAdd(             LIST, LITEM, VALUE)                                (GrListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define grListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define grListItemGet(                   LITEM)                                       (Gr *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define grListItemGetNext(               LITEM)                                       (GrListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define grListItemGetPrev(               LITEM)                                       (GrListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define grListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define grListKeyAdd(              LIST, KEY, VALUE)                                  (GrListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyAddBegin(         LIST, KEY, VALUE)                                  (GrListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyAddEnd(           LIST, KEY, VALUE)                                  (GrListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyCreate(                 COMPARE_FUNC)                                (GrList *)          g_ListKeyCreate(                               GrListKey, Gr, COMPARE_FUNC)
#define grListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, GrListKey, Gr, COMPARE_FUNC)
#define grListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define grListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define grListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define grListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define grListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define grListKeyFind(             LIST, KEY)                                         (GrListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define grListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define grListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define grListKeyGetBegin(         LIST)                                              (GrListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define grListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define grListKeyGetEnd(           LIST)                                              (GrListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define grListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GrListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define grListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define grListKeyItemGet(                LITEM)                                       (Gr *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define grListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define grListKeyItemGetNext(            LITEM)                                       (GrListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define grListKeyItemGetPrev(            LITEM)                                       (GrListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define grListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define grListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define grHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define grHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GrHash *)          g_HashCreate(                               GrHash, Gr, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define grHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, GrHash, Gr, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define grHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define grHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define grHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define grHashFind(                HASH, VALUE)                                       (Gr *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define grHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define grHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define grHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define grHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define grHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define grHashKeyCreate(                 HASHSIZE)                                    (GrHashKey *)       g_HashKeyCreate(                               GrHashKey, Gr, HASHSIZE)
#define grHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, GrHashKey, Gr, HASHSIZE)
#define grHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define grHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define grHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define grHashKeyFind(             HASH, KEY)                                         (Gr *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define grHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define grHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define grHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define grHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define grTreeAdd(                 TREE, VALUE)                                       (GrTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeCreate(                    COMPARE_FUNC)                                (GrTree *)          g_TreeCreate(                    GrTree, Gr, COMPARE_FUNC)
#define grTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, GrTree, Gr, COMPARE_FUNC)
#define grTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define grTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define grTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define grTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define grTreeFind(                TREE, VALUE)                                       (GrTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define grTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define grTreeGetBegin(            TREE)                                              (GrTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define grTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define grTreeGetEnd(              TREE)                                              (GrTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define grTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define grTreeItemGet(                   TITEM)                                       (Gr *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define grTreeItemGetNext(               TITEM)                                       (GrTreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define grTreeItemGetPrev(               TITEM)                                       (GrTreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define grTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define grTreeKeyAdd(              TREE, KEY, VALUE)                                  (GrTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define grTreeKeyCreate(                 COMPARE_FUNC)                                (GrTreeKey *)       g_TreeKeyCreate(                 GrTreeKey, Gr, COMPARE_FUNC)
#define grTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GrTreeKey, Gr, COMPARE_FUNC)
#define grTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define grTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define grTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define grTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define grTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define grTreeKeyFind(             TREE, KEY)                                         (GrTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define grTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define grTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define grTreeKeyGetBegin(         TREE)                                              (GrTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define grTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define grTreeKeyGetEnd(           TREE)                                              (GrTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define grTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemGet(                TITEM)                                       (Gr *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemGetNext(            TITEM)                                       (GrTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemGetPrev(            TITEM)                                       (GrTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gr4 containers.
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
   Gr4                  *p;
} Gr4Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gr4                   value;
} Gr4ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gr4ArrayKeyCell      *p;
} Gr4ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gr4ListItem Gr4ListItem;
struct Gr4ListItem
{
   Gr4ListItem          *next,
                           *prev;
   Gr4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gr4ListItem          *head,
                           *tail;
} Gr4List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gr4ListKeyItem Gr4ListKeyItem;
struct Gr4ListKeyItem
{
   Gr4ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gr4                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gr4ListKeyItem       *head,
                           *tail;
} Gr4ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gr4List            **binArray;
   GhashSize               binCount;
} Gr4Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gr4ListKey         **binArray;
   GhashSize               binCount;
} Gr4HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gr4Tree     Gr4Tree;
typedef struct Gr4TreeItem Gr4TreeItem;
struct Gr4TreeItem
{
   Gr4Tree              *owner;
   Gr4TreeItem          *parent;
   Gr4TreeItem          *childLeft;
   Gr4TreeItem          *childRight;
   GheapN                   heapValue;
   Gr4                   value;
};

struct Gr4Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gr4TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gr4TreeKey     Gr4TreeKey;
typedef struct Gr4TreeKeyItem Gr4TreeKeyItem;
struct Gr4TreeKeyItem
{
   Gr4TreeKey           *owner;
   Gr4TreeKeyItem       *parent;
   Gr4TreeKeyItem       *childLeft;
   Gr4TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gr4                   value;
};

struct Gr4TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gr4TreeKeyItem       *root;
};

#define gr4ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr4ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gr4ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr4ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr4ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gr4ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gr4ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gr4ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gr4Array *)         g_ArrayCreate(                                Gr4Array, Gr4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gr4ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gr4Array, Gr4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gr4ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gr4ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gr4ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gr4ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gr4ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gr4ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gr4ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gr4ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gr4ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gr4ArrayGet(                ARRAY)                                             (Gr4 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gr4ArrayGetAt(              ARRAY, INDEX)                                      (Gr4 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gr4ArrayGetBegin(           ARRAY)                                             (Gr4 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gr4ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gr4ArrayGetEnd(             ARRAY)                                             (Gr4 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gr4ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gr4ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gr4ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gr4ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gr4ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gr4ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr4ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gr4ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr4ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr4ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gr4ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gr4ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gr4ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gr4Array *)         g_ArrayKeyCreate(                 Gr4Array, Gr4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gr4ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gr4Array, Gr4, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gr4ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gr4ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gr4ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gr4ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gr4ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gr4 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gr4ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gr4ArrayKeyGetBegin(        ARRAY)                                             (Gr4 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyGetEnd(          ARRAY)                                             (Gr4 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gr4ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gr4ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gr4ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gr4ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gr4ListAdd(                 LIST, VALUE)                                       (Gr4ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gr4ListAddBegin(            LIST, VALUE)                                       (Gr4ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gr4ListAddEnd(              LIST, VALUE)                                       (Gr4ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gr4ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gr4List *)          g_ListCreate(                               Gr4List, Gr4, OPTIONAL_COMPARE_FUNC)
#define gr4ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gr4List, Gr4, OPTIONAL_COMPARE_FUNC)
#define gr4ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gr4ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gr4ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gr4ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gr4ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gr4ListFind(                LIST, VALUE)                                       (Gr4ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gr4ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gr4ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gr4ListGetBegin(            LIST)                                              (Gr4ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gr4ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gr4ListGetEnd(              LIST)                                              (Gr4ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gr4ListItemAdd(             LIST, LITEM, VALUE)                                (Gr4ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gr4ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gr4ListItemGet(                   LITEM)                                       (Gr4 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gr4ListItemGetNext(               LITEM)                                       (Gr4ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gr4ListItemGetPrev(               LITEM)                                       (Gr4ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gr4ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gr4ListKeyAdd(              LIST, KEY, VALUE)                                  (Gr4ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr4ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gr4ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr4ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gr4ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr4ListKeyCreate(                 COMPARE_FUNC)                                (Gr4List *)          g_ListKeyCreate(                               Gr4ListKey, Gr4, COMPARE_FUNC)
#define gr4ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gr4ListKey, Gr4, COMPARE_FUNC)
#define gr4ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gr4ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gr4ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gr4ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gr4ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gr4ListKeyFind(             LIST, KEY)                                         (Gr4ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gr4ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gr4ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gr4ListKeyGetBegin(         LIST)                                              (Gr4ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gr4ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gr4ListKeyGetEnd(           LIST)                                              (Gr4ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gr4ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gr4ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gr4ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gr4ListKeyItemGet(                LITEM)                                       (Gr4 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gr4ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gr4ListKeyItemGetNext(            LITEM)                                       (Gr4ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gr4ListKeyItemGetPrev(            LITEM)                                       (Gr4ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gr4ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gr4ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gr4HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gr4HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gr4Hash *)          g_HashCreate(                               Gr4Hash, Gr4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gr4HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gr4Hash, Gr4, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gr4HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gr4HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gr4HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gr4HashFind(                HASH, VALUE)                                       (Gr4 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gr4HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gr4HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gr4HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gr4HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gr4HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gr4HashKeyCreate(                 HASHSIZE)                                    (Gr4HashKey *)       g_HashKeyCreate(                               Gr4HashKey, Gr4, HASHSIZE)
#define gr4HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gr4HashKey, Gr4, HASHSIZE)
#define gr4HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gr4HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gr4HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gr4HashKeyFind(             HASH, KEY)                                         (Gr4 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gr4HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gr4HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gr4HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gr4HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gr4TreeAdd(                 TREE, VALUE)                                       (Gr4TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gr4TreeCreate(                    COMPARE_FUNC)                                (Gr4Tree *)          g_TreeCreate(                    Gr4Tree, Gr4, COMPARE_FUNC)
#define gr4TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gr4Tree, Gr4, COMPARE_FUNC)
#define gr4TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gr4TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gr4TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gr4TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gr4TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gr4TreeFind(                TREE, VALUE)                                       (Gr4TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gr4TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gr4TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gr4TreeGetBegin(            TREE)                                              (Gr4TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gr4TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gr4TreeGetEnd(              TREE)                                              (Gr4TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gr4TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gr4TreeItemGet(                   TITEM)                                       (Gr4 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gr4TreeItemGetNext(               TITEM)                                       (Gr4TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gr4TreeItemGetPrev(               TITEM)                                       (Gr4TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gr4TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gr4TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gr4TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gr4TreeKeyCreate(                 COMPARE_FUNC)                                (Gr4TreeKey *)       g_TreeKeyCreate(                 Gr4TreeKey, Gr4, COMPARE_FUNC)
#define gr4TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gr4TreeKey, Gr4, COMPARE_FUNC)
#define gr4TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gr4TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gr4TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gr4TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gr4TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gr4TreeKeyFind(             TREE, KEY)                                         (Gr4TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gr4TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gr4TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gr4TreeKeyGetBegin(         TREE)                                              (Gr4TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gr4TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gr4TreeKeyGetEnd(           TREE)                                              (Gr4TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gr4TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gr4TreeKeyItemGet(                TITEM)                                       (Gr4 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gr4TreeKeyItemGetNext(            TITEM)                                       (Gr4TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gr4TreeKeyItemGetPrev(            TITEM)                                       (Gr4TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gr4TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/******************************************************************************
Gr8 containers.
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
   Gr8                  *p;
} Gr8Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gr8                   value;
} Gr8ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gr8ArrayKeyCell      *p;
} Gr8ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gr8ListItem Gr8ListItem;
struct Gr8ListItem
{
   Gr8ListItem          *next,
                           *prev;
   Gr8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gr8ListItem          *head,
                           *tail;
} Gr8List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gr8ListKeyItem Gr8ListKeyItem;
struct Gr8ListKeyItem
{
   Gr8ListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gr8                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gr8ListKeyItem       *head,
                           *tail;
} Gr8ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gr8List            **binArray;
   GhashSize               binCount;
} Gr8Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gr8ListKey         **binArray;
   GhashSize               binCount;
} Gr8HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gr8Tree     Gr8Tree;
typedef struct Gr8TreeItem Gr8TreeItem;
struct Gr8TreeItem
{
   Gr8Tree              *owner;
   Gr8TreeItem          *parent;
   Gr8TreeItem          *childLeft;
   Gr8TreeItem          *childRight;
   GheapN                   heapValue;
   Gr8                   value;
};

struct Gr8Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gr8TreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gr8TreeKey     Gr8TreeKey;
typedef struct Gr8TreeKeyItem Gr8TreeKeyItem;
struct Gr8TreeKeyItem
{
   Gr8TreeKey           *owner;
   Gr8TreeKeyItem       *parent;
   Gr8TreeKeyItem       *childLeft;
   Gr8TreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gr8                   value;
};

struct Gr8TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gr8TreeKeyItem       *root;
};

#define gr8ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr8ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gr8ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr8ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gr8ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gr8ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gr8ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gr8ArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gr8Array *)         g_ArrayCreate(                                Gr8Array, Gr8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gr8ArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, Gr8Array, Gr8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gr8ArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gr8ArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gr8ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gr8ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gr8ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gr8ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gr8ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gr8ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gr8ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gr8ArrayGet(                ARRAY)                                             (Gr8 *)              g_ArrayGet(                (G_Array *) ARRAY) 
#define gr8ArrayGetAt(              ARRAY, INDEX)                                      (Gr8 *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gr8ArrayGetBegin(           ARRAY)                                             (Gr8 *)              g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gr8ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gr8ArrayGetEnd(             ARRAY)                                             (Gr8 *)              g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gr8ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gr8ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gr8ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gr8ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gr8ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gr8ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr8ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gr8ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr8ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gr8ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gr8ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gr8ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gr8ArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gr8Array *)         g_ArrayKeyCreate(                 Gr8Array, Gr8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gr8ArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, Gr8Array, Gr8, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gr8ArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gr8ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gr8ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gr8ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gr8ArrayKeyGetAt(           ARRAY, INDEX)                                      (Gr8 *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gr8ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gr8ArrayKeyGetBegin(        ARRAY)                                             (Gr8 *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyGetEnd(          ARRAY)                                             (Gr8 *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gr8ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gr8ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gr8ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gr8ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gr8ListAdd(                 LIST, VALUE)                                       (Gr8ListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gr8ListAddBegin(            LIST, VALUE)                                       (Gr8ListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gr8ListAddEnd(              LIST, VALUE)                                       (Gr8ListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gr8ListCreate(                    OPTIONAL_COMPARE_FUNC)                       (Gr8List *)          g_ListCreate(                               Gr8List, Gr8, OPTIONAL_COMPARE_FUNC)
#define gr8ListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, Gr8List, Gr8, OPTIONAL_COMPARE_FUNC)
#define gr8ListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gr8ListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gr8ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gr8ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gr8ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gr8ListFind(                LIST, VALUE)                                       (Gr8ListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gr8ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gr8ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gr8ListGetBegin(            LIST)                                              (Gr8ListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gr8ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gr8ListGetEnd(              LIST)                                              (Gr8ListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gr8ListItemAdd(             LIST, LITEM, VALUE)                                (Gr8ListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gr8ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gr8ListItemGet(                   LITEM)                                       (Gr8 *)              g_ListItemGet(                              (G_ListItem *) LITEM)
#define gr8ListItemGetNext(               LITEM)                                       (Gr8ListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gr8ListItemGetPrev(               LITEM)                                       (Gr8ListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gr8ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gr8ListKeyAdd(              LIST, KEY, VALUE)                                  (Gr8ListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr8ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gr8ListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr8ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gr8ListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gr8ListKeyCreate(                 COMPARE_FUNC)                                (Gr8List *)          g_ListKeyCreate(                               Gr8ListKey, Gr8, COMPARE_FUNC)
#define gr8ListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, Gr8ListKey, Gr8, COMPARE_FUNC)
#define gr8ListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gr8ListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gr8ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gr8ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gr8ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gr8ListKeyFind(             LIST, KEY)                                         (Gr8ListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gr8ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gr8ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gr8ListKeyGetBegin(         LIST)                                              (Gr8ListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gr8ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gr8ListKeyGetEnd(           LIST)                                              (Gr8ListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gr8ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gr8ListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gr8ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gr8ListKeyItemGet(                LITEM)                                       (Gr8 *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gr8ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gr8ListKeyItemGetNext(            LITEM)                                       (Gr8ListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gr8ListKeyItemGetPrev(            LITEM)                                       (Gr8ListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gr8ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gr8ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gr8HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gr8HashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gr8Hash *)          g_HashCreate(                               Gr8Hash, Gr8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gr8HashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, Gr8Hash, Gr8, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gr8HashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gr8HashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gr8HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gr8HashFind(                HASH, VALUE)                                       (Gr8 *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gr8HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gr8HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gr8HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gr8HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gr8HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gr8HashKeyCreate(                 HASHSIZE)                                    (Gr8HashKey *)       g_HashKeyCreate(                               Gr8HashKey, Gr8, HASHSIZE)
#define gr8HashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, Gr8HashKey, Gr8, HASHSIZE)
#define gr8HashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gr8HashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gr8HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gr8HashKeyFind(             HASH, KEY)                                         (Gr8 *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gr8HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gr8HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gr8HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gr8HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gr8TreeAdd(                 TREE, VALUE)                                       (Gr8TreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gr8TreeCreate(                    COMPARE_FUNC)                                (Gr8Tree *)          g_TreeCreate(                    Gr8Tree, Gr8, COMPARE_FUNC)
#define gr8TreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, Gr8Tree, Gr8, COMPARE_FUNC)
#define gr8TreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gr8TreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gr8TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gr8TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gr8TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gr8TreeFind(                TREE, VALUE)                                       (Gr8TreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gr8TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gr8TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gr8TreeGetBegin(            TREE)                                              (Gr8TreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gr8TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gr8TreeGetEnd(              TREE)                                              (Gr8TreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gr8TreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gr8TreeItemGet(                   TITEM)                                       (Gr8 *)              g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gr8TreeItemGetNext(               TITEM)                                       (Gr8TreeItem *)      g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gr8TreeItemGetPrev(               TITEM)                                       (Gr8TreeItem *)      g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gr8TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gr8TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gr8TreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gr8TreeKeyCreate(                 COMPARE_FUNC)                                (Gr8TreeKey *)       g_TreeKeyCreate(                 Gr8TreeKey, Gr8, COMPARE_FUNC)
#define gr8TreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, Gr8TreeKey, Gr8, COMPARE_FUNC)
#define gr8TreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gr8TreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gr8TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gr8TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gr8TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gr8TreeKeyFind(             TREE, KEY)                                         (Gr8TreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gr8TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gr8TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gr8TreeKeyGetBegin(         TREE)                                              (Gr8TreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gr8TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gr8TreeKeyGetEnd(           TREE)                                              (Gr8TreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gr8TreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gr8TreeKeyItemGet(                TITEM)                                       (Gr8 *)              g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gr8TreeKeyItemGetNext(            TITEM)                                       (Gr8TreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gr8TreeKeyItemGetPrev(            TITEM)                                       (Gr8TreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gr8TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
