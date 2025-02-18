/**************************************************************************************************
file:       gs
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
**************************************************************************************************/

#if !defined(GSFUNCTIONH)
#define      GSFUNCTIONH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define gsSubStrINDEX_START 0
#define gsSubStrINDEX_END   GindexMAX

/**************************************************************************************************
type:
**************************************************************************************************/
typedef enum
{
   gsFormattedTypeA,
   gsFormattedTypeU1,
   gsFormattedTypeU2,
   gsFormattedTypeS,
   gsFormattedTypeI,
   gsFormattedTypeN,
   gsFormattedTypeR
} GsFormattedType;

/**************************************************************************************************
prototype:
**************************************************************************************************/
// hand coded functions.
// gs
// Functions that greturn a Gs * may not greturn a 'new' Gs * but rather the same
// Gs * that was passed in.  This is so that you can daisy chain the functions
// together if you find that easier.
grlAPI Gs            *gsAppend(              Gs       * const str, Gs const * const value);
grlAPI Gs            *gsAppendA(             Gs       * const str, Char const * const cstr);
grlAPI Gs            *gsAppendU1(            Gs       * const str, Gc1 const * const cstr);
grlAPI Gs            *gsAppendU2(            Gs       * const str, Gc2 const * const cstr);
grlAPI Gs            *gsAppendC(             Gs       * const str, Gc2 const gc);
grlAPI Gs            *gsAppendCFormat(       Gs       * const str, Gc2 const gc, Gc2 const * const format);
grlAPI Gs            *gsAppendI(             Gs       * const str, Gi const i);
grlAPI Gs            *gsAppendIFormat(       Gs       * const str, Gi const i, Gc2 const * const format);
grlAPI Gs            *gsAppendN(             Gs       * const str, Gn const n);
grlAPI Gs            *gsAppendNFormat(       Gs       * const str, Gn const n, Gc2 const * const format);
grlAPI Gs            *gsAppendR(             Gs       * const str, Gr const r);
grlAPI Gs            *gsAppendRFormat(       Gs       * const str, Gr const r, Gc2 const * const format);
grlAPI Gs            *gsAppendFormat(        Gs       * const str, Gs const * const value, Gc2 const * const format);
grlAPI Gs            *gsAppendFormatA(       Gs       * const str, Char const * const cstr, Gc2 const * const format);
grlAPI Gs            *gsAppendFormatU1(      Gs       * const str, Gc1 const * const cstr, Gc2 const * const format);
grlAPI Gs            *gsAppendFormatU2(      Gs       * const str, Gc2 const * const cstr, Gc2 const * const format);
grlAPI Gs            *gsAppendSub(           Gs       * const str, Gs const * const value, Gindex const start, Gindex const end);
grlAPI Gs            *gsAppendSubFormat(     Gs       * const str, Gs const * const value, Gindex const start, Gindex const end, Gc2 const * const format);
// MISRA rule on ellipsis.  Do not use if you are not permitted.
//lint -save -e960 -e1916
grlAPI Gs            *gsAppendFormatted(     Gs       * const str, Gc2 const * const format, ...);
grlAPI Gs            *gsAppendParams(        Gs       * const str, ...);
grlAPI Gs            *gsAppendRandom(        Gs       * const str);
//lint -restore

grlAPI Gs            *gsCapitalize(         Gs       * const str);
grlAPI Gcompare       gsCompare(            Gs const * const as, Gs   const * const bs);
grlAPI Gcompare       gsCompareA(           Gs const * const a,  Char const * const b);
grlAPI Gcompare       gsCompareU1(          Gs const * const a,  Gc1  const * const b);
grlAPI Gcompare       gsCompareU2(          Gs const * const a,  Gc2  const * const b);
grlAPI Gcompare       gsCompareBase(        Gs const * const as, Gs   const * const bs);
grlAPI Gcompare       gsCompareBaseA(       Gs const * const a,  Char const * const b);
grlAPI Gcompare       gsCompareBaseU1(      Gs const * const a,  Gc1  const * const b);
grlAPI Gcompare       gsCompareBaseU2(      Gs const * const a,  Gc2  const * const b);
grlAPI Gcompare       gsCompareBaseCount(   Gs const * const as, Gs   const * const bs, Gcount const count);
grlAPI Gcompare       gsCompareBaseCountA(  Gs const * const a,  Char const * const b,  Gcount const count);
grlAPI Gcompare       gsCompareBaseCountU1( Gs const * const a,  Gc1  const * const b,  Gcount const count);
grlAPI Gcompare       gsCompareBaseCountU2( Gs const * const a,  Gc2  const * const b,  Gcount const count);
grlAPI Gcompare       gsCompareCount(       Gs const * const as, Gs   const * const bs, Gcount const count);
grlAPI Gcompare       gsCompareCountA(      Gs const * const a,  Char const * const b,  Gcount const count);
grlAPI Gcompare       gsCompareCountU1(     Gs const * const a,  Gc1  const * const b,  Gcount const count);
grlAPI Gcompare       gsCompareCountU2(     Gs const * const a,  Gc2  const * const b,  Gcount const count);

