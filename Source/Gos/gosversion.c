/******************************************************************************
file:       gosversion
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
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
#include "pre.h"

#if grlWINDOWS == 1
#if _MSC_VER > 1900
#include <VersionHelpers.h>
#endif
#endif

/******************************************************************************
Local Variables
******************************************************************************/

/******************************************************************************
Global Functions
******************************************************************************/
/******************************************************************************
func: gosversionGet

Get the version of the operating system.

return:
Gosversion
   The version of windows that the program is running on.
******************************************************************************/
grlAPI Gosversion gosversionGet(void)
{
   static Gosversion version = gosversionNA; //lint !e956

#if grlWINDOWS == 1
   OSVERSIONINFOEX info;
   Gi4             result;

   genter;

   greturnIf(version != gosversionNA, version);

#if _MSC_VER > 1900

   if      (IsWindows10OrGreater())
   {
      version = gosversionWIN10;
   }
   else if (IsWindows8Point1OrGreater())
   {
      version = gosversionWIN8_1;
   }
   else if (IsWindows8OrGreater())
   {
      version = gosversionWIN8;
   }
   else if (IsWindows7SP1OrGreater())
   {
      version = gosversionWIN7SP1;
   }
   else if (IsWindows7OrGreater())
   {
      version = gosversionWIN7;
   }
   else if (IsWindowsVistaSP2OrGreater())
   {
      version = gosversionWINVISTASP2;
   }
   else if (IsWindowsVistaSP1OrGreater())
   {
      version = gosversionWINVISTASP1;
   }
   else if (IsWindowsVistaOrGreater())
   {
      version = gosversionWINVISTA;
   }
   else if (IsWindowsXPSP3OrGreater())
   {
      version = gosversionWINXPSP3;
   }
   else if (IsWindowsXPSP2OrGreater())
   {
      version = gosversionWINXPSP2;
   }
   else if (IsWindowsXPSP1OrGreater())
   {
      version = gosversionWINXPSP1;
   }
   else if (IsWindowsXPOrGreater())
   {
      version = gosversionWINXP;
   }
   else if (IsWindowsServer())
   {
      version = gosversionWINSERVER;
   }
   else 
#endif
   {
      // Try calling GetVersionEx using the OSVERSIONINFOEX structure,
      // which is supported on Windows 2000.
      // If that fails, try using the OSVERSIONINFO structure.
      ZeroMemory(&info, gsizeof(OSVERSIONINFOEX));
      info.dwOSVersionInfoSize = gsizeof(OSVERSIONINFOEX);

#pragma warning(push)
#pragma warning(disable:4996)
      result = GetVersionEx((OSVERSIONINFO *) &info); //lint !e929
      if (!result)
      {
         // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
         info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

         result = GetVersionEx((OSVERSIONINFO *) &info); //lint !e929
         greturnIf(!result, gosversionNA);
      }
#pragma warning(pop)

      switch (info.dwPlatformId)
      {
      case VER_PLATFORM_WIN32_NT:

         // Test for the product.
         if (info.dwMajorVersion <= 4)
         {
            version = gosversionWINNT4;
            greturn version;
         }

         if (info.dwMajorVersion == 5 && info.dwMinorVersion == 0)
         {
            version = gosversionWIN2K;
            greturn version;
         }

         if (info.dwMajorVersion == 5 && info.dwMinorVersion == 1)
         {
            version = gosversionWINXP;
            greturn version;
         }
         break;

      case VER_PLATFORM_WIN32_WINDOWS:

         if (info.dwMajorVersion == 4 && info.dwMinorVersion == 0)
         {
            version = gosversionWIN95;
            greturn version;
         }

         if (info.dwMajorVersion == 4 && info.dwMinorVersion == 10)
         {
            version = gosversionWIN98;
            greturn version;
         }

         if (info.dwMajorVersion == 4 && info.dwMinorVersion == 90)
         {
            version = gosversionWINME;
            greturn version;
         }

         break;

      case VER_PLATFORM_WIN32s:

         version = gosversionWIN32S;
         greturn version;
      } //lint !e744

      version = gosversionNA;
   }
   greturn version;

#else
   genter;

   greturn version;
#endif
}
