#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

//#include "rpc.h"
//#include "rpcndr.h"

#ifndef __wtypes_h__
#define __wtypes_h__

/* Forward Declarations */

/* header files for imported files */
//#include "basetsd.h"
//#include "guiddef.h"

//+-------------------------------------------------------------------------
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------
#ifndef __IWinTypes_INTERFACE_DEFINED__
#define __IWinTypes_INTERFACE_DEFINED__

struct RemHGLOBAL{
  long fNullHGlobal;
  unsigned long cbData;
  byte data[ 1 ];
};

struct RemHMETAFILEPICT{
  long mm;
  long xExt;
  long yExt;
  unsigned long cbData;
  byte data[ 1 ];
};

struct RemHENHMETAFILE{
  unsigned long cbData;
  byte data[ 1 ];
};

struct RemHBITMAP{
  unsigned long cbData;
  byte data[ 1 ];
};

struct RemHPALETTE{
  unsigned long cbData;
  byte data[ 1 ];
};

struct RemBRUSH{
  unsigned long cbData;
  byte data[ 1 ];
};

#if !defined(_WIN32) && !defined(_MPPC_)
// The following code is for Win16 only
#ifndef WINAPI          // If not included with 3.1 headers...
#define PASCAL          pascal
#define CDECL           cdecl
#define VOID            void
#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
#define BYTE byte
#endif // !_BYTE_DEFINED
#ifndef _WORD_DEFINED
#define _WORD_DEFINED
#define WORD word
#endif // !_WORD_DEFINED
#define UINT unsigned int
#define INT int
#define BOOL long
#ifndef _LONG_DEFINED
#define _LONG_DEFINED
#define LONG long
#endif // !_LONG_DEFINED
#ifndef _WPARAM_DEFINED
#define _WPARAM_DEFINED
#define WPARAM dword
#endif // _WPARAM_DEFINED
#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
#define DWORD dword
#endif // !_DWORD_DEFINED
#ifndef _LPARAM_DEFINED
#define _LPARAM_DEFINED
#define LPARAM dword
#endif // !_LPARAM_DEFINED
#ifndef _LRESULT_DEFINED
#define _LRESULT_DEFINED
#define LRESULT dword
#endif // !_LRESULT_DEFINED
#define HANDLE dword
#define HMODULE dword
#define HINSTANCE dword
#define HRGN dword
#define HTASK dword
#define HKEY dword
#define HDESK dword
#define HMF dword
#define HEMF dword
#define HPEN dword
#define HRSRC dword
#define HSTR dword
#define HWINSTA dword
#define HKL dword
#define HGDIOBJ dword
#define HDWP dword
#ifndef _HFILE_DEFINED
#define _HFILE_DEFINED
#define HFILE int
#endif // !_HFILE_DEFINED
#ifndef _LPWORD_DEFINED
#define _LPWORD_DEFINED
#define LPWORD dword
#endif // !_LPWORD_DEFINED
#ifndef _LPDWORD_DEFINED
#define _LPDWORD_DEFINED
#define LPDWORD dword
#endif // !_LPDWORD_DEFINED
#define CHAR char
#define LPSTR dword
#define LPCSTR dword
#ifndef _WCHAR_DEFINED
#define _WCHAR_DEFINED
#define WCHAR short
#define TCHAR short
#endif // !_WCHAR_DEFINED
#define LPWSTR dword
#define LPTSTR dword
#define LPCWSTR dword
#define LPCTSTR dword
#ifndef _COLORREF_DEFINED
#define _COLORREF_DEFINED
#define COLORREF dword
#endif // !_COLORREF_DEFINED
#ifndef _LPCOLORREF_DEFINED
#define _LPCOLORREF_DEFINED
#define LPCOLORREF dword
#endif // !_LPCOLORREF_DEFINED
#define LPHANDLE dword

struct RECTL{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
};

struct POINT{
  LONG x;
  LONG y;
};

struct POINTL{
  LONG x;
  LONG y;
};

struct SIZE{
  int cx;
  int cy;
};
struct SIZEL{
  LONG cx;
  LONG cy;
};

#endif  //WINAPI
#endif  //!WIN32 && !MPPC
#ifndef _PALETTEENTRY_DEFINED
#define _PALETTEENTRY_DEFINED
struct PALETTEENTRY{
  BYTE peRed;
  BYTE peGreen;
  BYTE peBlue;
  BYTE peFlags;
};

