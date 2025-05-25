/**************************************************************************************************
file:         Gpath
author:       Robbert de Groot
copyright:    2002-2012, Robbert de Groot

description:
Path functions to handle paths in an independant way.

Gpaths can be...
/B7psSERVER_NAME
/B7pmMOUNT_NAME
/B7p/FOLDER_FILE_NAME
/B7pr (root directory of file system or mount)

So the following will translate to...
\\server\folder\folder\file.ext     /B7psserver/folder/folder/file.ext
\\server\folder\folder\file         /B7psserver/folder/folder/file
\\server\folder\folder\             /B7psserver/folder/folder
\\server\folder\folder              /B7psserver/folder/folder
C:\folder\folder\file.ext           /B7pmc/folder/folder/file.ext
C:\folder\folder\file               /B7pmc/folder/folder/file
C:\folder\folder\                   /B7pmc/folder/folder
\folder\folder\file.ext             /B7pr/folder/folder/file.ext
\folder\folder\file                 /B7pr/folder/folder/file
\folder\folder\                     /B7pr/folder/folder
folder\folder\file.ext              /B7p/folder/folder/file.ext
folder\folder\file                  /B7p/folder/folder/file
folder\folder\                      /B7p/folder/folder
file.ext                            /B7p/file.ext
file                                /B7p/file
                                    /B7p

I make no attempt to figure out if the tail is a file or not.  Folders can have
periods in their name.

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

#if !defined(GPATHHEADER)
#define      GPATHHEADER

/**************************************************************************************************
include:
**************************************************************************************************/

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define gpathFOLDER_SEPARATOR_UNIX           ((Gc2) L'/')
#define gpathFOLDER_SEPARATOR_WINDOWS        ((Gc2) L'\\')
#define gpathFOLDER_SEPARATOR_MACOSX         ((Gc2) L':')
#define gpathCURRENT_DIR                     L"."
#define gpathPARENT_DIR                      L".."

#if   defined(grlWINDOWS)

#define gpathFOLDER_SEPARATOR_SYSTEM         ((Gc2) L'\\')
#define gpathFOLDER_SEPARATOR_SYSTEM_ALT     ((Gc2) L'/')
#define gpathFILE_SEPARATOR_SYSTEM           ((Gc2) L'.')
#define gpathMOUNT_PREFIX_SYSTEM             0
#define gpathMOUNT_SUFFIX_SYSTEM             ((Gc2) L':')
#define gpathFOLDER_SEPARATOR_SYSTEM_STRING  L"\\"
#define gpathPARENT_DIR_SYSTEM               L".."

#elif defined(MACOSX)

#define gpathFOLDER_SEPARATOR_SYSTEM         ((Gc2) L':')
#define gpathFILE_SEPARATOR_SYSTEM           ((Gc2) L'.')
#define gpathMOUNT_PREFIX_SYSTEM             0
#define gpathMOUNT_SUFFIX_SYSTEM             0
#define gpathPARENT_DIR_SYSTEM               L"::"

#else

#define gpathFOLDER_SEPARATOR_SYSTEM         ((Gc2) L'/')
#define gpathFILE_SEPARATOR_SYSTEM           ((Gc2) L'.')
#define gpathMOUNT_PREFIX_SYSTEM             0
#define gpathMOUNT_SUFFIX_SYSTEM             0
#define gpathPARENT_DIR_SYSTEM               L".."

#endif

// system independent path tokesn
#define gpathFOLDER                          ((Gc2) L'/')
#define gpathMOUNT                           ((Gc2) L'm')
#define gpathSERVER                          ((Gc2) L's')
#define gpathROOT                            ((Gc2) L'r')
#define gpathSEPARATOR                       0xB7

typedef enum
{
   gpathTypeNONE,
   gpathTypeMOUNT,
   gpathTypeFOLDER,
   gpathTypeFILE,
   gpathTypeEXTENSION
} GpathType;

typedef Gs Gpath;

