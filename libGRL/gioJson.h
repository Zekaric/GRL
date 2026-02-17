/**************************************************************************************************
file:       gjson
author:     Robbert de Groot
copyright:  2021, Robbert de Groot

description:
Functions for dealing with raw JSON files.

Used jscon.org for information about reading format.
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
/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
#define gjsonCountDEFAULT          4096

typedef enum
{
   gioJsonModeREAD,
   gioJsonModeWRITE
} GioJsonMode;

typedef enum
{
   gioJsonStrLetterNORMAL,
   gioJsonStrLetterHEX,
   gioJsonStrLetterDONE,
   gioJsonStrLetterERROR
} GioJsonStrLetter;

typedef enum
{
   gioJsonScopeTypeNONE,

   gioJsonScopeTypeOBJECT,
   gioJsonScopeTypeARRAY,

   gioJsonScopeTypeCOUNT
} GioJsonScopeType;

typedef enum
{
   gioJsonTypeNONE,

   gioJsonTypeARRAY_START,
   gioJsonTypeARRAY_STOP,

   gioJsonTypeOBJECT_KEY,
   gioJsonTypeOBJECT_START,
   gioJsonTypeOBJECT_STOP,

   gioJsonTypeSEPARATOR,
   gioJsonTypeARRAY_SEPARATOR  = gioJsonTypeSEPARATOR,
   gioJsonTypeOBJECT_SEPARATOR = gioJsonTypeSEPARATOR,

   gioJsonTypeVALUE_STRING_START,
   gioJsonTypeVALUE_NUMBER_INTEGER,
   gioJsonTypeVALUE_NUMBER_NATURAL,
   gioJsonTypeVALUE_NUMBER_REAL,
   gioJsonTypeVALUE_FALSE,
   gioJsonTypeVALUE_NULL,
   gioJsonTypeVALUE_TRUE,

   gioJsonTypeERROR_UNEXPECTED_CHAR          = 100,
   gioJsonTypeERROR_CONSTANT_FALSE_EXPECTED,
   gioJsonTypeERROR_CONSTANT_NULL_EXPECTED,
   gioJsonTypeERROR_CONSTANT_TRUE_EXPECTED,
   gioJsonTypeERROR_NUMBER_EXPECTED,
   gioJsonTypeERROR_NUMBER_REAL_EXPECTED,

   gioJsonTypeINTERNAL_KEY_VALUE_SEPARATOR
} GioJsonType;

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GioJsonType              type;
   Gn8                      n;
   Gi8                      i;
   Gr8                      r;
   Gr4                      r4;
} GioJsonValue;

typedef struct
{
   GioJsonScopeType         type;
   Gb                       isNiceFormatting;
} GioJsonScope;

typedef struct
{
   // JSON file information and configuration.
   Gn8                      version;
   GioJsonMode              mode;
   Gindex                   scope;
   GioJsonScope             scopeList[1024];
   Gb                       isFirstItem;
   Gchar1                   key[gjsonCountDEFAULT + 1];

   // Data repo getters and setters.
   Gio                     *io;
   Gchar1                   lastByte;

   // Read value
   GioJsonValue             value;
   Gchar1                   hex[4];
} GioJson;

/**************************************************************************************************
variable:
**************************************************************************************************/

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gioJsonClocReader(IO)     gleakClocType(gioJsonClocReader_(IO), GioJson)
#define gioJsonClocWriter(IO)     gleakClocType(gioJsonClocWriter_(IO), GioJson)

grlAPI GioJson          *gioJsonClocReader_(                                           Gio * const gio);
grlAPI Gb                gioJsonClocReaderContent(         GioJson       * const json, Gio * const gio);
grlAPI GioJson          *gioJsonClocWriter_(                                           Gio * const gio);
grlAPI Gb                gioJsonClocWriterContent(         GioJson       * const json, Gio * const gio);

grlAPI void              gioJsonDloc(                      GioJson       * const json);
grlAPI void              gioJsonDlocContent(               GioJson       * const json);

grlAPI GioJsonType       gioJsonGetTypeArrayValueOrStop(  GioJson       * const json);
grlAPI GioJsonType       gioJsonGetTypeFileElement(       GioJson       * const json);
grlAPI GioJsonType       gioJsonGetTypeObjectKeyOrStop(   GioJson       * const json);
grlAPI GioJsonType       gioJsonGetTypeObjectValue(       GioJson       * const json);

