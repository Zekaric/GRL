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
#include "precompiled.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gdirArrayClocFromPath_

Create a directory listing based on a selection mask.
The passed in path may be relative or full.  It should not include a *.* mask
and should be a path to a folder.
**************************************************************************************************/
grlAPI GdirArray *gdirArrayClocFromPath_(const Gpath * const path)
{
   Gpath     *ptemp;
   Gs        *stemp;
   GdirArray *dlist;

   genter;

   dlist = NULL;

   greturnNullIf(!gpathIsPath(path));

   // Find first file in current directory
   // Create the mask.
   ptemp = gpathClocFrom(path);
   greturnNullIf(!ptemp);

   stemp = gsClocFromU2(L"*.*");
   if (gpathPush(ptemp, stemp))
   {
      dlist = gdirArrayClocFromMask(ptemp);
   }

   // Clean up
   gsDloc(ptemp);
   gsDloc(stemp);

   greturn dlist;
}

/**************************************************************************************************
func: gdirArrayClocFromMask_
**************************************************************************************************/
grlAPI GdirArray *gdirArrayClocFromMask_(const Gpath * const path)
{
   struct _wfinddata_t   finfo;
   Gi4                   htemp;
   GdirArray            *list;
   Gdir                 *data;
   Gpath                *pathMinusMask,
                        *pathSystem,
                        *pathWorking;

   genter;

   greturnNullIf(!gpathIsPath(path));

   // Create a full path.
   if (gpathIsRelative(path))
   {
      pathWorking = gdirGetWorking();

      gpathAppend(pathWorking, path); //lint !e534
      gpathReduce(pathWorking);       //lint !e534
   }
   else
   {
      pathWorking = gpathClocFrom(path);
   }

   // Find first file in current directory
   // Create the mask.
   pathMinusMask = gpathClocFrom(pathWorking);
   pathSystem    = gpathClocFrom(pathWorking);

   gpathPop(pathMinusMask); //lint !e534

   gpathSetToSystem(pathSystem); //lint !e534
   htemp = (Gi4) _wfindfirst(gsGet(pathSystem), &finfo);
   gsDloc(pathSystem);

   greturnNullIf(htemp == -1L);

   list = gdirArrayCloc();

   if (list != NULL)
   {
      loop
      {
         // Set the data.
         data = gmemClocType(Gdir);

         data->name = gsClocFromU2(finfo.name);

         data->path = gpathClocFrom(pathMinusMask);
         gpathPush(data->path, data->name); //lint !e534

         if (finfo.attrib & _A_SUBDIR)
         {
            data->type = gdirTypeFOLDER;
         }
         else
         {
            data->type = gdirTypeFILE;

            data->size = (Gi8) finfo.size;
         }

         data->timeAccessed = finfo.time_access;
         data->timeCreated  = finfo.time_create;
         data->timeModified = finfo.time_write;

         if (data->timeAccessed < 0)
         {
            data->timeAccessed = data->timeModified;
         }
         if (data->timeCreated < 0)
         {
            data->timeCreated = data->timeModified;
         }

         gdirArrayAddEnd(list, data); //lint !e534

         // Find the next entry if any.
         breakIf(_wfindnext(htemp, &finfo) != 0);
      }
   }

   if (_findclose(htemp) != 0)
   {
      debugHalt("_findclose failed for some reason");
   }

   // Clean up
   gsDloc(pathWorking);
   gsDloc(pathMinusMask);

   greturn list;
}

/**************************************************************************************************
func: gdirCloc_
**************************************************************************************************/
grlAPI Gdir *gdirCloc_(void)
{
   Gdir *gdir;

   genter;

   gdir = (Gdir *) gmemClocType(Gdir);
   greturnNullIf(!gdir);

   if (!gdirClocContent(gdir))
   {
      gmemDloc(gdir);
      greturn NULL;
   }

   greturn gdir;
}

/**************************************************************************************************
func: gdirClocContent
**************************************************************************************************/
grlAPI Gb gdirClocContent(Gdir * const gdir)
{
   genter;

   greturnFalseIf(!gdir);

   gmemClearType(gdir, Gdir);

   GTYPE_SET(gdir, "Gdir");

   greturn gbTRUE;
}

/**************************************************************************************************
func: gdirDloc
**************************************************************************************************/
grlAPI void gdirDloc(Gdir * const gdir)
{
   genter;

   greturnIf(!gdir)

   gdirDlocContent(gdir);

   gmemDloc(gdir);

   greturn;
}

