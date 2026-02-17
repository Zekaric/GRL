/**************************************************************************************************
file:       G_base
author:     Robbert de Groot
copyright:  2000, Robbert de Groot

description:
This header contains some very common constants, macroes, and types used
throughout the GRL library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2000, Robbert de Groot

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

// I have and PCLint from time to time.  When you see something like this it is
// to quiet some PCLint error/warnings that I deam to be ok and not needing to
// the changed or fixed.  I don't know what these ones mean off the top of my
// head but suffice to say I have looked into them.

#pragma once

// GRL was initially developed to be a DLL.  After a while I found DLLs were
// just being a pain when it comes to distribution of the exe.  So I have more
// recently adopted sticking to static libraries as it makes my life slightly
// less annoying.
#if defined(LIBGRL_STATIC)
#  define      grlAPI
#else
#  if defined(LIBGRL_EXPORTS)
#     define   grlAPI __declspec(dllexport)
#  else // LIBGRL_IMPORTS
#     define   grlAPI __declspec(dllimport)
#  endif
#endif

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define GappSUCCESS           0

// For the types further down below.
#define GiBIT_COUNT           64

#define GnMAX                 Gn8MAX
#define GiMAX                 Gi8MAX
#define GrMAX                 Gr8MAX
#define GrMIN                 Gr8MIN
#define GrPI                  M_PI
#define GrE                   M_E        // e
#define GrLOG2E               M_LOG2E    // log2(e)
#define GrLOG10E              M_LOG10E   // log10(e)
#define GrLN2                 M_LN2      // ln(2)
#define GrLN10                M_LN10     // ln(10)
#define GrPI                  M_PI       // pi
#define GrPI_OVER_2           M_PI_2     // pi/2
#define GrPI_OVER_4           M_PI_4     // pi/4
#define Gr1_OVER_PI           M_1_PI     // 1/pi
#define Gr2_OVER_PI           M_2_PI     // 2/pi
#define Gr2_OVER_SQROOT_PI    M_2_SQRTPI // 2/sqrt(pi)
#define GrSQROOT_2            M_SQRT2    // sqrt(2)
#define Gr1_OVER_SQROOT_2     M_SQRT1_2  // 1/sqrt(2)
#define GrM_PER_C                    10.000000000000
#define GrC_PER__                   100.000000000000
#define GrM_PER__                 1_000.000000000000
#define Gr__PER_K                 1_000.000000000000
#define GrM_PER_K             1_000_000.000000000000
#define GrINCH_PER_FOOT              12.000000000000
#define GrINCH_PER_MILE          63_360.000000000000
#define GrINCH_PER_NMILE         72_913.390000000000
#define GrINCH_PER_MM                 0.039370080000
#define GrINCH_PER_CM                 0.393700800000
#define GrINCH_PER_M                 39.370080000000
#define GrINCH_PER_KM            39_370.080000000000
#define GrFOOT_PER_INCH       (1 / GrINCH_PER_FOOT)
#define GrFOOT_PER_YARD               3.000000000000
#define GrFOOT_PER_MILE           5_280.000000000000
#define GrFOOT_PER_NMILE          6_076.115000000000
#define GrFOOT_PER_MM                 0.003280840000
#define GrFOOT_PER_CM                 0.032808400000
#define GrFOOT_PER_M                  3.280840000000
#define GrFOOT_PER_KM             3_280.840000000000
#define GrYARD_PER_INCH       (1 / GrINCH_PER_YARD)
#define GrYARD_PER_FOOT       (1 / GrFOOT_PER_YARD)
#define GrYARD_PER_MILE           1_760.000000000000
#define GrYARD_PER_NMILE          2_025.372000000000
#define GrYARD_PER_MM                 0.001093613000
#define GrYARD_PER_CM                 0.010936130000
#define GrYARD_PER_M                  1.093061300000
#define GrYARD_PER_KM             1_093.613000000000
#define GrMILE_PER_INCH       (1 / GrINCH_PER_MILE)
#define GrMILE_PER_FOOT       (1 / GrFOOT_PER_MILE)
#define GrMILE_PER_YARD       (1 / GrYARD_PER_MILE)
#define GrMILE_PER_NMILE              1.150779000000
#define GrMILE_PER_MM                 0.000000621371
#define GrMILE_PER_CM                 0.000006213710
#define GrMILE_PER_M                  0.000621371000
#define GrMILE_PER_KM                 0.621371000000
#define GrNMILE_PER_INCH      (1 / GrINCH_PER_NMILE)
#define GrNMILE_PER_FOOT      (1 / GrFOOT_PER_NMILE)
#define GrNMILE_PER_YARD      (1 / GrYARD_PER_NMILE)
#define GrNMILE_PER_MILE      (1 / GrMILE_PER_NMILE)
#define GrNMILE_PER_MM                0.000000539957
#define GrNMILE_PER_CM                0.000005399570
#define GrNMILE_PER_M                 0.000539957000
#define GrNMILE_PER_KM                0.539957000000
#define GrMM_PER_INCH                25.400000000000
#define GrMM_PER_FOOT               304.800000000000
#define GrMM_PER_YARD               914.400000000000
#define GrMM_PER_MILE         1_609_344.000000000000
#define GrMM_PER_NMILE        1_852_000.000000000000
#define GrCM_PER_INCH                 2.540000000000
#define GrCM_PER_FOOT                30.480000000000
#define GrCM_PER_YARD                91.440000000000
#define GrCM_PER_MILE           160_934.400000000000
#define GrCM_PER_NMILE          185_200.000000000000
#define GrM_PER_INCH                  0.025400000000
#define GrM_PER_FOOT                  0.304800000000
#define GrM_PER_YARD                  0.914400000000
#define GrM_PER_MILE              1_609.344000000000
#define GrM_PER_NMILE             1_852.000000000000
#define GrKM_PER_INCH                 0.000025400000
#define GrKM_PER_FOOT                 0.000304800000
#define GrKM_PER_YARD                 0.000914400000
#define GrKM_PER_MILE                 1.609344000000
#define GrKM_PER_NMILE                1.852000000000
#define GrPOINT_PER_INCH             72.000000000000
#define GrPOINT_PER_MM        (GrPOINT_PER_INCH * GrINCH_PER_MM)
#define GrTWIP_PER_INCH            1440.000000000000
#define GrTWIP_PER_MM         (GrTWIP_PER_INCH * GrINCH_PER_MM)
#define GrTWIP_PER_POINT             20.000000000000
#define GrHALF_POINT_PER_POINT        2.000000000000


#define Gi1MAX                INT8_MAX
#define Gi1MIN                INT8_MIN
#define Gi2MAX                INT16_MAX
#define Gi2MIN                INT16_MIN
#define Gi4MAX                INT32_MAX
#define Gi4MIN                INT32_MIN
#define Gi8MAX                INT64_MAX
#define Gi8MIN                INT64_MIN

#define Gn1MAX                UINT8_MAX
#define Gn2MAX                UINT16_MAX
#define Gn4MAX                UINT32_MAX
#define Gn8MAX                UINT64_MAX

#define Gr4MAX                FLT_MAX
#define Gr4MIN                FLT_MIN
#define Gr8MAX                DBL_MAX
#define Gr8MIN                DBL_MIN

#define GrNAN                 NAN
#define GrR4_EPSILON          FLT_EPSILON
#define Gr8R_EPSILON          DBL_EPSILON
#define Gr8INF                HUGE_VAL
#define Gr4INF                HUGE_VALF

#if defined(grl64)
#define GnpMAX                UINTPTR_MAX
#define GipMAX                INTPTR_MAX
#else
#define GnpMAX                UINTPTR_MAX
#define GipMAX                INTPTR_MAX
#endif

#define GcountMAX             Gi4MAX

#define GindexERROR           Gi4MIN
#define GindexMIN             Gi4MIN
#define GindexMAX             Gi4MAX

#define GoffsetMAX            Gi4MAX
#define GoffsetMIN            Gi4MIN

#define GsizeMAX              Gi4MAX

#define GhashNMAX             Gn4MAX

#define GheapNMAX             Gn4MAX

#define GidNONE               0
#define GidUNDEFINED          Gn4MAX

/**************************************************************************************************
macro:
**************************************************************************************************/

