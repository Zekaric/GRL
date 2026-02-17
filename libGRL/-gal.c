/********************************************************************

file:       gal
authour:    Robbert de Groot
copyright:  2005-2009, Robbert de Groot

description:
This is the entry point for running a gal script.

********************************************************************/

/********************************************************************
include:
********************************************************************/
#include "grl_pch.h"

/********************************************************************
local:
variable:
********************************************************************/
static int _started = FALSE;

/********************************************************************
global:
function:
********************************************************************/
/********************************************************************
func: galCreate

Create a gal runtime sandbox.

param:
path
   Gpath *
   in
   The path of the source repository.

return:
Gal *
********************************************************************/
GRLFUNC Gal *galCreate_(Gpath *path) 
{
   GENTER;
   Gal *gal;

   gal = gmemCreate(sizeof(Gal));
   GRETURN_IF(!gal, NULL);

   gal->galRepository = gpathCreateFrom(path);
   gal->scopeList     = galScopeListCreate();
   gal->variableList  = gnameCreate(ghashSize100);
   if (!gal->galRepository ||
       !gal->scopeList     ||
       !gal->variableList)
   {
      galDestroy(gal);
      GRETURN NULL;
   }

   GRETURN gal;
}

/********************************************************************
func: galDestroy

Clean up.

param:
gal
   Gal *
   in
   The gal.
********************************************************************/
GRLFUNC void galDestroy(Gal *gal) 
{
   GENTER;
   Garray *vlist;

   gpathDestroy(gal->galRepository);

   galScopeListDestroy(gal->scopeList);

   vlist = ghashCreateKeyArray(gal->variableList);
   garrayForEachCell(vlist, gmemDestroy);
   garrayDestroy(    vlist);

   gnameDestroy(gal->variableList);

   gmemDestroy(gal);
   GRETURN;
}

/********************************************************************
func: galIsStarted

Are the Gal routines started.
********************************************************************/
GRLFUNC int galIsStarted(void)
{
   GENTER;
   GRETURN(_started);
}

/********************************************************************
func: galRun

Run the script file.

param:
gal
   Gal *
   in
   The environment

instructionList, returnData, paramList
   Garray *, Gdata *, Garray *
   in, in, in
   The list of Gstr * that represent the code.
   The GRETURN data pointer.  Can be NULL.
   The parameter list.  An array of Gdata *.

return:
int
********************************************************************/
GRLFUNC int galRun(Gal *gal, Gstr *functionName, Gdata *returnData, GalParamList *paramList) 
{
   GENTER;

   Gpath       *path;
   GalFunction *func;
   GalScope    *scope;

   // Move to the right directory.
   path = gdirGetWorking();
   gdirSetWorking(gal->galRepository);

   func = galFunctionGet(functionName);
   RETURN_IF(!func, FALSE);

   // Read in the file.
   BBLK
   {
      scope = galScopeListPush(gal->scopeList);

      galFunctionRun(gal, scope, func, returnData, paramList);

      galScopeListPop(gal->scopeList);
   }
   ENDBBLK

   // Clean up.
   gdirSetWorking(path);
   gpathDestroy(path);

   GRETURN(TRUE);
}

/********************************************************************
func: galStart

Start the gal routines.

return:
int
********************************************************************/
GRLFUNC int galStart(void) 
{
   GENTER;

   GRETURN_IF(_started, TRUE);

   GRETURN_IF(!gdataIsStarted(), FALSE);

   galVariableStart();
   galFunctionStart();

   _started = TRUE;

   GRETURN(TRUE);
}

/********************************************************************
func: galStop

Clean up.
********************************************************************/
GRLFUNC void galStop(void) 
{
   GENTER;
   galFunctionStop();
   galVariableStop();

   _started = FALSE;
   GRETURN;
}
