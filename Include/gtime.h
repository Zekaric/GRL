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

#if !defined(GTIMEH)
#define      GTIMEH

/******************************************************************************
constant:
******************************************************************************/
typedef enum
{
   GtimeDST_UNKNOWN = -1,
   GtimeDST_INACTIVE,
   GtimeDST_ACTIVE
} GtimeDST;

/******************************************************************************
type:
******************************************************************************/
/*lint -save -e960 */
#if grlWINDOWS == 1

#define gtimeNONE Gi8MIN
#define Gtime __time64_t
#endif

#if defined(MACOSX)

#define Gtime time_t
#endif
/*lint -restore */

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Gtime gtimeGet(         void);
grlAPI Gb    gtimeGetTime(     Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);
grlAPI Gb    gtimeGetTimeLocal(Gtime const timeValue, GtimeDST * const daylightSavingTime, Gi4 * const year, Gi4 * const yearDay, Gi4 * const month, Gi4 * const monthDay, Gi4 * const weekDay, Gi4 * const hour, Gi4 * const minute, Gi4 * const second);

// Start and Stop called in grlStart and grtStop
       Gb    gtimeStart(       void);
       void  gtimeStop(        void);

#endif
