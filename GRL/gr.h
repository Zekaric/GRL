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

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
Gr containers.
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
   Gr                      *p;
} GrArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gr                       value;
} GrArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GrArrayKeyCell          *p;
} GrArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GrListItem GrListItem;
struct GrListItem
{
   GrListItem              *next,
                           *prev;
   Gr                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GrListItem              *head,
                           *tail;
} GrList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GrListKeyItem GrListKeyItem;
struct GrListKeyItem
{
   GrListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gr                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GrListKeyItem           *head,
                           *tail;
} GrListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GrList                **binArray;
   GhashSize               binCount;
} GrHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrListKey             **binArray;
   GhashSize               binCount;
} GrHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GrTree     GrTree;
typedef struct GrTreeItem GrTreeItem;
struct GrTreeItem
{
   GrTree                  *owner;
   GrTreeItem              *parent;
   GrTreeItem              *childLeft;
   GrTreeItem              *childRight;
   GheapN                   heapValue;
   Gr                       value;
};

struct GrTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GrTreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GrTreeKey     GrTreeKey;
typedef struct GrTreeKeyItem GrTreeKeyItem;
struct GrTreeKeyItem
{
   GrTreeKey               *owner;
   GrTreeKeyItem           *parent;
   GrTreeKeyItem           *childLeft;
   GrTreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gr                       value;
};

struct GrTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GrTreeKeyItem           *root;
};

#define grArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define grArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define grArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define grArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define grArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define grArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GrArray *)             g_ArrayCreate(                                "GrArray", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define grArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GrArray", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define grArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define grArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define grArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define grArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define grArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define grArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define grArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define grArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define grArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define grArrayGet(                ARRAY)                                            ((Gr *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define grArrayGetAt(              ARRAY, INDEX)                                     ((Gr *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define grArrayGetBegin(           ARRAY)                                            ((Gr *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define grArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define grArrayGetEnd(             ARRAY)                                            ((Gr *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
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
#define grArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GrArray *)             g_ArrayKeyCreate(                                "GrArrayKey", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define grArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GrArrayKey", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define grArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define grArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define grArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define grArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define grArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define grArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define grArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define grArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define grArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define grArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gr *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define grArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define grArrayKeyGetBegin(        ARRAY)                                            ((Gr *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define grArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetEnd(          ARRAY)                                            ((Gr *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define grArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define grArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define grArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define grArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define grArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define grArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define grArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define grListAdd(                 LIST, VALUE)                                       (GrListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define grListAddBegin(            LIST, VALUE)                                       (GrListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define grListAddEnd(              LIST, VALUE)                                       (GrListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define grListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GrList *)              g_ListCreate(                               "GrList", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define grListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GrList", Gr, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define grListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define grListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define grListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define grListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define grListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define grListFind(                LIST, VALUE)                                       (GrListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define grListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define grListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define grListGetBegin(            LIST)                                              (GrListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define grListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define grListGetEnd(              LIST)                                              (GrListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define grListItemAdd(             LIST, LITEM, VALUE)                                (GrListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define grListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define grListItemGet(                   LITEM)                                      ((Gr *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define grListItemGetNext(               LITEM)                                       (GrListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define grListItemGetPrev(               LITEM)                                       (GrListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define grListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define grListKeyAdd(              LIST, KEY, VALUE)                                  (GrListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyAddBegin(         LIST, KEY, VALUE)                                  (GrListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyAddEnd(           LIST, KEY, VALUE)                                  (GrListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define grListKeyCreate(                 COMPARE_FUNC)                                (GrList *)              g_ListKeyCreate(                               "GrListKey", Gr, gbFALSE, COMPARE_FUNC)
#define grListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GrListKey", Gr, gbFALSE, COMPARE_FUNC)
#define grListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define grListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define grListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define grListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define grListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define grListKeyFind(             LIST, KEY)                                         (GrListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define grListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define grListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define grListKeyGetBegin(         LIST)                                              (GrListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define grListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define grListKeyGetEnd(           LIST)                                              (GrListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define grListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GrListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define grListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define grListKeyItemGet(                LITEM)                                      ((Gr *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define grListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define grListKeyItemGetNext(            LITEM)                                       (GrListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define grListKeyItemGetPrev(            LITEM)                                       (GrListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define grListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define grListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define grHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define grHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GrHash *)              g_HashCreate(                               "GrHash", Gr, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define grHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GrHash", Gr, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define grHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define grHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define grHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define grHashFind(                HASH, VALUE)                                      ((Gr *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define grHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define grHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define grHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define grHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define grHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define grHashKeyCreate(                 HASHSIZE)                                    (GrHashKey *)           g_HashKeyCreate(                               "GrHashKey", Gr, gbFALSE, HASHSIZE)
#define grHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GrHashKey", Gr, gbFALSE, HASHSIZE)
#define grHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define grHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define grHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define grHashKeyFind(             HASH, KEY)                                        ((Gr *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define grHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define grHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define grHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define grHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define grTreeAdd(                 TREE, VALUE)                                       (GrTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeCreate(                    COMPARE_FUNC)                                (GrTree *)              g_TreeCreate(                               "GrTree", Gr, gbFALSE, COMPARE_FUNC)
#define grTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GrTree", Gr, gbFALSE, COMPARE_FUNC)
#define grTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define grTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define grTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define grTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define grTreeFind(                TREE, VALUE)                                       (GrTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define grTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define grTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define grTreeGetBegin(            TREE)                                              (GrTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define grTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define grTreeGetEnd(              TREE)                                              (GrTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define grTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define grTreeItemGet(                   TITEM)                                      ((Gr *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define grTreeItemGetNext(               TITEM)                                       (GrTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define grTreeItemGetPrev(               TITEM)                                       (GrTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define grTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define grTreeKeyAdd(              TREE, KEY, VALUE)                                  (GrTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define grTreeKeyCreate(                 COMPARE_FUNC)                                (GrTreeKey *)           g_TreeKeyCreate(                               "GrTreeKey", Gr, gbFALSE, COMPARE_FUNC)
#define grTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GrTreeKey", Gr, gbFALSE, COMPARE_FUNC)
#define grTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define grTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define grTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define grTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define grTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define grTreeKeyFind(             TREE, KEY)                                         (GrTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define grTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define grTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define grTreeKeyGetBegin(         TREE)                                              (GrTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define grTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define grTreeKeyGetEnd(           TREE)                                              (GrTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define grTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemGet(                TITEM)                                      ((Gr *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define grTreeKeyItemGetNext(            TITEM)                                       (GrTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemGetPrev(            TITEM)                                       (GrTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define grTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
