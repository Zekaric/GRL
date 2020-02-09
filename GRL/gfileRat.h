/******************************************************************************
file:       GfileRat
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL File Repository As A Table routines

What is a R.A.T.?

It is a simple self describing flat table file that uses either ASCII or Binary
for the storage of values.  If storage is in ASCII, for the most part it is 
human reatable and modifiable as long as you do not change the line lengths in
a text editor.

Format:

All lines terminate in a single line feed \n.  No other line terminations area 
allowed.  F-you Windows and Macs with your \r\n or \r.

Essentially this is a binary file just restricted to ASCII characters.

Line  Content
1     [GFRAT_AF|GFRAT_BF]'|'[RAT version, 8 Bytes]'|'[File version, 8 Bytes]'|'[Data version, 8 Bytes]'\n'
2     [Column names]'\n'
3     [Column Types and Sizes]'\n'
4+    [is deleted flag][row version][Table row data]

Version numbers: 
All version numbers use 8 bytes written using ASCII hex '0' - '9', 'A' - 'F'. 

Line 1: is the format line.  If the file is ASCII it will start with GRAFT_AF.
If the file is Binary it will start with GRAFT_BF.  We have three version 
numbers.  

First version number is for the version of GfileRat being used.  Currently version 1.
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

#if !defined(GFRATH)
#define      GFRATH

/******************************************************************************
constant:
******************************************************************************/
#define GfileRatVERSION 1

typedef enum
{
   gfileRatModeREAD_ONLY  = gfileOpenModeREAD_ONLY,
   gfileRatModeREAD_WRITE = gfileOpenModeREAD_WRITE
} GfileRatMode;

typedef enum 
{
   gfileRatTypeNONE,

   gfileRatTypeB,

   gfileRatTypeN1,
   gfileRatTypeN2,
   gfileRatTypeN4,
   gfileRatTypeN8,

   gfileRatTypeI1,
   gfileRatTypeI2,
   gfileRatTypeI4,
   gfileRatTypeI8,

   gfileRatTypeR4,
   gfileRatTypeR8,

   gfileRatTypeS,

   gfileRatTypeCOUNT
} GfileRatType;

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
} GfileRatRow;

// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GfileRatRow            **p;
} GfileRatRowArray;

typedef struct
{
   Gs                      *name;
   GfileRatType             type;
   Gcount                   byteCount;
} GfileRatCol;

// Same as G_Array ////////////////////////////////////////////////////////////
typedef struct 
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1,
                            isNullEnding     : 1;
   GrlCompareFunc           compareFunc;
   GfileRatCol             *p;
} GfileRatColArray;

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
   GfileRatColArray        *colArray;
   GfileRatRowArray        *rowArray;
   GfileOffset              offsetData;
   Gcount                   dataByteCount,
                            rowByteCount;
   Gn1                     *rowBuffer;
} GfileRat;

/******************************************************************************
prototype:
******************************************************************************/
grlAPI GfileRat      *gfileRatCreate(                                      Gpath const * const path, Gb const isBinary, GfileRatMode const mode);
grlAPI GfileRat      *gfileRatCreate_(                                     Gpath const * const path, Gb const isBinary, GfileRatMode const mode);
grlAPI Gb             gfileRatCreateContent(   GfileRat       * const rat, Gpath const * const path, Gb const isBinary, GfileRatMode const mode);

grlAPI void           gfileRatDestroy(         GfileRat       * const rat);
grlAPI void           gfileRatDestroyContent(  GfileRat       * const rat);

grlAPI Gcount         gfileRatGetColCount(     GfileRat const * const rat);
grlAPI Gcount         gfileRatGetRowCount(     GfileRat const * const rat);
grlAPI Gid            gfileRatGetVersion(      GfileRat const * const rat);

grlAPI Gb             gfileRatSetVersion(      GfileRat       * const rat, Gversion const version);
grlAPI Gb             gfileRatStore(           GfileRat       * const rat);

