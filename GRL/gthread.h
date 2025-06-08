/**************************************************************************************************
file:       gthread
author:     Robbert de Groot
copyright:  2009-2012, Robbert de Groot

description:
Threading routines.
**************************************************************************************************/

#if !defined(GTHREADH)
#define      GTHREADH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define gthreadMODULE "gthread"

typedef enum
{
   gthreadErrorNONE,
   gthreadErrorCREATE_MEMORY_FAIL,
   gthreadErrorCREATE_THREAD_FAIL,

   gthreadErrorLAST
} GthreadError;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GTYPE_VAR;

#if grlWINDOWS == 1
   HANDLE    handle;
   Gn4       id;
#else
#endif
} Gthread;

#if grlWINDOWS == 1
/*lint -save -e950 -e955 -e960 */
typedef Gn4 (__stdcall *GthreadFunction)(Gp *);
/*lint -restore */
#else
#endif

/**************************************************************************************************
prototype:
**************************************************************************************************/
// Thread functions.
grlAPI Gthread   *gthreadCloc(            GthreadFunction const function, Gp * const data);

grlAPI Gb         gthreadDloc(            Gthread       * const thread);

grlAPI Gb         gthreadGetReturnValue(  Gthread const * const thread, Gi4 * const value);

grlAPI Gb         gthreadIsGood(          Gthread const * const thread);

grlAPI Gb         gthreadWait(            Gcount const threadCount, Gthread const * const * const threadList);

// Inside the thread functions.
grlAPI Gb         gthreadCurrentExit(     Gn4 const exitValue);

grlAPI void       gthreadCurrentPause(    void);

