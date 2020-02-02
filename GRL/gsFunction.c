/******************************************************************************
file:       gs
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
local:
function:
******************************************************************************/
static Gs      *_FormatI(        Gi const i,     Gc2 const * const format);
static Gs      *_FormatN(        Gn const n,     Gc2 const * const format);
static Gs      *_FormatR(        Gr const r,     Gc2 const * const format);
static Gs      *_FormatString(   Gs * const str, Gc2 const * const format);

#if 0
static Gcount   _GetByteLength(  Gp * const ptr, GcType const type);
#endif
static Gcount   _GetLength(      Gp const * const ptr, GcType const type);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gsAppendA
******************************************************************************/
grlAPI Gs *gsAppendA(Gs * const str, Char const * const cstr)
{
   Gindex a;
   Gcount count,
          length,
          clength;
   Gc2    ctemp;

   genter;

   greturnNullIf(
      !str ||
      !cstr);

   // Nothing to add, append is ok.
   clength = (Gcount) strlen(cstr); //lint !e586
   greturnIf(!clength, str);

   // New size of the string.
   length = gsGetCount(str);
   count  = length + clength;

   // Resize the buffer.
   greturnNullIf(!gsSetCount(str, count));

   // Copy the data over.
   forCount(a, clength)
   {
      ctemp = (Gc2) cstr[a];
      greturnNullIf(!gsUpdateAt(str, length + a, &ctemp));
   }

   greturn str;
}

