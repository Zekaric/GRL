/**************************************************************************************************
FILE:       giorub
AUTHOR:     Robbert de Groot
COPYRIGHT:  2005-2009, Mintec inc.

description:
GRL Repository of Unstructured Blocks.

A Basic file format to be used as a basis for higher level file
formats.

All data fits into multiples of 32 Byte (B) chunks.

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

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gn8     GioRubIndex;
typedef Gn4     GioRubSize;
typedef Gn4     GioRubCount;
typedef Gn4     GioRubVersion;

typedef enum
{
   gioRubHeaderTypeDATA,
   gioRubHeaderTypeFILE,
   gioRubHeaderTypeFREE
} GioRubHeaderType;

typedef struct
{
   Gid                   rubId;
   GioRubCount           rubChunkCount;
   Gn8                   uncommon;
} GioRubHeaderCommon;

typedef struct
{
   Gid                   rubId;
   GioRubCount           rubChunkCount;
   Gid                   dataId;
   GioRubCount           dataSize;
} GioRubHeaderData;

typedef struct
{
   Gid                   rubId;
   GioRubVersion         rubVersion;
   Gid                   fileId;
   GioRubVersion         fileVersion;
} GioRubHeaderFile;

typedef struct
{
   Gid                   rubId;
   GioRubCount           rubChunkCount;
   GioRubIndex           next;
} GioRubHeaderFree;

typedef union
{
   GioRubHeaderCommon    common;
   GioRubHeaderData      data;
   GioRubHeaderFile      file;
   GioRubHeaderFree      free;
} GioRubHeader;

typedef struct
{
   GioRubIndex           index;
   GioRubHeader          header;
} GioRubData;

typedef struct
{
   GioRubIndex           index;
   GioRubCount           chunkCount;
} GioRubFree;

typedef struct
{
   Gfile                *file;
   GioRubHeader          header;
   GioRubIndex           rootIndex;
   GioRubIndex           lastIndex;
   GvArray              *dataList;
   GvArray              *freeList;
   Gb                    isLocked;
   Gb                    isCorrupt;
} GioRub;

typedef union
{
   Gn1                   n1[16];
   Gn2                   n2[8];
   Gn4                   n4[4];
   Gn8                   n8[2];
   Gi1                   i1[16];
   Gi2                   i2[8];
   Gi4                   i4[4];
   Gi8                   i8[2];
} GioRubExtra;

typedef struct
{
   GioRubHeader          header;
   GioRubExtra           dataExtra;
} GioRubChunk;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gioRubClocData(GRUB, GID_DATATYPE, GRUBSIZE_SIZE)                        ((GioRubData *) gleakCloc(gioRubClocData_((GRUB), (GID_DATATYPE), (GRUBSIZE_SIZE)), gsizeof(GioRubData)))
#define gioRubOpen(GPATH_FILE, GRUBOPENMODE, GID_FILETYPE, GRUBVERSION_VERSION)  ((GioRub *)     gleakCloc(gioRubOpen_((GPATH_FILE), (GRUBOPENMODE), (GID_FILETYPE), (GRUBVERSION_VERSION)), gsizeof(GioRub)))

grlAPI void           gioRubClose(           GioRub       * const rub);
grlAPI GioRubData    *gioRubClocData_(       GioRub const * const rub, Gid const dataType, GioRubSize const size);

grlAPI Gb             gioRubDlocData(        GioRub const * const rub, GioRubData * const data);

grlAPI Gb             gioRubFlush(           GioRub const * const rub);

grlAPI GioRubData    *gioRubGetData(         GioRub       * const rub, GioRubIndex const index);
grlAPI Gb             gioRubGetDataList(     GioRub const * const rub, Gindex const index, GioRubChunk ** const chunk);
grlAPI Gcount         gioRubGetDataListCount(GioRub       * const rub);
grlAPI GioRubIndex    gioRubGetRootIndex(    GioRub const * const rub);
grlAPI Gid            gioRubGetType(         GioRub const * const rub);
grlAPI GioRubVersion  gioRubGetVersion(      GioRub const * const rub);

grlAPI Gb             gioRubIsCorrupt(       GioRub const * const rub);

grlAPI Gb             gioRubLockOff(         GioRub       * const rub);
grlAPI Gfile         *gioRubLockOn(          GioRub const * const rub, GioRubData const * const data);

grlAPI GioRub        *gioRubOpen_(           Gpath const * const path, GfileOpenMode const mode, Gid const fileType, GioRubVersion const fileVersion);

grlAPI Gb             gioRubSetRootIndex(    GioRub       * const rub, GioRubIndex const index);
       Gb             gioRubStart(           void);
       void           gioRubStop(            void);

// data routines.
grlAPI void           gioRubDataDloc(        GioRubData       * const data);

grlAPI GioRubIndex    gioRubDataGetIndex(    GioRubData const * const data);
grlAPI GioRubSize     gioRubDataGetSize(     GioRubData const * const data);
grlAPI Gid            gioRubDataGetType(     GioRubData const * const data);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
