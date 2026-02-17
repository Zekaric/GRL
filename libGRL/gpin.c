/******************************************************************************
file:       gpin
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
GRL PlugIN.  A very simple plugin manager.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

#if 0
/******************************************************************************
local:
variable:
******************************************************************************/
static GpinPin *_pin     = NULL; //lint !e956
static Gname   *_pinDict = NULL; //lint !e956

/******************************************************************************
global:
prototype:
******************************************************************************/
/******************************************************************************
func: gpinAdd
******************************************************************************/
grlAPI Gb gpinAdd(const Gc2 * const name, Gp * const pinStruct)
{
   Gb    result;
   Gs *stemp;

   genter;

   greturnIf(
         !_pinDict ||
         !name,
      gbFALSE);

   stemp = gsCreateFromU2(name);
   greturnIf(!stemp, gbFALSE);

   // Populate with the first plugin.
   result = gbTRUE;
   if (gnameSet(_pinDict, stemp, pinStruct) == NULL)
   {
      result = gbFALSE;
   }
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gpinAddModule
******************************************************************************/
grlAPI Gb gpinAddModule(const Gc2 * const pinFileName)
{
   HMODULE module;
   Gb    (*pinMain)(GpinPin *pin);

   genter;

   module = LoadLibraryW(pinFileName);
   greturnIf(!module, gbFALSE);

   pinMain = (Gb (*)(GpinPin *)) GetProcAddress(module, "gpinMain"); //lint !e929 !e960
   if (!pinMain)
   {
      // No gpinMain, no need to keep this think loaded.
      FreeLibrary(module); //lint !e534
      greturn gbFALSE;
   }

   // Call the gpinMain function in the plugin library.
   greturn pinMain(_pin);
}

/******************************************************************************
func: gpinGet
******************************************************************************/
grlAPI Gp *gpinGet(const Gc2 * const name)
{
   Gs *stemp;
   Gp   *pin;

   genter;

   greturnIf(
         !_pinDict ||
         !name,
      NULL);

   // fetch the pin structure.
   stemp = gsCreateFromU2(name);
   pin   = gnameGet(_pinDict, stemp);
   gsDestroy(stemp);

   greturn pin;
}

/******************************************************************************
func: gpinStart
******************************************************************************/
GpinPin *gpinStart(void)
{
   genter;

   // Create the pin structure
   _pin = gmemCreateType(GpinPin);
   stopIf(!_pin);

   _pin->Add       = gpinAdd;       //lint !e960
   _pin->AddModule = gpinAddModule; //lint !e960
   _pin->Get       = gpinGet;       //lint !e960

   // Create the dictionary that stores the structure pointers.
   _pinDict = gnameCreate(ghashSize10);
   stopIf(!_pinDict);

   // Add the plugin manager
   stopIf(!gpinAdd(gpinPIN_NAME, _pin));

   greturn _pin;

STOP:
   gpinStop();

   greturn NULL;
}

/******************************************************************************
func: gpinStop
******************************************************************************/
void gpinStop(void)
{
   genter;

   // Clean up.
   gnameDestroy(_pinDict);
   _pinDict = NULL;

   gmemDestroy(_pin);
   _pin = NULL;

   greturn;
}
#endif
