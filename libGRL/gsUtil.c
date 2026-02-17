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
#include "pch.h"

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

   greturnNullIf(!path);

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnNullIf(!file);

   str = gsCloc();
   if (str)
   {
      if (gfileGetContentS(file, str) != gbTRUE)
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
      letter = getwchar();
      breakIf(letter == WEOF);

      gsAppendLetter(str, (Gchar) letter);
   }

   greturn str;
}

/******************************************************************************
func: gsArrayClocLoad_

Convenience function to read in a complete file without the low level stuff
to worry about.
******************************************************************************/
grlAPI GvArray *gsArrayClocLoad_(Gpath const * const path)
{
   Gfile       *file;
   GvArray   *strArray;

   genter;

   greturnNullIf(!path);

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnNullIf(!file);

   strArray = gvArrayCloc("Gs Array", NULL, gbTRUE);
   if (strArray)
   {
      if (gfileGetContentSArray(file, strArray) == GiMAX)
      {
         debugHalt("gfileGetContentSArray failed because of file or strArray");
      }
   }

   gfileClose(file);

   greturn strArray;
}
