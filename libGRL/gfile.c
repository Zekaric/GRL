/**************************************************************************************************
file:       gfile
author:     Robbert de Groot
copyright:  2000, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2000, Robbert de Groot

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
function:
**************************************************************************************************/
static void _Prep(Gfile * const file, GfileOpStatus const status);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gfileClose
**************************************************************************************************/
grlAPI void gfileClose(Gfile * const file)
{
   genter;

   greturnIf(
      !file ||
      !file->stream);

   // Make sure the file makes it to disk.
   if (!SDL_FlushIO(file->stream))
   {
      debugHalt("gfile: Flush failed");
   }

   // Close the file.
   if (!SDL_CloseIO(file->stream))
   {
      debugHalt("gfile: Close failed");
   }

   gmemDloc(file);

   greturn;
}

/**************************************************************************************************
func: gfileCreateFromStrArray
**************************************************************************************************/
grlAPI GfileCreate gfileCreateFromStrArray(Gpath const * const path, GvArray const * const lines)
{
   Gi4          count;
   Gfile       *file;
   GfileCreate  result;

   genter;

   greturnValIf(!path, gfileCreateBAD_PATH);

   file = gfileOpen(path, gfileOpenModeREAD_WRITE_NEW);
   greturnValIf(!file, gfileCreateFAILED_TO_OPEN_FILE);

   result = gfileCreateSUCCESS;
   count  = gfileSetSArray(file, lines);
   if (count != gvArrayGetCount(lines))
   {
      result = gfileCreateFAILED_TO_COMPLETELY_WRITE_FILE;
      debugHalt("Lines written does not match lines to be written.");
   }

   gfileClose(file);

   greturn result;
}

/**************************************************************************************************
func: gfileGet

Load in a bunch of bytes

return:
int
   0 - Nothing left to read.[\n]
   -1 - File wasn't openned for reading or reading not permitted.[\n]
   X - Number of characters read.
**************************************************************************************************/
grlAPI Gcount gfileGet(Gfile * const file, Gcount const count, Gp * const buffer)
{
   size_t readCount;

   genter;

   greturn0If(
      !file          ||
      !file->stream  ||
      !buffer        ||
      count == 0);

   // This set position call should allow us to call this function
   // right after a write function.
   _Prep(file, gfileOpStatusREADING);

   file->opStatus = gfileOpStatusREADING;

   readCount = SDL_ReadIO(file->stream, buffer, (size_t) count);

   if (readCount != count)
   {
      file->isAtEnd = gbTRUE;
      debugHalt("gfile: Read failed");
      greturn 0;
   }

   greturn (Gcount) readCount;
}

/**************************************************************************************************
func: gfileGetChar

Read in a gc up to and including a line feed.  The
line may not be null terminated.  It will read at most count chars.

return:
int
   0  - Nothing left to read.[\n]
   1  - Number of characters read.
**************************************************************************************************/
grlAPI Gcount gfileGetChar(Gfile * const file, Gchar * const letter)
{
   Gcount result,
          byteCount;
   Gchar1 c[4];

   genter;

   greturn0If(
      !file          ||
      !file->stream  ||
      !letter);

   result = 0;

   // This set position call should allow us to call this function
   // right after a write function.
   _Prep(file, gfileOpStatusREADING);

   file->opStatus = gfileOpStatusREADING;

   *letter = 0;

   // Read a character.
   result    = gfileGet(file, 1, c);
   greturn0If(!result);

   byteCount = gchar1GetByteCount(c[0]);
   if (byteCount > 1)
   {
      result = gfileGet(file, byteCount - 1, &(c[1]));
      greturn0If(!result);
   }

   // Convert to Gchar.
   gcharFromGchar1(c[0], c[1], c[2], c[3], letter);

   greturn byteCount;
}

