/******************************************************************************
file:       GsKey
author:     Robbert de Groot
copyright:  2015, Robbert de Groot

description:
Global name table.
******************************************************************************/

#if !defined(GSKEYH)
#define      GSKEYH

/******************************************************************************
type:
******************************************************************************/
typedef Gs     GsKey;

typedef GsHash GsKeyTable;

/******************************************************************************
prototype:
******************************************************************************/
// Global key table functions.
grlAPI GsKey const   *gsKeyIntern(                                       Gs   const * const value);
grlAPI GsKey const   *gsKeyInternA(                                      Char const * const value);
grlAPI GsKey const   *gsKeyInternU2(                                     Gc2  const * const value);

// User provided GsKeyTable functions.
grlAPI GsKey const   *gsKeyTableIntern(   GsKeyTable * const gsKeyTable, Gs   const * const value);
grlAPI GsKey const   *gsKeyTableInternA(  GsKeyTable * const gsKeyTable, Char const * const value);
grlAPI GsKey const   *gsKeyTableInternU2( GsKeyTable * const gsKeyTable, Gc2  const * const value);

grlAPI Gb             gsKeyStart(         void);
grlAPI void           gsKeyStop(          void);

/******************************************************************************
gsKeyTable macroes
******************************************************************************/
#define gsKeyTableAdd(           KEY_TABLE, VALUE)                                 g_HashAdd(           (G_Hash *) KEY_TABLE, (Gp *) VALUE)
#define gsKeyTableCreate(                   HASHSIZE)             (GsKeyTable *)   g_HashCreate(                              "GsKeyTable", GsKey *, gbTRUE, (GrlCompareFunc) gsCompare, (GrlHashFunc) gsHash, HASHSIZE)
#define gsKeyTableCreateContent( KEY_TABLE, HASHSIZE)                              g_HashCreateContent( (G_Hash *) KEY_TABLE, "GsKeyTable", GsKey *, gbTRUE, (GrlCompareFunc) gsCompare, (GrlHashFunc) gsHash, HASHSIZE)
#define gsKeyTableDestroy(       KEY_TABLE)                                        g_HashDestroy(       (G_Hash *) KEY_TABLE)
#define gsKeyTableDestroyContent(KEY_TABLE)                                        g_HashDestroyContent((G_Hash *) KEY_TABLE)
#define gsKeyTableErase(         KEY_TABLE, VALUE)                                 g_HashErase(         (G_Hash *) KEY_TABLE, (Gp *) VALUE)
#define gsKeyTableFind(          KEY_TABLE, VALUE)                (GsKey const *)  g_HashFind(          (G_Hash *) KEY_TABLE, (Gp *) VALUE)
#define gsKeyTableFlush(         KEY_TABLE)                                        g_HashFlush(         (G_Hash *) KEY_TABLE)
#define gsKeyTableForEach(       KEY_TABLE, GRLFOREACHFUNC)                        g_HashForEach(       (G_Hash *) KEY_TABLE, GRLFOREACHFUNC)
#define gsKeyTableGetCount(      KEY_TABLE)                                        g_HashGetCount(      (G_Hash *) KEY_TABLE)

#endif
