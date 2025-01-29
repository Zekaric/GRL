/********************************************************************
file:       gtemp
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Temp memory handling.
********************************************************************/

#if !defined(GTEMPH)
#define      GTEMPH

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
/*lint -save -e960 -e961 -e9022 -e9024 -e9026 */
#define gtempGs(SCOPE, STR)  (Gs *) gtemp(SCOPE, (Gp *) (STR), (GrlDlocFunc) gsDlocFunc)
/*lint -restore */

grlAPI Gp         *gtemp(       GtempScope * const scope, Gp * const mem, GrlDlocFunc const destroyF);

grlAPI GtempScope *gtempEnter(  void);
grlAPI GtempScope *gtempEnter_( void);
grlAPI void        gtempExit(   GtempScope * const scope);

       Gb          gtempStart(  void);
       void        gtempStop(   void);

#define gtempEnter() (GtempScope *) gleakCloc(gtempEnter_(), gsizeof(GtempScope))

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
