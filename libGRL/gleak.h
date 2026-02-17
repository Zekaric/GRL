/**************************************************************************************************
file:       gleak
author:     Robbert de Groot
copyright:  2000, Robbert de Groot

description:
Handles leak tracking.  Not necessarily memory leaks but for the moment that is
all it is being used for.

Usage:
Record your creation.

   (TYPE *) gleakCloc((Gp *) pointer, size);

TYPE here is the type of the pointer.  Usually gleakCloc() is inline with
another create function or found in a #define.

This creates a leak record, which holds the source file and line where that
creation happened.  This does not mean the pointer is currently a leak but it
is a potential leak.

Update your creation.  Sometimes the creation is nested deep down in some call
stack.  What you really want to know is where at the highest level did the leak
occue.  To do this, just call gleakCloc() again at the higher level.

Record your clean up.

   gleakDloc((Gp *) pointer);

This removes the leak record.

Display the results.  The results will always be displayed when the program
exists.  They are displayed in the output window in Visual Studio and are
formatted in a way you can click on them and you will be brought to the
location that was recorded.

Leak tracking is only done in debug.  Release builds will not include leak
tracking and so will not be negatively affected by the added performance hit
with leak tracking.

Leak tracking is thread safe.
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

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
Function:
**************************************************************************************************/
#if defined(_DEBUG)

#define gleakClocType(P,TYPE)    (TYPE *) gleakCloc_((void *) (P), gsizeof(TYPE), (Char *) __FILE__, __LINE__)
#define gleakCloc(    P,SIZE)             gleakCloc_((void *) (P), (SIZE),        (Char *) __FILE__, __LINE__)
#define gleakDloc(    P)                  gleakDloc_((void *) (P))

grlAPI Gp  *gleakCloc_(     Gp * const p, Gsize const size, Char const * const file, Gindex const line);
grlAPI Gp  *gleakDloc_(     Gp *p);

grlAPI Gb   gleakLockEnter( void);
grlAPI Gb   gleakLockExit(  void);

grlAPI void gleakReport(    void);

// gleakStart and Stop are called by grlStart and Stop
       Gb   gleakStart(     void);
       void gleakStop(      void);

#else

#define gleakClocTYPE(P,TYPE)    P
#define gleakCloc(    P,SIZE)    P
#define gleakDloc(    P)         P

#define gleakLockEnter()
#define gleakLockExit()

#define gleakReport()

        Gb   gleakStart(   void);
        void gleakStop(    void);

#endif

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