// Helper to convert a non quoted string to a quoted string for the pre-processor
#define CHAR_FROM_INT_(X)           #X
#define CHAR_FROM_INT(X)            CHAR_FROM_INT_(X)

// Wrapping sizeof to case to Gsize
#define gsizeof(V)                  ((Gsize) sizeof(V))

// Abs macro
#define gABS(V)                     (((V) <    0) ? -(V) : (V))
#define gMAX(A, B)                  (((A) >= (B)) ?  (A) : (B))
#define gMIN(A, B)                  (((A) >= (B)) ?  (B) : (A))
#define gIS_IN_RANGE(  V, MIN, MAX) ((MIN) <= (V) && (V) <= (MAX))
#define gIS_IN_BETWEEN(V, MIN, MAX) ((MIN) <  (V) && (V) <  (MAX))

// Loop macroes.
// I know some will hate these but I find they help prevent typo mistakes and
// to some degree they help in readability.
// for* - finite loops.
#define forCount(INDEX, COUNT)      for ((INDEX) = 0;           (INDEX) <  (COUNT); (INDEX) += 1)
#define forCountDown(INDEX, COUNT)  for ((INDEX) = (COUNT) - 1; (INDEX) >= 0;       (INDEX) -= 1)
// loop* - infinite loop.
#define loop                        for (;;)
#define loopCount(INDEX)            for ((INDEX) = 0;            ; (INDEX) += 1)
// loopOnce - single iteration loop.
#define loopOnce                    for (int __index__ = 0; __index__ < 1; __index__++)
// breakable scope
#define breakScope                  loopOnce

