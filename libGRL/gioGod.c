/**************************************************************************************************
file:       GioGod
author:     Robbert de Groot
copyright:  2025, Robbert de Groot

description:
GodLib is a IO library for GOD Files.  A GOD file is a JSON 'like' file without JSON's limitations.
GOD - Groot's Organized Data file.  JSON is nice and all but implementations are all over the map
because JavaScript has limitations.
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
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/
static Gb _isStarted = gbFALSE;

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioGodClocReader
**************************************************************************************************/
grlAPI GioGod *gioGodClocReader_(Gio * const gio)
{
   GioGod *giogod;

   genter;

   greturnNullIf(!_isStarted);

   // Create the structure
   giogod = gmemClocType(GioGod);
   greturnNullIf(!giogod);

   // Init the structure
   if (!gioGodClocReaderContent(giogod, gio))
   {
      gmemDloc(giogod);
      greturn NULL;
   }

   // Return the structure
   greturn giogod;
}

/**************************************************************************************************
func: gioGodClocReaderContent
**************************************************************************************************/
grlAPI Gb gioGodClocReaderContent(GioGod * const giogod, Gio * const gio)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod     ||
      !gio);

   gmemClearType(giogod, GioGod);

   giogod->mode              = gioGodModeREAD;
   giogod->io                = gio;
   giogod->scopeList[0].type = gioGodScopeTypeGROUP;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodClocWriter
**************************************************************************************************/
grlAPI GioGod *gioGodClocWriter_(Gio * const gio)
{
   GioGod *giogod;

   genter;

   greturnNullIf(!_isStarted);

   // Create the structure
   giogod = gmemClocType(GioGod);
   greturnNullIf(!giogod);

   // Init the structure
   if (!gioGodClocWriterContent(giogod, gio))
   {
      gmemDloc(giogod);
      greturn NULL;
   }

   // greturn the structure
   greturn giogod;
}

/**************************************************************************************************
func: gioGodClocWriterContent
**************************************************************************************************/
grlAPI Gb gioGodClocWriterContent(GioGod * const giogod, Gio * const gio)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod     ||
      !gio);

   gmemClearType(giogod, GioGod);
   giogod->mode              = gioGodModeWRITE;
   giogod->io                = gio;
   giogod->isFirstItem       = gbTRUE;
   giogod->scopeList[0].type = gioGodScopeTypeGROUP;

   greturnFalseIf(!gioGodSetGroupValueI(giogod, godFILE_HEADER_STR, godFILE_VERSION, 0));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodDloc
**************************************************************************************************/
grlAPI void gioGodDloc(GioGod * const giogod)
{
   genter;

   greturnIf(
      !_isStarted ||
      !giogod);

   gioGodDlocContent(giogod);

   gmemDloc(giogod);

   greturn;
}

/**************************************************************************************************
func: gioGodDlocContent
**************************************************************************************************/
grlAPI void gioGodDlocContent(GioGod * const giogod)
{
   genter;

   greturnIf(
      !_isStarted ||
      !giogod);

   greturn;
}

