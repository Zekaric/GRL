/**************************************************************************************************
file:       GodLib
author:     Robbert de Groot
copyright:  2025, Robbert de Groot

description:
GodLib is a IO library for GOD Files.  A GOD file is a JSON 'like' file without JSON's limitations.
GOD - Groot's Organized Data file.  JSON is nice and all but implementations are all over the map
because JavaScript has limitations.
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

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/
#define godCountDEFAULT             4096

typedef enum
{
   gioGodModeREAD,
   gioGodModeWRITE,
} GioGodMode;

typedef enum
{
   gioGodStrLetterNORMAL,
   gioGodStrLetterHEX,
   gioGodStrLetterDONE,
   gioGodStrLetterERROR
} GioGodStrLetter;

typedef enum
{
   gioGodScopeTypeNONE,

   gioGodScopeTypeGROUP,
   gioGodScopeTypeARRAY,

   gioGodScopeTypeCOUNT
} GioGodScopeType;

typedef enum
{
   gioGodTypeNONE,

   gioGodTypeARRAY_START,
   gioGodTypeARRAY_STOP,

   gioGodTypeGROUP_KEY,
   gioGodTypeGROUP_START,
   gioGodTypeGROUP_STOP,

   gioGodTypeSEPARATOR,

   gioGodTypeVALUE_BINARY_START,
   gioGodTypeVALUE_NUMBER_INTEGER,
   gioGodTypeVALUE_NUMBER_NATURAL,
   gioGodTypeVALUE_NUMBER_REAL,
   gioGodTypeVALUE_FALSE,
   gioGodTypeVALUE_INFINITY,
   gioGodTypeVALUE_INFINITY_NEGATIVE,
   gioGodTypeVALUE_MAX,
   gioGodTypeVALUE_MAX_NEGATIVE,
   gioGodTypeVALUE_MIN,
   gioGodTypeVALUE_MIN_NEGATIVE,
   gioGodTypeVALUE_NO_VALUE,
   gioGodTypeVALUE_NOT_A_NUMBER,
   gioGodTypeVALUE_NULL,
   gioGodTypeVALUE_STRING_START,
   gioGodTypeVALUE_TRUE,

   gioGodTypeERROR_UNEXPECTED_CHAR           = 100,
   gioGodTypeERROR_NUMBER_EXPECTED,
   gioGodTypeERROR_NUMBER_REAL_EXPECTED,

   gioGodTypeINTERNAL_KEY_VALUE_SEPARATOR
} GioGodType;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GioGodType            type;
   Gn8                   n;
   Gi8                   i;
   Gr8                   r;
   Gr4                   r4;
} GioGodValue;

typedef struct
{
   GioGodScopeType       type;
   Gb                    isNiceFormatting;
} GioGodScope;

typedef struct
{
   // GioGod file information and configuration.
   Gn8                   version;
   GioGodMode            mode;
   Gindex                scope;
   GioGodScope           scopeList[1024];
   Gb                    isFirstItem;
   Gb                    isKeySet;
   Gchar1                key[godCountDEFAULT + 1];

   // Data get and set.
   Gio                  *io;
   Gchar1                lastByte;

   // Read value.
   GioGodValue           value;
   Gchar1                hex[4];
} GioGod;

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
#define gioGodClocReader(IO)     gleakClocType(gioGodClocReader_(IO), GioGod)
#define gioGodClocWriter(IO)     gleakClocType(gioGodClocWriter_(IO), GioGod)

grlAPI GioGod           *gioGodClocReader_(                                          Gio * const io);
grlAPI Gb                gioGodClocReaderContent(        GioGod       * const gigod, Gio * const io);
grlAPI GioGod           *gioGodClocWriter_(                                          Gio * const io);
grlAPI Gb                gioGodClocWriterContent(        GioGod       * const gigod, Gio * const io);

grlAPI void              gioGodDloc(                     GioGod       * const gigod);
grlAPI void              gioGodDlocContent(              GioGod       * const gigod);

grlAPI GioGodType        gioGodGetTypeArrayValueOrStop(  GioGod       * const gigod);
grlAPI GioGodType        gioGodGetTypeFileElement(       GioGod       * const gigod);
grlAPI GioGodType        gioGodGetTypeObjectKeyOrStop(   GioGod       * const gigod);
grlAPI GioGodType        gioGodGetTypeObjectValue(       GioGod       * const gigod);

grlAPI Gb                gioGodGetI(                     GioGod       * const gigod,                        Gi8    *  const value);
grlAPI Gchar1 const     *gioGodGetKey(                   GioGod       * const gigod);
grlAPI Gb                gioGodGetN(                     GioGod       * const gigod,                        Gn8    *  const value);
grlAPI Gb                gioGodGetR(                     GioGod       * const gigod,                        Gr8    *  const value);
grlAPI Gb                gioGodGetR4(                    GioGod       * const gigod,                        Gr4    *  const value);
grlAPI Gb                gioGodGetStr(                   GioGod       * const gigod, Gcount const maxCount, Gchar1 *  const value);
grlAPI GioGodStrLetter   gioGodGetStrBinByte(            GioGod       * const gigod,                        Gn1    *  const value);
grlAPI GioGodStrLetter   gioGodGetStrLetter(             GioGod       * const gigod,                        Gchar1 *  const value);
grlAPI Gb                gioGodGetStrHex(                GioGod       * const gigod, Gchar1 * const h1, Gchar1 * const h2, Gchar1 * const h3, Gchar1 * const h4);

grlAPI Gb                gioGodIsKeyEqual(               GioGod const * const gigod, Gchar1 const * const value);
grlAPI Gb                gioGodIsTypeBin(                GioGodType const type);
grlAPI Gb                gioGodIsTypeI(                  GioGodType const type);
grlAPI Gb                gioGodIsTypeN(                  GioGodType const type);
grlAPI Gb                gioGodIsTypeR(                  GioGodType const type);
grlAPI Gb                gioGodIsTypeStr(                GioGodType const type);

grlAPI Gb                gioGodSetArrayStart(            GioGod       * const gigod);
grlAPI Gb                gioGodSetArrayStop(             GioGod       * const gigod);
grlAPI Gb                gioGodSetGroupStart(            GioGod       * const gigod);
grlAPI Gb                gioGodSetGroupStop(             GioGod       * const gigod);
grlAPI void              gioGodSetIsNiceFormatting(      GioGod       * const gigod, Gb const value);
grlAPI Gb                gioGodSetKey(                   GioGod       * const gigod, Gchar1 const * const key);
grlAPI Gb                gioGodSetSeparator(             GioGod       * const gigod);
grlAPI Gb                gioGodSetValueBin(              GioGod       * const gigod, Gcount const count, Gn1 const *    const value);
grlAPI Gb                gioGodSetValueBinByte(          GioGod       * const gigod,                     Gn1            const value);
grlAPI Gb                gioGodSetValueBinStart(         GioGod       * const gigod);
grlAPI Gb                gioGodSetValueB(                GioGod       * const gigod,                     Gb             const value);
grlAPI Gb                gioGodSetValueI(                GioGod       * const gigod,                     Gi8            const value, Gcount const byteCount);
grlAPI Gb                gioGodSetValueN(                GioGod       * const gigod,                     Gn8            const value, Gcount const byteCount);
grlAPI Gb                gioGodSetValueNull(             GioGod       * const gigod);
grlAPI Gb                gioGodSetValueR(                GioGod       * const gigod,                     Gr8            const value);
grlAPI Gb                gioGodSetValueR4(               GioGod       * const gigod,                     Gr4            const value);
grlAPI Gb                gioGodSetValueStr(              GioGod       * const gigod,                     Gchar1 const * const value);
grlAPI Gb                gioGodSetValueStrLetter(        GioGod       * const gigod,                     Gchar1         const value);
grlAPI Gb                gioGodSetValueStrStart(         GioGod       * const gigod);
grlAPI Gb                gioGodSetValueStrStop(          GioGod       * const gigod);
       Gb                gioGodStart(                    void);
       void              gioGodStop(                     void);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/

#define gioGodSetArrayValueArrayStart(    GOD)                                gioGodSetArrayStart(    GOD)
#define gioGodSetArrayValueArrayStop(     GOD)                                gioGodSetArrayStop(     GOD)
#define gioGodSetArrayValueB(             GOD,       VALUE)                   gioGodSetValueB(        GOD,       VALUE)
#define gioGodSetArrayValueBin(           GOD, SIZE, VALUE)                   gioGodSetValueBin(      GOD, SIZE, VALUE)
#define gioGodSetArrayValueBinByte(       GOD,       VALUE)                   gioGodSetValueBinByte(  GOD,       VALUE)
#define gioGodSetArrayValueBinStart(      GOD)                                gioGodSetValueBinStart( GOD)
#define gioGodSetArrayValueI(             GOD,       VALUE, BYTECOUNT)        gioGodSetValueI(        GOD,       VALUE, BYTECOUNT)
#define gioGodSetArrayValueN(             GOD,       VALUE, BYTECOUNT)        gioGodSetValueN(        GOD,       VALUE, BYTECOUNT)
#define gioGodSetArrayValueNull(          GOD)                                gioGodSetValueNull(     GOD)
#define gioGodSetArrayValueObjectStart(   GOD)                                gioGodSetGroupStart(    GOD)
#define gioGodSetArrayValueObjectStop(    GOD)                                gioGodSetGroupStop(     GOD)
#define gioGodSetArrayValueR(             GOD,       VALUE)                   gioGodSetValueR(        GOD,       VALUE)
#define gioGodSetArrayValueR4(            GOD,       VALUE)                   gioGodSetValueR4(       GOD,       VALUE)
#define gioGodSetArrayValueStr(           GOD,       VALUE)                   gioGodSetValueStr(      GOD,       VALUE)
#define gioGodSetArrayValueStrLetter(     GOD,       VALUE)                   gioGodSetValueStrLetter(GOD,       VALUE)
#define gioGodSetArrayValueStrStart(      GOD)                                gioGodSetValueStrStart( GOD)
#define gioGodSetArrayValueStrStop(       GOD)                                gioGodSetValueStrStop(  GOD)

#define gioGodSetGroupValueArrayStart(    GOD, KEY)                          (gioGodSetKey(           GOD, KEY) && gioGodSetArrayStart(   GOD))
#define gioGodSetGroupValueArrayStop(     GOD)                                gioGodSetArrayStop(     GOD)
#define gioGodSetGroupValueB(             GOD, KEY,       VALUE)             (gioGodSetKey(           GOD, KEY) && gioGodSetValueB(       GOD,       VALUE))
#define gioGodSetGroupValueBin(           GOD, KEY, SIZE, VALUE)             (gioGodSetKey(           GOD, KEY) && gioGodSetValueBin(     GOD, SIZE, VALUE))
#define gioGodSetGroupValueBinByte(       GOD,            VALUE)              gioGodSetValueBinByte(  GOD,       VALUE)
#define gioGodSetGroupValueBinStart(      GOD, KEY)                          (gioGodSetKey(           GOD, KEY) && gioGodSetValueBinStart(GOD))
#define gioGodSetGroupValueI(             GOD, KEY,       VALUE, BYTECOUNT)  (gioGodSetKey(           GOD, KEY) && gioGodSetValueI(       GOD,       VALUE, BYTECOUNT))
#define gioGodSetGroupValueN(             GOD, KEY,       VALUE, BYTECOUNT)  (gioGodSetKey(           GOD, KEY) && gioGodSetValueN(       GOD,       VALUE, BYTECOUNT))
#define gioGodSetGroupValueNone(          GOD, KEY)                           gioGodSetKey(           GOD, KEY)
#define gioGodSetGroupValueNull(          GOD, KEY)                          (gioGodSetKey(           GOD, KEY) && gioGodSetValueNull(    GOD))
#define gioGodSetGroupValueObjectStart(   GOD, KEY)                          (gioGodSetKey(           GOD, KEY) && gioGodSetGroupStart(  GOD))
#define gioGodSetGroupValueObjectStop(    GOD)                                gioGodSetGroupStop(     GOD)
#define gioGodSetGroupValueR(             GOD, KEY,       VALUE)             (gioGodSetKey(           GOD, KEY) && gioGodSetValueR(       GOD,       VALUE))
#define gioGodSetGroupValueR4(            GOD, KEY,       VALUE)             (gioGodSetKey(           GOD, KEY) && gioGodSetValueR4(      GOD,       VALUE))
#define gioGodSetGroupValueStr(           GOD, KEY,       VALUE)             (gioGodSetKey(           GOD, KEY) && gioGodSetValueStr(     GOD,       VALUE))
#define gioGodSetGroupValueStrLetter(     GOD,            VALUE)              gioGodSetValueStr(      GOD,       VALUE)
#define gioGodSetGroupValueStrStart(      GOD, KEY)                          (gioGodSetKey(           GOD, KEY) && gioGodSetValueStrStart(GOD))
#define gioGodSetGroupValueStrStop(       GOD)                                gioGodSetValueStrStop(  GOD)
