/******************************************************************************

file:       gnet
author:     Robbert de Groot
copyright:  2001-2012, Robbert de Groot

description:
Socket coding simplified.

******************************************************************************/
/******************************************************************************
include:  
******************************************************************************/
#include "pre.h"

/******************************************************************************
local: 
******************************************************************************/
/******************************************************************************
constant:  
******************************************************************************/
static Char const * const _codeStr[gnetWebCodeCOUNT] = {
   "100 Continue",
   "101 Switching Protocols",
   "200 Ok",
   "201 Created",
   "202 Accepted",
   "203 Non authoritative information",
   "204 No content",
   "205 Reset content",
   "206 Partial content",
   "300 Multiple choices",
   "301 Moved permanently",
   "302 Found",
   "303 See other",
   "304 Not modified",
   "305 Use proxy",
   "306 Unused",
   "307 Temporary redirect",
   "400 Bad request",
   "401 Unauthorized",
   "402 Payment required",
   "403 Forbidden",
   "404 Not found",
   "405 Method not allowed",
   "406 Not acceptable",
   "407 Proxy authentication required",
   "408 Request timeout",
   "409 Conflict",
   "410 Gone",
   "411 Length required",
   "412 Precondition failed",
   "413 Request entity too large",
   "414 Request uri too long",
   "415 Unsupported media type",
   "416 Requested range not satisfiable",
   "417 Expectation failed",
   "500 Internal server error",
   "501 Not implemented",
   "502 Bad gateway",
   "503 Service unavailable",
   "504 Gateway timeout",
   "505 Http version not supported",
};

static Char const * const _contentStr[gnetWebContentCOUNT] = {
   "",
   "application/octet-stream",
   "application/vnd.ms-excel",
   "application/pdf",
   "application/powerpoint",
   "application/postscript",
   "application/msword",
   "application/xml",
   "application/zip",
   "audio/midi",
   "audio/mpeg",
   "audio/mp4",
   "audio/ogg",
   "audio/wav",
   "audio/webm",
   "image/bmp",
   "image/gif",
   "image/jpeg",
   "image/png",
   "image/svg+xml",
   "image/tiff",
   "image/webp",
   "text/plain",
   "text/css",
   "text/csv",
   "text/html",
   "text/javascript",
   "video/x-msvideo",
   "video/h264",
   "video/mpeg",
   "video/mp4",
   "video/ogg",
   "video/quicktime"
   "video/x-ms-wmv"
};

static Gb const _contentIsBinary[gnetWebContentCOUNT] = {
   gbFALSE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbFALSE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbFALSE,
   gbTRUE,
   gbTRUE,
   gbFALSE,
   gbFALSE,
   gbFALSE,
   gbFALSE,
   gbFALSE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE,
   gbTRUE
};

static Char const * const _contentExt[gnetWebContentCOUNT][2] = {
   {NULL,    NULL},
   {NULL,    NULL},
   {".xlsx", ".xls"},
   {".pdf",  NULL},
   {".pptx", ".ppt"},
   {".ps",   NULL},
   {".docx", ".doc"},
   {".xml",  NULL},
   {".zip",  NULL},
   {".midi", ".mid"},
   {".mpg",  ".mp3"},
   {".mpg4", NULL},
   {".ogg",  NULL},
   {".wav",  NULL},
   {".webm", NULL},
   {".bmp",  NULL},
   {".gif",  NULL},
   {".jpeg", ".jpg"},
   {".png",  NULL},
   {".svg",  NULL},
   {".tiff", ".tif"},
   {".webp", NULL},
   {".txt",  NULL},
   {".css",  NULL},
   {".csv",  NULL},
   {".html", ".htm"},
   {".js",   NULL},
   {".avi",  NULL},
   {NULL,    NULL},
   {".mpeg", ".mpg"},
   {".mpg4", NULL},
   {".ogg",  NULL},
   {".mov",  ".qt"},
   {".wmv",  NULL}
};


