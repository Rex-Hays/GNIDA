/*++
Copyright (c) Microsoft Corporation. All rights reserved.
Module Name:
    winnetwk.h
Abstract:
    Standard WINNET Header File for WIN32
Environment:
    User Mode -Win32
Notes:
    optional-notes
--*/

#ifndef _WINNETWK_
#define _WINNETWK_

// Network types
#define     WNNC_NET_MSNET       0x00010000
#define     WNNC_NET_LANMAN      0x00020000
#define     WNNC_NET_NETWARE     0x00030000
#define     WNNC_NET_VINES       0x00040000
#define     WNNC_NET_10NET       0x00050000
#define     WNNC_NET_LOCUS       0x00060000
#define     WNNC_NET_SUN_PC_NFS  0x00070000
#define     WNNC_NET_LANSTEP     0x00080000
#define     WNNC_NET_9TILES      0x00090000
#define     WNNC_NET_LANTASTIC   0x000A0000
#define     WNNC_NET_AS400       0x000B0000
#define     WNNC_NET_FTP_NFS     0x000C0000
#define     WNNC_NET_PATHWORKS   0x000D0000
#define     WNNC_NET_LIFENET     0x000E0000
#define     WNNC_NET_POWERLAN    0x000F0000
#define     WNNC_NET_BWNFS       0x00100000
#define     WNNC_NET_COGENT      0x00110000
#define     WNNC_NET_FARALLON    0x00120000
#define     WNNC_NET_APPLETALK   0x00130000
#define     WNNC_NET_INTERGRAPH  0x00140000
#define     WNNC_NET_SYMFONET    0x00150000
#define     WNNC_NET_CLEARCASE   0x00160000
#define     WNNC_NET_FRONTIER    0x00170000
#define     WNNC_NET_BMC         0x00180000
#define     WNNC_NET_DCE         0x00190000
#define     WNNC_NET_AVID        0x001A0000
#define     WNNC_NET_DOCUSPACE   0x001B0000
#define     WNNC_NET_MANGOSOFT   0x001C0000
#define     WNNC_NET_SERNET      0x001D0000
#define     WNNC_NET_RIVERFRONT1 0X001E0000
#define     WNNC_NET_RIVERFRONT2 0x001F0000
#define     WNNC_NET_DECORB      0x00200000
#define     WNNC_NET_PROTSTOR    0x00210000
#define     WNNC_NET_FJ_REDIR    0x00220000
#define     WNNC_NET_DISTINCT    0x00230000
#define     WNNC_NET_TWINS       0x00240000
#define     WNNC_NET_RDR2SAMPLE  0x00250000
#define     WNNC_NET_CSC         0x00260000
#define     WNNC_NET_3IN1        0x00270000
#define     WNNC_NET_EXTENDNET   0x00290000
#define     WNNC_NET_STAC        0x002A0000
#define     WNNC_NET_FOXBAT      0x002B0000
#define     WNNC_NET_YAHOO       0x002C0000
#define     WNNC_NET_EXIFS       0x002D0000
#define     WNNC_NET_DAV         0x002E0000
#define     WNNC_NET_KNOWARE     0x002F0000
#define     WNNC_NET_OBJECT_DIRE 0x00300000
#define     WNNC_NET_MASFAX      0x00310000
#define     WNNC_NET_HOB_NFS     0x00320000
#define     WNNC_NET_SHIVA       0x00330000
#define     WNNC_NET_IBMAL       0x00340000
#define     WNNC_NET_LOCK        0x00350000
#define     WNNC_NET_TERMSRV     0x00360000
#define     WNNC_CRED_MANAGER   0xFFFF0000

//  Network Resources.
#define RESOURCE_CONNECTED      0x00000001
#define RESOURCE_GLOBALNET      0x00000002
#define RESOURCE_REMEMBERED     0x00000003
#define RESOURCE_RECENT         0x00000004
#define RESOURCE_CONTEXT        0x00000005
#define RESOURCETYPE_ANY        0x00000000
#define RESOURCETYPE_DISK       0x00000001
#define RESOURCETYPE_PRINT      0x00000002
#define RESOURCETYPE_RESERVED   0x00000008
#define RESOURCETYPE_UNKNOWN    0xFFFFFFFF

