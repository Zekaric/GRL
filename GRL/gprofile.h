/******************************************************************************

file:       gprofile
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
These are simple profile functions for profiling functions in a GRL program.
They are exclusivly called in genter and greturn* statements so you will
need to use those in functions you want profiled.  

The code only records how much total time a function uses during a run.  This
includes the time used in sub functions.

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

#if !defined(GPROFILEH)
#define      GPROFILEH

/******************************************************************************
GPROFILE_IS_ON defined in grlconfig.h
******************************************************************************/
#if GPROFILE_IS_ON == 1

/******************************************************************************
Functions
******************************************************************************/
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

#endif
