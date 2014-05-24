/* Winsock2.h -- definitions to be used with the WinSock 2 DLL and
 *               WinSock 2 applications.
 * This header file corresponds to version 2.2.x of the WinSock API
 * specification.
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 */

#ifndef _WINSOCK2API_
#define _WINSOCK2API_
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */

/*
 * Ensure structures are packed consistently.
 * Not necessary for WIN32, it is already packed >=4 and there are
 * no structures in this header that have alignment requirement
 * higher than 4.
 * For WIN64 we do not have compatibility requirement because it is
 * not possible to mix 32/16 bit code with 64 bit code in the same
 * process.
 */

#if !defined(WIN32) && !defined(_WIN64)
#pragma pack(push,4)
#endif
/*
 * Default: include function prototypes, don't include function typedefs.
 */
#ifndef INCL_WINSOCK_API_PROTOTYPES
#define INCL_WINSOCK_API_PROTOTYPES 1
#endif

#ifndef INCL_WINSOCK_API_TYPEDEFS
#define INCL_WINSOCK_API_TYPEDEFS 0
#endif

/*
 * Pull in WINDOWS.H if necessary
 */
#ifndef _INC_WINDOWS
#include <windows.h>
#endif /* _INC_WINDOWS */

/*
 * Define the current Winsock version. To build an earlier Winsock version
 * application redefine this value prior to including Winsock2.h.
 */

#if !defined(MAKEWORD)
#define MAKEWORD(low,high) high<<8|low
#endif

#ifndef WINSOCK_VERSION
#define WINSOCK_VERSION MAKEWORD(2,2)
#endif

/*
 * Establish DLL function linkage if supported by the current build
 * environment and not previously defined.
 */

#ifndef WINSOCK_API_LINKAGE
#ifdef DECLSPEC_IMPORT
#define WINSOCK_API_LINKAGE DECLSPEC_IMPORT
#else
#define WINSOCK_API_LINKAGE
#endif
#endif

/*
 * Basic system type definitions, taken from the BSD file sys/types.h.
 */
#define u_char unsigned char
#define u_short unsigned short
#define u_int unsigned int
#define u_long unsigned long
#define u_int64 qword

/*
 * The new type to be used in all
 * instances which refer to sockets.
 */
#define SOCKET dword

/*
 * Select uses arrays of SOCKETs.  These macros manipulate such
 * arrays.  FD_SETSIZE may be defined by the user before including
 * this file, but the default here should be >= 64.
 *
 * CAVEAT IMPLEMENTOR and USER: THESE MACROS AND TYPES MUST BE
 * INCLUDED IN WINSOCK2.H EXACTLY AS SHOWN HERE.
 */
#ifndef FD_SETSIZE
#define FD_SETSIZE      64
#endif /* FD_SETSIZE */

struct fd_set{
  u_int fd_count;               // how many are SET?
  SOCKET  fd_array[FD_SETSIZE];   // an array of SOCKETs
};
/*
 * Structure used in select() call, taken from the BSD file sys/time.h.
 */
struct timeval {
 long    tv_sec;         /* seconds */
 long    tv_usec;        /* and microseconds */
};

/*
 * Operations on timevals.
 *
 * NB: timercmp does not work for >= or <=.
 */
/*
#define timerisset(tvp)         ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
        ((tvp)->tv_sec cmp (uvp)->tv_sec || \
         (tvp)->tv_sec == (uvp)->tv_sec && (tvp)->tv_usec cmp (uvp)->tv_usec)
#define timerclear(tvp)         (tvp)->tv_sec = (tvp)->tv_usec = 0
	*/
/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 *
 *
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
#ifndef hostent
#define _IO(x,y)        x<<8|y|IOC_VOID

//#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))
//#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD	0x4004667F /* get # bytes to read */
#define FIONBIO   0x8004667E /* set/clear non-blocking i/o */
#define FIOASYNC	0x8004667D /* set/clear async i/o */

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
  dword/*char    **/h_name;           /* official name of host */
  dword/*char    ***/h_aliases;  /* alias list */
  short   h_addrtype;             /* host address type */
  short   h_length;               /* length of address */
  dword/*char    ***/h_addr_list; /* list of addresses */
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
#endif

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981, taken from the BSD file netinet/in.h.
 */

/*
 * Protocols
 */
#define IPPROTO_IP              0               /* dummy for IP */
#define IPPROTO_ICMP            1               /* control message protocol */
#define IPPROTO_IGMP            2               /* internet group management protocol */
#define IPPROTO_GGP             3               /* gateway^2 (deprecated) */
#define IPPROTO_TCP             6               /* tcp */
#define IPPROTO_PUP             12              /* pup */
#define IPPROTO_UDP             17              /* user datagram protocol */
#define IPPROTO_IDP             22              /* xns idp */
#define IPPROTO_IPV6            41              /* IPv6 */
#define IPPROTO_ND              77              /* UNOFFICIAL net disk proto */
#define IPPROTO_ICLFXBM         78
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

#ifndef in_addr
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
#define IN_CLASSD(i)            (i & 0xf0000000 == 0xe0000000)
#define IN_CLASSD_NET           0xf0000000       /* These ones aren't really */
#define IN_CLASSD_NSHIFT        28               /* net and host fields, but */
#define IN_CLASSD_HOST          0x0fffffff       /* routing needn't know.    */
#define IN_MULTICAST(i)         IN_CLASSD(i)
#define INADDR_ANY              0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        0xffffffff
#define INADDR_NONE             0xffffffff

#define ADDR_ANY                INADDR_ANY

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

