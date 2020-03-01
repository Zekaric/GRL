/******************************************************************************
file:       GfileRat
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL Ascii Database routines
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

/******************************************************************************
local:
constant:
******************************************************************************/

/******************************************************************************
type:
******************************************************************************/

/******************************************************************************
variable:
******************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/
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

static GfileRatRow   *_RowCreate(         GfileRat const * const rat);
static void           _RowDestroy(        GfileRat const * const rat, GfileRatRow * const row);

static Gs            *_SFromN1(           Gn1      const * const n, Gcount const count);
static Gb             _StoreAll(          GfileRat       * const rat);
static void           _StoreConfig(       GfileRat       * const rat, Gfile * const file);
static void           _StoreHeader(       GfileRat       * const rat, Gfile * const file);
static Gb             _StoreRow(          GfileRat       * const rat, Gfile *file, Gindex const indexRow);
static Gb             _StoreUpdatedRows(  GfileRat       * const rat);

static Gversion       _VersionFromN1(     Gn1      const * const n);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gfileRatCreate_
******************************************************************************/
grlAPI GfileRat *gfileRatCreate_(Gpath const * const path, Gb const isBinary, GfileRatMode const mode)
{
   GfileRat *rat;

   genter;

   rat = gmemCreateType(GfileRat);
   greturnNullIf(!rat);

   if (!gfileRatCreateContent(rat, path, isBinary, mode))
   {
      gfileRatDestroy(rat);
      greturn NULL;
   }

   greturn rat;
}

/******************************************************************************
func: gfileRatCreateContent
******************************************************************************/
grlAPI Gb gfileRatCreateContent(GfileRat * const rat, Gpath const * const path, Gb const isBinary,
   GfileRatMode const mode)
{
   Gb     result;
   Gfile *file;

   genter;

   greturnFalseIf(!rat);

   result = gbFALSE;

   rat->isBinary          = isBinary;
   rat->versionFile       = 0;
   rat->versionData       = 0;
   rat->path              = gpathCreateFrom(path);
   rat->pathBackup        = gpathCreateFrom(path);
   gpathPopExtension(  rat->pathBackup);
   gpathPushExtensionA(rat->pathBackup, "bak");

   rat->colArray          = gfileRatColArrayCreate();
   rat->rowArray          = gfileRatRowArrayCreate();
   rat->isUpdatedRowArray = gindexArrayCreate(gindexCompare, gbTRUE);
   rat->isDeletedRowArray = gindexArrayCreate(gindexCompare, gbTRUE);
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

/******************************************************************************
func: gfileRatDestroy
******************************************************************************/
grlAPI void gfileRatDestroy(GfileRat * const rat)
{
   genter;

   greturnVoidIf(!rat);

   gfileRatDestroyContent(rat);

   greturn;
}

/******************************************************************************
func: gfileRatDestroyContent
******************************************************************************/
grlAPI void gfileRatDestroyContent(GfileRat * const rat)
{
   Gindex  index;
   GfileRatCol *col;

   genter;

   greturnVoidIf(!rat);

   // Clean out all the dynamic values in the table.
   forCount (index, gfileRatRowArrayGetCount(rat->rowArray))
   {
      _RowDestroy(rat, gfileRatRowArrayGetAt(rat->rowArray, index));
   }
   gfileRatRowArrayDestroy(  rat->rowArray);

   // Clean out all the dynamic value in the columns.
   forCount (index, gfileRatColArrayGetCount(rat->colArray))
   {
      col = gfileRatColArrayGetAt(rat->colArray, index);

      gsDestroy(col->name);
   }
   gfileRatColArrayDestroy(  rat->colArray);

   gindexArrayDestroy(  rat->isUpdatedRowArray);

   gpathDestroy(        rat->path);
   
   gmemDestroy(         rat->rowBuffer);

   greturn;
}

/******************************************************************************
func: gfileRatGetColCount
******************************************************************************/
grlAPI Gcount gfileRatGetColCount(GfileRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gfileRatColArrayGetCount(rat->colArray);

   greturn count;
}

/******************************************************************************
func: gfileRatGetRowCount
******************************************************************************/
grlAPI Gcount gfileRatGetRowCount(GfileRat const * const rat)
{
   Gcount count;

   genter;

   greturn0If(!rat);

   count = gfileRatRowArrayGetCount(rat->rowArray);

   greturn count;
}

/******************************************************************************
func: gfileRatGetVersion
******************************************************************************/
grlAPI Gid gfileRatGetVersion(GfileRat const * const rat)
{
   genter;

   greturn0If(!rat);

   greturn rat->versionFile;
}

/******************************************************************************
func: gfileRatSetVersion
******************************************************************************/
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

/******************************************************************************
func: gfileRatStore
******************************************************************************/
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

/******************************************************************************
func: gfileRatColCreate
******************************************************************************/
grlAPI Gb gfileRatColCreate(GfileRat * const rat, Gindex const inColIndex, 
   Gs const * const colName, GfileRatType const type, Gcount const byteCountForStrings)
{
   Gindex    index,
             colIndex;
   Gb        result,
             allocFailed;
   GfileRatCol    col;
   GfileRatRow   *row;
   Gvp       vp;

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
   col.name = gsCreateFrom(colName);
   col.type = type;
   if (type == gfileRatTypeS)
   {
      col.byteCount = byteCountForStrings;
   }
   else
   {
      switch (type)
      {
      case gfileRatTypeB:    col.byteCount = 1;  break;
      case gfileRatTypeN1:   col.byteCount = 2;  break;
      case gfileRatTypeN2:   col.byteCount = 4;  break;
      case gfileRatTypeN4:   col.byteCount = 8;  break;
      case gfileRatTypeN8:   col.byteCount = 16; break;
      case gfileRatTypeI1:   col.byteCount = 2;  break;
      case gfileRatTypeI2:   col.byteCount = 4;  break;
      case gfileRatTypeI4:   col.byteCount = 8;  break;
      case gfileRatTypeI8:   col.byteCount = 16; break;
      case gfileRatTypeR4:   col.byteCount = 8;  break;
      case gfileRatTypeR8:   col.byteCount = 16; break;
      }
   }

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
         vp.s = gsCreate();
         if (!vp.s)
         {
            allocFailed = gbTRUE;
         }
      }

      if (!gvpArrayAddAt(row->value, colIndex, &vp))
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

/******************************************************************************
func: gfileRatColDestroy
******************************************************************************/
grlAPI Gb gfileRatColDestroy(GfileRat * const rat, Gindex const colIndex)
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
         gsDestroy(gvpArrayGetAt(row->value, colIndex)->s);
      }

      // Remove the column.
      gvpArrayEraseAt(row->value, 1, colIndex);
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

