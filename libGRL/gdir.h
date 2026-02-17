/**************************************************************************************************
file:       gdir
author:     Robbert de Groot
copyright:  2002-2010, Robbert de Groot

description:
Simple directory routines.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

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
type:
**************************************************************************************************/
typedef Gn     GdirFileSize;

typedef enum
{
   gdirTypeNONE,
   gdirTypeFILE,
   gdirTypeFOLDER,
   gdirTypeOTHER
} GdirType;

typedef struct
{
   GTYPE_VAR

   GdirType                 type;
   Gtime                    timeAccessed,
                            timeCreated,
                            timeModified;
   GdirFileSize             size;
} GdirInfo;

/**************************************************************************************************
function:
**************************************************************************************************/
#define gdirGetCurrent()                                    gleakClocType(GdirGetCurrent_(),                                      Gpath)
#define gdirGetList(PATH, PATTERN, IS_CASE_INSENSITIVE)     gleakClocType(gdirGetList_((PATH), (PATTERN), (IS_CASE_INSENSITIVE)), GvArray)

grlAPI Gb             gdirCopy(                 Gpath const * const pathSrc, Gpath const * const pathDst);
grlAPI Gb             gdirCreateFolder(         Gpath const * const path);

grlAPI Gb             gdirDestroy(              Gpath const * const path);

grlAPI GvArray       *gdirGetList_(             Gpath const * const path, Gs const * const pattern, Gb const isCaseInsensitive);
grlAPI GdirInfo       gdirGetInfo(              Gpath const * const path);

grlAPI Gb             gdirIsExisting(           Gpath const * const path);

grlAPI Gb             gdirRename(               Gpath const * const path, Gpath const * const pathDestination);

grlAPI GdirFileSize   gdirInfoGetSize(          GdirInfo const * const dirInfo);
grlAPI Gtime          gdirInfoGetTimeAccessed(  GdirInfo const * const dirInfo);
grlAPI Gtime          gdirInfoGetTimeCreated(   GdirInfo const * const dirInfo);
grlAPI Gtime          gdirInfoGetTimeModified(  GdirInfo const * const dirInfo);
grlAPI GdirType       gdirInfoGetType(          GdirInfo const * const dirInfo);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