/**************************************************************************************************
prototype:
**************************************************************************************************/
/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gpathGetAt(    PATH,INDEX)  (Gs *) gleakCloc((Gp *) gpathGetAt_(    (PATH), (INDEX)),  gsizeof(Gs))
#define gpathGetEnd(   PATH)        (Gs *) gleakCloc((Gp *) gpathGetEnd_(   (PATH)),           gsizeof(Gs))
#define gpathGetMount( PATH)        (Gs *) gleakCloc((Gp *) gpathGetMount_( (PATH)),           gsizeof(Gs))
#define gpathGetServer(PATH)        (Gs *) gleakCloc((Gp *) gpathGetServer_((PATH)),           gsizeof(Gs))
/*lint -restore */

grlAPI Gb      gpathAppend(        Gpath       * const path, Gpath const * const add);

#define        gpathCloc()          gsCloc()
#define        gpathClocFrom(P)   gsClocFrom(P)

#define        gpathDloc(      P)   gsDloc(   P)

grlAPI Gs     *gpathGetAt_(        Gpath const * const path, Gindex const index);
grlAPI Gcount  gpathGetCount(      Gpath const * const path);
grlAPI Gs     *gpathGetEnd_(       Gpath const * const path);
grlAPI Gs     *gpathGetMount_(     Gpath const * const path);
grlAPI Gs     *gpathGetServer_(    Gpath const * const path);

grlAPI Gb      gpathIsFromRoot(    Gpath const * const path);
grlAPI Gb      gpathIsPath(        Gpath const * const path);
grlAPI Gb      gpathIsRelative(    Gpath const * const path);

grlAPI Gb      gpathPop(           Gpath       * const path);
grlAPI Gb      gpathPopExtension(  Gpath       * const path);
grlAPI Gb      gpathPush(          Gpath       * const path, Gs  const * const value);
grlAPI Gb      gpathPushU2(        Gpath       * const path, Gc2 const * const value);
grlAPI Gb      gpathPushExtensionA(Gpath       * const path, Char const * const extension);

grlAPI Gb      gpathReduce(        Gpath       * const path);

grlAPI Gb      gpathSetFromSystem( Gs * const path);
grlAPI Gb      gpathSetIsFromRoot( Gpath       * const path, Gb const value);
grlAPI Gb      gpathSetMount(      Gpath       * const path, Gs const * const value);
grlAPI Gb      gpathSetServer(     Gpath       * const path, Gs const * const value);
grlAPI Gb      gpathSetToSystem(   Gpath       * const path);


