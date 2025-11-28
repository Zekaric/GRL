/**************************************************************************************************
file:       GsKey
author:     Robbert de Groot
copyright:  2015, Robbert de Groot

description:
Global name table.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
// This value may need adjustment
#define STR_TABLE_COUNT ghashSize10K

/**************************************************************************************************
variable:
**************************************************************************************************/
static Gb          _isStarted     = gbFALSE;
// The global name table.
static GsKeyTable *_strTable      = NULL;

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gsKeyIntern
**************************************************************************************************/
grlAPI GsKey const *gsKeyIntern(Gs const * const value)
{
   return gsKeyTableIntern(_strTable, value);
}

/**************************************************************************************************
func: gsKeyInternA
**************************************************************************************************/
grlAPI GsKey const *gsKeyInternA(Char const * const value)
{
   return gsKeyTableInternA(_strTable, value);
}

/**************************************************************************************************
func: gsKeyInternU2
**************************************************************************************************/
grlAPI GsKey const *gsKeyInternU2(Gc2 const * const value)
{
   return gsKeyTableInternU2(_strTable, value);
}

/**************************************************************************************************
func: gsKeyTableIntern
**************************************************************************************************/
grlAPI GsKey const *gsKeyTableIntern(GsKeyTable * const gsKeyTable, Gs const * const value)
{
   Gs const * stemp;

   genter;

   // Does the string already exist in the table?
   stemp = gsKeyTableFind(gsKeyTable, value);

   // No it doesn't, add the string.
   if (!stemp)
   {
      // Clone the string.
      stemp = gsClocFrom(value);
      greturnNullIf(!stemp);

      // Add it to the table.
      if (!gsKeyTableAdd(_strTable, stemp))
      {
         gsDloc((Gs *) stemp);
         greturn NULL;
      }
   }

   // Return the string.
   greturn (GsKey *) stemp;
}

/**************************************************************************************************
func: gsKeyTableInternA
**************************************************************************************************/
grlAPI GsKey const *gsKeyTableInternA(GsKeyTable * const gsKeyTable, Char const * const value)
{
   Gs          *stemp;
   GsKey const *result;

   genter;

   stemp  = gsClocFromA(value);
   result = gsKeyTableIntern(gsKeyTable, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
func: gsKeyTableInternU2
**************************************************************************************************/
grlAPI GsKey const *gsKeyTableInternU2(GsKeyTable * const gsKeyTable, Gc2 const * const value)
{
   Gs          *stemp;
   GsKey const *result;

   genter;

   stemp  = gsClocFromU2(value);
   result = gsKeyTableIntern(gsKeyTable, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
func: gsKeyStart
**************************************************************************************************/
grlAPI Gb gsKeyStart(void)
{
   genter;

   greturnTrueIf(_isStarted);

   _strTable = gsKeyTableCloc(STR_TABLE_COUNT);
   greturnFalseIf(!_strTable);

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsKeyStop
**************************************************************************************************/
grlAPI void gsKeyStop(void)
{
   genter;

   greturnIf(!_isStarted);

   gsKeyTableForEach(_strTable, (GrlForEachFunc) gsDlocFunc);
   gsKeyTableDloc(   _strTable);
   _strTable  = NULL;

   _isStarted = gbFALSE;

   greturn;
}