/******************************************************************************
type: 
******************************************************************************/

/******************************************************************************
variable:  
******************************************************************************/
static Gb _isStarted = gbFALSE;

/******************************************************************************
prototype: 
******************************************************************************/
static Gn4 __stdcall _GoThread(        Gp *netClientPtr);

static Gb            _ParseStartLine(  GnetWebData * const data);

/******************************************************************************
global: 
function: 
******************************************************************************/
/******************************************************************************
func: gnetWebCreate
******************************************************************************/
grlAPI GnetWeb *gnetWebCreate(Gs const * const port, Gcount const listenCount, GnetWebFunc func)
{
   GnetWeb *web;
   Gb       result;
   Gs      *defaultPort,
           *usePort;

   genter;

   result = gbFALSE;
   web    = NULL;

   web = gmemCreateType(GnetWeb);
   returnNullIf(!web);

   usePort = (Gs *) port;
   if (!port)
   {
      defaultPort = gsCreateFromA("80");
      usePort     = defaultPort;
   }

   web->net = gnetCreateServer(usePort, listenCount);
   stopIf(!web->net);

   web->func = func;

   result = gbTRUE;

STOP:
   if (!result)
   {
      gmemDestroy(web);
      greturn NULL;
   }

   greturn web;
}

/******************************************************************************
func: gnetWebCreateHeaderContent
******************************************************************************/
grlAPI Gs *gnetWebCreateHeaderContent(GnetWebCode const code, GnetWebContent const content, Gcount const size)
{
   Gs *headers;

   genter;

   headers = gsCreate();
   gsAppendA(headers, "HTTP/1.0 ");
   gsAppendA(headers, _codeStr[code]);
   gsAppendA(headers, "\r\n");

   gsAppendA(headers, "Content-type: ");
   gsAppendA(headers, _contentStr[content]);
   gsAppendA(headers, "\r\n");

   gsAppendA(headers, "Content-length: ");
   gsAppendN(headers, size);
   gsAppendA(headers, "\r\n");
   gsAppendA(headers, "\r\n");

   greturn headers;
}

/******************************************************************************
func: gnetWebDestroy
******************************************************************************/
grlAPI void gnetWebDestroy(GnetWeb * const web)
{
   genter;

   greturnVoidIf(!web);

   gnetDestroy(web->net);
   gsDestroy(  web->page404);
   gmemDestroy(web);

   greturn;
}

/******************************************************************************
func: gnetWebProcess

This function needs to be placed in an loop.
******************************************************************************/
grlAPI void gnetWebProcess(GnetWeb * const web)
{
   Gnet        *client;
   Gthread     *thread;
   GnetWebData *webData;
   Gb           result;

   genter;

   result = gbFALSE;

   //greturnVoidIf(!gnetIsDataWaiting(web->net));

   client = gnetServerAccept(web->net);
   greturnVoidIf(!client);

   webData = gmemCreateType(GnetWebData);
   stopIf(!webData);

   webData->client = client;
   webData->web    = web;

   thread = gthreadCreate(_GoThread, webData);

   result = gbTRUE;

STOP:
   if (!result)
   {
      gnetDestroy(client);
   }

   greturn;
}

/******************************************************************************
func: gnetWebSEscapeUrl

Escape URL strings.  I.E. replacing restricted letters with %... sequences.
******************************************************************************/
grlAPI Gs *gnetWebSEscapeUrl(Gs * const s)
{
   Gindex loopIndex;
   Char   letter[]   = "~ %/.#?;:$,+@&={}|\\^[]'<>\"",
          pattern[4],
          replace[2],
          hex[]      = "0123456789abcdef",
          Hex[]      = "0123456789ABCDEF";

   genter;

   replace[1] = 0;
   pattern[0] = '%';
   pattern[3] = 0;

   loop(loopIndex)
   {
      replace[0] = letter[loopIndex];

      breakIf(replace[0] == '\0');

      // Lowercase
      pattern[1] = hex[((letter[loopIndex] >> 4) & 0xF)];
      pattern[2] = hex[((letter[loopIndex]     ) & 0xF)];

      gsFindAndReplaceA(s, replace, pattern, NULL);

      // Uppercase
      pattern[1] = Hex[((letter[loopIndex] >> 4) & 0xF)];
      pattern[2] = Hex[((letter[loopIndex]     ) & 0xF)];

      gsFindAndReplaceA(s, replace, pattern, NULL);
   }

   greturn s;
}

