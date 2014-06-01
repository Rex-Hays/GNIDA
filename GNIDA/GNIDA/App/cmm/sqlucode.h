/*****************************************************************
** SQLUCODE.H - This is the the unicode include for ODBC Core functions.
**
** preconditions:
**      #include "windows.h"
**		#incluee "sql.h"
**
** (C) Copyright 1990 - 1998 By Microsoft Corp.
**
**		Created 6/20 for 3.00 specification
*********************************************************************/

#ifndef __SQLUCODE
#define __SQLUCODE

#include "sqlext.h"

#define SQL_WCHAR		 	-8
#define SQL_WVARCHAR	 	-9
#define SQL_WLONGVARCHAR 	-10
#define SQL_C_WCHAR			SQL_WCHAR

#ifdef UNICODE
#define SQL_C_TCHAR		SQL_C_WCHAR
#else
#define SQL_C_TCHAR		SQL_C_CHAR
#endif

#define SQL_SQLSTATE_SIZEW	10	/* size of SQLSTATE for unicode */

#ifndef RC_INVOKED

// UNICODE versions

extern WINAPI "odbc32.dll" {
	SQLRETURN SQLColAttributeW(SQLHSTMT	hstmt,SQLUSMALLINT iCol,SQLUSMALLINT iField,
		SQLPOINTER pCharAttr,SQLSMALLINT cbCharAttrMax,dword pcbCharAttr,SQLPOINTER	pNumAttr);
	SQLRETURN SQLColAttributesW(SQLHSTMT hstmt,SQLUSMALLINT icol,SQLUSMALLINT fDescType,
		SQLPOINTER rgbDesc,SQLSMALLINT cbDescMax,dword pcbDesc,dword pfDesc);
	SQLRETURN SQLConnectW(SQLHDBC hdbc,dword szDSN,SQLSMALLINT cbDSN,dword szUID,
    SQLSMALLINT cbUID,dword szAuthStr,SQLSMALLINT cbAuthStr);
	SQLRETURN SQLDescribeColW(SQLHSTMT hstmt,SQLUSMALLINT icol,dword szColName,
    SQLSMALLINT cbColNameMax,dword pcbColName,dword pfSqlType,dword pcbColDef,
    dword pibScale,dword pfNullable);
	SQLRETURN SQLErrorW(SQLHENV henv,SQLHDBC hdbc,SQLHSTMT hstmt,dword szSqlState,
    dword pfNativeError,dword szErrorMsg,SQLSMALLINT cbErrorMsgMax,dword pcbErrorMsg);
	SQLRETURN SQLExecDirectW(SQLHSTMT hstmt,dword szSqlStr,SQLINTEGER cbSqlStr);
	SQLRETURN SQLGetConnectAttrW(SQLHDBC hdbc,SQLINTEGER fAttribute,SQLPOINTER rgbValue,
		SQLINTEGER cbValueMax,dword pcbValue);
	SQLRETURN SQLGetCursorNameW(SQLHSTMT hstmt,dword szCursor,SQLSMALLINT cbCursorMax,dword pcbCursor);

#if (ODBCVER >= 0x0300)
	SQLRETURN SQLSetDescFieldW(SQLHDESC DescriptorHandle,SQLSMALLINT RecNumber,
		SQLSMALLINT FieldIdentifier,SQLPOINTER Value,SQLINTEGER BufferLength);
	SQLRETURN SQLGetDescFieldW(SQLHDESC hdesc,SQLSMALLINT iRecord,SQLSMALLINT iField,
		SQLPOINTER rgbValue,SQLINTEGER cbValueMax,dword pcbValue);
	SQLRETURN SQLGetDescRecW(SQLHDESC hdesc,SQLSMALLINT iRecord,dword szName,
		SQLSMALLINT cbNameMax,dword pcbName,dword pfType,dword pfSubType,dword pLength,
		dword pPrecision,dword pScale,dword pNullable);
	SQLRETURN SQLGetDiagFieldW(SQLSMALLINT fHandleType,SQLHANDLE handle,SQLSMALLINT iRecord,
		SQLSMALLINT fDiagField,SQLPOINTER rgbDiagInfo,SQLSMALLINT cbDiagInfoMax,dword pcbDiagInfo);
	SQLRETURN SQLGetDiagRecW(SQLSMALLINT fHandleType,SQLHANDLE handle,SQLSMALLINT iRecord,
		dword szSqlState,dword pfNativeError,dword szErrorMsg,SQLSMALLINT cbErrorMsgMax,dword pcbErrorMsg);
#endif

	SQLRETURN SQLPrepareW(SQLHSTMT hstmt,dword szSqlStr,SQLINTEGER cbSqlStr);
	SQLRETURN SQLSetConnectAttrW(SQLHDBC hdbc,SQLINTEGER fAttribute,SQLPOINTER rgbValue,SQLINTEGER cbValue);
	SQLRETURN SQLSetCursorNameW(SQLHSTMT hstmt,dword szCursor,SQLSMALLINT cbCursor);
	SQLRETURN SQLColumnsW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLGetConnectOptionW(SQLHDBC hdbc,SQLUSMALLINT fOption,SQLPOINTER pvParam);
	SQLRETURN SQLGetInfoW(SQLHDBC hdbc,SQLUSMALLINT fInfoType,SQLPOINTER rgbInfoValue,
		SQLSMALLINT cbInfoValueMax,dword pcbInfoValue);
	SQLRETURN SQLGetTypeInfoW(SQLHSTMT	StatementHandle,SQLSMALLINT	DataType);
	SQLRETURN SQLSetConnectOptionW(SQLHDBC hdbc,SQLUSMALLINT fOption,SQLULEN vParam);
	SQLRETURN SQLSpecialColumnsW(SQLHSTMT hstmt,SQLUSMALLINT fColType,dword szCatalogName,
		SQLSMALLINT cbCatalogName,dword szSchemaName,SQLSMALLINT cbSchemaName,
		dword szTableName,SQLSMALLINT cbTableName,SQLUSMALLINT fScope,SQLUSMALLINT fNullable);
	SQLRETURN SQLStatisticsW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,SQLUSMALLINT fUnique,SQLUSMALLINT fAccuracy);
	SQLRETURN SQLTablesW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,dword szTableType,SQLSMALLINT cbTableType);
	SQLRETURN SQLDataSourcesW(SQLHENV henv,SQLUSMALLINT fDirection,dword szDSN,
		SQLSMALLINT cbDSNMax,dword pcbDSN,dword szDescription,SQLSMALLINT cbDescriptionMax,
    dword pcbDescription);
	SQLRETURN SQLDriverConnectW(SQLHDBC hdbc,SQLHWND hwnd,dword szConnStrIn,
    SQLSMALLINT cbConnStrIn,dword szConnStrOut,SQLSMALLINT cbConnStrOutMax,
    dword pcbConnStrOut,SQLUSMALLINT fDriverCompletion);
	SQLRETURN SQLBrowseConnectW(SQLHDBC hdbc,dword szConnStrIn,SQLSMALLINT cbConnStrIn,
		dword szConnStrOut,SQLSMALLINT cbConnStrOutMax,dword pcbConnStrOut);
	SQLRETURN SQLColumnPrivilegesW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLGetStmtAttrW(SQLHSTMT hstmt,SQLINTEGER fAttribute,SQLPOINTER rgbValue,
		SQLINTEGER cbValueMax,dword pcbValue);
	SQLRETURN SQLSetStmtAttrW(SQLHSTMT hstmt,SQLINTEGER fAttribute,SQLPOINTER rgbValue,
		SQLINTEGER cbValueMax);
	SQLRETURN SQLForeignKeysW(SQLHSTMT hstmt,dword szPkCatalogName,SQLSMALLINT cbPkCatalogName,
		dword szPkSchemaName,SQLSMALLINT cbPkSchemaName,dword szPkTableName,
		SQLSMALLINT cbPkTableName,dword szFkCatalogName,SQLSMALLINT cbFkCatalogName,
		dword szFkSchemaName,SQLSMALLINT cbFkSchemaName,dword szFkTableName,SQLSMALLINT cbFkTableName);
	SQLRETURN SQLNativeSqlW(SQLHDBC hdbc,dword szSqlStrIn,SQLINTEGER cbSqlStrIn,
		dword szSqlStr,SQLINTEGER cbSqlStrMax,dword pcbSqlStr);
	SQLRETURN SQLPrimaryKeysW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,SQLSMALLINT cbTableName);
	SQLRETURN SQLProcedureColumnsW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szProcName,SQLSMALLINT cbProcName,
		dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLProceduresW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szProcName,SQLSMALLINT cbProcName);
	SQLRETURN SQLTablePrivilegesW(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,SQLSMALLINT cbTableName);
	SQLRETURN SQLDriversW(SQLHENV henv,SQLUSMALLINT fDirection,dword szDriverDesc,
		SQLSMALLINT cbDriverDescMax,dword pcbDriverDesc,dword szDriverAttributes,
		SQLSMALLINT cbDrvrAttrMax,dword pcbDrvrAttr);

