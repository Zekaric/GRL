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

/******************************************************************************
type: 
******************************************************************************/
#if grlWINDOWS == 1

typedef struct addrinfo                   GnetAddrInfo;
typedef struct sockaddr_storage           GnetSockAddrStorage;
typedef struct sigaction                  GnetSigAction;
typedef struct sockaddr_in                GnetSockAddrIn4;
typedef struct sockaddr_in6               GnetSockAddrIn6;
typedef struct sockaddr                   GnetSockAddr;

#else

typedef struct addrinfo                   GnetAddrInfo;
typedef struct sockaddr_storage           GnetSockAddrStorage;
typedef struct sigaction                  GnetSigAction;
typedef struct sockaddr_in                GnetSockAddrIn4;
typedef struct sockaddr_in6               GnetSockAddrIn6;
typedef struct sockaddr                   GnetSockAddr;

#endif

/******************************************************************************
variable:  
******************************************************************************/
static Gb _isStarted = gbFALSE;

/******************************************************************************
prototype: 
******************************************************************************/
static Gi2   _BufferGet(      Gnet * const net);

static void  _CloseSocket(    GnetSocket const socket);

static Gs   *_GetAddrStr(     GnetAddrInfo const * const addrInfo);
static Gs   *_GetSockAddrStr( GnetSockAddr const * const sockAddr);

static Gb    _IsAddr6(        GnetAddrInfo const * const addrInfo);
static Gb    _IsSockAddr6(    GnetSockAddr const * const sockAddr);

/******************************************************************************
global: 
function: 
******************************************************************************/
/******************************************************************************
func: gnetCreateServer

Create a server / listener socket.
******************************************************************************/
grlAPI Gnet *gnetCreateServer(Gs const * const port, Gcount const listenCount)
{
   Gnet        *net;
   GnetSocket   sid;
   GnetAddrInfo hints,
               *res,
               *p;
   Char const   yes     = '1';
   Gi4          status;
   Gb           result;
   Char        *cport;

   genter;

   result = gbFALSE;
   net    = NULL;
   res    = NULL;
   sid    = (GnetSocket) -1;

   gmemClearType(&hints, GnetAddrInfo);
   hints.ai_family   = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags    = AI_PASSIVE;

   cport  = gsCreateA(port);
   status = getaddrinfo(NULL, cport, &hints, &res);
   gmemDestroy(cport);

   greturnNullIf(status != 0);

   // loop through all the results and bind to the first we can
   for (p = res; p != NULL; p = p->ai_next)
   {
      sid = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
      continueIf(sid == -1);

      status = setsockopt(sid, SOL_SOCKET, SO_REUSEADDR, (char const *) &yes, sizeof(int));
      stopIf(status == -1);

      status = bind(sid, p->ai_addr, (int) p->ai_addrlen);
      if (status == -1)
      {
         _CloseSocket(sid);
         sid = (GnetSocket) -1;
         continue;
      }

      break;
   }

   // We didn't succeed in making a server socket.
   stopIf(p == NULL);

   // Set up listening connectors.
   status = listen(sid, listenCount);
   stopIf(status == -1);

   net = gmemCreateType(Gnet);
   stopIf(!net);

   net->sid    = sid;
   net->addr   = _GetAddrStr(p);
   net->port   = gsCreateFrom(port);
   net->isOpen = gbTRUE;

   result = gbTRUE;

STOP:
   if (!result)
   {
      _CloseSocket(sid);
      gmemDestroy(net);
      net = NULL;
   }
   freeaddrinfo(res);

   greturn net;
}

