/**************************************************************************************************
file:       gleak
author:     Robbert de Groot
copyright:  2000-2011, Robbert de Groot

description:
Memory or resource leak detection.

Not using genter macro since this is low level.

Not using gmem* functions as we would end up with a chicken and egg scenario.
**************************************************************************************************/

/**************************************************************************************************
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
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

#if defined(_DEBUG)

#include <stdio.h> //lint !e829

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
// Are we printing to a file as well?
#define gleakFILE_OUTPUT   0

// If you are finding you are still hitting a performance hurdle because of 
// gleak code then maybe increase this number.
#define gleakHASH_COUNT    16381

/**************************************************************************************************
local:
type:
**************************************************************************************************/
typedef struct Leak Leak;
struct Leak
{
   GTYPE_VAR

   // Leak pointer
   Gp          *p;

   // Leak information
   // Creation index.
   Gn           index;
   // Size of the buffer.
   Gsize        size;
   // Location in source.
   Char  const *file;
   Gindex       line;

   // Next leak report.
   Leak        *next;
};

/**************************************************************************************************
variable:
**************************************************************************************************/
// Next leak creation number.
static Gn     _index    = 0;

// The leak hash table.
static Leak **_leak     = NULL;  //lint !e956

// The thread lock.
static Glock  _lock;             //lint !e956

/**************************************************************************************************
function:
**************************************************************************************************/
static Leak *_Get(      Gp const * const p);

static Gn4   _Hash(     Gp const * const p);

static Gb    _Remove(   Gp const * const p);

static void  _Set(      Leak * const l);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gleakCloc

Create a leak item
**************************************************************************************************/
grlAPI Gp *gleakCloc_(Gp * const p, Gsize const size, Char const * const file, Gindex const line)
{
   Leak *l;

   returnValIf(!p, p);

   // Thread safety.
   glockEnter(&_lock);

   // See if there is already a leak report for this pointer.
   l = _Get(p);

   // No report, must be new.
   if (!l)
   {
      // Create a new leak structure.
      l = (Leak *) calloc((size_t) 1, gsizeof(Leak)); //lint !e586
      debugHaltIf(  !l, "No more memory!");
      returnValIf(!l, p);

      // Fill in the structure.
      GTYPE_SET(l, "Gleak Leak");
      l->p     = p;
      l->size  = size;
      l->index = _index++;

      // Add it to the hash table.
      _Set(l);
   }

   // Update the leak report with the new source location.
   l->file = file;
   l->line = line;

   glockExit(&_lock);

   return p;
}

/**************************************************************************************************
func: gleakDloc

Destroy a leak item.
**************************************************************************************************/
grlAPI Gp *gleakDloc_(Gp * const p)
{
   returnValIf(!p, p);

   // Thread safety.
   glockEnter(&_lock);

   // Find and remove the leak report for this pointer.
   if (!_Remove(p))
   {
      // If we are here then we may have the problem of a gleakCreate was not
      // used OR, we are trying to double destroy.  
      debugHalt("Pointer not found.");
   }

   glockExit(&_lock);

   return p;
}

/**************************************************************************************************
func: gleakLockEnter

Sometimes is may be faster to do the thread saftey higher up the food chain
just so that the locking in the above functions need not really at that exact
point.
**************************************************************************************************/
grlAPI Gb gleakLockEnter(void)
{
   glockEnter(&_lock);

   return gbTRUE;
}

/**************************************************************************************************
func: gleakLockExit
**************************************************************************************************/
grlAPI Gb gleakLockExit(void)
{
   glockExit(&_lock);

   return gbTRUE;
}

/**************************************************************************************************
func: gleakStart

Start the leak functions.
**************************************************************************************************/
Gb gleakStart(void)
{
   glockClocContent(&_lock);

   _leak = (Leak **) calloc((size_t) 1, gsizeof(Leak *) * gleakHASH_COUNT); //lint !e586

   return gbTRUE;
}

