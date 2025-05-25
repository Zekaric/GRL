/**************************************************************************************************
file:       Gv8
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

#if !defined(GV8H)
#define      GV8H

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype
**************************************************************************************************/
grlAPI Gcompare    gv8CompareI(      Gv8 const * const va, Gv8 const * const vb);
grlAPI Gcompare    gv8CompareN(      Gv8 const * const va, Gv8 const * const vb);
grlAPI Gcompare    gv8CompareR(      Gv8 const * const va, Gv8 const * const vb);
grlAPI Gcompare    gv8CompareS(      Gv8 const * const va, Gv8 const * const vb);

grlAPI Gb          gv8GetB(          Gv8 const * const v);
grlAPI Gi          gv8GetI(          Gv8 const * const v);
grlAPI Gn          gv8GetN(          Gv8 const * const v);
grlAPI Gp         *gv8GetP(          Gv8 const * const v);
grlAPI Gr          gv8GetR(          Gv8 const * const v);
grlAPI Gs         *gv8GetS(          Gv8 const * const v);

grlAPI GhashN      gv8Hash(          Gv8 const * const v);

grlAPI Gv8        *gv8SetB(          Gv8       * const v, Gb   const value);
grlAPI Gv8        *gv8SetI(          Gv8       * const v, Gi   const value);
grlAPI Gv8        *gv8SetN(          Gv8       * const v, Gn   const value);
grlAPI Gv8        *gv8SetP(          Gv8       * const v, Gp * const value);
grlAPI Gv8        *gv8SetR(          Gv8       * const v, Gr   const value);
grlAPI Gv8        *gv8SetS(          Gv8       * const v, Gs * const value);

#define gv8GetB(V)       (V)->b
#define gv8GetI(V)       (V)->i
#define gv8GetN(V)       (V)->n
#define gv8GetP(V)       (V)->p
#define gv8GetR(V)       (V)->r
#define gv8GetS(V)       (V)->s

#define gv8SetB(V, VAL)  ((V)->b = VAL, (V))
#define gv8SetI(V, VAL)  ((V)->i = VAL, (V))
#define gv8SetN(V, VAL)  ((V)->n = VAL, (V))
#define gv8SetP(V, VAL)  ((V)->p = VAL, (V))
#define gv8SetR(V, VAL)  ((V)->r = VAL, (V))
#define gv8SetS(V, VAL)  ((V)->s = VAL, (V))