/******************************************************************************
func: gfileRatColGetName
******************************************************************************/
grlAPI Gs *gfileRatColGetName(GfileRat const * const rat, Gindex const colIndex)
{
   GfileRatCol *col;

   genter;

   greturnNullIf(!rat);

   col = gfileRatColArrayGetAt(rat->colArray, colIndex);
   greturnNullIf(!col);

   greturn col->name;
}

/******************************************************************************
func: gfileRatColGetType
******************************************************************************/
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

/******************************************************************************
func: gfileRatColGetByteCount
******************************************************************************/
grlAPI Gcount gfileRatColGetByteCount(GfileRat const * const rat, Gindex const colIndex)
{
   GfileRatCol *col;

   genter;

   greturn0If(!rat);

   col = gfileRatColArrayGetAt(rat->colArray, colIndex);
   greturn0If(!col);

   greturn col->byteCount;
}

/******************************************************************************
func: gfileRatRowDestroy
******************************************************************************/
grlAPI Gb gfileRatRowDestroy(GfileRat * const rat, Gindex const rowIndex)
{
   Gindex  index;
   GfileRatRow *row;
   GfileRatCol  col;
   Gvp     vp;

   genter;

   greturnFalseIf(
      !rat ||
      (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex));

   vp.n = 0;
   row  = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);
   greturnFalseIf(row->isDeleted);

   // Clean up the strings.
   forCount (index, gfileRatColArrayGetCount(rat->colArray))
   {
      col = *gfileRatColArrayGetAt(rat->colArray, index);

      if (col.type == gfileRatTypeS)
      {
         gsDestroy(gvpArrayGetAt(row->value, index)->s);
      }

      // Clear out any of the data.
      gvpArrayUpdateAt(row->value, index, &vp);
   }

   row->isChanged = gbTRUE;
   row->isDeleted = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: gfileRatRowGetValue
******************************************************************************/
grlAPI Gvp gfileRatRowGetValue(GfileRat const * const rat, Gindex const rowIndex, Gindex const colIndex)
{
   Gvp      *vp,
             v;
   GfileRatRow   *row;

   genter;

   v.n = 0;

   if (!rat                                                             ||
       (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex) ||
       (colIndex < 0 || gfileRatColArrayGetCount(rat->colArray) <= colIndex))
   {
      greturn v;
   }

   row = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);

   vp = gvpArrayGetAt(row->value, colIndex);
   if (!vp)
   {
      greturn v;
   }

   greturn *vp;
}

/******************************************************************************
func: gfileRatRowIsExisting
******************************************************************************/
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

/******************************************************************************
func: gfileRatRowSetValue
******************************************************************************/
grlAPI Gb gfileRatRowSetValue(GfileRat * const rat, Gindex const rowIndex, Gindex const colIndex, 
   Gvp const value)
{
   GfileRatRow *row;

   genter;

   greturnFalseIf(
      !rat                                                             ||
      (rowIndex < 0 || gfileRatRowArrayGetCount(rat->rowArray) <= rowIndex) ||
      (colIndex < 0 || gfileRatColArrayGetCount(rat->colArray) <= colIndex));

   row = gfileRatRowArrayGetAt(rat->rowArray, rowIndex);
   gvpArrayUpdateAt(row->value, colIndex, &value);   

   greturn gbTRUE;
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _FileBackup
******************************************************************************/
static void _FileBackup(GfileRat const * const rat)
{
   genter;

   // Remove an old back if it exists.
   _FileBackupRemove(rat);

   // Rename the current table to be the back up table.
   gdirRename(rat->path, rat->pathBackup);

   greturn;
}

/******************************************************************************
func: _FileBackupRemove
******************************************************************************/
static void _FileBackupRemove(GfileRat const * const rat)
{
   genter;

   // Remove the old backup.
   gdirFileDestroy(rat->pathBackup);

   greturn;
}

/******************************************************************************
func: _FileOpen
******************************************************************************/
static Gfile *_FileOpen(GfileRat * const rat, GfileRatMode const mode)
{
   Gfile *file;

   genter;

   file = gfileOpen(rat->path, (GfileOpenMode) mode);
   
   greturn file;
}

/******************************************************************************
func: _Load
******************************************************************************/
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

/******************************************************************************
func: _LoadConfig
******************************************************************************/
static Gb _LoadConfig(GfileRat * const rat, Gfile * const file)
{
   Gb           result;
   Gindex       index;
   Gs          *line;
   GsArray     *sarray;
   GfileRatCol *col;

   genter;

   sarray = NULL;
   result = gbFALSE;

   // Get the column names.
   line = gsCreate();
   stopIf(!gfileGetS(file, gcTypeU1, line));
   sarray = gsCreateSplit(line, L'|');
   gsDestroy(line);

   // Create the column array.
   rat->colArray = gfileRatColArrayCreate();
   gfileRatColArraySetCount(rat->colArray, gsArrayGetCount(sarray));

   // Create the columns
   forCount(index, gsArrayGetCount(sarray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Set the column name.
      col->name = gsArrayGetAt(sarray, index);
   }

   // Clean up.
   gsArrayDestroy(sarray);
   sarray = NULL;


   // Get the column types.
   stopIf(!gfileGetS(file, gcTypeU1, line));
   sarray = gsCreateSplit(line, L'|');
   gsDestroy(line);

   // For all the columns...
   forCount(index, gsArrayGetCount(rat->colArray))
   {
      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Get the string part.
      line = gsArrayGetAt(sarray, index);
      stopIf(!line);

      gsTrimU2(line, WHITESPACE_U2);

      // Start of a new type, potentially.
      if      (gsIsEqualA(line, "b"))  { col->type = gfileRatTypeB;  }
      else if (gsIsEqualA(line, "n1")) { col->type = gfileRatTypeN1; }
      else if (gsIsEqualA(line, "n2")) { col->type = gfileRatTypeN2; }
      else if (gsIsEqualA(line, "n4")) { col->type = gfileRatTypeN4; }
      else if (gsIsEqualA(line, "n8")) { col->type = gfileRatTypeN8; }
      else if (gsIsEqualA(line, "i1")) { col->type = gfileRatTypeI1; }
      else if (gsIsEqualA(line, "i2")) { col->type = gfileRatTypeI2; }
      else if (gsIsEqualA(line, "i4")) { col->type = gfileRatTypeI4; }
      else if (gsIsEqualA(line, "i8")) { col->type = gfileRatTypeI8; }
      else if (gsIsEqualA(line, "r4")) { col->type = gfileRatTypeR4; }
      else if (gsIsEqualA(line, "r8")) { col->type = gfileRatTypeR8; }
      else if (*gsGetAt(line, 0) == L's')
      {
         gsEraseAt(line, 1, 0);

         col->type      = gfileRatTypeS;
         col->byteCount = (Gcount) gsGetN(line);
      }
      else 
      {
         // Unknown type.
         stop();
      }
   }

STOP:
   // Clean up
   gsArrayForEach(sarray, gsDestroyFunc);
   gsArrayDestroy(sarray);
   sarray = NULL;

   greturn result;
}

/******************************************************************************
func: _LoadHeader
******************************************************************************/
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
   line = gsCreate();
   stopIf(!gfileGetS(file, gcTypeU1, line));

   // Create the string array
   sarray = gsCreateSplit(line, L'|');

   // Clean up.
   gsDestroy(line);

   // Get the header.
   line = gsArrayGetAt(sarray, 0);

   // Are we dealing with an ASCII or Binary file or neither.
   if      (gsIsEqualA(line, "GRAFT_AF"))
   {
      rat->isBinary = gbFALSE;
   }
   else if (gsIsEqualA(line, "GRAFT_BF"))
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
   gsArrayForEach(sarray, gsDestroyFunc);
   gsArrayDestroy(sarray);

   greturn result;
}

/******************************************************************************
func: _LoadRow
******************************************************************************/
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
   row = _RowCreate(rat);

   // Get the isDeleted flag.
   row->isDeleted = rat->rowBuffer[rat->dataByteCount] == 'T';

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
#if grlSWAP_NEEDED == 1
         gswap2(&v2.n);
#endif
         value.n = v2.n;
         break;

      case gfileRatTypeN4:
      case gfileRatTypeI4:
      case gfileRatTypeR4:
         v4.n = (Gn4) _N4FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
#if grlSWAP_NEEDED == 1
         gswap4(&v4.n);
#endif
         value.r = (Grp) v4.r;
         break;

      case gfileRatTypeN8:
      case gfileRatTypeI8:
      case gfileRatTypeR8:
         value.n = _N8FromFileN1Hex(&rat->rowBuffer[bufferIndex]);
#if grlSWAP_NEEDED == 1
         gswap8(&value.n);
#endif
         break;

      case gfileRatTypeS:
         _SFromN1(&rat->rowBuffer[bufferIndex], col->byteCount);
      }

      bufferIndex += col->byteCount;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: _NFromHex
******************************************************************************/
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

/******************************************************************************
func: _N1FromFileN1Hex
******************************************************************************/
static Gn _N1FromFileN1Hex(Gn1 const * const n)
{
   Gn v;

   genter;
   
   v = 
      _NFromHex(&n[0]) <<  4 |
      _NFromHex(&n[1]);

   greturn v;
}

/******************************************************************************
func: _FileN1FromN
******************************************************************************/
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
      nvalue = ((value >> (shift[nindex]) + 4)) & 0xF;

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

      nvalue = ((value >> shift[nindex])) & 0xF;

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

/******************************************************************************
func: _N2FromFileN1Hex
******************************************************************************/
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

/******************************************************************************
func: _N4FromFileN1Hex
******************************************************************************/
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

/******************************************************************************
func: _N8FromFileN1Hex
******************************************************************************/
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

/******************************************************************************
func: _RowCreate
******************************************************************************/
static GfileRatRow *_RowCreate(GfileRat const * const rat)
{
   GfileRatRow *row;

   genter;

   row = gmemCreateType(GfileRatRow);
   greturnNullIf(!row);

   row->value = gvpArrayCreate(NULL, gbFALSE);
   if (!row->value)
   {
      _RowDestroy(rat, row);
      greturn NULL;
   }

   greturn row;
}

/******************************************************************************
func: _RowDestroy
******************************************************************************/
static void _RowDestroy(GfileRat const * const rat, GfileRatRow * const row)
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
         gsSetA(gvpArrayGetAt(row->value, index)->s, "");
      }
   }

   // Mark the row as deleted.
   gindexArrayAdd(rat->isUpdatedRowArray, row);
   gindexArrayAdd(rat->isDeletedRowArray, row);

   gmemDestroy(row);

   greturn;
}

/******************************************************************************
func: _SFromN1
******************************************************************************/
static Gs *_SFromN1(Gn1 const * const n, Gcount const count)
{
   Gs    *s;
   Gn1   *ntemp;

   genter;

   ntemp = gmemCreateTypeArray(Gn1, count + 1);
   gmemCopyOverTypeArray(n, Gn1, count, ntemp);

   s = gsCreateFromU1(ntemp);

   gmemDestroy(ntemp);

   greturn s;
}

/******************************************************************************
func: _StoreAll
******************************************************************************/
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

/******************************************************************************
func: _StoreConfig
******************************************************************************/
static void _StoreConfig(GfileRat * const rat, Gfile * const file)
{
   Gindex    index;
   Gcount    byteCount;
   GfileRatCol *col;
   Gs       *line,
            *type;

   genter;

   // Write out the column names.
   line = gsCreate();
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
   byteCount = 9;

   type = gsCreate();
   forCount(index, gfileRatColArrayGetCount(rat->colArray))
   {
      // Clean the type.
      gsFlush(type);

      // Get the column.
      col = gfileRatColArrayGetAt(rat->colArray, index);

      // Get the type.
      switch (col->type)
      {
      case gfileRatTypeB:  gsAppendA(type, "b");  byteCount += 1;                         break;
      case gfileRatTypeI1: gsAppendA(type, "i1"); byteCount += (rat->isBinary) ? 1 :  2; break;
      case gfileRatTypeI2: gsAppendA(type, "i2"); byteCount += (rat->isBinary) ? 2 :  4; break;
      case gfileRatTypeI4: gsAppendA(type, "i4"); byteCount += (rat->isBinary) ? 4 :  8; break;
      case gfileRatTypeI8: gsAppendA(type, "i8"); byteCount += (rat->isBinary) ? 8 : 16; break;
      case gfileRatTypeN1: gsAppendA(type, "n1"); byteCount += (rat->isBinary) ? 1 :  2; break;
      case gfileRatTypeN2: gsAppendA(type, "n2"); byteCount += (rat->isBinary) ? 2 :  4; break;
      case gfileRatTypeN4: gsAppendA(type, "n4"); byteCount += (rat->isBinary) ? 4 :  8; break;
      case gfileRatTypeN8: gsAppendA(type, "n8"); byteCount += (rat->isBinary) ? 8 : 16; break;
      case gfileRatTypeR4: gsAppendA(type, "r4"); byteCount += (rat->isBinary) ? 4 :  8; break;
      case gfileRatTypeR8: gsAppendA(type, "r8"); byteCount += (rat->isBinary) ? 8 : 16; break;
      case gfileRatTypeS:  
         gsAppendC(type, L's');  
         gsAppendN(type, col->byteCount);

         byteCount += col->byteCount; 
         break;
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
   }
   // Add the line.
   gsAppendC(line, L'\n');

   // Write the line.
   gfileSetS(file, gcTypeU1, line, NULL);
   gsDestroy(line);

   // Update the internal values.
   rat->dataByteCount = gsGetCount(line);
   rat->rowByteCount  = rat->dataByteCount + 9;

   // recreate the line buffer.
   gmemDestroy(rat->rowBuffer);
   rat->rowBuffer = gmemCreateTypeArray(Gn1, rat->rowByteCount);

   // Get the starting location of the data.
   rat->offsetData = gfileGetPosition(file);
}

/******************************************************************************
func: _StoreHeader
******************************************************************************/
static void _StoreHeader(GfileRat * const rat, Gfile * const file)
{
   Gn1 version[9];
   Gs *line;

   genter;

   // Create the line.
   line = gsCreate();

   // Add the header.
   if (rat->isBinary)
   {
      gsAppendA(line, "GRAFT_BF|");
   }
   else
   {
      gsAppendA(line, "GRAFT_AF|");
   }

   // Clear the version.
   gmemClearTypeArray(version, Gn1, 9);

   // Set the GRAFT version
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
   gsDestroy(line);

   greturn;
}

/******************************************************************************
func: _StoreRow
******************************************************************************/
static Gb _StoreRow(GfileRat * const rat, Gfile *file, Gindex const indexRow)
{
   Gindex             index,
                      byteOffset;
   Gb                 result;
   GfileRatCol       *col;
   GfileRatRow       *row;
   Gvp                vp;
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
#if grlSWAP_NEEDED == 1
   gswap4(&n4);
#endif
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
      vp = *gvpArrayGetAt(row->value, index);

#if grlSWAP_NEEDED == 1
      switch (col->type)
      {
      case gfileRatTypeI2:   
      case gfileRatTypeN2: 
         n2 = (Gn2) vp->n;
         gswap2(&n2);
         vp->n = n2;
         break;

      case gfileRatTypeI4:   
      case gfileRatTypeN4:   
      case gfileRatTypeR4:
         n4 = (Gn4) vp->n;
         gswap4(&n4);
         vp->n = n4;
         break;

      case gfileRatTypeI8:   
      case gfileRatTypeN8:   
      case gfileRatTypeR8:
         gswap8(&vp->n);
         break;
      }
#else
      switch (col->type)
      {
      case gfileRatTypeI2:   
      case gfileRatTypeN2: 
         n2 = (Gn2) vp.n;
         break;

      case gfileRatTypeI4:   
      case gfileRatTypeN4:   
      case gfileRatTypeR4:
         n4 = (Gn4) vp.n;
         break;
      }
#endif

      // Create the binary.
      if (rat->isBinary)
      {
         switch (col->type)
         {
         case gfileRatTypeB:
            switch (vp.b)
            {
            case gbFALSE:    rat->rowBuffer[byteOffset++] = 'F'; break;
            case gbTRUE:     rat->rowBuffer[byteOffset++] = 'T'; break;
            default:         rat->rowBuffer[byteOffset++] = ' '; break;
            }
            break;

         case gfileRatTypeI1:   
         case gfileRatTypeN1:   rat->rowBuffer[byteOffset++] = (Gn1) vp.n; break;
         case gfileRatTypeI2:   
         case gfileRatTypeN2:   gmemCopyOverType(&n2,   Gn2, &rat->rowBuffer[byteOffset]); byteOffset += 2; break;
         case gfileRatTypeI4:                           
         case gfileRatTypeN4:                           
         case gfileRatTypeR4:   gmemCopyOverType(&n4,   Gn4, &rat->rowBuffer[byteOffset]); byteOffset += 4;break;
         case gfileRatTypeI8:   
         case gfileRatTypeN8:   
         case gfileRatTypeR8:   gmemCopyOverType(&vp.n, Gn8, &rat->rowBuffer[byteOffset]); byteOffset += 8; break;
         case gfileRatTypeS:
            c1       = gsCreateU1(vp.s);
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
            switch (vp.b)
            {
            case gbFALSE:     rat->rowBuffer[byteOffset] = 'F'; break;
            case gbTRUE:      rat->rowBuffer[byteOffset] = 'T'; break;
            default:          rat->rowBuffer[byteOffset] = ' '; break;
            }
            break;

         case gfileRatTypeI1:   
         case gfileRatTypeN1:   _FileN1FromN(&rat->rowBuffer[byteOffset], 1, vp.n); break;
         case gfileRatTypeI2:   
         case gfileRatTypeN2:   _FileN1FromN(&rat->rowBuffer[byteOffset], 2, vp.n); break;
         case gfileRatTypeI4:   
         case gfileRatTypeN4:   
         case gfileRatTypeR4:   _FileN1FromN(&rat->rowBuffer[byteOffset], 4, vp.n); break;
         case gfileRatTypeI8:   
         case gfileRatTypeN8:   
         case gfileRatTypeR8:   _FileN1FromN(&rat->rowBuffer[byteOffset], 8, vp.n); break;
         case gfileRatTypeS:    
            c1       = gsCreateU1(vp.s);
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

/******************************************************************************
func: _StoreUpdatedRows
******************************************************************************/
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

/******************************************************************************
func: _VersionFromN1
******************************************************************************/
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
