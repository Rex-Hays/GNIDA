/* WINSOCK.H--definitions to be used with the WINSOCK.DLL
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * This header file corresponds to version 1.1 of the Windows Sockets specification.
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 */

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_

/*
 * Pull in WINDOWS.H if necessary
 */
#ifndef _INC_WINDOWS
#include <windows.h>
#endif /* _INC_WINDOWS */

/*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 */
#define u_char unsigned char
#define u_short unsigned short
#define u_int unsigned int
#define u_long unsigned long

/*
 * The new type to be used in all
 * instances which refer to sockets.
 */
#define SOCKET dword

/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       IOC_IN|IOC_OUT
                                        /* 0x20000000 distinguishes new &
                                           old ioctl's */
#define _IO(x,y)        x<<8|y|IOC_VOID
//#define _IOR(x,y,t)     (IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
//#define _IOW(x,y,t)     (IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)

#define FIONREAD	0x4004667F
?define FIONBIO   0x8004667E      // Const
?define FIOASYNC	0x8004667D
?define	PCL_NONE	0
?define HOST_ENT	0xC;

/* Socket I/O Controls */
#define SIOCSHIWAT  0x80047300  /* set high watermark */
#define SIOCGHIWAT  0x40047302  /* get high watermark */
#define SIOCSLOWAT  0x80047303  /* set low watermark */
#define SIOCGLOWAT  0x40047303  /* get low watermark */
#define SIOCATMARK  0x40047307  /* at oob mark? */

/*
 * Structures returned by network data base library, taken from the
 * BSD file netdb.h.  All addresses are supplied in host order, and
 * returned in network order (suitable for use in system calls).
 */

struct  hostent {
  dword/*char    **/ h_name;           /* official name of host */
  dword/*char    ***/ h_aliases;  /* alias list */
  short   h_addrtype;             /* host address type */
  short   h_length;               /* length of address */
  dword/*char    ***/ h_addr_list; /* list of addresses */
};
#define h_addr  h_addr_list          /* address, for backward compat */

/*
 * It is assumed here that a network number
 * fits in 32 bits.
 */
struct  netent {
  dword/*char    **/n_name;           /* official name of net */
  dword/*char    ***/n_aliases;  /* alias list */
  short   n_addrtype;             /* net address type */
  u_long  n_net;                  /* network # */
};

struct  servent {
  dword/*char    **/s_name;           /* official service name */
  dword/*char    ***/s_aliases;  /* alias list */
#ifdef _WIN64
  dword/*char    **/s_proto;          /* protocol to use */
  short   s_port;                 /* port # */
#else
  short   s_port;                 /* port # */
  dword/*char    **/s_proto;          /* protocol to use */
#endif
};

struct  protoent {
  dword/*char    **/p_name;           /* official protocol name */
  dword/*char    ***/p_aliases;  /* alias list */
  short   p_proto;                /* protocol # */
};

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
 */

/*
 * Protocols
 */
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */

#define IPPROTO_RAW             255             /* raw IP packet */
#define IPPROTO_MAX             256

/*
 * Port/socket numbers: network standard functions
 */
#define IPPORT_ECHO             7
#define IPPORT_DISCARD          9
#define IPPORT_SYSTAT           11
#define IPPORT_DAYTIME          13
#define IPPORT_NETSTAT          15
#define IPPORT_FTP              21
#define IPPORT_TELNET           23
#define IPPORT_SMTP             25
#define IPPORT_TIMESERVER       37
#define IPPORT_NAMESERVER       42
#define IPPORT_WHOIS            43
#define IPPORT_MTP              57

/*
 * Port/socket numbers: host specific functions
 */
#define IPPORT_TFTP             69
#define IPPORT_RJE              77
#define IPPORT_FINGER           79
#define IPPORT_TTYLINK          87
#define IPPORT_SUPDUP           95

/*
 * UNIX TCP sockets
 */
#define IPPORT_EXECSERVER       512
#define IPPORT_LOGINSERVER      513
#define IPPORT_CMDSERVER        514
#define IPPORT_EFSSERVER        520

/*
 * UNIX UDP sockets
 */
#define IPPORT_BIFFUDP          512
#define IPPORT_WHOSERVER        513
#define IPPORT_ROUTESERVER      520
                                        /* 520+1 also used */

/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 */
#define IPPORT_RESERVED         1024

/*
 * Link numbers
 */