#define RESOURCEUSAGE_CONNECTABLE   0x00000001
#define RESOURCEUSAGE_CONTAINER     0x00000002
#define RESOURCEUSAGE_NOLOCALDEVICE 0x00000004
#define RESOURCEUSAGE_SIBLING       0x00000008
#define RESOURCEUSAGE_ATTACHED      0x00000010
#define RESOURCEUSAGE_ALL           RESOURCEUSAGE_CONNECTABLE | RESOURCEUSAGE_CONTAINER | RESOURCEUSAGE_ATTACHED
#define RESOURCEUSAGE_RESERVED      0x80000000

#define RESOURCEDISPLAYTYPE_GENERIC        0x00000000
#define RESOURCEDISPLAYTYPE_DOMAIN         0x00000001
#define RESOURCEDISPLAYTYPE_SERVER         0x00000002
#define RESOURCEDISPLAYTYPE_SHARE          0x00000003
#define RESOURCEDISPLAYTYPE_FILE           0x00000004
#define RESOURCEDISPLAYTYPE_GROUP          0x00000005
#define RESOURCEDISPLAYTYPE_NETWORK        0x00000006
#define RESOURCEDISPLAYTYPE_ROOT           0x00000007
#define RESOURCEDISPLAYTYPE_SHAREADMIN     0x00000008
#define RESOURCEDISPLAYTYPE_DIRECTORY      0x00000009
#define RESOURCEDISPLAYTYPE_TREE           0x0000000A
#define RESOURCEDISPLAYTYPE_NDSCONTAINER   0x0000000B

struct NETRESOURCE{
  DWORD    dwScope;
  DWORD    dwType;
  DWORD    dwDisplayType;
  DWORD    dwUsage;
  LPSTR    lpLocalName;
  LPSTR    lpRemoteName;
  LPSTR    lpComment ;
  LPSTR    lpProvider;
};
#define NETRESOURCEW NETRESOURCE
#define NETRESOURCEA NETRESOURCE

//  Network Connections.
#define NETPROPERTY_PERSISTENT       1

#define CONNECT_UPDATE_PROFILE      0x00000001
#define CONNECT_UPDATE_RECENT       0x00000002
#define CONNECT_TEMPORARY           0x00000004
#define CONNECT_INTERACTIVE         0x00000008
#define CONNECT_PROMPT              0x00000010
#define CONNECT_NEED_DRIVE          0x00000020
#define CONNECT_REFCOUNT            0x00000040
#define CONNECT_REDIRECT            0x00000080
#define CONNECT_LOCALDRIVE          0x00000100
#define CONNECT_CURRENT_MEDIA       0x00000200
#define CONNECT_DEFERRED            0x00000400
#define CONNECT_RESERVED            0xFF000000
#define CONNECT_COMMANDLINE         0x00000800
#define CONNECT_CMD_SAVECRED        0x00001000