grlAPI Gb                gioJsonGetI(                      GioJson       * const json,                        Gi8    *  const value);
grlAPI Gchar1 const     *gioJsonGetKey(                    GioJson       * const json);
grlAPI Gb                gioJsonGetN(                      GioJson       * const json,                        Gn8    *  const value);
grlAPI Gb                gioJsonGetR(                      GioJson       * const json,                        Gr8    *  const value);
grlAPI Gb                gioJsonGetR4(                     GioJson       * const json,                        Gr4    *  const value);
grlAPI Gb                gioJsonGetStr(                    GioJson       * const json, Gcount const maxCount, Gchar1 *  const value);
grlAPI GioJsonStrLetter  gioJsonGetStrBinByte(             GioJson       * const json,                        Gn1    *  const value);
grlAPI GioJsonStrLetter  gioJsonGetStrLetter(              GioJson       * const json,                        Gchar1 *  const value);
grlAPI Gb                gioJsonGetStrHex(                 GioJson       * const json, Gchar1 * const h1, Gchar1 * const h2, Gchar1 * const h3, Gchar1 * const h4);

grlAPI Gb                gioJsonIsKeyEqual(                GioJson const * const json, Gchar1 const * const value);
grlAPI Gb                gioJsonIsTypeBin(                 GioJsonType const type);
grlAPI Gb                gioJsonIsTypeI(                   GioJsonType const type);
grlAPI Gb                gioJsonIsTypeN(                   GioJsonType const type);
grlAPI Gb                gioJsonIsTypeR(                   GioJsonType const type);
grlAPI Gb                gioJsonIsTypeStr(                 GioJsonType const type);

grlAPI Gb                gioJsonSetArrayStart(             GioJson       * const json);
grlAPI Gb                gioJsonSetArrayStop(              GioJson       * const json);
grlAPI void              gioJsonSetIsNiceFormatting(       GioJson       * const json, Gb const value);
grlAPI Gb                gioJsonSetKey(                    GioJson       * const json, Gchar1 const * const key);
grlAPI Gb                gioJsonSetObjectStart(            GioJson       * const json);
grlAPI Gb                gioJsonSetObjectStop(             GioJson       * const json);
grlAPI Gb                gioJsonSetSeparator(              GioJson       * const json);
grlAPI Gb                gioJsonSetValueBin(               GioJson       * const json, Gcount const count, Gn1 const *    const value);
grlAPI Gb                gioJsonSetValueBinByte(           GioJson       * const json,                     Gn1            const value);
grlAPI Gb                gioJsonSetValueBinStart(          GioJson       * const json);
grlAPI Gb                gioJsonSetValueBinStop(           GioJson       * const json);
grlAPI Gb                gioJsonSetValueB(                 GioJson       * const json,                     Gb             const value);
grlAPI Gb                gioJsonSetValueI(                 GioJson       * const json,                     Gi8            const value);
grlAPI Gb                gioJsonSetValueN(                 GioJson       * const json,                     Gn8            const value);
grlAPI Gb                gioJsonSetValueNull(              GioJson       * const json);
grlAPI Gb                gioJsonSetValueR(                 GioJson       * const json,                     Gr8            const value);
grlAPI Gb                gioJsonSetValueR4(                GioJson       * const json,                     Gr4            const value);
grlAPI Gb                gioJsonSetValueStr(               GioJson       * const json,                     Gchar1 const * const value);
grlAPI Gb                gioJsonSetValueStrLetter(         GioJson       * const json,                     Gchar1         const value);
grlAPI Gb                gioJsonSetValueStrStart(          GioJson       * const json);
grlAPI Gb                gioJsonSetValueStrStop(           GioJson       * const json);

#define gioJsonSetArrayValueArrayStart(   JSON)                  gioJsonSetArrayStart(     JSON)
#define gioJsonSetArrayValueArrayStop(    JSON)                  gioJsonSetArrayStop(      JSON)
#define gioJsonSetArrayValueB(            JSON,       VALUE)     gioJsonSetValueB(         JSON,       VALUE)
#define gioJsonSetArrayValueBin(          JSON, SIZE, VALUE)     gioJsonSetValueBin(       JSON, SIZE, VALUE)
#define gioJsonSetArrayValueBinByte(      JSON,       VALUE)     gioJsonSetValueBinByte(   JSON,       VALUE)
#define gioJsonSetArrayValueBinStart(     JSON)                  gioJsonSetValueBinStart(  JSON)
#define gioJsonSetArrayValueBinStop(      JSON)                  gioJsonSetValueBinStop(   JSON)
#define gioJsonSetArrayValueI(            JSON,       VALUE)     gioJsonSetValueI(         JSON,       VALUE)
#define gioJsonSetArrayValueN(            JSON,       VALUE)     gioJsonSetValueN(         JSON,       VALUE)
#define gioJsonSetArrayValueNull(         JSON)                  gioJsonSetValueNull(      JSON)
#define gioJsonSetArrayValueObjectStart(  JSON)                  gioJsonSetObjectStart(    JSON)
#define gioJsonSetArrayValueObjectStop(   JSON)                  gioJsonSetObjectStop(     JSON)
#define gioJsonSetArrayValueR(            JSON,       VALUE)     gioJsonSetValueR(         JSON,       VALUE)
#define gioJsonSetArrayValueR4(           JSON,       VALUE)     gioJsonSetValueR4(        JSON,       VALUE)
#define gioJsonSetArrayValueStr(          JSON,       VALUE)     gioJsonSetValueStr(       JSON,       VALUE)
#define gioJsonSetArrayValueStrLetter(    JSON,       VALUE)     gioJsonSetValueStrLetter( JSON,       VALUE)
#define gioJsonSetArrayValueStrStart(     JSON)                  gioJsonSetValueStrStart(  JSON)
#define gioJsonSetArrayValueStrStop(      JSON)                  gioJsonSetValueStrStop(   JSON)

