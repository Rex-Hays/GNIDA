/****************************************************************************
* windef.h -- Basic Windows Type Definitions                                *
* Copyright (c) Microsoft Corporation. All rights reserved.                 *
****************************************************************************/

#ifndef _WINDEF_
#define _WINDEF_

#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

// Win32 defines _WIN32 automatically,
// but Macintosh doesn't, so if we are using
// Win32 Functions, we must do it here

#ifdef _MAC
#ifndef _WIN32
#define _WIN32
#endif
#endif //_MAC

#ifndef WINVER
#define WINVER 0x0501
#endif /* WINVER */

/*
 * BASETYPES is defined in ntdef.h if these types are already defined
 */
#ifndef BASETYPES
#define BASETYPES
#define ULONG unsigned long
#define PULONG dword
#define USHORT unsigned short
#define PUSHORT dword
#define UCHAR unsigned char
#define PUCHAR dword
#define PSZ char
#endif  /* !BASETYPES */

#define MAX_PATH          260

#ifndef NULL
#define NULL    0
#endif

#define DWORD unsigned long
#define BOOL int
#define BYTE unsigned char
#define WORD unsigned short
#define FLOAT float
#define PFLOAT dword
#define PBOOL dword
#define LPBOOL dword
#define PBYTE dword
#define LPBYTE dword
#define PINT dword
#define LPINT dword
#define PWORD dword
#define LPWORD dword
#define LPLONG dword
#define PDWORD dword
#define LPDWORD dword
#define LPVOID dword
#define LPCVOID dword

#define SIZE_T dword
#define INT int
#define UINT unsigned int
#define PUINT dword

#define ULONG_PTR dword
#define PVOID dword
#define DWORD_PTR dword

#define HWND dword

#ifndef NT_INCLUDED
#include <winnt.h>
#endif /* NT_INCLUDED */

/* Types use for passing & returning polymorphic values */
#define WPARAM dword
#define LPARAM dword
#define LRESULT dword

#ifndef NOMINMAX
#ifndef max
inline dword fastcall max(EAX,EDX)
{
	IF (long EAX<EDX)
#if codesize
	EAX><EDX;
#else
	EAX=EDX;
#endif
;
}
#endif

#ifndef min
inline dword fastcall min(EAX,EDX)
{
	IF (long EAX>EDX)
#if codesize
	EAX><EDX;
#else
	EAX=EDX;
#endif
;
}
#endif
#endif  /* NOMINMAX */

#define MAKEWORD(low,high) high<<8|low
/*inline word MAKEWORD(AX,DX)
{
  DX<<=8;
  AX=AL|DX;
} */

#define MAKELONG(low,high) high<<16|low
/*inline dword MAKELONG(AX,DX)
{
  EDX<<=16;
  EAX=AX|EDX;
} */

#define LOWORD(l)           l&0xffff
#define HIWORD(l)           (dword) l>>16
#define LOBYTE(w)           w&0xff
#define HIBYTE(w)           w>>8&0xFF

#define ATOM word
#define HANDLE dword
#define SPHANDLE dword
#define LPHANDLE dword
#define HGLOBAL dword
#define HLOCAL dword
#define GLOBALHANDLE dword
#define LOCALHANDLE dword
#define HGDIOBJ dword
#define HKEY dword
#define PHKEY dword

#define HACCEL dword
#define HBITMAP dword
#define HBRUSH dword
#define COLORSPACE dword
#define HDC dword
#define HGLRC dword          // OpenGL
#define HDESK dword
#define HENHMETAFILE dword
#define HFONT dword
#define HICON dword
#define HMENU dword
#define HMETAFILE dword
#define HINSTANCE dword
#define HMODULE dword
#define HPALETTE dword
#define HPEN dword
#define HRGN dword
#define HRSRC dword
#define HSTR dword
#define HTASK dword
#define HWINSTA dword
#define HKL dword

#define HMONITOR dword
#define HWINEVENTHOOK dword
#define HUMPD dword
#define HIMAGELIST   dword

#define HFILE int
#define HCURSOR dword

#define COLORREF dword
#define LPCOLORREF dword

#define HFILE_ERROR -1

struct RECT
{
  LONG    left;
  LONG    top;
  LONG    right;
  LONG    bottom;
};

#define RECTL RECT

struct POINT
{
  LONG  x;
  LONG  y;
};

#define POINTL POINT

struct SIZE
{
  LONG        cx;
  LONG        cy;
};

#define SIZEL SIZE

struct POINTS
{
#ifndef _MAC
    SHORT   x;
    SHORT   y;
#else
    SHORT   y;
    SHORT   x;
#endif
};

/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_SIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#endif /* _WINDEF_ */
