/********************************************************************
file:       gtemp
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Temp memory handling.
********************************************************************/

#pragma once

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/********************************************************************
type:
********************************************************************/
typedef struct GtempData  GtempData;
typedef struct GtempScope GtempScope;

struct GtempData
{
   GTYPE_VAR

   GtempData      *next;
   Gp             *data;
   GrlDlocFunc     destroy;
};

struct GtempScope
{
   GTYPE_VAR

   GtempData      *data;
};

/********************************************************************
prototype:
********************************************************************/
#define gtempGs(SCOPE, STR)  (Gs *) gtemp(SCOPE, (Gp *) (STR), (GrlDlocFunc) gsDloc)

grlAPI Gp         *gtemp(       GtempScope * const scope, Gp * const mem, GrlDlocFunc const destroyF);

grlAPI GtempScope *gtempEnter_( void);
grlAPI void        gtempExit(   GtempScope * const scope);

       Gb          gtempStart(  void);
       void        gtempStop(   void);

#define gtempEnter()    gleakClocType(gtempEnter_(), GtempScope)

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
