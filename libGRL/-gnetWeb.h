/******************************************************************************

file:       gnetWeb
author:     Robbert de Groot
copyright:  2001-2012, Robbert de Groot
 
description:
Web server

******************************************************************************/
#if !defined(GNETWEBH)
#define      GNETWEBH

/******************************************************************************
include: 
******************************************************************************/

/******************************************************************************
constant:  
******************************************************************************/
typedef enum 
{
   gnetWebCode100,
   gnetWebCode100_CONTINUE                        = gnetWebCode100,
   gnetWebCode101,
   gnetWebCode101_SWITCHING_PROTOCOLS             = gnetWebCode101,
   gnetWebCode200,
   gnetWebCode200_OK                              = gnetWebCode200,
   gnetWebCode201,
   gnetWebCode201_CREATED                         = gnetWebCode201,
   gnetWebCode202,
   gnetWebCode202_ACCEPTED                        = gnetWebCode202,
   gnetWebCode203,
   gnetWebCode203_NON_AUTHORITATIVE_INFORMATION   = gnetWebCode203,
   gnetWebCode204,
   gnetWebCode204_NO_CONTENT                      = gnetWebCode204,
   gnetWebCode205,
   gnetWebCode205_RESET_CONTENT                   = gnetWebCode205,
   gnetWebCode206,
   gnetWebCode206_PARTIAL_CONTENT                 = gnetWebCode206,
   gnetWebCode300,
   gnetWebCode300_MULTIPLE_CHOICES                = gnetWebCode300,
   gnetWebCode301,
   gnetWebCode301_MOVED_PERMANENTLY               = gnetWebCode301,
   gnetWebCode302,
   gnetWebCode302_FOUND                           = gnetWebCode302,
   gnetWebCode303,
   gnetWebCode303_SEE_OTHER                       = gnetWebCode303,
   gnetWebCode304,
   gnetWebCode304_NOT_MODIFIED                    = gnetWebCode304,
   gnetWebCode305,
   gnetWebCode305_USE_PROXY                       = gnetWebCode305,
   gnetWebCode306,
   gnetWebCode306_UNUSED                          = gnetWebCode306,
   gnetWebCode307,
   gnetWebCode307_TEMPORARY_REDIRECT              = gnetWebCode307,
   gnetWebCode400,
   gnetWebCode400_BAD_REQUEST                     = gnetWebCode400,
   gnetWebCode401,
   gnetWebCode401_UNAUTHORIZED                    = gnetWebCode401,
   gnetWebCode402,
   gnetWebCode402_PAYMENT_REQUIRED                = gnetWebCode402,
   gnetWebCode403,
   gnetWebCode403_FORBIDDEN                       = gnetWebCode403,
   gnetWebCode404,
   gnetWebCode404_NOT_FOUND                       = gnetWebCode404,
   gnetWebCode405,
   gnetWebCode405_METHOD_NOT_ALLOWED              = gnetWebCode405,
   gnetWebCode406,
   gnetWebCode406_NOT_ACCEPTABLE                  = gnetWebCode406,
   gnetWebCode407,
   gnetWebCode407_PROXY_AUTHENTICATION_REQUIRED   = gnetWebCode407,
   gnetWebCode408,
   gnetWebCode408_REQUEST_TIMEOUT                 = gnetWebCode408,
   gnetWebCode409,
   gnetWebCode409_CONFLICT                        = gnetWebCode409,
   gnetWebCode410,
   gnetWebCode410_GONE                            = gnetWebCode410,
   gnetWebCode411,
   gnetWebCode411_LENGTH_REQUIRED                 = gnetWebCode411,
   gnetWebCode412,
   gnetWebCode412_PRECONDITION_FAILED             = gnetWebCode412,
   gnetWebCode413,
   gnetWebCode413_REQUEST_ENTITY_TOO_LARGE        = gnetWebCode413,
   gnetWebCode414,
   gnetWebCode414_REQUEST_URI_TOO_LONG            = gnetWebCode414,
   gnetWebCode415,
   gnetWebCode415_UNSUPPORTED_MEDIA_TYPE          = gnetWebCode415,
   gnetWebCode416,
   gnetWebCode416_REQUESTED_RANGE_NOT_SATISFIABLE = gnetWebCode416,
   gnetWebCode417,
   gnetWebCode417_EXPECTATION_FAILED              = gnetWebCode417,
   gnetWebCode500,
   gnetWebCode500_INTERNAL_SERVER_ERROR           = gnetWebCode500,
   gnetWebCode501,
   gnetWebCode501_NOT_IMPLEMENTED                 = gnetWebCode501,
   gnetWebCode502,
   gnetWebCode502_BAD_GATEWAY                     = gnetWebCode502,
   gnetWebCode503,
   gnetWebCode503_SERVICE_UNAVAILABLE             = gnetWebCode503,
   gnetWebCode504,
   gnetWebCode504_GATEWAY_TIMEOUT                 = gnetWebCode504,
   gnetWebCode505,
   gnetWebCode505_HTTP_VERSION_NOT_SUPPORTED      = gnetWebCode505,

   gnetWebCodeCOUNT
} GnetWebCode;