/**************************************************************************************************
func: gfileGet2

Read in 2 byte values.  Assume file is BE order.  This function will byte swap if system is LE.
**************************************************************************************************/
grlAPI Gb gfileGet2(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn2   *p;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count <= 0);

   if (gfileGet(file, 2 * count, i) != 2 * count)
   {
      debugHalt("gfileGet: didn't real all the bytes");
   }

   // Byte order swapping.
   p = (Gn2 *) i;
   forCount(a, count)
   {
      gswap2(&p[a]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileGet4

Read in 4 byte values.  Assume file is BE order.  This function will byte swap if system is LE.
**************************************************************************************************/
grlAPI Gb gfileGet4(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn4   *p;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count <= 0);

   if (gfileGet(file, 4 * count, i) != 4 * count)
   {
      debugHalt("gfileGet: didn't real all the bytes");
   }

   // Byte order swapping.
   p = (Gn4 *) i;
   forCount(a, count)
   {
      gswap4(&p[a]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileGet8

Read in 8 byte values.  Assume file is BE order.  This function will byte swap if system is LE.
**************************************************************************************************/
grlAPI Gb gfileGet8(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn8   *p;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count == 0);

   if (gfileGet(file, 8 * count, i) != 8 * count)
   {
      debugHalt("gfileGet: didn't real all the bytes");
   }

   // Byte order swapping.
   p = (Gn8 *) i;
   forCount(a, count)
   {
      gswap8(&p[a]);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileGetS

Read in a line of chars up to and including a line feed.  This assumes file is in UTF8 and UNIX
text file (single \n to terminate a line.)

return:
int
   0  - Nothing read.[\n]
   X  - Number of characters read.
**************************************************************************************************/
grlAPI Gcount gfileGetS(Gfile * const file, Gs * const str)
{
   Gindex a;
   Gcount result;
   Gchar  c;

   genter;

   greturn0If(
      !file          ||
      !file->stream  ||
      !str);

   // Init
   result = 0;

   // This set position call should allow us to call this function
   // right after a write function.
   _Prep(file, gfileOpStatusREADING);

   file->opStatus = gfileOpStatusREADING;

   a = 0;
   gsFlush(str);

   // Read in the line
   loop
   {
      // Init.
      c = 0;

      // Read a character.
      result = gfileGetChar(file, &c);
      if (result > 0)
      {
         if (!gsAddEnd(str, c))
         {
            debugHalt("gsAddEnd: failed");
            goto gfileGetSERROR;
         }
      }

      // All done.
      breakIf(result == 0);

      a++;

      // Check for linefeed
      breakIf(c == '\n');
   }

gfileGetSERROR:
   greturn a;
}

/**************************************************************************************************
func: gfileGetContent

Read the entire file.
**************************************************************************************************/
grlAPI Gb gfileGetContent(Gfile * const file, Gcount * const count, Gn1 ** const buffer)
{
   GfileCount   size;
   Gn1         *buf;

   genter;

   *count  = 0;
   *buffer = NULL;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !buffer);

   size = (GfileCount) SDL_GetIOSize(file->stream);
   greturnFalseIf(
      size <= 0 || GcountMAX <= size);

   buf = gmemClocTypeArray(Gn1, (Gsize) size);
   greturnFalseIf(!buf);

   if (gfileGet(file, (Gcount) size, buf) != size)
   {
      gmemDloc(buf);
      greturn gbFALSE;
   }

   *buffer = buf;
   *count  = (Gcount) size;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileGetContentS

Read in entire file into one Gs.
**************************************************************************************************/
grlAPI Gb gfileGetContentS(Gfile * const file, Gs * const str)
{
   Gcount result;
   Gb     returnResult,
          first;
   Gchar  c;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !str);

   first = gbTRUE;

   returnResult = gbTRUE;
   loop
   {
      // read in a line.
      result = gfileGetChar(file, &c);
      breakIf(result == 0);

      gsAddEnd(str, c);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileGetContentSArray

Read in the entire file and put the lines into an array.
**************************************************************************************************/
grlAPI Gcount gfileGetContentSArray(Gfile * const file, GvArray * const strArray)
{
   Gcount count;
   Gs    *stemp;

   genter;

   greturn0If(
      !file          ||
      !file->stream  ||
      !strArray);

   count = 0;
   loop
   {
      // Cloc the string.
      stemp = gsCloc();

      // All done.
      if (gfileGetS(file, stemp) == 0)
      {
         gsDloc(stemp);
         break;
      }

      // Append to the lines.
      if (!gvArrayAddEnd(strArray, gvFromP(stemp)))
      {
         debugHalt("gsArrayAddEnd: failed");
         break;
      }
      count++;
   }

   greturn count;
}

/**************************************************************************************************
func: gfileGetPosition

Get the current file position.

return:
Gi8
   -1 - Failed.[\n]
   X  - The file position.
**************************************************************************************************/
grlAPI GfileIndex gfileGetPosition(Gfile * const file)
{
   genter;

   greturn0If(
      !file ||
      !file->stream);

   // Return the file position.
   greturn SDL_TellIO(file->stream);
}

/**************************************************************************************************
func: gfileGetSize

Returns the size of the file.

return:
Gi8
   The size of the file.
**************************************************************************************************/
grlAPI GfileIndex gfileGetSize(Gfile * const file)
{
   genter;

   greturn0If(
      !file ||
      !file->stream);

   greturn SDL_GetIOSize(file->stream);
}

/**************************************************************************************************
func: gfileIsAtEnd
**************************************************************************************************/
grlAPI Gb gfileIsAtEnd(Gfile * const file)
{
   genter;

   greturnTrueIf(!file);

   greturn file->isAtEnd;
}

/**************************************************************************************************
func: gfileLoadContent
**************************************************************************************************/
grlAPI Gb gfileLoadContent(Gpath const * const path, Gcount * const count, Gn1 ** const buffer)
{
   Gfile *file;
   Gb     result;

   genter;

   greturnFalseIf(
      !path  ||
      !count ||
      !buffer);

   *count  = 0;
   *buffer = NULL;

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnFalseIf(!file);

   result = gfileGetContent(file, count, buffer);

   gfileClose(file);

   greturn result;
}

/**************************************************************************************************
func: gfileOpen_

Open a file

return:
Gfile *
   NULL - Failed[\n]
   X    - File open and ready to work with.
**************************************************************************************************/
Gfile *gfileOpen_(Gpath const * const path, GfileOpenMode const mode)
{
   Gfile    *file;
   Gchar1   *u1Path;

   genter;

   greturnNullIf(!path);

   // Initialize
   file = gmemClocType(Gfile);
   greturnNullIf(!file);

   GTYPE_SET(file, "Gfile");

   u1Path = gpathClocSystemChar1(path);

   // Open the file based on the provided mode.
   switch(mode)
   {
   case gfileOpenModeREAD_ONLY:
      file->stream = SDL_IOFromFile((char *) u1Path, "rb");
      break;

   case gfileOpenModeREAD_WRITE:
      file->stream = SDL_IOFromFile((char *) u1Path, "rb+");
      break;

   case gfileOpenModeREAD_WRITE_NEW:
      file->stream = SDL_IOFromFile((char *) u1Path, "wb");
      break;

   case gfileOpenModeAPPEND:
      file->stream = SDL_IOFromFile((char *) u1Path, "ab+");
      break;
   }

   gmemDloc(u1Path);

   if (!file->stream)
   {
      gmemDloc(file);
      greturn NULL;
   }

   greturn file;
}

/**************************************************************************************************
func: gfileOpenMem
**************************************************************************************************/
Gfile *gfileOpenMem_(GfileCount size, void *mem)
{
   Gfile *file;

   genter;

   greturnNullIf(
      !mem ||
      size <= 0);

   file = gmemClocType(Gfile);
   greturnNullIf(!file);

   file->stream = SDL_IOFromMem(mem, (size_t) size);
   if (!file->stream)
   {
      gmemDloc(file);
      greturn NULL;
   }

   greturn file;
}

/**************************************************************************************************
func: gfileSet

Write out a bunch of bytes
**************************************************************************************************/
grlAPI Gb gfileSet(Gfile * const file, Gcount const count, Gp const * const buffer,
   Gcount * const writeCount)
{
   size_t result;

   genter;

   greturnFalseIf(
      !file         ||
      !file->stream ||
      !buffer       ||
      count == 0);

   // This set position call should allow us to call this function
   // right after a read function.
   _Prep(file, gfileOpStatusWRITING);

   file->opStatus = gfileOpStatusWRITING;

   result = SDL_WriteIO(file->stream, buffer, (size_t) count);

   if (writeCount)
   {
      *writeCount = (Gcount) gMAX(result, 0);
   }

   if (*writeCount != count)
   {
      debugHalt("gfileSet: write did not write everything.");
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileSet2

Write out an array 2 Byte values.  Byte swap if system is LE and file is assumed to be BE.
**************************************************************************************************/
grlAPI Gb gfileSet2(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn2   *p;
   Gb     result;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count <= 0);

   p = (Gn2 *) i;
   forCount(a, count)
   {
      gswap2(&p[a]);
   }

   result = gbTRUE;
   if (!gfileSet(file, 2 * count, i, NULL))
   {
      debugHalt("gfileSet: failed, written size != buffer size");
      result = gbFALSE;
   }

   forCount(a, count)
   {
      gswap2(&p[a]);
   }

   greturn result;
}

/**************************************************************************************************
func: gfileSet4

Write out an array 4 Byte values.  Byte swap if system is LE and file is assumed to be BE.
**************************************************************************************************/
grlAPI Gb gfileSet4(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn4   *p;
   Gb     result;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count == 0);

   p = (Gn4 *) i;
   forCount(a, count)
   {
      gswap4(&p[a]);
   }

   result = gbTRUE;
   if (!gfileSet(file, 4 * count, i, NULL))
   {
      debugHalt("gfileSet: failed, written size != buffer size");
      result = gbFALSE;
   }

   forCount(a, count)
   {
      gswap4(&p[a]);
   }

   greturn result;
}

/**************************************************************************************************
func: gfileSet8

Write out an array 8 Byte values.  Byte swap if system is LE and file is assumed to be BE.
**************************************************************************************************/
grlAPI Gb gfileSet8(Gfile * const file, Gcount const count, Gp * const i)
{
   Gindex a;
   Gn8   *p;
   Gb     result;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !i             ||
      count == 0);

   p = (Gn8 *) i;
   forCount(a, count)
   {
      gswap8(&p[a]);
   }

   result = gbTRUE;
   if (!gfileSet(file, 8 * count, i, NULL))
   {
      debugHalt("gfileSet failed, written size != buffer size");
      result = gbFALSE;
   }

   forCount(a, count)
   {
      gswap8(&p[a]);
   }

   greturn result;
}

/**************************************************************************************************
func: gfileSetChar

Write a line of Gcs to a file.  Writes up to the null terminator
or at max count letters.  This will not send out a new line to the
file.
**************************************************************************************************/
grlAPI Gb gfileSetChar(Gfile * const file, Gchar const letter)
{
   Gcount count;
   Gb     result;
   Gchar1 c1[4];

   genter;

   greturn0If(
      !file ||
      !file->stream);

   result = gbFALSE;
   count  = gchar1FromGchar(letter, &c1[0], &c1[1], &c1[2], &c1[3]);
   result = gfileSet(file, count, c1, NULL);

   // Error
   greturn0If(!result);

   greturn count != 0;
}

/**************************************************************************************************
func: gfileSetS

Write a Gs to a file.

return:
int
   0 - Failed.[\n]
   X - Number of characters written.
**************************************************************************************************/
grlAPI Gb gfileSetS(Gfile * const file, Gs const * const line)
{
   Gindex   index;
   Gcount   count;
   Gb       result;

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      !line);

   result = gbFALSE;
   count  = gsGetCount(line);
   forCount(index, count)
   {
      result = gfileSetChar(file, gsGetAt(line, index));
      breakIf(!result);
   }

   greturn result;
}

/**************************************************************************************************
func: gfileSetSArray

Write a lines of Gcs to a file.

return:
int
   0 - Failed.[\n]
   X - Number of lines written.
**************************************************************************************************/
grlAPI Gb gfileSetSArray(Gfile * const file, GvArray const * const lines)
{
   Gindex   index;
   Gcount   count;
   Gb       result;

   genter;

   greturn0If(
      !file          ||
      !file->stream  ||
      !lines);

   result = gbFALSE;
   count  = gvArrayGetCount(lines);
   forCount(index, count)
   {
      result = gfileSetS(file, gvGetS(gvArrayGetAt(lines, index)));
      breakIf(!result);
   }

   greturn result;
}

/**************************************************************************************************
func: gfileSetPosition

Set the file position.
**************************************************************************************************/
grlAPI GfileSetPosition gfileSetPosition(Gfile * const file, Gposition const pos,
   GfileOffset const offset)
{
   SDL_IOWhence whence;

   genter;

   greturnValIf(
         !file ||
         !file->stream,
      gfileSetPositionBAD_FILE);

   // Prevent bad moves
   greturnValIf(
         pos == gpositionSTART &&
         offset < 0,
      gfileSetPositionBAD_POSITION);

   // Perform the seek.
   switch (pos)
   {
   case gpositionCURRENT: whence = SDL_IO_SEEK_CUR; break;
   case gpositionEND:     whence = SDL_IO_SEEK_END; break;
   case gpositionSTART:
   default:               whence = SDL_IO_SEEK_SET; break;
   }

   SDL_SeekIO(file->stream, offset, whence);

   file->opStatus = gfileOpStatusANY;
   file->isAtEnd  = gbFALSE;
   if (offset == 0 &&
       pos    == gpositionEND)
   {
      file->isAtEnd = gbTRUE;
   }

   greturn gfileSetPositionSUCCESS;
}

/**************************************************************************************************
func: gfileSetValue

Write out a bunch of bytes
**************************************************************************************************/
grlAPI Gb gfileSetValue(Gfile * const file, Gcount const count, Gn1 const value,
   Gcount * const writeCount)
{
#define gfileSetValueBUFFER_SIZE 2048

   Gindex       index;
   GfileCount   wCount,
                countSent,
                countRemaining;
   Gn1          buffer[gfileSetValueBUFFER_SIZE];

   genter;

   greturnFalseIf(
      !file          ||
      !file->stream  ||
      count == 0);

   wCount = -1;

   forCount(index, gfileSetValueBUFFER_SIZE)
   {
      buffer[index] = value;
   }

   // This set position call should allow us to call this function
   // right after a read function.
   _Prep(file, gfileOpStatusWRITING);

   file->opStatus = gfileOpStatusWRITING;

   countSent      = 0;
   countRemaining = count;
   loop
   {
      breakIf(countRemaining < 0);

      if (countRemaining > gfileSetValueBUFFER_SIZE)
      {
         wCount      = SDL_WriteIO(file->stream, buffer, gfileSetValueBUFFER_SIZE);
         countSent  += wCount;
         breakIf(wCount != gfileSetValueBUFFER_SIZE);
      }
      else
      {
         wCount       = SDL_WriteIO(file->stream, buffer, countRemaining);
         countSent   += wCount;
         breakIf(wCount != countRemaining);
      }

      countRemaining -= gfileSetValueBUFFER_SIZE;
   }

   if (writeCount)
   {
      *writeCount = (Gcount) gMAX(countSent, 0);
   }

   if (countSent != count)
   {
      debugHalt("_write did not write everything.");
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileStoreContent
**************************************************************************************************/
grlAPI Gb gfileStoreContent(Gpath const * const path, Gcount const count, Gn1 const * const buffer)
{
   Gfile *file;
   Gb     result;
   Gcount writeCount;

   genter;

   greturnFalseIf(
      !path  ||
      !count ||
      !buffer);

   file = gfileOpen(path, gfileOpenModeREAD_WRITE_NEW);
   greturnFalseIf(!file);

   result = gfileSet(file, count, buffer, &writeCount);

   gfileClose(file);

   greturn result;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _Prep

Prepare the file for reading or writing.
**************************************************************************************************/
static void _Prep(Gfile * const file, GfileOpStatus const status)
{
   Gi8 position;

   genter;

   // File is in a state that reading or writing is ok.  Nothing
   // needs to be done.
   greturnIf(file->opStatus & status);

   // Set the position so that we can read or write.
   position = gfileGetPosition(file);
   if (gfileSetPosition(file, gpositionSTART, position) != gfileSetPositionSUCCESS)
   {
      debugHalt("gfileSetPosition failed");
   }

/* _lseeki64(file, SEEK_CUR, 0) on an empty file sets it to byte 1?!
WTF?!?
#if grlWINDOWS == 1
   _lseeki64(file->file, SEEK_CUR, 0);
#else
   fseek(file->file, SEEK_CUR, 0);
#endif
*/

   file->opStatus = gfileOpStatusANY;

   greturn;
}
