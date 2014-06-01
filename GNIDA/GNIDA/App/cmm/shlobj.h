//===========================================================================
// Copyright (c) Microsoft Corporation. All rights reserved.
// File: shlobj.h
//===========================================================================

#ifndef _SHLOBJ_H_
#define _SHLOBJ_H_

#ifndef _WINRESRC_
#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif
#endif

#define OLECHAR short
/*
#include <ole2.h>
#ifndef _PRSHT_H_
#include <prsht.h>
#endif
*/
#ifndef _INC_COMMCTRL
#include <commctrl.h>   // for LPTBBUTTON
#endif

/*
#ifndef INITGUID
#include <shlguid.h>
#endif /* !INITGUID */
*/
#pragma pack(push,1)
//#include <shtypes.h>
//#include <shobjidl.h>

//===========================================================================
// Task allocator API
//  All the shell extensions MUST use the task allocator (see OLE 2.0
// programming guild for its definition) when they allocate or free
// memory objects (mostly ITEMIDLIST) that are returned across any
// shell interfaces. There are two ways to access the task allocator
// from a shell extension depending on whether or not it is linked with
// OLE32.DLL or not (purely for efficiency).
// (1) A shell extension which calls any OLE API (i.e., linked with
//  OLE32.DLL) should call OLE's task allocator (by retrieving
//  the task allocator by calling CoGetMalloc API).
// (2) A shell extension which does not call any OLE API (i.e., not linked
//  with OLE32.DLL) should call the shell task allocator API (defined
//  below), so that the shell can quickly loads it when OLE32.DLL is not
//  loaded by any application at that point.
// Notes:
//  In next version of Windowso release, SHGetMalloc will be replaced by
// the following macro.
// #define SHGetMalloc(ppmem)   CoGetMalloc(MEMCTX_TASK, ppmem)
//===========================================================================
extern WINAPI "shell32.dll"{
	dword SHGetMalloc(dword ppMalloc);
}

//===========================================================================
// IContextMenu interface
// [OverView]
//  The shell uses the IContextMenu interface in following three cases.
// case-1: The shell is loading context menu extensions.
//   When the user clicks the right mouse button on an item within the shell's
//  name space (i.g., file, directory, server, work-group, etc.), it creates
//  the default context menu for its type, then loads context menu extensions
//  that are registered for that type (and its base type) so that they can
//  add extra menu items. Those context menu extensions are registered at
//  HKCR\{ProgID}\shellex\ContextMenuHandlers.
// case-2: The shell is retrieving a context menu of sub-folders in extended
//   name-space.
//   When the explorer's name space is extended by name space extensions,
//  the shell calls their IShellFolder::GetUIObjectOf to get the IContextMenu
//  objects when it creates context menus for folders under those extended
//  name spaces.
// case-3: The shell is loading non-default drag and drop handler for directories.
//   When the user performed a non-default drag and drop onto one of file
//  system folders (i.e., directories), it loads shell extensions that are
//  registered at HKCR\{ProgID}\DragDropHandlers.
// [Member functions]
// IContextMenu::QueryContextMenu
//   This member function may insert one or more menuitems to the specified
//  menu (hmenu) at the specified location (indexMenu which is never be -1).
//  The IDs of those menuitem must be in the specified range (idCmdFirst and
//  idCmdLast). It returns the maximum menuitem ID offset (ushort) in the
//  'code' field (low word) of the scode.
//   The uFlags specify the context. It may have one or more of following
//  flags.
//  CMF_DEFAULTONLY: This flag is passed if the user is invoking the default
//   action (typically by double-clicking, case 1 and 2 only). Context menu
//   extensions (case 1) should not add any menu items, and returns NOERROR.
//  CMF_VERBSONLY: The explorer passes this flag if it is constructing
//   a context menu for a short-cut object (case 1 and case 2 only). If this
//   flag is passed, it should not add any menu-items that is not appropriate
//   from a short-cut.
//    A good example is the "Delete" menuitem, which confuses the user
//   because it is not clear whether it deletes the link source item or the
//   link itself.
//  CMF_EXPLORER: The explorer passes this flag if it has the left-side pane
//   (case 1 and 2 only). Context menu extensions should ignore this flag.
//   High word (16-bit) are reserved for context specific communications
//  and the rest of flags (13-bit) are reserved by the system.
// IContextMenu::InvokeCommand
//   This member is called when the user has selected one of menuitems that
//  are inserted by previous QueryContextMenu member. In this case, the
//  LOWORD(lpici->lpVerb) contains the menuitem ID offset (menuitem ID -
//  idCmdFirst).
//   This member function may also be called programmatically. In such a case,
//  lpici->lpVerb specifies the canonical name of the command to be invoked,
//  which is typically retrieved by GetCommandString member previously.
//  Parameters in lpci:
//    cbSize -- Specifies the size of this structure (sizeof(*lpci))
//    hwnd   -- Specifies the owner window for any message/dialog box.
//    fMask  -- Specifies whether or not dwHotkey/hIcon paramter is valid.
//    lpVerb -- Specifies the command to be invoked.
//    lpParameters -- Parameters (optional)
//    lpDirectory  -- Working directory (optional)
//    nShow -- Specifies the flag to be passed to ShowWindow (SW_*).
//    dwHotKey -- Hot key to be assigned to the app after invoked (optional).
//    hIcon -- Specifies the icon (optional).
//    hMonitor -- Specifies the default monitor (optional).
// IContextMenu::GetCommandString
//   This member function is called by the explorer either to get the
//  canonical (language independent) command name (uFlags == GCS_VERB) or
//  the help text ((uFlags & GCS_HELPTEXT) != 0) for the specified command.
//  The retrieved canonical string may be passed to its InvokeCommand
//  member function to invoke a command programmatically. The explorer
//  displays the help texts in its status bar; therefore, the length of
//  the help text should be reasonably short (<40 characters).
//  Parameters:
//   idCmd -- Specifies menuitem ID offset (from idCmdFirst)
//   uFlags -- Either GCS_VERB or GCS_HELPTEXT
//   pwReserved -- Reserved (must pass NULL when calling, must ignore when called)
//   pszName -- Specifies the string buffer.
//   cchMax -- Specifies the size of the string buffer.
//===========================================================================

// QueryContextMenu uFlags
#define CMF_NORMAL              0x00000000
#define CMF_DEFAULTONLY         0x00000001
#define CMF_VERBSONLY           0x00000002
#define CMF_EXPLORE             0x00000004
#define CMF_NOVERBS             0x00000008
#define CMF_CANRENAME           0x00000010
#define CMF_NODEFAULT           0x00000020
#define CMF_INCLUDESTATIC       0x00000040
#define CMF_EXTENDEDVERBS       0x00000100      // rarely used verbs
#define CMF_RESERVED            0xffff0000      // View specific

// GetCommandString uFlags
#define GCS_VERBA        0x00000000     // canonical verb
#define GCS_HELPTEXTA    0x00000001     // help text (for status bar)
#define GCS_VALIDATEA    0x00000002     // validate command exists
#define GCS_VERBW        0x00000004     // canonical verb (unicode)
#define GCS_HELPTEXTW    0x00000005     // help text (unicode version)
#define GCS_VALIDATEW    0x00000006     // validate command exists (unicode)
#define GCS_UNICODE      0x00000004     // for bit testing - Unicode string

#ifdef UNICODE
#define GCS_VERB        GCS_VERBW
#define GCS_HELPTEXT    GCS_HELPTEXTW
#define GCS_VALIDATE    GCS_VALIDATEW
#else
#define GCS_VERB        GCS_VERBA
#define GCS_HELPTEXT    GCS_HELPTEXTA
#define GCS_VALIDATE    GCS_VALIDATEA
#endif

#define CMDSTR_NEWFOLDERA   "NewFolder"
#define CMDSTR_VIEWLISTA    "ViewList"
#define CMDSTR_VIEWDETAILSA "ViewDetails"
#define CMDSTR_NEWFOLDERW   L"NewFolder"
#define CMDSTR_VIEWLISTW    L"ViewList"
#define CMDSTR_VIEWDETAILSW L"ViewDetails"

#ifdef UNICODE
#define CMDSTR_NEWFOLDER    CMDSTR_NEWFOLDERW
#define CMDSTR_VIEWLIST     CMDSTR_VIEWLISTW
#define CMDSTR_VIEWDETAILS  CMDSTR_VIEWDETAILSW
#else
#define CMDSTR_NEWFOLDER    CMDSTR_NEWFOLDERA
#define CMDSTR_VIEWLIST     CMDSTR_VIEWLISTA
#define CMDSTR_VIEWDETAILS  CMDSTR_VIEWDETAILSA
#endif

#define CMIC_MASK_HOTKEY        SEE_MASK_HOTKEY
#define CMIC_MASK_ICON          SEE_MASK_ICON
#define CMIC_MASK_FLAG_NO_UI    SEE_MASK_FLAG_NO_UI
#define CMIC_MASK_UNICODE       SEE_MASK_UNICODE
#define CMIC_MASK_NO_CONSOLE    SEE_MASK_NO_CONSOLE
#define CMIC_MASK_HASLINKNAME   SEE_MASK_HASLINKNAME
#define CMIC_MASK_FLAG_SEP_VDM  SEE_MASK_FLAG_SEPVDM
#define CMIC_MASK_HASTITLE      SEE_MASK_HASTITLE
#define CMIC_MASK_ASYNCOK       SEE_MASK_ASYNCOK
#define CMIC_MASK_SHIFT_DOWN    0x10000000
#define CMIC_MASK_CONTROL_DOWN  0x20000000
#define CMIC_MASK_FLAG_LOG_USAGE SEE_MASK_FLAG_LOG_USAGE
#define CMIC_MASK_PTINVOKE      0x20000000

#pragma pack(push,8)

//NOTE: When SEE_MASK_HMONITOR is set, hIcon is treated as hMonitor
struct CMINVOKECOMMANDINFO {
  DWORD cbSize;        // sizeof(CMINVOKECOMMANDINFO)
  DWORD fMask;         // any combination of CMIC_MASK_*
  HWND hwnd;           // might be NULL (indicating no owner window)
  LPCSTR lpVerb;       // either a string or MAKEINTRESOURCE(idOffset)
  LPCSTR lpParameters; // might be NULL (indicating no parameter)
  LPCSTR lpDirectory;  // might be NULL (indicating no specific directory)
  int nShow;           // one of SW_ values for ShowWindow() API
  DWORD dwHotKey;
  HANDLE hIcon;
};

struct CMINVOKECOMMANDINFOEX{
  DWORD cbSize;        // must be sizeof(CMINVOKECOMMANDINFOEX)
  DWORD fMask;         // any combination of CMIC_MASK_*
  HWND hwnd;           // might be NULL (indicating no owner window)
  LPCSTR lpVerb;       // either a string or MAKEINTRESOURCE(idOffset)
  LPCSTR lpParameters; // might be NULL (indicating no parameter)
  LPCSTR lpDirectory;  // might be NULL (indicating no specific directory)
  int nShow;           // one of SW_ values for ShowWindow() API
  DWORD dwHotKey;
  HANDLE hIcon;
  LPCSTR lpTitle;      // For CreateProcess-StartupInfo.lpTitle
  LPCWSTR lpVerbW;        // Unicode verb (for those who can use it)
  LPCWSTR lpParametersW;  // Unicode parameters (for those who can use it)
  LPCWSTR lpDirectoryW;   // Unicode directory (for those who can use it)
  LPCWSTR lpTitleW;       // Unicode title (for those who can use it)
#if (_WIN32_IE >= 0x0400)
  POINT   ptInvoke;       // Point where it's invoked
#endif
};

#pragma pack(pop)

struct IContextMenu{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  dword QueryContextMenu;
  dword InvokeCommand;
  dword GetCommandString;
};

// IContextMenu2 (IContextMenu with one new member)
// IContextMenu2::HandleMenuMsg
//  This function is called, if the client of IContextMenu is aware of
// IContextMenu2 interface and receives one of following messages while
// it is calling TrackPopupMenu (in the window proc of hwnd):
//      WM_INITPOPUP, WM_DRAWITEM and WM_MEASUREITEM
//  The callee may handle these messages to draw owner draw menuitems.

struct IContextMenu2{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IContextMenu methods ***
  dword QueryContextMenu;
  dword InvokeCommand;
  dword GetCommandString;
// *** IContextMenu2 methods ***
  dword HandleMenuMsg;
};

// IContextMenu3 (IContextMenu with one new member)
// IContextMenu3::HandleMenuMsg2
//  This function is called, if the client of IContextMenu is aware of
// IContextMenu3 interface and receives a menu message while
// it is calling TrackPopupMenu (in the window proc of hwnd):

struct IContextMenu3{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IContextMenu methods ***
  dword QueryContextMenu;
  dword InvokeCommand;
  dword GetCommandString;
// *** IContextMenu2 methods ***
  dword HandleMenuMsg;
// *** IContextMenu3 methods ***
  dword HandleMenuMsg2;
};

#define CSIDL_FLAG_PFTI_TRACKTARGET CSIDL_FLAG_DONT_VERIFY

// DESCRIPTION: PERSIST_FOLDER_TARGET_INFO
//    This stucture is used for Folder Shortcuts which allow the shell to
// have a file system folder act like another area in the name space.
// One of pidlTargetFolder, szTargetParsingName, or csidl needs to
// specify the destination name space.
// pidlTargetFolder: This is a full pidl to the target folder.  Can be NULL in the IPersistFolder3::InitializeEx()
//                   call but not in the GetFolderTargetInfo() return structure.
// szTargetParsingName: Empty string if not specified. Ortherwise, it is the parsible name
//                       to the target.  This name can be parsed by IShellFolder::
//                       ParsedName() from the desktop.
// szNetworkProvider: Can be an empty string.  If not empty, it specifies the type of network
//                    provider that will be used when binding to the target.  This is used
//                    for performance optimizations for the WNet APIs.
// dwAttributes: -1 if not known.  These are the SFGAO_ flags for IShellFolder::GetAttributesOf()
// csidl: This is -1 if it's not used.  This can be used instead of pidlTargetFolder or
//        szTargetParsingName to indicate the TargetFolder.  See the list of CSIDL_ folders
//        below.  CSIDL_FLAG_PFTI_TRACKTARGET means that the IShellFolder's target folder
//        should change if the user changes the target of the underlying CSIDL value.
//        You can also pass CSIDL_FLAG_CREATE to indicate that the target folder
//        should be created if it does not exist.  No other CSIDL_FLAG_* values are supported.

