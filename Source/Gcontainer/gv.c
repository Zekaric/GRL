/******************************************************************************

file:          gv
author:        Robbert de Groot
company:       
copyright:     2015, Robbert de Groot

description:

******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

/******************************************************************************
local:
constant:
******************************************************************************/

/******************************************************************************
type:
******************************************************************************/

/******************************************************************************
variable:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gpCompare
******************************************************************************/
grlAPI Gcompare gpCompare(Gp const * const valueA, Gp const * const valueB)
{
   genter;

   greturnIf(valueA < valueB, gcompareLESS_THAN);
   greturnIf(valueA > valueB, gcompareGREATER_THAN);
   greturn                    gcompareEQUAL;
}

/******************************************************************************
func: gvCompare
******************************************************************************/
grlAPI Gcompare gvCompareI(Gv const * const valueA, Gv const * const valueB)
{
   genter;

   greturnIf(valueA->value.i < valueB->value.i, gcompareLESS_THAN);
   greturnIf(valueA->value.i > valueB->value.i, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

grlAPI Gcompare gvCompareN(Gv const * const valueA, Gv const * const valueB)
{
   genter;

   greturnIf(valueA->value.n < valueB->value.n, gcompareLESS_THAN);
   greturnIf(valueA->value.n > valueB->value.n, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

grlAPI Gcompare gvCompareP(Gv const * const valueA, Gv const * const valueB)
{
   genter;

   greturnIf((Gnp) valueA->value.p < (Gnp) valueB->value.p, gcompareLESS_THAN);    //lint !e923
   greturnIf((Gnp) valueA->value.p > (Gnp) valueB->value.p, gcompareGREATER_THAN); //lint !e923
   greturn                                                  gcompareEQUAL;
}

grlAPI Gcompare gvCompareR(Gv const * const valueA, Gv const * const valueB)
{
   genter;

   greturnIf(valueA->value.r < valueB->value.r, gcompareLESS_THAN);
   greturnIf(valueA->value.r > valueB->value.r, gcompareGREATER_THAN);
   greturn                                      gcompareEQUAL;
}

/******************************************************************************
func: gvCreate
******************************************************************************/
grlAPI Gv *gvCreate(void)
{
   Gv *v;

   genter;

   v = gmemCreateType(Gv);
   greturnNullIf(!v);

   if (!gvCreateContent(v))
   {
      gmemDestroy(v);
   }

   greturn v;
}

/******************************************************************************
func: gvCreateContent
******************************************************************************/
grlAPI Gb gvCreateContent(Gv * const v)
{
   genter;

   greturnFalseIf(!v);

   gmemClearType(v, Gv);

   greturn gbTRUE;
}

/******************************************************************************
func: gvDestroy
******************************************************************************/
grlAPI void gvDestroy(Gv * const v)
{
   genter;

   gvDestroyContent(v);
   gmemDestroy(v);

   greturn;
}

/******************************************************************************
func: gvDestroyContent
******************************************************************************/
grlAPI void gvDestroyContent(Gv * const v)
{
   genter;

   gmemClearType(v, Gv);

   greturn;
}

/******************************************************************************
func: gvFrom
******************************************************************************/
grlAPI Gv gvFromI(Gip const value)
{
   Gv vtemp;

   vtemp.type     = gvTypeI;
   vtemp.value.i  = value;

   return vtemp;
}

grlAPI Gv gvFromN(Gnp const value)
{
   Gv vtemp;

   vtemp.type     = gvTypeN;
   vtemp.value.n  = value;

   return vtemp;
}

grlAPI Gv gvFromP(Gp * const value)
{
   Gv vtemp;

   vtemp.type     = gvTypeP;
   vtemp.value.p  = value;

   return vtemp;
}

grlAPI Gv gvFromR(Grp const value)
{
   Gv vtemp;

   vtemp.type     = gvTypeR;
   vtemp.value.r  = value;

   return vtemp;
}

grlAPI Gv gvFromS(Gs * const value)
{
   Gv vtemp;

   vtemp.type     = gvTypeS;
   vtemp.value.s  = value;

   return vtemp;
}

/******************************************************************************
func: gvGet
******************************************************************************/
grlAPI Gip gvGetI(Gv const * const v)
{
   genter;

   greturn0If(!v);

   greturnIf(v->type == gvTypeI,       v->value.i);
   greturnIf(v->type == gvTypeN, (Gip) v->value.n);
   greturnIf(v->type == gvTypeR, (Gip) v->value.r);
//RDG   greturnIf(v->type == gvTypeS, (Gip) gsGetI(v->value.s));

   greturn 0;
}

grlAPI Gnp gvGetN(Gv const * const v)
{
   genter;

   greturn0If(!v);

   greturnIf(v->type == gvTypeN,       v->value.n);
   greturnIf(v->type == gvTypeI, (Gnp) v->value.i);
   greturnIf(v->type == gvTypeR, (Gnp) v->value.r);
//RDG   greturnIf(v->type == gvTypeS, (Gnp) gsGetN(v->value.s));

   greturn 0;
}

grlAPI Gp *gvGetP(Gv const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnIf(
         v->type == gvTypeP ||
         v->type == gvTypeS,
      v->value.p);

   greturn 0;
}

grlAPI Grp gvGetR(Gv const * const v)
{
   genter;

   greturn0If(!v);

   greturnIf(v->type == gvTypeR,       v->value.r);
   greturnIf(v->type == gvTypeI, (Grp) v->value.i);
   greturnIf(v->type == gvTypeN, (Grp) v->value.n);
//RDG   greturnIf(v->type == gvTypeS, (Grp) gsGetR(v->value.s));

   greturn 0;
}

grlAPI Gs *gvGetS(Gv const * const v)
{
   genter;

   greturnNullIf(!v);

   greturnIf(v->type == gvTypeS, v->value.s);

   greturn NULL;
}

/******************************************************************************
func: gvHash
******************************************************************************/
grlAPI GhashN gvHash(Gv const * const value)
{
   genter;

   greturnIf(
         value->type == gvTypeP ||
         value->type == gvTypeS,
      (GhashN) (value->value.n / 4));

   greturn (GhashN) value->value.n;
}

/******************************************************************************
func: gvHashS
******************************************************************************/
grlAPI GhashN gvHashS(Gv const * const value)
{
   GhashN result = 0;

   genter;

   value;

//RDG   result = gsHash((Gs * ) value->value.s);

   greturn result;
}

/******************************************************************************
func: gvSet
******************************************************************************/
grlAPI Gb gvSetI(Gv * const v, Gip const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvTypeI;
   v->value.i = value;

   greturn gbTRUE;
}

grlAPI Gb gvSetN(Gv * const v, Gnp const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvTypeN;
   v->value.n = value;

   greturn gbTRUE;
}

grlAPI Gb gvSetP(Gv * const v, Gp * const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvTypeP;
   v->value.p = value;

   greturn gbTRUE;
}

grlAPI Gb gvSetR(Gv * const v, Grp const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvTypeR;
   v->value.r = value;

   greturn gbTRUE;
}

grlAPI Gb gvSetS(Gv * const v, Gs * const value)
{
   genter;

   greturnFalseIf(!v);

   v->type    = gvTypeS;
   v->value.s = value;

   greturn gbTRUE;
}
