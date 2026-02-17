/**************************************************************************************************
file:       giorub
author:     Robbert de Groot
copyright:  2005-2009, Mintec inc.

description:
GRL Repository of Unstructured Blocks.

A Basic file format to be used as a basis for higher level file formats that require the ability
to allocate and free chunks in the file and potentially truncate the file to become smaller.

All data fits into multiples of 32 Byte (B) chunks.  This might be wasteful but in the end it will
hopefully lead to easier hole finding and filling.  It makes debugging the file so much easier when
you can display the file in a hex editor showing 32 bytes per row.  Finding the RUB chunks becomes
trivial.

There are only 3 types of blocks in a RUB file.

The HEADER/INFO block which will be the first block of the file.  This will hold the GRUB header,
version, the file sub format header and version, and the pointer to the sub format root block.  And
also a pointer to the first Free block if any.

The DATA block is just a reserved chunk of memory.  RUB does not keep track of them, this is up to
the sub format to keep track of.  The contents is whatever the subformat wants to put in there.

The FREE (XXXX) block is a linked list of free block in the file.  When a program is adding and
removing blocks this could fragment the file and leave gaps.  The gaps are the free list.

Header Block:  First in the file.  Only one per file.
4 B  - "GRUB" Block header
4 B  - chunk count.  Always 1.
4 B  - "TYPE" Super format id.
4 B  - version
8 B  - Index to root chunk.
8 B  - Index to first free list block.
----
32 B = 1 chunk.

Free List Block:
4 B  - "XXXX"
4 B  - chunk count.
8 B  - Index of next free list chunk.  0 if end of list.
N B  - zeroed data.
----
Min 32 B = 1 chunk.

Data Block:
4 B  - "DATA"
4 B  - chunk count.
4 B  - "TYPE" super format data type id.
4 B  - raw size of data.
N B  - Data.
----
Min 32 B = 1 chunk.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2005, Robbert de Groot

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
#define FREE_CLEARS     1

#define FILEHEADER      "GRUB"
#define FREEHEADER      "XXXX"
#define DATAHEADER      "DATA"
#define FILEVERSION     1
#define CHUNKSIZE       32
#define DATAHEADERSIZE  16
#define FREEHEADERSIZE  16

/**************************************************************************************************
variable:
**************************************************************************************************/
static Gid            _fileId = { 0 },
                      _freeId = { 0 },
                      _dataId = { 0 };
static GioRubHeader   _freeHeader;

/**************************************************************************************************
prototype:
**************************************************************************************************/
static Gb          _BlockReadHeader(         GioRub       * const rub, GioRubHeader       * const header, GioRubHeaderType const type);
static Gb          _BlockWriteHeader(        GioRub const * const rub, GioRubHeader const * const header, GioRubHeaderType const type);

static void        _DataListDestroy(         GioRub       * const rub);
static Gb          _DataListRead(            GioRub       * const rub);
static Gb          _DataListReadChunk(       GioRub       * const rub, GioRubIndex const index, GioRubChunk * const chunk);
static Gb          _DataWriteClear(          GioRub const * const rub, GioRubData const * const data);
static Gb          _DataWriteHeader(         GioRub const * const rub, GioRubData       * const data);

static GioRubData *_FreeListCreateChunk(     GioRub const * const rub, Gid const dataType, const GioRubSize size);
static void        _FreeListDestroy(         GioRub const * const rub);
static Gb          _FreeListDestroyChunk(    GioRub const * const rub, GioRubData const * const data);
static GioRubIndex _FreeListGetFirstIndex(   GioRub const * const rub);
static Gb          _FreeListRead(            GioRub       * const rub, GioRubIndex const index);
static Gb          _FreeListWrite(           GioRub const * const rub);
static Gb          _FreeWriteClear(          GioRub const * const rub, GioRubIndex const index, const GioRubCount chunkCount);
static Gb          _FreeWriteHeader(         GioRub const * const rub, GioRubIndex const index, const GioRubCount chunkCount, GioRubFree const * const next);

static GioRubCount _GetChunkCount(           GioRubSize const size);

static Gb          _SetPosition(             GioRub const * const rub, GioRubIndex const index, GioRubCount const offset);

static Gb          _WriteHeader(             GioRub const * const rub);