extern WINAPI "mpr.dll"{
	DWORD WNetAddConnectionA(LPCSTR lpRemoteName,LPCSTR lpPassword,LPCSTR lpLocalName);
	DWORD WNetAddConnectionW(LPCWSTR lpRemoteName,LPCWSTR lpPassword,LPCWSTR lpLocalName);
#ifdef UNICODE
#define WNetAddConnection  WNetAddConnectionW
#else
#define WNetAddConnection  WNetAddConnectionA
#endif // !UNICODE

	DWORD WNetAddConnection2A(dword lpNetResource,LPCSTR lpPassword,LPCSTR lpUserName,DWORD dwFlags);
	DWORD WNetAddConnection2W(dword lpNetResource,LPCWSTR lpPassword,LPCWSTR lpUserName,DWORD dwFlags);
#ifdef UNICODE
#define WNetAddConnection2  WNetAddConnection2W
#else
#define WNetAddConnection2  WNetAddConnection2A
#endif // !UNICODE

	DWORD WNetAddConnection3A(dword hwndOwner,dword lpNetResource,LPCSTR lpPassword,LPCSTR lpUserName,DWORD dwFlags);
	DWORD WNetAddConnection3W(dword hwndOwner,dword lpNetResource,LPCWSTR lpPassword,LPCWSTR lpUserName,DWORD dwFlags);
#ifdef UNICODE
#define WNetAddConnection3  WNetAddConnection3W
#else
#define WNetAddConnection3  WNetAddConnection3A
#endif // !UNICODE

	DWORD WNetCancelConnectionA(LPCSTR lpName,BOOL fForce);
	DWORD WNetCancelConnectionW(LPCWSTR lpName,BOOL fForce);
#ifdef UNICODE
#define WNetCancelConnection  WNetCancelConnectionW
#else
#define WNetCancelConnection  WNetCancelConnectionA
#endif // !UNICODE

	DWORD WNetCancelConnection2A(LPCSTR lpName,DWORD dwFlags,BOOL fForce);
	DWORD WNetCancelConnection2W(LPCWSTR lpName,DWORD dwFlags,BOOL fForce);
#ifdef UNICODE
#define WNetCancelConnection2  WNetCancelConnection2W
#else
#define WNetCancelConnection2  WNetCancelConnection2A
#endif // !UNICODE

	DWORD WNetGetConnectionA(LPCSTR lpLocalName,LPSTR lpRemoteName,LPDWORD lpnLength);
	DWORD WNetGetConnectionW(LPCWSTR lpLocalName,LPWSTR lpRemoteName,LPDWORD lpnLength);
#ifdef UNICODE
#define WNetGetConnection  WNetGetConnectionW
#else
#define WNetGetConnection  WNetGetConnectionA
#endif // !UNICODE

	DWORD WNetUseConnectionA(dword hwndOwner,dword lpNetResource,LPCSTR lpPassword,
		LPCSTR lpUserID,DWORD dwFlags,LPSTR lpAccessName,LPDWORD lpBufferSize,LPDWORD lpResult);
	DWORD WNetUseConnectionW(dword hwndOwner,dword lpNetResource,LPCWSTR lpPassword,
		LPCWSTR lpUserID,DWORD dwFlags,LPWSTR lpAccessName,LPDWORD lpBufferSize,LPDWORD lpResult);
#ifdef UNICODE
#define WNetUseConnection  WNetUseConnectionW
#else
#define WNetUseConnection  WNetUseConnectionA
#endif // !UNICODE

//  Network Connection Dialogs.
	DWORD WNetConnectionDialog(dword hwnd,DWORD dwType);
	DWORD WNetDisconnectDialog(dword hwnd,DWORD dwType);
}
struct CONNECTDLGSTRUCT{
  DWORD cbStructure;       /* size of this structure in bytes */
  dword hwndOwner;          /* owner window for the dialog */
  dword lpConnRes;/* Requested Resource info    */
  DWORD dwFlags;           /* flags (see below) */
  DWORD dwDevNum;          /* number of devices connected to */
};
#define CONNECTDLGSTRUCTW CONNECTDLGSTRUCT
#define CONNECTDLGSTRUCTA CONNECTDLGSTRUCT

#define CONNDLG_RO_PATH     0x00000001 /* Resource path should be read-only    */
#define CONNDLG_CONN_POINT  0x00000002 /* Netware -style movable connection point enabled */
#define CONNDLG_USE_MRU     0x00000004 /* Use MRU combobox  */
#define CONNDLG_HIDE_BOX    0x00000008 /* Hide persistent connect checkbox  */

/*
 * NOTE:  Set at most ONE of the below flags.  If neither flag is set,
 *        then the persistence is set to whatever the user chose during
 *        a previous connection
 */
#define CONNDLG_PERSIST     0x00000010 /* Force persistent connection */
#define CONNDLG_NOT_PERSIST 0x00000020 /* Force connection NOT persistent */

struct DISCDLGSTRUCT{
  DWORD           cbStructure;      /* size of this structure in bytes */
  dword            hwndOwner;        /* owner window for the dialog */
  LPSTR           lpLocalName;      /* local device name */
  LPSTR           lpRemoteName;     /* network resource name */
  DWORD           dwFlags;          /* flags */
};
#define DISCDLGSTRUCTW DISCDLGSTRUCT
#define DISCDLGSTRUCTA DISCDLGSTRUCT