/**************************************************************************************************
func: gioGodGetTypeArrayValueOrStop
**************************************************************************************************/
grlAPI GioGodType gioGodGetTypeArrayValueOrStop(GioGod * const giogod)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !giogod,
      gioGodTypeNONE);

   // Reset the value type.
   giogod->value.type = gioGodTypeNONE;

   // Eat space.
   _GodEatSpace(giogod);

   if (giogod->lastByte == godARRAY_STOP_CHAR)
   {
      giogod->scope--;
      giogod->lastByte = 0;
      greturn gioGodTypeARRAY_STOP;
   }

   // If called after the first item in the array, then a separator between array elements is
   // possible.  Eat this separator and get to the next value.
   if (giogod->lastByte == godSEPARATOR_CHAR)
   {
      giogod->lastByte = 0;

      _GodEatSpace(giogod);
   }

   // What do we have as a value.
   switch (giogod->lastByte)
   {
   case godGROUP_START_CHAR:
      giogod->scope++;
      giogod->scopeList[giogod->scope].type             = gioGodScopeTypeGROUP;
      giogod->scopeList[giogod->scope].isNiceFormatting = giogod->scopeList[giogod->scope - 1].isNiceFormatting;

      giogod->lastByte = 0;
      greturn gioGodTypeGROUP_START;

   case godARRAY_START_CHAR:
      giogod->scope++;
      giogod->scopeList[giogod->scope].type             = gioGodScopeTypeARRAY;
      giogod->scopeList[giogod->scope].isNiceFormatting = giogod->scopeList[giogod->scope - 1].isNiceFormatting;

      giogod->lastByte = 0;
      greturn gioGodTypeARRAY_START;

   case godSTRING_QUOTE_CHAR:
      giogod->lastByte   = 0;
      giogod->value.type = gioGodTypeVALUE_STRING_START;
      greturn gioGodTypeVALUE_STRING_START;

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
      greturn _GodGetNumber(giogod);

   case 'I':
      breakIf(!_GodGetChar(giogod));
      greturnValIf(giogod->lastByte == '+', gioGodTypeVALUE_INFINITY);
      greturnValIf(giogod->lastByte == '-', gioGodTypeVALUE_INFINITY_NEGATIVE);
      break;

   case 'M':
      breakIf(!_GodGetChar(giogod));
      greturnValIf(giogod->lastByte == '+', gioGodTypeVALUE_MAX);
      greturnValIf(giogod->lastByte == '-', gioGodTypeVALUE_MAX_NEGATIVE);
      break;

   case 'm':
      breakIf(!_GodGetChar(giogod));
      greturnValIf(giogod->lastByte == '+', gioGodTypeVALUE_MIN);
      greturnValIf(giogod->lastByte == '-', gioGodTypeVALUE_MIN_NEGATIVE);
      break;

   case 'X':
      greturn gioGodTypeVALUE_NOT_A_NUMBER;

   case 'T':
      greturn gioGodTypeVALUE_TRUE;

   case 'F':
      greturn gioGodTypeVALUE_FALSE;

   case '~':
      greturn gioGodTypeVALUE_NULL;
   }

   greturn gioGodTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: godGetType_GroupKeyOrStop