#define IMPLINK_IP              155
#define IMPLINK_LOWEXPER        156
#define IMPLINK_HIGHEXPER       158

/*
 * Internet address (old style... should be updated)
 */
struct in_addr {
  union {
    struct { u_char s_b1,s_b2,s_b3,s_b4; } S_un_b;
    struct { u_short s_w1,s_w2; } S_un_w;
    u_long S_addr;
  }S_un;
#define s_addr  S_un.S_addr
                                /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2
                                /* host on imp */
#define s_net   S_un.S_un_b.s_b1
                                /* network */
#define s_imp   S_un.S_un_w.s_w2
                               /* imp */
#define s_impno S_un.S_un_b.s_b4
                                /* imp # */
#define s_lh    S_un.S_un_b.s_b3
                                /* logical host */
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define IN_CLASSA(i)            (i & 0x80000000 == 0)
#define IN_CLASSA_NET           0xff000000
#define IN_CLASSA_NSHIFT        24
#define IN_CLASSA_HOST          0x00ffffff
#define IN_CLASSA_MAX           128

#define IN_CLASSB(i)            (i & 0xc0000000 == 0x80000000)
#define IN_CLASSB_NET           0xffff0000
#define IN_CLASSB_NSHIFT        16
#define IN_CLASSB_HOST          0x0000ffff
#define IN_CLASSB_MAX           65536

#define IN_CLASSC(i)            (i & 0xe0000000 == 0xc0000000)
#define IN_CLASSC_NET           0xffffff00
#define IN_CLASSC_NSHIFT        8
#define IN_CLASSC_HOST          0x000000ff

#define INADDR_ANY              0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        0xffffffff
#define INADDR_NONE             0xffffffff

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
  short   sin_family;
  u_short sin_port;
  union{
    struct  in_addr sin_addr;
    dword S_addr;
  };
  char    sin_zero[8];
};

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

struct WSADATA{
  WORD                    wVersion;
  WORD                    wHighVersion;
#ifdef _WIN64
  unsigned short          iMaxSockets;
  unsigned short          iMaxUdpDg;
  dword/*char **/              lpVendorInfo;
  char                    szDescription[WSADESCRIPTION_LEN+1];
  char                    szSystemStatus[WSASYS_STATUS_LEN+1];
#else
  char                    szDescription[WSADESCRIPTION_LEN+1];
  char                    szSystemStatus[WSASYS_STATUS_LEN+1];
  unsigned short          iMaxSockets;
  unsigned short          iMaxUdpDg;
  dword/*char **/              lpVendorInfo;
#endif
};

#define WSAData WSADATA

/*
 * Options for use with [gs]etsockopt at the IP level.
 */
#define IP_OPTIONS          1           /* set/get IP per-packet options    */
#define IP_MULTICAST_IF     2           /* set/get IP multicast interface   */
#define IP_MULTICAST_TTL    3           /* set/get IP multicast timetolive  */
#define IP_MULTICAST_LOOP   4           /* set/get IP multicast loopback    */
#define IP_ADD_MEMBERSHIP   5           /* add  an IP group membership      */
#define IP_DROP_MEMBERSHIP  6           /* drop an IP group membership      */
#define IP_TTL              7           /* set/get IP Time To Live          */
#define IP_TOS              8           /* set/get IP Type Of Service       */
#define IP_DONTFRAGMENT     9           /* set/get IP Don't Fragment flag   */

#define IP_DEFAULT_MULTICAST_TTL   1    /* normally limit m'casts to 1 hop  */
#define IP_DEFAULT_MULTICAST_LOOP  1    /* normally hear sends if a member  */
#define IP_MAX_MEMBERSHIPS         20   /* per socket; must fit in one mbuf */

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct ip_mreq {
	in_addr  imr_multiaddr;  /* IP multicast address of group */
	in_addr  imr_interface;  /* local IP address of interface */
};

/*
 * Definitions related to sockets: types, address families, options,
 * taken from the BSD file sys/socket.h.
 */

/*
 * This is used instead of -1, since the
 * SOCKET type is unsigned.
 */
#define INVALID_SOCKET  ~0
#define SOCKET_ERROR            -1

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */

/*
 * Option flags per-socket.
 */
#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */

#define SO_DONTLINGER   ~SO_LINGER

/*
 * Additional options.
 */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */

/*
 * Options for connect and disconnect data and options.  Used only by
 * non-TCP/IP transports such as DECNet, OSI TP4, etc.
 */
