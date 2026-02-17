/**************************************************************************************************
file:       gdir
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
Simple directory routines.
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
include
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/

/**************************************************************************************************
func: gdirCopy
**************************************************************************************************/
grlAPI Gb gdirCopy(Gpath const * const pathSrc, Gpath const * const pathDst)
{
   Gb        result;
   Gchar1   *u1PathSrc,
            *u1PathDst;

   genter;

   greturnFalseIf(
      !pathSrc ||
      !pathDst);

   greturnFalseIf(!gdirIsExisting(pathSrc));

   u1PathSrc = gpathClocSystemChar1(pathSrc);
   u1PathDst = gpathClocSystemChar1(pathDst);

   result = SDL_CopyFile((char *) u1PathSrc, (char *) u1PathDst);

   gmemDloc(u1PathDst);
   gmemDloc(u1PathSrc);

   greturn result;
}

/**************************************************************************************************
func: gdirFolderCreate

Create the folder(s) provided in the path.
**************************************************************************************************/
grlAPI Gb gdirCreateFolder(Gpath const * const path)
{
   Gb        result;
   Gchar1   *u1Path;

   genter;

   greturnFalseIf(!path);

   u1Path = gpathClocSystemChar1(path);

   result = SDL_CreateDirectory((char *) u1Path);

   gmemDloc(u1Path);

   greturn result;
}

/**************************************************************************************************
func: gdirDestroy
**************************************************************************************************/
grlAPI Gb gdirDestroy(Gpath const * const path)
{
   Gb     result;
   Gchar1 *u1Path;

   genter;

   greturnFalseIf(path);

   u1Path = gpathClocSystemChar1(path);

   result = SDL_RemovePath((char *) u1Path);

   gmemDloc(u1Path);

   greturn result;
}

/**************************************************************************************************
func: gdirGetList

pattern can be NULL.  If NULL then everything is returned.  Wildcards are * match any number of
characters, ? match any 1 character.  All others are matched.
**************************************************************************************************/
grlAPI GvArray *gdirGetList_(Gpath const * const path, Gs const * const pattern,
   Gb const isCaseInsensitive)
{
   Gchar1 **list;
   Gindex   listIndex;
   Gcount   listCount;
   Gchar1  *u1Path,
           *u1Pattern;
   GvArray *dirList;

   genter;

   greturnNullIf(
      !path ||
      !pattern);

   u1Path    = gpathClocSystemChar1(path);
   u1Pattern = gsClocGchar1(pattern);

   listCount = 0;
   list      = (Gchar1 **) SDL_GlobDirectory(
      (char *) u1Path,
      (char *) u1Pattern,
      isCaseInsensitive * SDL_GLOB_CASEINSENSITIVE,
      &listCount);

   dirList = gvArrayCloc("GpathArray", NULL, gbTRUE);
   forCount(listIndex, listCount)
   {
      gvArrayAddEnd(dirList, gvFromP(gpathClocFromSystemChar1(list[listIndex])));
   }

   gmemDloc(u1Pattern);
   gmemDloc(u1Path);

   greturn dirList;
}

/**************************************************************************************************
func: gdirGetInfo
**************************************************************************************************/
grlAPI GdirInfo gdirGetInfo(Gpath const * const path)
{
   Gb           result;
   GdirInfo     info;
   SDL_PathInfo sinfo;
   Gchar1      *u1Path;

   genter;

   gmemClearType(&info, GdirInfo);
   info.type = gdirTypeNONE;

   greturnValIf(!path, info);

   u1Path = gpathClocSystemChar1(path);
   greturnValIf(!path, info);

   result = SDL_GetPathInfo((char *) u1Path, &sinfo);

   gmemDloc(u1Path);

   info.type         = (GdirType) sinfo.type;
   info.size         = sinfo.size;
   info.timeAccessed = sinfo.access_time;
   info.timeCreated  = sinfo.create_time;
   info.timeModified = sinfo.modify_time;

   greturn info;
}

/**************************************************************************************************
func: gdirIsExisting
**************************************************************************************************/
grlAPI Gb gdirIsExisting(Gpath const *const path)
{
   genter;

   greturn gdirGetInfo(path).type != gdirTypeNONE;
}

/**************************************************************************************************
func: gdirRenamePath
**************************************************************************************************/
grlAPI Gb gdirRename(Gpath const * const pathOld, Gpath const * const pathNew)
{
   Gb        result;
   Gchar1   *u1PathOld,
            *u1PathNew;

   genter;

   greturnFalseIf(
      !pathOld ||
      !pathNew ||
      !gdirIsExisting(pathOld));

   u1PathOld = gpathClocSystemChar1(pathOld);
   u1PathNew = gpathClocSystemChar1(pathNew);

   // move the file
   result = SDL_RenamePath((char *) u1PathOld, (char *) u1PathNew);

   gmemDloc(u1PathNew);
   gmemDloc(u1PathOld);

   greturn result;
}

/**************************************************************************************************
func: gdirIfoGetSize
**************************************************************************************************/
grlAPI GdirFileSize gdirInfoGetSize(GdirInfo const * const dir)
{
   genter;

   greturn0If(!dir);

   greturn dir->size;
}

/**************************************************************************************************
func: gdirInfoGetTimeAccessed
**************************************************************************************************/
grlAPI Gtime gdirInfoGetTimeAccessed(GdirInfo const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeAccessed;
}

/**************************************************************************************************
func: gdirInfoGetTimeCreated
**************************************************************************************************/
grlAPI Gtime gdirInfoGetTimeCreated(GdirInfo const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeCreated;
}

/**************************************************************************************************
func: gdirInfoGetTimeModified
**************************************************************************************************/
grlAPI Gtime gdirInfoGetTimeModified(GdirInfo const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeModified;
}

/**************************************************************************************************
func: gdirInfoGetType
**************************************************************************************************/
grlAPI GdirType gdirInfoGetType(GdirInfo const * const dir)
{
   genter;

   greturnValIf(!dir, gdirTypeNONE);

   greturn dir->type;
}
