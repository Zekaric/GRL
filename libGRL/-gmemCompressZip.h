/******************************************************************************
file:       gmemCompressZip
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
zlib wrapper.
******************************************************************************/

#if !defined(GMEMCOMPRESSZIPH)
#define      GMEMCOMPRESSZIPH

/******************************************************************************
global:
function:
******************************************************************************/
grlAPI Gb      gmemCompressZipCompress(        Gcount const ilen, Gp const * const idat, Gcount * const olen, Gp * const odat, GmemCompressLevel const level);

grlAPI Gb      gmemCompressZipDecompress(      Gcount const ilen, Gp const * const idat, Gcount * const olen, Gp * const odat);

grlAPI Gcount  gmemCompressZipGetMinBufferSize(Gcount const ilen);

#endif
