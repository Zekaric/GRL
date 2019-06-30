/******************************************************************************

file:          gprofile
author:        Robbert de Groot
company:       [company]
copyright:     2015, Robbert de Groot

description:

******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

#if GPROFILE_IS_ON == 1

/******************************************************************************
local:
constant:
******************************************************************************/
#define PROFILE_RECORD_COUNT  0x10000

/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   Gtime       total,
               content;
   Gcount      count;
   Char const *file;
   Char const *function;
} Gprofile;

/******************************************************************************
variable:
******************************************************************************/
static Gtime     _stack[4096];
static Gindex    _stackIndex  = 0;
static Gprofile *_list        = NULL;
static Gcount    _count       = 0;
static Gcount    _bankCount   = 1;
static Gtime     _lastTime    = 0;

/******************************************************************************
prototype:
******************************************************************************/

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gprofileCheckStack
******************************************************************************/
grlAPI void gprofileCheckStack(Gindex index)
{
   debugHaltIf(index != _stackIndex, "Bad Profile Stack.");
}

/******************************************************************************
func: gprofileEnter
******************************************************************************/
grlAPI Gtime gprofileEnter(Gindex * const index, Char const * const file, Char const * const function)
{
   // Create the list.
   if (!_list)
   {
      _list = memCreateTypeArray(Gprofile, PROFILE_RECORD_COUNT);
   }

   if (*index < 0)
   {
      *index = _count;
      _count++;

      // resize the list.
      if (_count % PROFILE_RECORD_COUNT == 0)
      {
         _bankCount++;
         _list = (Gprofile *) realloc(_list, (size_t) (_bankCount * PROFILE_RECORD_COUNT));
         debugHaltIf(!_list, "No more memory for profiling.  We have to stop.");
         exit(1);
      }

      _list[*index].count    = 0;
      _list[*index].file     = file;
      _list[*index].function = function;
      _list[*index].total    = 0;
      _list[*index].content  = 0;
   }

   _list[*index].count++;

   _stackIndex++;
   _stack[_stackIndex] = 0;

#if grlWINDOWS == 1
   {
      Gtime value[4];
      QueryPerformanceCounter((LARGE_INTEGER *) value);
      //debugHaltIf(value < _lastTime, "Time travel detected!");
      //_lastTime = value;
      return value[0];
   }
#else
   return gtimeGet();
#endif
}

/******************************************************************************
func: gprofileExit
******************************************************************************/
grlAPI void gprofileExit(Gindex const index, Gtime const time)
{
   Gtime value;

#if grlWINDOWS == 1
   QueryPerformanceCounter((LARGE_INTEGER *) &value);
   //debugHaltIf(value < _lastTime, "Time travel detected!");
   //_lastTime = value;
#else
   value = gtimeGet();
#endif

   value -= time;
   _list[index].total   += value;
   _list[index].content += gMAX(0, value - _stack[_stackIndex]);
   //debugHaltIf(_list[index].content < 0, "Time Travel detected!");

   _stackIndex--;
   _stack[_stackIndex] += value;
}

/******************************************************************************
func: gprofileReport
******************************************************************************/
grlAPI void gprofileReport(void)
{
   Gindex index,
          findex,
          maxIndex;
   Gtime  totalCount,
          totalTime;
   Gr     percentTime,
          percentContent,
          percentCount;
   Gc2    report[1024];

   totalCount = 0;
   totalTime  = 0;
   forCount(index, _count)
   {
      totalCount += _list[index].count;
      if (totalTime < _list[index].total)
      {
         totalTime = _list[index].total;
      }
   }

   // Print out the results in descending order.  I don't care about speed here
   debugPrint(
      L"=== PROFILE REPORT===\n"
      L"Time:\n");
   forCount(index, _count)
   {
      // Find the next record with the highest reported value.
      maxIndex = 0;
      forCount(findex, _count)
      {
         if (_list[findex].total   != gtimeNONE &&
             _list[maxIndex].total < _list[findex].total)
         {
            maxIndex = findex;
         }
      }

      percentTime    = ((Gr) _list[maxIndex].total)   * 100.0 / ((Gr) totalTime);
      percentContent = ((Gr) _list[maxIndex].content) * 100.0 / ((Gr) totalTime);
      percentCount   = ((Gr) _list[maxIndex].count)   * 100.0 / ((Gr) totalCount);
      
      swprintf(
         report, 
         1024,
         L"%-64S, %-32S, %15d, %10.3f, %15d, %10.3f, %15d, %10.3f,\n",
         _list[maxIndex].file,
         _list[maxIndex].function,

         (Gi4) _list[maxIndex].total,
         (Gr4) percentTime,

         (Gi4) _list[maxIndex].content,
         (Gr4) percentContent,

         (Gi4) _list[maxIndex].count,
         (Gr4) percentCount);
      debugPrint(report);

      // Reset the time so we don't look at it again.
      _list[maxIndex].total = gtimeNONE;
   }

   // Print out the results in descending order.  I don't care about speed here
   debugPrint(
      L"\n\n=== PROFILE REPORT===\n"
      L"Content:\n");
   forCount(index, _count)
   {
      // Find the next record with the highest reported value.
      maxIndex = 0;
      forCount(findex, _count)
      {
         if (_list[findex].content   != gtimeNONE &&
             _list[maxIndex].content < _list[findex].content)
         {
            maxIndex = findex;
         }
      }

      percentContent = ((Gr) _list[maxIndex].content) * 100.0 / ((Gr) totalTime);
      percentCount   = ((Gr) _list[maxIndex].count)   * 100.0 / ((Gr) totalCount);
      
      swprintf(
         report, 
         1024,
         L"%-64S, %-32S, %15d, %10.3f, %15d, %10.3f,\n",
         _list[maxIndex].file,
         _list[maxIndex].function,

         (Gi4) _list[maxIndex].content,
         (Gr4) percentContent,

         (Gi4) _list[maxIndex].count,
         (Gr4) percentCount);
      debugPrint(report);

      // Reset the time so we don't look at it again.
      _list[maxIndex].content = gtimeNONE;
   }

   // Print out the results in descending order.  Based on count this time.
   debugPrint(
      L"\n\n=== PROFILE REPORT===\n"
      L"Count:\n");
   forCount(index, _count)
   {
      // Find the next record with the highest reported value.
      maxIndex = 0;
      forCount(findex, _count)
      {
         if (_list[findex].count   != -1 &&
             _list[maxIndex].count < _list[findex].count)
         {
            maxIndex = findex;
         }
      }

      // We don't care if it's something less than...
      if (_list[maxIndex].count == 1)
      {
         break;
      }

      percentCount = ((Gr) _list[maxIndex].count) * 100.0 / ((Gr) totalCount);
      swprintf(
         report, 
         1024,
         L"%-64S, %-32S, %15d, %10.3f,\n",
         _list[maxIndex].file,
         _list[maxIndex].function,

         (Gi4) _list[maxIndex].count,
         (Gr4) percentCount);
      debugPrint(report);

      // Reset the time so we don't look at it again.
      _list[maxIndex].count = -1;
   }
}

#endif