/**************************************************************************************************
file:       Gv4
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

#if !defined(GV4H)
#define      GV4H

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
prototype
**************************************************************************************************/
grlAPI Gcompare    gv4CompareI(      Gv4 const * const va, Gv4 const * const vb);
grlAPI Gcompare    gv4CompareN(      Gv4 const * const va, Gv4 const * const vb);
grlAPI Gcompare    gv4CompareR(      Gv4 const * const va, Gv4 const * const vb);
grlAPI Gcompare    gv4CompareS(      Gv4 const * const va, Gv4 const * const vb);

grlAPI Gb          gv4GetB(          Gv4 const * const v);
grlAPI Gi          gv4GetI(          Gv4 const * const v);
grlAPI Gn          gv4GetN(          Gv4 const * const v);
grlAPI Gp         *gv4GetP(          Gv4 const * const v);
grlAPI Gr          gv4GetR(          Gv4 const * const v);
grlAPI Gs         *gv4GetS(          Gv4 const * const v);

grlAPI GhashN      gv4Hash(          Gv4 const * const v);

grlAPI Gv4        *gv4SetB(          Gv4       * const v, Gb   const value);
grlAPI Gv4        *gv4SetI(          Gv4       * const v, Gi   const value);
grlAPI Gv4        *gv4SetN(          Gv4       * const v, Gn   const value);
grlAPI Gv4        *gv4SetP(          Gv4       * const v, Gp * const value);
grlAPI Gv4        *gv4SetR(          Gv4       * const v, Gr   const value);
grlAPI Gv4        *gv4SetS(          Gv4       * const v, Gs * const value);

#define gv4GetB(V)       (V)->b
#define gv4GetI(V)       (V)->i
#define gv4GetN(V)       (V)->n
#define gv4GetP(V)       (V)->p
#define gv4GetR(V)       (V)->r
#define gv4GetS(V)       (V)->s

#define gv4SetB(V, VAL)  ((V)->b = VAL, (V))
#define gv4SetI(V, VAL)  ((V)->i = VAL, (V))
#define gv4SetN(V, VAL)  ((V)->n = VAL, (V))
#define gv4SetP(V, VAL)  ((V)->p = VAL, (V))
#define gv4SetR(V, VAL)  ((V)->r = VAL, (V))
#define gv4SetS(V, VAL)  ((V)->s = VAL, (V))

