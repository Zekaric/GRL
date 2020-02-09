/******************************************************************************
file:         Gpath
author:       Robbert de Groot
copyright:    2002-2012, Robbert de Groot
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
#include "precompiled.h"

/******************************************************************************
local:
type:
******************************************************************************/
typedef struct
{
   Gb         isFromRoot;
   GsArray   *folderList;
   Gs        *mount;
   Gs        *server;
} GpathData;

/******************************************************************************
prototype:
******************************************************************************/
static void  _DestroyPathData(   GpathData const * const path);

static Gb    _SetPathFromGpath(  GpathData       * const path, const Gpath * const value);
static Gb    _SetPathFromSystem( GpathData       * const path, const Gs    * const value);
static Gb    _SetGpathFromPath(  Gpath * const str, const GpathData * const path);
static Gb    _SetSystemFromPath( Gs    * const str, const GpathData * const path);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gpathAppend
******************************************************************************/
grlAPI Gb gpathAppend(Gpath * const path, const Gpath * const add)
{
   Gindex     index;
   Gb         result;
   GpathData  ptemp,
              atemp;
   const Gs  *str;

   genter;

   greturnFalseIf(
      !gpathIsPath(path) ||
      !gpathIsPath(add)); //lint !e960 !e9007

   gmemClearType(&ptemp, GpathData);
   gmemClearType(&atemp, GpathData);

   result = gbFALSE;
   stopIf(!_SetPathFromGpath(&ptemp, path));
   stopIf(!_SetPathFromGpath(&atemp, add));

   forCount(index, gsArrayGetCount(atemp.folderList))
   {
      str = gsCreateFrom(gsArrayGetAt(atemp.folderList, index));
      stopIf(!gsArrayAddEnd(ptemp.folderList, &str));
   }

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);
   _DestroyPathData(&atemp);

   greturn result;
}

/******************************************************************************
func: gpathGetAt_
******************************************************************************/
grlAPI Gs *gpathGetAt_(const Gpath * const path, const Gindex index)
{
   GpathData ptemp;
   Gs       *str;

   genter;

   greturnNullIf(!gpathIsPath(path));

   str = NULL;
   stopIf(!_SetPathFromGpath(&ptemp, path));

   str = gsCreateFrom(gsArrayGetAt(ptemp.folderList, index));
   
STOP:
   _DestroyPathData(&ptemp);

   greturn str;
}

/******************************************************************************
func: gpathGetCount

Get the number of elements in the path.
******************************************************************************/
grlAPI Gcount gpathGetCount(const Gpath * const path)
{
   GpathData ptemp;
   Gcount    count;

   genter;

   greturn0If(!gpathIsPath(path));

   count = 0;
   stopIf(!_SetPathFromGpath(&ptemp, path));
   
   count = gsArrayGetCount(ptemp.folderList);

STOP:
   _DestroyPathData(&ptemp);

   greturn count;
}

/******************************************************************************
func: gpathGetEnd_
******************************************************************************/
grlAPI Gs *gpathGetEnd_(const Gpath * const path)
{
   GpathData ptemp;
   Gs       *str;

   genter;

   greturnNullIf(!gpathIsPath(path));

   str = NULL;
   stopIf(!_SetPathFromGpath(&ptemp, path));

   str = gsCreateFrom(gsArrayGetEnd(ptemp.folderList));
   
STOP:
   _DestroyPathData(&ptemp);

   greturn str;
}

/******************************************************************************
func: gpathGetMount_
******************************************************************************/
grlAPI Gs *gpathGetMount_(const Gpath * const path)
{
   GpathData ptemp;
   Gs       *str;

   genter;

   greturnNullIf(!gpathIsPath(path));

   str = NULL;
   stopIf(!_SetPathFromGpath(&ptemp, path));
   
   str = gsCreateFrom(ptemp.mount);

STOP:
   _DestroyPathData(&ptemp);

   greturn str;
}

/******************************************************************************
func: gpathGetServer_
******************************************************************************/
grlAPI Gs *gpathGetServer_(const Gpath * const path)
{
   GpathData ptemp;
   Gs       *str;

   genter;

   greturnNullIf(!gpathIsPath(path));

   str = NULL;
   stopIf(!_SetPathFromGpath(&ptemp, path));
   
   str = gsCreateFrom(ptemp.server);

STOP:
   _DestroyPathData(&ptemp);

   greturn str;
}

