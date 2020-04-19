/******************************************************************************
file:         Gs
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrrays.
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

#if !defined(GSH)
#define      GSH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
type:
******************************************************************************/
// Same as G_Array
typedef struct Gs
{
   GCONTAINER_VAR;

   Gcount               countTotal;
   Gbit                 isVectorSizing   : 1,
                        isSorted         : 1,
                        isNullEnding     : 1;
   GrlCompareFunc       compareFunc;
   Gc2                 *p;
} Gs;

#define gsAdd(           STR,        VALUE)                                       g_ArrayAdd(                (G_Array *) STR,        (Gp *) VALUE) 
#define gsAddAt(         STR, INDEX, VALUE)                                       g_ArrayAddAt(              (G_Array *) STR, INDEX, (Gp *) VALUE) 
#define gsAddBegin(      STR,        VALUE)                                       g_ArrayAddBegin(           (G_Array *) STR,        (Gp *) VALUE) 
#define gsAddEnd(        STR,        VALUE)                                       g_ArrayAddEnd(             (G_Array *) STR,        (Gp *) VALUE) 
#define gsClear(         STR, COUNT, INDEX)                                       g_ArrayClear(              (G_Array *) STR, COUNT, INDEX) 
#define gsCopy(          STR, COUNT, INDEXSRC, INDEXDST)                          g_ArrayCopy(               (G_Array *) STR, COUNT, INDEXSRC, INDEXDST) 
#define gsCopyFrom(      STRDST, INDEXDST, STRSRC, COUNT, INDEXSRC)               g_ArrayCopyFrom(           (G_Array *) STRDST, INDEXDST, (G_Array *) STRSRC, COUNT, INDEXSRC) 
#define gsCreate(        )                                                (Gs  *) g_ArrayCreate(                              Gs, Gc2, gbFALSE, NULL, gbTRUE, gbTRUE)
#define gsCreateContent( STR)                                                     g_ArrayCreateContent(      (G_Array *) STR, Gs, Gc2, gbFALSE, NULL, gbTRUE, gbTRUE)
#define gsDestroy(       STR)                                                     g_ArrayDestroy(            (G_Array *) STR) 
#define gsDestroyContent(STR)                                                     g_ArrayDestroyContent(     (G_Array *) STR) 
#define gsErase(         STR, VALUE)                                              g_ArrayErase(              (G_Array *) STR, (Gp *) VALUE) 
#define gsEraseAt(       STR, COUNT, INDEX)                                       g_ArrayEraseAt(            (G_Array *) STR, COUNT, INDEX) 
#define gsEraseBegin(    STR)                                                     g_ArrayEraseBegin(         (G_Array *) STR) 
#define gsEraseEnd(      STR)                                                     g_ArrayEraseEnd(           (G_Array *) STR) 
#define gsFind(          STR, VALUE)                                              g_ArrayFind(               (G_Array *) STR, (Gp *) VALUE) 
#define gsFlush(         STR)                                                     g_ArrayFlush(              (G_Array *) STR) 
#define gsForEach(       STR, FUNC)                                               g_ArrayForEach(            (G_Array *) STR, FUNC) 
#define gsGet(           STR)                                            ((Gc2 *) g_ArrayGet(                (G_Array *) STR))
#define gsGetAt(         STR, INDEX)                                     ((Gc2 *) g_ArrayGetAt(              (G_Array *) STR, INDEX))
#define gsGetBegin(      STR)                                            ((Gc2 *) g_ArrayGetBegin(           (G_Array *) STR))
#define gsGetCount(      STR)                                                     g_ArrayGetCount(           (G_Array *) STR) 
#define gsGetEnd(        STR)                                            ((Gc2 *) g_ArrayGetEnd(             (G_Array *) STR))
#define gsGetSize(       STR)                                                     g_ArrayGetSize(            (G_Array *) STR) 
#define gsSetCount(      STR, VALUE)                                              g_ArraySetCount(           (G_Array *) STR, VALUE) 
#define gsSort(          STR)                                                     g_ArraySort(               (G_Array *) STR) 
#define gsSwap(          STR, INDEXA, INDEXB)                                     g_ArraySwap(               (G_Array *) STR, INDEXA, INDEXB) 
#define gsUpdateAt(      STR, INDEX, VALUE)                                       g_ArrayUpdateAt(           (G_Array *) STR, INDEX, (Gp *) VALUE) 

