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

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
typedef struct
{
   Gindex          index;
   Gv              repo;
   GrlGetBuffer    getBuffer;
   GrlSetBuffer    setBuffer;
} Gio;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gioCloc(     REPO, GETBUFFUNC, SETBUFFUNC)    gleakClocType(gioCloc_(     REPO, GETBUFFFUNC, SETBUFFUNC), Gio)
#define gioClocGbuf( REPO, GETBUFFUNC, SETBUFFUNC)    gleakClocType(gioClocGbuf_( REPO, GETBUFFFUNC, SETBUFFUNC), Gio)
#define gioClocGfile(REPO, GETBUFFUNC, SETBUFFUNC)    gleakClocType(gioClocGfile_(REPO, GETBUFFFUNC, SETBUFFUNC), Gio)

grlAPI Gio  *gioCloc_(                            Gv repo, GrlGetBuffer getBuffer, GrlSetBuffer setBuffer);
grlAPI Gio  *gioClocGbuf_(                        Gbuf  * const repo);
grlAPI Gio  *gioClocGfile_(                       Gfile * const repo);
grlAPI Gb    gioClocContent(     Gio * const gio, Gv repo, GrlGetBuffer getBuffer, GrlSetBuffer setBuffer);
grlAPI Gb    gioClocContentGbuf( Gio * const gio, Gbuf  * const repo);
grlAPI Gb    gioClocContentGfile(Gio * const gio, Gfile * const repo);

grlAPI void  gioDloc(            Gio * const gio);
grlAPI void  gioDlocContent(     Gio * const gio);

grlAPI Gb    gioGetBufferGbuf(   Gio * const gio, Gcount const byteCount, Gn1       * const data);
grlAPI Gb    gioGetBufferGfile(  Gio * const gio, Gcount const byteCount, Gn1       * const data);
grlAPI Gb    gioSetBufferGbuf(   Gio * const gio, Gcount const byteCount, Gn1 const * const data);
grlAPI Gb    gioSetBufferGfile(  Gio * const gio, Gcount const byteCount, Gn1 const * const data);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
