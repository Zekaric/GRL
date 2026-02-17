/**************************************************************************************************
file:       God_local
author:     Robbert de Groot
copyright:  2025, Robbert de Groot

description:
Write functions local to the library.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2025, Robbert de Groot

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
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

#define godFILE_HEADER_STR                        (Gchar1 *) "GOD"
#define godFILE_VERSION                           1

#define godARRAY_START_CHAR                       '['
#define godARRAY_STOP_CHAR                        ']'
#define godGROUP_START_CHAR                       '{'
#define godGROUP_STOP_CHAR                        '}'
#define godSEPARATOR_CHAR                         ','
#define godKEY_VALUE_SEPARATOR_CHAR               ':'
#define godBINARY_START_CHAR                      '*'
#define godSTRING_QUOTE_CHAR                      '\"'
#define godSTRING_ESCAPE_CHAR                     '\\'
#define godNUMBER_EXPONENT_1_CHAR                 'E'
#define godNUMBER_EXPONENT_2_CHAR                 'e'
#define godNUMBER_PLUS_CHAR                       '+'
#define godNUMBER_MINUS_CHAR                      '-'
#define godNUMBER_DECIMAL_CHAR                    '.'
#define godVALUE_FALSE_CHAR                       'F'
#define godVALUE_INFINITY_CHAR                    'I'
#define godVALUE_INFINITY_NEGATIVE_CHAR           'i'
#define godVALUE_MAX_CHAR                         'L'
#define godVALUE_MAX_NEGATIVE_CHAR                'l'
#define godVALUE_MIN_CHAR                         'S'
#define godVALUE_MIN_NEGATIVE_CHAR                's'
#define godVALUE_NOT_A_NUMBER_CHAR                '?'
#define godVALUE_NULL_CHAR                        'N'
#define godVALUE_TRUE_CHAR                        'T'

#define godSTRING_ESCAPE_QUOTE_STR                "\\\""
#define godSTRING_ESCAPE_BACK_SLASH_STR           "\\\\"
#define godSTRING_ESCAPE_FORWARD_SLASH_STR        "\\/"
#define godSTRING_ESCAPE_BACKSPACE_STR            "\\b"
#define godSTRING_ESCAPE_FORMFEED_STR             "\\f"
#define godSTRING_ESCAPE_NEWLINE_STR              "\\n"
#define godSTRING_ESCAPE_CARRIAGE_RETURN_STR      "\\r"
#define godSTRING_ESCAPE_UNICODE_STR              "\\u"
#define godSTRING_ESCAPE_TAB_STR                  "\\t"

#define godSPACE_SPACE_CHAR                       ' '
#define godSPACE_TAB_CHAR                         '\t'
#define godSPACE_NEWLINE_CHAR                     '\n'
#define godSPACE_CARRIAGE_RETURN_CHAR             '\r'
#define godBACKSPACE_CHAR                         '\b'
#define godFORMFEED_CHAR                          '\f'

#define godIS_SPACE(BYTE) (BYTE == godSPACE_SPACE_CHAR || BYTE == godSPACE_TAB_CHAR || BYTE == godSPACE_NEWLINE_CHAR || BYTE == godSPACE_CARRIAGE_RETURN_CHAR)

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
Gb           _GodEatSpace(          GioGod       * const god);

Gb           _GodGetChar(           GioGod       * const god);
GioGodType   _GodGetNumber(         GioGod       * const god);
GioGodType   _GodGetNumberInteger(  GioGod       * const god, Gchar1 * const str);
GioGodType   _GodGetNumberReal(     GioGod       * const god, Gchar1 * const str);

Gb           _GodIsSpace(           GioGod       * const god);

Gb           _GodSetBuffer(         GioGod const * const god, Gcount const bufCount, Gn1 const * const buf);
Gb           _GodSetByte(           GioGod const * const god, Gn1 const letter);
Gb           _GodSetI(              GioGod       * const god, Gi8 const value);
Gb           _GodSetIndent(         GioGod       * const god);
Gb           _GodSetN(              GioGod       * const god, Gn8 const value);
Gb           _GodSetNewLine(        GioGod       * const god);
Gb           _GodSetR(              GioGod       * const god, Gr8 const value);
Gb           _GodSetR4(             GioGod       * const god, Gr4 const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
