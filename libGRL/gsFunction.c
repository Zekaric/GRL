/**************************************************************************************************
file:       gs
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
variable:
**************************************************************************************************/
static Gs      *_whitespace   = NULL;

/**************************************************************************************************
function:
**************************************************************************************************/
#if 0
static Gs      *_FormatI(        Gi const i,     Char const * const format);
static Gs      *_FormatN(        Gn const n,     Char const * const format);
static Gs      *_FormatR(        Gr const r,     Char const * const format);
static Gs      *_FormatString(   Gs * const str, Char const * const format);

static Gcount   _GetLength(      Gp const * const ptr, gsParamType const type);
#endif

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gsAppend

Add a Gs to the string.

param:
str, add
   Gs *, Gs *
   in/out, in
   The strings.
**************************************************************************************************/
grlAPI Gs *gsAppend(Gs * const str, Gs const * const value)
{
   Gcount count,
          length;

   genter;

   greturnNullIf(
      !str ||
      !value);

   // New size of the string.
   length = gsGetCount(str);
   count  = length + gsGetCount(value);

   // Resize the buffer.
   greturnNullIf(!gsSetCount(str, count));

   // Copy the data over.
   greturnNullIf(!gsCopyFrom(str, length, value, gsGetCount(value), 0));

   greturn str;
}

