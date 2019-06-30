/******************************************************************************
file:       gbit
author:     Robbert de Groot
copyright:  2000-2010, Robbert de Groot

description:
Simple set and get bit functions in a bit array.
******************************************************************************/

#if !defined(GBITH)
#define      GBITH

/******************************************************************************
function:
******************************************************************************/
grlAPI Gn4      gbitArrayGet(     Gn4 const * const data, Gindex const bit, Gcount const count);
grlAPI Gsize    gbitArrayGetSize( Gcount const count);
grlAPI Gb       gbitArraySet(     Gn4       * const data, Gindex const bit, Gcount const count, Gn4 const value);

grlAPI Gn4      gbitGet(          Gn4 const data, Gindex const bit, Gcount const count);
grlAPI Gn4      gbitSet(          Gn4 const data, Gindex const bit, Gcount const count, Gn4 const value);

#endif
