
# G.R.L.: Groot's Runtime Library

This doc is in development so it will change quite a lot from update to update.  I am using Visual Studio for editing the doc.  Tabs are 4 but indents are 1 and spaces instead of tabs.

# Table Of Contenst:
**About G.R.L.**
 Description
 History
 License
 Goals
**How to compile GRL library**
 g_config.h
  GCHECK_MEMORY_IS_ON
  GMEM_INCLUDES_TYPE_STRING
  GTRACE_IS_ON
**How to compile with GRL library**
**How to use GRL library**
**Style**
**Macroes**
 breakIf()
 continueIf()
 debugHalt*()
 debugCheckMemory()
 debugPrint()
 for*(), loop*()
 gotoIf(), stopIf()
 return*()
 genter, greturn
 greturn*()
 gsizeof()
 gpHash", "gpHash()
**API**
**Grl**
 Function
**Char, Uchar**
 Type
**Galignment**
 Type
**Gb (Boolean)**
 Type
**Gbit**
 Type
 Function
**gbitArray**
 Function
**Gcompare**
 Type
**Gcount**
 Type
 Constant
 Function
**Gguid**
 Type
 Function
**GhashN**
 Type
**GheapN**
 Type
**Gi (Integer)**
 Type
 Constant
**Gid**
 Type
 Function
**Gindex**
 Type
 Constant
 Function
**Gkey**
 Type
**GkeyP**
 Type
**Gleak**
 Function
**Glock**
 Type
 Function
**Gmem**
 Function
**Gn (Natural and 0)**
 Type
 Constant
**Goffset**
 Type
 Constant
**Gosversion**
 Constant
 Function
**Gp (void)**
 Type
**Gposition**
 Type
**Gprofile**
**Gr (Real)**
 Type
 Constant
**Grandom**
 Type
 Function
**Gsize**
 Type
 Constant
 Function
**Gsize**
 Function
**Gtime**
 Type
 Function
**Gtrace**
 Constant
 Function
**Gv, GvType**
 Type
 Function
**Gvp**
 Type
**G*Func**
 Type

# About G.R.L.

## Description

G.R.L. (Girl) is a C kitchen sink library to make development easier.

## History

I joined a company back in 1995 that created software for Sun OS, Sun Solaris, SGI Irix, and Window NT 3.XX. In order for them to do that they used a cross platform library called Galaxy which was owned by a company called Visix. A little time after Java came on to the scene and a Visix thought that was going to be the future of cross platform development. They let Galaxy stagnate and focused on a Java product they developed. Moving on a few years the Java product did not sell well (I believe, no facts to back it up) and their bread and butter clients using Galaxy were moving on as their products were becoming stagnant because Galaxy was not keeping up with the times. Visix just decided to pack up and quit.

Galaxy is now owned by a Brazilian company called Ambiencia which appeared to have no interest in supporting any of the existing clients (without the clients to pay for yet another round of licensing to them even though a lot already paid a lot to Visix) and so essentially killed any  chance for Galaxy to move on. It is still around but no one should use it anymore in my opinion.  QT, Microsoft's WPF, Xamarin, and others have surpassed Galaxy.

QT did exist at the same time when the company was looking for a cross platform library but it was very small back then and not as complete as Galaxy was. Plus C++ compilers back then were not the same quality from platform to platform. Also the developers the company had already, mostly FORTRAN programmers, would have a harder jump to C++ than to C.  Or at least that was the feeling at the time.

This left us in a bit of a lurch. So on a whim, back in and around 2000, I started to make a kitchen sink library to replace Galaxy on my own time at home, in the hopes it would be adopted by the company. It never was.  They opted to move to C++ and its standard library instead. However, I use this library in my hobby coding so I still continue with the development of the library.  This library has gone through a couple of iterations as I was playing with a few ideas which some just did not work out.

Why not just wrap C++ stdlib for this work instead of writing everything again in C?  That is also an option when doing something like this.  I did not do it that way because I am not a big fan of C++.  I also like control.  I want to be able to tweak the implementation and not leave it in someone else's hands.  Yeah, yeah, reinventing the wheel.  But sometimes it is necessary to be happy.

Initially GRL stood for "Galaxy Replacement Library" but since it was not going to be doing that in reality, I just decided to rebrand it (de) "Groot's Runtime Library".  For the longest time I wanted to hopefully make money of this code but in my opinion that time has long since past.  So I decided to make it free for use.

## License

```
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
```

## Goals

* Kitchen sink library.  It should do 'almost' everything you need for development.

* Simplify API.  Some tasks networking with socket IO I find has an odd API or unknown gotchas that you will only find out once you hit them or have carefully read the fine detail in the documentation.  I would like to get rid of as much of those gotchas as possible.

* Cross platform.  Currently failing here because I am only adding to the library when the need arrises.  OSX and *NIX OSes will eventually come but currently, I spend most of my life in  WINDOWS.

* Performance.  The library should not really slow you down in terms of coding or in terms of run time.  There are always going to be some compromises but for the most part it should be out of the way and not causing grief.


# How to compile GRL library

I do not use helpers like CMake.  Mainly because I have not found one that is not annoying to me on some way.  So with this project there will be a...

* Visual Studio project(s) for a Windows compile.

* XCode project for OSX compiles (once done)

* Make file(s) or whatever for *NIX compiles (once done)


Find the appropriate solution for you and compile.

The library compiles to a static library instead of a DLL or shared library.  If you want a DLL or shared libary then you will have to do the work yourself.  I like to keep my life simple and just use static libraries as there is less pain involved when it comes time to release.

When you build the library you will need to provide some compile time defines.

* <strong>grlWINDOWS, grlOSX, or glrUNIX</strong>, needs to be defined so that proper platform code is compiled for the libary.

* <strong>grl32 or grl64</strong>, needs to be defined so that the proper architecture code is compiled for the library.

* <strong>grlSWAP</strong>, needs to be defined on little endian machines.


## g_config.h

In the source file g_config.h there are some flags at the top that you may wish to set for different code to be compiled in.

### GCHECK_MEMORY_IS_ON

