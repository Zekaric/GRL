/**************************************************************************************************
file:       Gi
author:     Robbert de Groot
copyright:  2020, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
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
**************************************************************************************************/

#if !defined(GIH)
#define      GIH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
Gi containers.
**************************************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gi                      *p;
} GiArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gi                       value;
} GiArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GiArrayKeyCell          *p;
} GiArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GiListItem GiListItem;
struct GiListItem
{
   GiListItem              *next,
                           *prev;
   Gi                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GiListItem              *head,
                           *tail;
} GiList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GiListKeyItem GiListKeyItem;
struct GiListKeyItem
{
   GiListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gi                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GiListKeyItem           *head,
                           *tail;
} GiListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GiList                **binArray;
   GhashSize               binCount;
} GiHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GiListKey             **binArray;
   GhashSize               binCount;
} GiHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GiTree     GiTree;
typedef struct GiTreeItem GiTreeItem;
struct GiTreeItem
{
   GiTree                  *owner;
   GiTreeItem              *parent;
   GiTreeItem              *childLeft;
   GiTreeItem              *childRight;
   GheapN                   heapValue;
   Gi                       value;
};

struct GiTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GiTreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GiTreeKey     GiTreeKey;
typedef struct GiTreeKeyItem GiTreeKeyItem;
struct GiTreeKeyItem
{
   GiTreeKey               *owner;
   GiTreeKeyItem           *parent;
   GiTreeKeyItem           *childLeft;
   GiTreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gi                       value;
};

struct GiTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GiTreeKeyItem           *root;
};

#define giArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define giArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define giArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define giArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define giArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define giArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GiArray *)             g_ArrayCloc(                                "GiArray", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define giArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "GiArray", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define giArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define giArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define giArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define giArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define giArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define giArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define giArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define giArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define giArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define giArrayForEachDown(        ARRAY, FUNC)                                                               g_ArrayForEachDown(        (G_Array *) ARRAY, FUNC) 
#define giArrayGet(                ARRAY)                                            ((Gi *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define giArrayGetAt(              ARRAY, INDEX)                                     ((Gi *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define giArrayGetBegin(           ARRAY)                                            ((Gi *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define giArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define giArrayGetEnd(             ARRAY)                                            ((Gi *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
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
#define giArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GiArray *)             g_ArrayKeyCloc(                                "GiArrayKey", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define giArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GiArrayKey", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define giArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define giArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define giArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define giArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define giArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define giArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define giArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define giArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define giArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define giArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gi *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define giArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define giArrayKeyGetBegin(        ARRAY)                                            ((Gi *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define giArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetEnd(          ARRAY)                                            ((Gi *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define giArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define giArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define giArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define giArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define giArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define giArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define giArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define giListAdd(                 LIST, VALUE)                                       (GiListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define giListAddBegin(            LIST, VALUE)                                       (GiListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define giListAddEnd(              LIST, VALUE)                                       (GiListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define giListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GiList *)              g_ListCloc(                               "GiList", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define giListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "GiList", Gi, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define giListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define giListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define giListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define giListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define giListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define giListFind(                LIST, VALUE)                                       (GiListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define giListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define giListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define giListGetBegin(            LIST)                                              (GiListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define giListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define giListGetEnd(              LIST)                                              (GiListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define giListItemAdd(             LIST, LITEM, VALUE)                                (GiListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define giListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define giListItemGet(                   LITEM)                                      ((Gi *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define giListItemGetNext(               LITEM)                                       (GiListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define giListItemGetPrev(               LITEM)                                       (GiListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define giListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define giListKeyAdd(              LIST, KEY, VALUE)                                  (GiListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyAddBegin(         LIST, KEY, VALUE)                                  (GiListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyAddEnd(           LIST, KEY, VALUE)                                  (GiListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define giListKeyCloc(                   COMPARE_FUNC)                                (GiList *)              g_ListKeyCloc(                               "GiListKey", Gi, gbFALSE, COMPARE_FUNC)
#define giListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "GiListKey", Gi, gbFALSE, COMPARE_FUNC)
#define giListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define giListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define giListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define giListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define giListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define giListKeyFind(             LIST, KEY)                                         (GiListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define giListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define giListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define giListKeyGetBegin(         LIST)                                              (GiListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define giListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define giListKeyGetEnd(           LIST)                                              (GiListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define giListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GiListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define giListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define giListKeyItemGet(                LITEM)                                      ((Gi *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define giListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define giListKeyItemGetNext(            LITEM)                                       (GiListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define giListKeyItemGetPrev(            LITEM)                                       (GiListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define giListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define giListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define giHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define giHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GiHash *)              g_HashCloc(                               "GiHash", Gi, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define giHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "GiHash", Gi, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define giHashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define giHashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define giHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define giHashFind(                HASH, VALUE)                                      ((Gi *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define giHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define giHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define giHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define giHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define giHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define giHashKeyCloc(                   HASHSIZE)                                    (GiHashKey *)           g_HashKeyCloc(                               "GiHashKey", Gi, gbFALSE, HASHSIZE)
#define giHashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "GiHashKey", Gi, gbFALSE, HASHSIZE)
#define giHashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define giHashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define giHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define giHashKeyFind(             HASH, KEY)                                        ((Gi *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define giHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define giHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define giHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define giHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define giTreeAdd(                 TREE, VALUE)                                       (GiTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeCloc(                      COMPARE_FUNC)                                (GiTree *)              g_TreeCloc(                               "GiTree", Gi, gbFALSE, COMPARE_FUNC)
#define giTreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "GiTree", Gi, gbFALSE, COMPARE_FUNC)
#define giTreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define giTreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define giTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define giTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define giTreeFind(                TREE, VALUE)                                       (GiTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define giTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define giTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define giTreeGetBegin(            TREE)                                              (GiTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define giTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define giTreeGetEnd(              TREE)                                              (GiTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define giTreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define giTreeItemGet(                   TITEM)                                      ((Gi *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define giTreeItemGetNext(               TITEM)                                       (GiTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define giTreeItemGetPrev(               TITEM)                                       (GiTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define giTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define giTreeKeyAdd(              TREE, KEY, VALUE)                                  (GiTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define giTreeKeyCloc(                   COMPARE_FUNC)                                (GiTreeKey *)           g_TreeKeyCloc(                               "GiTreeKey", Gi, gbFALSE, COMPARE_FUNC)
#define giTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GiTreeKey", Gi, gbFALSE, COMPARE_FUNC)
#define giTreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define giTreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define giTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define giTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define giTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define giTreeKeyFind(             TREE, KEY)                                         (GiTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define giTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define giTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define giTreeKeyGetBegin(         TREE)                                              (GiTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define giTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define giTreeKeyGetEnd(           TREE)                                              (GiTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define giTreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemGet(                TITEM)                                      ((Gi *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define giTreeKeyItemGetNext(            TITEM)                                       (GiTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemGetPrev(            TITEM)                                       (GiTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define giTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
