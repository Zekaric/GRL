/**************************************************************************************************
file:       gmath
author:     Robbert de Groot
copyright:  2001-2009, Robbert de Groot

description:
math routines
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) !!!!YEAR!!!!, Robbert de Groot
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

#if !defined(GMATHH)
#define      GMATHH

/**************************************************************************************************
Types
**************************************************************************************************/

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/*lint -save -e960 */
#define gmathDOUBLE_TOLERANCE  0.000000001
#define gmathFLOAT_TOLERANCE   0.001
#define gmathDEFAULT_TOLERANCE 0.001

#define gmathPI                3.14159265358974
#define gmathDEG_TO_RAD        0.01745329251994329577
#define gmathRAD_TO_DEG       57.29577951308232088
/*lint -restore */

typedef enum
{
   gmathAxisNONE,
   gmathAxisX,
   gmathAxisY,
   gmathAxisZ
} GmathAxis;

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "grect.h"

#include "gvec2.h"
#include "gvec3.h"

#include "gmatrix3.h"

/**************************************************************************************************
prototype: 
**************************************************************************************************/

#endif
