/**************************************************************************************************
file:       gvData
author:     Robbert de Groot
copyright:  2015, Robbert de Groot

description:
A data type that holds all types of data.

What's the difference between this and Gv?
Gv is more internal.  This type is intended to be cloc'd all the time.  So you will be dealing with
a pointer to this type always while Gv you will be dealing with it raw.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
func: gpCompare
**************************************************************************************************/
grlAPI Gcompare gpCompare(Gp const * const valueA, Gp const * const valueB)
{
   genter;

   greturnValIf(valueA < valueB, gcompareLESS_THAN);
   greturnValIf(valueA > valueB, gcompareGREATER_THAN);
   greturn                       gcompareEQUAL;
}

/**************************************************************************************************
func: gvDataCompare
**************************************************************************************************/
grlAPI Gcompare gvDataCompareI(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnValIf(valueA->value.i < valueB->value.i, gcompareLESS_THAN);
   greturnValIf(valueA->value.i > valueB->value.i, gcompareGREATER_THAN);
   greturn                                         gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareN(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnValIf(valueA->value.n < valueB->value.n, gcompareLESS_THAN);
   greturnValIf(valueA->value.n > valueB->value.n, gcompareGREATER_THAN);
   greturn                                         gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareP(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnValIf((Gnp) valueA->value.p < (Gnp) valueB->value.p, gcompareLESS_THAN);    
   greturnValIf((Gnp) valueA->value.p > (Gnp) valueB->value.p, gcompareGREATER_THAN); 
   greturn                                                     gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareR(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnValIf(valueA->value.r < valueB->value.r, gcompareLESS_THAN);
   greturnValIf(valueA->value.r > valueB->value.r, gcompareGREATER_THAN);
   greturn                                         gcompareEQUAL;
}

/**************************************************************************************************
func: gvDataCloc
**************************************************************************************************/
grlAPI GvData *gvDataCloc_(void)
{
   GvData *v;

   genter;

   v = gmemClocType(GvData);
   greturnNullIf(!v);

   if (!gvDataClocContent(v))
   {
      gmemDloc(v);
   }

   greturn v;
}

/**************************************************************************************************
func: gvDataClocContent
**************************************************************************************************/
grlAPI Gb gvDataClocContent(GvData * const v)
{
   genter;

   greturnFalseIf(!v);

   gmemClearType(v, GvData);

   GTYPE_SET(v, "GvData");

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvDataDloc
**************************************************************************************************/
grlAPI void gvDataDloc(GvData * const v)
{
   genter;

   gvDataDlocContent(v);
   gmemDloc(v);

   greturn;
}

/**************************************************************************************************
func: gvDataDlocContent
**************************************************************************************************/
grlAPI void gvDataDlocContent(GvData * const v)
{
   genter;

   gmemClearType(v, GvData);

   greturn;
}

/**************************************************************************************************
func: gvDataFrom
**************************************************************************************************/
grlAPI GvData gvDataFromI(Gi const value)
{
   GvData vtemp;

   vtemp.type     = gvDataTypeI;
   vtemp.value.i  = value;

   return vtemp;
}

grlAPI GvData gvDataFromN(Gn const value)
{
   GvData vtemp;

   vtemp.type     = gvDataTypeN;
   vtemp.value.n  = value;

   return vtemp;
}

grlAPI GvData gvDataFromP(Gp * const value)
{
   GvData vtemp;

   vtemp.type     = gvDataTypeP;
   vtemp.value.p  = value;

   return vtemp;
}

grlAPI GvData gvDataFromR(Gr const value)
{
   GvData vtemp;

   vtemp.type     = gvDataTypeR;
   vtemp.value.r  = value;

   return vtemp;
}

grlAPI GvData gvDataFromS(Gs * const value)
{
   GvData vtemp;

   vtemp.type     = gvDataTypeS;
   vtemp.value.s  = value;

   return vtemp;
}

/**************************************************************************************************
func: gvDataGet
**************************************************************************************************/
grlAPI Gi gvDataGetI(GvData const * const v)
{
   genter;

   greturn0If(!v);

   greturnValIf(v->type == gvDataTypeI,      v->value.i);
   greturnValIf(v->type == gvDataTypeN, (Gi) v->value.n);
   greturnValIf(v->type == gvDataTypeR, (Gi) v->value.r);
//RDG   greturnValIf(v->type == gvDataTypeS, (Gi) gsGetI(v->value.s));

   greturn 0;
}

grlAPI Gn gvDataGetN(GvData const * const v)
{
   genter;

   greturn0If(!v);

   greturnValIf(v->type == gvDataTypeN,      v->value.n);
   greturnValIf(v->type == gvDataTypeI, (Gn) v->value.i);
   greturnValIf(v->type == gvDataTypeR, (Gn) v->value.r);
//RDG   greturnValIf(v->type == gvDataTypeS, (Gn) gsGetN(v->value.s));

   greturn 0;
}

grlAPI Gp *gvDataGetP(GvData const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnValIf(
         v->type == gvDataTypeP ||
         v->type == gvDataTypeS,
      v->value.p);

   greturn 0;
}

grlAPI Gr gvDataGetR(GvData const * const v)
{
   genter;

   greturn0If(!v);

   greturnValIf(v->type == gvDataTypeR,      v->value.r);
   greturnValIf(v->type == gvDataTypeI, (Gr) v->value.i);
   greturnValIf(v->type == gvDataTypeN, (Gr) v->value.n);
//RDG   greturnValIf(v->type == gvDataTypeS, (Gr) gsGetR(v->value.s));

   greturn 0;
}

grlAPI Gs *gvDataGetS(GvData const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnValIf(v->type == gvDataTypeS, v->value.s);

   greturn NULL;
}

/**************************************************************************************************
func: gvDataHash
**************************************************************************************************/
grlAPI GhashN gvDataHash(GvData const * const value)
{
   genter;

   greturnValIf(
         value->type == gvDataTypeP ||
         value->type == gvDataTypeS,
      (GhashN) (value->value.n / 4));

   greturn (GhashN) value->value.n;
}

/**************************************************************************************************
func: gvDataHashS
**************************************************************************************************/
grlAPI GhashN gvDataHashS(GvData const * const value)
{
   GhashN result = 0;

   genter;

   value;

   result = gsHash((Gs * ) value->value.s);

   greturn result;
}

/**************************************************************************************************
func: gvDataSet
**************************************************************************************************/
grlAPI Gb gvDataSetI(GvData * const v, Gi const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvDataTypeI;
   v->value.i = value;

   greturn gbTRUE;
}

grlAPI Gb gvDataSetN(GvData * const v, Gn const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvDataTypeN;
   v->value.n = value;

   greturn gbTRUE;
}

grlAPI Gb gvDataSetP(GvData * const v, Gp * const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvDataTypeP;
   v->value.p = value;

   greturn gbTRUE;
}

grlAPI Gb gvDataSetR(GvData * const v, Gr const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvDataTypeR;
   v->value.r = value;

   greturn gbTRUE;
}

grlAPI Gb gvDataSetS(GvData * const v, Gs * const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvDataTypeS;
   v->value.s = value;

   greturn gbTRUE;
}
