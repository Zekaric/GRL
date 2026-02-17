/**************************************************************************************************
file:        Gbuf
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
dynamic array.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gbufAddAtArray
**************************************************************************************************/
grlAPI Gb gbufAddAtArray(Gbuf * const buf, Gindex const index, Gcount const count, Gn1 const * const value)
{
   Gindex     vindex;
   Gb         result;
   Gv1 const *buffer;

   genter;

   buffer = (Gv1 const *) value;

   greturnFalseIf(
      !buf ||
      count < 0);

   forCount(vindex, count)
   {
      result = gv1ArrayAddAt(&buf->buf, index + vindex, buffer[vindex]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufAddAtGuid
**************************************************************************************************/
grlAPI Gb gbufAddAtGuid(Gbuf * const buf, Gindex const index, Gguid const value)
{
   Gb         result;
   Gn1 const *buffer;

   genter;

   buffer = (Gn1 const *) &value;

   greturnFalseIf(!buf);

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufAddAtArray(buf, index, sizeof(Gguid), buffer);

   greturn result;
}

/**************************************************************************************************
func: gbufAddAtV1
**************************************************************************************************/
grlAPI Gb gbufAddAtV1(Gbuf * const buf, Gindex const index, Gv1 const value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   result = gv1ArrayAddAt(&buf->buf, index, value);

   greturn result;
}

/**************************************************************************************************
func: gbufAddAtV2
**************************************************************************************************/
grlAPI Gb gbufAddAtV2(Gbuf * const buf, Gindex const index, Gv2 const value)
{
   Gb  result;
   Gv2 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap2(&vtemp);

   result = gbufAddAtArray(buf, index, 2, vtemp.byte);

   greturn result;
}

/**************************************************************************************************
func: gbufAddAtV4
**************************************************************************************************/
grlAPI Gb gbufAddAtV4(Gbuf * const buf, Gindex const index, Gv4 const value)
{
   Gb  result;
   Gv4 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap4(&vtemp);

   result = gbufAddAtArray(buf, index, 4, vtemp.byte);

   greturn result;
}

/**************************************************************************************************
func: gbufAddAtV8
**************************************************************************************************/
grlAPI Gb gbufAddAtV8(Gbuf * const buf, Gindex const index, Gv8 const value)
{
   Gb  result;
   Gv8 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap8(&vtemp);

   result = gbufAddAtArray(buf, index, 8, vtemp.byte);

   greturn result;
}

/**************************************************************************************************
func: gbufAppendArray
**************************************************************************************************/
grlAPI Gb gbufAppendArray(Gbuf * const buf, Gcount const count, Gn1 const * const value)
{
   Gindex     index;
   Gb         result;
   Gv1 const *buffer;

   genter;

   buffer = (Gv1 *) &value;

   greturnFalseIf(
      !buf ||
      count < 0);

   forCount(index, count)
   {
      result = gv1ArrayAddEnd(&buf->buf, buffer[index]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufAppendGuid
**************************************************************************************************/
grlAPI Gb gbufAppendGuid(Gbuf * const buf, Gguid const value)
{
   Gb   result;
   Gn1 *buffer;

   genter;

   buffer = (Gn1 *) &value;

   greturnFalseIf(!buf);

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufAppendArray(buf, sizeof(Gguid), buffer);

   greturn result;
}

/**************************************************************************************************
func: gbufAppendV1
**************************************************************************************************/
grlAPI Gb gbufAppendV1(Gbuf * const buf, Gv1 value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   result = gv1ArrayAddEnd(&buf->buf, value);

   greturn result;
}

/**************************************************************************************************
func: gbufAppendV2
**************************************************************************************************/
grlAPI Gb gbufAppendV2(Gbuf * const buf, Gv2 value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   gswap2(&value);

   result = gbufAppendArray(buf, 2, (Gn1 *) &value.n);

   greturn result;
}

/**************************************************************************************************
func: gbufAppendV4
**************************************************************************************************/
grlAPI Gb gbufAppendV4(Gbuf * const buf, Gv4 value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   gswap4(&value);

   result = gbufAppendArray(buf, 4, (Gn1 *) &value.n);

   greturn result;
}

/**************************************************************************************************
func: gbufAppendV8
**************************************************************************************************/
grlAPI Gb gbufAppendV8(Gbuf * const buf, Gv8 value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   gswap8(&value);

   result = gbufAppendArray(buf, 8, (Gn1 *) &value.n);

   greturn result;
}

/**************************************************************************************************
func: gbufCloc_
**************************************************************************************************/
grlAPI Gbuf *gbufCloc_(void)
{
   Gbuf *buf;

   genter;

   buf = gmemClocType(Gbuf);
   greturnNullIf(!buf);

   if (!gbufClocContent(buf))
   {
      gbufDloc(buf);
      greturn NULL;
   }

   greturn buf;
}

/**************************************************************************************************
func: gbufClocContent
**************************************************************************************************/
grlAPI Gb gbufClocContent(Gbuf * const buf)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   GTYPE_SET(buf, "Gbuf");

   buf->index = 0;
   result = gv1ArrayClocContent(&buf->buf, "Gbuf", NULL, gbTRUE);

   greturn result;
}

/**************************************************************************************************
func: gbufDloc
**************************************************************************************************/
grlAPI void gbufDloc(Gbuf * const buf)
{
   genter;

   greturnIf(!buf);

   gbufDlocContent(buf);

   gmemDloc(buf);

   greturn;
}

/**************************************************************************************************
func: gbufDlocContent
**************************************************************************************************/
grlAPI void gbufDlocContent(Gbuf * const buf)
{
   genter;

   greturnIf(!buf);

   gv1ArrayDlocContent(&buf->buf);
   buf->index = 0;

   greturn;
}

/**************************************************************************************************
func: gbufFlush
**************************************************************************************************/
grlAPI void gbufFlush(Gbuf * const buf)
{
   genter;

   greturnIf(!buf);

   gv1ArrayFlush(&buf->buf);
   buf->index = 0;

   greturn;
}

/**************************************************************************************************
func: gbufGet
**************************************************************************************************/
grlAPI Gn1 *gbufGet(Gbuf const * const buf)
{
   genter;

   greturnNullIf(!buf);

   greturn (Gn1 *) gv1ArrayGet(&buf->buf);
}

/**************************************************************************************************
func: gbufGetAtArray

value should already be the size of count.
**************************************************************************************************/
grlAPI Gb gbufGetAtArray(Gbuf const * const buf, Gindex const index, Gcount const count, Gn1 * const value)
{
   Gindex vindex;

   genter;

   greturnFalseIf(
      !buf      ||
      count < 0 ||
      !value);

   forCount(vindex, count)
   {
      if (!gbufGetAtV1(buf, index + vindex, (Gv1 *) &(value[vindex])))
      {
         greturn gbFALSE;
      }
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufGetAtGuid
**************************************************************************************************/
grlAPI Gb gbufGetAtGuid(Gbuf const * const buf, Gindex const index, Gguid * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufGetAtArray(buf, index, gsizeof(Gguid), value->b);

   greturn result;
}

/**************************************************************************************************
func: gbufGetAtI1
**************************************************************************************************/
grlAPI Gb gbufGetAtV1(Gbuf const * const buf, Gindex const index, Gv1 * const value)
{
   Gv1 ptemp;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   ptemp = gv1ArrayGetAt(&buf->buf, index);

   value->n = ptemp.n;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufGetAtV2
**************************************************************************************************/
grlAPI Gb gbufGetAtV2(Gbuf const * const buf, Gindex const index, Gv2 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetAtArray(buf, index, 2, (Gn1 *) value);

   gswap2(value);

   greturn result;
}

/**************************************************************************************************
func: gbufGetAtV4
**************************************************************************************************/
grlAPI Gb gbufGetAtV4(Gbuf const * const buf, Gindex const index, Gv4 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetAtArray(buf, index, 4, (Gn1 *) value);

   gswap4(value);

   greturn result;
}

/**************************************************************************************************
func: gbufGetAtV8
**************************************************************************************************/
grlAPI Gb gbufGetAtV8(Gbuf const * const buf, Gindex const index, Gv8 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetAtArray(buf, index, 8, (Gn1 *) value);

   gswap8(value);

   greturn result;
}

/**************************************************************************************************
func: gbufGetArray
**************************************************************************************************/
grlAPI Gb gbufGetArray(Gbuf * const buf, Gcount const count, Gn1 * const value)
{
   Gindex vindex;

   genter;

   greturnFalseIf(
      !buf      ||
      count < 0 ||
      !value    ||
      buf->index >= gv1ArrayGetCount(&buf->buf));

   forCount(vindex, count)
   {
      greturnFalseIf(!gbufGetV1(buf, (Gv1 *) &(value[vindex])));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufGetCount
**************************************************************************************************/
grlAPI Gcount gbufGetCount(Gbuf const * const buf)
{
   Gcount count;

   genter;

   greturn0If(!buf);

   count = gv1ArrayGetCount(&buf->buf);

   greturn count;
}

/**************************************************************************************************
func: gbufGetGuid
**************************************************************************************************/
grlAPI Gb gbufGetGuid(Gbuf * const buf, Gguid * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetArray(buf, gsizeof(Gguid), value->b);

   greturn result;
}

/**************************************************************************************************
func: gbufGetV1
**************************************************************************************************/
grlAPI Gb gbufGetV1(Gbuf * const buf, Gv1 * const value)
{
   Gv1 ptemp;

   genter;

   greturnFalseIf(
      !buf   ||
      !value ||
      buf->index >= gv1ArrayGetCount(&buf->buf));


   ptemp = gv1ArrayGetAt(&buf->buf, buf->index);

   value->n = ptemp.n;

   buf->index++;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufGetV2
**************************************************************************************************/
grlAPI Gb gbufGetV2(Gbuf * const buf, Gv2 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetArray(buf, 2, (Gn1 *) value);

   gswap2(value);

   greturn result;
}

/**************************************************************************************************
func: gbufGetV4
**************************************************************************************************/
grlAPI Gb gbufGetV4(Gbuf * const buf, Gv4 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetArray(buf, 4, (Gn1 *) value);

   gswap4(value);

   greturn result;
}

/**************************************************************************************************
func: gbufGetV8
**************************************************************************************************/
grlAPI Gb gbufGetV8(Gbuf * const buf, Gv8 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      !value);

   result = gbufGetArray(buf, 8, (Gn1 *) value);

   gswap8(value);

   greturn result;
}

/**************************************************************************************************
func: gbufSetCount
**************************************************************************************************/
grlAPI Gb gbufSetCount(Gbuf * const buf, Gcount const value)
{
   Gb result;

   genter;

   greturnFalseIf(
      !buf ||
      value < 0);

   result = gv1ArraySetCount(&buf->buf, value);

   greturn result;
}

/**************************************************************************************************
func: gbufSetIndex
**************************************************************************************************/
grlAPI Gb gbufSetIndex(Gbuf * const buf, Gindex const value)
{
   genter;

   greturnFalseIf(!buf);

   buf->index = value;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufUpdateAtArray
**************************************************************************************************/
grlAPI Gb gbufUpdateAtArray(Gbuf * const buf, Gindex const index, Gcount const count,
   Gn1 const * const value)
{
   Gindex vindex;

   genter;

   greturnFalseIf(
      !buf       ||
      count <= 0 ||
      !value);

   forCount(vindex, count)
   {
      greturnFalseIf(!gbufUpdateAtV1(buf, index + vindex, *((Gv1 *) &value[vindex])));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gbufUpdateAtGuid
**************************************************************************************************/
grlAPI Gb gbufUpdateAtGuid(Gbuf * const buf, Gindex const index, Gguid const value)
{
   Gb result;

   genter;

   greturnFalseIf(!buf);

   result = gbufUpdateAtArray(buf, index, gsizeof(Gguid), value.b);

   greturn result;
}

/**************************************************************************************************
func: gbufUpdateAtV1
**************************************************************************************************/
grlAPI Gb gbufUpdateAtV1(Gbuf * const buf, Gindex const index, Gv1 const value)
{
   genter;

   greturnFalseIf(!buf);

   greturn gv1ArrayUpdateAt(&buf->buf, index, value);
}

/**************************************************************************************************
func: gbufUpdateAtV2
**************************************************************************************************/
grlAPI Gb gbufUpdateAtV2(Gbuf * const buf, Gindex const index, Gv2 const value)
{
   Gb  result;
   Gv2 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap2(&vtemp);

   result = gbufUpdateAtArray(buf, index, 2, vtemp.byte);

   greturn result;
}

/**************************************************************************************************
func: gbufUpdateAtV4
**************************************************************************************************/
grlAPI Gb gbufUpdateAtV4(Gbuf * const buf, Gindex const index, Gv4 const value)
{
   Gb  result;
   Gv4 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap4(&vtemp);

   result = gbufUpdateAtArray(buf, index, 4, vtemp.byte);

   greturn result;
}

/**************************************************************************************************
func: gbufUpdateAtV8
**************************************************************************************************/
grlAPI Gb gbufUpdateAtV8(Gbuf * const buf, Gindex const index, Gv8 const value)
{
   Gb  result;
   Gv8 vtemp;

   genter;

   greturnFalseIf(!buf);

   vtemp = value;
   gswap8(&vtemp);

   result = gbufUpdateAtArray(buf, index, 8, vtemp.byte);

   greturn result;
}
