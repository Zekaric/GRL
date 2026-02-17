/**************************************************************************************************
file:       gio
author:     Robbert de Groot
copyright:  2026, Robbert de Groot

description:
Handle reading and writing from and input or to an output.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2026, Robbert de Groot

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
#include "pch.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/

/**************************************************************************************************
variable:
**************************************************************************************************/
static Gb _isStarted = gbFALSE;

/**************************************************************************************************
prototype:
**************************************************************************************************/

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioCloc
**************************************************************************************************/
grlAPI Gio *gioCloc_(Gv repo, GrlGetBuffer getBuffer, GrlSetBuffer setBuffer)
{
   Gio *gio;

   genter;

   greturnNullIf(!_isStarted);

   gio = gmemClocType(Gio);
   greturnNullIf(!gio);

   if (!gioClocContent(gio, repo, getBuffer, setBuffer))
   {
      gmemDloc(gio);
      greturn NULL;
   }

   greturn gio;
}

/**************************************************************************************************
func: gioClocGbuf
**************************************************************************************************/
grlAPI Gio *gioClocGbuf_(Gbuf * const buf)
{
   Gio *gio;

   genter;

   gio = gmemClocType(Gio);
   greturnNullIf(!gio);

   if (!gioClocContent(gio, gvFromP(buf), gioGetBufferGbuf, gioSetBufferGbuf))
   {
      gioDloc(gio);
      greturn NULL;
   }

   greturn gio;
}

/**************************************************************************************************
func: gioClocGfile
**************************************************************************************************/
grlAPI Gio *gioClocGfile_(Gfile * const file)
{
   Gio *gio;

   genter;

   gio = gmemClocType(Gio);
   greturnNullIf(!gio);

   if (!gioClocContent(gio, gvFromP(file), gioGetBufferGfile, gioSetBufferGfile))
   {
      gioDloc(gio);
      greturn NULL;
   }

   greturn gio;
}

/**************************************************************************************************
func: gioClocContent
**************************************************************************************************/
grlAPI Gb gioClocContent(Gio * const gio, Gv repo, GrlGetBuffer getBuffer, GrlSetBuffer setBuffer)
{
   genter;

   greturnFalseIf(!gio);

   gmemClearType(gio, Gio);

   gio->repo      = repo;
   gio->getBuffer = getBuffer;
   gio->setBuffer = setBuffer;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioClocContentGbuf
**************************************************************************************************/
grlAPI Gb gioClocContentGbuf(Gio * const gio, Gbuf  * const repo)
{
   genter;

   greturn gioClocContent(gio, gvFromP(repo), gioGetBufferGbuf, gioSetBufferGbuf);
}

/**************************************************************************************************
func: gioClocContentGfile
**************************************************************************************************/
grlAPI Gb gioClocContentGfile(Gio * const gio, Gfile * const repo)
{
   genter;

   greturn gioClocContent(gio, gvFromP(repo), gioGetBufferGfile, gioSetBufferGfile);
}

/**************************************************************************************************
func: gioDloc
**************************************************************************************************/
grlAPI void gioDloc(Gio * const gio)
{
   genter;

   greturnIf(!gio);

   gioDlocContent(gio);

   gmemDloc(gio);

   greturn;
}

/**************************************************************************************************
func: gioDlocContent
**************************************************************************************************/
grlAPI void gioDlocContent(Gio * const gio)
{
   genter;

   greturnIf(!gio);

   gmemClearType(gio, Gio);

   greturn;
}

/**************************************************************************************************
func: gioGetBufferGbuf
**************************************************************************************************/
grlAPI Gb gioGetBufferGbuf(Gio * const gio, Gcount const byteCount, Gn1 * const data)
{
   Gindex index;
   Gv1    v;

   genter;

   forCount(index, byteCount)
   {
      greturnFalseIf(!gbufGetAtV1((Gbuf *) gvGetP(gio->repo), gio->index++, &v));

      data[index] = gv1GetN(v);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioGetBufferGfile
**************************************************************************************************/
grlAPI Gb gioGetBufferGfile(Gio * const gio, Gcount const byteCount, Gn1 * const data)
{
   genter;

   greturn (gfileGet((Gfile *) gvGetP(gio->repo), byteCount, data) == byteCount);
}

/**************************************************************************************************
func: gioSetBufferGbuf
**************************************************************************************************/
grlAPI Gb gioSetBufferGbuf(Gio * const gio, Gcount const byteCount, Gn1 const * const data)
{
   Gindex index;
   Gv1    v;

   genter;

   forCount(index, byteCount)
   {
      greturnFalseIf(!gbufAppendV1((Gbuf *) gvGetP(gio->repo), gv1SetN(v, data[index])));
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioSetBufferGfile
**************************************************************************************************/
grlAPI Gb gioSetBufferGfile(Gio * const gio, Gcount const byteCount, Gn1 const * const data)
{
   genter;

   greturn gfileSet((Gfile *) gvGetP(gio->repo), byteCount, data, NULL);
}
