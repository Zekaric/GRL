/******************************************************************************
file:       Gv
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

#if !defined(GVH)
#define      GVH

/******************************************************************************
Gv containers.
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
   Gv                  *p;
} GvArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gv                   value;
} GvArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GvArrayKeyCell      *p;
} GvArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GvListItem GvListItem;
struct GvListItem
{
   GvListItem          *next,
                           *prev;
   Gv                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvListItem          *head,
                           *tail;
} GvList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GvListKeyItem GvListKeyItem;
struct GvListKeyItem
{
   GvListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gv                   value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvListKeyItem       *head,
                           *tail;
} GvListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GvList            **binArray;
   GhashSize               binCount;
} GvHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GvListKey         **binArray;
   GhashSize               binCount;
} GvHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GvTree     GvTree;
typedef struct GvTreeItem GvTreeItem;
struct GvTreeItem
{
   GvTree              *owner;
   GvTreeItem          *parent;
   GvTreeItem          *childLeft;
   GvTreeItem          *childRight;
   GheapN                   heapValue;
   Gv                   value;
};

struct GvTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GvTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GvTreeKey     GvTreeKey;
typedef struct GvTreeKeyItem GvTreeKeyItem;
struct GvTreeKeyItem
{
   GvTreeKey           *owner;
   GvTreeKeyItem       *parent;
   GvTreeKeyItem       *childLeft;
   GvTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gv                   value;
};

struct GvTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GvTreeKeyItem       *root;
};

#define gvArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gvArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gvArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gvArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvArray *)             g_ArrayCreate(                                "GvArray", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GvArray", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gvArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gvArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gvArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gvArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gvArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gvArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gvArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gvArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gvArrayGet(                ARRAY)                                            ((Gv *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gvArrayGetAt(              ARRAY, INDEX)                                     ((Gv *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gvArrayGetBegin(           ARRAY)                                            ((Gv *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gvArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gvArrayGetEnd(             ARRAY)                                            ((Gv *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gvArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gvArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gvArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gvArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gvArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gvArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gvArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gvArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gvArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gvArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gvArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gvArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvArray *)             g_ArrayKeyCreate(                                "GvArrayKey", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GvArrayKey", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gvArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gvArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gvArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gvArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gvArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gvArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gvArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gvArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gvArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gv *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gvArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gvArrayKeyGetBegin(        ARRAY)                                            ((Gv *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gvArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gvArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gvArrayKeyGetEnd(          ARRAY)                                            ((Gv *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gvArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gvArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gvArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gvArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gvArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gvArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gvArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gvListAdd(                 LIST, VALUE)                                       (GvListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gvListAddBegin(            LIST, VALUE)                                       (GvListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gvListAddEnd(              LIST, VALUE)                                       (GvListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gvListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GvList *)              g_ListCreate(                               "GvList", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gvListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GvList", Gv, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gvListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gvListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gvListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gvListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gvListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gvListFind(                LIST, VALUE)                                       (GvListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gvListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gvListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gvListGetBegin(            LIST)                                              (GvListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gvListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gvListGetEnd(              LIST)                                              (GvListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gvListItemAdd(             LIST, LITEM, VALUE)                                (GvListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gvListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gvListItemGet(                   LITEM)                                      ((Gv *)                  g_ListItemGet(             (G_List *) LIST, (G_ListItem *) LITEM))
#define gvListItemGetNext(               LITEM)                                       (GvListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gvListItemGetPrev(               LITEM)                                       (GvListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gvListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gvListKeyAdd(              LIST, KEY, VALUE)                                  (GvListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvListKeyAddBegin(         LIST, KEY, VALUE)                                  (GvListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvListKeyAddEnd(           LIST, KEY, VALUE)                                  (GvListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvListKeyCreate(                 COMPARE_FUNC)                                (GvList *)              g_ListKeyCreate(                               "GvListKey", Gv, gbFALSE, COMPARE_FUNC)
#define gvListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GvListKey", Gv, gbFALSE, COMPARE_FUNC)
#define gvListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gvListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gvListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gvListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gvListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gvListKeyFind(             LIST, KEY)                                         (GvListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gvListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gvListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gvListKeyGetBegin(         LIST)                                              (GvListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gvListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gvListKeyGetEnd(           LIST)                                              (GvListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gvListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GvListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gvListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gvListKeyItemGet(                LITEM)                                      ((Gv *)                  g_ListKeyItemGet(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM))
#define gvListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gvListKeyItemGetNext(            LITEM)                                       (GvListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gvListKeyItemGetPrev(            LITEM)                                       (GvListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gvListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gvListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gvHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gvHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GvHash *)              g_HashCreate(                               "GvHash", Gv, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GvHash", Gv, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gvHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gvHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gvHashFind(                HASH, VALUE)                                      ((Gv *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gvHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gvHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gvHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gvHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gvHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gvHashKeyCreate(                 HASHSIZE)                                    (GvHashKey *)           g_HashKeyCreate(                               "GvHashKey", Gv, gbFALSE, HASHSIZE)
#define gvHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GvHashKey", Gv, gbFALSE, HASHSIZE)
#define gvHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gvHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gvHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gvHashKeyFind(             HASH, KEY)                                        ((Gv *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gvHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gvHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gvHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gvHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gvTreeAdd(                 TREE, VALUE)                                       (GvTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gvTreeCreate(                    COMPARE_FUNC)                                (GvTree *)              g_TreeCreate(                               "GvTree", Gv, gbFALSE, COMPARE_FUNC)
#define gvTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GvTree", Gv, gbFALSE, COMPARE_FUNC)
#define gvTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gvTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gvTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gvTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gvTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gvTreeFind(                TREE, VALUE)                                       (GvTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gvTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gvTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gvTreeGetBegin(            TREE)                                              (GvTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gvTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gvTreeGetEnd(              TREE)                                              (GvTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gvTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gvTreeItemGet(                   TITEM)                                      ((Gv *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gvTreeItemGetNext(               TITEM)                                       (GvTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gvTreeItemGetPrev(               TITEM)                                       (GvTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gvTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gvTreeKeyAdd(              TREE, KEY, VALUE)                                  (GvTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gvTreeKeyCreate(                 COMPARE_FUNC)                                (GvTreeKey *)           g_TreeKeyCreate(                               "GvTreeKey", Gv, gbFALSE, COMPARE_FUNC)
#define gvTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GvTreeKey", Gv, gbFALSE, COMPARE_FUNC)
#define gvTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gvTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gvTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gvTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gvTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gvTreeKeyFind(             TREE, KEY)                                         (GvTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gvTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gvTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gvTreeKeyGetBegin(         TREE)                                              (GvTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gvTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gvTreeKeyGetEnd(           TREE)                                              (GvTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gvTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gvTreeKeyItemGet(                TITEM)                                      ((Gv *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gvTreeKeyItemGetNext(            TITEM)                                       (GvTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gvTreeKeyItemGetPrev(            TITEM)                                       (GvTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gvTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
