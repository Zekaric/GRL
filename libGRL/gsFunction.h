/**************************************************************************************************
file:       gsFunction
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

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define gsSubStrINDEX_START      0
#define gsSubStrINDEX_END        GindexMAX

#define gsFIND_FAIL              GindexERROR

/**************************************************************************************************
const: GsStripMethod

Strip Whitespace enumeration

gsStripMethodESCAPE_CHAR - This will remove the escape letter "\"
This case will not touch these chars inside ""

gsStripMethodESCAPE_CHAR_ALL - This case will touch all cases

gsStripMethodWHITE_SPACE - This case will remove all white space
This case will not touch inside ""

gsStripMethodWHITE_SPACE_ALL - This will touch all cases

gsStripMethodWHITE_SPACE_ALL_BUT_ONE - This will reduce groups of
whitespace characters to " ".

gsStripMethodWHITE_SPACE_LEADING - Only leading white space.

gsStripMethodWHITE_SPACE_TRAILING - Only trailing white space.
**************************************************************************************************/
typedef enum
{
   gsStripMethodNONE                      = 0x00000000,

   gsStripMethodESCAPE_CHAR               = 0x00000001,
   gsStripMethodESCAPE_CHAR_ALL           = 0x00000002,

   gsStripMethodWHITE_SPACE               = 0x00000010,
   gsStripMethodWHITE_SPACE_ALL           = 0x00000020,

   gsStripMethodWHITE_SPACE_LEADING       = 0x10000000,
   gsStripMethodWHITE_SPACE_TRAILING      = 0x20000000

} GsStripMethod;

typedef enum
{
   gsOpDONE             = 0x00000000,

   // Next parameter is a...
   gsOpSTR              = 0x00000001,
   gsOpA                = 0x00000002,
   gsOpChar1            = 0x00000004,
   gsOpI                = 0x00000010,
   gsOpN                = 0x00000020,
   gsOpPARAMETER        = 0x000000FF,

   // Destory this parameter after the operation.
   // Mixed in with the above.
   gsOpDLOC             = 0x00000100,

   // Use a substring from this parameter, start and end index.
   gsOpSUB_STRING       = 0x00001000

} GsOp;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef enum
{
   gsParamTypeNONE,

   gsParamTypeA      = 0x00000001,
   gsParamTypeS      = 0x00000002,
   gsParamTypeS_DLOC = 0x10000002,
   gsParamTypeI      = 0x00000003,
   gsParamTypeN      = 0x00000004,
   gsParamTypeR      = 0x00000008,
} GsParamType;

#define GsHash  Gp

/**************************************************************************************************
prototype:
**************************************************************************************************/
// hand coded functions.
// gs
// Functions that greturn a Gs * may not greturn a 'new' Gs * but rather the same
// Gs * that was passed in.  This is so that you can daisy chain the functions
// together if you find that easier.
grlAPI Gs            *gsAppend(              Gs       * const str, Gs const * const value);
grlAPI Gs            *gsAppendA(             Gs       * const str, Char const * const value);
//grlAPI Gs            *gsAppendFormat(        Gs       * const str, Gs const * const value,                                       Char const * const format);
grlAPI Gs            *gsAppendGchar1(        Gs       * const str, Gchar1 const * const value);
grlAPI Gs            *gsAppendGchar2(        Gs       * const str, Gchar2 const * const value);
//grlAPI Gs            *gsAppendCharFormat(    Gs       * const str, Gchar const c,                                                Char const * const format);
grlAPI Gs            *gsAppendI(             Gs       * const str, Gi const i);
grlAPI Gs            *gsAppendLetter(        Gs       * const str, Gchar const c);
//grlAPI Gs            *gsAppendIFormat(       Gs       * const str, Gi const i,                                                   Char const * const format);
grlAPI Gs            *gsAppendN(             Gs       * const str, Gn const n);
//grlAPI Gs            *gsAppendNFormat(       Gs       * const str, Gn const n,                                                   Char const * const format);
grlAPI Gs            *gsAppendR(             Gs       * const str, Gr const r);
//grlAPI Gs            *gsAppendRFormat(       Gs       * const str, Gr const r,                                                   Char const * const format);
grlAPI Gs            *gsAppendSub(           Gs       * const str, Gs const * const value, Gindex const start, Gindex const end);
//grlAPI Gs            *gsAppendSubFormat(     Gs       * const str, Gs const * const value, Gindex const start, Gindex const end, Char const * const format);

grlAPI Gs            *gsAppendFormatted(     Gs       * const str, GsParamType formatType, ...);
grlAPI Gs            *gsAppendParams(        Gs       * const str, ...);