/**************************************************************************************************
func: gdirDlocContent
**************************************************************************************************/
grlAPI void gdirDlocContent(Gdir * const gdir)
{
   genter;

   greturnIf(!gdir)

   gsDloc(   gdir->name);
   gpathDloc(gdir->path);

   greturn;
}

/**************************************************************************************************
func: gdirFileDestroy
**************************************************************************************************/
grlAPI Gb gdirFileDestroy(Gpath const * const path)
{
   Gb     result;
   Gpath *tpath;

   genter;

   greturnFalseIf(
      !gpathIsPath(   path) ||
      !gdirIsExisting(path));

   // Get the system path.
   tpath = gpathClocFrom(path);
   gpathSetToSystem(tpath);

   // Perform the delete of the file.
   result = (Gb) (_wremove(gsGet(tpath)) == 0);

   // Clean up.
   gpathDloc(tpath);

   greturn result;
}

/**************************************************************************************************
func: gdirFolderCreate

Create the folder(s) provided in the path.
**************************************************************************************************/
grlAPI Gb gdirFolderCreate(Gpath const * const path)
{
   Gb      result;
   Gpath  *tpath,
          *popPath;

   genter;

   greturnFalseIf(
      !gpathIsPath(  path) ||
      gdirIsExisting(path));

   result  = gbTRUE;
   popPath = NULL;

   // test to see if the path already exists.
   tpath = gpathClocFrom(path);

   // Path doesn't already exist.
   // Pop up the dir tree.
   popPath = gpathClocFrom(tpath);
   gpathPop(popPath); //lint !e534

   // Test again recursively.
   result = gdirFolderCreate(popPath);
   gsDloc(popPath);
   stopIf(!result);

   // Create the directory.
   gpathSetToSystem(tpath); //lint !e534

   result = (Gb) (_wmkdir(gsGet(tpath)) == 0); //lint !e930

STOP:
   gsDloc(tpath);

   greturn result;
}

/**************************************************************************************************
func: gdirFolderDestroy
**************************************************************************************************/
grlAPI Gb gdirFolderDestroy(Gpath const * const path)
{
   Gb     result;
   Gpath *tpath;

   genter;

   greturnFalseIf(
      !gpathIsPath(   path) ||
      !gdirIsExisting(path));

   // Get the system path.
   tpath = gpathClocFrom(path);
   gpathSetToSystem(tpath);

   // Attempt to delete the folder.
   result = (Gb) (_wrmdir(gsGet(tpath)) == 0);

   // Clean up.
   gsDloc(tpath);

   greturn result;
}

/**************************************************************************************************
func: gdirGetAppData

Get the application data directory for the user.
**************************************************************************************************/
grlAPI Gpath *gdirGetAppData(void)
{
   Gs                *str;

#if grlWINDOWS == 1
   HKEY               key;
   Gc2                rpath[MAX_PATH],
                      profPath[MAX_PATH];
   DWORD              type;
   ULONG              pathLen,
                      profPathLen;
   Gc2 const * const  profileList = L"Volatile Environment";

   genter;

   profPath[0]    = 0;
   pathLen        =
      profPathLen = gsizeof(Gpath);

   //lint -save -e923 -e928 -e534 -e960 -e9048 -e917
   stopIf(
      ERROR_SUCCESS !=
         RegOpenKeyEx(HKEY_CURRENT_USER, profileList, 0, KEY_READ, &key));

   if (ERROR_SUCCESS ==
         RegQueryValueEx(
            key,
            L"APPDATA",
            NULL,
            &type,
            (LPBYTE) rpath,
            &pathLen))
   {
      ExpandEnvironmentStrings(rpath, profPath, profPathLen);
   }

   RegCloseKey(key);
   //lint -restore

STOP:
   str = gsClocFromU2(profPath);
   gpathSetFromSystem(str); //lint !e534
#else
   genter;

   str = NULL;
#endif

   greturn str;
}

/**************************************************************************************************
func: gdirGetProfile

Get the user profile path.
**************************************************************************************************/
grlAPI Gpath const *gdirGetProfile(void)
{
   Gs                *str;

#if grlWINDOWS == 1
   HKEY               key;
   Gc2                rpath[MAX_PATH],
                      profPath[MAX_PATH];
   DWORD              type;
   ULONG              pathLen,
                      profPathLen;
   Gc2 const * const  profileList = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ProfileList";

   genter;

   profPath[0]    = 0;
   pathLen        =
      profPathLen = gsizeof(Gpath);

   //lint -save -e923 -e928 -e534 -e960 -e9048 -e917
   stopIf(
      ERROR_SUCCESS !=
         RegOpenKeyEx(HKEY_LOCAL_MACHINE, profileList, 0, KEY_READ, &key));

   if (ERROR_SUCCESS ==
         RegQueryValueEx(
            key,
            L"ProfilesDirectory",
            NULL,
            &type,
            (LPBYTE) rpath,
            &pathLen))
   {
      ExpandEnvironmentStrings(rpath, profPath, profPathLen);
   }

   RegCloseKey(key);
   //lint -restore

STOP:
   str = gsClocFromU2(profPath);
   gpathSetFromSystem(str); //lint !e534
#else
   genter;

   str = NULL;
#endif

   greturn str;
}