/**************************************************************************************************
global:
function
**************************************************************************************************/
/**************************************************************************************************
func: gioRubClose

Close the chunk file.

param:
file
   GioRub *
   in
   The file.
**************************************************************************************************/
grlAPI void gioRubClose(GioRub * const rub)
{
   genter;

   greturnIf(!rub);

   rub->isLocked = gbFALSE;

   // Write out the latest information.
   _WriteHeader(rub);//lint !e534

   // Truncate file if possible.

   // Clean up.
   _FreeListDestroy(rub);

   _DataListDestroy(rub);

   // Close the file.
   gfileClose(rub->file);

   gmemDloc(rub);

   greturn;
}

/**************************************************************************************************
func: gioRubClocData

Create a new data chunk.

param:
file
   GioRub *
   in
   The file.

dataType
   char *
   in
   The type.

size
   Gn4
   in
   The size of the data chunk.

return:
GioRubData *
   The data chunk information.
**************************************************************************************************/
grlAPI GioRubData *gioRubClocData_(GioRub const * const rub, Gid const dataType, GioRubSize const size)
{
   GioRubData *data;

   genter;

   greturnNullIf(
      !rub                 ||
      !gidIsGood(dataType) ||
      size == 0            ||
      rub->isLocked);

   // Get a chunk.
   data = _FreeListCreateChunk(rub, dataType, size);

   greturn data;
}

