/**************************************************************************************************

file:          gvData
author:        Robbert de Groot
company:       
copyright:     2015, Robbert de Groot

description:

**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

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

   greturnIf(valueA < valueB, gcompareLESS_THAN);
   greturnIf(valueA > valueB, gcompareGREATER_THAN);
   greturn                    gcompareEQUAL;
}

/**************************************************************************************************
func: gvDataCompare
**************************************************************************************************/
grlAPI Gcompare gvDataCompareI(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnIf(valueA->value.i < valueB->value.i, gcompareLESS_THAN);
   greturnIf(valueA->value.i > valueB->value.i, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareN(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnIf(valueA->value.n < valueB->value.n, gcompareLESS_THAN);
   greturnIf(valueA->value.n > valueB->value.n, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareP(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnIf((Gnp) valueA->value.p < (Gnp) valueB->value.p, gcompareLESS_THAN);    //lint !e923
   greturnIf((Gnp) valueA->value.p > (Gnp) valueB->value.p, gcompareGREATER_THAN); //lint !e923
   greturn                                                  gcompareEQUAL;
}

grlAPI Gcompare gvDataCompareR(GvData const * const valueA, GvData const * const valueB)
{
   genter;

   greturnIf(valueA->value.r < valueB->value.r, gcompareLESS_THAN);
   greturnIf(valueA->value.r > valueB->value.r, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

/**************************************************************************************************
func: gvDataCloc
**************************************************************************************************/
grlAPI GvData *gvDataCloc(void)
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

   GTYPE_SET(v, "Gv");

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

   greturnIf(v->type == gvDataTypeI,      v->value.i);
   greturnIf(v->type == gvDataTypeN, (Gi) v->value.n);
   greturnIf(v->type == gvDataTypeR, (Gi) v->value.r);
//RDG   greturnIf(v->type == gvDataTypeS, (Gi) gsGetI(v->value.s));

   greturn 0;
}

grlAPI Gn gvDataGetN(GvData const * const v)
{
   genter;

   greturn0If(!v);

   greturnIf(v->type == gvDataTypeN,      v->value.n);
   greturnIf(v->type == gvDataTypeI, (Gn) v->value.i);
   greturnIf(v->type == gvDataTypeR, (Gn) v->value.r);
//RDG   greturnIf(v->type == gvDataTypeS, (Gn) gsGetN(v->value.s));

   greturn 0;
}

grlAPI Gp *gvDataGetP(GvData const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnIf(
         v->type == gvDataTypeP ||
         v->type == gvDataTypeS,
      v->value.p);

   greturn 0;
}

grlAPI Gr gvDataGetR(GvData const * const v)
{
   genter;

   greturn0If(!v);

   greturnIf(v->type == gvDataTypeR,      v->value.r);
   greturnIf(v->type == gvDataTypeI, (Gr) v->value.i);
   greturnIf(v->type == gvDataTypeN, (Gr) v->value.n);
//RDG   greturnIf(v->type == gvDataTypeS, (Gr) gsGetR(v->value.s));

   greturn 0;
}

grlAPI Gs *gvDataGetS(GvData const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnIf(v->type == gvDataTypeS, v->value.s);

   greturn NULL;
}

/**************************************************************************************************
func: gvDataHash
**************************************************************************************************/
grlAPI GhashN gvDataHash(GvData const * const value)
{
   genter;

   greturnIf(
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