/******************************************************************************
func: gpathIsFromRoot
******************************************************************************/
grlAPI Gb gpathIsFromRoot(const Gpath * const path)
{
   GpathData ptemp;
   Gb        btemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   btemp = gbFALSE;
   stopIf(!_SetPathFromGpath(&ptemp, path))
   
   btemp = ptemp.isFromRoot;
   
STOP:
   _DestroyPathData(&ptemp);

   greturn btemp;
}

/******************************************************************************
func: gpathIsPath
******************************************************************************/
grlAPI Gb gpathIsPath(const Gpath * const path)
{
   genter;

   // Header is missing.
   greturnFalseIf(
      !path                                        ||
      (*gsGetAt(path, 0) != (Gc2) 0xB7 &&
       *gsGetAt(path, 1) != L'p'));

   greturn gbTRUE;
}

/******************************************************************************
func: gpathIsRelative
******************************************************************************/
grlAPI Gb gpathIsRelative(const Gpath * const path)
{
   Gb        result;
   GpathData ptemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;
   if (!_SetPathFromGpath(&ptemp, path))
   {
      if (!(ptemp.isFromRoot        ||
            !gsIsEmpty(ptemp.mount) || //lint !e960 !e9007
            !gsIsEmpty(ptemp.server))) //lint !e960 !e9007
      {
         result = gbTRUE;
      }
   }
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathPop
******************************************************************************/
grlAPI Gb gpathPop(Gpath * const path)
{
   GpathData ptemp;
   Gb        result;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));

   gsDestroy(gsArrayGetEnd(ptemp.folderList)); //lint !e929
   gsArrayEraseEnd(ptemp.folderList);

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));
      
   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathPopExtension
******************************************************************************/
grlAPI Gb gpathPopExtension(Gpath * const path)
{
   Gindex location;

   genter;

   greturnFalseIf(!path);

   location = gsFindLastOfA(path, 0, ".");
   greturnFalseIf(location == gsFIND_FAIL);

   gsEraseSub(path, location, gsSubStrINDEX_END); //lint !e534

   greturn gbTRUE;
}

/******************************************************************************
func: gpathPush
******************************************************************************/
grlAPI Gb gpathPush(Gpath * const path, const Gs * const value)
{
   GpathData ptemp;
   Gb        result;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));
   stopIf(!gsArrayAddEnd(ptemp.folderList, gsCreateFrom(value)));
   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;
   
STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: 
******************************************************************************/
grlAPI Gb gpathPushU2(Gpath * const path, const wchar_t * const value)
{
   Gb  result;
   Gs *stemp;

   genter;

   stemp  = gsCreateFromU2(value);
   result = gpathPush(path, stemp);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gpathPushExtensionA
******************************************************************************/
grlAPI Gb gpathPushExtensionA(Gpath * const path, Char const * const extension)
{
   genter;

   greturnFalseIf(!path);

   gsAppendA(path, extension);

   greturn gbTRUE;
}

/******************************************************************************
func: gpathReduce
******************************************************************************/
grlAPI Gb gpathReduce(Gpath * const path)
{
   Gb        result;
   Gindex    a;
   GpathData ptemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));

   //lint -save -e850
   forCount(a, gsArrayGetCount(ptemp.folderList))
   {
      if (gsIsEqualU2(
            gsArrayGetAt(ptemp.folderList, a),
            gpathCURRENT_DIR))
      {
         gsDestroy(gsArrayGetAt(ptemp.folderList, a)); //lint !e929
         stopIf(!gsArrayEraseAt(ptemp.folderList, 1, a));
         a--;
      }

      if (gsIsEqualU2(
            gsArrayGetAt(ptemp.folderList, a),
            gpathPARENT_DIR))
      {
         gsDestroy(gsArrayGetAt(ptemp.folderList, a)); //lint !e929
         stopIf(!gsArrayEraseAt(ptemp.folderList, 1, a));
         a--;

         gsDestroy(gsArrayGetAt(ptemp.folderList, a)); //lint !e929
         stopIf(!gsArrayEraseAt(ptemp.folderList, 1, a));
         a--;
      }
   }
   //lint -restore

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));
   
   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathSetFromSystem
******************************************************************************/
grlAPI Gb gpathSetFromSystem(Gs * const path)
{
   Gb        result;
   GpathData ptemp;

   genter;

   result = gbFALSE;

   stopIf(!_SetPathFromSystem(&ptemp, path));
   
   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;
   
STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathSetIsFromRoot
******************************************************************************/
grlAPI Gb gpathSetIsFromRoot(Gpath * const path, const Gb value)
{
   GpathData ptemp;
   Gb        result;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;
   
   stopIf(!_SetPathFromGpath(&ptemp, path));
      
   ptemp.isFromRoot = value;

   gsFlush(ptemp.mount);
   gsFlush(ptemp.server);

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathSetMount
******************************************************************************/
grlAPI Gb gpathSetMount(Gpath * const path, const Gs * const value)
{
   GpathData ptemp;
   Gb        result;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));
   
   stopIf(!gsSet(ptemp.mount, value));

   ptemp.isFromRoot = gbFALSE;
   gsFlush(ptemp.server);

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathSetServer
******************************************************************************/
grlAPI Gb gpathSetServer(Gpath * const path, const Gs * const value)
{
   Gb        result;
   GpathData ptemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));
      
   stopIf(!gsSet(ptemp.server, value));

   ptemp.isFromRoot = gbFALSE;
   gsFlush(ptemp.mount);

   gsFlush(path);
   stopIf(!_SetGpathFromPath(path, &ptemp));

   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
func: gpathSetToSystem
******************************************************************************/
grlAPI Gb gpathSetToSystem(Gs * const path)
{
   Gb        result;
   GpathData ptemp;

   genter;

   greturnFalseIf(!gpathIsPath(path));

   result = gbFALSE;

   stopIf(!_SetPathFromGpath(&ptemp, path));

   gsFlush(path);
   stopIf(!_SetSystemFromPath(path, &ptemp));

   result = gbTRUE;

STOP:
   _DestroyPathData(&ptemp);

   greturn result;
}

/******************************************************************************
local: 
function: 
******************************************************************************/
/******************************************************************************
func: _DestroyPathData
******************************************************************************/
static void _DestroyPathData(const GpathData * const path)
{
   genter;

   gsArrayForEach(path->folderList, gsDestroyFunc);
   gsArrayDestroy(path->folderList);
   gsDestroy(     path->mount);
   gsDestroy(     path->server);

   greturn;
}

