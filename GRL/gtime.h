/******************************************************************************
file:       gtime
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
base time functions
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

#if !defined(GTIMEH)
#define      GTIMEH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
constant:
******************************************************************************/
typedef enum
{
   GtimeDST_UNKNOWN = -1,
   GtimeDST_INACTIVE,
   GtimeDST_ACTIVE
} GtimeDST;

/******************************************************************************
type:
******************************************************************************/
/*lint -save -e960 */
#if grlWINDOWS == 1

#define gtimeNONE Gi8MIN

typedef __time64_t Gtime;

#endif

#if defined(MACOSX)

typedef time_t Gtime;

#endif
/*lint -restore */

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gtime gtimeGet(         void);
grlAPI Gb    gtimeGetTime(     Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);
grlAPI Gb    gtimeGetTimeLocal(Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);

// Start and Stop called in grlStart and grtStop
       Gb    gtimeStart(       void);
       void  gtimeStop(        void);

/******************************************************************************
Gtime containers.
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
   Gtime                   *p;
} GtimeArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gtime                    value;
} GtimeArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GtimeArrayKeyCell       *p;
} GtimeArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GtimeListItem GtimeListItem;
struct GtimeListItem
{
   GtimeListItem           *next,
                           *prev;
   Gtime                    value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GtimeListItem           *head,
                           *tail;
} GtimeList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GtimeListKeyItem GtimeListKeyItem;
struct GtimeListKeyItem
{
   GtimeListKeyItem        *next,
                           *prev;
   Gkey const              *key;
   Gtime                    value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GtimeListKeyItem        *head,
                           *tail;
} GtimeListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GtimeList             **binArray;
   GhashSize               binCount;
} GtimeHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GtimeListKey          **binArray;
   GhashSize               binCount;
} GtimeHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GtimeTree     GtimeTree;
typedef struct GtimeTreeItem GtimeTreeItem;
struct GtimeTreeItem
{
   GtimeTree               *owner;
   GtimeTreeItem           *parent;
   GtimeTreeItem           *childLeft;
   GtimeTreeItem           *childRight;
   GheapN                   heapValue;
   Gtime                    value;
};

struct GtimeTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GtimeTreeItem           *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GtimeTreeKey     GtimeTreeKey;
typedef struct GtimeTreeKeyItem GtimeTreeKeyItem;
struct GtimeTreeKeyItem
{
   GtimeTreeKey            *owner;
   GtimeTreeKeyItem        *parent;
   GtimeTreeKeyItem        *childLeft;
   GtimeTreeKeyItem        *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gtime                    value;
};

struct GtimeTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GtimeTreeKeyItem        *root;
};

#define gtimeArrayAdd(                ARRAY,        VALUE)                                                     g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gtimeArrayAddAt(              ARRAY, INDEX, VALUE)                                                     g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gtimeArrayAddBegin(           ARRAY,        VALUE)                                                     g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gtimeArrayAddEnd(             ARRAY,        VALUE)                                                     g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gtimeArrayClear(              ARRAY, COUNT, INDEX)                                                     g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gtimeArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gtimeArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gtimeArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GtimeArray *)        g_ArrayCreate(                                "GtimeArray", Gtime, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gtimeArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayCreateContent(      (G_Array *) ARRAY, "GtimeArray", Gtime, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gtimeArrayDestroy(            ARRAY)                                                                   g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gtimeArrayDestroyContent(     ARRAY)                                                                   g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gtimeArrayErase(              ARRAY, VALUE)                                                            g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gtimeArrayEraseAt(            ARRAY, COUNT, INDEX)                                                     g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gtimeArrayEraseBegin(         ARRAY)                                                                   g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gtimeArrayEraseEnd(           ARRAY)                                                                   g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gtimeArrayFind(               ARRAY, VALUE)                                                            g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gtimeArrayFlush(              ARRAY)                                                                   g_ArrayFlush(              (G_Array *) ARRAY) 
#define gtimeArrayForEach(            ARRAY, FUNC)                                                             g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gtimeArrayGet(                ARRAY)                                             (Gtime *)             g_ArrayGet(                (G_Array *) ARRAY) 
#define gtimeArrayGetAt(              ARRAY, INDEX)                                      (Gtime *)             g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gtimeArrayGetBegin(           ARRAY)                                             (Gtime *)             g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gtimeArrayGetCount(           ARRAY)                                                                   g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gtimeArrayGetEnd(             ARRAY)                                             (Gtime *)             g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gtimeArrayGetSize(            ARRAY)                                                                   g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gtimeArraySetCount(           ARRAY, COUNT)                                                            g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gtimeArraySort(               ARRAY)                                                                   g_ArraySort(               (G_Array *) ARRAY) 
#define gtimeArraySwap(               ARRAY, INDEXA, INDEXB)                                                   g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gtimeArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                     g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gtimeArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gtimeArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gtimeArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gtimeArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gtimeArrayKeyClear(           ARRAY, COUNT, INDEX)                                                     g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gtimeArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gtimeArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gtimeArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GtimeArray *)        g_ArrayKeyCreate(                                "GtimeArrayKey", Gtime, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gtimeArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GtimeArrayKey", Gtime, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gtimeArrayKeyDestroy(         ARRAY)                                                                   g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyDestroyContent(  ARRAY)                                                                   g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyErase(           ARRAY, KEY)                                                              g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gtimeArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                     g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gtimeArrayKeyEraseBegin(      ARRAY)                                                                   g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyEraseEnd(        ARRAY)                                                                   g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyFind(            ARRAY, KEY)                                                              g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gtimeArrayKeyFlush(           ARRAY)                                                                   g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyForEach(         ARRAY, FUNC)                                                             g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gtimeArrayKeyGetAt(           ARRAY, INDEX)                                      (Gtime *)             g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX) 
#define gtimeArrayKeyGetAtKey(        ARRAY, INDEX)                                                            g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gtimeArrayKeyGetBegin(        ARRAY)                                             (Gtime *)             g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyGetBeginKey(     ARRAY)                                                                   g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyGetCount(        ARRAY)                                                                   g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyGetEnd(          ARRAY)                                             (Gtime *)             g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyGetEndKey(       ARRAY)                                                                   g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeyGetSize(         ARRAY)                                                                   g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeySetCount(        ARRAY, COUNT)                                                            g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gtimeArrayKeySort(            ARRAY)                                                                   g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gtimeArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                   g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gtimeArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                     g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gtimeArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                       g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gtimeListAdd(                 LIST, VALUE)                                       (GtimeListItem *)     g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gtimeListAddBegin(            LIST, VALUE)                                       (GtimeListItem *)     g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gtimeListAddEnd(              LIST, VALUE)                                       (GtimeListItem *)     g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gtimeListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GtimeList *)         g_ListCreate(                               "GtimeList", Gtime, OPTIONAL_COMPARE_FUNC)
#define gtimeListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                             g_ListCreateContent(       (G_List *) LIST, "GtimeList", Gtime, OPTIONAL_COMPARE_FUNC)
#define gtimeListDestroy(             LIST)                                                                    g_ListDestroy(             (G_List *) LIST)
#define gtimeListDestroyContent(      LIST)                                                                    g_ListDestroyContent(      (G_List *) LIST)
#define gtimeListErase(               LIST, VALUE)                                                             g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gtimeListEraseBegin(          LIST)                                                                    g_ListEraseBegin(          (G_List *) LIST)
#define gtimeListEraseEnd(            LIST)                                                                    g_ListEraseEnd(            (G_List *) LIST)
#define gtimeListFind(                LIST, VALUE)                                       (GtimeListItem *)     g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gtimeListFlush(               LIST)                                                                    g_ListFlush(               (G_List *) LIST)
#define gtimeListForEach(             LIST, FUNC)                                                              g_ListForEach(             (G_List *) LIST, FUNC)
#define gtimeListGetBegin(            LIST)                                              (GtimeListItem *)     g_ListGetBegin(            (G_List *) LIST)
#define gtimeListGetCount(            LIST)                                                                    g_ListGetCount(            (G_List *) LIST)
#define gtimeListGetEnd(              LIST)                                              (GtimeListItem *)     g_ListGetEnd(              (G_List *) LIST)
#define gtimeListItemAdd(             LIST, LITEM, VALUE)                                (GtimeListItem *)     g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gtimeListItemErase(           LIST, LITEM)                                                             g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gtimeListItemGet(                   LITEM)                                       (Gtime *)             g_ListItemGet(                              (G_ListItem *) LITEM)
#define gtimeListItemGetNext(               LITEM)                                       (GtimeListItem *)     g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gtimeListItemGetPrev(               LITEM)                                       (GtimeListItem *)     g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gtimeListItemUpdate(          LIST, LITEM, VALUE)                                                      g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gtimeListKeyAdd(              LIST, KEY, VALUE)                                  (GtimeListKeyItem *)  g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gtimeListKeyAddBegin(         LIST, KEY, VALUE)                                  (GtimeListKeyItem *)  g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gtimeListKeyAddEnd(           LIST, KEY, VALUE)                                  (GtimeListKeyItem *)  g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gtimeListKeyCreate(                 COMPARE_FUNC)                                (GtimeList *)         g_ListKeyCreate(                               "GtimeListKey", Gtime, COMPARE_FUNC)
#define gtimeListKeyCreateContent(    LIST, COMPARE_FUNC)                                                      g_ListKeyCreateContent(    (G_ListKey *) LIST, "GtimeListKey", Gtime, COMPARE_FUNC)
#define gtimeListKeyDestroy(          LIST)                                                                    g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gtimeListKeyDestroyContent(   LIST)                                                                    g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gtimeListKeyErase(            LIST, KEY)                                                               g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gtimeListKeyEraseBegin(       LIST)                                                                    g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gtimeListKeyEraseEnd(         LIST)                                                                    g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gtimeListKeyFind(             LIST, KEY)                                         (GtimeListKeyItem *)  g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gtimeListKeyFlush(            LIST)                                                                    g_ListKeyFlush(            (G_ListKey *) LIST)
#define gtimeListKeyForEach(          LIST, FUNC)                                                              g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gtimeListKeyGetBegin(         LIST)                                              (GtimeListKeyItem *)  g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gtimeListKeyGetCount(         LIST)                                                                    g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gtimeListKeyGetEnd(           LIST)                                              (GtimeListKeyItem *)  g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gtimeListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GtimeListKeyItem *)  g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gtimeListKeyItemErase(        LIST, LITEM)                                                             g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gtimeListKeyItemGet(                LITEM)                                       (Gtime *)             g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM)
#define gtimeListKeyItemGetKey(             LITEM)                                                             g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gtimeListKeyItemGetNext(            LITEM)                                       (GtimeListKeyItem *)  g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gtimeListKeyItemGetPrev(            LITEM)                                       (GtimeListKeyItem *)  g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gtimeListKeyItemUpdate(       LIST, LITEM, VALUE)                                                      g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gtimeListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                        g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gtimeHashAdd(                 HASH, VALUE)                                                             g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gtimeHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GtimeHash *)         g_HashCreate(                               "GtimeHash", Gtime, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gtimeHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                 g_HashCreateContent(       (G_Hash *) HASH, "GtimeHash", Gtime, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gtimeHashDestroy(             HASH)                                                                    g_HashDestroy(             (G_Hash *) HASH)
#define gtimeHashDestroyContent(      HASH)                                                                    g_HashDestroyContent(      (G_Hash *) HASH)
#define gtimeHashErase(               HASH, VALUE)                                                             g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gtimeHashFind(                HASH, VALUE)                                       (Gtime *)             g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE)
#define gtimeHashFlush(               HASH)                                                                    g_HashFlush(               (G_Hash *) HASH)
#define gtimeHashForEach(             HASH, FUNC)                                                              g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gtimeHashGetCount(            HASH)                                                                    g_HashGetCount(            (G_Hash *) HASH)
#define gtimeHashUpdate(              HASH, VALUE)                                                             g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gtimeHashKeyAdd(              HASH, KEY, VALUE)                                                        g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gtimeHashKeyCreate(                 HASHSIZE)                                    (GtimeHashKey *)      g_HashKeyCreate(                               "GtimeHashKey", Gtime, HASHSIZE)
#define gtimeHashKeyCreateContent(    HASH, HASHSIZE)                                                          g_HashKeyCreateContent(    (G_HashKey *) HASH, "GtimeHashKey", Gtime, HASHSIZE)
#define gtimeHashKeyDestroy(          HASH)                                                                    g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gtimeHashKeyDestroyContent(   HASH)                                                                    g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gtimeHashKeyErase(            HASH, KEY)                                                               g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gtimeHashKeyFind(             HASH, KEY)                                         (Gtime *)             g_HashKeyFind(             (G_HashKey *) HASH, KEY)
#define gtimeHashKeyFlush(            HASH)                                                                    g_HashKeyFlush(            (G_HashKey *) HASH)
#define gtimeHashKeyForEach(          HASH, FUNC)                                                              g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gtimeHashKeyGetCount(         HASH)                                                                    g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gtimeHashKeyUpdate(           HASH, KEY, VALUE)                                                        g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gtimeTreeAdd(                 TREE, VALUE)                                       (GtimeTreeItem *)     g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gtimeTreeCreate(                    COMPARE_FUNC)                                (GtimeTree *)         g_TreeCreate(                               "GtimeTree", Gtime, COMPARE_FUNC)
#define gtimeTreeCreateContent(       TREE, COMPARE_FUNC)                                                      g_TreeCreateContent(       (G_Tree *) TREE, "GtimeTree", Gtime, COMPARE_FUNC)
#define gtimeTreeDestroy(             TREE)                                                                    g_TreeDestroy(             (G_Tree *) TREE)
#define gtimeTreeDestroyContent(      TREE)                                                                    g_TreeDestroyContent(      (G_Tree *) TREE)
#define gtimeTreeErase(               TREE, VALUE)                                                             g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gtimeTreeEraseBegin(          TREE)                                                                    g_TreeEraseBegin(          (G_Tree *) TREE)
#define gtimeTreeEraseEnd(            TREE)                                                                    g_TreeEraseEnd(            (G_Tree *) TREE)
#define gtimeTreeFind(                TREE, VALUE)                                       (GtimeTreeItem *)     g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gtimeTreeFlush(               TREE)                                                                    g_TreeFlush(               (G_Tree *) TREE)
#define gtimeTreeForEach(             TREE, FUNC)                                                              g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gtimeTreeGetBegin(            TREE)                                              (GtimeTreeItem *)     g_TreeGetBegin(            (G_Tree *) TREE)
#define gtimeTreeGetCount(            TREE)                                                                    g_TreeGetCount(            (G_Tree *) TREE)
#define gtimeTreeGetEnd(              TREE)                                              (GtimeTreeItem *)     g_TreeGetEnd(              (G_Tree *) TREE)
#define gtimeTreeItemDestroy(         TREE, TITEM)                                                             g_TreeItemDestroy(         (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gtimeTreeItemGet(                   TITEM)                                       (Gtime *)             g_TreeItemGet(                              (G_TreeItem *) TITEM)
#define gtimeTreeItemGetNext(               TITEM)                                       (GtimeTreeItem *)     g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gtimeTreeItemGetPrev(               TITEM)                                       (GtimeTreeItem *)     g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gtimeTreeItemUpdate(          TREE, TITEM, VALUE)                                                      g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gtimeTreeKeyAdd(              TREE, KEY, VALUE)                                  (GtimeTreeKeyItem *)  g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gtimeTreeKeyCreate(                 COMPARE_FUNC)                                (GtimeTreeKey *)      g_TreeKeyCreate(                               "GtimeTreeKey", Gtime, COMPARE_FUNC)
#define gtimeTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                      g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GtimeTreeKey", Gtime, COMPARE_FUNC)
#define gtimeTreeKeyDestroy(          TREE)                                                                    g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gtimeTreeKeyDestroyContent(   TREE)                                                                    g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gtimeTreeKeyErase(            TREE, KEY)                                                               g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gtimeTreeKeyEraseBegin(       TREE)                                                                    g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gtimeTreeKeyEraseEnd(         TREE)                                                                    g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gtimeTreeKeyFind(             TREE, KEY)                                         (GtimeTreeKeyItem *)  g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gtimeTreeKeyFlush(            TREE)                                                                    g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gtimeTreeKeyForEach(          TREE, FUNC)                                                              g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gtimeTreeKeyGetBegin(         TREE)                                              (GtimeTreeKeyItem *)  g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gtimeTreeKeyGetCount(         TREE)                                                                    g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gtimeTreeKeyGetEnd(           TREE)                                              (GtimeTreeKeyItem *)  g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gtimeTreeKeyItemDestroy(      TREE, TITEM)                                                             g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gtimeTreeKeyItemGet(                TITEM)                                       (Gtime *)             g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM)
#define gtimeTreeKeyItemGetNext(            TITEM)                                       (GtimeTreeKeyItem *)  g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gtimeTreeKeyItemGetPrev(            TITEM)                                       (GtimeTreeKeyItem *)  g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gtimeTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                      g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
