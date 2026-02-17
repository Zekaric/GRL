/**************************************************************************************************
file:       gjson
author:     Robbert de Groot
copyright:  2021, Robbert de Groot

description:
Library for dealing with raw JSON files.
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
constant:
**************************************************************************************************/
#define INFINITY_STR             "Infinity"
#define INFINITY_STR_COUNT       8
#define INFINITY_NEG_STR         "-Infinity"
#define INFINITY_NEG_STR_COUNT   9
#define NOT_A_NUM_STR            "NaN"
#define NOT_A_NUM_STR_COUNT      3

/**************************************************************************************************
variable:
**************************************************************************************************/
static Gb _isStarted = gbFALSE;

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioJsonClocReader
**************************************************************************************************/
GioJson *gioJsonClocReader_(Gio * const gio)
{
   GioJson *json;

   genter;

   greturnNullIf(!_isStarted);

   // Create the json structure.
   json = gmemClocType(GioJson);
   greturnNullIf(!json);

   // Initialize the json structure.
   if (!gioJsonClocReaderContent(json, gio))
   {
      gmemDloc(json);
      greturn NULL;
   }

   // Return the json structure
   greturn json;
}

/**************************************************************************************************
func: gioJsonClocReaderContent
**************************************************************************************************/
Gb gioJsonClocReaderContent(GioJson * const json, Gio * const gio)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !gio);

   gmemClearType(json, GioJson);
   json->mode              = gioJsonModeREAD;
   json->io                = gio;
   json->scopeList[0].type = gioJsonScopeTypeNONE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonClocWriter
**************************************************************************************************/
GioJson *gioJsonClocWriter_(Gio * const gio)
{
   GioJson *json;

   genter;

   greturnNullIf(!_isStarted);

   // Create the json structure
   json = gmemClocType(GioJson);
   greturnNullIf(!json);

   // Initialize the structure
   if (!gioJsonClocWriterContent(json, gio))
   {
      gmemDloc(json);
      greturn NULL;
   }

   // Return the json structure
   greturn json;
}

/**************************************************************************************************
func: gioJsonClocWriterContent
**************************************************************************************************/
Gb gioJsonClocWriterContent(GioJson * const json, Gio * const gio)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !gio);

   gmemClearType(json, GioJson);
   json->mode                          = gioJsonModeWRITE;
   json->io                            = gio;
   json->isFirstItem                   = gbTRUE;
   json->scopeList[0].type             = gioJsonScopeTypeNONE;
   json->scopeList[0].isNiceFormatting = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonDloc
**************************************************************************************************/
void gioJsonDloc(GioJson * const json)
{
   genter;

   greturnIf(
      !_isStarted ||
      !json);

   gioJsonDlocContent(json);

   gmemDloc(json);

   greturn;
}

/**************************************************************************************************
func: gioJsonDlocContent
**************************************************************************************************/
void gioJsonDlocContent(GioJson * const json)
{
   genter;

   greturnIf(
      !_isStarted ||
      !json);

   greturn;
}

/**************************************************************************************************
func: gioJsonGetTypeArrayValueOrStop
**************************************************************************************************/
GioJsonType gioJsonGetTypeArrayValueOrStop(GioJson * const json)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !json,
      gioJsonTypeNONE);

   // Reset the value type.
   json->value.type = gioJsonTypeNONE;

   // Eat space.
   _JsonEatSpace(json);

   if (json->lastByte == jsonARRAY_STOP_CHAR)
   {
      json->scope--;
      json->lastByte = 0;
      greturn gioJsonTypeARRAY_STOP;
   }

   // If called after the first item in the array, then a separator between array elements is
   // possible.  Eat this separator and get to the next value.
   if (json->lastByte == jsonSEPARATOR_CHAR)
   {
      json->lastByte = 0;

      _JsonEatSpace(json);
   }

   // What do we have as a value.
   switch (json->lastByte)
   {
   case jsonOBJECT_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeOBJECT;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeOBJECT_START;

   case jsonARRAY_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeARRAY;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeARRAY_START;

   case jsonSTRING_QUOTE_CHAR:
      json->lastByte   = 0;
      json->value.type = gioJsonTypeVALUE_STRING_START;
      greturn gioJsonTypeVALUE_STRING_START;

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
   case '-':
      greturn _JsonGetNumber(json);

   case 't':
      greturn _JsonGetTrue(json);

   case 'f':
      greturn _JsonGetFalse(json);

   case 'n':
      greturn _JsonGetNull(json);
   }

   greturn gioJsonTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: gioJsonGetTypeFileElement

