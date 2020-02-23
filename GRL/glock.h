/******************************************************************************
file:       glock
author:     Robbert de Groot
copyright:  2009-2012, Robbert de Groot

description:
critical section lock routines.

Usage:

Initialize the lock

   Glock lock;

   glockCreateContent(&lock);

Enter critical section.

   glockEnter(&lock);

Exit critical section.

   glockExit(&lock);

Clean up lock.

   glockDestroyContent(&lock);
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

#if !defined(GLOCKH)
#define      GLOCKH

/******************************************************************************
type:
******************************************************************************/
#if grlWINDOWS == 1
typedef CRITICAL_SECTION Glock;
#else
#endif

/******************************************************************************
prototype:
******************************************************************************/
// Locking
grlAPI void       glockCreateContent(    Glock * const lock);

grlAPI void       glockDestroyContent(   Glock * const lock);

grlAPI void       glockEnter(            Glock * const lock);
grlAPI void       glockExit(             Glock * const lock);

/******************************************************************************
Glock containers.
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
   Glock                  **p;
} GlockArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   Glock                  *p;
} GlockArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GlockArrayKeyCell      **p;
} GlockArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GlockListItem GlockListItem;
struct GlockListItem
{
   GlockListItem           *next,
                           *prev;
   Glock                   *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GlockListItem           *head,
                           *tail;
} GlockList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GlockListKeyItem GlockListKeyItem;
struct GlockListKeyItem
{
   GlockListKeyItem        *next,
                           *prev;
   Gkey const              *key;
   Glock                   *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GlockListKeyItem        *head,
                           *tail;
} GlockListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GlockList              **binArray;
   GhashSize                binCount;
} GlockHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GlockListKey           **binArray;
   GhashSize                binCount;
} GlockHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GlockTree     GlockTree;
typedef struct GlockTreeItem GlockTreeItem;
struct GlockTreeItem
{
   GlockTree               *owner;
   GlockTreeItem           *parent;
   GlockTreeItem           *childLeft;
   GlockTreeItem           *childRight;
   GheapN                   heapValue;
   Glock                   *p;
};

struct GlockTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GlockTreeItem           *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GlockTreeKey     GlockTreeKey;
typedef struct GlockTreeKeyItem GlockTreeKeyItem;
struct GlockTreeKeyItem
{
   GlockTreeKey            *owner;
   GlockTreeKeyItem        *parent;
   GlockTreeKeyItem        *childLeft;
   GlockTreeKeyItem        *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Glock                   *p;
};

struct GlockTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GlockTreeKeyItem        *root;
};

#define glockArrayAdd(                ARRAY,        VALUE)                                                     g_ArrayAddP(               (G_Array *) ARRAY,        (Gp *) VALUE) 
#define glockArrayAddAt(              ARRAY, INDEX, VALUE)                                                     g_ArrayAddAtP(             (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define glockArrayAddBegin(           ARRAY,        VALUE)                                                     g_ArrayAddBeginP(          (G_Array *) ARRAY,        (Gp *) VALUE) 
#define glockArrayAddEnd(             ARRAY,        VALUE)                                                     g_ArrayAddEndP(            (G_Array *) ARRAY,        (Gp *) VALUE) 
#define glockArrayClear(              ARRAY, COUNT, INDEX)                                                     g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define glockArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define glockArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define glockArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GlockArray *)        g_ArrayCreate(                                GlockArray, Glock *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define glockArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayCreateContent(      (G_Array *) ARRAY, GlockArray, Glock *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define glockArrayDestroy(            ARRAY)                                                                   g_ArrayDestroy(            (G_Array *) ARRAY) 
#define glockArrayDestroyContent(     ARRAY)                                                                   g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define glockArrayErase(              ARRAY, VALUE)                                                            g_ArrayEraseP(             (G_Array *) ARRAY, (Gp *) VALUE) 
#define glockArrayEraseAt(            ARRAY, COUNT, INDEX)                                                     g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define glockArrayEraseBegin(         ARRAY)                                                                   g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define glockArrayEraseEnd(           ARRAY)                                                                   g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define glockArrayFind(               ARRAY, VALUE)                                                            g_ArrayFindP(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define glockArrayFlush(              ARRAY)                                                                   g_ArrayFlush(              (G_Array *) ARRAY) 
#define glockArrayForEach(            ARRAY, FUNC)                                                             g_ArrayForEachP(           (G_Array *) ARRAY, FUNC) 
#define glockArrayGet(                ARRAY)                                             (Glock **)            g_ArrayGet(                (G_Array *) ARRAY) 
#define glockArrayGetAt(              ARRAY, INDEX)                                      (Glock *)             g_ArrayGetAtP(             (G_Array *) ARRAY, INDEX))
#define glockArrayGetBegin(           ARRAY)                                             (Glock *)             g_ArrayGetBeginP(          (G_Array *) ARRAY))
#define glockArrayGetCount(           ARRAY)                                                                   g_ArrayGetCount(           (G_Array *) ARRAY) 
#define glockArrayGetEnd(             ARRAY)                                             (Glock *)             g_ArrayGetEndP(            (G_Array *) ARRAY))
#define glockArrayGetSize(            ARRAY)                                                                   g_ArrayGetSize(            (G_Array *) ARRAY) 
#define glockArraySetCount(           ARRAY, COUNT)                                                            g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define glockArraySort(               ARRAY)                                                                   g_ArraySort(               (G_Array *) ARRAY) 
#define glockArraySwap(               ARRAY, INDEXA, INDEXB)                                                   g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define glockArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                     g_ArrayUpdateAtP(          (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define glockArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define glockArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define glockArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define glockArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define glockArrayKeyClear(           ARRAY, COUNT, INDEX)                                                     g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define glockArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define glockArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define glockArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GlockArray *)        g_ArrayKeyCreate(                                GlockArray, Glock *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define glockArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GlockArray, Glock *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define glockArrayKeyDestroy(         ARRAY)                                                                   g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define glockArrayKeyDestroyContent(  ARRAY)                                                                   g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define glockArrayKeyErase(           ARRAY, KEY)                                                              g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define glockArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                     g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define glockArrayKeyEraseBegin(      ARRAY)                                                                   g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define glockArrayKeyEraseEnd(        ARRAY)                                                                   g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define glockArrayKeyFind(            ARRAY, KEY)                                                              g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define glockArrayKeyFlush(           ARRAY)                                                                   g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define glockArrayKeyForEach(         ARRAY, FUNC)                                                             g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define glockArrayKeyGetAt(           ARRAY, INDEX)                                    *((Glock **)            g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define glockArrayKeyGetAtKey(        ARRAY, INDEX)                                                            g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define glockArrayKeyGetBegin(        ARRAY)                                           *((Glock **)            g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define glockArrayKeyGetBeginKey(     ARRAY)                                                                   g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define glockArrayKeyGetCount(        ARRAY)                                                                   g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define glockArrayKeyGetEnd(          ARRAY)                                           *((Glock **)            g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define glockArrayKeyGetEndKey(       ARRAY)                                                                   g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define glockArrayKeyGetSize(         ARRAY)                                                                   g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define glockArrayKeySetCount(        ARRAY, COUNT)                                                            g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define glockArrayKeySort(            ARRAY)                                                                   g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define glockArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                   g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define glockArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                     g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define glockArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                       g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define glockListAdd(                 LIST, VALUE)                                       (GlockListItem *)     g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define glockListAddBegin(            LIST, VALUE)                                       (GlockListItem *)     g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define glockListAddEnd(              LIST, VALUE)                                       (GlockListItem *)     g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define glockListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GlockList *)         g_ListCreate(                               GlockList, Glock *, OPTIONAL_COMPARE_FUNC)
#define glockListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                             g_ListCreateContent(       (G_List *) LIST, GlockList, Glock *, OPTIONAL_COMPARE_FUNC)
#define glockListDestroy(             LIST)                                                                    g_ListDestroy(             (G_List *) LIST)
#define glockListDestroyContent(      LIST)                                                                    g_ListDestroyContent(      (G_List *) LIST)
#define glockListErase(               LIST, VALUE)                                                             g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define glockListEraseBegin(          LIST)                                                                    g_ListEraseBegin(          (G_List *) LIST)
#define glockListEraseEnd(            LIST)                                                                    g_ListEraseEnd(            (G_List *) LIST)
#define glockListFind(                LIST, VALUE)                                       (GlockListItem *)     g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define glockListFlush(               LIST)                                                                    g_ListFlush(               (G_List *) LIST)
#define glockListForEach(             LIST, FUNC)                                                              g_ListForEach(             (G_List *) LIST, FUNC)
#define glockListGetBegin(            LIST)                                              (GlockListItem *)     g_ListGetBegin(            (G_List *) LIST)
#define glockListGetCount(            LIST)                                                                    g_ListGetCount(            (G_List *) LIST)
#define glockListGetEnd(              LIST)                                              (GlockListItem *)     g_ListGetEnd(              (G_List *) LIST)
#define glockListItemAdd(             LIST, LITEM, VALUE)                                (GlockListItem *)     g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define glockListItemErase(           LIST, LITEM)                                                             g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define glockListItemGet(                   LITEM)                                     *((Glock **)            g_ListItemGet(                              (G_ListItem *) LITEM))
#define glockListItemGetNext(               LITEM)                                       (GlockListItem *)     g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define glockListItemGetPrev(               LITEM)                                       (GlockListItem *)     g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define glockListItemUpdate(          LIST, LITEM, VALUE)                                                      g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define glockListKeyAdd(              LIST, KEY, VALUE)                                  (GlockListKeyItem *)  g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define glockListKeyAddBegin(         LIST, KEY, VALUE)                                  (GlockListKeyItem *)  g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define glockListKeyAddEnd(           LIST, KEY, VALUE)                                  (GlockListKeyItem *)  g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define glockListKeyCreate(                 COMPARE_FUNC)                                (GlockList *)         g_ListKeyCreate(                 GlockListKey, Glock *, COMPARE_FUNC)
#define glockListKeyCreateContent(    LIST, COMPARE_FUNC)                                                      g_ListKeyCreateContent(    (G_ListKey *) LIST, GlockListKey, Glock *, COMPARE_FUNC)
#define glockListKeyDestroy(          LIST)                                                                    g_ListKeyDestroy(          (G_ListKey *) LIST)
#define glockListKeyDestroyContent(   LIST)                                                                    g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define glockListKeyErase(            LIST, KEY)                                                               g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define glockListKeyEraseBegin(       LIST)                                                                    g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define glockListKeyEraseEnd(         LIST)                                                                    g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define glockListKeyFind(             LIST, KEY)                                         (GlockListKeyItem *)  g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define glockListKeyFlush(            LIST)                                                                    g_ListKeyFlush(            (G_ListKey *) LIST)
#define glockListKeyForEach(          LIST, FUNC)                                                              g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define glockListKeyGetBegin(         LIST)                                              (GlockListKeyItem *)  g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define glockListKeyGetCount(         LIST)                                                                    g_ListKeyGetCount(         (G_ListKey *) LIST)
#define glockListKeyGetEnd(           LIST)                                              (GlockListKeyItem *)  g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define glockListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GlockListKeyItem *)  g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define glockListKeyItemErase(        LIST, LITEM)                                                             g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define glockListKeyItemGet(          LIST, LITEM)                                     *((Glock **)            g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define glockListKeyItemGetKey(       LIST, LITEM)                                                             g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define glockListKeyItemGetNext(      LIST, LITEM)                                       (GlockListKeyItem *)  g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define glockListKeyItemGetPrev(      LIST, LITEM)                                       (GlockListKeyItem *)  g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define glockListKeyItemUpdate(       LIST, LITEM, VALUE)                                                      g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define glockListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                        g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define glockHashAdd(                 HASH, VALUE)                                                             g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define glockHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GlockHash *)         g_HashCreate(                               GlockHash, Glock *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define glockHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                 g_HashCreateContent(       (G_Hash *) HASH, GlockHash, Glock *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define glockHashDestroy(             HASH)                                                                    g_HashDestroy(             (G_Hash *) HASH)
#define glockHashDestroyContent(      HASH)                                                                    g_HashDestroyContent(      (G_Hash *) HASH)
#define glockHashErase(               HASH, VALUE)                                                             g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define glockHashFind(                HASH, VALUE)                                     *((Glock **)            g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define glockHashFlush(               HASH)                                                                    g_HashFlush(               (G_Hash *) HASH)
#define glockHashForEach(             HASH, FUNC)                                                              g_HashForEach(             (G_Hash *) HASH, FUNC)
#define glockHashGetCount(            HASH)                                                                    g_HashGetCount(            (G_Hash *) HASH)
#define glockHashUpdate(              HASH, VALUE)                                                             g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define glockHashKeyAdd(              HASH, KEY, VALUE)                                                        g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define glockHashKeyCreate(                 HASHSIZE)                                    (GlockHashKey *)      g_HashKeyCreate(                               GlockHashKey, Glock *, HASHSIZE)
#define glockHashKeyCreateContent(    HASH, HASHSIZE)                                                          g_HashKeyCreateContent(    (G_HashKey *) HASH, GlockHashKey, Glock *, HASHSIZE)
#define glockHashKeyDestroy(          HASH)                                                                    g_HashKeyDestroy(          (G_HashKey *) HASH)
#define glockHashKeyDestroyContent(   HASH)                                                                    g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define glockHashKeyErase(            HASH, KEY)                                                               g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define glockHashKeyFind(             HASH, KEY)                                       *((Glock **)            g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define glockHashKeyFlush(            HASH)                                                                    g_HashKeyFlush(            (G_HashKey *) HASH)
#define glockHashKeyForEach(          HASH, FUNC)                                                              g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define glockHashKeyGetCount(         HASH)                                                                    g_HashKeyGetCount(         (G_HashKey *) HASH)
#define glockHashKeyUpdate(           HASH, KEY, VALUE)                                                        g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define glockTreeAdd(                 TREE, VALUE)                                       (GlockTreeItem *)     g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define glockTreeCreate(                    COMPARE_FUNC)                                (GlockTree *)         g_TreeCreate(                    GlockTree, Glock *, COMPARE_FUNC)
#define glockTreeCreateContent(       TREE, COMPARE_FUNC)                                                      g_TreeCreateContent(       (G_Tree *) TREE, GlockTree, Glock *, COMPARE_FUNC)
#define glockTreeDestroy(             TREE)                                                                    g_TreeDestroy(             (G_Tree *) TREE)
#define glockTreeDestroyContent(      TREE)                                                                    g_TreeDestroyContent(      (G_Tree *) TREE)
#define glockTreeErase(               TREE, VALUE)                                                             g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define glockTreeEraseBegin(          TREE)                                                                    g_TreeEraseBegin(          (G_Tree *) TREE)
#define glockTreeEraseEnd(            TREE)                                                                    g_TreeEraseEnd(            (G_Tree *) TREE)
#define glockTreeFind(                TREE, VALUE)                                       (GlockTreeItem *)     g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define glockTreeFlush(               TREE)                                                                    g_TreeFlush(               (G_Tree *) TREE)
#define glockTreeForEach(             TREE, FUNC)                                                              g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define glockTreeGetBegin(            TREE)                                              (GlockTreeItem *)     g_TreeGetBegin(            (G_Tree *) TREE)
#define glockTreeGetCount(            TREE)                                                                    g_TreeGetCount(            (G_Tree *) TREE)
#define glockTreeGetEnd(              TREE)                                              (GlockTreeItem *)     g_TreeGetEnd(              (G_Tree *) TREE)
#define glockTreeItemDestroy(         TREE, TITEM)                                                             g_TreeItemDestroy(         (G_Tree *) TREE, TITEM)
#define glockTreeItemGet(                   TITEM)                                     *((Glock **)            g_TreeItemGet(                              TITEM))
#define glockTreeItemGetNext(               TITEM)                                       (GlockTreeItem *)     g_TreeItemGetNext(                          TITEM)
#define glockTreeItemGetPrev(               TITEM)                                       (GlockTreeItem *)     g_TreeItemGetPrev(                          TITEM)
#define glockTreeItemUpdate(          TREE, TITEM, VALUE)                                                      g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define glockTreeKeyAdd(              TREE, KEY, VALUE)                                  (GlockTreeKeyItem *)  g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define glockTreeKeyCreate(                 COMPARE_FUNC)                                (GlockTreeKey *)      g_TreeKeyCreate(                               GlockTreeKey, Glock *, COMPARE_FUNC)
#define glockTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                      g_TreeKeyCreateContent(    (G_TreeKey *) TREE, GlockTreeKey, Glock *, COMPARE_FUNC)
#define glockTreeKeyDestroy(          TREE)                                                                    g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define glockTreeKeyDestroyContent(   TREE)                                                                    g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define glockTreeKeyErase(            TREE, KEY)                                                               g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define glockTreeKeyEraseBegin(       TREE)                                                                    g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define glockTreeKeyEraseEnd(         TREE)                                                                    g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define glockTreeKeyFind(             TREE, KEY)                                         (GlockTreeKeyItem *)  g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define glockTreeKeyFlush(            TREE)                                                                    g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define glockTreeKeyForEach(          TREE, FUNC)                                                              g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define glockTreeKeyGetBegin(         TREE)                                              (GlockTreeKeyItem *)  g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define glockTreeKeyGetCount(         TREE)                                                                    g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define glockTreeKeyGetEnd(           TREE)                                              (GlockTreeKeyItem *)  g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define glockTreeKeyItemDestroy(      TREE, TITEM)                                                             g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define glockTreeKeyItemGet(                TITEM)                                     *((Glock **)            g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM))
#define glockTreeKeyItemGetNext(            TITEM)                                       (GlockTreeKeyItem *)  g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define glockTreeKeyItemGetPrev(            TITEM)                                       (GlockTreeKeyItem *)  g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define glockTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                      g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

#endif