/*lint -save -e960 */
// Temporary until implemented.
#define gsCompareInverse             gsCompare
#define gsCompareBaseInverse         gsCompareBase
#define gsCompareNatural             gsCompare
#define gsCompareNaturalBase         gsCompareBase
#define gsCompareNaturalInverse      gsCompare
#define gsCompareNaturalBaseInverse  gsCompareBase
/*lint -restore */

/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gsClocA(S)                               ((Char *) gleakCloc(gsClocA_(            (S)),                                  gsizeof(Gs)))
#define gsClocFrom(S)                            ((Gs *)   gleakCloc(gsAppend(            gsCloc(), (S)),                        gsizeof(Gs)))
#define gsClocFromA(S)                           ((Gs *)   gleakCloc(gsAppendA(           gsCloc(), (Char *) (S)),               gsizeof(Gs)))
#define gsClocFromU1(S)                          ((Gs *)   gleakCloc(gsAppendU1(          gsCloc(), (S)),                        gsizeof(Gs)))
#define gsClocFromU2(S)                          ((Gs *)   gleakCloc(gsAppendU2(          gsCloc(), (S)),                        gsizeof(Gs)))
#define gsClocFromI(I)                           ((Gs *)   gleakCloc(gsAppendI(           gsCloc(), (I)),                        gsizeof(Gs)))
#define gsClocFromIFormat(I, FMT)                ((Gs *)   gleakCloc(gsAppendIFormat(     gsCloc(), (I), (FMT)),                 gsizeof(Gs)))
#define gsClocFromN(N)                           ((Gs *)   gleakCloc(gsAppendN(           gsCloc(), (N)),                        gsizeof(Gs)))
#define gsClocFromNFormat(N, FMT)                ((Gs *)   gleakCloc(gsAppendNFormat(     gsCloc(), (N), (FMT)),                 gsizeof(Gs)))
#define gsClocFromR(R)                           ((Gs *)   gleakCloc(gsAppendR(           gsCloc(), (R)),                        gsizeof(Gs)))
#define gsClocFromRFormat(R, FMT)                ((Gs *)   gleakCloc(gsAppendRFormat(     gsCloc(), (R), (FMT)),                 gsizeof(Gs)))
#define gsClocFromFormat(S, FMT)                 ((Gs *)   gleakCloc(gsAppendFormat(      gsCloc(), (S), (FMT)),                 gsizeof(Gs)))
#define gsClocFromFormatA(S, FMT)                ((Gs *)   gleakCloc(gsAppendFormatA(     gsCloc(), (S), (FMT)),                 gsizeof(Gs)))
#define gsClocFromFormatU1(S, FMT)               ((Gs *)   gleakCloc(gsAppendFormatU1(    gsCloc(), (S), (FMT)),                 gsizeof(Gs)))
#define gsClocFromFormatU2(S, FMT)               ((Gs *)   gleakCloc(gsAppendFormatU2(    gsCloc(), (S), (FMT)),                 gsizeof(Gs)))
#define gsClocFromFormatted(FMT, ...)            ((Gs *)   gleakCloc(gsAppendFormatted(   gsCloc(), (FMT), __VA_ARGS__),         gsizeof(Gs)))
#define gsClocFromParam(...)                     ((Gs *)   gleakCloc(gsAppendParams(      gsCloc(), __VA_ARGS__),                gsizeof(Gs)))
#define gsClocFromSub(S, START, END)             ((Gs *)   gleakCloc(gsAppendSub(         gsCloc(), (S), (START), (END)),        gsizeof(Gs)))
#define gsClocFromSubFormat(S, START, END, FMT)  ((Gs *)   gleakCloc(gsAppendSubFormat(   gsCloc(), (S), (START), (END), (FMT)), gsizeof(Gs)))
#define gsClocRandom()                           ((Gs *)   gleakCloc(gsAppendRandom(      gsCloc()),                             gsizeof(Gs)))
#define gsClocU1(S)                              ((Gc1 *)  gleakCloc(gsClocU1_(           (S)),                                  gsizeof(Gs)))
#if 0
// gsGet()
#define gsClocU2(S)                              ((Gc2 *)  gleakCloc(gsClocU2_(           (S)),                                  gsizeof(Gs)))
#endif
/*lint -restore */

