/**************************************************************************************************
file:       Gvp
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

#if !defined(GVPH)
#define      GVPH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype
**************************************************************************************************/
grlAPI Gcompare    gvpCompareI(      Gvp const * const va, Gvp const * const vb);
grlAPI Gcompare    gvpCompareN(      Gvp const * const va, Gvp const * const vb);
grlAPI Gcompare    gvpCompareR(      Gvp const * const va, Gvp const * const vb);
grlAPI Gcompare    gvpCompareS(      Gvp const * const va, Gvp const * const vb);

grlAPI Gb          gvpGetB(          Gvp const * const v);
grlAPI Gi          gvpGetI(          Gvp const * const v);
grlAPI Gn          gvpGetN(          Gvp const * const v);
grlAPI Gp         *gvpGetP(          Gvp const * const v);
grlAPI Gr          gvpGetR(          Gvp const * const v);
grlAPI Gs         *gvpGetS(          Gvp const * const v);

grlAPI GhashN      gvpHash(          Gvp const * const v);


grlAPI Gvp         *gvpSetB(         Gvp       * const v, Gb   const value);
grlAPI Gvp         *gvpSetI(         Gvp       * const v, Gi   const value);
grlAPI Gvp         *gvpSetN(         Gvp       * const v, Gn   const value);
grlAPI Gvp         *gvpSetP(         Gvp       * const v, Gp * const value);
grlAPI Gvp         *gvpSetR(         Gvp       * const v, Gr   const value);
grlAPI Gvp         *gvpSetS(         Gvp       * const v, Gs * const value);

#define gvpGetB(V)       (V)->b
#define gvpGetI(V)       (V)->i
#define gvpGetN(V)       (V)->n
#define gvpGetP(V)       (V)->p
#define gvpGetR(V)       (V)->r
#define gvpGetS(V)       (V)->s

#define gvpSetB(V, VAL)  ((V)->b = VAL, (V))
#define gvpSetI(V, VAL)  ((V)->i = VAL, (V))
#define gvpSetN(V, VAL)  ((V)->n = VAL, (V))
#define gvpSetP(V, VAL)  ((V)->p = VAL, (V))
#define gvpSetR(V, VAL)  ((V)->r = VAL, (V))
#define gvpSetS(V, VAL)  ((V)->s = VAL, (V))