#pragma pack(push,8)

struct PERSIST_FOLDER_TARGET_INFO
{
  dword  pidlTargetFolder;               // pidl for the folder we want to intiailize
  WCHAR         szTargetParsingName[MAX_PATH];  // optional parsing name for the target
  WCHAR         szNetworkProvider[MAX_PATH];    // optional network provider
  DWORD         dwAttributes;                   // optional FILE_ATTRIBUTES_ flags (-1 if not used)
  int           csidl;                          // optional folder index (SHGetFolderPath()) -1 if not used
};

#pragma pack(pop)

// DESCRIPTION: IPersistFolder3
//    This interface is implemented by an IShellFolder object that wants non-default
// handling of Folder Shortcuts.  In general, shell name space extensions should use
// pidlRoot (the alias pidl) as their location in the name space and pass it to public
// APIs, such as ShellExecute().  The one exception is that pidlTarget should be used
// when sending ChangeNotifies or registering to listen for change notifies
// (see SFVM_GETNOTIFY).
// InitializeEx: This method initializes an IShellFolder and specifies where
//               it is rooted in the name space.
//      pbc: May be NULL.
//      pidlRoot: This is the same parameter as IPersistFolder::Initialize(). Caller allocates
//                and frees this parameter.
//      ppfti: May be NULL, in which case this is the same as a call to IPersistFolder::Initialize().
//             Otherwise this is a Folder Shortcut and this structure specifies the target
//             folder and it's attributes.
// GetFolderTargetInfo: This is used by the caller to find information about
//             the folder shortcut.  This structure may not be initialized by the caller,
//             so the callee needs to initialize every member.  The callee allocates
//             pidlTargetFolder and the caller will free it.  Filling in pidlTargetFolder is
//             ALWAYS required.
struct IPersistFolder3
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IPersist methods ***
  dword GetClassID;
// *** IPersistFolder methods ***
  dword Initialize;
// *** IPersistFolder2 methods ***
  dword GetCurFolder;
// *** IPersistFolder3 methods ***
  dword InitializeEx;
  dword GetFolderTargetInfo;
};

//===========================================================================
// IExtractIcon interface
//  This interface is used in two different places in the shell.
// Case-1: Icons of sub-folders for the scope-pane of the explorer.
//  It is used by the explorer to get the "icon location" of
// sub-folders from each shell folders. When the user expands a folder
// in the scope pane of the explorer, the explorer does following:
//  (1) binds to the folder (gets IShellFolder),
//  (2) enumerates its sub-folders by calling its EnumObjects member,
//  (3) calls its GetUIObjectOf member to get IExtractIcon interface
//     for each sub-folders.
//  In this case, the explorer uses only IExtractIcon::GetIconLocation
// member to get the location of the appropriate icon. An icon location
// always consists of a file name (typically DLL or EXE) and either an icon
// resource or an icon index.
// Case-2: Extracting an icon image from a file
//  It is used by the shell when it extracts an icon image
// from a file. When the shell is extracting an icon from a file,
// it does following:
//  (1) creates the icon extraction handler object (by getting its CLSID
//     under the {ProgID}\shell\ExtractIconHanler key and calling
//     CoCreateInstance requesting for IExtractIcon interface).
//  (2) Calls IExtractIcon::GetIconLocation.
//  (3) Then, calls IExtractIcon::ExtractIcon with the location/index pair.
//  (4) If (3) returns NOERROR, it uses the returned icon.
//  (5) Otherwise, it recursively calls this logic with new location
//     assuming that the location string contains a fully qualified path name.
//  From extension programmer's point of view, there are only two cases
// where they provide implementations of IExtractIcon:
//  Case-1) providing explorer extensions (i.e., IShellFolder).
//  Case-2) providing per-instance icons for some types of files.
// Because Case-1 is described above, we'll explain only Case-2 here.
// When the shell is about display an icon for a file, it does following:
//  (1) Finds its ProgID and ClassID.
//  (2) If the file has a ClassID, it gets the icon location string from the
//    "DefaultIcon" key under it. The string indicates either per-class
//    icon (e.g., "FOOBAR.DLL,2") or per-instance icon (e.g., "%1,1").
//  (3) If a per-instance icon is specified, the shell creates an icon
//    extraction handler object for it, and extracts the icon from it
//    (which is described above).
//  It is important to note that the shell calls IExtractIcon::GetIconLocation
// first, then calls IExtractIcon::Extract. Most application programs
// that support per-instance icons will probably store an icon location
// (DLL/EXE name and index/id) rather than an icon image in each file.
// In those cases, a programmer needs to implement only the GetIconLocation
// member and it Extract member simply returns S_FALSE. They need to
// implement Extract member only if they decided to store the icon images
// within files themselved or some other database (which is very rare).
// [Member functions]
// IExtractIcon::GetIconLocation
//  This function returns an icon location.
//  Parameters:
//   uFlags     [in]  -- Specifies if it is opened or not (GIL_OPENICON or 0)
//   szIconFile [out] -- Specifies the string buffer buffer for a location name.
//   cchMax     [in]  -- Specifies the size of szIconFile (almost always MAX_PATH)
//   piIndex    [out] -- Sepcifies the address of UINT for the index.
//   pwFlags    [out] -- Returns GIL_* flags
//  Returns:
//   NOERROR, if it returns a valid location; S_FALSE, if the shell use a
//   default icon.
//  Notes: The location may or may not be a path to a file. The caller can
//   not assume anything unless the subsequent Extract member call returns
//   S_FALSE.
//   if the returned location is not a path to a file, GIL_NOTFILENAME should
//   be set in the returned flags.
// IExtractIcon::Extract
//  This function extracts an icon image from a specified file.
//  Parameters:
//   pszFile [in] -- Specifies the icon location (typically a path to a file).
//   nIconIndex [in] -- Specifies the icon index.
//   phiconLarge [out] -- Specifies the HICON variable for large icon.
//   phiconSmall [out] -- Specifies the HICON variable for small icon.
//   nIconSize [in] -- Specifies the size icon required (size of large icon)
//                     LOWORD is the requested large icon size
//                     HIWORD is the requested small icon size
//  Returns:
//   NOERROR, if it extracted the from the file.
//   S_FALSE, if the caller should extract from the file specified in the
//           location.
//===========================================================================

// GetIconLocation() input flags
#define GIL_OPENICON     0x0001      // allows containers to specify an "open" look
#define GIL_FORSHELL     0x0002      // icon is to be displayed in a ShellFolder
#define GIL_ASYNC        0x0020      // this is an async extract, return E_PENDING
#define GIL_DEFAULTICON  0x0040      // get the default icon location if the final one takes too long to get
#define GIL_FORSHORTCUT  0x0080      // the icon is for a shortcut to the object

// GetIconLocation() return flags
#define GIL_SIMULATEDOC  0x0001      // simulate this document icon for this
#define GIL_PERINSTANCE  0x0002      // icons from this class are per instance (each file has its own)
#define GIL_PERCLASS     0x0004      // icons from this class per class (shared for all files of this type)
#define GIL_NOTFILENAME  0x0008      // location is not a filename, must call ::ExtractIcon
#define GIL_DONTCACHE    0x0010      // this icon should not be cached

struct IExtractIcon
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IExtractIcon methods ***
  dword GetIconLocation;
  dword Extract;
};

#define IExtractIconW        IExtractIcon
#define IExtractIconA        IExtractIcon

//===========================================================================
// IShellIcon Interface
// used to get a icon index for a IShellFolder object.
// this interface can be implemented by a IShellFolder, as a quick way to
// return the icon for a object in the folder.
// a instance of this interface is only created once for the folder, unlike
// IExtractIcon witch is created once for each object.
// if a ShellFolder does not implement this interface, the standard
// GetUIObject(....IExtractIcon) method will be used to get a icon
// for all objects.
// the following standard imagelist indexs can be returned:
//      0   document (blank page) (not associated)
//      1   document (with stuff on the page)
//      2   application (exe, com, bat)
//      3   folder (plain)
//      4   folder (open)
// IShellIcon:GetIconOf(pidl, flags, lpIconIndex)
//      pidl            object to get icon for.
//      flags           GIL_* input flags (GIL_OPEN, ...)
//      lpIconIndex     place to return icon index.
//  returns:
//      NOERROR, if lpIconIndex contains the correct system imagelist index.
//      S_FALSE, if unable to get icon for this object, go through
//               GetUIObject, IExtractIcon, methods.
//===========================================================================

struct IShellIcon
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellIcon methods ***
  dword GetIconOf;
};

//===========================================================================
// IShellIconOverlayIdentifier
// Used to identify a file as a member of the group of files that have this specific
// icon overlay
// Users can create new IconOverlayIdentifiers and place them in the following registry
// location together with the Icon overlay image and their priority.
// HKEY_LOCAL_MACHINE "Software\\Microsoft\\Windows\\CurrentVersion\\ShellIconOverlayIdentifiers"
// The shell will enumerate through all IconOverlayIdentifiers at start, and prioritize
// them according to internal rules, in case the internal rules don't apply, we use their
// input priority
// IShellIconOverlayIdentifier:IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
//      pwszPath        full path of the file
//      dwAttrib        attribute of this file
//  returns:
//      S_OK,    if the file is a member
//      S_FALSE, if the file is not a member
//      E_FAIL,  if the operation failed due to bad WIN32_FIND_DATA
// IShellIconOverlayIdentifier::GetOverlayInfo(LPWSTR pwszIconFile, int * pIndex, DWORD * dwFlags) PURE;
//      pszIconFile    the path of the icon file
//      pIndex         Depend on the flags, this could contain the IconIndex
//      dwFlags        defined below
// IShellIconOverlayIdentifier::GetPriority(int * pIPriority) PURE;
//      pIPriority     the priority of this Overlay Identifier
//===========================================================================

struct IShellIconOverlayIdentifier
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellIconOverlayIdentifier methods ***
  dword IsMemberOf;
  dword GetOverlayInfo;
  dword GetPriority;
};

#define ISIOI_ICONFILE            0x00000001          // path is returned through pwszIconFile
#define ISIOI_ICONINDEX           0x00000002          // icon index in pwszIconFile is returned through pIndex

//===========================================================================
// IShellIconOverlay
// Used to return the icon overlay index or its icon index for an IShellFolder object,
// this is always implemented with IShellFolder
// IShellIconOverlay:GetOverlayIndex(LPCITEMIDLIST pidl, DWORD * pdwIndex)
//      pidl            object to identify icon overlay for.
//      pdwIndex        the Overlay Index in the system image list
// IShellIconOverlay:GetOverlayIconIndex(LPCITEMIDLIST pidl, DWORD * pdwIndex)
//      pdwIconIndex    the Overlay Icon index in the system image list
// This method is only used for those who are interested in seeing the real bits
// of the Overlay Icon
//  returns:
//      S_OK,  if the index of an Overlay is found
//      S_FALSE, if no Overlay exists for this file
//      E_FAIL, if pidl is bad
//===========================================================================

struct IShellIconOverlay
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellIconOverlay methods ***
  dword GetOverlayIndex;
  dword GetOverlayIconIndex;
};

#define OI_ASYNC 0xFFFFEEEE

//-------------------------------------------------------------------------
// SHGetIconOverlayIndex
// This function takes the path and icon/res id to the icon and convert it into
// an overlay index in the system image list.
// Note: there are totally only 15 slots for system image overlays, some of which
// was reserved by the system, or taken by the overlayidentifiers, so it's possible
// that this function would fail and return -1;
// To get the default overlays in the system, such as the share hand, link shortcut
// and slow files, pass NULL as the file name, then the IDO_SHGIOI_* flags as the icon index
//-------------------------------------------------------------------------

#define IDO_SHGIOI_SHARE  0x0FFFFFFF
#define IDO_SHGIOI_LINK   0x0FFFFFFE
#define IDO_SHGIOI_SLOWFILE 0x0FFFFFFFD
extern WINAPI "shell32.dll"{
	int SHGetIconOverlayIndexA(LPCSTR pszIconPath,int iIconIndex);
	int SHGetIconOverlayIndexW(LPCWSTR pszIconPath,int iIconIndex);
}
#ifdef UNICODE
#define SHGetIconOverlayIndex  SHGetIconOverlayIndexW
#else
#define SHGetIconOverlayIndex  SHGetIconOverlayIndexA
#endif // !UNICODE

enum SHELL_LINK_DATA_FLAGS{
  SLDF_HAS_ID_LIST         = 0x00000001,   // Shell link saved with ID list
  SLDF_HAS_LINK_INFO       = 0x00000002,   // Shell link saved with LinkInfo
  SLDF_HAS_NAME            = 0x00000004,
  SLDF_HAS_RELPATH         = 0x00000008,
  SLDF_HAS_WORKINGDIR      = 0x00000010,
  SLDF_HAS_ARGS            = 0x00000020,
  SLDF_HAS_ICONLOCATION    = 0x00000040,
  SLDF_UNICODE             = 0x00000080,   // the strings are unicode
  SLDF_FORCE_NO_LINKINFO   = 0x00000100,   // don't create a LINKINFO (make a dumb link)
  SLDF_HAS_EXP_SZ          = 0x00000200,   // the link contains expandable env strings
  SLDF_RUN_IN_SEPARATE     = 0x00000400,   // Run the 16-bit target exe in a separate VDM/WOW
  SLDF_HAS_LOGO3ID         = 0x00000800,   // this link is a special Logo3/MSICD link
  SLDF_HAS_DARWINID        = 0x00001000,   // this link is a special Darwin link
  SLDF_RUNAS_USER          = 0x00002000,   // Run this link as a different user
  SLDF_HAS_EXP_ICON_SZ     = 0x00004000,   // contains expandable env string for icon path
  SLDF_NO_PIDL_ALIAS       = 0x00008000,   // don't ever resolve to a logical location
  SLDF_FORCE_UNCNAME       = 0x00010000,   // make GetPath() prefer the UNC name to the local name
  SLDF_RUN_WITH_SHIMLAYER  = 0x00020000,   // Launch the target of this link w/ shim layer active
  SLDF_RESERVED            = 0x80000000,   // Reserved-- so we can use the low word as an index value in the future
};

