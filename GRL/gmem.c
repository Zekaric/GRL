/******************************************************************************
file:         Gmem
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
Routines for a memory handling.

How is memory handled?

We have memory pooling that does not free smaller blocks until told to flush
these blocks from memory.  The idea is to reduce the amount of time for 
allocation as malloc/calloc is not called all the time.  This improves program
performance but may lead to more memory fragmentation.

If you provide a 'small' size, I am actually allocating a buffer of a size that
falls in to a size bin.

There are 256 small size bins.  Sarting from a size of 8 and each bin increasing
in size by 4 bytes.  So 8, 12, 16, ... 1032. 

Anything larger is too large to pool.

Not using genter as these functions are too low level.
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

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
local:
constant:
******************************************************************************/
//lint -save -e960 -e961 -e9026 -e9022
#define POOL_COUNT               256
#define POOL_INC                 4
#define POOL_MIN                 8
#define POOL_UNBINNED_INDEX      GindexMAX

// Calculation to find the bin index
#define POOL_BIN_FROM_SIZE(SIZE) ((SIZE <= POOL_MIN) ? 0 : (((SIZE) - 1) / POOL_INC) - 1)
#define POOL_BIN_SIZE(POOL_BIN)  (((POOL_BIN) + 2) * POOL_INC)
//lint -restore

/******************************************************************************
type:
******************************************************************************/
typedef struct FreeList FreeList;

typedef struct
{
   Gi4             freeCount;
   FreeList       *freeList;
   Gi4             poolCount;
} Pool;

// free list structure;
struct FreeList
{
   FreeList       *next;
};

typedef struct
{
   GTYPE_VAR

   Gi4             size,
                   poolBin;
} Mem;

/******************************************************************************
variable:
******************************************************************************/
static Glock _lock;              //lint !e956
static Pool  _pool[POOL_COUNT];  //lint !e956

/******************************************************************************
function:
******************************************************************************/
static Gp   *_PoolCreate(  Char const * const type, Gi4 const size);

static void  _PoolDestroy( Gp * const mem);

static void  _PoolFlush(   void);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gmemClearAt
******************************************************************************/
grlAPI void gmemClearAt(Gp * const p, Gcount const byteCount, Gindex const byteIndex)
{
   Gn1 *pn;

   if (!p             ||
       byteCount <= 0 ||
       byteIndex <  0)
   {
      return;
   }

   pn = (Gn1 *) p;
   pn = &(pn[byteIndex]);

   // Clean up the pointer.
   memset(pn, 0, (size_t) byteCount);

   return;
}

/******************************************************************************
func: gmemCopy
******************************************************************************/
grlAPI Gb gmemCopy(Gp * const p, Gcount const byteCount, Gindex const byteIndexSrc, 
   Gindex const byteIndexDst)
{
   Gn1 *pn;

   // Nothing to copy.
   returnIf(byteCount == 0, gbTRUE);

   returnIf(
         !p                ||
         byteIndexSrc <  0 ||
         byteIndexDst <  0,
      gbFALSE);

   pn = (Gn1 *) p;

   memmove(&(pn[byteIndexDst]), &(pn[byteIndexSrc]), (size_t) byteCount);

   return gbTRUE;
}

/******************************************************************************
func: gmemCopyOverAt
******************************************************************************/
grlAPI Gb gmemCopyOverAt(Gp const * const pSrc, Gcount const byteCount, 
   Gindex const byteIndexSrc, Gp * const pDst, Gindex const byteIndexDst)
{
   Gn1 *pdn,
       *psn;

   // Same pointer, internal copy.
   returnIf(pDst == pSrc, gmemCopy(pDst, byteCount, byteIndexSrc, byteIndexDst));

   // Nothing to copy.
   returnIf(byteCount == 0, gbTRUE);

   returnIf(
         !pDst             ||
         !pSrc             ||
         byteIndexSrc <  0 ||
         byteIndexDst <  0,
      gbFALSE);

   pdn = (Gn1 *) pDst;
   psn = (Gn1 *) pSrc; //lint !e960 !e9005
   pdn = &(pdn[byteIndexDst]);
   psn = &(psn[byteIndexSrc]);

   memcpy(pdn, psn, (size_t) byteCount);

   return gbTRUE;
}