The first function you should be calling to obtain the value initial start of
the JSON file.
**************************************************************************************************/
GioJsonType gioJsonGetTypeFileElement(GioJson * const json)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !json,
      gioJsonTypeNONE);

   // Reset the value type.
   json->value.type = gioJsonTypeNONE;

   // Eat space.
   _JsonEatSpace(json);

   // What do we have as a value.
   switch (json->lastByte)
   {
   case jsonOBJECT_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeOBJECT;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeOBJECT_START;

   case jsonARRAY_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeARRAY;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeARRAY_START;

   case jsonSTRING_QUOTE_CHAR:
      json->lastByte   = 0;
      json->value.type = gioJsonTypeVALUE_STRING_START;
      greturn gioJsonTypeVALUE_STRING_START;

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
   case '-':
      greturn _JsonGetNumber(json);

   case 't':
      greturn _JsonGetTrue(json);

   case 'f':
      greturn _JsonGetFalse(json);

   case 'n':
      greturn _JsonGetNull(json);
   }

   greturn gioJsonTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: gioJsonGetTypeObjectKeyOrStop
**************************************************************************************************/
GioJsonType gioJsonGetTypeObjectKeyOrStop(GioJson * const json)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !json,
      gioJsonTypeNONE);

   // Reset the value type.
   json->value.type = gioJsonTypeNONE;

   // Eat space.
   _JsonEatSpace(json);

   if (json->lastByte == jsonOBJECT_STOP_CHAR)
   {
      json->scope--;
      json->lastByte = 0;
      greturn gioJsonTypeOBJECT_STOP;
   }

   // If called after the first key value pair, then a separator between object key values is
   // possible.  Eat this separator and get to the next key value.
   if (json->lastByte == jsonSEPARATOR_CHAR)
   {
      json->lastByte = 0;

      _JsonEatSpace(json);
   }

   // Found a key for a value.
   if (json->lastByte == jsonSTRING_QUOTE_CHAR)
   {
      // Reading in the key and the key value separator.
      json->lastByte = 0;

      greturnValIf(!gioJsonGetStr(json, gjsonCountDEFAULT, json->key), gioJsonTypeERROR_UNEXPECTED_CHAR);

      _JsonEatSpace(json);

      greturnValIf(json->lastByte != jsonKEY_VALUE_SEPARATOR_CHAR, gioJsonTypeERROR_UNEXPECTED_CHAR);

      json->lastByte = 0;

      greturn gioJsonTypeOBJECT_KEY;
   }

   greturn gioJsonTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: gioJsonGetTypeObjectValue
**************************************************************************************************/
GioJsonType gioJsonGetTypeObjectValue(GioJson * const json)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !json,
      gioJsonTypeNONE);

   // Reset the value type.
   json->value.type = gioJsonTypeNONE;

   // Eat space.
   _JsonEatSpace(json);

   // What do we have as a value.
   switch (json->lastByte)
   {
   case jsonOBJECT_STOP_CHAR:
      json->scope--;

      json->lastByte = 0;
      greturn gioJsonTypeOBJECT_STOP;

   case jsonKEY_VALUE_SEPARATOR_CHAR:
      json->lastByte = 0;
      greturn gioJsonTypeINTERNAL_KEY_VALUE_SEPARATOR;

   case jsonSEPARATOR_CHAR:
      json->lastByte = 0;
      greturn gioJsonTypeSEPARATOR;

   case jsonOBJECT_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeOBJECT;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeOBJECT_START;

   case jsonARRAY_START_CHAR:
      json->scope++;
      json->scopeList[json->scope].type             = gioJsonScopeTypeARRAY;
      json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

      json->lastByte = 0;
      greturn gioJsonTypeARRAY_START;

   case jsonSTRING_QUOTE_CHAR:
      json->lastByte   = 0;
      json->value.type = gioJsonTypeVALUE_STRING_START;
      greturn gioJsonTypeVALUE_STRING_START;

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
   case '-':
      greturn _JsonGetNumber(json);

   case 't':
      greturn _JsonGetTrue(json);

   case 'f':
      greturn _JsonGetFalse(json);

   case 'n':
      greturn _JsonGetNull(json);
   }

   greturn gioJsonTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: gioJsonGetKey
