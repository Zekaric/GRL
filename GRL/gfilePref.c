/**************************************************************************************************
file:       gfilePref
author:     Robbert de Groot
copyright:  2003-2011, Robbert de Groot

description:
A library to read and write a preference file.
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
local:
function:
**************************************************************************************************/
static Gb _GetLine(GfilePref * const pref, Gs * const line);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gfilePrefCloc_
**************************************************************************************************/
grlAPI GfilePref *gfilePrefCloc_(const GfilePrefMode mode, Gp * const value)
{
   GfilePref *pref;

   genter;

   greturnNullIf(
      mode == gfilePrefModeNONE ||
      !value);

   // Create the buffer.
   pref = gmemClocType(GfilePref);
   greturnNullIf(!pref);

   if (!gfilePrefClocContent(pref, mode, value))
   {
      gfilePrefDloc(pref);
      greturn NULL;
   }

   greturn pref;
}

/**************************************************************************************************
func: gfilePrefClocContent
**************************************************************************************************/
grlAPI Gb gfilePrefClocContent(GfilePref * const pref, const GfilePrefMode mode, Gp * const value)
{
   genter;

   greturnFalseIf(
      !pref                     ||
      mode == gfilePrefModeNONE ||
      !value);

   GTYPE_SET(pref, "GPref");

   if (mode == gfilePrefModeFILE)
   {
      pref->file   = (Gfile *) value;
   }
   else
   {
      pref->buffer = (Gs *) value;
   }

   pref->key   = gsCloc();
   pref->value = gsCloc();

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfilePrefDloc
**************************************************************************************************/
grlAPI void gfilePrefDloc(GfilePref * const pref)
{
   genter;

   greturnIf(!pref);

   gfilePrefDlocContent(pref);
   gmemDloc(pref);

   greturn;
}

/**************************************************************************************************
func: gfilePrefDlocContent
**************************************************************************************************/
grlAPI void gfilePrefDlocContent(GfilePref * const pref)
{
   genter;

   greturnIf(!pref);

   gsDloc(pref->key);
   gsDloc(pref->value);

   gmemClearType(pref, GfilePref);

   greturn;
}

/**************************************************************************************************
func: gfilePrefGet

Read the next record.
**************************************************************************************************/
grlAPI Gb gfilePrefGet(GfilePref * const pref)
{
   Gs    *line,
         *begin,
         *end;
   Gb     result;
   Gindex index;

   genter;

   greturnFalseIf(!pref);

   result = gbTRUE;
   line   = gsCloc();
   begin  = NULL;
   end    = NULL;

   gsFlush(pref->key);
   gsFlush(pref->value);

   loop
   {
      gsDloc(begin);

      // Get the line.
      if (!_GetLine(pref, line))
      {
         result = gbFALSE;
         break;
      }

      // Get rid of the white space in front.
      begin = gsClocFrom(line);
      gsStrip(
         begin,
         gcStripWHITE_SPACE_LEADING | gcStripWHITE_SPACE_TRAILING);//lint !e534
      gsStrip(line, gcStripWHITE_SPACE_LEADING); //lint !e534

      // Ignore comments.
      continueIf(
         gsIsEmpty(line)               ||
         (*gsGetBegin(line) != L'-' &&
          *gsGetBegin(line) != L'='));

      // Get the key.
      // Skip white space.
      for (index = 1; ; index++)
      {
         breakIf(index >= gsGetCount(line));
         continueIf(gcIsWhiteSpace((Gc) *gsGetAt(line, index)));//lint !e571
         break;
      }

      // Read the key.
      for (;; index++)
      {
         breakIf(index >= gsGetCount(line));
         breakIf(gcIsWhiteSpace((Gc) *gsGetAt(line, index)));//lint !e571
         if (!gsAppendC(pref->key, *gsGetAt(line, index)))
         {
            result = gbFALSE;
            break;
         }
      }

      if (*gsGetBegin(line) == L'-')
      {
         // Get the value.
         // Skip white space.
         for (;; index++)
         {
            breakIf(index >= gsGetCount(line));
            continueIf(gcIsWhiteSpace((Gc) *gsGetAt(line, index)));//lint !e571
            break;
         }

         // Read the value.
         if (!gsAppendSub(pref->value, line, index, gsSubStrINDEX_END))
         {
            result = gbFALSE;
            break;
         }

         // Single line values should be shortened to remove all leading
         // and trailing white space.
         gsStrip(
            pref->value,
            gcStripWHITE_SPACE_LEADING | gcStripWHITE_SPACE_TRAILING); //lint !e534
      }
      else
      {
         loop
         {
            // Get the line.
            breakIf(!_GetLine(pref, line));

            // End of the key value pair.
            end = gsClocFrom(line);
            gsStrip(
               end,
               gcStripWHITE_SPACE_LEADING | gcStripWHITE_SPACE_TRAILING); //lint !e534
            breakIf(gsIsEqual(begin, end));
            gsDloc(end);
            end = NULL;

            // Append the line.
            // from [1] because the first character is padding.
            if (!gsAppend(pref->value, line))
            {
               result = gbFALSE;
               break;
            }
         }

         // Cursor returns and line feeds may be important to the value so leave
         // them untouched.
      }

      break;
   }

   gsDloc(begin);
   gsDloc(end);
   gsDloc(line);

   greturn result;
}

/**************************************************************************************************
func: gfilePrefGetKey
**************************************************************************************************/
grlAPI Gs *gfilePrefGetKey(const GfilePref * const pref)
{
   genter;

   greturnNullIf(!pref);

   greturn pref->key;
}

/**************************************************************************************************
func: gfilePrefGetValue
**************************************************************************************************/
grlAPI Gs *gfilePrefGetValue(const GfilePref * const pref)
{
   genter;

   greturnNullIf(!pref);

   greturn pref->value;
}

#if 0
/**************************************************************************************************
func: gfilePrefLoadStrKeyValueArray
**************************************************************************************************/
grlAPI Gb gfilePrefLoadStrKeyValueArray(GfilePref * const pref, gsKeyValueArray * const strKeyValueArray)
{
   gsKeyValue *kv;

   genter;

   greturnFalseIf(
      !pref ||
      !strKeyValueArray);

   // Populate the article with the key values.
   while (gfilePrefGet(pref))
   {
      kv = gsKeyValueCloc();

      gsKeyValueSetKey(  kv, gfilePrefGetKey(  pref));
      gsKeyValueSetValue(kv, gfilePrefGetValue(pref));

      greturnFalseIf(!gsKeyValueArrayAddEnd(strKeyValueArray, kv));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfilePrefLoadStrTable

Populate a name table.
**************************************************************************************************/
grlAPI Gb gfilePrefLoadStrTable(GfilePref * const pref, GsTable * const strTable)
{
   genter;

   greturnFalseIf(
      !pref ||
      !strTable);

   // Populate the article with the key values.
   while (gfilePrefGet(pref))
   {
      greturnFalseIf(
         !gnameSet(
            strTable,
            gfilePrefGetKey(pref),
            (Gp *) gsClocFrom(gfilePrefGetValue(pref))));
   }

   greturn gbTRUE;
}
#endif

/**************************************************************************************************
func: gfilePrefSet

Write to the preference file.
**************************************************************************************************/
grlAPI Gb gfilePrefSet(const GfilePref * const pref, const Gs * const key, const Gs * const value)
{
   Gs *random;

   genter;

   greturnFalseIf(
      !pref ||
      !value);

   //lint -save -e534
   // Write to the file.
   if (pref->file)
   {
      if (gsIsMultiline(value))
      {
         random = gsClocFromI(grandomGetI(NULL)); //lint !e960

         gfileSetC(pref->file, gcTypeU1, '=');
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, key, NULL);
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, random, NULL);
         gfileSetC(pref->file, gcTypeU1, '\n');

         gfileSetS(pref->file, gcTypeU1, value, NULL);
         gfileSetC(pref->file, gcTypeU1, '\n');

         gfileSetC(pref->file, gcTypeU1, '=');
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, key, NULL);
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, random, NULL);
         gfileSetC(pref->file, gcTypeU1, '\n');

         gsDloc(random);
      }
      else
      {
         gfileSetC(pref->file, gcTypeU1, '-');
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, key, NULL);
         gfileSetC(pref->file, gcTypeU1, ' ');
         gfileSetS(pref->file, gcTypeU1, value, NULL);
         gfileSetC(pref->file, gcTypeU1, '\n');
      }
   }
   else
   {
      if (gsIsMultiline(value))
      {
         random = gsClocFromI(grandomGetI(NULL)); //lint !e960

         gsAppendA(pref->buffer, (Char const *) "= ");
         gsAppend( pref->buffer, key);
         gsAppendA(pref->buffer, (Char const *) " ");
         gsAppend( pref->buffer, random);
         gsAppendA(pref->buffer, (Char const *) "\n");

         gsAppend( pref->buffer, value);
         gsAppendA(pref->buffer, (Char const *) "\n");

         gsAppendA(pref->buffer, (Char const *) "= ");
         gsAppend( pref->buffer, key);
         gsAppendA(pref->buffer, (Char const *) " ");
         gsAppend( pref->buffer, random);
         gsAppendA(pref->buffer, (Char const *) "\n");

         gsDloc(random);
      }
      else
      {
         gsAppendA(pref->buffer, (Char const *) "- ");
         gsAppend( pref->buffer, key);
         gsAppendA(pref->buffer, (Char const *) " ");
         gsAppend( pref->buffer, value);
         gsAppendA(pref->buffer, (Char const *) "\n");
      }
   }
   //lint -restore

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfilePrefSetCharStr
**************************************************************************************************/
grlAPI Gb gfilePrefSetCharStr(const GfilePref * const pref, const Char * const key, const Char * const value)
{
   Gb    result;
   Gs *ntemp,
        *vtemp;

   genter;

   result = gbFALSE;

   ntemp = gsClocFromA(key);
   vtemp = gsClocFromA(value);

   if (ntemp &&
       vtemp)
   {
      result = gfilePrefSet(pref, ntemp, vtemp);
   }

   gsDloc(ntemp);
   gsDloc(vtemp);

   greturn result;
}

