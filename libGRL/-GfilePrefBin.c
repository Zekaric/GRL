/******************************************************************************
file:       GprefBinBin
author:     Robbert de Groot
copyright:  2003-2011, Robbert de Groot

description:
A library to read and write a binary preference file.
******************************************************************************/

/******************************************************************************
include
******************************************************************************/
#include "pre.h"

/******************************************************************************
local:
constant:
******************************************************************************/
#define GPREV_BIN_VERSION 1
#define GPREF_BIN_SPEC \
   "GPrefBin file format\n\n"\
   "This is a simple key value format.\n"\
   "File    = Record*\n"\
   "Record  = Key [+ Value] \n"\
   "Key     = b0SSSSSSS, [key bytes]\n"\
   "        = b1SSSSSSS, [key bytes]\n"\
   "              bSSSSSSS + 1 (1-128) defines size of [key bytes].\n"\
   "              0 start case means no value bytes follow.\n"\
   "              1 start case means value bytes follow.\n"\
   "Value   = b0VVVVVVV\n"\
   "              7 bit value.\n"\
   "        = b10SSSSSS bVVVVVVVV (x bSSSSSS + 1)\n"\
   "              Buffer of 1-64 bytes long.\n"\
   "        = b11CCCCCC bSSSSSSSS (x bCCCCCC + 1) bVVVVVVVV (x Size)\n"\
   "              Buffer. Size is a natural 1-64 bytes long.\n"\
   "All sizes are unsigned, big endian integers.\n"

/******************************************************************************
variable:
******************************************************************************/
static Gb    _isStarted = gbFALSE;
static Gs   *_headerStr = NULL;
static Gs   *_specStr   = NULL;

/******************************************************************************
prototype:
******************************************************************************/
static Gi4   _GetByte(  GprefBin * const pref);
static Gb    _GetBytes( GprefBin * const pref, Gcount const count, Gn1 * const buffer);

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gprefBinCreate
******************************************************************************/
grlAPI GprefBin *gprefBinCreate_(GprefBinMode const mode, Gp * const value)
{
   GprefBin *pref;

   genter;

   greturnIf(
         mode == gprefBinModeNONE ||
         !value,
      NULL);

   // Create the buffer.
   pref = gmemCreateType(GprefBin);
   greturnNullIf(!pref);

   if (!gprefBinCreateContent(pref, mode, value))
   {
      gprefBinDestroy(pref);
      greturn NULL;
   }

   greturn pref;
}

/******************************************************************************
func: gprefBinCreateContent
******************************************************************************/
grlAPI Gb gprefBinCreateContent(GprefBin * const pref, GprefBinMode const mode, Gp * const value)
{
   genter;

   greturnIf(
         !pref                    ||
         mode == gprefBinModeNONE ||
         !value,
      gbFALSE);

   if (mode == gprefBinModeFILE)
   {
      pref->file = (Gfile *) value;
   }
   else
   {
      pref->buffer = (Gbuf *) value;
   }

   pref->key = gsCreate();

   greturn gbTRUE;
}

/******************************************************************************
func: gprefBinDestroy
******************************************************************************/
grlAPI void gprefBinDestroy(GprefBin * const pref)
{
   genter;

   greturnVoidIf(!pref);

   gprefBinDestroyContent(pref);
   gmemDestroy(pref);

   greturn;
}

/******************************************************************************
func: gprefBinDestroyContent
******************************************************************************/
grlAPI void gprefBinDestroyContent(GprefBin * const pref)
{
   genter;

   greturnVoidIf(!pref);

   gsDestroy(pref->key);

   gmemClearType(pref, GprefBin);

   greturn;
}

/******************************************************************************
func: gprefBinGet

Read the next record.
******************************************************************************/
grlAPI Gb gprefBinGet(GprefBin * const pref)
{
   Gb     result,
          isValuePresent;
   Gindex index,
          loopIndex;
   Gi4    byte;
   Gcount count;
   Gc1    key[129];
   Gn     size;

   genter;

   greturnIf(!pref, gbFALSE);

   result = gbTRUE;

   gsFlush(pref->key);

   loopOnce(loopIndex)
   {
      // Get the line.
      byte = _GetByte(pref);

      // Check for value
      isValuePresent    = gbFALSE;
      pref->valueCount  = 0;
      pref->isValueRead = gbTRUE;
      if (byte & 0x80)
      {
         isValuePresent = gbTRUE;
      }

      // Get Key size;
      count = byte & 0x7f;
      gmemClearTypeArray(key, Gc1, 129);
      _GetBytes(pref, count, key);
      gsSetU1(pref->key, key);

      breakIf(!isValuePresent);

      // Get the value
      byte = _GetByte(pref);

      // 1-127 value.
      if      ((byte & 0x80) == 0)
      {
         pref->valueCount = 1;
         pref->value[0]   = (byte & 0x7f);
      }
      else if ((byte & 0xc0) == 0x80)
      {
         pref->valueCount = (byte & 0x3f) + 1;
         _GetBytes(pref, pref->valueCount, pref->value);
      }
      else 
      {
         pref->valueCount = (byte & 0x3f) + 1;
         if (pref->valueCount > 4)
         {
            result = gbFALSE;
            break;
         }

         size = 0;
         forCount(index, pref->valueCount)
         {
            size <<= 8;
            byte   = _GetByte(pref);
            size  |= byte;
         }
         pref->valueCount  = (Gcount) size;
         pref->isValueRead = gbFALSE;
      }
   }

   greturn result;
}

