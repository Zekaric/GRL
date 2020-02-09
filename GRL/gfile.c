/******************************************************************************
file:       gfile
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
#include "precompiled.h"

// lint quiet
//lint -save -e550 -e830

/******************************************************************************
local:
function:
******************************************************************************/
static void _Prep(  Gfile * const file, GfileOpStatus const status);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gfileClose
******************************************************************************/
grlAPI void gfileClose(Gfile * const file)
{
   genter;

   greturnVoidIf(
      !file ||
      !file->file);

   // Make sure the file makes it to disk.
#if grlWINDOWS == 1
   //_commit(file->file);
#else
   fflush(file->file);
#endif

   // Close the file.
#if grlWINDOWS == 1
   if (_close(file->file) != 0)
   {
      debugHalt("_close failed");
   }
#else
   fclose(file->file);
#endif

   gmemDestroy(file);

   greturn;
}

/******************************************************************************
func: gfileCreateFromStrArray
******************************************************************************/
grlAPI GfileCreate gfileCreateFromStrArray(Gpath const * const path, GcType const type, GsArray const * const lines)
{
   Gi4          count;
   Gfile       *file;
   GfileCreate  result;

   genter;

   greturnIf(!gpathIsPath(path), gfileCreateBAD_PATH);

   file = gfileOpen(path, gfileOpenModeREAD_WRITE_NEW);
   greturnIf(!file, gfileCreateFAILED_TO_OPEN_FILE);

   result = gfileCreateSUCCESS;
   count  = gfileSetSArray(file, type, lines);
   if (count != gsArrayGetCount(lines))
   {
      result = gfileCreateFAILED_TO_COMPLETELY_WRITE_FILE;
      debugHalt("Lines written does not match lines to be written.");
   }

   gfileClose(file);

   greturn result;
}

/******************************************************************************
func: gfileGet

Load in a bunch of bytes

return:
int
   0 - Nothing left to read.[\n]
   -1 - File wasn't openned for reading or reading not permitted.[\n]
   X - Number of characters read.
******************************************************************************/
grlAPI Gcount gfileGet(Gfile * const file, Gcount const count, Gp * const buffer)
{
   Gcount readCount;

   genter;

   greturn0If(
      !file       ||
      !file->file ||
      !buffer     ||
      count == 0);

   // This set position call should allow us to call this function
   // right after a write function.
   _Prep(file, gfileOpStatusREADING);

   file->opStatus = gfileOpStatusREADING;

#if grlWINDOWS == 1
   readCount = (Gcount) _read(file->file, buffer, (Gn4) count);
#else
   readCount = fread(buffer, count, 1, file->file);
#endif

   if (readCount < 0)
   {
      file->isAtEnd = gbTRUE;
      debugHalt("_read failed");
      greturn 0;
   }
   
   greturn readCount;
}

/******************************************************************************
func: gfileGetC

Read in a gc up to and including a line feed.  The
line may not be null terminated.  It will read at most count chars.

return:
int
   0  - Nothing left to read.[\n]
   1  - Number of characters read.
******************************************************************************/
grlAPI Gcount gfileGetC(Gfile * const file, GcType const type, Gc * const letter)
{
   Gcount result;
   Gc     c4;
   Gc2    c2[2];
   Gc1    ascii,
          c1[4];

   genter;

   greturn0If(
      !file       ||
      !file->file ||
      !letter);

   result = 0;

   // This set position call should allow us to call this function
   // right after a write function.
   _Prep(file, gfileOpStatusREADING);

   file->opStatus = gfileOpStatusREADING;

   c4      = 0;
   *letter = 0;

   // Read a character.
   //lint -save -e787
   switch (type)
   {
   case gcTypeA:
      result = gfileGet(file, gsizeof(Gc1), &(ascii));
      c4     = (Gc) ascii;
      break;

   case gcTypeU1:
      result = gfileGet(file, gsizeof(Gc1), c1);
      if (gcGetLetterByteCount((Gp *) c1, gcTypeU1) > 1)
      {
         result = gfileGet(
            file,
            (gsizeof(Gc1) * (gcGetLetterByteCount((Gp *) c1, gcTypeU1) - 1)),
            &(c1[1]));
      }
      c4 = gcFromU1(c1);
      break;

   case gcTypeU2:
      result = gfileGet(file, gsizeof(Gc2), c2);
#if grlSWAP_NEEDED == 1
      gswap2(&c2[0]);
#endif
      if (gcGetLetterByteCount((Gp *) c2, gcTypeU2) > 1)
      {
         result = gfileGet(file, gsizeof(Gc2), &(c2[1]));
#if grlSWAP_NEEDED == 1
         gswap2(&c2[1]);
#endif
      }
      c4 = gcFromU2(c2);
      break;

   case gcTypeU4:
      result = gfileGet(file, gsizeof(Gc), &(c4));
#if grlSWAP_NEEDED == 1
      gswap4(&c4);
#endif
      break;
   }
   //lint -restore

   // All done.
   greturn0If(result == 0);

   *letter = c4;

   greturn 1;
}