Set this to 1 if you want at every dynamic memory (gmemCreate and gmemDestroy and related) call a check on the sanity of the heap to be done.  On Windows this is a CRT function call.

You would use this if you are experiencing heap corruption and wanting to find out who might be corrupting the heap or at least narrow it down to when the Heap was good to when it became bad in an effort to narrow down your search.

### GMEM_INCLUDES_TYPE_STRING

Dynamic memory creations (gmemCreate* calls) often include a 'type' string.  This string is stored with the dynamic memory in debug by default.  Sometimes this comes in handy when you are dealing with baffling dynamic memory pointer issues.

### GTRACE_IS_ON

Function tracing.  This is mean to dump to a file the code flow.  The file will hold almost all of the functions that were called assuming genter and greturn* were used in the code.

# How to compile with GRL library

When you build your project and you intend to use this library, you will need to provide some compile time defines.

* <strong>grlWINDOWS, grlOSX, or glrUNIX</strong>, needs to be defined so that proper platform code is compiled for the libary.

* <strong>grl32 or grl64</strong>, needs to be defined so that the proper architecture code is compiled for the library.

* <strong>grlSWAP</strong>, needs to be defined on little endian machines.


Add the grl.lib and grl include path to your build.

# How to use GRL library

Add to your source file(s) the grl include...

```
#include "grl.h"
```

At your program start you need to call...

```
if (!grlStart())
{
   // Failed to start GRL.  Shutdown.
}
```

grlStart() will set up internal states of the library.  Failure to do this will cause problems.

At your program exit you should call...

```
grlStop();
```

grlStop() will display debug information like a leak report if you are doing leak checking with GRL.  It is not strictly necessary to call but it would be a wise thing to do in my opinion.

# Style

I use a particular style with GRL and my own coding.  With this style is makes identifying what something is fairly easily.

Naming convention being used.

```
Program Global:
Constant:        prefixTypeNameCONSTANT_VALUE
Type:            PrefixTypeName
Variable:        [There are none.  Use a module global and a function to manipulate it.]
Function:        prefixFuncionName()

Libary Global:
Function:        _prefixFunctionName

Module Global:
Variable:        static ... _variableName
Function:        static ... _FunctionName

Function Levle:
Varaible:        variableName
```

prefix being a string that identifies what part of the code it belongs to.  like glist for linked lists for example.

The capitalization is important.  I dislike the use of '_' because I find it annoying to type so I heavily use CamelCasing to differentiate the words in a name. Starting letter may or may not be capitalized and it is specific to usage.

The idea is that by just by looking at a name of something you should be able to tell the scope of what you are looking at without having to find our where it was actually defined.

Also on a little of the OCD side, I organize the C files so that I have sections, in order, includes, constants, types, variables, local function prototypes, global function definitions, local function definitions.  Simlar H files are ordered, includes (if needed), constants, types, and glocal function prototypes.

Indents are 3.

I line up =, logic ops, parameters on mulitple lines, etc.

I never have an assignment in a conditional, which means I write x == 0 instead of 0 == x.

Logic statements have the logic op at the end (not at the beginning) using reverse indentation.

Code is paragraphed.

etc.

# Macroes

You may find some or all of these macroes curious or infuriating.  I use them for the reason of better code readability (subjective I know) and better coding experience, reducing tired programmer mistakes and related.  You do not have to use any of these but I use them a lot in my own coding.

## breakIf()

```
#define breakIf(C)         if ((C)) { break; }
```

Loop control wrappers for common patterns.  Makes for easier to read code in my opinion and slightly less typing.

## continueIf()

```
#define continueIf(C)      if ((C)) { continue; }
```

Loop control wrappers for common patterns.  Makes for easier to read code in my opinion and slightly less typing.

## debugHalt*()

```
#define debugHalt(STRING)           /*lint -save -e944 -e917 -e920 -e960 -e9008 -e9007 */ assert(gbFALSE && (STRING)) /*lint -restore */
#define debugHaltIf(VALUE, STRING)  if (VALUE) { debugHalt(STRING); }
```

Halt is calling assert().  I just find it easier to read than using the assert() function call.

## debugCheckMemory()

```
#define debugCheckMemory()    _CrtCheckMemory();
```

CheckMemory will test the dynamic heap for corruption.  This can be handy when trying to find memory corruption.  Sprinkle these functions around your code where you think the corruption may be happening.

## debugPrint()

```
#define debugPrint(WSTR)            OutputDebugString(WSTR)
```

Print will print a wchar_t * string to the output window in case of Visual Studio on Windows.  Nothing specific for OSX and Linux yet.

## for*(), loop*()

```
#define forCount(INDEX, COUNT)      for ((INDEX) = 0;           (INDEX) <  (COUNT); (INDEX) += 1)
#define forCountDown(INDEX, COUNT)  for ((INDEX) = (COUNT) - 1; (INDEX) >= (COUNT); (INDEX) -= 1)
#define loop                        for (;;)
#define loopCount(INDEX)            for ((INDEX) = 0;            ; (INDEX) += 1)
#define loopOnce                    for (int __index__ = 0; __index__ < 1; __index__++)
```

Wrappers for loops.  You may find these curious but I find these save me some headaches as they reduce errors like bad increment and such.  Plus I find they are easier to read.

## gotoIf(), stopIf()

```
#define gotoIf(C,G)        if ((C)) { goto G; }
#define stopIf(C)          if ((C)) { goto STOP; }
```

Wrappers for goto calls.  If you need to use these, use them sparingly and only forward jumps to a equal or higher level scope.  Do not jump into another scope.  Sometimes it is useful for simple exception like handling.  Stop if will jump to the label STOP.

## return*()

```
#define returnIf(C,V)      if ((C)) { return (V); }
#define return0If(C)       if ((C)) { return 0; }
#define return1If(C)       if ((C)) { return 1; }
#define returnVoidIf(C)    if ((C)) { return; }
#define returnNullIf(C)    if ((C)) { return NULL; }
#define returnTrueIf(C)    if ((C)) { return gbTRUE; }
#define returnFalseIf(C)   if ((C)) { return gbFALSE; }
```

Basic return equivalents to greturn.  These do not call greturn and so are not paired with genter.

## genter, greturn

