/**************************************************************************************************
file:       God_set
author:     Robbert de Groot
copyright:  2025, Robbert de Groot

description:
Set functions local to the library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

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
#include "giogodLocal.h"

/**************************************************************************************************
global:
function
**************************************************************************************************/
/**************************************************************************************************
func: _GodSetBuffer
**************************************************************************************************/
Gb _GodSetBuffer(GioGod const * const god, Gcount const bufCount, Gn1 const * const buf)
{
   genter;

   assert(bufCount < GcountMAX);

   greturn god->io->setBuffer(god->io->repo.p, (Gn4) bufCount, buf);
}

/**************************************************************************************************
func: _GodSetByte
**************************************************************************************************/
Gb _GodSetByte(GioGod const * const god, Gn1 const letter)
{
   Gn1 byte[1];

   genter;

   byte[0] = letter;

   greturn _GodSetBuffer(god, 1, byte);
}

/**************************************************************************************************
func: _GodSetI
**************************************************************************************************/
Gb _GodSetI(GioGod * const god, Gi8 const value)
{
   Gn8 ntemp;

   genter;

   ntemp = 0;
   if (value < 0)
   {
      god->io->setBuffer(god->io->repo.p, 1, (Gn1 *) "-");
      ntemp = -value;
   }
   else
   {
      ntemp =  value;
   }

   greturn _GodSetN(god, ntemp);
}

/**************************************************************************************************
func: _GodSetIndent
**************************************************************************************************/
Gb _GodSetIndent(GioGod * const god)
{
   Gindex index;

   genter;

   // No writing indents when in compact mode.
   greturnTrueIf(!god->scopeList[god->scope].isNiceFormatting);

   forCount (index, god->scope)
   {
      greturnFalseIf(!_GodSetBuffer(god, 1, (Gn1 *) "\t"));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _GodSetN
**************************************************************************************************/
Gb _GodSetN(GioGod * const god, Gn8 const value)
{
   Gindex index,
          digit;
   Gcount count;
   Gn8    temp;
   Gn1    string[32];

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
      greturnFalseIf(!god->io->setBuffer(god->io->repo.p, 1, (Gn1 *) &string[index]));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _GodSetNewLine
**************************************************************************************************/
Gb _GodSetNewLine(GioGod * const god)
{
   genter;

   // No writing new lines when in compact mode.
   greturnTrueIf(!god->scopeList[god->scope].isNiceFormatting);

   greturnFalseIf(!_GodSetByte(god, (Gn1) godSPACE_NEWLINE_CHAR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: _GodSetR
**************************************************************************************************/
Gb _GodSetR(GioGod * const god, Gr8 const value)
{
   Gchar1 ctemp[80];

   genter;

   _sprintf_s_l((char *) ctemp, 80, "%.17g", gcharGetLocaleDefault(), value);

   greturn _GodSetBuffer(god, gchar1GetCount(ctemp), (Gn1 *) ctemp);
}

/**************************************************************************************************
func: _GodSetR4
**************************************************************************************************/
Gb _GodSetR4(GioGod * const god, Gr4 const value)
{
   Gchar1 ctemp[80];

   genter;

   _sprintf_s_l((char *) ctemp, 80, "%.8g", gcharGetLocaleDefault(), value);

   greturn _GodSetBuffer(god, gchar1GetCount(ctemp), (Gn1 *) ctemp);
}