#if 0
/**************************************************************************************************
FUNC: gsAppendFormat

Format is the same as an printf format.  The printf format is as
follows.

%[flags][width][.precision]I64(type)

For this function...

Valid [flags] are:
-   : Left align the result.
See MSDN Help doc for further information.

Valid [width] is non negative.  It never causes a truncation and
represents the 'minimum' length of the string.  '*' is normally
an option but not with this function.  width must be a valid
positive number.
See MSDN Help doc for further information.

Valid [precision] N/A here.

Always provide I64 for this case.

Valid (type) values (not optional like the other options above) are:
s   : Unicode string.  (lowercase s is the Only option.)
**************************************************************************************************/
grlAPI Gs *gsAppendFormat(Gs * const str, Gs const * const value, Char const * const format)
{
   Gs *atemp,
      *result;

   genter;

   greturnNullIf(
      !str   ||
      !value ||
      !format);

   atemp = gsClocFrom(value);
   greturnNullIf(!atemp);

   result = gsAppend(str, _FormatString(atemp, format));

   gsDloc(atemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendA
**************************************************************************************************/
grlAPI Gs *gsAppendA(Gs * const str, Char const * const cstr)
{
   Gindex a;
   Gcount count,
          length,
          clength;

   genter;

   greturnNullIf(
      !str ||
      !cstr);

   // Nothing to add, append is ok.
   clength = (Gcount) strlen((char *) cstr);
   greturnValIf(!clength, str);

   // New size of the string.
   length = gsGetCount(str);
   count  = length + clength;

   // Resize the buffer.
   greturnNullIf(!gsSetCount(str, count));

   // Copy the data over.
   forCount(a, clength)
   {
      greturnNullIf(!gsUpdateAt(str, length + a, cstr[a]));
   }

   greturn str;
}

/**************************************************************************************************
func: gsAppendGchar1
**************************************************************************************************/
grlAPI Gs *gsAppendGchar1(Gs * const str, Gchar1 const * const cstr)
{
   Gcount          count;
   Gchar1 const   *cp;
   Gchar           letter;

   genter;

   greturnNullIf(!str);

   greturnValIf(!cstr, str);

   cp = cstr;
   loop
   {
      count = gcharFromGchar1(*cp, *(cp + 1), *(cp + 2), *(cp + 3), &letter);
      gsAddEnd(str, letter);

      cp += count;
      breakIf(*cp == 0)
   }

   greturn str;
}

#if 0
/**************************************************************************************************
** FUNC: gsAppendFormatA
**************************************************************************************************/
grlAPI Gs *gsAppendFormatA(Gs * const str, Char const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp = gsClocFromA(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendLetter
**************************************************************************************************/
grlAPI Gs *gsAppendLetter(Gs * const str, Gchar const letter)
{
   genter;

   greturnNullIf(!gsAddEnd(str, letter));

   greturn str;
}

#if 0
/**************************************************************************************************
func: gsAppendCharFormat
**************************************************************************************************/
grlAPI Gs *gsAppendCharFormat(Gs * const str, Gc2 const gc, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str ||
      !gc  ||
      !format);

   stemp = gsCloc();
   greturnNullIf(!stemp);

   result = NULL;
   if (gsAppendC( stemp, gc) &&
       gsToFormat(stemp, format))
   {
      result = gsAppend(str, stemp);
   }

   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendI
**************************************************************************************************/
grlAPI Gs *gsAppendI(Gs * const str, Gi const i)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_i64toa_s(i, (char *) ctemp, (size_t) 80, 10) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

#if 0
/**************************************************************************************************
func: gsAppendIFormat

Format is the same as an printf format.  The printf format is as
follows.

   %[flags][width][.precision]I64(type)

For this function...

Valid [flags] are:
   -   : Left align the result.
   +   : Prefix with a + if positive.
   0   : Zero pad not applicable.
   ' ' : (Blank) reserve a space for the sign.  If positive,
         leave a blank.
   #   : Prefix Octal and Hex numbers with 0 and 0x respectively.
   See MSDN Help doc for further information.

Valid [width] is non negative.  It never causes a truncation and
   represents the 'minimum' length of the string.  '*' is normally
   an option but not with this function.  width must be a valid
   positive number.
   See MSDN Help doc for further information.

Valid [precision] is non negative.  This will pad in zeros on the
   left of the integer.
   See MSDN Help doc for further information.

Always provide I64 for this case.

Valid (type) values (not optional like the other options above) are:
   d   : Signed integer.
   o   : Unsigned octal.
   u   : Unsigned integer.
   x   : Unsigned hexadecimal.  Lower case letters.
   X   : Same as X with Upper case letters.
**************************************************************************************************/
grlAPI Gs *gsAppendIFormat(Gs * const str, Gi8 const i, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str ||
      !format);

   stemp = _FormatI(i, format);
   greturnNullIf(!stemp);

   result = gsAppend(str, stemp);

   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendN
**************************************************************************************************/
grlAPI Gs *gsAppendN(Gs * const str, Gn const n)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_ui64toa_s(n, (char *) ctemp, (size_t) 80, 10) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

#if 0
/**************************************************************************************************
func: gsAppendNformat

Format is the same as an printf format.  The printf format is as
follows.

   %[flags][width][.precision]I64(type)

For this function...

Valid [flags] are:
   -   : Left align the result.
   +   : Prefix with a + if positive.
   0   : Zero pad not applicable.
   ' ' : (Blank) reserve a space for the sign.  If positive,
         leave a blank.
   #   : Prefix Octal and Hex numbers with 0 and 0x respectively.
   See MSDN Help doc for further information.

Valid [width] is non negative.  It never causes a truncation and
   represents the 'minimum' length of the string.  '*' is normally
   an option but not with this function.  width must be a valid
   positive number.
   See MSDN Help doc for further information.

Valid [precision] is non negative.  This will pad in zeros on the
   left of the integer.
   See MSDN Help doc for further information.

Always provide I64 for this case.

Valid (type) values (not optional like the other options above) are:
   d   : Signed integer.
   o   : Unsigned octal.
   u   : Unsigned integer.
   x   : Unsigned hexadecimal.  Lower case letters.
   X   : Same as X with Upper case letters.
**************************************************************************************************/
grlAPI Gs *gsAppendNFormat(Gs * const str, Gn const n, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str ||
      !format);

   stemp = _FormatN(n, format);
   greturnNullIf(!stemp);

   result = gsAppend(str, stemp);

   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendR
**************************************************************************************************/
grlAPI Gs *gsAppendR(Gs * const str, Gr const r)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_gcvt_s((char *) ctemp, (size_t) 80, r, 15) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

#if 0
/**************************************************************************************************
func: gsAppendRformat

Format is the same as an printf format.  The printf format is as
follows.

   %[flags][width][.precision](type)

For this function...

Valid [flags] are:
   -   : Left align the result.
   +   : Prefix with a + if positive.
   0   : Zero pad not applicable.
   ' ' : (Blank) reserve a space for the sign.  If positive,
         leave a blank.
   #   : Prefix Octal and Hex numbers with 0 and 0x respectively.
   See MSDN Help doc for further information.

Valid [width] is non negative.  It never causes a truncation and
   represents the 'minimum' length of the string.  '*' is normally
   an option but not with this function.  width must be a valid
   positive number.
   See MSDN Help doc for further information.

Valid [precision] is non negative.  The max. number of decimal places after
   the decimal.
   See MSDN Help doc for further information.

Valid (type) values (not optional like the other options above) are:
   e   : Scientific notation always.
   E   : Same as e but the exponent 'e' is capitalized.
   f   : The number expanded out.
   g   : f or e is used when appropriate.
   G   : f or E is used when appropriate.
   a   : Display the number in hexidecimal form.
   A   : Same as a but with a P instead of p.
   See MSDN Help doc for further information.
**************************************************************************************************/
grlAPI Gs *gsAppendRFormat(Gs * const str, Gr const r, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str ||
      !format);

   stemp = _FormatR(r, format);
   greturnNullIf(!stemp);

   result = gsAppend(str, stemp);

   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendSub

Copy a substring starting at the letter at index start, and ending at the letter before end.  This
will not include the letter found at end.  If you want to include all the letters till the end you
can pass in GindexMAX.
**************************************************************************************************/
grlAPI Gs *gsAppendSub(Gs * const str, Gs const * const value, Gindex const start,
   Gindex const end)
{
   Gindex a,
          startTemp,
          endTemp;

   genter;

   greturnNullIf(
      !str        ||
      !value      ||
      start > end);

   greturnValIf(end == 0, str);

   // fix bad input.
   startTemp = gMIN(gsGetCount(value), start);
   endTemp   = gMIN(gsGetCount(value), end);

   a = gsGetCount(str);
   greturnNullIf(!gsSetCount(str, a + endTemp - startTemp));

   // Set the string.
   greturnNullIf(!gsCopyFrom(str, a, value, endTemp - startTemp, startTemp));

   greturn str;
}

#if 0
/**************************************************************************************************
** FUNC: gsAppendSubFormat
**************************************************************************************************/
grlAPI Gs *gsAppendSubFormat(Gs * const str, Gs const * const value, Gindex const start,
   Gindex const end, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str   ||
      !value ||
      !format);

   stemp = _FormatString(gsClocFromSub(value, start, end), format);
   greturnNullIf(!stemp);

   result = gsAppend(str, stemp);

   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsAppendFormatU1
**************************************************************************************************/
grlAPI Gs *gsAppendFormatU1(Gs * const str, Gc1 const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
        *result;

   genter;

   stemp = gsClocFromU1(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));

   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
func: gsAppendU2
**************************************************************************************************/
grlAPI Gs *gsAppendU2(Gs * const str, Gc2 const * const cstr)
{
   Gindex index;
   Gcount clength;
   Gc     unicodeCodePoint;

   genter;

   greturnNullIf(!str);

   greturnValIf(!cstr, str);

   clength = (Gcount) wcslen(cstr);
   greturnValIf(!clength, str);

   // Copy the data over.
   forCount(index, clength)
   {
      index += gcharFromCharW(&cstr[index], &unicodeCodePoint) - 1;
      gsAppendC(str, unicodeCodePoint);
      greturnNullIf(!str);
   }

   greturn str;
}

/**************************************************************************************************
** FUNC: gsAppendFormatU2
**************************************************************************************************/
grlAPI Gs *gsAppendFormatU2(Gs * const str, Gc2 const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
        *result;

   genter;

   greturnNullIf(
      !str  ||
      !cstr ||
      !format);

   stemp = gsClocFromU2(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));

   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsAppendFormatted

formatType should be gsParamA, gsParaS or gsParaS_DLOC.  Anything else will result in a failure.

The next paramter will be the format string.  This should be an Char * or Gs * depending on the
formatType.

After format, you have key value pairs of variables.

gsParamType keyType, Key, gsParamType valueType, Value,

Depending on type above value is one of the following.

Type (Gc2)                          Value
gsParamTypeA      - ascii        Char *
gsParamTypeS      - Gs           Gs   *
gsParamTypeS_DLOC - Gs           Gs   * but will be Dloc ed after call.
gsParamTypeI      - integer      Gi
gsParamTypeN      - natural      Gn

Terminate with a NULL value for gsParamTypeNONE.

Example:

gsAppendFormated(
   stemp,
   gsParamTypeA, "This is a %KEY% to replace with No Key! %KEY% will also be replaced.  $(OTHER) will be something else.",
   gsParamTypeA, "%KEY%",    gsParamTypeA, (Char *) "Hokey",
   gsParamTypeA, "$(OTHER)", gsParamTypeI, (Gi)     1024,
   gsParamTypeNONE);
**************************************************************************************************/
grlAPI Gs *gsAppendFormatted(Gs * const str, GsParamType const formatType, ...)
{
   Gs  const   *search,
               *replace;
   Gs          *stemp,
               *result;
   GsParamType  typeTemp;
   va_list      args;
   GtempScope  *tempScope;

   genter;

   greturnNullIf(!str);

   search  = NULL;
   replace = NULL;
   stemp   = NULL;

   tempScope = gtempEnter();
   greturnNullIf(!tempScope);

   va_start(args, formatType);

   // Get the format string.
   switch (formatType)
   {
   case gsParamTypeA:
      stemp = gtempGs(tempScope, gsAppendA(gsCloc(), va_arg(args, Char *)));
      break;

   case gsParamTypeS:
      stemp = gtempGs(tempScope, gsSet(gsCloc(), va_arg(args, Gs *)));
      break;

   case gsParamTypeS_DLOC:
      stemp = gtempGs(tempScope, va_arg(args, Gs *));
      break;

   default:
      stop();
   }

   // Do the variable substitution.
   loop
   {
      typeTemp = va_arg(args, GsParamType);
      breakIf(typeTemp == gsParamTypeNONE);

      switch (typeTemp)
      {
      case gsParamTypeA:
         search = gtempGs(tempScope, gsClocFromA(va_arg(args, Char *)));
         break;

      case gsParamTypeS:
         search =                    va_arg(args, Gs *);
         break;

      case gsParamTypeS_DLOC:
         search = gtempGs(tempScope, va_arg(args, Gs *));
         break;

      default:
         stop();
      }
      stopIf(!search);

      typeTemp = va_arg(args, GsParamType);
      switch (typeTemp)
      {
      case gsParamTypeA:
         replace = gtempGs(tempScope, gsClocFromA(va_arg(args, Char *)));
         break;

      case gsParamTypeS:
         replace = va_arg(args, Gs *);
         break;

      case gsParamTypeS_DLOC:
         replace = gtempGs(tempScope, va_arg(args, Gs *));
         break;

      case gsParamTypeI:
         replace = gtempGs(tempScope, gsClocFromI(va_arg(args, Gi)));
         break;

      case gsParamTypeN:
         replace = gtempGs(tempScope, gsClocFromN(va_arg(args, Gn)));
         break;

      case gsParamTypeR:
         replace = gtempGs(tempScope, gsClocFromR(va_arg(args, Gr)));
         break;
      }

      // Do the search and replace.
      stemp = gsFindAndReplace(stemp, search, replace, NULL);
   }

STOP:
   result = gsAppend(str, stemp);

   // Clean up.
   va_end(args);

   gtempExit(tempScope);

   greturn result;
}

/**************************************************************************************************
func: gsAppendParams

Appends a bunch of Gs * together.
**************************************************************************************************/
grlAPI Gs *gsAppendParams(Gs * const str, ...)
{
   Gs const *stemp;
   va_list   args;

   genter;

   greturnValIf(!str, str);

   va_start(args, str);

   loop
   {
      // NULL means end of the chain.
      stemp = (Gs *) va_arg(args, Gs *);
      breakIf(!stemp);

      // Do the search and replace.
      greturnNullIf(!gsAppend(str, stemp));
   }

   va_end(args);

   greturn str;
}

#if 0
/**************************************************************************************************
func: gsAppendRandom
**************************************************************************************************/
grlAPI Gs *gsAppendRandom(Gs * const str)
{
   Gi4 count,
       index,
       letter;

   genter;

   count = grandomGetN(NULL) % 20;

   forCount(index, count)
   {
      letter = grandomGetN(NULL) % 62;

      // upper case letter.
      if (0 <= letter && letter < 26)
      {
         gsAppendC(str, (Gchar) (L'A' + letter));
         continue;
      }

      letter -= 26;

      // lower case letter.
      if (0 <= letter && letter < 26)
      {
         gsAppendC(str, (Gchar) (L'a' + letter));
         continue;
      }

      letter -= 26;

      // number
      gsAppendC(str, (Gchar) (L'0' + letter));
   }

   greturn str;
}
#endif

/**************************************************************************************************
func: gsCompare*
**************************************************************************************************/
grlAPI Gcompare gsCompare(Gs const * const as, Gs const * const bs)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gchar  a,
          b;

   genter;

   greturnValIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, acount)
   {
      breakIf(index >= bcount);

      a = gsGetAt(as, index);
      b = gsGetAt(bs, index);

      greturnValIf(a < b, gcompareLESS_THAN);
      greturnValIf(a > b, gcompareGREATER_THAN);
   }

   greturnValIf(acount < bcount, gcompareLESS_THAN);
   greturnValIf(acount > bcount, gcompareGREATER_THAN);

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gsCompareA
**************************************************************************************************/
grlAPI Gcompare gsCompareA(Gs const * const as, Char const * const bs)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gchar  a,
          b;

   genter;

   greturnValIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = charGetCount(bs);

   forCount(index, acount)
   {
      breakIf(index >= bcount);

      a = gsGetAt(as, index);
      b = bs[index];

      greturnValIf(a < b, gcompareLESS_THAN);
      greturnValIf(a > b, gcompareGREATER_THAN);
   }

   greturnValIf(acount < bcount, gcompareLESS_THAN);
   greturnValIf(acount > bcount, gcompareGREATER_THAN);

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gsCompareContainer
**************************************************************************************************/
grlAPI Gcompare gsCompareContainer(Gv const * const av, Gv const * const bv)
{
   genter;

   greturn gsCompare(gvpGetS(av), gvpGetS(bv));
}

#if 0
/**************************************************************************************************
** FUNC: gsCompareA
**************************************************************************************************/
grlAPI Gcompare gsCompareA(Gs const * const a, Char const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromA(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareU1
**************************************************************************************************/
grlAPI Gcompare gsCompareU1(Gs const * const a, Gc1 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU1(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareU2
**************************************************************************************************/
grlAPI Gcompare gsCompareU2(Gs const * const a, Gc2 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU2(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsCompareBase

Compare the base strings together.  Ignores local so order may not
honour dictionary/telephone/region order.  Read up on this at
unicode.org
**************************************************************************************************/
grlAPI Gcompare gsCompareBase(Gs const * const as, Gs const * const bs)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gchar  a,
          b;

   genter;

   greturnValIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, acount)
   {
      breakIf(index >= bcount);

      a = gcharToLowerCase(gsGetAt(as, index));
      b = gcharToLowerCase(gsGetAt(bs, index));

      greturnValIf(a < b, gcompareLESS_THAN);
      greturnValIf(a > b, gcompareGREATER_THAN);
   }

   greturnValIf(acount < bcount, gcompareLESS_THAN);
   greturnValIf(acount > bcount, gcompareGREATER_THAN);

   greturn gcompareEQUAL;
}

/**************************************************************************************************
func: gsCompareBaseContainer
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseContainer(Gv const * const av, Gv const * const bv)
{
   genter;

   greturn gsCompareBase(gvpGetS(av), gvpGetS(bv));
}

#if 0
/**************************************************************************************************
** FUNC: gsCompareBaseA
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseA(Gs const * const a, Char const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromA(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareBaseU1
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseU1(Gs const * const a, Gc1 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU1(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareBaseU2
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseU2(Gs const * const a, Gc2 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU2(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsCompareBaseCount

Compare the base strings together.  Ignores locale so order may not honour dictionary/telephone/
region order.  Read up on this at unicode.org

Compares first Count letters.
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseCount(Gs const * const as, Gs const * const bs, Gcount const count)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gchar  a,
          b;

   genter;

   greturnValIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, gMIN(count, acount))
   {
      breakIf(index >= bcount);

      a = gcharToLowerCase(gsGetAt(as, index));
      b = gcharToLowerCase(gsGetAt(bs, index));

      greturnValIf(a < b, gcompareLESS_THAN);
      greturnValIf(a > b, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

#if 0
/**************************************************************************************************
** FUNC: gsCompareBaseCountA
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseCountA(Gs const * const a, Char const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromA(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareBaseCountU1
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseCountU1(Gs const * const a, Gc1 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU1(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareBaseCountU2
**************************************************************************************************/
grlAPI Gcompare gsCompareBaseCountU2(Gs const * const a, Gc2 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU2(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsCompareCount
**************************************************************************************************/
grlAPI Gcompare gsCompareCount(Gs const * const as, Gs const * const bs, Gcount const count)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gchar  a,
          b;

   genter;

   greturnValIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, gMIN(count, acount))
   {
      breakIf(index >= bcount);

      a = gsGetAt(as, index);
      b = gsGetAt(bs, index);

      greturnValIf(a < b, gcompareLESS_THAN);
      greturnValIf(a > b, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

#if 0
/**************************************************************************************************
** FUNC: gsCompareCountA
**************************************************************************************************/
grlAPI Gcompare gsCompareCountA(Gs const * const a, Char const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromA(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareCountU1
**************************************************************************************************/
grlAPI Gcompare gsCompareCountU1(Gs const * const a, Gc1 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU1(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsCompareCountU2
**************************************************************************************************/
grlAPI Gcompare gsCompareCountU2(Gs const * const a, Gc2 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnValIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsClocFromU2(b);
   greturnValIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsClocA

Cloc the Ascii string.  Assumes string is ASCII.
**************************************************************************************************/
grlAPI Char *gsClocA_(Gs const * const str)
{
   Gindex index;
   Gcount count;
   Char  *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.
   stemp = gmemClocTypeArray(Char, gsGetCount(str) + 1);
   greturnNullIf(!stemp);

   // copy the letters over.  Will not convert to UTF8.  Assumes letters are ASCII.
   count = gsGetCount(str);
   forCount(index, count)
   {
      stemp[index] = (Char) gsGetAt(str, index);
   }

   greturn stemp;
}

/**************************************************************************************************
func: gsClocGchar1
**************************************************************************************************/
grlAPI Gchar1 *gsClocChar1_(Gs const * const str)
{
   Gchar1    la,
             lb,
             lc,
             ld;
   Gindex    index,
             b;
   Gcount    lsize,
             count;
   Gchar1   *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.  Oversized but for worst case it'll do.
   count = gsGetCount(str);
   stemp = gmemClocTypeArray(Gchar1, count * 4 + 1);
   greturnNullIf(!stemp);

   // copy the letters over.
   b = 0;
   forCount(index, count)
   {
      lsize = gchar1FromGchar(gsGetAt(str, index), &la, &lb, &lc, &ld);

                        stemp[b++] = la;
      if (lsize >= 2) { stemp[b++] = lb; }
      if (lsize >= 3) { stemp[b++] = lc; }
      if (lsize >= 4) { stemp[b++] = ld; }
   }

   greturn stemp;
}

/**************************************************************************************************
func: gsClocChar2_
**************************************************************************************************/
grlAPI Gchar2 *gsClocChar2_(Gs const * const str)
{
   Gchar2    la,
             lb;
   Gi4       index,
             b,
             lsize,
             count;
   Gchar2   *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.  Oversized but for worst case it'll do.
   count = gsGetCount(str);
   stemp = gmemClocTypeArray(Gchar2, count * 2 + 1);
   greturnNullIf(!stemp);

   // copy the letters over.
   b = 0;
   forCount(index, count)
   {
      lsize = gchar2FromGchar(gsGetAt(str, index), &la, &lb);

                        stemp[b++] = la;
      if (lsize == 2) { stemp[b++] = lb; }
   }

   greturn stemp;
}

/***********************************************************************************************************
 * FUNC: gsClocJoin_
 *
 * Essential an inverse of gsClocSplit(). This takes a garray of
 * Gs's and joins them "with" the characters.
 *
 * For example, if your GvArray contained: ["a", "b", "c"] and you
 * joined with ";". Then you would get a result string: "a;b;c".
 *
 * An empty GvArray will result in an blank string that satisfies
 * gsIsEmpty().
 *
 * PARAM:
 * stringvec
 *    GvArray *
 *    in
 *    A vector of UStr's to join, value must not be NULL and must contain
 *    all valid Gss.
 *
 * with
 *    Char *
 *    in
 *    characters you wish to use to join the string, use "" if you
 *    do not want any characters in your string, this value
 *    must not be NULL.
 *
 * return:
 * Gs *
 *    A new string with all the strings in the vector joined together
 *    with the character string as glue.
 *
 *    NULL is greturned if there is no more memory.
 ***********************************************************************************************************/
grlAPI Gs *gsClocJoin_(GvArray const * const v, Gs const * const sep)
{
   Gs              *joined;
   Gs        const *stemp;
   Gcount           numstrings;
   Gindex           laststring,
                    i;
   GvArray   const *vector;

   genter;

   greturnNullIf(!v);

   vector = v;

   joined = gsCloc();
   greturnNullIf(!joined);

   // For each string in the string list, clone the string,
   // append the character seperator and then append the
   // result to the joined string.
   numstrings = gvArrayGetCount(vector);
   laststring = numstrings - 1;

   for (i = 0; i != numstrings; ++i )
   {
      stemp = gvGetS(gvArrayGetAt(vector, i));
      if (stemp == NULL)
      {
         gsDloc(joined);
         joined = NULL;
         greturn NULL;
      }

      greturnNullIf(!gsAppend(joined, stemp));
      if (i != laststring)
      {
         greturnNullIf(!gsAppend(joined, sep));
      }
   }

   greturn joined;
}

/**************************************************************************************************
func: gsClocSplit_

Takes a string an splits it into a vector of sub-strings based
on the characters passed in.

For example, the following string,

"this;is;a!test;would"

Will greturn,

"this", "is", "a", "test", "would"

Provided the delimiters = ";!"

Example:
A quick little example of spliting a string on ";".

int      i;
Gs    *str   = gsClocFromA("this;is;a;test");
GvArray *split = gsClocSplit(str, ";");

for (i = 0 ; i != garrayGetCount(split); ++i)
{
Gs *token = (Gs *) garrayGet(split, i);
printf("token is: %s.\n", gsGetA(token));
}
garrayForEach(split, gsDloc);
garrayDloc(split);

Note that we destroy the data prior to destroying the
vector container.

PARAM:
str
Gs *
in
string to split, input can not be NULL.

delimiters
Gs *
in
character string to use to make splits, input can not be NULL.

return:
GvArray *
An GvArray, N elements in length, where N is equal to the number
of substrings split off the the orginal.

Make sure you use garrayForEach(v, gsDloc) on the
greturned vector. See USAGE.

Some example calls,
gsClocSplit("this,is,a,test", ",") -> ["this", "is", "a", "test"]
gsClocSplit("this;is;", ";")       -> ["this", "is", ""]
gsClocSplit("!!!", "!")            -> ["", "", "", ""]
gsClocSplit("", ",")               -> [""]

NULL is greturned if there is no more memory, otherwise a garray
is always greturned. The length of the garray indicates success
or failure.  Note that an empty vector is defined by garrayIsEmpty().
**************************************************************************************************/
grlAPI GvArray *gsClocSplit_(Gs const * const str, Gchar const letter)
{
   Gindex   index;
   GvArray *slist;
   Gs      *substr;

   genter;

   greturnNullIf(
      !str ||
      !letter);

   slist = gvArrayCloc("Gs Array", NULL, gbTRUE);
   greturnNullIf(!slist);

   // Non recursive despite the function name.
   forCount(index, gsGetCount(str))
   {
      // Find the substrings;
      substr = gsCloc();
      for (; index < gsGetCount(str); index++)
      {
         breakIf(gsGetAt(str, index) == letter);

         greturnNullIf(!gsAppendLetter(substr, gsGetAt(str, index)));
      }
      greturnNullIf(!gvArrayAddEnd(slist, gvFromP(substr)));
   }

   greturn slist;
}

#if 0
/**************************************************************************************************
** FUNC: gsClocJoinA_
**************************************************************************************************/
grlAPI Gs *gsClocJoinA_(GvArray const * const v, Char const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsClocFromA(sep);
   greturnNullIf(!stemp);

   sresult = gsClocJoin(v, stemp);

   gsDloc(stemp);

   greturn sresult;
}

/**************************************************************************************************
** FUNC: gsClocJoinU1_
**************************************************************************************************/
grlAPI Gs *gsClocJoinU1_(GvArray const * const v, Gc1 const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsClocFromU1(sep);
   greturnNullIf(!stemp);

   sresult = gsClocJoin(v, stemp);

   gsDloc(stemp);

   greturn sresult;
}

/**************************************************************************************************
** FUNC: gsClocJoinU2_
**************************************************************************************************/
grlAPI Gs *gsClocJoinU2_(GvArray const * const v, Gc2 const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsClocFromU2(sep);
   greturnNullIf(!stemp);

   sresult = gsClocJoin(v, stemp);

   gsDloc(stemp);

   greturn sresult;
}
#endif


/**************************************************************************************************
func: gsEraseSub

Remove the chunk of the string.

param:
str
   Gs *
   in
   the sting.

start, end
   int, int
   in, in
   The end is not included in the destroy.
**************************************************************************************************/
grlAPI Gs *gsEraseSub(Gs * const str, Gindex const start, Gindex const end)
{
   genter;

   greturnNullIf(gsEraseAt(str, start, end - start));

   greturn str;
}

/**************************************************************************************************
func: gsFindAndReplace*

Find a given string in the existing string and replace it with another.

param:
str, find, replace
   Gs *, Gs *, Gs *
   in, in, in
   the string.

return:
int
   The number of times find was replaced.
**************************************************************************************************/
grlAPI Gs *gsFindAndReplace(Gs * const str, Gs const * const find, Gs const * const replace,
   Gcount * const count)
{
   Gindex idx;
   Gs    *temp;

   genter;

   greturnNullIf(
      !str ||
      !find);

   if (count)
   {
      *count = 0;
   }

   if (gsGetCount(str) != 0)
   {
      idx  = 0;
      temp = gsCloc();
      greturnNullIf(!temp);

      // Find all occurances of the find string and replace them with the
      // replace string.
      loop
      {
         idx = gsFindSub(str, 0, find);
         breakIf(idx == GindexERROR);

         if (count)
         {
            *count = *count + 1;
         }

         // Move the bits over to the temp string.
         stopIf(!gsAppendSub(temp, str, 0, idx));
         stopIf(!gsAppend(   temp, replace));
         stopIf(!gsAppendSub(temp, str, idx + gsGetCount(find), GindexMAX));

         // move the completed string back over.
         gsSet(str, temp);

         // reset temp.
         gsFlush(temp);
      }

STOP:
      gsDloc(temp);
   }

   greturn str;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindAndReplaceA
**************************************************************************************************/
grlAPI Gs *gsFindAndReplaceA(Gs * const str, Char const * const find,
   Char const * const  replace, Gcount * const count)
{
   Gs *fstr,
      *rstr,
      *result;

   genter;

   greturnNullIf(
      !str  ||
      !find ||
      !replace);

   result = NULL;
   fstr   = gsClocFromA(find);
   if (fstr)
   {
      rstr = gsClocFromA(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDloc(rstr);
      }
      gsDloc(fstr);
   }

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindAndReplaceU1
**************************************************************************************************/
grlAPI Gs *gsFindAndReplaceU1(Gs * const str, Gc1  const * const find, Gc1 const * const replace, Gcount * const count)
{
   Gs *fstr,
        *rstr,
        *result;

   genter;

   greturnNullIf(
      !str  ||
      !find ||
      !replace);

   result = NULL;
   fstr = gsClocFromU1(find);
   if (fstr)
   {
      rstr = gsClocFromU1(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDloc(rstr);
      }
      gsDloc(fstr);
   }

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindAndReplaceU2
**************************************************************************************************/
grlAPI Gs *gsFindAndReplaceU2(Gs * const str, Gc2 const * const find, Gc2 const * const replace, Gcount * const count)
{
   Gs *fstr,
        *rstr,
        *result;

   genter;

   greturnNullIf(
      !str  ||
      !find ||
      !replace);

   result = NULL;
   fstr   = gsClocFromU2(find);
   if (fstr)
   {
      rstr = gsClocFromU2(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDloc(rstr);
      }
      gsDloc(fstr);
   }

   greturn result;
}

/**************************************************************************************************
func: gsFindFirstCSVComma

Find the first comma in a comma separated value string.
**************************************************************************************************/
grlAPI Gindex gsFindFirstCSVComma(Gs const * const str, Gindex const position)
{
   Gindex index;
   Gb     isInQuotes;

   genter;

   isInQuotes = gbFALSE;
   for (index = position; index < gsGetCount(str); index++)
   {
      // Inside quotes
      if (!isInQuotes)
      {
         if (gsGetAt(str, index) == L'"')
         {
            isInQuotes = gbFALSE;
         }
      }
      // outside quotes
      else
      {
         if (gsGetAt(str, index) == L'"')
         {
            isInQuotes = gbTRUE;
         }
         else
         {
            breakIf(gsGetAt(str, index) == L',');
         }
      }
   }

   // Nothing found
   if (index >= gsGetCount(str))
   {
      index = GindexERROR;
   }

   greturn index;
}
#endif

/**************************************************************************************************
func: gsFindFirstNotOf*

Find the index of the first occurance of a letter not in letters in the
given string.

param:
str, letters
   Gs *, Gs *
   in, in
   the string.

return:
int
**************************************************************************************************/
grlAPI Gindex gsFindFirstNotOf(Gs const * const str, Gindex const position,
   Gs const * const letters)
{
   Gindex b,
          index;
   Gb     found;
   Gchar  letter;

   genter;

   greturnValIf(
         !str ||
         !letters,
      GindexERROR);

   found = gbFALSE;
   for (index = gMAX(0, position); index < gsGetCount(str); index++)
   {
      letter = gsGetAt(str, index);

      found = gbTRUE;
      forCount(b, gsGetCount(letters))
      {
         if (letter == gsGetAt(letters, b))
         {
            found = gbFALSE;
            break;
         }
      }

      breakIf(found)
   }

   greturn found ? index : GindexERROR;
}

/**************************************************************************************************
func: gsFindFirstNotOfChar
**************************************************************************************************/
grlAPI Gindex gsFindFirstNotOfChar(Gs const * const str, Gindex const position, Gchar const letter)
{
   Gindex index;
   Gb     found;

   genter;

   greturnValIf(!str, GindexERROR);

   found = gbFALSE;
   for (index = gMAX(0, position); index < gsGetCount(str); index++)
   {
      found = gbTRUE;
      if (gsGetAt(str, index) == letter)
      {
         found = gbFALSE;
         break;
      }

      breakIf(found);
   }

   greturn found ? index : GindexERROR;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindFirstNotOfA
**************************************************************************************************/
grlAPI Gindex gsFindFirstNotOfA(Gs const * const str, Gindex const position,
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromA(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindFirstNotOfU1
**************************************************************************************************/
grlAPI Gindex gsFindFirstNotOfU1(Gs const * const str, Gindex const position,
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU1(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindFirstNotOfU2
**************************************************************************************************/
grlAPI Gindex gsFindFirstNotOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU2(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsFindFirstOf*

Find the index of the first occurance of a letter in letters in the
given string.

param:
str, letters
   Gs *, Gs *
   in, in
   the string.

return:
int
**************************************************************************************************/
grlAPI Gindex gsFindFirstOf(Gs const * const str, Gindex const position, Gs const * const letters)
{
   Gindex b,
          index;
   Gb     found;
   Gchar  letter;

   genter;

   greturnValIf(
         !str ||
         !letters,
      GindexERROR);

   found = gbFALSE;
   for (index = gMAX(0, position); index < gsGetCount(str); index++)
   {
      letter = gsGetAt(str, index);

      forCount(b, gsGetCount(letters))
      {
         if (letter == gsGetAt(letters, b))
         {
            found = gbTRUE;
            stop();
         }
      }
   }

STOP:

   greturn found ? index : GindexERROR;
}

/**************************************************************************************************
func: gsFindFirstOfChar
**************************************************************************************************/
grlAPI Gindex gsFindFirstOfChar(Gs const * const str, Gindex const position, Gchar const letter)
{
   Gindex index;
   Gb     found;

   genter;

   greturnValIf(!str, GindexERROR);

   found = gbFALSE;
   for (index = gMAX(0, position); index < gsGetCount(str); index++)
   {
      if (gsGetAt(str, index) == letter)
      {
         found = gbTRUE;
         break;
      }
   }

   greturn found ? index : GindexERROR;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindFirstOfA
**************************************************************************************************/
grlAPI Gindex gsFindFirstOfA(Gs const * const str, Gindex const position,
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromA(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindFirstOfU1
**************************************************************************************************/
grlAPI Gindex gsFindFirstOfU1(Gs const * const str, Gindex const position,
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU1(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindFirstOfU2
**************************************************************************************************/
grlAPI Gindex gsFindFirstOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU2(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsFindLastNotOf

Find the index of the last occurance of a letter not in letters in the
given string.

param:
str, letters
   Gs *, Gs *
   in, in
   the string.

return:
int
**************************************************************************************************/
grlAPI Gindex gsFindLastNotOf(Gs const * const str, Gindex const position, Gs const * const letters)
{
   Gindex b,
          index;
   Gb     found;
   Gchar  letter;

   genter;

   greturnValIf(
         !str     ||
         !letters,
      GindexERROR);

   found = gbFALSE;
   for (index = gMIN(gsGetCount(str) - 1, position); index >= 0; index--)
   {
      letter = gsGetAt(str, index);

      found = gbTRUE;
      forCount(b, gsGetCount(letters))
      {
         if (letter == gsGetAt(letters, b))
         {
            found = gbFALSE;
            break;
         }
      }

      breakIf(found);
   }

   greturn found ? index : GindexERROR;
}

/**************************************************************************************************
func: gsFindLastNotOfChar
**************************************************************************************************/
grlAPI Gindex gsFindLastNotOfChar(Gs const * const str, Gindex const position, Gchar const letter)
{
   Gindex index;
   Gb     found;

   genter;

   greturnValIf(!str, GindexERROR);

   found = gbFALSE;
   for (index = gMIN(gsGetCount(str) - 1, position); index >= 0; index--)
   {
      found = gbTRUE;
      if (gsGetAt(str, index) == letter)
      {
         found = gbFALSE;
         break;
      }

      breakIf(found);
   }

   greturn found ? index : GindexERROR;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindLastNotOfA
**************************************************************************************************/
grlAPI Gindex gsFindLastNotOfA(Gs const * const str, Gindex const position,
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromA(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindLastNotOfU1
**************************************************************************************************/
grlAPI Gindex gsFindLastNotOfU1(Gs const * const str, Gindex const position,
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU1(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindLastNotOfU2
**************************************************************************************************/
grlAPI Gindex gsFindLastNotOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU2(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsFindLastOf

Find the index of the last occurance of a letter in letters in the
given string.

param:
str, letters
   Gs *, Gs *
   in, in
   the string.

return:
int
   The position of the letter or GindexERROR if not present in the string.
**************************************************************************************************/
grlAPI Gindex gsFindLastOf(Gs const * const str, Gindex const position, Gs const * const letters)
{
   Gindex b,
          index;
   Gb     found;
   Gchar  letter;

   genter;

   greturnValIf(
         !str     ||
         !letters,
      GindexERROR);

   found = gbFALSE;
   for (index = gMIN(gsGetCount(str) - 1, position); index >= 0; index--)
   {
      letter = gsGetAt(str, index);

      found = gbFALSE;
      forCount(b, gsGetCount(letters))
      {
         if (letter == gsGetAt(letters, b))
         {
            found = gbTRUE;
            break;
         }
      }

      breakIf(found);
   }

   greturn found ? index : GindexERROR;
}

/**************************************************************************************************
func: gsFindLastOfChar
**************************************************************************************************/
grlAPI Gindex gsFindLastOfChar(Gs const * const str, Gindex const position, Gchar const letter)
{
   Gindex index;
   Gb     found;

   genter;

   greturnValIf(!str, GindexERROR);

   found = gbFALSE;
   for (index = gMIN(gsGetCount(str) - 1, position); index >= 0; index--)
   {
      found = gbFALSE;
      if (gsGetAt(str, index) == letter)
      {
         found = gbTRUE;
         break;
      }

      breakIf(found);
   }

   greturn found ? index : GindexERROR;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindLastOfA
**************************************************************************************************/
grlAPI Gindex gsFindLastOfA(Gs const * const str, Gindex const position,
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromA(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindLastOfU1
**************************************************************************************************/
grlAPI Gindex gsFindLastOfU1(Gs const * const str, Gindex const position,
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU1(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindLastOfU2
**************************************************************************************************/
grlAPI Gindex gsFindLastOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU2(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsFindSub

Find a substring in a string.

param:
str, substr
   Gs *, Gs *
   in, in
   the string.

return:
int
   position of the substring or GindexERROR if not found.
**************************************************************************************************/
grlAPI Gindex gsFindSub(Gs const * const str, Gindex const position, Gs const * const substr)
{
   // This is a stupid simple algorithm just to get it done.  I didn't
   // use CRT wcsstr() because I'm not sure if the result is letter
   // count to the position of the substring or array count.  With U2,
   // some characters can span two array locations.

   // This code was taken from strstr() and modified for Gchar.
   // Which I'm surprised that it isn't more complex.  There are
   // faster string search algorithms.
   Gchar const *cp,
               *s1,
               *s2;

   genter;

   greturnValIf(
         !str ||
         !substr,
      GindexERROR);

   cp = gsGet(str) + position;
   while (*cp)
   {
      s1 = cp;
      s2 = gsGet(substr);

      while (*s1 &&
             *s2 &&
             !(*s1 - *s2))
      {
         s1++;
         s2++;
      }

      // We found the substr in str.
      greturnValIf(!*s2, (Gindex) (cp - gsGet(str)));

      // substring is longer than the rest of the
      // search string.  Terminate.
      breakIf(!*s1 && *s2);

      cp++;
   }

   greturn GindexERROR;
}

/**************************************************************************************************
func: gsFunctionStart
**************************************************************************************************/
Gb gsFunctionStart(void)
{
   genter;

   _whitespace = gsClocFromA(gcharWHITESPACE);
   greturnFalseIf(!_whitespace);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gsFunctionStop
**************************************************************************************************/
void gsFunctionStop(void)
{
   genter;

   gsDloc(_whitespace);

   greturn;
}

#if 0
/**************************************************************************************************
** FUNC: gsFindSubA
**************************************************************************************************/
grlAPI Gindex gsFindSubA(Gs const * const str, Gindex const position,
   Char const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromA(substr);
   result = gsFindSub(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindSubU1
**************************************************************************************************/
grlAPI Gindex gsFindSubU1(Gs const * const str, Gindex const position,
   Gc1 const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU1(substr);
   result = gsFindSub(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFindSubU2
**************************************************************************************************/
grlAPI Gindex gsFindSubU2(Gs const * const str, Gindex const position,
   Gc2 const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsClocFromU2(substr);
   result = gsFindSub(str, position, lstr);
   gsDloc(lstr);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsFromCSV
**
** Adjust the string from a CSV field.
**************************************************************************************************/
grlAPI Gs *gsFromCSV(Gs * const str)
{
   Gindex a;

   genter;

   greturnValIf(
         !str ||
         gsGetCount(str) == 0,
      str);

   // CSV if a string is in " then a comma or a quote appears in the string.
   if (gsGetBegin(str) == L'"')
   {
      // Remove the enclosing quotes.
      greturnNullIf(!gsEraseSub(str, 0, 1));
      greturnNullIf(!gsEraseSub(str, gsGetCount(str) - 1, gsGetCount(str)));

      // Search for double double quotes.
      for (a = gsGetCount(str) - 1; ; a--)
      {
         // "" gets translated to ".  "[x] should not happen.
         if (gsGetAt(str, a)     == L'"' &&
             gsGetAt(str, a - 1) == L'"')
         {
            greturnNullIf(!gsEraseSub(str, a, a + 1));
         }

         breakIf(a == 1);
      }
   }

   greturn str;
}
#endif

/**************************************************************************************************
func: gsGetI
**************************************************************************************************/
grlAPI Gi gsGetI(Gs const * const str)
{
   genter;

   greturn0If(!str);

   greturn gcharGetI(gsGet(str));
}

/**************************************************************************************************
func: gsGetN
**************************************************************************************************/
grlAPI Gn gsGetN(Gs const * const str)
{
   genter;

   greturn0If(!str);

   greturn gcharGetN(gsGet(str));
}

/**************************************************************************************************
func: gsGetNHex
**************************************************************************************************/
grlAPI Gn gsGetNHex(Gs const * const str)
{
   genter;

   greturn0If(!str);

   greturn gcharGetNHex(gsGet(str));
}

/**************************************************************************************************
func: gsGetR
**************************************************************************************************/
grlAPI Gr gsGetR(Gs const * const str)
{
   //TODO
#if 0
   Gc2 *stemp;
#endif
   Gr      rtemp = 0;

   genter;

   greturn0If(!str);

#if 0
   stemp = gsClocU2(str);
   rtemp = _wtof(stemp);
   gmemDloc(stemp);
#else
   //rtemp = _wtof(gsGet(str));
#endif

   greturn rtemp;
}

/**************************************************************************************************
func: gsGetWhitespace
**************************************************************************************************/
grlAPI Gs const *gsGetWhitespace(void)
{
   genter;

   greturn _whitespace;
}

/**************************************************************************************************
func: gsHash

Hash a string.

param:
str
   Gs *
   in
   String to hash.

return:
long
   This integer should be modulated with a prime value.
**************************************************************************************************/
grlAPI GhashN gsHash(Gs const * const str)
{
   Gindex a;
   GhashN hash,
          g;

   genter;

   greturn0If(!str);

   // Initialize the hash value
   hash = 0;

   // Iterate over all the letters.
   forCount(a, gsGetCount(str))
   {
      // Update the hash value.
      hash = (hash << 4) + (GhashN) gsGetAt(str, a);

      // g holds the top half byte of the hash value.
      g = hash & 0xf0000000;

      // If the value gets too large then adjust it.
      if (g)
      {
         hash = hash ^ (g >> 24);
         hash = hash ^ g;
      }
   }

   // greturn the hash value & GiMAX to keep the value positive
   greturn hash & GhashNMAX;
}

/**************************************************************************************************
func: gsHashContainer
**************************************************************************************************/
grlAPI GhashN gsHashContainer(Gv const * const v)
{
   genter;

   greturn gsHash(gvpGetS(v));
}

/**************************************************************************************************
func: gsInsert

Insert a string inside another string.  This isn't an efficient
operation so use with caution in busy places.

param:
dst
   Gs *
   in
   The string.

position
   int
   in
   The location to put the inserted string.

src
   Gs *
   in
   the string.
**************************************************************************************************/
Gs *gsInsert(Gs * const dst, Gindex const position, Gs const * const src)
{
   genter;

   greturnNullIf(
      !dst ||
      !src);

   if (position >= gsGetCount(dst))
   {
      greturnNullIf(!gsAppend(dst, src));
   }
   else
   {
      Gs *temp = gsCloc();

      greturnNullIf(!gsAppendSub(temp, dst, position, GindexMAX));
      greturnNullIf(!gsEraseAt(  dst, GcountMAX, position));
      greturnNullIf(!gsAppend(   dst, src));
      greturnNullIf(!gsAppend(   dst, temp));

      gsDloc(temp);
   }

   greturn dst;
}

#if 0
/**************************************************************************************************
** FUNC: gsInsertFormat
**************************************************************************************************/
grlAPI Gs *gsInsertFormat(Gs * const dst, Gindex const position,
   Gs const * const src, Char const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsClocFrom(src), format);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertA
**************************************************************************************************/
grlAPI Gs *gsInsertA(Gs * const dst, Gindex const position, Char const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsClocFromA(src);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertFormatA
**************************************************************************************************/
grlAPI Gs *gsInsertFormatA(Gs * const dst, Gindex const position,
   Char const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsClocFromA(src), format);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertU1
**************************************************************************************************/
grlAPI Gs *gsInsertU1(Gs * const dst, Gindex const position, Gc1 const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsClocFromU1(src);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertFormatU1
**************************************************************************************************/
grlAPI Gs *gsInsertFormatU1(Gs * const dst, Gindex const position,
   Gc1 const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsClocFromU1(src), format);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertU2
**************************************************************************************************/
grlAPI Gs *gsInsertU2(Gs * const dst, Gindex const position, Gc2 const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsClocFromU2(src);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsInsertFormatU2
**************************************************************************************************/
grlAPI Gs *gsInsertFormatU2(Gs * const dst, Gindex const position,
   Gc2 const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsClocFromU2(src), format);
   result = gsInsert(dst, position, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsIsBlank
**************************************************************************************************/
grlAPI Gb gsIsBlank(Gs const *const str)
{
   genter;

   greturnTrueIf(gsIsEmpty(str));

   greturn (gsFindFirstNotOf(str, 0, _whitespace) == GindexERROR);
}

/**************************************************************************************************
func: gsIsMultiline
**************************************************************************************************/
grlAPI Gb gsIsMultiline(Gs const * const str)
{
   Gindex index;

   genter;

   for (index = 0; ; index++)
   {
      breakIf(index >= gsGetCount(str));

      returnTrueIf(gsGetAt(str, index) == L'\n');
   }

   greturn gbFALSE;
}

/**************************************************************************************************
func: gsReverse

Reverse the string.

param:
dst
   Gs *
   in
   The string.
**************************************************************************************************/
grlAPI Gs *gsReverse(Gs * const str)
{
   Gindex index;
   Gcount count;

   genter;

   if (!str)
   {
      greturn str;
   }

   count = gsGetCount(str);
   forCount(index, count / 2)
   {
      gsSwap(str, index, count - 1 - index);
   }

   greturn str;
}

/**************************************************************************************************
func: gsPadHead
**************************************************************************************************/
grlAPI Gs *gsPadHead(Gs * const str, Gcount const length, Gchar const letter)
{
   genter;

   for (; gsGetCount(str) < length;)
   {
      greturnNullIf(!gsAddBegin(str, letter));
   }

   greturn str;
}

/**************************************************************************************************
func: gsPadTail
**************************************************************************************************/
grlAPI Gs *gsPadTail(Gs * const str, Gcount const length, Gchar const letter)
{
   genter;

   for (; gsGetCount(str) < length;)
   {
      greturnNullIf(!gsAddEnd(str, letter));
   }

   greturn str;
}

/**************************************************************************************************
func: gsStrip

strip stuff from the string.
**************************************************************************************************/
grlAPI Gs *gsStrip(Gs * const str, GsStripMethod const type)
{
   Gindex a,
          b;
   Gb     leadingWhite,
          inquotes;
   Gb     isEscaped;
   Gchar  backslash,
          quote;

   genter;

   greturnNullIf(!str);

   // Init
   backslash = (Gchar) '\\';
   quote     = (Gchar) '"';

   leadingWhite = gbTRUE;
   inquotes     = gbFALSE;
   isEscaped    = gbFALSE;

   // Pass 1.  Remove trailing whitespace.
   if (type & gsStripMethodWHITE_SPACE_TRAILING &&
       gsGetCount(str) > 0)
   {
      forCountDown(a, gsGetCount(str))
      {
         // move the null terminator up.
         if (gcharIsWhiteSpace(gsGetAt(str,a)))
         {
            // An escaped blank is still a trailing blank.
            if (a &&
                gsGetAt(str, a - 1) == backslash)
            {
               a = a - 1;
            }
         }
         else
         {
            break;
         }
      }

      // Set the new length.
      gsSetCount(str, a + 1);
   }

   // Pass 2. Take care of white space (leading and all) and
   // escape characters.
   b = 0;
   forCount(a, gsGetCount(str))
   {
      // Check for leading and internal white space.
      if ((type & gsStripMethodWHITE_SPACE           &&
           !inquotes)                                ||
          type & gsStripMethodWHITE_SPACE_ALL           ||
          (type & gsStripMethodWHITE_SPACE_LEADING   &&
           leadingWhite))
      {
         // White space
         continueIf(gcharIsWhiteSpace(gsGetAt(str, a)));

         // First non white space.
         // an escaped white space is still a white space.
         continueIf(
            !isEscaped                   &&
            gsGetAt(str, a) == backslash &&
            gcharIsWhiteSpace(gsGetAt(str, a + 1)));

         // last of the leading blanks.
         leadingWhite = gbFALSE;
      }

      // Check for escape character
      if (!isEscaped &&
          gsGetAt(str, a) == backslash)
      {
         isEscaped = 2;
      }

      if (isEscaped != 1                        &&
          ((type & gsStripMethodESCAPE_CHAR &&
            !inquotes)                       ||
           type & gsStripMethodESCAPE_CHAR_ALL))
      {
         if (gsGetAt(str, a) == backslash)
         {
            // skip it
            isEscaped--;
            continue;
         }
      }

      // Quote character
      if (gsGetAt(str, a) == quote)
      {
         // Make sure the character isn't escaped.
         if ((a &&
              gsGetAt(str, a - 1) != backslash) ||
             !a)
         {
            inquotes = (Gb) !inquotes;
         }
      }

      // Move the character
      isEscaped--;
      isEscaped = gMAX(0, isEscaped);

      greturnNullIf(!gsUpdateAt(str, b, gsGetAt(str, a)));
      b = b + 1;
   }

   // Null terminate the string.

   greturnNullIf(!gsSetCount(str, b));

   greturn str;
}

/**************************************************************************************************
func: gsStripCompress

Compress the white space runs to one space.
**************************************************************************************************/
grlAPI Gs *gsStripCompress(Gs * const str)
{
   Gindex a,
          b;
   Gb     found;

   genter;

   greturnNullIf(!str);

   // Get rid of the leading and trailing space.
   greturnNullIf(!gsStrip(str, gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING));

   // Remove all but one from the other strings of spaces.
   found = gbFALSE;

   b = 0;
   forCount(a, gsGetCount(str))
   {
      if (!found)
      {
         if (gcharIsWhiteSpace(gsGetAt(str, a)))
         {
            found = gbTRUE;
         }
      }
      else
      {
         // Only accept one white space.  Trim the others.
         continueIf(gcharIsWhiteSpace(gsGetAt(str, a)));

         // Not a white space.  Restart the search.
         found = gbFALSE;
      }

      // Move the character
      greturnNullIf(!gsUpdateAt(str, b, gsGetAt(str, a)));
      b = b + 1;
   }

   // Null terminate the string.
   greturnNullIf(!gsSetCount(str, b));

   greturn str;
}

#if 0
/**************************************************************************************************
** FUNC: gsToCSV
**
** Adjusts the string so that it can live in a CSV file.
**************************************************************************************************/
grlAPI Gs *gsToCSV(Gs * const str)
{
   Gindex a;

   genter;

   // Nothing to do.
   if (!str ||
       gsGetCount(str) == 0)
   {
      greturn str;
   }

   /* If the string contains a " (quote) or a , (comma) then we need
   ** to convert.  Not as efficient as it could be.*/
   if (gsFindFirstOfA(str, 0, (Char const *) "\",") != GindexERROR)
   {
      Gs *temp = gsCloc();

      greturnNullIf(!gsAppendC(temp, L'"'));

      // double the double quotes.
      forCount(a, gsGetCount(str))
      {
         if (gsGetAt(str, a) == L'"')
         {
            greturnNullIf(!gsAppendC(temp, L'"'));
         }
         greturnNullIf(!gsAppendC(temp, gsGetAt(str, a)));
      }

      greturnNullIf(!gsAppendC(temp, L'"'));

      greturnNullIf(!gsSet(str, temp));

      gsDloc(temp);
   }

   greturn str;
}

/**************************************************************************************************
** FUNC: gsToFormat
**
** See Append for more information.
**************************************************************************************************/
grlAPI Gs *gsToFormat(Gs * const str, Char const * const format)
{
   genter;

   greturnValIf(
         !str ||
         !format,
      str);

   greturn _FormatString(str, format);
}
#endif

/**************************************************************************************************
func: gsToLowerCase

Convert the string to all lower case letters.  ASCII only for now.
**************************************************************************************************/
grlAPI Gs *gsToLowerCase(Gs * const str)
{
   Gindex index;

   genter;

   greturnNullIf(!str);

   forCount(index, gsGetCount(str))
   {
      greturnNullIf(!gsUpdateAt(str, index, gcharToLowerCase(gsGetAt(str, index))));
   }

   greturn str;
}

/**************************************************************************************************
func: gsToUpperCase

Convert the string to all upper case letters.  ASCII only for now.
**************************************************************************************************/
grlAPI Gs *gsToUpperCase(Gs * const str)
{
   Gindex index;

   genter;

   greturnValIf(!str, str);

   forCount(index, gsGetCount(str))
   {
      greturnNullIf(!gsUpdateAt(str, index, gcharToUpperCase(gsGetAt(str, index))));
   }

   greturn str;
}

/**************************************************************************************************
func: gsTrim

Performs a left and right trim in succcession.  If you
wished to trim all the gcharWHITESPACE from a string you
would use,

gsTrimA(str, WHITESPACE_A);

PARAM:
str
   Gs *
   in/out
   The string to modify.  Modifications are destructive.

letters
   Char *
   in
   The set of letters you wish have trimmed from a string.
**************************************************************************************************/
grlAPI Gs *gsTrim(Gs * const str, Gs const * const letters)
{
   Gs *result;

   genter;

   greturnValIf(
         !str ||
         !letters,
      str);

   // Right side first because it'll make Trim left cheaper.
   result = gsTrimLeft(gsTrimRight(str, letters), letters);

   greturn result;
}

#if 0
/**************************************************************************************************
** FUNC: gsTrimA
**************************************************************************************************/
grlAPI Gs *gsTrimA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromA(letters);
   result = gsTrim(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimU1
**************************************************************************************************/
grlAPI Gs *gsTrimU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU1(letters);
   result = gsTrim(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimU2
**************************************************************************************************/
grlAPI Gs *gsTrimU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU2(letters);
   result = gsTrim(str, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gsTrimLeft

Performs a left trim on a string. Trimmed characters
are all those characters in the letters parameters.

PARAM:
str
   Gs *
   in/out
   The string to modify.  Modifications are destructive.

letters
   Char *
   in
   The set of letters you wish have trimmed from a string.
**************************************************************************************************/
grlAPI Gs *gsTrimLeft(Gs * const str, Gs const * const letters)
{
   Gs    *result;
   Gindex idx;

   genter;

   greturnValIf(
         !str ||
         !letters,
      str);

   idx = gsFindFirstNotOf(str, 0, letters);

   if (idx != GindexERROR)
   {
      result = gsEraseSub(str, 0, idx);

      greturn result;
   }

   result = str;

   greturn result;
}

#if 0
/**************************************************************************************************
** FUNC: gsTrimLeftA
**************************************************************************************************/
grlAPI Gs *gsTrimLeftA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromA(letters);
   result = gsTrimLeft(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimLeftU1
**************************************************************************************************/
grlAPI Gs *gsTrimLeftU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU1(letters);
   result = gsTrimLeft(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimLeftU2
**************************************************************************************************/
grlAPI Gs *gsTrimLeftU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU2(letters);
   result = gsTrimLeft(str, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
FUNC: gsTrimRight

Performs a right trim on a string. Trimmed characters
are all those characters in the letters parameters.

PARAM:
str
   Gs *
   in/out
   The string to modify.  Modifications are destructive.

letters
   Char *
   in
   The set of letters you wish have trimmed from a string.
**************************************************************************************************/
grlAPI Gs *gsTrimRight(Gs * const str, Gs const * const letters)
{
   Gs    *result;
   Gindex idx;

   genter;

   greturnValIf(
         !str ||
         !letters,
      str);

   idx = gsFindLastNotOf(str, 0, letters);

   if (idx != GindexERROR)
   {
      result = gsEraseSub(str, idx + 1, gsGetCount(str));

      greturn result;
   }

   result = str;

   greturn result;
}

#if 0
/**************************************************************************************************
** FUNC: gsTrimRightA
**************************************************************************************************/
grlAPI Gs *gsTrimRightA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromA(letters);
   result = gsTrimRight(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimRightU1
**************************************************************************************************/
grlAPI Gs *gsTrimRightU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU1(letters);
   result = gsTrimRight(str, stemp);
   gsDloc(stemp);

   greturn result;
}

/**************************************************************************************************
** FUNC: gsTrimRightU2
**************************************************************************************************/
grlAPI Gs *gsTrimRightU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsClocFromU2(letters);
   result = gsTrimRight(str, stemp);
   gsDloc(stemp);

   greturn result;
}
#endif

/**************************************************************************************************
func: gvDataDlocS

Used with the containers that store a gv for pointers.
**************************************************************************************************/
grlAPI void gvDataDlocS(GvData * const value)
{
   genter;

   gsDloc(gvDataGetS(value));

   greturn;
}

/**************************************************************************************************
local
function
**************************************************************************************************/
#if 0
/**************************************************************************************************
** FUNC: _Format*
**
** Format an integer.
**************************************************************************************************/
static Gs *_FormatI(Gi const i, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, i) == -1);

   result = gsClocFromU2(ctemp);

   greturn result;
}

static Gs *_FormatN(Gn const n, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, n) == -1);

   result = gsClocFromU2(ctemp);

   greturn result;
}

static Gs *_FormatR(Gr const r, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, r) == -1);

   result = gsClocFromU2(ctemp);

   greturn result;
}

static Gs *_FormatString(Gs * const str, Gc2 const * const format)
{
#if 0
   Gc2 ctemp[1024],
         *stemp;
#else
   Gc2 ctemp[1024];
#endif

   genter;

#if 0
   stemp = gsClocU2(str);
   swprintf_s(ctemp, 1024, format, stemp);
   gmemDloc(stemp);
#else
   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, gsGet(str)) == -1)
#endif

   greturnNullIf(!gsSetU2(str, ctemp));

   greturn str;
}

/**************************************************************************************************
func: _GetByteLength

Get the length of the data the hard way.
**************************************************************************************************/
static Gcount _GetByteLength(Gp *ptr, gsParamType type)
{
   Gcount result;
   Gi4     a;
   Gc1 *c1p;
   Gc2 *c2p;
   Gc4 *c4p;

   genter;

   switch (type)
   {
   case gsParamTypeA:
      result = (Gcount) strlen((Char *) ptr);

      greturn result;

   case gsParamTypeU1:
      c1p = (Gc1 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(
               c1p[a] == 0,
            (Gcount) (c1p - ((Gc1 *) ptr)));

         c1p = &(c1p[gcGetLetterByteCount((Gp *) c1p, type)]);
      }

   case gsParamTypeU2:
      c2p = (Gc2 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(
               c2p[a] == 0,
            (Gcount) (c2p - ((Gc2 *) ptr)));

         c1p = (Gc1 *) c2p;
         c2p = (Gc2 *) &(c1p[gcGetLetterByteCount((Gp *) c1p, type)]);
      }

   case gsParamTypeU4:
      c4p = (Gc4 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(
               c4p[a] == 0,
            (Gcount) (c4p - ((Gc4 *) ptr)));
      }
   }

   greturn 0;
}

/**************************************************************************************************
func: _GetLength

Get the length of the data the hard way.
**************************************************************************************************/
static Gcount _GetLength(Gp const * const ptr, gsParamType const type)
{
   Gcount       result;
   Gcount       a;
   const Gc1   *c1p;
   const Gc2   *c2p;
   const Gc4   *c4p;

   genter;

   switch (type)
   {
   case gsParamTypeA:
      result = (Gcount) strlen((char const *) ptr);

      greturn result;

   case gsParamTypeU1:
      c1p = (const Gc1 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(c1p[0] == 0, a);

         c1p = &(c1p[gcGetLetterByteCount((const Gp *) c1p, type)]);
      }

   case gsParamTypeU2:
      c2p = (const Gc2 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(c2p[0] == 0, a);

         c1p = (const Gc1 *) c2p;
         c2p = (const Gc2 *) &(c1p[gcGetLetterByteCount((const Gp *) c1p, type)]);
      }

   case gsParamTypeU4:
      c4p = (const Gc4 *) ptr;
      for (a = 0; ; a++)
      {
         greturnValIf(c4p[a] == 0, a);
      }
   }

   greturn 0;
}
#endif
