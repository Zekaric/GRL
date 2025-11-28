/**************************************************************************************************
file:       gc
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) 2000, Robbert de Groot
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

//lint -save -e550 -e830

/**************************************************************************************************
local:
variable:
**************************************************************************************************/

/**************************************************************************************************
global
function
**************************************************************************************************/
/**************************************************************************************************
gc
**************************************************************************************************/
/**************************************************************************************************
func: gcCompare

Compare the two strings.
**************************************************************************************************/
grlAPI Gcompare gcCompare(Gcount const length, Gc const * const a, Gc const * const b)
{
   Gindex index;
   Gi4    value;

   genter;

   greturnValIf(
         (!a && !b) ||
         length <= 0,
      gcompareEQUAL);

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

      value = a[index] - b[index];
      greturnValIf(value < 0, gcompareLESS_THAN);
      greturnValIf(value > 0, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gcCompareBase

compare string without case.
**************************************************************************************************/
grlAPI Gcompare gcCompareBase(Gcount const length, Gc2 const * const a, Gc2 const * const b)
{
   Gindex index;
   Gi4    value;

   genter;

   greturnValIf(
         (!a && !b) ||
         length <= 0,
      gcompareEQUAL);

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

      value = gcToLowerCase(a[index]) - gcToLowerCase(b[index]); //lint !e931
      greturnValIf(value < 0, gcompareLESS_THAN);
      greturnValIf(value > 0, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gc2Compare
**************************************************************************************************/
grlAPI Gcompare gc2Compare(Gc2 const * const a, Gc2 const * const b)
{
   genter;

   greturnValIf(*a == *b, gcompareEQUAL);
   greturnValIf(*a < *b,  gcompareLESS_THAN);
   greturn                gcompareGREATER_THAN;
}

/**************************************************************************************************
func: gcFromA
**************************************************************************************************/
grlAPI Gc gcFromA(Char const letter)
{
   genter;
   greturn (Gc) letter; //lint !e571
}

grlAPI Gc2 gc2FromA(Char const letter)
{
   genter;
   greturn (Gc) letter; //lint !e571
}

/**************************************************************************************************
func: gcFromU1

Convert a U1 Gc to Gc.

param:
str
   Gc1 *
   in
   The string, 1 to 4 bytes

return:
Gc
**************************************************************************************************/
grlAPI Gc gcFromU1(Gc1 const * const str)
{
   Gc letter;

   genter;

   greturn0If(!str);

   // one byte.
   if ((str[0] & 0x80) == 0)
   {
      greturn (Gc) str[0];
   }

   // two byte.
   if ((str[0] & 0xe0) == 0xc0)
   {
      letter =
         ((str[0] & 0x1f) << 6) |
          (str[1] & 0x3f);

      greturn letter;
   }

   // three byte.
   if ((str[0] & 0xf0) == 0xe0)
   {
      letter =
         ((((Gn4) str[0]) & 0x0f) << 12) |
         ((((Gn4) str[1]) & 0x3f) <<  6) |
          (((Gn4) str[2]) & 0x3f);

      greturn letter;
   }

   // four byte.
   letter =
      ((((Gn4) str[0]) & 0x07) << 18) |
      ((((Gn4) str[1]) & 0x3f) << 12) |
      ((((Gn4) str[2]) & 0x3f) <<  6) |
       (((Gn4) str[3]) & 0x3f);

   greturn letter;
}

/**************************************************************************************************
func: gcFromU2

Convert UFT16 to Gc

param:
str
   Gc2 *
   in
   the string.

return:
Gc
**************************************************************************************************/
grlAPI Gc gcFromU2(Gc2 const * const str)
{
   Gc letter;

   genter;

   greturn0If(!str);

   if ((str[0] & 0xd000) == 0xd000)
   {
      letter =
            (((Gn4) str[0]) & 0x03ff)                   + //lint !e571
           ((((Gn4) str[1]) & 0x003f) << 10)            + //lint !e571
         ((((((Gn4) str[1]) & 0x03C0) >>  6) + 1) << 16); //lint !e571

      greturn letter;
   }

   greturn (Gc) str[0]; //lint !e571
}

/**************************************************************************************************
func: gcGetCount
**************************************************************************************************/
grlAPI Gcount gcGetCount(Gc const * const str)
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
func: gcGetCountA
**************************************************************************************************/
grlAPI Gcount gcGetCountA(Char const * const str)
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
func: gcGetCountU1
**************************************************************************************************/
grlAPI Gcount gcGetCountU1(Gc1 const * const str)
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
func: gcGetCountU2
**************************************************************************************************/
grlAPI Gcount gcGetCountU2(Gc2 const * const str)
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
func: gcGetLength

Get the length of a raw Gc buffer.
**************************************************************************************************/
grlAPI Gcount gcGetLength(Gc const * const str)
{
   Gcount    count;
   Gc const *strTemp;

   genter;

   greturn0If(!str);

   strTemp = str;
   count   = 0;
   loop
   {
      breakIf(*strTemp == 0);
      strTemp++;
      count++;
   }

   greturn count;
}

/**************************************************************************************************
func: gc2GetLength
**************************************************************************************************/
grlAPI Gcount gc2GetLength(Gc2 const * const str)
{
   Gcount result;

   genter;

   result = (Gcount) wcslen(str);

   greturn result;
}

/**************************************************************************************************
func: gcGetLetterByteCount

Get the number of bytes used for the letter.
**************************************************************************************************/
grlAPI Gcount gcGetLetterByteCount(Gp const * const ptr, GcType const type)
{
   Gc1 const *c1;
   Gc2 const *c2;

   genter;

   greturn0If(
      !ptr               ||
      type == gcTypeNONE ||
      type == gcTypeSTR);

   //lint -save -e787
   switch (type)
   {
   case gcTypeA:
      greturn 1;

   case gcTypeU1:
      c1 = (Gc1 const *) ptr;
      greturnValIf((c1[0] & 0x80) == 0,    1);
      greturnValIf((c1[0] & 0xe0) == 0xc0, 2);
      greturnValIf((c1[0] & 0xf0) == 0xe0, 3);
      break;

   case gcTypeU2:
      c2 = (Gc2 const *) ptr;
      greturnValIf((c2[0] & 0xd000) != 0xd000, 2);
      break;
   }
   //lint -restore

   greturn 4;
}

/**************************************************************************************************
func: gcGetTypeSize

Get the base size of the type.

param:
type
   GcType
   in
   The type.

return:
int
   1, 2 or 4 bytes.
**************************************************************************************************/
grlAPI Gsize gcGetTypeSize(GcType const type)
{
   genter;

   greturn0If(
      type == gcTypeNONE ||
      type == gcTypeSTR);

   //lint -save -e787
   switch (type)
   {
   case gcTypeA:
   case gcTypeU1:
      greturn 1;

   case gcTypeU2:
      greturn 2;
   }
   //lint -restore

   greturn 4;
}

/**************************************************************************************************
func: gcIsAlpha

Test to see if the character is a letter.
**************************************************************************************************/
grlAPI Gb gcIsAlpha(Gc const letter)
{
   Gb  result;
   Gc2 l16[2];

   genter;

   gcToU2(letter, &(l16[0]), &(l16[1])); //lint !e534

   result = (iswdigit(l16[0])) ? gbTRUE : gbFALSE; //lint !e732 !e917

   greturn result;
}

/**************************************************************************************************
func: gcIsDigit

Is the letter a digit.
**************************************************************************************************/
grlAPI Gb gcIsDigit(Gc const letter)
{
   Gb  result;
   Gc2 l16[2];

   genter;

   gcToU2(letter, &(l16[0]), &(l16[1])); //lint !e534

   result = (iswdigit(l16[0])) ? gbTRUE : gbFALSE; //lint !e732 !e917

   greturn result;
}

/**************************************************************************************************
func: gcIsEqualU1
**************************************************************************************************/
grlAPI Gb gcIsEqualU1(Gcount const count, Gc1 const * const aStr, Gc1 const * const bStr)
{
   Gindex loopIndex;

   genter;

   forCount(loopIndex, count)
   {
      greturnFalseIf(aStr[loopIndex] != bStr[loopIndex]);

      breakIf(aStr[loopIndex] == 0);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gcIsWhiteSpace

Test to see if the letter is a white space.

param:
letter
   Gc
   in
   The letter

return:
int
**************************************************************************************************/
grlAPI Gb gcIsWhiteSpace(Gc const letter)
{
   Gb  result;
   Gc2 l16[2];

   genter;

   gcToU2(letter, &(l16[0]), &(l16[1])); //lint !e534

   result = (iswspace(l16[0]) | iswcntrl(l16[0])) ? gbTRUE : gbFALSE; //lint !e732 !e917 !e931

   greturn result;
}

/**************************************************************************************************
func: gcSearchForLetter

Find a letter in a raw Gc string.
**************************************************************************************************/
grlAPI Gc const *gcSearchForLetter(Gc const * const str, Gc const letter)
{
   Gindex strIndex;

   genter;

   greturnNullIf(!str);

   for (strIndex = 0; str[strIndex] != 0; strIndex++)
   {
      greturnValIf(
            str[strIndex] == letter,
         &(str[strIndex]));
   }

   greturn &(str[strIndex]);
}

/**************************************************************************************************
func: gcSearchForLetters

Find the first occurrance of a letter matching one of the given letters.
**************************************************************************************************/
grlAPI Gc const *gcSearchForLetters(Gc const * const str, Gc const * const letters)
{
   Gindex strIndex,
          letterIndex;

   genter;

   greturnNullIf(!str);

   greturnValIf(!letters, str);

   for (strIndex = 0; str[strIndex] != 0; strIndex++)
   {
      for (letterIndex = 0; letters[letterIndex] != 0; letterIndex++)
      {
         greturnValIf(
               str[strIndex] == letters[letterIndex],
            &(str[strIndex]));
      }
   }

   greturn &(str[strIndex]);
}

/**************************************************************************************************
func: gcSearchForLettersA

Find the first of a selection of letters.
**************************************************************************************************/
grlAPI Gc const *gcSearchForLettersA(Gc const * const str, Char const * const letters)
{
   Gindex strIndex,
          letterIndex;

   genter;

   greturnNullIf(!str);

   greturnValIf(!letters, str);

   for (strIndex = 0; str[strIndex] != 0; strIndex++)
   {
      for (letterIndex = 0; letters[letterIndex] != 0; letterIndex++)
      {
         greturnValIf(
               str[strIndex] == gcFromA(letters[letterIndex]),
            &(str[strIndex])); //lint !e737
      }
   }

   greturn &(str[strIndex]);
}

/**************************************************************************************************
func: gcSearchForLettersInv

Return the first occurrance of a letter not in the set of given letters.
**************************************************************************************************/
grlAPI Gc const *gcSearchForLettersInv(Gc const * const str, Gc const * const letters)
{
   Gindex strIndex,
          letterIndex;
   Gb     found;

   genter;

   greturnNullIf(!str);

   greturnValIf(!letters, str);

   for (strIndex = 0; str[strIndex] != 0; strIndex++)
   {
      found = gbTRUE;

      for (letterIndex = 0; letters[letterIndex] != 0; letterIndex++)
      {
         if (str[strIndex] == letters[letterIndex])
         {
            found = gbFALSE;
            break;
         }
      }

      greturnValIf(found, &(str[strIndex]));
   }

   greturn &(str[strIndex]);
}

/**************************************************************************************************
func: gcSearchForString

Find a substring in a string.
**************************************************************************************************/
grlAPI Gc const *gcSearchForString(Gc const * const str, Gcount const subStrLength,
   Gc const * const subStr)
{
   Gindex strIndex,
          tempIndex,
          subStrIndex;
   Gb     found;

   genter;

   greturnNullIf(!str);

   greturnValIf(
         subStrLength <= 0 ||
         !subStr,
      str);

   // Not the most elegant or fast way to search for the substring.
   for (strIndex = 0; str[strIndex] != 0; strIndex++)
   {
      found = gbTRUE;

      // Compare the string with the substring.
      tempIndex = strIndex;
      forCount(subStrIndex, subStrLength)
      {
         if (str[tempIndex] != subStr[subStrIndex])
         {
            found = gbFALSE;
            break;
         }
         tempIndex++;
      }

      // Found the substring.
      greturnValIf(found, &(str[strIndex]));
   }

   greturn &(str[strIndex]);
}

/**************************************************************************************************
func: gcStart
**************************************************************************************************/
Gb gcStart(void)
{
   genter;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gcStop
**************************************************************************************************/
void gcStop(void)
{
   genter;

   greturn;
}

/**************************************************************************************************
func: gcToLowerCase

Convert Gc to Gc1

param:
letter
   Gc
   in
   the letter.

return:
Gc
   The lower case letter.
**************************************************************************************************/
grlAPI Gc2 gcToLowerCase(Gc2 const letter)
{
   Gc2 result;

   genter;

   result = towlower(letter); //lint !e732 !e713 !e917

   greturn result;
}

/**************************************************************************************************
func: gcToA
**************************************************************************************************/
grlAPI Gc gcToA(Gc const letter)
{
   genter;
   greturnValIf(letter < 256, (Gc) letter);
   greturn 0;
}

/**************************************************************************************************
func: gcToU1

Convert Gc to Gc1

param:
letter
   Gc
   in
   the letter.

a, b, c, d
   Gc1 *
   out
   The letter

return:
int
   Number of Gc1s needed to represent the Gc.
**************************************************************************************************/
grlAPI Gcount gcToU1(Gc const letter, Gc1 * const a, Gc1 * const b, Gc1 * const c,
   Gc1 * const d)
{
   genter;

   greturn0If(
      !a ||
      !b ||
      !c ||
      !d);

   if (letter < 0x0000007f)
   {
      *d = 0;
      *c = 0;
      *b = 0;
      *a = (Gc1) letter;
      greturn 1;
   }

   if (letter < 0x000007ff)
   {
      *d = 0;
      *c = 0;
      *b = (Gc1) (0x80 |  (letter       & 0x3f));
      *a = (Gc1) (0xc0 | ((letter >> 6) & 0x1f));
      greturn 2;
   }

   if (letter < 0x0000ffff)
   {
      *d = 0;
      *c = (Gc1) (0x80 |  (letter        & 0x3f));
      *b = (Gc1) (0x80 | ((letter >>  6) & 0x3f));
      *a = (Gc1) (0xe0 | ((letter >> 12) & 0x0f));
      greturn 3;
   }

   // letter < 0x001fffff
   *d = (Gc1) (0x80 |  (letter        & 0x3f));
   *c = (Gc1) (0x80 | ((letter >>  6) & 0x3f));
   *b = (Gc1) (0x80 | ((letter >> 12) & 0x3f));
   *c = (Gc1) (0xf0 | ((letter >> 18) & 0x07));
   greturn 4;
}

/**************************************************************************************************
func: gcToU2

Convert Gc to Gc2

param:
letter
   Gc
   in
   the letter.

a, b
   Gc2 *
   out
   The letter

return:
int
   Number of Gc1s needed to represent the Gc.
**************************************************************************************************/
grlAPI Gcount gcToU2(Gc const letter, Gc2 * const a, Gc2 * const b)
{
   Gc letterTemp;

   genter;

   greturn0If(
      !a ||
      !b);

   if ((0x0000 < letter && letter < 0xd7ff) ||
       (0xe000 < letter && letter < 0xffff))
   {
      *b = 0;
      *a = (Gc2) letter;
      greturn 1;
   }

   *b = (Gc2) (0xdc00 | (letter & 0x03ff)); //lint !e960

   letterTemp = (letter >> 10) & 0x03ff;
   *a         = (Gc2)
      (0xd800 |
         (   (letterTemp       & 0x3f) +
          ((((letterTemp >> 6) & 0x1f) - 1) << 6) //lint !e960
         )
      );//lint !e960
   greturn 2;
}

/**************************************************************************************************
func: gcToUpperCase

Convert Gc to Gc1

param:
letter
   Gc
   in
   the letter.

return:
Gc
   The lower case letter.
**************************************************************************************************/
grlAPI Gc2 gcToUpperCase(Gc2 const letter)
{
   Gc2 result;

   genter;

   result = towupper(letter); //lint !e732 !e713 !e917

   greturn result;
}

//lint -restore