struct WSADATA {
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

#endif
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
 * The  following  may  be used in place of the address family, socket type, or
 * protocol  in  a  call  to WSASocket to indicate that the corresponding value
 * should  be taken from the supplied WSAPROTOCOL_INFO structure instead of the
 * parameter itself.
 */
#define FROM_PROTOCOL_INFO -1

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
#define SO_EXCLUSIVEADDRUSE ~SO_REUSEADDR /* disallow local address reuse */

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
 * WinSock 2 extension -- new options
 */
#define SO_GROUP_ID       0x2001      /* ID of a socket group */
#define SO_GROUP_PRIORITY 0x2002      /* the relative priority within a group*/
#define SO_MAX_MSG_SIZE   0x2003      /* maximum message size */
#define SO_PROTOCOL_INFOA 0x2004      /* WSAPROTOCOL_INFOA structure */
#define SO_PROTOCOL_INFOW 0x2005      /* WSAPROTOCOL_INFOW structure */
#ifdef UNICODE
#define SO_PROTOCOL_INFO  SO_PROTOCOL_INFOW
#else
#define SO_PROTOCOL_INFO  SO_PROTOCOL_INFOA
#endif /* UNICODE */
#define PVD_CONFIG        0x3001       /* configuration info for service provider */
#define SO_CONDITIONAL_ACCEPT 0x3002   /* enable true conditional accept: */
                                       /*  connection is not ack-ed to the */
                                       /*  other side until conditional */
                                       /*  function returns CF_ACCEPT */
/*
 * TCP options.
 */
#define TCP_NODELAY     0x0001

/*
 * Address families.
 */
#define AF_UNSPEC       0               /* unspecified */
/*
 * Although  AF_UNSPEC  is  defined for backwards compatibility, using
 * AF_UNSPEC for the "af" parameter when creating a socket is STRONGLY
 * DISCOURAGED.    The  interpretation  of  the  "protocol"  parameter
 * depends  on the actual address family chosen.  As environments grow
 * to  include  more  and  more  address families that use overlapping
 * protocol  values  there  is  more  and  more  chance of choosing an
 * undesired address family when AF_UNSPEC is used.
 */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_IPX          AF_NS           /* IPX protocols: IPX, SPX, etc. */
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
#define AF_FIREFOX      19              /* Protocols from Firefox */
#define AF_UNKNOWN1     20              /* Somebody is using this! */
#define AF_BAN          21              /* Banyan */
#define AF_ATM          22              /* Native ATM Services */
#define AF_INET6        23              /* Internetwork Version 6 */
#define AF_CLUSTER      24              /* Microsoft Wolfpack */
#define AF_12844        25              /* IEEE 1284.4 WG AF */
#define AF_IRDA         26              /* IrDA */
#define AF_NETDES       28              /* Network Designers OSI & gateway
                                           enabled protocols */
#define AF_TCNPROCESS   29
#define AF_TCNMESSAGE   30
#define AF_ICLFXBM      31
#define AF_MAX          32

#ifndef sockaddr
/*
 * Structure used by kernel to store most
 * addresses.
 */
struct sockaddr {
  u_short sa_family;              /* address family */
  char    sa_data[14];            /* up to 14 bytes of direct address */
};
#endif
/*
 * Portable socket structure (RFC 2553).
 */

/*
 * Desired design of maximum size and alignment.
 * These are implementation specific.
 */
#define _SS_MAXSIZE 128                  // Maximum size.
#define _SS_ALIGNSIZE sizeof(qword)  // Desired alignment.

/*
 * Definitions used for sockaddr_storage structure paddings design.
 */
#define _SS_PAD1SIZE _SS_ALIGNSIZE - sizeof (short)
#define _SS_PAD2SIZE _SS_MAXSIZE-sizeof(short)+_SS_PAD1SIZE+_SS_ALIGNSIZE

struct sockaddr_storage {
  short ss_family;               // Address family.
  char __ss_pad1[_SS_PAD1SIZE];  // 6 byte pad, this is to make
                                 // implementation specific pad up to
                                 // alignment field that follows explicit
                                 // in the data structure.
  qword __ss_align;            // Field to force desired structure.
  char __ss_pad2[_SS_PAD2SIZE];  // 112 byte pad to achieve desired size;
                                 // _SS_MAXSIZE value minus size of
                                 // ss_family, __ss_pad1, and
                                 // __ss_align fields is 112.
};

#ifndef sockproto
/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
  u_short sp_family;              /* address family */
  u_short sp_protocol;            /* protocol */
};
#endif

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
#define PF_ATM          AF_ATM
#define PF_INET6        AF_INET6
#define PF_MAX          AF_MAX

#ifndef linger
/*
 * Structure used for manipulating linger option.
 */
struct  linger {
  u_short l_onoff;                /* option on/off */
  u_short l_linger;               /* linger time */
};
#endif

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define SOL_SOCKET      0xffff          /* options for socket level */

/*
 * Maximum queue length specifiable by listen.
 */
#define SOMAXCONN       0x7fffffff

#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */

#define MSG_PARTIAL     0x8000          /* partial send or recv for message xport */

/*
 * WinSock 2 extension -- new flags for WSASend(), WSASendTo(), WSARecv() and
 *                          WSARecvFrom()
 */
#define MSG_INTERRUPT   0x10            /* send/recv in the interrupt context */
#define MSG_MAXIOVLEN   16

/*
 * Define constant based on rfc883, used by gethostbyxxxx() calls.
 */
#define MAXGETHOSTSTRUCT        1024

/*
 * WinSock 2 extension -- bit values and indices for FD_XXX network events
 */
#define FD_READ_BIT      0
#define FD_READ          1 << FD_READ_BIT
#define FD_WRITE_BIT     1
#define FD_WRITE         1 << FD_WRITE_BIT
#define FD_OOB_BIT       2
#define FD_OOB           1 << FD_OOB_BIT
#define FD_ACCEPT_BIT    3
#define FD_ACCEPT        1 << FD_ACCEPT_BIT
#define FD_CONNECT_BIT   4
#define FD_CONNECT       1 << FD_CONNECT_BIT
#define FD_CLOSE_BIT     5
#define FD_CLOSE         1 << FD_CLOSE_BIT
#define FD_QOS_BIT       6
#define FD_QOS           1 << FD_QOS_BIT
#define FD_GROUP_QOS_BIT 7
#define FD_GROUP_QOS     1 << FD_GROUP_QOS_BIT
#define FD_ROUTING_INTERFACE_CHANGE_BIT 8
#define FD_ROUTING_INTERFACE_CHANGE     1 << FD_ROUTING_INTERFACE_CHANGE_BIT
#define FD_ADDRESS_LIST_CHANGE_BIT 9
#define FD_ADDRESS_LIST_CHANGE     1 << FD_ADDRESS_LIST_CHANGE_BIT
#define FD_MAX_EVENTS    10
#define FD_ALL_EVENTS    1 << FD_MAX_EVENTS - 1

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

/*
 * Extended Windows Sockets error constant definitions
 */