#endif // !_PALETTEENTRY_DEFINED
#ifndef _LOGPALETTE_DEFINED
#define _LOGPALETTE_DEFINED
struct LOGPALETTE{
  WORD palVersion;
  WORD palNumEntries;
  PALETTEENTRY palPalEntry[ 1 ];
};

#endif // !_LOGPALETTE_DEFINED
#if defined(_WIN32) && !defined(OLE2ANSI)
#define OLECHAR short
#else
#define OLECHAR char
#endif
#define LPOLESTR dword
#define LPCOLESTR dword
#ifndef _WINDEF_
#define LPCRECTL dword
#define PVOID dword
#define LPVOID dword
#define FLOAT float
struct RECT{
  LONG left;
  LONG top;
  LONG right;
  LONG bottom;
};

#endif  //_WINDEF_
#define UCHAR unsigned char
#define SHORT short
#define USHORT word
#define DWORD dword
#define DOUBLE double

#ifndef _DWORDLONG_
#define DWORDLONG qword
#define PDWORDLONG dword
#endif // !_DWORDLONG_
#ifndef _ULONGLONG_
#define LONGLONG qword
#define ULONGLONG qword
#define PLONGLONG dword
#define PULONGLONG dword
#endif // _ULONGLONG_
/*#if 0
typedef struct _LARGE_INTEGER
    {
    LONGLONG QuadPart;
    } 	LARGE_INTEGER;

typedef LARGE_INTEGER *PLARGE_INTEGER;

typedef struct _ULARGE_INTEGER
    {
    ULONGLONG QuadPart;
    } 	ULARGE_INTEGER;

#endif // 0*/
#ifndef _WINBASE_
#ifndef _FILETIME_
#define _FILETIME_
struct FILETIME
{
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
};
#endif // !_FILETIME
#ifndef _SYSTEMTIME_
#define _SYSTEMTIME_
struct SYSTEMTIME
{
WORD wYear;
WORD wMonth;
WORD wDayOfWeek;
WORD wDay;
WORD wHour;
WORD wMinute;
WORD wSecond;
WORD wMilliseconds;
};

#endif // !_SYSTEMTIME
#ifndef _SECURITY_ATTRIBUTES_
#define _SECURITY_ATTRIBUTES_
struct SECURITY_ATTRIBUTES
{
	DWORD nLength;
	dword lpSecurityDescriptor;
	BOOL bInheritHandle;
};

#endif // !_SECURITY_ATTRIBUTES_
#ifndef SECURITY_DESCRIPTOR_REVISION
#define SECURITY_DESCRIPTOR_CONTROL word
#define PSECURITY_DESCRIPTOR_CONTROL dword
#define PSID dword

struct ACL
{
  UCHAR AclRevision;
  UCHAR Sbz1;
  USHORT AclSize;
  USHORT AceCount;
  USHORT Sbz2;
};

struct SECURITY_DESCRIPTOR
{
  UCHAR Revision;
  UCHAR Sbz1;
  SECURITY_DESCRIPTOR_CONTROL Control;
  PSID Owner;
  PSID Group;
  dword Sacl;
  dword Dacl;
};

#endif // !SECURITY_DESCRIPTOR_REVISION
#endif //_WINBASE_
struct COAUTHIDENTITY
{
  USHORT *User;
  ULONG UserLength;
  USHORT *Domain;
  ULONG DomainLength;
  USHORT *Password;
  ULONG PasswordLength;
  ULONG Flags;
};

struct COAUTHINFO
{
  DWORD dwAuthnSvc;
  DWORD dwAuthzSvc;
  LPWSTR pwszServerPrincName;
  DWORD dwAuthnLevel;
  DWORD dwImpersonationLevel;
  dword pAuthIdentityData;
  DWORD dwCapabilities;
};

#define SCODE long

#ifndef _HRESULT_DEFINED
#define _HRESULT_DEFINED
#define HRESULT long
#endif // !_HRESULT_DEFINED

#ifndef __OBJECTID_DEFINED
#define __OBJECTID_DEFINED
#define _OBJECTID_DEFINED
struct OBJECTID
{
  GUID Lineage;
  unsigned long Uniquifier;
};

#endif // !_OBJECTID_DEFINED
enum MEMCTX{
	MEMCTX_TASK	= 1,
	MEMCTX_SHARED	= 2,
	MEMCTX_MACSYSTEM	= 3,
	MEMCTX_UNKNOWN	= -1,
	MEMCTX_SAME	= -2
};