/******************************************************************************
func: gnetWebSUnescapeUrl

Unescape URL strings.  I.E. replacing %... with their respective characters.
******************************************************************************/
grlAPI Gs *gnetWebSUnescapeUrl(Gs * const s)
{
   Gindex loopIndex;
   Char   letter[]   = "~ %/.#?;:$,+@&={}|\\^[]'<>\"",
          pattern[4],
          replace[2],
          hex[]      = "0123456789abcdef",
          Hex[]      = "0123456789ABCDEF";

   genter;

   replace[1] = 0;
   pattern[0] = '%';
   pattern[3] = 0;

   loop(loopIndex)
   {
      replace[0] = letter[loopIndex];

      breakIf(replace[0] == '\0');

      // Lowercase
      pattern[1] = hex[((letter[loopIndex] >> 4) & 0xF)];
      pattern[2] = hex[((letter[loopIndex]     ) & 0xF)];

      gsFindAndReplaceA(s, pattern, replace, NULL);

      // Uppercase
      pattern[1] = Hex[((letter[loopIndex] >> 4) & 0xF)];
      pattern[2] = Hex[((letter[loopIndex]     ) & 0xF)];

      gsFindAndReplaceA(s, pattern, replace, NULL);
   }

   greturn s;
}

/******************************************************************************
func: gnetWebSetPage404A
******************************************************************************/
grlAPI void gnetWebSetPage404A(GnetWeb * const web, Char const * const value)
{
   genter;

   greturnVoidIf(!web || !value);

   gsDestroy(  web->page404);
   gmemDestroy(web->page404Char);
   gsDestroy(  web->page404Header);

   web->page404          = gsCreateFromA(value);
   web->page404Char      = gsCreateU1(  web->page404);
   web->page404CharCount = gcGetCountU1(web->page404Char);
   web->page404Header    = gnetWebCreateHeaderContent(
      gnetWebCode404,
      gnetWebContentTEXT_HTML,
      web->page404CharCount);

   greturn;
}

/******************************************************************************
func: gnetWebSetResult
******************************************************************************/
grlAPI Gb gnetWebSetResult(GnetWebData const * const data, Gs const * const headers,
   Gcount const size, Gn1 const * const content)
{
   Gc1   *charHead;
   Gn1   *resultData;
   Gcount headSize,
          resultSize;
   Gb     result;

   genter;

   result = gbFALSE;

   // Create the head.
   charHead = gsCreateU1(headers);
   headSize = gcGetCountU1(charHead);

   // Prep the result buffer
   resultSize = headSize + size;
   resultData = gmemCreateTypeArray(Gn1, resultSize);
   stopIf(!resultData);

   // Copy over the head.
   gmemCopyOverTypeArray(charHead, Gn1, headSize, resultData);
   gmemDestroy(charHead);

   // Copy over the data.
   gmemCopyOverTypeArrayAt(content, Gn1, size, 0, resultData, headSize);

   // Send the data.
   result = gnetSetBuffer(data->client, resultSize, resultData);

STOP:
   // Clean up.
   gmemDestroy(resultData);

   greturn result;
}

/******************************************************************************
func: gnetWebSetResult404

Send a 404 responce.
******************************************************************************/
grlAPI Gb gnetWebSetResult404(GnetWebData const * const data)
{
   Gb result;

   genter;

   result = gnetWebSetResult(
      data,
      data->web->page404Header,
      data->web->page404CharCount,
      data->web->page404Char);

   greturn result;
}