#define gsDestroyFunc g_ArrayDestroy

/******************************************************************************
Gs containers.
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
   Gs                 **p;
} GsArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   Gs                  *p;
} GsArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GsArrayKeyCell     **p;
} GsArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GsListItem GsListItem;
struct GsListItem
{
   GsListItem          *next,
                           *prev;
   Gs                  *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GsListItem          *head,
                           *tail;
} GsList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GsListKeyItem GsListKeyItem;
struct GsListKeyItem
{
   GsListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   Gs                  *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GsListKeyItem       *head,
                           *tail;
} GsListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GsList             **binArray;
   GhashSize                binCount;
} GsHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GsListKey          **binArray;
   GhashSize                binCount;
} GsHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GsTree     GsTree;
typedef struct GsTreeItem GsTreeItem;
struct GsTreeItem
{
   GsTree              *owner;
   GsTreeItem          *parent;
   GsTreeItem          *childLeft;
   GsTreeItem          *childRight;
   GheapN                   heapValue;
   Gs                  *p;
};

struct GsTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GsTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GsTreeKey     GsTreeKey;
typedef struct GsTreeKeyItem GsTreeKeyItem;
struct GsTreeKeyItem
{
   GsTreeKey           *owner;
   GsTreeKeyItem       *parent;
   GsTreeKeyItem       *childLeft;
   GsTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gs                  *p;
};

struct GsTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GsTreeKeyItem       *root;
};

#define gsArrayAdd(                ARRAY,        VALUE)                                                  g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gsArrayAddAt(              ARRAY, INDEX, VALUE)                                                  g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gsArrayAddBegin(           ARRAY,        VALUE)                                                  g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gsArrayAddEnd(             ARRAY,        VALUE)                                                  g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gsArrayClear(              ARRAY, COUNT, INDEX)                                                  g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gsArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                     g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gsArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                        g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gsArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GsArray *)        g_ArrayCreate(                                GsArray, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gsArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                       g_ArrayCreateContent(      (G_Array *) ARRAY, GsArray, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gsArrayDestroy(            ARRAY)                                                                g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gsArrayDestroyContent(     ARRAY)                                                                g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gsArrayErase(              ARRAY, VALUE)                                                         g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gsArrayEraseAt(            ARRAY, COUNT, INDEX)                                                  g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gsArrayEraseBegin(         ARRAY)                                                                g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gsArrayEraseEnd(           ARRAY)                                                                g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gsArrayFind(               ARRAY, VALUE)                                                         g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gsArrayFlush(              ARRAY)                                                                g_ArrayFlush(              (G_Array *) ARRAY) 
#define gsArrayForEach(            ARRAY, FUNC)                                                          g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gsArrayGet(                ARRAY)                                            ((Gs **)            g_ArrayGet(                (G_Array *) ARRAY))
#define gsArrayGetAt(              ARRAY, INDEX)                                     ((Gs *)             g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gsArrayGetBegin(           ARRAY)                                            ((Gs *)             g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gsArrayGetCount(           ARRAY)                                                                g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gsArrayGetEnd(             ARRAY)                                            ((Gs *)             g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gsArrayGetSize(            ARRAY)                                                                g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gsArraySetCount(           ARRAY, COUNT)                                                         g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gsArraySort(               ARRAY)                                                                g_ArraySort(               (G_Array *) ARRAY) 
#define gsArraySwap(               ARRAY, INDEXA, INDEXB)                                                g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gsArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                  g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gsArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gsArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define gsArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gsArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gsArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gsArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gsArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gsArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GsArray *)         g_ArrayKeyCreate(                                GsArray, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gsArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GsArray, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gsArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gsArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gsArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gsArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gsArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gsArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gsArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gsArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gsArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gsArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gs *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gsArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gsArrayKeyGetBegin(        ARRAY)                                            ((Gs *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gsArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gsArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gsArrayKeyGetEnd(          ARRAY)                                            ((Gs *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gsArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gsArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gsArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gsArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gsArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gsArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gsArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gsListAdd(                 LIST, VALUE)                                       (GsListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gsListAddBegin(            LIST, VALUE)                                       (GsListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gsListAddEnd(              LIST, VALUE)                                       (GsListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gsListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GsList *)          g_ListCreate(                               GsList, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gsListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, GsList, Gs *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gsListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gsListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gsListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gsListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gsListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gsListFind(                LIST, VALUE)                                       (GsListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gsListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gsListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gsListGetBegin(            LIST)                                              (GsListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gsListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gsListGetEnd(              LIST)                                              (GsListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gsListItemAdd(             LIST, LITEM, VALUE)                                (GsListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gsListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gsListItemGet(             LIST, LITEM)                                      ((Gs *)              g_ListItemGet(             (G_List *) LIST, (G_ListItem *) LITEM))
#define gsListItemGetNext(               LITEM)                                       (GsListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gsListItemGetPrev(               LITEM)                                       (GsListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gsListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gsListKeyAdd(              LIST, KEY, VALUE)                                  (GsListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gsListKeyAddBegin(         LIST, KEY, VALUE)                                  (GsListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gsListKeyAddEnd(           LIST, KEY, VALUE)                                  (GsListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gsListKeyCreate(                 COMPARE_FUNC)                                (GsList *)          g_ListKeyCreate(                               GsListKey, Gs *, gbTRUE, COMPARE_FUNC)
#define gsListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, GsListKey, Gs *, gbTRUE, COMPARE_FUNC)
#define gsListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gsListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gsListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gsListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gsListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gsListKeyFind(             LIST, KEY)                                         (GsListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gsListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gsListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gsListKeyGetBegin(         LIST)                                              (GsListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gsListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gsListKeyGetEnd(           LIST)                                              (GsListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gsListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GsListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gsListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gsListKeyItemGet(                LITEM)                                      ((Gs *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gsListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gsListKeyItemGetNext(            LITEM)                                       (GsListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gsListKeyItemGetPrev(            LITEM)                                       (GsListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gsListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gsListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gsHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gsHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GsHash *)          g_HashCreate(                               GsHash, Gs *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gsHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, GsHash, Gs *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gsHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gsHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gsHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gsHashFind(                HASH, VALUE)                                      ((Gs *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gsHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gsHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gsHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gsHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gsHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gsHashKeyCreate(                 HASHSIZE)                                    (GsHashKey *)       g_HashKeyCreate(                               GsHashKey, Gs *, gbTRUE, HASHSIZE)
#define gsHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, GsHashKey, Gs *, gbTRUE, HASHSIZE)
#define gsHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gsHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gsHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gsHashKeyFind(             HASH, KEY)                                        ((Gs *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gsHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gsHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gsHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gsHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gsTreeAdd(                 TREE, VALUE)                                       (GsTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gsTreeCreate(                    COMPARE_FUNC)                                (GsTree *)          g_TreeCreate(                               GsTree, Gs *, gbTRUE, COMPARE_FUNC)
#define gsTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, GsTree, Gs *, gbTRUE, COMPARE_FUNC)
#define gsTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gsTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gsTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gsTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gsTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gsTreeFind(                TREE, VALUE)                                       (GsTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gsTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gsTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gsTreeGetBegin(            TREE)                                              (GsTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gsTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gsTreeGetEnd(              TREE)                                              (GsTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gsTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, TITEM)
#define gsTreeItemGet(                   TITEM)                                      ((Gs *)              g_TreeItemGet(             (G_Tree *) TREE, TITEM))
#define gsTreeItemGetNext(               TITEM)                                       (GsTreeItem *)      g_TreeItemGetNext(                          TITEM)
#define gsTreeItemGetPrev(               TITEM)                                       (GsTreeItem *)      g_TreeItemGetPrev(                          TITEM)
#define gsTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define gsTreeKeyAdd(              TREE, KEY, VALUE)                                  (GsTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gsTreeKeyCreate(                 COMPARE_FUNC)                                (GsTreeKey *)       g_TreeKeyCreate(                               GsTreeKey, Gs *, gbTRUE, COMPARE_FUNC)
#define gsTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GsTreeKey, Gs *, gbTRUE, COMPARE_FUNC)
#define gsTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gsTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gsTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gsTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gsTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gsTreeKeyFind(             TREE, KEY)                                         (GsTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gsTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gsTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gsTreeKeyGetBegin(         TREE)                                              (GsTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gsTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gsTreeKeyGetEnd(           TREE)                                              (GsTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gsTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gsTreeKeyItemGet(                TITEM)                                      ((Gs *)              g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gsTreeKeyItemGetNext(            TITEM)                                       (GsTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gsTreeKeyItemGetPrev(            TITEM)                                       (GsTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gsTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
