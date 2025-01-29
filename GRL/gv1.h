/**************************************************************************************************
file:       Gv1
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

#if !defined(GV1H)
#define      GV1H

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype
**************************************************************************************************/
grlAPI Gcompare    gv1CompareI(      Gv1 const * const va, Gv1 const * const vb);
grlAPI Gcompare    gv1CompareN(      Gv1 const * const va, Gv1 const * const vb);

grlAPI Gb          gv1GetB(          Gv1 const * const v);
grlAPI Gi          gv1GetI(          Gv1 const * const v);
grlAPI Gn          gv1GetN(          Gv1 const * const v);

grlAPI GhashN      gv1Hash(          Gv1 const * const v);

grlAPI Gv1        *gv1SetB(          Gv1       * const v, Gb   const value);
grlAPI Gv1        *gv1SetI(          Gv1       * const v, Gi   const value);
grlAPI Gv1        *gv1SetN(          Gv1       * const v, Gn   const value);

#define gv1GetB(V)       (V)->b
#define gv1GetI(V)       (V)->i
#define gv1GetN(V)       (V)->n

#define gv1SetB(V, VAL)  ((V)->b = VAL, (V))
#define gv1SetI(V, VAL)  ((V)->i = VAL, (V))
#define gv1SetN(V, VAL)  ((V)->n = VAL, (V))

/**************************************************************************************************
Gv1 containers.
**************************************************************************************************/
// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gv1                      *p;
} Gv1Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gv1                       value;
} Gv1ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv1ArrayKeyCell          *p;
} Gv1ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gv1ListItem Gv1ListItem;
struct Gv1ListItem
{
   Gv1ListItem              *next,
                           *prev;
   Gv1                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv1ListItem              *head,
                           *tail;
} Gv1List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gv1ListKeyItem Gv1ListKeyItem;
struct Gv1ListKeyItem
{
   Gv1ListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gv1                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv1ListKeyItem           *head,
                           *tail;
} Gv1ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gv1List                **binArray;
   GhashSize               binCount;
} Gv1Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   Gv1ListKey             **binArray;
   GhashSize               binCount;
} Gv1HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gv1Tree     Gv1Tree;
typedef struct Gv1TreeItem Gv1TreeItem;
struct Gv1TreeItem
{
   Gv1Tree                  *owner;
   Gv1TreeItem              *parent;
   Gv1TreeItem              *childLeft;
   Gv1TreeItem              *childRight;
   GheapN                   heapValue;
   Gv1                       value;
};

struct Gv1Tree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gv1TreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gv1TreeKey     Gv1TreeKey;
typedef struct Gv1TreeKeyItem Gv1TreeKeyItem;
struct Gv1TreeKeyItem
{
   Gv1TreeKey               *owner;
   Gv1TreeKeyItem           *parent;
   Gv1TreeKeyItem           *childLeft;
   Gv1TreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gv1                       value;
};

struct Gv1TreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gv1TreeKeyItem           *root;
};

