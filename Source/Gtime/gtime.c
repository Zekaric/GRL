/******************************************************************************
file:       gtime
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
base time functions
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
#include "pre.h"

/******************************************************************************
local:
prototype:
******************************************************************************/
static void _Get(const struct tm ttemp, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gtimeGet

Get the time of the system.
******************************************************************************/
grlAPI Gtime gtimeGet(void)
{
   // No genter or greturn because this is called in gprofile which is embedded
   // in genter and greturn.

   Gtime timeValue;

   if (_time64(&timeValue) == -1)
   {
      debugHalt("_time64 failed");
      return 0;
   }

   return timeValue;
}

/******************************************************************************
func: gtimeGetLocalTime

Get the local time of the system in understandable format.

param:
time
   Gtime
   in
   the time.

daylightSavingTime, year, yearDay, month, monthDay, weekDay, hour, minute, second
   GtimeDST *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *
   in/out, in/out, in/out, in/out, in/out, in/out, in/out, in/out, in/out,
   Daylight saving time flag.  Year number.  Day of the year number (0-365).
   Month number.  Day of the month number.  Day of the week number (Sun = 0).
   Hour number.  Minute numbers.  Second Number.  All values here
   can be NULL if not desired.
******************************************************************************/
grlAPI Gb gtimeGetLocalTime(const Gtime timeValue, GtimeDST * const daylightSavingTime, 
   Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay,
   Gi4 * const hour, Gi4 * const minute, Gi4 * const second)
{
   struct tm ttemp;

   genter;

   if (_localtime64_s(&ttemp, &timeValue) != 0)
   {
      debugHalt("_localtime64_s failed");
      greturn gbFALSE;
   }

   _Get(ttemp, daylightSavingTime, year, yearDay, month, monthDay, weekDay, hour, minute, second);

   greturn gbTRUE;
}

/******************************************************************************
func: gtimeGetLocalTime

Get the local time of the system in understandable format.

param:
time
   Gtime
   in
   the time.

daylightSavingTime, year, yearDay, month, monthDay, weekDay, hour, minute, second
   GtimeDST *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *, Gi4 *
   in/out, in/out, in/out, in/out, in/out, in/out, in/out, in/out, in/out,
   Daylight saving time flag.  Year number.  Day of the year number (0-365).
   Month number.  Day of the month number.  Day of the week number (Sun = 0).
   Hour number.  Minute numbers.  Second Number.  All values here
   can be NULL if not desired.
******************************************************************************/
grlAPI Gb gtimeGetTime(const Gtime timeValue, GtimeDST * const daylightSavingTime,
   Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay,
   Gi4 * const hour, Gi4 * const minute, Gi4 * const second)
{
   struct tm ttemp;

   genter;

   if (_gmtime64_s(&ttemp, &timeValue) != 0)
   {
      debugHalt("_gmtime64_s failed");
      greturn gbFALSE;
   }

   _Get(ttemp, daylightSavingTime, year, yearDay, month, monthDay, weekDay, hour, minute, second);

   greturn gbTRUE;
}

/******************************************************************************
func: gtimeStart

Start the time functions.

return:
Gi4
******************************************************************************/
Gb gtimeStart(void)
{
   genter;

#if grlWINDOWS == 1
   _tzset();
#endif

   greturn gbTRUE;
}

/******************************************************************************
func: gtimeStop

Clean up.
******************************************************************************/
void gtimeStop(void)
{
   genter;
   greturn;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _Get

Get the time data.
******************************************************************************/
static void _Get(const struct tm ttemp, GtimeDST * const daylightSavingTime,
   Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, 
   Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second)
{
   genter;

   if (daylightSavingTime)
   {
      if (ttemp.tm_isdst < 0)
      {
         *daylightSavingTime = GtimeDST_UNKNOWN;
      }
      else if (ttemp.tm_isdst > 0)
      {
         *daylightSavingTime = GtimeDST_ACTIVE;
      }
      else
      {
         *daylightSavingTime = GtimeDST_INACTIVE;
      }
   }
   if (year)
   {
      *year = ((Gi4) ttemp.tm_year) + 1900;
   }
   if (yearDay)
   {
      *yearDay = ttemp.tm_yday;
   }
   if (month)
   {
      *month = ttemp.tm_mon;
   }
   if (monthDay)
   {
      *monthDay = ttemp.tm_mday;
   }
   if (weekDay)
   {
      *weekDay = ttemp.tm_wday;
   }
   if (hour)
   {
      *hour = ttemp.tm_hour;
   }
   if (minute)
   {
      *minute = ttemp.tm_min;
   }
   if (second)
   {
      *second = ttemp.tm_sec;
   }

   greturn;
}
