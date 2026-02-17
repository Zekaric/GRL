/**************************************************************************************************
file:       gtime
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
base time functions
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
variable:
**************************************************************************************************/
static SDL_DateFormat _formatDate   = SDL_DATE_FORMAT_YYYYMMDD;
static SDL_TimeFormat _formatTime   = SDL_TIME_FORMAT_24HR;

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gtimeGet

Get the time of the system.
**************************************************************************************************/
grlAPI Gtime gtimeGet(void)
{
   // Aiming to keep this function as fast as possible so no genter and greturn.
   Gtime timeValue;

   return0If(!SDL_GetCurrentTime(&timeValue));

   return timeValue;
}

/**************************************************************************************************
func: gtimeGetTime

Get the time of the system.
**************************************************************************************************/
grlAPI Gb gtimeGetTime(Gtime const timeValue, Gb const isLocalTime,
   Gi4 * const year, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay,
   Gi4 * const hour, Gi4 * const minute, Gi4 * const second, Gi4 * const nanoSecond)
{
   SDL_DateTime value;

   genter;

   greturnFalseIf(!SDL_TimeToDateTime(timeValue, &value, isLocalTime));

   if (year)       *year       = value.year;
   if (month)      *month      = value.month;
   if (monthDay)   *monthDay   = value.day;
   if (weekDay)    *weekDay    = value.day_of_week;
   if (hour)       *hour       = value.hour;
   if (minute)     *minute     = value.minute;
   if (second)     *second     = value.second;
   if (nanoSecond) *nanoSecond = value.nanosecond;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gtimeStart

Start the time functions.

return:
Gi4
**************************************************************************************************/
Gb gtimeStart(void)
{
   genter;

   if (!SDL_GetDateTimeLocalePreferences(&_formatDate, &_formatTime))
   {
      _formatDate = SDL_DATE_FORMAT_YYYYMMDD;
      _formatTime = SDL_TIME_FORMAT_24HR;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gtimeStop

Clean up.
**************************************************************************************************/
void gtimeStop(void)
{
   genter;
   greturn;
}
