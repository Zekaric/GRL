/**************************************************************************************************
file:       gthread
author:     Robbert de Groot
copyright:  2009, Robbert de Groot

description:
Threading routines.
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
constant:
**************************************************************************************************/
typedef enum
{
   gthreadPriorityLOW      = SDL_THREAD_PRIORITY_LOW,
   gthreadPriorityNORMAL   = SDL_THREAD_PRIORITY_NORMAL,
   gthreadPriorityHIGH     = SDL_THREAD_PRIORITY_HIGH,
   gthreadPriorityCRITICAL = SDL_THREAD_PRIORITY_TIME_CRITICAL
} GthreadPriority;

typedef enum
{
   gthreadStateNONE        = SDL_THREAD_UNKNOWN,
   gthreadStateNORMAL      = SDL_THREAD_ALIVE,
   gthreadStateDETACHED    = SDL_THREAD_DETACHED,
   gthreadStateCOMPLETE    = SDL_THREAD_COMPLETE
} GthreadState;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef SDL_Thread         Gthread;
typedef SDL_ThreadID       GthreadId;

typedef SDL_ThreadFunction GthreadFunc; // int (*)(void *data)

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gthreadCloc(             FUNC, NAME, DATA)    (Gthread *)    SDL_CreateThread(             FUNC, NAME, DATA)

#define gthreadDetach(           THREAD)                             SDL_DetachThread(             THREAD)

#define gthreadGetCurrId(        )                    (GthreadId)    SDL_GetCurrentThreadID(       )
#define gthreadGetId(            THREAD)              (GthreadId)    SDL_GetThreadID(              THREAD)
#define gthreadGetName(          THREAD)              (Char const *) SDL_GetThreadName(            THREAD)
#define gthreadGetState(         THREAD)              (GthreadState) SDL_GetThreadState(           THREAD)

#define gthreadSetCurrPriority(  PRIORITY)            (Gb)           SDL_SetCurrentThreadPriority( PRIORITY)

#define gthreadWait(             THREAD, STATUS)                     SDL_WaitThread(               THREAD, STATUS)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