#define WSASYSNOTREADY          WSABASEERR+91
#define WSAVERNOTSUPPORTED      WSABASEERR+92
#define WSANOTINITIALISED       WSABASEERR+93
#define WSAEDISCON              WSABASEERR+101
#define WSAENOMORE              WSABASEERR+102
#define WSAECANCELLED           WSABASEERR+103
#define WSAEINVALIDPROCTABLE    WSABASEERR+104
#define WSAEINVALIDPROVIDER     WSABASEERR+105
#define WSAEPROVIDERFAILEDINIT  WSABASEERR+106
#define WSASYSCALLFAILURE       WSABASEERR+107
#define WSASERVICE_NOT_FOUND    WSABASEERR+108
#define WSATYPE_NOT_FOUND       WSABASEERR+109
#define WSA_E_NO_MORE           WSABASEERR+110
#define WSA_E_CANCELLED         WSABASEERR+111
#define WSAEREFUSED             WSABASEERR+112

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

/* Non-recoverable errors, FORMERR, REFUSED, NOTIMP */
#define WSANO_RECOVERY          WSABASEERR+1003

/* Valid name, no data record of requested type */
#define WSANO_DATA              WSABASEERR+1004

/*
 * Define QOS related error return codes
 */
#define  WSA_QOS_RECEIVERS               WSABASEERR + 1005
         /* at least one Reserve has arrived */
#define  WSA_QOS_SENDERS                 WSABASEERR + 1006
         /* at least one Path has arrived */
#define  WSA_QOS_NO_SENDERS              WSABASEERR + 1007
         /* there are no senders */
#define  WSA_QOS_NO_RECEIVERS            WSABASEERR + 1008
         /* there are no receivers */
#define  WSA_QOS_REQUEST_CONFIRMED       WSABASEERR + 1009
         /* Reserve has been confirmed */
#define  WSA_QOS_ADMISSION_FAILURE       WSABASEERR + 1010
         /* error due to lack of resources */
#define  WSA_QOS_POLICY_FAILURE          WSABASEERR + 1011
         /* rejected for administrative reasons - bad credentials */
#define  WSA_QOS_BAD_STYLE               WSABASEERR + 1012
         /* unknown or conflicting style */
#define  WSA_QOS_BAD_OBJECT              WSABASEERR + 1013
         /* problem with some part of the filterspec or providerspecific
          * buffer in general */
#define  WSA_QOS_TRAFFIC_CTRL_ERROR      WSABASEERR + 1014
         /* problem with some part of the flowspec */
#define  WSA_QOS_GENERIC_ERROR           WSABASEERR + 1015
         /* general error */
#define  WSA_QOS_ESERVICETYPE            WSABASEERR + 1016
         /* invalid service type in flowspec */
#define  WSA_QOS_EFLOWSPEC               WSABASEERR + 1017
         /* invalid flowspec */
#define  WSA_QOS_EPROVSPECBUF            WSABASEERR + 1018
         /* invalid provider specific buffer */
#define  WSA_QOS_EFILTERSTYLE            WSABASEERR + 1019
         /* invalid filter style */
#define  WSA_QOS_EFILTERTYPE             WSABASEERR + 1020
         /* invalid filter type */
#define  WSA_QOS_EFILTERCOUNT            WSABASEERR + 1021
         /* incorrect number of filters */
#define  WSA_QOS_EOBJLENGTH              WSABASEERR + 1022
         /* invalid object length */
#define  WSA_QOS_EFLOWCOUNT              WSABASEERR + 1023
         /* incorrect number of flows */
#define  WSA_QOS_EUNKOWNPSOBJ            WSABASEERR + 1024
         /* unknown object in provider specific buffer */
#define  WSA_QOS_EPOLICYOBJ              WSABASEERR + 1025
         /* invalid policy object in provider specific buffer */
#define  WSA_QOS_EFLOWDESC               WSABASEERR + 1026
         /* invalid flow descriptor in the list */
#define  WSA_QOS_EPSFLOWSPEC             WSABASEERR + 1027
         /* inconsistent flow spec in provider specific buffer */
#define  WSA_QOS_EPSFILTERSPEC           WSABASEERR + 1028
         /* invalid filter spec in provider specific buffer */
#define  WSA_QOS_ESDMODEOBJ              WSABASEERR + 1029
         /* invalid shape discard mode object in provider specific buffer */
#define  WSA_QOS_ESHAPERATEOBJ           WSABASEERR + 1030
         /* invalid shaping rate object in provider specific buffer */
#define  WSA_QOS_RESERVED_PETYPE         WSABASEERR + 1031
         /* reserved policy element in provider specific buffer */

/*
 * WinSock error codes are also defined in winerror.h
 * Hence the IFDEF.
 */
#endif /* ifdef WSABASEERR */

/*
 * Compatibility macros.
 */
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND
#define TRY_AGAIN               WSATRY_AGAIN
#define NO_RECOVERY             WSANO_RECOVERY
#define NO_DATA                 WSANO_DATA
/* no address, look for MX record */
#define WSANO_ADDRESS           WSANO_DATA
#define NO_ADDRESS              WSANO_ADDRESS

/*
 * WinSock 2 extension -- new error codes and type definition
 */

#ifdef WIN32

#define WSAEVENT                HANDLE
#define WSAOVERLAPPED           OVERLAPPED

#define WSA_IO_PENDING          ERROR_IO_PENDING
#define WSA_IO_INCOMPLETE       ERROR_IO_INCOMPLETE
#define WSA_INVALID_HANDLE      ERROR_INVALID_HANDLE
#define WSA_INVALID_PARAMETER   ERROR_INVALID_PARAMETER
#define WSA_NOT_ENOUGH_MEMORY   ERROR_NOT_ENOUGH_MEMORY
#define WSA_OPERATION_ABORTED   ERROR_OPERATION_ABORTED

#define WSA_INVALID_EVENT       NULL
#define WSA_MAXIMUM_WAIT_EVENTS MAXIMUM_WAIT_OBJECTS
#define WSA_WAIT_FAILED         WAIT_FAILED
#define WSA_WAIT_EVENT_0        WAIT_OBJECT_0
#define WSA_WAIT_IO_COMPLETION  WAIT_IO_COMPLETION
#define WSA_WAIT_TIMEOUT        WAIT_TIMEOUT
#define WSA_INFINITE            INFINITE

#else /* WIN16 */

#define WSAEVENT dword

struct WSAOVERLAPPED {
  DWORD    Internal;
  DWORD    InternalHigh;
  DWORD    Offset;
  DWORD    OffsetHigh;
  WSAEVENT hEvent;
};