/******************************************************************************
func: gnetCreateClient

Create a client / caller socket.
******************************************************************************/
grlAPI Gnet *gnetCreateClient(Gs const * const server, Gs const * const port)
{
   GnetAddrInfo hints,
               *res;
   Gi4          status;
   GnetSocket   sid;
   Gn           portNumber;
   Gb           result;
   Gnet        *net;
   Gc2         *error;
   Char        *cserver,
               *cport;

   genter;

   net    = NULL;
   result = gbFALSE;

   // Port number out of range.
   portNumber = gsGetN(port);
   greturnNullIf(portNumber < 1024);
   greturnNullIf(portNumber > 65535);

   gmemClearType(&hints, GnetAddrInfo);
   hints.ai_family   = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_flags    = AI_PASSIVE;

   cserver = gsCreateA(server);
   cport   = gsCreateA(port);
   status = getaddrinfo(cserver, cport, &hints, &res);
   gmemDestroy(cserver);
   gmemDestroy(cport);

   error  = gai_strerror(status);
   greturnNullIf(status != 0);

   // Should find the right res instead of the first.  What what is the right one?
   sid = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
   stopIf(sid == -1);

   status = connect(sid, res->ai_addr, (int) res->ai_addrlen);
   stopIf(status == -1);

   net = gmemCreateType(Gnet);
   stopIf(!net);

   net->sid    = sid;
   net->addr   = gsCreateFrom(server);
   net->port   = gsCreateFrom(port);
   net->isOpen = gbTRUE;

   result = gbTRUE;

STOP:
   if (!result)
   {
      _CloseSocket(sid);
      gmemDestroy(net);
   }
   freeaddrinfo(res);

   greturn net;
}

/******************************************************************************
func: gnetDestroy
******************************************************************************/
grlAPI void gnetDestroy(Gnet * const net)
{
   genter;

   greturnVoidIf(!net);

   _CloseSocket(net->sid);
   gsDestroy(net->addr);
   gsDestroy(net->port);
   gmemDestroy(net);

   greturn;
}

/******************************************************************************
func: gnetGet

Get as much as we can up to byteCount.
******************************************************************************/
grlAPI Gi4 gnetGet(Gnet * const net, Gi4 const byteCount, Gn1 * const byteList)
{
   Gindex loopIndex;
   Gi4    count;
   Gi2    byte;

   genter;

   // Clear the buffer.
   loop(loopIndex)
   {
      // There is some stuff left in the buffer
      breakIf(net->index == net->count);

      // We are done.
      greturnTrueIf(loopIndex == byteCount);
      
      byte = _BufferGet(net);
      byteList[loopIndex] = (Gn1) byte;
   }
   if (net->index == net->count)
   {
      net->count = 0;
      net->index = 0;
   }

   // We are done.
   greturnTrueIf(loopIndex == byteCount);

   // Get as much as we can.
   count = recv(net->sid, (char *) byteList + loopIndex, byteCount - loopIndex, 0);

   // Connection was closed.
   if (count == 0)
   {
      net->isOpen = gbFALSE;
   }

   greturn count;
}

/******************************************************************************
func: gnetGetBuffer

Get the entire buffer.  
******************************************************************************/
grlAPI Gb gnetGetBuffer(Gnet * const net, Gi4 const byteCount, Gn1 * const byteList)
{
   Gi4    gotSoFar,
          left,
          count;
   Gindex loopIndex;

   genter;

   gotSoFar = 0;
   left     = byteCount;

   loop(loopIndex)
   {
      count = gnetGet(net, left, byteList + gotSoFar);
      breakIf(count == 0 || count == -1);

      gotSoFar += count;
      left     -= count;

      breakIf(gotSoFar == byteCount);
   }

   greturnFalseIf(count == 0 || count == -1);

   greturn gbTRUE;
}

/******************************************************************************
func: gnetGetHostAddresses

Pass in a host name and get the addresses associated with the host name.
******************************************************************************/
grlAPI GsArray *gnetGetHostAddresses(Gs const * const hostName)
{
   GnetAddrInfo hints,
               *res,
               *p;
   Gi4          status;
   GsArray     *addrList;
   Gs          *str;
   Char        *chostName;

   genter;
   
   gmemClearType(&hints, GnetAddrInfo);
   hints.ai_family   = AF_UNSPEC; 
   hints.ai_socktype = SOCK_STREAM;

   chostName = gsCreateA(hostName);
   status = getaddrinfo(chostName, NULL, &hints, &res);
   gmemDestroy(chostName);

   greturnNullIf(status != 0);

   addrList = gsArrayCreate(NULL, gbTRUE);

   for (p = res; p != NULL; p = p->ai_next)
   {
      str = _GetAddrStr(p);
      gsArrayAddEnd(addrList, str);
   }

   freeaddrinfo(res);

   greturn addrList;
}

