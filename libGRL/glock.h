/**************************************************************************************************
file:       glock
author:     Robbert de Groot
copyright:  2009, Robbert de Groot

description:
critical section lock routines.

Glock     locks use mutex operations.  They should not cause thread starvation.
GlockRead locks use mutex operations.  They are specific to the situation where there are more
   readers of the data and very few writes happen.  Writes will wait till all readers are locked
   out.
GlockSpin locks use atomic operations.  They can cause thread starvation.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2009, Robbert de Groot

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
type:
**************************************************************************************************/
typedef SDL_Mutex       Glock;
typedef SDL_RWLock      GlockRead;
typedef SDL_SpinLock    GlockSpin;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define glockSpinEnterTry(    LOCK)       (Gb)           SDL_TryLockSpinLock(          LOCK)
#define glockSpinEnter(       LOCK)                      SDL_LockSpinLock(             LOCK)
#define glockSpinExit(        LOCK)                      SDL_UnlockSpinLock(           LOCK)


#define glockCloc(            )           (Glock *)      SDL_CreateMutex(              )

#define glockDloc(            LOCK)                      SDL_DestroyMutex(             LOCK)

#define glockEnterTry(        LOCK)       (Gb)           SDL_TryLockMutex(             LOCK)
#define glockEnter(           LOCK)                      SDL_LockMutex(                LOCK)
#define glockExit(            LOCK)                      SDL_UnlockMutex(              LOCK)


#define glockReadCloc(        )           (GlockRead *)  SDL_CreateRWLock(             )

#define glockReadDloc(        LOCK)                      SDL_DestroyRWLock(            LOCK)

#define glockReadEntryTryRead(LOCK)       (Gb)           SDL_TryLockRWLockForReading(  LOCK)
#define glockReadEntryTry(    LOCK)       (Gb)           SDL_TryLockRWLockForWriting(  LOCK)
#define glockReadEntryRead(   LOCK)                      SDL_LockRWLockForReading(     LOCK)
#define glockReadEntry(       LOCK)                      SDL_LockRWLockForWriting(     LOCK)
#define glockReadExit(        LOCK)                      SDL_UnlockRWLock(             LOCK)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