/**************************************************************************************************
func: gfilePrefSetComment

Write a comment to the pref file.

param:
pref
   GfilePref *
   in
   the pref.

string
   Gs *
   in
   the string that is the comment.  Can be multiline.  Use only \n
   not \r\n.

return:
int
**************************************************************************************************/
grlAPI Gb gfilePrefSetComment(const GfilePref * const pref, const Gs * const value)
{
   Gindex a;

   genter;

   greturnFalseIf(
      !pref  ||
      !value ||
      !gsGetCount(value));

   //lint -save -e534
   // Write to the file.
   if (pref->file)
   {
      // We don't need to prefix with a # but I just
      // don't want to spend the effort to check if the
      // first character in a line is a - or =.  This
      // ensures the line is a comment.
      greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, '#'));
      greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, ' '));

      forCount(a, gsGetCount(value))
      {
         if (*gsGetAt(value, a) == L'\n')
         {
            greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, '\n'));
            greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, '#'));
            greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, ' '));
         }
         else
         {
            greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, (Gc) *gsGetAt(value, a)));
         }
      }

      greturnFalseIf(!gfileSetC(pref->file, gcTypeU1, '\n'));
   }
   else
   {
      greturnFalseIf(!gsAppendC(pref->buffer, '#'));
      greturnFalseIf(!gsAppendC(pref->buffer, ' '));

      forCount(a, gsGetCount(value))
      {
         if (*gsGetAt(value, a) == L'\n')
         {
            greturnFalseIf(!gsAppendC(pref->buffer, '\n'));
            greturnFalseIf(!gsAppendC(pref->buffer, '#'));
            greturnFalseIf(!gsAppendC(pref->buffer, ' '));
         }
         else
         {
            greturnFalseIf(!gsAppendC(pref->buffer, *gsGetAt(value, a)));
         }
      }

      greturnFalseIf(!gsAppendC(pref->buffer, '\n'));
   }
   //lint -restore

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfilePrefSetCommentCharStr

Write a comment to the pref file.

param:
pref
   GfilePref *
   in
   the pref.

string
   char *
   in
   the string that is the comment.  Can be multiline.  Use only \n
   not \r\n.

return:
int
**************************************************************************************************/
grlAPI Gb gfilePrefSetCommentA(const GfilePref * const pref, const Char * const value)
{
   Gb    result;
   Gs *stemp;

   genter;

   stemp = gsClocFromA(value);

   result = gfilePrefSetComment(pref, stemp);

   gsDloc(stemp);

   greturn result;
}

#if 0
/**************************************************************************************************
func: gsKeyValueArrayClocLoad
**************************************************************************************************/
grlAPI gsKeyValueArray *gsKeyValueArrayClocLoad(const Gpath * const fileName)
{
   gsKeyValueArray *skvArray;

   genter;

   skvArray = gsKeyValueArrayCloc();
   if (!gsKeyValueArrayLoad(skvArray, fileName))
   {
      gsKeyValueArrayDloc(skvArray);
      greturn NULL;
   }

   greturn skvArray;
}

/**************************************************************************************************
func: gsKeyValueArrayLoad
**************************************************************************************************/
grlAPI Gb gsKeyValueArrayLoad(gsKeyValueArray * const strKeyValueArray, const Gpath * const fileName)
{
   Gb     result;
   Gfile *file;
   GfilePref *pref;

   genter;

   greturnFalseIf(
      !strKeyValueArray ||
      !fileName);

   // open the file
   file = gfileOpen(fileName, gfileOpenREAD);
   // start the pref parser.
   pref = gfilePrefCloc(gfilePrefModeGFILE, file);

   // load the gname.
   result = gfilePrefLoadStrKeyValueArray(pref, strKeyValueArray);

   // clean up
   gfilePrefDloc(pref);
   gfileClose(file);

   greturn result;
}

