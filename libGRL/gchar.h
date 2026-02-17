/**************************************************************************************************
file:       gchar
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
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

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define gcharWHITESPACE          " \x09\x0a\x0b\x0c\x0d"

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
function:
**************************************************************************************************/

// Char
#define charGetCount(  VALUE)       (Gcount) strlen((char *) VALUE)
#define charwGetCount( VALUE)       (Gcount) wcslen((wchar_t *) VALUE)

#define charCompare(  SIZE, A, B)            strncmp((A), (B), (SIZE))
#define charIsEqual(  SIZE, A, B)           (strncmp((A), (B), (SIZE)) == 0)

grlAPI Gb             charIsMultiline(          Char const * const str);

// Gchar
grlAPI Gcompare       gcharCompare(             Gcount const count, Gchar const * const a, Gchar const * const b);
grlAPI Gcompare       gcharCompareA(            Gcount const count, Gchar const * const a, Char  const * const b);
grlAPI Gcompare       gcharCompareBase(         Gcount const count, Gchar const * const a, Gchar const * const b);

#define gcharFromChar(LETTER)    ((Gchar) LETTER)
grlAPI Gcount         gcharFromGchar1(          Gchar1 const letter1, Gchar1 const letter2, Gchar1 const letter3, Gchar1 const letter4, Gchar * const letter);
grlAPI Gcount         gcharFromGchar2(          Gchar2 const letter1, Gchar2 const letter2,                                             Gchar * const letter);

grlAPI Gcount         gcharGetCount(            Gchar const * const str);
grlAPI Gi             gcharGetI(                Gchar const * const str);
grlAPI _locale_t      gcharGetLocaleDefault(    void);
grlAPI Gn             gcharGetN(                Gchar const * const str);
grlAPI Gn             gcharGetNHex(             Gchar const * const str);
grlAPI Gr             gcharGetR(                Gchar const * const str, Gb const isLocalized);

grlAPI Gb             gcharIsDigit(             Gchar const letter);
grlAPI Gb             gcharIsEqual(             Gcount const count, Gchar const * const a, Gchar const * const b);
grlAPI Gb             gcharIsEqualA(            Gcount const count, Gchar const * const a, Char  const * const b);
grlAPI Gb             gcharIsWhiteSpace(        Gchar const letter);

       Gb             gcharStart(               void);
       void           gcharStop(                void);

grlAPI Gchar          gcharToLowerCase(         Gchar const letter);
grlAPI Gchar          gcharToUpperCase(         Gchar const letter);

// Gchar1
#define gchar1GetCount(VALUE)       (Gcount) strlen((char *) VALUE)

grlAPI Gcount         gchar1FromGchar(          Gchar const letter, Gchar1 * const a, Gchar1 * const b, Gchar1 * const c, Gchar1 * const d);

grlAPI Gcount         gchar1GetByteCount(       Gchar1 const letter);
grlAPI Gn             gchar1GetN(               Gchar1 const * const str);
grlAPI Gn             gchar1GetNHex(            Gchar1 const * const str);
grlAPI Gr             gchar1GetR(               Gchar1 const * const str, Gb const isLocalized);

// Gchar2
grlAPI Gcount         gchar2FromGchar(          Gchar const letter, Gchar2 * const a, Gchar2 * const b);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
