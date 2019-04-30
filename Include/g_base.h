/******************************************************************************
file:       G_base
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot

description:
This header contains some very common constants, macroes, and types used 
throughout the GRL library.  
******************************************************************************/

/******************************************************************************
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
******************************************************************************/

// I have and PCLint from time to time.  When you see something like this it is
// to quiet some PCLint error/warnings that I deam to be ok and not needing to
// the changed or fixed.  I don't know what these ones mean off the top of my
// head but suffice to say I have looked into them.
/*lint -save -e960 -e961 -e9026 */

#if !defined(G_BASEH)
#define      G_BASEH

// GRL was initially developed to be a DLL.  After a while I found DLLs were 
// just being a pain when it comes to distribution of the exe.  So I have more
// recently adopted sticking to static libraries as it makes my life slightly
// less annoying.
#if !defined(GRL_DLL)
#  define      grlAPI
#else
#  if defined(GRL_EXPORTS)
#     define   grlAPI __declspec(dllexport)
#  else
#     define   grlAPI __declspec(dllimport)
#  endif
#endif

// Expecting that GRL could be used in a C++ project so properly wrapping the
// code in these C++ blocks.  
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
constant:
******************************************************************************/

// For the types further down below.
#define GiBIT_COUNT           64

#define GnMAX                 Gn8MAX
#define GiMAX                 Gi8MAX
#define GrMAX                 Gr8MAX
#define GrMIN                 Gr8MIN

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

#if defined(grl64)
#define GnpMAX                UINTPTR_MAX
#define GipMAX                INTPTR_MAX
#else
#define GnpMAX                UINTPTR_MAX
#define GipMAX                INTPTR_MAX
#endif

#define GcountMAX             Gi4MAX

#define GindexERROR           Gi4MIN
#define GindexMAX             Gi4MAX

#define GoffsetMAX            Gi4MAX
#define GoffsetMIN            Gi4MIN

#define GsizeMAX              Gi4MAX

#define GhashNMAX             Gn4MAX

#define GheapNMAX             Gn4MAX

#define GidNONE               0
#define GidUNDEFINED          Gn4MAX

/******************************************************************************
macro:
******************************************************************************/

// Helper to convert a non quoted string to a quoted string for the pre-processor
#define CHAR_FROM_INT_(X) #X
#define CHAR_FROM_INT(X) CHAR_FROM_INT_(X)

// Wrapping sizeof to case to Gsize
#define gsizeof(V)         ((Gsize) sizeof(V))

// Loop macroes.  
// I know some will hate these but I find they help prevent typo mistakes and 
// to some degree they help in readability.
// for* - finite loops.
#define forCount(INDEX, COUNT)      for ((INDEX) = 0;           (INDEX) <  (COUNT); (INDEX) += 1)
#define forCountDown(INDEX, COUNT)  for ((INDEX) = (COUNT) - 1; (INDEX) >= (COUNT); (INDEX) -= 1)
// loop* - infinite loop.
#define loop                        for (;;)
#define loopCount(INDEX)            for ((INDEX) = 0;            ; (INDEX) += 1)
// loopOnce - single iteration loop.
#define loopOnce                    for (int __index__ = 0; __index__ < 1; __index__++)

// Return macroes
// Again some will hate these but I find they help prevent mistakes and improve
// readability.
// greturn* - macroes that call function exit code.  See genter.
#define greturnIf(C,V)     if ((C)) { greturn (V); }
#define greturn0If(C)      if ((C)) { greturn 0; }
#define greturn1If(C)      if ((C)) { greturn 1; }
#define greturnVoidIf(C)   if ((C)) { greturn; }
#define greturnNullIf(C)   if ((C)) { greturn NULL; }
#define greturnTrueIf(C)   if ((C)) { greturn gbTRUE; }
#define greturnFalseIf(C)  if ((C)) { greturn gbFALSE; }
// return - macroes that do not call function exit code.  So just wrapping 
//          return keyword.
#define returnIf(C,V)      if ((C)) { return (V); }
#define return0If(C)       if ((C)) { return 0; }
#define return1If(C)       if ((C)) { return 1; }
#define returnVoidIf(C)    if ((C)) { return; }
#define returnNullIf(C)    if ((C)) { return NULL; }
#define returnTrueIf(C)    if ((C)) { return gbTRUE; }
#define returnFalseIf(C)   if ((C)) { return gbFALSE; }
#define continueIf(C)      if ((C)) { continue; }
#define breakIf(C)         if ((C)) { break; }

// Goto macroes
// I am not a huge goto user but there are cases where they are useful.  Similar
// macroes to the returns above.  
// stopIf jumps to a specific label in the code.
/*lint -save -e9022 */ 
#define gotoIf(C,G)        if ((C)) { goto G; }
/*lint -restore */
#define stopIf(C)          if ((C)) { goto STOP; }

// debug macroes
// Essentially wrapping assert but in a style that I find easier to read.
#if defined(_DEBUG)

#define debugHaltIf(VALUE, STRING)  if (VALUE) { debugHalt(STRING); }
#define debugHalt(STRING)           /*lint -save -e944 -e917 -e920 -e960 -e9008 -e9007 */ assert(gbFALSE && (STRING)) /*lint -restore */
#define debugPrint(WSTR)            OutputDebugString(WSTR)

#if grlWINDOWS == 1
#define debugCheckMemory()    _CrtCheckMemory();
#else
#define debugCheckMemory()
#endif

#else

