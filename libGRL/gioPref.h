/**************************************************************************************************
file:       gioPref
author:     Robbert de Groot
copyright:  2003-2009, Robbert de Groot

description:
A library to read and write a gioPref file.

A Pref file is similar to an INI file and a bit similar to an XML file but dumbed down quite a bit.
At its root it is a Key - Value format with the ability to nest key values with-in a value.  A pref
file is a UTF8 file with UNIX line endings (/n).  Anything else is not a pref file.

Rules of the format:

1. Single line values begin with a '-'.
   Multi-line values begin with a '='.
   White space is stripped from before the - and =.

2. Any line starting with any other charater is a comment.

3. Single line format

   '-' [key] [value]

   [key]   can not contain spaces.  Any non space character is fine.  Space before and after the
           key are removed.
   [value] starts from the first non space letter after the key till the end of line.

4. Multi-line format

   '=' [key] [id]
   [value that can span multiple lines]
   '=' [key] [id]

   [key]   can not contain spaces.  Any non space character is fine.  Space before and after the
           key are removed.
   [id]    is to differenciate this multi-line value with potentially a multiiline value found with
           in its value.  The terminating '=' [key] [id] line should be exactly the same.
   [value] lines are treated verbatum.  No white space stripping performed.  new line characters
           maintained except for the last line which will be stripped.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2003, Robbert de Groot

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
/**************************************************************************************************
const: GioPrefMode

Getting information from a file or a string.
**************************************************************************************************/
#define GPREF_DEFAULT_COMMENT \
   "\n"\
   "gioPref file format\n\n"\
   "This is a simple key value format.  Nesting can occur.\n"\
   "Rules of the format:\n"\
   "1. Single line values begin with a '-'.\n"\
   "   Multi-line values begin with a '='.\n"\
   "   White space is stripped from before the - and =.\n"\
   "2. Any line starting with any other charater is a comment.\n"\
   "3. Single line format\n"\
   "   '-' [key] [value]\n"\
   "   [key] can not contain spaces.  Any non space character is fine.  Space before and after the key are removed.\n"\
   "   [value] starts from the first non space letter after the key till the end of line.\n"\
   "4. Multi-line format\n"\
   "   '=' [key] [id]\n"\
   "[value]\n"\
   "...\n"\
   "   '=' [key] [id]\n"\
   "   [key] can not contain spaces.  Any non space character is fine.  Space before and after the key are removed.\n"\
   "   [id] is to differenciate this multi-line value with potentially a multiiline value\n"\
   "   found with in its value.  The terminating '=' [key] [id] line should be exactly the same.\n"\
   "   [value] lines are treated verbatum.  No white space stripping performed.\n"\
   "   new line characters maintained except for the last line which will be stripped.\n"

typedef enum
{
   gioPrefModeREAD,
   gioPrefModeWRITE
} GioPrefMode;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GTYPE_VAR

   GioPrefMode  mode;
   Goffset      offset;
   Gio         *io;
   Gs          *key,
               *value;
} GioPref;

/**************************************************************************************************
function:
**************************************************************************************************/
#define gioPrefCloc(GPREFMODE, VALUE)   ((GioPref *) gleakCloc(gioPrefCloc_((GPREFMODE), (VALUE)), gsizeof(GioPref)))

grlAPI GioPref          *gioPrefClocReader_(                                       Gio * const io);
grlAPI Gb                gioPrefClocReaderContent(     GioPref       * const pref, Gio * const io);
grlAPI GioPref          *gioPrefClocWriter_(                                       Gio * const io);
grlAPI Gb                gioPrefClocWriterContent(     GioPref       * const pref, Gio * const io);

grlAPI void              gioPrefDloc(                  GioPref       * const pref);
grlAPI void              gioPrefDlocContent(           GioPref       * const pref);

grlAPI Gb                gioPrefGet(                   GioPref       * const pref);
grlAPI Gs               *gioPrefGetKey(                GioPref const * const pref);
grlAPI Gs               *gioPrefGetValue(              GioPref const * const pref);

//grlAPI Gb                gioPrefLoadStrKeyValueArray(  GioPref       * const pref, gsKeyValueArray * const strKeyValueArray);
//grlAPI Gb                gioPrefLoadStrTable(          GioPref       * const pref, GsTable * const strTable);

grlAPI Gb                gioPrefSet(                   GioPref const * const pref, Gs   const * const key, Gs   const * const value);
grlAPI Gb                gioPrefSetA(                  GioPref const * const pref, Char const * const key, Char const * const value);
grlAPI Gb                gioPrefSetComment(            GioPref const * const pref, Gs   const * const value);
grlAPI Gb                gioPrefSetCommentA(           GioPref const * const pref, Char const * const value);

// to avoid chicken and egg issue.
//grlAPI gsKeyValueArray  *gsKeyValueArrayClocLoad(        Gpath const * const fileName);
//grlAPI Gb                gsKeyValueArrayLoad(            gsKeyValueArray * const strKeyValueArray, Gpath const * const fileName);
//grlAPI Gb                gssHashLoad(                    GsTable * const strTable, Gpath const * const filename);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