extern WINAPI "mpr.dll"{
	DWORD WNetConnectionDialog1A(dword lpConnDlgStruct);
	DWORD WNetConnectionDialog1W(dword lpConnDlgStruct);
#ifdef UNICODE
#define WNetConnectionDialog1  WNetConnectionDialog1W
#else
#define WNetConnectionDialog1  WNetConnectionDialog1A
#endif // !UNICODE

#define DISC_UPDATE_PROFILE         0x00000001
#define DISC_NO_FORCE               0x00000040

	DWORD WNetDisconnectDialog1A(dword lpConnDlgStruct);
	DWORD WNetDisconnectDialog1W(dword lpConnDlgStruct);
#ifdef UNICODE
#define WNetDisconnectDialog1  WNetDisconnectDialog1W
#else
#define WNetDisconnectDialog1  WNetDisconnectDialog1A
#endif // !UNICODE

//  Network Browsing.
	DWORD WNetOpenEnumA(DWORD dwScope,DWORD dwType,DWORD dwUsage,dword lpNetResource,LPHANDLE lphEnum);
	DWORD WNetOpenEnumW(DWORD dwScope,DWORD dwType,DWORD dwUsage,dword lpNetResource,LPHANDLE lphEnum);
#ifdef UNICODE
#define WNetOpenEnum  WNetOpenEnumW
#else
#define WNetOpenEnum  WNetOpenEnumA
#endif // !UNICODE

	DWORD WNetEnumResourceA(HANDLE hEnum,LPDWORD lpcCount,LPVOID lpBuffer,LPDWORD lpBufferSize);
	DWORD WNetEnumResourceW(HANDLE hEnum,LPDWORD lpcCount,LPVOID lpBuffer,LPDWORD lpBufferSize);
#ifdef UNICODE
#define WNetEnumResource  WNetEnumResourceW
#else
#define WNetEnumResource  WNetEnumResourceA
#endif // !UNICODE

	DWORD WNetCloseEnum(HANDLE hEnum);
	DWORD WNetGetResourceParentA(dword lpNetResource,LPVOID lpBuffer,LPDWORD lpcbBuffer);
	DWORD WNetGetResourceParentW(dword lpNetResource,LPVOID lpBuffer,LPDWORD lpcbBuffer);
#ifdef UNICODE
#define WNetGetResourceParent  WNetGetResourceParentW
#else
#define WNetGetResourceParent  WNetGetResourceParentA
#endif // !UNICODE

	DWORD WNetGetResourceInformationA(dword lpNetResource,LPVOID lpBuffer,
		LPDWORD lpcbBuffer,dword lplpSystem);
	DWORD WNetGetResourceInformationW(dword lpNetResource,LPVOID lpBuffer,
    LPDWORD lpcbBuffer,dword lplpSystem);
#ifdef UNICODE
#define WNetGetResourceInformation  WNetGetResourceInformationW
#else
#define WNetGetResourceInformation  WNetGetResourceInformationA
#endif // !UNICODE
}
//  Universal Naming.
#define UNIVERSAL_NAME_INFO_LEVEL   0x00000001
#define REMOTE_NAME_INFO_LEVEL      0x00000002

struct UNIVERSAL_NAME_INFO{
  LPSTR    lpUniversalName;
};
#define UNIVERSAL_NAME_INFOW UNIVERSAL_NAME_INFO
#define UNIVERSAL_NAME_INFOA UNIVERSAL_NAME_INFO

struct REMOTE_NAME_INFO{
  LPSTR    lpUniversalName;
  LPSTR    lpConnectionName;
  LPSTR    lpRemainingPath;
};
#define REMOTE_NAME_INFOW REMOTE_NAME_INFO
#define REMOTE_NAME_INFOA REMOTE_NAME_INFO