#define debugHaltIf(VALUE, STRING)
#define debugHalt(STRING)
#define debugPrint(WSTR)
#define debugCheckMemory()

#endif

// Enter macroes
// When you get into the code you will see genter; in every (or most every) 
// function.  I wish 'C' or compilers had some option to add your own function
// entry code so I didn't have to do this.  
//
// Uses, At one point I had my own profiling code because there was a time when
// Microsoft stopped providing a profiler and there were no others that were 
// affordable or free.  Now we have options it isn't really necessary so I 
// removed that code but it was useful for a while.  
//
// I also had a simple garbage collector idea once where temporary created 
// heap memory would be cleaned up on function exit.  It was removed because
// it was not improving my coding life.
//
// Now it is mainly used for the TRACE_IS_ON flag.
#if 0 // kept in case I need to revisit.
#if   (GPROFILE_IS_ON == 1) && (GTRACE_IS_ON == 1)

#define genter \
   static Gindex ___profIndex___ = -1;\
   Gtime         ___profTime___  = gprofileEnter(&___profIndex___, __FILE__, __FUNCTION__);\
   gtraceEnter();

#elif GPROFILE_IS_ON == 1

#define genter \
   static Gindex ___profIndex___ = -1;\
   Gtime         ___profTime___  = gprofileEnter(&___profIndex___, __FILE__, __FUNCTION__);

#elif GTRACE_IS_ON == 1
#endif
#endif

#if GTRACE_IS_ON == 1

#define genter \
   gtraceEnter()

#else

#define genter 

#endif

// Return macroes
// Complements the enter macroes and is called on exit of a function.
#if 0
#if   (GPROFILE_IS_ON == 1) && (GTRACE_IS_ON == 1)

#define greturn \
   gtraceExit();\
   gprofileExit(___profIndex___, ___profTime___);\
   return

#elif GPROFILE_IS_ON == 1

#define greturn \
   gprofileExit(___profIndex___, ___profTime___);\
   return

#elif GTRACE_IS_ON == 1
#endif
#endif

#if GTRACE_IS_ON == 1

#define greturn \
   gtraceExit();\
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
#define gidGetFromC(VALUE)                \
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

/******************************************************************************
type:
******************************************************************************/

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

//TODO: Move to Gs
#define gsSubStrINDEX_START 0
#define gsSubStrINDEX_END   GindexMAX

// typedefs
// Why is this done?  One of C's failing was that it was not strict on defining
// what size a type was.  This lead to reduced portability of raw C code.  If
// you looked at any library with a certain amount of age you will see that 
// every one of them does something like this just so that they have some
// predictability porting their code to various hardware architectures and
// compilers.

// Char may seem like a curious typedef but this is mainly for PCLint which 
// warns against using char
typedef signed char        Char;
typedef unsigned char      Uchar;

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

// Keys in data containers are always const pointers.  So in the generic sense
// a key a void *
typedef Gp                 Gkey;
// The basic Key Value pair.  Value is a generic void *
typedef struct
{
   Gkey const              *key;
   Gp                      *value;
} GkeyP;

// Id is a basic natural number.  Not the same as a GUID but meant to be used
// in the same way in that it should be a unique number on other data.
typedef Gn4                Gid;

// HashN is for hashing functions.  Hash resturns are naturals.
typedef Gn4                GhashN;

// HeapN is for the heap uses.
typedef Gn4                GheapN;

/*lint -restore */

// Integer 2D Point structure.
typedef struct
{
   Gih          x,
                y;
} Gixy;

// Natural 2D Point structure.
typedef struct
{
   Gnh          x,
                y;
} Gnxy;

// Forward reference for GRL's Dynamic strings.
typedef struct Gs Gs;
typedef struct Gs Gpath;

// Generic value type.
typedef enum
{
   gvTypeNONE,

   gvTypeI,
   gvTypeN,
   gvTypeP,
   gvTypeR,

   gvTypeS,

   gvTypeCOUNT
} GvType;

// Generic data structure for any of the base data types.
typedef union
{
   Gip             i;
   Gnp             n;
   Gp             *p;
   Grp             r;
} Gvp;

// Generic data structure for any of the base data types but includes the 
// actual stored type.  Why use this?  Use this if you have a container that
// can store any of the types and you may not know based on location in the
// container that the stored type might be.
typedef struct
{
   GvType       type;
   union
   {
      Gip          i;
      Gnp          n;
      Gp          *p;
      Grp          r;
      Gs          *s;
   }            value;
} Gv; //lint !e960 !e9018

// GUID type.
typedef struct
{
   Gn8             n[2];
   Gn1             b[16];
} Gguid;

// Common callback function patterns.
typedef Gcompare   (*GrlCompareFunc)(        Gp const * const valueA, Gp const * const valueB);
typedef void       (*GrlDestroyFunc)(        Gp       * const value);
typedef void       (*GrlForEachFunc)(        Gp       * const value);
typedef void       (*GrlForEachKeyFunc)(     Gkey const * const key,    Gp       * const value);
typedef Gp        *(*GrlForEachProcessFunc)( Gp       * const value);
typedef void       (*GrlForEachAltFunc)(     Gp       * const value, GrlForEachFunc func);
typedef Gp const  *(*GrlGetFunc)(            Gp const * const mem, Gi4 const index);
typedef GhashN     (*GrlHashFunc)(           Gp const * const value);
typedef void       (*GrlSwapFunc)(           Gp       * const mem, Gi4 const indexA, Gi4 const indexB);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
