/**************************************************************************************************
file:       gjsonGet
author:     Robbert de Groot
copyright:  2021, Robbert de Groot

description:
Get functions local to the library.
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
local:
variable:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _JsonEatSpace
**************************************************************************************************/
Gb _JsonEatSpace(GioJson * const json)
{
   genter;

   greturnTrueIf(!_JsonIsSpace(json))

   loop
   {
      greturnFalseIf(!_JsonGetChar(json));

      greturnTrueIf( !_JsonIsSpace(json));
   }
}

/**************************************************************************************************
func: _JsonGetChar
**************************************************************************************************/
Gb _JsonGetChar(GioJson * const json)
{
   genter;

   greturnFalseIf(!json->io->getBuffer(json->io->repo.p, 1, &json->lastByte));

   greturn gbTRUE;
}

/**************************************************************************************************
func: _JsonGetFalse
**************************************************************************************************/
GioJsonType _JsonGetFalse(GioJson * const json)
{
   genter;

   loop
   {
      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'a');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'l');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 's');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'e');

      json->lastByte = 0;

      greturn gioJsonTypeVALUE_FALSE;
   }

   greturn gioJsonTypeERROR_CONSTANT_FALSE_EXPECTED;
}

/**************************************************************************************************
func: _JsonGetNull
**************************************************************************************************/
GioJsonType _JsonGetNull(GioJson * const json)
{
   genter;

   loop
   {
      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'u');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'l');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'l');

      json->lastByte = 0;

      greturn gioJsonTypeVALUE_NULL;
   }

   greturn gioJsonTypeERROR_CONSTANT_NULL_EXPECTED;
}

/**************************************************************************************************
func: _JsonGetNumber
**************************************************************************************************/
GioJsonType _JsonGetNumber(GioJson * const json)
{
   Gb     isIntegerNumberFound,
          isFractionalNumberFound,
          isExponentNumberFound;
   // Current doulbe maxes out a 10^+/-308, 400 characters is large enough.
   Gchar1 numberStr[400];
   int    index;

   genter;

   // Reset the number string.
   forCount(index, 400)
   {
      numberStr[index] = 0;
   }

   // Read in the integer part.
   isIntegerNumberFound = gbFALSE;
   numberStr[0]        = json->lastByte;
   if ('0' <= json->lastByte && json->lastByte <= '9')
   {
      isIntegerNumberFound = gbTRUE;
   }

   for (index = 1; ; index++)
   {
      // End of file.
      if (!_JsonGetChar(json))
      {
         greturnValIf(isIntegerNumberFound, _JsonGetNumberInteger(json, numberStr));
         greturn gioJsonTypeERROR_NUMBER_EXPECTED;
      }

      // Number is a Real
      if (json->lastByte == '.')
      {
         gotoIf(isIntegerNumberFound, GET_FRACTION);
         greturn gioJsonTypeERROR_NUMBER_EXPECTED;
      }
      // Number is Real with an exponent
      if (json->lastByte == 'e' ||
          json->lastByte == 'E')
      {
         gotoIf(isIntegerNumberFound, GET_EXPONENT);
         greturn gioJsonTypeERROR_NUMBER_EXPECTED;
      }

      // Add to the integer portion.
      if ('0' <= json->lastByte && json->lastByte <= '9')
      {
         numberStr[index]     = (Gchar) json->lastByte;
         isIntegerNumberFound = gbTRUE;
      }
      // Assuming this is the end of the number.
      else
      {
         greturnValIf(isIntegerNumberFound, _JsonGetNumberInteger(json, numberStr));
         greturn gioJsonTypeERROR_NUMBER_EXPECTED;
      }
   }

GET_FRACTION:
   // Decimal was found.
   isFractionalNumberFound = gbFALSE;
   numberStr[index++]      = '.';
   for (;; index++)
   {
      // End of file
      if (!_JsonGetChar(json))
      {
         greturnValIf(isFractionalNumberFound, _JsonGetNumberReal(json, numberStr));
         greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
      }

      // Exponent defined
      if (json->lastByte == 'e' ||
          json->lastByte == 'E')
      {
         gotoIf(isFractionalNumberFound, GET_EXPONENT);
         greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
      }

      // Add to the fractional portion.
      if ('0' <= json->lastByte && json->lastByte <= '9')
      {
         numberStr[index]        = (Gchar) json->lastByte;
         isFractionalNumberFound = gbTRUE;
      }
      // Assuming this is the end of the number.
      else
      {
         greturnValIf(isFractionalNumberFound, _JsonGetNumberReal(json, numberStr));
         greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
      }
   }

GET_EXPONENT:
   // Exponent was found
   isExponentNumberFound = gbFALSE;
   numberStr[index++]    = 'e';

   // End of file in the middle of a number!
   greturnValIf(!_JsonGetChar(json), gioJsonTypeERROR_NUMBER_REAL_EXPECTED);

   // Get the sign.
   if      ('0' <= json->lastByte && json->lastByte <= '9')
   {
      numberStr[index++]    = (Gchar) json->lastByte;
      isExponentNumberFound = gbTRUE;
   }
   // Negative exponent.
   else if (json->lastByte == '-')
   {
      numberStr[index++] = (Gchar) json->lastByte;
   }
   // Wasn't a sign or a digit after the 'e'.
   else if (json->lastByte != '+')
   {
      greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
   }
   // If it was a "+" sign we just eat it.  Unnecessary.

   // Get the exponent
   for (;; index++)
   {
      if (!_JsonGetChar(json))
      {
         greturnValIf(isExponentNumberFound, _JsonGetNumberReal(json, numberStr));
         greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
      }

      if ('0' <= json->lastByte && json->lastByte <= '9')
      {
         numberStr[index]      = (Gchar) json->lastByte;
         isExponentNumberFound = gbTRUE;
      }
      else
      {
         break;
      }
   }

   greturnValIf(isExponentNumberFound, _JsonGetNumberReal(json, numberStr));
   greturn gioJsonTypeERROR_NUMBER_REAL_EXPECTED;
}

