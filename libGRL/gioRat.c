/**************************************************************************************************
file:       GioRat
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL Ascii Database routines
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2020, Robbert de Groot

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
static void           _ColSet(            GioRat const * const rat, GioRatCol * const col, Gs * const name, GioRatType const type, Gcount byteCount);

static void           _FileBackup(        GioRat const * const rat);
static void           _FileBackupRemove(  GioRat const * const rat);
static Gfile         *_FileOpen(          GioRat       * const rat, GioRatMode const mode);

static Gb             _Load(              GioRat       * const rat, Gfile * const file);
static Gb             _LoadConfig(        GioRat       * const rat, Gfile * const file);
static Gb             _LoadHeader(        GioRat       * const rat, Gfile * const file);
static Gb             _LoadRow(           GioRat       * const rat, Gfile * const file, Gindex const index);

static Gn             _NFromHex(          Gn1      const * const n);
static Gn             _N1FromFileN1Hex(   Gn1      const * const n);
static void           _FileN1FromN(       Gn1            * const n, Gcount const byteCount, Gn const value);
static Gn             _N2FromFileN1Hex(   Gn1      const * const n);
static Gn             _N4FromFileN1Hex(   Gn1      const * const n);
static Gn             _N8FromFileN1Hex(   Gn1      const * const n);

static GioRatRow   *_RowCloc(           GioRat const * const rat);
static void           _RowDloc(           GioRat const * const rat, GioRatRow * const row);

static Gs            *_SFromN1(           Gn1      const * const n, Gcount const count);
static Gb             _StoreAll(          GioRat       * const rat);
static void           _StoreConfig(       GioRat       * const rat, Gfile * const file);
static void           _StoreHeader(       GioRat       * const rat, Gfile * const file);
static Gb             _StoreRow(          GioRat       * const rat, Gfile *file, Gindex const indexRow);
static Gb             _StoreUpdatedRows(  GioRat       * const rat);

static Gversion       _VersionFromN1(     Gn1      const * const n);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioRatCloc_
**************************************************************************************************/
grlAPI GioRat *gioRatCloc_(Gpath const * const path, Gb const isBinary, GioRatMode const mode)
{
   GioRat *rat;

   genter;

   rat = gmemClocType(GioRat);
   greturnNullIf(!rat);

   if (!gioRatClocContent(rat, path, isBinary, mode))
   {
      gioRatDloc(rat);
      greturn NULL;
   }

   greturn rat;
}

/**************************************************************************************************
func: gioRatClocContent
**************************************************************************************************/
grlAPI Gb gioRatClocContent(GioRat * const rat, Gpath const * const path, Gb const isBinary,
   GioRatMode const mode)
{
   Gb     result;
   Gfile *file;
   Gs    *ext;

   genter;

   greturnFalseIf(!rat);

   result = gbFALSE;

   GTYPE_SET(rat, "Grat");

   ext = gsClocFromA("bak");

   rat->isBinary          = isBinary;
   rat->versionFile       = 0;
   rat->versionData       = 0;
   rat->path              = gpathClocFrom(path);
   rat->pathBackup        = gpathClocFrom(path);
   gpathPopExtension( rat->pathBackup);
   gpathPushExtension(rat->pathBackup, ext);

   rat->colArray          = gvArrayCloc("GfileRatColArray", NULL,          gbTRUE);
   rat->rowArray          = gvArrayCloc("GfileRatRowArray", NULL,          gbTRUE);
   rat->isUpdatedRowArray = gvArrayCloc("GbArray",          gindexCompare, gbTRUE);
   rat->isDeletedRowArray = gvArrayCloc("GbArray",          gindexCompare, gbTRUE);
   rat->offsetData        = 0;
   rat->dataByteCount     = 0;
   rat->rowByteCount      = 0;
   rat->rowBuffer         = NULL;

   gsDloc(ext);

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
func: gioRatDloc
**************************************************************************************************/
grlAPI void gioRatDloc(GioRat * const rat)
{
   genter;

   greturnIf(!rat);

   gioRatDlocContent(rat);

   gmemDloc(rat);

   greturn;
}

/**************************************************************************************************
func: gioRatDlocContent
**************************************************************************************************/
grlAPI void gioRatDlocContent(GioRat * const rat)
{
   Gindex       index;
   GioRatCol *col;

   genter;

   greturnIf(!rat);

   // Clean out all the dynamic values in the table.
   forCount (index, gvArrayGetCount(rat->rowArray))
   {
      _RowDloc(rat, (GioRatRow *) gvArrayGetAt(rat->rowArray, index).p);
   }
   gvArrayDloc(rat->rowArray);

   // Clean out all the dynamic value in the columns.
   forCount (index, gvArrayGetCount(rat->colArray))
   {
      col = (GioRatCol *) gvArrayGetAt(rat->colArray, index).p;

      gsDloc(  col->name);
      gmemDloc(col);
   }
   gvArrayDloc(rat->colArray);

   gvArrayDloc(rat->isUpdatedRowArray);
   gvArrayDloc(rat->isDeletedRowArray);

   gpathDloc(rat->path);
   gpathDloc(rat->pathBackup);

   gmemDloc(rat->rowBuffer);

   greturn;
}

/**************************************************************************************************
func: gioRatGetColCount
**************************************************************************************************/
grlAPI Gcount gioRatGetColCount(GioRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gvArrayGetCount(rat->colArray);

   greturn count;
}

/**************************************************************************************************
func: gioRatGetRowCount
**************************************************************************************************/
grlAPI Gcount gioRatGetRowCount(GioRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gvArrayGetCount(rat->rowArray);

   greturn count;
}

/**************************************************************************************************
func: gioRatGetVersion
**************************************************************************************************/
grlAPI Gid gioRatGetVersion(GioRat const * const rat)
{
   genter;

   greturn0If(!rat);

   greturn rat->versionFile;
}

/**************************************************************************************************
func: gioRatSetVersion
**************************************************************************************************/
grlAPI Gb gioRatSetVersion(GioRat * const rat, Gversion const version)
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
func: gioRatStore
**************************************************************************************************/
grlAPI Gb gioRatStore(GioRat * const rat)
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
   gvArrayFlush(rat->isUpdatedRowArray);

   greturn result;
}

/**************************************************************************************************
func: gioRatColCloc
**************************************************************************************************/
grlAPI Gb gioRatColCloc(GioRat * const rat, Gindex const inColIndex, Gs const * const colName,
   GioRatType const type, Gcount const byteCountForStrings)
{
   Gindex       index,
                colIndex;
   Gb           result,
                allocFailed;
   GioRatCol *col;
   GioRatRow *row;
   Gv           v;

   genter;

   greturnFalseIf(!rat);

   // Properly set the index of the column.
   colIndex = inColIndex;
   if      (inColIndex < 0)
   {
      colIndex = 0;
   }
   else if (gvArrayGetCount(rat->colArray) < inColIndex)
   {
      colIndex = gvArrayGetCount(rat->colArray);
   }

   result = gbFALSE;

   // Setup the column information.
   col = gmemClocType(GioRatCol);
   _ColSet(rat, col, gsClocFrom(colName), type, byteCountForStrings);

   // Add the column to the array.
   gvArrayAddAt(rat->colArray, colIndex, gvFromP(col));
   rat->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gvArrayFlush(rat->isUpdatedRowArray);

   // Update the rows
   allocFailed = gbFALSE;
   forCount (index, gvArrayGetCount(rat->rowArray))
   {
      row = gratRowFromV(gvArrayGetAt(rat->rowArray, index));

      // Create a blank string if the column is a string.
      v.s = NULL;
      if (type == gioRatTypeS)
      {
         v.s = gsCloc();
         if (!v.s)
         {
            allocFailed = gbTRUE;
         }
      }

      if (!gvArrayAddAt(row->value, colIndex, v))
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
func: gioRatColDloc
**************************************************************************************************/
grlAPI Gb gioRatColDloc(GioRat * const rat, Gindex const colIndex)
{
   Gindex       index;
   Gb           result;
   GioRatCol *col;
   GioRatRow *row;

   genter;

   greturnFalseIf(
      !rat ||
      (colIndex < 0 || gvArrayGetCount(rat->colArray) <= colIndex));

   result = gbFALSE;

   // Get the column info.
   col = gratColFromV(gvArrayGetAt(rat->colArray, colIndex));

   // For all rows...
   forCount (index, gvArrayGetCount(rat->rowArray))
   {
      // Get the row.
      row = gratRowFromV(gvArrayGetAt(rat->rowArray, index));

      if (col->type == gioRatTypeS)
      {
         gsDloc(gvGetS(gvArrayGetAt(row->value, colIndex)));
      }

      // Remove the column.
      gvArrayEraseAt(row->value, 1, colIndex);
   }

   // Remove the column.
   gvArrayEraseAt(rat->colArray, 1, colIndex);

   // Mark a column as being update.
   rat->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gvArrayFlush(rat->isUpdatedRowArray);

   result = gbTRUE;

   greturn result;
}

/**************************************************************************************************
func: gioRatColGetName
**************************************************************************************************/
grlAPI Gs *gioRatColGetName(GioRat const * const rat, Gindex const colIndex)
{
   GioRatCol *col;

   genter;

   greturnNullIf(!rat);

   col = gratColFromV(gvArrayGetAt(rat->colArray, colIndex));
   greturnNullIf(!col);

   greturn col->name;
}

/**************************************************************************************************
func: gioRatColGetType
**************************************************************************************************/
grlAPI GioRatType gioRatColGetType(GioRat const * const rat, Gindex const colIndex)
{
   GioRatCol *col;

   genter;

   greturnValIf(!rat, gioRatTypeNONE);

   col = gratColFromV(gvArrayGetAt(rat->colArray, colIndex));
   greturnValIf(!col, gioRatTypeNONE);

   greturn col->type;
}

/**************************************************************************************************
func: gioRatColGetByteCount
**************************************************************************************************/
grlAPI Gcount gioRatColGetByteCount(GioRat const * const rat, Gindex const colIndex)
{
   GioRatCol *col;

   genter;

   greturn0If(!rat);

   col = gratColFromV(gvArrayGetAt(rat->colArray, colIndex));
   greturn0If(!col);

   greturn col->byteCount;
}

/**************************************************************************************************
func: gioRatRowCloc
**************************************************************************************************/
grlAPI Gindex gioRatRowCloc(GioRat * const rat)
{
   GioRatRow *row;

   genter;

   // Take from the deleted list first.
   if (gvArrayGetCount(rat->isDeletedRowArray))
   {
      row = gratRowFromV(gvArrayGetEnd(rat->isDeletedRowArray));
      gvArrayEraseEnd(rat->isDeletedRowArray, 1);
   }
   else
   {
      row = _RowCloc(rat);
      row->index = gvArrayGetCount(rat->rowArray);
      gvArrayAddEnd(rat->rowArray, gvFromP(row));
   }

   row->isChanged = gbTRUE;
   row->isDeleted = gbFALSE;

   greturn row->index;
}

/**************************************************************************************************
func: gioRatRowDloc
**************************************************************************************************/
grlAPI Gb gioRatRowDloc(GioRat * const rat, Gindex const rowIndex)
{
   Gindex       index;
   GioRatRow *row;
   GioRatCol *col;
   Gv           v;

   genter;

   greturnFalseIf(
      !rat ||
      (rowIndex < 0 || gvArrayGetCount(rat->rowArray) <= rowIndex));

   v.n = 0;
   row = gratRowFromV(gvArrayGetAt(rat->rowArray, rowIndex));
   greturnFalseIf(row->isDeleted);

   // Clean up the strings.
   forCount (index, gvArrayGetCount(rat->colArray))
   {
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      if (col->type == gioRatTypeS)
      {
         gsDloc(gvGetS(gvArrayGetAt(row->value, index)));
      }

      // Clear out any of the data.
      gvArrayUpdateAt(row->value, index, v);
   }

   row->isChanged = gbTRUE;
   row->isDeleted = gbTRUE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRatRowGetValue
**************************************************************************************************/
grlAPI Gv gioRatRowGetValue(GioRat const * const rat, Gindex const rowIndex, Gindex const colIndex)
{
   Gv           v;
   GioRatRow *row;

   genter;

   v.n = 0;

   greturnValIf(
         !rat                                                         ||
         (rowIndex < 0 || gvArrayGetCount(rat->rowArray) <= rowIndex) ||
         (colIndex < 0 || gvArrayGetCount(rat->colArray) <= colIndex),
      v);

   row = gratRowFromV(gvArrayGetAt(rat->rowArray, rowIndex));

   greturn gvArrayGetAt(row->value, colIndex);
}

/**************************************************************************************************
func: gioRatRowIsExisting
**************************************************************************************************/
grlAPI Gb gioRatRowIsExisting(GioRat const * const rat, Gindex const rowIndex)
{
   GioRatRow *row;

   genter;

   greturnFalseIf(
      !rat ||
      (rowIndex < 0 || gvArrayGetCount(rat->rowArray) <= rowIndex));

   row = gratRowFromV(gvArrayGetAt(rat->rowArray, rowIndex));
   greturnFalseIf(row->isDeleted);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRatRowSetValue
**************************************************************************************************/
grlAPI Gb gioRatRowSetValue(GioRat * const rat, Gindex const rowIndex, Gindex const colIndex,
   Gv const value)
{
   GioRatRow *row;

   genter;

   greturnFalseIf(
      !rat                                                         ||
      (rowIndex < 0 || gvArrayGetCount(rat->rowArray) <= rowIndex) ||
      (colIndex < 0 || gvArrayGetCount(rat->colArray) <= colIndex));

   row = gratRowFromV(gvArrayGetAt(rat->rowArray, rowIndex));
   gvArrayUpdateAt(row->value, colIndex, value);

   greturn gbTRUE;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _ColSet
**************************************************************************************************/
static void _ColSet(GioRat const * const rat, GioRatCol * const col, Gs * const name, GioRatType const type, Gcount byteCount)
{
   col->name = name;
   col->type = type;
   switch (type)
   {
   case gioRatTypeB:  col->byteCount = (rat->isBinary) ? 1 : 1;
   case gioRatTypeN1: col->byteCount = (rat->isBinary) ? 1 : 2;
   case gioRatTypeN2: col->byteCount = (rat->isBinary) ? 2 : 4;
   case gioRatTypeN4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gioRatTypeN8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gioRatTypeI1: col->byteCount = (rat->isBinary) ? 1 : 2;
   case gioRatTypeI2: col->byteCount = (rat->isBinary) ? 2 : 4;
   case gioRatTypeI4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gioRatTypeI8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gioRatTypeR4: col->byteCount = (rat->isBinary) ? 4 : 8;
   case gioRatTypeR8: col->byteCount = (rat->isBinary) ? 8 : 16;
   case gioRatTypeS:
      col->byteCount = byteCount;
      break;
   }
}

/**************************************************************************************************
func: _FileBackup
**************************************************************************************************/
static void _FileBackup(GioRat const * const rat)
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
static void _FileBackupRemove(GioRat const * const rat)
{
   genter;

   // Remove the old backup.
   gdirDestroy(rat->pathBackup);

   greturn;
}

/**************************************************************************************************
func: _FileOpen
**************************************************************************************************/
static Gfile *_FileOpen(GioRat * const rat, GioRatMode const mode)
{
   Gfile *file;

   genter;

   file = gfileOpen(rat->path, (GfileOpenMode) mode);

   greturn file;
}

/**************************************************************************************************
func: _Load
**************************************************************************************************/
static Gb _Load(GioRat * const rat, Gfile * const file)
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

There are two configuration lines.  First line is for the name of the fields.  The second is the
content of the fields.

Example:
First Name|Last Name|Age|Occupation|Eye Color\n
s32       |s32      |n1 |s64       |n1\n

First and Last name is a UTF8 string of 32 bytes.  Age is a natural number using 1 byte (in memory).
Occupation is a UTF8 string of 64 bytes.  Eye Color is encoded into an natural number using 1 byte
(in memory).

Each row of data will be of a fixed size based off of this configuration.
**************************************************************************************************/
static Gb _LoadConfig(GioRat * const rat, Gfile * const file)
{
   Gb           result;
   Gindex       index;
   Gs          *line,
               *arrayLine;
   GvArray     *sarray;
   GioRatCol *col;
   Gcount       byteCount;

   genter;

   sarray = NULL;
   result = gbFALSE;

   // Get the column names.
   line = gsCloc();
   stopIf(!gfileGetS(file, line));
   sarray = gsClocSplit(line, L'|');

   // Cloc the column array.
   gvArrayFlush(   rat->colArray);
   gvArraySetCount(rat->colArray, gvArrayGetCount(sarray));

   // Cloc the columns
   forCount(index, gvArrayGetCount(sarray))
   {
      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      // Set the column name.
      col->name = gsStrip(
         gvGetS(gvArrayGetAt(sarray, index)),
         gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING);
   }

   // Clean up.
   gvArrayDloc(sarray);
   sarray = NULL;

   // Get the column types.
   stopIf(!gfileGetS(file, line));
   sarray = gsClocSplit(line, L'|');

   byteCount = 0;

   // For all the columns...
   forCount(index, gvArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      // Get the string part.
      arrayLine = gvGetS(gvArrayGetAt(sarray, index));
      stopIf(!arrayLine);

      gsStrip(arrayLine, gsStripMethodWHITE_SPACE_LEADING | gsStripMethodWHITE_SPACE_TRAILING);

      // Start of a new type, potentially.
      if      (gsIsEqualA(arrayLine, "b"))  { _ColSet(rat, col, col->name, gioRatTypeB,  0); }
      else if (gsIsEqualA(arrayLine, "n1")) { _ColSet(rat, col, col->name, gioRatTypeN1, 0); }
      else if (gsIsEqualA(arrayLine, "n2")) { _ColSet(rat, col, col->name, gioRatTypeN2, 0); }
      else if (gsIsEqualA(arrayLine, "n4")) { _ColSet(rat, col, col->name, gioRatTypeN4, 0); }
      else if (gsIsEqualA(arrayLine, "n8")) { _ColSet(rat, col, col->name, gioRatTypeN8, 0); }
      else if (gsIsEqualA(arrayLine, "i1")) { _ColSet(rat, col, col->name, gioRatTypeI1, 0); }
      else if (gsIsEqualA(arrayLine, "i2")) { _ColSet(rat, col, col->name, gioRatTypeI2, 0); }
      else if (gsIsEqualA(arrayLine, "i4")) { _ColSet(rat, col, col->name, gioRatTypeI4, 0); }
      else if (gsIsEqualA(arrayLine, "i8")) { _ColSet(rat, col, col->name, gioRatTypeI8, 0); }
      else if (gsIsEqualA(arrayLine, "r4")) { _ColSet(rat, col, col->name, gioRatTypeR4, 0); }
      else if (gsIsEqualA(arrayLine, "r8")) { _ColSet(rat, col, col->name, gioRatTypeR8, 0); }
      else if (gsGetAt(arrayLine, 0) == L's')
      {
         gsEraseAt(arrayLine, 1, 0);

         _ColSet(rat, col, col->name, gioRatTypeS, (Gcount) gsGetN(arrayLine));
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
   gvArrayForEach(sarray, gsDloc);
   gvArrayDloc(   sarray);

   gsDloc(line);

   greturn result;
}

/**************************************************************************************************
func: _LoadHeader

Header line is

[Header String] '|' [Version Number] '|' [File Version] '|' [Data Version] '\n'

Examples:

GFRAT_AF|1|3|50\n
GFRAT_BF|1|3|50\n

First one for an ASCII only file.  Second one is a binary file.  Different is in the header.
**************************************************************************************************/
static Gb _LoadHeader(GioRat * const rat, Gfile * const file)
{
   Gb       result;
   Gs      *line;
   GvArray *sarray;
   Gversion version;

   genter;

   sarray = NULL;
   result = gbFALSE;

   // Get the versions.
   line = gsCloc();
   if (!gfileGetS(file, line))
   {
      gsDloc(line);
      stop();
   }

   // Cloc the string array
   sarray = gsClocSplit(line, L'|');

   // Clean up.
   gsDloc(line);

   // Get the header.
   line = gvGetS(gvArrayGetAt(sarray, 0));

   // Are we dealing with an ASCII or Binary file or neither.
   if      (gsIsEqualA(line, (Char const *) FILE_HEADER_ASCII))
   {
      rat->isBinary = gbFALSE;
   }
   else if (gsIsEqualA(line, (Char const *) FILE_HEADER_BINARY))
   {
      rat->isBinary = gbTRUE;
   }
   else
   {
      stop();
   }

   // What version of GAT file is this?
   line = gvGetS(gvArrayGetAt(sarray, 1));

   version = (Gversion) gsGetNHex(line);

   // We can't handle the future.
   stopIf(version > GioRatVERSION);
   // For the future.  We currently on have the one version.
   //if (version < GioRatVERSION)
   //{
   //   // Upgrade the file.
   //}

   // What version of the file.
   line = gvGetS(gvArrayGetAt(sarray, 2));

   rat->versionFile = (Gversion) gsGetNHex(line);

   // What version of the data.
   line = gvGetS(gvArrayGetAt(sarray, 3));

   rat->versionData = (Gversion) gsGetNHex(line);

   result = gbTRUE;

STOP:
   // Clean up.
   gvArrayForEach(sarray, gsDloc);
   gvArrayDloc(   sarray);

   greturn result;
}

/**************************************************************************************************
func: _LoadRow
**************************************************************************************************/
static Gb _LoadRow(GioRat * const rat, Gfile * const file, Gindex const rowIndex)
{
   Gindex             index,
                      bufferIndex;
   GfileSetPosition   positionResult;
   Gv                 value;
   Gv2                v2;
   Gv4                v4;
   GioRatCol       *col;
   GioRatRow       *row;

   genter;

   // Set the file position
   positionResult = gfileSetPosition(file, gpositionSTART, rat->offsetData + rat->rowByteCount * rowIndex);
   greturnFalseIf(positionResult != gfileSetPositionSUCCESS);

   // Get the row data.
   greturnFalseIf(gfileGet(file, rat->rowByteCount, rat->rowBuffer) != rat->rowByteCount);

   // Cloc the row.
   row = _RowCloc(rat);
   row->index = gvArrayGetCount(rat->rowArray);
   gvArrayAddEnd(rat->rowArray, gvFromP(row));

   // Get the isDeleted flag.
   row->isDeleted = rat->rowBuffer[rat->dataByteCount] == 'X';

   // If the row is deleted then no point in reading the rest of the row.
   if (row->isDeleted)
   {
      gvArrayAddEnd(rat->isDeletedRowArray, gvFromP(row));
      greturn gbTRUE;
   }

   // Get the data version.
   row->version = _VersionFromN1(&(rat->rowBuffer[rat->dataByteCount + 1]));

   // For all columns...
   bufferIndex = 0;
   forCount (index, gvArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      switch (col->type)
      {
      case gioRatTypeB:
         switch (rat->rowBuffer[bufferIndex])
         {
         case 'T': value.b = gbTRUE;      break;
         case 'F': value.b = gbFALSE;     break;
         default:  value.b = gbUNDEFINED; break;
         }
         break;

      case gioRatTypeN1:
      case gioRatTypeI1:
         value.n = _N1FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         break;

      case gioRatTypeN2:
      case gioRatTypeI2:
         v2.n = (Gn2) _N2FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap2(&v2.n);
         value.n = v2.n;
         break;

      case gioRatTypeN4:
      case gioRatTypeI4:
      case gioRatTypeR4:
         v4.n = (Gn4) _N4FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap4(&v4.n);
         value.r = (Grp) v4.r;
         break;

      case gioRatTypeN8:
      case gioRatTypeI8:
      case gioRatTypeR8:
         value.n = _N8FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
         gswap8(&value.n);
         break;

      case gioRatTypeS:
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
static GioRatRow *_RowCloc(GioRat const * const rat)
{
   GioRatRow *row;

   genter;

   row = gmemClocType(GioRatRow);
   greturnNullIf(!row);

   GTYPE_SET(row, "GfileRatRow");

   row->value = gvArrayCloc("value", NULL, gbFALSE);
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
static void _RowDloc(GioRat const * const rat, GioRatRow * const row)
{
   Gindex       index;
   GioRatCol *col;

   genter;

   greturnIf(!row);

   // For all the strings...
   forCount (index, index < gvArrayGetCount(rat->colArray))
   {
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      if (col->type == gioRatTypeS)
      {
         // Blank the strings.
         gsFlush(gvGetS(gvArrayGetAt(row->value, index)));
      }
   }

   // Mark the row as deleted.
   gvArrayAdd(rat->isUpdatedRowArray, gvFromP(row));
   gvArrayAdd(rat->isDeletedRowArray, gvFromP(row));

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
   gmemCopyOverTypeArray(ntemp, Gn1, count, n);

   s = gsClocFromGchar1(ntemp);

   gmemDloc(ntemp);

   greturn s;
}

/**************************************************************************************************
func: _StoreAll
**************************************************************************************************/
static Gb _StoreAll(GioRat * const rat)
{
   Gindex    index;
   Gb        result;
   Gfile    *file;

   genter;

   // Save the old file.
   _FileBackupRemove(rat);
   _FileBackup(      rat);

   // Open a new file.
   file = _FileOpen(rat, gioRatModeREAD_WRITE);

   // Write out the header.
   _StoreHeader(rat, file);

   // Write out the column name line.
   _StoreConfig(rat, file);

   // Write out the rows
   forCount(index, gvArrayGetCount(rat->rowArray))
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
static void _StoreConfig(GioRat * const rat, Gfile * const file)
{
   Gindex    index;
   Gcount    byteCount;
   GioRatCol *col;
   Gs       *line,
            *type;

   genter;

   // Write out the column names.
   line = gsCloc();
   forCount(index, gvArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      // Add the name.
      gsAppend(line, col->name);

      // Add the separator.
      if (index != gvArrayGetCount(rat->colArray) - 1)
      {
         gsAppendLetter(line, '|');
      }
   }
   // Add the new line.
   gsAppendLetter(line, '\n');

   // Write the line.
   gfileSetS(file, line);
   gsFlush(line);


   // Write out the column type line.
   // delete flag + version.
   byteCount = 0;

   type = gsCloc();
   forCount(index, gvArrayGetCount(rat->colArray))
   {
      // Clean the type.
      gsFlush(type);

      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      // Get the type.
      switch (col->type)
      {
      case gioRatTypeB:  gsAppendA(type, "b");  break;
      case gioRatTypeI1: gsAppendA(type, "i1"); break;
      case gioRatTypeI2: gsAppendA(type, "i2"); break;
      case gioRatTypeI4: gsAppendA(type, "i4"); break;
      case gioRatTypeI8: gsAppendA(type, "i8"); break;
      case gioRatTypeN1: gsAppendA(type, "n1"); break;
      case gioRatTypeN2: gsAppendA(type, "n2"); break;
      case gioRatTypeN4: gsAppendA(type, "n4"); break;
      case gioRatTypeN8: gsAppendA(type, "n8"); break;
      case gioRatTypeR4: gsAppendA(type, "r4"); break;
      case gioRatTypeR8: gsAppendA(type, "r8"); break;
      case gioRatTypeS:  gsAppendLetter(type, 's'); gsAppendN(type, col->byteCount); break;
      }

      // Pad the type.
      gsPadTail(type, gsGetCount(col->name), L' ');

      // Add the separator.
      if (index != gvArrayGetCount(rat->colArray) - 1)
      {
         gsAppendLetter(type, '|');
      }

      // Append the type.
      gsAppend(line, type);

      byteCount += col->byteCount;
   }
   gsDloc(type);

   // Add the line.
   gsAppendLetter(line, '\n');

   // Write the line.
   gfileSetS(file, line);
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

   greturn;
}

/**************************************************************************************************
func: _StoreHeader
**************************************************************************************************/
static void _StoreHeader(GioRat * const rat, Gfile * const file)
{
   Gn1 version[9];
   Gs *line;

   genter;

   // Cloc the line.
   line = gsCloc();

   // Add the header.
   if (rat->isBinary)
   {
      gsAppendA(line, (Char const *) FILE_HEADER_BINARY "|");
   }
   else
   {
      gsAppendA(line, (Char const *) FILE_HEADER_ASCII "|");
   }

   // Clear the version.
   gmemClearTypeArray(version, Gn1, 9);

   // Set the GFRAT version
   _FileN1FromN(version, 4, 1);
   gsAppendA(line, (Char *) version);
   gsAppendLetter(line, '|');

   // Set the file version.
   _FileN1FromN(version, 4, rat->versionFile);
   gsAppendA(line, (Char *) version);
   gsAppendLetter(line, '|');

   // Set the data version.
   rat->versionData++;
   _FileN1FromN(version, 4, rat->versionData);
   gsAppendA(line, (Char *) version);
   gsAppendLetter(line, '\n');

   // Set to the start of the file.
   gfileSetPosition(file, gpositionSTART, 0);
   gfileSetS(file, line);

   // Clean up
   gsDloc(line);

   greturn;
}

/**************************************************************************************************
func: _StoreRow
**************************************************************************************************/
static Gb _StoreRow(GioRat * const rat, Gfile *file, Gindex const indexRow)
{
   Gindex             index,
                      byteOffset;
   Gb                 result;
   GioRatCol       *col;
   GioRatRow       *row;
   Gv                 v;
   Gn2                n2;
   Gn4                n4;
   Gchar1            *c1;
   Gcount             c1Count,
                      writeCount;
   GfileSetPosition   positionResult;

   genter;

   result = gbFALSE;

   // Get the row.
   row = gratRowFromV(gvArrayGetAt(rat->rowArray, indexRow));
   greturnFalseIf(!row);

   // Update the version number of the row.
   row->version++;

   // For all columns...
   byteOffset = 0;

   // Store the is deleted flag.
   switch (row->isDeleted)
   {
   case gbFALSE: rat->rowBuffer[byteOffset++] = '-'; break;
   case gbTRUE:  rat->rowBuffer[byteOffset++] = 'X'; break;
   }

   // Store the data version.
   n4 = row->version;
   gswap4(&n4);
   if (rat->isBinary)
   {
      gmemCopyOverType(&rat->rowBuffer[byteOffset], Gn4, &n4); byteOffset += 4;
   }
   else
   {
      _FileN1FromN(&rat->rowBuffer[byteOffset], 4, n4);
   }
   byteOffset += 4;

   // Store the row data.
   forCount(index, gvArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gratColFromV(gvArrayGetAt(rat->colArray, index));

      // Get the row value;
      v = gvArrayGetAt(row->value, index);

      switch (col->type)
      {
      case gioRatTypeI2:
      case gioRatTypeN2:
         n2 = (Gn2) v.n;
         gswap2(&n2);
         v.n = n2;
         break;

      case gioRatTypeI4:
      case gioRatTypeN4:
      case gioRatTypeR4:
         n4 = (Gn4) v.n;
         gswap4(&n4);
         v.n = n4;
         break;

      case gioRatTypeI8:
      case gioRatTypeN8:
      case gioRatTypeR8:
         gswap8(&v.n);
         break;
      }

      // Cloc the binary.
      if (rat->isBinary)
      {
         switch (col->type)
         {
         case gioRatTypeB:
            switch (v.b)
            {
            case gbFALSE:    rat->rowBuffer[byteOffset++] = 'F'; break;
            case gbTRUE:     rat->rowBuffer[byteOffset++] = 'T'; break;
            default:         rat->rowBuffer[byteOffset++] = '?'; break;
            }
            break;

         case gioRatTypeI1:
         case gioRatTypeN1:   rat->rowBuffer[byteOffset++] = (Gn1) v.n; break;
         case gioRatTypeI2:
         case gioRatTypeN2:   gmemCopyOverType(&rat->rowBuffer[byteOffset],  Gn2, &n2); byteOffset += 2; break;
         case gioRatTypeI4:
         case gioRatTypeN4:
         case gioRatTypeR4:   gmemCopyOverType(&rat->rowBuffer[byteOffset],  Gn4, &n4); byteOffset += 4;break;
         case gioRatTypeI8:
         case gioRatTypeN8:
         case gioRatTypeR8:   gmemCopyOverType(&rat->rowBuffer[byteOffset], Gn8, &v.n); byteOffset += 8; break;
         case gioRatTypeS:
            c1       = gsClocGchar1(v.s);
            c1Count  = charGetCount(c1);
            gmemClearTypeArray(&rat->rowBuffer[byteOffset], Gn1, col->byteCount);
            gmemCopyOverType(  &rat->rowBuffer[byteOffset], gMIN(c1Count, col->byteCount), c1);
            break;
         }
      }
      // Cloc the ASCII.
      else
      {
         switch (col->type)
         {
         case gioRatTypeB:
            switch (v.b)
            {
            case gbFALSE:     rat->rowBuffer[byteOffset] = 'F'; break;
            case gbTRUE:      rat->rowBuffer[byteOffset] = 'T'; break;
            default:          rat->rowBuffer[byteOffset] = '?'; break;
            }
            break;

         case gioRatTypeI1:
         case gioRatTypeN1:   _FileN1FromN(&rat->rowBuffer[byteOffset], 1, v.n); break;
         case gioRatTypeI2:
         case gioRatTypeN2:   _FileN1FromN(&rat->rowBuffer[byteOffset], 2, v.n); break;
         case gioRatTypeI4:
         case gioRatTypeN4:
         case gioRatTypeR4:   _FileN1FromN(&rat->rowBuffer[byteOffset], 4, v.n); break;
         case gioRatTypeI8:
         case gioRatTypeN8:
         case gioRatTypeR8:   _FileN1FromN(&rat->rowBuffer[byteOffset], 8, v.n); break;
         case gioRatTypeS:
            c1       = gsClocGchar1(v.s);
            c1Count  = charGetCount(c1);
            gmemClearTypeArray(&rat->rowBuffer[byteOffset], Gn1, col->byteCount);
            gmemCopyOverType(  &rat->rowBuffer[byteOffset], gMIN(c1Count, col->byteCount), c1);
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
static Gb _StoreUpdatedRows(GioRat * const rat)
{
   Gfile       *file;
   Gindex       index;
   Gb           result;
   GioRatRow *row;

   genter;

   // Open the file
   file = _FileOpen(rat, gioRatModeREAD_WRITE);

   // Store the updated header line.
   _StoreHeader(rat, file);

   // Write out the modified rows.
   forCount(index, gvArrayGetCount(rat->isUpdatedRowArray))
   {
      // Get the updated row.
      row = gratRowFromV(gvArrayGetAt(rat->isUpdatedRowArray, index));

      // Store the updated row.
      _StoreRow(rat, file, row->index);
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