/******************************************************************************
** FUNC: gsAppendFormatA
******************************************************************************/
grlAPI Gs *gsAppendFormatA(Gs * const str, Char const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp = gsCreateFromA(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendC
******************************************************************************/
grlAPI Gs *gsAppendC(Gs * const str, Gc2 const gc)
{
   Gcount length;

   genter;

   greturnNullIf(
      !str ||
      !gc);

   length = gsGetCount(str);
   greturnNullIf(!gsSetCount(str, length + 1));

   greturnNullIf(!gsUpdateAt(str, length, &gc));

   greturn str;
}

/******************************************************************************
func: gsAppendCFormat
******************************************************************************/
grlAPI Gs *gsAppendCFormat(Gs * const str, Gc2 const gc, Gc2 const * const format)
{
   Gs *stemp,
        *result;

   genter;

   greturnNullIf(
      !str ||
      !gc  ||
      !format);

   stemp = gsCreate();
   greturnNullIf(!stemp);

   result = NULL;
   if (gsAppendC( stemp, gc) &&
       gsToFormat(stemp, format))
   {
      result = gsAppend(str, stemp);
   }

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendI
******************************************************************************/
grlAPI Gs *gsAppendI(Gs * const str, Gi const i)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_i64toa_s(i, ctemp, (size_t) 80, 10) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsAppendIFormat(Gs * const str, Gi8 const i, Gc2 const * const format)
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

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendN
******************************************************************************/
grlAPI Gs *gsAppendN(Gs * const str, Gn const n)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_ui64toa_s(n, ctemp, (size_t) 80, 10) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsAppendNFormat(Gs * const str, Gn const n, Gc2 const * const format)
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

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendR
******************************************************************************/
grlAPI Gs *gsAppendR(Gs * const str, Gr const r)
{
   Gs  *result;
   Char ctemp[80];

   genter;

   greturnNullIf(!str);

   greturnNullIf(_gcvt_s(ctemp, (size_t) 80, r, 15) != 0);

   result = gsAppendA(str, ctemp);

   greturn result;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsAppendRFormat(Gs * const str, Gr const r, Gc2 const * const format)
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

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendSub
******************************************************************************/
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
      start > end ||
      end   == 0);

   // fix bad input.
   startTemp = gMIN(gsGetCount(value), start);//lint !e666
   endTemp   = gMIN(gsGetCount(value), end);//lint !e666

   a = gsGetCount(str);
   greturnNullIf(!gsSetCount(str, a + endTemp - startTemp));

   // Set the string.
   greturnNullIf(!gsCopyFrom(str, a, value, endTemp - startTemp, startTemp));

   greturn str;
}

/******************************************************************************
** FUNC: gsAppendSubFormat
******************************************************************************/
grlAPI Gs *gsAppendSubFormat(Gs * const str, Gs const * const value,
   Gindex const start, Gindex const end, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   greturnNullIf(
      !str   ||
      !value ||
      !format);

   stemp = _FormatString(gsCreateFromSub(value, start, end), format);
   greturnNullIf(!stemp);

   result = gsAppend(str, stemp);

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppend

Add a Gs to the string.

param:
str, add
   Gs *, Gs *
   in/out, in
   The strings.
******************************************************************************/
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

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsAppendFormat(Gs * const str, Gs const * const value, Gc2 const * const format)
{
   Gs *atemp,
        *result;

   genter;

   greturnNullIf(
      !str   ||
      !value ||
      !format);

   atemp = gsCreateFrom(value);
   greturnNullIf(!atemp);

   result = gsAppend(str, _FormatString(atemp, format));

   gsDestroy(atemp);

   greturn result;
}

/******************************************************************************
func: gsAppendU1
******************************************************************************/
grlAPI Gs *gsAppendU1(Gs * const str, Gc1 const * const cstr)
{
   Gindex a;
   Gcount count,
          length,
          clength;
   Gc     letter;
   Gc2    ctemp;

   genter;

   greturnNullIf(
      !str ||
      !cstr);

   clength = _GetLength(cstr, gcTypeU1);
   greturnIf(!clength, str);

   // New size of the string.
   length = gsGetCount(str);
   count  = length + clength;

   // Resize the buffer.
   greturnNullIf(!gsSetCount(str, count));

   // Copy the data over.
   count = 0;
   forCount(a, clength)
   {
      letter = gcFromU1((Gc1 const *) &(cstr[count])); //lint !e926
      count += gcGetLetterByteCount((Gp const *) &(cstr[count]), gcTypeU1); 

      // TODO: This isn't right and should be fixed at some point.  No one is using this function yet.
      ctemp = (Gc2) letter;
      greturnNullIf(!gsUpdateAt(str, length + a, &ctemp));
   }

   greturn str;
}

/******************************************************************************
** FUNC: gsAppendFormatU1
******************************************************************************/
grlAPI Gs *gsAppendFormatU1(Gs * const str, Gc1 const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
        *result;

   genter;

   stemp = gsCreateFromU1(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendU2
******************************************************************************/
grlAPI Gs *gsAppendU2(Gs * const str, Gc2 const * const cstr)
{
   Gindex a,
          cidx;
   Gcount count,
          length,
          clength;
   Gc2    ctemp;

   genter;

   greturnNullIf(
      !str ||
      !cstr);

   clength = (Gcount) wcslen(cstr);
   greturnIf(!clength, str);

   // New size of the string.
   length = gsGetCount(str);
   count  = length + clength;

   // Resize the buffer.
   greturnNullIf(!gsSetCount(str, count));

   // Copy the data over.
   cidx = 0;
   forCount(a, clength)
   {
      ctemp = (Gc2) cstr[cidx];
      greturnNullIf(!gsUpdateAt(str, length + a, &ctemp));

      cidx++;
   }

   greturn str;
}

/******************************************************************************
** FUNC: gsAppendFormatU2
******************************************************************************/
grlAPI Gs *gsAppendFormatU2(Gs * const str, Gc2 const * const cstr, Gc2 const * const format)
{
   Gs *stemp,
        *result;

   genter;

   greturnNullIf(
      !str  ||
      !cstr ||
      !format);

   stemp = gsCreateFromU2(cstr);
   greturnNullIf(!stemp);

   result = gsAppend(str, _FormatString(stemp, format));

   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsAppendFormated

After format, you have pairs of variables.

Gc2 const * const key,
Gc2 const type, 
Depending on type above value is one of the following.

type 
"a" - ascii    key, value
"u" - UTF8     key, value
"U" - UTF16    key, value
"s" - Gs *     key, value
"i" - integer  value
"n" - natural  value
"r" - real     value
******************************************************************************/
grlAPI Gs *gsAppendFormated(Gs * const str, Gc2 const * const format, ...)//lint !e1916 !e960
{
   Gs  const   *search,
               *replace;
   Gs          *stemp,
               *result;
   Gc2          typeTemp;
   va_list      args;
   GtempScope  *tempScope;

   genter;

   greturnNullIf(
      !str ||
      !format);

   search  = NULL;
   replace = NULL;
   stemp   = NULL;

   tempScope = gtempEnter();
   greturnNullIf(!tempScope);

   va_start(args, format);

   stemp = gtempGs(tempScope, gsCreateFromU2((Gc2 const *) format));

   loop
   {
      search = gtempGs(tempScope, gsCreateFromU2(va_arg(args, Gc2 *))); //lint !e960
      breakIf(search == NULL);

      typeTemp = va_arg(args, Gc2);
      switch (typeTemp)
      {
      case 'a':
         replace = gtempGs(tempScope, gsCreateFromA(va_arg(args, Char *))); //lint !e960
         break;

      case 'u':
         replace = gtempGs(tempScope, gsCreateFromU1(va_arg(args, Gc1 *))); //lint !e960
         break;

      case 'U':
         replace = gtempGs(tempScope, gsCreateFromU2(va_arg(args, Gc2 *))); //lint !e960
         break;

      case 's':
         replace = va_arg(args, Gs *);
         break;

      case 'i':
         replace = gtempGs(tempScope, gsCreateFromI(va_arg(args, Gi)));
         break;

      case 'n':
         replace = gtempGs(tempScope, gsCreateFromN(va_arg(args, Gn)));
         break;

      case 'r':
         replace = gtempGs(tempScope, gsCreateFromR(va_arg(args, Gr)));
         break;
      }//lint !e787

      // Do the search and replace.
      stemp = gsFindAndReplace(stemp, search, replace, NULL);
   }

   result = gsAppend(str, stemp);

   // Clean up.
   va_end(args);

   gtempExit(tempScope);

   greturn result;//lint !e438
}//lint !e954

/******************************************************************************
func: gsAppendParams
******************************************************************************/
grlAPI Gs *gsAppendParams(Gs * const str, ...) //lint !e1916 !e960
{
   Gs const *stemp;
   va_list   args;

   genter;

   greturnIf(!str, str);

   va_start(args, str);

   loop
   {
      // NULL means end of the chain.
      stemp = (Gs *) va_arg(args, Gs *); //lint !e929
      breakIf(!stemp);

      // Do the search and replace.
      greturnNullIf(!gsAppend(str, stemp));
   }

   va_end(args);

   greturn str;//lint !e438
} //lint !e954

/******************************************************************************
func: gsAppendRandom
******************************************************************************/
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
         gsAppendC(str, (Gc2) (L'A' + letter));
         continue;
      }

      letter -= 26;

      // lower case letter.
      if (0 <= letter && letter < 26)
      {
         gsAppendC(str, (Gc2) (L'a' + letter));
         continue;
      }

      letter -= 26;

      // number
      gsAppendC(str, (Gc2) (L'0' + letter));
   }

   greturn str;
}

/******************************************************************************
** FUNC: gsCapitalize
**
** Capitalize the first letter if not a space.
******************************************************************************/
grlAPI Gs *gsCapitalize(Gs * const str)
{
   Gc2 letter;

   genter;

   greturnNullIf(!str);

   greturnIf(gsGetCount(str) == 0, str);

   // Officially not fully unicode compliant.
   letter = gcToUpperCase(*gsGetBegin(str));
   greturnNullIf(!gsUpdateAt(str, 0, &letter));

   greturn str;
}

/******************************************************************************
func: gsCompare*
******************************************************************************/
grlAPI Gcompare gsCompare(Gs const * const as, Gs const * const bs)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gc2    a,
          b;

   genter;

   greturnIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, acount)
   {
      breakIf(index >= bcount);

      a = *gsGetAt(as, index);
      b = *gsGetAt(bs, index);

      greturnIf(a < b, gcompareLESS_THAN);
      greturnIf(a > b, gcompareGREATER_THAN);
   }

   greturnIf(acount < bcount, gcompareLESS_THAN);
   greturnIf(acount > bcount, gcompareGREATER_THAN);

   greturn gcompareEQUAL;
}

/******************************************************************************
** FUNC: gsCompareA
******************************************************************************/
grlAPI Gcompare gsCompareA(Gs const * const a, Char const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromA(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareU1
******************************************************************************/
grlAPI Gcompare gsCompareU1(Gs const * const a, Gc1 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU1(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareU2
******************************************************************************/
grlAPI Gcompare gsCompareU2(Gs const * const a, Gc2 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU2(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompare(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsCompareBase

Compare the base strings together.  Ignores local so order may not
honour dictionary/telephone/region order.  Read up on this at
unicode.org
******************************************************************************/
grlAPI Gcompare gsCompareBase(Gs const * const as, Gs const * const bs)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gc     a,
          b;

   genter;

   greturnIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, acount)
   {
      breakIf(index >= bcount);

      a = gcToLowerCase(*gsGetAt(as, index));//lint !e732
      b = gcToLowerCase(*gsGetAt(bs, index));//lint !e732

      greturnIf(a < b, gcompareLESS_THAN);
      greturnIf(a > b, gcompareGREATER_THAN);
   }

   greturnIf(acount < bcount, gcompareLESS_THAN);
   greturnIf(acount > bcount, gcompareGREATER_THAN);

   greturn gcompareEQUAL;
}

/******************************************************************************
** FUNC: gsCompareBaseA
******************************************************************************/
grlAPI Gcompare gsCompareBaseA(Gs const * const a, Char const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromA(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareBaseU1
******************************************************************************/
grlAPI Gcompare gsCompareBaseU1(Gs const * const a, Gc1 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU1(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareBaseU2
******************************************************************************/
grlAPI Gcompare gsCompareBaseU2(Gs const * const a, Gc2 const * const b)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU2(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBase(a, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsCompareBaseCount

Compare the base strings together.  Ignores locale so order may not
honour dictionary/telephone/region order.  Read up on this at
unicode.org

Compares first Count letters.
******************************************************************************/
grlAPI Gcompare gsCompareBaseCount(Gs const * const as, Gs const * const bs, Gcount const count)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gc     a,
          b;

   genter;

   greturnIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, gMIN(count, acount))
   {
      breakIf(index >= bcount);

      a = gcToLowerCase(*gsGetAt(as, index));//lint !e732
      b = gcToLowerCase(*gsGetAt(bs, index));//lint !e732

      greturnIf(a < b, gcompareLESS_THAN);
      greturnIf(a > b, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/******************************************************************************
** FUNC: gsCompareBaseCountA
******************************************************************************/
grlAPI Gcompare gsCompareBaseCountA(Gs const * const a, Char const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromA(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareBaseCountU1
******************************************************************************/
grlAPI Gcompare gsCompareBaseCountU1(Gs const * const a, Gc1 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU1(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareBaseCountU2
******************************************************************************/
grlAPI Gcompare gsCompareBaseCountU2(Gs const * const a, Gc2 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU2(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareBaseCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsCompareCount
******************************************************************************/
grlAPI Gcompare gsCompareCount(Gs const * const as, Gs const * const bs, Gcount const count)
{
   Gcount acount,
          bcount;
   Gindex index;
   Gc2    a,
          b;

   genter;

   greturnIf(
         !as ||
         !bs,
      gcompareEQUAL);

   acount = gsGetCount(as);
   bcount = gsGetCount(bs);

   forCount(index, gMIN(count, acount))
   {
      breakIf(index >= bcount);

      a = *gsGetAt(as, index);
      b = *gsGetAt(bs, index);

      greturnIf(a < b, gcompareLESS_THAN);
      greturnIf(a > b, gcompareGREATER_THAN);
   }

   greturn gcompareEQUAL;
}

/******************************************************************************
** FUNC: gsCompareCountA
******************************************************************************/
grlAPI Gcompare gsCompareCountA(Gs const * const a, Char const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromA(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareCountU1
******************************************************************************/
grlAPI Gcompare gsCompareCountU1(Gs const * const a, Gc1 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU1(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsCompareCountU2
******************************************************************************/
grlAPI Gcompare gsCompareCountU2(Gs const * const a, Gc2 const * const b, Gcount const count)
{
   Gs     *stemp;
   Gcompare  result;

   genter;

   greturnIf(
         !a ||
         !b,
      gcompareEQUAL);

   stemp  = gsCreateFromU2(b);
   greturnIf(!stemp, gcompareEQUAL);

   result = gsCompareCount(a, stemp, count);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsCreateA

Create the Ascii string.
******************************************************************************/
grlAPI Char *gsCreateA_(Gs const * const str)
{
   Gindex index;
   Gcount count;
   Char  *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.
   stemp = gmemCreateTypeArray(Char, gsGetCount(str) + 1);//lint !e666
   greturnNullIf(!stemp);

   // copy the letters over.
   count = gsGetCount(str);
   forCount(index, count)
   {
      stemp[index] = (Char) gcToA(*gsGetAt(str, index));//lint !e666 !e732
   }

   greturn stemp;
}

/***************************************************************************************
 * FUNC: gsCreateJoin_
 *
 * Essential an inverse of gsCreateSplit(). This takes a garray of
 * Gs's and joins them "with" the characters.
 *
 * For example, if your GsArray contained: ["a", "b", "c"] and you
 * joined with ";". Then you would get a result string: "a;b;c".
 *
 * An empty GsArray will result in an blank string that satisfies
 * gsIsEmpty().
 *
 * PARAM:
 * stringvec
 *    GsArray *
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
 ***************************************************************************************/
grlAPI Gs *gsCreateJoin_(GsArray const * const v, Gs const * const sep)
{
   Gs              *joined;
   Gs        const *stemp;
   Gcount           numstrings;
   Gindex           laststring,
                    i;
   GsArray   const *vector;

   genter;

   greturnNullIf(!v);

   vector = v; //lint !e929 !e960

   joined = gsCreate();
   greturnNullIf(!joined);

   // For each string in the string list, clone the string,
   // append the character seperator and then append the
   // result to the joined string.
   numstrings = gsArrayGetCount(vector);
   laststring = numstrings - 1;

   for (i = 0; i != numstrings; ++i )
   {
      stemp = gsArrayGetAt(vector, i);
      if (stemp == NULL)
      {
         gsDestroy(joined);
         joined = NULL;
         greturn NULL;   //lint !e438
      }

      greturnNullIf(!gsAppend(joined, stemp));
      if (i != laststring)
      {
         greturnNullIf(!gsAppend(joined, sep));
      }
   }

   greturn joined;
}

/******************************************************************************
** FUNC: gsCreateJoinA_
******************************************************************************/
grlAPI Gs *gsCreateJoinA_(GsArray const * const v, Char const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsCreateFromA(sep);
   greturnNullIf(!stemp);

   sresult = gsCreateJoin(v, stemp);

   gsDestroy(stemp);

   greturn sresult;
}

/******************************************************************************
** FUNC: gsCreateJoinU1_
******************************************************************************/
grlAPI Gs *gsCreateJoinU1_(GsArray const * const v, Gc1 const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsCreateFromU1(sep);
   greturnNullIf(!stemp);

   sresult = gsCreateJoin(v, stemp);

   gsDestroy(stemp);

   greturn sresult;
}

/******************************************************************************
** FUNC: gsCreateJoinU2_
******************************************************************************/
grlAPI Gs *gsCreateJoinU2_(GsArray const * const v, Gc2 const * const sep)
{
   Gs *stemp,
        *sresult;

   genter;

   greturnNullIf(
      !v ||
      !sep);

   stemp   = gsCreateFromU2(sep);
   greturnNullIf(!stemp);

   sresult = gsCreateJoin(v, stemp);

   gsDestroy(stemp);

   greturn sresult;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsEraseSub(Gs * const str, Gindex const start, Gindex const end)
{
   Gindex startTemp,
          endTemp;

   genter;

   greturnNullIf(!str);

   greturnNullIf(start > end);

   // fix start and end.
   startTemp = gMIN(gsGetCount(str), start);//lint !e666
   endTemp   = gMIN(gsGetCount(str), end);//lint !e666

   greturnNullIf(!gsCopy(str, (str->count - endTemp) + 1, endTemp, startTemp));

   greturnNullIf(!gsSetCount(str, gsGetCount(str) - (endTemp - startTemp)));

   greturn str;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gs *gsFindAndReplace(Gs * const str, Gs const * const find, Gs const * const replace,
   Gcount * const count)
{
   Gindex idx;
   Gs    *temp,
         *result;

   genter;

   greturnNullIf(
      !str ||
      !find);

   result = NULL;

   if (count)
   {
      *count = 0;
   }

   if (gsGetCount(str) != 0)
   {
      idx  = 0;
      temp = gsCreate();
      greturnNullIf(!temp);

      // Find all occurances of the find string and replace them with the
      // replace string.
      loop
      {
         idx = gsFindSub(str, 0, find);
         breakIf(idx == gsFIND_FAIL);

         if (count)
         {
            *count = *count + 1;
         }

         // Move the bits over to the temp string.
         stopIf(!gsAppendSub(temp, str, 0, idx));
         stopIf(!gsAppend(   temp, replace));

         // Remove matched bits from the search string.
         stopIf(!gsEraseSub(str, 0, idx + gsGetCount(find)));

         // append the last bits of str.
         stopIf(!gsAppend(temp, str));

         // move the completed string back over.
         result = gsSet(str, temp);

         // reset temp.
         gsSetA(temp, "");
      }

STOP:
      gsDestroy(temp);
   }

   greturn result;
}

/******************************************************************************
** FUNC: gsFindAndReplaceA
******************************************************************************/
grlAPI Gs *gsFindAndReplaceA(Gs * const str, Char const * const find, 
   Char const * const  replace, Gcount * const count)
{
   Gs *fstr,
      *rstr,
      *result;

   genter;

   greturnIf(
         !str  ||
         !find ||
         !replace,
      NULL);

   result = NULL;
   fstr   = gsCreateFromA(find);
   if (fstr)
   {
      rstr = gsCreateFromA(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDestroy(rstr);
      }
      gsDestroy(fstr);
   }
   
   greturn result;
}

/******************************************************************************
** FUNC: gsFindAndReplaceU1
******************************************************************************/
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
   fstr = gsCreateFromU1(find);
   if (fstr)
   {
      rstr = gsCreateFromU1(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDestroy(rstr);
      }
      gsDestroy(fstr);
   }

   greturn result;
}

/******************************************************************************
** FUNC: gsFindAndReplaceU2
******************************************************************************/
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
   fstr   = gsCreateFromU2(find);
   if (fstr)
   {
      rstr = gsCreateFromU2(replace);
      if (rstr)
      {
         result = gsFindAndReplace(str, fstr, rstr, count);
         gsDestroy(rstr);
      }
      gsDestroy(fstr);
   }

   greturn result;
}

/******************************************************************************
func: gsFindFirstCSVComma

Find the first comma in a comma separated value string.
******************************************************************************/
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
         if (*gsGetAt(str, index) == L'"')
         {
            isInQuotes = gbFALSE;
         }
      }
      // outside quotes
      else
      {
         if (*gsGetAt(str, index) == L'"')
         {
            isInQuotes = gbTRUE;
         }
         else
         {
            breakIf(*gsGetAt(str, index) == L',');
         }
      }
   }

   // Nothing found
   if (index >= gsGetCount(str))
   {
      index = gsFIND_FAIL;
   }

   greturn index;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gindex gsFindFirstNotOf(Gs const * const str, Gindex const position, 
   Gs const * const letters)
{
   Gindex a,
          b;
   Gb     found;
   Gc2    aletter;

   genter;

   greturnIf(
         !str ||
         !letters,
      gsFIND_FAIL);

   for (a = position; a < gsGetCount(str); a++)
   {
      aletter = *gsGetAt(str, a);

      found = gbTRUE;
      forCount(b, gsGetCount(letters))
      {
         if (aletter == *gsGetAt(letters, b))
         {
            found = gbFALSE;
         }
      }

      greturnIf(found, a);
   }

   greturn gsFIND_FAIL;
}

/******************************************************************************
** FUNC: gsFindFirstNotOfA
******************************************************************************/
grlAPI Gindex gsFindFirstNotOfA(Gs const * const str, Gindex const position, 
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromA(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindFirstNotOfU1
******************************************************************************/
grlAPI Gindex gsFindFirstNotOfU1(Gs const * const str, Gindex const position,
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU1(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindFirstNotOfU2
******************************************************************************/
grlAPI Gindex gsFindFirstNotOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU2(letters);
   result = gsFindFirstNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gindex gsFindFirstOf(Gs const * const str, Gindex const position, 
   Gs const * const letters)
{
   Gindex a,
          b;
   Gc2    aletter;

   genter;

   greturnIf(
         !str ||
         !letters,
      gsFIND_FAIL);

   for (a = position; a < gsGetCount(str); a++)
   {
      aletter = *gsGetAt(str, a);

      forCount(b, gsGetCount(letters))
      {
         greturnIf(aletter == *gsGetAt(letters, b), a);
      }
   }
   greturn gsFIND_FAIL;
}

/******************************************************************************
** FUNC: gsFindFirstOfA
******************************************************************************/
grlAPI Gindex gsFindFirstOfA(Gs const * const str, Gindex const position, 
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromA(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindFirstOfU1
******************************************************************************/
grlAPI Gindex gsFindFirstOfU1(Gs const * const str, Gindex const position, 
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU1(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindFirstOfU2
******************************************************************************/
grlAPI Gindex gsFindFirstOfU2(Gs const * const str, Gindex const position, 
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU2(letters);
   result = gsFindFirstOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
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
******************************************************************************/
grlAPI Gindex gsFindLastNotOf(Gs const * const str, Gindex const position, 
   Gs const * const letters)
{
   Gindex a,
          b;
   Gb     found;
   Gc2    aletter;

   genter;

   greturnIf(
         !str     ||
         !letters,
      gsFIND_FAIL);

   for (a = gsGetCount(str) - 1; a >= position; a--)
   {
      aletter = *gsGetAt(str, a);

      found = gbTRUE;
      forCount(b, gsGetCount(letters))
      {
         if (aletter == *gsGetAt(letters, b))
         {
            found = gbFALSE;
            break;
         }
      }

      greturnIf(found, a);

      // End of the search.
      breakIf(!a);
   }
   greturn gsFIND_FAIL;
}

/******************************************************************************
** FUNC: gsFindLastNotOfA
******************************************************************************/
grlAPI Gindex gsFindLastNotOfA(Gs const * const str, Gindex const position,
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromA(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindLastNotOfU1
******************************************************************************/
grlAPI Gindex gsFindLastNotOfU1(Gs const * const str, Gindex const position, 
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU1(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindLastNotOfU2
******************************************************************************/
grlAPI Gindex gsFindLastNotOfU2(Gs const * const str, Gindex const position,
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU2(letters);
   result = gsFindLastNotOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
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
   The position of the letter or -1 if not present in the string.
******************************************************************************/
grlAPI Gindex gsFindLastOf(Gs const * const str, Gindex const position, 
   Gs const * const letters)
{
   Gindex a,
          b;
   Gc2    aletter;

   genter;

   greturnIf(
         !str     ||
         !letters,
      gsFIND_FAIL);

   for (a = gsGetCount(str) - 1; a >= position; a--)
   {
      aletter = *gsGetAt(str, a);

      forCount(b, gsGetCount(letters))
      {
         greturnIf(aletter == *gsGetAt(letters, b), a);
      }

      // End of the string.
      breakIf(!a);
   }

   greturn gsFIND_FAIL;
}

/******************************************************************************
** FUNC: gsFindLastOfA
******************************************************************************/
grlAPI Gindex gsFindLastOfA(Gs const * const str, Gindex const position, 
   Char const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromA(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindLastOfU1
******************************************************************************/
grlAPI Gindex gsFindLastOfU1(Gs const * const str, Gindex const position, 
   Gc1 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU1(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindLastOfU2
******************************************************************************/
grlAPI Gindex gsFindLastOfU2(Gs const * const str, Gindex const position, 
   Gc2 const * const letters)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU2(letters);
   result = gsFindLastOf(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
func: gsFindSub

Find a substring in a string.

param:
str, substr
   Gs *, Gs *
   in, in
   the string.

return:
int
   position of the substring or -1 if not found.
******************************************************************************/
grlAPI Gindex gsFindSub(Gs const * const str, Gindex const position, 
   Gs const * const substr)
{
   // This is a stupid simple algorithm just to get it done.  I didn't
   // use CRT wcsstr() because I'm not sure if the result is letter
   // count to the position of the substring or array count.  With U2,
   // some characters can span two array locations.

   // This code was taken from strstr() and modified for Gcs.
   // Which I'm surprised that it isn't more complex.  There are
   // faster string search algorithms.
   Gc2 const *cp,
             *s1,
             *s2;

   genter;

   greturnIf(
         !str ||
         !substr,
      gsFIND_FAIL);

   cp = gsGetAt(str, position);
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
      greturnIf(!*s2, (Gindex) (cp - gsGet(str)));//lint !e732 !e947 !e946

      // substring is longer than the rest of the
      // search string.  Terminate.
      breakIf(!*s1 && *s2);

      cp++;
   }

   greturn gsFIND_FAIL;
}

/******************************************************************************
** FUNC: gsFindSubA
******************************************************************************/
grlAPI Gindex gsFindSubA(Gs const * const str, Gindex const position, 
   Char const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromA(substr);
   result = gsFindSub(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindSubU1
******************************************************************************/
grlAPI Gindex gsFindSubU1(Gs const * const str, Gindex const position, 
   Gc1 const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU1(substr);
   result = gsFindSub(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFindSubU2
******************************************************************************/
grlAPI Gindex gsFindSubU2(Gs const * const str, Gindex const position, 
   Gc2 const * const substr)
{
   Gs    *lstr;
   Gindex result;

   genter;

   lstr   = gsCreateFromU2(substr);
   result = gsFindSub(str, position, lstr);
   gsDestroy(lstr);

   greturn result;
}

/******************************************************************************
** FUNC: gsFromCSV
**
** Adjust the string from a CSV field.
******************************************************************************/
grlAPI Gs *gsFromCSV(Gs * const str)
{
   Gindex a;

   genter;

   greturnIf(
         !str ||
         gsGetCount(str) == 0,
      str);

   // CSV if a string is in " then a comma or a quote appears in the string.
   if (*gsGetBegin(str) == L'"')
   {
      // Remove the enclosing quotes.
      greturnNullIf(!gsEraseSub(str, 0, 1));
      greturnNullIf(!gsEraseSub(str, gsGetCount(str) - 1, gsGetCount(str)));

      // Search for double double quotes.
      for (a = gsGetCount(str) - 1; ; a--)
      {
         // "" gets translated to ".  "[x] should not happen.
         if (*gsGetAt(str, a)     == L'"' &&
             *gsGetAt(str, a - 1) == L'"')
         {
            greturnNullIf(!gsEraseSub(str, a, a + 1));
         }

         breakIf(a == 1);
      }
   }

   greturn str;
}

/******************************************************************************
func: gsGetI
******************************************************************************/
grlAPI Gi gsGetI(Gs const * const str)
{
#if 0
   Gc2 *stemp;
#endif
   Gi   itemp;

   genter;

   greturn0If(!str);

#if 0
   stemp = gsCreateU2(str);
   itemp = (Gi) _wtoi64(stemp);
   gmemDestroy(stemp);
#else
   itemp = (Gi) _wtoi64(gsGet(str));
#endif

   greturn itemp;
}

/******************************************************************************
func: gsGetII
Parses "[I]?[I]" wheren ? can be any character that does not appear in an 
integer.
******************************************************************************/
grlAPI void gsGetII(Gs const * const str, Gi * const a, Gi * const b)
{
   Gindex itemp;
   Gs    *next;

   genter;

   greturnVoidIf(!str);

   *a = (Gi) _wtoi64(gsGet(str));

   itemp = gsFindFirstNotOfA(str, 0, "0123456789+-");
   next  = gsCreateFromSub(str, itemp + 1, GindexMAX);

   *b = (Gi) _wtoi64(gsGet(next));

   gsDestroy(next);

   greturn;
}

/******************************************************************************
func: gsGetN
******************************************************************************/
grlAPI Gn gsGetN(Gs const * const str)
{
#if 0
   Gc2 *stemp;
#endif
   Gi   ntemp;

   genter;

   greturn0If(!str);

#if 0
   stemp = gsCreateU2(str);
   ntemp = (Gi) _wtoi64(stemp);
   gmemDestroy(stemp);
#else
   ntemp = (Gi) _wtoi64(gsGet(str));
#endif

   greturn (Gn) ntemp;
}

/******************************************************************************
func: gsGetR
******************************************************************************/
grlAPI Gr gsGetR(Gs const * const str)
{
#if 0
   Gc2 *stemp;
#endif
   Gr      rtemp;

   genter;

   greturn0If(!str);

#if 0
   stemp = gsCreateU2(str);
   rtemp = _wtof(stemp);
   gmemDestroy(stemp);
#else
   rtemp = _wtof(gsGet(str));
#endif

   greturn rtemp;
}

/******************************************************************************
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
******************************************************************************/
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
      hash = (hash << 4) + (GhashN) *gsGetAt(str, a);

      // g holds the top half byte of the hash value.
      g = hash & 0xf0000000;

      // If the value gets too large then adjust it.
      if (g)
      {
         hash = hash ^ (g >> 24);//lint !e704
         hash = hash ^ g;
      }
   }

   // greturn the hash value & GiMAX to keep the value positive
   greturn hash & GhashNMAX;
}

/******************************************************************************
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
******************************************************************************/
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
      Gs *temp = gsCreate();

      greturnNullIf(!gsAppendSub(temp, dst, 0, position));
      greturnNullIf(!gsAppend(   temp, src));
      greturnNullIf(!gsAppendSub(temp, dst, position, gsGetCount(dst)));

      greturnNullIf(!gsSet(dst, temp));

      gsDestroy(temp);
   }//lint !e953

   greturn dst;
}

/******************************************************************************
** FUNC: gsInsertFormat
******************************************************************************/
grlAPI Gs *gsInsertFormat(Gs * const dst, Gindex const position, 
   Gs const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsCreateFrom(src), format);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertA
******************************************************************************/
grlAPI Gs *gsInsertA(Gs * const dst, Gindex const position, Char const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsCreateFromA(src);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertFormatA
******************************************************************************/
grlAPI Gs *gsInsertFormatA(Gs * const dst, Gindex const position, 
   Char const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsCreateFromA(src), format);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertU1
******************************************************************************/
grlAPI Gs *gsInsertU1(Gs * const dst, Gindex const position, Gc1 const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsCreateFromU1(src);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertFormatU1
******************************************************************************/
grlAPI Gs *gsInsertFormatU1(Gs * const dst, Gindex const position, 
   Gc1 const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsCreateFromU1(src), format);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertU2
******************************************************************************/
grlAPI Gs *gsInsertU2(Gs * const dst, Gindex const position, Gc2 const * const src)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = gsCreateFromU2(src);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsInsertFormatU2
******************************************************************************/
grlAPI Gs *gsInsertFormatU2(Gs * const dst, Gindex const position, 
   Gc2 const * const src, Gc2 const * const format)
{
   Gs *stemp,
      *result;

   genter;

   stemp  = _FormatString(gsCreateFromU2(src), format);
   result = gsInsert(dst, position, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gsIsBlank
******************************************************************************/
grlAPI Gb gsIsBlank(Gs const *const str)
{
   genter;

   greturnTrueIf(gsIsEmpty(str));

   greturnTrueIf(gsFindFirstNotOfA(str, 0, WHITESPACE_A) == gsFIND_FAIL);

   greturn gbFALSE;
}

/******************************************************************************
func: gsIsMultiline
******************************************************************************/
grlAPI Gb gsIsMultiline(Gs const * const str)
{
   Gindex index;

   genter;

   for (index = 0; ; index++)
   {
      breakIf(index >= gsGetCount(str));

      returnIf(*gsGetAt(str, index) == L'\n', gbTRUE);
   }

   greturn gbFALSE;
}

/******************************************************************************
func: gsReverse

Reverse the string.

param:
dst
   Gs *
   in
   The string.
******************************************************************************/
grlAPI Gs *gsReverse(Gs * const str)
{
   Gindex a;
   Gc2    temp;

   genter;

   if (!str)
   {
      greturn str;
   }

   forCount(a, gsGetCount(str) / 2)
   {
      temp = *gsGetAt(str, a);
      greturnNullIf(!gsUpdateAt(str, a, gsGetAt(str, (gsGetCount(str) - 1) - a)));
      greturnNullIf(!gsUpdateAt(str, (gsGetCount(str) - 1) - a, &temp));
   }

   greturn str;
}

/******************************************************************************
func: gsPadTail
******************************************************************************/
grlAPI Gs *gsPadTail(Gs * const str, Gcount const length, Gc2 const letter)
{
   genter;

   for (; gsGetCount(str) < length;)
   {
      greturnNullIf(!gsAppendC(str, letter));
   }

   greturn str;
}

/******************************************************************************
func: gsCreateSplit_

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
   Gs    *str   = gsCreateFromA("this;is;a;test");
   GsArray *split = gsCreateSplit(str, ";");

   for (i = 0 ; i != garrayGetCount(split); ++i)
   {
     Gs *token = (Gs *) garrayGet(split, i);
     printf("token is: %s.\n", gsGetA(token));
   }
   garrayForEach(split, gsDestroy);
   garrayDestroy(split);

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
GsArray *
   An GsArray, N elements in length, where N is equal to the number
   of substrings split off the the orginal.

   Make sure you use garrayForEach(v, gsDestroy) on the
   greturned vector. See USAGE.

   Some example calls,
      gsCreateSplit("this,is,a,test", ",") -> ["this", "is", "a", "test"]
      gsCreateSplit("this;is;", ";")       -> ["this", "is", ""]
      gsCreateSplit("!!!", "!")            -> ["", "", "", ""]
      gsCreateSplit("", ",")               -> [""]

   NULL is greturned if there is no more memory, otherwise a garray
   is always greturned. The length of the garray indicates success
   or failure.  Note that an empty vector is defined by garrayIsEmpty().
******************************************************************************/
grlAPI GsArray *gsCreateSplit_(Gs const * const str, Gc const letter)
{
   Gindex   index;
   GsArray *slist;
   Gs      *substr;

   genter;

   greturnNullIf(
      !str ||
      !letter);

   slist = gsArrayCreate((GrlCompareFunc) NULL, gbTRUE);
   greturnNullIf(!slist);

   // Non recursive despite the function name.
   forCount(index, gsGetCount(str))
   {
      // Find the substrings;
      substr = gsCreate();
      for (; index < gsGetCount(str); index++) //lint !e445
      {
         breakIf(*gsGetAt(str, index) == (Gc2) letter);

         greturnNullIf(!gsAppendC(substr, *gsGetAt(str, index)));
      }
      greturnNullIf(!gsArrayAddEnd(slist, substr));
   }

   greturn slist; //lint !e850
}

/******************************************************************************
func: gsCreateU1
******************************************************************************/
grlAPI Gc1 *gsCreateU1_(Gs const * const str)
{
   Gc1    la,
          lb,
          lc,
          ld;
   Gindex index,
          b;
   Gcount lsize,
          count;
   Gc1   *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.  Oversized but for worst case it'll do.
   count = gsGetCount(str);
   stemp = (Gc1 *) gmemCreateTypeArray(Gc1, count * 4); //lint !e926
   greturnNullIf(!stemp);

   // copy the letters over.
   b = 0;
   forCount(index, count)
   {
      lsize = gcToU1(*gsGetAt(str, index), &la, &lb, &lc, &ld); //lint !e732

                        stemp[b++] = la;
      if (lsize >= 2) { stemp[b++] = lb; }
      if (lsize >= 3) { stemp[b++] = lc; }
      if (lsize >= 4) { stemp[b++] = ld; }
   }

   greturn stemp;
}

/******************************************************************************
func: gsCreateU2
******************************************************************************/
grlAPI Gc2 *gsCreateU2_(Gs *str)
{
   Gc2   la,
         lb;
   Gi4   index,
         b,
         lsize,
         count;
   Gc2  *stemp;

   genter;

   greturnNullIf(!str);

   // Allocate the buffer.  Oversized but for worst case it'll do.
   count = gsGetCount(str);
   stemp = gmemCreateTypeArray(Gc2, count * 2);
   greturnNullIf(!stemp);

   // copy the letters over.
   b = 0;
   forCount(index, count)
   {
      lsize = gcToU2(*gsGetAt(str, index), &la, &lb);

                        stemp[b++] = la;
      if (lsize == 2) { stemp[b++] = lb; }
   }

   greturn stemp;
}

/******************************************************************************
func: gsStrip

strip stuff from the string.

param:
str
   Gs *
   in
   the string.

type
   GcStripType
   in
   what to strip.
******************************************************************************/
grlAPI Gs *gsStrip(Gs * const str, GcStrip const type)
{
   Gindex a,
          b;
   Gb     leadingWhite,
          inquotes;
   Gb     isEscaped;
   Gc2    backslash,
          quote;

   genter;

   greturnNullIf(!str);

   // Init
   backslash = (Gc2) '\\';
   quote     = (Gc2) '"';

   leadingWhite = gbTRUE;
   inquotes     = gbFALSE;
   isEscaped    = gbFALSE;

   // Pass 1.  Remove trailing whitespace.
   if (type & gcStripWHITE_SPACE_TRAILING &&
       gsGetCount(str) > 0)
   {
      for (a = gsGetCount(str) - 1; ; a--)
      {
         // move the null terminator up.
         if (gcIsWhiteSpace(*gsGetAt(str,a))) //lint !e732
         {
            breakIf(!gsSetCount(str, gsGetCount(str) - 1));

            // An escaped blank is still a trailing blank.
            if (a &&
                *gsGetAt(str, a - 1) == backslash)
            {
               a = a - 1;

               breakIf(!gsSetCount(str, gsGetCount(str) - 1));
            }
         }
         else
         {
            break;
         }

         breakIf(a == 0);
      }
   } //lint !e850

   /* Pass 2. Take care of white space (leading and all) and
   escape characters. */
   b = 0;
   forCount(a, gsGetCount(str))
   {
      // Check for leading and internal white space.
      if ((type & gcStripWHITE_SPACE           &&
           !inquotes)                                ||
          type & gcStripWHITE_SPACE_ALL           ||
          (type & gcStripWHITE_SPACE_LEADING   &&
           leadingWhite))
      {
         // White space
         continueIf(gcIsWhiteSpace(*gsGetAt(str, a))); //lint !e732

         // First non white space.
         // an escaped white space is still a white space.
         continueIf(
            !isEscaped                    &&
            *gsGetAt(str, a) == backslash &&
            gcIsWhiteSpace(*gsGetAt(str, a + 1))); //lint !e732

         // last of the leading blanks.
         leadingWhite = gbFALSE;
      }

      // Check for escape character
      if (!isEscaped &&
          *gsGetAt(str, a) == backslash)
      {
         isEscaped = 2;
      }

      if (isEscaped != 1                        &&
          ((type & gcStripESCAPE_CHAR &&
            !inquotes)                       ||
           type & gcStripESCAPE_CHAR_ALL))
      {
         if (*gsGetAt(str, a) == backslash)
         {
            // skip it
            isEscaped--;
            continue;
         }
      }

      // Quote character
      if (*gsGetAt(str, a) == quote)
      {
         // Make sure the character isn't escaped.
         if ((a &&
              *gsGetAt(str, a - 1) != backslash) ||
             !a)
         {
            inquotes = (Gb) !inquotes; //lint !e930
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

/******************************************************************************
func: gsStripCompress

Compress the white space runs to one space.
******************************************************************************/
grlAPI Gs *gsStripCompress(Gs * const str)
{
   Gindex a,
          b;
   Gb     found;

   genter;

   greturnNullIf(!str);

   // Get rid of the leading and trailing space.
   greturnNullIf(!gsStrip(str, gcStripWHITE_SPACE_LEADING | gcStripWHITE_SPACE_TRAILING));

   // Remove all but one from the other strings of spaces.
   found = gbFALSE;

   b = 0;
   forCount(a, gsGetCount(str))
   {
      if (!found)
      {
         if (gcIsWhiteSpace((Gc) *gsGetAt(str, a))) //lint !e732
         {
            found = gbTRUE;
         }
      }
      else
      {
         // Only accept one white space.  Trim the others.
         continueIf(gcIsWhiteSpace((Gc) *gsGetAt(str, a))); //lint !e732

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

/******************************************************************************
** FUNC: gsToCSV
**
** Adjusts the string so that it can live in a CSV file.
******************************************************************************/
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
   if (gsFindFirstOfA(str, 0, "\",") != gsFIND_FAIL)
   {
      Gs *temp = gsCreate();

      greturnNullIf(!gsAppendC(temp, L'"'));

      // double the double quotes.
      forCount(a, gsGetCount(str))
      {
         if (*gsGetAt(str, a) == L'"')
         {
            greturnNullIf(!gsAppendC(temp, L'"'));
         }
         greturnNullIf(!gsAppendC(temp, *gsGetAt(str, a)));
      }

      greturnNullIf(!gsAppendC(temp, L'"'));

      greturnNullIf(!gsSet(str, temp));

      gsDestroy(temp);
   }//lint !e953

   greturn str;
}

/******************************************************************************
** FUNC: gsToFormat
**
** See Append for more information.
******************************************************************************/
grlAPI Gs *gsToFormat(Gs * const str, Gc2 const * const format)
{
   genter;

   greturnIf(
         !str ||
         !format,
      str);

   greturn _FormatString(str, format);
}

/******************************************************************************
func: gsToLowerCase

Convert the string to all lower case letters.

param:
dst
   Gs *
   in
   The string.
******************************************************************************/
grlAPI Gs *gsToLowerCase(Gs * const str)
{
   Gindex a;
   Gc2    letter;

   genter;

   greturnNullIf(!str);

   forCount(a, gsGetCount(str))
   {
      letter = gcToLowerCase(*gsGetAt(str, a));
      greturnNullIf(!gsUpdateAt(str, a, &letter));
   }

   greturn str;
}

/******************************************************************************
func: gsToUpperCase

Convert the string to all upper case letters.

param:
dst
   Gs *
   in
   The string.
******************************************************************************/
grlAPI Gs *gsToUpperCase(Gs * const str)
{
   Gindex a;
   Gc2    letter;

   genter;

   greturnIf(!str, str);

   forCount(a, gsGetCount(str))
   {
      letter = gcToUpperCase(*gsGetAt(str, a));
      gsUpdateAt(str, a, &letter); //lint !e534
   }

   greturn str;
}

/******************************************************************************
 * FUNC: gsTrim
 *
 * Performs a left and right trim in succcession.  If you
 * wished to trim all the WHITESPACE from a string you
 * would use,
 *
 * gsModifyTrimA(str, WHITESPACE_A);
 *
 * PARAM:
 * str
 *    Gs *
 *    in/out
 *    The string to modify.  Modifications are destructive.
 *
 * letters
 *    Char *
 *    in
 *    The set of letters you wish have trimmed from a string.
 *******************************************************************/
grlAPI Gs *gsTrim(Gs * const str, Gs const * const letters)
{
   Gs *result;

   genter;

   greturnIf(
         !str ||
         !letters,
      str);

   // Right side first because it'll make Trim left cheaper.
   result = gsTrimLeft(gsTrimRight(str, letters), letters);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimA
******************************************************************************/
grlAPI Gs *gsTrimA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromA(letters);
   result = gsTrim(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimU1
******************************************************************************/
grlAPI Gs *gsTrimU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU1(letters);
   result = gsTrim(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimU2
******************************************************************************/
grlAPI Gs *gsTrimU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU2(letters);
   result = gsTrim(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
 * FUNC: gsTrimLeft
 *
 * Performs a left trim on a string. Trimmed characters
 * are all those characters in the letters parameters.
 *
 * PARAM:
 * str
 *    Gs *
 *    in/out
 *    The string to modify.  Modifications are destructive.
 *
 * letters
 *    Char *
 *    in
 *    The set of letters you wish have trimmed from a string.
 *******************************************************************/
grlAPI Gs *gsTrimLeft(Gs * const str, Gs const * const letters)
{
   Gs    *result;
   Gindex idx;

   genter;

   greturnIf(
         !str ||
         !letters,
      str);

   idx = gsFindFirstNotOf(str, 0, letters);

   if (idx != gsFIND_FAIL)
   {
      result = gsEraseSub(str, 0, idx);

      greturn result;
   }

   result = str;

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimLeftA
******************************************************************************/
grlAPI Gs *gsTrimLeftA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromA(letters);
   result = gsTrimLeft(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimLeftU1
******************************************************************************/
grlAPI Gs *gsTrimLeftU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU1(letters);
   result = gsTrimLeft(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimLeftU2
******************************************************************************/
grlAPI Gs *gsTrimLeftU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU2(letters);
   result = gsTrimLeft(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
 * FUNC: gsTrimRight
 *
 * Performs a right trim on a string. Trimmed characters
 * are all those characters in the letters parameters.
 *
 * PARAM:
 * str
 *    Gs *
 *    in/out
 *    The string to modify.  Modifications are destructive.
 *
 * letters
 *    Char *
 *    in
 *    The set of letters you wish have trimmed from a string.
 *******************************************************************/
grlAPI Gs *gsTrimRight(Gs * const str, Gs const * const letters)
{
   Gs    *result;
   Gindex idx;

   genter;

   greturnIf(
         !str ||
         !letters,
      str);

   idx = gsFindLastNotOf(str, gsGetCount(str), letters);

   if (idx != gsFIND_FAIL)
   {
      result = gsEraseSub(str, idx, gsGetCount(str));

      greturn result;
   }

   result = str;

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimRightA
******************************************************************************/
grlAPI Gs *gsTrimRightA(Gs * const str, Char const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromA(letters);
   result = gsTrimRight(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimRightU1
******************************************************************************/
grlAPI Gs *gsTrimRightU1(Gs * const str, Gc1 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU1(letters);
   result = gsTrimRight(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
** FUNC: gsTrimRightU2
******************************************************************************/
grlAPI Gs *gsTrimRightU2(Gs * const str, Gc2 const * const letters)
{
   Gs *stemp,
        *result;

   genter;

   stemp  = gsCreateFromU2(letters);
   result = gsTrimRight(str, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gvDestroyS

Used with the containers that store a gv for pointers.
******************************************************************************/
grlAPI void gvDestroyS(Gv * const value)
{
   genter;

   gsDestroy((Gs *) gvGetP(value));

   greturn;
}

/******************************************************************************
local
function
******************************************************************************/
/******************************************************************************
** FUNC: _Format*
**
** Format an integer.
******************************************************************************/
static Gs *_FormatI(Gi const i, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, i) == -1);

   result = gsCreateFromU2(ctemp);

   greturn result;
}

static Gs *_FormatN(Gn const n, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, n) == -1);

   result = gsCreateFromU2(ctemp);

   greturn result;
}

static Gs *_FormatR(Gr const r, Gc2 const * const format)
{
   Gs *result;
   Gc2 ctemp[1024];

   genter;

   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, r) == -1);

   result = gsCreateFromU2(ctemp);

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
   stemp = gsCreateU2(str);
   swprintf_s(ctemp, 1024, format, stemp);
   gmemDestroy(stemp);
#else
   greturnNullIf(swprintf_s(ctemp, (size_t) 1024, format, gsGet(str)) == -1)
#endif

   greturnNullIf(!gsSetU2(str, ctemp));

   greturn str;
}

#if 0
/******************************************************************************
func: _GetByteLength

Get the length of the data the hard way.
******************************************************************************/
static Gcount _GetByteLength(Gp *ptr, GcType type)
{
   Gcount result;
   Gi4     a;
   Gc1 *c1p;
   Gc2 *c2p;
   Gc4 *c4p;

   genter;

   switch (type)
   {
   case gcTypeA:
      result = (Gcount) strlen((Char *) ptr);

      greturn result;

   case gcTypeU1:
      c1p = (Gc1 *) ptr;
      for (a = 0; ; a++)
      {
         greturnIf(
               c1p[a] == 0,
            (Gcount) (c1p - ((Gc1 *) ptr)));

         c1p = &(c1p[gcGetLetterByteCount((Gp *) c1p, type)]);
      }

   case gcTypeU2:
      c2p = (Gc2 *) ptr;
      for (a = 0; ; a++)
      {
         greturnIf(
               c2p[a] == 0,
            (Gcount) (c2p - ((Gc2 *) ptr)));

         c1p = (Gc1 *) c2p;
         c2p = (Gc2 *) &(c1p[gcGetLetterByteCount((Gp *) c1p, type)]);
      }

   case gcTypeU4:
      c4p = (Gc4 *) ptr;
      for (a = 0; ; a++)
      {
         greturnIf(
               c4p[a] == 0,
            (Gcount) (c4p - ((Gc4 *) ptr)));
      }
   }

   greturn 0;
}
#endif

/******************************************************************************
func: _GetLength

Get the length of the data the hard way.
******************************************************************************/
static Gcount _GetLength(Gp const * const ptr, GcType const type)
{
   Gcount       result;
   Gcount       a;
   const Gc1   *c1p;
   const Gc2   *c2p;
   const Gc4   *c4p;

   genter;

   switch (type)
   {
   case gcTypeA:
      result = (Gcount) strlen((const Char *) ptr); 

      greturn result;

   case gcTypeU1:
      c1p = (const Gc1 *) ptr; 
      for (a = 0; ; a++)
      {
         greturnIf(c1p[0] == 0, a);

         c1p = &(c1p[gcGetLetterByteCount((const Gp *) c1p, type)]); 
      }

   case gcTypeU2:
      c2p = (const Gc2 *) ptr; 
      for (a = 0; ; a++)
      {
         greturnIf(c2p[0] == 0, a);

         c1p = (const Gc1 *) c2p; //lint !e928
         c2p = (const Gc2 *) &(c1p[gcGetLetterByteCount((const Gp *) c1p, type)]); //lint !e926 !e927 !e826
      }

   case gcTypeU4:
      c4p = (const Gc4 *) ptr; 
      for (a = 0; ; a++)
      {
         greturnIf(c4p[a] == 0, a);
      }
   } //lint !e787

   greturn 0;
}