/**************************************************************************************************
Gv4 containers.
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
   Gv4                      *p;
} Gv4Array;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gv4                       value;
} Gv4ArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv4ArrayKeyCell          *p;
} Gv4ArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct Gv4ListItem Gv4ListItem;
struct Gv4ListItem
{
   Gv4ListItem              *next,
                           *prev;
   Gv4                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv4ListItem              *head,
                           *tail;
} Gv4List;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct Gv4ListKeyItem Gv4ListKeyItem;
struct Gv4ListKeyItem
{
   Gv4ListKeyItem           *next,
                           *prev;
   Gkey const              *key;
   Gv4                       value;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   Gv4ListKeyItem           *head,
                           *tail;
} Gv4ListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc             hashFunc;
   GrlCompareFunc          compareFunc;
   Gv4List                **binArray;
   GhashSize               binCount;
} Gv4Hash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   Gv4ListKey             **binArray;
   GhashSize               binCount;
} Gv4HashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct Gv4Tree     Gv4Tree;
typedef struct Gv4TreeItem Gv4TreeItem;
struct Gv4TreeItem
{
   Gv4Tree                  *owner;
   Gv4TreeItem              *parent;
   Gv4TreeItem              *childLeft;
   Gv4TreeItem              *childRight;
   GheapN                   heapValue;
   Gv4                       value;
};

struct Gv4Tree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gv4TreeItem              *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct Gv4TreeKey     Gv4TreeKey;
typedef struct Gv4TreeKeyItem Gv4TreeKeyItem;
struct Gv4TreeKeyItem
{
   Gv4TreeKey               *owner;
   Gv4TreeKeyItem           *parent;
   Gv4TreeKeyItem           *childLeft;
   Gv4TreeKeyItem           *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gv4                       value;
};

struct Gv4TreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gv4TreeKeyItem           *root;
};

#define gv4ArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv4ArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv4ArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv4ArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gv4ArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gv4ArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv4ArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv4ArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv4Array *)             g_ArrayCloc(                                "Gv4Array", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv4ArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayClocContent(      (G_Array *) ARRAY, "Gv4Array", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gv4ArrayDloc(               ARRAY)                                                                     g_ArrayDloc(               (G_Array *) ARRAY) 
#define gv4ArrayDlocContent(        ARRAY)                                                                     g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gv4ArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv4ArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gv4ArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gv4ArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gv4ArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gv4ArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gv4ArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gv4ArrayGet(                ARRAY)                                            ((Gv4 *)                  g_ArrayGet(                (G_Array *) ARRAY))
#define gv4ArrayGetAt(              ARRAY, INDEX)                                     ((Gv4 *)                  g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gv4ArrayGetBegin(           ARRAY)                                            ((Gv4 *)                  g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gv4ArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gv4ArrayGetEnd(             ARRAY)                                            ((Gv4 *)                  g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gv4ArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gv4ArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gv4ArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gv4ArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gv4ArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gv4ArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv4ArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, VALUE) 
#define gv4ArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv4ArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, VALUE) 
#define gv4ArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv4ArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gv4ArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gv4ArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (Gv4Array *)             g_ArrayKeyCloc(                                "Gv4ArrayKey", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv4ArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "Gv4ArrayKey", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gv4ArrayKeyDloc(            ARRAY)                                                                     g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyDlocContent(     ARRAY)                                                                     g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gv4ArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gv4ArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gv4ArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gv4ArrayKeyGetAt(           ARRAY, INDEX)                                     ((Gv4 *)                  g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gv4ArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gv4ArrayKeyGetBegin(        ARRAY)                                            ((Gv4 *)                  g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gv4ArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyGetEnd(          ARRAY)                                            ((Gv4 *)                  g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gv4ArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gv4ArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gv4ArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gv4ArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gv4ArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gv4ListAdd(                 LIST, VALUE)                                       (Gv4ListItem *)          g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gv4ListAddBegin(            LIST, VALUE)                                       (Gv4ListItem *)          g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gv4ListAddEnd(              LIST, VALUE)                                       (Gv4ListItem *)          g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gv4ListCloc(                      OPTIONAL_COMPARE_FUNC)                       (Gv4List *)              g_ListCloc(                               "Gv4List", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv4ListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListClocContent(       (G_List *) LIST, "Gv4List", Gv4, gbFALSE, OPTIONAL_COMPARE_FUNC)
#define gv4ListDloc(                LIST)                                                                      g_ListDloc(                (G_List *) LIST)
#define gv4ListDlocContent(         LIST)                                                                      g_ListDlocContent(         (G_List *) LIST)
#define gv4ListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gv4ListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gv4ListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gv4ListFind(                LIST, VALUE)                                       (Gv4ListItem *)          g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gv4ListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gv4ListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gv4ListGetBegin(            LIST)                                              (Gv4ListItem *)          g_ListGetBegin(            (G_List *) LIST)
#define gv4ListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gv4ListGetEnd(              LIST)                                              (Gv4ListItem *)          g_ListGetEnd(              (G_List *) LIST)
#define gv4ListItemAdd(             LIST, LITEM, VALUE)                                (Gv4ListItem *)          g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gv4ListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gv4ListItemGet(                   LITEM)                                      ((Gv4 *)                  g_ListItemGet(                              (G_ListItem *) LITEM))
#define gv4ListItemGetNext(               LITEM)                                       (Gv4ListItem *)          g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gv4ListItemGetPrev(               LITEM)                                       (Gv4ListItem *)          g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gv4ListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gv4ListKeyAdd(              LIST, KEY, VALUE)                                  (Gv4ListKeyItem *)       g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv4ListKeyAddBegin(         LIST, KEY, VALUE)                                  (Gv4ListKeyItem *)       g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv4ListKeyAddEnd(           LIST, KEY, VALUE)                                  (Gv4ListKeyItem *)       g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gv4ListKeyCloc(                   COMPARE_FUNC)                                (Gv4List *)              g_ListKeyCloc(                               "Gv4ListKey", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4ListKeyClocContent(      LIST, COMPARE_FUNC)                                                        g_ListKeyClocContent(    (G_ListKey *) LIST, "Gv4ListKey", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4ListKeyDloc(             LIST)                                                                      g_ListKeyDloc(             (G_ListKey *) LIST)
#define gv4ListKeyDlocContent(      LIST)                                                                      g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gv4ListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gv4ListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gv4ListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gv4ListKeyFind(             LIST, KEY)                                         (Gv4ListKeyItem *)       g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gv4ListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gv4ListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gv4ListKeyGetBegin(         LIST)                                              (Gv4ListKeyItem *)       g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gv4ListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gv4ListKeyGetEnd(           LIST)                                              (Gv4ListKeyItem *)       g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gv4ListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (Gv4ListKeyItem *)       g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gv4ListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gv4ListKeyItemGet(                LITEM)                                      ((Gv4 *)                  g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gv4ListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gv4ListKeyItemGetNext(            LITEM)                                       (Gv4ListKeyItem *)       g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gv4ListKeyItemGetPrev(            LITEM)                                       (Gv4ListKeyItem *)       g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gv4ListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gv4ListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gv4HashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gv4HashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (Gv4Hash *)              g_HashCloc(                               "Gv4Hash", Gv4, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv4HashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashClocContent(       (G_Hash *) HASH, "Gv4Hash", Gv4, gbFALSE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gv4HashDloc(                HASH)                                                                      g_HashDloc(                (G_Hash *) HASH)
#define gv4HashDlocContent(         HASH)                                                                      g_HashDlocContent(         (G_Hash *) HASH)
#define gv4HashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gv4HashFind(                HASH, VALUE)                                      ((Gv4 *)                  g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gv4HashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gv4HashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gv4HashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gv4HashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gv4HashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gv4HashKeyCloc(                   HASHSIZE)                                    (Gv4HashKey *)           g_HashKeyCloc(                               "Gv4HashKey", Gv4, gbFALSE, HASHSIZE)
#define gv4HashKeyClocContent(      HASH, HASHSIZE)                                                            g_HashKeyClocContent(    (G_HashKey *) HASH, "Gv4HashKey", Gv4, gbFALSE, HASHSIZE)
#define gv4HashKeyDloc(             HASH)                                                                      g_HashKeyDloc(             (G_HashKey *) HASH)
#define gv4HashKeyDlocContent(      HASH)                                                                      g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gv4HashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gv4HashKeyFind(             HASH, KEY)                                        ((Gv4 *)                  g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gv4HashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gv4HashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gv4HashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gv4HashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gv4TreeAdd(                 TREE, VALUE)                                       (Gv4TreeItem *)          g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gv4TreeCloc(                      COMPARE_FUNC)                                (Gv4Tree *)              g_TreeCloc(                               "Gv4Tree", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4TreeClocContent(         TREE, COMPARE_FUNC)                                                        g_TreeClocContent(       (G_Tree *) TREE, "Gv4Tree", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4TreeDloc(                TREE)                                                                      g_TreeDloc(                (G_Tree *) TREE)
#define gv4TreeDlocContent(         TREE)                                                                      g_TreeDlocContent(         (G_Tree *) TREE)
#define gv4TreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gv4TreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gv4TreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gv4TreeFind(                TREE, VALUE)                                       (Gv4TreeItem *)          g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gv4TreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gv4TreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gv4TreeGetBegin(            TREE)                                              (Gv4TreeItem *)          g_TreeGetBegin(            (G_Tree *) TREE)
#define gv4TreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gv4TreeGetEnd(              TREE)                                              (Gv4TreeItem *)          g_TreeGetEnd(              (G_Tree *) TREE)
#define gv4TreeItemDloc(            TREE, TITEM)                                                               g_TreeItemDloc(            (G_Tree *) TREE, (G_TreeItem *) TITEM)
#define gv4TreeItemGet(                   TITEM)                                      ((Gv4 *)                  g_TreeItemGet(             (G_Tree *) TREE, (G_TreeItem *) TITEM))
#define gv4TreeItemGetNext(               TITEM)                                       (Gv4TreeItem *)          g_TreeItemGetNext(                          (G_TreeItem *) TITEM)
#define gv4TreeItemGetPrev(               TITEM)                                       (Gv4TreeItem *)          g_TreeItemGetPrev(                          (G_TreeItem *) TITEM)
#define gv4TreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, (G_TreeItem *) TITEM, (Gp *) VALUE)

#define gv4TreeKeyAdd(              TREE, KEY, VALUE)                                  (Gv4TreeKeyItem *)       g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gv4TreeKeyCloc(                   COMPARE_FUNC)                                (Gv4TreeKey *)           g_TreeKeyCloc(                               "Gv4TreeKey", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4TreeKeyClocContent(      TREE, COMPARE_FUNC)                                                        g_TreeKeyClocContent(    (G_TreeKey *) TREE, "Gv4TreeKey", Gv4, gbFALSE, COMPARE_FUNC)
#define gv4TreeKeyDloc(             TREE)                                                                      g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gv4TreeKeyDlocContent(      TREE)                                                                      g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gv4TreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gv4TreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gv4TreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gv4TreeKeyFind(             TREE, KEY)                                         (Gv4TreeKeyItem *)       g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gv4TreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gv4TreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gv4TreeKeyGetBegin(         TREE)                                              (Gv4TreeKeyItem *)       g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gv4TreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gv4TreeKeyGetEnd(           TREE)                                              (Gv4TreeKeyItem *)       g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gv4TreeKeyItemDloc(         TREE, TITEM)                                                               g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gv4TreeKeyItemGet(                TITEM)                                      ((Gv4 *)                  g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gv4TreeKeyItemGetNext(            TITEM)                                       (Gv4TreeKeyItem *)       g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gv4TreeKeyItemGetPrev(            TITEM)                                       (Gv4TreeKeyItem *)       g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gv4TreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
