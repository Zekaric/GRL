/******************************************************************************
file:       gdir
author:     Robbert de Groot
copyright:  2002-2010, Robbert de Groot

description:
Simple directory routines.
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

#if !defined(GDIRH)
#define      GDIRH

/******************************************************************************
type:
******************************************************************************/
typedef Gn     GdirFileSize;

typedef enum
{
   gdirTypeNONE,
   gdirTypeFILE,
   gdirTypeFOLDER
} GdirType;

typedef struct
{
   Gs                      *name;
   Gpath                   *path;
   GdirType                 type;
   Gtime                    timeAccessed,
                            timeCreated,
                            timeModified;
   GdirFileSize             size;
} Gdir;

// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   Gdir                   **p;
} GdirArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   Gdir                    *p;
} GdirArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GdirArrayKeyCell       **p;
} GdirArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GdirListItem GdirListItem;
struct GdirListItem
{
   GdirListItem            *next,
                           *prev;
   Gdir                    *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GdirListItem            *head,
                           *tail;
} GdirList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GdirListKeyItem GdirListKeyItem;
struct GdirListKeyItem
{
   GdirListKeyItem         *next,
                           *prev;
   Gkey const              *key;
   Gdir                    *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GdirListKeyItem         *head,
                           *tail;
} GdirListKey;

/******************************************************************************
function:
******************************************************************************/
#define gdirCreate()                   (Gdir *)      gleakCreate((void *) gdirCreate_(), gsizeof(Gdir));
#define gdirArrayCreateFromPath(PATH)  (GdirArray *) gleakCreate((void *) gdirArrayCreateFromPath_((PATH)), gsizeof(GdirArray))
#define gdirArrayCreateFromMask(PATH)  (GdirArray *) gleakCreate((void *) gdirArrayCreateFromMask_((PATH)), gsizeof(GdirArray))

grlAPI GdirArray     *gdirArrayCreateFromPath_( Gpath const * const path);
grlAPI GdirArray     *gdirArrayCreateFromMask_( Gpath const * const path);

grlAPI Gdir          *gdirCreate_(              void);
grlAPI Gb             gdirCreateContent(        Gdir       * const gdir);

grlAPI void           gdirDestroy(              Gdir       * const gdir);
grlAPI void           gdirDestroyContent(       Gdir       * const gdir);

grlAPI Gb             gdirFileDestroy(          Gpath const * const path);

grlAPI Gb             gdirFolderCreate(         Gpath const * const path);
grlAPI Gb             gdirFolderDestroy(        Gpath const * const path);

grlAPI Gpath         *gdirGetAppData(           void);
grlAPI Gs const      *gdirGetName(              Gdir const * const dir);
grlAPI Gpath const   *gdirGetPath(              Gdir const * const dir);
grlAPI Gpath const   *gdirGetProfile(           void);
grlAPI GdirFileSize   gdirGetSize(              Gdir const * const dir);
grlAPI Gtime          gdirGetTimeAccessed(      Gdir const * const dir);
grlAPI Gtime          gdirGetTimeCreated(       Gdir const * const dir);
grlAPI Gtime          gdirGetTimeModified(      Gdir const * const dir);
grlAPI GdirType       gdirGetType(              Gdir const * const dir);
grlAPI Gpath         *gdirGetWorking(           void);

grlAPI Gb             gdirIsExisting(           Gpath const * const path);

grlAPI Gb             gdirRename(               Gpath const * const path, Gpath const * const pathDestination);

grlAPI Gb             gdirSetWorking(           Gpath const * const path);