/**************************************************************************************************
func: gioRubDlocData

Free up a data chunk.

param:
file
   GioRub *
   in
   The file.

data
   GioRubData *
   in
   The data.
**************************************************************************************************/
grlAPI Gb gioRubDlocData(GioRub const * const rub, GioRubData * const data)
{
   genter;

   greturnFalseIf(
      !rub  ||
      !data ||
      rub->isLocked);

   // Destroy the data from the file.
   greturnValIf(!_FreeListDestroyChunk(rub, data), gbFALSE);

   gioRubDataDloc(data);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRubFlush

Make sure the header and free list are accurate.

param:
file
   GioRub *
   in
   The file.
**************************************************************************************************/
grlAPI Gb gioRubFlush(GioRub const * const rub)
{
   genter;

   greturnFalseIf(!_WriteHeader(rub));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRubGetData

Get a data chunk from the file.

param:
file
   GioRub *
   in
   The file.

index
   GioRubIndex
   in
   The index of the chunk.

return:
GioRubData *
**************************************************************************************************/
grlAPI GioRubData *gioRubGetData(GioRub * const rub, const GioRubIndex index)
{
   GioRubData  *data;
   GioRubHeader header;

   genter;

   greturnNullIf(
      !rub       ||
      index == 0 ||
      rub->isLocked);

   // Set the file position.
   greturnNullIf(!_SetPosition(rub, index, 0));

   // Get the header.
   greturnNullIf(!_BlockReadHeader(rub, &header, gioRubHeaderTypeDATA));

   // Header isn't recognized as a rub header.
   greturnNullIf(!gidIsEqual(header.data.rubId, _dataId));

   // Get the chunk information.
   data = gmemClocType(GioRubData);
   greturnNullIf(!data);

   data->index  = index;
   data->header = header;

   greturn data;
}

/**************************************************************************************************
func: gioRubGetDataList
**************************************************************************************************/
grlAPI Gb gioRubGetDataList(GioRub const * const rub, Gindex const index, GioRubChunk ** const chunk)
{
   genter;

   greturnFalseIf(
      !rub  ||
      !chunk);

   *chunk = (GioRubChunk *) gvGetP(gvArrayGetAt(rub->dataList, index));
   greturnFalseIf(!(*chunk));

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRubGetDataListCount
**************************************************************************************************/
grlAPI Gcount gioRubGetDataListCount(GioRub * const rub)
{
   genter;

   greturn0If(!rub);

   // Data chunk list not created yet.
   if (!rub->dataList)
   {
      // Create the list.
      rub->dataList = gvArrayCloc("GioRubData", NULL, gbTRUE);
      greturn0If(!rub->dataList);

      // Iterate over the Rub file to find all the data chunks.
      _DataListRead(rub);
   }

   greturn gvArrayGetCount(rub->dataList);
}

/**************************************************************************************************
func: gioRubGetType

Get the type of the file.

param:
file
   GioRub *
   in
   The file.

return:
char *
   4 characters.
**************************************************************************************************/
grlAPI Gid gioRubGetType(GioRub const * const rub)
{
   genter;

   returnValIf(!rub, GidNONE);

   greturn(rub->header.file.fileId);
}

/**************************************************************************************************
func: gioRubGetVersion

Return the version of the chunk file.

param:
file
   GioRub *
   in
   The file.

return:
int
**************************************************************************************************/
grlAPI Gn4 gioRubGetVersion(GioRub const * const rub)
{
   genter;

   greturn0If(!rub);

   greturn(rub->header.file.fileVersion);
}

/**************************************************************************************************
func: gioRubGetRootIndex

Get the root index of the file.

param:
file
   GioRub *
   in
   The file.

return:
GioRubIndex
   If 0 then root index has not been set yet or file passed in is bad.
**************************************************************************************************/
grlAPI GioRubIndex gioRubGetRootIndex(GioRub const * const rub)
{
   genter;

   greturn0If(!rub);

   greturn(rub->rootIndex);
}

/**************************************************************************************************
func: gioRubIsCorrupt
**************************************************************************************************/
grlAPI Gb gioRubIsCorrupt(GioRub const * const rub)
{
   genter;

   greturnFalseIf(!rub);

   greturn(rub->isCorrupt);
}

/**************************************************************************************************
func: gioRubLockOff

Finished the lock operation.

param:
file
   GioRub *
   in
   The file.
**************************************************************************************************/
grlAPI Gb gioRubLockOff(GioRub * const rub)
{
   genter;

   greturnFalseIf(!rub);

   rub->isLocked = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: grubLock

Lock the file to gain direct write access to the file.  The
position in the file will be at the start of the data's location.

param:
file
   GioRub *
   in
   The file.

return:
File *
**************************************************************************************************/
grlAPI Gfile *gioRubLockOn(GioRub const * const rub, GioRubData const * const data)
{
   genter;

   greturnNullIf(
      !rub ||
      !data);

   // Set the file position.
   greturnValIf(!_SetPosition(rub, data->index, DATAHEADERSIZE), NULL);

   greturn rub->file;
}

/**************************************************************************************************
func: grubOpen

Open an existing file.
**************************************************************************************************/
grlAPI GioRub *gioRubOpen_(Gpath const * const path, GfileOpenMode const mode, Gid const fileType,
   GioRubVersion const fileVersion)
{
   GioRub      *rub;
   GioRubHeader header;
   GioRubIndex  index;
   GioRubFree  *freeData;

   genter;

   greturnValIf(!path, NULL);

   // Create the file.
   rub = gmemClocType(GioRub);
   greturnNullIf(!rub);

   rub->header.file.rubId       = _fileId;
   rub->header.file.rubVersion  = FILEVERSION;
   rub->freeList                = gvArrayCloc("GioRubFree", NULL, gbFALSE);

   // Create a new file.
   if (mode == gfileOpenModeREAD_WRITE_NEW)
   {
      // Init.
      rub->file = gfileOpen(path, gfileOpenModeREAD_WRITE_NEW);
      if (!rub->file)
      {
         gioRubClose(rub);
         greturn NULL;
      }

      rub->header.file.fileId      = fileType;
      rub->header.file.fileVersion = fileVersion;

      // Add the dummy tail free chunk.
      freeData = gmemClocType(GioRubFree);
      greturnNullIf(!freeData);

      freeData->index      = 1;
      freeData->chunkCount = Gn4MAX;
      stopIf(!gvArrayAddAt(rub->freeList, 0, gvFromP(freeData)));

      stopIf(!_WriteHeader(rub));

      // Short cut, nothing further to do in the function.
      greturn rub;
   }

   // Open the file.
   if      (mode == gfileOpenModeREAD_ONLY)
   {
      rub->file = gfileOpen(path, gfileOpenModeREAD_ONLY);
   }
   else if (mode == gfileOpenModeREAD_WRITE)
   {
      rub->file = gfileOpen(path, gfileOpenModeREAD_WRITE);
   }

   stopIf(!rub->file);

   // Read in the information.
   stopIf(!_BlockReadHeader(rub, &header, gioRubHeaderTypeFILE));

   stopIf(
      !gidIsEqual(header.file.fileId, _fileId) ||
      header.file.fileVersion != 1);

   // Read in the root data index and the first free list item.
   stopIf(!gfileGet8(rub->file, 1, (Gp *) &(rub->rootIndex)));
   stopIf(!gfileGet8(rub->file, 1, (Gp *) &index));

   stopIf(!_FreeListRead(rub, index));

   greturn rub;

STOP:
   // Clean up on fail.
   gvArrayForEach(rub->freeList, (GrlForEachFunc) gmemDloc);//lint !e534 !e929 !e960
   gvArrayDloc(   rub->freeList);

   gfileClose(rub->file);

   gmemDloc(rub);

   greturn NULL;
}

/**************************************************************************************************
func: gioRubSetRootIndex

Set the root index for the file.

param:
file
   GioRub *
   in
   The file.

index
   GioRubIndex
   in
   Index to new root.
**************************************************************************************************/
grlAPI Gb gioRubSetRootIndex(GioRub * const rub, const GioRubIndex index)
{
   genter;

   greturnFalseIf(!rub);

   rub->rootIndex = index;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRubStart
**************************************************************************************************/
Gb gioRubStart(void)
{
   _fileId = gidGetFromC(FILEHEADER);
   _freeId = gidGetFromC(FREEHEADER);
   _dataId = gidGetFromC(DATAHEADER);

   _freeHeader.free.rubId = _freeId;

   return gbTRUE;
}

/**************************************************************************************************
func: gioRubStop
**************************************************************************************************/
void gioRubStop(void)
{
   // Nothing.
}

/**************************************************************************************************
Data routines.
**************************************************************************************************/
/**************************************************************************************************
func: gioRubDataDloc

data specific routines.

param:
data
   GioRubData *
   in
   The data to destroy.

return:
int
**************************************************************************************************/
grlAPI void gioRubDataDloc(GioRubData * const data)
{
   genter;

   gmemDloc(data);

   greturn;
}

/**************************************************************************************************
func: gioRubDataGetIndex

Get the index of the chunk for the data.

param:
data
   GioRubData *
   in
   The file.

return:
GioRubIndex
**************************************************************************************************/
grlAPI GioRubIndex gioRubDataGetIndex(GioRubData const * const data)
{
   genter;

   greturn0If(!data);

   greturn data->index;
}

/**************************************************************************************************
func: gioRubDataGetSize

Get the raw size of the data.

param:
data
   GioRubData *
   in
   The file.

return:
Gn4
**************************************************************************************************/
grlAPI GioRubSize gioRubDataGetSize(GioRubData const * const data)
{
   genter;

   greturn0If(!data);

   greturn data->header.data.dataSize;
}

/**************************************************************************************************
func: gioRubDataGetType

Get the type of the data chunk.

param:
data
   GioRubData *
   in
   The file.

return:
char *
   4 characters.
**************************************************************************************************/
grlAPI Gid gioRubDataGetType(GioRubData const * const data)
{
   genter;

   greturnValIf(!data, GidNONE);

   greturn data->header.data.dataId;
}

/**************************************************************************************************
Local Functions.
**************************************************************************************************/
/**************************************************************************************************
func: _BlockReadHeader

Read in the chunk header.

param:
file
   GioRub *
   in
   The file.

header, chunkCount
   char *, Gn4
   in, in
   The chunk header.

return:
int
**************************************************************************************************/
static Gb _BlockReadHeader(GioRub * const rub, GioRubHeader * const header, GioRubHeaderType const type)
{
   genter;

   type;

   greturnFalseIf(
      gfileGet(rub->file, gsizeof(GioRubHeader), header) != gsizeof(GioRubHeader));

#if grlSWAP_NEEDED == 1
   switch (type)
   {
   case gioRubHeaderTypeDATA:
      gswap4(&header->data.rubChunkCount);
      gswap4(&header->data.dataSize);
      break;

   case gioRubHeaderTypeFILE:
      gswap4(&header->file.rubVersion);
      gswap4(&header->file.fileVersion);
      break;

   case gioRubHeaderTypeFREE:
      gswap4(&header->free.rubChunkCount);
      gswap8(&header->free.next);
      break;
   }
#endif

   greturn gbTRUE;
}

/**************************************************************************************************
func: _BlockWriteHeader

Read in the chunk header.
**************************************************************************************************/
static Gb _BlockWriteHeader(GioRub const * const rub, GioRubHeader const * const header, GioRubHeaderType const type)
{
   GioRubHeader htemp;

   genter;

   htemp = *header;

#if grlSWAP_NEEDED == 1
   switch (type)
   {
   case gioRubHeaderTypeDATA:
      gswap4(&htemp.data.rubChunkCount);
      gswap4(&htemp.data.dataSize);
      break;

   case gioRubHeaderTypeFILE:
      gswap4(&htemp.file.rubVersion);
      gswap4(&htemp.file.fileVersion);
      break;

   case gioRubHeaderTypeFREE:
      gswap4(&htemp.free.rubChunkCount);
      gswap8(&htemp.free.next);
      break;
   }
#endif

   greturnFalseIf(!gfileSet(rub->file, gsizeof(GioRubHeader), &htemp, NULL));

   greturn gbTRUE;
}

/**************************************************************************************************
func: _DataListDestroy
**************************************************************************************************/
static void _DataListDestroy(GioRub * const rub)
{
   genter;

   gvArrayForEach(rub->dataList, gmemDloc);
   gvArrayDloc(rub->dataList);
   rub->dataList = NULL;

   greturn;
}

/**************************************************************************************************
func: _DataListRead
**************************************************************************************************/
static Gb _DataListRead(GioRub * const rub)
{
   Gindex       loopIndex;
   GioRubIndex  index;
   GioRubChunk *chunk;
   GfileIndex   fileSize;

   genter;

   // Get the file size.
   fileSize = gfileGetSize(rub->file);

   chunk = NULL;
   index = 1;
   loopCount(loopIndex)
   {
      // End of file.
      breakIf(index * CHUNKSIZE >= (GioRubIndex) fileSize);

      // Create a new chunk
      if (chunk == NULL)
      {
         chunk = gmemClocType(GioRubChunk);
      }

      greturnFalseIf(!_DataListReadChunk(rub, index, chunk));

      // Only fetch data chunks
      if      (gidIsEqual(chunk->header.common.rubId, _dataId))
      {
         // Append to the data list.
         gvArrayAddEnd(rub->dataList, gvFromP(chunk));

         chunk = NULL;

         // Next chunk location.
         index += chunk->header.data.rubChunkCount;
      }
      // Just skip over free chunks.
      else if (gidIsEqual(chunk->header.common.rubId, _freeId))
      {
         // Next chunk location.
         index += chunk->header.data.rubChunkCount;
      }
      // Unrecognized id.
      else
      {
         // Shouldn't really happen but file may be corrupted somehow.
         debugHalt("Potentially bad RUB file.");

         // Mark as corrupted/malformed.
         rub->isCorrupt = gbTRUE;

         // Just move forward one chunk until we find something readable.
         index++;
      }
   }

   gmemDloc(chunk);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _DataListReadChunk
**************************************************************************************************/
static Gb _DataListReadChunk(GioRub * const rub, GioRubIndex const index, GioRubChunk * const chunk)
{
   genter;

   greturnFalseIf(!_SetPosition(rub, index, 0));

   greturnFalseIf(!gfileGet(rub->file, gsizeof(GioRubChunk), chunk) != gsizeof(GioRubChunk));

#if grlSWAP_NEEDED == 1
   // We are just assuming this is a data chunk.  Even if it isn't the dataSize change won't
   // make a difference as we are only wanting data chunks.
   gswap4(&chunk->header.data.rubChunkCount);
   gswap4(&chunk->header.data.dataSize);
#endif

   greturn gbTRUE;
}

/**************************************************************************************************
func: _DataWriteClear

zero out the data buffer.

param:
file
   GioRub *
   in
   The file.

data
   GioRubData *
   in
   The data.

return:
int
**************************************************************************************************/
static Gb _DataWriteClear(GioRub const * const rub, GioRubData const * const data)
{
#if 1 // For speed, don't clear the contents.
   genter;

   greturnFalseIf(!_SetPosition(rub, data->index, DATAHEADERSIZE));

   // Zero out the data.
#if 0 // Zero out only the first chunk.
   greturnFalseIf(
      !gfileSetValue(
         rub->file,
         CHUNKSIZE - DATAHEADERSIZE,
         (Gn1) 0,
         NULL));
#else // Zero out the whole chunk.
   greturnFalseIf(
      !gfileSetValue(
         rub->file,
         data->header.data.rubChunkCount * CHUNKSIZE - DATAHEADERSIZE,
         (Gn1) 0,
         NULL));
#endif

   greturn gbTRUE;

#else

   return gbTRUE;
#endif
}

/**************************************************************************************************
func: _DataWriteHeader

Write out the data header.

param:
file
   GioRub *
   in
   The file.

data
   GioRubData *
   in
   The data.

return:
int
**************************************************************************************************/
static Gb _DataWriteHeader(GioRub const * const rub, GioRubData * const data)
{
   genter;

   greturnValIf(!_SetPosition(rub, data->index, 0), gbFALSE);

   data->header.data.rubId         = _dataId;
   data->header.data.rubChunkCount = _GetChunkCount(data->header.data.dataSize + DATAHEADERSIZE);

   greturnValIf(!_BlockWriteHeader(rub, &data->header, gioRubHeaderTypeDATA), gbFALSE);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _FreeListCreateChunk

Request a new chunk from the file.  Reusing the free list if a large
enough chunk is available.

param:
file
   GioRub *
   in
   The file.

dataType
   char *
   in
   The type of data for the chunk.

size
   Gn4
   in
   The raw size of the data.

return:
GioRubData *
**************************************************************************************************/
static GioRubData *_FreeListCreateChunk(GioRub const * const rub, Gid const dataType, const GioRubSize size)
{
   Gindex    index;
   Gn4       newCount;
   GioRubFree *freeData;
   GioRubData *data;

   genter;

   // Include the header in the chunk count.
   newCount = _GetChunkCount(size + DATAHEADERSIZE);

   forCount(index, gvArrayGetCount(rub->freeList))
   {
      freeData = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index));

      // Found a match.
      if (freeData->chunkCount >= newCount)
      {
         data = gmemClocType(GioRubData);
         greturnNullIf(!data);

         data->index                = freeData->index;
         data->header.data.dataSize = size;
         data->header.data.dataId   = dataType;

         greturnValIf(!_DataWriteHeader(rub, data), NULL);

         greturnValIf(!_DataWriteClear(rub, data), NULL);

         // Last free information alwasy Gn4MAX
         if (freeData->chunkCount != Gn4MAX)
         {
            freeData->chunkCount -= newCount;
         }

         if (freeData->chunkCount == 0)
         {
            gmemDloc(freeData);
            gvArrayEraseAt(rub->freeList, 1, index); //lint !e534
         }
         else
         {
            freeData->index += newCount;
         }

         greturn data;
      }
   }

   greturn NULL;
}

/**************************************************************************************************
func: _FreeListDestroy

Clean up the free list.

param:
file
   GioRub *
   in
   The file.
**************************************************************************************************/
static void _FreeListDestroy(GioRub const * const rub)
{
   Gindex    index;
   GioRubFree *freeData;

   genter;

   forCount(index, gvArrayGetCount(rub->freeList))
   {
      freeData = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index));
      gmemDloc(freeData);
   }

   gvArrayDloc(rub->freeList);
   greturn;
}

/**************************************************************************************************
func: _FreeListDestroyChunk

Release a chunk to the free list.

param:
file
   GioRub *
   in
   The file.

data
   GioRubData *
   in
   The data chunk.
**************************************************************************************************/
static Gb _FreeListDestroyChunk(GioRub const * const rub, GioRubData const * const data)
{
   Gindex    index;
   Gb        combined;
   GioRubFree *freeData,
            *ftemp;

   genter;

   // Create the free block info.
   freeData = gmemClocType(GioRubFree);
   greturnFalseIf(!freeData);

   freeData->index      = data->index;
   freeData->chunkCount = _GetChunkCount(data->header.data.dataSize + DATAHEADERSIZE);

   // Find the right place in the free list for the new block.
   combined = gbFALSE;
   forCount(index, gvArrayGetCount(rub->freeList))
   {
      ftemp = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index));

      // Merge with following chunk.
      if (freeData->index + freeData->chunkCount == ftemp->index)
      {
         ftemp->index       = freeData->index;

         if (ftemp->chunkCount != Gn4MAX)
         {
            ftemp->chunkCount += freeData->chunkCount;
         }

         gmemDloc(freeData);
         freeData = ftemp;
         combined = gbTRUE;
         break;
      }
      // Merge with previous chunk.
      else if (ftemp->index + ftemp->chunkCount == freeData->index)
      {
         if (ftemp->chunkCount != Gn4MAX)
         {
            ftemp->chunkCount += freeData->chunkCount;
         }

         gmemDloc(freeData);
         freeData = ftemp;
         combined = gbTRUE;
         break;
      }
      else if (freeData->index < ftemp->index)
      {
         break;
      }
   }

   // Add to the list if the freed chunk didn't merge with another chunk.
   if (!combined)
   {
      greturnFalseIf(!gvArrayAddAt(rub->freeList, index, gvFromP(freeData)));
   }

   // Check if merged chunk merges with a following chunk.
   ftemp = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index + 1));
   if (ftemp &&
         freeData->index + freeData->chunkCount == ftemp->index)
   {
      if (ftemp->chunkCount == Gn4MAX)
      {
         freeData->chunkCount = Gn4MAX;
      }
      else
      {
         freeData->chunkCount += ftemp->chunkCount;
      }

      gmemDloc(ftemp);
      greturnFalseIf(!gvArrayEraseAt(rub->freeList, 1, index + 1));
   }

   // Write out the new chunk.
   ftemp = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index + 1));
   greturnValIf(!_FreeWriteHeader(rub, freeData->index, freeData->chunkCount, ftemp), gbFALSE);

   // Write out the previous chunk.
   ftemp = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index - 1));
   if (ftemp)
   {
      greturnValIf(!_FreeWriteHeader(rub, ftemp->index, ftemp->chunkCount, freeData), gbFALSE);
   }
   greturn gbTRUE;
}

