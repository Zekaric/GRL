/******************************************************************************
file:       gmemCompressFast
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
zlib wrapper.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

#include "lz4.h"
#include "lz4hc.h"

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gmemCompressFastCompress

Compress a buffer.

param:
ilen, idat
   int, Gp *
   in, in
   The data

olen, odat
   int *, Gp **
   in/out, in/out
   The compressed data.  odat must be preallocated.

level
   int
   in
   The compression level.  1-9;

return:
int
   gbTRUE if all ok.
******************************************************************************/
grlAPI Gb gmemCompressFastCompress(Gcount const ilen, Gp const * const idat, Gcount * const olen,
   Gp * const odat, GmemCompressLevel const level)
{
   int result;

   genter;

   greturnFalseIf(
      !idat ||
      !odat ||
      !ilen ||
      !olen);

   result = 0;

   // Compress the buffer.
   switch (level)
   {
   case gmemCompressLevelLOW_FASTEST:
      result = LZ4_compress_fast((char *) idat, (char *) odat, ilen, *olen, 16);
      break;

   case gmemCompressLevelLOW_FASTER:
      result = LZ4_compress_fast((char *) idat, (char *) odat, ilen, *olen, 8);
      break;

   case gmemCompressLevelLOW_FAST:
      result = LZ4_compress_fast((char *) idat, (char *) odat, ilen, *olen, 4);
      break;

   case gmemCompressLevelLOW_MAX:
      result = LZ4_compress_fast((char *) idat, (char *) odat, ilen, *olen, 2);
      break;

   case gmemCompressLevelDEFAULT:
      result = LZ4_compress_fast((char *) idat, (char *) odat, ilen, *olen, 1);
      break;

   case gmemCompressLevelHIGH_MIN:
      result = LZ4_compress_HC((char *) idat, (char *) odat, ilen, *olen, LZ4HC_CLEVEL_MIN);
      break;

   case gmemCompressLevelHIGH_DEFAULT:
      result = LZ4_compress_HC((char *) idat, (char *) odat, ilen, *olen, LZ4HC_CLEVEL_DEFAULT);
      break;

   case gmemCompressLevelHIGH_OPTIMUM:
      result = LZ4_compress_HC((char *) idat, (char *) odat, ilen, *olen, LZ4HC_CLEVEL_OPT_MIN);
      break;

   case gmemCompressLevelHIGH_MAX:
      result = LZ4_compress_HC((char *) idat, (char *) odat, ilen, *olen, LZ4HC_CLEVEL_MAX);
      break;
   }

   greturnFalseIf(result == 0);

   *olen = result;

   greturn gbTRUE;
}

/******************************************************************************
func: gmemCompressFastDecompress

Decompress a buffer.

param:
ilen, idat
   int, Gp *
   in, in
   The data

olen, odat
   int *, Gp **
   in/out, in/out
   The decompressed data.  odat must be preallocated.  olen being
   the size of the buffer as it is.

return:
int
   gbTRUE if all ok.
******************************************************************************/
grlAPI Gb gmemCompressFastDecompress(const Gcount ilen, const Gp * const idat, Gcount * const olen,
   Gp * const odat)
{
   int result;

   genter;

   greturnFalseIf(
      !idat ||
      !ilen ||
      !olen ||
      !odat);

   // Uncompress the buffer.
   result = LZ4_decompress_safe((char *) idat, (char *) odat, ilen, *olen);
   greturnFalseIf(result < 0);

   *olen = result;

   greturn gbTRUE;
}

/******************************************************************************
func: gmemCompressFastGetMinBufferSize

Determine the minimum buffer size for a compressed buffer from a
source of a particular size.

param:
ilen
   int
   in
   The uncompressed size.

return:
int
   The compressed size.
******************************************************************************/
grlAPI Gcount gmemCompressFastGetMinBufferSize(Gcount const ilen)
{
   Gcount result;

   genter;
   
   result = (Gcount) LZ4_compressBound((int) ilen);

   greturn result;
}