struct DATABLOCKHEADER
{
  DWORD   cbSize;             // Size of this extra data block
  DWORD   dwSignature;        // signature of this extra data block
};

struct NT_CONSOLE_PROPS{
  DATABLOCKHEADER dbh;
  WORD     wFillAttribute;         // fill attribute for console
  WORD     wPopupFillAttribute;    // fill attribute for console popups
  COORD    dwScreenBufferSize;     // screen buffer size for console
  COORD    dwWindowSize;           // window size for console
  COORD    dwWindowOrigin;         // window origin for console
  DWORD    nFont;
  DWORD    nInputBufferSize;
  COORD    dwFontSize;
  UINT     uFontFamily;
  UINT     uFontWeight;
  WCHAR    FaceName[LF_FACESIZE];
  UINT     uCursorSize;
  BOOL     bFullScreen;
  BOOL     bQuickEdit;
  BOOL     bInsertMode;
  BOOL     bAutoPosition;
  UINT     uHistoryBufferSize;
  UINT     uNumberOfHistoryBuffers;
  BOOL     bHistoryNoDup;
  COLORREF ColorTable[ 16 ];
};
#define NT_CONSOLE_PROPS_SIG 0xA0000002

// This is a FE Console property
struct NT_FE_CONSOLE_PROPS{
  DATABLOCKHEADER dbh;
  UINT     uCodePage;
};
#define NT_FE_CONSOLE_PROPS_SIG 0xA0000004

struct EXP_DARWIN_LINK{
  DATABLOCKHEADER dbh;
  CHAR        szDarwinID[MAX_PATH];  // ANSI darwin ID associated with link
  WCHAR       szwDarwinID[MAX_PATH]; // UNICODE darwin ID associated with link
};
#define EXP_DARWIN_ID_SIG       0xA0000006
// BUGBUG (reinerf) - this has the same value as EXP_SZ_ICON_SIG?!?!?!
#define EXP_LOGO3_ID_SIG        0xA0000007
#define EXP_SPECIAL_FOLDER_SIG         0xA0000005   // LPEXP_SPECIAL_FOLDER

struct EXP_SPECIAL_FOLDER
{
  DWORD       cbSize;             // Size of this extra data block
  DWORD       dwSignature;        // signature of this extra data block
  DWORD       idSpecialFolder;    // special folder id this link points into
  DWORD       cbOffset;           // ofset into pidl from SLDF_HAS_ID_LIST for child
};

struct EXP_SZ_LINK
{
  DWORD       cbSize;             // Size of this extra data block
  DWORD       dwSignature;        // signature of this extra data block
  CHAR        szTarget[ MAX_PATH ];   // ANSI target name w/EXP_SZ in it
  WCHAR       swzTarget[ MAX_PATH ];  // UNICODE target name w/EXP_SZ in it
};
#define EXP_SZ_LINK_SIG                0xA0000001   // LPEXP_SZ_LINK (target)
#define EXP_SZ_ICON_SIG                0xA0000007   // LPEXP_SZ_LINK (icon)

struct IShellLinkDataList
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellLinkDataList methods ***
  dword AddDataBlock;
  dword CopyDataBlock;
  dword RemoveDataBlock;
  dword GetFlags;
  dword SetFlags;
};

struct IResolveShellLink
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IResolveShellLink methods ***
  dword ResolveShellLink;
};

#ifdef _INC_SHELLAPI    /* for LPSHELLEXECUTEINFO */
//===========================================================================
// IShellExecuteHook Interface
//===========================================================================

struct IShellExecuteHook
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellExecuteHookA methods ***
  dword Execute;
};

#define IShellExecuteHookW       IShellExecuteHook
#define IShellExecuteHookA       IShellExecuteHook
#endif

//===========================================================================
// IURLSearchHook Interface
//===========================================================================

struct IURLSearchHook
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IURLSearchHook methods ***
  dword Translate;
};

struct ISearchContext
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** ISearchContext methods ***
  dword GetSearchUrl;
  dword GetSearchText;
  dword GetSearchStyle;
};

struct IURLSearchHook2
{
// *** IURLSearchHook2 methods ***
  dword TranslateWithSearchContext;
};

//===========================================================================
// INewShortcutHook Interface
//===========================================================================

struct INewShortcutHook
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** INewShortcutHook methods ***
  dword SetReferent;
  dword GetReferent;
  dword SetFolder;
  dword GetFolder;
  dword GetName;
  dword GetExtension;
};

#define INewShortcutHookW        INewShortcutHook
#define INewShortcutHookA        INewShortcutHook

//===========================================================================
// ICopyHook Interface
//  The copy hook is called whenever file system directories are
//  copy/moved/deleted/renamed via the shell.  It is also called by the shell
//  on changes of status of printers.
//  Clients register their id under STRREG_SHEX_COPYHOOK for file system hooks
//  and STRREG_SHEx_PRNCOPYHOOK for printer hooks.
//  the CopyCallback is called prior to the action, so the hook has the chance
//  to allow, deny or cancel the operation by returning the falues:
//     IDYES  -  means allow the operation
//     IDNO   -  means disallow the operation on this file, but continue with
//              any other operations (eg. batch copy)
//     IDCANCEL - means disallow the current operation and cancel any pending
//              operations
//   arguments to the CopyCallback
//      hwnd - window to use for any UI
//      wFunc - what operation is being done
//      wFlags - and flags (FOF_*) set in the initial call to the file operation
//      pszSrcFile - name of the source file
//      dwSrcAttribs - file attributes of the source file
//      pszDestFile - name of the destiation file (for move and renames)
//      dwDestAttribs - file attributes of the destination file
//===========================================================================

#ifndef FO_MOVE //these need to be kept in sync with the ones in shellapi.h

// file operations
#define FO_MOVE           0x0001
#define FO_COPY           0x0002
#define FO_DELETE         0x0003
#define FO_RENAME         0x0004

#define FOF_MULTIDESTFILES         0x0001
#define FOF_CONFIRMMOUSE           0x0002
#define FOF_SILENT                 0x0004  // don't create progress/report
#define FOF_RENAMEONCOLLISION      0x0008
#define FOF_NOCONFIRMATION         0x0010  // Don't prompt the user.
#define FOF_WANTMAPPINGHANDLE      0x0020  // Fill in SHFILEOPSTRUCT.hNameMappings
                                      // Must be freed using SHFreeNameMappings
#define FOF_ALLOWUNDO              0x0040
#define FOF_FILESONLY              0x0080  // on *.*, do only files
#define FOF_SIMPLEPROGRESS         0x0100  // means don't show names of files
#define FOF_NOCONFIRMMKDIR         0x0200  // don't confirm making any needed dirs
#define FOF_NOERRORUI              0x0400  // don't put up error UI
#define FOF_NOCOPYSECURITYATTRIBS  0x0800  // dont copy NT file Security Attributes
#define FOF_NORECURSION            0x1000  // don't recurse into directories.
#define FOF_NO_CONNECTED_ELEMENTS  0x2000  // don't operate on connected file elements.
#define FOF_WANTNUKEWARNING        0x4000  // during delete operation, warn if nuking instead of recycling (partially overrides FOF_NOCONFIRMATION)
#define FOF_NORECURSEREPARSE       0x8000  // treat reparse points as objects, not containers

#define FILEOP_FLAGS WORD

// printer operations
#define PO_DELETE       0x0013  // printer is being deleted
#define PO_RENAME       0x0014  // printer is being renamed
#define PO_PORTCHANGE   0x0020  // port this printer connected to is being changed
                                // if this id is set, the strings received by
                                // the copyhook are a doubly-null terminated
                                // list of strings.  The first is the printer
                                // name and the second is the printer port.
#define PO_REN_PORT     0x0034  // PO_RENAME and PO_PORTCHANGE at same time.

// no POF_ flags currently defined
#define PRINTEROP_FLAGS UINT

#endif // FO_MOVE

struct ICopyHook
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** ICopyHook methods ***
  dword CopyCallback;
};

#define ICopyHookW       ICopyHook
#define ICopyHookA       ICopyHook

//===========================================================================
// IFileViewerSite Interface
//===========================================================================

struct IFileViewerSite
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IFileViewerSite methods ***
  dword SetPinnedWindow;
  dword GetPinnedWindow;
};

//===========================================================================
// IFileViewer Interface
// Implemented in a FileViewer component object.  Used to tell a
// FileViewer to PrintTo or to view, the latter happening though
// ShowInitialize and Show.  The filename is always given to the
// viewer through IPersistFile.
//===========================================================================

#pragma pack(push,8)

struct FVSHOWINFO
{
  // Stuff passed into viewer (in)
  DWORD cbSize;           // Size of structure for future expansion...
  HWND hwndOwner;         // who is the owner window.
  int iShow;              // The show command
  // Passed in and updated  (in/Out)
  DWORD dwFlags;          // flags
  RECT rect;              // Where to create the window may have defaults
  dword punkRel;      // Relese this interface when window is visible
  // Stuff that might be returned from viewer (out)
  OLECHAR strNewFile[MAX_PATH];   // New File to view.
};

#pragma pack(pop)

    // Define File View Show Info Flags.
#define FVSIF_RECT      0x00000001      // The rect variable has valid data.
#define FVSIF_PINNED    0x00000002      // We should Initialize pinned
#define FVSIF_NEWFAILED 0x08000000      // The new file passed back failed
                                        // to be viewed.
#define FVSIF_NEWFILE   0x80000000      // A new file to view has been returned
#define FVSIF_CANVIEWIT 0x40000000      // The viewer can view it.

struct IFileViewer
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IFileViewer methods ***
  dword ShowInitialize;
  dword Show;
  dword PrintTo;
};

#define IFileViewerW IFileViewer
#define IFileViewerA IFileViewer

//==========================================================================
// IShellBrowser/IShellView/IShellFolder interface
//  These three interfaces are used when the shell communicates with
// name space extensions. The shell (explorer) provides IShellBrowser
// interface, and extensions implements IShellFolder and IShellView
// interfaces.
//==========================================================================

//--------------------------------------------------------------------------
// Command/menuitem IDs
//  The explorer dispatches WM_COMMAND messages based on the range of
// command/menuitem IDs. All the IDs of menuitems that the view (right
// pane) inserts must be in FCIDM_SHVIEWFIRST/LAST (otherwise, the explorer
// won't dispatch them). The view should not deal with any menuitems
// in FCIDM_BROWSERFIRST/LAST (otherwise, it won't work with the future
// version of the shell).
//  FCIDM_SHVIEWFIRST/LAST      for the right pane (IShellView)
//  FCIDM_BROWSERFIRST/LAST     for the explorer frame (IShellBrowser)
//  FCIDM_GLOBAL/LAST           for the explorer's submenu IDs
//--------------------------------------------------------------------------
#define FCIDM_SHVIEWFIRST           0x0000
#define FCIDM_SHVIEWLAST            0x7fff
#define FCIDM_BROWSERFIRST          0xa000
#define FCIDM_BROWSERLAST           0xbf00
#define FCIDM_GLOBALFIRST           0x8000
#define FCIDM_GLOBALLAST            0x9fff

// Global submenu IDs and separator IDs
#define FCIDM_MENU_FILE             FCIDM_GLOBALFIRST+0x0000
#define FCIDM_MENU_EDIT             FCIDM_GLOBALFIRST+0x0040
#define FCIDM_MENU_VIEW             FCIDM_GLOBALFIRST+0x0080
#define FCIDM_MENU_VIEW_SEP_OPTIONS FCIDM_GLOBALFIRST+0x0081
#define FCIDM_MENU_TOOLS            FCIDM_GLOBALFIRST+0x00c0 // for Win9x compat
#define FCIDM_MENU_TOOLS_SEP_GOTO   FCIDM_GLOBALFIRST+0x00c1 // for Win9x compat
#define FCIDM_MENU_HELP             FCIDM_GLOBALFIRST+0x0100
#define FCIDM_MENU_FIND             FCIDM_GLOBALFIRST+0x0140
#define FCIDM_MENU_EXPLORE          FCIDM_GLOBALFIRST+0x0150
#define FCIDM_MENU_FAVORITES        FCIDM_GLOBALFIRST+0x0170

//--------------------------------------------------------------------------
// control IDs known to the view
//--------------------------------------------------------------------------
#define FCIDM_TOOLBAR      FCIDM_BROWSERFIRST + 0
#define FCIDM_STATUS       FCIDM_BROWSERFIRST + 1

//--------------------------------------------------------------------------
// The resource id of the offline cursor
// This cursor is avaialble in shdocvw.dll
#define IDC_OFFLINE_HAND        103

//-------------------------------------------------------------------------
// ICommDlgBrowser interface
//  ICommDlgBrowser interface is the interface that is provided by the new
// common dialog window to hook and modify the behavior of IShellView.  When
// a default view is created, it queries its parent IShellBrowser for the
// ICommDlgBrowser interface.  If supported, it calls out to that interface
// in several cases that need to behave differently in a dialog.
// Member functions:
//  ICommDlgBrowser::OnDefaultCommand()
//    Called when the user double-clicks in the view or presses Enter.  The
//   browser should return S_OK if it processed the action itself, S_FALSE
//   to let the view perform the default action.
//  ICommDlgBrowser::OnStateChange(ULONG uChange)
//    Called when some states in the view change.  'uChange' is one of the
//   CDBOSC_* values.  This call is made after the state (selection, focus,
//   etc) has changed.  There is no return value.
//  ICommDlgBrowser::IncludeObject(LPCITEMIDLIST pidl)
//    Called when the view is enumerating objects.  'pidl' is a relative
//   IDLIST.  The browser should return S_OK to include the object in the
//   view, S_FALSE to hide it
//-------------------------------------------------------------------------
#define CDBOSC_SETFOCUS     0x00000000
#define CDBOSC_KILLFOCUS    0x00000001
#define CDBOSC_SELCHANGE    0x00000002
#define CDBOSC_RENAME       0x00000003
#define CDBOSC_STATECHANGE  0x00000004

struct ICommDlgBrowser
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** ICommDlgBrowser methods ***
  dword OnDefaultCommand;
  dword OnStateChange;
  dword IncludeObject;
};

