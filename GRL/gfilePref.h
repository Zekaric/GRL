/******************************************************************************
file:       gfilePref
author:     Robbert de Groot
copyright:  2003-2009, Robbert de Groot

description:
A library to read and write a gfilePref file.

A Pref file is similar to an INI file and a bit similar to an XML file but 
dumbed down quite a bit.

At its root it is a Key - Value format with the ability to nest key values in
a value.

Rules of the format:

1. Single line values begin with a '-'.
   Multi-line values begin with a '='.
   White space is stripped from before the - and =.

2. Any line starting with any other charater is a comment.

3. Single line format
   
   '-' [key] [value]
   
   [key]   can not contain spaces.  Any non space character is fine.  Space 
           before and after the key are removed.
   [value] starts from the first non space letter after the key till the end of line.

4. Multi-line format
   
   '=' [key] [id]
   [value that can span multiple lines]
   '=' [key] [id]
   
   [key]   can not contain spaces.  Any non space character is fine.  Space 
           before and after the key are removed.
   [id]    is to differenciate this multi-line value with potentially a 
           multiiline value found with in its value.  The terminating 
           '=' [key] [id] line should be exactly the same.
   [value] lines are treated verbatum.  No white space stripping performed.
           new line characters maintained except for the last line which will
           be stripped.
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

#if !defined(GFILEPREFH)
#define      GFILEPREFH

/******************************************************************************
constant:
******************************************************************************/
/******************************************************************************
const: GfilePrefMode

Getting information from a file or a string.
******************************************************************************/
#define GPREF_DEFAULT_COMMENT \
   "\n"\
   "GFilePref file format\n\n"\
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
   gfilePrefModeNONE,
   gfilePrefModeFILE,
   gfilePrefModeSTR
} GfilePrefMode;

/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   GTYPE_VAR

   Goffset   bposition;
   Gfile    *file;
   Gs       *buffer,
            *key,
            *value;
} GfilePref;

/******************************************************************************
function:
******************************************************************************/
//lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026
#define gfilePrefCreate(GPREFMODE, VALUE) \
   ((GfilePref *) gleakCreate(gfilePrefCreate_((GPREFMODE), (VALUE)), gsizeof(GfilePref)))
//lint -restore

grlAPI GfilePref        *gfilePrefCreate_(               GfilePrefMode const mode, Gp * const value);
grlAPI Gb                gfilePrefCreateContent(         GfilePref       * const pref, GfilePrefMode const mode, Gp * const value);

grlAPI void              gfilePrefDestroy(               GfilePref       * const pref);
grlAPI void              gfilePrefDestroyContent(        GfilePref       * const pref);

grlAPI Gb                gfilePrefGet(                   GfilePref       * const pref);
grlAPI Gs               *gfilePrefGetKey(                GfilePref const * const pref);
grlAPI Gs               *gfilePrefGetValue(              GfilePref const * const pref);

//grlAPI Gb                gfilePrefLoadStrKeyValueArray(  GfilePref       * const pref, gsKeyValueArray * const strKeyValueArray);
//grlAPI Gb                gfilePrefLoadStrTable(          GfilePref       * const pref, GsTable * const strTable);

grlAPI Gb                gfilePrefSet(                   GfilePref const * const pref, Gs   const * const key, Gs   const * const value);
grlAPI Gb                gfilePrefSetA(                  GfilePref const * const pref, Char const * const key, Char const * const value);
grlAPI Gb                gfilePrefSetCharStr(            GfilePref const * const pref, Char const * const key, Char const * const value);
grlAPI Gb                gfilePrefSetComment(            GfilePref const * const pref, Gs   const * const value);
grlAPI Gb                gfilePrefSetCommentA(           GfilePref const * const pref, Char const * const value);

// to avoid chicken and egg issue.
//grlAPI gsKeyValueArray  *gsKeyValueArrayCreateLoad(      Gpath const * const fileName);
//grlAPI Gb                gsKeyValueArrayLoad(            gsKeyValueArray * const strKeyValueArray, Gpath const * const fileName);
//grlAPI Gb                gssHashLoad(                    GsTable * const strTable, Gpath const * const filename);

#endif
