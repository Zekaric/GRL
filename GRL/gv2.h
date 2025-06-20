/**************************************************************************************************
file:       Gv2
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

#if !defined(GV2H)
#define      GV2H

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype
**************************************************************************************************/
grlAPI Gcompare    gv2CompareI(      Gv2 const * const va, Gv2 const * const vb);
grlAPI Gcompare    gv2CompareN(      Gv2 const * const va, Gv2 const * const vb);

grlAPI Gb          gv2GetB(          Gv2 const * const v);
grlAPI Gi2         gv2GetI(          Gv2 const * const v);
grlAPI Gn2         gv2GetN(          Gv2 const * const v);

grlAPI GhashN      gv2Hash(          Gv2 const * const v);

grlAPI Gv2        *gv2SetB(          Gv2       * const v, Gb   const value);
grlAPI Gv2        *gv2SetI(          Gv2       * const v, Gi   const value);
grlAPI Gv2        *gv2SetN(          Gv2       * const v, Gn   const value);

#define gv2GetB(V)       (V)->b
#define gv2GetI(V)       (V)->i
#define gv2GetN(V)       (V)->n

#define gv2SetB(V, VAL)  ((V)->b = VAL, (V))
#define gv2SetI(V, VAL)  ((V)->i = VAL, (V))
#define gv2SetN(V, VAL)  ((V)->n = VAL, (V))