// ANSI versions
	SQLRETURN SQLColAttributeA(SQLHSTMT	hstmt,SQLSMALLINT	iCol,SQLSMALLINT iField,
		SQLPOINTER pCharAttr,SQLSMALLINT cbCharAttrMax,dword pcbCharAttr,SQLPOINTER	pNumAttr);
	SQLRETURN SQLColAttributesA(SQLHSTMT hstmt,SQLUSMALLINT icol,SQLUSMALLINT fDescType,
		SQLPOINTER rgbDesc,SQLSMALLINT cbDescMax,dword pcbDesc,dword pfDesc);
	SQLRETURN SQLConnectA(SQLHDBC hdbc,dword szDSN,SQLSMALLINT cbDSN,dword szUID,
		SQLSMALLINT cbUID,dword szAuthStr,SQLSMALLINT cbAuthStr);
	SQLRETURN SQLDescribeColA(SQLHSTMT hstmt,SQLUSMALLINT icol,dword szColName,
    SQLSMALLINT cbColNameMax,dword pcbColName,dword pfSqlType,dword pcbColDef,
    dword pibScale,dword pfNullable);
	SQLRETURN SQLErrorA(SQLHENV henv,SQLHDBC hdbc,SQLHSTMT hstmt,dword szSqlState,
		dword pfNativeError,dword szErrorMsg,SQLSMALLINT cbErrorMsgMax,dword pcbErrorMsg);
	SQLRETURN SQLExecDirectA(SQLHSTMT hstmt,dword szSqlStr,SQLINTEGER cbSqlStr);
	SQLRETURN SQLGetConnectAttrA(SQLHDBC hdbc,SQLINTEGER fAttribute,SQLPOINTER rgbValue,
		SQLINTEGER cbValueMax,dword pcbValue);
	SQLRETURN SQLGetCursorNameA(SQLHSTMT hstmt,dword szCursor,SQLSMALLINT cbCursorMax,dword pcbCursor);

