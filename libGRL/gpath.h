/**************************************************************************************************
file:         Gpath
author:       Robbert de Groot
copyright:    2002, Robbert de Groot

description:
Path functions to handle paths in an independant way.

Gpaths can be...
UNC:           //servername/zekaric/program
Windows Path:  C:/zekaric/program.exe
UNIX:          /usr/local/bin/program
Relative:      ./project/data.file
               ./../../what/the/hell.

I make no attempt to figure out if the tail is a file or not.  Folders can have
periods in their name.

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

/**************************************************************************************************
include:
**************************************************************************************************/

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
constant:
**************************************************************************************************/
/* From SDL_filesystem
|             | Windows | macOS/iOS | tvOS | Unix (XDG) | Haiku | Emscripten |
| ----------- | ------- | --------- | ---- | ---------- | ----- | ---------- |
| HOME        | X       | X         |      | X          | X     | X          |
| DESKTOP     | X       | X         |      | X          | X     |            |
| DOCUMENTS   | X       | X         |      | X          |       |            |
| DOWNLOADS   | Vista+  | X         |      | X          |       |            |
| MUSIC       | X       | X         |      | X          |       |            |
| PICTURES    | X       | X         |      | X          |       |            |
| PUBLICSHARE |         | X         |      | X          |       |            |
| SAVEDGAMES  | Vista+  |           |      |            |       |            |
| SCREENSHOTS | Vista+  |           |      |            |       |            |
| TEMPLATES   | X       | X         |      | X          |       |            |
| VIDEOS      | X       | X*        |      | X          |       |            |
*/
typedef enum
{
   gpathUserFolderHOME,
   gpathUserFolderDESKTOP,
   gpathUserFolderDOCUMENT,
   gpathUserFolderDOWNLOAD,
   gpathUserFolderMUSIC,
   gpathUserFolderPICTURES,
   gpathUserFolderPUBLIC_SHARE,
   gpathUserFolderSAVED_GAME,
   gpathUserFolderSCREEN_SHOT,
   gpathUserFolderTEMPLATE,
   gpathUserFolderVIDEO,

   gpathUserFolderCOUNT
} GpathUserFolder;

#define gpathDIR_SEPARATOR_UNIX              '/'
#define gpathDIR_SEPARATOR_WINDOWS           '\\'
#define gpathDIR_SEPARATOR_MACOSX            ':'
#define gpathFILE_SEPARATOR                  '.'
#define gpathCURRENT_DIR                     '.'
#define gpathPARENT_DIR                      ".."

#if   defined(grlWINDOWS)

#define gpathDIR_SEPARATOR_SYSTEM            gpathDIR_SEPARATOR_WINDOWS
#define gpathDIR_SEPARATOR_SYSTEM_ALT        gpathDIR_SEPARATOR_UNIX
#define gpathMOUNT_SUFFIX_SYSTEM             ':'
#define gpathFOLDER_SEPARATOR_SYSTEM_STRING  "\\"
#define gpathPARENT_DIR_SYSTEM               ".."

#elif defined(grlMACOSX)

#define gpathFOLDER_SEPARATOR_SYSTEM         ':'
#define gpathMOUNT_SUFFIX_SYSTEM             1
#define gpathPARENT_DIR_SYSTEM               "::"

#else // grlUNIX

#define gpathFOLDER_SEPARATOR_SYSTEM         gpathDIR_SEPARATOR_UNIX
#define gpathFOLDER_SEPARATOR_SYSTEM_ALT     gpathDIR_SEPARATOR_UNIX
#define gpathMOUNT_SUFFIX_SYSTEM             1
#define gpathPARENT_DIR_SYSTEM               ".."

#endif

typedef enum
{
   gpathTypeNONE,
   gpathTypeMOUNT,
   gpathTypeFOLDER,
   gpathTypeFILE,
   gpathTypeEXTENSION
} GpathType;

typedef struct
{
   Gb         isAbsolute;
   GvArray   *partList;
   Gs        *mount;
   Gs        *server;
} Gpath;

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gpathCloc(               )                            gleakClocType(gpathCloc_(               ),                  Gpath)
#define gpathClocAppPrefPath(    ORGNAME, APPNAME)            gleakClocType(gpathClocAppPrefPath_(    ORGNAME, APPNAME),  Gpath)
#define gpathClocAppResPath(     )                            gleakClocType(gpathClocAppResPath_(     ),                  Gpath)
#define gpathClocCurrent(        )                            gleakClocType(gpathClocCurrent_(        ),                  Gpath)
#define gpathClocFrom(           PATH)                        gleakClocType(gpathClocFrom_(           PATH),              Gpath)
#define gpathClocFromSystemChar1(SYSPATH)                     gleakClocType(gpathClocFromSystemChar1_(SYSPATH),           Gpath)
#define gpathClocSystemChar1(    PATH)             (Gchar1 *) gleakCloc(    gpathClocSystemChar1_(    PATH),      gsizeof(Gchar1) * 1000)
#define gpathClocUserFolder(     FOLDER)                      gleakClocType(gpathClocUserFolder_(     FOLDER),            Gpath)

grlAPI Gb          gpathAppend(              Gpath       * const path, Gpath const * const add);

grlAPI Gpath      *gpathCloc_(               void);
grlAPI Gb          gpathClocContent(         Gpath       * const path);
grlAPI Gpath      *gpathClocAppPrefPath_(    Gs const * const orgName, Gs const * const appName);
grlAPI Gpath      *gpathClocAppResPath_(     void);
grlAPI Gpath      *gpathClocCurrent_(        void);
grlAPI Gpath      *gpathClocFrom_(           Gpath const * const path);
grlAPI Gpath      *gpathClocFromSystemChar1_(Gchar1 const * const spath);
grlAPI Gchar1     *gpathClocSystemChar1_(    Gpath const * const path);
grlAPI Gpath      *gpathClocUserFolder_(     GpathUserFolder folder);

grlAPI void        gpathDloc(                Gpath       * const path);
grlAPI void        gpathDlocContent(         Gpath       * const path);

grlAPI Gs const   *gpathGetAt(               Gpath const * const path, Gindex const index);
grlAPI Gcount      gpathGetCount(            Gpath const * const path);
grlAPI Gs const   *gpathGetEnd(              Gpath const * const path);
grlAPI Gs const   *gpathGetMount(            Gpath const * const path);
grlAPI Gs const   *gpathGetServer(           Gpath const * const path);

grlAPI Gb          gpathIsAbsolute(          Gpath const * const path);

grlAPI Gb          gpathPop(                 Gpath       * const path);
grlAPI Gb          gpathPopExtension(        Gpath       * const path);
grlAPI Gb          gpathPush(                Gpath       * const path, Gs const * const value);
grlAPI Gb          gpathPushExtension(       Gpath       * const path, Gs const * const extension);

grlAPI Gb          gpathReduce(              Gpath       * const path);

grlAPI Gb          gpathSetMount(            Gpath       * const path, Gs const * const value);
grlAPI Gb          gpathSetServer(           Gpath       * const path, Gs const * const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
