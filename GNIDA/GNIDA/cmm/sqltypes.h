/*********************************************************************
** SQLTYPES.H - This file defines the types used in ODBC
** (C) Copyright 1995-1998 By Microsoft Corp.
**		Created 04/10/95 for 2.50 specification
**		Updated 12/11/95 for 3.00 specification
*********************************************************************/

#ifndef __SQLTYPES
#define __SQLTYPES

/* if ODBCVER is not defined, assume version 3.51 */
#ifndef ODBCVER
#define ODBCVER	0x0351
#endif  /* ODBCVER */

/* environment specific definitions */
#ifndef EXPORT
#define EXPORT
#endif

#ifndef RC_INVOKED

/* API declaration data types */
#define SQLCHAR byte
#define SQLCHAR signed char
#define SQLDATE  unsigned char
#define SQLDECIMAL unsigned char
#define SQLDOUBLE double
#define SQLFLOAT double
#define SQLINTEGER long
#define SQLUINTEGER unsigned long

#define SQLROWSETSIZE   SQLUINTEGER

#define SQLLEN          SQLINTEGER
#define SQLROWOFFSET    SQLINTEGER
#define SQLROWCOUNT     SQLUINTEGER
#define SQLULEN         SQLUINTEGER
#define SQLTRANSID      DWORD
#define SQLSETPOSIROW   SQLUSMALLINT
#define SQLNUMERIC unsigned char
#define SQLPOINTER dword
#define SQLREAL float
#define SQLSMALLINT short
#define SQLUSMALLINT unsigned short
#define SQLTIME    unsigned char
#define SQLTIMESTAMP unsigned char
#define SQLVARCHAR unsigned char

/* function return type */
#define SQLRETURN SQLSMALLINT

/* generic data structures */
#define SQLHANDLE dword
#define SQLHENV dword
#define SQLHDBC dword
#define SQLHSTMT dword
#define SQLHDESC dword

/* SQL portable types for C */
#define UCHAR  unsigned char
#define SCHAR  signed char
#define SQLSCHAR signed char
#define SDWORD long int
#define SWORD  short int
#define UDWORD unsigned long int
#define UWORD  unsigned short int
#define SQLUINTEGER unsigned long int

#define SLONG signed long
#define SSHORT signed short
#define ULONG unsigned long
#define USHORT unsigned short
#define SDOUBLE double
#define LDOUBLE double
#define SFLOAT float

#define PTR dword

#define HENV dword
#define HDBC dword
#define HSTMT dword

#define RETCODE signed short

#define SQLHWND HWND

#ifndef	__SQLDATE
#define	__SQLDATE
/* transfer types for DATE, TIME, TIMESTAMP */
struct DATE_STRUCT
{
  SQLSMALLINT    year;
  SQLUSMALLINT   month;
  SQLUSMALLINT   day;
};

#define SQL_DATE_STRUCT DATE_STRUCT

struct TIME_STRUCT
{
  SQLUSMALLINT   hour;
  SQLUSMALLINT   minute;
  SQLUSMALLINT   second;
};

#define SQL_TIME_STRUCT TIME_STRUCT

struct TIMESTAMP_STRUCT
{
  SQLSMALLINT    year;
  SQLUSMALLINT   month;
  SQLUSMALLINT   day;
  SQLUSMALLINT   hour;
  SQLUSMALLINT   minute;
  SQLUSMALLINT   second;
  SQLUINTEGER    fraction;
};

#define SQL_TIMESTAMP_STRUCT TIMESTAMP_STRUCT

/*
 * enumerations for DATETIME_INTERVAL_SUBCODE values for interval data types
 * these values are from SQL-92
 */
enum SQLINTERVAL{
	SQL_IS_YEAR						= 1,
	SQL_IS_MONTH					= 2,
	SQL_IS_DAY						= 3,
	SQL_IS_HOUR						= 4,
	SQL_IS_MINUTE					= 5,
	SQL_IS_SECOND					= 6,
	SQL_IS_YEAR_TO_MONTH			= 7,
	SQL_IS_DAY_TO_HOUR				= 8,
	SQL_IS_DAY_TO_MINUTE			= 9,
	SQL_IS_DAY_TO_SECOND			= 10,
	SQL_IS_HOUR_TO_MINUTE			= 11,
	SQL_IS_HOUR_TO_SECOND			= 12,
	SQL_IS_MINUTE_TO_SECOND			= 13
};

struct SQL_YEAR_MONTH
{
  SQLUINTEGER		year;
  SQLUINTEGER		month;
};

#define SQL_YEAR_MONTH_STRUCT SQL_YEAR_MONTH

struct SQL_DAY_SECOND
{
	SQLUINTEGER		day;
	SQLUINTEGER		hour;
	SQLUINTEGER		minute;
	SQLUINTEGER		second;
	SQLUINTEGER		fraction;
};

#define SQL_DAY_SECOND_STRUCT SQL_DAY_SECOND

struct SQL_INTERVAL_STRUCT
{
	unsigned int	interval_type;
	SQLSMALLINT		interval_sign;
	union {
		SQL_YEAR_MONTH_STRUCT		year_month;
		SQL_DAY_SECOND_STRUCT		day_second;
	}intval;
};

#endif	/* __SQLDATE	*/

/* the ODBC C types for SQL_C_SBIGINT and SQL_C_UBIGINT */
#if (ODBCVER >= 0x0300)
#if (_MSC_VER >= 900)
#define ODBCINT64	__int64
#endif

/* If using other compilers, define ODBCINT64 to the
	approriate 64 bit integer type */
#endif  /* ODBCVER >= 0x0300 */

/* internal representation of numeric data type */
#define SQL_MAX_NUMERIC_LEN		16
struct SQL_NUMERIC_STRUCT
{
	SQLCHAR		precision;
	SQLSCHAR	scale;
	SQLCHAR		sign;	/* 1 if positive, 0 if negative */
	SQLCHAR		val[SQL_MAX_NUMERIC_LEN];
};

#if (ODBCVER >= 0x0350)
#ifdef GUID_DEFINED
#define SQLGUID GUID
#else
/* size is 16 */
struct  SQLGUID
{
  DWORD Data1;
  WORD Data2;
  WORD Data3;
  BYTE Data4[ 8 ];
};
#endif  /* GUID_DEFINED */
#endif  /* ODBCVER >= 0x0350 */

#define BOOKMARK unsigned long int

#ifdef _WCHAR_T_DEFINED
#define SQLWCHAR wchar_t
#else
#define SQLWCHAR unsigned short
#endif

#ifdef UNICODE
#define SQLTCHAR SQLWCHAR
#else
#define SQLTCHAR SQLCHAR
#endif  /* UNICODE */

#endif     /* RC_INVOKED */
#endif /* #ifndef __SQLTYPES */