#if (ODBCVER >= 0x0300)
	SQLRETURN SQLGetDescFieldA(SQLHDESC hdesc,SQLSMALLINT iRecord,SQLSMALLINT iField,
		SQLPOINTER rgbValue,SQLINTEGER cbValueMax,dword pcbValue);
	SQLRETURN SQLGetDescRecA(SQLHDESC hdesc,SQLSMALLINT iRecord,dword szName,
		SQLSMALLINT cbNameMax,dword pcbName,dword pfType,dword pfSubType,
		dword pLength,dword pPrecision,dword pScale,dword pNullable);
	SQLRETURN SQLGetDiagFieldA(SQLSMALLINT fHandleType,SQLHANDLE handle,SQLSMALLINT iRecord,
		SQLSMALLINT fDiagField,SQLPOINTER rgbDiagInfo,SQLSMALLINT cbDiagInfoMax,dword pcbDiagInfo);
	SQLRETURN SQLGetDiagRecA(SQLSMALLINT fHandleType,SQLHANDLE handle,SQLSMALLINT iRecord,
		dword szSqlState,dword pfNativeError,dword szErrorMsg,SQLSMALLINT cbErrorMsgMax,
		dword pcbErrorMsg);
	SQLRETURN SQLGetStmtAttrA(SQLHSTMT hstmt,SQLINTEGER fAttribute,SQLPOINTER rgbValue,
		SQLINTEGER cbValueMax,dword pcbValue);