#ifndef _ROTFLAGS_DEFINED
#define _ROTFLAGS_DEFINED
#define ROTFLAGS_REGISTRATIONKEEPSALIVE 0x1
#define ROTFLAGS_ALLOWANYCLIENT 0x2
#endif // !_ROTFLAGS_DEFINED
#ifndef _ROT_COMPARE_MAX_DEFINED
#define _ROT_COMPARE_MAX_DEFINED
#define ROT_COMPARE_MAX 2048
#endif // !_ROT_COMPARE_MAX_DEFINED
enum CLSCTX{
	CLSCTX_INPROC_SERVER	= 0x1,
	CLSCTX_INPROC_HANDLER	= 0x2,
	CLSCTX_LOCAL_SERVER	= 0x4,
	CLSCTX_INPROC_SERVER16	= 0x8,
	CLSCTX_REMOTE_SERVER	= 0x10,
	CLSCTX_INPROC_HANDLER16	= 0x20,
	CLSCTX_INPROC_SERVERX86	= 0x40,
	CLSCTX_INPROC_HANDLERX86	= 0x80,
	CLSCTX_ESERVER_HANDLER	= 0x100,
	CLSCTX_RESERVED	= 0x200,
	CLSCTX_NO_CODE_DOWNLOAD	= 0x400,
	CLSCTX_NO_WX86_TRANSLATION	= 0x800,
	CLSCTX_NO_CUSTOM_MARSHAL	= 0x1000,
	CLSCTX_ENABLE_CODE_DOWNLOAD	= 0x2000,
	CLSCTX_NO_FAILURE_LOG	= 0x4000,
	CLSCTX_DISABLE_AAA	= 0x8000,
	CLSCTX_ENABLE_AAA	= 0x10000,
	CLSCTX_FROM_DEFAULT_CONTEXT	= 0x20000
};

enum MSHLFLAGS{
	MSHLFLAGS_NORMAL	= 0,
	MSHLFLAGS_TABLESTRONG	= 1,
	MSHLFLAGS_TABLEWEAK	= 2,
	MSHLFLAGS_NOPING	= 4,
	MSHLFLAGS_RESERVED1	= 8,
	MSHLFLAGS_RESERVED2	= 16,
	MSHLFLAGS_RESERVED3	= 32,
	MSHLFLAGS_RESERVED4	= 64
};

enum MSHCTX{
	MSHCTX_LOCAL	= 0,
	MSHCTX_NOSHAREDMEM	= 1,
	MSHCTX_DIFFERENTMACHINE	= 2,
	MSHCTX_INPROC	= 3,
	MSHCTX_CROSSCTX	= 4
};

enum DVASPECT{
	DVASPECT_CONTENT	= 1,
	DVASPECT_THUMBNAIL	= 2,
	DVASPECT_ICON	= 4,
	DVASPECT_DOCPRINT	= 8
};

enum STGC{
	STGC_DEFAULT	= 0,
	STGC_OVERWRITE	= 1,
	STGC_ONLYIFCURRENT	= 2,
	STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE	= 4,
	STGC_CONSOLIDATE	= 8
};

enum STGMOVE{
	STGMOVE_MOVE	= 0,
	STGMOVE_COPY	= 1,
	STGMOVE_SHALLOWCOPY	= 2
};

enum STATFLAG{
	STATFLAG_DEFAULT	= 0,
	STATFLAG_NONAME	= 1,
	STATFLAG_NOOPEN	= 2
};

#define HCONTEXT dword

#ifndef _LCID_DEFINED
#define _LCID_DEFINED
#define LCID dword

#endif // !_LCID_DEFINED
#ifndef _LANGID_DEFINED
#define _LANGID_DEFINED
#define LANGID word

#endif // !_LANGID_DEFINED
struct BYTE_BLOB
{
  unsigned long clSize;
  byte abData[ 1 ];
};

struct WORD_BLOB
{
  unsigned long clSize;
  unsigned short asData[ 1 ];
};

struct DWORD_BLOB
{
  unsigned long clSize;
  unsigned long alData[ 1 ];
};

struct FLAGGED_BYTE_BLOB
{
  unsigned long fFlags;
  unsigned long clSize;
  byte abData[ 1 ];
};

struct FLAGGED_WORD_BLOB
{
  unsigned long fFlags;
  unsigned long clSize;
  unsigned short asData[ 1 ];
};