// Col functions //////////////////////////////////////////////////////////////
grlAPI Gb             gfileRatColCreate(       GfileRat       * const rat, Gindex const colIndex, Gs const * const colName, GfileRatType const type, Gcount const byteCountForStrings);
                                                    
grlAPI Gb             gfileRatColDestroy(      GfileRat       * const rat, Gindex const colIndex);

grlAPI Gs            *gfileRatColGetName(      GfileRat const * const rat, Gindex const colIndex);
grlAPI GfileRatType   gfileRatColGetType(      GfileRat const * const rat, Gindex const colIndex);
grlAPI Gcount         gfileRatColGetByteCount( GfileRat const * const rat, Gindex const colIndex);

// Row functions //////////////////////////////////////////////////////////////
grlAPI Gvp            gfileRatRowGetValue(     GfileRat const * const rat, Gindex const rowIndex, Gindex const colIndex);

grlAPI Gb             gfileRatRowDestroy(      GfileRat       * const rat, Gindex const rowIndex);

grlAPI Gb             gfileRatRowIsExisting(   GfileRat const * const rat, Gindex const rowIndex);

grlAPI Gb             gfileRatRowSetValue(     GfileRat       * const rat, Gindex const rowIndex, Gindex const colIndex, Gvp const value);

#define gfileRatCreate(PATH, ISBINARY, MODE)  (GfileRat *) gleakCreate((void *) gfileRatCreate_(PATH, ISBINARY, MODE), gsizeof(GfileRat))

