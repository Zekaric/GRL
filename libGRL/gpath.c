/**************************************************************************************************
file:         Gpath
author:       Robbert de Groot
copyright:    2002, Robbert de Groot
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
type:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
static Gb       _PathFromSystem( Gpath       * const path, const Gchar1 * const value);
static Gchar1  *_SystemFromPath( Gpath const * const path);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gpathAppend
**************************************************************************************************/
grlAPI Gb gpathAppend(Gpath * const path, Gpath const * const add)
{
   Gindex     index;
   Gb         result;

   genter;

   greturnFalseIf(
      !path ||
      !add  ||
      add->isAbsolute);

   result = gbFALSE;

   forCount(index, gvArrayGetCount(add->partList))
   {
      stopIf(!gvArrayAddEnd(path->partList, gvArrayGetAt(add->partList, index)));
   }

   result = gbTRUE;

STOP:
   greturn result;
}

/**************************************************************************************************
func: gpathCloc_
**************************************************************************************************/
grlAPI Gpath *gpathCloc_(void)
{
   Gpath *path;

   genter;

   path = gmemClocType(Gpath);

   if (!gpathClocContent(path))
   {
      gpathDloc(path);
      greturn NULL;
   }

   greturn path;
}

/**************************************************************************************************
func: gpathClocContent
**************************************************************************************************/
grlAPI Gb gpathClocContent(Gpath * const path)
{
   genter;

   greturnFalseIf(!path);

   gmemClearType(path, Gpath);

   path->mount    = gsCloc();
   path->server   = gsCloc();
   path->partList = gvArrayCloc("GsArray", NULL, gbTRUE);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gpathClocAppResPath
**************************************************************************************************/
grlAPI Gpath *gpathClocAppResPath_(void)
{
   genter;

   greturn gpathClocFromSystemChar1((Gchar1 *) SDL_GetBasePath());
}

/**************************************************************************************************
func: gpathClocAppPrefPath
**************************************************************************************************/
grlAPI Gpath *gpathClocAppPrefPath_(Gs const * const orgName, Gs const * const appName)
{
   Gpath    *path;
   Gchar1   *orgNameChar1,
            *appNameChar1;

   genter;

   orgNameChar1 = gsClocGchar1(orgName);
   appNameChar1 = gsClocGchar1(appName);

   path = gpathClocFromSystemChar1((Gchar1 *) SDL_GetPrefPath((char *) orgNameChar1, (char *) appNameChar1));

   gmemDloc(appNameChar1);
   gmemDloc(orgNameChar1);

   greturn path;
}

/**************************************************************************************************
func: gpathClocCurrent_

Get the current working directory.
**************************************************************************************************/
grlAPI Gpath *gpathClocCurrent_(void)
{
   genter;

   greturn gpathClocFromSystemChar1((Gchar1 *) SDL_GetCurrentDirectory());
}

/**************************************************************************************************
func: gpathClocFrom_
**************************************************************************************************/
grlAPI Gpath *gpathClocFrom_(Gpath const * const path)
{
   Gindex index;
   Gcount count;
   Gpath *ptemp;
   Gs    *stemp;

   genter;

   ptemp = gpathCloc();

   ptemp->isAbsolute = path->isAbsolute;
   gsSet(ptemp->mount,  path->mount);
   gsSet(ptemp->server, path->server);

   count = gvArrayGetCount(path->partList);
   forCount(index, count)
   {
      stemp = gsClocFrom(gvGetS(gvArrayGetAt(path->partList, index)));
      gvArrayAddEnd(ptemp->partList, gvFromP(stemp));
   }

   greturn ptemp;
}

/**************************************************************************************************
func: gpathClocFromSystemChar1
**************************************************************************************************/
grlAPI Gpath *gpathClocFromSystemChar1_(Gchar1 const * const sysPath)
{
   Gpath *path;

   genter;

   path = gpathCloc();
   greturnNullIf(!path);

   if (!_PathFromSystem(path, sysPath))
   {
      gpathDloc(path);
      greturn NULL;
   }

   greturn path;
}

/**************************************************************************************************
func: gpathClocSystemChar1
**************************************************************************************************/
grlAPI Gchar1 *gpathClocSystemChar1_(Gpath const * const path)
{
   genter;

   greturnNullIf(!path);

   greturn _SystemFromPath(path);
}

/**************************************************************************************************
func: gpathClocUserFolder
**************************************************************************************************/
grlAPI Gpath *gpathClocUserFolder_(GpathUserFolder folder)
{
   genter;

   greturn gpathClocFromSystemChar1((Gchar1 *) SDL_GetUserFolder((SDL_Folder) folder));
}

/**************************************************************************************************
func: gpathDloc
**************************************************************************************************/
grlAPI void gpathDloc(Gpath * const path)
{
   genter;

   greturnIf(!path);

   gpathDlocContent(path);

   gmemDloc(path);

   greturn;
}

/**************************************************************************************************
func: gpathDlocContent
**************************************************************************************************/
grlAPI void gpathDlocContent(Gpath * const path)
{
   genter;

   greturnIf(!path);

   gsDloc(        path->mount);
   gsDloc(        path->server);
   gvArrayForEach(path->partList, gsDlocContainer);
   gvArrayDloc(   path->partList);

   greturn;
}

/**************************************************************************************************
func: gpathGetAt
**************************************************************************************************/
grlAPI Gs const *gpathGetAt(Gpath const * const path, const Gindex index)
{
   genter;

   greturnNullIf(!path);

   greturn gvGetS(gvArrayGetAt(path->partList, index));
}

/**************************************************************************************************
func: gpathGetCount

Get the number of elements in the path.
**************************************************************************************************/
grlAPI Gcount gpathGetCount(Gpath const * const path)
{
   genter;

   greturn0If(!path);

   greturn gvArrayGetCount(path->partList);
}

/**************************************************************************************************
func: gpathGetEnd
**************************************************************************************************/
grlAPI Gs const *gpathGetEnd(Gpath const * const path)
{
   genter;

   greturnNullIf(!path);

   greturn gvGetS(gvArrayGetEnd(path->partList));
}

/**************************************************************************************************
func: gpathGetMount
**************************************************************************************************/
grlAPI Gs const *gpathGetMount(Gpath const * const path)
{
   genter;

   greturnNullIf(!path);

   greturn path->mount;
}

/**************************************************************************************************
func: gpathGetServer
**************************************************************************************************/
grlAPI Gs const *gpathGetServer(Gpath const * const path)
{
   genter;

   greturnNullIf(!path);

   greturn path->server;
}

/**************************************************************************************************
func: gpathIsAbsolute
**************************************************************************************************/
grlAPI Gb gpathIsAbsolute(Gpath const * const path)
{
   genter;

   greturnFalseIf(!path);

   greturn path->isAbsolute;
}

/**************************************************************************************************
func: gpathPop
**************************************************************************************************/
grlAPI Gb gpathPop(Gpath * const path)
{
   genter;

   greturnFalseIf(!path);

   gsDloc(gvGetS(gvArrayGetEnd(path->partList)));

   greturn gvArrayEraseEnd(path->partList, 1);
}

/**************************************************************************************************
func: gpathPopExtension
**************************************************************************************************/
grlAPI Gb gpathPopExtension(Gpath * const path)
{
   Gindex location;
   Gs    *part;

   genter;

   greturnFalseIf(!path);

   part = gvGetS(gvArrayGetEnd(path->partList));

   location = gsFindLastOfChar(part, GindexMAX, gpathFILE_SEPARATOR);
   greturnFalseIf(location == GindexERROR);

   gsEraseAt(part, GcountMAX, location);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gpathPush
**************************************************************************************************/
grlAPI Gb gpathPush(Gpath * const path, Gs const * const value)
{
   genter;

   greturnFalseIf(!path);

   greturn gvArrayAddEnd(path->partList, gvFromP(gsClocFrom(value)));
}

/**************************************************************************************************
func: gpathPushExtension
**************************************************************************************************/
grlAPI Gb gpathPushExtension(Gpath * const path, Gs const * const extension)
{
   Gs *part;

   genter;

   greturnFalseIf(!path);

   part = gvGetS(gvArrayGetEnd(path->partList));

   greturnFalseIf(!gsAppendLetter(part, gpathFILE_SEPARATOR));
   greturn        gsAppend(       part, gsClocFrom(extension)) != NULL;
}

/**************************************************************************************************
func: gpathReduce
**************************************************************************************************/
grlAPI Gb gpathReduce(Gpath * const path)
{
   Gb     result;
   Gindex index;

   genter;

   greturnFalseIf(!path);

   result = gbFALSE;

   forCount(index, gvArrayGetCount(path->partList))
   {
#if 0 //TODO
      // If part of a folder then this is nothing part.
      if (gsIsEqual(gvGetS(gvArrayGetAt(path->partList, index)), gpathCURRENT_DIR))
      {
         if (index != 0)
         {
            gsDloc(gvGetS(gvArrayGetAt(path->partList, index)));
            stopIf(!gvArrayEraseAt(path->partList, index));
            index--;
         }
      }

      // Pop off some previous parts.
      if (gsIsEqual(gvGetS(gvArrayGetAt(path->partList, index)), gpathPARENT_DIR))
      {
         // Can't allow a parent directory reference as the first folder.
         stopIf(index == 1);

         gsDloc(gvGetS(gvArrayGetAt(path->partList, index)));
         stopIf(!gvArrayEraseAt(path->partList, 1, index));
         index--;

         gsDloc(gvGetS(gvArrayGetAt(path->partList, index)));
         stopIf(!gvArrayEraseAt(path->partList, 1, index));
         index--;
      }
#endif
   }

   result = gbTRUE;

#if 0
   STOP:
#endif

   greturn result;
}

/**************************************************************************************************
func: gpathSetMount
**************************************************************************************************/
grlAPI Gb gpathSetMount(Gpath * const path, const Gs * const value)
{
   genter;

   greturnFalseIf(!path);

   greturn gsSet(path->mount, value) != NULL;
}

/**************************************************************************************************
func: gpathSetServer
**************************************************************************************************/
grlAPI Gb gpathSetServer(Gpath * const path, const Gs * const value)
{
   genter;

   greturnFalseIf(!path);

   greturn gsSet(path->server, value) != NULL;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _SetPathFromSystem
**************************************************************************************************/
static Gb _PathFromSystem(Gpath * const path, Gchar1 const * const sysPath)
{
   Gindex index;
   Gchar  letter;
   Gs    *sSysPath,
         *part;

   genter;

   sSysPath = gsClocFromGchar1(sysPath);

   index             = 0;
   part              = NULL;
   path->isAbsolute  = gbFALSE;

   gsFlush(       path->server);
   gsFlush(       path->mount);
   gvArrayForEach(path->partList, gsDlocContainer);
   gvArrayFlush(  path->partList);

   // Determine what kind of path this is.

   // UNC full path "//..." or "\\..."
   letter = gsGetAt(sSysPath, 0);
   greturnFalseIf(!letter);

   if      ((letter               == gpathDIR_SEPARATOR_SYSTEM ||
             letter               == gpathDIR_SEPARATOR_SYSTEM_ALT) &&
            (gsGetAt(sSysPath, 1) == gpathDIR_SEPARATOR_SYSTEM ||
             gsGetAt(sSysPath, 1) == gpathDIR_SEPARATOR_SYSTEM_ALT))
   {
      index = 2;
      loop
      {
         letter = gsGetAt(sSysPath, index);
         breakIf(
            !letter                                    ||
            letter == gpathDIR_SEPARATOR_SYSTEM     ||
            letter == gpathDIR_SEPARATOR_SYSTEM_ALT ||
            letter == 0);

         gsAppendLetter(path->server, gsGetAt(sSysPath, index));
      }

      path->isAbsolute = gbTRUE;

      index++;
   }
   // Windows drive letter full path.  "C:\..." or "C:/..."
   else if (gsGetAt(sSysPath, 1) &&
            gsGetAt(sSysPath, 1) == gpathMOUNT_SUFFIX_SYSTEM)
   {
      gsAppendLetter(path->mount, letter);

      path->isAbsolute = gbTRUE;

      index = 3;
   }
   // root pathing "\..." or "/..."
   else if (letter == gpathDIR_SEPARATOR_SYSTEM ||
            letter == gpathDIR_SEPARATOR_SYSTEM_ALT)
   {
      path->isAbsolute = gbTRUE;

      index++;
   }
   // Relative pathing ".\" or "./"
   else if (letter == gpathCURRENT_DIR &&
            gsGetAt(sSysPath, 1)       &&
            (gsGetAt(sSysPath, 1) == gpathDIR_SEPARATOR_SYSTEM ||
             gsGetAt(sSysPath, 1) == gpathDIR_SEPARATOR_SYSTEM_ALT))
   {
      // Relative path.
      index = 2;
   }

   // Get the directories and file.
   loop
   {
      letter = gsGetAt(sSysPath, index++);
      if      (letter == 0)
      {
         if (part)
         {
            gvArrayAddEnd(path->partList, gvFromP(part));
         }
         break;
      }

      if (!part)
      {
         part = gsCloc();
      }

      if (letter == gpathDIR_SEPARATOR_SYSTEM     ||
          letter == gpathDIR_SEPARATOR_SYSTEM_ALT)
      {
         gvArrayAddEnd(path->partList, gvFromP(part));
         part = gsCloc();
      }
      else
      {
         gsAppendLetter(part, letter);
      }
   }

   // Clean up.
   gsDloc(sSysPath);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _SetSystemFromPath
**************************************************************************************************/
static Gchar1 *_SystemFromPath(Gpath const * const path)
{
   Gindex    index;
   Gs       *spath;
   Gchar1   *u1Path;

   genter;

   spath = gsCloc();

   // UNC full path. Windows "\\", Other "//"
   if      (!gsIsEmpty(path->server))
   {
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
      gsAppend(      spath, path->server);
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
   }
   // Windows drive letter full path. "C:\"
   else if (!gsIsEmpty(path->mount))
   {
      gsAppend(      spath, path->mount);
      gsAppendLetter(spath, gpathMOUNT_SUFFIX_SYSTEM);
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
   }
   // Unix from root full path. Windows "\", Other "/"
   else if (path->isAbsolute)
   {
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
   }
   // Relative path.
   else
   {
      gsAppendLetter(spath, gpathCURRENT_DIR);
      gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
   }

   forCount(index, gvArrayGetCount(path->partList))
   {
      if (index)
      {
         gsAppendLetter(spath, gpathDIR_SEPARATOR_SYSTEM);
      }
      gsAppend(spath, gvGetS(gvArrayGetAt(path->partList, index)));
   }

   u1Path = gsClocGchar1(spath);

   gsDloc(spath);

   greturn u1Path;
}
