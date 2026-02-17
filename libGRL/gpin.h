/******************************************************************************
file:       gpin
author:     Robbert de Groot
copyright:  2010-2010, Robbert de Groot

description:
GRL PlugIN.  A very simple plugin manager.
******************************************************************************/

#if !defined(GPINH)
#define      GPINH

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gb       gpinAdd(      Gc2 const * const name, Gp * const pinStruct);
grlAPI Gb       gpinAddModule(Gc2 const * const pinFileName);

grlAPI Gp      *gpinGet(      Gc2 const * const name);

grlAPI GpinPin *gpinStart(    void);
grlAPI void     gpinStop(     void);

#endif
