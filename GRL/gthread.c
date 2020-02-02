/******************************************************************************
file:       gthread
author:     Robbert de Groot
copyright:  2009-2012, Robbert de Groot

description:
Threading routines.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gthreadCreate
******************************************************************************/
grlAPI Gthread *gthreadCreate(GthreadFunction const function, Gp * const data)
{
   Gthread *thread;

   returnIf(!function, NULL);

   thread = (Gthread *) calloc((size_t) 1, gsizeof(Gthread)); //lint !e586
   if (!thread)
   {
      //gerrorSet(
      //   gerrorLevelERROR,
      //   gthreadMODULE,
      //   gthreadErrorCREATE_MEMORY_FAIL,
      //   "Memory create fail.");
      return NULL;
   }

#if grlWINDOWS == 1
   thread->handle = (HANDLE) _beginthreadex(
      NULL,
      0,
      function,
      data,
      0,
      &thread->id); //lint !e923
   if (thread->handle == (HANDLE) (Gip) -1) //lint !e923
   {
      free(thread); //lint !e586
      //gerrorSet(
      //   gerrorLevelERROR,
      //   gthreadMODULE,
      //   gthreadErrorCREATE_THREAD_FAIL,
      //   "Thread create fail.");
      return NULL;
   }
#else
#endif

   return thread;
}

/******************************************************************************
func: gthreadDestroy
******************************************************************************/
grlAPI Gb gthreadDestroy(Gthread * const thread)
{
   returnIf(!gthreadIsGood(thread), gbTRUE);

#if grlWINDOWS == 1
   CloseHandle(thread->handle); //lint !e534
#else
#endif

   free(thread); //lint !e586

   return gbTRUE;
}

/******************************************************************************
func: gthreadGetReturnValue
******************************************************************************/
grlAPI Gb gthreadGetReturnValue(const Gthread * const thread, Gi4 * const value)
{
   returnIf(!gthreadIsGood(thread), gbFALSE);

   {
#if grlWINDOWS == 1
   DWORD result;

   returnIf(!GetExitCodeThread(thread->handle, &result), gbFALSE);

   *value = result;
#else
#endif
   }

   return gbTRUE;
}

/******************************************************************************
func: gthreadIsGood
******************************************************************************/
grlAPI Gb gthreadIsGood(const Gthread * const thread)
{
   returnIf(!thread, gbFALSE);

#if grlWINDOWS == 1
   return (Gb) (thread->handle != 0); //lint !e930
#else
   return gbTRUE;
#endif
}

/******************************************************************************
func: gthreadWait
******************************************************************************/
grlAPI Gb gthreadWait(const Gcount threadCount, const Gthread * const * const threadList)
{
   returnIf(!threadCount, gbFALSE);

   {
#if grlWINDOWS == 1
   Gi4     result,
           index;
   HANDLE *hlist;

   hlist = (HANDLE *) calloc((size_t) 1, (size_t) (threadCount * gsizeof(HANDLE))); //lint !e586
   returnIf(!hlist, gbFALSE);

   forCount(index, threadCount)
   {
      hlist[index] = threadList[index]->handle;
   }

   result = WaitForMultipleObjects((DWORD) threadCount, hlist, gbTRUE, INFINITE);
   if      (result == WAIT_FAILED)
   {
      debugHalt("WaitForMultipleObjects failed");
   }
   else if (result >= WAIT_ABANDONED_0) //lint !e835
   {
      debugHalt("WaitForMultipleObjects abandoned");
   }

   free(hlist); //lint !e586
#else
#endif
   }

   return gbTRUE;
}

/******************************************************************************
func: gthreadCurrentExit

Called inside the thread when done.
******************************************************************************/
grlAPI Gb gthreadCurrentExit(const Gn4 exitValue)
{
#if grlWINDOWS == 1
   _endthreadex(exitValue);
#else
#endif
   return gbTRUE;
}

/******************************************************************************
func: gthreadCurrentPause

Give up control to let other threads process.
******************************************************************************/
grlAPI void gthreadCurrentPause(void)
{
#if grlWINDOWS == 1
   if (!SwitchToThread())
   {
      debugHalt("No other threads to switch to.");
   }
#else
#endif
   return;
}
