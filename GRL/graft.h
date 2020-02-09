/******************************************************************************
file:       Graft
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL Repository As A Flat Table routines

What is a R.A.F.T?

It is a simple self describing flat table file that uses either ASCII or Binary
for the storage of values.  If storage is in ASCII, for the most part it is 
human reatable and modifiable as long as you do not change the line lengths in
a text editor.

Format:

All lines terminate in a single line feed \n.  No other line terminations area 
allowed.  F-you Windows and Macs with your \r\n or \r.

Essentially this is a binary file just restricted to ASCII characters.

Line  Content
1     [GRAFT_AF|GRAFT_BF]'|'[GRAFT version, 8 Bytes]'|'[File version, 8 Bytes]'|'[Data version, 8 Bytes]'\n'
2     [Column names]'\n'
3     [Column Types and Sizes]'\n'
4+    [is deleted flag][row version][Table row data]

Version numbers: 
All version numbers use 8 bytes written using ASCII hex '0' - '9', 'A' - 'F'. 

Line 1: is the format line.  If the file is ASCII it will start with GRAFT_AF.
If the file is Binary it will start with GRAFT_BF.  We have three version 
numbers.  

First version number is for the version of Graft being used.  Currently version 1.
Second version number is the version of the file which indicates the table configuration.
Third version number is the version of the data the file contains.

Line 2: we have a list of column names.  A column name can be any string but 
it is restricted to not allow the | character.  That character is used to 
separate the column names.  Leading and trailing white spaces will be removed 
from column names.  Names are in UTF8 encoding.

E.G.: 
   First Name|Last Name|Salutation|Age|Gender|Address|Phone:Cell|Phone:Work\n

Line 3: we have the description of the types for each column.  This will also
essentially define the length of each record.

b         -  A boolean value.  T, true.  F, false.  " ", unset
n1, i1    -  A natural or integer number of 1 byte size.  
n2, i2    -  A natural or integer number of 2 bytes size. 
n4, i4    -  A natrual or integer number of 4 bytes in size.
n8, i8    -  A natrual or integer number of 4 bytes in size.
r4        -  A real number of 4 bytes in size. 
r8        -  A real number of 8 bytes in size.
s[count]  -  A UTF8 string.  The number that follows it the byte count.

Between columns we have '|' just like for line 2.  

You can pad the formats with ' ' so that the '|' matches with line 1 but it is
not required.

Line 4: The data for the columns follow in the order at they were defined in 
line 2 and taking up the same amount of space as defined in line 3.

Each line is prefixed with a isDeleted flag (a "b" column) and a data version 
number (a 4 byte "n" column.)  This tells us if the line has changed while we 
were working with the data.  

In ASCII values of i, n, and r are always in hex notation.  So characters 
"0" - "9", "A" - "F".

In Both ASCII and Binary, values of i, n, and r are always in network order, or
big endian.

In ASCII each column is separated with a '|'.  In binary it does not.

In ASCII each line terminates with a '\n'.  In binary it does not.
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

#if !defined(GRAFTH)
#define      GRAFTH

/******************************************************************************
constant:
******************************************************************************/
#define GraftVERSION 1

typedef enum
{
   graftModeREAD_ONLY  = gfileOpenModeREAD_ONLY,
   graftModeREAD_WRITE = gfileOpenModeREAD_WRITE
} GraftMode;

typedef enum 
{
   graftTypeNONE,

   graftTypeB,

   graftTypeN1,
   graftTypeN2,
   graftTypeN4,
   graftTypeN8,

   graftTypeI1,
   graftTypeI2,
   graftTypeI4,
   graftTypeI8,

   graftTypeR4,
   graftTypeR8,

   graftTypeS,

   graftTypeCOUNT
} GraftType;

/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   Gb                       isChanged;
   Gb                       isDeleted;
   GfileOffset              fileOffset;
   Gversion                 version;
   GvpArray                *value;
} GraftRow;

// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GraftRow               **p;
} GraftRowArray;

typedef struct
{
   Gs                      *name;
   GraftType                type;
   Gcount                   byteCount;
} GraftCol;

// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GraftCol                *p;
} GraftColArray;

typedef struct
{
   Gb                       isBinary, 
                            isUpdatedVersion,
                            isUpdatedColArray;
   GindexArray             *isUpdatedRowArray;
   GindexArray             *isDeletedRowArray;
   Gversion                 versionFile,
                            versionData;
   Gpath                   *path,
                           *pathBackup;
   GraftColArray           *colArray;
   GraftRowArray           *rowArray;
   GfileOffset              offsetData;
   Gcount                   dataByteCount,
                            rowByteCount;
   Gn1                     *rowBuffer;
} Graft;