```
#if 0 // kept in case I need to revisit.
#if   (GPROFILE_IS_ON == 1) && (GTRACE_IS_ON == 1)

#define genter
   static Gindex ___profIndex___ = -1;
   Gtime         ___profTime___  = gprofileEnter(&___profIndex___, __FILE__, __FUNCTION__);
   gtraceEnter();

#elif GPROFILE_IS_ON == 1

#define genter
   static Gindex ___profIndex___ = -1;
   Gtime         ___profTime___  = gprofileEnter(&___profIndex___, __FILE__, __FUNCTION__);

#elif GTRACE_IS_ON == 1
#endif
#endif

#if GTRACE_IS_ON == 1

#define genter
   gtraceEnter()

#else

#define genter

#endif

// Return macroes
// Complements the enter macroes and is called on exit of a function.
#if 0
#if   (GPROFILE_IS_ON == 1) && (GTRACE_IS_ON == 1)

#define greturn
   gtraceExit();
   gprofileExit(___profIndex___, ___profTime___);
   return

#elif GPROFILE_IS_ON == 1

#define greturn
   gprofileExit(___profIndex___, ___profTime___);
   return

#elif GTRACE_IS_ON == 1
#endif
#endif

#if GTRACE_IS_ON == 1

#define greturn
   gtraceExit();
   return

#else

#define greturn
   return

#endif
```

I have always wanted a way to add common code to the entry of the function and to the exit of a function.  Unfortunately there is no nice way to do this.  So all the higher level code that I write includes a genter and greturn macroes.  This way I can do what I want on entry and exit.

Things I have tried:

* Profiler code - For a time there was not any free profilers so I added some code to do that. Unfortunately it was not threadable but for the times I needed it it was useful.  Fortunately there are a few good free ones available now like, MicroProfiler, Sleepy, etc. so my code is no longer necessary.

* Tempory data cleanup - At one point I played with the idea of keeping track temporary dynamically allocated data that would automatically cleanup at function exit.  Unfortunately it was not that clean and added a bit more code smell so I felt it was not really worth it.

* I still have include function tracing.  Which unfortunately does not work well in a multi-threaded environment.  Works well in a single threaded program and what happens is that every function entry will be recorded in a trace file.


Those are some of the reasons I was using genter and greturn.  I keep them around just in case another need arrises.

## greturn*()

```
#define greturnIf(C,V)     if ((C)) { greturn (V); }
#define greturn0If(C)      if ((C)) { greturn 0; }
#define greturn1If(C)      if ((C)) { greturn 1; }
#define greturnVoidIf(C)   if ((C)) { greturn; }
#define greturnNullIf(C)   if ((C)) { greturn NULL; }
#define greturnTrueIf(C)   if ((C)) { greturn gbTRUE; }
#define greturnFalseIf(C)  if ((C)) { greturn gbFALSE; }
```

Wrappers for common greturn cases.  Makes for easier to read code in my opinion and slightly less typing.  These call greturn while matches genter.

## gsizeof()

```
#define gsizeof(V)         ((Gsize) sizeof(V))
```

Wrapper for sizeof function.

## gpHash", "gpHash()

```
#define gpHash(P) ((GhashN) ((((Gnp) P) / 4) % GhashNMAX))
```

A basic function for hashing a pointer.  This is assuming pointers are 4 byte aligned.

# API

Like a lot of C libraries I have defined my own types just to address the problem that C's base integer types are not strictly of a certain size.  Or there are missing types like boolean.

Granted newer updates to C have tried to rectify the situation but maybe a little too late.  Plus I dislike typeing '_' but will use it only for constants for historical reasons.  So all the new types like wchar_t, int16_t, etc.  God I hate that '_'.  It slows down typing in my opinion and does not really improve readability in my opinion.

Also other API that do not include a specific type but more a module for some purpose.

# Grl

Library level calls.  Mainly to set up the library before use.

## Function

```
grlAPI Gpath   *grlGetExePath(   void);
```

Get the path to the exe file.

```
grlAPI Gb       grlIsStarted(    void);
```

Is the grl library initialized and ready.

```
grlAPI Gb       grlSetExePath(   Gpath * const path);
```

Set the exe file path.  Not usually called by you.  The exe path is set on program start.

```
grlAPI Gb       grlStart(        void);
```

Start the grl library.

```
grlAPI void     grlStop(         void);
```

Stop the grl library.

# Char, Uchar

I define these because I am using PCLint program to keep the code somewhat clean of issues.  One of the things with PCLint is that it warns about using char and unsigned char so I have these defined to avoid the warning/error.

## Type

```
typedef signed char        Char;
typedef unsigned char      Uchar;
```

Not usually types I use.  However I define these because I am using PCLint program to keep the code somewhat clean of issues.  One of the things with PCLint is that it warns about using char and unsigned char so I have these defined to avoid the issue.

# Galignment

Various functions require defining an alignment in the horizontal and vertical directions.  Trying to define one type to cover them all.

## Type

```
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
```

Various functions require defining an alignment in the horizontal and vertical directions.  Trying to define one type to cover them all.

# Gb (Boolean)

Yes stdbool.h is a thing now for C but this was predating that.  GRL uses the above for boolean results.  UNDEFINED is rarely used and whatever uses UNDEFINED should explicitely say so.  Otherwise assume it is not a possibility.

## Type

```
typedef enum
{
   gbFALSE              =  0,
   gbTRUE               =  1,
   gbUNDEFINED          = -1
} Gb;
```

Yes stdbool.h is a thing now for C but this was predating that.  GRL uses the above for boolean results.  UNDEFINED is rarely used and whatever uses UNDEFINED should explicitely say so.  Otherwise assume it is not a possibility.

# Gbit

## Type

```
typedef unsigned int       Gbit;
```

This is specific to bit fields in a struct.  Because every time using standard C types, I forget the "unsigned" keyword.

## Function

```
grlAPI Gn4      gbitGet(          Gn4 const data, Gindex const bit, Gcount const count);
```

Find the value of bits in a simple 4 byte natural.

```
grlAPI Gn4      gbitSet(          Gn4 const data, Gindex const bit, Gcount const count, Gn4 const value);
```