/**************************************************************************************************
func: gssHashLoad
**************************************************************************************************/
grlAPI Gb gssHashLoad(GsTable * const strTable, const Gpath * const filename)
{
   Gb     result;
   Gfile *file;
   GfilePref *pref;

   genter;

   greturnFalseIf(
      !strTable ||
      !filename);

   // open the file
   file = gfileOpen(filename, gfileOpenREAD);
   // start the pref parser.
   pref = gfilePrefCloc(gfilePrefModeGFILE, file);

   // load the gname.
   result = gfilePrefLoadStrTable(pref, strTable);

   // clean up
   gfilePrefDloc(pref);
   gfileClose(file);

   greturn result;
}
#endif

/**************************************************************************************************
LOCAL: Functions
**************************************************************************************************/
/**************************************************************************************************
func: _GetLine

Get the next line.
**************************************************************************************************/
static Gb _GetLine(GfilePref * const pref, Gs * const line)
{
   Gc2 letter;

   genter;

   gsFlush(line);

   // Reading from a file.
   if (pref->file)
   {
      // Get the line.
      greturnFalseIf(!gfileGetS(pref->file, gcTypeU1, line));
   }
   else
   {
      // Copy over the next line in the string.
      for (;
           pref->bposition < gsGetCount(pref->buffer);
           pref->bposition++)
      {
         letter = *gsGetAt(pref->buffer, pref->bposition);
         greturnFalseIf(!gsAppendC(line, letter));

         breakIf(letter == (Gc2) '\n');
      }
      pref->bposition++;

      // Nothing more to read.
      greturnFalseIf(!gsGetCount(line));
   }

   greturn gbTRUE;
}
