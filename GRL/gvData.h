/******************************************************************************
file:       gvDataData
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
A data type that holds all types of data.  
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

#if !defined(GVDATAH)
#define      GVDATAH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
const:
******************************************************************************/
#define gvDataTYPE_I "GvData:I"
#define gvDataTYPE_N "GvData:N"
#define gvDataTYPE_P "GvData:P"
#define gvDataTYPE_R "GvData:R"
#define gvDataTYPE_V "GvData"

// type defined in gconst.h

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9026
grlAPI Gcompare    gpCompare(           Gp     const * const valueA, Gp const * const valueB);

// gvData is a simple light data holder.  Use carfully.
grlAPI Gcompare    gvDataCompareI(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareN(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareP(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareR(      GvData const * const valueA, GvData const * const valueB);

grlAPI GvData     *gvDataCreate(        void);
grlAPI Gb          gvDataCreateContent( GvData       * const v);

grlAPI void        gvDataDestroy(       GvData       * const v);
grlAPI void        gvDataDestroyContent(GvData       * const v);

grlAPI GvData      gvDataFromI(         Gi             const value);
grlAPI GvData      gvDataFromN(         Gn             const value);
grlAPI GvData      gvDataFromP(         Gp           * const value);
grlAPI GvData      gvDataFromR(         Gr             const value);
grlAPI GvData      gvDataFromS(         Gs           * const value);

grlAPI Gi          gvDataGetI(          GvData const * const v);
grlAPI Gn          gvDataGetN(          GvData const * const v);
grlAPI Gp         *gvDataGetP(          GvData const * const v);
grlAPI Gr          gvDataGetR(          GvData const * const v);
grlAPI Gs         *gvDataGetS(          GvData const * const v);

grlAPI GhashN      gvDataHash(          GvData const * const value);
grlAPI GhashN      gvDataHashS(         GvData const * const value);

grlAPI Gb          gvDataSetI(          GvData       * const v, Gi   const value);
grlAPI Gb          gvDataSetN(          GvData       * const v, Gn   const value);
grlAPI Gb          gvDataSetP(          GvData       * const v, Gp * const value);
grlAPI Gb          gvDataSetR(          GvData       * const v, Gr   const value);
grlAPI Gb          gvDataSetS(          GvData       * const v, Gs * const value);

//lint -restore

/******************************************************************************
GvData containers.
******************************************************************************/
/******************************************************************************
GvData containers.
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
   GvData                 **p;
} GvDataArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   GvData                  *p;
} GvDataArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GvDataArrayKeyCell     **p;
} GvDataArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GvDataListItem GvDataListItem;
struct GvDataListItem
{
   GvDataListItem          *next,
                           *prev;
   GvData                  *p;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvDataListItem          *head,
                           *tail;
} GvDataList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GvDataListKeyItem GvDataListKeyItem;
struct GvDataListKeyItem
{
   GvDataListKeyItem       *next,
                           *prev;
   Gkey const              *key;
   GvData                  *p;
};

typedef struct
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GvDataListKeyItem       *head,
                           *tail;
} GvDataListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GvDataList             **binArray;
   GhashSize                binCount;
} GvDataHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR

   GvDataListKey          **binArray;
   GhashSize                binCount;
} GvDataHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GvDataTree     GvDataTree;
typedef struct GvDataTreeItem GvDataTreeItem;
struct GvDataTreeItem
{
   GvDataTree              *owner;
   GvDataTreeItem          *parent;
   GvDataTreeItem          *childLeft;
   GvDataTreeItem          *childRight;
   GheapN                   heapValue;
   GvData                  *p;
};

struct GvDataTree
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GvDataTreeItem          *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GvDataTreeKey     GvDataTreeKey;
typedef struct GvDataTreeKeyItem GvDataTreeKeyItem;
struct GvDataTreeKeyItem
{
   GvDataTreeKey           *owner;
   GvDataTreeKeyItem       *parent;
   GvDataTreeKeyItem       *childLeft;
   GvDataTreeKeyItem       *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   GvData                  *p;
};

struct GvDataTreeKey
{
   GCONTAINER_VAR

   GrlCompareFunc           compareFunc;
   GvDataTreeKeyItem       *root;
};

#define gvDataArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvDataArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gvDataArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvDataArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gvDataArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gvDataArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvDataArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gvDataArrayCreate(                    OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvDataArray *)         g_ArrayCreate(                                "GvDataArray", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvDataArrayCreateContent(      ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayCreateContent(      (G_Array *) ARRAY, "GvDataArray", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gvDataArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gvDataArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gvDataArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gvDataArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gvDataArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gvDataArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gvDataArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gvDataArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gvDataArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gvDataArrayGet(                ARRAY)                                            ((GvData **)             g_ArrayGet(                (G_Array *) ARRAY))
#define gvDataArrayGetAt(              ARRAY, INDEX)                                     ((GvData *)              g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gvDataArrayGetBegin(           ARRAY)                                            ((GvData *)              g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gvDataArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gvDataArrayGetEnd(             ARRAY)                                            ((GvData *)              g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gvDataArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gvDataArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gvDataArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gvDataArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gvDataArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gvDataArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gvDataArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                  g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define gvDataArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gvDataArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                  g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gvDataArrayKeyClear(           ARRAY, COUNT, INDEX)                                                       g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gvDataArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gvDataArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gvDataArrayKeyCreate(                 OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GvDataArray *)         g_ArrayKeyCreate(                                "GvDataArray", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvDataArrayKeyCreateContent(   ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                            g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, "GvDataArray", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gvDataArrayKeyDestroy(         ARRAY)                                                                     g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyDestroyContent(  ARRAY)                                                                     g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyErase(           ARRAY, KEY)                                                                g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gvDataArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                       g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gvDataArrayKeyEraseBegin(      ARRAY)                                                                     g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyEraseEnd(        ARRAY)                                                                     g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyFind(            ARRAY, KEY)                                                                g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gvDataArrayKeyFlush(           ARRAY)                                                                     g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyForEach(         ARRAY, FUNC)                                                               g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gvDataArrayKeyGetAt(           ARRAY, INDEX)                                     ((GvData *)              g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gvDataArrayKeyGetAtKey(        ARRAY, INDEX)                                                              g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gvDataArrayKeyGetBegin(        ARRAY)                                            ((GvData *)              g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gvDataArrayKeyGetBeginKey(     ARRAY)                                                                     g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyGetCount(        ARRAY)                                                                     g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyGetEnd(          ARRAY)                                            ((GvData *)              g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gvDataArrayKeyGetEndKey(       ARRAY)                                                                     g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeyGetSize(         ARRAY)                                                                     g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeySetCount(        ARRAY, COUNT)                                                              g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gvDataArrayKeySort(            ARRAY)                                                                     g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gvDataArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                     g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gvDataArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                       g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gvDataArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                         g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gvDataListAdd(                 LIST, VALUE)                                       (GvDataListItem *)      g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gvDataListAddBegin(            LIST, VALUE)                                       (GvDataListItem *)      g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gvDataListAddEnd(              LIST, VALUE)                                       (GvDataListItem *)      g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gvDataListCreate(                    OPTIONAL_COMPARE_FUNC)                       (GvDataList *)          g_ListCreate(                               "GvDataList", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gvDataListCreateContent(       LIST, OPTIONAL_COMPARE_FUNC)                                               g_ListCreateContent(       (G_List *) LIST, "GvDataList", GvData *, gbTRUE, OPTIONAL_COMPARE_FUNC)
#define gvDataListDestroy(             LIST)                                                                      g_ListDestroy(             (G_List *) LIST)
#define gvDataListDestroyContent(      LIST)                                                                      g_ListDestroyContent(      (G_List *) LIST)
#define gvDataListErase(               LIST, VALUE)                                                               g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gvDataListEraseBegin(          LIST)                                                                      g_ListEraseBegin(          (G_List *) LIST)
#define gvDataListEraseEnd(            LIST)                                                                      g_ListEraseEnd(            (G_List *) LIST)
#define gvDataListFind(                LIST, VALUE)                                       (GvDataListItem *)      g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gvDataListFlush(               LIST)                                                                      g_ListFlush(               (G_List *) LIST)
#define gvDataListForEach(             LIST, FUNC)                                                                g_ListForEach(             (G_List *) LIST, FUNC)
#define gvDataListGetBegin(            LIST)                                              (GvDataListItem *)      g_ListGetBegin(            (G_List *) LIST)
#define gvDataListGetCount(            LIST)                                                                      g_ListGetCount(            (G_List *) LIST)
#define gvDataListGetEnd(              LIST)                                              (GvDataListItem *)      g_ListGetEnd(              (G_List *) LIST)
#define gvDataListItemAdd(             LIST, LITEM, VALUE)                                (GvDataListItem *)      g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gvDataListItemErase(           LIST, LITEM)                                                               g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gvDataListItemGet(             LIST, LITEM)                                      ((GvData *)              g_ListItemGet(                              (G_ListItem *) LITEM))
#define gvDataListItemGetNext(               LITEM)                                       (GvDataListItem *)      g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gvDataListItemGetPrev(               LITEM)                                       (GvDataListItem *)      g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gvDataListItemUpdate(          LIST, LITEM, VALUE)                                                        g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gvDataListKeyAdd(              LIST, KEY, VALUE)                                  (GvDataListKeyItem *)   g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvDataListKeyAddBegin(         LIST, KEY, VALUE)                                  (GvDataListKeyItem *)   g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvDataListKeyAddEnd(           LIST, KEY, VALUE)                                  (GvDataListKeyItem *)   g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gvDataListKeyCreate(                 COMPARE_FUNC)                                (GvDataList *)          g_ListKeyCreate(                               "GvDataListKey", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataListKeyCreateContent(    LIST, COMPARE_FUNC)                                                        g_ListKeyCreateContent(    (G_ListKey *) LIST, "GvDataListKey", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataListKeyDestroy(          LIST)                                                                      g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gvDataListKeyDestroyContent(   LIST)                                                                      g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gvDataListKeyErase(            LIST, KEY)                                                                 g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gvDataListKeyEraseBegin(       LIST)                                                                      g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gvDataListKeyEraseEnd(         LIST)                                                                      g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gvDataListKeyFind(             LIST, KEY)                                         (GvDataListKeyItem *)   g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gvDataListKeyFlush(            LIST)                                                                      g_ListKeyFlush(            (G_ListKey *) LIST)
#define gvDataListKeyForEach(          LIST, FUNC)                                                                g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gvDataListKeyGetBegin(         LIST)                                              (GvDataListKeyItem *)   g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gvDataListKeyGetCount(         LIST)                                                                      g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gvDataListKeyGetEnd(           LIST)                                              (GvDataListKeyItem *)   g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gvDataListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GvDataListKeyItem *)   g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gvDataListKeyItemErase(        LIST, LITEM)                                                               g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gvDataListKeyItemGet(                LITEM)                                      ((GvData *)              g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gvDataListKeyItemGetKey(             LITEM)                                                               g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gvDataListKeyItemGetNext(            LITEM)                                       (GvDataListKeyItem *)   g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gvDataListKeyItemGetPrev(            LITEM)                                       (GvDataListKeyItem *)   g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gvDataListKeyItemUpdate(       LIST, LITEM, VALUE)                                                        g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gvDataListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                          g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gvDataHashAdd(                 HASH, VALUE)                                                               g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gvDataHashCreate(                    COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GvDataHash *)          g_HashCreate(                               "GvDataHash", GvData *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvDataHashCreateContent(       HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                   g_HashCreateContent(       (G_Hash *) HASH, "GvDataHash", GvData *, gbTRUE, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gvDataHashDestroy(             HASH)                                                                      g_HashDestroy(             (G_Hash *) HASH)
#define gvDataHashDestroyContent(      HASH)                                                                      g_HashDestroyContent(      (G_Hash *) HASH)
#define gvDataHashErase(               HASH, VALUE)                                                               g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gvDataHashFind(                HASH, VALUE)                                      ((GvData *)              g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gvDataHashFlush(               HASH)                                                                      g_HashFlush(               (G_Hash *) HASH)
#define gvDataHashForEach(             HASH, FUNC)                                                                g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gvDataHashGetCount(            HASH)                                                                      g_HashGetCount(            (G_Hash *) HASH)
#define gvDataHashUpdate(              HASH, VALUE)                                                               g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gvDataHashKeyAdd(              HASH, KEY, VALUE)                                                          g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gvDataHashKeyCreate(                 HASHSIZE)                                    (GvDataHashKey *)       g_HashKeyCreate(                               "GvDataHashKey", GvData *, gbTRUE, HASHSIZE)
#define gvDataHashKeyCreateContent(    HASH, HASHSIZE)                                                            g_HashKeyCreateContent(    (G_HashKey *) HASH, "GvDataHashKey", GvData *, gbTRUE, HASHSIZE)
#define gvDataHashKeyDestroy(          HASH)                                                                      g_HashKeyDestroy(          (G_HashKey *) HASH)
#define gvDataHashKeyDestroyContent(   HASH)                                                                      g_HashKeyDestroyContent(   (G_HashKey *) HASH)
#define gvDataHashKeyErase(            HASH, KEY)                                                                 g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gvDataHashKeyFind(             HASH, KEY)                                        ((GvData *)              g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gvDataHashKeyFlush(            HASH)                                                                      g_HashKeyFlush(            (G_HashKey *) HASH)
#define gvDataHashKeyForEach(          HASH, FUNC)                                                                g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gvDataHashKeyGetCount(         HASH)                                                                      g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gvDataHashKeyUpdate(           HASH, KEY, VALUE)                                                          g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gvDataTreeAdd(                 TREE, VALUE)                                       (GvDataTreeItem *)      g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gvDataTreeCreate(                    COMPARE_FUNC)                                (GvDataTree *)          g_TreeCreate(                               "GvDataTree", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataTreeCreateContent(       TREE, COMPARE_FUNC)                                                        g_TreeCreateContent(       (G_Tree *) TREE, "GvDataTree", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataTreeDestroy(             TREE)                                                                      g_TreeDestroy(             (G_Tree *) TREE)
#define gvDataTreeDestroyContent(      TREE)                                                                      g_TreeDestroyContent(      (G_Tree *) TREE)
#define gvDataTreeErase(               TREE, VALUE)                                                               g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gvDataTreeEraseBegin(          TREE)                                                                      g_TreeEraseBegin(          (G_Tree *) TREE)
#define gvDataTreeEraseEnd(            TREE)                                                                      g_TreeEraseEnd(            (G_Tree *) TREE)
#define gvDataTreeFind(                TREE, VALUE)                                       (GvDataTreeItem *)      g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gvDataTreeFlush(               TREE)                                                                      g_TreeFlush(               (G_Tree *) TREE)
#define gvDataTreeForEach(             TREE, FUNC)                                                                g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gvDataTreeGetBegin(            TREE)                                              (GvDataTreeItem *)      g_TreeGetBegin(            (G_Tree *) TREE)
#define gvDataTreeGetCount(            TREE)                                                                      g_TreeGetCount(            (G_Tree *) TREE)
#define gvDataTreeGetEnd(              TREE)                                              (GvDataTreeItem *)      g_TreeGetEnd(              (G_Tree *) TREE)
#define gvDataTreeItemDestroy(         TREE, TITEM)                                                               g_TreeItemDestroy(         (G_Tree *) TREE, TITEM)
#define gvDataTreeItemGet(                   TITEM)                                      ((GvData *)              g_TreeItemGet(             (G_Tree *) TREE, TITEM))
#define gvDataTreeItemGetNext(               TITEM)                                       (GvDataTreeItem *)      g_TreeItemGetNext(                          TITEM)
#define gvDataTreeItemGetPrev(               TITEM)                                       (GvDataTreeItem *)      g_TreeItemGetPrev(                          TITEM)
#define gvDataTreeItemUpdate(          TREE, TITEM, VALUE)                                                        g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define gvDataTreeKeyAdd(              TREE, KEY, VALUE)                                  (GvDataTreeKeyItem *)   g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gvDataTreeKeyCreate(                 COMPARE_FUNC)                                (GvDataTreeKey *)       g_TreeKeyCreate(                               "GvDataTreeKey", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataTreeKeyCreateContent(    TREE, COMPARE_FUNC)                                                        g_TreeKeyCreateContent(    (G_TreeKey *) TREE, "GvDataTreeKey", GvData *, gbTRUE, COMPARE_FUNC)
#define gvDataTreeKeyDestroy(          TREE)                                                                      g_TreeKeyDestroy(          (G_TreeKey *) TREE)
#define gvDataTreeKeyDestroyContent(   TREE)                                                                      g_TreeKeyDestroyContent(   (G_TreeKey *) TREE)
#define gvDataTreeKeyErase(            TREE, KEY)                                                                 g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gvDataTreeKeyEraseBegin(       TREE)                                                                      g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gvDataTreeKeyEraseEnd(         TREE)                                                                      g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gvDataTreeKeyFind(             TREE, KEY)                                         (GvDataTreeKeyItem *)   g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gvDataTreeKeyFlush(            TREE)                                                                      g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gvDataTreeKeyForEach(          TREE, FUNC)                                                                g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gvDataTreeKeyGetBegin(         TREE)                                              (GvDataTreeKeyItem *)   g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gvDataTreeKeyGetCount(         TREE)                                                                      g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gvDataTreeKeyGetEnd(           TREE)                                              (GvDataTreeKeyItem *)   g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gvDataTreeKeyItemDestroy(      TREE, TITEM)                                                               g_TreeKeyItemDestroy(      (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gvDataTreeKeyItemGet(                TITEM)                                      ((GvData *)              g_TreeKeyItemGet(          (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM))
#define gvDataTreeKeyItemGetNext(            TITEM)                                       (GvDataTreeKeyItem *)   g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gvDataTreeKeyItemGetPrev(            TITEM)                                       (GvDataTreeKeyItem *)   g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gvDataTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                        g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
