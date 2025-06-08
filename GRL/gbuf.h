/**************************************************************************************************
file:         Gbuf
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
Dynamic byte buffer to hold anything.  User of these routines need to know how
to encode and decode the buffer.  Mainly to build or consume the buffer from
start to end but not strictly necessary to work that way.
**************************************************************************************************/

#if !defined(GBUFH)
#define      GBUFH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GTYPE_VAR;

   Gn1Array buf;
   Gindex   index;
} Gbuf;

/**************************************************************************************************
prototype:
**************************************************************************************************/
grlAPI Gb          gbufAddAtArray(     Gbuf       * const buf, Gindex const index, Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufAddAtGuid(      Gbuf       * const buf, Gindex const index,                     Gguid        const value);
grlAPI Gb          gbufAddAtV1(        Gbuf       * const buf, Gindex const index,                     Gv1          const value);
grlAPI Gb          gbufAddAtV2(        Gbuf       * const buf, Gindex const index,                     Gv2          const value);
grlAPI Gb          gbufAddAtV4(        Gbuf       * const buf, Gindex const index,                     Gv4          const value);
grlAPI Gb          gbufAddAtV8(        Gbuf       * const buf, Gindex const index,                     Gv8          const value);
grlAPI Gb          gbufAppendArray(    Gbuf       * const buf,                     Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufAppendGuid(     Gbuf       * const buf,                                         Gguid        const value);
grlAPI Gb          gbufAppendV1(       Gbuf       * const buf,                                         Gv1          const value);
grlAPI Gb          gbufAppendV2(       Gbuf       * const buf,                                         Gv2          const value);
grlAPI Gb          gbufAppendV4(       Gbuf       * const buf,                                         Gv4          const value);
grlAPI Gb          gbufAppendV8(       Gbuf       * const buf,                                         Gv8          const value);

grlAPI Gbuf       *gbufCloc_(          void);
grlAPI Gb          gbufClocContent(    Gbuf       * const buf);

grlAPI void        gbufDloc(           Gbuf       * const buf);
grlAPI void        gbufDlocContent(    Gbuf       * const buf);

grlAPI void        gbufFlush(          Gbuf       * const buf);

grlAPI Gn1        *gbufGet(            Gbuf const * const buf);
grlAPI Gb          gbufGetAtArray(     Gbuf const * const buf, Gindex const index, Gcount const count, Gn1        * const value);
grlAPI Gb          gbufGetAtGuid(      Gbuf const * const buf, Gindex const index,                     Gguid      * const value);
grlAPI Gb          gbufGetAtV1(        Gbuf const * const buf, Gindex const index,                     Gv1        * const value);
grlAPI Gb          gbufGetAtV2(        Gbuf const * const buf, Gindex const index,                     Gv2        * const value);
grlAPI Gb          gbufGetAtV4(        Gbuf const * const buf, Gindex const index,                     Gv4        * const value);
grlAPI Gb          gbufGetAtV8(        Gbuf const * const buf, Gindex const index,                     Gv8        * const value);
grlAPI Gb          gbufGetArray(       Gbuf       * const buf,                     Gcount const count, Gn1        * const value);
grlAPI Gcount      gbufGetCount(       Gbuf const * const buf);
grlAPI Gb          gbufGetGuid(        Gbuf       * const buf,                                         Gguid      * const value);
grlAPI Gb          gbufGetV1(          Gbuf       * const buf,                                         Gv1        * const value);
grlAPI Gb          gbufGetV2(          Gbuf       * const buf,                                         Gv2        * const value);
grlAPI Gb          gbufGetV4(          Gbuf       * const buf,                                         Gv4        * const value);
grlAPI Gb          gbufGetV8(          Gbuf       * const buf,                                         Gv8        * const value);

grlAPI Gb          gbufSetCount(       Gbuf       * const buf, Gcount const value);
grlAPI Gb          gbufSetIndex(       Gbuf       * const buf, Gindex const value);

grlAPI Gb          gbufUpdateAtArray(  Gbuf       * const buf, Gindex const index, Gcount const count, Gn1  const * const value);
grlAPI Gb          gbufUpdateAtGuid(   Gbuf       * const buf, Gindex const index,                     Gguid        const value);
grlAPI Gb          gbufUpdateAtV1(     Gbuf       * const buf, Gindex const index,                     Gv1          const value);
grlAPI Gb          gbufUpdateAtV2(     Gbuf       * const buf, Gindex const index,                     Gv2          const value);
grlAPI Gb          gbufUpdateAtV4(     Gbuf       * const buf, Gindex const index,                     Gv4          const value);
grlAPI Gb          gbufUpdateAtV8(     Gbuf       * const buf, Gindex const index,                     Gv8          const value);

/**************************************************************************************************
functions as macros:
**************************************************************************************************/
#define gbufCloc() (Gbuf *) gleakCloc((void *) gbufCloc_(), gsizeof(Gbuf))

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