//-------------------------------------------------------------------------
// ICommDlgBrowser2 interface
// Member functions:
//  ICommDlgBrowser2::Notify(IShellView *pshv, DWORD dwNotfyType)
//   Called when the view is wants to notify common dialog when an event
//  occurrs.
//  CDB2N_CONTEXTMENU_START indicates the context menu has started.
//  CDB2N_CONTEXTMENU_DONE  indicates the context menu has completed.
//  ICommDlgBrowser2::GetDefaultMenuText(IShellView *pshv,
//                                      WCHAR *pszText, INT cchMax)
//   Called when the view wants to get the default context menu text.
//  pszText points to buffer and cchMax specifies the size of the
//  buffer in characters.  The browser on return has filled the buffer
//  with the default context menu text.  The Shell will call this method
//  with at least a buffer size of MAX_PATH.  The browser should return
//  S_OK if it returned a new default menu text, S_FALSE to let the view
//  to use the normal default menu text.
//  ICommDlgBrowser2::GetViewFlags(DWORD *pdwFlags)
//     Called when the view wants to determine  if special customization needs to
//    be done for the common dialog browser. For example View calls this function to
//    determin if all files(hidden and system)needs to be shown. If the GetViewFlags returns a DWORD with
//    CDB2GVF_SHOWALLFILES  flag set then it will show all the files.
//-------------------------------------------------------------------------
#define CDB2N_CONTEXTMENU_DONE  0x00000001
#define CDB2N_CONTEXTMENU_START 0x00000002

//GetViewFlags
#define CDB2GVF_SHOWALLFILES        0x00000001

struct ICommDlgBrowser2
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** ICommDlgBrowser methods ***
  dword OnDefaultCommand;
  dword OnStateChange;
  dword IncludeObject;
// *** ICommDlgBrowser2 methods ***
  dword Notify;
  dword GetDefaultMenuText;
  dword GetViewFlags;
};

// function assumes the size of the buffer (MAX_PATH). The pidl
// should point to a file system object.
extern WINAPI "shell32.dll"{
	BOOL SHGetPathFromIDListA(dword pidl,LPSTR pszPath);
	BOOL SHGetPathFromIDListW(dword pidl,LPWSTR pszPath);
#ifdef UNICODE
#define SHGetPathFromIDList  SHGetPathFromIDListW
#else
#define SHGetPathFromIDList  SHGetPathFromIDListA
#endif // !UNICODE

	int SHCreateDirectoryExA(HWND hwnd,LPCSTR pszPath,dword psa);
	int SHCreateDirectoryExW(HWND hwnd,LPCWSTR pszPath,dword psa);
#ifdef UNICODE
#define SHCreateDirectoryEx  SHCreateDirectoryExW
#else
#define SHCreateDirectoryEx  SHCreateDirectoryExA
#endif // !UNICODE

	void SHOpenFolderAndSelectItems(dword pidlFolder,UINT cidl,dword apidl,DWORD dwFlags);
}
//-------------------------------------------------------------------------
// SHGetSpecialFolderLocation
//  Caller should use SHGetMalloc to obtain an allocator that can free the pidl
//-------------------------------------------------------------------------
// registry entries for special paths are kept in :
#define REGSTR_PATH_SPECIAL_FOLDERS    "\\Shell Folders"

#define CSIDL_DESKTOP                   0x0000        // <desktop>
#define CSIDL_INTERNET                  0x0001        // Internet Explorer (icon on desktop)
#define CSIDL_PROGRAMS                  0x0002        // Start Menu\Programs
#define CSIDL_CONTROLS                  0x0003        // My Computer\Control Panel
#define CSIDL_PRINTERS                  0x0004        // My Computer\Printers
#define CSIDL_PERSONAL                  0x0005        // My Documents
#define CSIDL_FAVORITES                 0x0006        // <user name>\Favorites
#define CSIDL_STARTUP                   0x0007        // Start Menu\Programs\Startup
#define CSIDL_RECENT                    0x0008        // <user name>\Recent
#define CSIDL_SENDTO                    0x0009        // <user name>\SendTo
#define CSIDL_BITBUCKET                 0x000a        // <desktop>\Recycle Bin
#define CSIDL_STARTMENU                 0x000b        // <user name>\Start Menu
#define CSIDL_MYDOCUMENTS               0x000c        // logical "My Documents" desktop icon
#define CSIDL_MYMUSIC                   0x000d        // "My Music" folder
#define CSIDL_MYVIDEO                   0x000e        // "My Videos" folder
#define CSIDL_DESKTOPDIRECTORY          0x0010        // <user name>\Desktop
#define CSIDL_DRIVES                    0x0011        // My Computer
#define CSIDL_NETWORK                   0x0012        // Network Neighborhood (My Network Places)
#define CSIDL_NETHOOD                   0x0013        // <user name>\nethood
#define CSIDL_FONTS                     0x0014        // windows\fonts
#define CSIDL_TEMPLATES                 0x0015
#define CSIDL_COMMON_STARTMENU          0x0016        // All Users\Start Menu
#define CSIDL_COMMON_PROGRAMS           0X0017        // All Users\Start Menu\Programs
#define CSIDL_COMMON_STARTUP            0x0018        // All Users\Startup
#define CSIDL_COMMON_DESKTOPDIRECTORY   0x0019        // All Users\Desktop
#define CSIDL_APPDATA                   0x001a        // <user name>\Application Data
#define CSIDL_PRINTHOOD                 0x001b        // <user name>\PrintHood
#ifndef CSIDL_LOCAL_APPDATA
#define CSIDL_LOCAL_APPDATA             0x001c        // <user name>\Local Settings\Applicaiton Data (non roaming)
#endif // CSIDL_LOCAL_APPDATA
#define CSIDL_ALTSTARTUP                0x001d        // non localized startup
#define CSIDL_COMMON_ALTSTARTUP         0x001e        // non localized common startup
#define CSIDL_COMMON_FAVORITES          0x001f
#ifndef _SHFOLDER_H_
#define CSIDL_INTERNET_CACHE            0x0020
#define CSIDL_COOKIES                   0x0021
#define CSIDL_HISTORY                   0x0022
#define CSIDL_COMMON_APPDATA            0x0023        // All Users\Application Data
#define CSIDL_WINDOWS                   0x0024        // GetWindowsDirectory()
#define CSIDL_SYSTEM                    0x0025        // GetSystemDirectory()
#define CSIDL_PROGRAM_FILES             0x0026        // C:\Program Files
#define CSIDL_MYPICTURES                0x0027        // C:\Program Files\My Pictures
#endif // _SHFOLDER_H_
#define CSIDL_PROFILE                   0x0028        // USERPROFILE
#define CSIDL_SYSTEMX86                 0x0029        // x86 system directory on RISC
#define CSIDL_PROGRAM_FILESX86          0x002a        // x86 C:\Program Files on RISC
#ifndef _SHFOLDER_H_
#define CSIDL_PROGRAM_FILES_COMMON      0x002b        // C:\Program Files\Common
#endif // _SHFOLDER_H_
#define CSIDL_PROGRAM_FILES_COMMONX86   0x002c        // x86 Program Files\Common on RISC
#define CSIDL_COMMON_TEMPLATES          0x002d        // All Users\Templates
#ifndef _SHFOLDER_H_
#define CSIDL_COMMON_DOCUMENTS          0x002e        // All Users\Documents
#define CSIDL_COMMON_ADMINTOOLS         0x002f        // All Users\Start Menu\Programs\Administrative Tools
#define CSIDL_ADMINTOOLS                0x0030        // <user name>\Start Menu\Programs\Administrative Tools
#endif // _SHFOLDER_H_
#define CSIDL_CONNECTIONS               0x0031        // Network and Dial-up Connections
#define CSIDL_COMMON_MUSIC              0x0035        // All Users\My Music
#define CSIDL_COMMON_PICTURES           0x0036        // All Users\My Pictures
#define CSIDL_COMMON_VIDEO              0x0037        // All Users\My Video
#define CSIDL_RESOURCES                 0x0038        // Resource Direcotry
#ifndef _SHFOLDER_H_
#define CSIDL_RESOURCES_LOCALIZED       0x0039        // Localized Resource Direcotry
#endif // _SHFOLDER_H_
#define CSIDL_COMMON_OEM_LINKS          0x003a        // Links to All Users OEM specific apps
#define CSIDL_CDBURN_AREA               0x003b        // USERPROFILE\Local Settings\Application Data\Microsoft\CD Burning
// unused                               0x003c
#define CSIDL_COMPUTERSNEARME           0x003d        // Computers Near Me (computered from Workgroup membership)
#ifndef _SHFOLDER_H_
#define CSIDL_FLAG_CREATE               0x8000        // combine with CSIDL_ value to force folder creation in SHGetFolderPath()
#endif // _SHFOLDER_H_
#define CSIDL_FLAG_DONT_VERIFY          0x4000        // combine with CSIDL_ value to return an unverified folder path
#define CSIDL_FLAG_NO_ALIAS             0x1000        // combine with CSIDL_ value to insure non-alias versions of the pidl
#define CSIDL_FLAG_PER_USER_INIT        0x0800        // combine with CSIDL_ value to indicate per-user init (eg. upgrade)
#define CSIDL_FLAG_MASK                 0xFF00        // mask for all possible flag values

enum SHGFP_TYPE{
  SHGFP_TYPE_CURRENT  = 0,   // current value for user, verify it exists
  SHGFP_TYPE_DEFAULT  = 1,   // default value, may not exist
};
extern WINAPI "shell32.dll"{
	dword SHGetSpecialFolderLocation(HWND hwnd,int csidl,dword ppidl);
	BOOL SHGetSpecialFolderPathA(HWND hwnd,LPSTR pszPath,int csidl,BOOL fCreate);
	BOOL SHGetSpecialFolderPathW(HWND hwnd,LPWSTR pszPath,int csidl,BOOL fCreate);
#ifdef UNICODE
#define SHGetSpecialFolderPath  SHGetSpecialFolderPathW
#else
#define SHGetSpecialFolderPath  SHGetSpecialFolderPathA
#endif // !UNICODE

	dword SHGetFolderPathA(HWND hwnd,int csidl,HANDLE hToken,DWORD dwFlags,LPSTR pszPath);
	dword SHGetFolderPathW(HWND hwnd,int csidl,HANDLE hToken,DWORD dwFlags,LPWSTR pszPath);
#ifdef UNICODE
#define SHGetFolderPath  SHGetFolderPathW
#else
#define SHGetFolderPath  SHGetFolderPathA
#endif // !UNICODE
 dword SHGetFolderLocation(HWND hwnd,int csidl,HANDLE hToken,DWORD dwFlags,dword ppidl);

	dword SHGetFolderPathAndSubDirA(HWND hwnd,int csidl,HANDLE hToken,DWORD dwFlags,LPCSTR pszSubDir,LPSTR pszPath);
	dword SHGetFolderPathAndSubDirW(HWND hwnd,int csidl,HANDLE hToken,DWORD dwFlags,LPCWSTR pszSubDir,LPWSTR pszPath);
#ifdef UNICODE
#define SHGetFolderPathAndSubDir  SHGetFolderPathAndSubDirW
#else
#define SHGetFolderPathAndSubDir  SHGetFolderPathAndSubDirA
#endif // !UNICODE
}
//-------------------------------------------------------------------------
// SHBrowseForFolder API
//-------------------------------------------------------------------------
//#pragma pack(push,8)

struct BROWSEINFO{
  HWND        hwndOwner;
  dword pidlRoot;
  LPSTR        pszDisplayName;        // Return display name of item selected.
  LPCSTR       lpszTitle;                     // text to go in the banner over the tree.
  UINT         ulFlags;                       // Flags that control the return stuff
  dword  lpfn;
  LPARAM       lParam;                        // extra info that's passed back in callbacks
  int          iImage;                        // output var: where to return the Image index.
};

//#pragma pack(pop)

#define BROWSEINFOW      BROWSEINFO
#define BROWSEINFOA      BROWSEINFO

// Browsing for directory.
#define BIF_RETURNONLYFSDIRS   0x0001  // For finding a folder to start document searching
#define BIF_DONTGOBELOWDOMAIN  0x0002  // For starting the Find Computer
#define BIF_STATUSTEXT         0x0004   // Top of the dialog has 2 lines of text for BROWSEINFO.lpszTitle and one line if
                                        // this flag is set.  Passing the message BFFM_SETSTATUSTEXTA to the hwnd can set the
                                        // rest of the text.  This is not used with BIF_USENEWUI and BROWSEINFO.lpszTitle gets
                                        // all three lines of text.
#define BIF_RETURNFSANCESTORS  0x0008
#define BIF_EDITBOX            0x0010   // Add an editbox to the dialog
#define BIF_VALIDATE           0x0020   // insist on valid result (or CANCEL)

#define BIF_NEWDIALOGSTYLE     0x0040   // Use the new dialog layout with the ability to resize
                                        // Caller needs to call OleInitialize() before using this API

#define BIF_USENEWUI           BIF_NEWDIALOGSTYLE | BIF_EDITBOX

#define BIF_BROWSEINCLUDEURLS  0x0080   // Allow URLs to be displayed or entered. (Requires BIF_USENEWUI)
#define BIF_UAHINT             0x0100   // Add a UA hint to the dialog, in place of the edit box. May not be combined with BIF_EDITBOX
#define BIF_NONEWFOLDERBUTTON  0x0200   // Do not add the "New Folder" button to the dialog.  Only applicable with BIF_NEWDIALOGSTYLE.
#define BIF_NOTRANSLATETARGETS 0x0400   // don't traverse target as shortcut

#define BIF_BROWSEFORCOMPUTER  0x1000  // Browsing for Computers.
#define BIF_BROWSEFORPRINTER   0x2000  // Browsing for Printers
#define BIF_BROWSEINCLUDEFILES 0x4000  // Browsing for Everything
#define BIF_SHAREABLE          0x8000  // sharable resources displayed (remote shares, requires BIF_USENEWUI)

// message from browser
#define BFFM_INITIALIZED        1
#define BFFM_SELCHANGED         2
#define BFFM_VALIDATEFAILEDA    3   // lParam:szPath ret:1(cont),0(EndDialog)
#define BFFM_VALIDATEFAILEDW    4   // lParam:wzPath ret:1(cont),0(EndDialog)
#define BFFM_IUNKNOWN           5   // provides IUnknown to client. lParam: IUnknown*