struct BYTE_SIZEDARR
{
  unsigned long clSize;
  byte *pData;
};

struct SHORT_SIZEDARR
{
  unsigned long clSize;
  unsigned short *pData;
};

struct LONG_SIZEDARR
{
  unsigned long clSize;
  unsigned long *pData;
};

struct HYPER_SIZEDARR
{
  unsigned long clSize;
  qword *pData;
};

#define	WDT_INPROC_CALL	0x48746457
#define	WDT_REMOTE_CALL	0x52746457
#define	WDT_INPROC64_CALL	0x50746457

struct userCLIPFORMAT
{
  long fContext;
  union{
    DWORD dwValue;
    word *pwszName;
  }u;
};

#define CLIPFORMAT word

struct GDI_NONREMOTE
{
	long fContext;
	union{
    long hInproc;
    DWORD hRemote;
  }u;
};

struct userHGLOBAL
{
	long fContext;
  union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
  }u;
};

struct userHMETAFILE
{
	long fContext;
	union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
  }u;
};

struct remoteMETAFILEPICT
{
	long mm;
	long xExt;
	long yExt;
	dword hMF;
};

struct userHMETAFILEPICT
{
  long fContext;
	union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
  }u;
};

struct userHENHMETAFILE
{
  long fContext;
  union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
	}u;
};

struct userBITMAP
{
  LONG bmType;
  LONG bmWidth;
  LONG bmHeight;
  LONG bmWidthBytes;
  WORD bmPlanes;
  WORD bmBitsPixel;
  ULONG cbSize;
  byte pBuffer[ 1 ];
};

struct userHBITMAP
{
  long fContext;
  union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
  }u;
};

struct userHPALETTE
{
  long fContext;
  union{
    long hInproc;
    dword hRemote;
    qword hInproc64;
  }u;
};

struct RemotableHandle
{
  long fContext;
  union{
    long hInproc;
    long hRemote;
  }u;
};

#define wireHWND dword
#define wireHMENU dword
#define wireHACCEL dword
#define wireHBRUSH dword
#define wireHFONT dword
#define wireHDC dword
#define wireHICON dword
#define HWND dword
#define HMENU dword
#define HACCEL dword
#define HBRUSH dword
#define HFONT dword
#define HDC dword
#define HICON dword
#ifndef _HCURSOR_DEFINED
#define _HCURSOR_DEFINED
#define HCURSOR dword
#endif // !_HCURSOR_DEFINED
#ifndef _TEXTMETRIC_DEFINED
#define _TEXTMETRIC_DEFINED
struct TEXTMETRICW
{
  LONG tmHeight;
  LONG tmAscent;
  LONG tmDescent;
  LONG tmInternalLeading;
  LONG tmExternalLeading;
  LONG tmAveCharWidth;
  LONG tmMaxCharWidth;
  LONG tmWeight;
  LONG tmOverhang;
  LONG tmDigitizedAspectX;
  LONG tmDigitizedAspectY;
  WCHAR tmFirstChar;
  WCHAR tmLastChar;
  WCHAR tmDefaultChar;
  WCHAR tmBreakChar;
  BYTE tmItalic;
  BYTE tmUnderlined;
  BYTE tmStruckOut;
  BYTE tmPitchAndFamily;
  BYTE tmCharSet;
};

#endif // !_TEXTMETRIC_DEFINED
#ifndef _WIN32           // The following code is for Win16 only
#ifndef WINAPI          // If not included with 3.1 headers...
struct MSG
{
  HWND hwnd;
  UINT message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD time;
  POINT pt;
};

#endif // _WIN32
#endif // WINAPI
#define wireHBITMAP dword
#define wireHPALETTE dword
#define wireHENHMETAFILE dword
#define wireHMETAFILE dword
#define wireHMETAFILEPICT dword
#define HGLOBAL dword
#define HLOCAL dword
#define HBITMAP dword
#define HPALETTE dword
#define HENHMETAFILE dword
#define HMETAFILE dword
#define HMETAFILEPICT dword

#endif /* __IWinTypes_INTERFACE_DEFINED__ */

#define DATE double

#ifndef _tagCY_DEFINED
#define _tagCY_DEFINED
#define _CY_DEFINED
/* the following isn't the real definition of CY, but it is */
/* what RPC knows how to remote */
struct CY
{
	LONGLONG int64;
};

#endif /* _tagCY_DEFINED */