struct NETINFOSTRUCT{
  DWORD cbStructure;
  DWORD dwProviderVersion;
  DWORD dwStatus;
  DWORD dwCharacteristics;
  ULONG_PTR dwHandle;
  WORD  wNetType;
  DWORD dwPrinters;
  DWORD dwDrives;
};

extern WINAPI "mpr.dll"{
	DWORD WNetGetUniversalNameA(LPCSTR lpLocalPath,DWORD dwInfoLevel,LPVOID lpBuffer,LPDWORD lpBufferSize);
	DWORD WNetGetUniversalNameW(LPCWSTR lpLocalPath,DWORD dwInfoLevel,LPVOID lpBuffer,LPDWORD lpBufferSize);
#ifdef UNICODE
#define WNetGetUniversalName  WNetGetUniversalNameW
#else
#define WNetGetUniversalName  WNetGetUniversalNameA
#endif // !UNICODE

//  Authentication and Logon/Logoff.
	DWORD WNetGetUserA(LPCSTR lpName,LPSTR lpUserName,LPDWORD lpnLength);
	DWORD WNetGetUserW(LPCWSTR lpName,LPWSTR lpUserName,LPDWORD lpnLength);
#ifdef UNICODE
#define WNetGetUser  WNetGetUserW
#else
#define WNetGetUser  WNetGetUserA
#endif // !UNICODE

// Other.
#define WNFMT_MULTILINE         0x01
#define WNFMT_ABBREVIATED       0x02
#define WNFMT_INENUM            0x10
#define WNFMT_CONNECTION        0x20

	DWORD WNetGetProviderNameA(DWORD dwNetType,LPSTR lpProviderName,LPDWORD lpBufferSize);
	DWORD WNetGetProviderNameW(DWORD dwNetType,LPWSTR lpProviderName,LPDWORD lpBufferSize);
#ifdef UNICODE
#define WNetGetProviderName  WNetGetProviderNameW
#else
#define WNetGetProviderName  WNetGetProviderNameA
#endif // !UNICODE

#define NETINFO_DLL16       0x00000001  /* Provider running as 16 bit Winnet Driver */
#define NETINFO_DISKRED     0x00000004  /* Provider requires disk redirections to connect */
#define NETINFO_PRINTERRED  0x00000008  /* Provider requires printer redirections to connect */

	DWORD WNetGetNetworkInformationA(LPCSTR lpProvider,dword lpNetInfoStruct);
	DWORD WNetGetNetworkInformationW(LPCWSTR lpProvider,dword lpNetInfoStruct);
#ifdef UNICODE
#define WNetGetNetworkInformation  WNetGetNetworkInformationW
#else
#define WNetGetNetworkInformation  WNetGetNetworkInformationA
#endif // !UNICODE

#define RP_LOGON    0x01        /* if set, do for logon, else for logoff */
#define RP_INIFILE  0x02        /* if set, reconcile .INI file, else reg. hive */

#define PP_DISPLAYERRORS    0x01    /* if set, display error messages, else fail silently if error */

//  Error handling.
	DWORD WNetGetLastErrorA(LPDWORD lpError,LPSTR lpErrorBuf,DWORD nErrorBufSize,
		LPSTR lpNameBuf,DWORD nNameBufSize);
	DWORD WNetGetLastErrorW(LPDWORD lpError,LPWSTR lpErrorBuf,DWORD nErrorBufSize,
		LPWSTR lpNameBuf,DWORD nNameBufSize);
#ifdef UNICODE
#define WNetGetLastError  WNetGetLastErrorW
#else
#define WNetGetLastError  WNetGetLastErrorA
#endif // !UNICODE
}
//  STATUS CODES
// General
#define WN_SUCCESS                      NO_ERROR
#define WN_NO_ERROR                     NO_ERROR
#define WN_NOT_SUPPORTED                ERROR_NOT_SUPPORTED
#define WN_CANCEL                       ERROR_CANCELLED
#define WN_RETRY                        ERROR_RETRY
#define WN_NET_ERROR                    ERROR_UNEXP_NET_ERR
#define WN_MORE_DATA                    ERROR_MORE_DATA
#define WN_BAD_POINTER                  ERROR_INVALID_ADDRESS
#define WN_BAD_VALUE                    ERROR_INVALID_PARAMETER
#define WN_BAD_USER                     ERROR_BAD_USERNAME
#define WN_BAD_PASSWORD                 ERROR_INVALID_PASSWORD
#define WN_ACCESS_DENIED                ERROR_ACCESS_DENIED
#define WN_FUNCTION_BUSY                ERROR_BUSY
#define WN_WINDOWS_ERROR                ERROR_UNEXP_NET_ERR
#define WN_OUT_OF_MEMORY                ERROR_NOT_ENOUGH_MEMORY
#define WN_NO_NETWORK                   ERROR_NO_NETWORK
#define WN_EXTENDED_ERROR               ERROR_EXTENDED_ERROR
#define WN_BAD_LEVEL                    ERROR_INVALID_LEVEL
#define WN_BAD_HANDLE                   ERROR_INVALID_HANDLE
#define WN_NOT_INITIALIZING             ERROR_ALREADY_INITIALIZED
#define WN_NO_MORE_DEVICES              ERROR_NO_MORE_DEVICES