/******************************************************************************
func: gfileGet2
******************************************************************************/
grlAPI Gb gfileGet2(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn2   *p;
#endif

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count <= 0);

   if (gfileGet(file, (gsizeof(Gn2) * count), i) != (gsizeof(Gn2) * count))
   {
      debugHalt("gfileGet didn't real all the bytes");
   }

#if grlSWAP_NEEDED == 1
   p = (Gn2 *) i;
   forCount(a, count)
   {
      gswap2(&p[a]);
   }
#endif

   greturn gbTRUE;
}

/******************************************************************************
func: gfileGet4
******************************************************************************/
grlAPI Gb gfileGet4(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn4   *p;
#endif

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count <= 0);

   if (gfileGet(file, (gsizeof(Gn4) * count), i) != (gsizeof(Gn4) * count))
   {
      debugHalt("gfileGet didn't real all the bytes");
   }

#if grlSWAP_NEEDED == 1
   p = (Gn4 *) i;
   forCount(a, count)
   {
      gswap4(&p[a]);
   }
#endif

   greturn gbTRUE;
}

/******************************************************************************
func: gfileGet8
******************************************************************************/
grlAPI Gb gfileGet8(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn8   *p;
#endif

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count == 0);

   if (gfileGet(file, (gsizeof(Gn8) * count), i) != (gsizeof(Gn8) * count))
   {
      debugHalt("gfileGet failed");
   }

#if grlSWAP_NEEDED == 1
   p = (Gn8 *) i;
   forCount(a, count)
   {
      gswap8(&p[a]);
   }
#endif

   greturn gbTRUE;
}

/******************************************************************************
func: gfileGetS

Read in a line of chars up to and including a line feed.

return:
int
   0  - Nothing read.[\n]
   X  - Number of characters read.
******************************************************************************/
grlAPI Gcount gfileGetS(Gfile * const file, GcType const type, Gs * const str)
{
   Gindex a;
   Gcount result;
   Gc     c4;
   Gc2    c2[2];
   Gc1    ascii,
          c1[4];

   genter;

   greturn0If(
      !file       ||
      !file->file ||
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
      c4 = 0;

      // Read a character.
      switch (type)
      {
      case gcTypeA:
         result = gfileGet(file, gsizeof(Gc1), &(ascii));
         if (result > 0)
         {
            if (!gsAppendC(str, gc2FromA(ascii))) //lint !e713 !e917
            {
               debugHalt("gsAppendC failed");
               goto gfileGetSERROR;
            }
         }
         c4 = (Gc) ascii;
         break;

      case gcTypeU1:
         result = gfileGet(file, gsizeof(Gc1), c1);
         if (result > 0)
         {
            Gcount count;
            
            count = gcGetLetterByteCount((Gp *) c1, gcTypeU1);
            if (count > 1)
            {
               result = gfileGet(
                  file,
                  (Gcount) (gsizeof(Gc1) * (count - 1)),
                  &(c1[1]));
            }
         }

         if (result > 0)
         {
            c4 = gcFromU1(c1);
            if (!gsAppendC(str, (Gc2) c4))
            {
               debugHalt("gsAppendC failed");
               goto gfileGetSERROR;
            }
         }
         break;

      case gcTypeU2:
         result = gfileGet(file, gsizeof(Gc2), c2);
         if (result > 0)
         {
#if grlSWAP_NEEDED == 1
            gswap2(&c2[0]);
#endif
            if (gcGetLetterByteCount((Gp *) c2, gcTypeU2) > 1)
            {
               result = gfileGet(file, gsizeof(Gc2), &(c2[1]));
#if grlSWAP_NEEDED == 1
               gswap2(&c2[1]);
#endif
            }
         }

         if (result > 0)
         {
            c4 = gcFromU2(c2);
            if (!gsAppendC(str, (Gc2) c4))
            {
               debugHalt("gsAppendC failed");
               goto gfileGetSERROR;
            }
         }
         break;

      case gcTypeU4:
         result = gfileGet(file, gsizeof(Gc), &(c4));
         if (result > 0)
         {
#if grlSWAP_NEEDED == 1
            gswap4(&c4);
#endif
            if (!gsAppendC(str, (Gc2) c4))
            {
               debugHalt("gsAppendC failed");
               goto gfileGetSERROR;
            }
         }
         break;
      } //lint !e787

      // All done.
      breakIf(result == 0);

      a++;

      // Check for linefeed
      breakIf(c4 == gcFromA((Char) '\n'));
   }

gfileGetSERROR:
   greturn a;
}

