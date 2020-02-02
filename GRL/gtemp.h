/********************************************************************
file:       gtemp
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Temp memory handling.
********************************************************************/

#if !defined(GTEMPH)
#define      GTEMPH

/********************************************************************
type:
********************************************************************/
typedef struct GtempData  GtempData;
typedef struct GtempScope GtempScope;

struct GtempData
{
   GtempData      *next;
   Gp             *data;
   GrlDestroyFunc  destroy;
};

struct GtempScope
{
   GtempData      *data;
};

/********************************************************************
prototype:
********************************************************************/
/*lint -save -e960 -e961 -e9022 -e9024 -e9026 */
#define gtempGs(SCOPE, STR)  (Gs *) gtemp(SCOPE, (Gp *) (STR), (GrlDestroyFunc) gsDestroyFunc)
/*lint -restore */

grlAPI Gp         *gtemp(       GtempScope * const scope, Gp * const mem, GrlDestroyFunc const destroyF);

grlAPI GtempScope *gtempEnter(  void);
grlAPI GtempScope *gtempEnter_( void);
grlAPI void        gtempExit(   GtempScope * const scope);

       Gb          gtempStart(  void);
       void        gtempStop(   void);

#define gtempEnter() (GtempScope *) gleakCreate(gtempEnter_(), gsizeof(GtempScope))

#endif