Set the value of bits in a simple 4 byte natural.

# gbitArray

Simple functions for setting bits in an array of Gn4 values.  Values can span over Gn4 boundaries.

## Function

```
grlAPI Gn4      gbitArrayGet(     Gn4 const * const data, Gindex const bit, Gcount const count);
```

Get the value of a bit range in the Gn4 array.

```
grlAPI Gsize    gbitArrayGetSize( Gcount const count);
```

Calculation on how many Gn4 values are required to store count bits.

```
grlAPI Gb       gbitArraySet(     Gn4       * const data, Gindex const bit, Gcount const count, Gn4 const value);
```

Get the value of the bits at a given bit range in the Gn4 array.

# Gcompare

Defining the result for all compare functions.  I do not remember why I have UNKNOWN and for the most part it is never used.  But like Gb and UNDEFINED, if a function returns UNKNOWN it should be made very clear.  I may remove it in the future.

## Type

```
typedef enum
{
   gcompareLESS_THAN    = -1,
   gcompareEQUAL        =  0,
   gcompareGREATER_THAN =  1,
   gcompareUNKNOWN      =  2
} Gcompare;
```

Defining the result for all compare functions.  I do not remember why I have UNKNOWN and for the most part it is never used.  But like Gb and UNDEFINED, if a function returns UNKNOWN it should be made very clear.  I may remove it in the future.

# Gcount

A common integer/natural type used in a lot of places.  This will be the most efficient size for the platform and currently is an integer and not a natural.  I initially tried a natural but for some things, you need negative numbers.  For simplicity I kept it an integer.  If you end up in a situation where the efficient size integer is not enough range then you will have to do something else.

Why not just use the raw integer type?  Well, sometimes the type adds to the description of the variable/parameter.  In this case, if I have a function that expects an offset then it is clear what that variable intends to do.  You may not need to even look at the name of the variable.  So I use it as a form of making the code more clear.

## Type

```
typedef Gi4                Gcount;
```

## Constant

```
#define GcountMAX             Gi4MAX
```

The limit constants for these types.

## Function

```
#define gcountIsGood(C)    (0 <= (C))
```

IsGood check for a gcount.

# Gguid

GUID type wrapper.  Using system calls to handle GUIDs.

## Type

```
typedef struct
{
   Gn8             n[2];
   Gn1             b[16];
} Gguid;
```

## Function

```
grlAPI void     gguidCreateContent(       Gguid * const guid);
```

Wrapper of OS routines for Initializing the contents of a GUID with a new unique GUID value.

```
grlAPI void     gguidCreateContentFromA(  Gguid * const guid, Char const * const string);
```

Initialize a Gguid from a char string representation of a GUID.

```
grlAPI Gb       gguidIsEqual(             Gguid const a, Gguid const b);
```

Test two guids for equality.

# GhashN

The data type that all hash functions will return.

## Type

```
typedef Gn4                GhashN;
```

The data type that all hash functions will return.

# GheapN

The data type that all heaps will use.  Currently only the Gtree uses this.  See Gtree implementation.

## Type

```
typedef Gn4                GheapN;
```

# Gi (Integer)

Integer type.

## Type

```
typedef int8_t             Gi1;
typedef int16_t            Gi2;
typedef int32_t            Gi4;
typedef int64_t            Gi8;
```

As you can see I am using the stdint types.  I believe when I was starting out with GRL it was not really common yet and I was using standard C types.  I could be wrong.  But like any other library, I define my own types based on memory size.  Instead of bits I use byte count.

```
typedef Gi8                Gi;
```

Same as the above but the numberless versions represent the largest possible representation of the type for the platform.  Which may not be the most efficient form for the types.

```
typedef intptr_t           Gip;
```

Pointer sized versions of integer and natural.

```
typedef Gi4                Gih;
```

Half size versions for the platform.

## Constant

```
#define GiMAX                 Gi8MAX

#define Gi1MAX                INT8_MAX
#define Gi1MIN                INT8_MIN
#define Gi2MAX                INT16_MAX
#define Gi2MIN                INT16_MIN
#define Gi4MAX                INT32_MAX
#define Gi4MIN                INT32_MIN
#define Gi8MAX                INT64_MAX
#define Gi8MIN                INT64_MIN

#define GipMAX                INTPTR_MAX
```

The limit constants for these types.  Not complete when it comes to Reals but I have not needed the other constants just yet.

# Gid

Simpler than a Gguid.  The uniqueness of an id is left to the programmer.

## Type

```
typedef Gn4                Gid;
```

Simpler than a Gguid.  The uniqueness of an id is left to the programmer.

## Function

```
#define gidGetN(ID)        ((Gn4) ID)
```

Return the natural value of the id.

```
#define gidGetFromN(VALUE) ((Gid) VALUE)
```

Convert a natrual value to an id.

```
#if defined(grlSWAP)
#define gidGetC(ID, CHAR4)
   (CHAR4[3] = (Char) (((ID) & 0xff000000) >> 24),
    CHAR4[2] = (Char) (((ID) & 0x00ff0000) >> 16),
    CHAR4[1] = (Char) (((ID) & 0x0000ff00) >>  8),
    CHAR4[0] = (Char) (((ID) & 0x000000ff)))
#else
#define gidGetC(ID, CHAR4)
   (CHAR4[0] = (Char) (((ID) & 0xff000000) >> 24),
    CHAR4[1] = (Char) (((ID) & 0x00ff0000) >> 16),
    CHAR4[2] = (Char) (((ID) & 0x0000ff00) >>  8),
    CHAR4[3] = (Char) (((ID) & 0x000000ff)))
#endif
```

Convert an id to a 4 character char string, not NULL terminated.

```
#if defined(grlSWAP)
#define gidGetFromC(CHAR4)
   ((CHAR4[3] << 24) |
    (CHAR4[2] << 16) |
    (CHAR4[1] <<  8) |
    (CHAR4[0]))
#else
#define gidGetFromC(VALUE)
   ((CHAR4[0] << 24) |
    (CHAR4[1] << 16) |
    (CHAR4[2] <<  8) |
    (CHAR4[3]))
#endif
```