/******************************************************************************
func: gfileGetContent

Read the entire file.
******************************************************************************/
grlAPI Gb gfileGetContent(Gfile * const file, Gcount * const count, Gn1 ** const buffer)
{
   Gcount    size;
   Gn1      *buf;

   genter;

   size = (Gcount) gfileGetSize(file);
   greturnFalseIf(!size);

   buf  = gmemCreateTypeArray(Gn1, size);
   greturnFalseIf(!buf);

   if (gfileGet(file, size, buf) != size)
   {
      gmemDestroy(buf);
      greturn gbFALSE;
   }

   *buffer = buf;
   *count  = size;

   greturn gbTRUE;
}

/******************************************************************************
func: gfileGetContentS

Read in the whole file into the Gsing.
******************************************************************************/
grlAPI Gb gfileGetContentS(Gfile * const file, GcType const type, Gs * const str)
{
   Gcount result;
   Gb     returnResult,
          first;
   Gs    *stemp;

   genter;

   greturnFalseIf(
      !file                ||
      !file->file          ||
      !(type == gcTypeU1 ||
        type == gcTypeU2 ||
        type == gcTypeU4 ||
        type == gcTypeA)   ||
      !str);

   stemp = gsCreate();
   first = gbTRUE;

   returnResult = gbTRUE;
   loop
   {
      // read in a line.
      result = gfileGetS(file, type, stemp);
      if (result == 0)
      {
         returnResult = gbFALSE;
         break;
      }

      if (!first)
      {
         if (!gsAppendA(str, "\n"))
         {
            debugHalt("strAppendA failed");
            break;
         }
         first = gbFALSE;
      }

      if (!gsAppend(str, stemp))
      {
         debugHalt("gsAppend fialed");
         break;
      }
   }

   // Clean up.
   gsDestroy(stemp);

   greturn returnResult;
}

/******************************************************************************
func: gfileGetContentSArray

Read in the entire file and put the lines into an array.

return:
int
   GcountMax - Nothing left to read.[\n]
   X         - Number of lines read.
******************************************************************************/
grlAPI Gcount gfileGetContentSArray(Gfile * const file, GcType const type, GsArray * const strArray)
{
   Gcount count;
   Gs    *stemp;

   genter;

   greturnIf(
         !file       ||
         !file->file ||
         !strArray,
      GcountMAX);

   count = 0;
   loop
   {
      // Create the string.
      stemp = gsCreate();

      // All done.
      if (gfileGetS(file, type, stemp) == 0)
      {
         gsDestroy(stemp);
         break;
      }

      // Append to the lines.
      if (!gsArrayAddEnd(strArray, stemp))
      {
         debugHalt("gsArrayAddLast failed");
         break;
      }
      count++;
   }

   greturn count;
}

/******************************************************************************
func: gfileGetPosition

Get the current file position.

return:
Gi8
   -1 - Failed.[\n]
   X  - The file position.
******************************************************************************/
grlAPI GfileIndex gfileGetPosition(Gfile * const file)
{
   Gi8 i;

   genter;

   greturnIf(
         !file ||
         !file->file,
      0);

   // Return the file position.
#if grlWINDOWS == 1
   i = _telli64(file->file);
#else
   i = ftell(file->file);
#endif

   greturn i;
} //lint !e818