/******************************************************************************
Gdir containers.
******************************************************************************/
#define gdirArrayAdd(                ARRAY,        VALUE)                                                    g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayAddAt(              ARRAY, INDEX, VALUE)                                                    g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gdirArrayAddBegin(           ARRAY,        VALUE)                                                    g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayAddEnd(             ARRAY,        VALUE)                                                    g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayClear(              ARRAY, COUNT, INDEX)                                                    g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gdirArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                       g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gdirArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                          g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gdirArrayCreate(             )                                                  (GdirArray *)        g_ArrayCreate(                                GdirArray, Gdir *, NULL, gbTRUE, gbFALSE)
#define gdirArrayCreateContent(      ARRAY)                                                                  g_ArrayCreateContent(      (G_Array *) ARRAY, GdirArray, Gdir *, NULL, gbTRUE, gbFALSE)
#define gdirArrayDestroy(            ARRAY)                                                                  g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gdirArrayDestroyContent(     ARRAY)                                                                  g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gdirArrayErase(              ARRAY, VALUE)                                                           g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gdirArrayEraseAt(            ARRAY, COUNT, INDEX)                                                    g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gdirArrayEraseBegin(         ARRAY)                                                                  g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gdirArrayEraseEnd(           ARRAY)                                                                  g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gdirArrayFind(               ARRAY, VALUE)                                                           g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gdirArrayFlush(              ARRAY)                                                                  g_ArrayFlush(              (G_Array *) ARRAY) 
#define gdirArrayForEach(            ARRAY, FUNC)                                                            g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gdirArrayGet(                ARRAY)                                             (Gdir **)            g_ArrayGet(                (G_Array *) ARRAY) 
#define gdirArrayGetAt(              ARRAY, INDEX)                                    *((Gdir **)            g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gdirArrayGetBegin(           ARRAY)                                           *((Gdir **)            g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gdirArrayGetCount(           ARRAY)                                                                  g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gdirArrayGetEnd(             ARRAY)                                           *((Gdir **)            g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gdirArrayGetSize(            ARRAY)                                                                  g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gdirArraySetCount(           ARRAY, COUNT)                                                           g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gdirArraySort(               ARRAY)                                                                  g_ArraySort(               (G_Array *) ARRAY) 
#define gdirArraySwap(               ARRAY, INDEXA, INDEXB)                                                  g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gdirArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                    g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gdirArrayKeyAdd(             ARRAY,        KEY, VALUE)                                               g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gdirArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                               g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define gdirArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                               g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gdirArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                               g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gdirArrayKeyClear(           ARRAY, COUNT, INDEX)                                                    g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gdirArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                       g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gdirArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                          g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gdirArrayKeyCreate(          )                                                  (GdirArray *)        g_ArrayKeyCreate(                                GdirArray, Gdir *, NULL, gbTRUE)
#define gdirArrayKeyCreateContent(   ARRAY)                                                                  g_ArrayKeyCreateContent(   (G_ArrayKey *) ARRAY, GdirArray, Gdir *, NULL, gbTRUE)
#define gdirArrayKeyDestroy(         ARRAY)                                                                  g_ArrayKeyDestroy(         (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyDestroyContent(  ARRAY)                                                                  g_ArrayKeyDestroyContent(  (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyErase(           ARRAY, KEY)                                                             g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gdirArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                    g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gdirArrayKeyEraseBegin(      ARRAY)                                                                  g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyEraseEnd(        ARRAY)                                                                  g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyFind(            ARRAY, KEY)                                                             g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gdirArrayKeyFlush(           ARRAY)                                                                  g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyForEach(         ARRAY, FUNC)                                                            g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gdirArrayKeyGetAt(           ARRAY, INDEX)                                    *((Gdir **)            g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gdirArrayKeyGetAtKey(        ARRAY, INDEX)                                                           g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gdirArrayKeyGetBegin(        ARRAY)                                           *((Gdir **)            g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gdirArrayKeyGetBeginKey(     ARRAY)                                                                  g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyGetCount(        ARRAY)                                                                  g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyGetEnd(          ARRAY)                                           *((Gdir **)            g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gdirArrayKeyGetEndKey(       ARRAY)                                                                  g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gdirArrayKeyGetSize(         ARRAY)                                                                  g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gdirArrayKeySetCount(        ARRAY, COUNT)                                                           g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gdirArrayKeySort(            ARRAY)                                                                  g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gdirArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                  g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gdirArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                    g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gdirArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                      g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gdirListAdd(                 LIST, VALUE)                                       (GdirListItem *)     g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gdirListAddBegin(            LIST, VALUE)                                       (GdirListItem *)     g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gdirListAddEnd(              LIST, VALUE)                                       (GdirListItem *)     g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gdirListCreate(              )                                                  (GdirList *)         g_ListCreate(                               GdirList, Gdir *, NULL)
#define gdirListCreateContent(       LIST)                                                                   g_ListCreateContent(       (G_List *) LIST, GdirList, Gdir *, NULL)
#define gdirListDestroy(             LIST)                                                                   g_ListDestroy(             (G_List *) LIST)
#define gdirListDestroyContent(      LIST)                                                                   g_ListDestroyContent(      (G_List *) LIST)
#define gdirListErase(               LIST, VALUE)                                                            g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gdirListEraseBegin(          LIST)                                                                   g_ListEraseBegin(          (G_List *) LIST)
#define gdirListEraseEnd(            LIST)                                                                   g_ListEraseEnd(            (G_List *) LIST)
#define gdirListFind(                LIST, VALUE)                                       (GdirListItem *)     g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gdirListFlush(               LIST)                                                                   g_ListFlush(               (G_List *) LIST)
#define gdirListForEach(             LIST, FUNC)                                                             g_ListForEach(             (G_List *) LIST, FUNC)
#define gdirListGetBegin(            LIST)                                              (GdirListItem *)     g_ListGetBegin(            (G_List *) LIST)
#define gdirListGetCount(            LIST)                                                                   g_ListGetCount(            (G_List *) LIST)
#define gdirListGetEnd(              LIST)                                              (GdirListItem *)     g_ListGetEnd(              (G_List *) LIST)
#define gdirListItemAdd(             LIST, LITEM, VALUE)                                (GdirListItem *)     g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gdirListItemErase(           LIST, LITEM)                                                            g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gdirListItemGet(                   LITEM)                                     *((Gdir **)            g_ListItemGet(                              (G_ListItem *) LITEM))
#define gdirListItemGetNext(               LITEM)                                       (GdirListItem *)     g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gdirListItemGetPrev(               LITEM)                                       (GdirListItem *)     g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gdirListItemUpdate(          LIST, LITEM, VALUE)                                                     g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gdirListKeyAdd(              LIST, KEY, VALUE)                                  (GdirListKeyItem *)  g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gdirListKeyAddBegin(         LIST, KEY, VALUE)                                  (GdirListKeyItem *)  g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gdirListKeyAddEnd(           LIST, KEY, VALUE)                                  (GdirListKeyItem *)  g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gdirListKeyCreate(           )                                                  (GdirList *)         g_ListKeyCreate(                               GdirListKey, Gdir *, NULL)
#define gdirListKeyCreateContent(    LIST)                                                                   g_ListKeyCreateContent(    (G_ListKey *) LIST, GdirListKey, Gdir *, NULL)
#define gdirListKeyDestroy(          LIST)                                                                   g_ListKeyDestroy(          (G_ListKey *) LIST)
#define gdirListKeyDestroyContent(   LIST)                                                                   g_ListKeyDestroyContent(   (G_ListKey *) LIST)
#define gdirListKeyErase(            LIST, KEY)                                                              g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gdirListKeyEraseBegin(       LIST)                                                                   g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gdirListKeyEraseEnd(         LIST)                                                                   g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gdirListKeyFind(             LIST, KEY)                                         (GdirListKeyItem *)  g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gdirListKeyFlush(            LIST)                                                                   g_ListKeyFlush(            (G_ListKey *) LIST)
#define gdirListKeyForEach(          LIST, FUNC)                                                             g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gdirListKeyGetBegin(         LIST)                                              (GdirListKeyItem *)  g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gdirListKeyGetCount(         LIST)                                                                   g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gdirListKeyGetEnd(           LIST)                                              (GdirListKeyItem *)  g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gdirListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GdirListKeyItem *)  g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gdirListKeyItemErase(        LIST, LITEM)                                                            g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gdirListKeyItemGet(                LITEM)                                     *((Gdir **)            g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gdirListKeyItemGetKey(             LITEM)                                                            g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gdirListKeyItemGetNext(            LITEM)                                       (GdirListKeyItem *)  g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gdirListKeyItemGetPrev(            LITEM)                                       (GdirListKeyItem *)  g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gdirListKeyItemUpdate(       LIST, LITEM, VALUE)                                                     g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gdirListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                       g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#endif