#define gv1ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv1ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv1ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv1ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv1ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gv1ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv1ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv1ArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv1Array *)             g_ArrayCloc(                                "Gv1Array", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv1ArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "Gv1Array", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv1ArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gv1ArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gv1ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv1ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gv1ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gv1ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gv1ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv1ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gv1ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gv1ArrayGet(                ARRAY)                                            ((Gv1 *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gv1ArrayGetAt(              ARRAY, INDEX)                                     ((Gv1 *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gv1ArrayGetBegin(           ARRAY)                                            ((Gv1 *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gv1ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gv1ArrayGetEnd(             ARRAY)                                            ((Gv1 *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gv1ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gv1ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gv1ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gv1ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gv1ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gv1ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv1ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gv1ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv1ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv1ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv1ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv1ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv1ArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv1Array *)             g_ArrayKeyCloc(                                "Gv1ArrayKey", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv1ArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "Gv1ArrayKey", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv1ArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gv1ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv1ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gv1ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gv1ArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gv1 *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gv1ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gv1ArrayKeyGetBegin(        ARRAY)                                            ((Gv1 *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gv1ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyGetEnd(          ARRAY)                                            ((Gv1 *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gv1ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gv1ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gv1ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gv1ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv1ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gv1ListAdd(                 LIST, VALUE)                                       (Gv1ListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gv1ListAddBegin(            LIST, VALUE)                                       (Gv1ListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gv1ListAddEnd(              LIST, VALUE)                                       (Gv1ListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gv1ListCloc(                      OPTIONAL_COMPARE_FUNC)                       (Gv1List *)              g_ListCloc(                               "Gv1List", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv1ListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "Gv1List", Gv1, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv1ListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gv1ListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gv1ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gv1ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gv1ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gv1ListFind(                LIST, VALUE)                                       (Gv1ListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gv1ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gv1ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gv1ListGetBegin(            LIST)                                              (Gv1ListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gv1ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gv1ListGetEnd(              LIST)                                              (Gv1ListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gv1ListItemAdd(             LIST, LITEM, VALUE)                                (Gv1ListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gv1ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gv1ListItemGet(                   LITEM)                                      ((Gv1 *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gv1ListItemGetNext(               LITEM)                                       (Gv1ListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gv1ListItemGetPrev(               LITEM)                                       (Gv1ListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gv1ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gv1ListKeyAdd(              LIST, KEY, VALUE)                                  (Gv1ListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv1ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gv1ListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv1ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gv1ListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv1ListKeyCloc(                   COMPARE_FUNC)                                (Gv1List *)              g_ListKeyCloc(                               "Gv1ListKey", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1ListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "Gv1ListKey", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1ListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gv1ListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gv1ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gv1ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gv1ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gv1ListKeyFind(             LIST, KEY)                                         (Gv1ListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gv1ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gv1ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gv1ListKeyGetBegin(         LIST)                                              (Gv1ListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gv1ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gv1ListKeyGetEnd(           LIST)                                              (Gv1ListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gv1ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gv1ListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gv1ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gv1ListKeyItemGet(                LITEM)                                      ((Gv1 *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gv1ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gv1ListKeyItemGetNext(            LITEM)                                       (Gv1ListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gv1ListKeyItemGetPrev(            LITEM)                                       (Gv1ListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gv1ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gv1ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gv1HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gv1HashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gv1Hash *)              g_HashCloc(                               "Gv1Hash", Gv1, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv1HashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "Gv1Hash", Gv1, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv1HashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gv1HashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gv1HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gv1HashFind(                HASH, VALUE)                                      ((Gv1 *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gv1HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gv1HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gv1HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gv1HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gv1HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gv1HashKeyCloc(                   HASHSIZE)                                    (Gv1HashKey *)           g_HashKeyCloc(                               "Gv1HashKey", Gv1, gbFALSE, HASHSIZE)
#define gv1HashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "Gv1HashKey", Gv1, gbFALSE, HASHSIZE)
#define gv1HashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gv1HashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gv1HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gv1HashKeyFind(             HASH, KEY)                                        ((Gv1 *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gv1HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gv1HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gv1HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gv1HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gv1TreeAdd(                 TREE, VALUE)                                       (Gv1TreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gv1TreeCloc(                      COMPARE_FUNC)                                (Gv1Tree *)              g_TreeCloc(                               "Gv1Tree", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1TreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "Gv1Tree", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1TreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gv1TreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gv1TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gv1TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gv1TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gv1TreeFind(                TREE, VALUE)                                       (Gv1TreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gv1TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gv1TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gv1TreeGetBegin(            TREE)                                              (Gv1TreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gv1TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gv1TreeGetEnd(              TREE)                                              (Gv1TreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gv1TreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gv1TreeItemGet(                   TITEM)                                      ((Gv1 *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gv1TreeItemGetNext(               TITEM)                                       (Gv1TreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gv1TreeItemGetPrev(               TITEM)                                       (Gv1TreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gv1TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gv1TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gv1TreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gv1TreeKeyCloc(                   COMPARE_FUNC)                                (Gv1TreeKey *)           g_TreeKeyCloc(                               "Gv1TreeKey", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1TreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "Gv1TreeKey", Gv1, gbFALSE, COMPARE_FUNC)
#define gv1TreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gv1TreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gv1TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gv1TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gv1TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gv1TreeKeyFind(             TREE, KEY)                                         (Gv1TreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gv1TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gv1TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gv1TreeKeyGetBegin(         TREE)                                              (Gv1TreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gv1TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gv1TreeKeyGetEnd(           TREE)                                              (Gv1TreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gv1TreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gv1TreeKeyItemGet(                TITEM)                                      ((Gv1 *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gv1TreeKeyItemGetNext(            TITEM)                                       (Gv1TreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gv1TreeKeyItemGetPrev(            TITEM)                                       (Gv1TreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gv1TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