#define gsClocFrom(S)                              gleakClocType(gsAppend(            gsCloc(), (S)),                        Gs)
#define gsClocFromA(A)                             gleakClocType(gsAppendA(           gsCloc(), (A)),                        Gs)
#define gsClocFromGchar1(S)                        gleakClocType(gsAppendGchar1(      gsCloc(), (S)),                        Gs)
#define gsClocFromGchar2(S)                        gleakClocType(gsAppendGchar2(      gsCloc(), (S)),                        Gs)
#define gsClocFromI(I)                             gleakClocType(gsAppendI(           gsCloc(), (I)),                        Gs)
//#define gsClocFromIFormat(I, FMT)                  gleakClocType(gsAppendIFormat(     gsCloc(), (I), (FMT)),                 Gs)
#define gsClocFromN(N)                             gleakClocType(gsAppendN(           gsCloc(), (N)),                        Gs)
//#define gsClocFromNFormat(N, FMT)                  gleakClocType(gsAppendNFormat(     gsCloc(), (N), (FMT)),                 Gs)
#define gsClocFromR(R)                             gleakClocType(gsAppendR(           gsCloc(), (R)),                        Gs)
//#define gsClocFromRFormat(R, FMT)                  gleakClocType(gsAppendRFormat(     gsCloc(), (R), (FMT)),                 Gs)
//#define gsClocFromFormat(S, FMT)                   gleakClocType(gsAppendFormat(      gsCloc(), (S), (FMT)),                 Gs)
#define gsClocFromFormatted(PTYPE, ...)            gleakClocType(gsAppendFormatted(   gsCloc(), (PTYPE), __VA_ARGS__),       Gs)
#define gsClocFromParam(...)                       gleakClocType(gsAppendParams(      gsCloc(), __VA_ARGS__),                Gs)
#define gsClocFromSub(S, START, END)               gleakClocType(gsAppendSub(         gsCloc(), (S), (START), (END)),        Gs)
//#define gsClocFromSubFormat(S, START, END, FMT)    gleakClocType(gsAppendSubFormat(   gsCloc(), (S), (START), (END), (FMT)), Gs)

#define gsClocA(S)                                 gleakCloc(    gsClocA_(            (S)),                                  gsizeof(Char  ) * gsGetCount(S))
#define gsClocGchar1(S)                            gleakCloc(    gsClocChar1_(        (S)),                                  gsizeof(Gchar1) * gsGetCount(S))
#define gsClocGchar2(S)                            gleakCloc(    gsClocChar2_(        (S)),                                  gsizeof(Gchar2) * gsGetCount(S))
#define gsClocJoin(A,S)                            gleakClocType(gsClocJoin_(A,S),   Gs)
#define gsClocSplit(S,L)                           gleakClocType(gsClocSplit_(S,L), GvArray)

grlAPI Char          *gsClocA_(           Gs      const * const str);
grlAPI Gchar1        *gsClocChar1_(       Gs      const * const str);
grlAPI Gchar2        *gsClocChar2_(       Gs      const * const str);
grlAPI Gs            *gsClocJoin_(        GvArray const * const v, Gs const * const sep);
grlAPI GvArray       *gsClocSplit_(       Gs      const * const str, Gchar const letter);

grlAPI Gcompare       gsCompare(             Gs const * const as, Gs   const * const bs);
grlAPI Gcompare       gsCompareA(            Gs const * const as, Char const * const bs);
grlAPI Gcompare       gsCompareContainer(    Gv const * const av, Gv   const * const bv);
grlAPI Gcompare       gsCompareBase(         Gs const * const as, Gs   const * const bs);
grlAPI Gcompare       gsCompareBaseContainer(Gv const * const av, Gv   const * const bv);
grlAPI Gcompare       gsCompareBaseCount(    Gs const * const as, Gs   const * const bs, Gcount const count);
grlAPI Gcompare       gsCompareCount(        Gs const * const as, Gs   const * const bs, Gcount const count);

// Temporary until implemented.
#define gsCompareInverse             gsCompare
#define gsCompareBaseInverse         gsCompareBase
#define gsCompareNatural             gsCompare
#define gsCompareNaturalBase         gsCompareBase
#define gsCompareNaturalInverse      gsCompare
#define gsCompareNaturalBaseInverse  gsCompareBase

grlAPI Gs            *gsEraseSub(           Gs       * const str, Gindex const start, Gindex const end);

