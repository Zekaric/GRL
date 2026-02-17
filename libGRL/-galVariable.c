/********************************************************************

file:       galVariable
authour:    Robbert de Groot
copyright:  2009-2009, Robbert de Groot

description:
handles variable name.

********************************************************************/

/********************************************************************
include: 
********************************************************************/
#include "grl_pch.h"

/********************************************************************
local: 
variable:
********************************************************************/
static Gname   *_name = NULL;

/********************************************************************
global: 
function:
********************************************************************/
/********************************************************************
func: galVariableSet
********************************************************************/
GnameKey *galVariableSet(Gstr *value)
{
   GENTER;

   GRETURN gnameSet(_name, value, (void *) 1);
}

/********************************************************************
func: galVariableSetASCII
********************************************************************/
GnameKey *galVariableSetASCII(const char *value)
{
   GENTER;

   GRETURN gnameSetASCII(_name, value, (void *) 1);
}

/********************************************************************
func: galVariableStart
********************************************************************/
int galVariableStart(void)
{
   GENTER;

   _name = gnameCreate(ghashSize1K);
   GRETURN_IF(!_name, FALSE);

   GRETURN TRUE;
}

/********************************************************************
func: galVariableStop
********************************************************************/
void galVariableStop(void)
{
   GENTER;

   gnameDestroy(_name);
   _name = NULL;

   GRETURN;
}
