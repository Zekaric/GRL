/**************************************************************************************************
file:       gioPref
author:     Robbert de Groot
copyright:  2003, Robbert de Groot

description:
A library to read and write a preference file.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2003, Robbert de Groot

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
include
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
function:
**************************************************************************************************/
static Gb _GetLine(GioPref * const pref, Gs * const line);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioPrefClocReader_
**************************************************************************************************/
grlAPI GioPref *gioPrefClocReader_(Gio * const io)
{
   GioPref *pref;

   genter;

   greturnNullIf(!io);

   // Create the buffer.
   pref = gmemClocType(GioPref);
   greturnNullIf(!pref);

   if (!gioPrefClocReaderContent(pref, io))
   {
      gioPrefDloc(pref);
      greturn NULL;
   }

   greturn pref;
}

/**************************************************************************************************
func: gioPrefClocReaderContent
**************************************************************************************************/
grlAPI Gb gioPrefClocReaderContent(GioPref * const pref, Gio * const io)
{
   genter;

   greturnFalseIf(
      !pref ||
      !io);

   GTYPE_SET(pref, "GPref");

   pref->mode  = gioPrefModeREAD;
   pref->io    = io;
   pref->key   = gsCloc();
   pref->value = gsCloc();

   greturn
      (pref->key &&
       pref->value);
}

/**************************************************************************************************
func: gioPrefClocWriter_
**************************************************************************************************/
grlAPI GioPref *gioPrefClocWriter_(Gio * const io)
{
   GioPref *pref;

   genter;

   greturnNullIf(!io);

   // Create the buffer.
   pref = gmemClocType(GioPref);
   greturnNullIf(!pref);

   if (!gioPrefClocWriterContent(pref, io))
   {
      gioPrefDloc(pref);
      greturn NULL;
   }

   greturn pref;
}

/**************************************************************************************************
func: gioPrefClocReaderContent
**************************************************************************************************/
grlAPI Gb gioPrefClocWriterContent(GioPref * const pref, Gio * const io)
{
   genter;

   greturnFalseIf(
      !pref ||
      !io);

   GTYPE_SET(pref, "GPref");

   pref->mode  = gioPrefModeWRITE;
   pref->io    = io;
   pref->key   = gsCloc();
   pref->value = gsCloc();

   greturn
      (pref->key &&
       pref->value);
}

/**************************************************************************************************
func: gioPrefDloc
**************************************************************************************************/
grlAPI void gioPrefDloc(GioPref * const pref)
{
   genter;

   greturnIf(!pref);

   gioPrefDlocContent(pref);
   gmemDloc(pref);

   greturn;
}

/**************************************************************************************************
func: gioPrefDlocContent
**************************************************************************************************/
grlAPI void gioPrefDlocContent(GioPref * const pref)
{
   genter;

   greturnIf(!pref);

   gsDloc(pref->key);
   gsDloc(pref->value);

   gmemClearType(pref, GioPref);

   greturn;
}

/**************************************************************************************************
func: gioPrefGet

Read the next record.
**************************************************************************************************/
grlAPI Gb gioPrefGet(GioPref * const pref)
{
   Gs    *line,
         *begin,
         *end;
   Gb     result;
   Gindex index;

   genter;

   greturnFalseIf(
      !pref ||
      !pref->mode == gioPrefModeREAD);

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
         gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING);
      gsStrip(line, gsStripMethodWHITE_SPACE_LEADING);

      // Ignore comments.
      continueIf(
         gsIsEmpty(line)               ||
         (gsGetBegin(line) != L'-' &&
          gsGetBegin(line) != L'='));

      // Get the key.
      // Skip white space.
      for (index = 1; ; index++)
      {
         breakIf(index >= gsGetCount(line));
         continueIf(gcharIsWhiteSpace(gsGetAt(line, index)));
         break;
      }

      // Read the key.
      for (;; index++)
      {
         breakIf(index >= gsGetCount(line));
         breakIf(gcharIsWhiteSpace(gsGetAt(line, index)));
         if (!gsAppendLetter(pref->key, gsGetAt(line, index)))
         {
            result = gbFALSE;
            break;
         }
      }

      if (gsGetBegin(line) == L'-')
      {
         // Get the value.
         // Skip white space.
         for (;; index++)
         {
            breakIf(index >= gsGetCount(line));
            continueIf(gcharIsWhiteSpace(gsGetAt(line, index)));
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
            gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING);
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
               gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING);
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
func: gioPrefGetKey
**************************************************************************************************/
grlAPI Gs *gioPrefGetKey(const GioPref * const pref)
{
   genter;

   greturnNullIf(!pref);

   greturn pref->key;
}