**************************************************************************************************/
Gchar1 const *gioJsonGetKey(GioJson * const json)
{
   genter;

   greturnNullIf(
      !_isStarted ||
      !json);

   greturn json->key;
}

/**************************************************************************************************
func: gioJsonGetI
**************************************************************************************************/
Gb gioJsonGetI(GioJson * const json, Gi8 * const value)
{
   genter;

   *value = 0;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      json->value.type != gioJsonTypeVALUE_NUMBER_INTEGER);

   *value = json->value.i;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonGetN
**************************************************************************************************/
Gb gioJsonGetN(GioJson * const json, Gn8 *  const value)
{
   genter;

   *value = 0;

   greturnFalseIf(
      !_isStarted ||
      !json);

   *value = json->value.n;

   // Return is false if the type of the number is no a natural or if it is a negative integer.
   greturnFalseIf(
      !(json->value.type == gioJsonTypeVALUE_NUMBER_NATURAL    ||
        (json->value.type == gioJsonTypeVALUE_NUMBER_INTEGER &&
         json->value.i    == (Gi8) json->value.n)));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonGetR

All numbers can be real.  However not all integers or naturals can be propely
or accurately be represented in real.  Up to the caller to determine if they
are doing something right in that situation.
**************************************************************************************************/
Gb gioJsonGetR(GioJson * const json, Gr8 * const value)
{
   genter;

   // The string may be a constant that represents some real value.  Attempt to parse it.
   if (json->value.type == gioJsonTypeVALUE_STRING_START)
   {
      GioJsonStrLetter  jletter;
      int             index;
      Gchar1          letter;
      Gchar           stemp[16];

      loopCount(index)
      {
         jletter = gioJsonGetStrLetter(json, &letter);
         breakIf(jletter == gioJsonStrLetterDONE);

         // Encountered a letter we aren't expening or the string is much larger than the constants
         // we know about.
         greturnFalseIf(
            jletter == gioJsonStrLetterERROR ||
            index >= 10);

         stemp[index] = letter;
      }
      greturnFalseIf(jletter == gioJsonStrLetterERROR);

      // Null terminate the string.
      stemp[index] = 0;

      if      (gcharIsEqualA(INFINITY_STR_COUNT, stemp, INFINITY_STR))
      {
         *value = Gr8INF;
      }
      else if (gcharIsEqualA(INFINITY_NEG_STR_COUNT, stemp, INFINITY_NEG_STR))
      {
         *value = -Gr8INF;
      }
      else if (gcharIsEqualA(NOT_A_NUM_STR_COUNT, stemp, NOT_A_NUM_STR))
      {
         *value = GrNAN;
      }
      // Not a constant we are familiar with.
      else
      {
         greturn gbFALSE;
      }

      greturn gbTRUE;
   }

   // Real value already parse and set in the value variable.
   *value = json->value.r;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonGetR4
**************************************************************************************************/
Gb gioJsonGetR4(GioJson * const json, Gr4 *  const value)
{
   genter;

   // The string may be a constant that represents some real value.  Attempt to parse it.
   if (json->value.type == gioJsonTypeVALUE_STRING_START)
   {
      GioJsonStrLetter  jletter;
      int             index;
      Gchar1          letter;
      Gchar           stemp[16];

      loopCount(index)
      {
         jletter = gioJsonGetStrLetter(json, &letter);
         breakIf(jletter == gioJsonStrLetterDONE);

         // Encountered a letter we aren't expening or the string is much larger than the constants
         // we know about.
         greturnFalseIf(
            jletter == gioJsonStrLetterERROR ||
            index >= 10);

         stemp[index] = letter;
      }
      greturnFalseIf(jletter == gioJsonStrLetterERROR);

      // Null terminate the string.
      stemp[index] = 0;

      if      (gcharIsEqualA(INFINITY_STR_COUNT, stemp, INFINITY_STR))
      {
         *value = Gr4INF;
      }
      else if (gcharIsEqualA(INFINITY_NEG_STR_COUNT, stemp, INFINITY_NEG_STR))
      {
         *value = -Gr4INF;
      }
      else if (gcharIsEqualA(NOT_A_NUM_STR_COUNT, stemp, NOT_A_NUM_STR))
      {
         *value = GrNAN;
      }
      // Not a constant we are familiar with.
      else
      {
         greturn gbFALSE;
      }

      greturn gbTRUE;
   }

   // Real value already parse and set in the value variable.
   *value = json->value.r4;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonGetStr
**************************************************************************************************/
Gb gioJsonGetStr(GioJson * const json, Gcount const maxCount, Gchar1 * const value)
{
   Gi4            index;
   GioJsonStrLetter letterType;

   genter;

   // Get the letters.
   forCount(index, maxCount)
   {
      letterType = gioJsonGetStrLetter(json, &value[index]);
      breakIf(letterType == gioJsonStrLetterDONE);

      // Convert Unicode letter to UTF8
      if (letterType == gioJsonStrLetterHEX)
      {
         // todo
      }
      greturnFalseIf(letterType == gioJsonStrLetterERROR);
   }

   // Null terminate
   if (index != maxCount)
   {
      value[index] = 0;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonGetStrBinByte
**************************************************************************************************/
GioJsonStrLetter gioJsonGetStrBinByte(GioJson * const json, Gn1 * const value)
{
   Gn1 vtemp;

   genter;

   greturnValIf(!json, gioJsonStrLetterERROR);

   greturnValIf(!json->io->getBuffer(json->io->repo.p, 1, &json->lastByte), gioJsonStrLetterERROR);

   greturnValIf(json->lastByte == '\"', gioJsonStrLetterDONE);

   switch (json->lastByte)
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
      vtemp = (json->lastByte - '0') << 4;
      break;

   case 'A':
   case 'B':
   case 'C':
   case 'D':
   case 'E':
   case 'F':
      vtemp = (json->lastByte - 'A' + 0xA) << 4;
      break;

   case 'a':
   case 'b':
   case 'c':
   case 'd':
   case 'e':
   case 'f':
      vtemp = (json->lastByte - 'a' + 0xA) << 4;
      break;
   }

   greturnValIf(!json->io->getBuffer(json->io->repo.p, 1, &json->lastByte), gioJsonStrLetterERROR);

   greturnValIf(json->lastByte == '\"', gioJsonStrLetterERROR);

   switch (json->lastByte)
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
      vtemp |= json->lastByte - '0';
      break;

   case 'A':
   case 'B':
   case 'C':
   case 'D':
   case 'E':
   case 'F':
      vtemp |= json->lastByte - 'A' + 0xA;
      break;

   case 'a':
   case 'b':
   case 'c':
   case 'd':
   case 'e':
   case 'f':
      vtemp |= json->lastByte - 'a' + 0xA;
      break;
   }

   *value = vtemp;

   greturn gioJsonStrLetterNORMAL;
}

/**************************************************************************************************
func: gioJsonGetStrLetter

Returns...
gioJsonStrLetterNORMAL when is it just a regular UTF8 letter or letter part.
gioJsonStrLetterHEX    when it is a \u[hex][hex][hex][hex] esscaped sequence.
gioJsonStrLetterDONE   when the string was fully read.
gioJsonStrLetterERROR  when there was a problem reading the string.
**************************************************************************************************/
GioJsonStrLetter gioJsonGetStrLetter(GioJson * const json, Gchar1 * const value)
{
   genter;

   *value = 0;

   greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);

   // Escaped letter
   if (json->lastByte == '\\')
   {
      greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);

      switch (json->lastByte)
      {
      case jsonSTRING_QUOTE_CHAR:
         *value = jsonSTRING_QUOTE_CHAR;
         break;

      case jsonBACK_SLASH_CHAR:
         *value = jsonBACK_SLASH_CHAR;
         break;

      case jsonFOREWARD_SLASH_CHAR:
         *value = jsonFOREWARD_SLASH_CHAR;
         break;

      case 'b':
         *value = '\b';
         break;

      case 'f':
         *value = '\f';
         break;

      case 'n':
         *value = '\n';
         break;

      case 'r':
         *value = '\r';
         break;

      case 't':
         *value = '\t';
         break;

      case 'u':
         *value = 0;
         greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);
         json->hex[0] = _JsonStrToHex(json->lastByte);

         greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);
         json->hex[1] = _JsonStrToHex(json->lastByte);

         greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);
         json->hex[1] = _JsonStrToHex(json->lastByte);

         greturnValIf(!_JsonGetChar(json), gioJsonStrLetterERROR);
         json->hex[1] = _JsonStrToHex(json->lastByte);

         greturn gioJsonStrLetterHEX;

      default:
         // Unknow excape sequence.
         greturn gioJsonStrLetterERROR;
      }
   }
   else
   {
      if (json->lastByte == '\"')
      {
         json->lastByte = 0;

         greturn gioJsonStrLetterDONE;
      }

      *value = (Gchar) json->lastByte;
   }

   greturn gioJsonStrLetterNORMAL;
}

