/**************************************************************************************************
file:       gjsonSet
author:     Robbert de Groot
copyright:  2021, Robbert de Groot

description:
Set functions local to the library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2021, Robbert de Groot

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
#include "giojsonLocal.h"

/**************************************************************************************************
global:
function
**************************************************************************************************/
/**************************************************************************************************
func: _JsonSetBuffer
**************************************************************************************************/
Gb _JsonSetBuffer(GioJson const * const json, Gcount const bufCount, Gchar1 const * const buf)
{
   genter;

   assert(bufCount < GcountMAX);

   greturn json->io->setBuffer(json->io->repo.p, (Gn4) bufCount, buf);
}

/**************************************************************************************************
func: _JsonSetI
**************************************************************************************************/
Gb _JsonSetI(GioJson * const json, Gi8 const value)
{
   Gn8 ntemp;

   genter;

   ntemp = 0;
   if (value < 0)
   {
      json->io->setBuffer(json->io->repo.p, 1, (Gn1 *) "-");
      ntemp = -value;
   }
   else
   {
      ntemp =  value;
   }

   greturn _JsonSetN(json, ntemp);
}

/**************************************************************************************************
func: _JsonSetIndent
**************************************************************************************************/
Gb _JsonSetIndent(GioJson * const json)
{
   Gi4 index;

   genter;

   // No writing indents when in compact mode.
   greturnTrueIf(!json->scopeList[json->scope].isNiceFormatting);

   forCount (index, json->scope)
   {
      greturnFalseIf(!_JsonSetBuffer(json, 1, (Gn1 *) "\t"));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _JsonSetN
**************************************************************************************************/
Gb _JsonSetN(GioJson * const json, Gn8 const value)
{
   int index,
       count,
       digit;
   Gn8 temp;
   Gn1 string[32];

   genter;

   temp = value;
   loopCount(index)
   {
      digit = temp % 10;
      temp  = temp / 10;

      string[index] = (Gn1) ('0' + digit);

      breakIf(temp == 0);
   }

   count = index + 1;
   forCountDown (index, count)
   {
      greturnFalseIf(!json->io->setBuffer(json->io->repo.p, 1, (Gn1 *) &string[index]));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _JsonSetNewLine
**************************************************************************************************/
Gb _JsonSetNewLine(GioJson * const json)
{
   genter;

   // No writing new lines when in compact mode.
   greturnTrueIf(!json->scopeList[json->scope].isNiceFormatting);

   greturnFalseIf(!_JsonSetBuffer(json, 1, (Gn1 *) "\n"));

   greturn gbTRUE;
}

/**************************************************************************************************
func: _JsonSetR
**************************************************************************************************/
Gb _JsonSetR(GioJson * const json, Gr8 const value)
{
   Gchar ctemp[80];

   genter;

   if      (value == HUGE_VAL)
   {
      greturn _JsonSetBuffer(json, 10, (Gn1 *) "\"Infinity\"");
   }
   else if (value == -HUGE_VAL)
   {
      greturn _JsonSetBuffer(json, 11, (Gn1 *) "\"-Infinity\"");
   }
   else if (isnan(value))
   {
      greturn _JsonSetBuffer(json, 5, (Gn1 *) "\"NaN\"");
   }

   _sprintf_s_l((char *) ctemp, 80, "%.17g", gcharGetLocaleDefault(), value);

   greturn _JsonSetBuffer(json, gcharGetCount(ctemp), (Gn1 *) ctemp);
}

/**************************************************************************************************
func: _JsonSetR4
**************************************************************************************************/
Gb _JsonSetR4(GioJson * const json, Gr4 const value)
{
   Gchar ctemp[80];

   genter;

   if      (value == HUGE_VALF)
   {
      greturn _JsonSetBuffer(json, 10, (Gn1 *) "\"Infinity\"");
   }
   else if (value == -HUGE_VALF)
   {
      greturn _JsonSetBuffer(json, 11, (Gn1 *) "\"-Infinity\"");
   }
   else if (isnan(value))
   {
      greturn _JsonSetBuffer(json, 5, (Gn1 *) "\"NaN\"");
   }

   _sprintf_s_l((char *) ctemp, 80, "%.8g", gcharGetLocaleDefault(), value);

   greturn _JsonSetBuffer(json, gcharGetCount(ctemp), (Gn1 *) ctemp);
}