// messages to browser
#define BFFM_SETSTATUSTEXTA     WM_USER + 100
#define BFFM_ENABLEOK           WM_USER + 101
#define BFFM_SETSELECTIONA      WM_USER + 102
#define BFFM_SETSELECTIONW      WM_USER + 103
#define BFFM_SETSTATUSTEXTW     WM_USER + 104
#define BFFM_SETOKTEXT          WM_USER + 105 // Unicode only
#define BFFM_SETEXPANDED        WM_USER + 106 // Unicode only

enum {
    ISHCUTCMDID_DOWNLOADICON  = 0,
    ISHCUTCMDID_INTSHORTCUTCREATE = 1,
};

extern WINAPI "shell32.dll"{
	dword SHBrowseForFolderA(dword lpbi);
	dword SHBrowseForFolderW(dword lpbi);

#ifdef UNICODE
#define SHBrowseForFolder   SHBrowseForFolderW
#define BFFM_SETSTATUSTEXT  BFFM_SETSTATUSTEXTW
#define BFFM_SETSELECTION   BFFM_SETSELECTIONW
#define BFFM_VALIDATEFAILED BFFM_VALIDATEFAILEDW
#else
#define SHBrowseForFolder   SHBrowseForFolderA
#define BFFM_SETSTATUSTEXT  BFFM_SETSTATUSTEXTA
#define BFFM_SETSELECTION   BFFM_SETSELECTIONA
#define BFFM_VALIDATEFAILED BFFM_VALIDATEFAILEDA
#endif

//-------------------------------------------------------------------------
// SHLoadInProc
//   When this function is called, the shell calls CoCreateInstance
//  (or equivalent) with CLSCTX_INPROC_SERVER and the specified CLSID
//  from within the shell's process and release it immediately.
//-------------------------------------------------------------------------
	dword SHLoadInProc(dword rclsid);

//-------------------------------------------------------------------------
// SHEnableServiceObject
//   Like SHLoadInProc, but gives control over the object's lifetime
//  via fEnable parameter.  TRUE tells the shell to create the object
//  and hold onto it, FALSE tells the shell to look for the previously
//  created instance of the object and release it.
//-------------------------------------------------------------------------
	dword SHEnableServiceObject(dword rclsid,BOOL fEnable);

//-------------------------------------------------------------------------
// Internet Shortcut Object
//-------------------------------------------------------------------------
// Cmds for CGID_ShortCut
#define CMDID_INTSHORTCUTCREATE ISHCUTCMDID_INTSHORTCUTCREATE

//  Helper function which returns a IShellFolder interface to the desktop
// folder. This is equivalent to call CoCreateInstance with CLSID_ShellDesktop.
//  CoCreateInstance(CLSID_Desktop, NULL,
//                   CLSCTX_INPROC, IID_IShellFolder, &pshf);
	dword SHGetDesktopFolder(dword ppshf);
}
// IShellFolder IBindCtx* parameters. the IUnknown for these are
// accessed through IBindCtx::RegisterObjectParam/GetObjectParam
// use this to provide the data needed create IDLists through
// IShellFolder::ParseDisplayName(). this data applies to the last element
// of the name that is parsed (c:\foo\bar.txt, data applies to bar.txt)
// this makes creating these IDLists much faster that suppling the name only

#define STR_FILE_SYS_BIND_DATA      L"File System Bind Data"

struct IFileSystemBindData
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IFileSystemBindData methods ***
  dword SetFindData;
  dword GetFindData;
};

struct IShellDetails
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellDetails methods ***
  dword GetDetailsOf;
  dword ColumnClick;
};

//-------------------------------------------------------------------------
// IObjMgr interface
// [Member functions]
// IObjMgr::Append(punk)
//   This function adds an object to the end of a list of objects.
// IObjMgr::Remove(punk)
//   This function removes an object from a list of objects.
// This is implemented by CLSID_ACLMulti so each AutoComplete List
// (CLSID_ACLHistory, CLSID_ACListISF, CLSID_ACLMRU) can be added.
// CLSID_ACLMulti's IEnumString will then be the union of the results
// from the COM Objects added.
//-------------------------------------------------------------------------

struct IObjMgr
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IObjMgr specific methods ***
  dword Append;
  dword Remove;
};

//-------------------------------------------------------------------------
// ICurrentWorkingDirectory interface
// [Member functions]
// ICurrentWorkingDirectory::GetDirectory(LPWSTR pwzPath, DWORD cchSize)
//   This function gets the Current Working Directory from a COM object that
//   stores such state.
// ICurrentWorkingDirectory::SetDirectory(LPCWSTR pwzPath)
//   This function sets the Current Working Directory of a COM object that
//   stores such state.
// This function can be used generically.  One COM object that implements it
// is CLSID_ACListISF so that the AutoComplete engine can complete relative
// paths.  SetDirectory() will set the "Current Working Directory" and
// AutoComplete with then complete both absolute and relative paths.
// For Example, if ::SetDirectory(L"C:\Program Files") is called, then
// the user can AutoComplete "..\winnt".  In order to set the current
// working directory for non-file system paths, "ftp://ftp.microsoft.com/" or
// "Control Panel" for example, use IPersistFolder.
//-------------------------------------------------------------------------

struct ICurrentWorkingDirectory
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** ICurrentWorkingDirectory specific methods ***
  dword GetDirectory;
  dword SetDirectory;
};

//-------------------------------------------------------------------------
// IACList interface
// [Member functions]
// IObjMgr::Expand(LPCOLESTR)
//   This function tells an autocomplete list to expand a specific string.
// If the user enters a multi-level path, AutoComplete (CLSID_AutoComplete)
// will use this interface to tell the "AutoComplete Lists" where to expand
// the results.
// For Example, if the user enters "C:\Program Files\Micros", AutoComplete
// first completely enumerate the "AutoComplete Lists" via IEnumString.  Then it
// will call the "AutoComplete Lists" with IACList::Expand(L"C:\Program Files").
// It will then enumerate the IEnumString interface again to get results in
// that directory.
//-------------------------------------------------------------------------

struct IACList
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IACList specific methods ***
  dword Expand;
};

//-------------------------------------------------------------------------
// IACList2 interface
// [Description]
//              This interface exists to allow the caller to set filter criteria
// for an AutoComplete List.  AutoComplete Lists generates the list of
// possible AutoComplete completions.  CLSID_ACListISF is one AutoComplete
// List COM object that implements this interface.
//-------------------------------------------------------------------------

enum AUTOCOMPLETELISTOPTIONS{
    ACLO_NONE            = 0,    // don't enumerate anything
    ACLO_CURRENTDIR      = 1,    // enumerate current directory
    ACLO_MYCOMPUTER      = 2,    // enumerate MyComputer
    ACLO_DESKTOP         = 4,    // enumerate Desktop Folder
    ACLO_FAVORITES       = 8,    // enumerate Favorites Folder
    ACLO_FILESYSONLY     = 16,   // enumerate only the file system
    ACLO_FILESYSDIRS     = 32,   // enumerate only the file system dirs, UNC shares, and UNC servers.
};

struct IACList2// IACList
{
// *** IACList2 specific methods ***
  dword SetOptions;
  dword GetOptions;
};

/*-------------------------------------------------------------------------*\
    INTERFACE: IProgressDialog

    DESCRIPTION:
        CLSID_ProgressDialog/IProgressDialog exist to allow a caller to create
    a progress dialog, set it's title, animation, text lines, progress, and
    it will do all the work of updating on a background thread, being modless,
    handling the user cancelling the operation, and estimating the time remaining
    until the operation completes.

    USAGE:
        This is how the dialog is used during operations that require progress
    and the ability to cancel:
    {
        DWORD dwComplete, dwTotal;
        IProgressDialog * ppd;
        CoCreateInstance(CLSID_ProgressDialog, NULL, CLSCTX_INPROC_SERVER, IID_IProgressDialog, (void **)&ppd);
        ppd->SetTitle(L"My Slow Operation");                                // Set the title of the dialog.
        ppd->SetAnimation(hInstApp, IDA_OPERATION_ANIMATION);               // Set the animation to play.
        ppd->StartProgressDialog(hwndParent, punk, PROGDLG_AUTOTIME, NULL); // Display and enable automatic estimated time remaining.
        ppd->SetCancelMsg(L"Please wait while the current operation is cleaned up", NULL);   // Will only be displayed if Cancel button is pressed.

        dwComplete = 0;
        dwTotal = CalcTotalUnitsToDo();

        // Reset because CalcTotalUnitsToDo() took a long time and the estimated time
        // is based on the time between ::StartProgressDialog() and the first
        // ::SetProgress() call.
        ppd->Timer(PDTIMER_RESET, NULL);

        for (nIndex = 0; nIndex < nTotal; nIndex++)
        {
            if (TRUE == ppd->HasUserCancelled())
                break;

            ppd->SetLine(2, L"I'm processing item n", FALSE, NULL);
            dwComplete += DoSlowOperation();

            ppd->SetProgress(dwCompleted, dwTotal);
        }

        ppd->StopProgressDialog();
        ppd->Release();
    }
\*-------------------------------------------------------------------------*/

// Flags for IProgressDialog::StartProgressDialog() (dwFlags)
#define PROGDLG_NORMAL          0x00000000      // default normal progress dlg behavior
#define PROGDLG_MODAL           0x00000001      // the dialog is modal to its hwndParent (default is modeless)
#define PROGDLG_AUTOTIME        0x00000002      // automatically updates the "Line3" text with the "time remaining" (you cant call SetLine3 if you passs this!)
#define PROGDLG_NOTIME          0x00000004      // we dont show the "time remaining" if this is set. We need this if dwTotal < dwCompleted for sparse files
#define PROGDLG_NOMINIMIZE      0x00000008      // Do not have a minimize button in the caption bar.
#define PROGDLG_NOPROGRESSBAR   0x00000010      // Don't display the progress bar

// Time Actions (dwTimerAction)
#define PDTIMER_RESET       0x00000001       // Reset the timer so the progress will be calculated from now until the first ::SetProgress() is called so
                                             // those this time will correspond to the values passed to ::SetProgress().  Only do this before ::SetProgress() is called.

struct IProgressDialog
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** IProgressDialog specific methods
  dword StartProgressDialog;
  dword StopProgressDialog;
  dword SetTitle;
  dword SetAnimation;
  dword HasUserCancelled;
  dword SetProgress;
  dword SetProgress64;
  dword SetLine;
  dword SetCancelMsg;
  dword Timer;
};

//==========================================================================
// IInputObjectSite/IInputObject interfaces
//  These interfaces allow us (or ISVs) to install/update external Internet
// Toolbar for IE and the shell. The frame will simply get the CLSID from
// registry (to be defined) and CoCreateInstance it.
//==========================================================================

//-------------------------------------------------------------------------
// IInputObjectSite interface
//   A site implements this interface so the object can communicate
// focus change to it.
// [Member functions]
// IInputObjectSite::OnFocusChangeIS(punkObj, fSetFocus)
//   Object (punkObj) is getting or losing the focus.
//-------------------------------------------------------------------------

struct IInputObjectSite
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IInputObjectSite specific methods ***
  dword OnFocusChangeIS;
};

//-------------------------------------------------------------------------
// IInputObject interface
//   An object implements this interface so the site can communicate
// activation and accelerator events to it.
// [Member functions]
// IInputObject::UIActivateIO(fActivate, lpMsg)
//   Activates or deactivates the object.  lpMsg may be NULL.  Returns
//   S_OK if the activation succeeded.
// IInputObject::HasFocusIO()
//   Returns S_OK if the object has the focus, S_FALSE if not.
// IInputObject::TranslateAcceleratorIO(lpMsg)
//   Allow the object to process the message.  Returns S_OK if the
//   message was processed (eaten).
//-------------------------------------------------------------------------

struct IInputObject
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IInputObject specific methods ***
  dword UIActivateIO;
  dword HasFocusIO;
  dword TranslateAcceleratorIO;
};

//==========================================================================
// IDockingWindowSite/IDockingWindow/IDockingWindowFrame interfaces
// IInputObjectSite/IInputObject interfaces
//  These interfaces allow us (or ISVs) to install/update external Internet
// Toolbar for IE and the shell. The frame will simply get the CLSID from
// registry (to be defined) and CoCreateInstance it.
//==========================================================================

//-------------------------------------------------------------------------
// IDockingWindowSite interface
//   A site implements this interface so the object can negotiate for
// and inquire about real estate on the site.
// [Member functions]
// IDockingWindowSite::GetBorderDW(punkObj, prcBorder)
//   Site returns the bounding rectangle of the given source object
//   (punkObj).
// IDockingWindowSite::RequestBorderSpaceDW(punkObj, pbw)
//   Object requests that the site makes room for it, as specified in
//   *pbw.
// IDockingWindowSite::SetBorderSpaceDW(punkObj, pbw)
//   Object requests that the site set the border spacing to the size
//   specified in *pbw.
//-------------------------------------------------------------------------

struct IDockingWindowSite
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IOleWindow methods ***
  dword GetWindow;
  dword ContextSensitiveHelp;
// *** IDockingWindowSite methods ***
  dword GetBorderDW;
  dword RequestBorderSpaceDW;
  dword SetBorderSpaceDW;
};

//-------------------------------------------------------------------------
// IDockingWindowFrame interface
// [Member functions]
// IDockingWindowFrame::AddToolbar(punkSrc, pwszItem, dwReserved)
// IDockingWindowFrame::RemoveToolbar(punkSrc, dwRemoveFlags)
// IDockingWindowFrame::FindToolbar(pwszItem, riid, ppv)
//-------------------------------------------------------------------------

// flags for RemoveToolbar
#define DWFRF_NORMAL            0x0000
#define DWFRF_DELETECONFIGDATA  0x0001

// flags for AddToolbar
#define DWFAF_HIDDEN  0x0001   // add hidden

struct IDockingWindowFrame
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IOleWindow methods ***
  dword GetWindow;
  dword ContextSensitiveHelp;
// *** IDockingWindowFrame methods ***
  dword AddToolbar;
  dword RemoveToolbar;
  dword FindToolbar;
};