/******************************************************************************
func: gnetGetHostName
******************************************************************************/
grlAPI Gs *gnetGetHostName(void)
{
   Gi4   status;
   Char  hostName[1024];
   Gi4   hostNameLength;

   genter;

   hostName[0]    = 0;
   hostNameLength = 1024;

   status = gethostname(hostName, 1024);
   if (status == -1)
   {
      greturn NULL;
   }

   greturn gsCreateFromA(hostName);
}

/******************************************************************************
func: gnetGetRemoteName
******************************************************************************/
grlAPI Gs *gnetGetRemoteName(Gnet const * const net)
{
   Gi4             status;
   GnetSockAddr    sockAddr;
   Gi4             size;
   Gs             *str;

   genter;

   size = sizeof(GnetSockAddr);
   status = getpeername(net->sid, &sockAddr, &size);

   str = _GetSockAddrStr(&sockAddr);

   greturn str;
}

/******************************************************************************
func: gnetGetSToLF
******************************************************************************/
grlAPI Gs *gnetGetSToLF(Gnet * const net)
{
   Gs    *str;
   Gindex loopIndex;
   Gi2    byte;

   genter;

   str = gsCreate();

   loop(loopIndex)
   {
      // Get the next byte from the socket.
      byte = _BufferGet(net);
      breakIf(byte == -1);

      // Append the byte to the string.
      gsAppendC(str, (Gc2) byte);

      // We have found the LF
      breakIf(gsGetAt(str, gsGetCount(str) - 1) == '\n');
   }

   greturn str;
}

/******************************************************************************
func: gnetIsDataWaiting
******************************************************************************/
grlAPI Gb gnetIsDataWaiting(Gnet const * const net)
{
   struct timeval tv;
   Gi4            status;
   fd_set         set,
                  readSet;

   genter;

   tv.tv_sec      =
      tv.tv_usec  = 0;

   FD_ZERO(&readSet);
   FD_ZERO(&set);
   FD_SET(net->sid, &set);

   status = select((int) net->sid + 1, &readSet, NULL, NULL, &tv);

   greturnTrueIf(FD_ISSET(net->sid, &readSet));

   greturn gbFALSE;
}

/******************************************************************************
func: gnetIsOpen
******************************************************************************/
grlAPI Gb gnetIsOpen(Gnet const * const net)
{
   Gb result;

   genter;

   result = net->isOpen;

   greturn result;
}

/******************************************************************************
func: gnetSet

Send as much as we can up to byteCount.
******************************************************************************/
grlAPI Gi4 gnetSet(Gnet const * const net, Gi4 const byteCount, Gn1 const * const byteList)
{
   Gi4 count;

   genter;

   count = send(net->sid, (char const *) byteList, byteCount, 0);

   return count;
}

/******************************************************************************
func: gnetSetBuffer

Send all byteCount bytes before returning.
******************************************************************************/
grlAPI Gb gnetSetBuffer(Gnet const * const net, Gi4 const byteCount, Gn1 const * const byteList)
{
   Gindex loopIndex;
   Gi4    left,
          sentSoFar,
          count;

   genter;

   sentSoFar = 0;
   left      = byteCount;

   loop(loopIndex)
   {
      count = gnetSet(net, left, byteList + sentSoFar);
      breakIf(count == -1);

      sentSoFar += count;
      left      -= count;

      breakIf(sentSoFar == byteCount);
   }

   greturnFalseIf(count == -1);

   greturn gbTRUE;
}

/******************************************************************************
func: gnetServerAccept
******************************************************************************/
grlAPI Gnet *gnetServerAccept(Gnet const * const net)
{
   GnetSockAddrStorage  sockAddrStorage;
   socklen_t            sockLen;
   GnetSocket           sid;
   Gnet                *netClient;
   Gb                   result;

   genter;

   result = gbFALSE;

   sockLen = sizeof(GnetSockAddrStorage);

   sid = accept(net->sid, (GnetSockAddr *) &sockAddrStorage, &sockLen);
   greturnNullIf(sid == -1);

   netClient = gmemCreateType(Gnet);
   stopIf(!netClient);

   netClient->sid  = sid;
   netClient->addr = _GetSockAddrStr((GnetSockAddr const * const) &sockAddrStorage);

   result = gbTRUE;

STOP:
   if (!result)
   {
      _CloseSocket(sid);
   }

   greturn netClient;
}