typedef enum
{
   gnetWebContentNONE,

   gnetWebContentAPP_DATA,
   gnetWebContentAPP_EXCEL,
   gnetWebContentAPP_PDF,
   gnetWebContentAPP_POWERPOINT,
   gnetWebContentAPP_PS,
   gnetWebContentAPP_WORD,
   gnetWebContentAPP_XML,
   gnetWebContentAPP_ZIP,
   gnetWebContentAUDIO_MIDI,
   gnetWebContentAUDIO_MPG,
   gnetWebContentAUDIO_MPG4,
   gnetWebContentAUDIO_OGG,
   gnetWebContentAUDIO_WAV,
   gnetWebContentAUDIO_WEBM,
   gnetWebContentIMAGE_BMP,
   gnetWebContentIMAGE_GIF,
   gnetWebContentIMAGE_JPG,
   gnetWebContentIMAGE_PNG,
   gnetWebContentIMAGE_SVG,
   gnetWebContentIMAGE_TIF,
   gnetWebContentIMAGE_WEBP,
   gnetWebContentTEXT_ASCII,
   gnetWebContentTEXT_CSS,
   gnetWebContentTEXT_CSV,
   gnetWebContentTEXT_HTML,
   gnetWebContentTEXT_JAVASCRIPT,
   gnetWebContentVIDEO_AVI,
   gnetWebContentVIDEO_H264,
   gnetWebContentVIDEO_MPG,
   gnetWebContentVIDEO_MPG4,
   gnetWebContentVIDEO_OGG,
   gnetWebContentVIDEO_QUICKTIME,
   gnetWebContentVIDEO_WMV,

   gnetWebContentCOUNT
} GnetWebContent;

#define gnetWebMethodGET      "GET"
#define gnetWebMethodPOST     "POST"

/* C++ include */
#if defined(__cplusplus)
extern "C"
{
#endif
/***************/

/******************************************************************************
type: 
******************************************************************************/
typedef struct GnetWebData GnetWebData;
typedef void (*GnetWebFunc)(GnetWebData *data);

typedef struct
{
   Gnet           *net;
   GnetWebFunc     func;
   Gs             *page404;
   Gcount          page404CharCount;
   Gc1            *page404Char;
   Gs             *page404Header;
} GnetWeb;

struct GnetWebData
{
   GnetWeb        *web;
   Gnet           *client;
   Gs             *startLine,
                  *cmdMethod,
                  *cmdUrl,
                  *cmdUrlScheme, // http:// or https://
                  *cmdUrlHost,
                  *cmdUrlPath,
                  *cmdUrlPath_NoFile,
                  *cmdUrlFile,
                  *cmdUrlFileExt,
                  *cmdVersion;
   GnetWebContent  content;
   GsArray        *headerLine;
   void           *data;
};

/******************************************************************************
prototype:  
******************************************************************************/
grlAPI GnetWeb       *gnetWebCreate(                  Gs          const * const port, Gcount const listenCount, GnetWebFunc func);
grlAPI Gs            *gnetWebCreateHeaderContent(     GnetWebCode const code, GnetWebContent const content, Gcount const size);

grlAPI void           gnetWebDestroy(                 GnetWeb           * const net);

grlAPI void           gnetWebProcess(                 GnetWeb           * const web);

grlAPI void           gnetWebSetPage404A(             GnetWeb           * const web, Char const * const value);
grlAPI Gb             gnetWebSetResult(               GnetWebData const * const data, Gs const * const headers, Gcount const size, Gn1 const * const content);
grlAPI Gb             gnetWebSetResult404(            GnetWebData const * const data);
grlAPI Gb             gnetWebSetResultBinary(         GnetWebData const * const data, GnetWebCode const code, GnetWebContent const content, Gcount const dataContentSize, Gn1  const * const dataContent);
grlAPI void           gnetWebSetResultA(              GnetWebData const * const data, GnetWebCode const code, GnetWebContent const content, Gcount const dataContentSize, Char const * const dataContent);
grlAPI Gb             gnetWebSetResultFile(           GnetWebData const * const data,                         GnetWebContent const content, Gs const * const file);
grlAPI void           gnetWebSetResultS(              GnetWebData const * const data, GnetWebCode const code, GnetWebContent const content,                               Gs   const * const dataContent);
grlAPI Gb             gnetWebStart(                   void);
grlAPI void           gnetWebStop(                    void);

grlAPI Gnet          *gnetWebDataGetClient(           GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdMethod(        GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrl(           GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrlFile(       GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrlFileExt(    GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrlHost(       GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrlPath(       GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdUrlPath_NoFile(GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetCmdVersion(       GnetWebData const * const gnetWebData);
grlAPI GnetWebContent gnetWebDataGetContent(          GnetWebData const * const gnetWebData);
grlAPI void          *gnetWebDataGetData(             GnetWebData const * const gnetWebData);
grlAPI GsArray       *gnetWebDataGetHeaderLine(       GnetWebData const * const gnetWebData);
grlAPI Gs            *gnetWebDataGetStartLine(        GnetWebData const * const gnetWebData);
grlAPI GnetWeb       *gnetWebDataGetWeb(              GnetWebData const * const gnetWebData);

/* C++ include */
#if defined(__cplusplus)
}
#endif
/***************/

#endif