#define SO_CONNDATA     0x7000
#define SO_CONNOPT      0x7001
#define SO_DISCDATA     0x7002
#define SO_DISCOPT      0x7003
#define SO_CONNDATALEN  0x7004
#define SO_CONNOPTLEN   0x7005
#define SO_DISCDATALEN  0x7006
#define SO_DISCOPTLEN   0x7007

/*
 * Option for opening sockets for synchronous access.
 */
#define SO_OPENTYPE     0x7008
#define SO_SYNCHRONOUS_ALERT    0x10
#define SO_SYNCHRONOUS_NONALERT 0x20

/*
 * Other NT-specific options.
 */
#define SO_MAXDG        0x7009
#define SO_MAXPATHDG    0x700A
#define SO_UPDATE_ACCEPT_CONTEXT 0x700B
#define SO_CONNECT_TIME 0x700C

/*
 * TCP options.
 */
#define TCP_NODELAY     0x0001
#define TCP_BSDURGENT   0x7000

/*
 * Address families.
 */
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_IPX          6               /* IPX and SPX */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO          /* OSI is ISO */
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* AppleTalk */
#define AF_NETBIOS      17              /* NetBios-style addresses */
#define AF_VOICEVIEW    18              /* VoiceView */
#define AF_FIREFOX      19              /* FireFox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */
#define AF_MAX          22

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
  u_short sa_family;              /* address family */
  char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
  u_short sp_family;              /* address family */
  u_short sp_protocol;            /* protocol */
};

/*
 * Protocol families, same as address families for now.
 */
#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_IPX          AF_IPX
#define PF_ISO          AF_ISO
#define PF_OSI          AF_OSI
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK
#define PF_VOICEVIEW    AF_VOICEVIEW
#define PF_FIREFOX      AF_FIREFOX
#define PF_UNKNOWN1     AF_UNKNOWN1
#define PF_BAN          AF_BAN
#define PF_MAX          AF_MAX

/*
 * Structure used for manipulating linger option.
 */
struct  linger {
  u_short l_onoff;                /* option on/off */
  u_short l_linger;               /* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define SOL_SOCKET      0xffff          /* options for socket level */

/*
 * Maximum queue length specifiable by listen.
 */
#define SOMAXCONN       5
#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */
#define MSG_MAXIOVLEN   16
#define MSG_PARTIAL     0x8000          /* partial send or recv for message xport */

/*
 * Define constant based on rfc883, used by gethostbyxxxx() calls.
 */
#define MAXGETHOSTSTRUCT        1024

/*
 * Define flags to be used with the WSAAsyncSelect() call.
 */
#define FD_READ         0x01
#define FD_WRITE        0x02
#define FD_OOB          0x04
#define FD_ACCEPT       0x08
#define FD_CONNECT      0x10
#define FD_CLOSE        0x20

/*
 * WinSock error codes are also defined in winerror.h
 * Hence the IFDEF.
 */
#ifndef WSABASEERR

/*
 * All Windows Sockets error constants are biased by WSABASEERR from
 * the "normal"
 */
#define WSABASEERR              10000
/*
 * Windows Sockets definitions of regular Microsoft C error constants
 */
#define WSAEINTR                WSABASEERR+4
#define WSAEBADF                WSABASEERR+9
#define WSAEACCES               WSABASEERR+13
#define WSAEFAULT               WSABASEERR+14
#define WSAEINVAL               WSABASEERR+22
#define WSAEMFILE               WSABASEERR+24

/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
#define WSAEWOULDBLOCK          WSABASEERR+35
#define WSAEINPROGRESS          WSABASEERR+36
#define WSAEALREADY             WSABASEERR+37
#define WSAENOTSOCK             WSABASEERR+38
#define WSAEDESTADDRREQ         WSABASEERR+39
#define WSAEMSGSIZE             WSABASEERR+40
#define WSAEPROTOTYPE           WSABASEERR+41
#define WSAENOPROTOOPT          WSABASEERR+42
#define WSAEPROTONOSUPPORT      WSABASEERR+43
#define WSAESOCKTNOSUPPORT      WSABASEERR+44
#define WSAEOPNOTSUPP           WSABASEERR+45
#define WSAEPFNOSUPPORT         WSABASEERR+46
#define WSAEAFNOSUPPORT         WSABASEERR+47
#define WSAEADDRINUSE           WSABASEERR+48
#define WSAEADDRNOTAVAIL        WSABASEERR+49
#define WSAENETDOWN             WSABASEERR+50
#define WSAENETUNREACH          WSABASEERR+51
#define WSAENETRESET            WSABASEERR+52
#define WSAECONNABORTED         WSABASEERR+53
#define WSAECONNRESET           WSABASEERR+54
#define WSAENOBUFS              WSABASEERR+55
#define WSAEISCONN              WSABASEERR+56
#define WSAENOTCONN             WSABASEERR+57
#define WSAESHUTDOWN            WSABASEERR+58
#define WSAETOOMANYREFS         WSABASEERR+59
#define WSAETIMEDOUT            WSABASEERR+60
#define WSAECONNREFUSED         WSABASEERR+61
#define WSAELOOP                WSABASEERR+62
#define WSAENAMETOOLONG         WSABASEERR+63
#define WSAEHOSTDOWN            WSABASEERR+64
#define WSAEHOSTUNREACH         WSABASEERR+65
#define WSAENOTEMPTY            WSABASEERR+66
#define WSAEPROCLIM             WSABASEERR+67
#define WSAEUSERS               WSABASEERR+68
#define WSAEDQUOT               WSABASEERR+69
#define WSAESTALE               WSABASEERR+70
#define WSAEREMOTE              WSABASEERR+71
#define WSAEDISCON              WSABASEERR+101

/*
 * Extended Windows Sockets error constant definitions
 */
#define WSASYSNOTREADY          WSABASEERR+91
#define WSAVERNOTSUPPORTED      WSABASEERR+92
#define WSANOTINITIALISED       WSABASEERR+93

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver). Note that these errors are
 * retrieved via WSAGetLastError() and must therefore follow
 * the rules for avoiding clashes with error numbers from
 * specific implementations or language run-time systems.
 * For this reason the codes are based at WSABASEERR+1001.
 * Note also that [WSA]NO_ADDRESS is defined only for
 * compatibility purposes.
 */