/******************************************************************************
func: gfileGetSize

Returns the size of the file.

return:
Gi8
   The size of the file.
******************************************************************************/
grlAPI GfileIndex gfileGetSize(Gfile * const file)
{
   GfileIndex i,
              current;

   genter;

   greturn0If(
      !file ||
      !file->file);

   // Make sure we can make it back to original position.
   current = gfileGetPosition(file);

   // Seek to the end of the file.
   if (gfileSetPosition(file, gpositionEND, (Gi8) 0) != gfileSetPositionSUCCESS)
   {
      debugHalt("gfileSetPosition failed");
   }

   // Get the position at the end of the file.
   i = gfileGetPosition(file);
   if (i < 0)
   {
      i = 0;
   }

   // Seek back to the original position.
   if (gfileSetPosition(file, gpositionSTART, current) != gfileSetPositionSUCCESS)
   {
      debugHalt("gfileSetPosition failed");
   }

   greturn i;
}

/******************************************************************************
func: gfileIsAtEnd
******************************************************************************/
grlAPI Gb gfileIsAtEnd(Gfile * const file)
{
   Gb result;

   genter;

   greturnTrueIf(!file);

   result = file->isAtEnd;

   greturn result;
}

/******************************************************************************
func: gfileLoadContent
******************************************************************************/
grlAPI Gb gfileLoadContent(Gs const * const pathS, Gcount * const count, Gn1 ** const buffer)
{
   Gpath *path;
   Gb     result;

   genter;

   result = gbFALSE;

   path = gsCreateFrom(pathS);
   greturnFalseIf(!path);

   gpathSetFromSystem(path);
   stopIf(!path);

   result = gfileOpenLoadContent(path, count, buffer);

STOP:
   gpathDestroy(path);

   greturn result;
}

/******************************************************************************
func: gfileOpen_

Open a file

return:
Gfile *
   NULL - Failed[\n]
   X    - File open and ready to work with.
******************************************************************************/
Gfile *gfileOpen_(Gpath const * const path, GfileOpenMode const mode)
{
   Gfile     *file;
   Gs        *stemp;
#if grlWINDOWS == 1
   Gc2 const *systemStr;
#else
   Gc1       *systemStr;
#endif

   genter;

   debugHaltIf(   !gpathIsPath(path), "Passing in path is not a Gpath.");
   greturnIf(!gpathIsPath(path), NULL);

   // Initialize
   file = gmemCreateType(Gfile);
   greturnNullIf(!file);

   stemp = gsCreateFrom(path);
   gpathSetToSystem(stemp); //lint !e534
#if grlWINDOWS == 1
   //systemStr = gsCreateU2(stemp);
   systemStr = gsGet(stemp);
#else
   systemStr = gsCreateA(stemp);
#endif

   // Open the file based on the provided mode.
   switch(mode)
   {
   case gfileOpenModeREAD_ONLY:
#if grlWINDOWS == 1
      if (_wsopen_s(
            &file->file,
            systemStr,
            _O_BINARY | _O_RANDOM | _O_RDONLY, //lint !e835
            _SH_DENYWR,
            _S_IREAD) != 0)
      {
         //debugHalt("_wsopen_s failed");
      }
#else
      file->file = fopen(systemStr, "rb+");
#endif
      break;

   case gfileOpenModeREAD_WRITE:
#if grlWINDOWS == 1
      if (_wsopen_s(
            &file->file,
            systemStr,
            _O_BINARY | _O_RANDOM | _O_RDWR | _O_CREAT,
            _SH_DENYWR,
            _S_IREAD | _S_IWRITE) != 0)
      {
         //debugHalt("_wsopen_s failed");
      }
#else
      file->file = fopen(systemStr, "wb+");
#endif
      break;

   case gfileOpenModeREAD_WRITE_NEW:
#if grlWINDOWS == 1
      if (_wsopen_s(
            &file->file,
            systemStr,
            _O_BINARY | _O_RANDOM | _O_RDWR | _O_CREAT | _O_TRUNC,
            _SH_DENYWR,
            _S_IREAD | _S_IWRITE) != 0)
      {
         //debugHalt("_wsopen_s failed");
      }
#else
      file->file = fopen(systemStr, "wb");
#endif
      break;

   case gfileOpenModeAPPEND:
#if grlWINDOWS == 1
      if (_wsopen_s(
            &file->file,
            systemStr,
            _O_BINARY | _O_RDWR | _O_CREAT | _O_APPEND,
            _SH_DENYWR,
            _S_IREAD | _S_IWRITE) != 0)
      {
         //debugHalt("_wsopen_s failed");
      }
#else
      file->file = fopen(systemStr, "ab+");
#endif
      break;
   }

#if grlWINDOWS == 1
   gsDestroy(stemp);
#else
   gmemDestroy(systemStr);
#endif

#if grlWINDOWS == 1
   if (file->file == -1)
   {
      gmemDestroy(file);
      file = NULL;
   }
#else
   if (!file->file)
   {
      gmemDestroy(file);
      file = NULL;
   }
#endif

   greturn file;
}

