/******************************************************************************
file:       gsUtil
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
Some simple and convenient string file load routines.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "precompiled.h"

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gsClocLoad

Convenience function to read in a complete file without the low level stuff
to worry about.
******************************************************************************/
grlAPI Gs *gsClocLoad_(Gpath const * const path)
{
   Gfile *file;
   Gs  *str;

   genter;

   greturnNullIf(!gpathIsPath(path));

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnNullIf(!file);

   str = gsCloc();
   if (str)
   {
      if (gfileGetContentS(file, gcTypeU1, str) != gbTRUE)
      {
         debugHalt("gfileGetContentS failed");
      }
   }

   gfileClose(file);

   greturn str;
}

/******************************************************************************
func: gsClocInput_

Assumes no backspacing and arrow keys.
******************************************************************************/
grlAPI Gs *gsClocInput_(void)
{
   wint_t  letter;
   Gs     *str;

   genter;

   str = gsCloc();
   greturnNullIf(!str);

   loop
   {
      letter = getwchar(); //lint !e9047
      breakIf(letter == WEOF);

      gsAppendC(str, (wchar_t) letter); //lint !e534
   }

   greturn str;
}

/******************************************************************************
func: gsArrayClocLoad_

Convenience function to read in a complete file without the low level stuff
to worry about.
******************************************************************************/
grlAPI GsArray *gsArrayClocLoad_(Gpath const * const path)
{
   Gfile       *file;
   GsArray   *strArray;

   genter;

   greturnNullIf(!gpathIsPath(path));

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnNullIf(!file);

   strArray = gsArrayCloc((GrlCompareFunc) NULL, gbTRUE);
   if (strArray)
   {
      if (gfileGetContentSArray(file, gcTypeU1, strArray) == GiMAX)
      {
         debugHalt("gfileGetContentSArray failed because of file or strArray");
      }
   }

   gfileClose(file);

   greturn strArray;
}

/******************************************************************************
func: gssHashClocLoad
******************************************************************************/
grlAPI GsHashKey *gsHashKeyClocLoad_(GhashSize const hashSize,
   Gpath const * const path)
{
   Gfile       *file;
   GfilePref   *pref;
   GsHashKey   *table;
   Gs          *valueStr;
   GsKey const *skey;

   genter;

   pref = NULL;

   table = gsHashKeyCloc(hashSize);
   greturnNullIf(!table);

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   stopIf(!file);

   pref = gfilePrefCloc(gfilePrefModeFILE, file);
   stopIf(!pref);

   loop
   {
      stopIf(!gfilePrefGet(pref));

      skey     = gsKeyIntern(gfilePrefGetKey(  pref));
      valueStr = gsClocFrom( gfilePrefGetValue(pref));

      stopIf(!gsHashKeyAdd(table, skey, valueStr));
   }

STOP:
   gfilePrefDloc(pref);
   gfileClose(file);

   greturn table;
}
