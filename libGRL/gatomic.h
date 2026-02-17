/**************************************************************************************************
file:       gatomic
author:     Robbert de Groot
copyright:  2026, Robbert de Groot

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

Copyright (c) 2026, Robbert de Groot

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
typedef SDL_AtomicInt   Gatomici;
typedef SDL_AtomicU32   Gatomicn;
typedef void            Gatomicp;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gatomiciAdd(     PATOMIC, VALUE)      (Gi4) SDL_AddAtomicInt(           PATOMIC, VALUE)
#define gatomiciAdd1(    PATOMIC)             (Gi4) SDL_AddAtomicInt(           PATOMIC, 1)
#define gatomiciCompSwap(PATOMIC, OLD, NEW)   (Gb)  SDL_CompareAndSwapAtomicInt(PATOMIC, OLD, NEW)
#define gatomiciGet(     PATOMIC)             (Gi4) SDL_GetAtomicInt(           PATOMIC)
#define gatomiciSet(     PATOMIC, VALUE)      (Gi4) SDL_SetAtomicInt(           PATOMIC, VALUE)
#define gatomiciSub(     PATOMIC, VALUE)      (Gi4) SDL_AddAtomicInt(           PATOMIC, -(VALUE))
#define gatomiciSub1(    PATOMIC)             (Gi4) SDL_AddAtomicInt(           PATOMIC, -1)

#define gatomicnAdd(     PATOMIC, VALUE)      (Gi4) SDL_AddAtomicU32(           PATOMIC, VALUE)
#define gatomicnAdd1(    PATOMIC)             (Gi4) SDL_AddAtomicU32(           PATOMIC, 1)
#define gatomicnCompSwap(PATOMIC, OLD, NEW)   (Gb)  SDL_CompareAndSwapAtomicU32(PATOMIC, OLD, NEW)
#define gatomicnGet(     PATOMIC)             (Gi4) SDL_GetAtomicU32(           PATOMIC)
#define gatomicnSet(     PATOMIC, VALUE)      (Gi4) SDL_SetAtomicU32(           PATOMIC, VALUE)
#define gatomicnSub(     PATOMIC, VALUE)      (Gi4) SDL_AddAtomicU32(           PATOMIC, -(VALUE))
#define gatomicnSub1(    PATOMIC)             (Gi4) SDL_AddAtomicU32(           PATOMIC, -1)

#define gatomicpCompSwap(PATOMIC, OLD, NEW)   (Gb)  SDL_CompareAndSwapAtomicPointer(PATOMIC, OLD, NEW)
#define gatomicpGet(     PATOMIC)             (Gi4) SDL_GetAtomicPointer(           PATOMIC)
#define gatomicpSet(     PATOMIC, VALUE)      (Gi4) SDL_SetAtomicPointer(           PATOMIC, VALUE)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