grlAPI Char          *gsClocA_(           Gs      const * const str);
grlAPI Gs            *gsClocJoin_(        GsArray const * const v, Gs   const * const sep);
grlAPI Gs            *gsClocJoinA_(       GsArray const * const v, Char const * const sep);
grlAPI Gs            *gsClocJoinU1_(      GsArray const * const v, Gc1  const * const sep);
grlAPI Gs            *gsClocJoinU2_(      GsArray const * const v, Gc2  const * const sep);
grlAPI GsArray       *gsClocSplit_(       Gs      const * const str, Gc const letter);
grlAPI Gc1           *gsClocU1_(          Gs      const * const str);
//grlAPI Gc2           *gsClocU2_(          Gs const * str);

/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gsClocJoin(A,S)                              ((Gs *) gleakCloc(gsClocJoin_(A,S),                 gsizeof(Gs)))
#define gsClocJoinA(A,S)                             ((Gs *) gleakCloc(gsClocJoinA_(A,S),                gsizeof(Gs)))
#define gsClocJoinU1(A,S)                            ((Gs *) gleakCloc(gsClocJoinU1_(A,S),               gsizeof(Gs)))
#define gsClocJoinU2(A,S)                            ((Gs *) gleakCloc(gsClocJoinU2_(A,S),               gsizeof(Gs)))

#define gsClocSplit(S,L)                             ((GsArray *) gleakCloc(gsClocSplit_(S,L),           gsizeof(GsArray)))
/*lint -restore */


grlAPI Gs            *gsEraseSub(           Gs       * const str, Gindex const start, Gindex const end);