/**************************************************************************************************
Gpath containers.
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
   Gpath                  **p;
} GpathArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct
{
   Gkey const              *key;
   Gpath                   *p;
} GpathArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GpathArrayKeyCell      **p;
} GpathArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GpathListItem GpathListItem;
struct GpathListItem
{
   GpathListItem           *next,
                           *prev;
   Gpath                   *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GpathListItem           *head,
                           *tail;
} GpathList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GpathListKeyItem GpathListKeyItem;
struct GpathListKeyItem
{
   GpathListKeyItem        *next,
                           *prev;
   Gkey const              *key;
   Gpath                   *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GpathListKeyItem        *head,
                           *tail;
} GpathListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GpathList              **binArray;
   GhashSize                binCount;
} GpathHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GpathListKey           **binArray;
   GhashSize                binCount;
} GpathHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GpathTree     GpathTree;
typedef struct GpathTreeItem GpathTreeItem;
struct GpathTreeItem
{
   GpathTree               *owner;
   GpathTreeItem           *parent;
   GpathTreeItem           *childLeft;
   GpathTreeItem           *childRight;
   GheapN                   heapValue;
   Gpath                   *p;
};

struct GpathTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GpathTreeItem           *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GpathTreeKey     GpathTreeKey;
typedef struct GpathTreeKeyItem GpathTreeKeyItem;
struct GpathTreeKeyItem
{
   GpathTreeKey            *owner;
   GpathTreeKeyItem        *parent;
   GpathTreeKeyItem        *childLeft;
   GpathTreeKeyItem        *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gpath                   *p;
};

struct GpathTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GpathTreeKeyItem        *root;
};

#define gpathArrayAdd(                ARRAY,        VALUE)                                                     g_ArrayAddP(               (G_Array *) ARRAY,        (Gp *) VALUE)
#define gpathArrayAddAt(              ARRAY, INDEX, VALUE)                                                     g_ArrayAddAtP(             (G_Array *) ARRAY, INDEX, (Gp *) VALUE)
#define gpathArrayAddBegin(           ARRAY,        VALUE)                                                     g_ArrayAddBeginP(          (G_Array *) ARRAY,        (Gp *) VALUE)
#define gpathArrayAddEnd(             ARRAY,        VALUE)                                                     g_ArrayAddEndP(            (G_Array *) ARRAY,        (Gp *) VALUE)
#define gpathArrayClear(              ARRAY, COUNT, INDEX)                                                     g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX)
#define gpathArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gpathArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC)
#define gpathArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpathArray *)        g_ArrayCloc(                                "GpathArray", Gpath *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpathArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayClocContent(      (G_Array *) ARRAY, "GpathArray", Gpath *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gpathArrayDloc(               ARRAY)                                                                   g_ArrayDloc(               (G_Array *) ARRAY)
#define gpathArrayDlocContent(        ARRAY)                                                                   g_ArrayDlocContent(        (G_Array *) ARRAY)
#define gpathArrayErase(              ARRAY, VALUE)                                                            g_ArrayEraseP(             (G_Array *) ARRAY, (Gp *) VALUE)
#define gpathArrayEraseAt(            ARRAY, COUNT, INDEX)                                                     g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX)
#define gpathArrayEraseBegin(         ARRAY)                                                                   g_ArrayEraseBegin(         (G_Array *) ARRAY)
#define gpathArrayEraseEnd(           ARRAY)                                                                   g_ArrayEraseEnd(           (G_Array *) ARRAY)
#define gpathArrayFind(               ARRAY, VALUE)                                                            g_ArrayFindP(              (G_Array *) ARRAY, (Gp *) VALUE)
#define gpathArrayFlush(              ARRAY)                                                                   g_ArrayFlush(              (G_Array *) ARRAY)
#define gpathArrayForEach(            ARRAY, FUNC)                                                             g_ArrayForEachP(           (G_Array *) ARRAY, FUNC)
#define gpathArrayGet(                ARRAY)                                             (Gpath **)            g_ArrayGet(                (G_Array *) ARRAY)
#define gpathArrayGetAt(              ARRAY, INDEX)                                      (Gpath *)             g_ArrayGetAtP(             (G_Array *) ARRAY, INDEX))
#define gpathArrayGetBegin(           ARRAY)                                             (Gpath *)             g_ArrayGetBeginP(          (G_Array *) ARRAY))
#define gpathArrayGetCount(           ARRAY)                                                                   g_ArrayGetCount(           (G_Array *) ARRAY)
#define gpathArrayGetEnd(             ARRAY)                                             (Gpath *)             g_ArrayGetEndP(            (G_Array *) ARRAY))
#define gpathArrayGetSize(            ARRAY)                                                                   g_ArrayGetSize(            (G_Array *) ARRAY)
#define gpathArraySetCount(           ARRAY, COUNT)                                                            g_ArraySetCount(           (G_Array *) ARRAY, COUNT)
#define gpathArraySort(               ARRAY)                                                                   g_ArraySort(               (G_Array *) ARRAY)
#define gpathArraySwap(               ARRAY, INDEXA, INDEXB)                                                   g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB)
#define gpathArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                     g_ArrayUpdateAtP(          (G_Array *) ARRAY, INDEX, (Gp *) VALUE)

#define gpathArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE)
#define gpathArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE)
#define gpathArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE)
#define gpathArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE)
#define gpathArrayKeyClear(           ARRAY, COUNT, INDEX)                                                     g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gpathArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                        g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST)
#define gpathArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                           g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC)
#define gpathArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GpathArray *)        g_ArrayKeyCloc(                                "GpathArrayKey", Gpath *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpathArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                          g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GpathArrayKey", Gpath *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gpathArrayKeyDloc(            ARRAY)                                                                   g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY)
#define gpathArrayKeyDlocContent(     ARRAY)                                                                   g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY)
#define gpathArrayKeyErase(           ARRAY, KEY)                                                              g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY)
#define gpathArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                     g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX)
#define gpathArrayKeyEraseBegin(      ARRAY)                                                                   g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY)
#define gpathArrayKeyEraseEnd(        ARRAY)                                                                   g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY)
#define gpathArrayKeyFind(            ARRAY, KEY)                                                              g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY)
#define gpathArrayKeyFlush(           ARRAY)                                                                   g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY)
#define gpathArrayKeyForEach(         ARRAY, FUNC)                                                             g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC)
#define gpathArrayKeyGetAt(           ARRAY, INDEX)                                    *((Gpath **)            g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gpathArrayKeyGetAtKey(        ARRAY, INDEX)                                                            g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX)
#define gpathArrayKeyGetBegin(        ARRAY)                                           *((Gpath **)            g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gpathArrayKeyGetBeginKey(     ARRAY)                                                                   g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY)
#define gpathArrayKeyGetCount(        ARRAY)                                                                   g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY)
#define gpathArrayKeyGetEnd(          ARRAY)                                           *((Gpath **)            g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gpathArrayKeyGetEndKey(       ARRAY)                                                                   g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY)
#define gpathArrayKeyGetSize(         ARRAY)                                                                   g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY)
#define gpathArrayKeySetCount(        ARRAY, COUNT)                                                            g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT)
#define gpathArrayKeySort(            ARRAY)                                                                   g_ArrayKeySort(            (G_ArrayKey *) ARRAY)
#define gpathArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                   g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB)
#define gpathArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                     g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE)
#define gpathArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                       g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY)

#define gpathListAdd(                 LIST, VALUE)                                       (GpathListItem *)     g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gpathListAddBegin(            LIST, VALUE)                                       (GpathListItem *)     g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gpathListAddEnd(              LIST, VALUE)                                       (GpathListItem *)     g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gpathListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GpathList *)         g_ListCloc(                               "GpathList", Gpath *, OPTIONAL_COMPARE_FUNC)
#define gpathListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                             g_ListClocContent(       (G_List *) LIST, "GpathList", Gpath *, OPTIONAL_COMPARE_FUNC)
#define gpathListDloc(                LIST)                                                                    g_ListDloc(                (G_List *) LIST)
#define gpathListDlocContent(         LIST)                                                                    g_ListDlocContent(         (G_List *) LIST)
#define gpathListErase(               LIST, VALUE)                                                             g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gpathListEraseBegin(          LIST)                                                                    g_ListEraseBegin(          (G_List *) LIST)
#define gpathListEraseEnd(            LIST)                                                                    g_ListEraseEnd(            (G_List *) LIST)
#define gpathListFind(                LIST, VALUE)                                       (GpathListItem *)     g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gpathListFlush(               LIST)                                                                    g_ListFlush(               (G_List *) LIST)
#define gpathListForEach(             LIST, FUNC)                                                              g_ListForEach(             (G_List *) LIST, FUNC)
#define gpathListGetBegin(            LIST)                                              (GpathListItem *)     g_ListGetBegin(            (G_List *) LIST)
#define gpathListGetCount(            LIST)                                                                    g_ListGetCount(            (G_List *) LIST)
#define gpathListGetEnd(              LIST)                                              (GpathListItem *)     g_ListGetEnd(              (G_List *) LIST)
#define gpathListItemAdd(             LIST, LITEM, VALUE)                                (GpathListItem *)     g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gpathListItemErase(           LIST, LITEM)                                                             g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gpathListItemGet(                   LITEM)                                     *((Gpath **)            g_ListItemGet(                              (G_ListItem *) LITEM))
#define gpathListItemGetNext(               LITEM)                                       (GpathListItem *)     g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gpathListItemGetPrev(               LITEM)                                       (GpathListItem *)     g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gpathListItemUpdate(          LIST, LITEM, VALUE)                                                      g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gpathListKeyAdd(              LIST, KEY, VALUE)                                  (GpathListKeyItem *)  g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpathListKeyAddBegin(         LIST, KEY, VALUE)                                  (GpathListKeyItem *)  g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpathListKeyAddEnd(           LIST, KEY, VALUE)                                  (GpathListKeyItem *)  g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gpathListKeyCloc(                   COMPARE_FUNC)                                (GpathList *)         g_ListKeyCloc(                               "GpathListKey", Gpath *, COMPARE_FUNC)
#define gpathListKeyClocContent(      LIST, COMPARE_FUNC)                                                      g_ListKeyClocContent(    (G_ListKey *) LIST, "GpathListKey", Gpath *, COMPARE_FUNC)
#define gpathListKeyDloc(             LIST)                                                                    g_ListKeyDloc(             (G_ListKey *) LIST)
#define gpathListKeyDlocContent(      LIST)                                                                    g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gpathListKeyErase(            LIST, KEY)                                                               g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gpathListKeyEraseBegin(       LIST)                                                                    g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gpathListKeyEraseEnd(         LIST)                                                                    g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gpathListKeyFind(             LIST, KEY)                                         (GpathListKeyItem *)  g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gpathListKeyFlush(            LIST)                                                                    g_ListKeyFlush(            (G_ListKey *) LIST)
#define gpathListKeyForEach(          LIST, FUNC)                                                              g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gpathListKeyGetBegin(         LIST)                                              (GpathListKeyItem *)  g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gpathListKeyGetCount(         LIST)                                                                    g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gpathListKeyGetEnd(           LIST)                                              (GpathListKeyItem *)  g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gpathListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GpathListKeyItem *)  g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gpathListKeyItemErase(        LIST, LITEM)                                                             g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gpathListKeyItemGet(          LIST, LITEM)                                     *((Gpath **)            g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gpathListKeyItemGetKey(       LIST, LITEM)                                                             g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gpathListKeyItemGetNext(      LIST, LITEM)                                       (GpathListKeyItem *)  g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gpathListKeyItemGetPrev(      LIST, LITEM)                                       (GpathListKeyItem *)  g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gpathListKeyItemUpdate(       LIST, LITEM, VALUE)                                                      g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gpathListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                        g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gpathHashAdd(                 HASH, VALUE)                                                             g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gpathHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GpathHash *)         g_HashCloc(                               "GpathHash", Gpath *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpathHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                 g_HashClocContent(       (G_Hash *) HASH, "GpathHash", Gpath *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gpathHashDloc(                HASH)                                                                    g_HashDloc(                (G_Hash *) HASH)
#define gpathHashDlocContent(         HASH)                                                                    g_HashDlocContent(         (G_Hash *) HASH)
#define gpathHashErase(               HASH, VALUE)                                                             g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gpathHashFind(                HASH, VALUE)                                     *((Gpath **)            g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gpathHashFlush(               HASH)                                                                    g_HashFlush(               (G_Hash *) HASH)
#define gpathHashForEach(             HASH, FUNC)                                                              g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gpathHashGetCount(            HASH)                                                                    g_HashGetCount(            (G_Hash *) HASH)
#define gpathHashUpdate(              HASH, VALUE)                                                             g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gpathHashKeyAdd(              HASH, KEY, VALUE)                                                        g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gpathHashKeyCloc(                   HASHSIZE)                                    (GpathHashKey *)      g_HashKeyCloc(                               "GpathHashKey", Gpath *, HASHSIZE)
#define gpathHashKeyClocContent(      HASH, HASHSIZE)                                                          g_HashKeyClocContent(    (G_HashKey *) HASH, "GpathHashKey", Gpath *, HASHSIZE)
#define gpathHashKeyDloc(             HASH)                                                                    g_HashKeyDloc(             (G_HashKey *) HASH)
#define gpathHashKeyDlocContent(      HASH)                                                                    g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gpathHashKeyErase(            HASH, KEY)                                                               g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gpathHashKeyFind(             HASH, KEY)                                       *((Gpath **)            g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gpathHashKeyFlush(            HASH)                                                                    g_HashKeyFlush(            (G_HashKey *) HASH)
#define gpathHashKeyForEach(          HASH, FUNC)                                                              g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gpathHashKeyGetCount(         HASH)                                                                    g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gpathHashKeyUpdate(           HASH, KEY, VALUE)                                                        g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gpathTreeAdd(                 TREE, VALUE)                                       (GpathTreeItem *)     g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gpathTreeCloc(                      COMPARE_FUNC)                                (GpathTree *)         g_TreeCloc(                               "GpathTree", Gpath *, COMPARE_FUNC)
#define gpathTreeClocContent(         TREE, COMPARE_FUNC)                                                      g_TreeClocContent(       (G_Tree *) TREE, "GpathTree", Gpath *, COMPARE_FUNC)
#define gpathTreeDloc(                TREE)                                                                    g_TreeDloc(                (G_Tree *) TREE)
#define gpathTreeDlocContent(         TREE)                                                                    g_TreeDlocContent(         (G_Tree *) TREE)
#define gpathTreeErase(               TREE, VALUE)                                                             g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gpathTreeEraseBegin(          TREE)                                                                    g_TreeEraseBegin(          (G_Tree *) TREE)
#define gpathTreeEraseEnd(            TREE)                                                                    g_TreeEraseEnd(            (G_Tree *) TREE)
#define gpathTreeFind(                TREE, VALUE)                                       (GpathTreeItem *)     g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gpathTreeFlush(               TREE)                                                                    g_TreeFlush(               (G_Tree *) TREE)
#define gpathTreeForEach(             TREE, FUNC)                                                              g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gpathTreeGetBegin(            TREE)                                              (GpathTreeItem *)     g_TreeGetBegin(            (G_Tree *) TREE)
#define gpathTreeGetCount(            TREE)                                                                    g_TreeGetCount(            (G_Tree *) TREE)
#define gpathTreeGetEnd(              TREE)                                              (GpathTreeItem *)     g_TreeGetEnd(              (G_Tree *) TREE)
#define gpathTreeItemDloc(            TREE, TITEM)                                                             g_TreeItemDloc(            (G_Tree *) TREE, TITEM)
#define gpathTreeItemGet(                   TITEM)                                     *((Gpath **)            g_TreeItemGet(                              TITEM))
#define gpathTreeItemGetNext(               TITEM)                                       (GpathTreeItem *)     g_TreeItemGetNext(                          TITEM)
#define gpathTreeItemGetPrev(               TITEM)                                       (GpathTreeItem *)     g_TreeItemGetPrev(                          TITEM)
#define gpathTreeItemUpdate(          TREE, TITEM, VALUE)                                                      g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define gpathTreeKeyAdd(              TREE, KEY, VALUE)                                  (GpathTreeKeyItem *)  g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gpathTreeKeyCloc(                   COMPARE_FUNC)                                (GpathTreeKey *)      g_TreeKeyCloc(                               "GpathTreeKey", Gpath *, COMPARE_FUNC)
#define gpathTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                      g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GpathTreeKey", Gpath *, COMPARE_FUNC)
#define gpathTreeKeyDloc(             TREE)                                                                    g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gpathTreeKeyDlocContent(      TREE)                                                                    g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gpathTreeKeyErase(            TREE, KEY)                                                               g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gpathTreeKeyEraseBegin(       TREE)                                                                    g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gpathTreeKeyEraseEnd(         TREE)                                                                    g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gpathTreeKeyFind(             TREE, KEY)                                         (GpathTreeKeyItem *)  g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gpathTreeKeyFlush(            TREE)                                                                    g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gpathTreeKeyForEach(          TREE, FUNC)                                                              g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gpathTreeKeyGetBegin(         TREE)                                              (GpathTreeKeyItem *)  g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gpathTreeKeyGetCount(         TREE)                                                                    g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gpathTreeKeyGetEnd(           TREE)                                              (GpathTreeKeyItem *)  g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gpathTreeKeyItemDloc(         TREE, TITEM)                                                             g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gpathTreeKeyItemGet(                TITEM)                                     *((Gpath **)            g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM))
#define gpathTreeKeyItemGetNext(            TITEM)                                       (GpathTreeKeyItem *)  g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gpathTreeKeyItemGetPrev(            TITEM)                                       (GpathTreeKeyItem *)  g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gpathTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                      g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