/**************************************************************************************************
func: gleakStop

clean up;
**************************************************************************************************/
void gleakStop(void)
{
   Gn4           a;
   Gp           *p;
   Leak         *l,
                *ltemp;
   wchar_t       debug[1024];
#if gleakFILE_OUTPUT == 1
   FILE         *f;

   glockEnter(&_lock);

   f = fopen("c:\\grl_leak.txt", "a");
   fprintf(f, "********************************************************************************\n");
#else
#endif

#if defined(grlWINDOWS)
   OutputDebugString(L"*** Leak Report ***\n");
#endif

   // CSV output
   forCount(a, gleakHASH_COUNT)
   {
      l = _leak[a];
      loop
      {
         breakIf(!l);
         if (!l->p)
         {
            ltemp = l->next;
            free(l); //lint !e586
            l = ltemp;
         }

#if gleakFILE_OUTPUT == 1
         if (f)
         {
            fprintf(f, "LEAK: size %d\n", l->size);
         }
#endif

         swprintf(
            debug,
            (size_t) 1024,
            L"%S\t%d\t%I64u\t%d\n", //lint !e816
            l->file,
            l->line,
            l->index,
            l->size); //lint !e534
#if defined(grlWINDOWS)
         OutputDebugString(debug);
#endif

#if gleakFILE_OUTPUT == 1
         if (f)
         {
            fprintf(f, "   %10x LINE: %10d  FILE: ", (unsigned int) (p), l->line);
            fprintf(f, l->file);
            fprintf(f, "\n");
         }
#endif

         // Next leak item
         l = l->next;
      }
   }

   OutputDebugString(L"*** =========== ***\n");

   // Debug window output and Clean up.
   forCount(a, gleakHASH_COUNT)
   {
      l = _leak[a];
      loop
      {
         breakIf(!l);
         if (!l->p)
         {
            ltemp = l->next;
            free(l); //lint !e586
            l = ltemp;
         }

#if gleakFILE_OUTPUT == 1
         if (f)
         {
            fprintf(f, "LEAK: size %d\n", l->size);
         }
#endif

         swprintf(
            debug,
            (size_t) 1024,
            L"%S(%d) : alloc: index %7I64u   size %d\n", //lint !e816
            l->file,
            l->line,
            l->index,
            l->size); //lint !e534
#if defined(grlWINDOWS)
         OutputDebugString(debug);
#endif

#if gleakFILE_OUTPUT == 1
         if (f)
         {
            fprintf(f, "   %10x LINE: %10d  FILE: ", (unsigned int) (p), l->line);
            fprintf(f, l->file);
            fprintf(f, "\n");
         }
#endif

         // Next leak item
         p = l;
         l = l->next;
         free(p); //lint !e586
      }
   }

   free(_leak); //lint !e586
   _leak = NULL;

#if defined(grlWINDOWS)
   OutputDebugString(L"*******************\n");
#endif

#if gleakFILE_OUTPUT == 1
   fclose(f);
#endif

   glockExit(&_lock);

   return;
}

/**************************************************************************************************
local:
**************************************************************************************************/
/**************************************************************************************************
func: _Get
**************************************************************************************************/
static Leak *_Get(Gp const * const p)
{
   Leak  *l;
   GhashN index;

   index = _Hash(p) % gleakHASH_COUNT;
   l     = _leak[index];

   loop
   {
      breakIf(!l);

      returnValIf(l->p == p, l);

      l = l->next;
   }

   return NULL;
}

/**************************************************************************************************
func: _Hash
**************************************************************************************************/
static Gn4 _Hash(Gp const * const p)
{
   // Assuming 4 byte aligned data.
   return (Gn4) (((Gnp) p) >> 2); //lint !e923
}

/**************************************************************************************************
func: _Remove
**************************************************************************************************/
static Gb _Remove(Gp const * const p)
{
   Leak  *l,
         *prevl;
   GhashN index;

   prevl = NULL;

   index = _Hash(p) % gleakHASH_COUNT;
   l     = _leak[index];

   loop
   {
      breakIf(!l);

      if (l->p == p)
      {
         if (prevl)
         {
            prevl->next = l->next;
         }
         else
         {
            _leak[index] = l->next;
         }

         free(l); //lint !e586
         return gbTRUE;
      }

      prevl = l;
      l     = l->next;
   }

   return gbFALSE;
}

/**************************************************************************************************
func: _Set
**************************************************************************************************/
static void _Set(Leak * const l)
{
   Gi4 index;

   index        = (Gi4) (_Hash(l->p) % gleakHASH_COUNT);
   l->next      = _leak[index];
   _leak[index] = l;

   return;
}

#else

/**************************************************************************************************
include:
**************************************************************************************************/
#include "grl.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gleakStart
**************************************************************************************************/
Gb gleakStart(void)
{
   return gbTRUE;
}

/**************************************************************************************************
func: gleakStop
**************************************************************************************************/
void gleakStop(void)
{
   return;
}

#endif