**************************************************************************************************/
grlAPI GioGodType gioGodGetTypeGrouptKeyOrStop(GioGod * const giogod)
{
   Gindex index;

   genter;

   greturnValIf(
         !_isStarted ||
         !giogod,
      gioGodTypeNONE);

   // Reset the value type.
   giogod->value.type = gioGodTypeNONE;

   // Eat space.
   _GodEatSpace(giogod);

   if (giogod->lastByte == godGROUP_STOP_CHAR)
   {
      giogod->scope--;
      giogod->lastByte = 0;
      greturn gioGodTypeGROUP_STOP;
   }

   // If called after the first key value pair, then a separator between object key values is
   // possible.  Eat this separator and get to the next key value.
   if (giogod->lastByte == godSEPARATOR_CHAR)
   {
      giogod->lastByte = 0;

      _GodEatSpace(giogod);
   }

   // Expecting a key
   _GodEatSpace(giogod);
   greturnValIf(
         giogod->lastByte == godKEY_VALUE_SEPARATOR_CHAR ||
         giogod->lastByte == godSEPARATOR_CHAR           ||
         giogod->lastByte == godGROUP_STOP_CHAR,
      gioGodTypeERROR_UNEXPECTED_CHAR);

   // Get the characters till key value separator, group value separator, or group terminator
   giogod->key[0] = giogod->lastByte;
   for (index = 1; index < godCountDEFAULT; index++)
   {
      greturnValIf(!_GodGetChar(giogod), gioGodTypeERROR_UNEXPECTED_CHAR);

      breakIf(
         giogod->lastByte == godKEY_VALUE_SEPARATOR_CHAR ||
         giogod->lastByte == godSEPARATOR_CHAR           ||
         giogod->lastByte == godGROUP_STOP_CHAR);

      giogod->key[index] = giogod->lastByte;
   }

   // Trim trailing spaces.
   for (index--; index >= 0; index--)
   {
      breakIf(!godIS_SPACE(giogod->key[index]));
      giogod->key[index] = 0;
   }

   // Just a key
   gmemClearType(&giogod->value, GioGodValue);
   if      (giogod->lastByte == godSEPARATOR_CHAR ||
            giogod->lastByte == godGROUP_STOP_CHAR)
   {
      giogod->value.type = gioGodTypeVALUE_NO_VALUE;

      greturn gioGodTypeGROUP_KEY;
   }
   else if (giogod->lastByte == godKEY_VALUE_SEPARATOR_CHAR)
   {
      giogod->lastByte = 0;

      greturn gioGodTypeGROUP_KEY;
   }

   greturn gioGodTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: godGetType_GroupValue
**************************************************************************************************/
grlAPI GioGodType gioGodGetTypeGroupValue(GioGod * const giogod)
{
   genter;

   greturnValIf(
         !_isStarted ||
         !giogod,
      gioGodTypeNONE);

   // Already know there is no value for this key.
   greturnValIf(giogod->value.type == gioGodTypeVALUE_NO_VALUE, gioGodTypeVALUE_NO_VALUE);

   // Eat space.
   _GodEatSpace(giogod);

   // What do we have as a value.
   switch (giogod->lastByte)
   {
   case godGROUP_STOP_CHAR:
      giogod->scope--;

      giogod->lastByte = 0;
      greturn gioGodTypeGROUP_STOP;

   case godKEY_VALUE_SEPARATOR_CHAR:
      giogod->lastByte = 0;
      greturn gioGodTypeINTERNAL_KEY_VALUE_SEPARATOR;

   case godSEPARATOR_CHAR:
      giogod->lastByte = 0;
      greturn gioGodTypeSEPARATOR;

   case godARRAY_START_CHAR:
      giogod->scope++;
      giogod->scopeList[giogod->scope].type             = gioGodScopeTypeARRAY;
      giogod->scopeList[giogod->scope].isNiceFormatting = giogod->scopeList[giogod->scope - 1].isNiceFormatting;

      giogod->lastByte = 0;
      greturn gioGodTypeARRAY_START;

   case godGROUP_START_CHAR:
      giogod->scope++;
      giogod->scopeList[giogod->scope].type             = gioGodScopeTypeGROUP;
      giogod->scopeList[giogod->scope].isNiceFormatting = giogod->scopeList[giogod->scope - 1].isNiceFormatting;

      giogod->lastByte = 0;
      greturn gioGodTypeGROUP_START;

   case godBINARY_START_CHAR:
      giogod->lastByte   = 0;
      giogod->value.type = gioGodTypeVALUE_BINARY_START;
      greturn gioGodTypeVALUE_BINARY_START;

   case godSTRING_QUOTE_CHAR:
      giogod->lastByte   = 0;
      giogod->value.type = gioGodTypeVALUE_STRING_START;
      greturn gioGodTypeVALUE_STRING_START;

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
      greturn _GodGetNumber(giogod);

   case godVALUE_INFINITY_CHAR:
      greturn gioGodTypeVALUE_INFINITY;

   case godVALUE_INFINITY_NEGATIVE_CHAR:
      greturn gioGodTypeVALUE_INFINITY_NEGATIVE;

   case godVALUE_MAX_CHAR:
      greturn gioGodTypeVALUE_MAX;

   case godVALUE_MAX_NEGATIVE_CHAR:
      greturn gioGodTypeVALUE_MAX_NEGATIVE;

   case godVALUE_MIN_CHAR:
      greturn gioGodTypeVALUE_MIN;

   case godVALUE_MIN_NEGATIVE_CHAR:
      greturn gioGodTypeVALUE_MIN_NEGATIVE;

   case godVALUE_TRUE_CHAR:
      greturn gioGodTypeVALUE_TRUE;

   case godVALUE_FALSE_CHAR:
      greturn gioGodTypeVALUE_FALSE;

   case godVALUE_NULL_CHAR:
      greturn gioGodTypeVALUE_NULL;
   }

   greturn gioGodTypeERROR_UNEXPECTED_CHAR;
}

/**************************************************************************************************
func: gioGodSetArrayStart
**************************************************************************************************/
grlAPI Gb gioGodSetArrayStart(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbTRUE;

   greturnFalseIf(!_GodSetByte(giogod, (Gn1) godARRAY_START_CHAR));

   giogod->scope++;
   giogod->scopeList[giogod->scope].type             = gioGodScopeTypeARRAY;
   giogod->scopeList[giogod->scope].isNiceFormatting = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetArrayStop
**************************************************************************************************/
grlAPI Gb gioGodSetArrayStop(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod     ||
      giogod->scope == 0);

   giogod->scopeList[giogod->scope].type = gioGodScopeTypeNONE;
   giogod->scope--;

   giogod->isFirstItem = gbFALSE;

   greturnFalseIf(!_GodSetByte(   giogod, (Gn1) godARRAY_STOP_CHAR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetKey
**************************************************************************************************/
grlAPI Gb gioGodSetKey(GioGod * const giogod, Gchar1 const * const key)
{
   Gi4 index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod     ||
      !key);

   greturnFalseIf(!gioGodSetSeparator(giogod));

   giogod->isFirstItem = gbFALSE;

   loopCount(index)
   {
      breakIf(key[index] == 0);

      greturnFalseIf(
         key[index] == godKEY_VALUE_SEPARATOR_CHAR ||
         key[index] == godSEPARATOR_CHAR);

      greturnFalseIf(!_GodSetBuffer(giogod, 1, (Gn1 *) &key[index]));
   }

   giogod->isKeySet = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetGroupStart
**************************************************************************************************/
grlAPI Gb gioGodSetGroupStart(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbTRUE;

   greturnFalseIf(!_GodSetByte(giogod, (Gn1) godGROUP_START_CHAR));

   giogod->scope++;
   giogod->scopeList[giogod->scope].type             = gioGodScopeTypeGROUP;
   giogod->scopeList[giogod->scope].isNiceFormatting = giogod->scopeList[giogod->scope - 1].isNiceFormatting;

   greturnFalseIf(!_GodSetNewLine(giogod));
   greturnFalseIf(!_GodSetIndent( giogod));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetGroupStop
**************************************************************************************************/
grlAPI Gb gioGodSetGroupStop(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod     ||
      giogod->scope == 0);

   giogod->scopeList[giogod->scope].type = gioGodScopeTypeNONE;
   giogod->scope--;

   giogod->isFirstItem = gbFALSE;

   greturnFalseIf(!_GodSetNewLine(giogod));
   greturnFalseIf(!_GodSetIndent( giogod));
   greturnFalseIf(!_GodSetByte(   giogod, (Gn1) godGROUP_STOP_CHAR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetIsNiceFormatting

Creating a new write will default to minimal formatting.  To turn on nice formatting you need to
call this function.  You can turn it off after starting a new array or new object if not longer
desired.  New arrays and groups will inherit from the parent array or group.
**************************************************************************************************/
grlAPI void gioGodSetIsNiceFormatting(GioGod * const giogod, Gb const value)
{
   genter;

   greturnIf(
      !_isStarted ||
      !giogod);

   giogod->scopeList[giogod->scope].isNiceFormatting = value;

   greturn;
}

/**************************************************************************************************
func: gioGodSetSeparator
**************************************************************************************************/
grlAPI Gb gioGodSetSeparator(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if (!giogod->isFirstItem)
   {
      greturnFalseIf(!_GodSetByte(   giogod, (Gn1) godSEPARATOR_CHAR));
      greturnFalseIf(!_GodSetNewLine(giogod));
      greturnFalseIf(!_GodSetIndent( giogod));
   }

   giogod->isFirstItem = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueBin
**************************************************************************************************/
grlAPI Gb gioGodSetValueBin(GioGod * const giogod, Gcount const count, Gn1 const * const value)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod        ||
      !value);

   greturnFalseIf(!gioGodSetValueBinStart(giogod));
   forCount(index, count)
   {
      greturnFalseIf(!gioGodSetValueBinByte(giogod, value[index]));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueBinByte
**************************************************************************************************/
grlAPI Gb gioGodSetValueBinByte(GioGod * const giogod, Gn1 const value)
{
   Gchar1 letters[] = "0123456789ABCDEF";
   Gn1  output[2];

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   output[0] = letters[value >> 4];
   output[1] = letters[value & 0x0F];

   greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) output));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueBinStart
**************************************************************************************************/
grlAPI Gb gioGodSetValueBinStart(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   greturnFalseIf(!_GodSetByte(giogod, (Gn1) godBINARY_START_CHAR));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueB
**************************************************************************************************/
grlAPI Gb gioGodSetValueB(GioGod * const giogod, Gb const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   if (value == gbTRUE)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_TRUE_CHAR);
   }

   greturn _GodSetByte(giogod, (Gn1) godVALUE_FALSE_CHAR);
}

/**************************************************************************************************
func: gioGodSetValueI
**************************************************************************************************/
grlAPI Gb gioGodSetValueI(GioGod * const giogod, Gi8 const value, Gcount const byteCount)
{
   Gb isMin,
      isMax;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   isMin    =
      isMax = gbFALSE;

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   switch (byteCount)
   {
   case 1:
      if      (value == Gi1MAX)
      {
         isMax = gbTRUE;
      }
      else if (value == Gi1MIN)
      {
         isMin =- gbTRUE;
      }
      break;

   case 2:
      if      (value == Gi2MAX)
      {
         isMax = gbTRUE;
      }
      else if (value == Gi2MIN)
      {
         isMin =- gbTRUE;
      }
      break;

   case 4:
      if      (value == Gi4MAX)
      {
         isMax = gbTRUE;
      }
      else if (value == Gi4MIN)
      {
         isMin =- gbTRUE;
      }
      break;

   case 8:
      if      (value == Gi8MAX)
      {
         isMax = gbTRUE;
      }
      else if (value == Gi8MIN)
      {
         isMin =- gbTRUE;
      }
      break;
   }

   if (isMax)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_CHAR);
   }

   if (isMin)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_NEGATIVE_CHAR);
   }

   greturn _GodSetI(giogod, value);
}

/**************************************************************************************************
func: gioGodSetValueN
**************************************************************************************************/
grlAPI Gb gioGodSetValueN(GioGod * const giogod, Gn8 const value, Gcount const byteCount)
{
   Gb isMax;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   isMax = gbFALSE;

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   switch (byteCount)
   {
   case 1:
      if (value == Gn1MAX)
      {
         isMax = gbTRUE;
      }
      break;

   case 2:
      if (value == Gn2MAX)
      {
         isMax = gbTRUE;
      }
      break;

   case 4:
      if (value == Gn4MAX)
      {
         isMax = gbTRUE;
      }
      break;

   case 8:
      if (value == Gn8MAX)
      {
         isMax = gbTRUE;
      }
      break;
   }

   giogod->isFirstItem = gbFALSE;

   if (isMax)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_CHAR);
   }

   greturn _GodSetN(giogod, value);
}