// Return macroes
// Again some will hate these but I find they help prevent mistakes and improve
// readability.
// greturn* - macroes that call function exit code.  See genter.
#define greturnIf(C)       if ((C)) { greturn; }
#define greturnValIf(C,V)  if ((C)) { greturn (V); }
#define greturn0If(C)      if ((C)) { greturn 0; }
#define greturn1If(C)      if ((C)) { greturn 1; }
#define greturnNullIf(C)   if ((C)) { greturn NULL; }
#define greturnTrueIf(C)   if ((C)) { greturn gbTRUE; }
#define greturnFalseIf(C)  if ((C)) { greturn gbFALSE; }
// return - macroes that do not call function exit code.  So just wrapping
//          return keyword.
#define returnIf(C)        if ((C)) { return; }
#define returnValIf(C,V)   if ((C)) { return (V); }
#define return0If(C)       if ((C)) { return 0; }
#define return1If(C)       if ((C)) { return 1; }
#define returnNullIf(C)    if ((C)) { return NULL; }
#define returnTrueIf(C)    if ((C)) { return gbTRUE; }
#define returnFalseIf(C)   if ((C)) { return gbFALSE; }

#define continueIf(C)      if ((C)) { continue; }
#define breakIf(C)         if ((C)) { break; }

// Goto macroes
// I am not a huge goto user but there are cases where they are useful.  Similar
// macroes to the returns above.
// stopIf jumps to a specific label in the code.
#define gotoIf(C,G)        if ((C)) { goto G; }
#define stop()             goto STOP
#define stopIf(C)          if ((C)) { goto STOP; }

// debug macroes
// Essentially wrapping assert but in a style that I find easier to read.
#if defined(_DEBUG)

#define debugHaltIf(VALUE, STRING)  if (VALUE) { debugHalt(STRING); }
#define debugHalt(STRING)           assert(gbFALSE && (STRING))
#define debugPrintU2(WSTR)          OutputDebugStringW(WSTR)
#define debugPrintA( ASTR)          OutputDebugStringA(ASTR)
#define debugPrintFormatU2(FMT, ...)     \
{\
   CharW __debug_str[1024];\
   swprintf_s(__debug_str, 1024, FMT, __VA_ARGS__);\
   debugPrintU2(__debug_str);\
}
#define debugPrintFormatA(FMT, ...)     \
{\
   char __debug_str[1024];\
   sprintf_s(__debug_str, 1024, FMT, __VA_ARGS__);\
   debugPrintA(__debug_str);\
}