Convert a 4 character char string, not NULL terminated, to an id.

```
#define gidIsEqual(A,B)    ((A) == (B))
```

Compare two ids for equality.

```
#define gidIsGood(I)       (0 < (I))
```

Check if the id is valid.

```
#define gidIsUndefined(ID) ((ID) == Gn4MAX)
```

Check if the is set to something.

# Gindex

A common integer/natural type used in a lot of places.  This will be the most efficient size for the platform and currently is an integer and not a natural.  I initially tried a natural but for some things, you need negative numbers.  For simplicity I kept it an integer.  If you end up in a situation where the efficient size integer is not enough range then you will have to do something else.

Why not just use the raw integer type?  Well, sometimes the type adds to the description of the variable/parameter.  In this case, if I have a function that expects an offset then it is clear what that variable intends to do.  You may not need to even look at the name of the variable.  So I use it as a form of making the code more clear.

## Type

```
typedef Gi4                Gindex;
```

## Constant

```
#define GindexERROR           Gi4MIN
#define GindexMAX             Gi4MAX
```

The limit constants for these types.

## Function

```
#define gindexIsGood(I,C)  (0 <= (I) && (I) < (C))
```

IsGood checks for a gindex.

# Gkey

The general idea of a key for use in key value pais for the data containers.  A key will always be a const pointer.  So uniqueness is the pointer and not necessarily the contents of the pointer.

## Type

```
typedef Gp                 Gkey;
```

# GkeyP

The basis of a key value pair.  A const pointer for the key and some generic data pointer for the value.

## Type

```
typedef struct
{
   Gkey const              *key;
   Gp                      *value;
} GkeyP;
```

The basis of a key value pair.  A const pointer for the key and some generic data pointer for the value.

# Gleak

No types.  Just an API for tracking resource leaks.  Not specifically for memory leaks but is used by gmem for dynamic memory leak tracking.

Internally gleak code maintains a hash table of leak records.  The hash table is organized as bins of linked lists of leak records.  This is reasonably fast in debug.  If not, you may need to tweak the hash table size to reduce linked list lengths.

gleak is completely disabled in release builds.

## Function

```
#define gleakCreate(P,S) gleakCreate_((P), (S), __FILE__, __LINE__)
grlAPI Gp  *gleakCreate_(   Gp * const p, Gsize const size, Char const * const file, Gindex const line);
```

You would not use gleakCreate_() directly, just gleakCreate() macro.  You should call gleakCreate() on the same pointer up the call stack.  The last gleakCreate() call will overwrite any previous leak record.

Create a leak record.  If this leak record is not destroyed it will be reported at grlStop().  A leak record includes the file and location in the file where the leak occurred.  You would not use gleakCreate_() directly, just gleakCreate() macro.  You should call gleakCreate() on the same pointer up the call stack.  The last gleakCreate() call will overwrite any previous leak record.

```
#define gleakDestroy(P)  gleakDestroy_((P))
grlAPI Gp  *gleakDestroy_(  Gp *p);
```

Destroy a leak record.  This is done when the resource was properly closed, destroyed, or whatever needed to happen to it.

```
grlAPI Gb   gleakLockEnter( void);
grlAPI Gb   gleakLockExit(  void);
```

If you have a lot of gleakCreate() calls in rapid succession you may want to call wrap them in between a LockEnter and LockExit so that the lock only happens once and the speed of the enclosed code will be uninterrupted and fast.

# Glock

Critical Section lock routines.

<strong>Example Use:</strong>

```
// Define the lock.
static Glock _lock;

...

// Somewhere on startup.
{
   // Initialize the lock
   glockCreateContent(&_lock);
}

// Somewhere on shutdown.
{
   // Clean up
   glockDestroyContent(&_lock);
}

// Somewhere threaded.
{
   // Entering the critical section.  The thread will halt here if another thread has the lock.
   glockEnter(&_lock);

   // If the thread is executing here then it is the only one executing here.

   // We are done, release the lock.
   glockExit(&_lock);
}

```

## Type

```
#if grlWINDOWS == 1
typedef CRITICAL_SECTION Glock;
#else
#endif
```

Currently only Windows defined.  I haven't started on any other platforms.

## Function

```
grlAPI void       glockCreateContent(    Glock * const lock);
```

Initializes a lock.

```
grlAPI void       glockDestroyContent(   Glock * const lock);
```

Clean up a lock.

```
grlAPI void       glockEnter(            Glock * const lock);
```

Enter a critical section.

Code will stop here until the lock is obtained.

```
grlAPI void       glockExit(             Glock * const lock);
```

Exit a critical section.

# Gmem

Dynamic memory functions.  In debug these will make use of gleak for memory leak tracking.

In both debug and release, dynamic memory buffers that are 'small' are pooled.  Meaning, if you create a bunch of small buffers like the size of 80 bytes.  Then all those buffers when 'destroyed' will just be kept around in a pool of buffers that are 80 bytes in size.  When the next time the program asks for an 80 byte buffer, the first available buffer from the pool is used.

Why are we doing this?  Dynamic memory creation and destruction can be slow.  Often causing a kernel call which basically locks the system down in order to perform the operation.  If we can avoid these calls as much as possible then the speed of the program will be greatly improved.  At the cost of using some more memory that is.  Reusing a previously allocated buffer is a lot quicker than having to free it and then recreate it.

Use gmemFlushPools() to reclaim the memory.  Eventually I may add a thread to do the pool flushing but for now this is the responsibility of the programmer.

## Function

```
#define memCreate(               BYTECOUNT)                                      calloc((size_t) 1, (size_t) (BYTECOUNT))
#define memCreateType(           TYPE)                                  (TYPE *) memCreate(gsizeof(TYPE))
#define memCreateTypeArray(      TYPE, COUNT)                           (TYPE *) memCreate(gsizeof(TYPE) * (COUNT))
```

Simple wrappers around standard C dynamic memory creation functions.  Not gleak tracked.

CreateType, and CreateTypeArray are convenience functions for making a buffer of a size of a type or a buffer of a size of an array of type.  I use these to reduce tired programmer errors when writing out dynamic memory creation calls.