/**************************************************************************************************
func: gioGodSetValueNull
**************************************************************************************************/
grlAPI Gb gioGodSetValueNull(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   greturn _GodSetByte(giogod, (Gn1) godVALUE_NULL_CHAR);
}

/**************************************************************************************************
func: gioGodSetValueR
**************************************************************************************************/
grlAPI Gb gioGodSetValueR(GioGod * const giogod, Gr8 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   if (isnan(value))
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_NOT_A_NUMBER_CHAR);
   }
   if (isinf(value) && value < 0)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_INFINITY_NEGATIVE_CHAR);
   }
   if (isinf(value))
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_INFINITY_CHAR);
   }
   if (value == -Gr8MAX)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_NEGATIVE_CHAR);
   }
   if (value == Gr8MAX)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_CHAR);
   }
   if (value == -Gr8MIN)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MIN_NEGATIVE_CHAR);
   }
   if (value == Gr8MIN)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MIN_CHAR);
   }

   greturn _GodSetR(giogod, value);
}

/**************************************************************************************************
func: gioGodSetValueR4
**************************************************************************************************/
grlAPI Gb gioGodSetValueR4(GioGod * const giogod, Gr4 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   if (isnan(value))
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_NOT_A_NUMBER_CHAR);
   }
   if (isinf(value) && value < 0)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_INFINITY_NEGATIVE_CHAR);
   }
   if (isinf(value))
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_INFINITY_CHAR);
   }
   if (value == -Gr4MAX)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_NEGATIVE_CHAR);
   }
   if (value == Gr4MAX)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MAX_CHAR);
   }
   if (value == -Gr4MIN)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MIN_NEGATIVE_CHAR);
   }
   if (value == Gr4MIN)
   {
      greturn _GodSetByte(giogod, (Gn1) godVALUE_MIN_CHAR);
   }

   greturn _GodSetR4(giogod, value);
}

