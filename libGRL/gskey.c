/**************************************************************************************************
file:       GsKey
author:     Robbert de Groot
copyright:  2015, Robbert de Groot

description:
Global name table.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2015, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

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
static GsKeyTable *_skeyTable     = NULL;

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gsKeyIntern
**************************************************************************************************/
grlAPI GsKey const *gsKeyIntern(Gs const * const value)
{
   return gsKeyTableIntern(_skeyTable, value);
}

/**************************************************************************************************
func: gsKeyTableIntern
**************************************************************************************************/
grlAPI GsKey const *gsKeyTableIntern(GsKeyTable * const gsKeyTable, Gs const * const value)
{
   GsKey const *stemp;

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
      if (!gsKeyTableAdd(_skeyTable, stemp))
      {
         gsDloc((Gs *) stemp);
         greturn NULL;
      }
   }

   // Return the string.
   greturn (GsKey *) stemp;
}

/**************************************************************************************************
func: gsKeyStart
**************************************************************************************************/
grlAPI Gb gsKeyStart(void)
{
   genter;

   greturnTrueIf(_isStarted);

   _skeyTable = gsKeyTableCloc(STR_TABLE_COUNT);
   greturnFalseIf(!_skeyTable);

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

   gsKeyTableForEach(_skeyTable, (GrlForEachFunc) gsDlocContainer);
   gsKeyTableDloc(   _skeyTable);
   _skeyTable  = NULL;

   _isStarted = gbFALSE;

   greturn;
}
