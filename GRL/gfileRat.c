/**************************************************************************************************
file:       GfileRat
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL Ascii Database routines
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
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
#define FILE_HEADER_ASCII  "GFRAT_AF"
#define FILE_HEADER_BINARY "GFRAT_BF"

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
static void           _ColSet(            GfileRat const * const rat, GfileRatCol * const col, Gs * const name, GfileRatType const type, Gcount byteCount);

static void           _FileBackup(        GfileRat const * const rat);
static void           _FileBackupRemove(  GfileRat const * const rat);
static Gfile         *_FileOpen(          GfileRat       * const rat, GfileRatMode const mode);

static Gb             _Load(              GfileRat       * const rat, Gfile * const file);
static Gb             _LoadConfig(        GfileRat       * const rat, Gfile * const file);
static Gb             _LoadHeader(        GfileRat       * const rat, Gfile * const file);
static Gb             _LoadRow(           GfileRat       * const rat, Gfile * const file, Gindex const index);

static Gn             _NFromHex(          Gn1      const * const n);
static Gn             _N1FromFileN1Hex(   Gn1      const * const n);
static void           _FileN1FromN(       Gn1            * const n, Gcount const byteCount, Gn const value);
static Gn             _N2FromFileN1Hex(   Gn1      const * const n);
static Gn             _N4FromFileN1Hex(   Gn1      const * const n);
static Gn             _N8FromFileN1Hex(   Gn1      const * const n);

static GfileRatRow   *_RowCloc(           GfileRat const * const rat);
static void           _RowDloc(           GfileRat const * const rat, GfileRatRow * const row);

static Gs            *_SFromN1(           Gn1      const * const n, Gcount const count);
static Gb             _StoreAll(          GfileRat       * const rat);
static void           _StoreConfig(       GfileRat       * const rat, Gfile * const file);
static void           _StoreHeader(       GfileRat       * const rat, Gfile * const file);
static Gb             _StoreRow(          GfileRat       * const rat, Gfile *file, Gindex const indexRow);
static Gb             _StoreUpdatedRows(  GfileRat       * const rat);

static Gversion       _VersionFromN1(     Gn1      const * const n);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gfileRatCloc_
**************************************************************************************************/
grlAPI GfileRat *gfileRatCloc_(Gpath const * const path, Gb const isBinary, GfileRatMode const mode)
{
   GfileRat *rat;

   genter;

   rat = gmemClocType(GfileRat);
   greturnNullIf(!rat);

   if (!gfileRatClocContent(rat, path, isBinary, mode))
   {
      gfileRatDloc(rat);
      greturn NULL;
   }

   greturn rat;
}

/**************************************************************************************************
func: gfileRatClocContent
**************************************************************************************************/
grlAPI Gb gfileRatClocContent(GfileRat * const rat, Gpath const * const path, Gb const isBinary,
   GfileRatMode const mode)
{
   Gb     result;
   Gfile *file;

   genter;

   greturnFalseIf(!rat);

   result = gbFALSE;

   GTYPE_SET(rat, "GfileRat");

   rat->isBinary          = isBinary;
   rat->versionFile       = 0;
   rat->versionData       = 0;
   rat->path              = gpathClocFrom(path);
   rat->pathBackup        = gpathClocFrom(path);
   gpathPopExtension(  rat->pathBackup);
   gpathPushExtensionA(rat->pathBackup, "bak");

   rat->colArray          = gfileRatColArrayCloc();
   rat->rowArray          = gfileRatRowArrayCloc();
   rat->isUpdatedRowArray = gindexArrayCloc(gindexCompare, gbTRUE);
   rat->isDeletedRowArray = gindexArrayCloc(gindexCompare, gbTRUE);
   rat->offsetData        = 0;
   rat->dataByteCount     = 0;
   rat->rowByteCount      = 0;
   rat->rowBuffer         = NULL;

   // Open the file
   file = _FileOpen(rat, mode);
   stopIf(!file);

   // Load in the file.
   stopIf(!_Load(rat, file));

   result = gbTRUE;

STOP:
   // Clean up
   gfileClose(file);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileRatDloc
**************************************************************************************************/
grlAPI void gfileRatDloc(GfileRat * const rat)
{
   genter;

   greturnVoidIf(!rat);

   gfileRatDlocContent(rat);

   gmemDloc(rat);

   greturn;
}

/**************************************************************************************************
func: gfileRatDlocContent
**************************************************************************************************/
grlAPI void gfileRatDlocContent(GfileRat * const rat)
{
   Gindex  index;
   GfileRatCol *col;

   genter;

   greturnVoidIf(!rat);

   // Clean out all the dynamic values in the table.
   forCount (index, gfileRatRowArrayGetCount(rat->rowArray))
   {
      _RowDloc(rat, gfileRatRowArrayGetAt(rat->rowArray, index));
   }
   gfileRatRowArrayDloc(rat->rowArray);

   // Clean out all the dynamic value in the columns.
   forCount (index, gfileRatColArrayGetCount(rat->colArray))
   {
      col = gfileRatColArrayGetAt(rat->colArray, index);

      gsDloc(col->name);
   }
   gfileRatColArrayDloc(rat->colArray);

   gindexArrayDloc(rat->isUpdatedRowArray);
   gindexArrayDloc(rat->isDeletedRowArray);

   gpathDloc(rat->path);
   gpathDloc(rat->pathBackup);

   gmemDloc(rat->rowBuffer);

   greturn;
}

/**************************************************************************************************
func: gfileRatGetColCount
**************************************************************************************************/
grlAPI Gcount gfileRatGetColCount(GfileRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gfileRatColArrayGetCount(rat->colArray);

   greturn count;
}

/**************************************************************************************************
func: gfileRatGetRowCount
**************************************************************************************************/
grlAPI Gcount gfileRatGetRowCount(GfileRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gfileRatRowArrayGetCount(rat->rowArray);

   greturn count;
}

/**************************************************************************************************
func: gfileRatGetVersion
**************************************************************************************************/
grlAPI Gid gfileRatGetVersion(GfileRat const * const rat)
{
   genter;

   greturn0If(!rat);

   greturn rat->versionFile;
}

/**************************************************************************************************
func: gfileRatSetVersion
**************************************************************************************************/
grlAPI Gb gfileRatSetVersion(GfileRat * const rat, Gversion const version)
{
   genter;

   greturnFalseIf(
      !rat ||
      version <= rat->versionFile);

   rat->versionFile      = version;
   rat->isUpdatedVersion = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileRatStore
**************************************************************************************************/
grlAPI Gb gfileRatStore(GfileRat * const rat)
{
   Gb result;

   genter;

   greturnFalseIf(!rat);

   // Update the whole file.
   if (rat->isUpdatedColArray)
   {
      result = _StoreAll(rat);
   }
   // Update only certain rows.
   else
   {
      result = _StoreUpdatedRows(rat);
   }

   // Reset the flags.
   rat->isUpdatedColArray = gbFALSE;
   rat->isUpdatedVersion  = gbFALSE;
   gindexArrayFlush(rat->isUpdatedRowArray);

   greturn result;
}

/**************************************************************************************************
func: gfileRatColCloc
**************************************************************************************************/
grlAPI Gb gfileRatColCloc(GfileRat * const rat, Gindex const inColIndex, Gs const * const colName, 
   GfileRatType const type, Gcount const byteCountForStrings)
{
   Gindex       index,
                colIndex;
   Gb           result,
                allocFailed;
   GfileRatCol  col;
   GfileRatRow *row;
   Gv           v;

   genter;

   greturnFalseIf(!rat);

   // Properly set the index of the column.
   colIndex = inColIndex;
   if (inColIndex < 0)
   {
      colIndex = 0;
   }
   else if (gfileRatColArrayGetCount(rat->colArray) < inColIndex)
   {
      colIndex = gfileRatColArrayGetCount(rat->colArray);
   }

   result = gbFALSE;

   // Setup the column information.
   _ColSet(rat, &col, gsClocFrom(colName), type, byteCountForStrings);

   // Add the column to the array.
   gfileRatColArrayAddAt(rat->colArray, colIndex, &col);
   rat->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gindexArrayFlush(rat->isUpdatedRowArray);

   // Update the rows
   allocFailed = gbFALSE;
   forCount (index, gfileRatRowArrayGetCount(rat->rowArray))
   {
      row = gfileRatRowArrayGetAt(rat->rowArray, index);

      // Create a blank string if the column is a string.
      if (type == gfileRatTypeS)
      {
         v.s = gsCloc();
         if (!v.s)
         {
            allocFailed = gbTRUE;
         }
      }

      if (!gvArrayAddAt(row->value, colIndex, &v))
      {
         allocFailed = gbTRUE;
      }
   }

   // The table is still in good status.
   if (!allocFailed)
   {
      result = gbTRUE;
   }

   greturn result;
}

/**************************************************************************************************
func: gfileRatColDloc
**************************************************************************************************/
grlAPI Gb gfileRatColDloc(GfileRat * const rat, Gindex const colIndex)
{
   Gindex       index;
   Gb           result;
   GfileRatCol  col;
   GfileRatRow *row;

   genter;

   greturnFalseIf(
      !rat ||
      (colIndex < 0 || gfileRatColArrayGetCount(rat->colArray) <= colIndex));

   result = gbFALSE;

   // Get the column info.
   col = *gfileRatColArrayGetAt(rat->colArray, colIndex);

   // For all rows...
   forCount (index, gfileRatRowArrayGetCount(rat->rowArray))
   {
      // Get the row.
      row = gfileRatRowArrayGetAt(rat->rowArray, index);

      if (col.type == gfileRatTypeS)
      {
         gsDloc(gvArrayGetAt(row->value, colIndex)->s);
      }

      // Remove the column.
      gvArrayEraseAt(row->value, 1, colIndex);
   }

   // Remove the column.
   gfileRatColArrayEraseAt(rat->colArray, 1, colIndex);

   // Mark a column as being update.
   rat->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gindexArrayFlush(rat->isUpdatedRowArray);

   result = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: gfileRatColGetName
**************************************************************************************************/
grlAPI Gs *gfileRatColGetName(GfileRat const * const rat, Gindex const colIndex)
{
   GfileRatCol *col;

   genter;

   greturnNullIf(!rat);

   col = gfileRatColArrayGetAt(rat->colArray, colIndex);
   greturnNullIf(!col);

   greturn col->name;
}

/**************************************************************************************************
func: gfileRatColGetType
**************************************************************************************************/
grlAPI GfileRatType gfileRatColGetType(GfileRat const * const rat, Gindex const colIndex)
{
   GfileRatCol *col;

   genter;

   if (!rat)
   {
      greturn gfileRatTypeNONE;
   }

   col = gfileRatColArrayGetAt(rat->colArray, colIndex);
   if (!col)
   {
      greturn gfileRatTypeNONE;
   }

   greturn col->type;
}

/**************************************************************************************************
func: gfileRatColGetByteCount
**************************************************************************************************/
grlAPI Gcount gfileRatColGetByteCount(GfileRat const * const rat, Gindex const colIndex)
{
   GfileRatCol *col;

   genter;

   greturn0If(!rat);

   col = gfileRatColArrayGetAt(rat->colArray, colIndex);
   greturn0If(!col);

   greturn col->byteCount;
}

/**************************************************************************************************
func: gfileRatRowDloc
**************************************************************************************************/
grlAPI Gb gfileRatRowDloc(GfileRat * const rat, Gindex const rowIndex)
{
   Gindex       index;
   GfileRatRow *row;
   GfileRatCol  col;
   Gv           v;

   genter;

   greturnFalseIf(
      !rat ||
      (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex));

   v.n = 0;
   row  = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);
   greturnFalseIf(row->isDeleted);

   // Clean up the strings.
   forCount (index, gfileRatColArrayGetCount(rat->colArray))
   {
      col = *gfileRatColArrayGetAt(rat->colArray, index);

      if (col.type == gfileRatTypeS)
      {
         gsDloc(gvArrayGetAt(row->value, index)->s);
      }

      // Clear out any of the data.
      gvArrayUpdateAt(row->value, index, &v);
   }

   row->isChanged = gbTRUE;
   row->isDeleted = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileRatRowGetValue
**************************************************************************************************/
grlAPI Gv gfileRatRowGetValue(GfileRat const * const rat, Gindex const rowIndex, Gindex const colIndex)
{
   Gv          *vp,
                v;
   GfileRatRow *row;

   genter;

   v.n = 0;

   if (!rat                                                                  ||
       (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex) ||
       (colIndex < 0 || gfileRatColArrayGetCount(rat->colArray) <= colIndex))
   {
      greturn v;
   }

   row = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);

   vp = gvArrayGetAt(row->value, colIndex);
   if (!vp)
   {
      greturn v;
   }

   greturn *vp;
}

/**************************************************************************************************
func: gfileRatRowIsExisting
**************************************************************************************************/
grlAPI Gb gfileRatRowIsExisting(GfileRat const * const rat, Gindex const rowIndex)
{
   GfileRatRow *row;

   genter;

   greturnFalseIf(
      !rat                                                               ||
      (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex));

   row = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);
   greturnFalseIf(row->isDeleted);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gfileRatRowSetValue
**************************************************************************************************/
grlAPI Gb gfileRatRowSetValue(GfileRat * const rat, Gindex const rowIndex, Gindex const colIndex,
   Gv const value)
{
   GfileRatRow *row;

   genter;

   greturnFalseIf(
      !rat                                                             ||
      (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex) ||
      (colIndex < 0 || gfileRatColArrayGetCount(rat->colArray) <= colIndex));

   row = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);
   gvArrayUpdateAt(row->value, colIndex, &value);

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ColSet
**************************************************************************************************/
static void _ColSet(GfileRat const * const rat, GfileRatCol * const col, Gs * const name, GfileRatType const type, Gcount byteCount)
{
   col->name = name;
   col->type = type;
   switch (type)
   {
   case gfileRatTypeB:  col->byteCount = (rat->isBinary) ? 1 : 1;
   case gfileRatTypeN1: col->byteCount = (rat->isBinary) ? 1 : 2;
   case gfileRatTypeN2: col->byteCount = (rat->isBinary) ? 2 : 4;
   case gfileRatTypeN4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gfileRatTypeN8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gfileRatTypeI1: col->byteCount = (rat->isBinary) ? 1 : 2;
   case gfileRatTypeI2: col->byteCount = (rat->isBinary) ? 2 : 4;
   case gfileRatTypeI4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gfileRatTypeI8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gfileRatTypeR4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gfileRatTypeR8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gfileRatTypeS:
      col->byteCount = byteCount;
      break;
   }
}

/**************************************************************************************************
func: _FileBackup
**************************************************************************************************/
static void _FileBackup(GfileRat const * const rat)
{
   genter;

   // Remove an old back if it exists.
   _FileBackupRemove(rat);

   // Rename the current table to be the back up table.
   gdirRename(rat->path, rat->pathBackup);

   greturn;
}

/**************************************************************************************************
func: _FileBackupRemove
**************************************************************************************************/
static void _FileBackupRemove(GfileRat const * const rat)
{
   genter;

   // Remove the old backup.
   gdirFileDestroy(rat->pathBackup);

   greturn;
}

/**************************************************************************************************
func: _FileOpen
**************************************************************************************************/
static Gfile *_FileOpen(GfileRat * const rat, GfileRatMode const mode)
{
   Gfile *file;

   genter;

   file = gfileOpen(rat->path, (GfileOpenMode) mode);

   greturn file;
}

/**************************************************************************************************
func: _Load
**************************************************************************************************/
static Gb _Load(GfileRat * const rat, Gfile * const file)
{
   Gb        result;
   Gindex    index;

   genter;

   result = gbFALSE;

   // Header line.
   stopIf(!_LoadHeader(rat, file));

   // Config lines
   stopIf(!_LoadConfig(rat, file));

   // For all rows...
   loopCount(index)
   {
      // Load the row.
      breakIf(!_LoadRow(rat, file, index));
   }

   result = gbTRUE;

STOP:
   greturn result;
}

/**************************************************************************************************
func: _LoadConfig
**************************************************************************************************/
static Gb _LoadConfig(GfileRat * const rat, Gfile * const file)
{
   Gb           result;
   Gindex       index;
   Gs          *line,
               *arrayLine;
   GsArray     *sarray;
   GfileRatCol *col;
   Gcount       byteCount;

   genter;

   sarray = NULL;
   result = gbFALSE;

   // Get the column names.
   line = gsCloc();
   stopIf(!gfileGetS(file, gcTypeU1, line));
   sarray = gsClocSplit(line, L'|');

   // Create the column array.
   gfileRatColArrayFlush(   rat->colArray);
   gfileRatColArraySetCount(rat->colArray, gsArrayGetCount(sarray));

   // Create the columns
   forCount(index, gsArrayGetCount(sarray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Set the column name.
      col->name = gsStrip(
         gsArrayGetAt(sarray, index),
         gcStripWHITE_SPACE_LEADING | gcStripWHITE_SPACE_TRAILING);
   }

   // Clean up.
   gsArrayDloc(sarray);
   sarray = NULL;

   // Get the column types.
   stopIf(!gfileGetS(file, gcTypeU1, line));
   sarray = gsClocSplit(line, L'|');

   byteCount = 0;

   // For all the columns...
   forCount(index, gsArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Get the string part.
      arrayLine = gsArrayGetAt(sarray, index);
      stopIf(!arrayLine);

      gsTrimU2(arrayLine, WHITESPACE_U2);

      // Start of a new type, potentially.
      if      (gsIsEqualA(arrayLine, "b"))  { _ColSet(rat, col, col->name, gfileRatTypeB,  0); }
      else if (gsIsEqualA(arrayLine, "n1")) { _ColSet(rat, col, col->name, gfileRatTypeN1, 0); }
      else if (gsIsEqualA(arrayLine, "n2")) { _ColSet(rat, col, col->name, gfileRatTypeN2, 0); }
      else if (gsIsEqualA(arrayLine, "n4")) { _ColSet(rat, col, col->name, gfileRatTypeN4, 0); }
      else if (gsIsEqualA(arrayLine, "n8")) { _ColSet(rat, col, col->name, gfileRatTypeN8, 0); }
      else if (gsIsEqualA(arrayLine, "i1")) { _ColSet(rat, col, col->name, gfileRatTypeI1, 0); }
      else if (gsIsEqualA(arrayLine, "i2")) { _ColSet(rat, col, col->name, gfileRatTypeI2, 0); }
      else if (gsIsEqualA(arrayLine, "i4")) { _ColSet(rat, col, col->name, gfileRatTypeI4, 0); }
      else if (gsIsEqualA(arrayLine, "i8")) { _ColSet(rat, col, col->name, gfileRatTypeI8, 0); }
      else if (gsIsEqualA(arrayLine, "r4")) { _ColSet(rat, col, col->name, gfileRatTypeR4, 0); }
      else if (gsIsEqualA(arrayLine, "r8")) { _ColSet(rat, col, col->name, gfileRatTypeR8, 0); }
      else if (*gsGetAt(arrayLine, 0) == L's')
      {
         gsEraseAt(arrayLine, 1, 0);

         _ColSet(rat, col, col->name, gfileRatTypeS, (Gcount) gsGetN(arrayLine));
      }
      else
      {
         // Unknown type.
         stop();
      }

      byteCount += col->byteCount;
   }

   // Set the data offset
   rat->offsetData = gfileGetPosition(file);

   // Set up the buffer size;
   rat->dataByteCount = byteCount;
   rat->rowByteCount  = byteCount + 9;

   // Set up the row line buffer.
   gmemDloc(rat->rowBuffer);
   rat->rowBuffer = gmemClocTypeArray(Gn1, rat->rowByteCount);

STOP:
   // Clean up
   gsArrayForEach(sarray, gsDlocFunc);
   gsArrayDloc(   sarray);

   gsDloc(line);

   greturn result;
}

/**************************************************************************************************
func: _LoadHeader
**************************************************************************************************/
static Gb _LoadHeader(GfileRat * const rat, Gfile * const file)
{
   Gb       result;
   Gs      *line;
   GsArray *sarray;
   Gversion version;

   genter;

   sarray = NULL;
   result = gbFALSE;

   // Get the versions.
   line = gsCloc();
   if (!gfileGetS(file, gcTypeU1, line))
   {
      gsDloc(line);
      stop();
   }

   // Create the string array
   sarray = gsClocSplit(line, L'|');

   // Clean up.
   gsDloc(line);

   // Get the header.
   line = gsArrayGetAt(sarray, 0);

   // Are we dealing with an ASCII or Binary file or neither.
   if      (gsIsEqualA(line, FILE_HEADER_ASCII))
   {
      rat->isBinary = gbFALSE;
   }
   else if (gsIsEqualA(line, FILE_HEADER_BINARY))
   {
      rat->isBinary = gbTRUE;
   }
   else
   {
      stop();
   }

   // What version of GAT file is this?
   line = gsArrayGetAt(sarray, 1);

   version = (Gversion) gsGetNHex(line);

   // We can't handle the future.
   stopIf(version > GfileRatVERSION);
   // For the future.  We currently on have the one version.
   //if (version < GfileRatVERSION)
   //{
   //   // Upgrade the file.
   //}

   // What version of the file.
   line = gsArrayGetAt(sarray, 2);

   rat->versionFile = (Gversion) gsGetNHex(line);

   // What version of the data.
   line = gsArrayGetAt(sarray, 3);

   rat->versionData = (Gversion) gsGetNHex(line);

   result = gbTRUE;

STOP:
   // Clean up.
   gsArrayForEach(sarray, gsDlocFunc);
   gsArrayDloc(   sarray);


   greturn result;
}

/**************************************************************************************************
func: _LoadRow
**************************************************************************************************/
static Gb _LoadRow(GfileRat * const rat, Gfile * const file, Gindex const rowIndex)
{
   Gindex             index,
                      bufferIndex;
   GfileSetPosition   positionResult;
   Gv                 value;
   Gv2                v2;
   Gv4                v4;
   GfileRatCol       *col;
   GfileRatRow       *row;

   genter;

   // Set the file position
   positionResult = gfileSetPosition(file, gpositionSTART, rat->offsetData + rat->rowByteCount * rowIndex);
   greturnFalseIf(positionResult != gfileSetPositionSUCCESS);

   // Get the row data.
   greturnFalseIf(gfileGet(file, rat->rowByteCount, rat->rowBuffer) != rat->rowByteCount);

   // Create the row.
   row = _RowCloc(rat);

   // Get the isDeleted flag.
   row->isDeleted = rat->rowBuffer[rat->dataByteCount] == 'T';

   // If the row is deleted then no point in reading the rest of the row.
   if (row->isDeleted)
   {
      gindexArrayAddEnd(rat->isDeletedRowArray, &rowIndex);
      greturn gbTRUE;
   }

   // Get the data version.
   row->version = _VersionFromN1(&(rat->rowBuffer[rat->dataByteCount + 1]));

   // For all columns...
   bufferIndex = 0;
   forCount (index, gfileRatColArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      switch (col->type)
      {
      case gfileRatTypeB:
         switch (rat->rowBuffer[bufferIndex])
         {
         case 'T': value.b = gbTRUE;      break;
         case 'F': value.b = gbFALSE;     break;
         default:  value.b = gbUNDEFINED; break;
         }
         break;

      case gfileRatTypeN1:
      case gfileRatTypeI1:
         value.n = _N1FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         break;

      case gfileRatTypeN2:
      case gfileRatTypeI2:
         v2.n = (Gn2) _N2FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap2(&v2.n);
         value.n = v2.n;
         break;

      case gfileRatTypeN4:
      case gfileRatTypeI4:
      case gfileRatTypeR4:
         v4.n = (Gn4) _N4FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap4(&v4.n);
         value.r = (Grp) v4.r;
         break;

      case gfileRatTypeN8:
      case gfileRatTypeI8:
      case gfileRatTypeR8:
         value.n = _N8FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap8(&value.n);
         break;

      case gfileRatTypeS:
         _SFromN1(&rat->rowBuffer[bufferIndex], col->byteCount);
      }

      bufferIndex += col->byteCount;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NFromHex
**************************************************************************************************/
static Gn _NFromHex(Gn1 const * const n)
{
   genter;

   switch (*n)
   {
   case '0': greturn 0;
   case '1': greturn 1;
   case '2': greturn 2;
   case '3': greturn 3;
   case '4': greturn 4;
   case '5': greturn 5;
   case '6': greturn 6;
   case '7': greturn 7;
   case '8': greturn 8;
   case '9': greturn 9;
   case 'a':
   case 'A': greturn 0xa;
   case 'b':
   case 'B': greturn 0xb;
   case 'c':
   case 'C': greturn 0xc;
   case 'd':
   case 'D': greturn 0xd;
   case 'e':
   case 'E': greturn 0xe;
   }

   greturn 0xf;
}

/**************************************************************************************************
func: _N1FromFileN1Hex
**************************************************************************************************/
static Gn _N1FromFileN1Hex(Gn1 const * const n)
{
   Gn v;

   genter;

   v =
      _NFromHex(&n[0]) <<  4 |
      _NFromHex(&n[1]);

   greturn v;
}

/**************************************************************************************************
func: _FileN1FromN
**************************************************************************************************/
static void _FileN1FromN(Gn1 * const n, Gcount const byteCount, Gn const value)
{
   Gindex index,
          nindex;
   Gcount shift[] = { 0, 8, 16, 24, 32, 40, 48, 56 };
   Gn1    nvalue;

   genter;

   nindex = byteCount - 1;
   for (index = 0; index < byteCount; index++)
   {
      nvalue = (value >> (shift[nindex] + 4)) & 0xF;

      switch(nvalue)
      {
      case 0x0: n[index * 2 + 0] = '0'; break;
      case 0x1: n[index * 2 + 0] = '1'; break;
      case 0x2: n[index * 2 + 0] = '2'; break;
      case 0x3: n[index * 2 + 0] = '3'; break;
      case 0x4: n[index * 2 + 0] = '4'; break;
      case 0x5: n[index * 2 + 0] = '5'; break;
      case 0x6: n[index * 2 + 0] = '6'; break;
      case 0x7: n[index * 2 + 0] = '7'; break;
      case 0x8: n[index * 2 + 0] = '8'; break;
      case 0x9: n[index * 2 + 0] = '9'; break;
      case 0xa: n[index * 2 + 0] = 'A'; break;
      case 0xb: n[index * 2 + 0] = 'B'; break;
      case 0xc: n[index * 2 + 0] = 'C'; break;
      case 0xd: n[index * 2 + 0] = 'D'; break;
      case 0xe: n[index * 2 + 0] = 'E'; break;
      case 0xf: n[index * 2 + 0] = 'F'; break;
      }

      nvalue = (value >> shift[nindex]) & 0xF;

      switch(nvalue)
      {
      case 0x0: n[index * 2 + 1] = '0'; break;
      case 0x1: n[index * 2 + 1] = '1'; break;
      case 0x2: n[index * 2 + 1] = '2'; break;
      case 0x3: n[index * 2 + 1] = '3'; break;
      case 0x4: n[index * 2 + 1] = '4'; break;
      case 0x5: n[index * 2 + 1] = '5'; break;
      case 0x6: n[index * 2 + 1] = '6'; break;
      case 0x7: n[index * 2 + 1] = '7'; break;
      case 0x8: n[index * 2 + 1] = '8'; break;
      case 0x9: n[index * 2 + 1] = '9'; break;
      case 0xa: n[index * 2 + 1] = 'A'; break;
      case 0xb: n[index * 2 + 1] = 'B'; break;
      case 0xc: n[index * 2 + 1] = 'C'; break;
      case 0xd: n[index * 2 + 1] = 'D'; break;
      case 0xe: n[index * 2 + 1] = 'E'; break;
      case 0xf: n[index * 2 + 1] = 'F'; break;
      }

      nindex--;
   }

   greturn;
}

/**************************************************************************************************
func: _N2FromFileN1Hex
**************************************************************************************************/
static Gn _N2FromFileN1Hex(Gn1 const * const n)
{
   Gn v;

   genter;

   v =
      _NFromHex(&n[0]) << 12 |
      _NFromHex(&n[1]) <<  8 |
      _NFromHex(&n[2]) <<  4 |
      _NFromHex(&n[3]);

   greturn v;
}

/**************************************************************************************************
func: _N4FromFileN1Hex
**************************************************************************************************/
static Gn _N4FromFileN1Hex(Gn1 const * const n)
{
   Gn v;

   genter;

   v =
      _NFromHex(&n[0]) << 28 |
      _NFromHex(&n[1]) << 24 |
      _NFromHex(&n[2]) << 20 |
      _NFromHex(&n[3]) << 16 |
      _NFromHex(&n[4]) << 12 |
      _NFromHex(&n[5]) <<  8 |
      _NFromHex(&n[6]) <<  4 |
      _NFromHex(&n[7]);

   greturn v;
}

/**************************************************************************************************
func: _N8FromFileN1Hex
**************************************************************************************************/
static Gn _N8FromFileN1Hex(Gn1 const * const n)
{
   Gn v;

   genter;

   v =
      _NFromHex(&n[ 0]) << 60 |
      _NFromHex(&n[ 1]) << 56 |
      _NFromHex(&n[ 2]) << 52 |
      _NFromHex(&n[ 3]) << 48 |
      _NFromHex(&n[ 4]) << 44 |
      _NFromHex(&n[ 5]) << 40 |
      _NFromHex(&n[ 6]) << 36 |
      _NFromHex(&n[ 7]) << 32 |
      _NFromHex(&n[ 8]) << 28 |
      _NFromHex(&n[ 9]) << 24 |
      _NFromHex(&n[10]) << 20 |
      _NFromHex(&n[11]) << 16 |
      _NFromHex(&n[12]) << 12 |
      _NFromHex(&n[13]) <<  8 |
      _NFromHex(&n[14]) <<  4 |
      _NFromHex(&n[15]);

   greturn v;
}

/**************************************************************************************************
func: _RowCloc
**************************************************************************************************/
static GfileRatRow *_RowCloc(GfileRat const * const rat)
{
   GfileRatRow *row;

   genter;

   row = gmemClocType(GfileRatRow);
   greturnNullIf(!row);

   GTYPE_SET(row, "GfileRatRow");

   row->value = gvArrayCloc(NULL, gbFALSE);
   if (!row->value)
   {
      _RowDloc(rat, row);
      greturn NULL;
   }

   greturn row;
}

/**************************************************************************************************
func: _RowDloc
**************************************************************************************************/
static void _RowDloc(GfileRat const * const rat, GfileRatRow * const row)
{
   Gindex  index;
   GfileRatCol *col;

   genter;

   greturnVoidIf(!row);

   // For all the strings...
   forCount (index, index < gfileRatColArrayGetCount(rat->colArray))
   {
      col = gfileRatColArrayGetAt(rat->colArray, index);

      if (col->type == gfileRatTypeS)
      {
         // Blank the strings.
         gsSetA(gvArrayGetAt(row->value, index)->s, "");
      }
   }

   // Mark the row as deleted.
   gindexArrayAdd(rat->isUpdatedRowArray, row);
   gindexArrayAdd(rat->isDeletedRowArray, row);

   gmemDloc(row);

   greturn;
}

/**************************************************************************************************
func: _SFromN1
**************************************************************************************************/
static Gs *_SFromN1(Gn1 const * const n, Gcount const count)
{
   Gs    *s;
   Gn1   *ntemp;

   genter;

   ntemp = gmemClocTypeArray(Gn1, count + 1);
   gmemCopyOverTypeArray(n, Gn1, count, ntemp);

   s = gsClocFromU1(ntemp);

   gmemDloc(ntemp);

   greturn s;
}

/**************************************************************************************************
func: _StoreAll
**************************************************************************************************/
static Gb _StoreAll(GfileRat * const rat)
{
   Gindex    index;
   Gb        result;
   Gfile    *file;

   genter;

   // Save the old file.
   _FileBackupRemove(rat);
   _FileBackup(      rat);

   // Open a new file.
   file = _FileOpen(rat, gfileRatModeREAD_WRITE);

   // Write out the header.
   _StoreHeader(rat, file);

   // Write out the column name line.
   _StoreConfig(rat, file);

   // Write out the rows
   forCount(index, gfileRatRowArrayGetCount(rat->rowArray))
   {
      _StoreRow(rat, file, index);
   }

   // Close the file.
   gfileClose(file);

   result = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: _StoreConfig
**************************************************************************************************/
static void _StoreConfig(GfileRat * const rat, Gfile * const file)
{
   Gindex    index;
   Gcount    byteCount;
   GfileRatCol *col;
   Gs       *line,
            *type;

   genter;

   // Write out the column names.
   line = gsCloc();
   forCount(index, gfileRatColArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Add the name.
      gsAppend(line, col->name);

      // Add the separator.
      if (index != gfileRatColArrayGetCount(rat->colArray) - 1)
      {
         gsAppendC(line, L'|');
      }
   }
   // Add the new line.
   gsAppendC(line, L'\n');

   // Write the line.
   gfileSetS(file, gcTypeU1, line, NULL);
   gsFlush(line);


   // Write out the column type line.
   // delete flag + version.
   byteCount = 0;

   type = gsCloc();
   forCount(index, gfileRatColArrayGetCount(rat->colArray))
   {
      // Clean the type.
      gsFlush(type);

      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Get the type.
      switch (col->type)
      {
      case gfileRatTypeB:  gsAppendA(type, "b");  break;
      case gfileRatTypeI1: gsAppendA(type, "i1"); break;
      case gfileRatTypeI2: gsAppendA(type, "i2"); break;
      case gfileRatTypeI4: gsAppendA(type, "i4"); break;
      case gfileRatTypeI8: gsAppendA(type, "i8"); break;
      case gfileRatTypeN1: gsAppendA(type, "n1"); break;
      case gfileRatTypeN2: gsAppendA(type, "n2"); break;
      case gfileRatTypeN4: gsAppendA(type, "n4"); break;
      case gfileRatTypeN8: gsAppendA(type, "n8"); break;
      case gfileRatTypeR4: gsAppendA(type, "r4"); break;
      case gfileRatTypeR8: gsAppendA(type, "r8"); break;
      case gfileRatTypeS:  gsAppendC(type, L's'); gsAppendN(type, col->byteCount); break;
      }

      // Pad the type.
      gsPadTail(type, gsGetCount(col->name), L' ');

      // Add the separator.
      if (index != gfileRatColArrayGetCount(rat->colArray) - 1)
      {
         gsAppendC(type, L'|');
      }

      // Append the type.
      gsAppend(line, type);

      byteCount += col->byteCount;
   }
   gsDloc(type);

   // Add the line.
   gsAppendC(line, L'\n');

   // Write the line.
   gfileSetS(file, gcTypeU1, line, NULL);
   gsDloc(line);

   // Has config changed since last we saved?
   if (byteCount != rat->dataByteCount)
   {
      // Update the internal values.
      rat->dataByteCount = byteCount;
      rat->rowByteCount  = byteCount + 9;

      // Update the row buffer.
      gmemDloc(rat->rowBuffer);
      rat->rowBuffer = gmemClocTypeArray(Gn1, rat->rowByteCount);
   }

   // Get the starting location of the data.
   rat->offsetData = gfileGetPosition(file);
}

/**************************************************************************************************
func: _StoreHeader
**************************************************************************************************/
static void _StoreHeader(GfileRat * const rat, Gfile * const file)
{
   Gn1 version[9];
   Gs *line;

   genter;

   // Create the line.
   line = gsCloc();

   // Add the header.
   if (rat->isBinary)
   {
      gsAppendA(line, FILE_HEADER_BINARY "|");
   }
   else
   {
      gsAppendA(line, FILE_HEADER_ASCII "|");
   }

   // Clear the version.
   gmemClearTypeArray(version, Gn1, 9);

   // Set the GFRAT version
   _FileN1FromN(version, 4, 1);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, L'|');

   // Set the file version.
   _FileN1FromN(version, 4, rat->versionFile);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, L'|');

   // Set the data version.
   rat->versionData++;
   _FileN1FromN(version, 4, rat->versionData);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, L'\n');

   // Set to the start of the file.
   gfileSetPosition(file, gpositionSTART, 0);
   gfileSetS(file, gcTypeU1, line, NULL);

   // Clean up
   gsDloc(line);

   greturn;
}

/**************************************************************************************************
func: _StoreRow
**************************************************************************************************/
static Gb _StoreRow(GfileRat * const rat, Gfile *file, Gindex const indexRow)
{
   Gindex             index,
                      byteOffset;
   Gb                 result;
   GfileRatCol       *col;
   GfileRatRow       *row;
   Gv                 v;
   Gn2                n2;
   Gn4                n4;
   Gc1               *c1;
   Gcount             c1Count,
                      writeCount;
   GfileSetPosition   positionResult;

   genter;

   result = gbFALSE;

   // Get the row.
   row = gfileRatRowArrayGetAt(rat->rowArray, indexRow);
   greturnFalseIf(!row);

   // Update the version number of the row.
   row->version++;

   // For all columns...
   byteOffset = 0;

   // Store the is deleted flag.
   switch (row->isDeleted)
   {
   case gbFALSE: rat->rowBuffer[byteOffset++] = 'F'; break;
   case gbTRUE:  rat->rowBuffer[byteOffset++] = 'T'; break;
   }

   // Store the data version.
   n4 = row->version;
   gswap4(&n4);
   if (rat->isBinary)
   {
      gmemCopyOverType(&n4, Gn4, &rat->rowBuffer[byteOffset]); byteOffset += 4;
   }
   else
   {
      _FileN1FromN(&rat->rowBuffer[byteOffset], 4, n4);
   }
   byteOffset += 4;

   // Store the row data.
   forCount(index, gfileRatColArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Get the row value;
      v = *gvArrayGetAt(row->value, index);

      switch (col->type)
      {
      case gfileRatTypeI2:
      case gfileRatTypeN2:
         n2 = (Gn2) v.n;
         gswap2(&n2);
         v.n = n2;
         break;

      case gfileRatTypeI4:
      case gfileRatTypeN4:
      case gfileRatTypeR4:
         n4 = (Gn4) v.n;
         gswap4(&n4);
         v.n = n4;
         break;

      case gfileRatTypeI8:
      case gfileRatTypeN8:
      case gfileRatTypeR8:
         gswap8(&v.n);
         break;
      }

      // Create the binary.
      if (rat->isBinary)
      {
         switch (col->type)
         {
         case gfileRatTypeB:
            switch (v.b)
            {
            case gbFALSE:    rat->rowBuffer[byteOffset++] = 'F'; break;
            case gbTRUE:     rat->rowBuffer[byteOffset++] = 'T'; break;
            default:         rat->rowBuffer[byteOffset++] = ' '; break;
            }
            break;

         case gfileRatTypeI1:
         case gfileRatTypeN1:   rat->rowBuffer[byteOffset++] = (Gn1) v.n; break;
         case gfileRatTypeI2:
         case gfileRatTypeN2:   gmemCopyOverType(&n2,  Gn2, &rat->rowBuffer[byteOffset]); byteOffset += 2; break;
         case gfileRatTypeI4:
         case gfileRatTypeN4:
         case gfileRatTypeR4:   gmemCopyOverType(&n4,  Gn4, &rat->rowBuffer[byteOffset]); byteOffset += 4;break;
         case gfileRatTypeI8:
         case gfileRatTypeN8:
         case gfileRatTypeR8:   gmemCopyOverType(&v.n, Gn8, &rat->rowBuffer[byteOffset]); byteOffset += 8; break;
         case gfileRatTypeS:
            c1       = gsClocU1(v.s);
            c1Count  = gcGetCountU1(c1);
            gmemClearTypeArray(&rat->rowBuffer[byteOffset], Gn1, col->byteCount);
            gmemCopyOverType(c1, gMIN(c1Count, col->byteCount), &rat->rowBuffer[byteOffset]);
            break;
         }
      }
      // Create the ASCII.
      else
      {
         switch (col->type)
         {
         case gfileRatTypeB:
            switch (v.b)
            {
            case gbFALSE:     rat->rowBuffer[byteOffset] = 'F'; break;
            case gbTRUE:      rat->rowBuffer[byteOffset] = 'T'; break;
            default:          rat->rowBuffer[byteOffset] = ' '; break;
            }
            break;

         case gfileRatTypeI1:
         case gfileRatTypeN1:   _FileN1FromN(&rat->rowBuffer[byteOffset], 1, v.n); break;
         case gfileRatTypeI2:
         case gfileRatTypeN2:   _FileN1FromN(&rat->rowBuffer[byteOffset], 2, v.n); break;
         case gfileRatTypeI4:
         case gfileRatTypeN4:
         case gfileRatTypeR4:   _FileN1FromN(&rat->rowBuffer[byteOffset], 4, v.n); break;
         case gfileRatTypeI8:
         case gfileRatTypeN8:
         case gfileRatTypeR8:   _FileN1FromN(&rat->rowBuffer[byteOffset], 8, v.n); break;
         case gfileRatTypeS:
            c1       = gsClocU1(v.s);
            c1Count  = gcGetCountU1(c1);
            gmemClearTypeArray(&rat->rowBuffer[byteOffset], Gn1, col->byteCount);
            gmemCopyOverType(c1, gMIN(c1Count, col->byteCount), &rat->rowBuffer[byteOffset]);
            break;
         }
      }
   }

   // Set the file position
   positionResult = gfileSetPosition(file, gpositionSTART, rat->offsetData + rat->rowByteCount * indexRow);
   stopIf(positionResult != gfileSetPositionSUCCESS);

   // Get the row data.
   stopIf(!gfileSet(file, rat->rowByteCount, rat->rowBuffer, &writeCount));

   result = gbTRUE;

STOP:
   greturn result;
}

/**************************************************************************************************
func: _StoreUpdatedRows
**************************************************************************************************/
static Gb _StoreUpdatedRows(GfileRat * const rat)
{
   Gfile *file;
   Gindex index,
          indexRow;
   Gb     result;

   genter;

   // Open the file
   file = _FileOpen(rat, gfileRatModeREAD_WRITE);

   // Store the updated header line.
   _StoreHeader(rat, file);

   // Write out the modified rows.
   forCount(index, gindexArrayGetCount(rat->isUpdatedRowArray))
   {
      // Get the updated row.
      indexRow = *gindexArrayGetAt(rat->isUpdatedRowArray, index);

      // Store the updated row.
      _StoreRow(rat, file, indexRow);
   }

   // Close the file.
   gfileClose(file);

   result = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: _VersionFromN1
**************************************************************************************************/
static Gversion _VersionFromN1(Gn1 const * const n)
{
   Gversion version;

   genter;

   version = (Gversion)
      (_NFromHex(&n[0]) << 28 |
       _NFromHex(&n[1]) << 24 |
       _NFromHex(&n[2]) << 20 |
       _NFromHex(&n[3]) << 16 |
       _NFromHex(&n[4]) << 12 |
       _NFromHex(&n[5]) <<  8 |
       _NFromHex(&n[6]) <<  4 |
       _NFromHex(&n[7]));

   greturn version;
}
