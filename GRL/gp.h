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
Gp containers.
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
   Gp                 **p;
} GpArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   Gp                  *p;
} GpArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GpArrayKeyCell     **p;
} GpArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GpListItem GpListItem;
struct GpListItem
{
   GpListItem          *next,
                           *prev;
   Gp                  *p;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GpListItem          *head,
                           *tail;
} GpList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GpListKeyItem GpListKeyItem;
struct GpListKeyItem
{
   GpListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gp                  *p;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GpListKeyItem       *head,
                           *tail;
} GpListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GpList             **binArray;
   GhashSize                binCount;
} GpHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GpListKey          **binArray;
   GhashSize                binCount;
} GpHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GpTree     GpTree;
typedef struct GpTreeItem GpTreeItem;
struct GpTreeItem
{
   GpTree              *owner;
   GpTreeItem          *parent;
   GpTreeItem          *childLeft;
   GpTreeItem          *childRight;
   GheapN                   heapValue;
   Gp                  *p;
};

struct GpTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GpTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GpTreeKey     GpTreeKey;
typedef struct GpTreeKeyItem GpTreeKeyItem;
struct GpTreeKeyItem
{
   GpTreeKey           *owner;
   GpTreeKeyItem       *parent;
   GpTreeKeyItem       *childLeft;
   GpTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gp                  *p;
};

struct GpTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GpTreeKeyItem       *root;
};

#define gpArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gpArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gpArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gpArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gpArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gpArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gpArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gpArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpArray *)             g_ArrayCreate(                                "GpArray", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GpArray", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gpArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gpArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gpArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gpArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gpArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gpArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gpArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gpArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gpArrayGet(                ARRAY)                                            ((Gp **)                 g_ArrayGet(                (G_Array *) ARRAY))
#define gpArrayGetAt(              ARRAY, INDEX)                                     ((Gp *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gpArrayGetBegin(           ARRAY)                                            ((Gp *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gpArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gpArrayGetEnd(             ARRAY)                                            ((Gp *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gpArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gpArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gpArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gpArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gpArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gpArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gpArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define gpArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gpArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gpArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gpArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gpArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gpArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpArray *)             g_ArrayKeyCreate(                                "GpArrayKey", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GpArrayKey", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gpArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gpArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gpArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gpArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gpArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gpArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gpArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gpArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gpArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gp *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gpArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gpArrayKeyGetBegin(        ARRAY)                                            ((Gp *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gpArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gpArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gpArrayKeyGetEnd(          ARRAY)                                            ((Gp *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gpArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gpArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gpArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gpArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gpArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gpArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gpArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gpListAdd(                 LIST, VALUE)                                       (GpListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gpListAddBegin(            LIST, VALUE)                                       (GpListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gpListAddEnd(              LIST, VALUE)                                       (GpListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gpListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GpList *)              g_ListCreate(                               "GpList", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gpListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GpList", Gp *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gpListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gpListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gpListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gpListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gpListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gpListFind(                LIST, VALUE)                                       (GpListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gpListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gpListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gpListGetBegin(            LIST)                                              (GpListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gpListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gpListGetEnd(              LIST)                                              (GpListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gpListItemAdd(             LIST, LITEM, VALUE)                                (GpListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gpListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gpListItemGet(             LIST, LITEM)                                      ((Gp *)                  g_ListItemGet(             (G_List *) LIST, (G_ListItem *) LITEM))
#define gpListItemGetNext(               LITEM)                                       (GpListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gpListItemGetPrev(               LITEM)                                       (GpListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gpListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gpListKeyAdd(              LIST, KEY, VALUE)                                  (GpListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpListKeyAddBegin(         LIST, KEY, VALUE)                                  (GpListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpListKeyAddEnd(           LIST, KEY, VALUE)                                  (GpListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpListKeyCreate(                 COMPARE_FUNC)                                (GpList *)              g_ListKeyCreate(                               "GpListKey", Gp *, gbTRUE, COMPARE_FUNC)
#define gpListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GpListKey", Gp *, gbTRUE, COMPARE_FUNC)
#define gpListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gpListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gpListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gpListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gpListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gpListKeyFind(             LIST, KEY)                                         (GpListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gpListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gpListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gpListKeyGetBegin(         LIST)                                              (GpListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gpListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gpListKeyGetEnd(           LIST)                                              (GpListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gpListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GpListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gpListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gpListKeyItemGet(                LITEM)                                      ((Gp *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gpListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gpListKeyItemGetNext(            LITEM)                                       (GpListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gpListKeyItemGetPrev(            LITEM)                                       (GpListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gpListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gpListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gpHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gpHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GpHash *)              g_HashCreate(                               "GpHash", Gp *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GpHash", Gp *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gpHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gpHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gpHashFind(                HASH, VALUE)                                      ((Gp *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gpHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gpHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gpHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gpHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gpHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gpHashKeyCreate(                 HASHSIZE)                                    (GpHashKey *)           g_HashKeyCreate(                               "GpHashKey", Gp *, gbTRUE, HASHSIZE)
#define gpHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GpHashKey", Gp *, gbTRUE, HASHSIZE)
#define gpHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gpHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gpHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gpHashKeyFind(             HASH, KEY)                                        ((Gp *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gpHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gpHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gpHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gpHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gpTreeAdd(                 TREE, VALUE)                                       (GpTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gpTreeCreate(                    COMPARE_FUNC)                                (GpTree *)              g_TreeCreate(                               "GpTree", Gp *, gbTRUE, COMPARE_FUNC)
#define gpTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GpTree", Gp *, gbTRUE, COMPARE_FUNC)
#define gpTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gpTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gpTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gpTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gpTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gpTreeFind(                TREE, VALUE)                                       (GpTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gpTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gpTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gpTreeGetBegin(            TREE)                                              (GpTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gpTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gpTreeGetEnd(              TREE)                                              (GpTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gpTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, TITEM)
#define gpTreeItemGet(                   TITEM)                                      ((Gp *)                  g_TreeItemGet(             (G_Tree *) TREE, TITEM))
#define gpTreeItemGetNext(               TITEM)                                       (GpTreeItem *)          g_TreeItemGetNext(                          TITEM)
#define gpTreeItemGetPrev(               TITEM)                                       (GpTreeItem *)          g_TreeItemGetPrev(                          TITEM)
#define gpTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define gpTreeKeyAdd(              TREE, KEY, VALUE)                                  (GpTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gpTreeKeyCreate(                 COMPARE_FUNC)                                (GpTreeKey *)           g_TreeKeyCreate(                               "GpTreeKey", Gp *, gbTRUE, COMPARE_FUNC)
#define gpTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GpTreeKey", Gp *, gbTRUE, COMPARE_FUNC)
#define gpTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gpTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gpTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gpTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gpTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gpTreeKeyFind(             TREE, KEY)                                         (GpTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gpTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gpTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gpTreeKeyGetBegin(         TREE)                                              (GpTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gpTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gpTreeKeyGetEnd(           TREE)                                              (GpTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gpTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gpTreeKeyItemGet(                TITEM)                                      ((Gp *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gpTreeKeyItemGetNext(            TITEM)                                       (GpTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gpTreeKeyItemGetPrev(            TITEM)                                       (GpTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gpTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