/**************************************************************************************************
Gv8 containers.
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
   Gv8                      *p;
} Gv8Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gv8                       value;
} Gv8ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv8ArrayKeyCell          *p;
} Gv8ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gv8ListItem Gv8ListItem;
struct Gv8ListItem
{
   Gv8ListItem              *next,
                           *prev;
   Gv8                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv8ListItem              *head,
                           *tail;
} Gv8List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gv8ListKeyItem Gv8ListKeyItem;
struct Gv8ListKeyItem
{
   Gv8ListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gv8                       value;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv8ListKeyItem           *head,
                           *tail;
} Gv8ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gv8List                **binArray;
   GhashSize               binCount;
} Gv8Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   Gv8ListKey             **binArray;
   GhashSize               binCount;
} Gv8HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gv8Tree     Gv8Tree;
typedef struct Gv8TreeItem Gv8TreeItem;
struct Gv8TreeItem
{
   Gv8Tree                  *owner;
   Gv8TreeItem              *parent;
   Gv8TreeItem              *childLeft;
   Gv8TreeItem              *childRight;
   GheapN                   heapValue;
   Gv8                       value;
};

struct Gv8Tree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gv8TreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gv8TreeKey     Gv8TreeKey;
typedef struct Gv8TreeKeyItem Gv8TreeKeyItem;
struct Gv8TreeKeyItem
{
   Gv8TreeKey               *owner;
   Gv8TreeKeyItem           *parent;
   Gv8TreeKeyItem           *childLeft;
   Gv8TreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gv8                       value;
};

struct Gv8TreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gv8TreeKeyItem           *root;
};

#define gv8ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv8ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv8ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv8ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv8ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gv8ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv8ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv8ArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv8Array *)             g_ArrayCloc(                                "Gv8Array", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv8ArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "Gv8Array", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv8ArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gv8ArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gv8ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv8ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gv8ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gv8ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gv8ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv8ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gv8ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gv8ArrayGet(                ARRAY)                                            ((Gv8 *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gv8ArrayGetAt(              ARRAY, INDEX)                                     ((Gv8 *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gv8ArrayGetBegin(           ARRAY)                                            ((Gv8 *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gv8ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gv8ArrayGetEnd(             ARRAY)                                            ((Gv8 *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gv8ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gv8ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gv8ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gv8ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gv8ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gv8ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv8ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gv8ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv8ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv8ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv8ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv8ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv8ArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv8Array *)             g_ArrayKeyCloc(                                "Gv8ArrayKey", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv8ArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "Gv8ArrayKey", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv8ArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gv8ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv8ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gv8ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gv8ArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gv8 *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gv8ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gv8ArrayKeyGetBegin(        ARRAY)                                            ((Gv8 *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gv8ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyGetEnd(          ARRAY)                                            ((Gv8 *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gv8ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gv8ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gv8ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gv8ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv8ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gv8ListAdd(                 LIST, VALUE)                                       (Gv8ListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gv8ListAddBegin(            LIST, VALUE)                                       (Gv8ListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gv8ListAddEnd(              LIST, VALUE)                                       (Gv8ListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gv8ListCloc(                      OPTIONAL_COMPARE_FUNC)                       (Gv8List *)              g_ListCloc(                               "Gv8List", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv8ListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "Gv8List", Gv8, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv8ListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gv8ListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gv8ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gv8ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gv8ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gv8ListFind(                LIST, VALUE)                                       (Gv8ListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gv8ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gv8ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gv8ListGetBegin(            LIST)                                              (Gv8ListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gv8ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gv8ListGetEnd(              LIST)                                              (Gv8ListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gv8ListItemAdd(             LIST, LITEM, VALUE)                                (Gv8ListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gv8ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gv8ListItemGet(                   LITEM)                                      ((Gv8 *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gv8ListItemGetNext(               LITEM)                                       (Gv8ListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gv8ListItemGetPrev(               LITEM)                                       (Gv8ListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gv8ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gv8ListKeyAdd(              LIST, KEY, VALUE)                                  (Gv8ListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv8ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gv8ListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv8ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gv8ListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv8ListKeyCloc(                   COMPARE_FUNC)                                (Gv8List *)              g_ListKeyCloc(                               "Gv8ListKey", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8ListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "Gv8ListKey", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8ListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gv8ListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gv8ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gv8ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gv8ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gv8ListKeyFind(             LIST, KEY)                                         (Gv8ListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gv8ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gv8ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gv8ListKeyGetBegin(         LIST)                                              (Gv8ListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gv8ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gv8ListKeyGetEnd(           LIST)                                              (Gv8ListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gv8ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gv8ListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gv8ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gv8ListKeyItemGet(                LITEM)                                      ((Gv8 *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gv8ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gv8ListKeyItemGetNext(            LITEM)                                       (Gv8ListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gv8ListKeyItemGetPrev(            LITEM)                                       (Gv8ListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gv8ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gv8ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gv8HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gv8HashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gv8Hash *)              g_HashCloc(                               "Gv8Hash", Gv8, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv8HashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "Gv8Hash", Gv8, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv8HashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gv8HashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gv8HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gv8HashFind(                HASH, VALUE)                                      ((Gv8 *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gv8HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gv8HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gv8HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gv8HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gv8HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gv8HashKeyCloc(                   HASHSIZE)                                    (Gv8HashKey *)           g_HashKeyCloc(                               "Gv8HashKey", Gv8, gbFALSE, HASHSIZE)
#define gv8HashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "Gv8HashKey", Gv8, gbFALSE, HASHSIZE)
#define gv8HashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gv8HashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gv8HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gv8HashKeyFind(             HASH, KEY)                                        ((Gv8 *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gv8HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gv8HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gv8HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gv8HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gv8TreeAdd(                 TREE, VALUE)                                       (Gv8TreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gv8TreeCloc(                      COMPARE_FUNC)                                (Gv8Tree *)              g_TreeCloc(                               "Gv8Tree", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8TreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "Gv8Tree", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8TreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gv8TreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gv8TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gv8TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gv8TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gv8TreeFind(                TREE, VALUE)                                       (Gv8TreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gv8TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gv8TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gv8TreeGetBegin(            TREE)                                              (Gv8TreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gv8TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gv8TreeGetEnd(              TREE)                                              (Gv8TreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gv8TreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gv8TreeItemGet(                   TITEM)                                      ((Gv8 *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gv8TreeItemGetNext(               TITEM)                                       (Gv8TreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gv8TreeItemGetPrev(               TITEM)                                       (Gv8TreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gv8TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gv8TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gv8TreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gv8TreeKeyCloc(                   COMPARE_FUNC)                                (Gv8TreeKey *)           g_TreeKeyCloc(                               "Gv8TreeKey", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8TreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "Gv8TreeKey", Gv8, gbFALSE, COMPARE_FUNC)
#define gv8TreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gv8TreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gv8TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gv8TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gv8TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gv8TreeKeyFind(             TREE, KEY)                                         (Gv8TreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gv8TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gv8TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gv8TreeKeyGetBegin(         TREE)                                              (Gv8TreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gv8TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gv8TreeKeyGetEnd(           TREE)                                              (Gv8TreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gv8TreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gv8TreeKeyItemGet(                TITEM)                                      ((Gv8 *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gv8TreeKeyItemGetNext(            TITEM)                                       (Gv8TreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gv8TreeKeyItemGetPrev(            TITEM)                                       (Gv8TreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gv8TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