/**************************************************************************************************
func: gioJsonGetStrHex
**************************************************************************************************/
Gb gioJsonGetStrHex(GioJson * const json, Gchar1 * const h1, Gchar1 * const h2, Gchar1 * const h3,
   Gchar1 * const h4)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !h1         ||
      !h2         ||
      !h3         ||
      !h4);

   *h1 = json->hex[0];
   *h2 = json->hex[1];
   *h3 = json->hex[2];
   *h4 = json->hex[3];

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonIsKeyEqual
**************************************************************************************************/
Gb gioJsonIsKeyEqual(GioJson const * const json, Gchar1 const * const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !value);

   greturn charIsEqual(gjsonCountDEFAULT, (Char *) json->key, (Char *) value);
}

/**************************************************************************************************
func: gioJsonIsTypeBin
**************************************************************************************************/
Gb gioJsonIsTypeBin(GioJsonType const type)
{
   genter;

   greturnFalseIf(!_isStarted);

   // Binary blobs with this library is stored in a hex dump in a stirng.
   greturn (type == gioJsonTypeVALUE_STRING_START);
}

/**************************************************************************************************
func: gioJsonIsTypeI
**************************************************************************************************/
Gb gioJsonIsTypeI(GioJsonType const type)
{
   genter;

   greturnFalseIf(!_isStarted);

   greturn (type == gioJsonTypeVALUE_NUMBER_INTEGER);
}