/**************************************************************************************************
Gvp containers.
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
   Gvp                      *p;
} GvpArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gvp                       value;
} GvpArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GvpArrayKeyCell          *p;
} GvpArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GvpListItem GvpListItem;
struct GvpListItem
{
   GvpListItem              *next,
                           *prev;
   Gvp                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvpListItem              *head,
                           *tail;
} GvpList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GvpListKeyItem GvpListKeyItem;
struct GvpListKeyItem
{
   GvpListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gvp                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvpListKeyItem           *head,
                           *tail;
} GvpListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   GvpList                **binArray;
   GhashSize               binCount;
} GvpHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GvpListKey             **binArray;
   GhashSize               binCount;
} GvpHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GvpTree     GvpTree;
typedef struct GvpTreeItem GvpTreeItem;
struct GvpTreeItem
{
   GvpTree                  *owner;
   GvpTreeItem              *parent;
   GvpTreeItem              *childLeft;
   GvpTreeItem              *childRight;
   GheapN                   heapValue;
   Gvp                       value;
};

struct GvpTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GvpTreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GvpTreeKey     GvpTreeKey;
typedef struct GvpTreeKeyItem GvpTreeKeyItem;
struct GvpTreeKeyItem
{
   GvpTreeKey               *owner;
   GvpTreeKeyItem           *parent;
   GvpTreeKeyItem           *childLeft;
   GvpTreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gvp                       value;
};

struct GvpTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GvpTreeKeyItem           *root;
};

#define gvpArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE)
#define gvpArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE)
#define gvpArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE)
#define gvpArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE)
#define gvpArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX)
#define gvpArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gvpArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC)
#define gvpArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvpArray *)            g_ArrayCloc(                                  "GvpArray", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvpArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(        (G_Array *) ARRAY, "GvpArray", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvpArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY)
#define gvpArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY)
#define gvpArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE)
#define gvpArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX)
#define gvpArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY)
#define gvpArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY)
#define gvpArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE)
#define gvpArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY)
#define gvpArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC)
#define gvpArrayForEachDown(        ARRAY, FUNC)                                                               g_ArrayForEachDown(        (G_Array *) ARRAY, FUNC)
#define gvpArrayGet(                ARRAY)                                            ((Gvp *)                 g_ArrayGet(                (G_Array *) ARRAY))
#define gvpArrayGetAt(              ARRAY, INDEX)                                     ((Gvp *)                 g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gvpArrayGetBegin(           ARRAY)                                            ((Gvp *)                 g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gvpArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY)
#define gvpArrayGetEnd(             ARRAY)                                            ((Gvp *)                 g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gvpArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY)
#define gvpArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT)
#define gvpArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY)
#define gvpArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB)
#define gvpArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE)

#define gvpArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gvpArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE)
#define gvpArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gvpArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gvpArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gvpArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gvpArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC)
#define gvpArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvpArray *)             g_ArrayKeyCloc(                                "GvpArrayKey", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvpArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GvpArrayKey", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvpArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY)
#define gvpArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY)
#define gvpArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY)
#define gvpArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gvpArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY)
#define gvpArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY)
#define gvpArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY)
#define gvpArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY)
#define gvpArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC)
#define gvpArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gvp *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gvpArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gvpArrayKeyGetBegin(        ARRAY)                                            ((Gvp *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gvpArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY)
#define gvpArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY)
#define gvpArrayKeyGetEnd(          ARRAY)                                            ((Gvp *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gvpArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY)
#define gvpArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY)
#define gvpArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT)
#define gvpArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY)
#define gvpArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB)
#define gvpArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE)
#define gvpArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY)

#define gvpListAdd(                 LIST, VALUE)                                       (GvpListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gvpListAddBegin(            LIST, VALUE)                                       (GvpListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gvpListAddEnd(              LIST, VALUE)                                       (GvpListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gvpListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GvpList *)              g_ListCloc(                               "GvpList", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gvpListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "GvpList", Gvp, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gvpListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gvpListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gvpListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gvpListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gvpListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gvpListFind(                LIST, VALUE)                                       (GvpListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gvpListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gvpListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gvpListGetBegin(            LIST)                                              (GvpListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gvpListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gvpListGetEnd(              LIST)                                              (GvpListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gvpListItemAdd(             LIST, LITEM, VALUE)                                (GvpListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gvpListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gvpListItemGet(                   LITEM)                                      ((Gvp *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gvpListItemGetNext(               LITEM)                                       (GvpListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gvpListItemGetPrev(               LITEM)                                       (GvpListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gvpListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gvpListKeyAdd(              LIST, KEY, VALUE)                                  (GvpListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvpListKeyAddBegin(         LIST, KEY, VALUE)                                  (GvpListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvpListKeyAddEnd(           LIST, KEY, VALUE)                                  (GvpListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvpListKeyCloc(                   COMPARE_FUNC)                                (GvpList *)              g_ListKeyCloc(                               "GvpListKey", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "GvpListKey", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gvpListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gvpListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gvpListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gvpListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gvpListKeyFind(             LIST, KEY)                                         (GvpListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gvpListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gvpListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gvpListKeyGetBegin(         LIST)                                              (GvpListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gvpListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gvpListKeyGetEnd(           LIST)                                              (GvpListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gvpListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GvpListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gvpListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gvpListKeyItemGet(                LITEM)                                      ((Gvp *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gvpListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gvpListKeyItemGetNext(            LITEM)                                       (GvpListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gvpListKeyItemGetPrev(            LITEM)                                       (GvpListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gvpListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gvpListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gvpHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gvpHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GvpHash *)              g_HashCloc(                               "GvpHash", Gvp, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvpHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "GvpHash", Gvp, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvpHashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gvpHashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gvpHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gvpHashFind(                HASH, VALUE)                                      ((Gvp *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gvpHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gvpHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gvpHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gvpHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gvpHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gvpHashKeyCloc(                   HASHSIZE)                                    (GvpHashKey *)           g_HashKeyCloc(                               "GvpHashKey", Gvp, gbFALSE, HASHSIZE)
#define gvpHashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "GvpHashKey", Gvp, gbFALSE, HASHSIZE)
#define gvpHashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gvpHashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gvpHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gvpHashKeyFind(             HASH, KEY)                                        ((Gvp *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gvpHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gvpHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gvpHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gvpHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gvpTreeAdd(                 TREE, VALUE)                                       (GvpTreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gvpTreeCloc(                      COMPARE_FUNC)                                (GvpTree *)              g_TreeCloc(                               "GvpTree", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpTreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "GvpTree", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpTreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gvpTreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gvpTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gvpTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gvpTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gvpTreeFind(                TREE, VALUE)                                       (GvpTreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gvpTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gvpTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gvpTreeGetBegin(            TREE)                                              (GvpTreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gvpTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gvpTreeGetEnd(              TREE)                                              (GvpTreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gvpTreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gvpTreeItemGet(                   TITEM)                                      ((Gvp *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gvpTreeItemGetNext(               TITEM)                                       (GvpTreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gvpTreeItemGetPrev(               TITEM)                                       (GvpTreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gvpTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gvpTreeKeyAdd(              TREE, KEY, VALUE)                                  (GvpTreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gvpTreeKeyCloc(                   COMPARE_FUNC)                                (GvpTreeKey *)           g_TreeKeyCloc(                               "GvpTreeKey", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GvpTreeKey", Gvp, gbFALSE, COMPARE_FUNC)
#define gvpTreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gvpTreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gvpTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gvpTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gvpTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gvpTreeKeyFind(             TREE, KEY)                                         (GvpTreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gvpTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gvpTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gvpTreeKeyGetBegin(         TREE)                                              (GvpTreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gvpTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gvpTreeKeyGetEnd(           TREE)                                              (GvpTreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gvpTreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gvpTreeKeyItemGet(                TITEM)                                      ((Gvp *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gvpTreeKeyItemGetNext(            TITEM)                                       (GvpTreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gvpTreeKeyItemGetPrev(            TITEM)                                       (GvpTreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gvpTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