/**************************************************************************************************
Gthread containers.
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
   Gthread                **p;
} GthreadArray;

// Same as G_ArrayKey /////////////////////////////////////////////////////////
typedef struct 
{
   Gkey const              *key;
   Gthread                 *p;
} GthreadArrayKeyCell;

typedef struct
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   GthreadArrayKeyCell    **p;
} GthreadArrayKey;

// Same as G_List and G_ListItem //////////////////////////////////////////////
typedef struct GthreadListItem GthreadListItem;
struct GthreadListItem
{
   GthreadListItem         *next,
                           *prev;
   Gthread                 *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GthreadListItem         *head,
                           *tail;
} GthreadList;

// Same as G_ListKey and G_ListKeyItem ////////////////////////////////////////
typedef struct GthreadListKeyItem GthreadListKeyItem;
struct GthreadListKeyItem
{
   GthreadListKeyItem      *next,
                           *prev;
   Gkey const              *key;
   Gthread                 *p;
};

typedef struct
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   Gb                       isSorted;
   GthreadListKeyItem      *head,
                           *tail;
} GthreadListKey;

// Same as G_Hash /////////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GrlHashFunc              hashFunc;
   GrlCompareFunc           compareFunc;
   GthreadList            **binArray;
   GhashSize                binCount;
} GthreadHash;

// Same as G_HashKey //////////////////////////////////////////////////////////
typedef struct
{
   GCONTAINER_VAR;

   GthreadListKey         **binArray;
   GhashSize                binCount;
} GthreadHashKey;

// same as G_Tree and G_TreeItem //////////////////////////////////////////////
typedef struct GthreadTree     GthreadTree;
typedef struct GthreadTreeItem GthreadTreeItem;
struct GthreadTreeItem
{
   GthreadTree             *owner;
   GthreadTreeItem         *parent;
   GthreadTreeItem         *childLeft;
   GthreadTreeItem         *childRight;
   GheapN                   heapValue;
   Gthread                 *p;
};

struct GthreadTree
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GthreadTreeItem         *root;
};

// Same as G_TreeKey and G_TreeKeyItem ////////////////////////////////////////
typedef struct GthreadTreeKey     GthreadTreeKey;
typedef struct GthreadTreeKeyItem GthreadTreeKeyItem;
struct GthreadTreeKeyItem
{
   GthreadTreeKey          *owner;
   GthreadTreeKeyItem      *parent;
   GthreadTreeKeyItem      *childLeft;
   GthreadTreeKeyItem      *childRight;
   GheapN                   heapValue;
   Gkey const              *key;
   Gthread                 *p;
};

struct GthreadTreeKey
{
   GCONTAINER_VAR;

   GrlCompareFunc           compareFunc;
   GthreadTreeKeyItem      *root;
};

#define gthreadArrayAdd(                ARRAY,        VALUE)                                                      g_ArrayAddP(               (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gthreadArrayAddAt(              ARRAY, INDEX, VALUE)                                                      g_ArrayAddAtP(             (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gthreadArrayAddBegin(           ARRAY,        VALUE)                                                      g_ArrayAddBeginP(          (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gthreadArrayAddEnd(             ARRAY,        VALUE)                                                      g_ArrayAddEndP(            (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gthreadArrayClear(              ARRAY, COUNT, INDEX)                                                      g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gthreadArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                         g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gthreadArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                            g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gthreadArrayCloc(                      OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GthreadArray *)       g_ArrayCloc(                                "GthreadArray", Gthread *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gthreadArrayClocContent(        ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                           g_ArrayClocContent(      (G_Array *) ARRAY, "GthreadArray", Gthread *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING, gbFALSE)
#define gthreadArrayDloc(               ARRAY)                                                                    g_ArrayDloc(               (G_Array *) ARRAY) 
#define gthreadArrayDlocContent(        ARRAY)                                                                    g_ArrayDlocContent(        (G_Array *) ARRAY) 
#define gthreadArrayErase(              ARRAY, VALUE)                                                             g_ArrayEraseP(             (G_Array *) ARRAY, (Gp *) VALUE) 
#define gthreadArrayEraseAt(            ARRAY, COUNT, INDEX)                                                      g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gthreadArrayEraseBegin(         ARRAY)                                                                    g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gthreadArrayEraseEnd(           ARRAY)                                                                    g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gthreadArrayFind(               ARRAY, VALUE)                                                             g_ArrayFindP(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gthreadArrayFlush(              ARRAY)                                                                    g_ArrayFlush(              (G_Array *) ARRAY) 
#define gthreadArrayForEach(            ARRAY, FUNC)                                                              g_ArrayForEachP(           (G_Array *) ARRAY, FUNC) 
#define gthreadArrayGet(                ARRAY)                                             (Gthread **)           g_ArrayGet(                (G_Array *) ARRAY) 
#define gthreadArrayGetAt(              ARRAY, INDEX)                                      (Gthread *)            g_ArrayGetAtP(             (G_Array *) ARRAY, INDEX))
#define gthreadArrayGetBegin(           ARRAY)                                             (Gthread *)            g_ArrayGetBeginP(          (G_Array *) ARRAY))
#define gthreadArrayGetCount(           ARRAY)                                                                    g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gthreadArrayGetEnd(             ARRAY)                                             (Gthread *)            g_ArrayGetEndP(            (G_Array *) ARRAY))
#define gthreadArrayGetSize(            ARRAY)                                                                    g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gthreadArraySetCount(           ARRAY, COUNT)                                                             g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gthreadArraySort(               ARRAY)                                                                    g_ArraySort(               (G_Array *) ARRAY) 
#define gthreadArraySwap(               ARRAY, INDEXA, INDEXB)                                                    g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gthreadArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                      g_ArrayUpdateAtP(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gthreadArrayKeyAdd(             ARRAY,        KEY, VALUE)                                                 g_ArrayKeyAdd(             (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gthreadArrayKeyAddAt(           ARRAY, INDEX, KEY, VALUE)                                                 g_ArrayKeyAddAt(           (G_ArrayKey *) ARRAY, INDEX, KEY, (Gp *) VALUE) 
#define gthreadArrayKeyAddBegin(        ARRAY,        KEY, VALUE)                                                 g_ArrayKeyAddBegin(        (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gthreadArrayKeyAddEnd(          ARRAY,        KEY, VALUE)                                                 g_ArrayKeyAddEnd(          (G_ArrayKey *) ARRAY,        KEY, (Gp *) VALUE) 
#define gthreadArrayKeyClear(           ARRAY, COUNT, INDEX)                                                      g_ArrayKeyClear(           (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gthreadArrayKeyCopy(            ARRAY, COUNT, INDEXSRC, INDEXDST)                                         g_ArrayKeyCopy(            (G_ArrayKey *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gthreadArrayKeyCopyFrom(        ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                            g_ArrayKeyCopyFrom(        (G_ArrayKey *) ARRAYDST, INDEXDST, (G_ArrayKey *) ARRAYSRC, COUNT, INDEXSRC) 
#define gthreadArrayKeyCloc(                   OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)    (GthreadArray *)       g_ArrayKeyCloc(                                "GthreadArrayKey", Gthread *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gthreadArrayKeyClocContent(     ARRAY, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)                           g_ArrayKeyClocContent(   (G_ArrayKey *) ARRAY, "GthreadArrayKey", Gthread *, OPTIONAL_COMPARE_FUNC, IS_VECTOR_SIZING)
#define gthreadArrayKeyDloc(            ARRAY)                                                                    g_ArrayKeyDloc(            (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyDlocContent(     ARRAY)                                                                    g_ArrayKeyDlocContent(     (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyErase(           ARRAY, KEY)                                                               g_ArrayKeyErase(           (G_ArrayKey *) ARRAY, KEY) 
#define gthreadArrayKeyEraseAt(         ARRAY, COUNT, INDEX)                                                      g_ArrayKeyEraseAt(         (G_ArrayKey *) ARRAY, COUNT, INDEX) 
#define gthreadArrayKeyEraseBegin(      ARRAY)                                                                    g_ArrayKeyEraseBegin(      (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyEraseEnd(        ARRAY)                                                                    g_ArrayKeyEraseEnd(        (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyFind(            ARRAY, KEY)                                                               g_ArrayKeyFind(            (G_ArrayKey *) ARRAY, KEY) 
#define gthreadArrayKeyFlush(           ARRAY)                                                                    g_ArrayKeyFlush(           (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyForEach(         ARRAY, FUNC)                                                              g_ArrayKeyForEach(         (G_ArrayKey *) ARRAY, FUNC) 
#define gthreadArrayKeyGetAt(           ARRAY, INDEX)                                    *((Gthread **)           g_ArrayKeyGetAt(           (G_ArrayKey *) ARRAY, INDEX))
#define gthreadArrayKeyGetAtKey(        ARRAY, INDEX)                                                             g_ArrayKeyGetAtKey(        (G_ArrayKey *) ARRAY, INDEX) 
#define gthreadArrayKeyGetBegin(        ARRAY)                                           *((Gthread **)           g_ArrayKeyGetBegin(        (G_ArrayKey *) ARRAY))
#define gthreadArrayKeyGetBeginKey(     ARRAY)                                                                    g_ArrayKeyGetBeginKey(     (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyGetCount(        ARRAY)                                                                    g_ArrayKeyGetCount(        (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyGetEnd(          ARRAY)                                           *((Gthread **)           g_ArrayKeyGetEnd(          (G_ArrayKey *) ARRAY))
#define gthreadArrayKeyGetEndKey(       ARRAY)                                                                    g_ArrayKeyGetEndKey(       (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeyGetSize(         ARRAY)                                                                    g_ArrayKeyGetSize(         (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeySetCount(        ARRAY, COUNT)                                                             g_ArrayKeySetCount(        (G_ArrayKey *) ARRAY, COUNT) 
#define gthreadArrayKeySort(            ARRAY)                                                                    g_ArrayKeySort(            (G_ArrayKey *) ARRAY) 
#define gthreadArrayKeySwap(            ARRAY, INDEXA, INDEXB)                                                    g_ArrayKeySwap(            (G_ArrayKey *) ARRAY, INDEXA, INDEXB) 
#define gthreadArrayKeyUpdateAt(        ARRAY, INDEX, VALUE)                                                      g_ArrayKeyUpdateAt(        (G_ArrayKey *) ARRAY, INDEX, (Gp *) VALUE) 
#define gthreadArrayKeyUpdateAtKey(     ARRAY, INDEX, KEY)                                                        g_ArrayKeyUpdateAtKey(     (G_ArrayKey *) ARRAY, INDEX, KEY) 

#define gthreadListAdd(                 LIST, VALUE)                                       (GthreadListItem *)    g_ListAdd(                 (G_List *) LIST, (Gp *) VALUE)
#define gthreadListAddBegin(            LIST, VALUE)                                       (GthreadListItem *)    g_ListAddBegin(            (G_List *) LIST, (Gp *) VALUE)
#define gthreadListAddEnd(              LIST, VALUE)                                       (GthreadListItem *)    g_ListAddEnd(              (G_List *) LIST, (Gp *) VALUE)
#define gthreadListCloc(                      OPTIONAL_COMPARE_FUNC)                       (GthreadList *)        g_ListCloc(                               "GthreadList", Gthread *, OPTIONAL_COMPARE_FUNC)
#define gthreadListClocContent(         LIST, OPTIONAL_COMPARE_FUNC)                                              g_ListClocContent(       (G_List *) LIST, "GthreadList", Gthread *, OPTIONAL_COMPARE_FUNC)
#define gthreadListDloc(                LIST)                                                                     g_ListDloc(                (G_List *) LIST)
#define gthreadListDlocContent(         LIST)                                                                     g_ListDlocContent(         (G_List *) LIST)
#define gthreadListErase(               LIST, VALUE)                                                              g_ListErase(               (G_List *) LIST, (Gp *) VALUE)
#define gthreadListEraseBegin(          LIST)                                                                     g_ListEraseBegin(          (G_List *) LIST)
#define gthreadListEraseEnd(            LIST)                                                                     g_ListEraseEnd(            (G_List *) LIST)
#define gthreadListFind(                LIST, VALUE)                                       (GthreadListItem *)    g_ListFind(                (G_List *) LIST, (Gp *) VALUE)
#define gthreadListFlush(               LIST)                                                                     g_ListFlush(               (G_List *) LIST)
#define gthreadListForEach(             LIST, FUNC)                                                               g_ListForEach(             (G_List *) LIST, FUNC)
#define gthreadListGetBegin(            LIST)                                              (GthreadListItem *)    g_ListGetBegin(            (G_List *) LIST)
#define gthreadListGetCount(            LIST)                                                                     g_ListGetCount(            (G_List *) LIST)
#define gthreadListGetEnd(              LIST)                                              (GthreadListItem *)    g_ListGetEnd(              (G_List *) LIST)
#define gthreadListItemAdd(             LIST, LITEM, VALUE)                                (GthreadListItem *)    g_ListItemAdd(             (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)
#define gthreadListItemErase(           LIST, LITEM)                                                              g_ListItemErase(           (G_List *) LIST, (G_ListItem *) LITEM)
#define gthreadListItemGet(                   LITEM)                                     *((Gthread **)           g_ListItemGet(                              (G_ListItem *) LITEM))
#define gthreadListItemGetNext(               LITEM)                                       (GthreadListItem *)    g_ListItemGetNext(                          (G_ListItem *) LITEM)
#define gthreadListItemGetPrev(               LITEM)                                       (GthreadListItem *)    g_ListItemGetPrev(                          (G_ListItem *) LITEM)
#define gthreadListItemUpdate(          LIST, LITEM, VALUE)                                                       g_ListItemUpdate(          (G_List *) LIST, (G_ListItem *) LITEM, (Gp *) VALUE)

#define gthreadListKeyAdd(              LIST, KEY, VALUE)                                  (GthreadListKeyItem *) g_ListKeyAdd(              (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gthreadListKeyAddBegin(         LIST, KEY, VALUE)                                  (GthreadListKeyItem *) g_ListKeyAddBegin(         (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gthreadListKeyAddEnd(           LIST, KEY, VALUE)                                  (GthreadListKeyItem *) g_ListKeyAddEnd(           (G_ListKey *) LIST, KEY, (Gp *) VALUE)
#define gthreadListKeyCloc(                   COMPARE_FUNC)                                (GthreadList *)        g_ListKeyCloc(                               "GthreadListKey", Gthread *, COMPARE_FUNC)
#define gthreadListKeyClocContent(      LIST, COMPARE_FUNC)                                                       g_ListKeyClocContent(    (G_ListKey *) LIST, "GthreadListKey", Gthread *, COMPARE_FUNC)
#define gthreadListKeyDloc(             LIST)                                                                     g_ListKeyDloc(             (G_ListKey *) LIST)
#define gthreadListKeyDlocContent(      LIST)                                                                     g_ListKeyDlocContent(      (G_ListKey *) LIST)
#define gthreadListKeyErase(            LIST, KEY)                                                                g_ListKeyErase(            (G_ListKey *) LIST, KEY)
#define gthreadListKeyEraseBegin(       LIST)                                                                     g_ListKeyEraseBegin(       (G_ListKey *) LIST)
#define gthreadListKeyEraseEnd(         LIST)                                                                     g_ListKeyEraseEnd(         (G_ListKey *) LIST)
#define gthreadListKeyFind(             LIST, KEY)                                         (GthreadListKeyItem *) g_ListKeyFind(             (G_ListKey *) LIST, KEY)
#define gthreadListKeyFlush(            LIST)                                                                     g_ListKeyFlush(            (G_ListKey *) LIST)
#define gthreadListKeyForEach(          LIST, FUNC)                                                               g_ListKeyForEach(          (G_ListKey *) LIST, FUNC)
#define gthreadListKeyGetBegin(         LIST)                                              (GthreadListKeyItem *) g_ListKeyGetBegin(         (G_ListKey *) LIST)
#define gthreadListKeyGetCount(         LIST)                                                                     g_ListKeyGetCount(         (G_ListKey *) LIST)
#define gthreadListKeyGetEnd(           LIST)                                              (GthreadListKeyItem *) g_ListKeyGetEnd(           (G_ListKey *) LIST)
#define gthreadListKeyItemAdd(          LIST, LITEM, KEY, VALUE)                           (GthreadListKeyItem *) g_ListKeyItemAdd(          (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY, (Gp *) VALUE)
#define gthreadListKeyItemErase(        LIST, LITEM)                                                              g_ListKeyItemErase(        (G_ListKey *) LIST, (G_ListKeyItem *) LITEM)
#define gthreadListKeyItemGet(          LIST, LITEM)                                     *((Gthread **)           g_ListKeyItemGet(                              (G_ListKeyItem *) LITEM))
#define gthreadListKeyItemGetKey(       LIST, LITEM)                                                              g_ListKeyItemGetKey(                           (G_ListKeyItem *) LITEM)
#define gthreadListKeyItemGetNext(      LIST, LITEM)                                       (GthreadListKeyItem *) g_ListKeyItemGetNext(                          (G_ListKeyItem *) LITEM)
#define gthreadListKeyItemGetPrev(      LIST, LITEM)                                       (GthreadListKeyItem *) g_ListKeyItemGetPrev(                          (G_ListKeyItem *) LITEM)
#define gthreadListKeyItemUpdate(       LIST, LITEM, VALUE)                                                       g_ListKeyItemUpdate(       (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, (Gp *) VALUE)
#define gthreadListKeyItemUpdateKey(    LIST, LITEM, KEY)                                                         g_ListKeyItemUpdateKey(    (G_ListKey *) LIST, (G_ListKeyItem *) LITEM, KEY)

#define gthreadHashAdd(                 HASH, VALUE)                                                              g_HashAdd(                 (G_Hash *) HASH, (Gp *) VALUE)
#define gthreadHashCloc(                      COMPARE_FUNC, HASH_FUNC, HASHSIZE)           (GthreadHash *)        g_HashCloc(                               "GthreadHash", Gthread *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gthreadHashClocContent(         HASH, COMPARE_FUNC, HASH_FUNC, HASHSIZE)                                  g_HashClocContent(       (G_Hash *) HASH, "GthreadHash", Gthread *, COMPARE_FUNC, HASH_FUNC, HASHSIZE)
#define gthreadHashDloc(                HASH)                                                                     g_HashDloc(                (G_Hash *) HASH)
#define gthreadHashDlocContent(         HASH)                                                                     g_HashDlocContent(         (G_Hash *) HASH)
#define gthreadHashErase(               HASH, VALUE)                                                              g_HashErase(               (G_Hash *) HASH, (Gp *) VALUE)
#define gthreadHashFind(                HASH, VALUE)                                     *((Gthread **)           g_HashFind(                (G_Hash *) HASH, (Gp *) VALUE))
#define gthreadHashFlush(               HASH)                                                                     g_HashFlush(               (G_Hash *) HASH)
#define gthreadHashForEach(             HASH, FUNC)                                                               g_HashForEach(             (G_Hash *) HASH, FUNC)
#define gthreadHashGetCount(            HASH)                                                                     g_HashGetCount(            (G_Hash *) HASH)
#define gthreadHashUpdate(              HASH, VALUE)                                                              g_HashUpdate(              (G_Hash *) HASH, (Gp *) VALUE)

#define gthreadHashKeyAdd(              HASH, KEY, VALUE)                                                         g_HashKeyAdd(              (G_HashKey *) HASH, KEY, (Gp *) VALUE)
#define gthreadHashKeyCloc(                   HASHSIZE)                                    (GthreadHashKey *)     g_HashKeyCloc(                               "GthreadHashKey", Gthread *, HASHSIZE)
#define gthreadHashKeyClocContent(      HASH, HASHSIZE)                                                           g_HashKeyClocContent(    (G_HashKey *) HASH, "GthreadHashKey", Gthread *, HASHSIZE)
#define gthreadHashKeyDloc(             HASH)                                                                     g_HashKeyDloc(             (G_HashKey *) HASH)
#define gthreadHashKeyDlocContent(      HASH)                                                                     g_HashKeyDlocContent(      (G_HashKey *) HASH)
#define gthreadHashKeyErase(            HASH, KEY)                                                                g_HashKeyErase(            (G_HashKey *) HASH, KEY)
#define gthreadHashKeyFind(             HASH, KEY)                                       *((Gthread **)           g_HashKeyFind(             (G_HashKey *) HASH, KEY))
#define gthreadHashKeyFlush(            HASH)                                                                     g_HashKeyFlush(            (G_HashKey *) HASH)
#define gthreadHashKeyForEach(          HASH, FUNC)                                                               g_HashKeyForEach(          (G_HashKey *) HASH, FUNC)
#define gthreadHashKeyGetCount(         HASH)                                                                     g_HashKeyGetCount(         (G_HashKey *) HASH)
#define gthreadHashKeyUpdate(           HASH, KEY, VALUE)                                                         g_HashKeyUpdate(           (G_HashKey *) HASH, KEY, (Gp *) VALUE)

#define gthreadTreeAdd(                 TREE, VALUE)                                       (GthreadTreeItem *)    g_TreeAdd(                 (G_Tree *) TREE, (Gp *) VALUE)
#define gthreadTreeCloc(                      COMPARE_FUNC)                                (GthreadTree *)        g_TreeCloc(                               "GthreadTree", Gthread *, COMPARE_FUNC)
#define gthreadTreeClocContent(         TREE, COMPARE_FUNC)                                                       g_TreeClocContent(       (G_Tree *) TREE, "GthreadTree", Gthread *, COMPARE_FUNC)
#define gthreadTreeDloc(                TREE)                                                                     g_TreeDloc(                (G_Tree *) TREE)
#define gthreadTreeDlocContent(         TREE)                                                                     g_TreeDlocContent(         (G_Tree *) TREE)
#define gthreadTreeErase(               TREE, VALUE)                                                              g_TreeErase(               (G_Tree *) TREE, (Gp *) VALUE)
#define gthreadTreeEraseBegin(          TREE)                                                                     g_TreeEraseBegin(          (G_Tree *) TREE)
#define gthreadTreeEraseEnd(            TREE)                                                                     g_TreeEraseEnd(            (G_Tree *) TREE)
#define gthreadTreeFind(                TREE, VALUE)                                       (GthreadTreeItem *)    g_TreeFind(                (G_Tree *) TREE, (Gp *) VALUE)
#define gthreadTreeFlush(               TREE)                                                                     g_TreeFlush(               (G_Tree *) TREE)
#define gthreadTreeForEach(             TREE, FUNC)                                                               g_TreeForEach(             (G_Tree *) TREE, FUNC)
#define gthreadTreeGetBegin(            TREE)                                              (GthreadTreeItem *)    g_TreeGetBegin(            (G_Tree *) TREE)
#define gthreadTreeGetCount(            TREE)                                                                     g_TreeGetCount(            (G_Tree *) TREE)
#define gthreadTreeGetEnd(              TREE)                                              (GthreadTreeItem *)    g_TreeGetEnd(              (G_Tree *) TREE)
#define gthreadTreeItemDloc(            TREE, TITEM)                                                              g_TreeItemDloc(            (G_Tree *) TREE, TITEM)
#define gthreadTreeItemGet(                   TITEM)                                     *((Gthread **)           g_TreeItemGet(                              TITEM))
#define gthreadTreeItemGetNext(               TITEM)                                       (GthreadTreeItem *)    g_TreeItemGetNext(                          TITEM)
#define gthreadTreeItemGetPrev(               TITEM)                                       (GthreadTreeItem *)    g_TreeItemGetPrev(                          TITEM)
#define gthreadTreeItemUpdate(          TREE, TITEM, VALUE)                                                       g_TreeItemUpdate(          (G_Tree *) TREE, TITEM, (Gp *) VALUE)

#define gthreadTreeKeyAdd(              TREE, KEY, VALUE)                                  (GthreadTreeKeyItem *) g_TreeKeyAdd(              (G_TreeKey *) TREE, KEY, (Gp *) VALUE)
#define gthreadTreeKeyCloc(                   COMPARE_FUNC)                                (GthreadTreeKey *)     g_TreeKeyCloc(                               "GthreadTreeKey", Gthread *, COMPARE_FUNC)
#define gthreadTreeKeyClocContent(      TREE, COMPARE_FUNC)                                                       g_TreeKeyClocContent(    (G_TreeKey *) TREE, "GthreadTreeKey", Gthread *, COMPARE_FUNC)
#define gthreadTreeKeyDloc(             TREE)                                                                     g_TreeKeyDloc(             (G_TreeKey *) TREE)
#define gthreadTreeKeyDlocContent(      TREE)                                                                     g_TreeKeyDlocContent(      (G_TreeKey *) TREE)
#define gthreadTreeKeyErase(            TREE, KEY)                                                                g_TreeKeyErase(            (G_TreeKey *) TREE, KEY)
#define gthreadTreeKeyEraseBegin(       TREE)                                                                     g_TreeKeyEraseBegin(       (G_TreeKey *) TREE)
#define gthreadTreeKeyEraseEnd(         TREE)                                                                     g_TreeKeyEraseEnd(         (G_TreeKey *) TREE)
#define gthreadTreeKeyFind(             TREE, KEY)                                         (GthreadTreeKeyItem *) g_TreeKeyFind(             (G_TreeKey *) TREE, KEY)
#define gthreadTreeKeyFlush(            TREE)                                                                     g_TreeKeyFlush(            (G_TreeKey *) TREE)
#define gthreadTreeKeyForEach(          TREE, FUNC)                                                               g_TreeKeyForEach(          (G_TreeKey *) TREE, FUNC)
#define gthreadTreeKeyGetBegin(         TREE)                                              (GthreadTreeKeyItem *) g_TreeKeyGetBegin(         (G_TreeKey *) TREE)
#define gthreadTreeKeyGetCount(         TREE)                                                                     g_TreeKeyGetCount(         (G_TreeKey *) TREE)
#define gthreadTreeKeyGetEnd(           TREE)                                              (GthreadTreeKeyItem *) g_TreeKeyGetEnd(           (G_TreeKey *) TREE)
#define gthreadTreeKeyItemDloc(         TREE, TITEM)                                                              g_TreeKeyItemDloc(         (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM)
#define gthreadTreeKeyItemGet(                TITEM)                                     *((Gthread **)           g_TreeKeyItemGet(                              (G_TreeKeyItem *) TITEM))
#define gthreadTreeKeyItemGetNext(            TITEM)                                       (GthreadTreeKeyItem *) g_TreeKeyItemGetNext(                          (G_TreeKeyItem *) TITEM)
#define gthreadTreeKeyItemGetPrev(            TITEM)                                       (GthreadTreeKeyItem *) g_TreeKeyItemGetPrev(                          (G_TreeKeyItem *) TITEM)
#define gthreadTreeKeyItemUpdate(       TREE, TITEM, VALUE)                                                       g_TreeKeyItemUpdate(       (G_TreeKey *) TREE, (G_TreeKeyItem *) TITEM, (Gp *) VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
