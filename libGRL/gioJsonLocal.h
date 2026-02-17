/**************************************************************************************************
file:       gjsonLocal
author:     Robbert de Groot
copyright:  2021, Robbert de Groot

description:
Write functions local to the library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2021, Robbert de Groot

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
include:
**************************************************************************************************/

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
#define jsonARRAY_START_STR                        "["
#define jsonARRAY_STOP_STR                         "]"
#define jsonOBJECT_START_STR                       "{"
#define jsonOBJECT_STOP_STR                        "}"
#define jsonSEPARATOR_STR                          ","
#define jsonKEY_VALUE_SEPARATOR_STR                ":"
#define jsonSTRING_QUOTE_STR                       "\""
#define jsonSTRING_ESCAPE_STR                      "\\"
#define jsonSTRING_ESCAPE_QUOTE_STR                "\\\""
#define jsonSTRING_ESCAPE_BACK_SLASH_STR           "\\\\"
#define jsonSTRING_ESCAPE_FORWARD_SLASH_STR        "\\/"
#define jsonSTRING_ESCAPE_BACKSPACE_STR            "\\b"
#define jsonSTRING_ESCAPE_FORMFEED_STR             "\\f"
#define jsonSTRING_ESCAPE_LINEFEED_STR             "\\n"
#define jsonSTRING_ESCAPE_CARRIAGE_RETURN_STR      "\\r"
#define jsonSTRING_ESCAPE_UNICODE_STR              "\\u"
#define jsonSTRING_ESCAPE_TAB_STR                  "\\t"
#define jsonNUMBER_EXPONENT_1_STR                  "E"
#define jsonNUMBER_EXPONENT_2_STR                  "e"
#define jsonNUMBER_PLUS_STR                        "+"
#define jsonNUMBER_MINUS_STR                       "-"
#define jsonNUMBER_DECIMAL_STR                     "."

#define jsonARRAY_START_CHAR                       '['
#define jsonARRAY_STOP_CHAR                        ']'
#define jsonOBJECT_START_CHAR                      '{'
#define jsonOBJECT_STOP_CHAR                       '}'
#define jsonSEPARATOR_CHAR                         ','
#define jsonKEY_VALUE_SEPARATOR_CHAR               ':'
#define jsonSTRING_QUOTE_CHAR                      '\"'
#define jsonBACK_SLASH_CHAR                        '\\'
#define jsonFOREWARD_SLASH_CHAR                    '/'
#define jsonNUMBER_EXPONENT_1_CHAR                 'E'
#define jsonNUMBER_EXPONENT_2_CHAR                 'e'
#define jsonNUMBER_PLUS_CHAR                       '+'
#define jsonNUMBER_MINUS_CHAR                      '-'
#define jsonNUMBER_DECIMAL_CHAR                    '.'

#define jsonIS_SPACE(BYTE) (BYTE == ' ' || BYTE == '\t' || BYTE == '\n' || BYTE == '\r')

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
Gb           _JsonEatSpace(         GioJson       * const json);

Gb           _JsonGetChar(          GioJson       * const json);
GioJsonType  _JsonGetFalse(         GioJson       * const json);
GioJsonType  _JsonGetNull(          GioJson       * const json);
GioJsonType  _JsonGetNumber(        GioJson       * const json);
GioJsonType  _JsonGetNumberInteger( GioJson       * const json, Gchar1 const * const str);
GioJsonType  _JsonGetNumberReal(    GioJson       * const json, Gchar1 const * const str);
GioJsonType  _JsonGetTrue(          GioJson       * const json);

Gb           _JsonIsSpace(          GioJson       * const json);

Gb           _JsonStrStart(         void);
void         _JsonStrStop(          void);
Gchar1       _JsonStrToHex(         Gchar1 const value);

Gb           _JsonSetBuffer(        GioJson const * const json, Gcount const bufCount, Gchar1 const * const buf);
Gb           _JsonSetI(             GioJson       * const json, Gi8 const value);
Gb           _JsonSetIndent(        GioJson       * const json);
Gb           _JsonSetN(             GioJson       * const json, Gn8 const value);
Gb           _JsonSetNewLine(       GioJson       * const json);
Gb           _JsonSetR(             GioJson       * const json, Gr8 const value);
Gb           _JsonSetR4(            GioJson       * const json, Gr4 const value);