#define WSA_IO_PENDING          WSAEWOULDBLOCK
#define WSA_IO_INCOMPLETE       WSAEWOULDBLOCK
#define WSA_INVALID_HANDLE      WSAENOTSOCK
#define WSA_INVALID_PARAMETER   WSAEINVAL
#define WSA_NOT_ENOUGH_MEMORY   WSAENOBUFS
#define WSA_OPERATION_ABORTED   WSAEINTR

#define WSA_INVALID_EVENT       NULL
#define WSA_MAXIMUM_WAIT_EVENTS MAXIMUM_WAIT_OBJECTS
#define WSA_WAIT_FAILED         -1L
#define WSA_WAIT_EVENT_0        0
#define WSA_WAIT_TIMEOUT        0x102L
#define WSA_INFINITE            -1L

#endif  /* WIN32 */

/*
 * WinSock 2 extension -- WSABUF and QOS struct, include qos.h
 * to pull in FLOWSPEC and related definitions
 */
#include <qos.h>
struct WSABUF {
  u_long      len;     /* the length of the buffer */
  dword/*char  **/  buf;     /* the pointer to the buffer */
};

struct QOS
{
  FLOWSPEC      SendingFlowspec;       /* the flow spec for data sending */
  FLOWSPEC      ReceivingFlowspec;     /* the flow spec for data receiving */
  WSABUF        ProviderSpecific;      /* additional provider specific stuff */
};

/*
 * WinSock 2 extension -- manifest constants for return values of the condition function
 */
#define CF_ACCEPT       0x0000
#define CF_REJECT       0x0001
#define CF_DEFER        0x0002

/*
 * WinSock 2 extension -- manifest constants for shutdown()
 */
#define SD_RECEIVE      0x00
#define SD_SEND         0x01
#define SD_BOTH         0x02

/*
 * WinSock 2 extension -- data type and manifest constants for socket groups
 */
#define GROUP unsigned int

#define SG_UNCONSTRAINED_GROUP   0x01
#define SG_CONSTRAINED_GROUP     0x02

/*
 * WinSock 2 extension -- data type for WSAEnumNetworkEvents()
 */
struct WSANETWORKEVENTS {
  long lNetworkEvents;
  int iErrorCode[FD_MAX_EVENTS];
};

/*
 * WinSock 2 extension -- WSAPROTOCOL_INFO structure and associated
 * manifest constants
 */

#ifndef GUID_DEFINED
#include <guiddef.h>
#endif /* GUID_DEFINED */

#define MAX_PROTOCOL_CHAIN 7

#define BASE_PROTOCOL      1
#define LAYERED_PROTOCOL   0

struct WSAPROTOCOLCHAIN {
  int ChainLen;                                 /* the length of the chain,     */
                                                /* length = 0 means layered protocol, */
                                                /* length = 1 means base protocol, */
                                                /* length > 1 means protocol chain */
  DWORD ChainEntries[MAX_PROTOCOL_CHAIN];       /* a list of dwCatalogEntryIds */
};

#define WSAPROTOCOL_LEN  255

struct WSAPROTOCOL_INFOA {
  DWORD dwServiceFlags1;
  DWORD dwServiceFlags2;
  DWORD dwServiceFlags3;
  DWORD dwServiceFlags4;
  DWORD dwProviderFlags;
  GUID ProviderId;
  DWORD dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int iVersion;
  int iAddressFamily;
  int iMaxSockAddr;
  int iMinSockAddr;
  int iSocketType;
  int iProtocol;
  int iProtocolMaxOffset;
  int iNetworkByteOrder;
  int iSecurityScheme;
  DWORD dwMessageSize;
  DWORD dwProviderReserved;
  CHAR   szProtocol[WSAPROTOCOL_LEN+1];
};
struct WSAPROTOCOL_INFOW {
  DWORD dwServiceFlags1;
  DWORD dwServiceFlags2;
  DWORD dwServiceFlags3;
  DWORD dwServiceFlags4;
  DWORD dwProviderFlags;
  GUID ProviderId;
  DWORD dwCatalogEntryId;
  WSAPROTOCOLCHAIN ProtocolChain;
  int iVersion;
  int iAddressFamily;
  int iMaxSockAddr;
  int iMinSockAddr;
  int iSocketType;
  int iProtocol;
  int iProtocolMaxOffset;
  int iNetworkByteOrder;
  int iSecurityScheme;
  DWORD dwMessageSize;
  DWORD dwProviderReserved;
  WCHAR  szProtocol[WSAPROTOCOL_LEN+1];
};
#ifdef UNICODE
#define WSAPROTOCOL_INFO WSAPROTOCOL_INFOW
#else
#define WSAPROTOCOL_INFO WSAPROTOCOL_INFOA
#endif /* UNICODE */

/* Flag bit definitions for dwProviderFlags */
#define PFL_MULTIPLE_PROTO_ENTRIES          0x00000001
#define PFL_RECOMMENDED_PROTO_ENTRY         0x00000002
#define PFL_HIDDEN                          0x00000004
#define PFL_MATCHES_PROTOCOL_ZERO           0x00000008

/* Flag bit definitions for dwServiceFlags1 */
#define XP1_CONNECTIONLESS                  0x00000001
#define XP1_GUARANTEED_DELIVERY             0x00000002
#define XP1_GUARANTEED_ORDER                0x00000004
#define XP1_MESSAGE_ORIENTED                0x00000008
#define XP1_PSEUDO_STREAM                   0x00000010
#define XP1_GRACEFUL_CLOSE                  0x00000020
#define XP1_EXPEDITED_DATA                  0x00000040
#define XP1_CONNECT_DATA                    0x00000080
#define XP1_DISCONNECT_DATA                 0x00000100
#define XP1_SUPPORT_BROADCAST               0x00000200
#define XP1_SUPPORT_MULTIPOINT              0x00000400
#define XP1_MULTIPOINT_CONTROL_PLANE        0x00000800
#define XP1_MULTIPOINT_DATA_PLANE           0x00001000
#define XP1_QOS_SUPPORTED                   0x00002000
#define XP1_INTERRUPT                       0x00004000
#define XP1_UNI_SEND                        0x00008000
#define XP1_UNI_RECV                        0x00010000
#define XP1_IFS_HANDLES                     0x00020000
#define XP1_PARTIAL_MESSAGE                 0x00040000

#define BIGENDIAN                           0x0000
#define LITTLEENDIAN                        0x0001

#define SECURITY_PROTOCOL_NONE              0x0000

/*
 * WinSock 2 extension -- manifest constants for WSAJoinLeaf()
 */
#define JL_SENDER_ONLY    0x01
#define JL_RECEIVER_ONLY  0x02
#define JL_BOTH           0x04

