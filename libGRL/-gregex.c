/******************************************************************************

file:       gregex
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Regular expression matching, substitution etc.

******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

/******************************************************************************
local:
variable:
******************************************************************************/
static Gb _started = gbFALSE; //lint !e956

/******************************************************************************
prototype:
******************************************************************************/
static Gb             _Parse(         Gregex const * const regex, Gs const * const str);
static GsArray     *_ParseGetParts( Gs const * const str);
static GregexGroup   *_ParsePart(     Gs const * const str);
static Gb             _ParseParts(    Gregex const * const regex, GsArray const * const atemp);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gregexCreate_

Create the regular expression data.
******************************************************************************/
grlAPI Gregex *gregexCreate_(Gs const * const str)
{
   Gregex *regex;

   genter;

   greturnNullIf(!str);

   regex = gregexDataCreate();
   greturnNullIf(!regex);

   // Set up the expression with the given string.
   gregexDataSetString(regex, str); //lint !e534

   stopIf(!_Parse(regex, str));

   gregexDataSetRex(regex, grexCreate(gregexDataGetStringRex(regex), gbFALSE)); //lint !e534
   stopIf(!gregexDataGetRex(regex));

   greturn regex;

STOP:
   // Clean up when something failed.
   gregexDestroy(regex);

   greturn NULL;
}

/******************************************************************************
func: gregexDestroy

Clean up.
******************************************************************************/
grlAPI void gregexDestroy(Gregex * const regex)
{
   genter;

   greturnVoidIf(!regex);

   gregexDataDestroy(regex);

   greturn;
}

/******************************************************************************
func: gregexIsStarted

Are the routines started.
******************************************************************************/
grlAPI Gb gregexIsStarted(void)
{
   genter;

   greturn _started;
}

/******************************************************************************
func: gregexOptimize

Optimize if we are going to reuse this expression many times.
******************************************************************************/
grlAPI Gb gregexOptimize(Gregex const * const regex)
{
   genter;

   greturnFalseIf(!regex);

   greturnFalseIf(!grexOptimize(gregexDataGetRex(regex)));

   greturn gbTRUE;
}