```
#define memDestroy(              P)                                              free((Gp *) (P))
```

Freeing the dynamic memory using standart C functions.

```
#define gmemClear(               P, BYTECOUNT)                                   gmemClearAt(   (P),     (BYTECOUNT),               0)
#define gmemClearType(           P, TYPE)                                        gmemClearAt(   (P),     gsizeof(TYPE),             0)
#define gmemClearTypeAt(         P, TYPE, INDEX)                                 gmemClearAt(   (P),     gsizeof(TYPE),             gsizeof(TYPE) * (INDEX))
#define gmemClearTypeArray(      P, TYPE, COUNT)                                 gmemClearAt(   (P),     gsizeof(TYPE) * (COUNT),   0)
#define gmemClearTypeArrayAt(    P, TYPE, COUNT, INDEX)                          gmemClearAt(   (P),     gsizeof(TYPE) * (COUNT),   gsizeof(TYPE) * (INDEX))

grlAPI void  gmemClearAt(     Gp         * const p,    Gcount const byteCount, Gindex const byteIndex);
```

Given a pointer to a buffer, zero out its memroy.

<strong>Type</strong> will specify the size of memory to zero out.

<strong>At</strong> will indicate where inside an array of types to zero out.

<strong>Array</strong> will indicate we will be zeroing out an array of types.

```
#define gmemCopyTypeArray(       P, TYPE, COUNT, INDEX_SRC,    INDEX_DST)        gmemCopy(      (P),     gsizeof(TYPE) * (COUNT),   gsizeof(TYPE) * (INDEX_SRC),  gsizeof(TYPE) * (INDEX_DST))
```

Copying a subset of an array of types, onto itself at a new location.

```
#define gmemCopyOver(            PSRC, BYTECOUNT,              PDST)             gmemCopyOverAt((PSRC),  (BYTECOUNT),               0,                       (PDST),  (Gi) 0)
#define gmemCopyOverType(        PSRC, TYPE,                   PDST)             gmemCopyOverAt((PSRC),  gsizeof(TYPE),             0,                       (PDST),  (Gi) 0)
#define gmemCopyOverTypeArray(   PSRC, TYPE, COUNT,            PDST)             gmemCopyOverAt((PSRC),  gsizeof(TYPE) * (COUNT),   0,                       (PDST),  (Gi) 0)
#define gmemCopyOverTypeArrayAt( PSRC, TYPE, COUNT, INDEX_SRC, PDST, INDEX_DST)  gmemCopyOverAt((PSRC),  gsizeof(TYPE) * (COUNT),   gsizeof(TYPE) * (INDEX_SRC),  (PDST),  gsizeof(TYPE) * (INDEX_DST))

grlAPI Gb    gmemCopy(        Gp         * const p,    Gcount const byteCount, Gindex const byteIndexSrc,                  Gindex const byteIndexDst);
grlAPI Gb    gmemCopyOverAt(  Gp   const * const pSrc, Gcount const byteCount, Gindex const byteIndexSrc, Gp * const pDst, Gindex const byteIndexDst);
```

Copying part of a buffer onto another buffer.  Non-overlapping.  Use gmemCopyTypeArray() if copying into the same buffer.

```
#define gmemCreate(              TYPE_CHAR,  BYTECOUNT)                          gleakCreate((Gp *) gmemCreate_((TYPE_CHAR),    (BYTECOUNT)),                   (BYTECOUNT))
#define gmemCreateType(          TYPE)                                  (TYPE *) gleakCreate((Gp *) gmemCreate_(#TYPE,          gsizeof(TYPE)),           gsizeof(TYPE))
#define gmemCreateTypeArray(     TYPE,       COUNT)                     (TYPE *) gleakCreate((Gp *) gmemCreate_(#TYPE " ARRAY", gsizeof(TYPE) * (COUNT)), gsizeof(TYPE) * (COUNT))

grlAPI Gp   *gmemCreate_(     Char const * const type, Gcount const byteCount);
```

Create a new dynamic memory buffer.

CreateType, and CreateTypeArray are convenience functions for making a buffer of a size of a type or a buffer of a size of an array of type.  I use these to reduce tired programmer errors when writing out dynamic memory creation calls.

gleak tracking is only done in debug builds.

```
grlAPI void  gmemDestroy(     Gp        * const p);
```

Clean up dynamic memory created by using the gmemCreate*() functions above.  Do not use with memCreate, malloc, or calloc calls.

```
#define gmemIsEqual(             PA, PB, COUNT)                                  (memcmp((PA), (PB), (size_t) (COUNT))  == 0)
#define gmemIsEqualType(         PA, PB, TYPE)                                   (memcmp((PA), (PB), sizeof(TYPE))      == 0)
```

wrapper to memcmp functions.

```
grlAPI void  gmemFlushPools(  void);
```

Trim the memory pools.  See description for more information.

```
#define gmemSet(                 P,    BYTECOUNT, BYTEVALUE)                     memset((P), (BYTEVALUE), (size_t) (BYTECOUNT))

grlAPI void  gmemSetDefaced(  Gp        * const p,    Gcount const byteCount);
```

Set the values of the bytes in a buffer.  Defaced will set the values to things like 0xFEEDFACE, 0xDEADBEEF, etc.

# Gn (Natural and 0)

Natural numbers including 0, or in other words, unsigned integers.

## Type

```
typedef uint8_t            Gn1;
typedef uint16_t           Gn2;
typedef uint32_t           Gn4;
typedef uint64_t           Gn8;
```

Or in other words, unsigned integers.

As you can see I am using the stdint types.  I believe when I was starting out with GRL it was not really common yet and I was using standard C types.  I could be wrong.  But like any other library, I define my own types based on memory size.  Instead of bits I use byte count.

```
typedef Gn8                Gn;
```

Same as the above but the numberless versions represent the largest possible representation of the type for the platform.  Which may not be the most efficient form for the types.

```
typedef uintptr_t          Gnp;
```

Pointer sized versions of integer and natural.

```
typedef Gn4                Gnh;
```

Half size versions for the platform.

## Constant