/******************************************************************************
func: gfileOpenLoadContent
******************************************************************************/
grlAPI Gb gfileOpenLoadContent(Gpath const * const path, Gcount * const count, Gn1 ** const buffer)
{
   Gfile *file;
   Gb     result;

   genter;

   file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   greturnFalseIf(!file);

   result = gfileGetContent(file, count, buffer);

   gfileClose(file);

   greturn result;
}

/******************************************************************************
func: gfileOpenStoreContent
******************************************************************************/
grlAPI Gb gfileOpenStoreContent(Gpath const * const path, Gcount const count, Gn1 const * const buffer)
{
   Gfile *file;
   Gb     result;
   Gcount writeCount;

   genter;

   file = gfileOpen(path, gfileOpenModeREAD_WRITE_NEW);
   greturnFalseIf(!file);

   result = gfileSet(file, count, buffer, &writeCount);

   gfileClose(file);

   greturn result;
}

/******************************************************************************
func: gfileSet

Write out a bunch of bytes
******************************************************************************/
grlAPI Gb gfileSet(Gfile * const file, Gcount const count, Gp const * const buffer,
   Gcount * const writeCount)
{
   Gcount wc;

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !buffer     ||
      count == 0);

   // This set position call should allow us to call this function
   // right after a read function.
   _Prep(file, gfileOpStatusWRITING);

   file->opStatus = gfileOpStatusWRITING;

#if grlWINDOWS == 1
   wc = (Gcount) _write(file->file, buffer, (Gn4) count);
#else
   wc = fwrite(buffer, count, 1, file->file);
#endif

   if (writeCount)
   {
      *writeCount = gMAX(wc, 0);
   }

   if (wc == -1)
   {
      debugHalt("_write failed");
      greturn gbFALSE;
   }
   
   if (wc != count)  
   {
      debugHalt("_write did not write everything.");
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gfileSetA
******************************************************************************/
grlAPI Gb gfileSetA(Gfile * const file, GcType const type, Char const * const line,
   Gcount * const writeCount)
{
   Gb  result;
   Gs *stemp;

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !line);

   stemp  = gsCreateFromA(line);
   result = gfileSetS(file, type, stemp, writeCount);
   gsDestroy(stemp);

   greturn result;
}

/******************************************************************************
func: gfileSetC

Write a line of Gcs to a file.  Writes up to the null terminator
or at max count letters.  This will not send out a new line to the
file.
******************************************************************************/
grlAPI Gcount gfileSetC(Gfile * const file, GcType const type, Gc const letter)
{
   Gcount count;
   Gb     result;
   Gc1    ascii,
          c1[4];
   Gc2    c2[2];

   genter;

   greturnIf(
         !file ||
         !file->file,
      0);

   // This set position call should allow us to call this function
   // right after a read function.
   _Prep(file, gfileOpStatusWRITING);

   file->opStatus = gfileOpStatusWRITING;

   result = gbFALSE;

   // Write out to file.
   switch(type)
   {
   case gcTypeA:
      ascii  = (Gc1) letter;
      result = gfileSet(file, gsizeof(Gc1), &ascii, NULL);
      break;

   case gcTypeU1:
      count  = gcToU1(letter, &c1[0], &c1[1], &c1[2], &c1[3]);
      result = gfileSet(file, gsizeof(Gc1) * count, c1, NULL);
      break;

   case gcTypeU2:
      count  = gcToU2(letter, &c2[0], &c2[1]);
      result = gfileSet(file, gsizeof(Gc2) * count, c2, NULL);
      break;

   case gcTypeU4:
      result = gfileSet(file, gsizeof(Gc4), &letter, NULL);
   } //lint !e787

   // Error
   greturnIf(!result, 0);
   greturn 1;
}

