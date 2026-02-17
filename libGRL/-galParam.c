/********************************************************************

file:       galParam
authour:    Robbert de Groot
copyright:  2009-2009, Robbert de Groot

description:
handles param structure.

********************************************************************/

/********************************************************************
include: 
********************************************************************/
#include "grl_pch.h"

/********************************************************************
global: 
function:
********************************************************************/
/********************************************************************
func: galParamCreateContent
********************************************************************/
int galParamCreateContent(GalParam *param)
{
   GENTER;

   gmemClear(param, sizeof(GalParam));

   GRETURN TRUE;
}

/********************************************************************
func: galParamDestroyContent
********************************************************************/
int galParamDestroyContent(GalParam *param)
{
   GENTER;

   gmemClear(param, sizeof(GalParam));

   GRETURN TRUE;
}

/********************************************************************
func: galParamGetCommandList
********************************************************************/
GalCommandList *galParamGetCommandList(GalParam *param)
{
   GENTER;

   GRETURN_IF(
         param->type == galParamTypeDATA ||
         param->type == galParamTypeVARIABLE,
      NULL);

   GRETURN param->data.commandList;
}

/********************************************************************
func: galParamGetData
********************************************************************/
Gdata *galParamGetData(GalParam *param)
{
   GENTER;

   GRETURN_IF(param->type != galParamTypeDATA, NULL);

   GRETURN &param->data.data;
}

/********************************************************************
func: galParamGetType
********************************************************************/
GalParamType galParamGetType(GalParam *param)
{
   GENTER;

   GRETURN param->type;
}

/********************************************************************
func: galParamGetVariableName
********************************************************************/
GnameKey *galParamGetVariableName(GalParam *param)
{
   GENTER;

   GRETURN_IF(param->type != galParamTypeVARIABLE, NULL);

   GRETURN param->data.variable;
}

/********************************************************************
func: galParamSetData
********************************************************************/
int galParamSetData(GalParam *param, Gdata *data)
{
   GENTER;

   gdataSet(&param->data.data, data);

   GRETURN TRUE;
}

/********************************************************************
func: galParamSetType
********************************************************************/
int galParamSetType(GalParam *param, GalParamType type)
{
   GENTER;

   param->type = type;

   switch(param->type) 
   {
   case galParamTypeDATA:
      break;

   case galParamTypeVARIABLE:
      param->data.variable = NULL;
      break;

   case galParamTypeEXPRESSION:
   case galParamTypeIF_LIST:
   case galParamTypePARAMETER_LIST:
   case galParamTypeSCRIPT:
   case galParamTypeVARIABLE_LIST:
   case galParamTypeVARIABLE_NAME_LIST:
      param->data.commandList = galCommandListCreate();
      break;
   }

   GRETURN TRUE;
}

/********************************************************************
func: galParamSetVariableName
********************************************************************/
int galParamSetVariableName(GalParam *param, Gstr *value)
{
   GENTER;

   GRETURN_IF(param->type != galParamTypeVARIABLE, FALSE);

   param->data.variable = galVariableSet(value);

   GRETURN TRUE;
}