#endif

	SQLRETURN SQLGetTypeInfoA(SQLHSTMT StatementHandle,SQLSMALLINT DataTyoe);
	SQLRETURN SQLPrepareA(SQLHSTMT hstmt,dword szSqlStr,SQLINTEGER cbSqlStr);
	SQLRETURN SQLSetConnectAttrA(SQLHDBC hdbc,SQLINTEGER fAttribute,
		SQLPOINTER rgbValue,SQLINTEGER cbValue);
	SQLRETURN SQLSetCursorNameA(SQLHSTMT hstmt,dword szCursor,SQLSMALLINT cbCursor);
	SQLRETURN SQLColumnsA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLGetConnectOptionA(SQLHDBC hdbc,SQLUSMALLINT fOption,SQLPOINTER pvParam);
	SQLRETURN SQLGetInfoA(SQLHDBC hdbc,SQLUSMALLINT fInfoType,SQLPOINTER rgbInfoValue,
		SQLSMALLINT cbInfoValueMax,dword pcbInfoValue);
	SQLRETURN SQLGetStmtOptionA(SQLHSTMT hstmt,SQLUSMALLINT fOption,SQLPOINTER pvParam);
	SQLRETURN SQLSetConnectOptionA(SQLHDBC hdbc,SQLUSMALLINT fOption,SQLULEN vParam);
	SQLRETURN SQLSetStmtOptionA(SQLHSTMT hstmt,SQLUSMALLINT fOption,SQLULEN vParam);
	SQLRETURN SQLSpecialColumnsA(SQLHSTMT hstmt,SQLUSMALLINT fColType,dword szCatalogName,
		SQLSMALLINT cbCatalogName,dword szSchemaName,SQLSMALLINT cbSchemaName,
		dword szTableName,SQLSMALLINT cbTableName,SQLUSMALLINT fScope,SQLUSMALLINT fNullable);
	SQLRETURN SQLStatisticsA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
    SQLSMALLINT cbTableName,SQLUSMALLINT fUnique,SQLUSMALLINT fAccuracy);
	SQLRETURN SQLTablesA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,SQLSMALLINT cbTableName,
    dword szTableType,SQLSMALLINT cbTableType);
	SQLRETURN SQLDataSourcesA(SQLHENV henv,SQLUSMALLINT fDirection,dword szDSN,
		SQLSMALLINT cbDSNMax,dword pcbDSN,dword szDescription,
		SQLSMALLINT cbDescriptionMax,dword pcbDescription);
	SQLRETURN SQLDriverConnectA(SQLHDBC hdbc,SQLHWND hwnd,dword szConnStrIn,
		SQLSMALLINT cbConnStrIn,dword szConnStrOut,SQLSMALLINT cbConnStrOutMax,
		dword pcbConnStrOut,SQLUSMALLINT fDriverCompletion);
	SQLRETURN SQLBrowseConnectA(SQLHDBC hdbc,dword szConnStrIn,SQLSMALLINT cbConnStrIn,
		dword szConnStrOut,SQLSMALLINT cbConnStrOutMax,dword pcbConnStrOut);
	SQLRETURN SQLColumnPrivilegesA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,
		SQLSMALLINT cbTableName,dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLDescribeParamA(SQLHSTMT hstmt,SQLUSMALLINT ipar,dword pfSqlType,
		dword pcbParamDef,dword pibScale,dword pfNullable);
	SQLRETURN SQLForeignKeysA(SQLHSTMT hstmt,dword szPkCatalogName,SQLSMALLINT cbPkCatalogName,
		dword szPkSchemaName,SQLSMALLINT cbPkSchemaName,dword szPkTableName,SQLSMALLINT cbPkTableName,
		dword szFkCatalogName,SQLSMALLINT cbFkCatalogName,dword szFkSchemaName,
		SQLSMALLINT cbFkSchemaName,dword szFkTableName,SQLSMALLINT cbFkTableName);
	SQLRETURN SQLNativeSqlA(SQLHDBC hdbc,dword szSqlStrIn,SQLINTEGER cbSqlStrIn,
		dword szSqlStr,SQLINTEGER cbSqlStrMax,dword pcbSqlStr);
	SQLRETURN SQLPrimaryKeysA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,SQLSMALLINT cbTableName);
	SQLRETURN SQLProcedureColumnsA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szProcName,SQLSMALLINT cbProcName,
		dword szColumnName,SQLSMALLINT cbColumnName);
	SQLRETURN SQLProceduresA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szProcName,SQLSMALLINT cbProcName);
	SQLRETURN SQLTablePrivilegesA(SQLHSTMT hstmt,dword szCatalogName,SQLSMALLINT cbCatalogName,
		dword szSchemaName,SQLSMALLINT cbSchemaName,dword szTableName,SQLSMALLINT cbTableName);
	SQLRETURN SQLDriversA(SQLHENV henv,SQLUSMALLINT fDirection,dword szDriverDesc,
		SQLSMALLINT cbDriverDescMax,dword pcbDriverDesc,dword szDriverAttributes,
		SQLSMALLINT cbDrvrAttrMax,dword pcbDrvrAttr);
}
//---------------------------------------------
// Mapping macros for Unicode
//---------------------------------------------
#ifndef	SQL_NOUNICODEMAP	// define this to disable the mapping
#ifdef 	UNICODE
#define	SQLColAttribute		SQLColAttributeW
#define	SQLColAttributes	SQLColAttributesW
#define	SQLConnect			SQLConnectW
#define	SQLDescribeCol		SQLDescribeColW
#define	SQLError			SQLErrorW
#define	SQLExecDirect		SQLExecDirectW
#define	SQLGetConnectAttr	SQLGetConnectAttrW
#define	SQLGetCursorName	SQLGetCursorNameW
#define	SQLGetDescField		SQLGetDescFieldW
#define	SQLGetDescRec		SQLGetDescRecW
#define	SQLGetDiagField		SQLGetDiagFieldW
#define	SQLGetDiagRec		SQLGetDiagRecW
#define	SQLPrepare			SQLPrepareW
#define	SQLSetConnectAttr	SQLSetConnectAttrW
#define	SQLSetCursorName	SQLSetCursorNameW
#define	SQLSetDescField		SQLSetDescFieldW
#define SQLSetStmtAttr		SQLSetStmtAttrW
#define SQLGetStmtAttr		SQLGetStmtAttrW
#define	SQLColumns			SQLColumnsW
#define	SQLGetConnectOption	SQLGetConnectOptionW
#define	SQLGetInfo			SQLGetInfoW
#define SQLGetTypeInfo		SQLGetTypeInfoW
#define	SQLSetConnectOption	SQLSetConnectOptionW
#define	SQLSpecialColumns	SQLSpecialColumnsW
#define	SQLStatistics		SQLStatisticsW
#define	SQLTables			SQLTablesW
#define	SQLDataSources		SQLDataSourcesW
#define	SQLDriverConnect	SQLDriverConnectW
#define	SQLBrowseConnect	SQLBrowseConnectW
#define	SQLColumnPrivileges	SQLColumnPrivilegesW
#define	SQLForeignKeys		SQLForeignKeysW
#define	SQLNativeSql		SQLNativeSqlW
#define	SQLPrimaryKeys		SQLPrimaryKeysW
#define	SQLProcedureColumns	SQLProcedureColumnsW
#define	SQLProcedures		SQLProceduresW
#define	SQLTablePrivileges	SQLTablePrivilegesW
#define	SQLDrivers			SQLDriversW
#endif	/* UNICODE */
#endif	/* SQL_NOUNICODEMAP	*/

#endif /* RC_INVOKED */

#endif  /* #ifndef __SQLUCODE */
