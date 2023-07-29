/******************************************************************************
file:         Gbuf
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
func: gbufAddEndArray
******************************************************************************/
grlAPI Gb gbufAddEndArray(Gbuf * const buf, Gcount const count, Gn1 const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   forCount(index, count)
   {
      result = gn1ArrayAddEnd(buf, &value[index]);
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gbufAddEndA
******************************************************************************/
grlAPI Gb gbufAddEndA(Gbuf * const buf, Char const * const value)
{
   Gindex index;
   Gb     result;

   genter;

   loopCount(index)
   {
      result = gn1ArrayAddEnd(buf, &value[index]);
      breakIf(value[index] == 0);
   }

   greturn result;
}

/******************************************************************************
func: gbufAddEndGuid
******************************************************************************/
grlAPI Gb gbufAddEndGuid(Gbuf * const buf, Gguid const value)
{
   Gb result;

   genter;

   // I don't know if byte swapping needs to happen here.  Something to test.
   result = gbufAddEndArray(buf, sizeof(Gguid), value.b);

   greturn result;
}

/******************************************************************************
func: gbufAddEndI2
******************************************************************************/
grlAPI Gb gbufAddEndI2(Gbuf * const buf, Gi2 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED
   gswap2(&value);
#endif
   
   result = gbufAddEndArray(buf, 2, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndI4
******************************************************************************/
grlAPI Gb gbufAddEndI4(Gbuf * const buf, Gi4 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif
   
   result = gbufAddEndArray(buf, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndI8
******************************************************************************/
grlAPI Gb gbufAddEndI8(Gbuf * const buf, Gi8 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif
   
   result = gbufAddEndArray(buf, 8, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndId
******************************************************************************/
grlAPI Gb gbufAddEndId(Gbuf * const buf, Gid const value)
{
   Char c[4];

   Gb result;

   genter;

   gidGetC(value, c);
   result = gbufAddEndArray(buf, 4, (Gn1 *) c);

   greturn result;
}

/******************************************************************************
func: gbufAddEndN2
******************************************************************************/
grlAPI Gb gbufAddEndN2(Gbuf * const buf, Gn2 value)
{
   Gb result;

   genter;
   
#if grlSWAP_NEEDED == 1
   gswap2(&value);
#endif
   
   result = gbufAddEndArray(buf, 2, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndN4
******************************************************************************/
grlAPI Gb gbufAddEndN4(Gbuf * const buf, Gn4 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif
   
   result = gbufAddEndArray(buf, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndN8
******************************************************************************/
grlAPI Gb gbufAddEndN8(Gbuf * const buf, Gn8 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif
   
   result = gbufAddEndArray(buf, 8, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndR4
******************************************************************************/
grlAPI Gb gbufAddEndR4(Gbuf * const buf, Gr4 value)
{
   Gb result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif
   
   result = gbufAddEndArray(buf, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndR8
******************************************************************************/
grlAPI Gb gbufAddEndR8(Gbuf * const buf, Gr8 value)
{
   Gb result;

   genter;
   
#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif

   result = gbufAddEndArray(buf, 8, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gbufAddEndS
******************************************************************************/
grlAPI Gb gbufAddEndS(Gbuf * const buf, Gs const * const value)
{
   Gb     result;
   Gc1   *u1;

   genter;
   
   u1 = gsCreateU1(value);
   greturnFalseIf(!u1);
   result = gbufAddEndA(buf, (Char *) u1);
   gmemDestroy(u1);

   greturn result;
}