// Connection
#define WN_NOT_CONNECTED                       ERROR_NOT_CONNECTED
#define WN_OPEN_FILES                          ERROR_OPEN_FILES
#define WN_DEVICE_IN_USE                       ERROR_DEVICE_IN_USE
#define WN_BAD_NETNAME                         ERROR_BAD_NET_NAME
#define WN_BAD_LOCALNAME                       ERROR_BAD_DEVICE
#define WN_ALREADY_CONNECTED                   ERROR_ALREADY_ASSIGNED
#define WN_DEVICE_ERROR                        ERROR_GEN_FAILURE
#define WN_CONNECTION_CLOSED                   ERROR_CONNECTION_UNAVAIL
#define WN_NO_NET_OR_BAD_PATH                  ERROR_NO_NET_OR_BAD_PATH
#define WN_BAD_PROVIDER                        ERROR_BAD_PROVIDER
#define WN_CANNOT_OPEN_PROFILE                 ERROR_CANNOT_OPEN_PROFILE
#define WN_BAD_PROFILE                         ERROR_BAD_PROFILE
#define WN_BAD_DEV_TYPE                        ERROR_BAD_DEV_TYPE
#define WN_DEVICE_ALREADY_REMEMBERED           ERROR_DEVICE_ALREADY_REMEMBERED
#define WN_CONNECTED_OTHER_PASSWORD            ERROR_CONNECTED_OTHER_PASSWORD
#define WN_CONNECTED_OTHER_PASSWORD_DEFAULT    ERROR_CONNECTED_OTHER_PASSWORD_DEFAULT

// Enumeration
#define WN_NO_MORE_ENTRIES              ERROR_NO_MORE_ITEMS
#define WN_NOT_CONTAINER                ERROR_NOT_CONTAINER

// Authentication
#define WN_NOT_AUTHENTICATED            ERROR_NOT_AUTHENTICATED
#define WN_NOT_LOGGED_ON                ERROR_NOT_LOGGED_ON
#define WN_NOT_VALIDATED                ERROR_NO_LOGON_SERVERS

//  For Shell
struct NETCONNECTINFOSTRUCT{
  DWORD cbStructure;
  DWORD dwFlags;
  DWORD dwSpeed;
  DWORD dwDelay;
  DWORD dwOptDataSize;
};

#define WNCON_FORNETCARD        0x00000001
#define WNCON_NOTROUTED         0x00000002
#define WNCON_SLOWLINK          0x00000004
#define WNCON_DYNAMIC           0x00000008

extern WINAPI "mpr.dll"{
	DWORD MultinetGetConnectionPerformanceA(dword lpNetResource,dword lpNetConnectInfoStruct);
	DWORD MultinetGetConnectionPerformanceW(dword lpNetResource,dword lpNetConnectInfoStruct);
}
#ifdef UNICODE
#define MultinetGetConnectionPerformance  MultinetGetConnectionPerformanceW
#else
#define MultinetGetConnectionPerformance  MultinetGetConnectionPerformanceA
#endif // !UNICODE
#endif  // _WINNETWK_
