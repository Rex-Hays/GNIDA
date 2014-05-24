/*++ BUILD Version: 0001    // Increment this if a change has global effects
Copyright (c) Microsoft Corporation.  All rights reserved.
Module Name:
    Winreg.h
Abstract:
    This module contains the function prototypes and constant, type and
    structure definitions for the Windows 32-Bit Registry API.
--*/

#ifndef _WINREG_
#define _WINREG_

#ifndef WINVER
#define WINVER 0x0500   // version 5.0
#endif /* !WINVER */

// Requested Key access mask type.
//#define REGSAM dword

// Reserved Key Handles.
#define HKEY_CLASSES_ROOT           0x80000000
#define HKEY_CURRENT_USER           0x80000001
#define HKEY_LOCAL_MACHINE          0x80000002
#define HKEY_USERS                  0x80000003
#define HKEY_PERFORMANCE_DATA       0x80000004
#define HKEY_PERFORMANCE_TEXT       0x80000050
#define HKEY_PERFORMANCE_NLSTEXT    0x80000060
#define HKEY_CURRENT_CONFIG         0x80000005
#define HKEY_DYN_DATA               0x80000006

/*NOINC*/
#ifndef _PROVIDER_STRUCTS_DEFINED
#define _PROVIDER_STRUCTS_DEFINED

#define PROVIDER_KEEPS_VALUE_LENGTH 0x1
struct val_context {
  int valuelen;       // the total length of this value
  LPVOID value_context;   // provider's context
  LPVOID val_buff_ptr;    // where in the ouput buffer the value is.
};

struct PVALUE{           // Provider supplied value/context.
  LPSTR   pv_valuename;          // The value name pointer
  int pv_valuelen;
  LPVOID pv_value_context;
  DWORD pv_type;
};
#define PVALUEW PVALUE
#define PVALUEA PVALUE

struct REG_PROVIDER{
  dword pi_R0_1val;
  dword pi_R0_allvals;
  dword pi_R3_1val;
  dword pi_R3_allvals;
  DWORD pi_flags;    // capability flags (none defined yet).
  LPVOID pi_key_context;
};

#define  provider_info REG_PROVIDER

struct VALENT{
  LPSTR   ve_valuename;
  DWORD ve_valuelen;
  DWORD_PTR ve_valueptr;
  DWORD ve_type;
};
#define value_entA VALENT
#define value_entW VALENT
#define VALENTW VALENT
#define VALENTA VALENT

#endif // not(_PROVIDER_STRUCTS_DEFINED)
/*INC*/

// Default values for parameters that do not exist in the Win 3.1
// compatible APIs.
#define WIN31_CLASS                 NULL

#include <reason.h>             // get the public reasons