grlAPI Gs            *gsFindAndReplace(     Gs       * const str, Gs   const * const find, Gs   const * const replace, Gcount * const count);
//grlAPI Gindex         gsFindFirstCSVComma(  Gs const * const str, Gindex const position);
grlAPI Gindex         gsFindFirstNotOf(     Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindFirstNotOfChar( Gs const * const str, Gindex const position, Gchar const letter);
grlAPI Gindex         gsFindFirstOf(        Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindFirstOfChar(    Gs const * const str, Gindex const position, Gchar const letter);
grlAPI Gindex         gsFindLastNotOf(      Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindLastNotOfChar(  Gs const * const str, Gindex const position, Gchar const letter);
grlAPI Gindex         gsFindLastOf(         Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindLastOfChar(     Gs const * const str, Gindex const position, Gchar const letter);
grlAPI Gindex         gsFindSub(            Gs const * const str, Gindex const position, Gs   const * const substr);
//grlAPI Gs            *gsFromCSV(            Gs       * const str);

       Gb             gsFunctionStart(      void);
       void           gsFunctionStop(       void);

grlAPI Gi             gsGetI(               Gs const * const str);
grlAPI Gn             gsGetN(               Gs const * const str);
grlAPI Gn             gsGetNHex(            Gs const * const str);
grlAPI Gr             gsGetR(               Gs const * const str);
grlAPI Gs const      *gsGetWhitespace(      void);

grlAPI GhashN         gsHash(               Gs const * const str);
grlAPI GhashN         gsHashContainer(      Gv const * const str);

grlAPI Gs            *gsInsert(             Gs       * const dst, Gindex const position, Gs   const * const src);
//grlAPI Gs            *gsInsertFormat(       Gs       * const dst, Gindex const position, Gs   const * const src, Char const * const format);

grlAPI Gb             gsIsBlank(            Gs const *const str);

#define gsIsEqual(           A, B)           (gsCompare(           A, B)        == gcompareEQUAL)
#define gsIsEqualA(          A, B)           (gsCompareA(          A, B)        == gcompareEQUAL)
#define gsIsEqualCount(      A, B, COUNT)    (gsCompareCount(      A, B, COUNT) == gcompareEQUAL)
#define gsIsEqualBase(       A, B)           (gsCompareCountBase(  A, B, COUNT) == gcompareEQUAL)
#define gsIsEqualBaseCount(  A, B, COUNT)    (gsCompareBaseCount(  A, B, COUNT) == gcompareEQUAL)

#define gsIsEmpty(S)                       (gsGetCount(S) == 0)

grlAPI Gb             gsIsMultiline(        Gs const * const str);

grlAPI Gs            *gsReverse(            Gs       * const str);

grlAPI Gs            *gsPadHead(            Gs       * const str, Gcount const length, Gchar const letter);
grlAPI Gs            *gsPadTail(            Gs       * const str, Gindex const length, Gchar const letter);

#define gsSet(            S, VALS)                  (gsFlush(S), gsAppend(          S, VALS))
#define gsSetI(           S, VALI)                  (gsFlush(S), gsAppendI(         S, VALI))
//#define gsSetIFormat(     S, VALI, FMT)             (gsFlush(S), gsAppendIFormat(   S, VALI, FMT))
#define gsSetN(           S, VALN)                  (gsFlush(S), gsAppendN(         S, VALN))
//#define gsSetNFormat(     S, VALN, FMT)             (gsFlush(S), gsAppendNFormat(   S, VALN, FMT))
#define gsSetR(           S, VALR)                  (gsFlush(S), gsAppendR(         S, VALR))
//#define gsSetRFormat(     S, VALR, FMT)             (gsFlush(S), gsAppendRFormat(   S, VALR, FMT))
//#define gsSetFormat(      S, VALS, FMT)             (gsFlush(S), gsAppendFormat(    S, VALS, FMT))
//#define gsSetFormatted(   S, FMT, ...)              (gsFlush(S), gsAppendFormatted( S, FMT, __VA_ARGS__))
#define gsSetParams(      S, ...)                   (gsFlush(S), gsAppendParams(    S, __VA_ARGS__))
#define gsSetSub(         S, VALS, START, END)      (gsFlush(S), gsAppendSub(       S, VALS, START, END))
#define gsSetSubFormat(   S, VALS, START, END, FMT) (gsFlush(S), gsAppendSubFormat( S, VALS, START, END, FMT))

grlAPI Gs            *gsStrip(              Gs       * const str, GsStripMethod const type);
grlAPI Gs            *gsStripCompress(      Gs       * const str);

//grlAPI Gs            *gsToCSV(              Gs       * const str);
//grlAPI Gs            *gsToFormat(           Gs       * const str, Char const * const format);
grlAPI Gs            *gsToLowerCase(        Gs       * const str);
grlAPI Gs            *gsToUpperCase(        Gs       * const str);
grlAPI Gs            *gsTrim(               Gs       * const str, Gs   const * const letters);
grlAPI Gs            *gsTrimLeft(           Gs       * const str, Gs   const * const letters);
grlAPI Gs            *gsTrimRight(          Gs       * const str, Gs   const * const letters);

grlAPI void           gvDataDlocS(          GvData * const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