```
#define GnMAX                 Gn8MAX

#define Gn1MAX                UINT8_MAX
#define Gn2MAX                UINT16_MAX
#define Gn4MAX                UINT32_MAX
#define Gn8MAX                UINT64_MAX

#define GnpMAX                UINTPTR_MAX
```

The limit constants for these types.  Not complete when it comes to Reals but I have not needed the other constants just yet.

# Goffset

A common integer/natural type used in a lot of places.  This will be the most efficient size for the platform and currently is an integer and not a natural.  I initially tried a natural but for some things, you need negative numbers.  For simplicity I kept it an integer.  If you end up in a situation where the efficient size integer is not enough range then you will have to do something else.

Why not just use the raw integer type?  Well, sometimes the type adds to the description of the variable/parameter.  In this case, if I have a function that expects an offset then it is clear what that variable intends to do.  You may not need to even look at the name of the variable.  So I use it as a form of making the code more clear.

## Type

```
typedef Gi4                Goffset;
```

## Constant

```
#define GoffsetMAX            Gi4MAX
#define GoffsetMIN            Gi4MIN
```

The limit constants for these types.

# Gosversion

## Constant

```
typedef enum
{
   gosversionNA,

   gosversionWIN32S,
   gosversionWIN95,
   gosversionWIN98,
   gosversionWINME,

   gosversionWINNT351,
   gosversionWINNT4,
   gosversionWIN2K,
   gosversionWINXP,
   gosversionWINXPSP1,
   gosversionWINXPSP2,
   gosversionWINXPSP3,
   gosversionWINVISTA,
   gosversionWINVISTASP1,
   gosversionWINVISTASP2,
   gosversionWIN7,
   gosversionWIN7SP1,
   gosversionWIN8,
   gosversionWIN8_1,
   gosversionWIN10,
   gosversionWINSERVER,

   gosversionMACCLASSIC,
   gosversionMACOSX
} Gosversion;
```

## Function

```
grlAPI Gosversion gosversionGet(void);
```

Get the os the program is running on.

# Gp (void)

Why not just use void?  I do use void in places like empty function paramerters, but seeing as I have basically redefined everything else, might as well redefine this one as well.  Usually never used alone, always used with '*' for a void pointer.

## Type

```
typedef void               Gp;
```

Why not just use void?  I do use void in places like empty function paramerters, but seeing as I have basically redefined everything else, might as well redefine this one as well.  Usually never used alone, always used with '*' for a void pointer.

# Gposition

A lot of functions need an anchor location for offsetting from.  Using this type to handle those situations.

## Type

```
typedef enum
{
   gpositionSTART   = SEEK_SET,
   gpositionEND     = SEEK_END,
   gpositionCURRENT = SEEK_CUR
} Gposition;
```

A lot of functions need an anchor location for offsetting from.  Using this type to handle those situations.

# Gprofile

Code to profile your program.  Unfortunately this code is not thread safe and you probably are better off using an actual profiler.

To use, you only need to set the compiler flag GPROFILE_IS_ON to 1 and recompile.  The program will print out a report on the function times when the program exits.  If the program crashes then no report is written out.

# Gr (Real)

Real numbers or floating point numbers.

## Type

```
typedef float              Gr4;
typedef double             Gr8;
```

Different names for standard types just to be complete.

```
typedef Gr8                Gr;
```

Same as the above but the numberless versions represent the largest possible representation of the type for the platform.  Which may not be the most efficient form for the types.  I'm ignoring long double since it only allows for higher exponents and not higher precision.

```
typedef Gr8                Grp;
```

Pointer sized versions of integer and natural.

## Constant

```
#define GrMAX                 Gr8MAX

#define GrMIN                 Gr8MIN

#define Gr4MAX                FLT_MAX
#define Gr4MIN                FLT_MIN
#define Gr8MAX                DBL_MAX
#define Gr8MIN                DBL_MIN
```

The limit constants for these types.  Not complete when it comes to Reals but I have not needed the other constants just yet.

# Grandom

Random number generator.  This is not my code but found on the internet.  Not cryptographically random.

```
   A C-program for MT19937-64 (2004/9/29 version).
   Coded by Takuji Nishimura and Makoto Matsumoto.

   This is a 64-bit version of Mersenne Twister pseudorandom number
   generator.

   Before using, initialize the state by using init_genrand64(seed)
   or init_by_array64(init_key, key_length).

   Copyright (C) 2004, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS Gn4ERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   References:
   T. Nishimura, ``Tables of 64-bit Mersenne Twisters''
     ACM Transactions on Modeling and
     Computer Simulation 10. (2000) 348--357.
   M. Matsumoto and T. Nishimura,
     ``Mersenne Twister: a 623-dimensionally equidistributed
       uniform pseudorandom number generator''
     ACM Transactions on Modeling and
     Computer Simulation 8. (Jan. 1998) 3--30.

   Any feedback is very welcome.
   http://www.math.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove spaces)
```

## Type

```
typedef struct
{
   Gb  isInit;
   Gn8 mt[NN];
   Gn4 mti;
} Grandom;
```

## Function

```
void grandomCreateContent(Grandom * const r, Gn8 const seed);
```

Initializes a Grandom structure with a seed.

```
void grandomCreateContentByArray(Grandom * const r, Gcount const keyCount, Gn8 const * const keyList);
```

Initializes a Grandom structure with an array of values.

```
Gn grandomGetN(Grandom * const r);
```

Get a natural random number between [0, GnMAX].

```
Gi grandomGetI(Grandom * const r);
```

Get an integer random number between [0, GiMAX].

```
Gr grandomGetR(Grandom * const r);
```

Get a real random number between [0, 1].

```
Gr grandomGetROpen1(Grandom * const r);
```

Get a real random number between [0, 1).

```
Gr grandomGetROpen(Grandom * const r);
```

Get a real random number between (0, 1).

# Gsize

A common integer/natural type used in a lot of places.  This will be the most efficient size for the platform and currently is an integer and not a natural.  I initially tried a natural but for some things, you need negative numbers.  For simplicity I kept it an integer.  If you end up in a situation where the efficient size integer is not enough range then you will have to do something else.