// API Prototypes.
extern WINAPI "advapi32.dll"{
	LONG RegCloseKey(HKEY hKey);
	LONG RegOverridePredefKey(HKEY hKey,HKEY hNewHKey);
	LONG RegOpenUserClassesRoot(HANDLE hToken,DWORD  dwOptions,dword samDesired,PHKEY  phkResult);
	LONG RegOpenCurrentUser(dword samDesired,PHKEY phkResult);
	LONG RegDisablePredefinedCache();
	LONG RegConnectRegistryA(LPCSTR lpMachineName,HKEY hKey,PHKEY phkResult);
	LONG RegConnectRegistryW(LPCWSTR lpMachineName,HKEY hKey,PHKEY phkResult);
#ifdef UNICODE
#define RegConnectRegistry  RegConnectRegistryW
#else
#define RegConnectRegistry  RegConnectRegistryA
#endif // !UNICODE

	LONG RegCreateKeyA(HKEY hKey,LPCSTR lpSubKey,PHKEY phkResult);
	LONG RegCreateKeyW(HKEY hKey,LPCWSTR lpSubKey,PHKEY phkResult);
#ifdef UNICODE
#define RegCreateKey  RegCreateKeyW
#else
#define RegCreateKey  RegCreateKeyA
#endif // !UNICODE

	LONG RegCreateKeyExA(HKEY hKey,LPCSTR lpSubKey,DWORD Reserved,LPSTR lpClass,
		DWORD dwOptions,dword samDesired,dword lpSecurityAttributes,PHKEY phkResult,LPDWORD lpdwDisposition);
	LONG RegCreateKeyExW(HKEY hKey,LPCWSTR lpSubKey,DWORD Reserved,LPWSTR lpClass,
		DWORD dwOptions,dword samDesired,dword lpSecurityAttributes,PHKEY phkResult,LPDWORD lpdwDisposition);
#ifdef UNICODE
#define RegCreateKeyEx  RegCreateKeyExW
#else
#define RegCreateKeyEx  RegCreateKeyExA
#endif // !UNICODE

	LONG RegDeleteKeyA(HKEY hKey,LPCSTR lpSubKey);
	LONG RegDeleteKeyW(HKEY hKey,LPCWSTR lpSubKey);
#ifdef UNICODE
#define RegDeleteKey  RegDeleteKeyW
#else
#define RegDeleteKey  RegDeleteKeyA
#endif // !UNICODE

	LONG RegDeleteValueA(HKEY hKey,LPCSTR lpValueName);
	LONG RegDeleteValueW(HKEY hKey,LPCWSTR lpValueName);
#ifdef UNICODE
#define RegDeleteValue  RegDeleteValueW
#else
#define RegDeleteValue  RegDeleteValueA
#endif // !UNICODE

	LONG RegEnumKeyA(HKEY hKey,DWORD dwIndex,LPSTR lpName,DWORD cbName);
	LONG RegEnumKeyW(HKEY hKey,DWORD dwIndex,LPWSTR lpName,DWORD cbName);
#ifdef UNICODE
#define RegEnumKey  RegEnumKeyW
#else
#define RegEnumKey  RegEnumKeyA
#endif // !UNICODE

	LONG RegEnumKeyExA(HKEY hKey,DWORD dwIndex,LPSTR lpName,LPDWORD lpcbName,
		LPDWORD lpReserved,LPSTR lpClass,LPDWORD lpcbClass,dword lpftLastWriteTime);
	LONG RegEnumKeyExW(HKEY hKey,DWORD dwIndex,LPWSTR lpName,LPDWORD lpcbName,
		LPDWORD lpReserved,LPWSTR lpClass,LPDWORD lpcbClass,dword lpftLastWriteTime);
#ifdef UNICODE
#define RegEnumKeyEx  RegEnumKeyExW
#else
#define RegEnumKeyEx  RegEnumKeyExA
#endif // !UNICODE

	LONG RegEnumValueA(HKEY hKey,DWORD dwIndex,LPSTR lpValueName,LPDWORD lpcbValueName,
		LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
	LONG RegEnumValueW(HKEY hKey,DWORD dwIndex,LPWSTR lpValueName,LPDWORD lpcbValueName,
		LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
#ifdef UNICODE
#define RegEnumValue  RegEnumValueW
#else
#define RegEnumValue  RegEnumValueA
#endif // !UNICODE

	LONG RegFlushKey(HKEY hKey);
	LONG RegGetKeySecurity(HKEY hKey,dword SecurityInformation,
		dword pSecurityDescriptor,LPDWORD lpcbSecurityDescriptor);
	LONG RegLoadKeyA(HKEY hKey,LPCSTR lpSubKey,LPCSTR lpFile);
	LONG RegLoadKeyW(HKEY hKey,LPCWSTR lpSubKey,LPCWSTR lpFile);
#ifdef UNICODE
#define RegLoadKey  RegLoadKeyW
#else
#define RegLoadKey  RegLoadKeyA
#endif // !UNICODE

	LONG RegNotifyChangeKeyValue(HKEY hKey,BOOL bWatchSubtree,DWORD dwNotifyFilter,
		HANDLE hEvent,BOOL fAsynchronus);
	LONG RegOpenKeyA(HKEY hKey,LPCSTR lpSubKey,PHKEY phkResult);
	LONG RegOpenKeyW(HKEY hKey,LPCWSTR lpSubKey,PHKEY phkResult);
#ifdef UNICODE
#define RegOpenKey  RegOpenKeyW
#else
#define RegOpenKey  RegOpenKeyA
#endif // !UNICODE

	LONG RegOpenKeyExA(HKEY hKey,LPCSTR lpSubKey,DWORD ulOptions,dword samDesired,PHKEY phkResult);
	LONG RegOpenKeyExW(HKEY hKey,LPCWSTR lpSubKey,DWORD ulOptions,dword samDesired,PHKEY phkResult);
#ifdef UNICODE
#define RegOpenKeyEx  RegOpenKeyExW
#else
#define RegOpenKeyEx  RegOpenKeyExA
#endif // !UNICODE

	LONG RegQueryInfoKeyA(HKEY hKey,LPSTR lpClass,LPDWORD lpcbClass,LPDWORD lpReserved,
		LPDWORD lpcSubKeys,LPDWORD lpcbMaxSubKeyLen,LPDWORD lpcbMaxClassLen,LPDWORD lpcValues,
		LPDWORD lpcbMaxValueNameLen,LPDWORD lpcbMaxValueLen,LPDWORD lpcbSecurityDescriptor,
		dword lpftLastWriteTime);
	LONG RegQueryInfoKeyW(HKEY hKey,LPWSTR lpClass,LPDWORD lpcbClass,LPDWORD lpReserved,
		LPDWORD lpcSubKeys,LPDWORD lpcbMaxSubKeyLen,LPDWORD lpcbMaxClassLen,LPDWORD lpcValues,
		LPDWORD lpcbMaxValueNameLen,LPDWORD lpcbMaxValueLen,LPDWORD lpcbSecurityDescriptor,
		dword lpftLastWriteTime);
#ifdef UNICODE
#define RegQueryInfoKey  RegQueryInfoKeyW
#else
#define RegQueryInfoKey  RegQueryInfoKeyA
#endif // !UNICODE

	LONG RegQueryValueA(HKEY hKey,LPCSTR lpSubKey,LPSTR lpValue,PLONG lpcbValue);
	LONG RegQueryValueW(HKEY hKey,LPCWSTR lpSubKey,LPWSTR lpValue,PLONG lpcbValue);
#ifdef UNICODE
#define RegQueryValue  RegQueryValueW
#else
#define RegQueryValue  RegQueryValueA
#endif // !UNICODE

	LONG RegQueryMultipleValuesA(HKEY hKey,dword val_list,DWORD num_vals,
		LPSTR lpValueBuf,LPDWORD ldwTotsize);
	LONG RegQueryMultipleValuesW(HKEY hKey,dword val_list,DWORD num_vals,
		LPWSTR lpValueBuf,LPDWORD ldwTotsize);
#ifdef UNICODE
#define RegQueryMultipleValues  RegQueryMultipleValuesW
#else
#define RegQueryMultipleValues  RegQueryMultipleValuesA
#endif // !UNICODE

	LONG RegQueryValueExA(HKEY hKey,LPCSTR lpValueName,LPDWORD lpReserved,
		LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
	LONG RegQueryValueExW(HKEY hKey,LPCWSTR lpValueName,LPDWORD lpReserved,
		LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
#ifdef UNICODE
#define RegQueryValueEx  RegQueryValueExW
#else
#define RegQueryValueEx  RegQueryValueExA
#endif // !UNICODE

	LONG RegReplaceKeyA(HKEY hKey,LPCSTR lpSubKey,LPCSTR lpNewFile,LPCSTR lpOldFile);
	LONG RegReplaceKeyW(HKEY hKey,LPCWSTR lpSubKey,LPCWSTR lpNewFile,LPCWSTR lpOldFile);
#ifdef UNICODE
#define RegReplaceKey  RegReplaceKeyW
#else
#define RegReplaceKey  RegReplaceKeyA
#endif // !UNICODE

	LONG RegRestoreKeyA(HKEY hKey,LPCSTR lpFile,DWORD dwFlags);
	LONG RegRestoreKeyW(HKEY hKey,LPCWSTR lpFile,DWORD dwFlags);
#ifdef UNICODE
#define RegRestoreKey  RegRestoreKeyW
#else
#define RegRestoreKey  RegRestoreKeyA
#endif // !UNICODE

	LONG RegSaveKeyA(HKEY hKey,LPCSTR lpFile,dword lpSecurityAttributes);
	LONG RegSaveKeyW(HKEY hKey,LPCWSTR lpFile,dword lpSecurityAttributes);
#ifdef UNICODE
#define RegSaveKey  RegSaveKeyW
#else
#define RegSaveKey  RegSaveKeyA
#endif // !UNICODE

	LONG RegSetKeySecurity(HKEY hKey,dword SecurityInformation,dword pSecurityDescriptor);
	LONG RegSetValueA(HKEY hKey,LPCSTR lpSubKey,DWORD dwType,LPCSTR lpData,DWORD cbData);
	LONG RegSetValueW(HKEY hKey,LPCWSTR lpSubKey,DWORD dwType,LPCWSTR lpData,DWORD cbData);
#ifdef UNICODE
#define RegSetValue  RegSetValueW
#else
#define RegSetValue  RegSetValueA
#endif // !UNICODE

	LONG RegSetValueExA(HKEY hKey,LPCSTR lpValueName,DWORD Reserved,DWORD dwType,
		dword lpData,DWORD cbData);
	LONG RegSetValueExW(HKEY hKey,LPCWSTR lpValueName,DWORD Reserved,DWORD dwType,
		dword lpData,DWORD cbData);
#ifdef UNICODE
#define RegSetValueEx  RegSetValueExW
#else
#define RegSetValueEx  RegSetValueExA
#endif // !UNICODE

	LONG RegUnLoadKeyA(HKEY hKey,LPCSTR lpSubKey);
	LONG RegUnLoadKeyW(HKEY hKey,LPCWSTR lpSubKey);
#ifdef UNICODE
#define RegUnLoadKey  RegUnLoadKeyW
#else
#define RegUnLoadKey  RegUnLoadKeyA
#endif // !UNICODE

// Remoteable System Shutdown APIs
	BOOL InitiateSystemShutdownA(LPSTR lpMachineName,LPSTR lpMessage,DWORD dwTimeout,
		BOOL bForceAppsClosed,BOOL bRebootAfterShutdown);
	BOOL InitiateSystemShutdownW(LPWSTR lpMachineName,LPWSTR lpMessage,DWORD dwTimeout,
		BOOL bForceAppsClosed,BOOL bRebootAfterShutdown);
#ifdef UNICODE
#define InitiateSystemShutdown  InitiateSystemShutdownW
#else
#define InitiateSystemShutdown  InitiateSystemShutdownA
#endif // !UNICODE

	BOOL AbortSystemShutdownA(LPSTR lpMachineName);
	BOOL AbortSystemShutdownW(LPWSTR lpMachineName);
#ifdef UNICODE
#define AbortSystemShutdown  AbortSystemShutdownW
#else
#define AbortSystemShutdown  AbortSystemShutdownA
#endif // !UNICODE

// defines for InitiateSystemShutdownEx reason codes
// Then for Historical reasons support some old symbols, internal only
#define REASON_SWINSTALL    SHTDN_REASON_MAJOR_SOFTWARE|SHTDN_REASON_MINOR_INSTALLATION
#define REASON_HWINSTALL    SHTDN_REASON_MAJOR_HARDWARE|SHTDN_REASON_MINOR_INSTALLATION
#define REASON_SERVICEHANG  SHTDN_REASON_MAJOR_SOFTWARE|SHTDN_REASON_MINOR_HUNG
#define REASON_UNSTABLE     SHTDN_REASON_MAJOR_SYSTEM|SHTDN_REASON_MINOR_UNSTABLE
#define REASON_SWHWRECONF   SHTDN_REASON_MAJOR_SOFTWARE|SHTDN_REASON_MINOR_RECONFIG
#define REASON_OTHER        SHTDN_REASON_MAJOR_OTHER|SHTDN_REASON_MINOR_OTHER
#define REASON_UNKNOWN      SHTDN_REASON_UNKNOWN
#define REASON_PLANNED_FLAG SHTDN_REASON_FLAG_PLANNED

	BOOL InitiateSystemShutdownExA(LPSTR lpMachineName,LPSTR lpMessage,DWORD dwTimeout,
		BOOL bForceAppsClosed,BOOL bRebootAfterShutdown,DWORD dwReason);
	BOOL InitiateSystemShutdownExW(LPWSTR lpMachineName,LPWSTR lpMessage,DWORD dwTimeout,
		BOOL bForceAppsClosed,BOOL bRebootAfterShutdown,DWORD dwReason);
#ifdef UNICODE
#define InitiateSystemShutdownEx  InitiateSystemShutdownExW
#else
#define InitiateSystemShutdownEx  InitiateSystemShutdownExA
#endif // !UNICODE

	LONG RegSaveKeyExA(HKEY hKey,LPCSTR lpFile,dword pSecurityAttributes,DWORD Flags);
	LONG RegSaveKeyExW(HKEY hKey,LPCWSTR lpFile,dword lpSecurityAttributes,DWORD Flags);
#ifdef UNICODE
#define RegSaveKeyEx  RegSaveKeyExW
#else
#define RegSaveKeyEx  RegSaveKeyExA
#endif // !UNICODE

	LONG Wow64Win32ApiEntry(DWORD dwFuncNumber,DWORD dwFlag,DWORD dwRes);

	BOOL GetUserNameA(LPSTR lpBuffer,LPDWORD nSize);
	BOOL GetUserNameW(LPWSTR lpBuffer,LPDWORD nSize);
#ifdef UNICODE
#define GetUserName  GetUserNameW
#else
#define GetUserName  GetUserNameA
#endif // !UNICODE

// Logon Support APIs
#define LOGON32_LOGON_INTERACTIVE       2
#define LOGON32_LOGON_NETWORK           3
#define LOGON32_LOGON_BATCH             4
#define LOGON32_LOGON_SERVICE           5
#define LOGON32_LOGON_UNLOCK            7
#define LOGON32_LOGON_NETWORK_CLEARTEXT 8
#define LOGON32_LOGON_NEW_CREDENTIALS   9

#define LOGON32_PROVIDER_DEFAULT    0
#define LOGON32_PROVIDER_WINNT35    1
#define LOGON32_PROVIDER_WINNT40    2
#define LOGON32_PROVIDER_WINNT50    3

	BOOL LogonUserA(LPSTR lpszUsername,LPSTR lpszDomain,LPSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,dword phToken);
	BOOL LogonUserW(LPWSTR lpszUsername,LPWSTR lpszDomain,LPWSTR lpszPassword,DWORD dwLogonType,DWORD dwLogonProvider,dword phToken);
#ifdef UNICODE
#define LogonUser  LogonUserW
#else
#define LogonUser  LogonUserA
#endif // !UNICODE

}

#endif // _WINREG_