/******************************************************************************
func: gfileSet2

Write out an array 2 Byte values.
******************************************************************************/
grlAPI Gb gfileSet2(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn2   *p;
#endif
   Gb     result;

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count <= 0);

#if grlSWAP_NEEDED == 1
   p = (Gn2 *) i;
   forCount(a, count)
   {
      gswap2(&p[a]);
   }
#endif

   result = gbTRUE;
   if (!gfileSet(file, gsizeof(Gn2), i, NULL))
   {
      debugHalt("gfileSet failed, written size != buffer size");
      result = gbFALSE;
   }

#if grlSWAP_NEEDED == 1
   forCount(a, count)
   {
      gswap2(&p[a]);
   }
#endif

   greturn result;
}

/******************************************************************************
func: gfileSet4

Write out an array 4 Byte values.
******************************************************************************/
grlAPI Gb gfileSet4(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn4   *p;
#endif
   Gb     result;

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count == 0);

#if grlSWAP_NEEDED == 1
   p = (Gn4 *) i;
   forCount(a, count)
   {
      gswap4(&p[a]);
   }
#endif

   result = gbTRUE;
   if (!gfileSet(file, gsizeof(Gn4), i, NULL))
   {
      debugHalt("gfileSet failed, written size != buffer size");
      result = gbFALSE;
   }

#if grlSWAP_NEEDED == 1
   forCount(a, count)
   {
      gswap4(&p[a]);
   }
#endif

   greturn result;
}

/******************************************************************************
func: gfileSet8
******************************************************************************/
grlAPI Gb gfileSet8(Gfile * const file, Gcount const count, Gp * const i)
{
#if grlSWAP_NEEDED == 1
   Gindex a;
   Gn8   *p;
#endif
   Gb     result;

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      !i          ||
      count == 0);

#if grlSWAP_NEEDED == 1
   p = (Gn8 *) i;
   forCount(a, count)
   {
      gswap8(&p[a]);
   }
#endif

   result = gbTRUE;
   if (!gfileSet(file, gsizeof(Gn8) * count, i, NULL))
   {
      debugHalt("gfileSet failed, written size != buffer size");
      result = gbFALSE;
   }

#if grlSWAP_NEEDED == 1
   forCount(a, count)
   {
      gswap8(&p[a]);
   }
#endif

   greturn result;
}