/**************************************************************************************************
func: gioGodSetValueStr
**************************************************************************************************/
grlAPI Gb gioGodSetValueStr(GioGod * const giogod, Gchar1 const * const str)
{
   Gindex index;

   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod        ||
      !str);

   greturnFalseIf(!gioGodSetValueStrStart(giogod));
   loopCount(index)
   {
      breakIf(str[index] == 0);

      greturnFalseIf(!gioGodSetValueStrLetter(giogod, str[index]));
   }
   greturnFalseIf(!gioGodSetValueStrStop(giogod));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueStrLetter
**************************************************************************************************/
grlAPI Gb gioGodSetValueStrLetter(GioGod * const giogod, Gchar1 const value)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   switch (value)
   {
   case godSTRING_QUOTE_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_QUOTE_STR));
      break;

   case godSTRING_ESCAPE_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_BACK_SLASH_STR));
      break;

   case godBACKSPACE_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_BACKSPACE_STR));
      break;

   case godFORMFEED_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_FORMFEED_STR));
      break;

   case godSPACE_NEWLINE_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_NEWLINE_STR));
      break;

   case godSPACE_CARRIAGE_RETURN_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_CARRIAGE_RETURN_STR));
      break;

   case godSPACE_TAB_CHAR:
      greturnFalseIf(!_GodSetBuffer(giogod, 2, (Gn1 *) godSTRING_ESCAPE_TAB_STR));
      break;

   default:
      greturnFalseIf(!_GodSetBuffer(giogod, 1, (Gn1 *) &value));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodSetValueStrStart
**************************************************************************************************/
grlAPI Gb gioGodSetValueStrStart(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   if      (giogod->scopeList[giogod->scope].type == gioGodScopeTypeARRAY)
   {
      greturnFalseIf(!gioGodSetSeparator(giogod));
   }
   else if (giogod->scopeList[giogod->scope].type == gioGodScopeTypeGROUP)
   {
      greturnFalseIf(!_GodSetByte(giogod, (Gn1) godKEY_VALUE_SEPARATOR_CHAR));
   }

   giogod->isFirstItem = gbFALSE;

   greturn _GodSetByte(giogod, (Gn1) godSTRING_QUOTE_CHAR);
}

/**************************************************************************************************
func: gioGodSetValueStrStop
**************************************************************************************************/
grlAPI Gb gioGodSetValueStrStop(GioGod * const giogod)
{
   genter;

   greturnFalseIf(
      !_isStarted ||
      !giogod);

   greturn _GodSetByte(giogod, (Gn1) godSTRING_QUOTE_CHAR);
}

/**************************************************************************************************
func: gioGodStart
**************************************************************************************************/
Gb gioGodStart(void)
{
   genter;

   greturnTrueIf(_isStarted);

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGodStop
**************************************************************************************************/
void gioGodStop(void)
{
   genter;

   greturnIf(!_isStarted);

   _isStarted = gbFALSE;
}
