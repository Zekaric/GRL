/******************************************************************************

file:       gnet
author:     Robbert de Groot
copyright:  2001-2012, Robbert de Groot
 
description:
Socket coding simplified.

******************************************************************************/
#if !defined(GNETH)
#define      GNETH

/******************************************************************************
include: 
******************************************************************************/
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#if defined(WIN32)

#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#endif

/******************************************************************************
constant:  
******************************************************************************/

#define gnetLISTEN_DEFAULT    10

#define gnetBUFFER_SIZE       2048

/* C++ include */
#if defined(__cplusplus)
extern "C"
{
#endif
/***************/

/******************************************************************************
type: 
******************************************************************************/
#if defined(WIN32)
typedef SOCKET GnetSocket;
#else
typedef int    GnetSocket;
#endif

typedef struct
{
   GnetSocket   sid;
   Gs          *addr,
               *port;
   Gb           isOpen;
   Gn1          buffer[gnetBUFFER_SIZE];
   Gi4          count,
                index;
} Gnet;

/******************************************************************************
prototype:  
******************************************************************************/
grlAPI Gnet    *gnetCreateServer(      Gs   const * const port, Gcount const listenCount);
grlAPI Gnet    *gnetCreateClient(      Gs   const * const server, Gs const * const port);

grlAPI void     gnetDestroy(           Gnet       * const net);

grlAPI Gi4      gnetGet(               Gnet       * const net, Gi4 const byteCount, Gn1 * const byteList);
grlAPI Gb       gnetGetBuffer(         Gnet       * const net, Gi4 const byteCount, Gn1 * const byteList);
grlAPI GsArray *gnetGetHostAddresses(  Gs   const * const hostName);
grlAPI Gs      *gnetGetHostName(       void);
grlAPI Gs      *gnetGetRemoteName(     Gnet const * const net);
grlAPI Gs      *gnetGetSToLF(          Gnet       * const net);

grlAPI Gb       gnetIsDataWaiting(     Gnet const * const net);
grlAPI Gb       gnetIsOpen(            Gnet const * const net);

grlAPI Gi4      gnetSet(               Gnet const * const net, Gi4 const byteCount, Gn1 const * const byteList);
grlAPI Gb       gnetSetBuffer(         Gnet const * const net, Gi4 const byteCount, Gn1 const * const byteList);
grlAPI Gnet    *gnetServerAccept(      Gnet const * const net);
grlAPI Gb       gnetStart(             void);
grlAPI void     gnetStop(              void);

/* C++ include */
#if defined(__cplusplus)
}
#endif
/***************/

#endif