/**************************************************************************************************
func: gioJsonIsTypeN
**************************************************************************************************/
Gb gioJsonIsTypeN(GioJsonType const type)
{
   genter;

   greturnFalseIf(!_isStarted);

   greturn
      (type == gioJsonTypeVALUE_NUMBER_INTEGER ||
       type == gioJsonTypeVALUE_NUMBER_NATURAL);
}

/**************************************************************************************************
func: gioJsonIsTypeR
**************************************************************************************************/
Gb gioJsonIsTypeR(GioJsonType const type)
{
   genter;

   greturnFalseIf(!_isStarted);

   greturn
      (type == gioJsonTypeVALUE_NUMBER_INTEGER || // Integerss can be Reals
       type == gioJsonTypeVALUE_NUMBER_NATURAL || // Naturals can be Reals
       type == gioJsonTypeVALUE_NUMBER_REAL    ||
       type == gioJsonTypeVALUE_STRING_START);    // Without actually parsing the string we won't
                                                // really know but there are a few constants that
                                                // are in strings.  So there is a possibility.
}

/**************************************************************************************************
func: gioJsonIsTypeStr
**************************************************************************************************/
Gb gioJsonIsTypeStr(GioJsonType const type)
{
   genter;

   greturnFalseIf(!_isStarted);

   // Binary blobs with this library is stored in a hex dump in a stirng.
   greturn (type == gioJsonTypeVALUE_STRING_START);
}