/*
 * WinSock 2 extension -- manifest constants for WSASocket()
 */
#define WSA_FLAG_OVERLAPPED           0x01
#define WSA_FLAG_MULTIPOINT_C_ROOT    0x02
#define WSA_FLAG_MULTIPOINT_C_LEAF    0x04
#define WSA_FLAG_MULTIPOINT_D_ROOT    0x08
#define WSA_FLAG_MULTIPOINT_D_LEAF    0x10

/*
 * WinSock 2 extension -- manifest constants for WSAIoctl()
 */
#define IOC_UNIX                      0x00000000
#define IOC_WS2                       0x08000000
#define IOC_PROTOCOL                  0x10000000
#define IOC_VENDOR                    0x18000000

#define _WSAIO(x,y)                   IOC_VOID|x|y
#define _WSAIOR(x,y)                  IOC_OUT|x|y
#define _WSAIOW(x,y)                  IOC_IN|x|y
#define _WSAIORW(x,y)                 IOC_INOUT|x|y

#define SIO_ASSOCIATE_HANDLE          _WSAIOW(IOC_WS2,1)
#define SIO_ENABLE_CIRCULAR_QUEUEING  _WSAIO(IOC_WS2,2)
#define SIO_FIND_ROUTE                _WSAIOR(IOC_WS2,3)
#define SIO_FLUSH                     _WSAIO(IOC_WS2,4)
#define SIO_GET_BROADCAST_ADDRESS     _WSAIOR(IOC_WS2,5)
#define SIO_GET_EXTENSION_FUNCTION_POINTER  _WSAIORW(IOC_WS2,6)
#define SIO_GET_QOS                   _WSAIORW(IOC_WS2,7)
#define SIO_GET_GROUP_QOS             _WSAIORW(IOC_WS2,8)
#define SIO_MULTIPOINT_LOOPBACK       _WSAIOW(IOC_WS2,9)
#define SIO_MULTICAST_SCOPE           _WSAIOW(IOC_WS2,10)
#define SIO_SET_QOS                   _WSAIOW(IOC_WS2,11)
#define SIO_SET_GROUP_QOS             _WSAIOW(IOC_WS2,12)
#define SIO_TRANSLATE_HANDLE          _WSAIORW(IOC_WS2,13)
#define SIO_ROUTING_INTERFACE_QUERY   _WSAIORW(IOC_WS2,20)
#define SIO_ROUTING_INTERFACE_CHANGE  _WSAIOW(IOC_WS2,21)
#define SIO_ADDRESS_LIST_QUERY        _WSAIOR(IOC_WS2,22)
#define SIO_ADDRESS_LIST_CHANGE       _WSAIO(IOC_WS2,23)
#define SIO_QUERY_TARGET_PNP_HANDLE   _WSAIOR(IOC_WS2,24)
#define SIO_ADDRESS_LIST_SORT         _WSAIORW(IOC_WS2,25)

/*
 * WinSock 2 extension -- manifest constants and associated structures
 * for WSANSPIoctl()
 */
#define SIO_NSP_NOTIFY_CHANGE         _WSAIOW(IOC_WS2,25)

enum WSACOMPLETIONTYPE{
  NSP_NOTIFY_IMMEDIATELY = 0,
  NSP_NOTIFY_HWND,
  NSP_NOTIFY_EVENT,
  NSP_NOTIFY_PORT,
  NSP_NOTIFY_APC,
};

struct WSACOMPLETION {
  dword Type;
  union {
    struct {
      HWND hWnd;
      UINT uMsg;
      WPARAM context;
    } WindowMessage;
    struct {
      dword lpOverlapped;
    } Event;
    struct {
      dword lpOverlapped;
      dword lpfnCompletionProc;
    } Apc;
    struct {
      dword lpOverlapped;
      HANDLE hPort;
      ULONG_PTR Key;
    } Port;
  }Parameters;
};

/*
 * WinSock 2 extension -- manifest constants for SIO_TRANSLATE_HANDLE ioctl
 */
#define TH_NETDEV        0x00000001
#define TH_TAPI          0x00000002

/*
 * Microsoft Windows Extended data types required for the functions to
 * convert   back  and  forth  between  binary  and  string  forms  of
 * addresses.
 */
#define SOCKADDR sockaddr
#define SOCKADDR_STORAGE sockaddr_storage

/*
 * Manifest constants and type definitions related to name resolution and
 * registration (RNR) API
 */
#ifndef _tagBLOB_DEFINED
#define _tagBLOB_DEFINED
#define _BLOB_DEFINED
#define _LPBLOB_DEFINED
struct BLOB {
  ULONG cbSize ;
  dword/*BYTE **/pBlobData ;
};
#endif

/*
 * Service Install Flags
 */
#define SERVICE_MULTIPLE       0x00000001

/*
 *& Name Spaces
 */
#define NS_ALL                      0
#define NS_SAP                      1
#define NS_NDS                      2
#define NS_PEER_BROWSE              3
#define NS_SLP                      5
#define NS_DHCP                     6
#define NS_TCPIP_LOCAL              10
#define NS_TCPIP_HOSTS              11
#define NS_DNS                      12
#define NS_NETBT                    13
#define NS_WINS                     14
#define NS_NLA                      15    /* Network Location Awareness */
#define NS_NBP                      20
#define NS_MS                       30
#define NS_STDA                     31
#define NS_NTDS                     32
#define NS_X500                     40
#define NS_NIS                      41
#define NS_NISPLUS                  42
#define NS_WRQ                      50
#define NS_NETDES                   60    /* Network Designers Limited */

/*
 * Resolution flags for WSAGetAddressByName().
 * Note these are also used by the 1.1 API GetAddressByName, so
 * leave them around.
 */
#define RES_UNUSED_1                0x00000001
#define RES_FLUSH_CACHE             0x00000002
#ifndef RES_SERVICE
#define RES_SERVICE                 0x00000004
#endif /* RES_SERVICE */

/*
 * Well known value names for Service Types
 */
#define SERVICE_TYPE_VALUE_IPXPORTA      "IpxSocket"
#define SERVICE_TYPE_VALUE_IPXPORTW     L"IpxSocket"
#define SERVICE_TYPE_VALUE_SAPIDA        "SapId"
#define SERVICE_TYPE_VALUE_SAPIDW       L"SapId"
#define SERVICE_TYPE_VALUE_TCPPORTA      "TcpPort"
#define SERVICE_TYPE_VALUE_TCPPORTW     L"TcpPort"
#define SERVICE_TYPE_VALUE_UDPPORTA      "UdpPort"
#define SERVICE_TYPE_VALUE_UDPPORTW     L"UdpPort"
#define SERVICE_TYPE_VALUE_OBJECTIDA     "ObjectId"
#define SERVICE_TYPE_VALUE_OBJECTIDW    L"ObjectId"