//-------------------------------------------------------------------------
// IRunnableTask interface
//   This is a free threaded interface used for putting items on a background
// scheduler for execution within the view.  It allows a scheduler to start and
// stop tasks on as many worker threads as it deems necessary.
// Run(), Kill() and Suspend() may be called from different threads.
// [Member functions]
// IRunnableTask::Run(void)
//   Initiate the task to run.  This should return E_PENDING if the task
//   has been suspended.
// IRunnableTask::Kill(void)
// IRunnableTask::Suspend(void)
// IRunnableTask::Resume(void)
// IRunnableTask::IsRunning(void)
//-------------------------------------------------------------------------

// Convenient state values
#define IRTIR_TASK_NOT_RUNNING  0
#define IRTIR_TASK_RUNNING      1
#define IRTIR_TASK_SUSPENDED    2
#define IRTIR_TASK_PENDING      3
#define IRTIR_TASK_FINISHED     4

struct IRunnableTask
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IRunnableTask methods ***
  dword Run;
  dword Kill;
  dword Suspend;
  dword Resume;
  dword IsRunning;
};

/* ***************** IThumbnailCapture
 * CaptureThumbnail : takes an IHTMLDocument2 and returns a thumbnail of specified
 *                    size as an hbitmap
 */

struct IThumbnailCapture
{
// *** IThumbnailCapture methods ***
  dword CaptureThumbnail;
};

#if (_WIN32_IE >= 0x400)
// We need to make sure that WININET.H is included before this interface is
// used because the COMPONENT structure uses INTERNET_MAX_URL_LENGTH
#ifdef _WININET_
//  Flags and structures used by IActiveDesktop

struct WALLPAPEROPT
{
  DWORD   dwSize;     // size of this Structure.
  DWORD   dwStyle;    // WPSTYLE_* mentioned above
};

struct COMPONENTSOPT
{
  DWORD   dwSize;             //Size of this structure
  BOOL    fEnableComponents;  //Enable components?
  BOOL    fActiveDesktop;     // Active desktop enabled ?
};

struct COMPPOS
{
  DWORD   dwSize;             //Size of this structure
  int     iLeft;              //Left of top-left corner in screen co-ordinates.
  int     iTop;               //Top of top-left corner in screen co-ordinates.
  DWORD   dwWidth;            // Width in pixels.
  DWORD   dwHeight;           // Height in pixels.
  int     izIndex;            // Indicates the Z-order of the component.
  BOOL    fCanResize;         // Is the component resizeable?
  BOOL    fCanResizeX;        // Resizeable in X-direction?
  BOOL    fCanResizeY;        // Resizeable in Y-direction?
  int     iPreferredLeftPercent;    //Left of top-left corner as percent of screen width
  int     iPreferredTopPercent;     //Top of top-left corner as percent of screen height
};

struct COMPSTATEINFO
{
  DWORD   dwSize;             // Size of this structure.
  int     iLeft;              // Left of the top-left corner in screen co-ordinates.
  int     iTop;               // Top of top-left corner in screen co-ordinates.
  DWORD   dwWidth;            // Width in pixels.
  DWORD   dwHeight;           // Height in pixels.
  DWORD   dwItemState;        // State of the component (full-screen mode or split-screen or normal state.
};

#define COMPONENT_TOP 0x3fffffff  // izOrder value meaning component is at the top

// iCompType values
#define COMP_TYPE_HTMLDOC       0
#define COMP_TYPE_PICTURE       1
#define COMP_TYPE_WEBSITE       2
#define COMP_TYPE_CONTROL       3
#define COMP_TYPE_CFHTML        4
#define COMP_TYPE_MAX           4

// The following is the COMPONENT structure used in IE4.01, IE4.0 and Memphis. It is kept here for compatibility
// reasons.
struct IE4COMPONENT
{
  DWORD   dwSize;             //Size of this structure
  DWORD   dwID;               //Reserved: Set it always to zero.
  int     iComponentType;     //One of COMP_TYPE_*
  BOOL    fChecked;           // Is this component enabled?
  BOOL    fDirty;             // Had the component been modified and not yet saved to disk?
  BOOL    fNoScroll;          // Is the component scrollable?
  COMPPOS cpPos;              // Width, height etc.,
  WCHAR   wszFriendlyName[MAX_PATH];          // Friendly name of component.
  WCHAR   wszSource[INTERNET_MAX_URL_LENGTH]; //URL of the component.
  WCHAR   wszSubscribedURL[INTERNET_MAX_URL_LENGTH]; //Subscrined URL
};

// The following is the new NT5 component structure. Note that the initial portion of this component exactly
// matches the IE4COMPONENT structure. All new fields are added at the bottom and the dwSize field is used to
// distinguish between IE4COMPONENT and the new COMPONENT structures.
struct COMPONENT
{
  DWORD   dwSize;             //Size of this structure
  DWORD   dwID;               //Reserved: Set it always to zero.
  int     iComponentType;     //One of COMP_TYPE_*
  BOOL    fChecked;           // Is this component enabled?
  BOOL    fDirty;             // Had the component been modified and not yet saved to disk?
  BOOL    fNoScroll;          // Is the component scrollable?
  COMPPOS cpPos;              // Width, height etc.,
  WCHAR   wszFriendlyName[MAX_PATH];          // Friendly name of component.
  WCHAR   wszSource[INTERNET_MAX_URL_LENGTH]; //URL of the component.
  WCHAR   wszSubscribedURL[INTERNET_MAX_URL_LENGTH]; //Subscrined URL
  //New fields are added below. Everything above here must exactly match the IE4COMPONENT Structure.
  DWORD           dwCurItemState; // Current state of the Component.
  COMPSTATEINFO   csiOriginal;    // Original state of the component when it was first added.
  COMPSTATEINFO   csiRestored;    // Restored state of the component.
};

// Defines for dwCurItemState
#define IS_NORMAL               0x00000001
#define IS_FULLSCREEN           0x00000002
#define IS_SPLIT                0x00000004
#define IS_VALIDSIZESTATEBITS   IS_NORMAL|IS_SPLIT|IS_FULLSCREEN  // The set of IS_* state bits which define the "size" of the component - these bits are mutually exclusive.
#define IS_VALIDSTATEBITS       IS_NORMAL|IS_SPLIT|IS_FULLSCREEN|0x80000000|0x40000000  // All of the currently defined IS_* bits.

////////////////////////////////////////////
// Flags for IActiveDesktop::ApplyChanges()
#define AD_APPLY_SAVE             0x00000001
#define AD_APPLY_HTMLGEN          0x00000002
#define AD_APPLY_REFRESH          0x00000004
#define AD_APPLY_ALL              AD_APPLY_SAVE|AD_APPLY_HTMLGEN|AD_APPLY_REFRESH
#define AD_APPLY_FORCE            0x00000008
#define AD_APPLY_BUFFERED_REFRESH 0x00000010
#define AD_APPLY_DYNAMICREFRESH   0x00000020

////////////////////////////////////////////
// Flags for IActiveDesktop::GetWallpaperOptions()
//           IActiveDesktop::SetWallpaperOptions()
#define WPSTYLE_CENTER      0
#define WPSTYLE_TILE        1
#define WPSTYLE_STRETCH     2
#define WPSTYLE_MAX         3

////////////////////////////////////////////
// Flags for IActiveDesktop::ModifyComponent()
#define COMP_ELEM_TYPE          0x00000001
#define COMP_ELEM_CHECKED       0x00000002
#define COMP_ELEM_DIRTY         0x00000004
#define COMP_ELEM_NOSCROLL      0x00000008
#define COMP_ELEM_POS_LEFT      0x00000010
#define COMP_ELEM_POS_TOP       0x00000020
#define COMP_ELEM_SIZE_WIDTH    0x00000040
#define COMP_ELEM_SIZE_HEIGHT   0x00000080
#define COMP_ELEM_POS_ZINDEX    0x00000100
#define COMP_ELEM_SOURCE        0x00000200
#define COMP_ELEM_FRIENDLYNAME  0x00000400
#define COMP_ELEM_SUBSCRIBEDURL 0x00000800
#define COMP_ELEM_ORIGINAL_CSI  0x00001000
#define COMP_ELEM_RESTORED_CSI  0x00002000
#define COMP_ELEM_CURITEMSTATE  0x00004000

#define COMP_ELEM_ALL   COMP_ELEM_TYPE|COMP_ELEM_CHECKED|COMP_ELEM_DIRTY| \
                         COMP_ELEM_NOSCROLL|COMP_ELEM_POS_LEFT|COMP_ELEM_SIZE_WIDTH| \
                         COMP_ELEM_SIZE_HEIGHT|COMP_ELEM_POS_ZINDEX|COMP_ELEM_SOURCE| \
                         COMP_ELEM_FRIENDLYNAME|COMP_ELEM_POS_TOP|COMP_ELEM_SUBSCRIBEDURL| \
                         COMP_ELEM_ORIGINAL_CSI|COMP_ELEM_RESTORED_CSI|COMP_ELEM_CURITEMSTATE

////////////////////////////////////////////
// Flags for IActiveDesktop::AddDesktopItemWithUI()
enum
{
  DTI_ADDUI_DEFAULT               = 0x00000000,
  DTI_ADDUI_DISPSUBWIZARD         = 0x00000001,
  DTI_ADDUI_POSITIONITEM          = 0x00000002,
};

////////////////////////////////////////////
// Flags for IActiveDesktop::AddUrl()
#define ADDURL_SILENT           0X0001

////////////////////////////////////////////
// Default positions for ADI
#define COMPONENT_DEFAULT_LEFT    0xFFFF
#define COMPONENT_DEFAULT_TOP     0xFFFF

//  Interface for manipulating the Active Desktop.

struct IActiveDesktop
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IActiveDesktop methods
  dword ApplyChanges;
  dword GetWallpaper;
  dword SetWallpaper;
  dword GetWallpaperOptions;
  dword SetWallpaperOptions;
  dword GetPattern;
  dword SetPattern;
  dword GetDesktopItemOptions;
  dword SetDesktopItemOptions;
  dword AddDesktopItem;
  dword AddDesktopItemWithUI;
  dword ModifyDesktopItem;
  dword RemoveDesktopItem;
  dword GetDesktopItemCount;
  dword GetDesktopItem;
  dword GetDesktopItemByID;
  dword GenerateDesktopItemHtml;
  dword AddUrl;
  dword GetDesktopItemBySource;
};

#endif // _WININET_

#if (_WIN32_IE >= 0x0500)

#define MAX_COLUMN_NAME_LEN 80
#define MAX_COLUMN_DESC_LEN 128
/*
#pragma pack(push,1)
struct SHCOLUMNINFO{
  SHCOLUMNID  scid;                           // OUT the unique identifier of this column
  VARTYPE     vt;                             // OUT the native type of the data returned
  DWORD       fmt;                            // OUT this listview format (LVCFMT_LEFT, usually)
  UINT        cChars;                         // OUT the default width of the column, in characters
  DWORD       csFlags;                        // OUT SHCOLSTATE flags
  WCHAR wszTitle[MAX_COLUMN_NAME_LEN];        // OUT the title of the column
  WCHAR wszDescription[MAX_COLUMN_DESC_LEN];  // OUT full description of this column
};
#pragma pack(pop)
	*/
#pragma pack(push,8)

struct SHCOLUMNINIT{
  ULONG   dwFlags;              // initialization flags
  ULONG   dwReserved;           // reserved for future use.
  WCHAR   wszFolder[MAX_PATH];  // fully qualified folder path (or empty if multiple folders)
};

#define SHCDF_UPDATEITEM        0x00000001      // this flag is a hint that the file has changed since the last call to GetItemData

struct SHCOLUMNDATA{
  ULONG   dwFlags;             // combination of SHCDF_ flags.
  DWORD   dwFileAttributes;    // file attributes.
  ULONG   dwReserved;          // reserved for future use.
  WCHAR*  pwszExt;             // address of file name extension
  WCHAR   wszFile[MAX_PATH];   // Absolute path of file.
};

#pragma pack(pop)

// Note: these objects must be threadsafe!  GetItemData _will_ be called
// simultaneously from multiple threads.
struct IColumnProvider
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IColumnProvider methods
  dword Initialize;
  dword GetColumnInfo;
  dword GetItemData;
};

///////////////////////////////////////////////////////
// Drag and Drop helper
// Purpose: To expose the Shell drag images
// This interface is implemented in the shell by CLSID_DragDropHelper.
// To use:
//   If you are the source of a drag (i.e. in response to LV_DRAGBEGIN or
//    equivelent begin drag message) call
//    IDragSourceHelper::InitializeFromWindow
//              (<hwnd of window supporting DI_GETDRAGIMAGE>,
//               <pointer to POINT indicating offset to the mouse from
//                  the upper left corner of the image>,
//               <pointer to data object>)
//      NOTE: The Data object must support IDataObject::SetData with multiple
//            data types and GetData must implement data type cloning
//            (Including HGLOBAL), not just aliasing.
//   If you wish to have an image while over your application add the
//    IDragImages::Dr* calls to your IDropTarget implementation. For Example:
//    STDMETHODIMP CUserDropTarget::DragEnter(IDataObject* pDataObject,
//                                            DWORD grfKeyState,
//                                            POINTL pt, DWORD* pdwEffect)
//    {
//          // Process your DragEnter
//          // Call IDragImages::DragEnter last.
//          _pDropTargetHelper->DragEnter(_hwndDragOver, pDataObject,
//                                        (POINT*)&pt, *pdwEffect);
//          return hres;
//    }
//   If you wish to be able to source a drag image from a custom control,
//     implement a handler for the RegisterWindowMessage(DI_GETDRAGIMAGE).
//     The LPARAM is a pointer to an SHDRAGIMAGE structure.
//      sizeDragImage  -   Calculate the length and width required to render
//                          the images.
//      ptOffset       -   Calculate the offset from the upper left corner to
//                          the mouse cursor within the image
//      hbmpDragImage  -   CreateBitmap( sizeDragImage.cx, sizeDragImage.cy,
//                           GetDeviceCaps(hdcScreen, PLANES),
//                           GetDeviceCaps(hdcScreen, BITSPIXEL),
//                           NULL);
//   Drag Images will only be displayed on Windows NT 5.0 or later.
//   Note about IDropTargetHelper::Show - This method is provided for
//     showing/hiding the Drag image in low color depth video modes. When
//     painting to a window that is currently being dragged over (i.e. For
//     indicating a selection) you need to hide the drag image by calling this
//     method passing FALSE. After the window is done painting, Show the image
//     again by passing TRUE.

