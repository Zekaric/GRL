/**************************************************************************************************
file:       gchar
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
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

/**************************************************************************************************
local:
variable:
**************************************************************************************************/
static _locale_t   _localeLocal;
static _locale_t   _localeDefault;

/**************************************************************************************************
global
function
**************************************************************************************************/
/**************************************************************************************************
func: charIsMultiline
**************************************************************************************************/
grlAPI Gb charIsMultiline(Char const * const str)
{
   Char const *cp;

   genter;

   cp = str;

   loop
   {
      breakIf(      *cp == '\n');

      greturnFalseIf(*cp == 0);

      cp++;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gcharCompare

Compare the two strings.
**************************************************************************************************/
grlAPI Gcompare gcharCompare(Gcount const length, Gchar const * const a, Gchar const * const b)
{
   Gindex index;
   Gi4    value;

   genter;

   greturnValIf(
         (!a && !b) ||
         length <= 0,
      gcompareEQUAL);

   // same pointer.
   greturnValIf(a == b, gcompareEQUAL);

   // a is null, less than b.
   greturnValIf(!a, gcompareLESS_THAN);

   // b is null, greater than a.
   greturnValIf(!b, gcompareGREATER_THAN);

   forCount(index, length)
   {
      // end of both strings and found no difference.  Equal.
      greturnValIf(
            a[index] == 0 &&
            b[index] == 0,
         gcompareEQUAL);

      // a terminated before b.  a is less than b.
      greturnValIf(a[index] == 0, gcompareLESS_THAN);

      // b terminated before a.  a is greater than b.
      greturnValIf(b[index] == 0, gcompareGREATER_THAN);

      // Which is greater?
      value = a[index] - b[index];
      greturnValIf(value < 0, gcompareLESS_THAN);
      greturnValIf(value > 0, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gcharCompareA
**************************************************************************************************/
grlAPI Gcompare gcharCompareA(Gcount const length, Gchar const * const a, Char const * const b)
{
   Gindex index;
   Gi4    value;

   genter;

   greturnValIf(
      (!a && !b) ||
      length <= 0,
      gcompareEQUAL);

   // a is null, less than b.
   greturnValIf(!a, gcompareLESS_THAN);

   // b is null, greater than a.
   greturnValIf(!b, gcompareGREATER_THAN);

   forCount(index, length)
   {
      // end of both strings and found no difference.  Equal.
      greturnValIf(
         a[index] == 0 &&
         b[index] == 0,
         gcompareEQUAL);

      // a terminated before b.  a is less than b.
      greturnValIf(a[index] == 0, gcompareLESS_THAN);

      // b terminated before a.  a is greater than b.
      greturnValIf(b[index] == 0, gcompareGREATER_THAN);

      // Which is greater?
      value = a[index] - b[index];
      greturnValIf(value < 0, gcompareLESS_THAN);
      greturnValIf(value > 0, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gcharCompareBase

compare string without case.
**************************************************************************************************/
grlAPI Gcompare gcharCompareBase(Gcount const length, Gchar const * const a, Gchar const * const b)
{
   Gindex index;
   Gi4    value;

   genter;

   greturnValIf(
         (!a && !b) ||
         length <= 0,
      gcompareEQUAL);

   // same pointer.
   greturnValIf(a == b, gcompareEQUAL);

   greturnValIf(!a, gcompareLESS_THAN);

   greturnValIf(!b, gcompareGREATER_THAN);

   forCount(index, length)
   {
      greturnValIf(
            a[index] == 0 &&
            b[index] == 0,
         gcompareEQUAL);

      greturnValIf(a[index] == 0, gcompareLESS_THAN);

      greturnValIf(b[index] == 0, gcompareGREATER_THAN);

      // Which is greater based of their lower case value.
      // This is not culturally sensitive.
      value = gcharToLowerCase(a[index]) - gcharToLowerCase(b[index]);
      greturnValIf(value < 0, gcompareLESS_THAN);
      greturnValIf(value > 0, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gcharFromGchar1

Convert a Gchar1 to Gchar.
**************************************************************************************************/
grlAPI Gcount gcharFromGchar1(Gchar1 const letter1, Gchar1 const letter2, Gchar1 const letter3,
   Gchar1 const letter4, Gchar * const letter)
{
   genter;

   greturn0If(!letter);

   // one byte.
   if ((letter1 & 0x80) == 0)
   {
      *letter = letter1;
      greturn 1;
   }

   // two byte.
   if ((letter1 & 0xe0) == 0xc0)
   {
      *letter =
         (((Gchar) letter1 & 0x1f) << 6) |
          ((Gchar) letter2 & 0x3f);
   }

   // three byte.
   if ((letter1 & 0xf0) == 0xe0)
   {
      *letter =
         ((((Gchar) letter1) & 0x0f) << 12) |
         ((((Gchar) letter2) & 0x3f) <<  6) |
          (((Gchar) letter3) & 0x3f);
      greturn 3;
   }

   // four byte.
   *letter =
      ((((Gchar) letter1) & 0x07) << 18) |
      ((((Gchar) letter2) & 0x3f) << 12) |
      ((((Gchar) letter3) & 0x3f) <<  6) |
       (((Gchar) letter4) & 0x3f);
   greturn 4;
}

/**************************************************************************************************
func: gcharFromGchar2

Convert Gchar2 to Gchar.
**************************************************************************************************/
grlAPI Gcount gcharFromGchar2(Gchar2 const letter1, Gchar2 const letter2, Gchar * const letter)
{
   genter;

   greturn0If(!letter);

   if ((letter1 & 0xd000) == 0xd000)
   {
      *letter =
            (((Gchar) letter1) & 0x03ff)                   +
           ((((Gchar) letter2) & 0x003f) << 10)            +
         ((((((Gchar) letter2) & 0x03C0) >>  6) + 1) << 16);
      greturn 2;
   }

   *letter = letter1;
   greturn 1;
}

/**************************************************************************************************
func: gchar1FromGchar
**************************************************************************************************/
grlAPI Gcount gchar1FromGchar(Gchar const letter, Gchar1 * const letter1, Gchar1 * const letter2,
   Gchar1 * const letter3, Gchar1 * const letter4)
{
   genter;

   greturn0If(
      !letter1 ||
      !letter2 ||
      !letter3 ||
      !letter4);

   if (letter < 0x0000007f)
   {
      *letter4 = 0;
      *letter3 = 0;
      *letter2 = 0;
      *letter1 = (Gchar1) letter;
      greturn 1;
   }

   if (letter < 0x000007ff)
   {
      *letter4 = 0;
      *letter3 = 0;
      *letter2 = (Gchar1) (0x80 |  (letter       & 0x3f));
      *letter1 = (Gchar1) (0xc0 | ((letter >> 6) & 0x1f));
      greturn 2;
   }

   if (letter < 0x0000ffff)
   {
      *letter4 = 0;
      *letter3 = (Gchar1) (0x80 |  (letter        & 0x3f));
      *letter2 = (Gchar1) (0x80 | ((letter >>  6) & 0x3f));
      *letter1 = (Gchar1) (0xe0 | ((letter >> 12) & 0x0f));
      greturn 3;
   }

   // letter < 0x001fffff
   *letter4 = (Gchar1) (0x80 |  (letter        & 0x3f));
   *letter3 = (Gchar1) (0x80 | ((letter >>  6) & 0x3f));
   *letter2 = (Gchar1) (0x80 | ((letter >> 12) & 0x3f));
   *letter1 = (Gchar1) (0xf0 | ((letter >> 18) & 0x07));
   greturn 4;
}

/**************************************************************************************************
func: gchar2FromGchar
**************************************************************************************************/
grlAPI Gcount gchar2FromGchar(Gchar const letter, Gchar2 * const letter1, Gchar2 * const letter2)
{
   Gchar letterTemp;

   genter;

   greturn0If(
      !letter1 ||
      !letter2);

   if ((0x0000 < letter && letter < 0xd7ff) ||
       (0xe000 < letter && letter < 0xffff))
   {
      *letter2 = 0;
      *letter1 = (Gchar2) letter;
      greturn 1;
   }

   *letter2   = (Gchar2) (0xdc00 | (letter & 0x03ff));

   letterTemp = (letter >> 10) & 0x03ff;
   *letter1   = (Gchar2)
      (0xd800 |
         (   (letterTemp       & 0x3f) +
          ((((letterTemp >> 6) & 0x1f) - 1) << 6)));
   greturn 2;
}

/**************************************************************************************************
func: gcharGetCount
**************************************************************************************************/
grlAPI Gcount gcharGetCount(Gchar const * const str)
{
   Gindex loopIndex;

   genter;

   loopCount(loopIndex)
   {
      breakIf(!str[loopIndex]);
   }

   greturn loopIndex;
}

/**************************************************************************************************
func: gcharGetI
**************************************************************************************************/
grlAPI Gi gcharGetI(Gchar const * const str)
{
   Gi           i,
                iLetter;
   Gb           isNegative,
                isDone;
   Gchar const *cp;

   genter;

   cp = str;

   // Eat space
   while (*cp)
   {
      breakIf(!gcharIsWhiteSpace(*cp));
   }

   isNegative = gbFALSE;
   if (*cp == '-')
   {
      isNegative = gbTRUE;
   }

   i      = 0;
   isDone = gbFALSE;
   while (*cp)
   {
      iLetter = 0;
      switch (*cp)
      {
      case '0':                   break;
      case '1': iLetter = 1;      break;
      case '2': iLetter = 2;      break;
      case '3': iLetter = 3;      break;
      case '4': iLetter = 4;      break;
      case '5': iLetter = 5;      break;
      case '6': iLetter = 6;      break;
      case '7': iLetter = 7;      break;
      case '8': iLetter = 8;      break;
      case '9': iLetter = 9;      break;
      default:  isDone  = gbTRUE; break;
      }

      breakIf(isDone);

      i = i * 10 + iLetter;
   }

   greturn (isNegative) ? -i : i;
}

/**************************************************************************************************
func: gcharGetLocaleDefault
**************************************************************************************************/
grlAPI _locale_t gcharGetLocaleDefault(void)
{
   genter;
   greturn _localeDefault;
}

/**************************************************************************************************
func: gcharGetN
**************************************************************************************************/
grlAPI Gn gcharGetN(Gchar const * const str)
{
   Gn           n;
   Gb           isDone;
   Gchar const *cp;

   genter;

   cp = str;

   // Eat space
   while (*cp)
   {
      breakIf(!gcharIsWhiteSpace(*cp));
   }

   n      = 0;
   isDone = gbFALSE;
   while (*cp)
   {
      switch (*cp)
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         n = n * 10 + *cp - '0';
         break;

      default:
         isDone = gbTRUE;
         break;
      }

      breakIf(isDone);
   }

   greturn n;
}

/**************************************************************************************************
func: gchar1GetN
**************************************************************************************************/
grlAPI Gn8 gchar1GetN(Gchar1 const * const str)
{
   Gn            n;
   Gb            isDone;
   Gchar1 const *cp;

   genter;

   cp = str;

   // Eat space
   while (*cp)
   {
      breakIf(!gcharIsWhiteSpace((Gchar) *cp));
   }

   n      = 0;
   isDone = gbFALSE;
   while (*cp)
   {
      switch (*cp)
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         n = n * 10 + *cp - '0';
         break;

      default:
         isDone = gbTRUE;
         break;
      }

      breakIf(isDone);
   }

   greturn n;
}

/**************************************************************************************************
func: gcharGetNHex
**************************************************************************************************/
grlAPI Gn gcharGetNHex(Gchar const * const str)
{
   Gn           n,
                nLetter;
   Gb           isDone;
   Gchar const *cp;

   genter;

   cp = str;

   // Eat space
   while (*cp)
   {
      breakIf(!gcharIsWhiteSpace(*cp));
   }

   n      = 0;
   isDone = gbFALSE;
   while (*cp)
   {
      nLetter = 0;
      switch (*cp)
      {
      case '0':                     break;
      case '1': nLetter = 0x1;      break;
      case '2': nLetter = 0x2;      break;
      case '3': nLetter = 0x3;      break;
      case '4': nLetter = 0x4;      break;
      case '5': nLetter = 0x5;      break;
      case '6': nLetter = 0x6;      break;
      case '7': nLetter = 0x7;      break;
      case '8': nLetter = 0x8;      break;
      case '9': nLetter = 0x9;      break;
      case 'a':
      case 'A': nLetter = 0xa;      break;
      case 'b':
      case 'B': nLetter = 0xb;      break;
      case 'c':
      case 'C': nLetter = 0xc;      break;
      case 'd':
      case 'D': nLetter = 0xd;      break;
      case 'e':
      case 'E': nLetter = 0xe;      break;
      case 'f':
      case 'F': nLetter = 0xf;      break;
      default:  isDone  = gbTRUE; break;
      }

      breakIf(isDone);

      n = (n << 4) | nLetter;
   }

   greturn n;
}

/**************************************************************************************************
func: gchar1GetNHex
**************************************************************************************************/
grlAPI Gn gchar1GetNHex(Gchar1 const * const str)
{
   Gn            n,
                 nLetter;
   Gb            isDone;
   Gchar1 const *cp;

   genter;

   cp = str;

   // Eat space
   while (*cp)
   {
      breakIf(!gcharIsWhiteSpace(*cp));
   }

   n      = 0;
   isDone = gbFALSE;
   while (*cp)
   {
      nLetter = 0;
      switch (*cp)
      {
      case '0':                     break;
      case '1': nLetter = 0x1;      break;
      case '2': nLetter = 0x2;      break;
      case '3': nLetter = 0x3;      break;
      case '4': nLetter = 0x4;      break;
      case '5': nLetter = 0x5;      break;
      case '6': nLetter = 0x6;      break;
      case '7': nLetter = 0x7;      break;
      case '8': nLetter = 0x8;      break;
      case '9': nLetter = 0x9;      break;
      case 'a':
      case 'A': nLetter = 0xa;      break;
      case 'b':
      case 'B': nLetter = 0xb;      break;
      case 'c':
      case 'C': nLetter = 0xc;      break;
      case 'd':
      case 'D': nLetter = 0xd;      break;
      case 'e':
      case 'E': nLetter = 0xe;      break;
      case 'f':
      case 'F': nLetter = 0xf;      break;
      default:  isDone  = gbTRUE; break;
      }

      breakIf(isDone);

      n = (n << 4) | nLetter;
   }

   greturn n;
}

/**************************************************************************************************
func: gcharGetR
**************************************************************************************************/
grlAPI Gr gcharGetR(Gchar const * const str, Gb const isLocalized)
{
   Gindex index;
   Gr     result;
   Gchar1 ctemp[512];

   genter;

   isLocalized;
   result = 0;

   // Move to a char * so that we can use a built in function.
   forCount(index, gMAX(gcharGetCount(str), 511))
   {
      ctemp[index] = (Gchar1) str[index];

      breakIf(ctemp[index] == 0);
   }
   ctemp[index] = 0;

   result = gchar1GetR(ctemp, isLocalized);

   greturn result;
}

/**************************************************************************************************
func: gchar1GetR
**************************************************************************************************/
grlAPI Gr gchar1GetR(Gchar1 const * const str, Gb const isLocalized)
{
   Gr result;

   genter;

   // Whatever the local locale is.
   if (isLocalized)
   {
      result = _atof_l((Char *) str, _localeLocal);
   }
   // Default North American Locale; '.' for decimal place.
   else
   {
      result = _atof_l((Char *) str, _localeDefault);
   }

   greturn result;
}

/**************************************************************************************************
func: gchar1GetByteCount
**************************************************************************************************/
grlAPI Gcount gchar1GetByteCount(Gchar1 const letter)
{
   genter;

   greturnValIf((letter & 0x80) == 0, 1);

   greturnValIf((letter & 0xe0) == 0xc0, 2);

   greturnValIf((letter & 0xf0) == 0xe0, 3);

   greturn 4;
}

/**************************************************************************************************
func: gcharIsDigit

Is the letter a digit.
**************************************************************************************************/
grlAPI Gb gcharIsDigit(Gchar const letter)
{
   genter;

   greturn ('0' <= letter && letter <= '9') ? gbFALSE : gbTRUE;
}

/**************************************************************************************************
func: gcharIsEqual
**************************************************************************************************/
grlAPI Gb gcharIsEqual(Gcount const count, Gchar const * const a, Gchar const * const b)
{
   genter;

   greturn gcharCompare(count, a, b) == gcompareEQUAL ? gbTRUE : gbFALSE;
}

/**************************************************************************************************
func: gcharIsEqualA
**************************************************************************************************/
grlAPI Gb gcharIsEqualA(Gcount const count, Gchar const * const a, Char const * const b)
{
   genter;

   greturn gcharCompareA(count, a, b) == gcompareEQUAL ? gbTRUE : gbFALSE;
}

/**************************************************************************************************
func: gcharIsWhiteSpace

Test to see if the letter is a white space.
**************************************************************************************************/
grlAPI Gb gcharIsWhiteSpace(Gchar const letter)
{
   genter;

   greturn
      (letter == (Gchar) gcharWHITESPACE[0] ||
       letter == (Gchar) gcharWHITESPACE[1] ||
       letter == (Gchar) gcharWHITESPACE[2] ||
       letter == (Gchar) gcharWHITESPACE[3] ||
       letter == (Gchar) gcharWHITESPACE[4] ||
       letter == (Gchar) gcharWHITESPACE[5]);
}

/**************************************************************************************************
func: gcharStart
**************************************************************************************************/
Gb gcharStart(void)
{
   genter;

   _localeDefault = _create_locale(LC_ALL, "C");

   greturn gbTRUE;
}

/**************************************************************************************************
func: gcharStop
**************************************************************************************************/
void gcharStop(void)
{
   genter;

   greturn;
}

/**************************************************************************************************
func: gcharToLowerCase

Only ASCII at the moment.
**************************************************************************************************/
grlAPI Gchar gcharToLowerCase(Gchar const letter)
{
   genter;

   greturnValIf(letter > 127, letter);

   greturn (Gchar) tolower((Char) letter);
}

/**************************************************************************************************
func: gcharToUpperCase

Only ASCII at the moment.
**************************************************************************************************/
grlAPI Gchar gcharToUpperCase(Gchar const letter)
{
   genter;

   greturnValIf(letter > 127, letter);

   greturn (Gchar) toupper((Gchar) letter);
}