grlAPI Gs            *gsFindAndReplace(     Gs       * const str, Gs   const * const find, Gs   const * const replace, Gcount * const count);
grlAPI Gs            *gsFindAndReplaceA(    Gs       * const str, Char const * const find, Char const * const replace, Gcount * const count);
grlAPI Gs            *gsFindAndReplaceU1(   Gs       * const str, Gc1  const * const find, Gc1  const * const replace, Gcount * const count);
grlAPI Gs            *gsFindAndReplaceU2(   Gs       * const str, Gc2  const * const find, Gc2  const * const replace, Gcount * const count);
grlAPI Gindex         gsFindFirstCSVComma(  Gs const * const str, Gindex const position);
grlAPI Gindex         gsFindFirstOf(        Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindFirstOfA(       Gs const * const str, Gindex const position, Char const * const letters);
grlAPI Gindex         gsFindFirstOfU1(      Gs const * const str, Gindex const position, Gc1  const * const letters);
grlAPI Gindex         gsFindFirstOfU2(      Gs const * const str, Gindex const position, Gc2  const * const letters);
grlAPI Gindex         gsFindFirstNotOf(     Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindFirstNotOfA(    Gs const * const str, Gindex const position, Char const * const letters);
grlAPI Gindex         gsFindFirstNotOfU1(   Gs const * const str, Gindex const position, Gc1  const * const letters);
grlAPI Gindex         gsFindFirstNotOfU2(   Gs const * const str, Gindex const position, Gc2  const * const letters);
grlAPI Gindex         gsFindLastOf(         Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindLastOfA(        Gs const * const str, Gindex const position, Char const * const letters);
grlAPI Gindex         gsFindLastOfU1(       Gs const * const str, Gindex const position, Gc1  const * const letters);
grlAPI Gindex         gsFindLastOfU2(       Gs const * const str, Gindex const position, Gc2  const * const letters);
grlAPI Gindex         gsFindLastNotOf(      Gs const * const str, Gindex const position, Gs   const * const letters);
grlAPI Gindex         gsFindLastNotOfA(     Gs const * const str, Gindex const position, Char const * const letters);
grlAPI Gindex         gsFindLastNotOfU1(    Gs const * const str, Gindex const position, Gc1  const * const letters);
grlAPI Gindex         gsFindLastNotOfU2(    Gs const * const str, Gindex const position, Gc2  const * const letters);
grlAPI Gindex         gsFindSub(            Gs const * const str, Gindex const position, Gs   const * const substr);
grlAPI Gindex         gsFindSubA(           Gs const * const str, Gindex const position, Char const * const substr);
grlAPI Gindex         gsFindSubU1(          Gs const * const str, Gindex const position, Gc1  const * const substr);
grlAPI Gindex         gsFindSubU2(          Gs const * const str, Gindex const position, Gc2  const * const substr);
grlAPI Gs            *gsFromCSV(            Gs       * const str);

grlAPI Gi             gsGetI(               Gs const * const str);
grlAPI void           gsGetII(              Gs const * const str, Gi * const a, Gi * const b);
//grlAPI Gcount         gsGetLengthAlternate( Gs const * const str);
//grlAPI Gcount         gsGetLengthA(         Gs const * const str);
//grlAPI Gcount         gsGetLengthU1(        Gs const * const str);
//grlAPI Gcount         gsGetLengthU2(        Gs const * const str);
grlAPI Gn             gsGetN(               Gs const * const str);
grlAPI Gn             gsGetNHex(            Gs const * const str);
grlAPI Gr             gsGetR(               Gs const * const str);

grlAPI GhashN         gsHash(               Gs const * const str);

grlAPI Gs            *gsInsert(             Gs       * const dst, Gindex const position, Gs   const * const src);
grlAPI Gs            *gsInsertA(            Gs       * const dst, Gindex const position, Char const * const src);
grlAPI Gs            *gsInsertU1(           Gs       * const dst, Gindex const position, Gc1  const * const src);
grlAPI Gs            *gsInsertU2(           Gs       * const dst, Gindex const position, Gc2  const * const src);
grlAPI Gs            *gsInsertFormat(       Gs       * const dst, Gindex const position, Gs   const * const src, Gc2 const * const format);
grlAPI Gs            *gsInsertFormatA(      Gs       * const dst, Gindex const position, Char const * const src, Gc2 const * const format);
grlAPI Gs            *gsInsertFormatU1(     Gs       * const dst, Gindex const position, Gc1  const * const src, Gc2 const * const format);
grlAPI Gs            *gsInsertFormatU2(     Gs       * const dst, Gindex const position, Gc2  const * const src, Gc2 const * const format);

grlAPI Gb             gsIsBlank(            Gs const *const str);

/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gsIsEqual(           A, B)           (gsCompare(           A, B)        == 0)
#define gsIsEqualA(          A, B)           (gsCompareA(          A, B)        == 0)
#define gsIsEqualU1(         A, B)           (gsCompareU1(         A, B)        == 0)
#define gsIsEqualU2(         A, B)           (gsCompareU2(         A, B)        == 0)
#define gsIsEqualCount(      A, B, COUNT)    (gsCompareCount(      A, B, COUNT) == 0)
#define gsIsEqualCountA(     A, B, COUNT)    (gsCompareCountA(     A, B, COUNT) == 0)
#define gsIsEqualCountU1(    A, B, COUNT)    (gsCompareCountU1(    A, B, COUNT) == 0)
#define gsIsEqualCountU2(    A, B, COUNT)    (gsCompareCountU2(    A, B, COUNT) == 0)
#define gsIsEqualBase(       A, B)           (gsCompareCountBase(  A, B, COUNT) == 0)
#define gsIsEqualBaseA(      A, B)           (gsCompareBaseA(      A, B)        == 0)
#define gsIsEqualBaseCount(  A, B, COUNT)    (gsCompareBaseCount(  A, B, COUNT) == 0)
#define gsIsEqualBaseCountA( A, B, COUNT)    (gsCompareBaseCountA( A, B, COUNT) == 0)
/*lint -restore */

/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gsIsEmpty(S)                       (gsGetCount(S) == 0)
/*lint -restore */

grlAPI Gb             gsIsMultiline(        Gs const * const str);

grlAPI Gs            *gsReverse(            Gs       * const str);

grlAPI Gs            *gsPadHead(            Gs       * const str, Gcount const length, Gc2 const letter);
grlAPI Gs            *gsPadTail(            Gs       * const str, Gindex const length, Gc2 const letter);

/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gsSet(            S, VALS)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppend(          S, VALS))                     /*lint -restore */
#define gsSetA(           S, VALS)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendA(         S, VALS))                     /*lint -restore */
#define gsSetU1(          S, VALS)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendU1(        S, VALS))                     /*lint -restore */
#define gsSetU2(          S, VALS)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendU2(        S, VALS))                     /*lint -restore */
#define gsSetI(           S, VALI)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendI(         S, VALI))                     /*lint -restore */
#define gsSetIFormat(     S, VALI, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendIFormat(   S, VALI, FMT))                /*lint -restore */
#define gsSetN(           S, VALN)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendN(         S, VALN))                     /*lint -restore */
#define gsSetNFormat(     S, VALN, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendNFormat(   S, VALN, FMT))                /*lint -restore */
#define gsSetR(           S, VALR)                  /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendR(         S, VALR))                     /*lint -restore */
#define gsSetRFormat(     S, VALR, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendRFormat(   S, VALR, FMT))                /*lint -restore */
#define gsSetFormat(      S, VALS, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendFormat(    S, VALS, FMT))                /*lint -restore */
#define gsSetFormatA(     S, VALS, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendFormatA(   S, VALS, FMT))                /*lint -restore */
#define gsSetFormatU1(    S, VALS, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendFormatU1(  S, VALS, FMT))                /*lint -restore */
#define gsSetFormatU2(    S, VALS, FMT)             /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendFormatU2(  S, VALS, FMT))                /*lint -restore */
#define gsSetFormatted(   S, FMT, ...)              /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendFormatted( S, FMT, __VA_ARGS__))         /*lint -restore */
#define gsSetParams(      S, ...)                   /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendParams(    S, __VA_ARGS__))              /*lint -restore */
#define gsSetSub(         S, VALS, START, END)      /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendSub(       S, VALS, START, END))         /*lint -restore */
#define gsSetSubFormat(   S, VALS, START, END, FMT) /*lint -save -esym( 960, 12.10 ) -e9008 */ (gsFlush(S), gsAppendSubFormat( S, VALS, START, END, FMT))    /*lint -restore */
/*lint -restore */

grlAPI Gs            *gsStrip(              Gs       * const str, GcStrip const type);
grlAPI Gs            *gsStripCompress(      Gs       * const str);

grlAPI Gs            *gsToCSV(              Gs       * const str);
grlAPI Gs            *gsToFormat(           Gs       * const str, Gc2 const * const format);
grlAPI Gs            *gsToLowerCase(        Gs       * const str);
grlAPI Gs            *gsToUpperCase(        Gs       * const str);
grlAPI Gs            *gsTrim(               Gs       * const str, Gs   const * const letters);
grlAPI Gs            *gsTrimA(              Gs       * const str, Char const * const letters);
grlAPI Gs            *gsTrimU1(             Gs       * const str, Gc1  const * const letters);
grlAPI Gs            *gsTrimU2(             Gs       * const str, Gc2  const * const letters);
grlAPI Gs            *gsTrimLeft(           Gs       * const str, Gs   const * const letters);
grlAPI Gs            *gsTrimLeftA(          Gs       * const str, Char const * const letters);
grlAPI Gs            *gsTrimLeftU1(         Gs       * const str, Gc1  const * const letters);
grlAPI Gs            *gsTrimLeftU2(         Gs       * const str, Gc2  const * const letters);
grlAPI Gs            *gsTrimRight(          Gs       * const str, Gs   const * const letters);
grlAPI Gs            *gsTrimRightA(         Gs       * const str, Char const * const letters);
grlAPI Gs            *gsTrimRightU1(        Gs       * const str, Gc1  const * const letters);
grlAPI Gs            *gsTrimRightU2(        Gs       * const str, Gc2  const * const letters);

// Functions as defines.
#if 0
#define gsGetLengthA(STR)                  gsGetLengthAlternate(STR)
#define gsGetLengthU1(STR)                 gsGetLengthAlternate(STR)
#define gsGetLengthU2(STR)                 gsGetLengthAlternate(STR)

#define gsSetLengthA(STR, COUNT, PAD)      gsSetLength(STR, COUNT, gcFromA((Char) PAD))
#define gsSetLengthU1(STR, COUNT, PAD)     gsSetLength(STR, COUNT, gcFromU1((Gc *) PAD))
#define gsSetLengthU2(STR, COUNT, PAD)     gsSetLength(STR, COUNT, gcFromU2((Gc2 *) PAD))
#endif

grlAPI void           gvDataDlocS(          GvData * const value);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