#pragma pack(push,8)

struct SHDRAGIMAGE
{
  SIZE        sizeDragImage;      // OUT - The length and Width of the
                                  //        rendered image
  POINT       ptOffset;           // OUT - The Offset from the mouse cursor to
                                  //        the upper left corner of the image
  HBITMAP     hbmpDragImage;      // OUT - The Bitmap containing the rendered
                                  //        drag images
  COLORREF    crColorKey;         // OUT - The COLORREF that has been blitted
                                  //        to the background of the images
};

#pragma pack(pop)

// This is sent to a window to get the rendered images to a bitmap
// Call RegisterWindowMessage to get the ID
#define DI_GETDRAGIMAGE     "ShellGetDragImage"

struct IDropTargetHelper
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDropTargetHelper
  dword DragEnter;
  dword DragLeave;
  dword DragOver;
  dword Drop;
  dword Show;
};

struct IDragSourceHelper
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // IDragSourceHelper
  dword InitializeFromBitmap;
  dword InitializeFromWindow;
};
#endif // _WIN32_IE >= 0x0500
#endif // _WIN32_IE

//==========================================================================
// Clipboard format which may be supported by IDataObject from system
// defined shell folders (such as directories, network, ...).
//==========================================================================
#define CFSTR_SHELLIDLIST                   "Shell IDList Array"      // CF_IDLIST
#define CFSTR_SHELLIDLISTOFFSET             "Shell Object Offsets"    // CF_OBJECTPOSITIONS
#define CFSTR_NETRESOURCES                  "Net Resource"            // CF_NETRESOURCE
#define CFSTR_FILEDESCRIPTORA               "FileGroupDescriptor"     // CF_FILEGROUPDESCRIPTORA
#define CFSTR_FILEDESCRIPTORW               "FileGroupDescriptorW"    // CF_FILEGROUPDESCRIPTORW
#define CFSTR_FILECONTENTS                  "FileContents"            // CF_FILECONTENTS
#define CFSTR_FILENAMEA                     "FileName"                // CF_FILENAMEA
#define CFSTR_FILENAMEW                     "FileNameW"               // CF_FILENAMEW
#define CFSTR_PRINTERGROUP                  "PrinterFriendlyName"     // CF_PRINTERS
#define CFSTR_FILENAMEMAPA                  "FileNameMap"             // CF_FILENAMEMAPA
#define CFSTR_FILENAMEMAPW                  "FileNameMapW"            // CF_FILENAMEMAPW
#define CFSTR_SHELLURL                      "UniformResourceLocator"
#define CFSTR_INETURLA                      CFSTR_SHELLURL
#define CFSTR_INETURLW                      "UniformResourceLocatorW"
#define CFSTR_PREFERREDDROPEFFECT           "Preferred DropEffect"
#define CFSTR_PERFORMEDDROPEFFECT           "Performed DropEffect"
#define CFSTR_PASTESUCCEEDED                "Paste Succeeded"
#define CFSTR_INDRAGLOOP                    "InShellDragLoop"
#define CFSTR_DRAGCONTEXT                   "DragContext"
#define CFSTR_MOUNTEDVOLUME                 "MountedVolume"
#define CFSTR_PERSISTEDDATAOBJECT           "PersistedDataObject"
#define CFSTR_TARGETCLSID                   "TargetCLSID"                         // HGLOBAL with a CLSID of the drop target
#define CFSTR_LOGICALPERFORMEDDROPEFFECT    "Logical Performed DropEffect"
#define CFSTR_AUTOPLAY_SHELLIDLISTS         "Autoplay Enumerated IDList Array"  //  (HGLOBAL with LPIDA)

#ifdef UNICODE
#define CFSTR_FILEDESCRIPTOR    CFSTR_FILEDESCRIPTORW
#define CFSTR_FILENAME          CFSTR_FILENAMEW
#define CFSTR_FILENAMEMAP       CFSTR_FILENAMEMAPW
#define CFSTR_INETURL           CFSTR_INETURLW
#else
#define CFSTR_FILEDESCRIPTOR    CFSTR_FILEDESCRIPTORA
#define CFSTR_FILENAME          CFSTR_FILENAMEA
#define CFSTR_FILENAMEMAP       CFSTR_FILENAMEMAPA
#define CFSTR_INETURL           CFSTR_INETURLA
#endif

#define DVASPECT_SHORTNAME      2 // use for CF_HDROP to get short name version of file paths
#define DVASPECT_COPY           3 // use to indicate format is a "Copy" of the data (FILECONTENTS, FILEDESCRIPTOR, etc)
#define DVASPECT_LINK           4 // use to indicate format is a "Shortcut" to the data (FILECONTENTS, FILEDESCRIPTOR, etc)

#pragma pack(push,8)
// format of CF_NETRESOURCE
struct NRESARRAY {     // anr
  UINT cItems;
  NETRESOURCE nr[1];
};
#pragma pack(pop)

// format of CF_IDLIST
struct CIDA {
  UINT cidl;          // number of relative IDList
  UINT aoffset[1];    // [0]: folder IDList, [1]-[cidl]: item IDList
};

// FILEDESCRIPTOR.dwFlags field indicate which fields are to be used
enum FD_FLAGS{
  FD_CLSID            = 0x0001,
  FD_SIZEPOINT        = 0x0002,
  FD_ATTRIBUTES       = 0x0004,
  FD_CREATETIME       = 0x0008,
  FD_ACCESSTIME       = 0x0010,
  FD_WRITESTIME       = 0x0020,
  FD_FILESIZE         = 0x0040,
  FD_PROGRESSUI       = 0x4000,       // Show Progress UI w/Drag and Drop
  FD_LINKUI           = 0x8000,       // 'link' UI is prefered
};

struct FILEDESCRIPTORA{ // fod
  DWORD dwFlags;
  CLSID clsid;
  SIZEL sizel;
  POINTL pointl;
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  CHAR   cFileName[ MAX_PATH ];
};

struct FILEDESCRIPTORW{ // fod
  DWORD dwFlags;
  CLSID clsid;
  SIZEL sizel;
  POINTL pointl;
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  WCHAR  cFileName[ MAX_PATH ];
};

#ifdef UNICODE
#define FILEDESCRIPTOR      FILEDESCRIPTORW
#else
#define FILEDESCRIPTOR      FILEDESCRIPTORA
#endif

// format of CF_FILEGROUPDESCRIPTOR
struct FILEGROUPDESCRIPTORA { // fgd
  UINT cItems;
  FILEDESCRIPTORA fgd[1];
};

struct FILEGROUPDESCRIPTORW { // fgd
  UINT cItems;
  FILEDESCRIPTORW fgd[1];
};

#ifdef UNICODE
#define FILEGROUPDESCRIPTOR     FILEGROUPDESCRIPTORW
#else
#define FILEGROUPDESCRIPTOR     FILEGROUPDESCRIPTORA
#endif

// format of CF_HDROP and CF_PRINTERS, in the HDROP case the data that follows
// is a double null terinated list of file names, for printers they are printer
// friendly names
struct DROPFILES {
  DWORD pFiles;                       // offset of file list
  POINT pt;                           // drop point (client coords)
  BOOL fNC;                           // is it on NonClient area
                                      // and pt is in screen coords
  BOOL fWide;                         // WIDE character switch
};

//====== File System Notification APIs ===============================

//  File System Notification flags
#define SHCNE_RENAMEITEM          0x00000001L
#define SHCNE_CREATE              0x00000002L
#define SHCNE_DELETE              0x00000004L
#define SHCNE_MKDIR               0x00000008L
#define SHCNE_RMDIR               0x00000010L
#define SHCNE_MEDIAINSERTED       0x00000020L
#define SHCNE_MEDIAREMOVED        0x00000040L
#define SHCNE_DRIVEREMOVED        0x00000080L
#define SHCNE_DRIVEADD            0x00000100L
#define SHCNE_NETSHARE            0x00000200L
#define SHCNE_NETUNSHARE          0x00000400L
#define SHCNE_ATTRIBUTES          0x00000800L
#define SHCNE_UPDATEDIR           0x00001000L
#define SHCNE_UPDATEITEM          0x00002000L
#define SHCNE_SERVERDISCONNECT    0x00004000L
#define SHCNE_UPDATEIMAGE         0x00008000L
#define SHCNE_DRIVEADDGUI         0x00010000L
#define SHCNE_RENAMEFOLDER        0x00020000L
#define SHCNE_FREESPACE           0x00040000L

// SHCNE_EXTENDED_EVENT: the extended event is identified in dwItem1,
// packed in LPITEMIDLIST format (same as SHCNF_DWORD packing).
// Additional information can be passed in the dwItem2 parameter
// of SHChangeNotify (called "pidl2" below), which if present, must also
// be in LPITEMIDLIST format.
// Unlike the standard events, the extended events are ORDINALs, so we
// don't run out of bits.  Extended events follow the SHCNEE_* naming
// convention.
// The dwItem2 parameter varies according to the extended event.

#define SHCNE_EXTENDED_EVENT      0x04000000L
#define SHCNE_ASSOCCHANGED        0x08000000L
#define SHCNE_DISKEVENTS          0x0002381FL
#define SHCNE_GLOBALEVENTS        0x0C0581E0L // Events that dont match pidls first
#define SHCNE_ALLEVENTS           0x7FFFFFFFL
#define SHCNE_INTERRUPT           0x80000000L // The presence of this flag indicates
                                            // that the event was generated by an
                                            // interrupt.  It is stripped out before
                                            // the clients of SHCNNotify_ see it.
// SHCNE_EXTENDED_EVENT extended events.  These events are ordinals.
// This is not a bitfield.
#define SHCNEE_ORDERCHANGED         2L  // pidl2 is the changed folder
#define SHCNEE_MSI_CHANGE           4L  // pidl2 is a SHChangeProductKeyAsIDList
#define SHCNEE_MSI_UNINSTALL        5L  // pidl2 is a SHChangeProductKeyAsIDList

// Flags
// uFlags & SHCNF_TYPE is an ID which indicates what dwItem1 and dwItem2 mean
#define SHCNF_IDLIST      0x0000        // LPITEMIDLIST
#define SHCNF_PATHA       0x0001        // path name
#define SHCNF_PRINTERA    0x0002        // printer friendly name
#define SHCNF_DWORD       0x0003        // DWORD
#define SHCNF_PATHW       0x0005        // path name
#define SHCNF_PRINTERW    0x0006        // printer friendly name
#define SHCNF_TYPE        0x00FF
#define SHCNF_FLUSH       0x1000
#define SHCNF_FLUSHNOWAIT 0x2000

#ifdef UNICODE
#define SHCNF_PATH      SHCNF_PATHW
#define SHCNF_PRINTER   SHCNF_PRINTERW
#else
#define SHCNF_PATH      SHCNF_PATHA
#define SHCNF_PRINTER   SHCNF_PRINTERA
#endif

//  APIs
extern WINAPI "shell32.dll"{
	void SHChangeNotify(LONG wEventId,UINT uFlags,LPCVOID dwItem1,LPCVOID dwItem2);
}
// IShellChangeNotify
struct IShellChangeNotify
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IShellChangeNotify methods ***
  dword OnChange;
};

// IQueryInfo
//-------------------------------------------------------------------------
// IQueryInfo interface
// [Methods]
//              ::GetInfoTip()
//-------------------------------------------------------------------------

struct IQueryInfo
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IQueryInfo methods ***
  dword GetInfoTip;
  dword GetInfoFlags;
};

#define QITIPF_DEFAULT          0x00000000
#define QITIPF_USENAME          0x00000001
#define QITIPF_LINKNOTARGET     0x00000002
#define QITIPF_LINKUSETARGET    0x00000004
#define QITIPF_USESLOWTIP       0x00000008  // Flag says it's OK to take a long time generating tip

#define QIF_CACHED           0x00000001
#define QIF_DONTEXPANDFOLDER 0x00000002

// SHAddToRecentDocs
#define SHARD_PIDL      0x00000001L
#define SHARD_PATHA     0x00000002L
#define SHARD_PATHW     0x00000003L

#ifdef UNICODE
#define SHARD_PATH  SHARD_PATHW
#else
#define SHARD_PATH  SHARD_PATHA
#endif

struct SHChangeProductKeyAsIDList {
  USHORT cb;
  WCHAR wszProductKey[39];
  USHORT cbZero;
};

extern WINAPI "shell32.dll"{
	void SHAddToRecentDocs(UINT uFlags,LPCVOID pv);
	void SHUpdateImageA(LPCSTR pszHashItem,int iIndex,UINT uFlags,int iImageIndex);
	void SHUpdateImageW(LPCWSTR pszHashItem,int iIndex,UINT uFlags,int iImageIndex);
#ifdef UNICODE
#define SHUpdateImage  SHUpdateImageW
#else
#define SHUpdateImage  SHUpdateImageA
#endif // !UNICODE

	dword SHGetInstanceExplorer(dword ppunk);
}
// SHGetDataFromIDListA/W
// SHGetDataFromIDList nFormat values TCHAR
#define SHGDFIL_FINDDATA        1
#define SHGDFIL_NETRESOURCE     2
#define SHGDFIL_DESCRIPTIONID   3
#define SHDID_ROOT_REGITEM          1
#define SHDID_FS_FILE               2
#define SHDID_FS_DIRECTORY          3
#define SHDID_FS_OTHER              4
#define SHDID_COMPUTER_DRIVE35      5
#define SHDID_COMPUTER_DRIVE525     6
#define SHDID_COMPUTER_REMOVABLE    7
#define SHDID_COMPUTER_FIXED        8
#define SHDID_COMPUTER_NETDRIVE     9
#define SHDID_COMPUTER_CDROM        10
#define SHDID_COMPUTER_RAMDISK      11
#define SHDID_COMPUTER_OTHER        12
#define SHDID_NET_DOMAIN            13
#define SHDID_NET_SERVER            14
#define SHDID_NET_SHARE             15
#define SHDID_NET_RESTOFNET         16
#define SHDID_NET_OTHER             17
#define SHDID_COMPUTER_IMAGING      18
#define SHDID_COMPUTER_AUDIO        19
#define SHDID_COMPUTER_SHAREDDOCS   20