/******************************************************************************
func: gprefBinGetKey
******************************************************************************/
grlAPI Gs *gprefBinGetKey(GprefBin const * const pref)
{
   genter;

   greturnIf(!pref, NULL);

   greturn pref->key;
}

/******************************************************************************
func: gprefBinGetKeyHeader
******************************************************************************/
grlAPI Gs const * const gprefBinGetKeyHeader(void)
{
   genter;

   greturn _headerStr;
}

/******************************************************************************
func: gprefBinGetValue
******************************************************************************/
grlAPI Gb gprefBinGetValue(GprefBin * const pref, Gn1 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   result = gbTRUE;

   if (pref->isValueRead)
   {
      if (value)
      {
         gmemCopyOverTypeArray(pref->value, Gn1, pref->valueCount, value); 
      }
      else
      {
         pref->bufferIndex += pref->valueCount;
      }
   }
   else
   {
      if (value)
      {
         if (!_GetBytes(pref, pref->valueCount, value))
         {
            result = gbFALSE;
         }
      }
      else
      {
         if (gfileSetPosition(pref->file, gpositionCURRENT, pref->valueCount) !=
               gfileSetPositionSUCCESS)
         {
            result = gbFALSE;
         }
      }
      pref->isValueRead = gbTRUE;
   }

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueGuid
******************************************************************************/
grlAPI Gb gprefBinGetValueGuid(GprefBin * const pref, Gguid * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   greturnFalseIf(gprefBinGetValueCount(pref) != 16);

   result = gprefBinGetValue(pref, (Gn1 *) value->b);

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueI4
******************************************************************************/
grlAPI Gb gprefBinGetValueI4(GprefBin * const pref, Gi4 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   greturnFalseIf(gprefBinGetValueCount(pref) != 4);

   result = gprefBinGetValue(pref, (Gn1 *) value);

#if grlSWAP_NEEDED == 1
   gswap4(value);
#endif

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueN4
******************************************************************************/
grlAPI Gb gprefBinGetValueN4(GprefBin * const pref, Gn4 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   greturnFalseIf(gprefBinGetValueCount(pref) != 4);

   result = gprefBinGetValue(pref, (Gn1 *) value);

#if grlSWAP_NEEDED == 1
   gswap4(value);
#endif

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueN8
******************************************************************************/
grlAPI Gb gprefBinGetValueN8(GprefBin * const pref, Gn8 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   greturnFalseIf(gprefBinGetValueCount(pref) != 8);

   result = gprefBinGetValue(pref, (Gn1 *) value);

#if grlSWAP_NEEDED == 1
   gswap8(value);
#endif

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueR4
******************************************************************************/
grlAPI Gb gprefBinGetValueR4(GprefBin * const pref, Gr4 * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   greturnFalseIf(gprefBinGetValueCount(pref) != 4);

   result = gprefBinGetValue(pref, (Gn1 *) value);

#if grlSWAP_NEEDED == 1
   gswap4(value);
#endif

   greturn result;
}

/******************************************************************************
func: gprefBinGetValueA
******************************************************************************/
grlAPI Gb gprefBinGetValueA(GprefBin * const pref, Char * const value)
{
   Gb result;

   genter;

   greturnFalseIf(!pref);

   result = gprefBinGetValue(pref, (Gn1 *) value);
   
   greturn result;
}

/******************************************************************************
func: gprefBinGetValueS
******************************************************************************/
grlAPI Gb gprefBinGetValueS(GprefBin * const pref, Gs * const value)
{
   Gb     result;
   Gc1   *utf8String;

   genter;

   greturnFalseIf(!pref);

   result = gbFALSE;

   utf8String = gmemCreateTypeArray(Gn1, gprefBinGetValueCount(pref));
   greturnFalseIf(!utf8String);

   stopIf(!gprefBinGetValue(pref, utf8String));

   gsSetU1(value, utf8String);

   result = gbTRUE;

STOP:
   gmemDestroy(utf8String);
   
   greturn result;
}

/******************************************************************************
func: gprefBinGetValueCount
******************************************************************************/
grlAPI Gcount gprefBinGetValueCount(GprefBin const * const pref)
{
   genter;

   greturn pref->valueCount;
}

/******************************************************************************
func: gprefBinGetValueCreate_
******************************************************************************/
grlAPI Gn1 *gprefBinGetValueCreate_(GprefBin * const pref)
{
   Gn1 *value;

   genter;

   value = gmemCreateTypeArray(Gn1, pref->valueCount);
   greturnNullIf(!value);

   if (!gprefBinGetValue(pref, value))
   {
      gmemDestroy(value);
      greturn NULL;
   }

   greturn value;
}

/******************************************************************************
func: gprefBinGetValueIndex
******************************************************************************/
grlAPI GfileIndex gprefBinGetValueIndex(GprefBin const * const pref)
{
   GfileIndex pos;

   genter;

   if (pref->file)
   {
      pos = gfileGetPosition(pref->file);
   }
   else
   {
      pos = pref->bufferIndex;
   }

   greturn pos;
}

/******************************************************************************
func: gprefBinSet

Write to the preference file.
******************************************************************************/
grlAPI Gb gprefBinSet(GprefBin const * const pref, Gs const * const key, Gcount const byteCount, Gn1 const * const byteBuffer)
{
   Gb     result;
   Gi4    size;
   Gn1    byte;
   Gn1   *buffer;
   Gcount count;

   genter;

   greturnFalseIf(!pref);

   result = gbTRUE;

   // Get the key.
   buffer = gsCreateU1(key);
   size   = gcGetCountU1(buffer);
   stopIf(size > 128);

   // Get the key size byte.
   byte = (Gn1) (size - 1);
   if (byteCount)
   {
      byte |= ((Gn1) 0x80);
   }

   //lint -save -e534
   // Write to the file.
   if (pref->file)
   {
      result &= gfileSet(pref->file, 1,    &byte,  NULL);
      result &= gfileSet(pref->file, size, buffer, NULL);

      // Simple 7 bit value.
      if      (byteCount     == 1 && 
               byteBuffer[0] <  128)
      {
         result &= gfileSet(pref->file, 1, byteBuffer, NULL);
      }
      // Simple 64 byte dump
      else if (0 < byteCount && byteCount <= 64)
      {
         byte = (Gn1) (0x80 | (byteCount - 1));
         result &= gfileSet(pref->file, 1,         &byte,      NULL);
         result &= gfileSet(pref->file, byteCount, byteBuffer, NULL);
      }
      else if (0 < byteCount)
      {
         if      (byteCount < (1 << 8))
         {
            byte  = 0xC1;
            count = 1;
         }
         else if (byteCount < (1 << 16))
         {
            byte  = 0xC2;
            count = 2;
         }
         else if (byteCount < (1 << 24))
         {
            byte  = 0xC3;
            count = 3;
         }
         else //if (byteCount < (1 << 32))
         {
            byte  = 0xC4;
            count = 4;
         }
         // Larger numbers to come later.
         result &= gfileSet(pref->file, 1, &byte, NULL);

         // dump out the size.
         switch (count)
         {
         case 4:
            byte = (Gn1) ((byteCount >> 24) & 0xff);
            result &= gfileSet(pref->file, 1, &byte, NULL);
         case 3:
            byte = (Gn1) ((byteCount >> 16) & 0xff);
            result &= gfileSet(pref->file, 1, &byte, NULL);
         case 2:
            byte = (Gn1) ((byteCount >>  8) & 0xff);
            result &= gfileSet(pref->file, 1, &byte, NULL);
         case 1:
         default:
            byte = (Gn1) ((byteCount >>  0) & 0xff);
            result &= gfileSet(pref->file, 1, &byte, NULL);
         }

         result &= gfileSet(pref->file, byteCount, byteBuffer, NULL);
      }
   }
   else
   {
      // In memory buffer writing to come later.
   }
   //lint -restore

STOP:
   gmemDestroy(buffer);

   greturn result;
}

/******************************************************************************
func: gprefBinSetA
******************************************************************************/
grlAPI Gb gprefBinSetA(GprefBin const * const pref, Char const * const key, Gcount const byteCount, Gn1 const * const byteBuffer)
{
   Gs *skey;
   Gb  result;

   genter;

   skey   = gsCreateFromA(key);
   result = gprefBinSet(pref, skey, byteCount, byteBuffer);
   gsDestroy(skey);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAGuid
******************************************************************************/
grlAPI Gb gprefBinSetAGuid(GprefBin const * const pref, Char const * const key, Gguid value)
{
   Gb result;

   genter;

   result = gprefBinSetA(pref, key, 16, value.b);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAI4
******************************************************************************/
grlAPI Gb gprefBinSetAI4(GprefBin const * const pref, Char const * const key, Gi4 value)
{
   Gb   result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif

   result = gprefBinSetA(pref, key, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAN4
******************************************************************************/
grlAPI Gb gprefBinSetAN4(GprefBin const * const pref, Char const * const key, Gn4 value)
{
   Gb   result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif

   result = gprefBinSetA(pref, key, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAN8
******************************************************************************/
grlAPI Gb gprefBinSetAN8(GprefBin const * const pref, Char const * const key, Gn8 value)
{
   Gb   result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap8(&value);
#endif

   result = gprefBinSetA(pref, key, 8, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAR4
******************************************************************************/
grlAPI Gb gprefBinSetAR4(GprefBin const * const pref, Char const * const key, Gr4 value)
{
   Gb   result;

   genter;

#if grlSWAP_NEEDED == 1
   gswap4(&value);
#endif

   result = gprefBinSetA(pref, key, 4, (Gn1 *) &value);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAA
******************************************************************************/
grlAPI Gb gprefBinSetAA(GprefBin const * const pref, Char const * const key, Char const * const value)
{
   Gb result;

   genter;

   result = gprefBinSetA(pref, key, gcGetCountA(value), (Gn1 *) value);

   greturn result;
}

/******************************************************************************
func: gprefBinSetAS
******************************************************************************/
grlAPI Gb gprefBinSetAS(GprefBin const * const pref, Char const * const key, Gs const * const value)
{
   Gb   result;
   Gc1 *utf8;

   genter;

   utf8   = gsCreateU1(value);
   result = gprefBinSetA(pref, key, gcGetCountU1(utf8), utf8);
   gmemDestroy(utf8);

   greturn result;
}

/******************************************************************************
func: gprefBinSetHeader
******************************************************************************/
grlAPI Gb gprefBinSetHeader(GprefBin const * const pref)
{
   Gb  result;
   Gn4 byte;

   genter;

   byte   = GPREV_BIN_VERSION;
#if grlSWAP_NEEDED == 1
   gswap4(&byte);
#endif

   result = gprefBinSet(pref, _headerStr, 4, (Gn1 *) &byte);

   greturn result;
}

/******************************************************************************
func: gprefBinSetSpec
******************************************************************************/
grlAPI Gb gprefBinSetSpec(GprefBin const * const pref)
{
   Gb  result;

   genter;

   result = gprefBinSet(pref, _specStr, gcGetCountA(GPREF_BIN_SPEC), (Gn1 *) GPREF_BIN_SPEC);

   greturn result;
}

/******************************************************************************
func: gprefBinStart
******************************************************************************/
Gb gprefBinStart(void)
{
   genter;

   greturnTrueIf(_isStarted);

   _headerStr = gsCreateFromA("GPref Bin\n");
   _specStr   = gsCreateFromA("GPref Bin Spec\n");

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: gprefBinStop
******************************************************************************/
void gprefBinStop(void)
{
   genter;

   greturnVoidIf(!_isStarted);

   gsDestroy(_headerStr);
   gsDestroy(_specStr);

   _isStarted = gbFALSE;

   greturn;
}

/******************************************************************************
LOCAL: Functions
******************************************************************************/
/******************************************************************************
func: _GetByte
******************************************************************************/
static Gi4 _GetByte(GprefBin * const pref)
{
   Gi4  byte;
   Gn1  value;

   genter;

   byte = -1;

   if (pref->file)
   {
      if (gfileGet(pref->file, 1, &value))
      {
         byte = value;
      }
   }
   else
   {
      greturnIf(pref->bufferIndex >= gbufGetCount(pref->buffer), -1);

      byte = gbufGetAt(pref->buffer, (Gindex) pref->bufferIndex);
      pref->bufferIndex++;
   }

   greturn byte;
}

/******************************************************************************
func: _GetBytes
******************************************************************************/
static Gb _GetBytes(GprefBin * const pref, Gcount const count, Gn1 * const buffer)
{
   Gb     result;
   Gindex index;

   genter;

   result = gbTRUE;

   if (pref->file)
   {
      if (gfileGet(pref->file, count, buffer) != count)
      {
         result = gbFALSE;
      }
   }
   else
   {
      forCount(index, count)
      {
         buffer[index] = gbufGetAt(pref->buffer, (Gindex) pref->bufferIndex++);
         breakIf(count <= pref->bufferIndex);
      }

      if (index != count)
      {
         result = gbFALSE;
      }
   }

   greturn result;
}