/**************************************************************************************************
func: _FreeListGetFirstIndex

Get the first index of the free list.

param:
file
   GioRub *
   in
   The file.

return:
GioRubIndex
**************************************************************************************************/
static GioRubIndex _FreeListGetFirstIndex(GioRub const * const rub)
{
   GioRubFree const *freeData;

   genter;

   if (gvArrayGetCount(rub->freeList) == 0)
   {
      greturn 0;
   }

   freeData = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, 0));

   greturn freeData->index;
}

/**************************************************************************************************
func: _FreeListRead

Read in the free list.

param:
file
   GioRub *
   in
   The file.

index
   GioRubIndex
   in
   The index for the first block.

return:
int
**************************************************************************************************/
static Gb _FreeListRead(GioRub * const rub, const GioRubIndex index)
{
   Gindex         loopIndex;
   GioRubHeader   header;
   GioRubFree    *freeData;

   genter;

   // Set up the initial read.
   header.free.next = index;

   loopCount(loopIndex)
   {
      // Nothing more to do.
      breakIf(!index ||
               index == Gn4MAX);

      // Set the position to the start of the free item.
      greturnValIf(!_SetPosition(rub, header.free.next, 0), gbFALSE);

      // Read in the header.
      greturnValIf(!_BlockReadHeader(rub, &header, gioRubHeaderTypeFREE), gbFALSE);

      // Test to see if the header is properl.
      greturnValIf(!gidIsEqual(header.free.rubId, _freeId), gbFALSE);

      // Couldn't allocate memory for the free chunk.
      freeData = gmemClocType(GioRubFree);
      greturnFalseIf(!freeData);

      freeData->index      = index;
      freeData->chunkCount = header.free.rubChunkCount;

      // Add to the list.
      greturnValIf(!gvArrayAddEnd(rub->freeList, gvFromP(freeData)), gbFALSE);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _FreeListWrite

Write out the free list.

param:
file
   GioRub *
   in
   The file.

return:
int
**************************************************************************************************/
static Gb _FreeListWrite(GioRub const * const rub)
{
   Gindex          index;
   GioRubFree const *freeData,
                  *ftemp;

   genter;

   // For all items.
   ftemp = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, 0));
   forCount(index, gvArrayGetCount(rub->freeList))
   {
      freeData = ftemp;
      ftemp    = (GioRubFree *) gvGetP(gvArrayGetAt(rub->freeList, index + 1));

      stopIf(!_FreeWriteHeader(rub, freeData->index, freeData->chunkCount, ftemp));

      stopIf(!_FreeWriteClear(rub, freeData->index, freeData->chunkCount));
   }

   greturn gbTRUE;

STOP:
   debugHalt("Error");
   greturn gbFALSE;
}