#define gioJsonSetFileValueArrayStart(   JSON)                   gioJsonSetArrayStart(     JSON)
#define gioJsonSetFileValueArrayStop(    JSON)                   gioJsonSetArrayStop(      JSON)
#define gioJsonSetFileValueB(            JSON,       VALUE)      gioJsonSetValueB(         JSON,       VALUE)
#define gioJsonSetFileValueBin(          JSON, SIZE, VALUE)      gioJsonSetValueBin(       JSON, SIZE, VALUE)
#define gioJsonSetFileValueBinByte(      JSON,       VALUE)      gioJsonSetValueBinByte(   JSON,       VALUE)
#define gioJsonSetFileValueBinStart(     JSON)                   gioJsonSetValueBinStart(  JSON)
#define gioJsonSetFileValueBinStop(      JSON)                   gioJsonSetValueBinStop(   JSON)
#define gioJsonSetFileValueI(            JSON,       VALUE)      gioJsonSetValueI(         JSON,       VALUE)
#define gioJsonSetFileValueN(            JSON,       VALUE)      gioJsonSetValueN(         JSON,       VALUE)
#define gioJsonSetFileValueNull(         JSON)                   gioJsonSetValueNull(      JSON)
#define gioJsonSetFileValueObjectStart(  JSON)                   gioJsonSetObjectStart(    JSON)
#define gioJsonSetFileValueObjectStop(   JSON)                   gioJsonSetObjectStop(     JSON)
#define gioJsonSetFileValueR(            JSON,       VALUE)      gioJsonSetValueR(         JSON,       VALUE)
#define gioJsonSetFileValueR4(           JSON,       VALUE)      gioJsonSetValueR4(        JSON,       VALUE)
#define gioJsonSetFileValueStr(          JSON,       VALUE)      gioJsonSetValueStr(       JSON,       VALUE)
#define gioJsonSetFileValueStrLetter(    JSON,       VALUE)      gioJsonSetValueStrLetter( JSON,       VALUE)
#define gioJsonSetFileValueStrStart(     JSON)                   gioJsonSetValueStrStart(  JSON)
#define gioJsonSetFileValueStrStop(      JSON)                   gioJsonSetValueStrStop(   JSON)

#define gioJsonSetObjectValueArrayStart( JSON, KEY)              (gioJsonSetKey(           JSON, KEY) && gioJsonSetArrayStart(   JSON))
#define gioJsonSetObjectValueArrayStop(  JSON)                   gioJsonSetArrayStop(      JSON)
#define gioJsonSetObjectValueB(          JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueB(       JSON,       VALUE))
#define gioJsonSetObjectValueBin(        JSON, KEY, SIZE, VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueBin(     JSON, SIZE, VALUE))
#define gioJsonSetObjectValueBinByte(    JSON,            VALUE) gioJsonSetValueBinByte(   JSON,       VALUE)
#define gioJsonSetObjectValueBinStart(   JSON, KEY)              (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueBinStart(JSON))
#define gioJsonSetObjectValueBinStop(    JSON)                   gioJsonSetValueBinStop(   JSON)
#define gioJsonSetObjectValueI(          JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueI(       JSON,       VALUE))
#define gioJsonSetObjectValueN(          JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueN(       JSON,       VALUE))
#define gioJsonSetObjectValueNull(       JSON, KEY)              (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueNull(    JSON))
#define gioJsonSetObjectValueObjectStart(JSON, KEY)              (gioJsonSetKey(           JSON, KEY) && gioJsonSetObjectStart(  JSON))
#define gioJsonSetObjectValueObjectStop( JSON)                   gioJsonSetObjectStop(     JSON)
#define gioJsonSetObjectValueR(          JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueR(       JSON,       VALUE))
#define gioJsonSetObjectValueR4(         JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueR4(      JSON,       VALUE))
#define gioJsonSetObjectValueStr(        JSON, KEY,       VALUE) (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueStr(     JSON,       VALUE))
#define gioJsonSetObjectValueStrLetter(  JSON,            VALUE) gioJsonSetValueStr(       JSON,       VALUE)
#define gioJsonSetObjectValueStrStart(   JSON, KEY)              (gioJsonSetKey(           JSON, KEY) && gioJsonSetValueStrStart(JSON))
#define gioJsonSetObjectValueStrStop(    JSON)                   gioJsonSetValueStrStop(   JSON)

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
