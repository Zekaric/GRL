/**************************************************************************************************
file:       gfile
author:     Robbert de Groot
copyright:  2000, Robbert de Groot

description:
Simple file routines without any of the standard lib problems.
These file routines are large file compatible.  It uses windows
file routines to accomplish this.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2000, Robbert de Groot

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

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gi  GfileOffset;
typedef Gi  GfileIndex;
typedef Gi  GfileCount;

typedef struct Gfile
{
   GTYPE_VAR

   GfileOpStatus   opStatus;
   Gb              isAtEnd;
   SDL_IOStream   *stream;
} Gfile;

/**************************************************************************************************
function:
**************************************************************************************************/
#define gfileOpen(PATH,MODE)     gleakClocType(gfileOpen_((PATH), (MODE)),    Gfile)
#define gfileOpenMem(COUNT, MEM) gleakClocType(gfileOpenMem_((COUNT), (MEM)), Gfile)

grlAPI void              gfileClose(                        Gfile * const file);
grlAPI GfileCreate       gfileCreateFromStrArray(           Gpath const * const path, GvArray const * const lines);

grlAPI Gcount            gfileGet(                          Gfile * const file, Gcount const count, Gp * const buffer);
grlAPI Gb                gfileGet2(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gb                gfileGet4(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gb                gfileGet8(                         Gfile * const file, Gcount const count, Gp * const i);
grlAPI Gcount            gfileGetChar(                      Gfile * const file, Gchar * const letter);
grlAPI Gcount            gfileGetS(                         Gfile * const file, Gs * const str);
grlAPI Gb                gfileGetContent(                   Gfile * const file, Gcount * const count, Gn1 ** const buffer);
grlAPI Gb                gfileGetContentS(                  Gfile * const file, Gs * const str);
grlAPI Gcount            gfileGetContentSArray(             Gfile * const file, GvArray * const strArray);
grlAPI GfileIndex        gfileGetPosition(                  Gfile * const file);
grlAPI GfileIndex        gfileGetSize(                      Gfile * const file);

grlAPI Gb                gfileIsAtEnd(                      Gfile * const file);

grlAPI Gb                gfileLoadContent(                  Gpath const * const path, Gcount * const count, Gn1 ** const buffer);

grlAPI Gfile            *gfileOpen_(                        Gpath const * const path, GfileOpenMode const mode);
grlAPI Gfile            *gfileOpenMem_(                     GfileCount size, void *mem);

grlAPI Gb                gfileSet(                          Gfile * const file, Gcount const count, Gp const * const buffer, Gcount * const writeCount);
grlAPI Gb                gfileSet2(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSet4(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSet8(                         Gfile * const file, Gcount const count,       Gp * const i);
grlAPI Gb                gfileSetChar(                      Gfile * const file, Gchar const letter);
grlAPI Gb                gfileSetS(                         Gfile * const file, Gs const * const line);
grlAPI Gb                gfileSetSArray(                    Gfile * const file, GvArray const * const lines);
grlAPI GfileSetPosition  gfileSetPosition(                  Gfile * const file, Gposition const pos, GfileOffset const offset);
grlAPI Gb                gfileSetValue(                     Gfile * const file, Gcount const count, Gn1 const value, Gcount * const writeCount);
grlAPI Gb                gfileStoreContent(                 Gpath const * const path, Gcount const count, Gn1 const * const buffer);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