/**************************************************************************************************
func: _FreeWriteClear

clear out the free chunk.

param:
file
   GioRub *
   in
   The file

index, chunkCount
   GioRubIndex, Gn4
   in, in
   The chunk to write out and the next chunk in line.
**************************************************************************************************/
static Gb _FreeWriteClear(GioRub const * const rub, GioRubIndex const index, GioRubCount const chunkCount)
{
   genter;

   stopIf(!_SetPosition(rub, index, FREEHEADERSIZE));

   // Zero out the first chunk.
   stopIf(
      !gfileSetValue(
         rub->file,
         CHUNKSIZE - FREEHEADERSIZE,
         (Gn1) 0,
         NULL));

#if FREE_CLEARS
   /*rdg This was initially #if defined(_DEBUG)
   ** I kind of like the blanking out of data.  I'll keep it in even in
   ** production until we need more speed for whatever reason.*/
   if (chunkCount != Gn4MAX)
   {
      // Zero out the remaining chunks.
      stopIf(
         !gfileSetValue(
            rub->file,
            chunkCount * CHUNKSIZE,
            (Gn1) 0,
            NULL));
   }
#endif

   greturn gbTRUE;

STOP:
   debugHalt("Error");
   greturn gbFALSE;
}

/**************************************************************************************************
func: _FreeWriteHeader

Write out a free chunk.

param:
file
   GioRub *
   in
   The file

current, next
   GioRubFree *, GioRubFree *
   in, in
   The chunk to write out and the next chunk in line.

return:
int
**************************************************************************************************/
static Gb _FreeWriteHeader(GioRub const * const rub, GioRubIndex const index, GioRubCount const chunkCount, GioRubFree const * const next)
{
   genter;

   stopIf(!_SetPosition(rub, index, 0));

   _freeHeader.free.rubChunkCount = chunkCount;
   _freeHeader.free.next          = 0;
   if (next)
   {
      _freeHeader.free.next = next->index;
   }

   stopIf(!_BlockWriteHeader(rub, &_freeHeader, gioRubHeaderTypeFREE));

   greturn gbTRUE;

STOP:
   debugHalt("Error");
   greturn gbFALSE;
}

