//+---------------------------------------------------------------------------
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//  File:       objbase.h
//  Contents:   Component object model defintions.
//----------------------------------------------------------------------------

//#include <rpc.h>
//#include <rpcndr.h>
#if !defined( _OBJBASE_H_ )
#define _OBJBASE_H_

#pragma option(push,8)

/****** Interface Declaration ***********************************************/
/*
 *      These are macros for declaring interfaces.  They exist so that
 *      a single definition of the interface is simulataneously a proper
 *      declaration of the interface structures (C++ abstract classes)
 *      for both C and C++.
 *      DECLARE_INTERFACE(iface) is used to declare an interface that does
 *      not derive from a base interface.
 *      DECLARE_INTERFACE_(iface, baseiface) is used to declare an interface
 *      that does derive from a base interface.
 *      By default if the source file has a .c extension the C version of
 *      the interface declaratations will be expanded; if it has a .cpp
 *      extension the C++ version will be expanded. if you want to force
 *      the C version expansion even though the source file has a .cpp
 *      extension, then define the macro "CINTERFACE".
 *      eg.     cl -DCINTERFACE file.cpp
 *      Example Interface declaration:
 *          #undef  INTERFACE
 *          #define INTERFACE   IClassFactory
 *          DECLARE_INTERFACE_(IClassFactory, IUnknown)
 *          {
 *              // *** IUnknown methods ***
 *              STDMETHOD(QueryInterface) (THIS_
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObj) PURE;
 *              STDMETHOD_(ULONG,AddRef) (THIS) PURE;
 *              STDMETHOD_(ULONG,Release) (THIS) PURE;
 *
 *              // *** IClassFactory methods ***
 *              STDMETHOD(CreateInstance) (THIS_
 *                                        LPUNKNOWN pUnkOuter,
 *                                        REFIID riid,
 *                                        LPVOID FAR* ppvObject) PURE;
 *          };
 *      Example C++ expansion:
 *          struct FAR IClassFactory : public IUnknown
 *          {
 *              virtual HRESULT STDMETHODCALLTYPE QueryInterface(
 *                                                  IID FAR& riid,
 *                                                  LPVOID FAR* ppvObj) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE AddRef(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE Release(void) = 0;
 *              virtual HRESULT STDMETHODCALLTYPE CreateInstance(
 *                                              LPUNKNOWN pUnkOuter,
 *                                              IID FAR& riid,
 *                                              LPVOID FAR* ppvObject) = 0;
 *          };
 *          NOTE: Our documentation says '#define interface class' but we use
 *          'struct' instead of 'class' to keep a lot of 'public:' lines
 *          out of the interfaces.  The 'FAR' forces the 'this' pointers to
 *          be far, which is what we need.
 *      Example C expansion:
 *          typedef struct IClassFactory
 *          {
 *              const struct IClassFactoryVtbl FAR* lpVtbl;
 *          } IClassFactory;
 *          typedef struct IClassFactoryVtbl IClassFactoryVtbl;
 *          struct IClassFactoryVtbl
 *          {
 *              HRESULT (STDMETHODCALLTYPE * QueryInterface) (
 *                                                  IClassFactory FAR* This,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObj) ;
 *              HRESULT (STDMETHODCALLTYPE * AddRef) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * Release) (IClassFactory FAR* This) ;
 *              HRESULT (STDMETHODCALLTYPE * CreateInstance) (
 *                                                  IClassFactory FAR* This,
 *                                                  LPUNKNOWN pUnkOuter,
 *                                                  IID FAR* riid,
 *                                                  LPVOID FAR* ppvObject);
 *              HRESULT (STDMETHODCALLTYPE * LockServer) (
 *                                                  IClassFactory FAR* This,
 *                                                  BOOL fLock);
 *          };
 */
/****** Additional basic types **********************************************/
//#include <stdlib.h>

//#define LISet32(li,v) ((li).HighPart = ((LONG) (v)) < 0 ? -1 : 0, (li).LowPart = (v))
//#define ULISet32(li,v) ((li).HighPart = 0, (li).LowPart = (v))
#define CLSCTX_INPROC           CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER

// With DCOM, CLSCTX_REMOTE_SERVER should be included
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
#define CLSCTX_ALL              CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER| \
                                 CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER
#define CLSCTX_SERVER           CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER
#else
#define CLSCTX_ALL              CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER|CLSCTX_LOCAL_SERVER
#define CLSCTX_SERVER           CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER
#endif

// class registration flags; passed to CoRegisterClassObject
enum REGCLS{
  REGCLS_SINGLEUSE = 0,       // class object only generates one instance
  REGCLS_MULTIPLEUSE = 1,     // same class object genereates multiple inst.
                              // and local automatically goes into inproc tbl.
  REGCLS_MULTI_SEPARATE = 2,  // multiple use, but separate control over each
                              // context.
  REGCLS_SUSPENDED      = 4,  // register is as suspended, will be activated
                              // when app calls CoResumeClassObjects
  REGCLS_SURROGATE      = 8   // must be used when a surrogate process
                              // is registering a class object that will be
                              // loaded in the surrogate
};

// interface marshaling definitions
#define MARSHALINTERFACE_MIN 500 // minimum number of bytes for interface marshl

// Common typedefs for paramaters used in Storage API's, gleamed from storage.h
// Also contains Storage error codes, which should be moved into the storage
// idl files.
#define CWCSTORAGENAME 32

/* Storage instantiation modes */
#define STGM_DIRECT             0x00000000L
#define STGM_TRANSACTED         0x00010000L
#define STGM_SIMPLE             0x08000000L
#define STGM_READ               0x00000000L
#define STGM_WRITE              0x00000001L
#define STGM_READWRITE          0x00000002L
#define STGM_SHARE_DENY_NONE    0x00000040L
#define STGM_SHARE_DENY_READ    0x00000030L
#define STGM_SHARE_DENY_WRITE   0x00000020L
#define STGM_SHARE_EXCLUSIVE    0x00000010L
#define STGM_PRIORITY           0x00040000L
#define STGM_DELETEONRELEASE    0x04000000L
#define STGM_NOSCRATCH          0x00100000L
#define STGM_CREATE             0x00001000L
#define STGM_CONVERT            0x00020000L
#define STGM_FAILIFTHERE        0x00000000L
#define STGM_NOSNAPSHOT         0x00200000L
#define STGM_DIRECT_SWMR        0x00400000L

/*  flags for internet asyncronous and layout docfile */
#define ASYNC_MODE_COMPATIBILITY    0x00000001L
#define ASYNC_MODE_DEFAULT          0x00000000L
#define STGTY_REPEAT                0x00000100L
#define STG_TOEND                   0xFFFFFFFFL
#define STG_LAYOUT_SEQUENTIAL       0x00000000L
#define STG_LAYOUT_INTERLEAVED      0x00000001L
#define STGFMT_STORAGE          0
#define STGFMT_NATIVE           1
#define STGFMT_FILE             3
#define STGFMT_ANY              4
#define STGFMT_DOCFILE          5

// This is a legacy define to allow old component to builds
#define STGFMT_DOCUMENT         0

#include <wtypes.h>
//#include <unknwn.h>
//#include <objidl.h>

#include <guiddef.h>

/*#ifndef INITGUID
#include <cguid.h>
#endif*/

// COM initialization flags; passed to CoInitialize.
enum COINIT{
  COINIT_APARTMENTTHREADED  = 0x2,      // Apartment model
#if  (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
  // These constants are only valid on Windows NT 4.0
  COINIT_MULTITHREADED      = 0x0,      // OLE calls objects on any thread.
  COINIT_DISABLE_OLE1DDE    = 0x4,      // Don't use DDE for Ole1 support.
  COINIT_SPEED_OVER_MEMORY  = 0x8,      // Trade memory for speed.
#endif // DCOM
};

/* flags for CoGetStdMarshalEx */
enum STDMSHLFLAGS{
  SMEXF_SERVER     = 0x01,       // server side aggregated std marshaler
  SMEXF_HANDLER    = 0x02        // client side (handler) agg std marshaler
};