/**************************************************************************************************
func: gdirGetWorking

Get the current working directory.
**************************************************************************************************/
grlAPI Gpath *gdirGetWorking(void)
{
   Gs  *str;

#if grlWINDOWS == 1
   Gc2 syspath[4096];

   genter;

   str = NULL;
   if (_wgetcwd(syspath, 4096))
   {
      str = gsClocFromU2(syspath);
      gpathSetFromSystem(str); //lint !e534
   }
#else
   genter;

   str = NULL;
#endif

   greturn str;
}

/**************************************************************************************************
func: gdirGetName
**************************************************************************************************/
grlAPI const Gs *gdirGetName(Gdir const * const dir)
{
   genter;

   greturnNullIf(!dir);

   greturn dir->name;
}

/**************************************************************************************************
func: gdirGetPath
**************************************************************************************************/
grlAPI const Gpath *gdirGetPath(Gdir const * const dir)
{
   genter;

   greturnNullIf(!dir);

   greturn dir->path;
}

/**************************************************************************************************
func: gdirGetSize
**************************************************************************************************/
grlAPI GdirFileSize gdirGetSize(Gdir const * const dir)
{
   genter;

   greturn0If(!dir);

   greturn dir->size;
}

/**************************************************************************************************
func: gdirGetTimeAccessed
**************************************************************************************************/
grlAPI Gtime gdirGetTimeAccessed(Gdir const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeAccessed;
}

/**************************************************************************************************
func: gdirGetTimeCreated
**************************************************************************************************/
grlAPI Gtime gdirGetTimeCreated(Gdir const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeCreated;
}

/**************************************************************************************************
func: gdirGetTimeModified
**************************************************************************************************/
grlAPI Gtime gdirGetTimeModified(Gdir const * const dir)
{
   genter;

   greturnValIf(!dir, -1);

   greturn dir->timeModified;
}

/**************************************************************************************************
func: gdirGetType
**************************************************************************************************/
grlAPI GdirType gdirGetType(Gdir const * const dir)
{
   genter;

   greturnValIf(!dir, gdirTypeNONE);

   greturn dir->type;
}

/**************************************************************************************************
func: gdirIsExisting
**************************************************************************************************/
grlAPI Gb gdirIsExisting(const Gpath * const path)
{
   Gb      result;
   Gs   *ptemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   ptemp = gpathClocFrom(path);
   greturnFalseIf(!ptemp);

   result = gbFALSE;
   if (gpathSetToSystem(ptemp))
   {
      result = (Gb) (_waccess(gsGet(ptemp), 0) == 0); //lint !e930
   }

   gsDloc(ptemp);

   greturn result;
}

/**************************************************************************************************
func: gdirRename
**************************************************************************************************/
grlAPI Gb gdirRename(Gpath const * const path, Gpath const * const pathDestination)
{
   Gb     result;
   Gpath *tpath,
         *tpathDestination;

   genter;

   greturnFalseIf(
      !gpathIsPath(   path)            ||
      !gpathIsPath(   pathDestination) ||
      !gdirIsExisting(path));

   // Get the system paths;
   tpath             = gpathClocFrom(path);
   tpathDestination  = gpathClocFrom(pathDestination);

   gpathSetToSystem(tpath);
   gpathSetToSystem(tpathDestination);

   // move the file
   result = (Gb) (_wrename(gsGet(tpath), gsGet(tpathDestination)) == 0);

   gpathDloc(tpath);
   gpathDloc(tpathDestination);

   greturn result;
}

/**************************************************************************************************
func: gdirSetWorking
**************************************************************************************************/
grlAPI Gb gdirSetWorking(const Gpath * const path)
{
   Gs     *ptemp;

   genter;

   ptemp = gpathClocFrom(path);
   greturnFalseIf(!ptemp);

   gpathSetToSystem(ptemp); //lint !e534

   if (_wchdir(gsGet(ptemp)))
   {
      gsDloc(ptemp);

      // something wrong.
      greturn gbFALSE;
   }

   gsDloc(ptemp);

   greturn gbTRUE;
}