#if grlWINDOWS == 1
#define debugCheckMemory()             _CrtCheckMemory()
#define debugSetCheckMemoryAgresive()  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define debugCheckMemory()
#define debugSetCheckMemoryAgresive()
#endif

#else

#define debugHaltIf(                VALUE, STRING)
#define debugHalt(                  STRING)
#define debugPrintU2(               WSTR)
#define debugPrintA(                ASTR)
#define debugPrintFormatU2(         FMT, ...)
#define debugPrintFormatA(          FMT, ...)
#define debugCheckMemory(           )
#define debugSetCheckMemoryAgresive()
#define debugPrintMsg(              FMT, ...)

#endif

// Enter macroes
// When you get into the code you will see genter; in every (or most every) function.  I wish 'C'
// or compilers had some option to add your own function entry code so I didn't have to do this.
//
// Uses:
// At one point I had my own profiling code because there was a time when Microsoft stopped
// providing a profiler and there were no others that were affordable or free.  Now we have options
// it isn't really necessary and my solution still had issues.  I.E. it wouldn't do multi-threading
// profiling.  So I removed that code but it was useful for a while.
//
// I also had a simple garbage collector idea once where temporary, created on heap memory, would
// be cleaned up on function exit.  It was removed because it was not improving my coding life.
//
// Now it is mainly used for the TRACE_IS_ON flag.  The debug genter is jsut to ensure that if I
// do turn on or add new entry code that my code will compile properly.
#if   defined(_DEBUG) && (GTRACE_IS_ON == 1)

#define genter \
   int ___genterValue___ = 0;\
   gtraceEnter()

#elif defined(_DEBUG)

#define genter \
   int ___genterValue___ = 0

#else

#define genter

#endif

// Return macroes
// Complements the enter macroes and is called on exit of a function.
#if   defined(_DEBUG) && (GTRACE_IS_ON == 1)

#define greturn \
   gtraceExit();\
   ___genterValue___ = 1;  \
   return

#elif defined(_DEBUG)

#define greturn            \
   ___genterValue___ = 1;  \
   return

#else

#define greturn \
   return

#endif

// Macroes for Gid
#define gidIsEqual(A,B)    ((A) == (B))
#define gidIsGood(I)       (0 < (I))
#define gidIsUndefined(ID) ((ID) == Gn4MAX)
#define gidGetN(ID)        ((Gn4) ID)
#define gidGetFromN(VALUE) ((Gid) VALUE)
#if defined(grlSWAP)
#define gidGetC(ID, CHAR4)                \
   (CHAR4[3] = (Char) (((ID) & 0xff000000) >> 24), \
    CHAR4[2] = (Char) (((ID) & 0x00ff0000) >> 16), \
    CHAR4[1] = (Char) (((ID) & 0x0000ff00) >>  8), \
    CHAR4[0] = (Char) (((ID) & 0x000000ff)))
#define gidGetFromC(CHAR4)                \
   ((CHAR4[3] << 24) |                    \
    (CHAR4[2] << 16) |                    \
    (CHAR4[1] <<  8) |                    \
    (CHAR4[0]))
#else
#define gidGetC(ID, CHAR4)                \
   (CHAR4[0] = (Char) (((ID) & 0xff000000) >> 24), \
    CHAR4[1] = (Char) (((ID) & 0x00ff0000) >> 16), \
    CHAR4[2] = (Char) (((ID) & 0x0000ff00) >>  8), \
    CHAR4[3] = (Char) (((ID) & 0x000000ff)))
#define gidGetFromC(CHAR4)                \
   ((CHAR4[0] << 24) |                    \
    (CHAR4[1] << 16) |                    \
    (CHAR4[2] <<  8) |                    \
    (CHAR4[3]))
#endif

#define gcountIsGood(C)    (0 <= (C))

#define gindexIsGood(I,C)  (0 <= (I) && (I) < (C))

#define gsizeIsGood(S)     (0 <= (S))

// Simple hash function for pointers. This assumes pointers are byte aligned to
// the 4 bytes.  This is why we are dividing by 4 to remove the multiple of 4
// nature of a pointer.
#define gpHash(P) ((GhashN) ((((Gnp) P) / 4) % GhashNMAX))

