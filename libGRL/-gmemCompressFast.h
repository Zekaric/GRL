/******************************************************************************
file:       gmemCompressFast
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
zlib wrapper.
******************************************************************************/

#if !defined(GMEMCOMPRESSFASTH)
#define      GMEMCOMPRESSFASTH

/******************************************************************************
global:
function:
******************************************************************************/
grlAPI Gb      gmemCompressFastCompress(        Gcount const ilen, Gp const * const idat, Gcount * const olen, Gp * const odat, Gi4 const level);

grlAPI Gb      gmemCompressFastDecompress(      Gcount const ilen, Gp const * const idat, Gcount * const olen, Gp * const odat);

grlAPI Gcount  gmemCompressFastGetMinBufferSize(Gcount const ilen);

#endif