/**************************************************************************************************
func: _JsonGetNumberInteger
**************************************************************************************************/
GioJsonType _JsonGetNumberInteger(GioJson * const json, Gchar1 const * const numberStr)
{
   GioJsonType type;

   genter;

   // Default number type.
   type = gioJsonTypeVALUE_NUMBER_INTEGER;

   // This is a negative number.  Definitely not a natural number.
   if (numberStr[0] == '-')
   {
      json->value.n = gchar1GetN(&numberStr[1]);
      if      (json->value.n == ((Gn8) Gi8MAX) + 1)
      {
         json->value.i = Gi8MIN;
      }
      else if (json->value.n <= Gi8MAX)
      {
         json->value.i = - (Gi8) json->value.n;
      }

      json->value.n  = 0;
      json->value.r  = (Gr8) json->value.i;
      json->value.r4 = (Gr4) json->value.i;

      json->value.type = type;
      greturn type;
   }

   json->value.n = gchar1GetN(numberStr);
   // This unsigned integer is small enough to be a signed integer.
   if (json->value.n <= Gi8MAX)
   {
      json->value.i = json->value.n;
   }
   // Special case.  Not all unsigned integers can be represented as a signed integer.
   else
   {
      json->value.i = 0;
      type          = gioJsonTypeVALUE_NUMBER_NATURAL;
   }

   json->value.r  = (Gr8)  json->value.n;
   json->value.r4 = (Gr4) json->value.n;

   // Set the type of the value.
   json->value.type = type;

   greturn type;
}

/**************************************************************************************************
func: _JsonGetNumberReal
**************************************************************************************************/
GioJsonType _JsonGetNumberReal(GioJson * const json, Gchar1 const * const str)
{
   genter;

   json->value.i    = 0;
   json->value.n    = 0;
   json->value.r    = gchar1GetR(str, gbFALSE);
   json->value.r4   = (Gr4) json->value.r;
   json->value.type = gioJsonTypeVALUE_NUMBER_REAL;

   greturn gioJsonTypeVALUE_NUMBER_REAL;
}

/**************************************************************************************************
func: _JsonGetTrue
**************************************************************************************************/
GioJsonType _JsonGetTrue(GioJson * const json)
{
   genter;

   loop
   {
      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'r');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'u');

      breakIf(!_JsonGetChar(json));
      breakIf(json->lastByte != 'e');

      json->lastByte = 0;

      greturn gioJsonTypeVALUE_TRUE;
   }

   greturn gioJsonTypeERROR_CONSTANT_TRUE_EXPECTED;
}

/**************************************************************************************************
func: _JsonIsSpace
**************************************************************************************************/
Gb _JsonIsSpace(GioJson * const json)
{
   genter;

   greturnTrueIf(
      json->lastByte == 0    ||
      json->lastByte == 0x09 ||
      json->lastByte == 0x0A ||
      json->lastByte == 0x0D ||
      json->lastByte == 0x20);

   greturn gbFALSE;
}