/**************************************************************************************************
type:
**************************************************************************************************/

// Enums could be constants but I put them here because they are more 'types'
// in my opinion.

// Alignment is more a UI thing.  This may move out to my GUI (GRL User
// Interface) Library.  I do not remember why I put this here except that I
// may have found a use outside of GUI.
typedef enum
{
   galignmentDEFAULT    = 0,

   galignmentH_LEFT     = 0x10000000,
   galignmentH_CENTER   = 0x01000000,
   galignmentH_FILL     = 0x00100000,
   galignmentH_RIGHT    = 0x00010000,

   galignmentV_TOP      = 0x00001000,
   galignmentV_CENTER   = 0x00000100,
   galignmentV_FILL     = 0x00000010,
   galignmentV_BOTTOM   = 0x00000001,

   galignmentH_MASK     = 0xFFFF0000u,
   galignmentV_MASK     = 0x0000FFFF
} Galignment;

// B for Boolean
// stdbool.h was not around when I was developing GRL.  So this was my boolean
// type.
// UNDEFINED is rarely used, assume it isn't an option unless the function
// specifically states it could be an option.
typedef enum
{
   gbFALSE              =  0,
   gbTRUE               =  1,
   gbUNDEFINED          = -1
} Gb;

// Compare function result options.  All compare functions should return this
// type unless they have a good reason not too.
// UNKNOWN is rarely used, assume it isn't an option unless the function
// specifically states it could be an option.
typedef enum
{
   gcompareLESS_THAN    = -1,
   gcompareEQUAL        =  0,
   gcompareGREATER_THAN =  1,
   gcompareUNKNOWN      =  2
} Gcompare;

// Position function options.  I never liked the SEEK_ prefix and thise could
// be used elsewhere other than file IO.
typedef enum
{
   gpositionSTART   = SEEK_SET,
   gpositionEND     = SEEK_END,
   gpositionCURRENT = SEEK_CUR
} Gposition;

// typedefs
// Why is this done?  One of C's failing was that it was not strict on defining
// what size a type was.  This lead to reduced portability of raw C code.  If
// you looked at any library with a certain amount of age you will see that
// every one of them does something like this just so that they have some
// predictability porting their code to various hardware architectures and
// compilers.

// Yes I am using stdint types.  My code actually predated stdint but I
// modified the typedefs to use them instead.  Why not used stdint types?
// I really loath using '_'.  I find it hard to type and slows me down.
// i - integer (Z) numbers, positive and negative whole numbers.
// n - natural (N) numbers, positive whole numbers including 0.
// r - real (R) numbers, ok as 'real' as they can be on a computer.  float and double.
typedef int8_t             Gi1;
typedef int16_t            Gi2;
typedef int32_t            Gi4;
typedef int64_t            Gi8;
typedef uint8_t            Gn1;
typedef uint16_t           Gn2;
typedef uint32_t           Gn4;
typedef uint64_t           Gn8;
typedef float              Gr4;
typedef double             Gr8;

// Same as the above but the largest size they can be.  This does not mean the
// most efficient speed and memory wise.
typedef void               Gp;
typedef Gi8                Gi;
typedef Gn8                Gn;
typedef Gr8                Gr;

// Char may seem like a curious typedef but this is mainly for PCLint which
// warns against using char
typedef char               Char;
typedef wchar_t            CharW;

// Grl string base.  Unicode.  Gchar1 is UTF8, Gchar2 is UTF16, Gchar is UTF32.
typedef Gn1                Gchar1;
typedef Gn2                Gchar2;
typedef Gn4                Gchar;

// I and N types that are the same memory size as a pointer.
typedef intptr_t           Gip;
typedef uintptr_t          Gnp;

// Half sizes based on architecture.  I believe I am using these when working
// on a arbitrarily precise number format and routines.
#if defined(grl64)
typedef Gi4                Gih;
typedef Gn4                Gnh;
typedef Gr8                Grp;
#else
typedef Gi2                Gih;
typedef Gn2                Gnh;
typedef Gr4                Grp;
#endif

