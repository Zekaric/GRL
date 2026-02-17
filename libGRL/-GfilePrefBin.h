/******************************************************************************
file:       GprefBin
author:     Robbert de Groot
copyright:  2003-2009, Robbert de Groot

description:
A library to read and write a GprefBin files.

A GprefBin file is a simple linear list of records file.

Each record is a key and value pair.  Value may be optional.

Records are in sequence from start of file to end of file.
Random access is possible but not really a format for
overwriting unless you are careful.

Record format:
Keys are 1-128 UTF8 bytes long.
Keys may have a value associated with them.

Key part of record format:
byte  0 - 0??????? no value, just key.
          1??????? value follows key.
          .SSSSSSS
            SSSSSSS + 1 is the size of the key buffer + 1.
bytes 1 - SSSSSSS + 1
            Key UTF8 string.

Value part of record format:
byte  0 - 0VVVVVVV
            7 bit value.
        - 10SSSSSS VVVVVVVV (x SSSSSS + 1)
            Buffer of 1-64 bytes.
        - 11CCCCCC SSSSSSSS (x CCCCCC + 1), VVVVVVVV (x Size)
            Buffer where size is 1-64 byte natural.
******************************************************************************/

#if !defined(GPREFBINH)
#define      GPREFBINH

/******************************************************************************
constant:
******************************************************************************/
typedef enum
{
   gprefBinModeNONE,
   gprefBinModeFILE,
   gprefBinModeBUFFER
} GprefBinMode;


/******************************************************************************
type:
******************************************************************************/
typedef struct
{
   Gfile       *file;
   Gbuf    *buffer;
   GfileIndex   bufferIndex;

   Gs          *key;
   Gn1          value[64];
   Gcount       valueCount;
   Gb           isValueRead;
} GprefBin;

/******************************************************************************
function:
******************************************************************************/
//lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026
#define gprefBinCreate(GPREFMODE, GFILE_OR_GN1ARRAY) \
   ((GprefBin *) gleakCreate(gprefBinCreate_((GPREFMODE), (GFILE_OR_GN1ARRAY)), gsizeof(Gpref)))
#define gprefBinGetValueCreate(PREF) \
   (Gn1 *) gleakCreate(gprefBinGetValueCreate_(PREF), gprefBinGetValueCount(PREF));
//lint -restore

grlAPI GprefBin         *gprefBinCreate_(                                       GprefBinMode const mode, Gp * const value);
grlAPI Gb                gprefBinCreateContent(    GprefBin       * const pref, GprefBinMode const mode, Gp * const value);

grlAPI void              gprefBinDestroy(          GprefBin       * const pref);
grlAPI void              gprefBinDestroyContent(   GprefBin       * const pref);

grlAPI Gb                gprefBinGet(              GprefBin       * const pref);
grlAPI Gs               *gprefBinGetKey(           GprefBin const * const pref);
grlAPI Gs const * const  gprefBinGetKeyHeader(     void);
grlAPI Gb                gprefBinGetValue(         GprefBin       * const pref, Gn1 * const value);
grlAPI Gb                gprefBinGetValueGuid(     GprefBin       * const pref, Gguid * const value);
grlAPI Gb                gprefBinGetValueI4(       GprefBin       * const pref, Gi4 * const value);
grlAPI Gb                gprefBinGetValueN4(       GprefBin       * const pref, Gn4 * const value);
grlAPI Gb                gprefBinGetValueN8(       GprefBin       * const pref, Gn8 * const value);
grlAPI Gb                gprefBinGetValueR4(       GprefBin       * const pref, Gr4 * const value);
grlAPI Gb                gprefBinGetValueA(        GprefBin       * const pref, Char * const value);
grlAPI Gb                gprefBinGetValueS(        GprefBin       * const pref, Gs * const value);
grlAPI Gcount            gprefBinGetValueCount(    GprefBin const * const pref);
grlAPI Gn1              *gprefBinGetValueCreate_(  GprefBin       * const pref);
grlAPI GfileIndex        gprefBinGetValueIndex(    GprefBin const * const pref);

grlAPI Gb                gprefBinSet(              GprefBin const * const pref, Gs   const * const key, Gcount const byteCount, Gn1 const * const byteBuffer);
grlAPI Gb                gprefBinSetA(             GprefBin const * const pref, Char const * const key, Gcount const byteCount, Gn1 const * const byteBuffer);
grlAPI Gb                gprefBinSetAGuid(         GprefBin const * const pref, Char const * const key, Gguid value);
grlAPI Gb                gprefBinSetAI4(           GprefBin const * const pref, Char const * const key, Gi4 value);
grlAPI Gb                gprefBinSetAN4(           GprefBin const * const pref, Char const * const key, Gn4 value);
grlAPI Gb                gprefBinSetAN8(           GprefBin const * const pref, Char const * const key, Gn8 value);
grlAPI Gb                gprefBinSetAR4(           GprefBin const * const pref, Char const * const key, Gr4 value);
grlAPI Gb                gprefBinSetAA(            GprefBin const * const pref, Char const * const key, Char const * const value);
grlAPI Gb                gprefBinSetAS(            GprefBin const * const pref, Char const * const key, Gs const * const value);
grlAPI Gb                gprefBinSetHeader(        GprefBin const * const pref);
grlAPI Gb                gprefBinSetSpec(          GprefBin const * const pref);
       Gb                gprefBinStart(            void);
       void              gprefBinStop(             void);

#endif