#define gfileRatColArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatColArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gfileRatColArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatColArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatColArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gfileRatColArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gfileRatColArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gfileRatColArrayCreate(                  )                                             (GfileRatColArray *)    g_ArrayCreate(                                GfileRatColArray, GfileRatCol, NULL, gbFALSE, gbFALSE)
#define gfileRatColArrayCreateContent(      ARRAY)                                                                     g_ArrayCreateContent(      (G_Array *) ARRAY, GfileRatColArray, GfileRatCol, NULL, gbFALSE, gbFALSE)
#define gfileRatColArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gfileRatColArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gfileRatColArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gfileRatColArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gfileRatColArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gfileRatColArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gfileRatColArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gfileRatColArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gfileRatColArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gfileRatColArrayGet(                ARRAY)                                             (GfileRatCol *)         g_ArrayGet(                (G_Array *) ARRAY) 
#define gfileRatColArrayGetAt(              ARRAY, INDEX)                                      (GfileRatCol *)         g_ArrayGetAt(              (G_Array *) ARRAY, INDEX) 
#define gfileRatColArrayGetBegin(           ARRAY)                                             (GfileRatCol *)         g_ArrayGetBegin(           (G_Array *) ARRAY) 
#define gfileRatColArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gfileRatColArrayGetEnd(             ARRAY)                                             (GfileRatCol *)         g_ArrayGetEnd(             (G_Array *) ARRAY) 
#define gfileRatColArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gfileRatColArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gfileRatColArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gfileRatColArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gfileRatColArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#define gfileRatRowArrayAdd(                ARRAY,        VALUE)                                                       g_ArrayAdd(                (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatRowArrayAddAt(              ARRAY, INDEX, VALUE)                                                       g_ArrayAddAt(              (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 
#define gfileRatRowArrayAddBegin(           ARRAY,        VALUE)                                                       g_ArrayAddBegin(           (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatRowArrayAddEnd(             ARRAY,        VALUE)                                                       g_ArrayAddEnd(             (G_Array *) ARRAY,        (Gp *) VALUE) 
#define gfileRatRowArrayClear(              ARRAY, COUNT, INDEX)                                                       g_ArrayClear(              (G_Array *) ARRAY, COUNT, INDEX) 
#define gfileRatRowArrayCopy(               ARRAY, COUNT, INDEXSRC, INDEXDST)                                          g_ArrayCopy(               (G_Array *) ARRAY, COUNT, INDEXSRC, INDEXDST) 
#define gfileRatRowArrayCopyFrom(           ARRAYDST, INDEXDST, ARRAYSRC, COUNT, INDEXSRC)                             g_ArrayCopyFrom(           (G_Array *) ARRAYDST, INDEXDST, (G_Array *) ARRAYSRC, COUNT, INDEXSRC) 
#define gfileRatRowArrayCreate(                  )                                             (GfileRatRowArray *)    g_ArrayCreate(                                GfileRatRowArray, GfileRatRow *, NULL, gbTRUE, gbFALSE)
#define gfileRatRowArrayCreateContent(      ARRAY)                                                                     g_ArrayCreateContent(      (G_Array *) ARRAY, GfileRatRowArray, GfileRatRow *, NULL, gbTRUE, gbFALSE)
#define gfileRatRowArrayDestroy(            ARRAY)                                                                     g_ArrayDestroy(            (G_Array *) ARRAY) 
#define gfileRatRowArrayDestroyContent(     ARRAY)                                                                     g_ArrayDestroyContent(     (G_Array *) ARRAY) 
#define gfileRatRowArrayErase(              ARRAY, VALUE)                                                              g_ArrayErase(              (G_Array *) ARRAY, (Gp *) VALUE) 
#define gfileRatRowArrayEraseAt(            ARRAY, COUNT, INDEX)                                                       g_ArrayEraseAt(            (G_Array *) ARRAY, COUNT, INDEX) 
#define gfileRatRowArrayEraseBegin(         ARRAY)                                                                     g_ArrayEraseBegin(         (G_Array *) ARRAY) 
#define gfileRatRowArrayEraseEnd(           ARRAY)                                                                     g_ArrayEraseEnd(           (G_Array *) ARRAY) 
#define gfileRatRowArrayFind(               ARRAY, VALUE)                                                              g_ArrayFind(               (G_Array *) ARRAY, (Gp *) VALUE) 
#define gfileRatRowArrayFlush(              ARRAY)                                                                     g_ArrayFlush(              (G_Array *) ARRAY) 
#define gfileRatRowArrayForEach(            ARRAY, FUNC)                                                               g_ArrayForEach(            (G_Array *) ARRAY, FUNC) 
#define gfileRatRowArrayGet(                ARRAY)                                             (GfileRatRow **)        g_ArrayGet(                (G_Array *) ARRAY) 
#define gfileRatRowArrayGetAt(              ARRAY, INDEX)                                    *((GfileRatRow **)        g_ArrayGetAt(              (G_Array *) ARRAY, INDEX))
#define gfileRatRowArrayGetBegin(           ARRAY)                                           *((GfileRatRow **)        g_ArrayGetBegin(           (G_Array *) ARRAY))
#define gfileRatRowArrayGetCount(           ARRAY)                                                                     g_ArrayGetCount(           (G_Array *) ARRAY) 
#define gfileRatRowArrayGetEnd(             ARRAY)                                           *((GfileRatRow **)        g_ArrayGetEnd(             (G_Array *) ARRAY))
#define gfileRatRowArrayGetSize(            ARRAY)                                                                     g_ArrayGetSize(            (G_Array *) ARRAY) 
#define gfileRatRowArraySetCount(           ARRAY, COUNT)                                                              g_ArraySetCount(           (G_Array *) ARRAY, COUNT) 
#define gfileRatRowArraySort(               ARRAY)                                                                     g_ArraySort(               (G_Array *) ARRAY) 
#define gfileRatRowArraySwap(               ARRAY, INDEXA, INDEXB)                                                     g_ArraySwap(               (G_Array *) ARRAY, INDEXA, INDEXB) 
#define gfileRatRowArrayUpdateAt(           ARRAY, INDEX, VALUE)                                                       g_ArrayUpdateAt(           (G_Array *) ARRAY, INDEX, (Gp *) VALUE) 

#endif
