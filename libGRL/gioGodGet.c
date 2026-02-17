/**************************************************************************************************
file:       God_get
author:     Robbert de Groot
copyright:  2025, Robbert de Groot

description:
Get functions local to the library.
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
local:
variable:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _GodEatSpace
**************************************************************************************************/
Gb _GodEatSpace(GioGod * const god)
{
   genter;

   greturnTrueIf(!_GodIsSpace(god))

   loop
   {
      greturnFalseIf(!_GodGetChar(god));

      greturnTrueIf(!_GodIsSpace(god));
   }
}

/**************************************************************************************************
func: _GodGetChar
**************************************************************************************************/
Gb _GodGetChar(GioGod * const god)
{
   genter;

   greturnFalseIf(!god->io->getBuffer(god->io->repo.p, 1, &god->lastByte));

   greturn gbTRUE;
}

/**************************************************************************************************
func: _GodGetNumber
**************************************************************************************************/
GioGodType _GodGetNumber(GioGod * const god)
{
   Gb        isIntegerNumberFound,
             isFractionalNumberFound,
             isExponentNumberFound;
   // Current double maxes out a 10^+/-308, 400 characters is large enough.
   Gchar1    numberStr[400];
   int       index;

   genter;

   // Reset the number string.
   forCount(index, 400)
   {
      numberStr[index] = 0;
   }

   // Read in the integer part.
   isIntegerNumberFound = gbFALSE;
   numberStr[0]         = god->lastByte;
   if ('0' <= god->lastByte && god->lastByte <= '9')
   {
      isIntegerNumberFound = gbTRUE;
   }

   for (index = 1; ; index++)
   {
      // End of file.
      if (!_GodGetChar(god))
      {
         greturnValIf(isIntegerNumberFound, _GodGetNumberInteger(god, numberStr));
         greturn gioGodTypeERROR_NUMBER_EXPECTED;
      }

      // Number is a Real
      if (god->lastByte == '.')
      {
         gotoIf(isIntegerNumberFound, GET_FRACTION);
         greturn gioGodTypeERROR_NUMBER_EXPECTED;
      }
      // Number is Real with an exponent
      if (god->lastByte == 'e' ||
          god->lastByte == 'E')
      {
         gotoIf(isIntegerNumberFound, GET_EXPONENT);
         greturn gioGodTypeERROR_NUMBER_EXPECTED;
      }

      // Add to the integer portion.
      if ('0' <= god->lastByte && god->lastByte <= '9')
      {
         numberStr[index]     = (Gchar1) god->lastByte;
         isIntegerNumberFound = gbTRUE;
      }
      // Assuming this is the end of the number.
      else
      {
         greturnValIf(isIntegerNumberFound, _GodGetNumberInteger(god, numberStr));
         greturn gioGodTypeERROR_NUMBER_EXPECTED;
      }
   }

GET_FRACTION:
   // Decimal was found.
   isFractionalNumberFound = gbFALSE;
   numberStr[index++]      = '.';
   for (;; index++)
   {
      // End of file
      if (!_GodGetChar(god))
      {
         greturnValIf(isFractionalNumberFound, _GodGetNumberReal(god, numberStr));
         greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
      }

      // Exponent defined
      if (god->lastByte == 'e' ||
          god->lastByte == 'E')
      {
         gotoIf(isFractionalNumberFound, GET_EXPONENT);
         greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
      }

      // Add to the fractional portion.
      if ('0' <= god->lastByte && god->lastByte <= '9')
      {
         numberStr[index]        = (Gchar1) god->lastByte;
         isFractionalNumberFound = gbTRUE;
      }
      // Assuming this is the end of the number.
      else
      {
         greturnValIf(isFractionalNumberFound, _GodGetNumberReal(god, numberStr));
         greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
      }
   }

GET_EXPONENT:
   // Exponent was found
   isExponentNumberFound = gbFALSE;
   numberStr[index++]    = 'e';

   // End of file in the middle of a number!
   greturnValIf(!_GodGetChar(god), gioGodTypeERROR_NUMBER_REAL_EXPECTED);

   // Get the sign.
   if      ('0' <= god->lastByte && god->lastByte <= '9')
   {
      numberStr[index++]    = (Gchar1) god->lastByte;
      isExponentNumberFound = gbTRUE;
   }
   // Negative exponent.
   else if (god->lastByte == '-')
   {
      numberStr[index++] = (Gchar1) god->lastByte;
   }
   // Wasn't a sign or a digit after the 'e'.
   else if (god->lastByte != '+')
   {
      greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
   }
   // If it was a "+" sign we just eat it.  Unnecessary.

   // Get the exponent
   for (;; index++)
   {
      if (!_GodGetChar(god))
      {
         greturnValIf(isExponentNumberFound, _GodGetNumberReal(god, numberStr));
         greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
      }

      if ('0' <= god->lastByte && god->lastByte <= '9')
      {
         numberStr[index]      = (Gchar1) god->lastByte;
         isExponentNumberFound = gbTRUE;
      }
      else
      {
         break;
      }
   }

   greturnValIf(isExponentNumberFound, _GodGetNumberReal(god, numberStr));

   greturn gioGodTypeERROR_NUMBER_REAL_EXPECTED;
}

/**************************************************************************************************
func: _GodGetNumberInteger
**************************************************************************************************/
GioGodType _GodGetNumberInteger(GioGod * const god, Gchar1 * const numberStr)
{
   GioGodType type;

   genter;

   // Default number type.
   type = gioGodTypeVALUE_NUMBER_INTEGER;

   // This is a negative number.  Definitely not a natural number.
   if (numberStr[0] == '-')
   {
      god->value.n = gchar1GetN(&numberStr[1]);
      if      (god->value.n == ((Gn8) Gi8MAX) + 1)
      {
         god->value.i = Gi8MIN;
      }
      else if (god->value.n <= Gi8MAX)
      {
         god->value.i = - (Gi8) god->value.n;
      }

      god->value.n  = 0;
      god->value.r  = (Gr8)  god->value.i;
      god->value.r4 = (Gr4) god->value.i;

      god->value.type = type;

      greturn type;
   }

   god->value.n = gchar1GetN(numberStr);
   // This unsigned integer is small enough to be a signed integer.
   if (god->value.n <= Gi8MAX)
   {
      god->value.i = god->value.n;
   }
   // Special case.  Not all unsigned integers can be represented as a signed integer.
   else
   {
      god->value.i = 0;
      type          = gioGodTypeVALUE_NUMBER_NATURAL;
   }

   god->value.r  = (Gr8)  god->value.n;
   god->value.r4 = (Gr4) god->value.n;

   // Set the type of the value.
   god->value.type = type;

   greturn type;
}

/**************************************************************************************************
func: _GodGetNumberReal
**************************************************************************************************/
GioGodType _GodGetNumberReal(GioGod * const god, Gchar1 * const str)
{
   genter;

   god->value.i    = 0;
   god->value.n    = 0;
   god->value.r    = gchar1GetR(str, gbFALSE);
   god->value.r4   = (Gr4) god->value.r;
   god->value.type = gioGodTypeVALUE_NUMBER_REAL;

   greturn gioGodTypeVALUE_NUMBER_REAL;
}

/**************************************************************************************************
func: _GodIsSpace
**************************************************************************************************/
Gb _GodIsSpace(GioGod * const god)
{
   genter;

   greturnTrueIf(
      god->lastByte == 0    ||
      god->lastByte == 0x09 ||
      god->lastByte == 0x0A ||
      god->lastByte == 0x0D ||
      god->lastByte == 0x20);

   greturn gbFALSE;
}