/* Authoritative Answer: Host not found */
#define WSAHOST_NOT_FOUND       WSABASEERR+1001

/* Non-Authoritative: Host not found, or SERVERFAIL */
#define WSATRY_AGAIN            WSABASEERR+1002

/* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define WSANO_RECOVERY          WSABASEERR+1003

/* Valid name, no data record of requested type */
#define WSANO_DATA              WSABASEERR+1004

/*
 * WinSock error codes are also defined in winerror.h
 * Hence the IFDEF.
 */
#endif /* ifdef WSABASEERR */

/*
 * Compatibility macros.
 */

#define h_errno         WSAGetLastError()
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND
#define TRY_AGAIN               WSATRY_AGAIN
#define NO_RECOVERY             WSANO_RECOVERY
#define NO_DATA                 WSANO_DATA
/* no address, look for MX record */
#define WSANO_ADDRESS           WSANO_DATA
#define NO_ADDRESS              WSANO_ADDRESS

struct TRANSMIT_FILE_BUFFERS {
  PVOID Head;
  DWORD HeadLength;
  PVOID Tail;
  DWORD TailLength;
};

#define TF_DISCONNECT       0x01
#define TF_REUSE_SOCKET     0x02
#define TF_WRITE_BEHIND     0x04

/* Socket function prototypes */
extern WINAPI "WSOCK32.DLL"{
	SOCKET accept(SOCKET s,dword addr,dword addrlen);
	int bind(SOCKET s,dword addr,int namelen);
	int closesocket(SOCKET s);
	int connect(SOCKET s,dword name,int namelen);
	int ioctlsocket(SOCKET s,long cmd,dword argp);
	int getpeername(SOCKET s,dword name,dword namelen);
	int getsockname(SOCKET s,dword name,dword namelen);
	int getsockopt(SOCKET s,int level,int optname,dword optval,dword optlen);
	u_long htonl(u_long hostlong);
	u_short htons(u_short hostshort);
	unsigned long inet_addr(dword cp);
	dword inet_ntoa(in_addr in);
	int listen(SOCKET s,int backlog);
	u_long ntohl(u_long netlong);
	u_short ntohs(u_short netshort);
	int recv(SOCKET s,dword buf,int len,int flags);
	int recvfrom(SOCKET s,dword buf,int len,int flags,dword from,dword fromlen);
	int select(int nfds,dword readfds,dword writefds,dword exceptfds,dword timeout);
	int send(SOCKET s,dword buf,int len,int flags);
	int sendto(SOCKET s,dword buf,int len,int flags,dword to,int tolen);
	int setsockopt(SOCKET s,int level,int optname,dword optval,int optlen);
	int shutdown(SOCKET s,int how);
	SOCKET socket(int af,int type,int protocol);

/* Database function prototypes */
	dword gethostbyaddr(dword addr,int len,int type);
	dword gethostbyname(dword name);
	int gethostname(dword name,int namelen);
	dword getservbyport(int port,dword proto);
	dword getservbyname(dword name,dword proto);
	dword getprotobynumber(int proto);
	dword getprotobyname(dword name);

/* Microsoft Windows Extension function prototypes */
	int WSAStartup(WORD wVersionRequired,dword lpWSAData);
	int WSACleanup(void);
	void WSASetLastError(int iError);
	int WSAGetLastError(void);
	BOOL WSAIsBlocking(void);
	int WSAUnhookBlockingHook(void);
	dword WSASetBlockingHook(dword lpBlockFunc);
	int WSACancelBlockingCall(void);
	HANDLE WSAAsyncGetServByName(HWND hWnd,u_int wMsg,dword name,dword proto,dword buf,int buflen);
	HANDLE WSAAsyncGetServByPort(HWND hWnd,u_int wMsg,int port,dword proto,dword buf,int buflen);
	HANDLE WSAAsyncGetProtoByName(HWND hWnd,u_int wMsg,dword name,dword buf,int buflen);
	HANDLE WSAAsyncGetProtoByNumber(HWND hWnd,u_int wMsg,int number,dword buf,int buflen);
	HANDLE WSAAsyncGetHostByName(HWND hWnd,u_int wMsg,dword name,dword buf,int buflen);
	HANDLE WSAAsyncGetHostByAddr(HWND hWnd,u_int wMsg,dword addr,int len,int type,dword buf,int buflen);
	int WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
	int WSAAsyncSelect(SOCKET s,HWND hWnd,u_int wMsg,long lEvent);
	int WSARecvEx(SOCKET s,dword buf,int len,dword flags);
	BOOL TransmitFile(SOCKET hSocket,HANDLE hFile,DWORD nNumberOfBytesToWrite,
		DWORD nNumberOfBytesPerSend,dword lpOverlapped,dword lpTransmitBuffers,DWORD dwReserved);
	BOOL AcceptEx(SOCKET sListenSocket,SOCKET sAcceptSocket,PVOID lpOutputBuffer,
		DWORD dwReceiveDataLength,DWORD dwLocalAddressLength,DWORD dwRemoteAddressLength,
		dword lpdwBytesReceived,dword lpOverlapped);
	VOID GetAcceptExSockaddrs(PVOID lpOutputBuffer,DWORD dwReceiveDataLength,
		DWORD dwLocalAddressLength,DWORD dwRemoteAddressLength,dword LocalSockaddr,
		LPINT LocalSockaddrLength,dword RemoteSockaddr,LPINT RemoteSockaddrLength);
}
/* Microsoft Windows Extended data types */
#define SOCKADDR sockaddr
#define SOCKADDR_IN sockaddr_in
#define LINGER linger
#define IN_ADDR in_addr
//#define FD_SET fd_set
#define HOSTENT hostent
#define SERVENT servent
#define PROTOENT protoent
#define TIMEVAL timeval

/*
 * Windows message parameter composition and decomposition
 * macros.
 * WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to a WSAAsyncGetXByY() routine.
 */
#define WSAMAKEASYNCREPLY(buflen,error)     MAKELONG(buflen,error)
/*
 * WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to WSAAsyncSelect().
 */
#define WSAMAKESELECTREPLY(event,error)     MAKELONG(event,error)
/*
 * WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
 * to extract the buffer length from the lParam in the response
 * to a WSAGetXByY().
 */
#define WSAGETASYNCBUFLEN(lParam)           LOWORD(lParam)
/*
 * WSAGETASYNCERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAGetXByY().
 */
#define WSAGETASYNCERROR(lParam)            HIWORD(lParam)
/*
 * WSAGETSELECTEVENT is intended for use by the Windows Sockets application
 * to extract the event code from the lParam in the response
 * to a WSAAsyncSelect().
 */
#define WSAGETSELECTEVENT(lParam)           LOWORD(lParam)
/*
 * WSAGETSELECTERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAAsyncSelect().
 */
#define WSAGETSELECTERROR(lParam)           HIWORD(lParam)

#endif  /* _WINSOCKAPI_ */
