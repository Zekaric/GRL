/******************************************************************************
file:         Gbuf
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
Dynamic byte buffer to hold anything.  User of these routines need to know how
to encode and decode the buffer.
******************************************************************************/

#if !defined(GBUFH)
#define      GBUFH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
type:
******************************************************************************/
typedef Gn1Array Gbuf;

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gb          gbufAddAt(          Gbuf       * const s, Gindex const index, Gn1 const value);
grlAPI Gb          gbufAddBegin(       Gbuf       * const s,                     Gn1 const value);
grlAPI Gb          gbufAddEnd(         Gbuf       * const s,                     Gn1 const value);
grlAPI Gb          gbufAddEndArray(    Gbuf       * const s, Gcount const count, Gn1 const * const value);
grlAPI Gb          gbufAddEndA(        Gbuf       * const s,                     Char const * const value);
grlAPI Gb          gbufAddEndGuid(     Gbuf       * const s,                     Gguid const value);
grlAPI Gb          gbufAddEndI2(       Gbuf       * const s,                     Gi2 value);
grlAPI Gb          gbufAddEndI4(       Gbuf       * const s,                     Gi4 value);
grlAPI Gb          gbufAddEndI8(       Gbuf       * const s,                     Gi8 value);
grlAPI Gb          gbufAddEndId(       Gbuf       * const s,                     Gid const value);
grlAPI Gb          gbufAddEndN2(       Gbuf       * const s,                     Gn2 value);
grlAPI Gb          gbufAddEndN4(       Gbuf       * const s,                     Gn4 value);
grlAPI Gb          gbufAddEndN8(       Gbuf       * const s,                     Gn8 value);
grlAPI Gb          gbufAddEndR4(       Gbuf       * const s,                     Gr4 value);
grlAPI Gb          gbufAddEndR8(       Gbuf       * const s,                     Gr8 value);
grlAPI Gb          gbufAddEndS(        Gbuf       * const s,                     Gs const * const value);

grlAPI Gb          gbufClear(          Gbuf       * const s, Gcount const count, Gindex const index);
grlAPI Gb          gbufCopy(           Gbuf       * const s, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb          gbufCopyFrom(       Gbuf       * const sDst, Gindex const indexDst, Gbuf const * const sSrc, Gcount const count, Gindex const indexSrc);
grlAPI Gbuf       *gbufCreate_(        void);
grlAPI Gb          gbufCreateContent(  Gbuf       * const s);

grlAPI void        gbufDestroy(        Gbuf       * const s);
grlAPI void        gbufDestroyContent( Gbuf const * const s);

grlAPI Gb          gbufEraseAt(        Gbuf       * const s, Gcount const count, Gindex const index);
grlAPI void        gbufEraseBegin(     Gbuf       * const s);
grlAPI void        gbufEraseEnd(       Gbuf       * const s);

grlAPI Gindex      gbufFind(           Gbuf const * const s, Gp const * const value);
grlAPI void        gbufFlush(          Gbuf       * const s);
grlAPI Gb          gbufForEach(        Gbuf const * const s, GrlForEachFunc const func);

grlAPI Gn1        *gbufGet(            Gbuf const * const s);
grlAPI Gn1         gbufGetAt(          Gbuf const * const s, Gindex const index);
grlAPI Gn1         gbufGetBegin(       Gbuf const * const s);
grlAPI Gcount      gbufGetCount(       Gbuf const * const s);
grlAPI Gn1         gbufGetEnd(         Gbuf const * const s);

grlAPI Gb          gbufSetCount(       Gbuf       * const s, Gcount const value);
grlAPI Gb          gbufSwap(           Gbuf       * const s, Gindex const indexA, Gindex const indexB);

grlAPI Gb          gbufUpdateAt(       Gbuf       * const s, Gindex const index, Gn1 const value);

/******************************************************************************
functions as macros:
******************************************************************************/
#define gbufAddAt(         BUF, INDEX, VALUE)                           gn1ArrayAddAt(        (Gn1Array *) (BUF), INDEX, VALUE)
#define gbufAddBegin(      BUF,        VALUE)                           gn1ArrayAddBegin(     (Gn1Array *) (BUF),        VALUE)
#define gbufAddEnd(        BUF,        VALUE)                           gn1ArrayAddEnd(       (Gn1Array *) (BUF),        VALUE)
#define gbufClear(         BUF, INDEX, COUNT)                           gn1ArrayClear(        (Gn1Array *) (BUF), INDEX, COUNT)
#define gbufCopy(          BUF, COUNT, INDEXSRC, INDEXDST)              gn1ArrayCopy(         (Gn1Array *) (BUF), COUNT, INDEXSRC, INDEXDST)
#define gbufCopyFrom(      BUFDST, INDEXDST, BUFSRC, COUNT, INDEXSRC)   gn1ArrayCopyFrom(     (Gn1Array *) (BUFDST), INDEXDST, (Gn1Array *) (BUFSRC), COUNT, INDEXSRC)
#define gbufCreate()                                      (Gn1Array *)  g_ArrayCreate(                            "Gbuf", Gn1, gbFALSE, NULL, gbTRUE, gbFALSE)
#define gbufCreateContent( BUF)                                         g_ArrayCreateContent( (G_Array *)  (BUF), "Gbuf", Gn1, gbFALSE, NULL, gbTRUE, gbFALSE)
#define gbufDestroy(       BUF)                                         g_ArrayDestroy(       (G_Array *)  (BUF)) 
#define gbufDestroyContent(BUF)                                         g_ArrayDestroyContent((G_Array *)  (BUF)) 
#define gbufEraseAt(       BUF, COUNT, INDEX)                           gn1ArrayEraseAt(      (Gn1Array *) (BUF), COUNT, INDEX)
#define gbufEraseBegin(    BUF)                                         gn1ArrayEraseBegin(   (Gn1Array *) (BUF))
#define gbufEraseEnd(      BUF)                                         gn1ArrayEraseEnd(     (Gn1Array *) (BUF))
#define gbufFind(          BUF, VALUE)                                  gn1ArrayFind(         (Gn1Array *) (BUF), VALUE)
#define gbufFlush(         BUF)                                         gn1ArrayFlush(        (Gn1Array *) (BUF))
#define gbufForEach(       BUF, FUNC)                                   gn1ArrayForEach(      (Gn1Array *) (BUF), FUNC)
#define gbufGet(           BUF)                                         gn1ArrayGet(          (Gn1Array *) (BUF))
#define gbufGetAt(         BUF, INDEX)                                  gn1ArrayGetAt(        (Gn1Array *) (BUF), INDEX)
#define gbufGetBegin(      BUF)                                         gn1ArrayGetBegin(     (Gn1Array *) (BUF))
#define gbugGetCount(      BUF)                                         gn1ArrayGetCount(     (Gn1Array *) (BUF))
#define gbufGetEnd(        BUF)                                         gn1ArrayGetEnd(       (Gn1Array *) (BUF))
#define gbufSetCount(      BUF)                                         gn1ArraySetCount(     (Gn1Array *) (BUF))
#define gbufSwap(          BUF, INDEXA, INDEXB)                         gn1ArraySwap(         (Gn1Array *) (BUF), INDEXA, INDEXB)
#define gbufUpdateAt(      BUF, INDEX, VALUE)                           gn1ArrayUpdateAt(     (Gn1Array *) (BUF), INDEX, VALUE)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
