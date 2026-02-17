/**************************************************************************************************
file:       grob
author:     Robbert de Groot
copyright:  2000, Robbert de Groot

description:
GRL Repository of Organized Blocks.

These routines will implement a B-Tree using a grob file.

grob File Type is "GROB"

Information Block:  Root index of the grob file.  Only one per file.
   grob Data Type "INFO"
   4 B  - Version number of grob.
   4 B  - Sub format information.  Similar to how GROB is to GRUB.
   4 B  - Count of keys in the key nodes. (KC)
   4 B  - Key Size. (KS)
   8 B  - Index to root key node.

Key Node Block:
   grob Data Type "NODE"
   8 B                        - The key count.
   ((KS + 8) *       KC) B    - The keys and offset.
   (      8  * (KC + 1)) B    - The offsets.

Data Block:
   grob Data Type "DATA"
   KS B  - The key.
    4 B  - Type of the data. "INT ", "NAT ", "REAL", "STR ", "PNT "
    4 B  - raw size of data.
    N B  - Data.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2000, Robbert de Groot

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

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   Gn8          index;
   Gchar1      *key;
   Gid          dataType;
   Gn4          size;
} GioRobData;

typedef struct
{
   Gn8          index;
   Gn4          keyCount;
   Gchar1      *keyList;
   Gn8         *indexList,
               *nodeList;
} GioRobNode;

typedef struct
{
   GioRub   *rub;
   Gn4       version;
   Gn4       keyCount;
   Gn4       keySize;
   Gid       fileType;
   Gn8       rootNodeIndex;
   Gb        isLocked;
} GioRob;

/**************************************************************************************************
function:
**************************************************************************************************/
#define gioRobCreateData(GROB, CHAR_KEY, GID_DATATYPE, GN4_SIZE)                       ((GioRobData *) gleakCloc(gioRobClocData_((GROB), (CHAR_KEY), (GID_DATATYPE), (GN4_SIZE))))

#define gioRobOpen(GSTR_FILE, GROBOPENMODE, CHAR_FILETYPE, GN4_KEYCOUNT, GN4_KEYSIZE)  ((GioRob *)     gleakCloc(gioRobOpen_((GSTR_FILE), (GROBOPENMODE), (CHAR_FILETYPE), (GN4_KEYCOUNT), (GN4_KEYSIZE))))


grlAPI void           gioRobClose(        GioRob       * const rob);
grlAPI GioRobData    *gioRobClocData_(    GioRob       * const rob, Gchar1 const * const key, Gid const dataType, Gn4 const size);

grlAPI Gb             gioRobDlocData(     GioRob       * const rob, GioRobData * const data);

grlAPI void           gioRobFlush(        GioRob const * const rob);

grlAPI GioRobData    *gioRobGetData(      GioRob const * const rob, Gchar1 const * const key);
grlAPI Gn4            gioRobGetKeyCount(  GioRob const * const rob);
grlAPI Gn4            gioRobGetKeySize(   GioRob const * const rob);
grlAPI Gid            gioRobGetType(      GioRob const * const rob);
grlAPI Gn4            gioRobGetVersion(   GioRob const * const rob);

grlAPI Gfile         *gioRobLockOn(       GioRob const * const rob, GioRobData const * const data);
grlAPI Gb             gioRobLockOff(      GioRob       * const rob);

grlAPI GioRob        *gioRobOpen_(        Gpath const * const path, GfileOpenMode const mode, Gid const fileType, Gn4 const keyCount, Gn4 const keySize);

       Gb             gioRobStart(        void);
       void           gioRobStop(         void);

// data routines.
grlAPI Gb             gioRobDataDloc(     GioRobData       * const data);

grlAPI Gchar1 const  *gioRobDataGetKey(   GioRobData const * const data);
grlAPI Gn4            gioRobDataGetSize(  GioRobData const * const data);
grlAPI Gid            gioRobDataGetType(  GioRobData const * const data);
