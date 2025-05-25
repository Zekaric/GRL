/**************************************************************************************************
file:       Gguid
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
GUID is the Globally Unique Identifier structure.  This code wraps some of the
madness.
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

#if !defined(GGUIDH)
#define      GGUIDH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
grlAPI void     gguidClocContent(         Gguid * const guid);
grlAPI void     gguidCreateContentFromA(  Gguid * const guid, Char const * const string);

grlAPI Gb       gguidIsEqual(             Gguid const a, Gguid const b);

/**************************************************************************************************
Gguid containers.
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
   Gguid                  *p;
} GguidArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gguid                   value;
} GguidArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GguidArrayKeyCell      *p;
} GguidArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GguidListItem GguidListItem;
struct GguidListItem
{
   GguidListItem          *next,
                           *prev;
   Gguid                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GguidListItem          *head,
                           *tail;
} GguidList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GguidListKeyItem GguidListKeyItem;
struct GguidListKeyItem
{
   GguidListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gguid                   value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GguidListKeyItem       *head,
                           *tail;
} GguidListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GguidList            **binArray;
   GhashSize               binCount;
} GguidHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GguidListKey         **binArray;
   GhashSize               binCount;
} GguidHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GguidTree     GguidTree;
typedef struct GguidTreeItem GguidTreeItem;
struct GguidTreeItem
{
   GguidTree              *owner;
   GguidTreeItem          *parent;
   GguidTreeItem          *childLeft;
   GguidTreeItem          *childRight;
   GheapN                   heapValue;
   Gguid                   value;
};

struct GguidTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GguidTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GguidTreeKey     GguidTreeKey;
typedef struct GguidTreeKeyItem GguidTreeKeyItem;
struct GguidTreeKeyItem
{
   GguidTreeKey           *owner;
   GguidTreeKeyItem       *parent;
   GguidTreeKeyItem       *childLeft;
   GguidTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gguid                   value;
};

struct GguidTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GguidTreeKeyItem       *root;
};

#define gguidArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gguidArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gguidArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gguidArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gguidArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gguidArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gguidArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gguidArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GguidArray *)          g_ArrayCloc(                                "GguidArray", Gguid, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gguidArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "GguidArray", Gguid, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gguidArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gguidArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gguidArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gguidArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gguidArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gguidArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gguidArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gguidArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gguidArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gguidArrayGet(                ARRAY)                                             (Gguid *)               g_ArrayGet(                (G_Array *) ARRAY) 
#define gguidArrayGetAt(              ARRAY, INDEX)                                      (Gguid *)               g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gguidArrayGetBegin(           ARRAY)                                             (Gguid *)               g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gguidArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gguidArrayGetEnd(             ARRAY)                                             (Gguid *)               g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gguidArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gguidArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gguidArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gguidArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gguidArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gguidArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gguidArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gguidArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gguidArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gguidArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gguidArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gguidArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gguidArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GguidArray *)          g_ArrayKeyCloc(                                "GguidArrayKey", Gguid, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gguidArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GguidArrayKey", Gguid, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gguidArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gguidArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gguidArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gguidArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gguidArrayKeyGetAt(           ARRAY, INDEX)                                      (Gguid *)               g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gguidArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gguidArrayKeyGetBegin(        ARRAY)                                             (Gguid *)               g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyGetEnd(          ARRAY)                                             (Gguid *)               g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gguidArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gguidArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gguidArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gguidArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gguidArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gguidArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gguidListAdd(                 LIST, VALUE)                                       (GguidListItem *)       g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gguidListAddBegin(            LIST, VALUE)                                       (GguidListItem *)       g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gguidListAddEnd(              LIST, VALUE)                                       (GguidListItem *)       g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gguidListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GguidList *)           g_ListCloc(                               "GguidList", Gguid, OPTIONAL_COMPARE_FUNC)
#define gguidListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "GguidList", Gguid, OPTIONAL_COMPARE_FUNC)
#define gguidListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gguidListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gguidListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gguidListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gguidListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gguidListFind(                LIST, VALUE)                                       (GguidListItem *)       g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gguidListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gguidListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gguidListGetBegin(            LIST)                                              (GguidListItem *)       g_ListGetBegin(            (G_List *) LIST)
#define gguidListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gguidListGetEnd(              LIST)                                              (GguidListItem *)       g_ListGetEnd(              (G_List *) LIST)
#define gguidListItemAdd(             LIST, LITEM, VALUE)                                (GguidListItem *)       g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gguidListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gguidListItemGet(                   LITEM)                                       (Gguid *)               g_ListItemGet(                              (G_ListItem *) LITEM)
#define gguidListItemGetNext(               LITEM)                                       (GguidListItem *)       g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gguidListItemGetPrev(               LITEM)                                       (GguidListItem *)       g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gguidListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gguidListKeyAdd(              LIST, KEY, VALUE)                                  (GguidListKeyItem *)    g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gguidListKeyAddBegin(         LIST, KEY, VALUE)                                  (GguidListKeyItem *)    g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gguidListKeyAddEnd(           LIST, KEY, VALUE)                                  (GguidListKeyItem *)    g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gguidListKeyCloc(                   COMPARE_FUNC)                                (GguidList *)           g_ListKeyCloc(                               "GguidListKey", Gguid, COMPARE_FUNC)
#define gguidListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "GguidListKey", Gguid, COMPARE_FUNC)
#define gguidListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gguidListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gguidListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gguidListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gguidListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gguidListKeyFind(             LIST, KEY)                                         (GguidListKeyItem *)    g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gguidListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gguidListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gguidListKeyGetBegin(         LIST)                                              (GguidListKeyItem *)    g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gguidListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gguidListKeyGetEnd(           LIST)                                              (GguidListKeyItem *)    g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gguidListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GguidListKeyItem *)    g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gguidListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gguidListKeyItemGet(                LITEM)                                       (Gguid *)               g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gguidListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gguidListKeyItemGetNext(            LITEM)                                       (GguidListKeyItem *)    g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gguidListKeyItemGetPrev(            LITEM)                                       (GguidListKeyItem *)    g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gguidListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gguidListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gguidHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gguidHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GguidHash *)           g_HashCloc(                               "GguidHash", Gguid, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gguidHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "GguidHash", Gguid, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gguidHashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gguidHashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gguidHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gguidHashFind(                HASH, VALUE)                                       (Gguid *)               g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gguidHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gguidHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gguidHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gguidHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gguidHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gguidHashKeyCloc(                   HASHSIZE)                                    (GguidHashKey *)        g_HashKeyCloc(                               "GguidHashKey", Gguid, HASHSIZE)
#define gguidHashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "GguidHashKey", Gguid, HASHSIZE)
#define gguidHashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gguidHashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gguidHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gguidHashKeyFind(             HASH, KEY)                                         (Gguid *)               g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gguidHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gguidHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gguidHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gguidHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gguidTreeAdd(                 TREE, VALUE)                                       (GguidTreeItem *)       g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gguidTreeCloc(                      COMPARE_FUNC)                                (GguidTree *)           g_TreeCloc(                               "GguidTree", Gguid, COMPARE_FUNC)
#define gguidTreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "GguidTree", Gguid, COMPARE_FUNC)
#define gguidTreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gguidTreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gguidTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gguidTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gguidTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gguidTreeFind(                TREE, VALUE)                                       (GguidTreeItem *)       g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gguidTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gguidTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gguidTreeGetBegin(            TREE)                                              (GguidTreeItem *)       g_TreeGetBegin(            (G_Tree *) TREE)
#define gguidTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gguidTreeGetEnd(              TREE)                                              (GguidTreeItem *)       g_TreeGetEnd(              (G_Tree *) TREE)
#define gguidTreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gguidTreeItemGet(                   TITEM)                                       (Gguid *)               g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gguidTreeItemGetNext(               TITEM)                                       (GguidTreeItem *)       g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gguidTreeItemGetPrev(               TITEM)                                       (GguidTreeItem *)       g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gguidTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gguidTreeKeyAdd(              TREE, KEY, VALUE)                                  (GguidTreeKeyItem *)    g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gguidTreeKeyCloc(                   COMPARE_FUNC)                                (GguidTreeKey *)        g_TreeKeyCloc(                               "GguidTreeKey", Gguid, COMPARE_FUNC)
#define gguidTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GguidTreeKey", Gguid, COMPARE_FUNC)
#define gguidTreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gguidTreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gguidTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gguidTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gguidTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gguidTreeKeyFind(             TREE, KEY)                                         (GguidTreeKeyItem *)    g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gguidTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gguidTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gguidTreeKeyGetBegin(         TREE)                                              (GguidTreeKeyItem *)    g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gguidTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gguidTreeKeyGetEnd(           TREE)                                              (GguidTreeKeyItem *)    g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gguidTreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gguidTreeKeyItemGet(                TITEM)                                       (Gguid *)               g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gguidTreeKeyItemGetNext(            TITEM)                                       (GguidTreeKeyItem *)    g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gguidTreeKeyItemGetPrev(            TITEM)                                       (GguidTreeKeyItem *)    g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gguidTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
