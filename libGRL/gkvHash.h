/**************************************************************************************************
file:       gkvHash
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
GkvHash and name table to mimic Galaxy vname and vdict functionality
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

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

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   GCONTAINER_VAR;

   GkvList           *binArray;
   GhashSize          binCount;
} GkvHash;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gkvHashCloc(             TYPE, HASHSIZE)    gleakClocType(gkvHashCloc_(               (Char *) TYPE, (HASHSIZE)), GkvHash)
#define gkvHashClocContent(HASH, TYPE, HASHSIZE)                  gkvHashClocContent_(  HASH, (Char *) TYPE, (HASHSIZE))

grlAPI Gb          gkvHashAdd(             GkvHash       * const hash, Gk const * const key, Gv const value);

grlAPI GkvHash    *gkvHashCloc_(                                       Char const * const typeName, GhashSize const hashSize);
grlAPI Gb          gkvHashClocContent_(    GkvHash       * const hash, Char const * const typeName, GhashSize const hashSize);

grlAPI void        gkvHashDloc(            GkvHash       * const hash);
grlAPI void        gkvHashDlocContent(     GkvHash       * const hash);

grlAPI Gb          gkvHashErase(           GkvHash       * const hash, Gk const * const key);

grlAPI Gv          gkvHashFind(            GkvHash const * const hash, Gk const * const key);
grlAPI void        gkvHashFlush(           GkvHash       * const hash);
grlAPI Gb          gkvHashForEach(         GkvHash const * const hash, GrlForEachKeyFunc const func);

grlAPI Gcount      gkvHashGetCount(        GkvHash const * const hash);

grlAPI Gb          gkvHashUpdate(          GkvHash const * const hash, Gk const * const key, Gv const value);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