// Count Index Offset Size
// A lot of functions have parameters that indicate a count, index, offset, and
// size.  So I made them their own types to make it more obvious the intended
// used of the variable/parameter.  These will use the most efficient integer
// representation for the architecture.
typedef Gi4                Gcount;
typedef Gi4                Gindex;
typedef Gi4                Goffset;
typedef Gi4                Gsize;

// Because bit fields in a structure definition always trips me up.  Needs to be
// unsigned.
typedef unsigned int       Gbit;

// Id is a basic natural number.  Not the same as a GUID but meant to be used
// in the same way in that it should be a unique number on other data.
typedef Gn4                Gid;

typedef Gn4                Gversion;

// GUID type.
typedef struct
{
   Gn8                      n[2];
   Gn1                      b[16];
} Gguid;

// HashN is for hashing functions.  Hash resturns are naturals.
typedef Gn4                GhashN;

// HeapN is for the heap uses.
typedef Gn4                GheapN;

// Integer 2D Point structure.
typedef struct
{
   Gih                      x;
   Gih                      y;
} Gixy;

// Natural 2D Point structure.
typedef struct
{
   Gnh                      x;
   Gnh                      y;
} Gnxy;

// Forward reference for GRL's Dynamic strings.
typedef struct Gv4Array Gv4Array;
typedef Gv4Array        Gs;

// Generic value type.
typedef enum
{
   gvDataTypeNONE,

   gvDataTypeI,
   gvDataTypeN,
   gvDataTypeP,
   gvDataTypeR,

   gvDataTypeS,

   gvDataTypeCOUNT
} GvDataType;

// The largest values for all types.
typedef union
{
   Gn1                      byte[8]; // assuming pointer size is 8 bytes.
   Gi                       b;
   Gi                       i;
   Gn                       n;
   Gr                       r;
   Gs                      *s;        // assuming pointer size is 8 bytes.
   Gp                      *p;        // assuming pointer size is 8 bytes.
} Gv;

typedef Gv Gv8;

typedef union
{
   Gn1                      byte[4];
   Gi4                      b;
   Gi4                      i;
   Gn4                      n;
   Gr4                      r;
   Gchar                    c;
} Gv4;

typedef union
{
   Gn1                      byte[2];
   Gi2                      b;
   Gi2                      i;
   Gn2                      n;
} Gv2;

typedef union
{
   Gn1                      byte[1];
   Gi1                      b;
   Gi1                      i;
   Gn1                      n;
} Gv1;

// Generic data structure for any of the base data types but includes the
// actual stored type.  Why use this?  Use this if you have a container that
// can store any of the types and you may not know based on location in the
// container that the stored type might be.
typedef struct
{
   GTYPE_VAR

   GvDataType               type;
   Gv                       value;
} GvData;

// Keys in data containers are always const pointers.  So in the generic sense
// a key a void *
typedef Gp                 Gk;
// The basic Key Value pair.  Value is a generic void *
typedef struct
{
   Gk const                *key;
   Gv                       value;
} Gkv;

// Common callback function patterns.
typedef Gcompare   (*GrlCompareFunc)(        Gp const * const valueA, Gp const * const valueB);
typedef void       (*GrlDlocFunc)(           Gp       * const value);
typedef void       (*GrlForEachFunc)(        Gp       * const value);
typedef void       (*GrlForEachKeyFunc)(     Gk const * const key,    Gp const * const value);
typedef Gp        *(*GrlForEachProcessFunc)( Gp       * const value);
typedef void       (*GrlForEachAltFunc)(     Gp       * const value,  GrlForEachFunc func);
typedef Gp const  *(*GrlGetFunc)(            Gp const * const mem,    Gi4 const index);
typedef GhashN     (*GrlHashFunc)(           Gp const * const value);
typedef void       (*GrlSwapFunc)(           Gp       * const mem,    Gi4 const indexA, Gi4 const indexB);

typedef Gb         (*GrlGetBuffer)(          Gp       * const dataSource,      Gcount const byteCount, Gn1       * const data);
typedef Gb         (*GrlSetBuffer)(          Gp       * const dataDestination, Gcount const byteCount, Gn1 const * const data);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