/******************************************************************************
func: gfileSetS

Write a line of Gcs to a file.  Writes up to the null terminator.

return:
int
   0 - Failed.[\n]
   X - Number of characters written.
******************************************************************************/
grlAPI Gb gfileSetS(Gfile * const file, GcType const type, Gs const * const line,
   Gcount * const writeCount)
{
   Gindex a;
   Gcount count,
          wc;
   Gb     result;
   Gc1    ascii,
          c1[4];
   Gc2    c2[2];
   Gc     c4;

   genter;

   if (writeCount) 
   {
      *writeCount = 0;
   }

   greturnFalseIf(
      !file       ||
      !file->file ||
      !line);

   // This set position call should allow us to call this function
   // right after a read function.
   _Prep(file, gfileOpStatusWRITING);

   file->opStatus = gfileOpStatusWRITING;

   result = gbFALSE;

   forCount(a, gsGetCount(line))
   {
      // End of the line
      c4 = *gsGetAt(line, a); //lint !e571 !e732
      breakIf(!c4);

      // Write out to file.
      switch (type)
      {
      case gcTypeA:
         ascii  = (Gc1) c4;
         result = gfileSet(file, gsizeof(Gc1), &ascii, &wc);
         break;

      case gcTypeU1:
         count  = gcToU1(c4, &c1[0], &c1[1], &c1[2], &c1[3]);
         result = gfileSet(file, gsizeof(Gc1) * count, c1, &wc);
         break;

      case gcTypeU2:
         count  = gcToU2(c4, &c2[0], &c2[1]);
         result = gfileSet(file, gsizeof(Gc2) * count, c2, &wc);
         break;

      case gcTypeU4:
         result = gfileSet(file, gsizeof(Gc4), &c4, &wc);
      } //lint !e787

      if (writeCount) 
      {
         *writeCount = a;
      }

      // Error
      greturnFalseIf(!result);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gfileSetSArray

Write a lines of Gcs to a file.

return:
int
   0 - Failed.[\n]
   X - Number of lines written.
******************************************************************************/
grlAPI Gcount gfileSetSArray(Gfile * const file, GcType const type, GsArray const * const lines)
{
   Gindex     index;
   Gcount     count;
   Gs  const *str;

   genter;

   greturnIf(
         !file       ||
         !file->file ||
         !lines,
      0);

   count = gsArrayGetCount(lines);
   forCount(index, count)
   {
      str = gsArrayGetAt(lines, index);

      breakIf(!gfileSetS(file, type, str, NULL));
   }

   greturn index;
}

/******************************************************************************
func: gfileSetPosition

Set the file position.
******************************************************************************/
grlAPI GfileSetPosition gfileSetPosition(Gfile * const file, Gposition const pos, 
   GfileOffset const offset)
{
   genter;

   greturnIf(
         !file ||
         !file->file,
      gfileSetPositionBAD_FILE);

   // Prevent bad moves
   greturnIf(
         pos == gpositionSTART &&
         offset < 0,
      gfileSetPositionBAD_POSITION);

   // Perform the seek.
#if grlWINDOWS == 1
   {
      GfileOffset newPos;
      newPos = _lseeki64(file->file, offset, pos); //lint !e641
      greturnIf(newPos == -1, gfileSetPositionFAILURE);
   }
#else
   fseek(file->file, offset, pos);
#endif

   file->opStatus = gfileOpStatusANY;
   file->isAtEnd  = gbFALSE;
   if (offset == 0 &&
       pos    == gpositionEND)
   {
      file->isAtEnd = gbTRUE;
   }

   greturn gfileSetPositionSUCCESS;
}

/******************************************************************************
func: gfileSetValue

Write out a bunch of bytes
******************************************************************************/
grlAPI Gb gfileSetValue(Gfile * const file, Gcount const count, Gn1 const value,
   Gcount * const writeCount)
{
#define gfileSetValueBUFFER_SIZE 2048

   Gindex index;
   Gcount wc,
          countSent,
          countRemaining;
   Gn1    buffer[gfileSetValueBUFFER_SIZE];

   genter;

   greturnFalseIf(
      !file       ||
      !file->file ||
      count == 0);

   wc = -1;

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
#if grlWINDOWS == 1
         wc = (Gcount) _write(file->file, buffer, gfileSetValueBUFFER_SIZE);
#else
         wc = fwrite(buffer, gfileSetValueBUFFER_SIZE, 1, file->file);
#endif
         countSent += wc;
         breakIf(wc != gfileSetValueBUFFER_SIZE);
      }
      else
      {
#if grlWINDOWS == 1
         wc = (Gcount) _write(file->file, buffer, countRemaining);
#else
         wc = fwrite(buffer, countRemaining, 1, file->file);
#endif
         countSent += wc;
         breakIf(wc != countRemaining);
      }

      countRemaining -= gfileSetValueBUFFER_SIZE;
   }
      
   if (writeCount)
   {
      *writeCount = gMAX(countSent, 0);
   }

   if (wc == -1)
   {
      debugHalt("_write failed");
      greturn gbFALSE;
   }
   
   if (countSent != count)  
   {
      debugHalt("_write did not write everything.");
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: gfileStoreContent
******************************************************************************/
grlAPI Gb gfileStoreContent(Gs const * const pathS, Gcount const count, Gn1 const * const buffer)
{
   Gpath *path;
   Gb     result;

   genter;

   result = gbFALSE;

   path = gsCreateFrom(pathS);
   greturnFalseIf(!path);

   gpathSetFromSystem(path);
   stopIf(!path);

   result = gfileOpenStoreContent(path, count, buffer);

STOP:
   gpathDestroy(path);

   greturn result;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _Prep

Prepare the file for reading or writing.
******************************************************************************/
static void _Prep(Gfile * const file, GfileOpStatus const status)
{
   Gi8 position;

   genter;

   // File is in a state that reading or writing is ok.  Nothing
   // needs to be done.
   greturnVoidIf(file->opStatus & status);

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
