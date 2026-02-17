/**************************************************************************************************
file:         Gs
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
The base for a dynamic arrrays.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2011, Robbert de Groot

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

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
#define gsCloc()    gleakClocType(gsCloc_(), Gs)

grlAPI Gb             gsAddAt(         Gs       * const a, Gindex const index, Gchar const value);
grlAPI Gb             gsAddBegin(      Gs       * const a,                     Gchar const value);
grlAPI Gb             gsAddEnd(        Gs       * const a,                     Gchar const value);

grlAPI Gs            *gsCloc_(         void);
grlAPI Gb             gsClocContent(   Gs       * const a);
grlAPI Gb             gsCopy(          Gs       * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
grlAPI Gb             gsCopyFrom(      Gs       * const aDst, Gindex const indexDst, Gs const * const aSrc, Gcount const count, Gindex const indexSrc);

grlAPI void           gsDloc(          Gs       * const a);
grlAPI void           gsDlocContent(   Gs const * const a);
grlAPI void           gsDlocContainer( Gv const * const v);

grlAPI Gb             gsEraseAt(       Gs       * const a, Gcount const count, Gindex const index);
grlAPI Gb             gsEraseBegin(    Gs       * const a, Gcount const count);
grlAPI Gb             gsEraseEnd(      Gs       * const a, Gcount const count);

grlAPI void           gsFlush(         Gs       * const a);
grlAPI Gb             gsForEach(       Gs const * const a, GrlForEachFunc const func);
grlAPI Gb             gsForEachDown(   Gs const * const a, GrlForEachFunc const func);

grlAPI Gchar const   *gsGet(           Gs const * const a);
grlAPI Gchar          gsGetAt(         Gs const * const a, Gindex const index);
grlAPI Gchar          gsGetBegin(      Gs const * const a);
grlAPI Gcount         gsGetCount(      Gs const * const a);
grlAPI Gchar          gsGetEnd(        Gs const * const a);

grlAPI Gb             gsSetCount(      Gs       * const a, Gcount const value);
grlAPI Gb             gsSwap(          Gs       * const a, Gindex const indexA, Gindex const indexB);

grlAPI Gb             gsUpdateAt(      Gs       * const a, Gindex const index, Gchar const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