/**************************************************************************************************
func: gioPrefGetValue
**************************************************************************************************/
grlAPI Gs *gioPrefGetValue(const GioPref * const pref)
{
   genter;

   greturnNullIf(!pref);

   greturn pref->value;
}

#if 0
/**************************************************************************************************
func: gioPrefLoadStrKeyValueArray
**************************************************************************************************/
grlAPI Gb gioPrefLoadStrKeyValueArray(gioPref * const pref, gsKeyValueArray * const strKeyValueArray)
{
   gsKeyValue *kv;

   genter;

   greturnFalseIf(
      !pref ||
      !strKeyValueArray);

   // Populate the article with the key values.
   while (gioPrefGet(pref))
   {
      kv = gsKeyValueCloc();

      gsKeyValueSetKey(  kv, gioPrefGetKey(  pref));
      gsKeyValueSetValue(kv, gioPrefGetValue(pref));

      greturnFalseIf(!gsKeyValueArrayAddEnd(strKeyValueArray, kv));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioPrefLoadStrTable

Populate a name table.
**************************************************************************************************/
grlAPI Gb gioPrefLoadStrTable(gioPref * const pref, GsTable * const strTable)
{
   genter;

   greturnFalseIf(
      !pref ||
      !strTable);

   // Populate the article with the key values.
   while (gioPrefGet(pref))
   {
      greturnFalseIf(
         !gnameSet(
            strTable,
            gioPrefGetKey(pref),
            (Gp *) gsClocFrom(gioPrefGetValue(pref))));
   }

   greturn gbTRUE;
}
#endif

/**************************************************************************************************
func: gioPrefSet

Write to the preference file.
**************************************************************************************************/
grlAPI Gb gioPrefSet(const GioPref * const pref, const Gs * const key, const Gs * const value)
{
   Gs     *random;
   Gcount  ckeyLen;
   Gcount  cvalLen;
   Gcount  crndLen;
   Gchar1 *ckey;
   Gchar1 *cval;
   Gchar1 *crnd;

   genter;

   greturnFalseIf(
      !pref                           ||
      !pref->mode == gioPrefModeWRITE ||
      !key);

   ckey    = gsClocGchar1(key);
   ckeyLen = gchar1GetCount(ckey);
   cval    = gsClocGchar1(value);
   cvalLen = gchar1GetCount(cval);

   if (gsIsMultiline(value))
   {
      random  = gsClocFromI(grandomGetI(NULL));
      crnd    = gsClocGchar1(random);
      crndLen = gchar1GetCount(crnd);

      pref->io->setBuffer(pref->io->repo.p, 2, (Gn1 *) '= ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, ckey);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, crndLen, crnd);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n');

      pref->io->setBuffer(pref->io->repo.p, cvalLen, cval);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n');

      pref->io->setBuffer(pref->io->repo.p, 2, (Gn1 *) '= ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, ckey);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, crndLen, crnd);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n');

      gmemDloc(crnd);
      gsDloc(random);
   }
   else
   {
      pref->io->setBuffer(pref->io->repo.p, 2, (Gn1 *) '- ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, ckey);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, cvalLen, cval);
      pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n');
   }

   gmemDloc(cval);
   gmemDloc(ckey);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioPrefSetA
**************************************************************************************************/
grlAPI Gb gioPrefSetA(const GioPref * const pref, const Char * const key, const Char * const value)
{
   Gs     *random;
   Gcount  ckeyLen;
   Gcount  cvalLen;
   Gcount  crndLen;
   Gchar1 *crnd;

   genter;

   ckeyLen = charGetCount(key);
   cvalLen = charGetCount(value);

   if (charIsMultiline(value))
   {
      random  = gsClocFromI(grandomGetI(NULL));
      crnd    = gsClocGchar1(random);
      crndLen = gchar1GetCount(crnd);

      pref->io->setBuffer(pref->io->repo.p, 2,       (Gn1 *) '= ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, (Gn1 *) key);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, crndLen, (Gn1 *) crnd);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) '\n');

      pref->io->setBuffer(pref->io->repo.p, cvalLen, (Gn1 *) value);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) '\n');

      pref->io->setBuffer(pref->io->repo.p, 2,       (Gn1 *) '= ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, (Gn1 *) key);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, crndLen, (Gn1 *) crnd);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) '\n');

      gmemDloc(crnd);
      gsDloc(random);
   }
   else
   {
      pref->io->setBuffer(pref->io->repo.p, 2,       (Gn1 *) '- ');
      pref->io->setBuffer(pref->io->repo.p, ckeyLen, (Gn1 *) key);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) ' ');
      pref->io->setBuffer(pref->io->repo.p, cvalLen, (Gn1 *) value);
      pref->io->setBuffer(pref->io->repo.p, 1,       (Gn1 *) '\n');
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioPrefSetComment

Write a comment to the pref file.

param:
pref
   GioPref *
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
grlAPI Gb gioPrefSetComment(const GioPref * const pref, const Gs * const value)
{
   Gindex a;
   Gchar1 l[4];
   Gcount lcount;

   genter;

   greturnFalseIf(
      !pref  ||
      !value ||
      !gsGetCount(value));

   // We don't need to prefix with a # but I just
   // don't want to spend the effort to check if the
   // first character in a line is a - or =.  This
   // ensures the line is a comment.
   greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 2, (Gn1 *) '# '));

   forCount(a, gsGetCount(value))
   {
      if (gsGetAt(value, a) == '\n')
      {
         greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 3, (Gn1 *) '\n# '));
      }
      else
      {
         lcount = gchar1FromGchar(gsGetAt(value, a), &l[1], &l[2], &l[3], &l[4]);
         greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, lcount, (Gn1 *) l));
      }
   }

   greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n'));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioPrefSetCommentCharStr

Write a comment to the pref file.

param:
pref
   GioPref *
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
grlAPI Gb gioPrefSetCommentA(const GioPref * const pref, const Char * const value)
{
   Gindex a;

   genter;

   greturnFalseIf(
      !pref  ||
      !value ||
      !charGetCount(value));

   // We don't need to prefix with a # but I just
   // don't want to spend the effort to check if the
   // first character in a line is a - or =.  This
   // ensures the line is a comment.
   greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 2, (Gn1 *) '# '));

   forCount(a, charGetCount(value))
   {
      if (value[a] == '\n')
      {
         greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 3, (Gn1 *) '\n# '));
      }
      else
      {
         greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) &value[a]));
      }
   }

   greturnFalseIf(!pref->io->setBuffer(pref->io->repo.p, 1, (Gn1 *) '\n'));

   greturn gbTRUE;
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
   gioPref *pref;

   genter;

   greturnFalseIf(
      !strKeyValueArray ||
      !fileName);

   // open the file
   file = gfileOpen(fileName, gfileOpenREAD);
   // start the pref parser.
   pref = gioPrefCloc(gioPrefModeGFILE, file);

   // load the gname.
   result = gioPrefLoadStrKeyValueArray(pref, strKeyValueArray);

   // clean up
   gioPrefDloc(pref);
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
   gioPref *pref;

   genter;

   greturnFalseIf(
      !strTable ||
      !filename);

   // open the file
   file = gfileOpen(filename, gfileOpenREAD);
   // start the pref parser.
   pref = gioPrefCloc(gioPrefModeGFILE, file);

   // load the gname.
   result = gioPrefLoadStrTable(pref, strTable);

   // clean up
   gioPrefDloc(pref);
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
static Gb _GetLine(GioPref * const pref, Gs * const line)
{
   Gindex index;
   Gchar1 l[4];
   Gcount count;
   Gchar  letter;

   genter;

   gsFlush(line);

   loopCount(index)
   {
      greturnFalseIf(!pref->io->getBuffer(pref->io->repo.p, 1, l));

      count = gchar1GetByteCount(l[0]);
      if (count > 1)
      {
         pref->io->getBuffer(pref->io->repo.p, count - 1, &l[1]);
      }

      gcharFromGchar1(l[1], l[2], l[3], l[4], &letter);

      gsAppendLetter(line, letter);

      breakIf(letter == (Gchar) '\n');
   }

   greturn gbTRUE;
}