/* The following isn't the real definition of Decimal type, */
/* but it is what RPC knows how to remote */
struct DEC
{
  USHORT wReserved;
  BYTE scale;
  BYTE sign;
  ULONG Hi32;
  ULONGLONG Lo64;
};

#define wireBSTR dword
#define BSTR dword
#define LPBSTR dword
#define VARIANT_BOOL short
//typedef boolean BOOLEAN;

/* The BSTRBLOB structure is used by some implementations */
/* of the IPropertyStorage interface when marshaling BSTRs */
/* on systems which don't support BSTR marshaling. */
#ifndef _tagBSTRBLOB_DEFINED
#define _tagBSTRBLOB_DEFINED
struct BSTRBLOB
{
  ULONG cbSize;
  BYTE *pData;
};

#endif
#define VARIANT_TRUE -1
#define VARIANT_FALSE 0
#ifndef _tagBLOB_DEFINED
#define _tagBLOB_DEFINED
#define _BLOB_DEFINED
#define _LPBLOB_DEFINED
struct BLOB
{
  ULONG cbSize;
  BYTE *pBlobData;
};

#endif
struct CLIPDATA
{
  ULONG cbSize;
  long ulClipFmt;
  BYTE *pClipData;
};

// Macro to calculate the size of the above pClipData
#define CBPCLIPDATA(clipdata) clipdata.cbSize - sizeof(clipdata.ulClipFmt)
#define VARTYPE word

/*
 * VARENUM usage key,
 * * [V] - may appear in a VARIANT
 * * [T] - may appear in a TYPEDESC
 * * [P] - may appear in an OLE property set
 * * [S] - may appear in a Safe Array
 *  VT_EMPTY            [V]   [P]     nothing
 *  VT_NULL             [V]   [P]     SQL style Null
 *  VT_I2               [V][T][P][S]  2 byte signed int
 *  VT_I4               [V][T][P][S]  4 byte signed int
 *  VT_R4               [V][T][P][S]  4 byte real
 *  VT_R8               [V][T][P][S]  8 byte real
 *  VT_CY               [V][T][P][S]  currency
 *  VT_DATE             [V][T][P][S]  date
 *  VT_BSTR             [V][T][P][S]  OLE Automation string
 *  VT_DISPATCH         [V][T]   [S]  IDispatch *
 *  VT_ERROR            [V][T][P][S]  SCODE
 *  VT_BOOL             [V][T][P][S]  True=-1, False=0
 *  VT_VARIANT          [V][T][P][S]  VARIANT *
 *  VT_UNKNOWN          [V][T]   [S]  IUnknown *
 *  VT_DECIMAL          [V][T]   [S]  16 byte fixed point
 *  VT_RECORD           [V]   [P][S]  user defined type
 *  VT_I1               [V][T][P][s]  signed char
 *  VT_UI1              [V][T][P][S]  unsigned char
 *  VT_UI2              [V][T][P][S]  unsigned short
 *  VT_UI4              [V][T][P][S]  unsigned long
 *  VT_I8                  [T][P]     signed 64-bit int
 *  VT_UI8                 [T][P]     unsigned 64-bit int
 *  VT_INT              [V][T][P][S]  signed machine int
 *  VT_UINT             [V][T]   [S]  unsigned machine int
 *  VT_INT_PTR             [T]        signed machine register size width
 *  VT_UINT_PTR            [T]        unsigned machine register size width
 *  VT_VOID                [T]        C style void
 *  VT_HRESULT             [T]        Standard return type
 *  VT_PTR                 [T]        pointer type
 *  VT_SAFEARRAY           [T]        (use VT_ARRAY in VARIANT)
 *  VT_CARRAY              [T]        C style array
 *  VT_USERDEFINED         [T]        user defined type
 *  VT_LPSTR               [T][P]     null terminated string
 *  VT_LPWSTR              [T][P]     wide null terminated string
 *  VT_FILETIME               [P]     FILETIME
 *  VT_BLOB                   [P]     Length prefixed bytes
 *  VT_STREAM                 [P]     Name of the stream follows
 *  VT_STORAGE                [P]     Name of the storage follows
 *  VT_STREAMED_OBJECT        [P]     Stream contains an object
 *  VT_STORED_OBJECT          [P]     Storage contains an object
 *  VT_VERSIONED_STREAM       [P]     Stream with a GUID version
 *  VT_BLOB_OBJECT            [P]     Blob contains an object
 *  VT_CF                     [P]     Clipboard format
 *  VT_CLSID                  [P]     A Class ID
 *  VT_VECTOR                 [P]     simple counted array
 *  VT_ARRAY            [V]           SAFEARRAY*
 *  VT_BYREF            [V]           void* for local use
 *  VT_BSTR_BLOB                      Reserved for system use
 */
