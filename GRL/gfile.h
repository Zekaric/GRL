/**************************************************************************************************
file:       gfile
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Simple file routines without any of the standard lib problems.
These file routines are large file compatible.  It uses windows
file routines to accomplish this.
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

#if !defined(GFILEH)
#define      GFILEH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gi  GfileOffset;
typedef Gn  GfileIndex;

typedef enum
{
   gfileOpenModeREAD_ONLY,
   gfileOpenModeREAD_WRITE,
   gfileOpenModeREAD_WRITE_NEW,
   gfileOpenModeAPPEND
} GfileOpenMode;

typedef enum
{
   gfileOpStatusNONE     = 0x00,
   gfileOpStatusREADING  = 0x01,
   gfileOpStatusWRITING  = 0x02,
   gfileOpStatusANY      = 0x03
} GfileOpStatus;

typedef enum
{
   gfileCreateSUCCESS,
   gfileCreateBAD_PATH,
   gfileCreateFAILED_TO_OPEN_FILE,
   gfileCreateFAILED_TO_COMPLETELY_WRITE_FILE
} GfileCreate;

typedef enum
{
   gfileSetPositionSUCCESS,
   gfileSetPositionBAD_FILE,
   gfileSetPositionBAD_POSITION,
   gfileSetPositionFAILURE
} GfileSetPosition;

typedef struct Gfile Gfile;
struct Gfile
{
   GTYPE_VAR;

   GfileOpStatus   opStatus;
   Gb              isAtEnd;
#if grlWINDOWS == 1
   Gi4              file;
#else
   FILE           *file;
#endif
};

/**************************************************************************************************
function:
**************************************************************************************************/
/*lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026 */
#define gfileOpen(PATH,MODE)  ((Gfile *) gleakCloc(gfileOpen_((PATH), (MODE)), gsizeof(Gfile)))
/*lint -restore */

grlAPI void              gfileClose(                        Gfile * const file);
grlAPI GfileCreate       gfileCreateFromStrArray(           Gpath const * const path, GcType const type, GsArray const * const lines);

grlAPI Gcount            gfileGet(                          Gfile * const file, Gcount const count, Gp * const buffer);
grlAPI Gb                gfileGet2(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gb                gfileGet4(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gb                gfileGet8(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gcount            gfileGetC(                         Gfile * const file, GcType const type, Gc * const letter);
grlAPI Gcount            gfileGetS(                         Gfile * const file, GcType const type, Gs * const str);
grlAPI Gb                gfileGetContent(                   Gfile * const file, Gcount * const count, Gn1 ** const buffer);
grlAPI Gb                gfileGetContentS(                  Gfile * const file, GcType const type, Gs * const str);
grlAPI Gcount            gfileGetContentSArray(             Gfile * const file, GcType const type, GsArray * const strArray);
grlAPI GfileIndex        gfileGetPosition(                  Gfile * const file);
grlAPI GfileIndex        gfileGetSize(                      Gfile * const file);

grlAPI Gb                gfileIsAtEnd(                      Gfile * const file);

grlAPI Gb                gfileLoadContent(                  Gs const * const pathS, Gcount * const count, Gn1 ** const buffer);

grlAPI Gfile            *gfileOpen_(                        Gpath const * const path, GfileOpenMode const mode);
grlAPI Gb                gfileOpenLoadContent(              Gpath const * const path, Gcount * const count, Gn1 ** const buffer);
grlAPI Gb                gfileOpenStoreContent(             Gpath const * const path, Gcount const count, Gn1 const * const buffer);

grlAPI Gb                gfileSet(                          Gfile * const file, Gcount const count, Gp const * const buffer, Gcount * const writeCount);
grlAPI Gb                gfileSet2(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSet4(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSet8(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSetA(                         Gfile * const file, GcType const type, Char const * const line, Gcount * const writeCount);
grlAPI Gcount            gfileSetC(                         Gfile * const file, GcType const type, Gc const letter);
grlAPI Gb                gfileSetS(                         Gfile * const file, GcType const type, Gs const * const line, Gcount * const writeCount);
grlAPI Gcount            gfileSetSArray(                    Gfile * const file, GcType const type, GsArray const * const lines);
grlAPI GfileSetPosition  gfileSetPosition(                  Gfile * const file, Gposition const pos, GfileOffset const offset);
grlAPI Gb                gfileSetValue(                     Gfile * const file, Gcount const count, Gn1 const value, Gcount * const writeCount);
grlAPI Gb                gfileStoreContent(                 Gpath const * const path, Gcount const count, Gn1 const * const buffer);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
