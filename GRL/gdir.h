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

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

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

/******************************************************************************
Gdir containers.
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
   Gdir                 **p;
} GdirArray;

#define gdirArrayAdd(                ARRAY,        VALUE)                                             g_ArrayAdd(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayAddAt(              ARRAY, INDEX, VALUE)                                             g_ArrayAddAt(         (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gdirArrayAddBegin(           ARRAY,        VALUE)                                             g_ArrayAddBegin(      (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayAddEnd(             ARRAY,        VALUE)                                             g_ArrayAddEnd(        (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gdirArrayClear(              ARRAY, COUNT, INDEX)                                             g_ArrayClear(         (G_Array *) ARRAY, COUNT, INDEX) 
#define gdirArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                g_ArrayCopy(          (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gdirArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                   g_ArrayCopyFrom(      (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gdirArrayCreate(                  )                                             (GdirArray *) g_ArrayCreate(                           GdirArray, Gdir *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gdirArrayCreateContent(      ARRAY)                                                           g_ArrayCreateContent( (G_Array *) ARRAY, GdirArray, Gdir *, gbTRUE, NULL, gbTRUE, gbFALSE)
#define gdirArrayDestroy(            ARRAY)                                                           g_ArrayDestroy(       (G_Array *) ARRAY) 
#define gdirArrayDestroyContent(     ARRAY)                                                           g_ArrayDestroyContent((G_Array *) ARRAY) 
#define gdirArrayErase(              ARRAY, VALUE)                                                    g_ArrayErase(         (G_Array *) ARRAY, (Gp *) VALUE) 
#define gdirArrayEraseAt(            ARRAY, COUNT, INDEX)                                             g_ArrayEraseAt(       (G_Array *) ARRAY, COUNT, INDEX) 
#define gdirArrayEraseBegin(         ARRAY)                                                           g_ArrayEraseBegin(    (G_Array *) ARRAY) 
#define gdirArrayEraseEnd(           ARRAY)                                                           g_ArrayEraseEnd(      (G_Array *) ARRAY) 
#define gdirArrayFind(               ARRAY, VALUE)                                                    g_ArrayFind(          (G_Array *) ARRAY, (Gp *) VALUE) 
#define gdirArrayFlush(              ARRAY)                                                           g_ArrayFlush(         (G_Array *) ARRAY) 
#define gdirArrayForEach(            ARRAY, FUNC)                                                     g_ArrayForEach(       (G_Array *) ARRAY, FUNC) 
#define gdirArrayGet(                ARRAY)                                            ((Gdir **)     g_ArrayGet(           (G_Array *) ARRAY))
#define gdirArrayGetAt(              ARRAY, INDEX)                                     ((Gdir *)      g_ArrayGetAt(         (G_Array *) ARRAY, INDEX))
#define gdirArrayGetBegin(           ARRAY)                                            ((Gdir *)      g_ArrayGetBegin(      (G_Array *) ARRAY))
#define gdirArrayGetCount(           ARRAY)                                                           g_ArrayGetCount(      (G_Array *) ARRAY) 
#define gdirArrayGetEnd(             ARRAY)                                            ((Gdir *)      g_ArrayGetEnd(        (G_Array *) ARRAY))
#define gdirArrayGetSize(            ARRAY)                                                           g_ArrayGetSize(       (G_Array *) ARRAY) 
#define gdirArraySetCount(           ARRAY, COUNT)                                                    g_ArraySetCount(      (G_Array *) ARRAY, COUNT) 
#define gdirArraySort(               ARRAY)                                                           g_ArraySort(          (G_Array *) ARRAY) 
#define gdirArraySwap(               ARRAY, INDEXA, INDEXB)                                           g_ArraySwap(          (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gdirArrayUpdateAt(           ARRAY, INDEX, VALUE)                                             g_ArrayUpdateAt(      (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

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

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