/******************************************************************************
func: gmemCreate_
******************************************************************************/
grlAPI Gp *gmemCreate_(Char const * const type, Gcount const byteCount)
{
   Gn1  *p;

   returnIf(byteCount <= 0, NULL);

#if GCHECK_MEMORY_IS_ON == 1
   debugCheckMemory()
#endif

   glockEnter(&_lock);

   // Create the data.
   p = (Gn1 *) _PoolCreate(type, byteCount);
   // Out of memory.
   if (!p)
   {
      // Flush pools just in case they are causing the problem
      _PoolFlush();
      p = (Gn1 *) _PoolCreate(type, byteCount);
   }

   // We really are out of memory.
   if (!p)
   {
      glockExit(&_lock);
      return NULL;
   }

   glockExit(&_lock);

#if GCHECK_MEMORY_IS_ON == 1
   debugCheckMemory()
#endif

   return p;
}

/******************************************************************************
func: gmemDestroy
******************************************************************************/
grlAPI void gmemDestroy(Gp * const p)
{
   if (!p)
   {
      return;
   }

#if GCHECK_MEMORY_IS_ON == 1
   debugCheckMemory()
#endif

   glockEnter(&_lock);

   _PoolDestroy(gleakDestroy(p));

   glockExit(&_lock);

#if GCHECK_MEMORY_IS_ON == 1
   debugCheckMemory()
#endif

   return;
}

/******************************************************************************
func: gmemFlushPools
******************************************************************************/
grlAPI void gmemFlushPools(void)
{
   glockEnter(&_lock);

   _PoolFlush();

   glockExit(&_lock);
}

/******************************************************************************
func: gmemSetDefaced

Fill the buffer with garbage values. 0xDEADBEEF, 0xFEEDFACE, 0xDEAFCAFE, and
0xFEE1F00D
******************************************************************************/
grlAPI void gmemSetDefaced(Gp * const p, Gcount const byteCount)
{
   Gcount count;
   Gn1   *pn;
   Gn4   *pn4;

   genter;

   greturnVoidIf(byteCount <= 0);

   pn    = (Gn1 *) p;
   count = 0;

   // Not aligned to the 4 byte boundary.
   if (((Gnp) pn) & 0x3) //lint !e923
   {
      loopOnce
      {
         *pn = 0xf0; pn++; count++;
         greturnVoidIf(count == byteCount);
         breakIf((((Gnp) pn) & 0x3) == 0); //lint !e923

         *pn = 0xf0; pn++; count++;
         greturnVoidIf(count == byteCount);
         breakIf((((Gnp) pn) & 0x3) == 0); //lint !e923

         *pn = 0xf0; pn++; count++;
         greturnVoidIf(count == byteCount);
         breakIf((((Gnp) pn) & 0x3) == 0); //lint !e923
      }
   }

   pn4 = (Gn4 *) pn; //lint !e927 !e826
   loop
   {
      breakIf(byteCount - count < 4);

#if defined(grlSWAP)
      *pn4 = 0xefbeadde;
#else
      *pn4 = 0xdeadbeef;
#endif
      pn4++; count += 4;
      greturnVoidIf(count == byteCount);
      breakIf(byteCount - count < 4);

#if defined(grlSWAP)
      *pn4 = 0xcefaedfe;
#else
      *pn4 = 0xfeedface;
#endif
      pn4++; count += 4;
      greturnVoidIf(count == byteCount);
      breakIf(byteCount - count < 4);

#if defined(grlSWAP)
      *pn4 = 0xfecaafde;
#else
      *pn4 = 0xdeafcafe;
#endif
      pn4++; count += 4;
      greturnVoidIf(count == byteCount);
      breakIf(byteCount - count < 4);

#if defined(grlSWAP)
      *pn4 = 0x0df0e1fe;
#else
      *pn4 = 0xfee1f00d;
#endif
      pn4++; count += 4;
      greturnVoidIf(count == byteCount);
      breakIf(byteCount - count < 4);
   }

   pn = (Gn1 *) pn4; //lint !e928
   *pn = 0xf0; pn++; count++;
   greturnVoidIf(count == byteCount);

   *pn = 0xf0; pn++; count++;
   greturnVoidIf(count == byteCount);

   *pn = 0xf0; /* pn++; */ count++;
   greturnVoidIf(count == byteCount);
}