/**************************************************************************************************
func: gioJsonSetArrayStart
**************************************************************************************************/
Gb gioJsonSetArrayStart(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   greturnFalseIf(!_JsonSetBuffer(json, 1, (Gn1 *) jsonARRAY_START_STR));

   json->scope++;
   json->scopeList[json->scope].type             = gioJsonScopeTypeARRAY;
   json->scopeList[json->scope].isNiceFormatting = gbFALSE;

   json->isFirstItem = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetArrayStop
**************************************************************************************************/
Gb gioJsonSetArrayStop(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      json->scope == 0);

   json->scopeList[json->scope].type = gioJsonScopeTypeNONE;
   json->scope--;

   json->isFirstItem = gbFALSE;

   greturnFalseIf(!_JsonSetBuffer( json, 1, (Gn1 *) jsonARRAY_STOP_STR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetIsNiceFormatting
**************************************************************************************************/
void gioJsonSetIsNiceFormatting(GioJson * const json, Gb const value)
{
   genter;

   greturnIf(
      !_isStarted ||
      !json);

   json->scopeList[json->scope].isNiceFormatting = value;

   greturn;
}

/**************************************************************************************************
func: gioJsonSetKey
**************************************************************************************************/
Gb gioJsonSetKey(GioJson * const json, Gchar1 const * const key)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !key);

   greturnFalseIf(!gioJsonSetSeparator(json));

   json->isFirstItem = gbFALSE;

   greturnFalseIf(!gioJsonSetValueStrStart(json));
   loopCount(index)
   {
      breakIf(key[index] == 0);

      greturnFalseIf(!gioJsonSetValueStrLetter(json, key[index]));
   }
   greturnFalseIf(!gioJsonSetValueStrStop(json));

   greturnFalseIf(!_JsonSetBuffer( json, 1, (Gn1 *) jsonKEY_VALUE_SEPARATOR_STR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetObjectStart
**************************************************************************************************/
Gb gioJsonSetObjectStart(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   greturnFalseIf(!_JsonSetBuffer( json, 1, (Gn1 *) jsonOBJECT_START_STR));

   json->scope++;
   json->scopeList[json->scope].type             = gioJsonScopeTypeOBJECT;
   json->scopeList[json->scope].isNiceFormatting = json->scopeList[json->scope - 1].isNiceFormatting;

   json->isFirstItem = gbTRUE;

   greturnFalseIf(!_JsonSetNewLine(json));
   greturnFalseIf(!_JsonSetIndent( json));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetObjectStop
**************************************************************************************************/
Gb gioJsonSetObjectStop(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      json->scope == 0);

   json->scopeList[json->scope].type = gioJsonScopeTypeNONE;
   json->scope--;

   json->isFirstItem = gbFALSE;

   greturnFalseIf(!_JsonSetNewLine(json));
   greturnFalseIf(!_JsonSetIndent( json));
   greturnFalseIf(!_JsonSetBuffer( json, 1, (Gn1 *) jsonOBJECT_STOP_STR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetSeparator
**************************************************************************************************/
Gb gioJsonSetSeparator(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (!json->isFirstItem)
   {
      greturnFalseIf(!_JsonSetBuffer(json, 1, (Gn1 *) jsonSEPARATOR_STR));
      greturnFalseIf(!_JsonSetNewLine( json));
      greturnFalseIf(!_JsonSetIndent(  json));
   }
   json->isFirstItem = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueBin
**************************************************************************************************/
Gb gioJsonSetValueBin(GioJson * const json, Gcount const count, Gn1 const * const value)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !value);

   greturnFalseIf(!gioJsonSetValueStrStart(json));
   forCount(index, count)
   {
      greturnFalseIf(!gioJsonSetValueBinByte(json, value[index]));
   }
   greturnFalseIf(!gioJsonSetValueStrStop(json));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueBinByte
**************************************************************************************************/
Gb gioJsonSetValueBinByte(GioJson * const json, Gn1 const value)
{
   Char letters[] = "0123456789ABCDEF";
   Gn1  output[2];

   genter;

   greturnFalseIf(!json);

   output[0] = letters[value >> 4];
   output[1] = letters[value & 0x0F];

   greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) output));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueBinStart
**************************************************************************************************/
Gb gioJsonSetValueBinStart(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   greturnFalseIf(!gioJsonSetValueStrStart(json));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueBinStop
**************************************************************************************************/
Gb gioJsonSetValueBinStop(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   greturnFalseIf(!gioJsonSetValueStrStop(json));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueB
**************************************************************************************************/
Gb gioJsonSetValueB(GioJson * const json, Gb const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   if (value == gbTRUE)
   {
      greturn _JsonSetBuffer(json, 4, (Gn1 *) "true");
   }

   greturn _JsonSetBuffer(json, 5, (Gn1 *) "false");
}

/**************************************************************************************************
func: gioJsonSetValueI
**************************************************************************************************/
Gb gioJsonSetValueI(GioJson * const json, Gi8 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   greturn _JsonSetI(json, value);
}

/**************************************************************************************************
func: gioJsonSetValueN
**************************************************************************************************/
Gb gioJsonSetValueN(GioJson * const json, Gn8 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   greturn _JsonSetN(json, value);
}

/**************************************************************************************************
func: gioJsonSetValueNull
**************************************************************************************************/
Gb gioJsonSetValueNull(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   json->isFirstItem = gbFALSE;

   greturn _JsonSetBuffer(json, 4, (Gn1 *) "null");
}

/**************************************************************************************************
func: gioJsonSetValueR
**************************************************************************************************/
Gb gioJsonSetValueR(GioJson * const json, Gr8 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   greturn _JsonSetR(json, value);
}

/**************************************************************************************************
func: gioJsonSetValueR4
**************************************************************************************************/
Gb gioJsonSetValueR4(GioJson * const json, Gr4 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   greturn _JsonSetR4(json, value);
}

/**************************************************************************************************
func: gioJsonSetValueStr
**************************************************************************************************/
Gb gioJsonSetValueStr(GioJson * const json, Gchar1 const * const str)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !json       ||
      !str);

   greturnFalseIf(!gioJsonSetValueStrStart(json));
   loopCount(index)
   {
      breakIf(str[index] == 0);

      greturnFalseIf(!gioJsonSetValueStrLetter(json, str[index]));
   }
   greturnFalseIf(!gioJsonSetValueStrStop(json));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueStrLetter
**************************************************************************************************/
Gb gioJsonSetValueStrLetter(GioJson * const json, Gchar1 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   switch (value)
   {
   case jsonSTRING_QUOTE_CHAR:
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_QUOTE_STR));
      break;

   case jsonBACK_SLASH_CHAR:
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_BACK_SLASH_STR));
      break;

   case jsonFOREWARD_SLASH_CHAR:
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_FORWARD_SLASH_STR));
      break;

   case '\b':
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_BACKSPACE_STR));
      break;

   case '\f':
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_FORMFEED_STR));
      break;

   case '\n':
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_LINEFEED_STR));
      break;

   case '\r':
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_CARRIAGE_RETURN_STR));
      break;

   case '\t':
      greturnFalseIf(!_JsonSetBuffer(json, 2, (Gn1 *) jsonSTRING_ESCAPE_TAB_STR));
      break;

   default:
      greturnFalseIf(!_JsonSetBuffer(json, 1, (Gn1 *) &value));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioJsonSetValueStrStart
**************************************************************************************************/
Gb gioJsonSetValueStrStart(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   if (json->scopeList[json->scope].type == gioJsonScopeTypeARRAY)
   {
      greturnFalseIf(!gioJsonSetSeparator(json));
   }

   json->isFirstItem = gbFALSE;

   greturn _JsonSetBuffer(json, 1, (Gn1 *) jsonSTRING_QUOTE_STR);
}

/**************************************************************************************************
func: gioJsonSetValueStrStop
**************************************************************************************************/
Gb gioJsonSetValueStrStop(GioJson * const json)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !json);

   greturn _JsonSetBuffer(json, 1, (Gn1 *) "\"");
}