/******************************************************************************
func: gnetWebSetResultBinary
******************************************************************************/
grlAPI Gb gnetWebSetResultBinary(GnetWebData const * const data, GnetWebCode const code,
   GnetWebContent const content, Gcount const dataContentSize, Gn1 const * const dataContent)
{
   Gs *headers;
   Gb  result;

   genter;

   headers = gnetWebCreateHeaderContent(code, content, dataContentSize);
   greturnFalseIf(!headers);

   result  = gnetWebSetResult(data, headers, dataContentSize, dataContent);

   gsDestroy(headers);

   greturn result;
}

/******************************************************************************
func: gnetWebSetResultA
******************************************************************************/
grlAPI void gnetWebSetResultA(GnetWebData const * const data, GnetWebCode const code, 
   GnetWebContent const content, Gcount const dataContentSize,  Char const * const dataContent)
{
   Gs *headers;

   genter;

   headers = gnetWebCreateHeaderContent(code, content, dataContentSize);

   gnetWebSetResult(data, headers, dataContentSize, (Gn1 *) dataContent);

   gsDestroy(headers);

   greturn;
}

/******************************************************************************
func: gnetWebSetResultFile

No code result as the code result will be determined if the file is found
and readable.
******************************************************************************/
grlAPI Gb gnetWebSetResultFile(GnetWebData const * const data, GnetWebContent const content,
   Gs const * const filePath)
{
   Gindex  loopIndex;
   Gcount  count;
   Gn1    *buffer;
   Gb      result;
   Gpath  *finalPath,
          *path;

   genter;

   // Get the working directory.
   finalPath = gdirGetWorking();

   // Get the asked for path.
   path = gsCreateFrom(filePath);
   gpathSetFromSystem(path);

   // Append to the working directory.
   forCount (loopIndex, gpathGetCount(path))
   {
      gpathPush(finalPath, gpathGetAt(path, loopIndex));
   }
   
   // Could not load the file.  File probably doesn't exist.
   if (!gfileOpenLoadContent(finalPath, &count, &buffer))
   {
      result = gnetWebSetResult404(data);
   }

   // Send the file with ok result.
   result = gnetWebSetResultBinary(data, gnetWebCode200_OK, content, count, buffer);

   // Clean up
   gmemDestroy(buffer);

   greturn result;
}

/******************************************************************************
func: gnetWebSetResultS
******************************************************************************/
grlAPI void gnetWebSetResultS(GnetWebData const * const data, GnetWebCode const code, 
   GnetWebContent const content, Gs const * const dataContent)
{
   Gs    *headers;
   Gc1   *dataContentS;
   Gcount dataContentSize;

   genter;

   dataContentS    = gsCreateU1(dataContent);
   dataContentSize = gcGetCountU1(dataContentS);

   headers = gnetWebCreateHeaderContent(code, content, dataContentSize);

   gnetWebSetResult(data, headers, dataContentSize, dataContentS);

   gmemDestroy(dataContentS);
   gsDestroy(headers);

   greturn;
}