/******************************************************************************
func: gnetStart

Start the network routines.
******************************************************************************/
grlAPI Gb gnetStart(void)
{
   // Windows only.
#if defined(WIN32)
   // if this doesn't work
   WSADATA wsaData;
   // WSAData wsaData; then try this instead 

   genter;

   // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0;
   // Initialize the socket library.
   greturnFalseIf(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0);
#else
   genter;
#endif

   _isStarted = gbTRUE;

   greturn gbTRUE;
}

/******************************************************************************
func: gnetStop 
******************************************************************************/
grlAPI void gnetStop(void)
{
   genter;

   // Windows Code
#if defined(WIN32)
   // Let the library clean up
   WSACleanup();
#endif

   _isStarted = gbFALSE;

   greturn;
}

/******************************************************************************
local: 
function: 
******************************************************************************/
/******************************************************************************
func: _BufferGet

Get a byte from the socket.  This buffer reads from the port.
******************************************************************************/
static Gi2 _BufferGet(Gnet * const net)
{
   genter;

   // Buffer is empty.
   if (net->index == 0 ||
       net->index == net->count)
   {
      // Get as much as we can from the socket up to BUFFER_SIZE.
      net->index = 0;
      net->count = 0;
      net->count = gnetGet(net, gnetBUFFER_SIZE, net->buffer);

      // Connection closed closed.
      greturnIf(net->count == 0, -1);
   }

   // Get the next byte in the buffer.
   greturn net->buffer[net->index++];
}

/******************************************************************************
func: _CloseSocket
******************************************************************************/
static void _CloseSocket(GnetSocket const sid)
{
   genter;

   greturnVoidIf(sid == -1);

#if defined(WIN32)
   closesocket(sid);
#else
   close(sid);
#endif

   greturn;
}

/******************************************************************************
func: _GetAddrStr
******************************************************************************/
static Gs *_GetAddrStr(GnetAddrInfo const * const addrInfo)
{
   Char   ipStr[INET6_ADDRSTRLEN];
   void  *addr;

   genter;

   if (!_IsAddr6(addrInfo))
   {
      GnetSockAddrIn4 *ip = (GnetSockAddrIn4 *) addrInfo->ai_addr;
      addr = &(ip->sin_addr);
   }
   else
   {
      GnetSockAddrIn6 *ip = (GnetSockAddrIn6 *) addrInfo->ai_addr;
      addr = &(ip->sin6_addr);
   }

   inet_ntop(addrInfo->ai_family, addr, ipStr, INET6_ADDRSTRLEN);
   
   greturn gsCreateFromA(ipStr);
}

/******************************************************************************
func: _GetSockAddrStr
******************************************************************************/
static Gs *_GetSockAddrStr(GnetSockAddr const * const sockAddr)
{
   Char   ipStr[INET6_ADDRSTRLEN];
   void  *addr;

   genter;

   if (!_IsSockAddr6((GnetSockAddr *) sockAddr))
   {
      GnetSockAddrIn4 *ip = (GnetSockAddrIn4 *) sockAddr;
      addr = &(ip->sin_addr);
   }
   else
   {
      GnetSockAddrIn6 *ip = (GnetSockAddrIn6 *) sockAddr;
      addr = &(ip->sin6_addr);
   }

   inet_ntop(sockAddr->sa_family, addr, ipStr, INET6_ADDRSTRLEN);
   
   greturn gsCreateFromA(ipStr);
}

/******************************************************************************
func: _IsAddr6
******************************************************************************/
static Gb _IsAddr6(GnetAddrInfo const * const addrInfo)
{
   genter;

   if (addrInfo->ai_family == AF_INET)
   {
      greturn gbFALSE;
   }
   
   greturn gbTRUE;
}

/******************************************************************************
func: _IsSockAddr6
******************************************************************************/
static Gb _IsSockAddr6(GnetSockAddr const * const sockAddr)
{
   genter;

   if (sockAddr->sa_family == AF_INET)
   {
      greturn gbFALSE;
   }
   
   greturn gbTRUE;
}