#ifdef UNICODE
#define SERVICE_TYPE_VALUE_SAPID        SERVICE_TYPE_VALUE_SAPIDW
#define SERVICE_TYPE_VALUE_TCPPORT      SERVICE_TYPE_VALUE_TCPPORTW
#define SERVICE_TYPE_VALUE_UDPPORT      SERVICE_TYPE_VALUE_UDPPORTW
#define SERVICE_TYPE_VALUE_OBJECTID     SERVICE_TYPE_VALUE_OBJECTIDW
#else /* not UNICODE */
#define SERVICE_TYPE_VALUE_SAPID        SERVICE_TYPE_VALUE_SAPIDA
#define SERVICE_TYPE_VALUE_TCPPORT      SERVICE_TYPE_VALUE_TCPPORTA
#define SERVICE_TYPE_VALUE_UDPPORT      SERVICE_TYPE_VALUE_UDPPORTA
#define SERVICE_TYPE_VALUE_OBJECTID     SERVICE_TYPE_VALUE_OBJECTIDA
#endif

#ifndef __CSADDR_DEFINED__
#define __CSADDR_DEFINED__

/*
 * SockAddr Information
 */
struct SOCKET_ADDRESS {
  dword lpSockaddr ;
  INT iSockaddrLength ;
};

/*
 * CSAddr Information
 */
struct CSADDR_INFO {
  SOCKET_ADDRESS LocalAddr ;
  SOCKET_ADDRESS RemoteAddr ;
  INT iSocketType ;
  INT iProtocol ;
};
#endif /* __CSADDR_DEFINED__ */

/*
 * Address list returned via SIO_ADDRESS_LIST_QUERY
 */
struct SOCKET_ADDRESS_LIST {
  INT             iAddressCount;
  SOCKET_ADDRESS  Address[1];
};

/*
 *  Address Family/Protocol Tuples
 */
struct AFPROTOCOLS {
  INT iAddressFamily;
  INT iProtocol;
};

/*
 * The comparators
 */
enum WSAECOMPARATOR{
  COMP_EQUAL = 0,
  COMP_NOTLESS
};

struct WSAVERSION
{
  DWORD           dwVersion;
  dword  ecHow;
};

struct WSAQUERYSET
{
  DWORD           dwSize;
  LPSTR           lpszServiceInstanceName;
  dword          lpServiceClassId;
  dword    lpVersion;
  LPSTR           lpszComment;
  DWORD           dwNameSpace;
  dword          lpNSProviderId;
  LPSTR           lpszContext;
  DWORD           dwNumberOfProtocols;
  dword   lpafpProtocols;
  LPSTR           lpszQueryString;
  DWORD           dwNumberOfCsAddrs;
  dword   lpcsaBuffer;
  DWORD           dwOutputFlags;
  dword          lpBlob;
};
#define WSAQUERYSETW WSAQUERYSET
#define WSAQUERYSETA WSAQUERYSET

#define LUP_DEEP                0x0001
#define LUP_CONTAINERS          0x0002
#define LUP_NOCONTAINERS        0x0004
#define LUP_NEAREST             0x0008
#define LUP_RETURN_NAME         0x0010
#define LUP_RETURN_TYPE         0x0020
#define LUP_RETURN_VERSION      0x0040
#define LUP_RETURN_COMMENT      0x0080
#define LUP_RETURN_ADDR         0x0100
#define LUP_RETURN_BLOB         0x0200
#define LUP_RETURN_ALIASES      0x0400
#define LUP_RETURN_QUERY_STRING 0x0800
#define LUP_RETURN_ALL          0x0FF0
#define LUP_RES_SERVICE         0x8000
#define LUP_FLUSHCACHE       0x1000
#define LUP_FLUSHPREVIOUS    0x2000

/*
 * Return flags
 */
#define  RESULT_IS_ALIAS      0x0001
#define  RESULT_IS_ADDED      0x0010
#define  RESULT_IS_CHANGED    0x0020
#define  RESULT_IS_DELETED    0x0040

/*
 * Service Address Registration and Deregistration Data Types.
 */
enum WSAESETSERVICEOP{
  RNRSERVICE_REGISTER=0,
  RNRSERVICE_DEREGISTER,
  RNRSERVICE_DELETE
};

/*
 * Service Installation/Removal Data Types.
 */
struct WSANSCLASSINFO
{
  LPSTR   lpszName;
  DWORD   dwNameSpace;
  DWORD   dwValueType;
  DWORD   dwValueSize;
  LPVOID  lpValue;
};
#define WSANSCLASSINFOW WSANSCLASSINFO
#define WSANSCLASSINFOA WSANSCLASSINFO

struct WSASERVICECLASSINFO
{
  dword              lpServiceClassId;
  LPSTR               lpszServiceClassName;
  DWORD               dwCount;
  dword   lpClassInfos;
};
#define WSASERVICECLASSINFOW WSASERVICECLASSINFO
#define WSASERVICECLASSINFOA WSASERVICECLASSINFO

struct WSANAMESPACE_INFO{
  GUID                NSProviderId;
  DWORD               dwNameSpace;
  BOOL                fActive;
  DWORD               dwVersion;
  LPSTR               lpszIdentifier;
};
#define WSANAMESPACE_INFOW WSANAMESPACE_INFO
#define WSANAMESPACE_INFOA WSANAMESPACE_INFO

