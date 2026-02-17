/**************************************************************************************************
file:       GioRat
author:     Robbert de Groot
copyright:  2020, Robbert de Groot

description:
GRL Repository As A Table routines

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
If the file is Binary it will start with GFRAT_BF.  We have three version
numbers.

First version number is for the version of GioRat being used.  Currently version 1.
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

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define GioRatVERSION 1

typedef enum
{
   gioRatModeREAD_ONLY  = gfileOpenModeREAD_ONLY,
   gioRatModeREAD_WRITE = gfileOpenModeREAD_WRITE
} GioRatMode;

typedef enum
{
   gioRatTypeNONE,

   gioRatTypeB,

   gioRatTypeN1,
   gioRatTypeN2,
   gioRatTypeN4,
   gioRatTypeN8,

   gioRatTypeI1,
   gioRatTypeI2,
   gioRatTypeI4,
   gioRatTypeI8,

   gioRatTypeR4,
   gioRatTypeR8,

   gioRatTypeS,

   gioRatTypeCOUNT
} GioRatType;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GTYPE_VAR

   Gindex                   index;
   Gb                       isChanged;
   Gb                       isDeleted;
   GfileOffset              fileOffset;
   Gversion                 version;
   GvArray                 *value;
} GioRatRow;

typedef struct
{
   Gs                      *name;
   GioRatType               type;
   Gcount                   byteCount;
} GioRatCol;

typedef struct
{
   GTYPE_VAR

   Gb                       isBinary,
                            isUpdatedVersion,
                            isUpdatedColArray;
   GvArray                 *isUpdatedRowArray;
   GvArray                 *isDeletedRowArray;
   Gversion                 versionFile,
                            versionData;
   Gpath                   *path,
                           *pathBackup;
   GvArray                 *colArray;
   GvArray                 *rowArray;
   GfileOffset              offsetData;
   Gcount                   dataByteCount,
                            rowByteCount;
   Gn1                     *rowBuffer;
} GioRat;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gratCloc(PATH, ISBINARY, MODE)   gleakClocType(gioRatCloc_(PATH, ISBINARY, MODE), GioRat)

grlAPI GioRat        *gioRatCloc_(                                     Gpath const * const path, Gb const isBinary, GioRatMode const mode);
grlAPI Gb             gioRatClocContent(     GioRat       * const rat, Gpath const * const path, Gb const isBinary, GioRatMode const mode);

grlAPI void           gioRatDloc(            GioRat       * const rat);
grlAPI void           gioRatDlocContent(     GioRat       * const rat);

grlAPI Gcount         gioRatGetColCount(     GioRat const * const rat);
grlAPI Gcount         gioRatGetRowCount(     GioRat const * const rat);
grlAPI Gid            gioRatGetVersion(      GioRat const * const rat);

grlAPI Gb             gioRatSetVersion(      GioRat       * const rat, Gversion const version);
grlAPI Gb             gioRatStore(           GioRat       * const rat);

// Col functions //////////////////////////////////////////////////////////////
grlAPI Gb             gioRatColCloc(         GioRat       * const rat, Gindex const colIndex, Gs const * const colName, GioRatType const type, Gcount const byteCountForStrings);

grlAPI Gb             gioRatColDloc(         GioRat       * const rat, Gindex const colIndex);

grlAPI Gs            *gioRatColGetName(      GioRat const * const rat, Gindex const colIndex);
grlAPI GioRatType     gioRatColGetType(      GioRat const * const rat, Gindex const colIndex);
grlAPI Gcount         gioRatColGetByteCount( GioRat const * const rat, Gindex const colIndex);

// Row functions //////////////////////////////////////////////////////////////
grlAPI Gindex         gioRatRowCloc(         GioRat       * const rat);

grlAPI Gb             gioRatRowDloc(         GioRat       * const rat, Gindex const rowIndex);

grlAPI Gv             gioRatRowGetValue(     GioRat const * const rat, Gindex const rowIndex, Gindex const colIndex);

grlAPI Gb             gioRatRowIsExisting(   GioRat const * const rat, Gindex const rowIndex);

grlAPI Gb             gioRatRowSetValue(     GioRat       * const rat, Gindex const rowIndex, Gindex const colIndex, Gv const value);


#define gratRowFromV(V)   ((GioRatRow *) (V).p)
#define gratColFromV(V)   ((GioRatCol *) (V).p)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