/* Flags for Synchronization API and Classes */
enum COWAIT_FLAGS{
  COWAIT_WAITALL = 1,
  COWAIT_ALERTABLE = 2
};

// STG initialization options for StgCreateStorageEx and StgOpenStorageEx
#define STGOPTIONS_VERSION 2

struct STGOPTIONS
{
  USHORT usVersion;            // Versions 1 and 2 supported
  USHORT reserved;             // must be 0 for padding
  ULONG ulSectorSize;          // docfile header sector size (512)
  WCHAR *pwcsTemplateFile;  // version 2 or above
};

/****** STD Object API Prototypes *****************************************/
extern WINAPI "ole32.dll"{
	DWORD CoBuildVersion(VOID);
/* init/uninit */
	CoInitialize(LPVOID pvReserved);
	void CoUninitialize(void);
	CoGetMalloc(DWORD dwMemContext,dword ppMalloc);
	DWORD CoGetCurrentProcess(void);
	CoRegisterMallocSpy(dword pMallocSpy);
	CoRevokeMallocSpy(void);
	CoCreateStandardMalloc(DWORD memctx,dword ppMalloc);
	CoInitializeEx(LPVOID pvReserved,DWORD dwCoInit);
	CoGetCallerTID(LPDWORD lpdwTID );
	ULONG DebugCoGetRpcFault(void);
	void DebugCoSetRpcFault(ULONG);
/* COM+ APIs */
	CoGetObjectContext(dword riid,dword ppv);
/* register/revoke/get class objects */
	CoGetClassObject(dword rclsid,DWORD dwClsContext,LPVOID pvReserved,dword riid,dword ppv);
	CoRegisterClassObject(dword rclsid,dword pUnk,DWORD dwClsContext,DWORD flags,LPDWORD lpdwRegister);
	CoRevokeClassObject(DWORD dwRegister);
	CoResumeClassObjects(void);
	CoSuspendClassObjects(void);
	ULONG CoAddRefServerProcess(void);
	ULONG CoReleaseServerProcess(void);
	CoGetPSClsid(dword riid,dword pClsid);
	CoRegisterPSClsid(dword riid,dword rclsid);
// Registering surrogate processes
	CoRegisterSurrogate(dword pSurrogate);
/* marshaling interface pointers */
	CoGetMarshalSizeMax(dword pulSize,dword riid,dword pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags);
	CoMarshalInterface(dword pStm,dword riid,dword pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags);
	CoUnmarshalInterface(dword pStm,dword riid,dword ppv);
	CoMarshalHresult(dword pstm,dword hresult);
	CoUnmarshalHresult(dword pstm,dword phresult);
	CoReleaseMarshalData(dword pStm);
	CoDisconnectObject(dword pUnk,DWORD dwReserved);
	CoLockObjectExternal(dword pUnk,BOOL fLock,BOOL fLastUnlockReleases);
	CoGetStandardMarshal(dword riid,dword pUnk,DWORD dwDestContext,LPVOID pvDestContext,DWORD mshlflags,dword ppMarshal);
	CoGetStdMarshalEx(dword pUnkOuter,DWORD smexflags,dword ppUnkInner);
	BOOL CoIsHandlerConnected(dword pUnk);
// Apartment model inter-thread interface passing helpers
	CoMarshalInterThreadInterfaceInStream(dword riid,dword pUnk,dword ppStm);
	CoGetInterfaceAndReleaseStream(dword pStm,dword iid,dword ppv);
	CoCreateFreeThreadedMarshaler(dword  punkOuter,dword ppunkMarshal);
/* dll loading helpers; keeps track of ref counts and unloads all on exit */
	dword CoLoadLibrary(dword lpszLibName,BOOL bAutoFree);
	void CoFreeLibrary(dword hInst);
	void CoFreeAllLibraries(void);
	void CoFreeUnusedLibraries(void);
	void CoFreeUnusedLibrariesEx(DWORD dwUnloadDelay,DWORD dwReserved);
/* Call Security. */
	CoInitializeSecurity(dword pSecDesc,LONG cAuthSvc,dword asAuthSvc,dword pReserved1,
		DWORD dwAuthnLevel,DWORD dwImpLevel,dword pAuthList,DWORD dwCapabilities,dword pReserved3 );
	CoGetCallContext(dword riid,dword ppInterface);
	CoQueryProxyBlanket(dword pProxy,DWORD pwAuthnSvc,DWORD pAuthzSvc,dword pServerPrincName,
		DWORD pAuthnLevel,DWORD pImpLevel,dword pAuthInfo,DWORD pCapabilites);
	CoSetProxyBlanket(dword pProxy,DWORD dwAuthnSvc,DWORD dwAuthzSvc,dword pServerPrincName,
		DWORD dwAuthnLevel,DWORD dwImpLevel,dword pAuthInfo,DWORD dwCapabilities);
	CoCopyProxy(dword pProxy,dword ppCopy);
	CoQueryClientBlanket(DWORD pAuthnSvc,DWORD pAuthzSvc,dword pServerPrincName,
		DWORD pAuthnLevel,DWORD pImpLevel,dword pPrivs,DWORD pCapabilities);
	CoImpersonateClient();
	CoRevertToSelf();
	CoQueryAuthenticationServices(DWORD pcAuthSvc,dword asAuthSvc);
	CoSwitchCallContext(dword pNewObject,dword pOldObject);

#define COM_RIGHTS_EXECUTE 1
#define COM_RIGHTS_SAFE_FOR_SCRIPTING 2

	CoCreateInstance(dword rclsid,dword pUnkOuter,DWORD dwClsContext,dword riid,dword ppv);
	CoGetInstanceFromFile(dword pServerInfo,dword pClsid,dword punkOuter,
		DWORD dwClsCtx,DWORD grfMode,dword pwszName,DWORD dwCount,dword pResults);
	CoGetInstanceFromIStorage(dword pServerInfo,dword pClsid,dword punkOuter,
		DWORD dwClsCtx,dword pstg,DWORD dwCount,dword pResults);
	CoCreateInstanceEx(dword Clsid,dword punkOuter,DWORD dwClsCtx,dword pServerInfo,
		DWORD dwCount,dword pResults);
	CoGetCancelObject(DWORD dwThreadId,dword iid,dword ppUnk);
	CoSetCancelObject(dword pUnk);
	CoCancelCall(DWORD dwThreadId,ULONG ulTimeout);
	CoTestCancel();
	CoEnableCallCancellation(dword pReserved);
	CoDisableCallCancellation(dword pReserved);
	CoAllowSetForegroundWindow(dword pUnk,dword lpvReserved);
	DcomChannelSetHResult(dword pvReserved,dword pulReserved,HRESULT appsHR);
	StringFromCLSID(dword rclsid,dword lplpsz);
	CLSIDFromString(dword lpsz,dword pclsid);
	StringFromIID(dword rclsid,dword lplpsz);
	IIDFromString(dword lpsz,dword lpiid);
	BOOL CoIsOle1Class(dword rclsid);
	ProgIDFromCLSID(dword clsid,dword lplpszProgID);
	CLSIDFromProgID(dword lpszProgID,dword lpclsid);
	CLSIDFromProgIDEx(dword lpszProgID,dword lpclsid);
	int StringFromGUID2(dword rguid,dword lpsz,int cchMax);
	CoCreateGuid(dword pguid);
	BOOL CoFileTimeToDosDateTime(dword lpFileTime,dword lpDosDate,dword lpDosTime);
	BOOL CoDosDateTimeToFileTime(WORD nDosDate,WORD nDosTime,dword lpFileTime);
	CoFileTimeNow(dword lpFileTime );
	CoRegisterMessageFilter(dword lpMessageFilter,dword lplpMessageFilter);
	CoRegisterChannelHook(dword ExtensionUuid,dword pChannelHook);
	CoWaitForMultipleHandles(DWORD dwFlags,DWORD dwTimeout,ULONG cHandles,dword pHandles,LPDWORD lpdwindex);
	CoGetTreatAsClass(dword clsidOld,dword pClsidNew);
	CoTreatAsClass(dword clsidOld,dword clsidNew);
	DllGetClassObject(dword rclsid,dword riid,dword ppv);
	DllCanUnloadNow(void);
	LPVOID CoTaskMemAlloc(SIZE_T cb);
	LPVOID CoTaskMemRealloc(LPVOID pv,SIZE_T cb);
	void  CoTaskMemFree(LPVOID pv);
	CreateDataAdviseHolder(dword ppDAHolder);
	CreateDataCache(dword pUnkOuter,dword rclsid,dword iid,dword ppv);
	StgCreateDocfile(dword pwcsName,DWORD grfMode,DWORD reserved,dword ppstgOpen);
	StgCreateDocfileOnILockBytes(dword plkbyt,DWORD grfMode,DWORD reserved,dword ppstgOpen);
	StgOpenStorage(dword pwcsName,dword pstgPriority,DWORD grfMode,dword snbExclude,
		DWORD reserved,dword ppstgOpen);
	StgOpenStorageOnILockBytes(dword plkbyt,dword pstgPriority,DWORD grfMode,
		dword snbExclude,DWORD reserved,dword ppstgOpen);
	StgIsStorageFile(dword pwcsName);
	StgIsStorageILockBytes(dword plkbyt);
	StgSetTimes(dword lpszName,dword pctime,dword patime,dword pmtime);
	StgOpenAsyncDocfileOnIFillLockBytes(dword pflb,DWORD grfMode,DWORD asyncFlags,
		dword ppstgOpen);
	StgGetIFillLockBytesOnILockBytes(dword pilb,dword ppflb);
	StgGetIFillLockBytesOnFile(dword pwcsName,dword ppflb);
	StgOpenLayoutDocfile(dword pwcsDfName,DWORD grfMode,DWORD reserved,dword ppstgOpen);
	StgCreateStorageEx(dword pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,
		dword pStgOptions,dword reserved,dword riid,dword ppObjectOpen);
	StgOpenStorageEx(dword pwcsName,DWORD grfMode,DWORD stgfmt,DWORD grfAttrs,
		dword pStgOptions,dword reserved,dword riid,dword ppObjectOpen);
	BindMoniker(dword pmk,DWORD grfOpt,dword iidResult,dword ppvResult);
	CoInstall(dword pbc,DWORD dwFlags,dword pClassSpec,dword pQuery,LPWSTR pszCodeBase);
	CoGetObject(LPCWSTR pszName,dword pBindOptions,dword riid,dword ppv);
	MkParseDisplayName(dword pbc,dword szUserName,dword pchEaten,dword ppmk);
	MonikerRelativePathTo(dword pmkSrc,dword pmkDest,dword ppmkRelPath,BOOL dwReserved);
	MonikerCommonPrefixWith(dword pmkThis,dword pmkOther,dword ppmkCommon);
	CreateBindCtx(DWORD reserved,dword ppbc);
	CreateGenericComposite(dword pmkFirst,dword pmkRest,dword ppmkComposite);
	GetClassFile(dword szFilename,dword pclsid);
	CreateClassMoniker(dword rclsid,dword ppmk);
	CreateFileMoniker(dword lpszPathName,dword ppmk);
	CreateItemMoniker(dword lpszDelim,dword lpszItem,dword ppmk);
	CreateAntiMoniker(dword ppmk);
	CreatePointerMoniker(dword punk,dword ppmk);
	CreateObjrefMoniker(dword punk,dword ppmk);
	GetRunningObjectTable(DWORD reserved,dword pprot);
	CreateStdProgressIndicator(HWND hwndParent,dword pszTitle,dword pIbscCaller,dword ppIbsc);
	CreateStreamOnHGlobal(dword,BOOL,dword);
}
//#include <urlmon.h>
//#include <propidl.h>

#endif     // __OBJBASE_H__