/******************************************************************************
func: _SetPathFromGpath
******************************************************************************/
static Gb _SetPathFromGpath(GpathData * const path, const Gpath * const value)
{
   Gindex index;
   Gc2    letter;
   Gs    *folder;

   genter;

   folder            = NULL;
   path->isFromRoot  = gbFALSE;
   path->server      = gsCreate();
   path->mount       = gsCreate();
   path->folderList  = gsArrayCreate((GrlCompareFunc) NULL, gbTRUE);

   // Get the server
   index  = 2;
   letter = *gsGetAt(value, index);
   if      (letter == gpathSERVER)
   {
      index++;
      loop
      {
         letter = *gsGetAt(value, index);
         breakIf(letter == gpathSEPARATOR);

         gsAppendC(path->server, letter); //lint !e534
      }
      index++;
   }
   else if (letter == gpathMOUNT)
   {
      index++;

      letter = *gsGetAt(value, index);
      gsAppendC(path->mount, letter); //lint !e534

      index++;
   }
   else if (letter == gpathROOT)
   {
      path->isFromRoot = gbTRUE;
      index++;
   }
   else
   {
      // None of the above.  Probably just a / for a path part.
      index--;
   }

   // Get the folders
   index++;
   loop
   {
      letter = *gsGetAt(value, index);
      if (letter == 0 ||
          letter == gpathFOLDER)
      {
         if (!gsIsEmpty(folder))
         {
            gsArrayAddEnd(path->folderList, folder); //lint !e534
         }
         else
         {
            gsDestroy(folder);
         }
         folder = NULL;

         breakIf(letter == 0);

         index++;
         continue;
      }

      if (!folder)
      {
         folder = gsCreate();
      }
      gsAppendU2(folder, &letter); //lint !e534
      index++;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: _SetPathFromSystem
******************************************************************************/
static Gb _SetPathFromSystem(GpathData * const path, const Gs * const value)
{
   Gindex index;
   Gc2   *letter;
   Gs    *folder;

   genter;

   index             = 0;
   folder            = NULL;
   path->isFromRoot  = gbFALSE;
   path->server      = gsCreate();
   path->mount       = gsCreate();
   path->folderList  = gsArrayCreate((GrlCompareFunc) NULL, gbTRUE);

   // Determine what kind of path this is.
#if grlWINDOWS == 1
   // UNC path
   letter = gsGetAt(value, 0);
   greturnFalseIf(!letter);

   if      ((*letter == gpathFOLDER_SEPARATOR_SYSTEM              ||
             *letter == gpathFOLDER_SEPARATOR_SYSTEM_ALT)            &&
            (*gsGetAt(value, 1) == gpathFOLDER_SEPARATOR_SYSTEM   ||
             *gsGetAt(value, 1) == gpathFOLDER_SEPARATOR_SYSTEM_ALT))
   {
      index = 2;
      loop
      {
         letter = gsGetAt(value, index);
         breakIf(!letter                                     ||
                 *letter == gpathFOLDER_SEPARATOR_SYSTEM     ||
                 *letter == gpathFOLDER_SEPARATOR_SYSTEM_ALT ||
                 *letter == 0);

         gsAppendC(path->server, *gsGetAt(value, index)); //lint !e534
      }
      index++;
   }
   // Full path like C:\...
   else if (gsGetAt(value, 1) &&
            *gsGetAt(value, 1) == gpathMOUNT_SUFFIX_SYSTEM)
   {
      gsAppendC(path->mount, *letter); //lint !e534
      index = 3;
   }
   // root pathing \...
   else if (*letter == gpathFOLDER_SEPARATOR_SYSTEM ||
            *letter == gpathFOLDER_SEPARATOR_SYSTEM_ALT)
   {
      path->isFromRoot = gbTRUE;
      index++;
   }

   // Get the folders.
   loop
   {
      letter = gsGetAt(value, index);
      if      (letter  == NULL ||
               *letter == 0)
      {
         if (folder)
         {
            gsArrayAddEnd(path->folderList, &folder); //lint !e534
         }
         folder = NULL;
         break;
      }

      if (!folder)
      {
         folder = gsCreate();
      }

      if (*letter == gpathFOLDER_SEPARATOR_SYSTEM     ||
          *letter == gpathFOLDER_SEPARATOR_SYSTEM_ALT)
      {
         gsArrayAddEnd(path->folderList, &folder); //lint !e534
         folder = gsCreate();
      }
      else
      {
         gsAppendC(folder, *letter); //lint !e534
      }
      index++;
   }
#else
#endif

   greturn gbTRUE; //lint !e438
}

/******************************************************************************
func: _SetGpathFromPath
******************************************************************************/
static Gb _SetGpathFromPath(Gpath * const str, const GpathData * const path)
{
   Gindex index;

   genter;

   greturnFalseIf(!gsAppendC(str, 0xB7));
   greturnFalseIf(!gsAppendC(str, 'p'));

   if      (!gsIsEmpty(path->server))
   {
      greturnFalseIf(!gsAppendC(str, gpathSERVER));
      greturnFalseIf(!gsAppend( str, path->server));
   }
   else if (!gsIsEmpty(path->mount))
   {
      greturnFalseIf(!gsAppendC(str, gpathMOUNT));
      greturnFalseIf(!gsAppend( str, path->mount));
   }
   else if (path->isFromRoot)
   {
      greturnFalseIf(!gsAppendC(str, gpathROOT));
   }

   forCount(index, gsArrayGetCount(path->folderList))
   {
      greturnFalseIf(!gsAppendC(str, gpathFOLDER));
      greturnFalseIf(!gsAppend( str, gsArrayGetAt(path->folderList, index)));
   }

   greturn gbTRUE;
}

/******************************************************************************
func: _SetSystemFromPath
******************************************************************************/
static Gb _SetSystemFromPath(Gs * const str, const GpathData * const path)
{
   Gindex index;

   genter;

#if grlWINDOWS == 1
   //lint -save -e534
   if      (!gsIsEmpty(path->server))
   {
      gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
      gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
      gsAppend( str, path->server);
      gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
   }
   else if (!gsIsEmpty(path->mount))
   {
      gsAppend( str, path->mount);
      gsAppendC(str, gpathMOUNT_SUFFIX_SYSTEM);
      gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
   }
   else if (path->isFromRoot)
   {
      gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
   }

   forCount(index, gsArrayGetCount(path->folderList))
   {
      if (index)
      {
         gsAppendC(str, gpathFOLDER_SEPARATOR_SYSTEM);
      }
      gsAppend(str, gsArrayGetAt(path->folderList, index));
   }
   //lint -restore
#else
#endif

   greturn gbTRUE;
}