/******************************************************************************
prototype:
******************************************************************************/
grlAPI Graft      *graftCreate(                                    Gpath const * const path, Gb const isBinary, GraftMode const mode);
grlAPI Graft      *graftCreate_(                                   Gpath const * const path, Gb const isBinary, GraftMode const mode);
grlAPI Gb          graftCreateContent(   Graft       * const raft, Gpath const * const path, Gb const isBinary, GraftMode const mode);

grlAPI void        graftDestroy(         Graft       * const raft);
grlAPI void        graftDestroyContent(  Graft       * const raft);

grlAPI Gcount      graftGetColCount(     Graft const * const raft);
grlAPI Gcount      graftGetRowCount(     Graft const * const raft);
grlAPI Gid         graftGetVersion(      Graft const * const raft);

grlAPI Gb          graftSetVersion(      Graft       * const raft, Gversion const version);
grlAPI Gb          graftStore(           Graft       * const raft);

// Col functions //////////////////////////////////////////////////////////////
grlAPI Gb          graftColCreate(       Graft       * const raft, Gindex const colIndex, Gs const * const colName, GraftType const type, Gcount const byteCountForStrings);
                                                 
grlAPI Gb          graftColDestroy(      Graft       * const raft, Gindex const colIndex);

grlAPI Gs         *graftColGetName(      Graft const * const raft, Gindex const colIndex);
grlAPI GraftType   graftColGetType(      Graft const * const raft, Gindex const colIndex);
grlAPI Gcount      graftColGetByteCount( Graft const * const raft, Gindex const colIndex);

// Row functions //////////////////////////////////////////////////////////////
grlAPI Gvp         graftRowGetValue(     Graft const * const raft, Gindex const rowIndex, Gindex const colIndex);

grlAPI Gb          graftRowDestroy(      Graft       * const raft, Gindex const rowIndex);

grlAPI Gb          graftRowIsExisting(   Graft const * const raft, Gindex const rowIndex);

grlAPI Gb          graftRowSetValue(     Graft       * const raft, Gindex const rowIndex, Gindex const colIndex, Gvp const value);

#define graftCreate(PATH, MODE)  (Graft *) gleakCreate((void *) graftCreate_(PATH, MODE), gsizeof(Graft))

#define graftColArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftColArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define graftColArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftColArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftColArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define graftColArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define graftColArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define graftColArrayCreate(                  )                                             (GraftColArray *)       g_ArrayCreate(                                GraftColArray, GraftCol, NULL, gbFALSE, gbFALSE)
#define graftColArrayCreateContent(      ARRAY)                                                                     g_ArrayCreateContent(      (G_Array *) ARRAY, GraftColArray, GraftCol, NULL, gbFALSE, gbFALSE)
#define graftColArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define graftColArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define graftColArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define graftColArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define graftColArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define graftColArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define graftColArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define graftColArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define graftColArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define graftColArrayGet(                ARRAY)                                             (GraftCol *)            g_ArrayGet(                (G_Array *) ARRAY) 
#define graftColArrayGetAt(              ARRAY, INDEX)                                      (GraftCol *)            g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define graftColArrayGetBegin(           ARRAY)                                             (GraftCol *)            g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define graftColArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define graftColArrayGetEnd(             ARRAY)                                             (GraftCol *)            g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define graftColArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define graftColArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define graftColArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define graftColArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define graftColArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define graftRowArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftRowArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define graftRowArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftRowArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define graftRowArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define graftRowArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define graftRowArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define graftRowArrayCreate(                  )                                             (GraftRowArray *)         g_ArrayCreate(                                GraftRowArray, GraftRow *, NULL, gbTRUE, gbFALSE)
#define graftRowArrayCreateContent(      ARRAY)                                                                     g_ArrayCreateContent(      (G_Array *) ARRAY, GraftRowArray, GraftRow *, NULL, gbTRUE, gbFALSE)
#define graftRowArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define graftRowArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define graftRowArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define graftRowArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define graftRowArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define graftRowArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define graftRowArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define graftRowArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define graftRowArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define graftRowArrayGet(                ARRAY)                                             (GraftRow **)           g_ArrayGet(                (G_Array *) ARRAY) 
#define graftRowArrayGetAt(              ARRAY, INDEX)                                    *((GraftRow **)           g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define graftRowArrayGetBegin(           ARRAY)                                           *((GraftRow **)           g_ArrayGetBegin(           (G_Array *) ARRAY))
#define graftRowArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define graftRowArrayGetEnd(             ARRAY)                                           *((GraftRow **)           g_ArrayGetEnd(             (G_Array *) ARRAY))
#define graftRowArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define graftRowArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define graftRowArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define graftRowArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define graftRowArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#endif
