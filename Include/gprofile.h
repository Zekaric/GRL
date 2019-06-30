/******************************************************************************

file:       gprofile
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
These are simple profile functions for profiling functions in a GRL program.
They are exclusivly called in genter and greturn* statements so you will
need to use those in functions you want profiled.  

The code only records how much total time a function uses during a run.  This
includes the time used in sub functions.

******************************************************************************/

#if !defined(GPROFILEH)
#define      GPROFILEH

/******************************************************************************
GPROFILE_IS_ON defined in grlconfig.h
******************************************************************************/
#if GPROFILE_IS_ON == 1

/******************************************************************************
Functions
******************************************************************************/
grlAPI void  gprofileCheckStack( Gindex index);

grlAPI Gtime gprofileEnter(      Gindex * const index, Char const * const file, Char const * const function);
grlAPI void  gprofileExit(       Gindex   const index, Gtime const startTime);

grlAPI void  gprofileReport(     void);

#else

#define gprofileCheckStack(I)       

#define gprofileEnter(I,FILE,FUNC)  0
#define gprofileExit(I,TIME)        

#define gprofileReport()            

#endif

#endif