/**************************************************************************************************
Gv2 containers.
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
   Gv2                      *p;
} Gv2Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gv2                       value;
} Gv2ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv2ArrayKeyCell          *p;
} Gv2ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gv2ListItem Gv2ListItem;
struct Gv2ListItem
{
   Gv2ListItem              *next,
                           *prev;
   Gv2                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv2ListItem              *head,
                           *tail;
} Gv2List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gv2ListKeyItem Gv2ListKeyItem;
struct Gv2ListKeyItem
{
   Gv2ListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gv2                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv2ListKeyItem           *head,
                           *tail;
} Gv2ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gv2List                **binArray;
   GhashSize               binCount;
} Gv2Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gv2ListKey             **binArray;
   GhashSize               binCount;
} Gv2HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gv2Tree     Gv2Tree;
typedef struct Gv2TreeItem Gv2TreeItem;
struct Gv2TreeItem
{
   Gv2Tree                  *owner;
   Gv2TreeItem              *parent;
   Gv2TreeItem              *childLeft;
   Gv2TreeItem              *childRight;
   GheapN                   heapValue;
   Gv2                       value;
};

struct Gv2Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gv2TreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gv2TreeKey     Gv2TreeKey;
typedef struct Gv2TreeKeyItem Gv2TreeKeyItem;
struct Gv2TreeKeyItem
{
   Gv2TreeKey               *owner;
   Gv2TreeKeyItem           *parent;
   Gv2TreeKeyItem           *childLeft;
   Gv2TreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gv2                       value;
};

struct Gv2TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gv2TreeKeyItem           *root;
};

#define gv2ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE)
#define gv2ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE)
#define gv2ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE)
#define gv2ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE)
#define gv2ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX)
#define gv2ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gv2ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC)
#define gv2ArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv2Array *)            g_ArrayCloc(                                  "Gv2Array", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv2ArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(        (G_Array *) ARRAY, "Gv2Array", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv2ArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY)
#define gv2ArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY)
#define gv2ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE)
#define gv2ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX)
#define gv2ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY)
#define gv2ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY)
#define gv2ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE)
#define gv2ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY)
#define gv2ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC)
#define gv2ArrayForEachDown(        ARRAY, FUNC)                                                               g_ArrayForEachDown(        (G_Array *) ARRAY, FUNC)
#define gv2ArrayGet(                ARRAY)                                            ((Gv2 *)                 g_ArrayGet(                (G_Array *) ARRAY))
#define gv2ArrayGetAt(              ARRAY, INDEX)                                     ((Gv2 *)                 g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gv2ArrayGetBegin(           ARRAY)                                            ((Gv2 *)                 g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gv2ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY)
#define gv2ArrayGetEnd(             ARRAY)                                            ((Gv2 *)                 g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gv2ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY)
#define gv2ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT)
#define gv2ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY)
#define gv2ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB)
#define gv2ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE)

#define gv2ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gv2ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE)
#define gv2ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gv2ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE)
#define gv2ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gv2ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gv2ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC)
#define gv2ArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv2Array *)             g_ArrayKeyCloc(                                "Gv2ArrayKey", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv2ArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "Gv2ArrayKey", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv2ArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY)
#define gv2ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gv2ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY)
#define gv2ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC)
#define gv2ArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gv2 *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gv2ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gv2ArrayKeyGetBegin(        ARRAY)                                            ((Gv2 *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gv2ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyGetEnd(          ARRAY)                                            ((Gv2 *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gv2ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY)
#define gv2ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY)
#define gv2ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT)
#define gv2ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY)
#define gv2ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB)
#define gv2ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE)
#define gv2ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY)

#define gv2ListAdd(                 LIST, VALUE)                                       (Gv2ListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gv2ListAddBegin(            LIST, VALUE)                                       (Gv2ListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gv2ListAddEnd(              LIST, VALUE)                                       (Gv2ListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gv2ListCloc(                      OPTIONAL_COMPARE_FUNC)                       (Gv2List *)              g_ListCloc(                               "Gv2List", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv2ListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "Gv2List", Gv2, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv2ListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gv2ListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gv2ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gv2ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gv2ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gv2ListFind(                LIST, VALUE)                                       (Gv2ListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gv2ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gv2ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gv2ListGetBegin(            LIST)                                              (Gv2ListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gv2ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gv2ListGetEnd(              LIST)                                              (Gv2ListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gv2ListItemAdd(             LIST, LITEM, VALUE)                                (Gv2ListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gv2ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gv2ListItemGet(                   LITEM)                                      ((Gv2 *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gv2ListItemGetNext(               LITEM)                                       (Gv2ListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gv2ListItemGetPrev(               LITEM)                                       (Gv2ListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gv2ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gv2ListKeyAdd(              LIST, KEY, VALUE)                                  (Gv2ListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv2ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gv2ListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv2ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gv2ListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv2ListKeyCloc(                   COMPARE_FUNC)                                (Gv2List *)              g_ListKeyCloc(                               "Gv2ListKey", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2ListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "Gv2ListKey", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2ListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gv2ListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gv2ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gv2ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gv2ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gv2ListKeyFind(             LIST, KEY)                                         (Gv2ListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gv2ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gv2ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gv2ListKeyGetBegin(         LIST)                                              (Gv2ListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gv2ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gv2ListKeyGetEnd(           LIST)                                              (Gv2ListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gv2ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gv2ListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gv2ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gv2ListKeyItemGet(                LITEM)                                      ((Gv2 *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gv2ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gv2ListKeyItemGetNext(            LITEM)                                       (Gv2ListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gv2ListKeyItemGetPrev(            LITEM)                                       (Gv2ListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gv2ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gv2ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gv2HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gv2HashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gv2Hash *)              g_HashCloc(                               "Gv2Hash", Gv2, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv2HashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "Gv2Hash", Gv2, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv2HashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gv2HashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gv2HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gv2HashFind(                HASH, VALUE)                                      ((Gv2 *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gv2HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gv2HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gv2HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gv2HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gv2HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gv2HashKeyCloc(                   HASHSIZE)                                    (Gv2HashKey *)           g_HashKeyCloc(                               "Gv2HashKey", Gv2, gbFALSE, HASHSIZE)
#define gv2HashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "Gv2HashKey", Gv2, gbFALSE, HASHSIZE)
#define gv2HashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gv2HashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gv2HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gv2HashKeyFind(             HASH, KEY)                                        ((Gv2 *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gv2HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gv2HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gv2HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gv2HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gv2TreeAdd(                 TREE, VALUE)                                       (Gv2TreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gv2TreeCloc(                      COMPARE_FUNC)                                (Gv2Tree *)              g_TreeCloc(                               "Gv2Tree", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2TreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "Gv2Tree", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2TreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gv2TreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gv2TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gv2TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gv2TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gv2TreeFind(                TREE, VALUE)                                       (Gv2TreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gv2TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gv2TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gv2TreeGetBegin(            TREE)                                              (Gv2TreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gv2TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gv2TreeGetEnd(              TREE)                                              (Gv2TreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gv2TreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gv2TreeItemGet(                   TITEM)                                      ((Gv2 *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gv2TreeItemGetNext(               TITEM)                                       (Gv2TreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gv2TreeItemGetPrev(               TITEM)                                       (Gv2TreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gv2TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gv2TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gv2TreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gv2TreeKeyCloc(                   COMPARE_FUNC)                                (Gv2TreeKey *)           g_TreeKeyCloc(                               "Gv2TreeKey", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2TreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "Gv2TreeKey", Gv2, gbFALSE, COMPARE_FUNC)
#define gv2TreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gv2TreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gv2TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gv2TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gv2TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gv2TreeKeyFind(             TREE, KEY)                                         (Gv2TreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gv2TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gv2TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gv2TreeKeyGetBegin(         TREE)                                              (Gv2TreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gv2TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gv2TreeKeyGetEnd(           TREE)                                              (Gv2TreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gv2TreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gv2TreeKeyItemGet(                TITEM)                                      ((Gv2 *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gv2TreeKeyItemGetNext(            TITEM)                                       (Gv2TreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gv2TreeKeyItemGetPrev(            TITEM)                                       (Gv2TreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gv2TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