/* Socket function prototypes */
extern WINAPI "WS2_32.DLL"{
	SOCKET accept(SOCKET s,dword addr,dword addrlen);
	int bind(SOCKET s,dword name,int namelen);
	int closesocket(SOCKET s);
	int connect(SOCKET s,dword name,int namelen);
	int ioctlsocket(SOCKET s,long cmd,dword argp);
	int getpeername(SOCKET s,dword name,dword namelen);
	int getsockname(SOCKET s,dword name,dword namelen);
	int getsockopt(SOCKET s,int level,int optname,dword optval,dword optlen);
	u_long htonl(u_long hostlong);
	u_short htons(u_short hostshort);
	unsigned long inet_addr(dword cp);
	dword inet_ntoa(struct in_addr);
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
	dword gethostbyaddr(dword addr,int len,int type);
	dword gethostbyname(dword name);
	int gethostname(dword name,int namelen);
	dword getservbyport(int port,dword proto);
	dword getservbyname(dword name,dword proto);
	dword getprotobynumber(int number);
	dword getprotobyname(dword name);
	int WSAStartup(WORD wVersionRequested,dword lpWSAData);
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
	SOCKET WSAAccept(SOCKET s,dword addr,LPINT addrlen,dword lpfnCondition,DWORD_PTR dwCallbackData);
	BOOL WSACloseEvent(WSAEVENT hEvent);
	int WSAConnect(SOCKET s,dword name,int namelen,dword lpCallerData,dword lpCalleeData,dword lpSQOS,dword lpGQOS);
	dword WSACreateEvent(void);
	int WSADuplicateSocketA(SOCKET s,DWORD dwProcessId,dword lpProtocolInfo);
	int WSADuplicateSocketW(SOCKET s,DWORD dwProcessId,dword lpProtocolInfo);
#ifdef UNICODE
#define WSADuplicateSocket  WSADuplicateSocketW
#else
#define WSADuplicateSocket  WSADuplicateSocketA
#endif /* !UNICODE */
	int WSAEnumNetworkEvents(SOCKET s,WSAEVENT hEventObject,dword lpNetworkEvents);
	int WSAEnumProtocolsA(LPINT lpiProtocols,dword lpProtocolBuffer,LPDWORD lpdwBufferLength);
	int WSAEnumProtocolsW(LPINT lpiProtocols,dword lpProtocolBuffer,LPDWORD lpdwBufferLength);
#ifdef UNICODE
#define WSAEnumProtocols  WSAEnumProtocolsW
#else
#define WSAEnumProtocols  WSAEnumProtocolsA
#endif /* !UNICODE */
	int WSAEventSelect(SOCKET s,WSAEVENT hEventObject,long lNetworkEvents);
	BOOL WSAGetOverlappedResult(SOCKET s,dword lpOverlapped,LPDWORD lpcbTransfer,BOOL fWait,LPDWORD lpdwFlags);
	BOOL WSAGetQOSByName(SOCKET s,dword lpQOSName,dword lpQOS);
	int WSAHtonl(SOCKET s,u_long hostlong,dword lpnetlong);
	int WSAHtons(SOCKET s,u_short hostshort,dword lpnetshort);
	int WSAIoctl(SOCKET s,DWORD dwIoControlCode,LPVOID lpvInBuffer,DWORD cbInBuffer,
		LPVOID lpvOutBuffer,DWORD cbOutBuffer,LPDWORD lpcbBytesReturned,
		dword lpOverlapped,dword lpCompletionRoutine);
	SOCKET WSAJoinLeaf(SOCKET s,dword name,int namelen,dword lpCallerData,
		dword lpCalleeData,dword lpSQOS,dword lpGQOS,DWORD dwFlags);
	int WSANtohl(SOCKET s,u_long netlong,dword lphostlong);
	int WSANtohs(SOCKET s,u_short netshort,dword lphostshort);
	int WSARecv(SOCKET s,dword lpBuffers,DWORD dwBufferCount,dword lpNumberOfBytesRecvd,
		LPDWORD lpFlags,dword lpOverlapped,dword lpCompletionRoutine);
	int WSARecvDisconnect(SOCKET s,dword lpInboundDisconnectData);
	int WSARecvFrom(SOCKET s,dword lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesRecvd,
		LPDWORD lpFlags,dword lpFrom,dword lpFromlen,dword lpOverlapped,dword lpCompletionRoutine);
	BOOL WSAResetEvent(WSAEVENT hEvent);
	int WSASend(SOCKET s,dword lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesSent,
		DWORD dwFlags,dword lpOverlapped,dword lpCompletionRoutine);
	int WSASendDisconnect(SOCKET s,dword lpOutboundDisconnectData);
	int WSASendTo(SOCKET s,dword lpBuffers,DWORD dwBufferCount,LPDWORD lpNumberOfBytesSent,
		DWORD dwFlags,dword lpTo,int iTolen,dword lpOverlapped,dword lpCompletionRoutine);
	BOOL WSASetEvent(WSAEVENT hEvent);
	SOCKET WSASocketA(int af,int type,int protocol,dword lpProtocolInfo,GROUP g,DWORD dwFlags);
	SOCKET WSASocketW(int af,int type,int protocol,dword lpProtocolInfo,GROUP g,DWORD dwFlags);
#ifdef UNICODE
#define WSASocket  WSASocketW
#else
#define WSASocket  WSASocketA
#endif /* !UNICODE */
	DWORD WSAWaitForMultipleEvents(DWORD cEvents,dword lphEvents,BOOL fWaitAll,
		DWORD dwTimeout,BOOL fAlertable);
	INT WSAAddressToStringA(dword lpsaAddress,DWORD dwAddressLength,dword lpProtocolInfo,
		dword lpszAddressString,DWORD lpdwAddressStringLength);
	INT WSAAddressToStringW(dword lpsaAddress,DWORD dwAddressLength,dword lpProtocolInfo,
		dword lpszAddressString,DWORD lpdwAddressStringLength);
#ifdef UNICODE
#define WSAAddressToString  WSAAddressToStringW
#else
#define WSAAddressToString  WSAAddressToStringA
#endif /* !UNICODE */
	INT WSAStringToAddressA(LPSTR AddressString,INT AddressFamily,dword lpProtocolInfo,
		dword lpAddress,dword lpAddressLength);
	INT WSAStringToAddressW(LPWSTR AddressString,INT AddressFamily,
		dword lpProtocolInfo,dword lpAddress,dword lpAddressLength);
#ifdef UNICODE
#define WSAStringToAddress  WSAStringToAddressW
#else
#define WSAStringToAddress  WSAStringToAddressA
#endif /* !UNICODE */
	INT WSALookupServiceBeginA(dword lpqsRestrictions,DWORD dwControlFlags,dword lphLookup);
	INT WSALookupServiceBeginW(dword lpqsRestrictions,DWORD dwControlFlags,dword lphLookup);
#ifdef UNICODE
#define WSALookupServiceBegin  WSALookupServiceBeginW
#else
#define WSALookupServiceBegin  WSALookupServiceBeginA
#endif /* !UNICODE */
	INT WSALookupServiceNextA(HANDLE hLookup,DWORD dwControlFlags,DWORD lpdwBufferLength,dword lpqsResults);
	INT WSALookupServiceNextW(HANDLE hLookup,DWORD dwControlFlags,DWORD lpdwBufferLength,dword lpqsResults);
#ifdef UNICODE
#define WSALookupServiceNext  WSALookupServiceNextW
#else
#define WSALookupServiceNext  WSALookupServiceNextA
#endif /* !UNICODE */
	INT WSANSPIoctl(HANDLE hLookup,DWORD dwControlCode,LPVOID lpvInBuffer,DWORD cbInBuffer,
		LPVOID lpvOutBuffer,DWORD cbOutBuffer,DWORD lpcbBytesReturned,dword lpCompletion);
	INT WSALookupServiceEnd(HANDLE hLookup);
	INT WSAInstallServiceClassA(dword lpServiceClassInfo);
	INT WSAInstallServiceClassW(dword lpServiceClassInfo);
#ifdef UNICODE
#define WSAInstallServiceClass  WSAInstallServiceClassW
#else
#define WSAInstallServiceClass  WSAInstallServiceClassA
#endif /* !UNICODE */
	INT WSARemoveServiceClass(dword lpServiceClassId);
	INT WSAGetServiceClassInfoA(dword lpProviderId,dword lpServiceClassId,
		DWORD lpdwBufSize,dword lpServiceClassInfo);
	INT WSAGetServiceClassInfoW(dword lpProviderId,dword lpServiceClassId,
		DWORD lpdwBufSize,dword lpServiceClassInfo);
#ifdef UNICODE
#define WSAGetServiceClassInfo  WSAGetServiceClassInfoW
#else
#define WSAGetServiceClassInfo  WSAGetServiceClassInfoA
#endif /* !UNICODE */
	INT WSAEnumNameSpaceProvidersA(DWORD lpdwBufferLength,dword lpnspBuffer);
	INT WSAEnumNameSpaceProvidersW(DWORD lpdwBufferLength,dword lpnspBuffer);
#ifdef UNICODE
#define WSAEnumNameSpaceProviders  WSAEnumNameSpaceProvidersW
#else
#define WSAEnumNameSpaceProviders  WSAEnumNameSpaceProvidersA
#endif /* !UNICODE */
	INT WSAGetServiceClassNameByClassIdA(dword lpServiceClassId,LPSTR lpszServiceClassName,
		DWORD lpdwBufferLength);
	INT WSAGetServiceClassNameByClassIdW(dword lpServiceClassId,LPWSTR lpszServiceClassName,
		DWORD lpdwBufferLength);
#ifdef UNICODE
#define WSAGetServiceClassNameByClassId  WSAGetServiceClassNameByClassIdW
#else
#define WSAGetServiceClassNameByClassId  WSAGetServiceClassNameByClassIdA
#endif /* !UNICODE */
	INT WSASetServiceA(dword lpqsRegInfo,dword essoperation,DWORD dwControlFlags);
	INT WSASetServiceW(dword lpqsRegInfo,dword essoperation,DWORD dwControlFlags);
#ifdef UNICODE
#define WSASetService  WSASetServiceW
#else
#define WSASetService  WSASetServiceA
#endif /* !UNICODE */
	INT WSAProviderConfigChange(dword lpNotificationHandle,dword lpOverlapped,dword lpCompletionRoutine);
	int __WSAFDIsSet(SOCKET, dword);
}
/* Microsoft Windows Extended data types */
#define SOCKADDR_IN sockaddr_in
#define LINGER linger
#define IN_ADDR in_addr
//#define FD_SET fd_set
#define HOSTENT hostent
#define SERVENT servent
#define PROTOENT protoent
#define TIMEVAL timeval
#ifndef WSAMAKEASYNCREPLY
#define h_errno         WSAGetLastError

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
 * to a WSAAsyncGetXByY().
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
#endif

