/********************************************************************

file:       galCommand
authour:    Robbert de Groot
copyright:  2009-2009, Robbert de Groot

description:
handles command structure.

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
func: galCommandCreateContent
********************************************************************/
int galCommandCreateContent(GalCommand *command)
{
   GENTER;

   gmemClear(command, sizeof(GalCommand));

   command->paramList = galParamListCreate();
   GRETURN_IF(!command->paramList, FALSE);

   GRETURN TRUE;
}

/********************************************************************
func: galCommandDestroyContent
********************************************************************/
int galCommandDestroyContent(GalCommand *command)
{
   GENTER;

   galParamListDestroy(command->paramList);

   gmemClear(command, sizeof(GalCommand));

   GRETURN TRUE;
}

/********************************************************************
func: galCommandGetFunctionName
********************************************************************/
GnameKey *galCommandGetFunctionName(GalCommand *command)
{
   GENTER;

   GRETURN command->functionName;
}

/********************************************************************
func: galCommandGetParamList
********************************************************************/
GalParamList *galCommandGetParamList(GalCommand *command)
{
   GENTER;

   GRETURN command->paramList;
}

/********************************************************************
func: galCommandSetFunctionName
********************************************************************/
int galCommandSetFunctionName(GalCommand *command, GnameKey *functionName)
{
   GENTER;

   command->functionName = functionName;

   GRETURN TRUE;
}