Why not just use the raw integer type?  Well, sometimes the type adds to the description of the variable/parameter.  In this case, if I have a function that expects an offset then it is clear what that variable intends to do.  You may not need to even look at the name of the variable.  So I use it as a form of making the code more clear.

## Type

```
typedef Gi4                Gsize;
```

## Constant

```
#define GsizeMAX              Gi4MAX
```

The limit constants for these types.

## Function

```
#define gsizeIsGood(S)     (0 <= (S))
```

IsGood check for a gsize.

# Gsize

## Function

```
grlAPI Gp *gswap2(Gp *value);
grlAPI Gp *gswap4(Gp *value);
grlAPI Gp *gswap8(Gp *value);
```

Byte swapping from Big Endian to Little Endian or vice versa for 2, 4, or 8 Byte values.

# Gtime

## Type

```
#define Gtime time_t
```

Using built in 64 bit time routines.

## Function

```
grlAPI Gtime gtimeGet(         void);
```

Get the current time for the computer.

```
grlAPI Gb    gtimeGetTimeLocal(Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);
```

Get the local time values from the time structure.

```
grlAPI Gb    gtimeGetTime(     Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);
```

Get the GMT time value from the time structure.

# Gtrace

Code for recording the program execution to a file.  This code is thread safe.

## Constant

```
typedef enum
{
	gtraceLevelNONE       = 0x00000000,
	gtraceLevelALL        = 0xffffffffU,
	gtraceLevelENTER_EXIT = 0x10000000,
	gtraceLevelNOTICE     = 0x20000000,
	gtraceLevelWARNING    = 0x40000000,
	gtraceLevelERROR      = 0x80000000U
} GtraceLevel;
```

The level of verbosity you want to record to the trace file.  The more you write out the slower your program will perform.

## Function

```
grlAPI Gb      gtraceEnter(     void);
grlAPI void    gtraceExit(      void);
```

Used by genter and greturn macroes.

```
grlAPI void    gtraceMessage(   GtraceLevel level, char *message);
```

Sends a trace message to the trace file.

```
grlAPI Gb      gtraceStart(     GtraceLevel level, char *filename);
```

Should be called at the start of the program.  You provide the file to write to and the level of messaging you want to record.

```
grlAPI void    gtraceStop(      void);
```

Should be called at the end of the program execution.

# Gv, GvType

Gv is more involved than Gvp.  I was using this as variable storage in a scripting language that I wrote up.  The type is to identify what actual value is stored in the generic value structure.

## Type

```
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
```

Gv is more involved than Gvp.  I was using this as variable storage in a scripting language that I wrote up.  The type is to identify what actual value is stored in the generic value structure.

## Function

```
grlAPI Gcompare    gpCompare(       Gp const * const valueA, Gp const * const valueB);
grlAPI Gcompare    gvCompareI(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareN(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareP(      Gv const * const valueA, Gv const * const valueB);
grlAPI Gcompare    gvCompareR(      Gv const * const valueA, Gv const * const valueB);
```

Compare two Gv structures.

```
grlAPI Gv         *gvCreate(        void);
grlAPI Gb          gvCreateContent( Gv       * const v);
```

Create a dynamic Gv structure or intialize a Gv structure.

```
grlAPI void        gvDestroy(       Gv       * const v);
grlAPI void        gvDestroyContent(Gv       * const v);
```

Destroy a dynamic Gv structure or deinitialize a Gv structure.

```
grlAPI Gv          gvFromI(         Gip  const value);
grlAPI Gv          gvFromN(         Gnp  const value);
grlAPI Gv          gvFromP(         Gp * const value);
grlAPI Gv          gvFromR(         Grp  const value);
grlAPI Gv          gvFromS(         Gs * const value);
```

Get a Gv structure from a specific value type.

```
grlAPI Gip         gvGetI(          Gv const * const v);
grlAPI Gnp         gvGetN(          Gv const * const v);
grlAPI Gp         *gvGetP(          Gv const * const v);
grlAPI Grp         gvGetR(          Gv const * const v);
grlAPI Gs         *gvGetS(          Gv const * const v);
```

Get a specific value from a Gv structure.

```
grlAPI GhashN      gvHash(          Gv const * const value);
grlAPI GhashN      gvHashS(         Gv const * const value);
```

Hash a Gv structure.

```
grlAPI Gb          gvSetI(          Gv       * const v, Gip  const value);
grlAPI Gb          gvSetN(          Gv       * const v, Gnp  const value);
grlAPI Gb          gvSetP(          Gv       * const v, Gp * const value);
grlAPI Gb          gvSetR(          Gv       * const v, Grp  const value);
grlAPI Gb          gvSetS(          Gv       * const v, Gs * const value);
```

Set the value of a Gv structure.

# Gvp

Generic value structure.  This is assuming, when you use this structure you know what is stored inside.

## Type

```
typedef union
{
	Gip             i;
	Gnp             n;
	Gp             *p;
	Grp             r;
} Gvp;
```

Generic value structure.  This is assuming, when you use this structure you know what is stored inside.

# G*Func

Various function types for callbacks.

## Type

```
typedef Gcompare   (*GrlCompareFunc)(        Gp const * const valueA, Gp const * const valueB);
```

Comparing to items together.

```
typedef void       (*GrlDestroyFunc)(        Gp       * const value);
```

Clean up dynamic memory.

```
typedef void       (*GrlForEachFunc)(        Gp       * const value);
```

Used in a ForEach function call to perform an action on each item.

```
typedef void       (*GrlForEachKeyFunc)(     Gkey const * const key,    Gp       * const value);
```

Used on a ForEach function with a key value container.

```
typedef Gp        *(*GrlForEachProcessFunc)( Gp       * const value);
```

-

```
typedef void       (*GrlForEachAltFunc)(     Gp       * const value, GrlForEachFunc func);
```

-

```
typedef Gp const  *(*GrlGetFunc)(            Gp const * const mem, Gi4 const index);
```

A form of array/buffer access function.

```
typedef GhashN     (*GrlHashFunc)(           Gp const * const value);
```

Obtain a hash value of something.

```
typedef void       (*GrlSwapFunc)(           Gp       * const mem, Gi4 const indexA, Gi4 const indexB);
```

Swap two values in a form of array/buffer.
