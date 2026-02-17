/********************************************************************

file:       galMod_Sys
authour:    Robbert de Groot
copyright:  2005-2009, Robbert de Groot

description:
System module.

********************************************************************/

/********************************************************************
include
********************************************************************/
#include "grl_pch.h"

/********************************************************************
global 
function
********************************************************************/
/********************************************************************
func: galMod_Sys

Process a system call.
********************************************************************/
GRLFUNC void galMod_Sys(Gal *gal, GalScope *scope, Garray *line) 
{
   GENTER;
   Gn4    a;
   Gpath *path;
   Gdata *data;
   Gstr  *str,
         *function,
         *stemp;

   scope;
   gal;
   data = (Gdata *) garrayGet(line, 2);
   str  = gdataCreateGstr(data);
   path = gpathCreateFromGstr(str);
   gstrDestroy(str);

   str = gpathGet(path, gpathTypeFOLDER);
   gpathDestroy(path);

   function = gstrCreateFromASCII("print");
   if (!gstrCompare(function, str)) 
   { 
      const Gchar2 *wtemp;

      for (a = 3; a < garrayGetCount(line); a++) 
      {         
         data = (Gdata *) garrayGet(line, a);
         if (!data) 
         {
            continue;
         }

         stemp = gdataCreateGstr(data);
         wtemp = gstrGetUTF16(stemp);
         wprintf(L"%s", wtemp);
         gstrDestroy(stemp);
      }
   }
   gstrDestroy(function);

   function = gstrCreateFromASCII("printNewLine");
   if (!gstrCompare(function, str)) 
   { 
      wprintf(L"\n");
   }
   gstrDestroy(function);

   gstrDestroy(str);
   GRETURN;
}
