/******************************************************************************
file:         Gbuf
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
Dynamic byte buffer to hold anything.  User of these routines need to know how
to encode and decode the buffer.  Mainly to build or consume the buffer from 
start to end but not strictly necessary to work that way.
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
typedef struct
{
   GTYPE_VAR

   Gn1Array buf;
   Gindex   index;
} Gbuf;

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gb          gbufAddAtArray(     Gbuf       * const buf, Gindex const index, Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufAddAtA(         Gbuf       * const buf, Gindex const index,                     Char const * const value);
grlAPI Gb          gbufAddAtGuid(      Gbuf       * const buf, Gindex const index,                     Gguid        const value);
grlAPI Gb          gbufAddAtV1(        Gbuf       * const buf, Gindex const index,                     Gv1          const value);
grlAPI Gb          gbufAddAtV2(        Gbuf       * const buf, Gindex const index,                     Gv2          const value);
grlAPI Gb          gbufAddAtV4(        Gbuf       * const buf, Gindex const index,                     Gv4          const value);
grlAPI Gb          gbufAddAtV8(        Gbuf       * const buf, Gindex const index,                     Gv8          const value);
grlAPI Gb          gbufAddAtS(         Gbuf       * const buf, Gindex const index,                     Gs   const * const value);
grlAPI Gb          gbufAppendArray(    Gbuf       * const buf,                     Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufAppendA(        Gbuf       * const buf,                                         Char const * const value);
grlAPI Gb          gbufAppendGuid(     Gbuf       * const buf,                                         Gguid        const value);
grlAPI Gb          gbufAppendV1(       Gbuf       * const buf,                                         Gv1          const value);
grlAPI Gb          gbufAppendV2(       Gbuf       * const buf,                                         Gv2          const value);
grlAPI Gb          gbufAppendV4(       Gbuf       * const buf,                                         Gv4          const value);
grlAPI Gb          gbufAppendV8(       Gbuf       * const buf,                                         Gv8          const value);
grlAPI Gb          gbufAppendS(        Gbuf       * const buf,                                         Gs   const * const value);

grlAPI Gbuf       *gbufCreate_(        void);
grlAPI Gb          gbufCreateContent(  Gbuf       * const buf);

grlAPI void        gbufDestroy(        Gbuf       * const buf);
grlAPI void        gbufDestroyContent( Gbuf       * const buf);

grlAPI void        gbufFlush(          Gbuf       * const buf);

grlAPI Gn1        *gbufGet(            Gbuf const * const buf);
grlAPI Gn1         gbufGetAtArray(     Gbuf const * const buf, Gindex const index, Gcount * const count, Gn1  ** const value);
grlAPI Gn1         gbufGetAtA(         Gbuf const * const buf, Gindex const index, Gcount * const cound, Char ** const value);
grlAPI Gn1         gbufGetAtGuid(      Gbuf const * const buf, Gindex const index,                       Gguid * const value);
grlAPI Gn1         gbufGetAtV1(        Gbuf const * const buf, Gindex const index,                       Gv1   * const value);
grlAPI Gn1         gbufGetAtV2(        Gbuf const * const buf, Gindex const index,                       Gv2   * const value);
grlAPI Gn1         gbufGetAtV4(        Gbuf const * const buf, Gindex const index,                       Gv4   * const value);
grlAPI Gn1         gbufGetAtV8(        Gbuf const * const buf, Gindex const index,                       Gv8   * const value);
grlAPI Gn1         gbufGetAtS(         Gbuf const * const buf, Gindex const index,                       Gs   ** const value);
grlAPI Gb          gbufGetArray(       Gbuf const * const buf,                     Gcount * const count, Gn1  ** const value);
grlAPI Gb          gbufGetA(           Gbuf const * const buf,                     Gcount * const count, Char ** const value);
grlAPI Gcount      gbufGetCount(       Gbuf const * const buf);
grlAPI Gb          gbufGetGuid(        Gbuf const * const buf,                                           Gguid * const value);
grlAPI Gb          gbufGetV1(          Gbuf const * const buf,                                           Gv1   * const value);
grlAPI Gb          gbufGetV2(          Gbuf const * const buf,                                           Gv2   * const value);
grlAPI Gb          gbufGetV4(          Gbuf const * const buf,                                           Gv4   * const value);
grlAPI Gb          gbufGetV8(          Gbuf const * const buf,                                           Gv8   * const value);
grlAPI Gb          gbufGetS(           Gbuf const * const buf,                                           Gs   ** const value);

grlAPI Gb          gbufSetCount(       Gbuf       * const buf, Gcount const value);
grlAPI Gb          gbufSetIndex(       Gbuf       * const buf, Gindex const value);

grlAPI Gb          gbufUpdateAtArray(  Gbuf       * const buf, Gindex const index, Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufUpdateAtA(      Gbuf       * const buf, Gindex const index,                     Char const * const value);
grlAPI Gb          gbufUpdateAtGuid(   Gbuf       * const buf, Gindex const index,                     Gguid        const value);
grlAPI Gb          gbufUpdateAtV1(     Gbuf       * const buf, Gindex const index,                     Gv1          const value);
grlAPI Gb          gbufUpdateAtV2(     Gbuf       * const buf, Gindex const index,                     Gv2          const value);
grlAPI Gb          gbufUpdateAtV4(     Gbuf       * const buf, Gindex const index,                     Gv4          const value);
grlAPI Gb          gbufUpdateAtV8(     Gbuf       * const buf, Gindex const index,                     Gv8          const value);
grlAPI Gb          gbufUpdateAtS(      Gbuf       * const buf, Gindex const index,                     Gs   const * const value);

/******************************************************************************
functions as macros:
******************************************************************************/
#define gbufCreate() (Gbuf *) gleakCreate((void *) gbufCreate_(), gsizeof(Gbuf))

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