enum VARENUM{
	VT_EMPTY	= 0,
	VT_NULL	= 1,
	VT_I2	= 2,
	VT_I4	= 3,
	VT_R4	= 4,
	VT_R8	= 5,
	VT_CY	= 6,
	VT_DATE	= 7,
	VT_BSTR	= 8,
	VT_DISPATCH	= 9,
	VT_ERROR	= 10,
	VT_BOOL	= 11,
	VT_VARIANT	= 12,
	VT_UNKNOWN	= 13,
	VT_DECIMAL	= 14,
	VT_I1	= 16,
	VT_UI1	= 17,
	VT_UI2	= 18,
	VT_UI4	= 19,
	VT_I8	= 20,
	VT_UI8	= 21,
	VT_INT	= 22,
	VT_UINT	= 23,
	VT_VOID	= 24,
	VT_HRESULT	= 25,
	VT_PTR	= 26,
	VT_SAFEARRAY	= 27,
	VT_CARRAY	= 28,
	VT_USERDEFINED	= 29,
	VT_LPSTR	= 30,
	VT_LPWSTR	= 31,
	VT_RECORD	= 36,
	VT_INT_PTR	= 37,
	VT_UINT_PTR	= 38,
	VT_FILETIME	= 64,
	VT_BLOB	= 65,
	VT_STREAM	= 66,
	VT_STORAGE	= 67,
	VT_STREAMED_OBJECT	= 68,
	VT_STORED_OBJECT	= 69,
	VT_BLOB_OBJECT	= 70,
	VT_CF	= 71,
	VT_CLSID	= 72,
	VT_VERSIONED_STREAM	= 73,
	VT_BSTR_BLOB	= 0xfff,
	VT_VECTOR	= 0x1000,
	VT_ARRAY	= 0x2000,
	VT_BYREF	= 0x4000,
	VT_RESERVED	= 0x8000,
	VT_ILLEGAL	= 0xffff,
	VT_ILLEGALMASKED	= 0xfff,
	VT_TYPEMASK	= 0xfff
};
#define PROPID dword

#ifndef SID_IDENTIFIER_AUTHORITY_DEFINED
#define SID_IDENTIFIER_AUTHORITY_DEFINED
struct SID_IDENTIFIER_AUTHORITY
{
  UCHAR Value[ 6 ];
};

#endif
#ifndef SID_DEFINED
#define SID_DEFINED
struct SID
{
  BYTE Revision;
  BYTE SubAuthorityCount;
  SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
  ULONG SubAuthority[ 1 ];
};

struct SID_AND_ATTRIBUTES
{
  dword Sid;
  DWORD Attributes;
};

#endif
struct CSPLATFORM
{
  DWORD dwPlatformId;
  DWORD dwVersionHi;
  DWORD dwVersionLo;
  DWORD dwProcessorArch;
};

struct QUERYCONTEXT
{
  DWORD dwContext;
  CSPLATFORM Platform;
  LCID Locale;
  DWORD dwVersionHi;
  DWORD dwVersionLo;
};

enum TYSPEC{
	TYSPEC_CLSID	= 0,
	TYSPEC_FILEEXT	= TYSPEC_CLSID + 1,
	TYSPEC_MIMETYPE	= TYSPEC_FILEEXT + 1,
	TYSPEC_FILENAME	= TYSPEC_MIMETYPE + 1,
	TYSPEC_PROGID	= TYSPEC_FILENAME + 1,
	TYSPEC_PACKAGENAME	= TYSPEC_PROGID + 1,
	TYSPEC_OBJECTID	= TYSPEC_PACKAGENAME + 1
};

struct uCLSSPEC
{
  DWORD tyspec;
  union{
    CLSID clsid;
    LPOLESTR pFileExt;
    LPOLESTR pMimeType;
    LPOLESTR pProgId;
    LPOLESTR pFileName;
    struct{
      LPOLESTR pPackageName;
      GUID PolicyId;
    }ByName;
    struct{
      GUID ObjectId;
      GUID PolicyId;
    }ByObjectId;
  }tagged_union;
};

/* Additional Prototypes for ALL interfaces */
/* end of Additional Prototypes */

#endif
