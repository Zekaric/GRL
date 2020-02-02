/******************************************************************************
file:       gleak
author:     Robbert de Groot
copyright:  2000-2011, Robbert de Groot

description:
Handles leak tracking.  Not necessarily memory leaks but for the moment that is
all it is being used for.  

Usage:
Record your creation.

   (TYPE *) gleakCreate((Gp *) pointer, size);

TYPE here is the type of the pointer.  Usually gleakCreate() is inline with 
another create function or found in a #define.

This creates a leak record, which holds the source file and line where that
creation happened.  This does not mean the pointer is currently a leak but it 
is a potential leak.

Update your creation.  Sometimes the creation is nested deep down in some call
stack.  What you really want to know is where at the highest level did the leak
occue.  To do this, just call gleakCreate() again at the higher level.

Record your clean up.

   gleakDestroy((Gp *) pointer);

This removes the leak record.

Display the results.  The results will always be displayed when the program 
exists.  They are displayed in the output window in Visual Studio and are 
formatted in a way you can click on them and you will be brought to the 
location that was recorded.

Leak tracking is only done in debug.  Release builds will not include leak
tracking and so will not be negatively affected by the added performance hit
with leak tracking.

Leak tracking is thread safe.
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

#if !defined(GLEAKH)
#define      GLEAKH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
constant:
******************************************************************************/
//typedef enum
//{
//   gleakErrorNONE,
//   gleakErrorPOINTER_NOT_FOUND
//} GleakError;

/******************************************************************************
Function:
******************************************************************************/
#if defined(_DEBUG)

/*lint -save -e960 -e961 -e9026 */
#define gleakCreate(P,S) gleakCreate_((P), (S), __FILE__, __LINE__)
#define gleakDestroy(P)  gleakDestroy_((P))
/*lint -restore */

grlAPI Gp  *gleakCreate_(   Gp * const p, Gsize const size, Char const * const file, Gindex const line);
grlAPI Gp  *gleakDestroy_(  Gp *p);

grlAPI Gb   gleakLockEnter( void);
grlAPI Gb   gleakLockExit(  void);

// gleakStart and Stop are called by grlStart and Stop
       Gb   gleakStart(     void);
       void gleakStop(      void);

#else

#define gleakCreate(P,S)         P
#define gleakDestroy(P)          P

#define gleakLockEnter()
#define gleakLockExit()

        Gb   gleakStart(   void);
        void gleakStop(    void);

#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