:void pascal FD_CLR(dword fd, set)
uses EDX ESI
{
	EDX=set;
	FOR(ESI=0;ESI<EDX.fd_set.fd_count;ESI++){
		IF(EDX.fd_set.fd_array[ESI*4]==fd){
			WHILE(EDX.fd_set.fd_count-1>=ESI){
				EDX.fd_set.fd_array[ESI*4]=EDX.fd_set.fd_array[ESI*4+sizeof(int)];
				ESI++;
			}
			EDX.fd_set.fd_count--;
			BREAK;
		}
	}
}

:void pascal FD_SET(dword fd, set)
uses EDX ESI
{
	EDX=set;
	FOR(ESI=0;ESI< EDX.fd_set.fd_count;ESI++){
		IF(EDX.fd_set.fd_array[ESI*4]==fd)BREAK;
	}
	IF(ESI==EDX.fd_set.fd_count){
		IF(EDX.fd_set.fd_count<FD_SETSIZE){
			EDX.fd_set.fd_array[ESI*4]=fd;
			EDX.fd_set.fd_count++;
		}
	}
}

:void FD_ZERO(EAX)
{
	EAX.fd_set.fd_count=0;
}

#define FD_ISSET(fd,set) __WSAFDIsSet(fd,set)

/*
#define FD_CLR(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set FAR *)(set))->fd_count ; __i++) { \
        if (((fd_set FAR *)(set))->fd_array[__i] == fd) { \
            while (__i < ((fd_set FAR *)(set))->fd_count-1) { \
                ((fd_set FAR *)(set))->fd_array[__i] = \
                    ((fd_set FAR *)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((fd_set FAR *)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)

#define FD_SET(fd, set) do { \
    u_int __i; \
    for (__i = 0; __i < ((fd_set FAR *)(set))->fd_count; __i++) { \
        if (((fd_set FAR *)(set))->fd_array[__i] == (fd)) { \
            break; \
        } \
    } \
    if (__i == ((fd_set FAR *)(set))->fd_count) { \
        if (((fd_set FAR *)(set))->fd_count < FD_SETSIZE) { \
            ((fd_set FAR *)(set))->fd_array[__i] = (fd); \
            ((fd_set FAR *)(set))->fd_count++; \
        } \
    } \
} while(0)

#define FD_ZERO(set) (((fd_set FAR *)(set))->fd_count=0)

#define FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (fd_set FAR *)(set))
*/


#if !defined(WIN32) && !defined(_WIN64)
#pragma pack(pop)
#endif
#ifdef IPV6STRICT
#include <wsipv6ok.h>
#endif // IPV6STRICT

#endif  /* _WINSOCK2API_ */
