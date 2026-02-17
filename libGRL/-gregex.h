/**************************************************************************************************
file:       gregex
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Regular expression matching, substitution etc.

GRL Regular Expressions are simpler than PERL's or POSIX's.  We don't try to be everything.  These
tools are simple and easy to understand.

A GRL Regular Expression (GRE) is made up of groups.

Character Matching Group:
([!]{match}[{count}])
   {match} is one of the following.
      . - Match any character.
      # - Match digit 0-9.
      a - Match alpha a-zA-Z.
      v - Match alpha and _.
      l - Match any printable letter
      _ - Match white space.

   ! - Invert the match. (Optional)
      . - Not applicable
      # - Match any non-digit
      a - Match any non-alpha
      v - Match any non-alpha and _.
      l - Match any non-printable letter
      _ - Match any non-white space.

   {count} is optional.  If missing, a count = 1.
      0 = 0 or 1 occurances.
      + = 1 or n occurances.
      * = 0 or n occurances.  n can be any number.
      n = 1 or n occurances.  n can be any number.
      # = An actual number not #.  Number of matches to make.

String Matching Group:
([!]=string)
   ! - Invert the match. (Optional)

   = - No other option.
   string - The actual value to match.

Specialty Matching Group:
({match})
   {match} is one of the following.
      { - Match start of line.
      } - Match end of line.
      d - Match number. integer, float, scientific.
      x - Match hex 0x...
      o - Match octal 0...
      v - Match variable name.  First character a-zA-Z_,
          subsequent letters a-zA-z0-9_
**************************************************************************************************/

#pragma once

/**************************************************************************************************
constant:
**************************************************************************************************/
typedef enum
{
   gregexCharCountONE          = 1,
   gregexCharCountONE_OR_N     = Gi4MAX,
   gregexCharCountZERO_OR_ONE  = 0,
   gregexCharCountZERO_OR_N    = (Gi4MAX - 1)
} GregexCharCount;

typedef enum
{
   gregexOpNONE,

   // Character
   gregexOpCHAR_ANY,
   gregexOpCHAR_DIGIT,
   gregexOpCHAR_DIGIT_0,
   gregexOpCHAR_ALPHA,
   gregexOpCHAR_ALPHA_,
   gregexOpCHAR_SPACE,

   // String
   gregexOpSTRING_MATCH,

   // Specialty
   gregexOpLINE_START,
   gregexOpLINE_STOP,
   gregexOpNUMBER,
   gregexOpNUMBER_HEX,
   gregexOpNUMBER_OCTAL,
   gregexOpIDENTIFIER,

   gregexOpCOUNT
} GregexOp;

/**************************************************************************************************
type:
**************************************************************************************************/
#include "GregexGroup.h"
#include "GregexData.h"

typedef GregexData Gregex;
//typedef struct
//{
//   Gs        *str;
//   GsArray   *parsed;
//   Gs        *rexStr;
//   Grex        *rex;
//} Gregex;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gregexCreate(REGEX)   ((Gregex *) gleakCreate(gregexCreate_(REGEX), gsizeof(Gregex)))

grlAPI  Gregex *gregexCreate_(   Gs const * const str);

grlAPI  void    gregexDestroy(   Gregex       * const regex);

grlAPI  Gb      gregexIsStarted( void);

grlAPI  Gb      gregexOptimize(  Gregex const * const regex);

grlAPI  Gb      gregexSearch(    Gregex const * const regex, Gs const * const str, GsArray * const strArray);
grlAPI  Gb      gregexStart(     void);
grlAPI  void    gregexStop(      void);
