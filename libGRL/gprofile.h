/**************************************************************************************************

file:       gprofile
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
These are simple profile functions for profiling functions in a GRL program.  They are exclusivly
called in genter and greturn* statements so you will need to use those in functions you want
profiled.

The code only records how much total time a function uses during a run.  This includes the time
used in sub functions.  The code is not thread safe.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

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
GPROFILE_IS_ON defined in grlconfig.h
**************************************************************************************************/
#if GPROFILE_IS_ON == 1

/**************************************************************************************************
Functions
**************************************************************************************************/
grlAPI void  gprofileCheckStack( Gindex index);

grlAPI Gtime gprofileEnter(      Gindex * const index, Char const * const file, Char const * const function);
grlAPI void  gprofileExit(       Gindex   const index, Gtime const startTime);

grlAPI void  gprofileReport(     void);

#else

#define gprofileCheckStack(I)

#define gprofileEnter(I,FILE,FUNC)  0
#define gprofileExit(I,TIME)

#define gprofileReport()

#endif

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