/**************************************************************************************************
func: _GetChunkCount

Get the number of chunks for a given size.

param:
size
   Gn4
   in
   The raw size.

return:
Gn4
**************************************************************************************************/
static GioRubCount _GetChunkCount(GioRubSize const size)
{
   genter;

   if (size % CHUNKSIZE)
   {
      greturn (size / CHUNKSIZE) + 1;
   }

   greturn(size / CHUNKSIZE);
}

/**************************************************************************************************
func: _SetPosition

Set the position into the file.

param:
file
   GioRub *
   in
   The file.

index
   GioRubIndex
   in
   The chunk index.

offset
   Gn4
   in
   The offset into the chunk.

return:
int
**************************************************************************************************/
static Gb _SetPosition(GioRub const * const rub, GioRubIndex const index, GioRubCount const offset)
{
   genter;

   if (gfileSetPosition(rub->file, gpositionSTART, (Goffset) (index * CHUNKSIZE + offset)) !=
         gfileSetPositionSUCCESS)
   {
      debugHalt("gfileSetPosition failed");
      greturn gbFALSE;
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: _WriteHeader

Write out the file header.

param:
file
   GioRub *
   in
   The file.

return:
int
**************************************************************************************************/
static Gb _WriteHeader(GioRub const * const rub)
{
   GioRubIndex index;

   genter;

   stopIf(!_SetPosition(rub, (GioRubIndex) 0, (Gn4) 0));

   // Chunk header.
   stopIf(!_BlockWriteHeader(rub, &rub->header, gioRubHeaderTypeFILE));

   // Root index.
   stopIf(!gfileSet8(rub->file, 1, (Gp *) &(rub->rootIndex))); //lint !e960 !e9005

   // Free list.
   index = _FreeListGetFirstIndex(rub);
   stopIf(!gfileSet8(rub->file, 1, (Gp *) &index)); //lint !e960 !e9005

   stopIf(!_FreeListWrite(rub));

   greturn gbTRUE;

STOP:
   debugHalt("Error");
   greturn gbFALSE;
}
