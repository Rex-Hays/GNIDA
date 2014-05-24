/*++
Copyright (c) Microsoft Corporation.  All rights reserved.
Module Name:
    lzdos.h
Abstract:
    Public interface to LZEXP?.LIB.
Author:
Revision History:
--*/

#ifndef _LZEXPAND_
#define _LZEXPAND_

/*
** Error Return Codes
*/
#define LZERROR_BADINHANDLE   -1  /* invalid input handle */
#define LZERROR_BADOUTHANDLE  -2  /* invalid output handle */
#define LZERROR_READ          -3  /* corrupt compressed file format */
#define LZERROR_WRITE         -4  /* out of space for output file */
#define LZERROR_GLOBALLOC     -5  /* insufficient memory for LZFile struct */
#define LZERROR_GLOBLOCK      -6  /* bad global handle */
#define LZERROR_BADVALUE      -7  /* input parameter out of acceptable range*/
#define LZERROR_UNKNOWNALG    -8  /* compression algorithm not recognized */

/*
** Prototypes
*/

extern WINAPI "lz32.dll" {
	INT LZStart(VOID);
	VOID LZDone(VOID);
	LONG CopyLZFile(INT,INT);
	LONG LZCopy(INT,INT);
	INT LZInit(INT);
	INT GetExpandedNameA(LPSTR,LPSTR);
	INT GetExpandedNameW(LPWSTR,LPWSTR);
#ifdef UNICODE
#define GetExpandedName  GetExpandedNameW
#else
#define GetExpandedName  GetExpandedNameA
#endif // !UNICODE
	INT LZOpenFileA(LPSTR,LPOFSTRUCT,WORD);
	INT LZOpenFileW(LPWSTR,LPOFSTRUCT,WORD);
#ifdef UNICODE
#define LZOpenFile  LZOpenFileW
#else
#define LZOpenFile  LZOpenFileA
#endif // !UNICODE
	LONG LZSeek(INT,LONG,INT);
	INT LZRead(INT,LPSTR,INT);
	VOID LZClose(INT);
}

#endif // _LZEXPAND_
