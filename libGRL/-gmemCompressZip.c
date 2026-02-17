/******************************************************************************
file:       gmemCompressZip
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
zlib wrapper.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

#include "zlib.h"

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gmemCompressZipCompress

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
grlAPI Gb gmemCompressZipCompress(Gcount const ilen, Gp const * const idat, Gcount * const olen,
   Gp * const odat, GmemCompressLevel const level)
{
   uLongf minSize;
   Gcount result;

   genter;

   greturnFalseIf(
      !idat ||
      !odat ||
      !ilen ||
      !olen);

   result  = ~Z_OK;
   minSize = (uLongf) *olen;
   *olen   = 0;

   // Compress the buffer.
   switch (level)
   {
   case gmemCompressLevelLOW_FASTEST:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_SPEED);
      break;

   case gmemCompressLevelLOW_FASTER:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_SPEED + 1);
      break;

   case gmemCompressLevelLOW_FAST:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_SPEED + 2);
      break;

   case gmemCompressLevelLOW_MAX:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_SPEED + 3);
      break;

   case gmemCompressLevelDEFAULT:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_DEFAULT_COMPRESSION);
      break;

   case gmemCompressLevelHIGH_MIN:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_COMPRESSION - 3);
      break;

   case gmemCompressLevelHIGH_DEFAULT:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_COMPRESSION - 2);
      break;

   case gmemCompressLevelHIGH_OPTIMUM:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_COMPRESSION - 1);
      break;

   case gmemCompressLevelHIGH_MAX:
      result = compress2((Bytef *) odat, &minSize, (Bytef const *) idat, (uLong) ilen, Z_BEST_COMPRESSION);
      break;
   }

   greturnFalseIf(result != Z_OK);

   *olen = minSize;

   greturn gbTRUE;
}

/******************************************************************************
func: gmemCompressZipDecompress

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
grlAPI Gb gmemCompressZipDecompress(const Gcount ilen, const Gp * const idat, Gcount * const olen,
   Gp * const odat)
{
   Gcount result;
   uLongf    size;

   genter;

   greturnFalseIf(
      !idat ||
      !ilen ||
      !olen ||
      !odat);

   size  = (uLongf) *olen;
   *olen = 0;

   // Uncompress the buffer.
   result = uncompress((Bytef *) odat, &size, (Bytef const *) idat, (uLong) ilen);
   greturnFalseIf(result != Z_OK);

   *olen = size;

   greturn gbTRUE;
}

/******************************************************************************
func: gmemCompressZipGetMinBufferSize

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
grlAPI Gcount gmemCompressZipGetMinBufferSize(Gcount const ilen)
{
   Gcount result;

   genter;
   
   result = (Gcount) compressBound((uLong) ilen);

   greturn result;
}