/******************************************************************************
func: gnetWebStart

Start the network routines.
******************************************************************************/
grlAPI Gb gnetWebStart(void)
{
   genter;

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: gnetWebStop
******************************************************************************/
grlAPI void gnetWebStop(void)
{
   genter;

   _isStarted = gbFALSE;

   greturn;
}

/******************************************************************************
func: gnetWebDataGetClient
******************************************************************************/
grlAPI Gnet * gnetWebDataGetClient(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->client;
}

/******************************************************************************
func: gnetWebDataGetCmdMethod
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdMethod(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdMethod;
}

/******************************************************************************
func: gnetWebDataGetCmdUrl
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrl(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrl;
}

/******************************************************************************
func: gnetWebDataGetCmdUrlFile
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrlFile(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrlFile;
}

/******************************************************************************
func: gnetWebDataGetCmdUrlFileExt
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrlFileExt(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrlFileExt;
}

/******************************************************************************
func: gnetWebDataGetCmdUrlHost
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrlHost(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrlHost;
}

/******************************************************************************
func: gnetWebDataGetCmdUrlPath
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrlPath(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrlPath;
}

/******************************************************************************
func: gnetWebDataGetCmdUrlPath_NoFile
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdUrlPath_NoFile(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdUrlPath_NoFile;
}

/******************************************************************************
func: gnetWebDataGetCmdVersion
******************************************************************************/
grlAPI Gs * gnetWebDataGetCmdVersion(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->cmdVersion;
}

/******************************************************************************
func: gnetWebDataGetContent
******************************************************************************/
grlAPI GnetWebContent gnetWebDataGetContent(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      gnetWebContentNONE);

   greturn gnetWebData->content;
}

/******************************************************************************
func: gnetWebDataGetData
******************************************************************************/
grlAPI void * gnetWebDataGetData(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->data;
}

/******************************************************************************
func: gnetWebDataGetHeaderLine
******************************************************************************/
grlAPI GsArray * gnetWebDataGetHeaderLine(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->headerLine;
}

/******************************************************************************
func: gnetWebDataGetStartLine
******************************************************************************/
grlAPI Gs * gnetWebDataGetStartLine(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->startLine;
}

/******************************************************************************
func: gnetWebDataGetWeb
******************************************************************************/
grlAPI GnetWeb * gnetWebDataGetWeb(GnetWebData const * const gnetWebData)
{
   genter;

   greturnIf(
         !_isStarted ||
         !gnetWebData,
      NULL);

   greturn gnetWebData->web;
}

/******************************************************************************
local: 
function: 
******************************************************************************/
/******************************************************************************
func: _GoThread
******************************************************************************/
static Gn4 __stdcall _GoThread(Gp *webDataPtr)
{
   Gindex       loopIndex;
   GnetWebData *data;
   Gs          *headerLine;

   genter;

   data = (GnetWebData *) webDataPtr;

   // Parse the request
   data->startLine  = gnetGetSToLF(data->client);

   data->headerLine = gsArrayCreate(NULL, gbTRUE);
   loop(loopIndex)
   {
      headerLine = gnetGetSToLF(data->client);
      breakIf(
         (gsGetAt(headerLine, 0) == '\r' &&
          gsGetAt(headerLine, 1) == '\n' &&
          gsGetCount(headerLine) == 2)      ||
         (gsGetAt(headerLine, 0) == '\n' &&
          gsGetCount(headerLine) == 1));

      gsArrayAddEnd(data->headerLine, headerLine);
   }
   gsDestroy(headerLine);

   // Parse the start line.
   _ParseStartLine(data);

   // Call the callback function
   data->web->func(data);

   // Clean up
   gnetDestroy(data->client);

   gsArrayForEach(data->headerLine, (GrlForEachFunc) gsDestroy);
   gsArrayDestroy(data->headerLine);
   
   gsDestroy(data->startLine);
   gsDestroy(data->cmdMethod);
   gsDestroy(data->cmdUrl);
   gsDestroy(data->cmdUrlHost);
   gsDestroy(data->cmdUrlPath);
   gsDestroy(data->cmdUrlPath_NoFile);
   gsDestroy(data->cmdUrlFile);
   gsDestroy(data->cmdUrlScheme);
   gsDestroy(data->cmdVersion);

   // Clean up the data structure that was created for this thread.
   gmemDestroy(webDataPtr);

   // Stop the thread
   gthreadCurrentExit(gbTRUE);

   greturn 0;
}