/******************************************************************************
func: gmemStart
******************************************************************************/
Gb gmemStart(void)
{
   glockCreateContent(&_lock);

   // Prep the pool.
   memset(_pool, 0, gsizeof(Pool) * POOL_COUNT);

   return gbTRUE;
}

/******************************************************************************
func: gmemStop
******************************************************************************/
void gmemStop(void)
{
   glockDestroyContent(&_lock);

   return;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _PoolCreate
******************************************************************************/
static Gp *_PoolCreate(Char const * const type, Gi4 const size)
{
   Gi4  poolBin;
   Mem *buffer;

   // Type may not be used.
   type;

   poolBin = POOL_BIN_FROM_SIZE(size);

   // To big for the pools.  Create and Destroy are unpooled.
   if (poolBin > POOL_COUNT)
   {
      buffer = (Mem *) calloc((size_t) 1, gsizeof(Mem) + (size_t) size); //lint !e586
      if (!buffer)
      {
         debugHalt("calloc failed");
         return NULL;
      }

      GTYPE_SET(buffer, type);

      buffer->size    = size;
      buffer->poolBin = POOL_UNBINNED_INDEX;
   }
   else
   {
      // Pooled memory.
      // Pop from the free list.
      if (_pool[poolBin].freeList != NULL) //lint !e661
      {
         // Get the buffer.
         buffer = (Mem *) _pool[poolBin].freeList; //lint !e661 !e826 !e929

         // Pop the buffer from the free list.
         _pool[poolBin].freeList = _pool[poolBin].freeList->next; //lint !e661
         _pool[poolBin].freeCount--; //lint !e661

         // Clear the buffer.
         gmemClear(buffer, (Gcount) (gsizeof(Mem) + POOL_BIN_SIZE(poolBin)));
      }
      else
      {
         buffer = (Mem *) calloc((size_t) 1, sizeof(Mem) + (size_t) POOL_BIN_SIZE(poolBin)); //lint !e586 !e960
         if (!buffer)
         {
            debugHalt("calloc failed");
            return NULL;
         }

         _pool[poolBin].poolCount++; //lint !e661
      }

      GTYPE_SET(buffer, type);

      buffer->size    = size;
      buffer->poolBin = poolBin;
   }

   return (Gp *) &(buffer[1]); //lint !e429 !e826
}

/******************************************************************************
func: _PoolDestroy
******************************************************************************/
static void _PoolDestroy(Gp * const mem)
{
   Gindex    poolBin;
   Mem      *buffer;
   FreeList *freeList;

   buffer = (Mem *) mem;
   buffer--;

#if defined(_DEBUG)
   // Make it easier to see that something is being blow away.
   gmemSetDefaced(&(buffer[1]), (Gcount) buffer->size);
#endif

   poolBin = (Gindex) buffer->poolBin;

   // Memory is not pooled.
   if (poolBin == POOL_UNBINNED_INDEX)
   {
      free(buffer); //lint !e424 !e586
   }
   // Memory is pooled.
   else
   {
      // Put the memory on the free list.
      freeList                = (FreeList *) (Gp *) buffer;
      freeList->next          = _pool[poolBin].freeList;
      _pool[poolBin].freeList = freeList;
      _pool[poolBin].freeCount++;
   }

   return;
}

/******************************************************************************
func: _PoolFlush
******************************************************************************/
static void _PoolFlush(void)
{
   Gindex index;
   Mem   *buffer;

   forCount(index, POOL_COUNT)
   {
      loop
      {
         breakIf(_pool[index].freeList == NULL);

         buffer = (Mem *) _pool[index].freeList; //lint !e826 !e929
         _pool[index].freeList = _pool[index].freeList->next;
         _pool[index].freeCount--;
         _pool[index].poolCount--;

         // Destroy the buffer.
         free(buffer); //lint !e586
      }

#if defined(_DEBUG)
      if (_pool[index].poolCount > 0)
      {
         wchar_t stemp[80];
         swprintf(
            stemp,
            (size_t) 80,
            L"Memory pool %3d still contains allocated data.\n",
            index); //lint !e534 
         debugPrint(stemp);
      }
#endif
   }
}
