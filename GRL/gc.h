/**************************************************************************************************
file:       gc
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot
**************************************************************************************************/

/**************************************************************************************************
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
**************************************************************************************************/

#if !defined(GCHARH)
#define      GCHARH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
#define GcBYTE_ORDER 0xfeff

/*lint -save -e960 */
#define WHITESPACE_A              " \x09\x0a\x0b\x0c\x0d"
#define WHITESPACE_U2            L" \x09\x0a\x0b\x0c\x0d"

#define gsINTERNAL_BUFFER_SIZE   (size_t) 256

#define gsDYNAMIC_EXPAND_FACTOR  (size_t) 2

#define gsFIND_FAIL              GindexERROR
/*lint -restore */

/**************************************************************************************************
const: GcStrip

Strip Whitespace enumeration

gcStripESCAPE_CHAR - This will remove the escape letter "\"
This case will not touch these chars inside ""

gcStripESCAPE_CHAR_ALL - This case will touch all cases

gcStripWHITE_SPACE - This case will remove all white space
This case will not touch inside ""

gcStripWHITE_SPACE_ALL - This will touch all cases

gcStripWHITE_SPACE_ALL_BUT_ONE - This will reduce groups of
whitespace characters to " ".

gcStripWHITE_SPACE_LEADING - Only leading white space.

gcStripWHITE_SPACE_TRAILING - Only trailing white space.
**************************************************************************************************/
typedef enum
{
   gcStripNONE                      = 0x00000000,

   gcStripESCAPE_CHAR               = 0x00000001,
   gcStripESCAPE_CHAR_ALL           = 0x00000002,

   gcStripWHITE_SPACE               = 0x00000010,
   gcStripWHITE_SPACE_ALL           = 0x00000020,

   gcStripWHITE_SPACE_LEADING       = 0x10000000,
   gcStripWHITE_SPACE_TRAILING      = 0x20000000

} GcStrip;

typedef enum
{
   gcTypeNONE,
   gcTypeA,
   gcTypeU1,
   gcTypeU2,
   gcTypeU4,

   gcTypeSTR
} GcType;

typedef enum
{
   gsOpDONE              = 0x00000000,

   // Next parameter is a...
   gsOpGSTR              = 0x00000001,
   gsOpA                 = 0x00000010,
   gsOpU1                = 0x00000020,
   gsOpU2                = 0x00000040,
   //gsOpGCHAR          = 0x00000080,
   gsOpPARAMETER         = 0x000000FF,

   // Destory this parameter after the operation.
   // Mixed in with the above.
   gsOpPARAMETER_DESTROY = 0x00000100,

   // Use a substring from this parameter, start and end index.
   gsOpSUB_STRING        = 0x00001000

} GsOp;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef Gn4       Gc;
typedef Gn1       Gc1;
typedef wchar_t   Gc2;
typedef Gn4       Gc4;

/*lint -save -e960 -e9018 */
typedef union
{
   Gc       *str;
   Gc1      *str1;
   Gc2      *str2;
   Gc4      *str4;
} GcPointer;
/*lint -restore */

/**************************************************************************************************
function:
**************************************************************************************************/
// gc
grlAPI Gcompare   gcCompare(               Gcount const count, Gc  const * const a, Gc  const * const b);
grlAPI Gcompare   gcCompareBase(           Gcount const count, Gc2 const * const a, Gc2 const * const b);
grlAPI Gcompare   gc2Compare(              Gc2 const * const a, Gc2 const * const b);

grlAPI Gc         gcFromA(                 Char const letter);
grlAPI Gc2        gc2FromA(                Char const letter);
grlAPI Gc         gcFromU1(                Gc1 const * const str);
grlAPI Gc         gcFromU2(                Gc2 const * const str);

grlAPI Gcount     gcGetCount(              Gc const * const str);
grlAPI Gcount     gcGetCountA(             Char const * const str);
grlAPI Gcount     gcGetCountU1(            Gc1 const * const str);
grlAPI Gcount     gcGetCountU2(            Gc2 const * const str);
grlAPI Gcount     gcGetLetterByteCount(    Gp const *ptr, GcType type);
grlAPI Gsize      gcGetTypeSize(           GcType type);

grlAPI Gb         gcIsAlpha(               Gc const letter);
grlAPI Gb         gcIsDigit(               Gc const letter);
grlAPI Gb         gcIsEqualU1(             Gcount const count, Gc1 const * const aStr, Gc1 const * const bStr);
grlAPI Gb         gcIsWhiteSpace(          Gc const letter);

grlAPI Gc const  *gcSearchForLetter(       Gc const * const str, Gc           const letter);
grlAPI Gc const  *gcSearchForLetters(      Gc const * const str, Gc   const * const letters);
grlAPI Gc const  *gcSearchForLettersA(     Gc const * const str, Char const * const letters);
grlAPI Gc const  *gcSearchForLettersInv(   Gc const * const str, Gc   const * const letters);
grlAPI Gc const  *gcSearchForString(       Gc const * const str, Gcount const subStrLength, Gc const * const subStr);
       Gb         gcStart(                 void);
       void       gcStop(                  void);

grlAPI Gc2        gcToLowerCase(           Gc2 const letter);
grlAPI Gc         gcToA(                   Gc  const letter);
grlAPI Gcount     gcToU1(                  Gc  const letter, Gc1 * const a, Gc1 * const b, Gc1 * const c, Gc1 * const d);
grlAPI Gcount     gcToU2(                  Gc  const letter, Gc2 * const a, Gc2 * const b);
grlAPI Gc2        gcToUpperCase(           Gc2 const letter);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