/******************************************************************************
func: gregexSearch

Find the matches.  This function will greturn strings for each group
of the regular expression.

strArray can be NULL which means we don't care for this information.
******************************************************************************/
grlAPI Gb gregexSearch(Gregex const * const regex, Gs const * const str, GsArray * const strArray)
{
   Gindex a,
          result;

   genter;

   result = grexSearch(gregexDataGetRex(regex), str, gbFALSE);
   greturnFalseIf(result <= 0);

   // Fill out the array
   if (strArray)
   {
      forCount(a, result)
      {
         if (!gsArrayAddEnd(strArray, grexGetMatch(regex->rex, a)))
         {
            debugHalt("gsArrayAddLast failed");
            break;
         }
      }
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gregexStart
******************************************************************************/
grlAPI Gb gregexStart(void)
{
   genter;

   greturnFalseIf(!gregexGroupStart());
   greturnFalseIf(!gregexDataStart());

   _started = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: gregexStop
******************************************************************************/
grlAPI void gregexStop(void)
{
   genter;

   gregexDataStop();
   gregexGroupStop();

   _started = gbFALSE;

   greturn;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _Parse

Parse the regular expression string.
******************************************************************************/
static Gb _Parse(Gregex const * const regex, Gs const * const str)
{
   Gb           result;
   GsArray   *parts;

   genter;

   // Get the group strings.
   parts = _ParseGetParts(str);

   // Parse the group strings.
   result = _ParseParts(regex, parts);

   gsArrayForEach(parts, (GrlForEachFunc) gsDestroy); //lint !e534 !e929 !e960
   gsArrayDestroy(parts);

   greturn result;
}

/******************************************************************************
func: _ParseGetParts

Get the bracketed items.
******************************************************************************/
static GsArray *_ParseGetParts(Gs const * const str)
{
   Gindex   loopIndex,
            loopIndex2,
            a;
   Gs      *stemp;
   GsArray *atemp;

   genter;

   atemp = gsArrayCreate((GrlCompareFunc) NULL, gbTRUE); //lint !e960 !e611

   a = 0;

   loop(loopIndex)
   {
      // Find a regular expression group start
      loop(loopIndex2)
      {
         greturnIf(a >= gsGetCount(str), atemp);

         breakIf(gsGetAt(str, a) == (Gc2) L'(');

         a++;
      }
      a++;

      // Find the regular expression group stop.
      // Although wrong, this routine allows for the last
      // ')' to be missing and the string will still be valid.
      stemp = gsCreate();
      loop(loopIndex2)
      {
         breakIf(
            a                 >= gsGetCount(str) ||
            gsGetAt(str, a) == (Gc2) L')'); //lint !e960 !e9007

         // Assign the letter to the string fragment.
         gsAppendC(stemp, gsGetAt(str, a)); //lint !e534
         a++;
      }
      a++;

      gsArrayAddEnd(atemp, stemp); //lint !e534
   }
}

/******************************************************************************
func: _ParsePart

Create the group for the given group string.
******************************************************************************/
static GregexGroup *_ParsePart(Gs const * const str)
{
   Gindex       a;
   GregexGroup *group;
   Gs          *stemp;

   genter;

   //lint -save -e534
   group = gregexGroupCreate();
   greturnNullIf(!group);

   a = 0;

   // invert the match result.
   if (gsGetAt(str, a) == (Gc2) L'!')
   {
      gregexGroupSetIsNegated(group, gbTRUE);
      a++;
   }

   // what to match.
   if      (gsGetAt(str, a) == (Gc2) L'*')
   {
      gregexGroupSetIsNegated(group, gbFALSE);
      gregexGroupSetOperation(group, gregexOpCHAR_ANY);
   }
   else if (gsGetAt(str, a) == (Gc2) L'#')
   {
      gregexGroupSetOperation(group, gregexOpCHAR_DIGIT);
   }
   else if (gsGetAt(str, a) == (Gc2) L'a')
   {
      gregexGroupSetOperation(group, gregexOpCHAR_ALPHA);
   }
   else if (gsGetAt(str, a) == (Gc2) L'l')
   {
      gregexGroupSetOperation(group, gregexOpCHAR_ALPHA_);
   }
   else if (gsGetAt(str, a) == (Gc2) L'_')
   {
      gregexGroupSetOperation(group, gregexOpCHAR_SPACE);
   }
   else if (gsGetAt(str, a) == (Gc2) L'=')
   {
      gregexGroupSetOperation(group, gregexOpSTRING_MATCH);
   }
   else if (gsGetAt(str, a) == (Gc2) L'{')
   {
      gregexGroupSetOperation(group, gregexOpLINE_START);
   }
   else if (gsGetAt(str, a) == (Gc2) L'}')
   {
      gregexGroupSetOperation(group, gregexOpLINE_STOP);
   }
   else if (gsGetAt(str, a) == (Gc2) L'd')
   {
      gregexGroupSetOperation(group, gregexOpNUMBER);
   }
   else if (gsGetAt(str, a) == (Gc2) L'x')
   {
      gregexGroupSetOperation(group, gregexOpNUMBER_HEX);
   }
   else if (gsGetAt(str, a) == (Gc2) L'o')
   {
      gregexGroupSetOperation(group, gregexOpNUMBER_OCTAL);
   }
   else if (gsGetAt(str, a) == (Gc2) L'i')
   {
      gregexGroupSetOperation(group, gregexOpIDENTIFIER);
   }
   else
   {
      //nothing
   }
   a++;

   // Optional information.
   switch (group->operation)
   {
   case gregexOpCHAR_ANY:
   case gregexOpCHAR_DIGIT:
   case gregexOpCHAR_ALPHA:
   case gregexOpCHAR_ALPHA_:
   case gregexOpCHAR_SPACE:
      gregexGroupSetCount(group, gregexCharCountONE);
      if      (gsGetAt(str, a) == (Gc2) L'0')
      {
         gregexGroupSetCount(group, gregexCharCountZERO_OR_ONE);
      }
      else if (gsGetAt(str, a) == (Gc2) L'@')
      {
         gregexGroupSetCount(group, gregexCharCountZERO_OR_N);
      }
      else if (gsGetAt(str, a) == (Gc2) L'n')
      {
         gregexGroupSetCount(group, gregexCharCountONE_OR_N);
      }
      else if ((Gc2) L'1'     <= gsGetAt(str, a) && //lint !e747
               gsGetAt(str, a) <= (Gc2) L'9') //lint !e747 !e960 !e9007
      {
         Gs *number = gsCreateFromSub(str, a, gsSubStrINDEX_END); //lint !e747 !e917
         gregexGroupSetCount(group, (GregexCharCount) gMAX(1, gsGetI(number))); //lint !e666 !e930
         gsDestroy(number);
      }//lint !e953
      else
      {
         //nothing
      }
      break;

   case gregexOpSTRING_MATCH:
      stemp = gsCreateFromSub(str, a, gsSubStrINDEX_END); //lint !e747 !e732
      gregexGroupSetString(group, stemp);
      gsDestroy(stemp);
      break;

   case gregexOpLINE_START:
   case gregexOpLINE_STOP:
   case gregexOpNUMBER:
   case gregexOpNUMBER_HEX:
   case gregexOpNUMBER_OCTAL:
   case gregexOpIDENTIFIER:
      break;
   } //lint !e787
   //lint -restore

   greturn group;
}

/******************************************************************************
func: _ParseParts

For each group parce it's contents.
******************************************************************************/
static Gb _ParseParts(Gregex const * const regex, GsArray const * const atemp)
{
   Gindex             a;
   Gs          const *str;
   Gs                *strRex;
   GregexGroup const *group;

   genter;

   //lint -save -e534
   strRex = gregexDataGetStringRex(regex);

   // For all group strings...
   forCount(a, gsArrayGetCount(atemp))
   {
      // get the string.
      str = gsArrayGetAt(atemp, a);

      // Create a group item.
      group = _ParsePart(str);
      greturnFalseIf(!group);

      // Append the group.
      //gregexGroupArrayAddEnd(gregexDataGetGroupList(regex), group); //lint !e666

      gsAppendC(strRex, '(');
      switch (group->operation)
      {
      case gregexOpCHAR_ANY:
         gsAppendC(strRex, '.');
         goto PARSE_PART_CHAR_COUNT;

      case gregexOpCHAR_DIGIT:
         if (gregexGroupIsNegated(group))
         {
            gsAppendU2(strRex, L"\\D");
         }
         else
         {
            gsAppendU2(strRex, L"\\d");
         }
         goto PARSE_PART_CHAR_COUNT;

      case gregexOpCHAR_ALPHA:
         if (gregexGroupIsNegated(group))
         {
            gsAppendU2(strRex, L"[^[:alpha:]]");
         }
         else
         {
            gsAppendU2(strRex, L"[:alpha:]");
         }
         goto PARSE_PART_CHAR_COUNT;

      case gregexOpCHAR_ALPHA_:
         if (gregexGroupIsNegated(group))
         {
            gsAppendU2(strRex, L"\\W");
         }
         else
         {
            gsAppendU2(strRex, L"\\w");
         }
         goto PARSE_PART_CHAR_COUNT;

      case gregexOpCHAR_SPACE:
         if (gregexGroupIsNegated(group))
         {
            gsAppendU2(strRex, L"\\S");
         }
         else
         {
            gsAppendU2(strRex, L"\\s");
         }
         goto PARSE_PART_CHAR_COUNT;

      case gregexOpSTRING_MATCH:
         gsAppend(strRex, gregexGroupGetString(group));
         goto PARSE_PART_END;

      case gregexOpLINE_START:
         gsAppendC(strRex, '^');
         goto PARSE_PART_END;

      case gregexOpLINE_STOP:
         gsAppendC(strRex, '$');
         goto PARSE_PART_END;

      case gregexOpNUMBER:
         gsAppendU2(strRex, L"[+-]?\\d+\\.\\d+e[+-]?\\d+|[+-]?\\d+\\.\\d+|[+-]?\\d+");
         goto PARSE_PART_END;

      case gregexOpNUMBER_HEX:
         gsAppendU2(strRex, L"0x[0-7a-fA-F]+|0");
         goto PARSE_PART_END;

      case gregexOpNUMBER_OCTAL:
         gsAppendU2(strRex, L"0[0-7]*");
         goto PARSE_PART_END;

      case gregexOpIDENTIFIER:
         gsAppendU2(strRex, L"[[:alpha:]_]?|[[:alpha:]_]\\w*");
         goto PARSE_PART_END;
      } //lint !e787

PARSE_PART_CHAR_COUNT:
      if      (group->count == gregexCharCountONE_OR_N)
      {
         gsAppendC(strRex, '+');
      }
      else if (group->count == gregexCharCountZERO_OR_ONE)
      {
         gsAppendC(strRex, '?');
      }
      else if (group->count == gregexCharCountZERO_OR_N)
      {
         gsAppendC(strRex, '*');
      }
      else if (group->count > 1) //lint !e641
      {
         gsAppendC(strRex, '{');
         gsAppendN(   strRex, gregexGroupGetCount(group)); //lint !e747 !e641
         gsAppendC(strRex, ',');
         gsAppendN(   strRex, gregexGroupGetCount(group)); //lint !e747 !e641
         gsAppendC(strRex, '}');
      }
      else
      {
         //nothing;
      }

PARSE_PART_END:
      gsAppendC(strRex, ')');
   }
   //lint -restore

   greturn gbTRUE;
}
