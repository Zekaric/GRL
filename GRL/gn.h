/**************************************************************************************************
file:       Gn
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

#if !defined(GNH)
#define      GNH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
Gn containers.
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
   Gn                      *p;
} GnArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gn                       value;
} GnArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GnArrayKeyCell          *p;
} GnArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GnListItem GnListItem;
struct GnListItem
{
   GnListItem              *next,
                           *prev;
   Gn                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GnListItem              *head,
                           *tail;
} GnList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GnListKeyItem GnListKeyItem;
struct GnListKeyItem
{
   GnListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gn                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GnListKeyItem           *head,
                           *tail;
} GnListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GnList                **binArray;
   GhashSize               binCount;
} GnHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GnListKey             **binArray;
   GhashSize               binCount;
} GnHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GnTree     GnTree;
typedef struct GnTreeItem GnTreeItem;
struct GnTreeItem
{
   GnTree                  *owner;
   GnTreeItem              *parent;
   GnTreeItem              *childLeft;
   GnTreeItem              *childRight;
   GheapN                   heapValue;
   Gn                       value;
};

struct GnTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GnTreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GnTreeKey     GnTreeKey;
typedef struct GnTreeKeyItem GnTreeKeyItem;
struct GnTreeKeyItem
{
   GnTreeKey               *owner;
   GnTreeKeyItem           *parent;
   GnTreeKeyItem           *childLeft;
   GnTreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gn                       value;
};

struct GnTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GnTreeKeyItem           *root;
};

#define gnArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gnArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gnArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gnArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gnArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gnArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GnArray *)             g_ArrayCloc(                                "GnArray", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gnArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "GnArray", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gnArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gnArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gnArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gnArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gnArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gnArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gnArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gnArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gnArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gnArrayForEachDown(        ARRAY, FUNC)                                                               g_ArrayForEachDown(        (G_Array *) ARRAY, FUNC) 
#define gnArrayGet(                ARRAY)                                            ((Gn *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gnArrayGetAt(              ARRAY, INDEX)                                     ((Gn *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gnArrayGetBegin(           ARRAY)                                            ((Gn *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gnArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gnArrayGetEnd(             ARRAY)                                            ((Gn *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
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
#define gnArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GnArray *)             g_ArrayKeyCloc(                                "GnArrayKey", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gnArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GnArrayKey", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gnArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gnArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gnArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gnArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gnArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gnArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gnArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gnArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gnArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gnArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gn *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gnArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gnArrayKeyGetBegin(        ARRAY)                                            ((Gn *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gnArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetEnd(          ARRAY)                                            ((Gn *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gnArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gnArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gnArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gnArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gnArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gnArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gnArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gnListAdd(                 LIST, VALUE)                                       (GnListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gnListAddBegin(            LIST, VALUE)                                       (GnListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gnListAddEnd(              LIST, VALUE)                                       (GnListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gnListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GnList *)              g_ListCloc(                               "GnList", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gnListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "GnList", Gn, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gnListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gnListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gnListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gnListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gnListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gnListFind(                LIST, VALUE)                                       (GnListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gnListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gnListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gnListGetBegin(            LIST)                                              (GnListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gnListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gnListGetEnd(              LIST)                                              (GnListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gnListItemAdd(             LIST, LITEM, VALUE)                                (GnListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gnListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gnListItemGet(                   LITEM)                                      ((Gn *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gnListItemGetNext(               LITEM)                                       (GnListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gnListItemGetPrev(               LITEM)                                       (GnListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gnListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gnListKeyAdd(              LIST, KEY, VALUE)                                  (GnListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyAddBegin(         LIST, KEY, VALUE)                                  (GnListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyAddEnd(           LIST, KEY, VALUE)                                  (GnListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gnListKeyCloc(                   COMPARE_FUNC)                                (GnList *)              g_ListKeyCloc(                               "GnListKey", Gn, gbFALSE, COMPARE_FUNC)
#define gnListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "GnListKey", Gn, gbFALSE, COMPARE_FUNC)
#define gnListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gnListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gnListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gnListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gnListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gnListKeyFind(             LIST, KEY)                                         (GnListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gnListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gnListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gnListKeyGetBegin(         LIST)                                              (GnListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gnListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gnListKeyGetEnd(           LIST)                                              (GnListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gnListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GnListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gnListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gnListKeyItemGet(                LITEM)                                      ((Gn *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gnListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gnListKeyItemGetPrev(            LITEM)                                       (GnListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gnListKeyItemGetNext(            LITEM)                                       (GnListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gnListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gnListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gnHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gnHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GnHash *)              g_HashCloc(                               "GnHash", Gn, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gnHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "GnHash", Gn, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gnHashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gnHashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gnHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gnHashFind(                HASH, VALUE)                                      ((Gn *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gnHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gnHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gnHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gnHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gnHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gnHashKeyCloc(                   HASHSIZE)                                    (GnHashKey *)           g_HashKeyCloc(                               "GnHashKey", Gn, gbFALSE, HASHSIZE)
#define gnHashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "GnHashKey", Gn, gbFALSE, HASHSIZE)
#define gnHashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gnHashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gnHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gnHashKeyFind(             HASH, KEY)                                        ((Gn *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gnHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gnHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gnHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gnHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gnTreeAdd(                 TREE, VALUE)                                       (GnTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeCloc(                      COMPARE_FUNC)                                (GnTree *)              g_TreeCloc(                               "GnTree", Gn, gbFALSE, COMPARE_FUNC)
#define gnTreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "GnTree", Gn, gbFALSE, COMPARE_FUNC)
#define gnTreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gnTreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gnTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gnTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gnTreeFind(                TREE, VALUE)                                       (GnTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gnTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gnTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gnTreeGetBegin(            TREE)                                              (GnTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gnTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gnTreeGetEnd(              TREE)                                              (GnTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gnTreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gnTreeItemGet(                   TITEM)                                      ((Gn *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gnTreeItemGetNext(               TITEM)                                       (GnTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gnTreeItemGetPrev(               TITEM)                                       (GnTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gnTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gnTreeKeyAdd(              TREE, KEY, VALUE)                                  (GnTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gnTreeKeyCloc(                   COMPARE_FUNC)                                (GnTreeKey *)           g_TreeKeyCloc(                               "GnTreeKey", Gn, gbFALSE, COMPARE_FUNC)
#define gnTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GnTreeKey", Gn, gbFALSE, COMPARE_FUNC)
#define gnTreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gnTreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gnTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gnTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gnTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gnTreeKeyFind(             TREE, KEY)                                         (GnTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gnTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gnTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gnTreeKeyGetBegin(         TREE)                                              (GnTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gnTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gnTreeKeyGetEnd(           TREE)                                              (GnTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gnTreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemGet(                TITEM)                                      ((Gn *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gnTreeKeyItemGetNext(            TITEM)                                       (GnTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemGetPrev(            TITEM)                                       (GnTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gnTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/**************************************************************************************************
Gn1 containers.
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
   Gn1                     *p;
} Gn1Array;

#define gn1ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gn1ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gn1ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gn1ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gn1ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gn1ArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gn1Array *)            g_ArrayCloc(                                "Gn1Array", Gn1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn1ArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "Gn1Array", Gn1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gn1ArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gn1ArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gn1ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn1ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gn1ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gn1ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gn1ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gn1ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gn1ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gn1ArrayForEachDown(        ARRAY, FUNC)                                                               g_ArrayForEachDown(        (G_Array *) ARRAY, FUNC) 
#define gn1ArrayGet(                ARRAY)                                            ((Gn1 *)                 g_ArrayGet(                (G_Array *) ARRAY))
#define gn1ArrayGetAt(              ARRAY, INDEX)                                     ((Gn1 *)                 g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gn1ArrayGetBegin(           ARRAY)                                            ((Gn1 *)                 g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gn1ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gn1ArrayGetEnd(             ARRAY)                                            ((Gn1 *)                 g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gn1ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gn1ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gn1ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gn1ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gn1ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif

