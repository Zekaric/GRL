/******************************************************************************
file:       Graft
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
static void        _FileBackup(        Graft const * const raft);
static void        _FileBackupRemove(  Graft const * const raft);
static Gfile      *_FileOpen(          Graft       * const raft, GraftMode const mode);
                                                   
static Gb          _Load(              Graft       * const raft, Gfile * const file);
static Gb          _LoadConfig(        Graft       * const raft, Gfile * const file);
static Gb          _LoadHeader(        Graft       * const raft, Gfile * const file);
static Gb          _LoadRow(           Graft       * const raft, Gfile * const file, Gindex const index);

static Gnp         _NFromHex(          Gn1   const * const n);
static Gnp         _N1FromN1(          Gn1   const * const n);
static Gnp         _N1FromN1Hex(       Gn1   const * const n);
static void        _N1FromN(           Gn1         * const n, Gcount const byteCount, Gn const value);
static Gnp         _N2FromN1(          Gn1   const * const n);
static Gnp         _N2FromN1Hex(       Gn1   const * const n);
static Gnp         _N4FromN1(          Gn1   const * const n);
static Gnp         _N4FromN1Hex(       Gn1   const * const n);
static Gnp         _N8FromN1(          Gn1   const * const n);
static Gnp         _N8FromN1Hex(       Gn1   const * const n);

static GraftRow   *_RowCreate(         Graft const * const raft);
static void        _RowDestroy(        Graft const * const raft, GraftRow * const row);

static Gs         *_SFromN1(           Gn1   const * const n, Gcount const count);
static Gb          _StoreAll(          Graft       * const raft);
static void        _StoreConfig(       Graft       * const raft, Gfile * const file);
static void        _StoreHeader(       Graft       * const raft, Gfile * const file);
static Gb          _StoreRow(          Graft       * const raft, Gfile *file, Gindex const indexRow);
static Gb          _StoreUpdatedRows(  Graft       * const raft);

static Gversion    _VersionFromN1(     Gn1   const * const n);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: graftCreate_
******************************************************************************/
grlAPI Graft *graftCreate_(Gpath const * const path, Gb const isBinary, GraftMode const mode)
{
   Graft *raft;

   genter;

   raft = gmemCreateType(Graft);
   greturnNullIf(!raft);

   if (!graftCreateContent(raft, path, isBinary, mode))
   {
      graftDestroy(raft);
      greturn NULL;
   }

   greturn raft;
}

/******************************************************************************
func: graftCreateContent
******************************************************************************/
grlAPI Gb graftCreateContent(Graft * const raft, Gpath const * const path, Gb const isBinary, GraftMode const mode)
{
   Gb     result;
   Gfile *file;

   genter;

   greturnFalseIf(!raft);

   result = gbFALSE;

   raft->isBinary          = isBinary;
   raft->versionFile       = 0;
   raft->versionData       = 0;
   raft->path              = gpathCreateFrom(path);
   raft->pathBackup        = gpathCreateFrom(path);
   gpathPopExtension(  raft->pathBackup);
   gpathPushExtensionA(raft->pathBackup, "bak");

   raft->colArray          = graftColArrayCreate();
   raft->rowArray          = graftRowArrayCreate();
   raft->isUpdatedRowArray = gindexArrayCreate(gindexCompare, gbTRUE);
   raft->isDeletedRowArray = gindexArrayCreate(gindexCompare, gbTRUE);
   raft->offsetData        = 0;
   raft->dataByteCount     = 0;
   raft->rowByteCount      = 0;
   raft->rowBuffer         = NULL;

   // Open the file
   file = _FileOpen(raft, mode);
   stopIf(!file);

   // Load in the file.
   stopIf(!_Load(raft, file));

   result = gbTRUE;

STOP:
   // Clean up
   gfileClose(file);

   greturn gbTRUE;
}

/******************************************************************************
func: graftDestroy
******************************************************************************/
grlAPI void graftDestroy(Graft * const raft)
{
   genter;

   greturnVoidIf(!raft);

   graftDestroyContent(raft);

   greturn;
}

/******************************************************************************
func: graftDestroyContent
******************************************************************************/
grlAPI void graftDestroyContent(Graft * const raft)
{
   Gindex  index;
   GraftCol *col;

   genter;

   greturnVoidIf(!raft);

   // Clean out all the dynamic values in the table.
   forCount (index, graftRowArrayGetCount(raft->rowArray))
   {
      _RowDestroy(raft, graftRowArrayGetAt(raft->rowArray, index));
   }
   graftRowArrayDestroy(  raft->rowArray);

   // Clean out all the dynamic value in the columns.
   forCount (index, graftColArrayGetCount(raft->colArray))
   {
      col = graftColArrayGetAt(raft->colArray, index);

      gsDestroy(col->name);
   }
   graftColArrayDestroy(  raft->colArray);

   gindexArrayDestroy(  raft->isUpdatedRowArray);

   gpathDestroy(        raft->path);
   
   gmemDestroy(         raft->rowBuffer);

   greturn;
}

/******************************************************************************
func: graftGetColCount
******************************************************************************/
grlAPI Gcount graftGetColCount(Graft const * const raft)
{
   Gcount count;

   genter;

   greturn0If(!raft);

   count = graftColArrayGetCount(raft->colArray);

   greturn count;
}

/******************************************************************************
func: graftGetRowCount
******************************************************************************/
grlAPI Gcount graftGetRowCount(Graft const * const raft)
{
   Gcount count;

   genter;

   greturn0If(!raft);

   count = graftRowArrayGetCount(raft->rowArray);

   greturn count;
}

/******************************************************************************
func: graftGetVersion
******************************************************************************/
grlAPI Gid graftGetVersion(Graft const * const raft)
{
   genter;

   greturn0If(!raft);

   greturn raft->versionFile;
}

/******************************************************************************
func: graftSetVersion
******************************************************************************/
grlAPI Gb graftSetVersion(Graft * const raft, Gversion const version)
{
   genter;

   greturnFalseIf(
      !raft ||
      version <= raft->versionFile);

   raft->versionFile      = version;
   raft->isUpdatedVersion = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: graftStore
******************************************************************************/
grlAPI Gb graftStore(Graft * const raft)
{
   Gb result;

   genter;

   greturnFalseIf(!raft);

   // Update the whole file.  
   if (raft->isUpdatedColArray)
   {
      result = _StoreAll(raft);
   }
   // Update only certain rows.
   else 
   {
      result = _StoreUpdatedRows(raft);
   }

   // Reset the flags.
   raft->isUpdatedColArray = gbFALSE;
   raft->isUpdatedVersion  = gbFALSE;
   gindexArrayFlush(raft->isUpdatedRowArray);

   greturn result;
}

/******************************************************************************
func: graftColCreate
******************************************************************************/
grlAPI Gb graftColCreate(Graft * const raft, Gindex const inColIndex, 
   Gs const * const colName, GraftType const type, Gcount const byteCountForStrings)
{
   Gindex    index,
             colIndex;
   Gb        result,
             allocFailed;
   GraftCol    col;
   GraftRow   *row;
   Gvp       vp;

   genter;
   
   greturnFalseIf(!raft);

   // Properly set the index of the column.
   colIndex = inColIndex;
   if (inColIndex < 0) 
   {
      colIndex = 0;
   }
   else if (graftColArrayGetCount(raft->colArray) < inColIndex)
   {
      colIndex = graftColArrayGetCount(raft->colArray);
   }

   result = gbFALSE;

   // Setup the column information.
   col.name = gsCreateFrom(colName);
   col.type = type;
   if (type == graftTypeS)
   {
      col.byteCount = byteCountForStrings;
   }
   else
   {
      switch (type)
      {
      case graftTypeB:    col.byteCount = 1;  break;
      case graftTypeN1:   col.byteCount = 2;  break;
      case graftTypeN2:   col.byteCount = 4;  break;
      case graftTypeN4:   col.byteCount = 8;  break;
      case graftTypeN8:   col.byteCount = 16; break;
      case graftTypeI1:   col.byteCount = 2;  break;
      case graftTypeI2:   col.byteCount = 4;  break;
      case graftTypeI4:   col.byteCount = 8;  break;
      case graftTypeI8:   col.byteCount = 16; break;
      case graftTypeR4:   col.byteCount = 8;  break;
      case graftTypeR8:   col.byteCount = 16; break;
      }
   }

   // Add the column to the array.
   graftColArrayAddAt(raft->colArray, colIndex, &col);
   raft->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gindexArrayFlush(raft->isUpdatedRowArray);

   // Update the rows
   allocFailed = gbFALSE;
   forCount (index, graftRowArrayGetCount(raft->rowArray))
   {
      row = graftRowArrayGetAt(raft->rowArray, index);

      // Create a blank string if the column is a string.
      if (type == graftTypeS)
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
func: graftColDestroy
******************************************************************************/
grlAPI Gb graftColDestroy(Graft * const raft, Gindex const colIndex)
{
   Gindex    index;
   Gb        result;
   GraftCol    col;
   GraftRow   *row;

   genter;

   greturnFalseIf(
      !raft ||
      (colIndex < 0 || graftColArrayGetCount(raft->colArray) <= colIndex));

   result = gbFALSE;

   // Get the column info.
   col = *graftColArrayGetAt(raft->colArray, colIndex);

   // For all rows...
   forCount (index, graftRowArrayGetCount(raft->rowArray))
   {
      // Get the row.
      row = graftRowArrayGetAt(raft->rowArray, index);

      if (col.type == graftTypeS)
      {
         gsDestroy(gvpArrayGetAt(row->value, colIndex)->s);
      }

      // Remove the column.
      gvpArrayEraseAt(row->value, 1, colIndex);
   }

   // Remove the column.
   graftColArrayEraseAt(raft->colArray, 1, colIndex);

   // Mark a column as being update.
   raft->isUpdatedColArray = gbTRUE;

   // If a column changed then all records have changed.
   gindexArrayFlush(raft->isUpdatedRowArray);

   result = gbTRUE;

   greturn result;
}

/******************************************************************************
func: graftColGetName
******************************************************************************/
grlAPI Gs *graftColGetName(Graft const * const raft, Gindex const colIndex)
{
   GraftCol *col;

   genter;

   greturnNullIf(!raft);

   col = graftColArrayGetAt(raft->colArray, colIndex);
   greturnNullIf(!col);

   greturn col->name;
}

/******************************************************************************
func: graftColGetType
******************************************************************************/
grlAPI GraftType graftColGetType(Graft const * const raft, Gindex const colIndex)
{
   GraftCol *col;

   genter;

   if (!raft)
   {
      greturn graftTypeNONE;
   }

   col = graftColArrayGetAt(raft->colArray, colIndex);
   if (!col)
   {
      greturn graftTypeNONE;
   }

   greturn col->type;
}

/******************************************************************************
func: graftColGetByteCount
******************************************************************************/
grlAPI Gcount graftColGetByteCount(Graft const * const raft, Gindex const colIndex)
{
   GraftCol *col;

   genter;

   greturn0If(!raft);

   col = graftColArrayGetAt(raft->colArray, colIndex);
   greturn0If(!col);

   greturn col->byteCount;
}

/******************************************************************************
func: graftRowDestroy
******************************************************************************/
grlAPI Gb graftRowDestroy(Graft * const raft, Gindex const rowIndex)
{
   Gindex  index;
   GraftRow *row;
   GraftCol  col;
   Gvp     vp;

   genter;

   greturnFalseIf(
      !raft ||
      (rowIndex < 0 || graftRowArrayGetCount(raft->rowArray) <= rowIndex));

   vp.n = 0;
   row  = graftRowArrayGetAt(raft->rowArray, rowIndex);
   greturnFalseIf(row->isDeleted);

   // Clean up the strings.
   forCount (index, graftColArrayGetCount(raft->colArray))
   {
      col = *graftColArrayGetAt(raft->colArray, index);

      if (col.type == graftTypeS)
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
func: graftRowGetValue
******************************************************************************/
grlAPI Gvp graftRowGetValue(Graft const * const raft, Gindex const rowIndex, Gindex const colIndex)
{
   Gvp      *vp,
             v;
   GraftRow   *row;

   genter;

   v.n = 0;

   if (!raft                                                             ||
       (rowIndex < 0 || graftRowArrayGetCount(raft->rowArray) <= rowIndex) ||
       (colIndex < 0 || graftColArrayGetCount(raft->colArray) <= colIndex))
   {
      greturn v;
   }

   row = graftRowArrayGetAt(raft->rowArray, rowIndex);

   vp = gvpArrayGetAt(row->value, colIndex);
   if (!vp)
   {
      greturn v;
   }

   greturn *vp;
}

/******************************************************************************
func: graftRowIsExisting
******************************************************************************/
grlAPI Gb graftRowIsExisting(Graft const * const raft, Gindex const rowIndex)
{
   GraftRow *row;

   genter;

   greturnFalseIf(
      !raft                                                               ||
      (rowIndex < 0 || graftRowArrayGetCount(raft->rowArray) <= rowIndex));

   row = graftRowArrayGetAt(raft->rowArray, rowIndex);
   greturnFalseIf(row->isDeleted);

   greturn gbTRUE;
}

/******************************************************************************
func: graftRowSetValue
******************************************************************************/
grlAPI Gb graftRowSetValue(Graft * const raft, Gindex const rowIndex, Gindex const colIndex, 
   Gvp const value)
{
   GraftRow *row;

   genter;

   greturnFalseIf(
      !raft                                                             ||
      (rowIndex < 0 || graftRowArrayGetCount(raft->rowArray) <= rowIndex) ||
      (colIndex < 0 || graftColArrayGetCount(raft->colArray) <= colIndex));

   row = graftRowArrayGetAt(raft->rowArray, rowIndex);
   gvpArrayUpdateAt(row->value, colIndex, &value);   
}

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _FileBackup
******************************************************************************/
static void _FileBackup(Graft const * const raft)
{
   genter;

   // Remove an old back if it exists.
   _FileBackupRemove(raft);

   // Rename the current table to be the back up table.
   gdirRename(raft->path, raft->pathBackup);

   greturn;
}

/******************************************************************************
func: _FileBackupRemove
******************************************************************************/
static void _FileBackupRemove(Graft const * const raft)
{
   genter;

   // Remove the old backup.
   gdirFileDestroy(raft->pathBackup);

   greturn;
}

/******************************************************************************
func: _FileOpen
******************************************************************************/
static Gfile *_FileOpen(Graft * const raft, GraftMode const mode)
{
   Gfile *file;

   genter;

   file = gfileOpen(raft->path, (GfileOpenMode) mode);
   
   greturn file;
}

/******************************************************************************
func: _Load
******************************************************************************/
static Gb _Load(Graft * const raft, Gfile * const file)
{
   Gb        result;
   Gindex    index;

   genter;

   result = gbFALSE;

   // Header line.
   stopIf(!_LoadHeader(raft, file));

   // Config lines
   stopIf(!_LoadConfig(raft, file));

   // For all rows...
   loopCount(index)
   {
      // Load the row.
      breakIf(!_LoadRow(raft, file, index));
   }

   result = gbTRUE;

STOP:
   greturn result;
}

/******************************************************************************
func: _LoadConfig
******************************************************************************/
static Gb _LoadConfig(Graft * const raft, Gfile * const file)
{
   Gb        result;
   Gindex    index;
   Gs       *line;
   GsArray  *sarray;
   GraftCol *col;

   genter;

   result = gbFALSE;

   // Get the column names.
   stopIf(!gfileGetS(file, gcTypeU1, line));
   sarray = gsCreateSplit(line, L'|');
   gsDestroy(line);

   // Create the column array.
   raft->colArray = graftColArrayCreate();
   graftColArraySetCount(raft->colArray, gsArrayGetCount(sarray));

   // Create the columns
   forCount(index, gsArrayGetCount(sarray))
   {
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
   forCount(index, gsArrayGetCount(raft->colArray))
   {
      // Get the column.
      col = graftColArrayGetAt(raft->colArray, index);

      // Get the string part.
      line = gsArrayGetAt(sarray, index);
      stopIf(!line);

      gsTrimU2(line, WHITESPACE_U2);

      // Start of a new type, potentially.
      if      (gsIsEqualA(line, "b"))  { col->type = graftTypeB;  }
      else if (gsIsEqualA(line, "n1")) { col->type = graftTypeN1; }
      else if (gsIsEqualA(line, "n2")) { col->type = graftTypeN2; }
      else if (gsIsEqualA(line, "n4")) { col->type = graftTypeN4; }
      else if (gsIsEqualA(line, "n8")) { col->type = graftTypeN8; }
      else if (gsIsEqualA(line, "i1")) { col->type = graftTypeI1; }
      else if (gsIsEqualA(line, "i2")) { col->type = graftTypeI2; }
      else if (gsIsEqualA(line, "i4")) { col->type = graftTypeI4; }
      else if (gsIsEqualA(line, "i8")) { col->type = graftTypeI8; }
      else if (gsIsEqualA(line, "r4")) { col->type = graftTypeR4; }
      else if (gsIsEqualA(line, "r8")) { col->type = graftTypeR8; }
      else if (*gsGetAt(line, 0) == L's')
      {
         gsEraseAt(line, 1, 0);

         col->type      = graftTypeS;
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
static Gb _LoadHeader(Graft * const raft, Gfile * const file)
{
   Gb       result;
   Gs      *line;
   GsArray *sarray;
   Gversion version;

   genter;

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
      raft->isBinary = gbFALSE;
   }
   else if (gsIsEqualA(line, "GRAFT_BF"))
   {
      raft->isBinary = gbTRUE;
   }
   else 
   {
      stop();
   }

   // What version of GAT file is this?
   line = gsArrayGetAt(sarray, 1);

   version = (Gversion) gsGetNHex(line);

   // We can't handle the future.
   stopIf(version > GraftVERSION);
   // For the future.  We currently on have the one version.
   //if (version < GraftVERSION)
   //{
   //   // Upgrade the file.
   //}

   // What version of the file.
   line = gsArrayGetAt(sarray, 2);

   raft->versionFile = (Gversion) gsGetNHex(line);

   // What version of the data.
   line = gsArrayGetAt(sarray, 3);

   raft->versionData = (Gversion) gsGetNHex(line);

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
static Gb _LoadRow(Graft * const raft, Gfile * const file, Gindex const rowIndex)
{
   Gindex           index,
                    bufferIndex;          
   GfileSetPosition positionResult;
   Gvp              value;
   Gv4              v4;
   GraftCol          *col;
   GraftRow          *row;
   
   genter;

   // Set the file position
   positionResult = gfileSetPosition(file, gpositionSTART, raft->offsetData + raft->rowByteCount * rowIndex);
   greturnFalseIf(positionResult != gfileSetPositionSUCCESS);

   // Get the row data.
   greturnFalseIf(gfileGet(file, raft->rowByteCount, raft->rowBuffer) != raft->rowByteCount);

   // Create the row.
   row = _RowCreate(raft);

   // Get the isDeleted flag.
   row->isDeleted = raft->rowBuffer[raft->dataByteCount] == 'T';

   // Get the data version.
   row->version = _VersionFromN1(&(raft->rowBuffer[raft->dataByteCount + 1]));

   // For all columns...
   bufferIndex = 0;
   forCount (index, graftColArrayGetCount(raft->colArray))
   {
      // Get the column.
      col = graftColArrayGetAt(raft->colArray, index);

      switch (col->type)
      {
      case graftTypeB:
         switch (raft->rowBuffer[bufferIndex])
         {
         case 'T': value.b = gbTRUE;      break;
         case 'F': value.b = gbFALSE;     break;
         default:  value.b = gbUNDEFINED; break;
         }
         break;

      case graftTypeN1:
         if (raft->rowBuffer[bufferIndex] == ' ')
         {
            value.n = _N1FromN1(&raft->rowBuffer[bufferIndex]);
         }
         else
         {
            value.n = _N1FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeN2:
         if (raft->rowBuffer[bufferIndex] == ' ')
         {
            value.n = _N2FromN1(&raft->rowBuffer[bufferIndex]);
         }
         else
         {
            value.n = _N2FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeN4:
         if (raft->rowBuffer[bufferIndex] == ' ')
         {
            value.n = _N4FromN1(&raft->rowBuffer[bufferIndex]);
         }
         else
         {
            value.n = _N4FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeN8:
         if (raft->rowBuffer[bufferIndex] == ' ')
         {
            value.n = _N8FromN1(&raft->rowBuffer[bufferIndex]);
         }
         else
         {
            value.n = _N8FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeI1:
         if (raft->rowBuffer[bufferIndex] == ' ' ||
             raft->rowBuffer[bufferIndex] == '-')
         {
            value.n = _N1FromN1(&raft->rowBuffer[bufferIndex]);

            if (raft->rowBuffer[bufferIndex] == '-')
            {
               value.i = -value.i;
            }
         }
         else
         {
            value.n = _N1FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeI2:
         if (raft->rowBuffer[bufferIndex] == ' ' ||
             raft->rowBuffer[bufferIndex] == '-')
         {
            value.n = _N2FromN1(&raft->rowBuffer[bufferIndex]);

            if (raft->rowBuffer[bufferIndex] == '-')
            {
               value.i = -value.i;
            }
         }
         else
         {
            value.n = _N2FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeI4:
         if (raft->rowBuffer[bufferIndex] == ' ' ||
             raft->rowBuffer[bufferIndex] == '-')
         {
            value.n = _N4FromN1(&raft->rowBuffer[bufferIndex]);

            if (raft->rowBuffer[bufferIndex] == '-')
            {
               value.i = -value.i;
            }
         }
         else
         {
            value.n = _N4FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeI8:
         if (raft->rowBuffer[bufferIndex] == ' ' ||
             raft->rowBuffer[bufferIndex] == '-')
         {
            value.n = _N8FromN1(&raft->rowBuffer[bufferIndex]);

            if (raft->rowBuffer[bufferIndex] == '-')
            {
               value.i = -value.i;
            }
         }
         else
         {
            value.n = _N8FromN1Hex(&raft->rowBuffer[bufferIndex]);
         }
         break;

      case graftTypeR4:
         v4.n = (Gn4) _N4FromN1Hex(&raft->rowBuffer[bufferIndex]);
#if grlSWAP_NEEDED == 1
         gswap4(&v4.n);
#endif
         value.r = (Grp) v4.r;
         break;

      case graftTypeR8:
         value.n = _N8FromN1Hex(&raft->rowBuffer[bufferIndex]);
#if grlSWAP_NEEDED == 1
         gswap8(&value.n);
#endif
         break;

      case graftTypeS:
         _SFromN1(&raft->rowBuffer[bufferIndex], col->byteCount);
      }

      bufferIndex += col->byteCount;
   }

   greturn gbTRUE;
}

/******************************************************************************
func: _NFromHex
******************************************************************************/
static Gnp _NFromHex(Gn1 const * const n)
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
func: _N1FromN1
******************************************************************************/
static Gnp _N1FromN1(Gn1 const * const n)
{
   Gnp v;

   genter;

   v = (Gnp) (n[1] - '0');

   greturn v;
}

/******************************************************************************
func: _N1FromN1Hex
******************************************************************************/
static Gnp _N1FromN1Hex(Gn1 const * const n)
{
   Gnp v;

   genter;
   
   v = 
      _NFromHex(&n[0]) <<  4 |
      _NFromHex(&n[1]);

   greturn v;
}

/******************************************************************************
func: _N1FromN
******************************************************************************/
static void _N1FromN(Gn1 * const n, Gcount const byteCount, Gn const value)
{
   Gindex index,
          nindex;
   Gcount shift[] = { 0, 8, 16, 24, 32, 40, 48, 56 };
   Gn1    nvalue;

   genter;

   nindex = byteCount - 1;
   for (index = 0; index < byteCount; index++)
   {
      nvalue = ((value >> shift[nindex]) >> 4) & 0xF;

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

      nvalue = ((value >> shift[nindex]) >> 0) & 0xF;

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
   }

   greturn;
}

/******************************************************************************
func: _N2FromN1
******************************************************************************/
static Gnp _N2FromN1(Gn1 const * const n)
{
   Gnp v;

   genter;

   v = 
      (Gnp) (n[1] - '0') * (Gnp) 100            +
      (Gnp) (n[2] - '0') * (Gnp) 10             +
      (Gnp) (n[3] - '0');

   greturn v;
}

/******************************************************************************
func: _N2FromN1Hex
******************************************************************************/
static Gnp _N2FromN1Hex(Gn1 const * const n)
{
   Gnp v;

   genter;
   
   v = 
      _NFromHex(&n[0]) << 12 |
      _NFromHex(&n[1]) <<  8 |
      _NFromHex(&n[2]) <<  4 |
      _NFromHex(&n[3]);

   greturn v;
}

/******************************************************************************
func: _N4FromN1
******************************************************************************/
static Gnp _N4FromN1(Gn1 const * const n)
{
   Gnp v;

   genter;

   v = 
      (Gnp) (n[1] - '0') * (Gnp) 1000000        + 
      (Gnp) (n[2] - '0') * (Gnp) 100000         +
      (Gnp) (n[3] - '0') * (Gnp) 10000          +
      (Gnp) (n[4] - '0') * (Gnp) 1000           +
      (Gnp) (n[5] - '0') * (Gnp) 100            +
      (Gnp) (n[6] - '0') * (Gnp) 10             +
      (Gnp) (n[7] - '0');

   greturn v;
}

/******************************************************************************
func: _N4FromN1Hex
******************************************************************************/
static Gnp _N4FromN1Hex(Gn1 const * const n)
{
   Gnp v;

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
func: _N8FromN1
******************************************************************************/
static Gnp _N8FromN1(Gn1 const * const n)
{
   Gnp v;

   genter;

   v = 
      (Gnp) (n[ 1] - '0') * (Gnp) 100000000000000 +
      (Gnp) (n[ 2] - '0') * (Gnp) 10000000000000  +
      (Gnp) (n[ 3] - '0') * (Gnp) 1000000000000   +
      (Gnp) (n[ 4] - '0') * (Gnp) 100000000000    +
      (Gnp) (n[ 5] - '0') * (Gnp) 10000000000     +
      (Gnp) (n[ 6] - '0') * (Gnp) 1000000000      +
      (Gnp) (n[ 7] - '0') * (Gnp) 100000000       +
      (Gnp) (n[ 8] - '0') * (Gnp) 10000000        +
      (Gnp) (n[ 9] - '0') * (Gnp) 1000000         + 
      (Gnp) (n[10] - '0') * (Gnp) 100000          +
      (Gnp) (n[11] - '0') * (Gnp) 10000           +
      (Gnp) (n[12] - '0') * (Gnp) 1000            +
      (Gnp) (n[13] - '0') * (Gnp) 100             +
      (Gnp) (n[14] - '0') * (Gnp) 10              +
      (Gnp) (n[15] - '0');

   greturn v;
}

/******************************************************************************
func: _N8FromN1Hex
******************************************************************************/
static Gnp _N8FromN1Hex(Gn1 const * const n)
{
   Gnp v;

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
static GraftRow *_RowCreate(Graft const * const raft)
{
   GraftRow *row;

   genter;

   row = gmemCreateType(GraftRow);
   greturnNullIf(!row);

   row->value = gvpArrayCreate(NULL, gbFALSE);
   if (!row->value)
   {
      _RowDestroy(raft, row);
      greturn NULL;
   }

   greturn row;
}

/******************************************************************************
func: _RowDestroy
******************************************************************************/
static void _RowDestroy(Graft const * const raft, GraftRow * const row)
{
   Gindex  index;
   GraftCol *col;

   genter;

   greturnVoidIf(!row);

   // For all the strings...
   forCount (index, index < graftColArrayGetCount(raft->colArray))
   {
      col = graftColArrayGetAt(raft->colArray, index);

      if (col->type == graftTypeS)
      {
         // Blank the strings.
         gsSetA(gvpArrayGetAt(row->value, index)->s, "");
      }
   }

   // Mark the row as deleted.
   gindexArrayAdd(raft->isUpdatedRowArray, row);
   gindexArrayAdd(raft->isDeletedRowArray, row);

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
static Gb _StoreAll(Graft * const raft)
{
   Gindex    index;
   Gb        result;
   Gfile    *file;

   genter;

   // Save the old file.
   _FileBackupRemove(raft);
   _FileBackup(      raft);

   // Open a new file.
   file = _FileOpen(raft, graftModeREAD_WRITE);

   // Write out the header.
   _StoreHeader(raft, file);

   // Write out the column name line.
   _StoreConfig(raft, file);

   // Write out the rows
   forCount(index, graftRowArrayGetCount(raft->rowArray))
   {
      _StoreRow(raft, file, index);
   }

   // Close the file.
   gfileClose(file);

   result = gbTRUE;

   greturn result;
}

/******************************************************************************
func: _StoreConfig
******************************************************************************/
static void _StoreConfig(Graft * const raft, Gfile * const file)
{
   Gindex    index;
   Gcount    byteCount;
   GraftCol *col;
   Gs       *line,
            *type;

   genter;

   // Write out the column names.
   line = gsCreate();
   forCount(index, graftColArrayGetCount(raft->colArray))
   {
      // Get the column.
      col = graftColArrayGetAt(raft->colArray, index);

      // Add the name.
      gsAppend(line, col->name);

      // Add the separator.
      if (index != graftColArrayGetCount(raft->colArray) - 1)
      {
         gsAppendC(line, '|');
      }
   }
   // Add the new line.
   gsAppendC(line, '\n');
   
   // Write the line.
   gfileSetS(file, gcTypeU1, line, NULL);
   gsFlush(line);


   // Write out the column type line.
   // delete flag + version.
   byteCount = 9;

   type = gsCreate();
   forCount(index, graftColArrayGetCount(raft->colArray))
   {
      // Clean the type.
      gsFlush(type);

      // Get the column.
      col = graftColArrayGetAt(raft->colArray, index);

      // Get the type.
      switch (col->type)
      {
      case graftTypeB:  gsAppendA(type, "b");  byteCount += 1;                         break;
      case graftTypeI1: gsAppendA(type, "i1"); byteCount += (raft->isBinary) ? 1 :  2; break;
      case graftTypeI2: gsAppendA(type, "i2"); byteCount += (raft->isBinary) ? 2 :  4; break;
      case graftTypeI4: gsAppendA(type, "i4"); byteCount += (raft->isBinary) ? 4 :  8; break;
      case graftTypeI8: gsAppendA(type, "i8"); byteCount += (raft->isBinary) ? 8 : 16; break;
      case graftTypeN1: gsAppendA(type, "n1"); byteCount += (raft->isBinary) ? 1 :  2; break;
      case graftTypeN2: gsAppendA(type, "n2"); byteCount += (raft->isBinary) ? 2 :  4; break;
      case graftTypeN4: gsAppendA(type, "n4"); byteCount += (raft->isBinary) ? 4 :  8; break;
      case graftTypeN8: gsAppendA(type, "n8"); byteCount += (raft->isBinary) ? 8 : 16; break;
      case graftTypeR4: gsAppendA(type, "r4"); byteCount += (raft->isBinary) ? 4 :  8; break;
      case graftTypeR8: gsAppendA(type, "r8"); byteCount += (raft->isBinary) ? 8 : 16; break;
      case graftTypeS:  
         gsAppendC(type, 's');  
         gsAppendN(type, col->byteCount);

         byteCount += col->byteCount; 
         break;
      }

      // Pad the type.
      gsPadTail(type, gsGetCount(col->name), L' ');

      // Add the separator.
      if (index != graftColArrayGetCount(raft->colArray) - 1)
      {
         gsAppendC(type, '|');
      }

      // Append the type.
      gsAppend(line, type);
   }
   // Add the line.
   gsAppendC(line, '\n');

   // Write the line.
   gfileSetS(file, gcTypeU1, line, NULL);
   gsDestroy(line);

   // Update the internal values.
   raft->dataByteCount = gsGetCount(line);
   raft->rowByteCount  = raft->dataByteCount + 9;

   // recreate the line buffer.
   gmemDestroy(raft->rowBuffer);
   raft->rowBuffer = gmemCreateTypeArray(Gn1, raft->rowByteCount);

   // Get the starting location of the data.
   raft->offsetData = gfileGetPosition(file);
}

/******************************************************************************
func: _StoreHeader
******************************************************************************/
static void _StoreHeader(Graft * const raft, Gfile * const file)
{
   Gn1 version[9];
   Gs *line;

   genter;

   // Create the line.
   line = gsCreate();

   // Add the header.
   if (raft->isBinary)
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
   _N1FromN(version, 4, 1);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, L'|');
   
   // Set the file version.
   _N1FromN(version, 4, raft->versionFile);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, L'|');
   
   // Set the data version.
   raft->versionData++;
   _N1FromN(version, 4, raft->versionData);
   gsAppendA(line, (Char *) version);
   gsAppendC(line, '\n');

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
static Gb _StoreRow(Graft * const raft, Gfile *file, Gindex const indexRow)
{
   Gindex    index,
             byteOffset;
   Gb        result;
   GraftCol *col;
   GraftRow *row;
   Gvp       vp;
#if grlSWAP_NEEDED == 1
   Gn2       n2;
   Gn4       n4;
#endif
   Gc1      *c1;
   Gcount    c1Count;

   genter;

   // Get the row.
   row = graftRowArrayGetAt(raft->rowArray, indexRow);
   greturnFalseIf(!row);

   // Update the version number of the row.
   row->version++;

   // For all columns...
   byteOffset = 0;
   forCount(index, graftColArrayGetCount(raft->colArray))
   {
      // Get the column.
      col = graftColArrayGetAt(raft->colArray, index);
      
      // Get the row value;
      vp = *gvpArrayGetAt(row->value, index);

#if grlSWAP_NEEDED == 1
      switch (col->type)
      {
      case graftTypeI2:   
      case graftTypeN2: 
         n2 = (Gn2) vp->n;
         gswap2(&n2);
         vp->n = n2;
         break;

      case graftTypeI4:   
      case graftTypeN4:   
      case graftTypeR4:
         n4 = (Gn4) vp->n;
         gswap4(&n4);
         vp->n = n4;
         break;

      case graftTypeI8:   
      case graftTypeN8:   
      case graftTypeR8:
         gswap8(&vp->n);
         break;
      }
#else
      switch (col->type)
      {
      case graftTypeI2:   
      case graftTypeN2: 
         n2 = (Gn2) vp->n;
         break;

      case graftTypeI4:   
      case graftTypeN4:   
      case graftTypeR4:
         n4 = (Gn4) vp->n;
         break;
      }
#endif

      // Create the binary.
      if (raft->isBinary)
      {
         switch (col->type)
         {
         case graftTypeB:
            switch (vp->b)
            {
            case gbFALSE:    raft->rowBuffer[byteOffset++] = 'F'; break;
            case gbTRUE:     raft->rowBuffer[byteOffset++] = 'T'; break;
            default:         raft->rowBuffer[byteOffset++] = ' '; break;
            }
            break;

         case graftTypeI1:   
         case graftTypeN1:   raft->rowBuffer[byteOffset++] = (Gn1) vp->n; break;
         case graftTypeI2:   
         case graftTypeN2:   gmemCopyOverType(n2, Gn2, &raft->rowBuffer[byteOffset]); byteOffset += 2; break;
         case graftTypeI4:   
         case graftTypeN4:   
         case graftTypeR4:   gmemCopyOverType(n4, Gn4, &raft->rowBuffer[byteOffset]); byteOffset += 4;break;
         case graftTypeI8:   
         case graftTypeN8:   
         case graftTypeR8:   gmemCopyOverType(n8, Gn8, &raft->rowBuffer[byteOffset]); byteOffset += 8; break;
         case graftTypeS:
            c1       = gsCreateU1(vp->s);
            c1Count  = gcGetCountU1(c1);
            gmemClearTypeArray(&raft->rowBuffer[byteOffset], Gn1, col->byteCount); 
            gmemCopyOverType(c1, gMIN(c1Count, col->byteCount), &raft->rowBuffer[byteOffset]); 
            break;
         }
      }
      // Create the ASCII.
      else
      {
         switch (col->type)
         {
         case graftTypeB:
            switch (vp->b)
            {
            case gbFALSE:     raft->rowBuffer[byteOffset] = 'F'; break;
            case gbTRUE:      raft->rowBuffer[byteOffset] = 'T'; break;
            default:          raft->rowBuffer[byteOffset] = ' '; break;
            }
            break;

         case graftTypeI1:   
         case graftTypeN1:   _N1FromN1(&raft->rowBuffer[byteOffset], vp->n); break;
         case graftTypeI2:   
         case graftTypeN2:   _N1FromN2(&raft->rowBuffer[byteOffset], vp->n); break;
         case graftTypeI4:   
         case graftTypeN4:   
         case graftTypeR4:   _N1FromN4(&raft->rowBuffer[byteOffset], vp->n); break;
         case graftTypeI8:   
         case graftTypeN8:   
         case graftTypeR8:   _N1FromN8(&raft->rowBuffer[byteOffset], vp->n); break;
         case graftTypeS:    
            c1       = gsCreateU1(vp->s);
            c1Count  = gcGetCountU1(c1);
            gmemClearTypeArray(&raft->rowBuffer[byteOffset], Gn1, col->byteCount); 
            gmemCopyOverType(c1, gMIN(c1Count, col->byteCount), &raft->rowBuffer[byteOffset]); 
            break;
         }
      }
   }

   greturn result;
}

/******************************************************************************
func: _StoreUpdatedRows
******************************************************************************/
static Gb _StoreUpdatedRows(Graft * const raft)
{
   Gfile *file;
   Gindex index,
          indexRow;
   Gb     result;

   genter;

   // Open the file
   file = _FileOpen(raft, graftModeREAD_WRITE);

   // Store the updated header line.
   _StoreHeader(raft, file);

   // Write out the modified rows.
   forCount(index, gindexArrayGetCount(raft->isUpdatedRowArray))
   {
      // Get the updated row.
      indexRow = *gindexArrayGetAt(raft->isUpdatedRowArray, index);

      // Store the updated row.
      _StoreRow(raft, file, indexRow);
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