/******************************************************************************
func: _ParseStartLine
******************************************************************************/
static Gb _ParseStartLine(GnetWebData * const data)
{
   Gindex    loopIndex;
   Gi4       index;
   GsArray  *split;
   Gs       *temp;
   Gb        isHttpProvided,
             isKeyValueProvided;

   genter;

   isHttpProvided     = gbTRUE;
   isKeyValueProvided = gbFALSE;

   // Parse the start line parts.
   split = gsCreateSplit(data->startLine, ' ');
   data->cmdMethod  = gsArrayGetAt(split, 0);
   data->cmdUrl     = gsArrayGetAt(split, 1);
   data->cmdVersion = gsArrayGetAt(split, 2);
   gsArrayDestroy(split);

   gsTrimA(data->cmdMethod,   WHITESPACE_A);
   gsTrimA(data->cmdUrl,      WHITESPACE_A);
   gsTrimA(data->cmdVersion,  WHITESPACE_A);

   // Parse the URL parts.
   temp = gsCreateFrom(data->cmdUrl);

   // Get the scheme
   if      (gsIsEqualBaseA(temp, "https://"))
   {
      data->cmdUrlScheme = gsCreateFromA("https://");
      gsEraseAt(temp, 8, 0);
   }
   else if (gsIsEqualBaseA(temp, "http://"))
   {
      data->cmdUrlScheme = gsCreateFromA("http://");
      gsEraseAt(temp, 7, 0);
   }
   else
   {
      // Scheme is missing.  Default to http://
      data->cmdUrlScheme = gsCreateFromA("http://");
      // Nothing to erase, missing from url.
      isHttpProvided = gbFALSE;
   }
   
   // Get the host
   if (isHttpProvided)
   {
      index = gsFindFirstOfA(temp, 0, "/");
      data->cmdUrlHost = gsCreateFromSub(temp, 0, index + 1);
      gsEraseAt(temp, index, 0);
   }

   // Get the path
   index = gsFindFirstOfA(temp, 0, "?");
   if (index == gsFIND_FAIL)
   {
      // there are no key value pairs on the URL.
      data->cmdUrlPath = temp;
      temp             = NULL;
   }
   else
   {
      // there are key values after the path.
      isKeyValueProvided = gbTRUE;

      data->cmdUrlPath = gsCreateFromSub(temp, 0, index);
      gsEraseAt(temp, index, 0);
   }

   // Get the file
   index = gsFindLastOfA(data->cmdUrlPath, 0, "/");
   if (index == gsFIND_FAIL)
   {
      // This case should never happen.
      data->cmdUrlFile        = gsCreateFrom(data->cmdUrlPath);
      data->cmdUrlPath_NoFile = gsCreate();
   }
   else
   {
      data->cmdUrlFile        = gsCreateFromSub(data->cmdUrlPath, index + 1, GindexMAX);
      data->cmdUrlPath_NoFile = gsCreateFromSub(data->cmdUrlPath, 0,         index + 1);
   }

   // Get the extension for the file.
   index = gsFindLastOfA(data->cmdUrlFile, 0, ".");

   // Find the content type if possible.
   data->content = gnetWebContentNONE;
   if (index != gsFIND_FAIL)
   {
      data->cmdUrlFileExt = gsCreateFromSub(data->cmdUrlFile, index, GindexMAX);

      forCount (loopIndex, gnetWebContentCOUNT)
      {
         continueIf(!_contentExt[loopIndex][0]);

         if (gsIsEqualBaseA(data->cmdUrlFileExt, _contentExt[loopIndex][0]))
         {
            data->content = loopIndex;
            break;
         }

         continueIf(!_contentExt[loopIndex][1]);

         if (gsIsEqualBaseA(data->cmdUrlFileExt, _contentExt[loopIndex][1]))
         {
            data->content = loopIndex;
            break;
         }
      }
   }
   
   // Get the key values
   if (isKeyValueProvided)
   {
      // Todo.
   }

   gsDestroy(temp);

   greturn gbTRUE;
}
