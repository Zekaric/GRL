/********************************************************************
file:       gtemp
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Temp memory handling.
********************************************************************/

/********************************************************************
include:
********************************************************************/
#include "precompiled.h"

/********************************************************************
function:
********************************************************************/
/********************************************************************
func: gtemp

Add a temporary memory item.
********************************************************************/
grlAPI Gp *gtemp(GtempScope * const scope, Gp * const mem, GrlDlocFunc const destroyF)
{
   GtempData *data;

   genter;

   debugHaltIf(!scope, "Missing gtempEnter() call.");

   greturnIf(
         !mem      ||
         !destroyF ||
         !scope,
      mem);

   // Failed to create memory will cause a leak.
   data = gmemClocType(GtempData);
   greturnIf(!data, mem);

   // Add to the list of temporaries in the current scope.
   GTYPE_SET(data, "GtempData");
   data->next  = scope->data;
   scope->data = data;

   // Set the record.
   data->data    = mem;
   data->destroy = destroyF;

   greturn mem;
}

/********************************************************************
func: gtempEnter_

Possibly need to resize the modified int list.
********************************************************************/
grlAPI GtempScope *gtempEnter_(void)
{
   GtempScope *scope;

   genter;

   scope = gmemClocType(GtempScope);
   greturnNullIf(!scope);

   GTYPE_SET(scope, "GtempScope");

   greturn scope;
}

/********************************************************************
func: gtempExit_

Dloc all the temporary memory.
********************************************************************/
grlAPI void gtempExit(GtempScope * const scope)
{
   GtempData  *data,
              *dataNext;

   genter;

   data = scope->data;
   loop
   {
      breakIf(!data);
      dataNext = data->next;

      data->destroy(data->data);
      gmemDloc(data);

      data = dataNext;
   }

   gmemDloc(scope);

   greturn;
}

/********************************************************************
func: gtempStart

Start up the gtemp routines.
********************************************************************/
Gb gtempStart(void)
{
   genter;

   greturn gbTRUE;
}

/********************************************************************
func: gtempStop

Stop the temp routines.
********************************************************************/
void gtempStop(void)
{
}