#pragma pack(push,8)

struct SHDESCRIPTIONID {
  DWORD   dwDescriptionId;
  CLSID   clsid;
};
#pragma pack(pop)

// these delegate to IShellFolder2::GetItemData()
extern WINAPI "shell32.dll"{
	dword SHGetDataFromIDListA(dword psf,dword pidl,int nFormat,dword pv,int cb);
	dword SHGetDataFromIDListW(dword psf,dword pidl,int nFormat,dword pv,int cb);
}
#ifdef UNICODE
#define SHGetDataFromIDList  SHGetDataFromIDListW
#else
#define SHGetDataFromIDList  SHGetDataFromIDListA
#endif // !UNICODE

//===========================================================================

// PROPIDs for Internet Shortcuts (FMTID_Intshcut) to be used with
// IPropertySetStorage/IPropertyStorage
// The known property ids and their variant types are:
//      PID_IS_URL          [VT_LPWSTR]   URL
//      PID_IS_NAME         [VT_LPWSTR]   Name of the internet shortcut
//      PID_IS_WORKINGDIR   [VT_LPWSTR]   Working directory for the shortcut
//      PID_IS_HOTKEY       [VT_UI2]      Hotkey for the shortcut
//      PID_IS_SHOWCMD      [VT_I4]       Show command for shortcut
//      PID_IS_ICONINDEX    [VT_I4]       Index into file that has icon
//      PID_IS_ICONFILE     [VT_LPWSTR]   File that has the icon
//      PID_IS_WHATSNEW     [VT_LPWSTR]   What's New text
//      PID_IS_AUTHOR       [VT_LPWSTR]   Author
//      PID_IS_DESCRIPTION  [VT_LPWSTR]   Description text of site
//      PID_IS_COMMENT      [VT_LPWSTR]   User annotated comment
#define PID_IS_URL           2
#define PID_IS_NAME          4
#define PID_IS_WORKINGDIR    5
#define PID_IS_HOTKEY        6
#define PID_IS_SHOWCMD       7
#define PID_IS_ICONINDEX     8
#define PID_IS_ICONFILE      9
#define PID_IS_WHATSNEW      10
#define PID_IS_AUTHOR        11
#define PID_IS_DESCRIPTION   12
#define PID_IS_COMMENT       13

// PROPIDs for Internet Sites (FMTID_InternetSite) to be used with
// IPropertySetStorage/IPropertyStorage
// The known property ids and their variant types are:
//      PID_INTSITE_WHATSNEW     [VT_LPWSTR]   What's New text
//      PID_INTSITE_AUTHOR       [VT_LPWSTR]   Author
//      PID_INTSITE_LASTVISIT    [VT_FILETIME] Time site was last visited
//      PID_INTSITE_LASTMOD      [VT_FILETIME] Time site was last modified
//      PID_INTSITE_VISITCOUNT   [VT_UI4]      Number of times user has visited
//      PID_INTSITE_DESCRIPTION  [VT_LPWSTR]   Description text of site
//      PID_INTSITE_COMMENT      [VT_LPWSTR]   User annotated comment
//      PID_INTSITE_RECURSE      [VT_UI4]      Levels to recurse (0-3)
//      PID_INTSITE_WATCH        [VT_UI4]      PIDISM_ flags
//      PID_INTSITE_SUBSCRIPTION [VT_UI8]      Subscription cookie
//      PID_INTSITE_URL          [VT_LPWSTR]   URL
//      PID_INTSITE_TITLE        [VT_LPWSTR]   Title
//      PID_INTSITE_CODEPAGE     [VT_UI4]      Codepage of the document
//      PID_INTSITE_TRACKING     [VT_UI4]      Tracking
//      PID_INTSITE_ICONINDEX    [VT_I4]       Retrieve the index to the icon
//      PID_INTSITE_ICONFILE     [VT_LPWSTR]   Retrieve the file containing the icon index.
#define PID_INTSITE_WHATSNEW      2
#define PID_INTSITE_AUTHOR        3
#define PID_INTSITE_LASTVISIT     4
#define PID_INTSITE_LASTMOD       5
#define PID_INTSITE_VISITCOUNT    6
#define PID_INTSITE_DESCRIPTION   7
#define PID_INTSITE_COMMENT       8
#define PID_INTSITE_FLAGS         9
#define PID_INTSITE_CONTENTLEN    10
#define PID_INTSITE_CONTENTCODE   11
#define PID_INTSITE_RECURSE       12
#define PID_INTSITE_WATCH         13
#define PID_INTSITE_SUBSCRIPTION  14
#define PID_INTSITE_URL           15
#define PID_INTSITE_TITLE         16
#define PID_INTSITE_CODEPAGE      18
#define PID_INTSITE_TRACKING      19
#define PID_INTSITE_ICONINDEX     20
#define PID_INTSITE_ICONFILE      21

// Flags for PID_IS_FLAGS
#define PIDISF_RECENTLYCHANGED  0x00000001
#define PIDISF_CACHEDSTICKY     0x00000002
#define PIDISF_CACHEIMAGES      0x00000010
#define PIDISF_FOLLOWALLLINKS   0x00000020

// Values for PID_INTSITE_WATCH
#define PIDISM_GLOBAL           0       // Monitor based on global setting
#define PIDISM_WATCH            1       // User says watch
#define PIDISM_DONTWATCH        2       // User says don't watch

////////////////////////////////////////////////////////////////////
// The shell keeps track of some per-user state to handle display
// options that is of major interest to ISVs.
// The key one requested right now is "DoubleClickInWebView".
//  SysFiles are these windows special files:
//      "dll sys vxd 386 drv"
//  hidden files are files with the FILE_ATTRIBUTE_HIDDEN attribute
//  system files are files with the FILE_ATTRIBUTE_SYSTEM attribute
//      fShowAllObjects fShowSysFiles   Result
//      --------------- -------------   ------
//      0               0               hide hidden + SysFiles + system files
//      0               1               hide hidden files.
//      1               0               show all files.
//      1               1               show all files.
struct SHELLFLAGSTATE{
  BOOL fShowAllObjects : 1;
  BOOL fShowExtensions : 1;
  BOOL fNoConfirmRecycle : 1;
  BOOL fShowSysFiles : 1;
  BOOL fShowCompColor : 1;
  BOOL fDoubleClickInWebView : 1;
  BOOL fDesktopHTML : 1;
  BOOL fWin95Classic : 1;
  BOOL fDontPrettyPath : 1;
  BOOL fShowAttribCol : 1;
  BOOL fMapNetDrvBtn : 1;
  BOOL fShowInfoTip : 1;
  BOOL fHideIcons : 1;
  UINT fRestFlags : 3;
};

#define SSF_SHOWALLOBJECTS          0x00000001
#define SSF_SHOWEXTENSIONS          0x00000002
#define SSF_SHOWCOMPCOLOR           0x00000008
#define SSF_SHOWSYSFILES            0x00000020
#define SSF_DOUBLECLICKINWEBVIEW    0x00000080
#define SSF_SHOWATTRIBCOL           0x00000100
#define SSF_DESKTOPHTML             0x00000200
#define SSF_WIN95CLASSIC            0x00000400
#define SSF_DONTPRETTYPATH          0x00000800
#define SSF_SHOWINFOTIP             0x00002000
#define SSF_MAPNETDRVBUTTON         0x00001000
#define SSF_NOCONFIRMRECYCLE        0x00008000
#define SSF_HIDEICONS               0x00004000

extern WINAPI "shell32.dll"{
// SHGetSettings(LPSHELLFLAGSTATE lpss, DWORD dwMask)
// Specify the bits you are interested in in dwMask and they will be
// filled out in the lpss structure.
// When these settings change, a WM_SETTINGCHANGE message is sent
// with the string lParam value of "ShellState".
	void SHGetSettings(dword lpsfs,DWORD dwMask);

// SHBindToParent(LPCITEMIDLIST pidl, REFIID riid, void **ppv, LPCITEMIDLIST *ppidlLast)
// Given a pidl, you can get an interface pointer (as specified by riid) of the pidl's parent folder (in ppv)
// If ppidlLast is non-NULL, you can also get the pidl of the last item.
	dword SHBindToParent(dword pidl,dword riid,dword ppv,dword ppidlLast);

// SHSTDAPI SHParseDisplayName(PCWSTR pszName, IBindCtx *pbc, LPITEMIDLIST *ppidl, SFGAOF sfgaoIn, SFGAOF *psfgaoOut)
//  given a string it will call psfDesktop->ParseDisplayName() to try and create a pidl
//  if no pbc specified, it uses the preferred options for parsing.
//  this includes mapping file system paths to their appropriate aliased location (RegisterObjectParam(STR_PARSE_TRANSLATE_ALIASES))
//  psfgaoOut is optional for SFGAO attributes
	dword SHParseDisplayName(dword pszName,dword pbc,dword ppidl,dword sfgaoIn,dword psfgaoOut);

// SHPathPrepareForWrite(HWND hwnd, IUnknown *punkEnableModless, LPCTSTR pszPath, DWORD dwFlags)
// DESCRIPTION:
//     This API will prepare the path for the caller.  This includes:
// 1. Prompting for the ejectable media to be re-inserted. (Floppy, CD-ROM, ZIP drive, etc.)
// 2. Prompting for the media to be formatted. (Floppy, hard drive, etc.)
// 3. Remount mapped drives if the connection was lost. (\\unc\share mapped to N: becomes disconnected)
// 4. If the path doesn't exist, create it.  (SHPPFW_DIRCREATE and SHPPFW_ASKDIRCREATE)
// 5. Display an error if the media is read only. (SHPPFW_NOWRITECHECK not set)
// PARAMETERS:
//      hwnd: Parernt window for UI.  NULL means don't display UI. OPTIONAL
//      punkEnableModless: Parent that will be set to modal during UI using IOleInPlaceActiveObject::EnableModeless(). OPTIONAL
//      pszPath: Path to verify is valid for writting.  This can be a UNC or file drive path.  The path
//               should only contain directories.  Pass SHPPFW_IGNOREFILENAME if the last path segment
//               is always filename to ignore.
//      dwFlags: SHPPFW_* Flags to modify behavior
//-------------------------------------------------------------------------
#define SHPPFW_NONE             0x00000000
#define SHPPFW_DEFAULT          SHPPFW_DIRCREATE        // May change
#define SHPPFW_DIRCREATE        0x00000001              // Create the directory if it doesn't exist without asking the user.
#define SHPPFW_ASKDIRCREATE     0x00000002              // Create the directory if it doesn't exist after asking the user.
#define SHPPFW_IGNOREFILENAME   0x00000004              // Ignore the last item in pszPath because it's a file.  Example: pszPath="C:\DirA\DirB", only use "C:\DirA".
#define SHPPFW_NOWRITECHECK     0x00000008              // Caller only needs to read from the drive, so don't check if it's READ ONLY.
#define SHPPFW_MEDIACHECKONLY   0x00000010              // do the retrys on the media (or net path), return errors if the file can't be found

	dword SHPathPrepareForWriteA(HWND hwnd,dword punkEnableModless,LPCSTR pszPath,DWORD dwFlags);
	dword SHPathPrepareForWriteW(HWND hwnd,dword punkEnableModless,LPCWSTR pszPath,DWORD dwFlags);
#ifdef UNICODE
#define SHPathPrepareForWrite  SHPathPrepareForWriteW
#else
#define SHPathPrepareForWrite  SHPathPrepareForWriteA
#endif // !UNICODE
}
//--------------------------------------------------------------------------
// Interface used for exposing the INI file methods on a shortcut file
//--------------------------------------------------------------------------
struct INamedPropertyBag
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** INamedPropertyBag methods ***
  dword ReadPropertyNPB;
  dword WritePropertyNPB;
  dword RemovePropertyNPB;
};

extern WINAPI "shell32.dll"{
#ifdef __urlmon_h__
//    NOTE: urlmon.h must be included before shlobj.h to access this function.
//    SoftwareUpdateMessageBox
//    Provides a standard message box for the alerting the user that a software
//    update is available or installed. No UI will be displayed if there is no
//    update available or if the available update version is less than or equal
//    to the Advertised update version.
//    hWnd                - [in] Handle of owner window
//    szDistUnit          - [in] Unique identifier string for a code distribution unit. For
//                               ActiveX controls and Active Setup installed components, this
//                               is typically a GUID string.
//    dwFlags             - [in] Must be 0.
//    psdi                - [in,out] Pointer to SOFTDISTINFO ( see URLMon.h ). May be NULL.
//                                cbSize should be initialized
//                                by the caller to sizeof(SOFTDISTINFO), dwReserved should be set to 0.
//    RETURNS:
//    IDNO     - The user chose cancel. If *pbRemind is FALSE, the caller should save the
//               update version from the SOFTDISTINFO and pass it in as the Advertised
//               version in future calls.
//    IDYES    - The user has selected Update Now/About Update. The caller should navigate to
//               the SOFTDISTINFO's pszHREF to initiate the install or learn about it.
//               The caller should save the update version from the SOFTDISTINFO and pass
//               it in as the Advertised version in future calls.
//    IDIGNORE - There is no pending software update. Note: There is
//               no Ignore button in the standard UI. This occurs if the available
//               version is less than the installed version or is not present or if the
//               Advertised version is greater than or equal to the update version.
//    IDABORT  - An error occured. Call GetSoftwareUpdateInfo() for a more specific HRESULT.
//               Note: There is no Abort button in the standard UI.

	DWORD SoftwareUpdateMessageBox(HWND hWnd,LPCWSTR szDistUnit,DWORD dwFlags,dword psdi );
#endif // if __urlmon_h__

#pragma pack(pop)

	BOOL ImportPrivacySettings(LPCWSTR szFilename,dword pfParsePrivacyPreferences,dword pfParsePerSiteRules);
	dword DoPrivacyDlg(HWND hwndParent,dword pszUrl,dword pPrivacyEnum,BOOL fReportAllSites);
}
#endif // _SHLOBJ_H_
