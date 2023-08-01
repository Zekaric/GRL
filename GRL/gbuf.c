/******************************************************************************
file:        Gbuf
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
dynamic array.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gbufAddAtArray
******************************************************************************/
grlAPI Gb gbufAddAtArray(Gbuf * const buf, Gindex const bufIndex, Gcount const count, Gn1  const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   forCountDown(index, count)
   {
      result = gn1ArrayAddAt(&buf->buf, bufIndex, &value[index]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gbufAddAtA
******************************************************************************/
grlAPI Gb gbufAddAtA(Gbuf * const buf, Gindex const bufIndex, Char const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   forCountDown(index, gcGetCountA(value))
   {
      result = gn1ArrayAddAt(&buf->buf, bufIndex, &value[index]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gbufAddAtGuid
******************************************************************************/
grlAPI Gb gbufAddAtGuid(Gbuf * const buf, Gindex const bufIndex, Gguid const value)
{
   Gb result;

   genter;

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufAddAtArray(buf, bufIndex, sizeof(Gguid), value.b);

   greturn result;
}

/******************************************************************************
func: gbufAddAtV1
******************************************************************************/
grlAPI Gb gbufAddAtV1(Gbuf * const buf, Gindex const bufIndex, Gv1 const value)
{
   Gb result;

   genter;

   result = gn1ArrayAddAt(&buf->buf, bufIndex, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAddAtV2
******************************************************************************/
grlAPI Gb gbufAddAtV2(Gbuf * const buf, Gindex const bufIndex, Gv2 const value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED
   gswap2(&value);
#endif
   
   result = gbufAddAtArray(buf, bufIndex, 2, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAddAtV4
******************************************************************************/
grlAPI Gb gbufAddAtV4(Gbuf * const buf, Gindex const bufIndex, Gv4 const value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif
   
   result = gbufAddAtArray(buf, bufIndex, 4, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAddAtV8
******************************************************************************/
grlAPI Gb gbufAddAtV8(Gbuf * const buf, Gindex const bufIndex, Gv8 const value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif
   
   result = gbufAddAtArray(buf, bufIndex, 8, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAddAtS

Convert to UTF8 first and then store the value.
******************************************************************************/
grlAPI Gb gbufAddAtS(Gbuf * const buf, Gindex const bufIndex, Gs const * const value)
{
   Gb     result;
   Gc1   *u1;

   genter;
   
   u1 = gsCreateU1(value);
   greturnFalseIf(!u1);

   result = gbufAddAtA(buf, bufIndex, (Char *) u1);
   
   gmemDestroy(u1);

   greturn result;
}

/******************************************************************************
func: gbufAppendArray
******************************************************************************/
grlAPI Gb gbufAppendArray(Gbuf * const buf, Gcount const count, Gn1 const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   forCount(index, count)
   {
      result = gn1ArrayAddEnd(&buf->buf, &value[index]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gbufAppendA
******************************************************************************/
grlAPI Gb gbufAppendA(Gbuf * const buf, Char const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   loopCount(index)
   {
      result = gn1ArrayAddEnd(&buf->buf, &value[index]);
      breakIf(value[index] == 0);
   }

   greturn result;
}

/******************************************************************************
func: gbufAppendGuid
******************************************************************************/
grlAPI Gb gbufAppendGuid(Gbuf * const buf, Gguid const value)
{
   Gb result;

   genter;

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufAppendArray(buf, sizeof(Gguid), value.b);

   greturn result;
}

/******************************************************************************
func: gbufAppendV1
******************************************************************************/
grlAPI Gb gbufAppendV1(Gbuf * const buf, Gv1 value)
{
   Gb result;

   genter;

   result = gn1ArrayAddEnd(&buf->buf, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAppendV2
******************************************************************************/
grlAPI Gb gbufAppendV2(Gbuf * const buf, Gv2 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED
   gswap2(&value);
#endif
   
   result = gbufAppendArray(buf, 2, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAppendV4
******************************************************************************/
grlAPI Gb gbufAppendV4(Gbuf * const buf, Gv4 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif
   
   result = gbufAppendArray(buf, 4, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAppendV8
******************************************************************************/
grlAPI Gb gbufAppendV8(Gbuf * const buf, Gv8 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif
   
   result = gbufAppendArray(buf, 8, (Gn1 *) &value.n);

   greturn result;
}

/******************************************************************************
func: gbufAppendS
******************************************************************************/
grlAPI Gb gbufAppendS(Gbuf * const buf, Gs const * const value)
{
   Gb     result;
   Gc1   *u1;

   genter;
   
   u1 = gsCreateU1(value);
   greturnFalseIf(!u1);
   result = gbufAppendA(buf, (Char *) u1);
   gmemDestroy(u1);

   greturn result;
}

/******************************************************************************
func: gbufCreate_
******************************************************************************/
grlAPI Gbuf *gbufCreate_(void)
{
   Gbuf *buf;

   genter;

   buf = gmemCreateType(Gbuf);
   greturnNullIf(!buf);

   if (!gbufCreateContent(buf))
   {
      gbufDestroy(buf);
      greturn NULL;
   }

   greturn buf;
}

/******************************************************************************
func: gbufCreateContent
******************************************************************************/
grlAPI Gb gbufCreateContent(Gbuf * const buf)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   GTYPE_SET(buf, "Gbuf");

   buf->index = 0;
   result = gn1ArrayCreateContent(&buf->buf, NULL, gbTRUE);

   greturn result;
}

/******************************************************************************
func: gbufDestroy
******************************************************************************/
grlAPI void gbufDestroy(Gbuf * const buf)
{
   genter;

   greturnVoidIf(!buf);

   gbufDestroyContent(buf);

   gmemDestroy(buf);

   greturn;
}

/******************************************************************************
func: gbufDestroyContent
******************************************************************************/
grlAPI void gbufDestroyContent(Gbuf * const buf)
{
   genter;

   greturnVoidIf(!buf);

   gn1ArrayDestroyContent(&buf->buf);
   buf->index = 0;

   greturn;
}

/******************************************************************************
func: gbufFlush
******************************************************************************/
grlAPI void gbufFlush(Gbuf * const buf)
{
   genter;

   greturnVoidIf(!buf);

   gn1ArrayFlush(&buf->buf);
   buf->index = 0;

   greturn;
}

/******************************************************************************
func: 
******************************************************************************/
grlAPI Gn1 *gbufGet(Gbuf const * const buf)
{
   Gn1 *result;

   genter;

   greturnNullIf(!buf);

   result = gn1ArrayGet(&buf->buf);

   greturn result;
}

/******************************************************************************
func: gbufGetAtArray
******************************************************************************/
grlAPI Gn1 gbufGetAtArray(Gbuf const * const buf, Gindex const index, Gcount * const count, Gn1 ** const value)
{
}

/******************************************************************************
func: gbufGetAtA
******************************************************************************/
grlAPI Gn1 gbufGetAtA(Gbuf const * const buf, Gindex const index, Gcount * const cound, Char ** const value)
{
}

/******************************************************************************
func: gbufGetAtGuid
******************************************************************************/
grlAPI Gn1 gbufGetAtGuid(Gbuf const * const buf, Gindex const index, Gguid * const value)
{
}

/******************************************************************************
func: gbufGetAtI1
******************************************************************************/
grlAPI Gn1 gbufGetAtV1(Gbuf const * const buf, Gindex const index, Gv1 * const value)
{
}

/******************************************************************************
func: gbufGetAtV2
******************************************************************************/
grlAPI Gn1 gbufGetAtV2(Gbuf const * const buf, Gindex const index, Gv2 * const value)
{
}

/******************************************************************************
func: gbufGetAtV4
******************************************************************************/
grlAPI Gn1 gbufGetAtV4(Gbuf const * const buf, Gindex const index, Gv4 * const value)
{
}

/******************************************************************************
func: gbufGetAtV8
******************************************************************************/
grlAPI Gn1 gbufGetAtV8(Gbuf const * const buf, Gindex const index, Gv8 * const value)
{
}

/******************************************************************************
func: gbufGetAtS
******************************************************************************/
grlAPI Gn1 gbufGetAtS(Gbuf const * const buf, Gindex const index, Gs ** const value)
{
}

/******************************************************************************
func: gbufGetArray
******************************************************************************/
grlAPI Gb gbufGetArray(Gbuf const * const buf, Gcount * const count, Gn1 ** const value)
{
}

/******************************************************************************
func: gbufGetA
******************************************************************************/
grlAPI Gb gbufGetA(Gbuf const * const buf, Gcount * const count, Char ** const value)
{
}

/******************************************************************************
func: gbufGetCount
******************************************************************************/
grlAPI Gcount gbufGetCount(Gbuf const * const buf)
{
}

/******************************************************************************
func: gbufGetGuid
******************************************************************************/
grlAPI Gb gbufGetGuid(Gbuf const * const buf, Gguid * const value)
{
}

/******************************************************************************
func: gbufGetV1
******************************************************************************/
grlAPI Gb gbufGetV1(Gbuf const * const buf, Gv1 * const value)
{
}

/******************************************************************************
func: gbufGetV2
******************************************************************************/
grlAPI Gb gbufGetV2(Gbuf const * const buf, Gv2 * const value)
{
}

/******************************************************************************
func: gbufGetV4
******************************************************************************/
grlAPI Gb gbufGetV4(Gbuf const * const buf, Gv4 * const value)
{
}

/******************************************************************************
func: gbufGetV8
******************************************************************************/
grlAPI Gb gbufGetV8(Gbuf const * const buf, Gv8 * const value)
{
}

/******************************************************************************
func: gbufGetS
******************************************************************************/
grlAPI Gb gbufGetS(Gbuf const * const buf, Gs ** const value)
{
}

/******************************************************************************
func: gbufSetCount
******************************************************************************/
grlAPI Gb gbufSetCount(Gbuf * const buf, Gcount const value)
{
}

/******************************************************************************
func: gbufSetIndex
******************************************************************************/
grlAPI Gb gbufSetIndex(Gbuf * const buf, Gindex const value)
{
   genter;

   greturnFalseIf(
      !buf      ||
      value < 0 || gn1ArrayGetSize(&buf->buf) <= value);

   buf->index = value;

   greturn gbTRUE;
}

/******************************************************************************
func: gbufUpdateAtArray
******************************************************************************/
grlAPI Gb gbufUpdateAtArray(Gbuf * const buf, Gindex const index, Gcount const count, Gn1 const * const value)
{
}

/******************************************************************************
func: gbufUpdateAtA
******************************************************************************/
grlAPI Gb gbufUpdateAtA(Gbuf * const buf, Gindex const index, Char const * const value)
{
}

/******************************************************************************
func: gbufUpdateAtGuid
******************************************************************************/
grlAPI Gb gbufUpdateAtGuid(Gbuf * const buf, Gindex const index, Gguid const value)
{
}

/******************************************************************************
func: gbufUpdateAtV1
******************************************************************************/
grlAPI Gb gbufUpdateAtV1(Gbuf * const buf, Gindex const index, Gv1 const value)
{
}

/******************************************************************************
func: gbufUpdateAtV2
******************************************************************************/
grlAPI Gb gbufUpdateAtV2(Gbuf * const buf, Gindex const index, Gv2 const value)
{
}

/******************************************************************************
func: gbufUpdateAtV4
******************************************************************************/
grlAPI Gb gbufUpdateAtV4(Gbuf * const buf, Gindex const index, Gv4 const value)
{
}

/******************************************************************************
func: gbufUpdateAtV8
******************************************************************************/
grlAPI Gb gbufUpdateAtV8(Gbuf * const buf, Gindex const index, Gv8 const value)
{
}

/******************************************************************************
func: gbufUpdateAtS
******************************************************************************/
grlAPI Gb gbufUpdateAtS(Gbuf * const buf, Gindex const index, Gs const * const value)
{
}
