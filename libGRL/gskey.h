/**************************************************************************************************
file:       GsKey
author:     Robbert de Groot
copyright:  2015, Robbert de Groot

description:
Global name table.
**************************************************************************************************/

#pragma once

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gs     GsKey;

typedef GvHash GsKeyTable;

/**************************************************************************************************
prototype:
**************************************************************************************************/
// Global key table functions.
grlAPI GsKey const   *gsKeyIntern(                                       Gs   const * const value);

// User provided GsKeyTable functions.
grlAPI GsKey const   *gsKeyTableIntern(   GsKeyTable * const gsKeyTable, Gs   const * const value);

grlAPI Gb             gsKeyStart(         void);
grlAPI void           gsKeyStop(          void);

/**************************************************************************************************
gsKeyTable macroes
**************************************************************************************************/
#define gsKeyTableAdd(           KEY_TABLE, VALUE)                                  gvHashAdd(        (GvHash *) KEY_TABLE, gvFromP((Gp *) VALUE))
#define gsKeyTableCloc(                     HASHSIZE)       (GsKeyTable *)          gvHashCloc(                             "GsKeyTable", (GrlCompareFunc) gsCompareContainer, (GrlHashFunc) gsHashContainer, HASHSIZE)
#define gsKeyTableClocContent(   KEY_TABLE, HASHSIZE)                               gvHashClocContent((GvHash *) KEY_TABLE, "GsKeyTable", (GrlCompareFunc) gsCompareContainer, (GrlHashFunc) gsHashContainer, HASHSIZE)
#define gsKeyTableDloc(          KEY_TABLE)                                         gvHashDloc(       (GvHash *) KEY_TABLE)
#define gsKeyTableDlocContent(   KEY_TABLE)                                         gvHashDlocContent((GvHash *) KEY_TABLE)
#define gsKeyTableErase(         KEY_TABLE, VALUE)                                  gvHashErase(      (GvHash *) KEY_TABLE, gvFromP((Gp *) VALUE))
#define gsKeyTableFind(          KEY_TABLE, VALUE)          (GsKey const *) gvGetS( gvHashFind(       (GvHash *) KEY_TABLE, gvFromP((Gp *) VALUE)))
#define gsKeyTableFlush(         KEY_TABLE)                                         gvHashFlush(      (GvHash *) KEY_TABLE)
#define gsKeyTableForEach(       KEY_TABLE, GRLFOREACHFUNC)                         gvHashForEach(    (GvHash *) KEY_TABLE, GRLFOREACHFUNC)
#define gsKeyTableGetCount(      KEY_TABLE)                                         gvHashGetCount(   (GvHash *) KEY_TABLE)
