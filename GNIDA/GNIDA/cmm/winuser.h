/****************************************************************************
* winuser.h -- USER procedure declarations, constant definitions and macros *
* Copyright (c) Microsoft Corporation. All rights reserved.                          *
****************************************************************************/

#ifndef _WINUSER_
#define _WINUSER_

#ifndef WINVER
#define WINVER  0x0500      /* version 5.0 */
#endif /* !WINVER */

//#include <stdarg.h>

#ifndef NOUSER

#define HDWP HANDLE
#define MENUTEMPLATEA void
#define MENUTEMPLATEW VOID
#ifdef UNICODE
#define MENUTEMPLATE MENUTEMPLATEW
#else
#define MENUTEMPLATE MENUTEMPLATEA
#endif // UNICODE
#define LPMENUTEMPLATEA dword
#define LPMENUTEMPLATEW dword
#ifdef UNICODE
#define LPMENUTEMPLATE LPMENUTEMPLATEW
#else
#define LPMENUTEMPLATE LPMENUTEMPLATEA
#endif // UNICODE

#define IS_INTRESOURCE(_r) (_r>>16==0)

#ifndef NORESOURCE

/*
 * Predefined Resource Types
 */
#define RT_CURSOR           1
#define RT_BITMAP           2
#define RT_ICON             3
#define RT_MENU             4
#define RT_DIALOG           5
#define RT_STRING           6
#define RT_FONTDIR          7
#define RT_FONT             8
#define RT_ACCELERATOR      9
#define RT_RCDATA           10
#define RT_MESSAGETABLE     11

#define DIFFERENCE     11
#define RT_GROUP_CURSOR RT_CURSOR + DIFFERENCE
#define RT_GROUP_ICON   RT_ICON + DIFFERENCE
#define RT_VERSION      16
#define RT_DLGINCLUDE   17
#define RT_PLUGPLAY     19
#define RT_VXD          20
#define RT_ANICURSOR    21
#define RT_ANIICON      22
#define RT_HTML         23
#ifdef RC_INVOKED
#define RT_MANIFEST                        24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID  1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID 1   /* inclusive */
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16  /* inclusive */
#else  /* RC_INVOKED */
#define RT_MANIFEST                        24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID 1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID  1
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16
#endif /* RC_INVOKED */

#endif /* !NORESOURCE */

#define va_list dword

extern WINAPI "user32.dll"{
	int wvsprintfA(LPSTR,LPCSTR,va_list arglist);
	int wvsprintfW(LPWSTR,LPCWSTR,va_list arglist);
#ifdef UNICODE
#define wvsprintf  wvsprintfW
#else
#define wvsprintf  wvsprintfA
#endif // !UNICODE
	int cdecl wsprintfA(LPSTR,LPCSTR,...);
	int cdecl wsprintfW(LPWSTR,LPCWSTR,...);
#ifdef UNICODE
#define wsprintf  wsprintfW
#else
#define wsprintf  wsprintfA
#endif // !UNICODE
}
/*
 * SPI_SETDESKWALLPAPER defined constants
 */
#define SETWALLPAPER_DEFAULT    -1

#ifndef NOSCROLL

/*
 * Scroll Bar Constants
 */
#define SB_HORZ             0
#define SB_VERT             1
#define SB_CTL              2
#define SB_BOTH             3

/*
 * Scroll Bar Commands
 */
#define SB_LINEUP           0
#define SB_LINELEFT         0
#define SB_LINEDOWN         1
#define SB_LINERIGHT        1
#define SB_PAGEUP           2
#define SB_PAGELEFT         2
#define SB_PAGEDOWN         3
#define SB_PAGERIGHT        3
#define SB_THUMBPOSITION    4
#define SB_THUMBTRACK       5
#define SB_TOP              6
#define SB_LEFT             6
#define SB_BOTTOM           7
#define SB_RIGHT            7
#define SB_ENDSCROLL        8

#endif /* !NOSCROLL */

#ifndef NOSHOWWINDOW

/*
 * ShowWindow() Commands
 */
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_NORMAL           1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_MAXIMIZE         3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9
#define SW_SHOWDEFAULT      10
#define SW_FORCEMINIMIZE    11
#define SW_MAX              11

/*
 * Old ShowWindow() Commands
 */
#define HIDE_WINDOW         0
#define SHOW_OPENWINDOW     1
#define SHOW_ICONWINDOW     2
#define SHOW_FULLSCREEN     3
#define SHOW_OPENNOACTIVATE 4

/*
 * Identifiers for the WM_SHOWWINDOW message
 */
#define SW_PARENTCLOSING    1
#define SW_OTHERZOOM        2
#define SW_PARENTOPENING    3
#define SW_OTHERUNZOOM      4

#endif /* !NOSHOWWINDOW */

/*
 * AnimateWindow() Commands
 */
#define AW_HOR_POSITIVE             0x00000001
#define AW_HOR_NEGATIVE             0x00000002
#define AW_VER_POSITIVE             0x00000004
#define AW_VER_NEGATIVE             0x00000008
#define AW_CENTER                   0x00000010
#define AW_HIDE                     0x00010000
#define AW_ACTIVATE                 0x00020000
#define AW_SLIDE                    0x00040000
#define AW_BLEND                    0x00080000

/*
 * WM_KEYUP/DOWN/CHAR HIWORD(lParam) flags
 */
#define KF_EXTENDED       0x0100
#define KF_DLGMODE        0x0800
#define KF_MENUMODE       0x1000
#define KF_ALTDOWN        0x2000
#define KF_REPEAT         0x4000
#define KF_UP             0x8000

#ifndef NOVIRTUALKEYCODES

/*
 * Virtual Keys, Standard Set
 */
#define VK_LBUTTON        0x01
#define VK_RBUTTON        0x02
#define VK_CANCEL         0x03
#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */

/*
 * 0x07 : unassigned
 */

#define VK_BACK           0x08
#define VK_TAB            0x09

/*
 * 0x0A - 0x0B : reserved
 */

#define VK_CLEAR          0x0C
#define VK_RETURN         0x0D
#define VK_SHIFT          0x10
#define VK_CONTROL        0x11
#define VK_MENU           0x12
#define VK_PAUSE          0x13
#define VK_CAPITAL        0x14
#define VK_KANA           0x15
#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define VK_HANGUL         0x15
#define VK_JUNJA          0x17
#define VK_FINAL          0x18
#define VK_HANJA          0x19
#define VK_KANJI          0x19
#define VK_ESCAPE         0x1B
#define VK_CONVERT        0x1C
#define VK_NONCONVERT     0x1D
#define VK_ACCEPT         0x1E
#define VK_MODECHANGE     0x1F
#define VK_SPACE          0x20
#define VK_PRIOR          0x21
#define VK_NEXT           0x22
#define VK_END            0x23
#define VK_HOME           0x24
#define VK_LEFT           0x25
#define VK_UP             0x26
#define VK_RIGHT          0x27
#define VK_DOWN           0x28
#define VK_SELECT         0x29
#define VK_PRINT          0x2A
#define VK_EXECUTE        0x2B
#define VK_SNAPSHOT       0x2C
#define VK_INSERT         0x2D
#define VK_DELETE         0x2E
#define VK_HELP           0x2F

/*
 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x40 : unassigned
 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
#define VK_A 'A'
#define VK_B 'B'
#define VK_C 'C'
#define VK_D 'D'
#define VK_E 'E'
#define VK_F 'F'
#define VK_G 'G'
#define VK_H 'H'
#define VK_I 'I'
#define VK_J 'J'
#define VK_K 'K'
#define VK_L 'L'
#define VK_M 'M'
#define VK_N 'N'
#define VK_O 'O'
#define VK_P 'P'
#define VK_Q 'Q'
#define VK_LWIN           0x5B
#define VK_RWIN           0x5C
#define VK_APPS           0x5D

/*
 * 0x5E : reserved
 */
#define VK_SLEEP          0x5F
#define VK_NUMPAD0        0x60
#define VK_NUMPAD1        0x61
#define VK_NUMPAD2        0x62
#define VK_NUMPAD3        0x63
#define VK_NUMPAD4        0x64
#define VK_NUMPAD5        0x65
#define VK_NUMPAD6        0x66
#define VK_NUMPAD7        0x67
#define VK_NUMPAD8        0x68
#define VK_NUMPAD9        0x69
#define VK_MULTIPLY       0x6A
#define VK_ADD            0x6B
#define VK_SEPARATOR      0x6C
#define VK_SUBTRACT       0x6D
#define VK_DECIMAL        0x6E
#define VK_DIVIDE         0x6F
#define VK_F1             0x70
#define VK_F2             0x71
#define VK_F3             0x72
#define VK_F4             0x73
#define VK_F5             0x74
#define VK_F6             0x75
#define VK_F7             0x76
#define VK_F8             0x77
#define VK_F9             0x78
#define VK_F10            0x79
#define VK_F11            0x7A
#define VK_F12            0x7B
#define VK_F13            0x7C
#define VK_F14            0x7D
#define VK_F15            0x7E
#define VK_F16            0x7F
#define VK_F17            0x80
#define VK_F18            0x81
#define VK_F19            0x82
#define VK_F20            0x83
#define VK_F21            0x84
#define VK_F22            0x85
#define VK_F23            0x86
#define VK_F24            0x87

/*
 * 0x88 - 0x8F : unassigned
 */
#define VK_NUMLOCK        0x90
#define VK_SCROLL         0x91

/*
 * NEC PC-9800 kbd definitions
 */
#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad

/*
 * Fujitsu/OASYS kbd definitions
 */
#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

/*
 * 0x97 - 0x9F : unassigned
 */

/*
 * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
 * No other API or message will distinguish left and right keys in this way.
 */
#define VK_LSHIFT         0xA0
#define VK_RSHIFT         0xA1
#define VK_LCONTROL       0xA2
#define VK_RCONTROL       0xA3
#define VK_LMENU          0xA4
#define VK_RMENU          0xA5
#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC
#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

/*
 * 0xB8 - 0xB9 : reserved
 */
#define VK_OEM_1          0xBA   // ';:' for US
#define VK_OEM_PLUS       0xBB   // '+' any country
#define VK_OEM_COMMA      0xBC   // ',' any country
#define VK_OEM_MINUS      0xBD   // '-' any country
#define VK_OEM_PERIOD     0xBE   // '.' any country
#define VK_OEM_2          0xBF   // '/?' for US
#define VK_OEM_3          0xC0   // '`~' for US

/*
 * 0xC1 - 0xD7 : reserved
 */

/*
 * 0xD8 - 0xDA : unassigned
 */
#define VK_OEM_4          0xDB  //  '[{' for US
#define VK_OEM_5          0xDC  //  '\|' for US
#define VK_OEM_6          0xDD  //  ']}' for US
#define VK_OEM_7          0xDE  //  ''"' for US
#define VK_OEM_8          0xDF

/*
 * 0xE0 : reserved
 */

/*
 * Various extended or enhanced keyboards
 */
#define VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define VK_ICO_HELP       0xE3  //  Help key on ICO
#define VK_ICO_00         0xE4  //  00 key on ICO
#define VK_PROCESSKEY     0xE5
#define VK_ICO_CLEAR      0xE6
#define VK_PACKET         0xE7

/*
 * 0xE8 : unassigned
 */

/*
 * Nokia/Ericsson definitions
 */
#define VK_OEM_RESET      0xE9
#define VK_OEM_JUMP       0xEA
#define VK_OEM_PA1        0xEB
#define VK_OEM_PA2        0xEC
#define VK_OEM_PA3        0xED
#define VK_OEM_WSCTRL     0xEE
#define VK_OEM_CUSEL      0xEF
#define VK_OEM_ATTN       0xF0
#define VK_OEM_FINISH     0xF1
#define VK_OEM_COPY       0xF2
#define VK_OEM_AUTO       0xF3
#define VK_OEM_ENLW       0xF4
#define VK_OEM_BACKTAB    0xF5
#define VK_ATTN           0xF6
#define VK_CRSEL          0xF7
#define VK_EXSEL          0xF8
#define VK_EREOF          0xF9
#define VK_PLAY           0xFA
#define VK_ZOOM           0xFB
#define VK_NONAME         0xFC
#define VK_PA1            0xFD
#define VK_OEM_CLEAR      0xFE

/*
 * 0xFF : reserved
 */

#endif /* !NOVIRTUALKEYCODES */

#ifndef NOWH

/*
 * SetWindowsHook() codes
 */
#define WH_MIN              -1
#define WH_MSGFILTER        -1
#define WH_JOURNALRECORD    0
#define WH_JOURNALPLAYBACK  1
#define WH_KEYBOARD         2
#define WH_GETMESSAGE       3
#define WH_CALLWNDPROC      4
#define WH_CBT              5
#define WH_SYSMSGFILTER     6
#define WH_MOUSE            7
#define WH_HARDWARE         8
#define WH_DEBUG            9
#define WH_SHELL           10
#define WH_FOREGROUNDIDLE  11
#define WH_CALLWNDPROCRET  12
#define WH_KEYBOARD_LL     13
#define WH_MOUSE_LL        14
#if(WINVER >= 0x0400)
#if (_WIN32_WINNT >= 0x0400)
#define WH_MAX             14
#else
#define WH_MAX             12
#endif // (_WIN32_WINNT >= 0x0400)
#else
#define WH_MAX             11
#endif

#define WH_MINHOOK         WH_MIN
#define WH_MAXHOOK         WH_MAX

/*
 * Hook Codes
 */
#define HC_ACTION           0
#define HC_GETNEXT          1
#define HC_SKIP             2
#define HC_NOREMOVE         3
#define HC_NOREM            HC_NOREMOVE
#define HC_SYSMODALON       4
#define HC_SYSMODALOFF      5

/*
 * CBT Hook Codes
 */
#define HCBT_MOVESIZE       0
#define HCBT_MINMAX         1
#define HCBT_QS             2
#define HCBT_CREATEWND      3
#define HCBT_DESTROYWND     4
#define HCBT_ACTIVATE       5
#define HCBT_CLICKSKIPPED   6
#define HCBT_KEYSKIPPED     7
#define HCBT_SYSCOMMAND     8
#define HCBT_SETFOCUS       9

/*
 * HCBT_CREATEWND parameters pointed to by lParam
 */
struct CBT_CREATEWND
{
  dword lpcs;
  dword           hwndInsertAfter;
};
#define CBT_CREATEWNDW CBT_CREATEWND
#define CBT_CREATEWNDA CBT_CREATEWND

/*
 * HCBT_ACTIVATE structure pointed to by lParam
 */
struct CBTACTIVATESTRUCT
{
  BOOL    fMouse;
  dword    hWndActive;
};

/*
 * WTSSESSION_NOTIFICATION struct pointed by lParam, for WM_WTSSESSION_CHANGE
 */
struct WTSSESSION_NOTIFICATION
{
  DWORD cbSize;
  DWORD dwSessionId;

};

/*
 * codes passed in WPARAM for WM_WTSSESSION_CHANGE
 */
#define WTS_CONSOLE_CONNECT                0x1
#define WTS_CONSOLE_DISCONNECT             0x2
#define WTS_REMOTE_CONNECT                 0x3
#define WTS_REMOTE_DISCONNECT              0x4
#define WTS_SESSION_LOGON                  0x5
#define WTS_SESSION_LOGOFF                 0x6
#define WTS_SESSION_LOCK                   0x7
#define WTS_SESSION_UNLOCK                 0x8

/*
 * WH_MSGFILTER Filter Proc Codes
 */
#define MSGF_DIALOGBOX      0
#define MSGF_MESSAGEBOX     1
#define MSGF_MENU           2
#define MSGF_SCROLLBAR      5
#define MSGF_NEXTWINDOW     6
#define MSGF_MAX            8                       // unused
#define MSGF_USER           4096

/*
 * Shell support
 */
#define HSHELL_WINDOWCREATED        1
#define HSHELL_WINDOWDESTROYED      2
#define HSHELL_ACTIVATESHELLWINDOW  3
#define HSHELL_WINDOWACTIVATED      4
#define HSHELL_GETMINRECT           5
#define HSHELL_REDRAW               6
#define HSHELL_TASKMAN              7
#define HSHELL_LANGUAGE             8
#define HSHELL_ACCESSIBILITYSTATE   11
#define HSHELL_APPCOMMAND           12
#define HSHELL_WINDOWREPLACED       13
/* wparam for HSHELL_ACCESSIBILITYSTATE */
#define    ACCESS_STICKYKEYS            0x0001
#define    ACCESS_FILTERKEYS            0x0002
#define    ACCESS_MOUSEKEYS             0x0003

/* cmd for HSHELL_APPCOMMAND and WM_APPCOMMAND */
#define APPCOMMAND_BROWSER_BACKWARD       1
#define APPCOMMAND_BROWSER_FORWARD        2
#define APPCOMMAND_BROWSER_REFRESH        3
#define APPCOMMAND_BROWSER_STOP           4
#define APPCOMMAND_BROWSER_SEARCH         5
#define APPCOMMAND_BROWSER_FAVORITES      6
#define APPCOMMAND_BROWSER_HOME           7
#define APPCOMMAND_VOLUME_MUTE            8
#define APPCOMMAND_VOLUME_DOWN            9
#define APPCOMMAND_VOLUME_UP              10
#define APPCOMMAND_MEDIA_NEXTTRACK        11
#define APPCOMMAND_MEDIA_PREVIOUSTRACK    12
#define APPCOMMAND_MEDIA_STOP             13
#define APPCOMMAND_MEDIA_PLAY_PAUSE       14
#define APPCOMMAND_LAUNCH_MAIL            15
#define APPCOMMAND_LAUNCH_MEDIA_SELECT    16
#define APPCOMMAND_LAUNCH_APP1            17
#define APPCOMMAND_LAUNCH_APP2            18
#define APPCOMMAND_BASS_DOWN              19
#define APPCOMMAND_BASS_BOOST             20
#define APPCOMMAND_BASS_UP                21
#define APPCOMMAND_TREBLE_DOWN            22
#define APPCOMMAND_TREBLE_UP              23
#define APPCOMMAND_MICROPHONE_VOLUME_MUTE 24
#define APPCOMMAND_MICROPHONE_VOLUME_DOWN 25
#define APPCOMMAND_MICROPHONE_VOLUME_UP   26
#define APPCOMMAND_HELP                   27
#define APPCOMMAND_FIND                   28
#define APPCOMMAND_NEW                    29
#define APPCOMMAND_OPEN                   30
#define APPCOMMAND_CLOSE                  31
#define APPCOMMAND_SAVE                   32
#define APPCOMMAND_PRINT                  33
#define APPCOMMAND_UNDO                   34
#define APPCOMMAND_REDO                   35
#define APPCOMMAND_COPY                   36
#define APPCOMMAND_CUT                    37
#define APPCOMMAND_PASTE                  38
#define APPCOMMAND_REPLY_TO_MAIL          39
#define APPCOMMAND_FORWARD_MAIL           40
#define APPCOMMAND_SEND_MAIL              41
#define APPCOMMAND_SPELL_CHECK            42
#define APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE    43
#define APPCOMMAND_MIC_ON_OFF_TOGGLE      44
#define APPCOMMAND_CORRECTION_LIST        45

#define FAPPCOMMAND_MOUSE 0x8000
#define FAPPCOMMAND_KEY   0
#define FAPPCOMMAND_OEM   0x1000
#define FAPPCOMMAND_MASK  0xF000
#define GET_APPCOMMAND_LPARAM(lParam) lParam& ~FAPPCOMMAND_MASK
#define GET_DEVICE_LPARAM(lParam)     lParam & FAPPCOMMAND_MASK
#define GET_MOUSEORKEY_LPARAM         GET_DEVICE_LPARAM
#define GET_FLAGS_LPARAM(lParam)      LOWORD(lParam)
#define GET_KEYSTATE_LPARAM(lParam)   GET_FLAGS_LPARAM(lParam)

/*
 * Message Structure used in Journaling
 */
struct EVENTMSG {
  UINT    message;
  UINT    paramL;
  UINT    paramH;
  DWORD    time;
  dword     hwnd;
};

/*
 * Message structure used by WH_CALLWNDPROC
 */
struct CWPSTRUCT {
  LPARAM  lParam;
  WPARAM  wParam;
  UINT    message;
  dword    hwnd;
};

/*
 * Message structure used by WH_CALLWNDPROCRET
 */
struct CWPRETSTRUCT {
  LRESULT lResult;
  LPARAM  lParam;
  WPARAM  wParam;
  UINT    message;
  dword    hwnd;
};

/*
 * Low level hook flags
 */
#define LLKHF_EXTENDED       KF_EXTENDED >> 8
#define LLKHF_INJECTED       0x00000010
#define LLKHF_ALTDOWN        KF_ALTDOWN >> 8
#define LLKHF_UP             KF_UP >> 8
#define LLMHF_INJECTED       0x00000001

/*
 * Structure used by WH_KEYBOARD_LL
 */
struct KBDLLHOOKSTRUCT {
  DWORD   vkCode;
  DWORD   scanCode;
  DWORD   flags;
  DWORD   time;
  ULONG_PTR dwExtraInfo;
};

/*
 * Structure used by WH_MOUSE_LL
 */
struct MSLLHOOKSTRUCT {
  POINT   pt;
  DWORD   mouseData;
  DWORD   flags;
  DWORD   time;
  ULONG_PTR dwExtraInfo;
};

/*
 * Structure used by WH_DEBUG
 */
struct DEBUGHOOKINFO
{
  DWORD   idThread;
  DWORD   idThreadInstaller;
  LPARAM  lParam;
  WPARAM  wParam;
  int     code;
};

/*
 * Structure used by WH_MOUSE
 */
struct MOUSEHOOKSTRUCT {
  POINT   pt;
  dword    hwnd;
  UINT    wHitTestCode;
  ULONG_PTR dwExtraInfo;
};

struct MOUSEHOOKSTRUCTEX
{
  MOUSEHOOKSTRUCT mouseHook;
  DWORD   mouseData;
};

/*
 * Structure used by WH_HARDWARE
 */
struct HARDWAREHOOKSTRUCT {
  dword    hwnd;
  UINT    message;
  WPARAM  wParam;
  LPARAM  lParam;
};
#endif /* !NOWH */

/*
 * Keyboard Layout API
 */
#define HKL_PREV            0
#define HKL_NEXT            1

#define KLF_ACTIVATE        0x00000001
#define KLF_SUBSTITUTE_OK   0x00000002
#define KLF_REORDER         0x00000008
#define KLF_REPLACELANG     0x00000010
#define KLF_NOTELLSHELL     0x00000080
#define KLF_SETFORPROCESS   0x00000100
#define KLF_SHIFTLOCK       0x00010000
#define KLF_RESET           0x40000000

/*
 * Bits in wParam of WM_INPUTLANGCHANGEREQUEST message
 */
#define INPUTLANGCHANGE_SYSCHARSET 0x0001
#define INPUTLANGCHANGE_FORWARD    0x0002
#define INPUTLANGCHANGE_BACKWARD   0x0004

/*
 * Size of KeyboardLayoutName (number of characters), including nul terminator
 */
#define KL_NAMELENGTH       9

struct MOUSEMOVEPOINT {
  int   x;
  int   y;
  DWORD time;
  ULONG_PTR dwExtraInfo;
};

struct USEROBJECTFLAGS {
  BOOL fInherit;
  BOOL fReserved;
  DWORD dwFlags;
};

extern WINAPI "user32.dll"{
	HKL LoadKeyboardLayoutA(LPCSTR pwszKLID,UINT Flags);
	HKL LoadKeyboardLayoutW(LPCWSTR pwszKLID,UINT Flags);
#ifdef UNICODE
#define LoadKeyboardLayout  LoadKeyboardLayoutW
#else
#define LoadKeyboardLayout  LoadKeyboardLayoutA
#endif // !UNICODE
	dword ActivateKeyboardLayout(HKL hkl,UINT Flags);
	int ToUnicodeEx(UINT wVirtKey,UINT wScanCode,dword lpKeyState,LPWSTR pwszBuff,
		int cchBuff,UINT wFlags,HKL dwhkl);
	BOOL UnloadKeyboardLayout(HKL hkl);
	BOOL GetKeyboardLayoutNameA(LPSTR pwszKLID);
	BOOL GetKeyboardLayoutNameW(LPWSTR pwszKLID);
#ifdef UNICODE
#define GetKeyboardLayoutName  GetKeyboardLayoutNameW
#else
#define GetKeyboardLayoutName  GetKeyboardLayoutNameA
#endif // !UNICODE
	int GetKeyboardLayoutList(int nBuff,dword lpList);
	HKL GetKeyboardLayout(DWORD idThread);
/*
 * Values for resolution parameter of GetMouseMovePointsEx
 */
#define GMMP_USE_DISPLAY_POINTS          1
#define GMMP_USE_HIGH_RESOLUTION_POINTS  2
	int GetMouseMovePointsEx(UINT cbSize,dword lppt,dword lpptBuf,int nBufPoints,DWORD resolution);

#ifndef NODESKTOP
/*
 * Desktop-specific access flags
 */
#define DESKTOP_READOBJECTS         0x0001L
#define DESKTOP_CREATEWINDOW        0x0002L
#define DESKTOP_CREATEMENU          0x0004L
#define DESKTOP_HOOKCONTROL         0x0008L
#define DESKTOP_JOURNALRECORD       0x0010L
#define DESKTOP_JOURNALPLAYBACK     0x0020L
#define DESKTOP_ENUMERATE           0x0040L
#define DESKTOP_WRITEOBJECTS        0x0080L
#define DESKTOP_SWITCHDESKTOP       0x0100L
/*
 * Desktop-specific control flags
 */
#define DF_ALLOWOTHERACCOUNTHOOK    0x0001L

#ifdef _WINGDI_
#ifndef NOGDI
	HDESK CreateDesktopA(LPCSTR lpszDesktop,LPCSTR lpszDevice,dword pDevmode,
		DWORD dwFlags,ACCESS_MASK dwDesiredAccess,dword lpsa);
	HDESK CreateDesktopW(LPCWSTR lpszDesktop,LPCWSTR lpszDevice,dword pDevmode,
		DWORD dwFlags,ACCESS_MASK dwDesiredAccess,dword lpsa);
#ifdef UNICODE
#define CreateDesktop  CreateDesktopW
#else
#define CreateDesktop  CreateDesktopA
#endif // !UNICODE
#endif /* NOGDI */
#endif /* _WINGDI_ */

	HDESK OpenDesktopA(LPCSTR lpszDesktop,DWORD dwFlags,BOOL fInherit,ACCESS_MASK dwDesiredAccess);
	HDESK OpenDesktopW(LPCWSTR lpszDesktop,DWORD dwFlags,BOOL fInherit,ACCESS_MASK dwDesiredAccess);
#ifdef UNICODE
#define OpenDesktop  OpenDesktopW
#else
#define OpenDesktop  OpenDesktopA
#endif // !UNICODE

	HDESK OpenInputDesktop(DWORD dwFlags,BOOL fInherit,ACCESS_MASK dwDesiredAccess);
	BOOL EnumDesktopsA(HWINSTA hwinsta,dword lpEnumFunc,LPARAM lParam);
	BOOL EnumDesktopsW(HWINSTA hwinsta,dword lpEnumFunc,LPARAM lParam);
#ifdef UNICODE
#define EnumDesktops  EnumDesktopsW
#else
#define EnumDesktops  EnumDesktopsA
#endif // !UNICODE

	BOOL EnumDesktopWindows(HDESK hDesktop,dword lpfn,LPARAM lParam);
	BOOL SwitchDesktop(HDESK hDesktop);
	BOOL SetThreadDesktop(HDESK hDesktop);
	BOOL CloseDesktop(HDESK hDesktop);
	HDESK GetThreadDesktop(DWORD dwThreadId);
#endif  /* !NODESKTOP */

#ifndef NOWINDOWSTATION
/*
 * Windowstation-specific access flags
 */
#define WINSTA_ENUMDESKTOPS         0x0001L
#define WINSTA_READATTRIBUTES       0x0002L
#define WINSTA_ACCESSCLIPBOARD      0x0004L
#define WINSTA_CREATEDESKTOP        0x0008L
#define WINSTA_WRITEATTRIBUTES      0x0010L
#define WINSTA_ACCESSGLOBALATOMS    0x0020L
#define WINSTA_EXITWINDOWS          0x0040L
#define WINSTA_ENUMERATE            0x0100L
#define WINSTA_READSCREEN           0x0200L

/*
 * Windowstation-specific attribute flags
 */
#define WSF_VISIBLE                 0x0001L

	HWINSTA CreateWindowStationA(LPCSTR lpwinsta,DWORD dwReserved,ACCESS_MASK dwDesiredAccess,dword lpsa);
	HWINSTA CreateWindowStationW(LPCWSTR lpwinsta,DWORD dwReserved,ACCESS_MASK dwDesiredAccess,dword lpsa);
#ifdef UNICODE
#define CreateWindowStation  CreateWindowStationW
#else
#define CreateWindowStation  CreateWindowStationA
#endif // !UNICODE

	HWINSTA OpenWindowStationA(LPCSTR lpszWinSta,BOOL fInherit,ACCESS_MASK dwDesiredAccess);
	HWINSTA OpenWindowStationW(LPCWSTR lpszWinSta,BOOL fInherit,ACCESS_MASK dwDesiredAccess);
#ifdef UNICODE
#define OpenWindowStation  OpenWindowStationW
#else
#define OpenWindowStation  OpenWindowStationA
#endif // !UNICODE

	BOOL EnumWindowStationsA(dword lpEnumFunc,LPARAM lParam);
	BOOL EnumWindowStationsW(dword lpEnumFunc,LPARAM lParam);
#ifdef UNICODE
#define EnumWindowStations  EnumWindowStationsW
#else
#define EnumWindowStations  EnumWindowStationsA
#endif // !UNICODE

	BOOL CloseWindowStation(HWINSTA hWinSta);
	BOOL SetProcessWindowStation(HWINSTA hWinSta);
	HWINSTA GetProcessWindowStation(VOID);
#endif  /* !NOWINDOWSTATION */

#ifndef NOSECURITY

	BOOL SetUserObjectSecurity(HANDLE hObj,dword pSIRequested,dword pSID);
	BOOL GetUserObjectSecurity(HANDLE hObj,dword pSIRequested,dword pSID,
		DWORD nLength,DWORD lpnLengthNeeded);

#define UOI_FLAGS       1
#define UOI_NAME        2
#define UOI_TYPE        3
#define UOI_USER_SID    4

	BOOL GetUserObjectInformationA(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength,DWORD lpnLengthNeeded);
	BOOL GetUserObjectInformationW(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength,DWORD lpnLengthNeeded);
#ifdef UNICODE
#define GetUserObjectInformation  GetUserObjectInformationW
#else
#define GetUserObjectInformation  GetUserObjectInformationA
#endif // !UNICODE

	BOOL SetUserObjectInformationA(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength);
	BOOL SetUserObjectInformationW(HANDLE hObj,int nIndex,PVOID pvInfo,DWORD nLength);
#ifdef UNICODE
#define SetUserObjectInformation  SetUserObjectInformationW
#else
#define SetUserObjectInformation  SetUserObjectInformationA
#endif // !UNICODE

#endif  /* !NOSECURITY */
}
struct WNDCLASSEX{
  UINT        cbSize;
  /* Win 3.x */
  UINT        style;
  dword     lpfnWndProc;
  int         cbClsExtra;
  int         cbWndExtra;
  HINSTANCE   hInstance;
  HICON       hIcon;
  HCURSOR     hCursor;
  HBRUSH      hbrBackground;
  LPCSTR      lpszMenuName;
  LPCSTR      lpszClassName;
  /* Win 4.0 */
  HICON       hIconSm;
};
#define WNDCLASSEXW WNDCLASSEX
#define WNDCLASSEXA WNDCLASSEX

struct WNDCLASS{
  UINT        style;
  dword     lpfnWndProc;
  int         cbClsExtra;
  int         cbWndExtra;
  HINSTANCE   hInstance;
  HICON       hIcon;
  HCURSOR     hCursor;
  HBRUSH      hbrBackground;
  LPCSTR      lpszMenuName;
  LPCSTR      lpszClassName;
};
#define WNDCLASSW WNDCLASS
#define WNDCLASSA WNDCLASS

#ifndef NOMSG

/*
 * Message structure
 */
struct MSG {
  dword        hwnd;
  UINT        message;
  WPARAM      wParam;
  LPARAM      lParam;
  DWORD       time;
  POINT       pt;
#ifdef _MAC
  DWORD       lPrivate;
#endif
};

#define POINTSTOPOINT(pt,pts)   \
        { pt.x = LOWORD(pts);   \
          pt.y = HIWORD(pts); }

#define POINTTOPOINTS(pt)      MAKELONG(pt.x,pt.y)
#define MAKEWPARAM(l,h)      MAKELONG(l,h)
#define MAKELPARAM(l,h)      MAKELONG(l,h)
#define MAKELRESULT(l,h)     MAKELONG(l,h)

#endif /* !NOMSG */

#ifndef NOWINOFFSETS

/*
 * Window field offsets for GetWindowLong()
 */
#define GWL_WNDPROC         -4
#define GWL_HINSTANCE       -6
#define GWL_HWNDPARENT      -8
#define GWL_STYLE           -16
#define GWL_EXSTYLE         -20
#define GWL_USERDATA        -21
#define GWL_ID              -12

#define GWLP_WNDPROC        -4
#define GWLP_HINSTANCE      -6
#define GWLP_HWNDPARENT     -8
#define GWLP_USERDATA       -21
#define GWLP_ID             -12

/*
 * Class field offsets for GetClassLong()
 */
#define GCL_MENUNAME        -8
#define GCL_HBRBACKGROUND   -10
#define GCL_HCURSOR         -12
#define GCL_HICON           -14
#define GCL_HMODULE         -16
#define GCL_CBWNDEXTRA      -18
#define GCL_CBCLSEXTRA      -20
#define GCL_WNDPROC         -24
#define GCL_STYLE           -26
#define GCW_ATOM            -32

#define GCL_HICONSM         -34

#define GCLP_MENUNAME       -8
#define GCLP_HBRBACKGROUND  -10
#define GCLP_HCURSOR        -12
#define GCLP_HICON          -14
#define GCLP_HMODULE        -16
#define GCLP_WNDPROC        -24
#define GCLP_HICONSM        -34

#endif /* !NOWINOFFSETS */

#ifndef NOWINMESSAGES

/*
 * Window Messages
 */
#define WM_NULL                         0x0000
#define WM_CREATE                       0x0001
#define WM_DESTROY                      0x0002
#define WM_MOVE                         0x0003
#define WM_SIZE                         0x0005
#define WM_ACTIVATE                     0x0006
/*
 * WM_ACTIVATE state values
 */
#define     WA_INACTIVE     0
#define     WA_ACTIVE       1
#define     WA_CLICKACTIVE  2
#define WM_SETFOCUS                     0x0007
#define WM_KILLFOCUS                    0x0008
#define WM_ENABLE                       0x000A
#define WM_SETREDRAW                    0x000B
#define WM_SETTEXT                      0x000C
#define WM_GETTEXT                      0x000D
#define WM_GETTEXTLENGTH                0x000E
#define WM_PAINT                        0x000F
#define WM_CLOSE                        0x0010
#ifndef _WIN32_WCE
#define WM_QUERYENDSESSION              0x0011
#define WM_QUERYOPEN                    0x0013
#define WM_ENDSESSION                   0x0016
#endif
#define WM_QUIT                         0x0012
#define WM_ERASEBKGND                   0x0014
#define WM_SYSCOLORCHANGE               0x0015
#define WM_SHOWWINDOW                   0x0018
#define WM_WININICHANGE                 0x001A
#define WM_SETTINGCHANGE                WM_WININICHANGE
#define WM_DEVMODECHANGE                0x001B
#define WM_ACTIVATEAPP                  0x001C
#define WM_FONTCHANGE                   0x001D
#define WM_TIMECHANGE                   0x001E
#define WM_CANCELMODE                   0x001F
#define WM_SETCURSOR                    0x0020
#define WM_MOUSEACTIVATE                0x0021
#define WM_CHILDACTIVATE                0x0022
#define WM_QUEUESYNC                    0x0023
#define WM_GETMINMAXINFO                0x0024
/*
 * Struct pointed to by WM_GETMINMAXINFO lParam
 */
struct MINMAXINFO {
  POINT ptReserved;
  POINT ptMaxSize;
  POINT ptMaxPosition;
  POINT ptMinTrackSize;
  POINT ptMaxTrackSize;
};

#define WM_PAINTICON                    0x0026
#define WM_ICONERASEBKGND               0x0027
#define WM_NEXTDLGCTL                   0x0028
#define WM_SPOOLERSTATUS                0x002A
#define WM_DRAWITEM                     0x002B
#define WM_MEASUREITEM                  0x002C
#define WM_DELETEITEM                   0x002D
#define WM_VKEYTOITEM                   0x002E
#define WM_CHARTOITEM                   0x002F
#define WM_SETFONT                      0x0030
#define WM_GETFONT                      0x0031
#define WM_SETHOTKEY                    0x0032
#define WM_GETHOTKEY                    0x0033
#define WM_QUERYDRAGICON                0x0037
#define WM_COMPAREITEM                  0x0039
#ifndef _WIN32_WCE
#define WM_GETOBJECT                    0x003D
#endif
#define WM_COMPACTING                   0x0041
#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
#define WM_WINDOWPOSCHANGING            0x0046
#define WM_WINDOWPOSCHANGED             0x0047
#define WM_POWER                        0x0048
/*
 * wParam for WM_POWER window message and DRV_POWER driver notification
 */
#define PWR_OK              1
#define PWR_FAIL            -1
#define PWR_SUSPENDREQUEST  1
#define PWR_SUSPENDRESUME   2
#define PWR_CRITICALRESUME  3
#define WM_COPYDATA                     0x004A
#define WM_CANCELJOURNAL                0x004B

/*
 * lParam of WM_COPYDATA message points to...
 */
struct COPYDATASTRUCT {
  ULONG_PTR dwData;
  DWORD cbData;
  PVOID lpData;
};

struct MDINEXTMENU
{
  HMENU   hmenuIn;
  HMENU   hmenuNext;
  dword    hwndNext;
};

#define WM_NOTIFY                       0x004E
#define WM_INPUTLANGCHANGEREQUEST       0x0050
#define WM_INPUTLANGCHANGE              0x0051
#define WM_TCARD                        0x0052
#define WM_HELP                         0x0053
#define WM_USERCHANGED                  0x0054
#define WM_NOTIFYFORMAT                 0x0055
#define NFR_ANSI                             1
#define NFR_UNICODE                          2
#define NF_QUERY                             3
#define NF_REQUERY                           4
#define WM_CONTEXTMENU                  0x007B
#define WM_STYLECHANGING                0x007C
#define WM_STYLECHANGED                 0x007D
#define WM_DISPLAYCHANGE                0x007E
#define WM_GETICON                      0x007F
#define WM_SETICON                      0x0080
#define WM_NCCREATE                     0x0081
#define WM_NCDESTROY                    0x0082
#define WM_NCCALCSIZE                   0x0083
#define WM_NCHITTEST                    0x0084
#define WM_NCPAINT                      0x0085
#define WM_NCACTIVATE                   0x0086
#define WM_GETDLGCODE                   0x0087
#ifndef _WIN32_WCE
#define WM_SYNCPAINT                    0x0088
#endif
#define WM_NCMOUSEMOVE                  0x00A0
#define WM_NCLBUTTONDOWN                0x00A1
#define WM_NCLBUTTONUP                  0x00A2
#define WM_NCLBUTTONDBLCLK              0x00A3
#define WM_NCRBUTTONDOWN                0x00A4
#define WM_NCRBUTTONUP                  0x00A5
#define WM_NCRBUTTONDBLCLK              0x00A6
#define WM_NCMBUTTONDOWN                0x00A7
#define WM_NCMBUTTONUP                  0x00A8
#define WM_NCMBUTTONDBLCLK              0x00A9
#define WM_NCXBUTTONDOWN                0x00AB
#define WM_NCXBUTTONUP                  0x00AC
#define WM_NCXBUTTONDBLCLK              0x00AD
#define WM_INPUT                        0x00FF
#define WM_KEYFIRST                     0x0100
#define WM_KEYDOWN                      0x0100
#define WM_KEYUP                        0x0101
#define WM_CHAR                         0x0102
#define WM_DEADCHAR                     0x0103
#define WM_SYSKEYDOWN                   0x0104
#define WM_SYSKEYUP                     0x0105
#define WM_SYSCHAR                      0x0106
#define WM_SYSDEADCHAR                  0x0107
#if(_WIN32_WINNT >= 0x0501)
#define WM_UNICHAR                      0x0109
#define WM_KEYLAST                      0x0109
#define UNICODE_NOCHAR                  0xFFFF
#else
#define WM_KEYLAST                      0x0108
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_IME_STARTCOMPOSITION         0x010D
#define WM_IME_ENDCOMPOSITION           0x010E
#define WM_IME_COMPOSITION              0x010F
#define WM_IME_KEYLAST                  0x010F

#define WM_INITDIALOG                   0x0110
#define WM_COMMAND                      0x0111
#define WM_SYSCOMMAND                   0x0112
#define WM_TIMER                        0x0113
#define WM_HSCROLL                      0x0114
#define WM_VSCROLL                      0x0115
#define WM_INITMENU                     0x0116
#define WM_INITMENUPOPUP                0x0117
#define WM_MENUSELECT                   0x011F
#define WM_MENUCHAR                     0x0120
#define WM_ENTERIDLE                    0x0121
#ifndef _WIN32_WCE
#define WM_MENURBUTTONUP                0x0122
#define WM_MENUDRAG                     0x0123
#define WM_MENUGETOBJECT                0x0124
#define WM_UNINITMENUPOPUP              0x0125
#define WM_MENUCOMMAND                  0x0126

#ifndef _WIN32_WCE
#define WM_CHANGEUISTATE                0x0127
#define WM_UPDATEUISTATE                0x0128
#define WM_QUERYUISTATE                 0x0129

/*
 * LOWORD(wParam) values in WM_*UISTATE*
 */
#define UIS_SET                         1
#define UIS_CLEAR                       2
#define UIS_INITIALIZE                  3

/*
 * HIWORD(wParam) values in WM_*UISTATE*
 */
#define UISF_HIDEFOCUS                  0x1
#define UISF_HIDEACCEL                  0x2
#define UISF_ACTIVE                     0x4
#endif

#endif

#define WM_CTLCOLORMSGBOX               0x0132
#define WM_CTLCOLOREDIT                 0x0133
#define WM_CTLCOLORLISTBOX              0x0134
#define WM_CTLCOLORBTN                  0x0135
#define WM_CTLCOLORDLG                  0x0136
#define WM_CTLCOLORSCROLLBAR            0x0137
#define WM_CTLCOLORSTATIC               0x0138
#define WM_MOUSEFIRST                   0x0200
#define WM_MOUSEMOVE                    0x0200
#define WM_LBUTTONDOWN                  0x0201
#define WM_LBUTTONUP                    0x0202
#define WM_LBUTTONDBLCLK                0x0203
#define WM_RBUTTONDOWN                  0x0204
#define WM_RBUTTONUP                    0x0205
#define WM_RBUTTONDBLCLK                0x0206
#define WM_MBUTTONDOWN                  0x0207
#define WM_MBUTTONUP                    0x0208
#define WM_MBUTTONDBLCLK                0x0209
#define WM_MOUSEWHEEL                   0x020A
#if (_WIN32_WINNT >= 0x0500)
#define WM_XBUTTONDOWN                  0x020B
#define WM_XBUTTONUP                    0x020C
#define WM_XBUTTONDBLCLK                0x020D
#endif
#if (_WIN32_WINNT >= 0x0500)
#define WM_MOUSELAST                    0x020D
#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
#define WM_MOUSELAST                    0x020A
#else
#define WM_MOUSELAST                    0x0209
#endif /* (_WIN32_WINNT >= 0x0500) */

/* Value for rolling one detent */
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  HIWORD(wParam)

/* Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
#define WHEEL_PAGESCROLL                UINT_MAX
#define GET_KEYSTATE_WPARAM(wParam)     LOWORD(wParam)
#define GET_NCHITTEST_WPARAM(wParam)    LOWORD(wParam)
#define GET_XBUTTON_WPARAM(wParam)      HIWORD(wParam)

/* XButton values are WORD flags */
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
/* Were there to be an XBUTTON3, its value would be 0x0004 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216

#define WM_POWERBROADCAST               0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001
#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003
#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005
#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008
#define PBTF_APMRESUMEFROMFAILURE       0x00000001
#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A
#define PBT_APMOEMEVENT                 0x000B
#define PBT_APMRESUMEAUTOMATIC          0x0012
#endif

#define WM_DEVICECHANGE                 0x0219
#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDICASCADE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229
#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286
#define WM_IME_REQUEST                  0x0288
#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291

#define WM_MOUSEHOVER                   0x02A1
#define WM_MOUSELEAVE                   0x02A3
#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2
#define WM_WTSSESSION_CHANGE            0x02B1
#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define WM_PAINTCLIPBOARD               0x0309
#define WM_VSCROLLCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define WM_HSCROLLCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318
#define WM_APPCOMMAND                   0x0319
#define WM_THEMECHANGED                 0x031A
#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F
#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F
#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F
#define WM_APP                          0x8000

/*
 * NOTE: All Message Numbers below 0x0400 are RESERVED.
 *
 * Private Window Messages Start Here:
 */
#define WM_USER                         0x0400

/*  wParam for WM_SIZING message  */
#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8

#ifndef NONCMESSAGES

/*
 * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
 */
#define HTERROR             -2
#define HTTRANSPARENT       -1
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTCAPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21

/*
 * SendMessageTimeout values
 */
#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif /* !NONCMESSAGES */

/*
 * WM_MOUSEACTIVATE Return Codes
 */
#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

/*
 * WM_SETICON / WM_GETICON Type Codes
 */
#define ICON_SMALL          0
#define ICON_BIG            1
#define ICON_SMALL2         2

extern WINAPI "user32.dll"{
	UINT RegisterWindowMessageA(LPCSTR lpString);
	UINT RegisterWindowMessageW(LPCWSTR lpString);
#ifdef UNICODE
#define RegisterWindowMessage  RegisterWindowMessageW
#else
#define RegisterWindowMessage  RegisterWindowMessageA
#endif // !UNICODE
	BOOL TrackMouseEvent(dword lpEventTrack);
}
/*
 * WM_SIZE message wParam values
 */
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4

/*
 * Obsolete constant names
 */
#define SIZENORMAL          SIZE_RESTORED
#define SIZEICONIC          SIZE_MINIMIZED
#define SIZEFULLSCREEN      SIZE_MAXIMIZED
#define SIZEZOOMSHOW        SIZE_MAXSHOW
#define SIZEZOOMHIDE        SIZE_MAXHIDE

/*
 * WM_WINDOWPOSCHANGING/CHANGED struct pointed to by lParam
 */
struct WINDOWPOS {
  dword    hwnd;
  dword    hwndInsertAfter;
  int     x;
  int     y;
  int     cx;
  int     cy;
  UINT    flags;
};

/*
 * WM_NCCALCSIZE parameter structure
 */
struct NCCALCSIZE_PARAMS {
  RECT       rgrc[3];
  dword lppos;
};

/*
 * WM_NCCALCSIZE "window valid rect" return values
 */
#define WVR_ALIGNTOP        0x0010
#define WVR_ALIGNLEFT       0x0020
#define WVR_ALIGNBOTTOM     0x0040
#define WVR_ALIGNRIGHT      0x0080
#define WVR_HREDRAW         0x0100
#define WVR_VREDRAW         0x0200
#define WVR_REDRAW         WVR_HREDRAW|WVR_VREDRAW
#define WVR_VALIDRECTS      0x0400

#ifndef NOKEYSTATES

/*
 * Key State Masks for Mouse Messages
 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040

#endif /* !NOKEYSTATES */

#ifndef NOTRACKMOUSEEVENT

#define TME_HOVER       0x00000001
#define TME_LEAVE       0x00000002
#define TME_NONCLIENT   0x00000010
#define TME_QUERY       0x40000000
#define TME_CANCEL      0x80000000

#define HOVER_DEFAULT   0xFFFFFFFF

struct TRACKMOUSEEVENT {
  DWORD cbSize;
  DWORD dwFlags;
  dword  hwndTrack;
  DWORD dwHoverTime;
};

#endif /* !NOTRACKMOUSEEVENT */

#endif /* !NOWINMESSAGES */

#ifndef NOWINSTYLES

/*
 * Window Styles
 */
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L
#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L
#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

/*
 * Common Window Styles
 */
#define WS_OVERLAPPEDWINDOW WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME| \
                             WS_MINIMIZEBOX|WS_MAXIMIZEBOX
#define WS_POPUPWINDOW      WS_POPUP|WS_BORDER|WS_SYSMENU
#define WS_CHILDWINDOW      WS_CHILD

/*
 * Extended Window Styles
 */
#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L
#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L
#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L
#define WS_EX_OVERLAPPEDWINDOW  WS_EX_WINDOWEDGE|WS_EX_CLIENTEDGE
#define WS_EX_PALETTEWINDOW     WS_EX_WINDOWEDGE|WS_EX_TOOLWINDOW|WS_EX_TOPMOST

#define WS_EX_LAYERED           0x00080000
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
#define WS_EX_COMPOSITED        0x02000000L
#define WS_EX_NOACTIVATE        0x08000000L

/*
 * Class styles
 */
#define CS_VREDRAW          0x0001
#define CS_HREDRAW          0x0002
#define CS_DBLCLKS          0x0008
#define CS_OWNDC            0x0020
#define CS_CLASSDC          0x0040
#define CS_PARENTDC         0x0080
#define CS_NOCLOSE          0x0200
#define CS_SAVEBITS         0x0800
#define CS_BYTEALIGNCLIENT  0x1000
#define CS_BYTEALIGNWINDOW  0x2000
#define CS_GLOBALCLASS      0x4000

#define CS_IME              0x00010000
#define CS_DROPSHADOW       0x00020000

#endif /* !NOWINSTYLES */
/* WM_PRINT flags */
#define PRF_CHECKVISIBLE    0x00000001L
#define PRF_NONCLIENT       0x00000002L
#define PRF_CLIENT          0x00000004L
#define PRF_ERASEBKGND      0x00000008L
#define PRF_CHILDREN        0x00000010L
#define PRF_OWNED           0x00000020L

/* 3D border styles */
#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008
#define BDR_OUTER       BDR_RAISEDOUTER|BDR_SUNKENOUTER
#define BDR_INNER       BDR_RAISEDINNER|BDR_SUNKENINNER
#define BDR_RAISED      BDR_RAISEDOUTER|BDR_RAISEDINNER
#define BDR_SUNKEN      BDR_SUNKENOUTER|BDR_SUNKENINNER
#define EDGE_RAISED     BDR_RAISEDOUTER|BDR_RAISEDINNER
#define EDGE_SUNKEN     BDR_SUNKENOUTER|BDR_SUNKENINNER
#define EDGE_ETCHED     BDR_SUNKENOUTER|BDR_RAISEDINNER
#define EDGE_BUMP       BDR_RAISEDOUTER|BDR_SUNKENINNER

/* Border flags */
#define BF_LEFT         0x0001
#define BF_TOP          0x0002
#define BF_RIGHT        0x0004
#define BF_BOTTOM       0x0008
#define BF_TOPLEFT      BF_TOP|BF_LEFT
#define BF_TOPRIGHT     BF_TOP|BF_RIGHT
#define BF_BOTTOMLEFT   BF_BOTTOM| BF_LEFT
#define BF_BOTTOMRIGHT  BF_BOTTOM| BF_RIGHT
#define BF_RECT         BF_LEFT|BF_TOP|BF_RIGHT|BF_BOTTOM
#define BF_DIAGONAL     0x0010

// For diagonal lines, the BF_RECT flags specify the end point of the
// vector bounded by the rectangle parameter.
#define BF_DIAGONAL_ENDTOPRIGHT     BF_DIAGONAL|BF_TOP|BF_RIGHT
#define BF_DIAGONAL_ENDTOPLEFT      BF_DIAGONAL|BF_TOP|BF_LEFT
#define BF_DIAGONAL_ENDBOTTOMLEFT   BF_DIAGONAL|BF_BOTTOM|BF_LEFT
#define BF_DIAGONAL_ENDBOTTOMRIGHT  BF_DIAGONAL|BF_BOTTOM|BF_RIGHT

#define BF_MIDDLE       0x0800  /* Fill in the middle */
#define BF_SOFT         0x1000  /* For softer buttons */
#define BF_ADJUST       0x2000  /* Calculate the space left over */
#define BF_FLAT         0x4000  /* For flat rather than 3D borders */
#define BF_MONO         0x8000  /* For monochrome borders */

extern WINAPI "user32.dll"{
	BOOL DrawEdge(HDC hdc,dword qrc,UINT edge,UINT grfFlags);

/* flags for DrawFrameControl */
#define DFC_CAPTION             1
#define DFC_MENU                2
#define DFC_SCROLL              3
#define DFC_BUTTON              4
#define DFC_POPUPMENU           5

#define DFCS_CAPTIONCLOSE       0x0000
#define DFCS_CAPTIONMIN         0x0001
#define DFCS_CAPTIONMAX         0x0002
#define DFCS_CAPTIONRESTORE     0x0003
#define DFCS_CAPTIONHELP        0x0004
#define DFCS_MENUARROW          0x0000
#define DFCS_MENUCHECK          0x0001
#define DFCS_MENUBULLET         0x0002
#define DFCS_MENUARROWRIGHT     0x0004
#define DFCS_SCROLLUP           0x0000
#define DFCS_SCROLLDOWN         0x0001
#define DFCS_SCROLLLEFT         0x0002
#define DFCS_SCROLLRIGHT        0x0003
#define DFCS_SCROLLCOMBOBOX     0x0005
#define DFCS_SCROLLSIZEGRIP     0x0008
#define DFCS_SCROLLSIZEGRIPRIGHT 0x0010
#define DFCS_BUTTONCHECK        0x0000
#define DFCS_BUTTONRADIOIMAGE   0x0001
#define DFCS_BUTTONRADIOMASK    0x0002
#define DFCS_BUTTONRADIO        0x0004
#define DFCS_BUTTON3STATE       0x0008
#define DFCS_BUTTONPUSH         0x0010
#define DFCS_INACTIVE           0x0100
#define DFCS_PUSHED             0x0200
#define DFCS_CHECKED            0x0400
#define DFCS_TRANSPARENT        0x0800
#define DFCS_HOT                0x1000
#define DFCS_ADJUSTRECT         0x2000
#define DFCS_FLAT               0x4000
#define DFCS_MONO               0x8000

	BOOL DrawFrameControl(HDC,dword,UINT,UINT);

/* flags for DrawCaption */
#define DC_ACTIVE           0x0001
#define DC_SMALLCAP         0x0002
#define DC_ICON             0x0004
#define DC_TEXT             0x0008
#define DC_INBUTTON         0x0010
#define DC_GRADIENT         0x0020
#define DC_BUTTONS          0x1000

	BOOL DrawCaption(dword,HDC,dword,UINT);

#define IDANI_OPEN          1
#define IDANI_CAPTION       3

	BOOL DrawAnimatedRects(dword hwnd,int idAni,dword lprcFrom,dword lprcTo);
}
#ifndef NOCLIPBOARD

/*
 * Predefined Clipboard Formats
 */
#define CF_TEXT             1
#define CF_BITMAP           2
#define CF_METAFILEPICT     3
#define CF_SYLK             4
#define CF_DIF              5
#define CF_TIFF             6
#define CF_OEMTEXT          7
#define CF_DIB              8
#define CF_PALETTE          9
#define CF_PENDATA          10
#define CF_RIFF             11
#define CF_WAVE             12
#define CF_UNICODETEXT      13
#define CF_ENHMETAFILE      14
#define CF_HDROP            15
#define CF_LOCALE           16
#define CF_DIBV5            17

#if(WINVER >= 0x0500)
#define CF_MAX              18
#elif(WINVER >= 0x0400)
#define CF_MAX              17
#else
#define CF_MAX              15
#endif

#define CF_OWNERDISPLAY     0x0080
#define CF_DSPTEXT          0x0081
#define CF_DSPBITMAP        0x0082
#define CF_DSPMETAFILEPICT  0x0083
#define CF_DSPENHMETAFILE   0x008E

/*
 * "Private" formats don't get GlobalFree()'d
 */
#define CF_PRIVATEFIRST     0x0200
#define CF_PRIVATELAST      0x02FF

/*
 * "GDIOBJ" formats do get DeleteObject()'d
 */
#define CF_GDIOBJFIRST      0x0300
#define CF_GDIOBJLAST       0x03FF

#endif /* !NOCLIPBOARD */

/*
 * Defines for the fVirt field of the Accelerator table structure.
 */
#define FVIRTKEY  TRUE          /* Assumed to be == TRUE */
#define FNOINVERT 0x02
#define FSHIFT    0x04
#define FCONTROL  0x08
#define FALT      0x10

struct ACCEL {
#ifndef _MAC
  BYTE   fVirt;               /* Also called the flags field */
  WORD   key;
  WORD   cmd;
#else
  WORD   fVirt;               /* Also called the flags field */
  WORD   key;
  DWORD  cmd;
#endif
};

struct PAINTSTRUCT {
  HDC         hdc;
  BOOL        fErase;
  RECT        rcPaint;
  BOOL        fRestore;
  BOOL        fIncUpdate;
  BYTE        rgbReserved[32];
};

struct CREATESTRUCT{
  LPVOID      lpCreateParams;
  HINSTANCE   hInstance;
  HMENU       hMenu;
  dword        hwndParent;
  int         cy;
  int         cx;
  int         y;
  int         x;
  LONG        style;
  LPCSTR      lpszName;
  LPCSTR      lpszClass;
  DWORD       dwExStyle;
};
#define CREATESTRUCTW CREATESTRUCT
#define CREATESTRUCTA CREATESTRUCT

struct WINDOWPLACEMENT {
  UINT  length;
  UINT  flags;
  UINT  showCmd;
  POINT ptMinPosition;
  POINT ptMaxPosition;
  RECT  rcNormalPosition;
#ifdef _MAC
  RECT  rcDevice;
#endif
};

#define WPF_SETMINPOSITION          0x0001
#define WPF_RESTORETOMAXIMIZED      0x0002
#define WPF_ASYNCWINDOWPLACEMENT    0x0004

struct NMHDR
{
  dword      hwndFrom;
  dword  idFrom;
  UINT      code;         // NM_ code
};

struct STYLESTRUCT
{
  DWORD   styleOld;
  DWORD   styleNew;
};

/*
 * Owner draw control types
 */
#define ODT_MENU        1
#define ODT_LISTBOX     2
#define ODT_COMBOBOX    3
#define ODT_BUTTON      4
#define ODT_STATIC      5

/*
 * Owner draw actions
 */
#define ODA_DRAWENTIRE  0x0001
#define ODA_SELECT      0x0002
#define ODA_FOCUS       0x0004

/*
 * Owner draw state
 */
#define ODS_SELECTED    0x0001
#define ODS_GRAYED      0x0002
#define ODS_DISABLED    0x0004
#define ODS_CHECKED     0x0008
#define ODS_FOCUS       0x0010
#define ODS_DEFAULT         0x0020
#define ODS_COMBOBOXEDIT    0x1000
#define ODS_HOTLIGHT        0x0040
#define ODS_INACTIVE        0x0080
#define ODS_NOACCEL         0x0100
#define ODS_NOFOCUSRECT     0x0200

/*
 * MEASUREITEMSTRUCT for ownerdraw
 */
struct MEASUREITEMSTRUCT {
  UINT       CtlType;
  UINT       CtlID;
  UINT       itemID;
  UINT       itemWidth;
  UINT       itemHeight;
  ULONG_PTR  itemData;
};

/*
 * DRAWITEMSTRUCT for ownerdraw
 */
struct DRAWITEMSTRUCT {
  UINT        CtlType;
  UINT        CtlID;
  UINT        itemID;
  UINT        itemAction;
  UINT        itemState;
  dword        hwndItem;
  HDC         hDC;
  RECT        rcItem;
  ULONG_PTR   itemData;
};

/*
 * DELETEITEMSTRUCT for ownerdraw
 */
struct DELETEITEMSTRUCT {
  UINT       CtlType;
  UINT       CtlID;
  UINT       itemID;
  dword       hwndItem;
  ULONG_PTR  itemData;
};

/*
 * COMPAREITEMSTUCT for ownerdraw sorting
 */
struct COMPAREITEMSTRUCT {
  UINT        CtlType;
  UINT        CtlID;
  dword        hwndItem;
  UINT        itemID1;
  ULONG_PTR   itemData1;
  UINT        itemID2;
  ULONG_PTR   itemData2;
  DWORD       dwLocaleId;
};

struct BSMINFO{
  UINT  cbSize;
  HDESK hdesk;
  dword  hwnd;
  LUID  luid;
};

struct FLASHWINFO{
  UINT  cbSize;
  dword  hwnd;
  DWORD dwFlags;
  UINT  uCount;
  DWORD dwTimeout;
};

extern WINAPI "user32.dll"{
#ifndef NOMSG
/*
 * Message Function Templates
 */
	BOOL GetMessageA(dword lpMsg,dword hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
	BOOL GetMessageW(dword lpMsg,dword hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
#ifdef UNICODE
#define GetMessage  GetMessageW
#else
#define GetMessage  GetMessageA
#endif // !UNICODE

	BOOL TranslateMessage(dword lpMsg);
	LRESULT DispatchMessageA(dword lpMsg);
	LRESULT DispatchMessageW(dword lpMsg);
#ifdef UNICODE
#define DispatchMessage  DispatchMessageW
#else
#define DispatchMessage  DispatchMessageA
#endif // !UNICODE

	BOOL SetMessageQueue(int cMessagesMax);
	BOOL PeekMessageA(dword lpMsg,dword hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
	BOOL PeekMessageW(dword lpMsg,dword hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
#ifdef UNICODE
#define PeekMessage  PeekMessageW
#else
#define PeekMessage  PeekMessageA
#endif // !UNICODE

/*
 * PeekMessage() Options
 */
#define PM_NOREMOVE         0x0000
#define PM_REMOVE           0x0001
#define PM_NOYIELD          0x0002
#define PM_QS_INPUT         QS_INPUT << 16
#define PM_QS_POSTMESSAGE   QS_POSTMESSAGE | QS_HOTKEY | QS_TIMER << 16
#define PM_QS_PAINT         QS_PAINT << 16
#define PM_QS_SENDMESSAGE   QS_SENDMESSAGE << 16

#endif /* !NOMSG */

	BOOL RegisterHotKey(dword hWnd,int id,UINT fsModifiers,UINT vk);
	BOOL UnregisterHotKey(dword hWnd,int id);

#define MOD_ALT         0x0001
#define MOD_CONTROL     0x0002
#define MOD_SHIFT       0x0004
#define MOD_WIN         0x0008

#define IDHOT_SNAPWINDOW        -1    /* SHIFT-PRINTSCRN  */
#define IDHOT_SNAPDESKTOP       -2    /* PRINTSCRN        */

#ifdef WIN_INTERNAL
#ifndef LSTRING
#define NOLSTRING
#endif /* LSTRING */
#ifndef LFILEIO
#define NOLFILEIO
#endif /* LFILEIO */
#endif /* WIN_INTERNAL */

#define ENDSESSION_LOGOFF    0x80000000

#define EWX_LOGOFF          0
#define EWX_SHUTDOWN        0x00000001
#define EWX_REBOOT          0x00000002
#define EWX_FORCE           0x00000004
#define EWX_POWEROFF        0x00000008
#define EWX_FORCEIFHUNG     0x00000010

#define ExitWindows(dwReserved,Code) ExitWindowsEx(EWX_LOGOFF,0xFFFFFFFF)

	BOOL ExitWindowsEx(UINT uFlags,DWORD dwReserved);
	BOOL SwapMouseButton(BOOL fSwap);
	DWORD GetMessagePos(VOID);
	LONG GetMessageTime(VOID);
	LPARAM GetMessageExtraInfo(VOID);
	LPARAM SetMessageExtraInfo(LPARAM lParam);
	LRESULT SendMessageA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	LRESULT SendMessageW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define SendMessage  SendMessageW
#else
#define SendMessage  SendMessageA
#endif // !UNICODE

	LRESULT SendMessageTimeoutA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,
		UINT fuFlags,UINT uTimeout,dword lpdwResult);
	LRESULT SendMessageTimeoutW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,
		UINT fuFlags,UINT uTimeout,dword lpdwResult);
#ifdef UNICODE
#define SendMessageTimeout  SendMessageTimeoutW
#else
#define SendMessageTimeout  SendMessageTimeoutA
#endif // !UNICODE

	BOOL SendNotifyMessageA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	BOOL SendNotifyMessageW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define SendNotifyMessage  SendNotifyMessageW
#else
#define SendNotifyMessage  SendNotifyMessageA
#endif // !UNICODE

	BOOL SendMessageCallbackA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,
		dword lpResultCallBack,ULONG_PTR dwData);
	BOOL SendMessageCallbackW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam,
		dword lpResultCallBack,ULONG_PTR dwData);
#ifdef UNICODE
#define SendMessageCallback  SendMessageCallbackW
#else
#define SendMessageCallback  SendMessageCallbackA
#endif // !UNICODE

	long BroadcastSystemMessageExA(DWORD,LPDWORD,UINT,WPARAM,LPARAM,dword);
	long BroadcastSystemMessageExW(DWORD,LPDWORD,UINT,WPARAM,LPARAM,dword);
#ifdef UNICODE
#define BroadcastSystemMessageEx  BroadcastSystemMessageExW
#else
#define BroadcastSystemMessageEx  BroadcastSystemMessageExA
#endif // !UNICODE

#if defined(_WIN32_WINNT)
	long BroadcastSystemMessageA(DWORD,LPDWORD,UINT,WPARAM,LPARAM);
	long BroadcastSystemMessageW(DWORD,LPDWORD,UINT,WPARAM,LPARAM);
#ifdef UNICODE
#define BroadcastSystemMessage  BroadcastSystemMessageW
#else
#define BroadcastSystemMessage  BroadcastSystemMessageA
#endif // !UNICODE
#elif defined(_WIN32_WINDOWS)
// The Win95 version isn't A/W decorated
	long BroadcastSystemMessage(DWORD,LPDWORD,UINT,WPARAM,LPARAM);
#endif

//Broadcast Special Message Recipient list
#define BSM_ALLCOMPONENTS       0x00000000
#define BSM_VXDS                0x00000001
#define BSM_NETDRIVER           0x00000002
#define BSM_INSTALLABLEDRIVERS  0x00000004
#define BSM_APPLICATIONS        0x00000008
#define BSM_ALLDESKTOPS         0x00000010

//Broadcast Special Message Flags
#define BSF_QUERY               0x00000001
#define BSF_IGNORECURRENTTASK   0x00000002
#define BSF_FLUSHDISK           0x00000004
#define BSF_NOHANG              0x00000008
#define BSF_POSTMESSAGE         0x00000010
#define BSF_FORCEIFHUNG         0x00000020
#define BSF_NOTIMEOUTIFNOTHUNG  0x00000040
#define BSF_ALLOWSFW            0x00000080
#define BSF_SENDNOTIFYMESSAGE   0x00000100
#define BSF_RETURNHDESK         0x00000200
#define BSF_LUID                0x00000400

#define BROADCAST_QUERY_DENY         0x424D5144  // Return this value to deny a query.

// RegisterDeviceNotification
#define HDEVNOTIFY PVOID

#define DEVICE_NOTIFY_WINDOW_HANDLE          0x00000000
#define DEVICE_NOTIFY_SERVICE_HANDLE         0x00000001
#define DEVICE_NOTIFY_ALL_INTERFACE_CLASSES  0x00000004

	HDEVNOTIFY RegisterDeviceNotificationA(HANDLE hRecipient,LPVOID NotificationFilter,DWORD Flags);
	HDEVNOTIFY RegisterDeviceNotificationW(HANDLE hRecipient,LPVOID NotificationFilter,DWORD Flags);
#ifdef UNICODE
#define RegisterDeviceNotification  RegisterDeviceNotificationW
#else
#define RegisterDeviceNotification  RegisterDeviceNotificationA
#endif // !UNICODE

	BOOL UnregisterDeviceNotification(HDEVNOTIFY Handle);
	BOOL PostMessageA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	BOOL PostMessageW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define PostMessage  PostMessageW
#else
#define PostMessage  PostMessageA
#endif // !UNICODE

	BOOL PostThreadMessageA(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam);
	BOOL PostThreadMessageW(DWORD idThread,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define PostThreadMessage  PostThreadMessageW
#else
#define PostThreadMessage  PostThreadMessageA
#endif // !UNICODE

#define PostAppMessageA(idThread,wMsg,wParam,lParam)\
        PostThreadMessageA(idThread,wMsg,wParam,lParam)
#define PostAppMessageW(idThread,wMsg,wParam,lParam)\
        PostThreadMessageW(idThread,wMsg,wParam,lParam)
#ifdef UNICODE
#define PostAppMessage  PostAppMessageW
#else
#define PostAppMessage  PostAppMessageA
#endif // !UNICODE

/*
 * Special dword value for use with PostMessage() and SendMessage()
 */
#define HWND_BROADCAST  0xffff

#define HWND_MESSAGE     -3

	BOOL AttachThreadInput(DWORD idAttach,DWORD idAttachTo,BOOL fAttach);
	BOOL ReplyMessage(LRESULT lResult);
	BOOL WaitMessage(VOID);
	DWORD WaitForInputIdle(HANDLE hProcess,DWORD dwMilliseconds);
	LRESULT DefWindowProcA(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	LRESULT DefWindowProcW(dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define DefWindowProc  DefWindowProcW
#else
#define DefWindowProc  DefWindowProcA
#endif // !UNICODE

	VOID PostQuitMessage(int nExitCode);

#ifdef STRICT
	LRESULT CallWindowProcA(dword lpPrevWndFunc,dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	LRESULT CallWindowProcW(dword lpPrevWndFunc,dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define CallWindowProc  CallWindowProcW
#else
#define CallWindowProc  CallWindowProcA
#endif // !UNICODE

#else /* !STRICT */

	LRESULT CallWindowProcA(dword lpPrevWndFunc,dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	LRESULT CallWindowProcW(dword lpPrevWndFunc,dword hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define CallWindowProc  CallWindowProcW
#else
#define CallWindowProc  CallWindowProcA
#endif // !UNICODE

#endif /* !STRICT */

	BOOL InSendMessage(VOID);
	DWORD InSendMessageEx(LPVOID lpReserved);

/*
 * InSendMessageEx return value
 */
#define ISMEX_NOSEND      0x00000000
#define ISMEX_SEND        0x00000001
#define ISMEX_NOTIFY      0x00000002
#define ISMEX_CALLBACK    0x00000004
#define ISMEX_REPLIED     0x00000008

	UINT GetDoubleClickTime(VOID);
	BOOL SetDoubleClickTime(UINT);
	ATOM RegisterClassA(dword lpWndClass);
	ATOM RegisterClassW(dword lpWndClass);
#ifdef UNICODE
#define RegisterClass  RegisterClassW
#else
#define RegisterClass  RegisterClassA
#endif // !UNICODE

	BOOL UnregisterClassA(LPCSTR lpClassName,HINSTANCE hInstance);
	BOOL UnregisterClassW(LPCWSTR lpClassName,HINSTANCE hInstance);
#ifdef UNICODE
#define UnregisterClass  UnregisterClassW
#else
#define UnregisterClass  UnregisterClassA
#endif // !UNICODE

	BOOL GetClassInfoA(HINSTANCE hInstance,LPCSTR lpClassName,dword lpWndClass);
	BOOL GetClassInfoW(HINSTANCE hInstance,LPCWSTR lpClassName,dword lpWndClass);
#ifdef UNICODE
#define GetClassInfo  GetClassInfoW
#else
#define GetClassInfo  GetClassInfoA
#endif // !UNICODE

	ATOM RegisterClassExA(dword);
	ATOM RegisterClassExW(dword);
#ifdef UNICODE
#define RegisterClassEx  RegisterClassExW
#else
#define RegisterClassEx  RegisterClassExA
#endif // !UNICODE

	BOOL GetClassInfoExA(HINSTANCE,LPCSTR,dword);
	BOOL GetClassInfoExW(HINSTANCE,LPCWSTR,dword);
#ifdef UNICODE
#define GetClassInfoEx  GetClassInfoExW
#else
#define GetClassInfoEx  GetClassInfoExA
#endif // !UNICODE

#define CW_USEDEFAULT       0x80000000

/*
 * Special value for CreateWindow, et al.
 */
#define HWND_DESKTOP        0

	dword CreateWindowExA(DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,
		DWORD dwStyle,int X,int Y,int nWidth,int nHeight,dword hWndParent,HMENU hMenu,
		HINSTANCE hInstance,LPVOID lpParam);
	dword CreateWindowExW(DWORD dwExStyle,LPCWSTR lpClassName,LPCWSTR lpWindowName,
		DWORD dwStyle,int X,int Y,int nWidth,int nHeight,dword hWndParent,HMENU hMenu,
		HINSTANCE hInstance,LPVOID lpParam);
#ifdef UNICODE
#define CreateWindowEx  CreateWindowExW
#else
#define CreateWindowEx  CreateWindowExA
#endif // !UNICODE

#define CreateWindowA(lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)\
CreateWindowExA(0L,lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)
#define CreateWindowW(lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)\
CreateWindowExW(0L,lpClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,lpParam)
#ifdef UNICODE
#define CreateWindow  CreateWindowW
#else
#define CreateWindow  CreateWindowA
#endif // !UNICODE

	BOOL IsWindow(dword hWnd);
	BOOL IsMenu(HMENU hMenu);
	BOOL IsChild(dword hWndParent,dword hWnd);
	BOOL DestroyWindow(dword hWnd);
	BOOL ShowWindow(dword hWnd,int nCmdShow);
	BOOL AnimateWindow(dword hWnd,DWORD dwTime,DWORD dwFlags);

#if defined(_WINGDI_) && !defined (NOGDI)
	BOOL UpdateLayeredWindow(dword hWnd,HDC hdcDst,dword pptDst,dword psize,
		HDC hdcSrc,dword pptSrc,COLORREF crKey,dword pblend,DWORD dwFlags);
#endif

	BOOL GetLayeredWindowAttributes(dword hwnd,dword pcrKey,dword pbAlpha,DWORD pdwFlags);
#define PW_CLIENTONLY           0x00000001
	BOOL PrintWindow(dword hwnd,HDC hdcBlt,UINT nFlags);

	BOOL SetLayeredWindowAttributes(dword hwnd,COLORREF crKey,BYTE bAlpha,DWORD dwFlags);

#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#define ULW_COLORKEY            0x00000001
#define ULW_ALPHA               0x00000002
#define ULW_OPAQUE              0x00000004

	BOOL ShowWindowAsync(dword hWnd,int nCmdShow);
	BOOL FlashWindow(dword hWnd,BOOL bInvert);
	BOOL FlashWindowEx(dword pfwi);

#define FLASHW_STOP         0
#define FLASHW_CAPTION      0x00000001
#define FLASHW_TRAY         0x00000002
#define FLASHW_ALL          FLASHW_CAPTION|FLASHW_TRAY
#define FLASHW_TIMER        0x00000004
#define FLASHW_TIMERNOFG    0x0000000C

	BOOL ShowOwnedPopups(dword hWnd,BOOL fShow);
	BOOL OpenIcon(dword hWnd);
	BOOL CloseWindow(dword hWnd);
	BOOL MoveWindow(dword hWnd,int X,int Y,int nWidth,int nHeight,BOOL bRepaint);
	BOOL SetWindowPos(dword hWnd,dword hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags);
	BOOL GetWindowPlacement(dword hWnd,dword lpwndpl);
	BOOL SetWindowPlacement(dword hWnd,dword lpwndpl);

#ifndef NODEFERWINDOWPOS
	HDWP BeginDeferWindowPos(int nNumWindows);
	HDWP DeferWindowPos(HDWP hWinPosInfo,dword hWnd,dword hWndInsertAfter,int x,int y,
		int cx,int cy,UINT uFlags);
	BOOL EndDeferWindowPos(HDWP hWinPosInfo);
#endif /* !NODEFERWINDOWPOS */

	BOOL IsWindowVisible(dword hWnd);
	BOOL IsIconic(dword hWnd);
	BOOL AnyPopup(VOID);
	BOOL BringWindowToTop(dword hWnd);
	BOOL IsZoomed(dword hWnd);
}
/*
 * SetWindowPos Flags
 */
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send WM_NCCALCSIZE */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send WM_WINDOWPOSCHANGING */
#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000

#define HWND_TOP        0
#define HWND_BOTTOM     1
#define HWND_TOPMOST    -1
#define HWND_NOTOPMOST  -2

#ifndef NOCTLMGR

/*
 * WARNING:
 * The following structures must NOT be DWORD padded because they are
 * followed by strings, etc that do not have to be DWORD aligned.
 */
#pragma pack(push,2)

/*
 * original NT 32 bit dialog template:
 */
struct DLGTEMPLATE{
  DWORD style;
  DWORD dwExtendedStyle;
  WORD cdit;
  short x;
  short y;
  short cx;
  short cy;
};

/*
 * 32 bit Dialog item template.
 */
struct DLGITEMTEMPLATE{
  DWORD style;
  DWORD dwExtendedStyle;
  short x;
  short y;
  short cx;
  short cy;
  WORD id;
};

#pragma pack(pop)/* Resume normal packing */

extern WINAPI "user32.dll"{
	dword CreateDialogParamA(HINSTANCE hInstance,LPCSTR lpTemplateName,dword hWndParent,
		dword lpDialogFunc,LPARAM dwInitParam);
	dword CreateDialogParamW(HINSTANCE hInstance,LPCWSTR lpTemplateName,dword hWndParent,
		dword lpDialogFunc,LPARAM dwInitParam);
#ifdef UNICODE
#define CreateDialogParam  CreateDialogParamW
#else
#define CreateDialogParam  CreateDialogParamA
#endif // !UNICODE

	dword CreateDialogIndirectParamA(HINSTANCE hInstance,dword lpTemplate,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
	dword CreateDialogIndirectParamW(HINSTANCE hInstance,dword lpTemplate,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
#ifdef UNICODE
#define CreateDialogIndirectParam  CreateDialogIndirectParamW
#else
#define CreateDialogIndirectParam  CreateDialogIndirectParamA
#endif // !UNICODE

#define CreateDialogA(hInstance,lpName,hWndParent,lpDialogFunc) \
CreateDialogParamA(hInstance,lpName,hWndParent,lpDialogFunc,0L)
#define CreateDialogW(hInstance,lpName,hWndParent,lpDialogFunc) \
CreateDialogParamW(hInstance,lpName,hWndParent,lpDialogFunc,0L)
#ifdef UNICODE
#define CreateDialog  CreateDialogW
#else
#define CreateDialog  CreateDialogA
#endif // !UNICODE

#define CreateDialogIndirectA(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
CreateDialogIndirectParamA(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#define CreateDialogIndirectW(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
CreateDialogIndirectParamW(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#ifdef UNICODE
#define CreateDialogIndirect  CreateDialogIndirectW
#else
#define CreateDialogIndirect  CreateDialogIndirectA
#endif // !UNICODE

	dword DialogBoxParamA(HINSTANCE hInstance,LPCSTR lpTemplateName,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
	dword DialogBoxParamW(HINSTANCE hInstance,LPCWSTR lpTemplateName,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
#ifdef UNICODE
#define DialogBoxParam  DialogBoxParamW
#else
#define DialogBoxParam  DialogBoxParamA
#endif // !UNICODE

	dword DialogBoxIndirectParamA(HINSTANCE hInstance,dword hDialogTemplate,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
	dword DialogBoxIndirectParamW(HINSTANCE hInstance,dword hDialogTemplate,
		dword hWndParent,dword lpDialogFunc,LPARAM dwInitParam);
#ifdef UNICODE
#define DialogBoxIndirectParam  DialogBoxIndirectParamW
#else
#define DialogBoxIndirectParam  DialogBoxIndirectParamA
#endif // !UNICODE

#define DialogBoxA(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
DialogBoxParamA(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#define DialogBoxW(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
DialogBoxParamW(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#ifdef UNICODE
#define DialogBox  DialogBoxW
#else
#define DialogBox  DialogBoxA
#endif // !UNICODE

#define DialogBoxIndirectA(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
DialogBoxIndirectParamA(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#define DialogBoxIndirectW(hInstance,lpTemplate,hWndParent,lpDialogFunc) \
DialogBoxIndirectParamW(hInstance,lpTemplate,hWndParent,lpDialogFunc,0L)
#ifdef UNICODE
#define DialogBoxIndirect  DialogBoxIndirectW
#else
#define DialogBoxIndirect  DialogBoxIndirectA
#endif // !UNICODE

	BOOL EndDialog(dword hDlg,dword nResult);
	dword GetDlgItem(dword hDlg,int nIDDlgItem);
	BOOL SetDlgItemInt(dword hDlg,int nIDDlgItem,UINT uValue,BOOL bSigned);
	UINT GetDlgItemInt(dword hDlg,int nIDDlgItem,dword lpTranslated,BOOL bSigned);
	BOOL SetDlgItemTextA(dword hDlg,int nIDDlgItem,LPCSTR lpString);
	BOOL SetDlgItemTextW(dword hDlg,int nIDDlgItem,LPCWSTR lpString);
#ifdef UNICODE
#define SetDlgItemText  SetDlgItemTextW
#else
#define SetDlgItemText  SetDlgItemTextA
#endif // !UNICODE

	UINT GetDlgItemTextA(dword hDlg,int nIDDlgItem,LPSTR lpString,int nMaxCount);
	UINT GetDlgItemTextW(dword hDlg,int nIDDlgItem,LPWSTR lpString,int nMaxCount);
#ifdef UNICODE
#define GetDlgItemText  GetDlgItemTextW
#else
#define GetDlgItemText  GetDlgItemTextA
#endif // !UNICODE

	BOOL CheckDlgButton(dword hDlg,int nIDButton,UINT uCheck);
	BOOL CheckRadioButton(dword hDlg,int nIDFirstButton,int nIDLastButton,int nIDCheckButton);
	UINT IsDlgButtonChecked(dword hDlg,int nIDButton);
	dword SendDlgItemMessageA(dword hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam);
	dword SendDlgItemMessageW(dword hDlg,int nIDDlgItem,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define SendDlgItemMessage  SendDlgItemMessageW
#else
#define SendDlgItemMessage  SendDlgItemMessageA
#endif // !UNICODE

	dword GetNextDlgGroupItem(dword hDlg,dword hCtl,BOOL bPrevious);
	dword GetNextDlgTabItem(dword hDlg,dword hCtl,BOOL bPrevious);
	int GetDlgCtrlID(dword hWnd);
	long GetDialogBaseUnits(VOID);
	dword DefDlgProcA(dword hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);
	dword DefDlgProcW(dword hDlg,UINT Msg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define DefDlgProc  DefDlgProcW
#else
#define DefDlgProc  DefDlgProcA
#endif // !UNICODE

/*
 * Window extra byted needed for private dialog classes.
 */
#ifndef _MAC
#define DLGWINDOWEXTRA 30
#else
#define DLGWINDOWEXTRA 48
#endif

#endif /* !NOCTLMGR */

#ifndef NOMSG
	BOOL CallMsgFilterA(dword lpMsg,int nCode);
	BOOL CallMsgFilterW(dword lpMsg,int nCode);
#ifdef UNICODE
#define CallMsgFilter  CallMsgFilterW
#else
#define CallMsgFilter  CallMsgFilterA
#endif // !UNICODE
#endif /* !NOMSG */

#ifndef NOCLIPBOARD

/*
 * Clipboard Manager Functions
 */
	BOOL OpenClipboard(dword hWndNewOwner);
	BOOL CloseClipboard(VOID);
	DWORD GetClipboardSequenceNumber(VOID);
	dword GetClipboardOwner(VOID);
	dword SetClipboardViewer(dword hWndNewViewer);
	dword GetClipboardViewer(VOID);
	BOOL ChangeClipboardChain(dword hWndRemove,dword hWndNewNext);
	HANDLE SetClipboardData(UINT uFormat,HANDLE hMem);
	HANDLE GetClipboardData(UINT uFormat);
	UINT RegisterClipboardFormatA(LPCSTR lpszFormat);
	UINT RegisterClipboardFormatW(LPCWSTR lpszFormat);
#ifdef UNICODE
#define RegisterClipboardFormat  RegisterClipboardFormatW
#else
#define RegisterClipboardFormat  RegisterClipboardFormatA
#endif // !UNICODE

	int CountClipboardFormats(VOID);
	UINT EnumClipboardFormats(UINT format);
	int GetClipboardFormatNameA(UINT format,LPSTR lpszFormatName,int cchMaxCount);
	int GetClipboardFormatNameW(UINT format,LPWSTR lpszFormatName,int cchMaxCount);
#ifdef UNICODE
#define GetClipboardFormatName  GetClipboardFormatNameW
#else
#define GetClipboardFormatName  GetClipboardFormatNameA
#endif // !UNICODE

	BOOL EmptyClipboard(VOID);
	BOOL IsClipboardFormatAvailable(UINT format);
	int GetPriorityClipboardFormat(dword paFormatPriorityList,int cFormats);
	dword GetOpenClipboardWindow(VOID);
#endif /* !NOCLIPBOARD */

/*
 * Character Translation Routines
 */
	BOOL CharToOemA(LPCSTR lpszSrc,LPSTR lpszDst);
	BOOL CharToOemW(LPCWSTR lpszSrc,LPSTR lpszDst);
#ifdef UNICODE
#define CharToOem  CharToOemW
#else
#define CharToOem  CharToOemA
#endif // !UNICODE

	BOOL OemToCharA(LPCSTR lpszSrc,LPSTR lpszDst);
	BOOL OemToCharW(LPCSTR lpszSrc,LPWSTR lpszDst);
#ifdef UNICODE
#define OemToChar  OemToCharW
#else
#define OemToChar  OemToCharA
#endif // !UNICODE

	BOOL CharToOemBuffA(LPCSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
	BOOL CharToOemBuffW(LPCWSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
#ifdef UNICODE
#define CharToOemBuff  CharToOemBuffW
#else
#define CharToOemBuff  CharToOemBuffA
#endif // !UNICODE

	BOOL OemToCharBuffA(LPCSTR lpszSrc,LPSTR lpszDst,DWORD cchDstLength);
	BOOL OemToCharBuffW(LPCSTR lpszSrc,LPWSTR lpszDst,DWORD cchDstLength);
#ifdef UNICODE
#define OemToCharBuff  OemToCharBuffW
#else
#define OemToCharBuff  OemToCharBuffA
#endif // !UNICODE

	LPSTR CharUpperA(LPSTR lpsz);
	LPWSTR CharUpperW(LPWSTR lpsz);
#ifdef UNICODE
#define CharUpper  CharUpperW
#else
#define CharUpper  CharUpperA
#endif // !UNICODE

	DWORD CharUpperBuffA(LPSTR lpsz,DWORD cchLength);
	DWORD CharUpperBuffW(LPWSTR lpsz,DWORD cchLength);
#ifdef UNICODE
#define CharUpperBuff  CharUpperBuffW
#else
#define CharUpperBuff  CharUpperBuffA
#endif // !UNICODE

	LPSTR CharLowerA(LPSTR lpsz);
	LPWSTR CharLowerW(LPWSTR lpsz);
#ifdef UNICODE
#define CharLower  CharLowerW
#else
#define CharLower  CharLowerA
#endif // !UNICODE

	DWORD CharLowerBuffA(LPSTR lpsz,DWORD cchLength);
	DWORD CharLowerBuffW(LPWSTR lpsz,DWORD cchLength);
#ifdef UNICODE
#define CharLowerBuff  CharLowerBuffW
#else
#define CharLowerBuff  CharLowerBuffA
#endif // !UNICODE

	LPSTR CharNextA(LPCSTR lpsz);
	LPWSTR CharNextW(LPCWSTR lpsz);
#ifdef UNICODE
#define CharNext  CharNextW
#else
#define CharNext  CharNextA
#endif // !UNICODE

	LPSTR CharPrevA(LPCSTR lpszStart,LPCSTR lpszCurrent);
	LPWSTR CharPrevW(LPCWSTR lpszStart,LPCWSTR lpszCurrent);
#ifdef UNICODE
#define CharPrev  CharPrevW
#else
#define CharPrev  CharPrevA
#endif // !UNICODE

	LPSTR CharNextExA(WORD CodePage,LPCSTR lpCurrentChar,DWORD dwFlags);
	LPSTR CharPrevExA(WORD CodePage,LPCSTR lpStart,LPCSTR lpCurrentChar,DWORD dwFlags);

/*
 * Compatibility defines for character translation routines
 */
#define AnsiToOem CharToOemA
#define OemToAnsi OemToCharA
#define AnsiToOemBuff CharToOemBuffA
#define OemToAnsiBuff OemToCharBuffA
#define AnsiUpper CharUpperA
#define AnsiUpperBuff CharUpperBuffA
#define AnsiLower CharLowerA
#define AnsiLowerBuff CharLowerBuffA
#define AnsiNext CharNextA
#define AnsiPrev CharPrevA

#ifndef  NOLANGUAGE
/*
 * Language dependent Routines
 */
	BOOL IsCharAlphaA(CHAR ch);
	BOOL IsCharAlphaW(WCHAR ch);
#ifdef UNICODE
#define IsCharAlpha  IsCharAlphaW
#else
#define IsCharAlpha  IsCharAlphaA
#endif // !UNICODE

	BOOL IsCharAlphaNumericA(CHAR ch);
	BOOL IsCharAlphaNumericW(WCHAR ch);
#ifdef UNICODE
#define IsCharAlphaNumeric  IsCharAlphaNumericW
#else
#define IsCharAlphaNumeric  IsCharAlphaNumericA
#endif // !UNICODE

	BOOL IsCharUpperA(CHAR ch);
	BOOL IsCharUpperW(WCHAR ch);
#ifdef UNICODE
#define IsCharUpper  IsCharUpperW
#else
#define IsCharUpper  IsCharUpperA
#endif // !UNICODE

	BOOL IsCharLowerA(CHAR ch);
	BOOL IsCharLowerW(WCHAR ch);
#ifdef UNICODE
#define IsCharLower  IsCharLowerW
#else
#define IsCharLower  IsCharLowerA
#endif // !UNICODE
#endif  /* !NOLANGUAGE */

	dword SetFocus(dword hWnd);
	dword GetActiveWindow(VOID);
	dword GetFocus(VOID);
	UINT GetKBCodePage(VOID);
	SHORT GetKeyState(int nVirtKey);
	SHORT GetAsyncKeyState(int vKey);
	BOOL GetKeyboardState(dword lpKeyState);
	BOOL SetKeyboardState(dword lpKeyState);
	int GetKeyNameTextA(LONG lParam,LPSTR lpString,int nSize);
	int GetKeyNameTextW(LONG lParam,LPWSTR lpString,int nSize);
#ifdef UNICODE
#define GetKeyNameText  GetKeyNameTextW
#else
#define GetKeyNameText  GetKeyNameTextA
#endif // !UNICODE

	int GetKeyboardType(int nTypeFlag);
	int ToAscii(UINT uVirtKey,UINT uScanCode,dword lpKeyState,LPWORD lpChar,UINT uFlags);
	int ToAsciiEx(UINT uVirtKey,UINT uScanCode,dword lpKeyState,LPWORD lpChar,UINT uFlags,HKL dwhkl);
	int ToUnicode(UINT wVirtKey,UINT wScanCode,dword lpKeyState,LPWSTR pwszBuff,int cchBuff,UINT wFlags);
	DWORD OemKeyScan(WORD wOemChar);
	SHORT VkKeyScanA(CHAR ch);
	SHORT VkKeyScanW(WCHAR ch);
#ifdef UNICODE
#define VkKeyScan  VkKeyScanW
#else
#define VkKeyScan  VkKeyScanA
#endif // !UNICODE

	SHORT VkKeyScanExA(CHAR ch,HKL dwhkl);
	SHORT VkKeyScanExW(WCHAR ch,HKL dwhkl);
#ifdef UNICODE
#define VkKeyScanEx  VkKeyScanExW
#else
#define VkKeyScanEx  VkKeyScanExA
#endif // !UNICODE
#define KEYEVENTF_EXTENDEDKEY 0x0001
#define KEYEVENTF_KEYUP       0x0002
#define KEYEVENTF_UNICODE     0x0004
#define KEYEVENTF_SCANCODE    0x0008

	VOID keybd_event(BYTE bVk,BYTE bScan,DWORD dwFlags,ULONG_PTR dwExtraInfo);

#define MOUSEEVENTF_MOVE        0x0001 /* mouse move */
#define MOUSEEVENTF_LEFTDOWN    0x0002 /* left button down */
#define MOUSEEVENTF_LEFTUP      0x0004 /* left button up */
#define MOUSEEVENTF_RIGHTDOWN   0x0008 /* right button down */
#define MOUSEEVENTF_RIGHTUP     0x0010 /* right button up */
#define MOUSEEVENTF_MIDDLEDOWN  0x0020 /* middle button down */
#define MOUSEEVENTF_MIDDLEUP    0x0040 /* middle button up */
#define MOUSEEVENTF_XDOWN       0x0080 /* x button down */
#define MOUSEEVENTF_XUP         0x0100 /* x button down */
#define MOUSEEVENTF_WHEEL       0x0800 /* wheel button rolled */
#define MOUSEEVENTF_VIRTUALDESK 0x4000 /* map to entire virtual desktop */
#define MOUSEEVENTF_ABSOLUTE    0x8000 /* absolute move */

	VOID mouse_event(DWORD dwFlags,DWORD dx,DWORD dy,DWORD dwData,ULONG_PTR dwExtraInfo);
}

struct MOUSEINPUT {
  LONG    dx;
  LONG    dy;
  DWORD   mouseData;
  DWORD   dwFlags;
  DWORD   time;
  ULONG_PTR dwExtraInfo;
};

struct KEYBDINPUT {
  WORD    wVk;
  WORD    wScan;
  DWORD   dwFlags;
  DWORD   time;
  ULONG_PTR dwExtraInfo;
};

struct HARDWAREINPUT {
  DWORD   uMsg;
  WORD    wParamL;
  WORD    wParamH;
};

#define INPUT_MOUSE     0
#define INPUT_KEYBOARD  1
#define INPUT_HARDWARE  2

struct INPUT {
  DWORD   type;
  union
  {
    MOUSEINPUT      mi;
    KEYBDINPUT      ki;
    HARDWAREINPUT   hi;
  };
};

struct LASTINPUTINFO {
  UINT cbSize;
  DWORD dwTime;
};

extern WINAPI "user32.dll"{
	UINT SendInput(UINT cInputs,dword pInputs,int cbSize);
	BOOL GetLastInputInfo(dword plii);
	UINT MapVirtualKeyA(UINT uCode,UINT uMapType);
	UINT MapVirtualKeyW(UINT uCode,UINT uMapType);
#ifdef UNICODE
#define MapVirtualKey  MapVirtualKeyW
#else
#define MapVirtualKey  MapVirtualKeyA
#endif // !UNICODE

	UINT MapVirtualKeyExA(UINT uCode,UINT uMapType,HKL dwhkl);
	UINT MapVirtualKeyExW(UINT uCode,UINT uMapType,HKL dwhkl);
#ifdef UNICODE
#define MapVirtualKeyEx  MapVirtualKeyExW
#else
#define MapVirtualKeyEx  MapVirtualKeyExA
#endif // !UNICODE

	BOOL GetInputState(VOID);
	DWORD GetQueueStatus(UINT flags);
	dword GetCapture(VOID);
	dword SetCapture(dword hWnd);
	BOOL ReleaseCapture(VOID);
	DWORD MsgWaitForMultipleObjects(DWORD nCount,dword pHandles,BOOL fWaitAll,
		DWORD dwMilliseconds,DWORD dwWakeMask);
	DWORD MsgWaitForMultipleObjectsEx(DWORD nCount,dword pHandles,DWORD dwMilliseconds,
		DWORD dwWakeMask,DWORD dwFlags);

#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004

/*
 * Queue status flags for GetQueueStatus() and MsgWaitForMultipleObjects()
 */
#define QS_KEY              0x0001
#define QS_MOUSEMOVE        0x0002
#define QS_MOUSEBUTTON      0x0004
#define QS_POSTMESSAGE      0x0008
#define QS_TIMER            0x0010
#define QS_PAINT            0x0020
#define QS_SENDMESSAGE      0x0040
#define QS_HOTKEY           0x0080
#define QS_ALLPOSTMESSAGE   0x0100
#define QS_RAWINPUT         0x0400

#define QS_MOUSE           QS_MOUSEMOVE|QS_MOUSEBUTTON

#if (_WIN32_WINNT >= 0x0501)
#define QS_INPUT           QS_MOUSE|QS_KEY|QS_RAWINPUT
#else
#define QS_INPUT           QS_MOUSE|QS_KEY
#endif // (_WIN32_WINNT >= 0x0501)

#define QS_ALLEVENTS QS_INPUT|QS_POSTMESSAGE|QS_TIMER|QS_PAINT|QS_HOTKEY

#define QS_ALLINPUT QS_INPUT|QS_POSTMESSAGE|QS_TIMER|QS_PAINT|QS_HOTKEY|QS_SENDMESSAGE

/*
 * Windows Functions
 */
	dword SetTimer(dword hWnd,dword nIDEvent,UINT uElapse,dword lpTimerFunc);
	BOOL KillTimer(dword hWnd,dword uIDEvent);
	BOOL IsWindowUnicode(dword hWnd);
	BOOL EnableWindow(dword hWnd,BOOL bEnable);
	BOOL IsWindowEnabled(dword hWnd);
	HACCEL LoadAcceleratorsA(HINSTANCE hInstance,LPCSTR lpTableName);
	HACCEL LoadAcceleratorsW(HINSTANCE hInstance,LPCWSTR lpTableName);
#ifdef UNICODE
#define LoadAccelerators  LoadAcceleratorsW
#else
#define LoadAccelerators  LoadAcceleratorsA
#endif // !UNICODE

	HACCEL CreateAcceleratorTableA(dword,int);
	HACCEL CreateAcceleratorTableW(dword,int);
#ifdef UNICODE
#define CreateAcceleratorTable  CreateAcceleratorTableW
#else
#define CreateAcceleratorTable  CreateAcceleratorTableA
#endif // !UNICODE

	BOOL DestroyAcceleratorTable(HACCEL hAccel);
	int CopyAcceleratorTableA(HACCEL hAccelSrc,dword lpAccelDst,int cAccelEntries);
	int CopyAcceleratorTableW(HACCEL hAccelSrc,dword lpAccelDst,int cAccelEntries);
#ifdef UNICODE
#define CopyAcceleratorTable  CopyAcceleratorTableW
#else
#define CopyAcceleratorTable  CopyAcceleratorTableA
#endif // !UNICODE

#ifndef NOMSG
	int TranslateAcceleratorA(dword hWnd,HACCEL hAccTable,dword lpMsg);
	int TranslateAcceleratorW(dword hWnd,HACCEL hAccTable,dword lpMsg);
#ifdef UNICODE
#define TranslateAccelerator  TranslateAcceleratorW
#else
#define TranslateAccelerator  TranslateAcceleratorA
#endif // !UNICODE
#endif /* !NOMSG */

#ifndef NOSYSMETRICS

/*
 * GetSystemMetrics() codes
 */
#define SM_CXSCREEN             0
#define SM_CYSCREEN             1
#define SM_CXVSCROLL            2
#define SM_CYHSCROLL            3
#define SM_CYCAPTION            4
#define SM_CXBORDER             5
#define SM_CYBORDER             6
#define SM_CXDLGFRAME           7
#define SM_CYDLGFRAME           8
#define SM_CYVTHUMB             9
#define SM_CXHTHUMB             10
#define SM_CXICON               11
#define SM_CYICON               12
#define SM_CXCURSOR             13
#define SM_CYCURSOR             14
#define SM_CYMENU               15
#define SM_CXFULLSCREEN         16
#define SM_CYFULLSCREEN         17
#define SM_CYKANJIWINDOW        18
#define SM_MOUSEPRESENT         19
#define SM_CYVSCROLL            20
#define SM_CXHSCROLL            21
#define SM_DEBUG                22
#define SM_SWAPBUTTON           23
#define SM_RESERVED1            24
#define SM_RESERVED2            25
#define SM_RESERVED3            26
#define SM_RESERVED4            27
#define SM_CXMIN                28
#define SM_CYMIN                29
#define SM_CXSIZE               30
#define SM_CYSIZE               31
#define SM_CXFRAME              32
#define SM_CYFRAME              33
#define SM_CXMINTRACK           34
#define SM_CYMINTRACK           35
#define SM_CXDOUBLECLK          36
#define SM_CYDOUBLECLK          37
#define SM_CXICONSPACING        38
#define SM_CYICONSPACING        39
#define SM_MENUDROPALIGNMENT    40
#define SM_PENWINDOWS           41
#define SM_DBCSENABLED          42
#define SM_CMOUSEBUTTONS        43

#define SM_CXFIXEDFRAME           SM_CXDLGFRAME  /* ;win40 name change */
#define SM_CYFIXEDFRAME           SM_CYDLGFRAME  /* ;win40 name change */
#define SM_CXSIZEFRAME            SM_CXFRAME     /* ;win40 name change */
#define SM_CYSIZEFRAME            SM_CYFRAME     /* ;win40 name change */
#define SM_SECURE               44
#define SM_CXEDGE               45
#define SM_CYEDGE               46
#define SM_CXMINSPACING         47
#define SM_CYMINSPACING         48
#define SM_CXSMICON             49
#define SM_CYSMICON             50
#define SM_CYSMCAPTION          51
#define SM_CXSMSIZE             52
#define SM_CYSMSIZE             53
#define SM_CXMENUSIZE           54
#define SM_CYMENUSIZE           55
#define SM_ARRANGE              56
#define SM_CXMINIMIZED          57
#define SM_CYMINIMIZED          58
#define SM_CXMAXTRACK           59
#define SM_CYMAXTRACK           60
#define SM_CXMAXIMIZED          61
#define SM_CYMAXIMIZED          62
#define SM_NETWORK              63
#define SM_CLEANBOOT            67
#define SM_CXDRAG               68
#define SM_CYDRAG               69
#define SM_SHOWSOUNDS           70
#define SM_CXMENUCHECK          71   /* Use instead of GetMenuCheckMarkDimensions()! */
#define SM_CYMENUCHECK          72
#define SM_SLOWMACHINE          73
#define SM_MIDEASTENABLED       74

#define SM_MOUSEWHEELPRESENT    75
#define SM_XVIRTUALSCREEN       76
#define SM_YVIRTUALSCREEN       77
#define SM_CXVIRTUALSCREEN      78
#define SM_CYVIRTUALSCREEN      79
#define SM_CMONITORS            80
#define SM_SAMEDISPLAYFORMAT    81
#define SM_IMMENABLED           82
#define SM_CXFOCUSBORDER        83
#define SM_CYFOCUSBORDER        84

#if (WINVER < 0x0500) && (!defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0400))
#define SM_CMETRICS             76
#else
#define SM_CMETRICS             86
#endif
#define SM_REMOTESESSION        0x1000
#define SM_SHUTTINGDOWN         0x2000

	int GetSystemMetrics(int nIndex);

#endif /* !NOSYSMETRICS */

#ifndef NOMENUS

	HMENU LoadMenuA(HINSTANCE hInstance,LPCSTR lpMenuName);
	HMENU LoadMenuW(HINSTANCE hInstance,LPCWSTR lpMenuName);
#ifdef UNICODE
#define LoadMenu  LoadMenuW
#else
#define LoadMenu  LoadMenuA
#endif // !UNICODE

	HMENU LoadMenuIndirectA(dword lpMenuTemplate);
	HMENU LoadMenuIndirectW(dword lpMenuTemplate);
#ifdef UNICODE
#define LoadMenuIndirect  LoadMenuIndirectW
#else
#define LoadMenuIndirect  LoadMenuIndirectA
#endif // !UNICODE

	HMENU GetMenu(dword hWnd);
	BOOL SetMenu(dword hWnd,HMENU hMenu);
	BOOL ChangeMenuA(HMENU hMenu,UINT cmd,dword lpszNewItem,UINT cmdInsert,UINT flags);
	BOOL ChangeMenuW(HMENU hMenu,UINT cmd,dword lpszNewItem,UINT cmdInsert,UINT flags);
#ifdef UNICODE
#define ChangeMenu  ChangeMenuW
#else
#define ChangeMenu  ChangeMenuA
#endif // !UNICODE

	BOOL HiliteMenuItem(dword hWnd,HMENU hMenu,UINT uIDHiliteItem,UINT uHilite);
	int GetMenuStringA(HMENU hMenu,UINT uIDItem,LPSTR lpString,int nMaxCount,UINT uFlag);
	int GetMenuStringW(HMENU hMenu,UINT uIDItem,LPWSTR lpString,int nMaxCount,UINT uFlag);
#ifdef UNICODE
#define GetMenuString  GetMenuStringW
#else
#define GetMenuString  GetMenuStringA
#endif // !UNICODE

	UINT GetMenuState(HMENU hMenu,UINT uId,UINT uFlags);
	BOOL DrawMenuBar(dword hWnd);

#define PMB_ACTIVE      0x00000001

	HMENU GetSystemMenu(dword hWnd,BOOL bRevert);
	HMENU CreateMenu(VOID);
	HMENU CreatePopupMenu(VOID);
	BOOL DestroyMenu(HMENU hMenu);
	DWORD CheckMenuItem(HMENU hMenu,UINT uIDCheckItem,UINT uCheck);
	BOOL EnableMenuItem(HMENU hMenu,UINT uIDEnableItem,UINT uEnable);
	HMENU GetSubMenu(HMENU hMenu,int nPos);
	UINT GetMenuItemID(HMENU hMenu,int nPos);
	int GetMenuItemCount(HMENU hMenu);
	BOOL InsertMenuA(HMENU hMenu,UINT uPosition,UINT uFlags,dword uIDNewItem,LPCSTR lpNewItem);
	BOOL InsertMenuW(HMENU hMenu,UINT uPosition,UINT uFlags,dword uIDNewItem,LPCWSTR lpNewItem);
#ifdef UNICODE
#define InsertMenu  InsertMenuW
#else
#define InsertMenu  InsertMenuA
#endif // !UNICODE

	BOOL AppendMenuA(HMENU hMenu,UINT uFlags,dword uIDNewItem,LPCSTR lpNewItem);
	BOOL AppendMenuW(HMENU hMenu,UINT uFlags,dword uIDNewItem,LPCWSTR lpNewItem);
#ifdef UNICODE
#define AppendMenu  AppendMenuW
#else
#define AppendMenu  AppendMenuA
#endif // !UNICODE

	BOOL ModifyMenuA(HMENU hMnu,UINT uPosition,UINT uFlags,dword uIDNewItem,LPCSTR lpNewItem);
	BOOL ModifyMenuW(HMENU hMnu,UINT uPosition,UINT uFlags,dword uIDNewItem,LPCWSTR lpNewItem);
#ifdef UNICODE
#define ModifyMenu  ModifyMenuW
#else
#define ModifyMenu  ModifyMenuA
#endif // !UNICODE

	BOOL RemoveMenu(HMENU hMenu,UINT uPosition,UINT uFlags);
	BOOL DeleteMenu(HMENU hMenu,UINT uPosition,UINT uFlags);
	BOOL SetMenuItemBitmaps(HMENU hMenu,UINT uPosition,UINT uFlags,HBITMAP hBitmapUnchecked,HBITMAP hBitmapChecked);
	LONG GetMenuCheckMarkDimensions(VOID);
	BOOL TrackPopupMenu(HMENU hMenu,UINT uFlags,int x,int y,int nReserved,dword hWnd,dword prcRect);
	BOOL TrackPopupMenuEx(HMENU,UINT,int,int,dword,dword);
}
/* return codes for WM_MENUCHAR */
#define MNC_IGNORE  0
#define MNC_CLOSE   1
#define MNC_EXECUTE 2
#define MNC_SELECT  3

struct TPMPARAMS
{
  UINT    cbSize;     /* Size of structure */
  RECT    rcExclude;  /* Screen coordinates of rectangle to exclude when positioning */
};

#define MNS_NOCHECK         0x80000000
#define MNS_MODELESS        0x40000000
#define MNS_DRAGDROP        0x20000000
#define MNS_AUTODISMISS     0x10000000
#define MNS_NOTIFYBYPOS     0x08000000
#define MNS_CHECKORBMP      0x04000000
#define MIM_MAXHEIGHT               0x00000001
#define MIM_BACKGROUND              0x00000002
#define MIM_HELPID                  0x00000004
#define MIM_MENUDATA                0x00000008
#define MIM_STYLE                   0x00000010
#define MIM_APPLYTOSUBMENUS         0x80000000

struct MENUINFO
{
  DWORD   cbSize;
  DWORD   fMask;
  DWORD   dwStyle;
  UINT    cyMax;
  HBRUSH  hbrBack;
  DWORD   dwContextHelpID;
  ULONG_PTR dwMenuData;
};

extern WINAPI "user32.dll"{
	BOOL GetMenuInfo(HMENU,dword);
	BOOL SetMenuInfo(HMENU,dword);
	BOOL EndMenu(VOID);
}

/*
 * WM_MENUDRAG return values.
 */
#define MND_CONTINUE       0
#define MND_ENDMENU        1

struct MENUGETOBJECTINFO
{
  DWORD dwFlags;
  UINT uPos;
  HMENU hmenu;
  PVOID riid;
  PVOID pvObj;
};

/*
 * MENUGETOBJECTINFO dwFlags values
 */
#define MNGOF_TOPGAP         0x00000001
#define MNGOF_BOTTOMGAP      0x00000002

/*
 * WM_MENUGETOBJECT return values
 */
#define MNGO_NOINTERFACE     0x00000000
#define MNGO_NOERROR         0x00000001

#define MIIM_STATE       0x00000001
#define MIIM_ID          0x00000002
#define MIIM_SUBMENU     0x00000004
#define MIIM_CHECKMARKS  0x00000008
#define MIIM_TYPE        0x00000010
#define MIIM_DATA        0x00000020
#define MIIM_STRING      0x00000040
#define MIIM_BITMAP      0x00000080
#define MIIM_FTYPE       0x00000100

#define HBMMENU_CALLBACK            -1
#define HBMMENU_SYSTEM               1
#define HBMMENU_MBAR_RESTORE         2
#define HBMMENU_MBAR_MINIMIZE        3
#define HBMMENU_MBAR_CLOSE           5
#define HBMMENU_MBAR_CLOSE_D         6
#define HBMMENU_MBAR_MINIMIZE_D      7
#define HBMMENU_POPUP_CLOSE          8
#define HBMMENU_POPUP_RESTORE        9
#define HBMMENU_POPUP_MAXIMIZE      10
#define HBMMENU_POPUP_MINIMIZE      11

struct MENUITEMINFO
{
  UINT     cbSize;
  UINT     fMask;
  UINT     fType;         // used if MIIM_TYPE (4.0) or MIIM_FTYPE (>4.0)
  UINT     fState;        // used if MIIM_STATE
  UINT     wID;           // used if MIIM_ID
  HMENU    hSubMenu;      // used if MIIM_SUBMENU
  HBITMAP  hbmpChecked;   // used if MIIM_CHECKMARKS
  HBITMAP  hbmpUnchecked; // used if MIIM_CHECKMARKS
  ULONG_PTR dwItemData;   // used if MIIM_DATA
  LPSTR    dwTypeData;    // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
  UINT     cch;           // used if MIIM_TYPE (4.0) or MIIM_STRING (>4.0)
#if(WINVER >= 0x0500)
  HBITMAP  hbmpItem;      // used if MIIM_BITMAP
#endif /* WINVER >= 0x0500 */
};
#define MENUITEMINFOW MENUITEMINFO
#define MENUITEMINFOA MENUITEMINFO

extern WINAPI "user32.dll"{
	BOOL InsertMenuItemA(HMENU,UINT,BOOL,dword);
	BOOL InsertMenuItemW(HMENU,UINT,BOOL,dword);
#ifdef UNICODE
#define InsertMenuItem  InsertMenuItemW
#else
#define InsertMenuItem  InsertMenuItemA
#endif // !UNICODE

	BOOL GetMenuItemInfoA(HMENU,UINT,BOOL,dword);
	BOOL GetMenuItemInfoW(HMENU,UINT,BOOL,dword);
#ifdef UNICODE
#define GetMenuItemInfo  GetMenuItemInfoW
#else
#define GetMenuItemInfo  GetMenuItemInfoA
#endif // !UNICODE

	BOOL SetMenuItemInfoA(HMENU,UINT,BOOL,dword);
	BOOL SetMenuItemInfoW(HMENU,UINT,BOOL,dword);
#ifdef UNICODE
#define SetMenuItemInfo  SetMenuItemInfoW
#else
#define SetMenuItemInfo  SetMenuItemInfoA
#endif // !UNICODE

#define GMDI_USEDISABLED    0x0001L
#define GMDI_GOINTOPOPUPS   0x0002L

UINT GetMenuDefaultItem(HMENU hMenu,UINT fByPos,UINT gmdiFlags);
BOOL SetMenuDefaultItem(HMENU hMenu,UINT uItem,UINT fByPos);
BOOL GetMenuItemRect(dword hWnd,HMENU hMenu,UINT uItem,dword lprcItem);
int MenuItemFromPoint(dword hWnd,HMENU hMenu,POINT ptScreen);
}
/*
 * Flags for TrackPopupMenu
 */
#define TPM_LEFTBUTTON  0x0000L
#define TPM_RIGHTBUTTON 0x0002L
#define TPM_LEFTALIGN   0x0000L
#define TPM_CENTERALIGN 0x0004L
#define TPM_RIGHTALIGN  0x0008L
#define TPM_TOPALIGN        0x0000L
#define TPM_VCENTERALIGN    0x0010L
#define TPM_BOTTOMALIGN     0x0020L
#define TPM_HORIZONTAL      0x0000L     /* Horz alignment matters more */
#define TPM_VERTICAL        0x0040L     /* Vert alignment matters more */
#define TPM_NONOTIFY        0x0080L     /* Don't send any notification msgs */
#define TPM_RETURNCMD       0x0100L
#define TPM_RECURSE         0x0001L
#define TPM_HORPOSANIMATION 0x0400L
#define TPM_HORNEGANIMATION 0x0800L
#define TPM_VERPOSANIMATION 0x1000L
#define TPM_VERNEGANIMATION 0x2000L
#define TPM_NOANIMATION     0x4000L
#define TPM_LAYOUTRTL       0x8000L

#endif /* !NOMENUS */

// Drag-and-drop support
// Obsolete - use OLE instead
struct DROPSTRUCT
{
  dword    hwndSource;
  dword    hwndSink;
  DWORD   wFmt;
  ULONG_PTR dwData;
  POINT   ptDrop;
  DWORD   dwControlData;
};

#define DOF_EXECUTABLE      0x8001      // wFmt flags
#define DOF_DOCUMENT        0x8002
#define DOF_DIRECTORY       0x8003
#define DOF_MULTIPLE        0x8004
#define DOF_PROGMAN         0x0001
#define DOF_SHELLDATA       0x0002
#define DO_DROPFILE         0x454C4946L
#define DO_PRINTFILE        0x544E5250L

extern WINAPI "user32.dll"{
	DWORD DragObject(dword,dword,UINT,ULONG_PTR,HCURSOR);
	BOOL DragDetect(dword,POINT);
	BOOL DrawIcon(HDC hDC,int X,int Y,HICON hIcon);
}

#ifndef NODRAWTEXT

/*
 * DrawText() Format Flags
 */
#define DT_TOP                      0x00000000
#define DT_LEFT                     0x00000000
#define DT_CENTER                   0x00000001
#define DT_RIGHT                    0x00000002
#define DT_VCENTER                  0x00000004
#define DT_BOTTOM                   0x00000008
#define DT_WORDBREAK                0x00000010
#define DT_SINGLELINE               0x00000020
#define DT_EXPANDTABS               0x00000040
#define DT_TABSTOP                  0x00000080
#define DT_NOCLIP                   0x00000100
#define DT_EXTERNALLEADING          0x00000200
#define DT_CALCRECT                 0x00000400
#define DT_NOPREFIX                 0x00000800
#define DT_INTERNAL                 0x00001000
#define DT_EDITCONTROL              0x00002000
#define DT_PATH_ELLIPSIS            0x00004000
#define DT_END_ELLIPSIS             0x00008000
#define DT_MODIFYSTRING             0x00010000
#define DT_RTLREADING               0x00020000
#define DT_WORD_ELLIPSIS            0x00040000
#define DT_NOFULLWIDTHCHARBREAK     0x00080000
#define DT_HIDEPREFIX               0x00100000
#define DT_PREFIXONLY               0x00200000

struct DRAWTEXTPARAMS
{
  UINT    cbSize;
  int     iTabLength;
  int     iLeftMargin;
  int     iRightMargin;
  UINT    uiLengthDrawn;
};

extern WINAPI "user32.dll"{
	int DrawTextA(HDC hDC,LPCSTR lpString,int nCount,dword lpRect,UINT uFormat);
	int DrawTextW(HDC hDC,LPCWSTR lpString,int nCount,dword lpRect,UINT uFormat);
#ifdef UNICODE
#define DrawText  DrawTextW
#else
#define DrawText  DrawTextA
#endif // !UNICODE

	int DrawTextExA(HDC,LPSTR,int,dword,UINT,dword);
	int DrawTextExW(HDC,LPWSTR,int,dword,UINT,dword);
#ifdef UNICODE
#define DrawTextEx  DrawTextExW
#else
#define DrawTextEx  DrawTextExA
#endif // !UNICODE

#endif /* !NODRAWTEXT */

	BOOL GrayStringA(HDC hDC,HBRUSH hBrush,dword lpOutputFunc,LPARAM lpData,
		int nCount,int X,int Y,int nWidth,int nHeight);
	BOOL GrayStringW(HDC hDC,HBRUSH hBrush,dword lpOutputFunc,LPARAM lpData,
		int nCount,int X,int Y,int nWidth,int nHeight);
#ifdef UNICODE
#define GrayString  GrayStringW
#else
#define GrayString  GrayStringA
#endif // !UNICODE

/* Monolithic state-drawing routine */
/* Image type */
#define DST_COMPLEX     0x0000
#define DST_TEXT        0x0001
#define DST_PREFIXTEXT  0x0002
#define DST_ICON        0x0003
#define DST_BITMAP      0x0004

/* State type */
#define DSS_NORMAL      0x0000
#define DSS_UNION       0x0010  /* Gray string appearance */
#define DSS_DISABLED    0x0020
#define DSS_MONO        0x0080
#define DSS_HIDEPREFIX  0x0200
#define DSS_PREFIXONLY  0x0400
#define DSS_RIGHT       0x8000

	BOOL DrawStateA(HDC,HBRUSH,dword,LPARAM,WPARAM,int,int,int,int,UINT);
	BOOL DrawStateW(HDC,HBRUSH,dword,LPARAM,WPARAM,int,int,int,int,UINT);
#ifdef UNICODE
#define DrawState  DrawStateW
#else
#define DrawState  DrawStateA
#endif // !UNICODE

	LONG TabbedTextOutA(HDC hDC,int X,int Y,LPCSTR lpString,int nCount,
		int nTabPositions,dword lpnTabStopPositions,int nTabOrigin);
	LONG TabbedTextOutW(HDC hDC,int X,int Y,LPCWSTR lpString,int nCount,
		int nTabPositions,dword lpnTabStopPositions,int nTabOrigin);
#ifdef UNICODE
#define TabbedTextOut  TabbedTextOutW
#else
#define TabbedTextOut  TabbedTextOutA
#endif // !UNICODE

	DWORD GetTabbedTextExtentA(HDC hDC,LPCSTR lpString,int nCount,int nTabPositions,
		dword lpnTabStopPositions);
	DWORD GetTabbedTextExtentW(HDC hDC,LPCWSTR lpString,int nCount,
		int nTabPositions,dword lpnTabStopPositions);
#ifdef UNICODE
#define GetTabbedTextExtent  GetTabbedTextExtentW
#else
#define GetTabbedTextExtent  GetTabbedTextExtentA
#endif // !UNICODE

	BOOL UpdateWindow(dword hWnd);
	dword SetActiveWindow(dword hWnd);
	dword GetForegroundWindow(VOID);
	BOOL PaintDesktop(HDC hdc);
	BOOL SetForegroundWindow(dword hWnd);
	BOOL AllowSetForegroundWindow(DWORD dwProcessId);
#define ASFW_ANY    -1
	BOOL LockSetForegroundWindow(UINT uLockCode);
#define LSFW_LOCK       1
#define LSFW_UNLOCK     2

	dword WindowFromDC(HDC hDC);
	HDC GetDC(dword hWnd);
	HDC GetDCEx(dword hWnd,HRGN hrgnClip,DWORD flags);

/*
 * GetDCEx() flags
 */
#define DCX_WINDOW           0x00000001L
#define DCX_CACHE            0x00000002L
#define DCX_NORESETATTRS     0x00000004L
#define DCX_CLIPCHILDREN     0x00000008L
#define DCX_CLIPSIBLINGS     0x00000010L
#define DCX_PARENTCLIP       0x00000020L
#define DCX_EXCLUDERGN       0x00000040L
#define DCX_INTERSECTRGN     0x00000080L
#define DCX_EXCLUDEUPDATE    0x00000100L
#define DCX_INTERSECTUPDATE  0x00000200L
#define DCX_LOCKWINDOWUPDATE 0x00000400L
#define DCX_VALIDATE         0x00200000L

	HDC GetWindowDC(dword hWnd);
	int ReleaseDC(dword hWnd,HDC hDC);
	HDC BeginPaint(dword hWnd,dword lpPaint);
	BOOL EndPaint(dword hWnd,dword lpPaint);
	BOOL GetUpdateRect(dword hWnd,dword lpRect,BOOL bErase);
	int GetUpdateRgn(dword hWnd,HRGN hRgn,BOOL bErase);
	int SetWindowRgn(dword hWnd,HRGN hRgn,BOOL bRedraw);
	int GetWindowRgn(dword hWnd,HRGN hRgn);
	int GetWindowRgnBox(dword hWnd,dword lprc);
	int ExcludeUpdateRgn(HDC hDC,dword hWnd);
	BOOL InvalidateRect(dword hWnd,dword lpRect,BOOL bErase);
	BOOL ValidateRect(dword hWnd,dword lpRect);
	BOOL InvalidateRgn(dword hWnd,HRGN hRgn,BOOL bErase);
	BOOL ValidateRgn(dword hWnd,HRGN hRgn);
	BOOL RedrawWindow(dword hWnd,dword lprcUpdate,HRGN hrgnUpdate,UINT flags);

/*
 * RedrawWindow() flags
 */
#define RDW_INVALIDATE          0x0001
#define RDW_INTERNALPAINT       0x0002
#define RDW_ERASE               0x0004
#define RDW_VALIDATE            0x0008
#define RDW_NOINTERNALPAINT     0x0010
#define RDW_NOERASE             0x0020
#define RDW_NOCHILDREN          0x0040
#define RDW_ALLCHILDREN         0x0080
#define RDW_UPDATENOW           0x0100
#define RDW_ERASENOW            0x0200
#define RDW_FRAME               0x0400
#define RDW_NOFRAME             0x0800

/*
 * LockWindowUpdate API
 */
	BOOL LockWindowUpdate(dword hWndLock);
	BOOL ScrollWindow(dword hWnd,int XAmount,int YAmount,dword lpRect,dword lpClipRect);
	BOOL ScrollDC(HDC hDC,int dx,int dy,dword lprcScroll,dword lprcClip,
		HRGN hrgnUpdate,dword lprcUpdate);
	int ScrollWindowEx(dword hWnd,int dx,int dy,dword prcScroll,dword prcClip,
		HRGN hrgnUpdate,dword prcUpdate,UINT flags);

#define SW_SCROLLCHILDREN   0x0001  /* Scroll children within *lprcScroll. */
#define SW_INVALIDATE       0x0002  /* Invalidate after scrolling */
#define SW_ERASE            0x0004  /* If SW_INVALIDATE, don't send WM_ERASEBACKGROUND */
#define SW_SMOOTHSCROLL     0x0010  /* Use smooth scrolling */

#ifndef NOSCROLL

	int SetScrollPos(dword hWnd,int nBar,int nPos,BOOL bRedraw);
	int GetScrollPos(dword hWnd,int nBar);
	BOOL SetScrollRange(dword hWnd,int nBar,int nMinPos,int nMaxPos,BOOL bRedraw);
	BOOL GetScrollRange(dword hWnd,int nBar,LPINT lpMinPos,LPINT lpMaxPos);
	BOOL ShowScrollBar(dword hWnd,int wBar,BOOL bShow);
	BOOL EnableScrollBar(dword hWnd,UINT wSBflags,UINT wArrows);

/*
 * EnableScrollBar() flags
 */
#define ESB_ENABLE_BOTH     0x0000
#define ESB_DISABLE_BOTH    0x0003
#define ESB_DISABLE_LEFT    0x0001
#define ESB_DISABLE_RIGHT   0x0002
#define ESB_DISABLE_UP      0x0001
#define ESB_DISABLE_DOWN    0x0002
#define ESB_DISABLE_LTUP    ESB_DISABLE_LEFT
#define ESB_DISABLE_RTDN    ESB_DISABLE_RIGHT

#endif  /* !NOSCROLL */

	BOOL SetPropA(dword hWnd,LPCSTR lpString,HANDLE hData);
	BOOL SetPropW(dword hWnd,LPCWSTR lpString,HANDLE hData);
#ifdef UNICODE
#define SetProp  SetPropW
#else
#define SetProp  SetPropA
#endif // !UNICODE

	HANDLE GetPropA(dword hWnd,LPCSTR lpString);
	HANDLE GetPropW(dword hWnd,LPCWSTR lpString);
#ifdef UNICODE
#define GetProp  GetPropW
#else
#define GetProp  GetPropA
#endif // !UNICODE

	HANDLE RemovePropA(dword hWnd,LPCSTR lpString);
	HANDLE RemovePropW(dword hWnd,LPCWSTR lpString);
#ifdef UNICODE
#define RemoveProp  RemovePropW
#else
#define RemoveProp  RemovePropA
#endif // !UNICODE

	int EnumPropsExA(dword hWnd,dword lpEnumFunc,LPARAM lParam);
	int EnumPropsExW(dword hWnd,dword lpEnumFunc,LPARAM lParam);
#ifdef UNICODE
#define EnumPropsEx  EnumPropsExW
#else
#define EnumPropsEx  EnumPropsExA
#endif // !UNICODE

	int EnumPropsA(dword hWnd,dword lpEnumFunc);
	int EnumPropsW(dword hWnd,dword lpEnumFunc);
#ifdef UNICODE
#define EnumProps  EnumPropsW
#else
#define EnumProps  EnumPropsA
#endif // !UNICODE

	BOOL SetWindowTextA(dword hWnd,LPCSTR lpString);
	BOOL SetWindowTextW(dword hWnd,LPCWSTR lpString);
#ifdef UNICODE
#define SetWindowText  SetWindowTextW
#else
#define SetWindowText  SetWindowTextA
#endif // !UNICODE

	int GetWindowTextA(dword hWnd,LPSTR lpString,int nMaxCount);
	int GetWindowTextW(dword hWnd,LPWSTR lpString,int nMaxCount);
#ifdef UNICODE
#define GetWindowText  GetWindowTextW
#else
#define GetWindowText  GetWindowTextA
#endif // !UNICODE

	int GetWindowTextLengthA(dword hWnd);
	int GetWindowTextLengthW(dword hWnd);
#ifdef UNICODE
#define GetWindowTextLength  GetWindowTextLengthW
#else
#define GetWindowTextLength  GetWindowTextLengthA
#endif // !UNICODE

	BOOL GetClientRect(dword hWnd,dword lpRect);
	BOOL GetWindowRect(dword hWnd,dword lpRect);
	BOOL AdjustWindowRect(dword lpRect,DWORD dwStyle,BOOL bMenu);
	BOOL AdjustWindowRectEx(dword lpRect,DWORD dwStyle,BOOL bMenu,DWORD dwExStyle);
}
#define HELPINFO_WINDOW    0x0001
#define HELPINFO_MENUITEM  0x0002
struct HELPINFO      /* Structure pointed to by lParam of WM_HELP */
{
  UINT    cbSize;             /* Size in bytes of this struct  */
  int     iContextType;       /* Either HELPINFO_WINDOW or HELPINFO_MENUITEM */
  int     iCtrlId;            /* Control Id or a Menu item Id. */
  HANDLE  hItemHandle;        /* hWnd of control or hMenu.     */
  DWORD_PTR dwContextId;      /* Context Id associated with this item */
  POINT   MousePos;           /* Mouse Position in screen co-ordinates */
};

extern WINAPI "user32.dll"{
	BOOL SetWindowContextHelpId(dword,DWORD);
	DWORD GetWindowContextHelpId(dword);
	BOOL SetMenuContextHelpId(HMENU,DWORD);
	DWORD GetMenuContextHelpId(HMENU);

#ifndef NOMB

/*
 * MessageBox() Flags
 */
#define MB_OK                       0x00000000L
#define MB_OKCANCEL                 0x00000001L
#define MB_ABORTRETRYIGNORE         0x00000002L
#define MB_YESNOCANCEL              0x00000003L
#define MB_YESNO                    0x00000004L
#define MB_RETRYCANCEL              0x00000005L
#define MB_CANCELTRYCONTINUE        0x00000006L

#define MB_ICONHAND                 0x00000010L
#define MB_ICONQUESTION             0x00000020L
#define MB_ICONEXCLAMATION          0x00000030L
#define MB_ICONASTERISK             0x00000040L

#define MB_USERICON                 0x00000080L
#define MB_ICONWARNING              MB_ICONEXCLAMATION
#define MB_ICONERROR                MB_ICONHAND

#define MB_ICONINFORMATION          MB_ICONASTERISK
#define MB_ICONSTOP                 MB_ICONHAND
#define MB_DEFBUTTON1               0x00000000L
#define MB_DEFBUTTON2               0x00000100L
#define MB_DEFBUTTON3               0x00000200L
#define MB_DEFBUTTON4               0x00000300L

#define MB_APPLMODAL                0x00000000L
#define MB_SYSTEMMODAL              0x00001000L
#define MB_TASKMODAL                0x00002000L
#define MB_HELP                     0x00004000L // Help Button

#define MB_NOFOCUS                  0x00008000L
#define MB_SETFOREGROUND            0x00010000L
#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L

#define MB_TOPMOST                  0x00040000L
#define MB_RIGHT                    0x00080000L
#define MB_RTLREADING               0x00100000L

#if (_WIN32_WINNT >= 0x0400)
#define MB_SERVICE_NOTIFICATION          0x00200000L
#else
#define MB_SERVICE_NOTIFICATION          0x00040000L
#endif
#define MB_SERVICE_NOTIFICATION_NT3X     0x00040000L

#define MB_TYPEMASK                 0x0000000FL
#define MB_ICONMASK                 0x000000F0L
#define MB_DEFMASK                  0x00000F00L
#define MB_MODEMASK                 0x00003000L
#define MB_MISCMASK                 0x0000C000L

	int MessageBoxA(dword hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
	int MessageBoxW(dword hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType);
#ifdef UNICODE
#define MessageBox  MessageBoxW
#else
#define MessageBox  MessageBoxA
#endif // !UNICODE

	int MessageBoxExA(dword hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType,WORD wLanguageId);
	int MessageBoxExW(dword hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType,WORD wLanguageId);
#ifdef UNICODE
#define MessageBoxEx  MessageBoxExW
#else
#define MessageBoxEx  MessageBoxExA
#endif // !UNICODE
}

struct MSGBOXPARAMS
{
  UINT        cbSize;
  dword        hwndOwner;
  HINSTANCE   hInstance;
  LPCSTR      lpszText;
  LPCSTR      lpszCaption;
  DWORD       dwStyle;
  LPCSTR      lpszIcon;
  DWORD_PTR   dwContextHelpId;
  dword      lpfnMsgBoxCallback;
  DWORD       dwLanguageId;
};
#define MSGBOXPARAMSW MSGBOXPARAMS
#define MSGBOXPARAMSA MSGBOXPARAMS

extern WINAPI "user32.dll"{
	int MessageBoxIndirectA(dword);
	int MessageBoxIndirectW(dword);
#ifdef UNICODE
#define MessageBoxIndirect  MessageBoxIndirectW
#else
#define MessageBoxIndirect  MessageBoxIndirectA
#endif // !UNICODE

	BOOL MessageBeep(UINT uType);
#endif /* !NOMB */

	int ShowCursor(BOOL bShow);
	BOOL SetCursorPos(int X,int Y);
	HCURSOR SetCursor(HCURSOR hCursor);
	BOOL GetCursorPos(dword lpPoint);
	BOOL ClipCursor(dword lpRect);
	BOOL GetClipCursor(dword lpRect);
	HCURSOR GetCursor(VOID);
	BOOL CreateCaret(dword hWnd,HBITMAP hBitmap,int nWidth,int nHeight);
	UINT GetCaretBlinkTime(VOID);
	BOOL SetCaretBlinkTime(UINT uMSeconds);
	BOOL DestroyCaret(VOID);
	BOOL HideCaret(dword hWnd);
	BOOL ShowCaret(dword hWnd);
	BOOL SetCaretPos(int X,int Y);
	BOOL GetCaretPos(dword lpPoint);
	BOOL ClientToScreen(dword hWnd,dword lpPoint);
	BOOL ScreenToClient(dword hWnd,dword lpPoint);
	int MapWindowPoints(dword hWndFrom,dword hWndTo,dword lpPoints,UINT cPoints);
	dword WindowFromPoint(POINT Point);
	dword ChildWindowFromPoint(dword hWndParent,POINT Point);

#define CWP_ALL             0x0000
#define CWP_SKIPINVISIBLE   0x0001
#define CWP_SKIPDISABLED    0x0002
#define CWP_SKIPTRANSPARENT 0x0004

	dword ChildWindowFromPointEx(dword,POINT,UINT);

#ifndef NOCOLOR

/*
 * Color Types
 */
#define CTLCOLOR_MSGBOX         0
#define CTLCOLOR_EDIT           1
#define CTLCOLOR_LISTBOX        2
#define CTLCOLOR_BTN            3
#define CTLCOLOR_DLG            4
#define CTLCOLOR_SCROLLBAR      5
#define CTLCOLOR_STATIC         6
#define CTLCOLOR_MAX            7

#define COLOR_SCROLLBAR         0
#define COLOR_BACKGROUND        1
#define COLOR_ACTIVECAPTION     2
#define COLOR_INACTIVECAPTION   3
#define COLOR_MENU              4
#define COLOR_WINDOW            5
#define COLOR_WINDOWFRAME       6
#define COLOR_MENUTEXT          7
#define COLOR_WINDOWTEXT        8
#define COLOR_CAPTIONTEXT       9
#define COLOR_ACTIVEBORDER      10
#define COLOR_INACTIVEBORDER    11
#define COLOR_APPWORKSPACE      12
#define COLOR_HIGHLIGHT         13
#define COLOR_HIGHLIGHTTEXT     14
#define COLOR_BTNFACE           15
#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT           18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT      20
#define COLOR_3DDKSHADOW        21
#define COLOR_3DLIGHT           22
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
#define COLOR_HOTLIGHT          26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#define COLOR_MENUHILIGHT       29
#define COLOR_MENUBAR           30
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT

	DWORD GetSysColor(int nIndex);
	HBRUSH GetSysColorBrush(int nIndex);
	BOOL SetSysColors(int cElements,DWORD lpaElements,DWORD lpaRgbValues);
#endif /* !NOCOLOR */

	BOOL DrawFocusRect(HDC hDC,DWORD lprc);
	int FillRect(HDC hDC,DWORD lprc,HBRUSH hbr);
	int FrameRect(HDC hDC,DWORD lprc,HBRUSH hbr);
	BOOL InvertRect(HDC hDC,DWORD lprc);
	BOOL SetRect(dword lprc,int xLeft,int yTop,int xRight,int yBottom);
	BOOL SetRectEmpty(dword lprc);
	BOOL CopyRect(dword lprcDst,dword lprcSrc);
	BOOL InflateRect(dword lprc,int dx,int dy);
	BOOL IntersectRect(dword lprcDst,dword lprcSrc1,dword lprcSrc2);
	BOOL UnionRect(dword lprcDst,dword lprcSrc1,dword lprcSrc2);
	BOOL SubtractRect(dword lprcDst,dword lprcSrc1,dword lprcSrc2);
	BOOL OffsetRect(dword lprc,int dx,int dy);
	BOOL IsRectEmpty(dword lprc);
	BOOL EqualRect(dword lprc1,dword lprc2);
	BOOL PtInRect(dword lprc,POINT pt);

#ifndef NOWINOFFSETS
	WORD GetWindowWord(dword hWnd,int nIndex);
	WORD SetWindowWord(dword hWnd,int nIndex,WORD wNewWord);
	LONG GetWindowLongA(dword hWnd,int nIndex);
	LONG GetWindowLongW(dword hWnd,int nIndex);
#ifdef UNICODE
#define GetWindowLong  GetWindowLongW
#else
#define GetWindowLong  GetWindowLongA
#endif // !UNICODE

	LONG SetWindowLongA(dword hWnd,int nIndex,LONG dwNewLong);
	LONG SetWindowLongW(dword hWnd,int nIndex,LONG dwNewLong);
#ifdef UNICODE
#define SetWindowLong  SetWindowLongW
#else
#define SetWindowLong  SetWindowLongA
#endif // !UNICODE

#define GetWindowLongPtrA   GetWindowLongA
#define GetWindowLongPtrW   GetWindowLongW
#ifdef UNICODE
#define GetWindowLongPtr  GetWindowLongPtrW
#else
#define GetWindowLongPtr  GetWindowLongPtrA
#endif // !UNICODE

#define SetWindowLongPtrA   SetWindowLongA
#define SetWindowLongPtrW   SetWindowLongW
#ifdef UNICODE
#define SetWindowLongPtr  SetWindowLongPtrW
#else
#define SetWindowLongPtr  SetWindowLongPtrA
#endif // !UNICODE

	WORD GetClassWord(dword hWnd,int nIndex);
	WORD SetClassWord(dword hWnd,int nIndex,WORD wNewWord);
	DWORD GetClassLongA(dword hWnd,int nIndex);
	DWORD GetClassLongW(dword hWnd,int nIndex);
#ifdef UNICODE
#define GetClassLong  GetClassLongW
#else
#define GetClassLong  GetClassLongA
#endif // !UNICODE

	DWORD SetClassLongA(dword hWnd,int nIndex,LONG dwNewLong);
	DWORD SetClassLongW(dword hWnd,int nIndex,LONG dwNewLong);
#ifdef UNICODE
#define SetClassLong  SetClassLongW
#else
#define SetClassLong  SetClassLongA
#endif // !UNICODE

#define GetClassLongPtrA    GetClassLongA
#define GetClassLongPtrW    GetClassLongW
#ifdef UNICODE
#define GetClassLongPtr  GetClassLongPtrW
#else
#define GetClassLongPtr  GetClassLongPtrA
#endif // !UNICODE

#define SetClassLongPtrA    SetClassLongA
#define SetClassLongPtrW    SetClassLongW
#ifdef UNICODE
#define SetClassLongPtr  SetClassLongPtrW
#else
#define SetClassLongPtr  SetClassLongPtrA
#endif // !UNICODE

#endif /* !NOWINOFFSETS */

	BOOL GetProcessDefaultLayout(dword pdwDefaultLayout);
	BOOL SetProcessDefaultLayout(DWORD dwDefaultLayout);
	dword GetDesktopWindow(VOID);
	dword GetParent(dword hWnd);
	dword SetParent(dword hWndChild,dword hWndNewParent);
	BOOL EnumChildWindows(dword hWndParent,dword lpEnumFunc,LPARAM lParam);
	dword FindWindowA(LPCSTR lpClassName,LPCSTR lpWindowName);
	dword FindWindowW(LPCWSTR lpClassName,LPCWSTR lpWindowName);
#ifdef UNICODE
#define FindWindow  FindWindowW
#else
#define FindWindow  FindWindowA
#endif // !UNICODE

	dword FindWindowExA(dword,dword,LPCSTR,LPCSTR);
	dword FindWindowExW(dword,dword,LPCWSTR,LPCWSTR);
#ifdef UNICODE
#define FindWindowEx  FindWindowExW
#else
#define FindWindowEx  FindWindowExA
#endif // !UNICODE

	BOOL EnumWindows(dword lpEnumFunc,LPARAM lParam);
	BOOL EnumThreadWindows(DWORD dwThreadId,dword lpfn,LPARAM lParam);

#define EnumTaskWindows(hTask,lpfn,lParam) EnumThreadWindows(HandleToUlong(hTask),lpfn,lParam)

	int GetClassNameA(dword hWnd,LPSTR lpClassName,int nMaxCount);
	int GetClassNameW(dword hWnd,LPWSTR lpClassName,int nMaxCount);
#ifdef UNICODE
#define GetClassName  GetClassNameW
#else
#define GetClassName  GetClassNameA
#endif // !UNICODE

	dword GetTopWindow(dword hWnd);

#define GetNextWindow(hWnd,wCmd) GetWindow(hWnd,wCmd)
#define GetSysModalWindow() NULL
#define SetSysModalWindow(hWnd) NULL

	DWORD GetWindowThreadProcessId(dword hWnd,dword lpdwProcessId);
	BOOL IsGUIThread(BOOL bConvert);

#define GetWindowTask(hWnd) GetWindowThreadProcessId(hWnd,NULL)

	dword GetLastActivePopup(dword hWnd);

/*
 * GetWindow() Constants
 */
#define GW_HWNDFIRST        0
#define GW_HWNDLAST         1
#define GW_HWNDNEXT         2
#define GW_HWNDPREV         3
#define GW_OWNER            4
#define GW_CHILD            5
#if(WINVER <= 0x0400)
#define GW_MAX              5
#else
#define GW_ENABLEDPOPUP     6
#define GW_MAX              6
#endif

	dword GetWindow(dword hWnd,UINT uCmd);

#ifndef NOWH

#ifdef STRICT

	dword SetWindowsHookA(int nFilterType,dword pfnFilterProc);
	dword SetWindowsHookW(int nFilterType,dword pfnFilterProc);
#ifdef UNICODE
#define SetWindowsHook  SetWindowsHookW
#else
#define SetWindowsHook  SetWindowsHookA
#endif // !UNICODE

#else /* !STRICT */

	dword SetWindowsHookA(int nFilterType,dword pfnFilterProc);
	dword SetWindowsHookW(int nFilterType,dword pfnFilterProc);
#ifdef UNICODE
#define SetWindowsHook  SetWindowsHookW
#else
#define SetWindowsHook  SetWindowsHookA
#endif // !UNICODE

#endif /* !STRICT */

	BOOL UnhookWindowsHook(int nCode,dword pfnFilterProc);
	dword SetWindowsHookExA(int idHook,dword lpfn,HINSTANCE hmod,DWORD dwThreadId);
	dword SetWindowsHookExW(int idHook,dword lpfn,HINSTANCE hmod,DWORD dwThreadId);
#ifdef UNICODE
#define SetWindowsHookEx  SetWindowsHookExW
#else
#define SetWindowsHookEx  SetWindowsHookExA
#endif // !UNICODE

	BOOL UnhookWindowsHookEx(dword hhk);
	dword CallNextHookEx(dword hhk,int nCode,WPARAM wParam,LPARAM lParam);

/*
 * Macros for source-level compatibility with old functions.
 */
#ifdef STRICT
#define DefHookProc(nCode,wParam,lParam,phhk) CallNextHookEx(*phhk,nCode,wParam,lParam)
#else
#define DefHookProc(nCode,wParam,lParam,phhk) CallNextHookEx(*phhk,nCode,wParam,lParam)
#endif /* STRICT */
#endif /* !NOWH */

#ifndef NOMENUS

/* ;win40  -- A lot of MF_* flags have been renamed as MFT_* and MFS_* flags */
/*
 * Menu flags for Add/Check/EnableMenuItem()
 */
#define MF_INSERT           0x00000000L
#define MF_CHANGE           0x00000080L
#define MF_APPEND           0x00000100L
#define MF_DELETE           0x00000200L
#define MF_REMOVE           0x00001000L
#define MF_BYCOMMAND        0x00000000L
#define MF_BYPOSITION       0x00000400L
#define MF_SEPARATOR        0x00000800L
#define MF_ENABLED          0x00000000L
#define MF_GRAYED           0x00000001L
#define MF_DISABLED         0x00000002L
#define MF_UNCHECKED        0x00000000L
#define MF_CHECKED          0x00000008L
#define MF_USECHECKBITMAPS  0x00000200L
#define MF_STRING           0x00000000L
#define MF_BITMAP           0x00000004L
#define MF_OWNERDRAW        0x00000100L
#define MF_POPUP            0x00000010L
#define MF_MENUBARBREAK     0x00000020L
#define MF_MENUBREAK        0x00000040L
#define MF_UNHILITE         0x00000000L
#define MF_HILITE           0x00000080L

#define MF_DEFAULT          0x00001000L
#define MF_SYSMENU          0x00002000L
#define MF_HELP             0x00004000L
#define MF_RIGHTJUSTIFY     0x00004000L

#define MF_MOUSESELECT      0x00008000L
#define MF_END              0x00000080L  /* Obsolete -- only used by old RES files */

#define MFT_STRING          MF_STRING
#define MFT_BITMAP          MF_BITMAP
#define MFT_MENUBARBREAK    MF_MENUBARBREAK
#define MFT_MENUBREAK       MF_MENUBREAK
#define MFT_OWNERDRAW       MF_OWNERDRAW
#define MFT_RADIOCHECK      0x00000200L
#define MFT_SEPARATOR       MF_SEPARATOR
#define MFT_RIGHTORDER      0x00002000L
#define MFT_RIGHTJUSTIFY    MF_RIGHTJUSTIFY

/* Menu flags for Add/Check/EnableMenuItem() */
#define MFS_GRAYED          0x00000003L
#define MFS_DISABLED        MFS_GRAYED
#define MFS_CHECKED         MF_CHECKED
#define MFS_HILITE          MF_HILITE
#define MFS_ENABLED         MF_ENABLED
#define MFS_UNCHECKED       MF_UNCHECKED
#define MFS_UNHILITE        MF_UNHILITE
#define MFS_DEFAULT         MF_DEFAULT

	BOOL CheckMenuRadioItem(HMENU,UINT,UINT,UINT,UINT);
}
/*
 * Menu item resource format
 */
struct MENUITEMTEMPLATEHEADER{
  WORD versionNumber;
  WORD offset;
};

struct MENUITEMTEMPLATE{        // version 0
  WORD mtOption;
  WORD mtID;
  WCHAR mtString[1];
};
#define MF_END             0x00000080L

#endif /* !NOMENUS */

#ifndef NOSYSCOMMANDS

/*
 * System Menu Command Values
 */
#define SC_SIZE         0xF000
#define SC_MOVE         0xF010
#define SC_MINIMIZE     0xF020
#define SC_MAXIMIZE     0xF030
#define SC_NEXTWINDOW   0xF040
#define SC_PREVWINDOW   0xF050
#define SC_CLOSE        0xF060
#define SC_VSCROLL      0xF070
#define SC_HSCROLL      0xF080
#define SC_MOUSEMENU    0xF090
#define SC_KEYMENU      0xF100
#define SC_ARRANGE      0xF110
#define SC_RESTORE      0xF120
#define SC_TASKLIST     0xF130
#define SC_SCREENSAVE   0xF140
#define SC_HOTKEY       0xF150
#define SC_DEFAULT      0xF160
#define SC_MONITORPOWER 0xF170
#define SC_CONTEXTHELP  0xF180
#define SC_SEPARATOR    0xF00F

/*
 * Obsolete names
 */
#define SC_ICON         SC_MINIMIZE
#define SC_ZOOM         SC_MAXIMIZE

#endif /* !NOSYSCOMMANDS */

struct ICONINFO {
  BOOL    fIcon;
  DWORD   xHotspot;
  DWORD   yHotspot;
  HBITMAP hbmMask;
  HBITMAP hbmColor;
};

/* Icon/Cursor header */
struct CURSORSHAPE
{
  int     xHotSpot;
  int     yHotSpot;
  int     cx;
  int     cy;
  int     cbWidth;
  BYTE    Planes;
  BYTE    BitsPixel;
};

extern WINAPI "user32.dll"{
/*
 * Resource Loading Routines
 */
	dword LoadBitmapA(HINSTANCE hInstance,LPCSTR lpBitmapName);
	dword LoadBitmapW(HINSTANCE hInstance,LPCWSTR lpBitmapName);
#ifdef UNICODE
#define LoadBitmap  LoadBitmapW
#else
#define LoadBitmap  LoadBitmapA
#endif // !UNICODE

	dword LoadCursorA(HINSTANCE hInstance,LPCSTR lpCursorName);
	dword LoadCursorW(HINSTANCE hInstance,LPCWSTR lpCursorName);
#ifdef UNICODE
#define LoadCursor  LoadCursorW
#else
#define LoadCursor  LoadCursorA
#endif // !UNICODE

	dword LoadCursorFromFileA(LPCSTR lpFileName);
	dword LoadCursorFromFileW(LPCWSTR lpFileName);
#ifdef UNICODE
#define LoadCursorFromFile  LoadCursorFromFileW
#else
#define LoadCursorFromFile  LoadCursorFromFileA
#endif // !UNICODE

	dword CreateCursor(HINSTANCE hInst,int xHotSpot,int yHotSpot,int nWidth,
		int nHeight,dword pvANDPlane,dword pvXORPlane);
	BOOL DestroyCursor(HCURSOR hCursor);

#ifndef _MAC
#define CopyCursor(pcur) CopyIcon(pcur)
#else
	dword CopyCursor(HCURSOR hCursor);
#endif

/*
 * Standard Cursor IDs
 */
#define IDC_ARROW           32512
#define IDC_IBEAM           32513
#define IDC_WAIT            32514
#define IDC_CROSS           32515
#define IDC_UPARROW         32516
#define IDC_SIZE            32640  /* OBSOLETE: use IDC_SIZEALL */
#define IDC_ICON            32641  /* OBSOLETE: use IDC_ARROW */
#define IDC_SIZENWSE        32642
#define IDC_SIZENESW        32643
#define IDC_SIZEWE          32644
#define IDC_SIZENS          32645
#define IDC_SIZEALL         32646
#define IDC_NO              32648 /*not in win3.1 */
#define IDC_HAND            32649
#define IDC_APPSTARTING     32650 /*not in win3.1 */
#define IDC_HELP            32651

	BOOL SetSystemCursor(HCURSOR hcur,DWORD id);
	dword LoadIconA(HINSTANCE hInstance,LPCSTR lpIconName);
	dword LoadIconW(HINSTANCE hInstance,LPCWSTR lpIconName);
#ifdef UNICODE
#define LoadIcon  LoadIconW
#else
#define LoadIcon  LoadIconA
#endif // !UNICODE

	dword CreateIcon(HINSTANCE hInstance,int nWidth,int nHeight,BYTE cPlanes,
		BYTE cBitsPixel,dword lpbANDbits,dword lpbXORbits);
	BOOL DestroyIcon(HICON hIcon);
	int LookupIconIdFromDirectory(dword presbits,BOOL fIcon);
	int LookupIconIdFromDirectoryEx(dword presbits,BOOL fIcon,int cxDesired,
		int cyDesired,UINT Flags);
	dword CreateIconFromResource(dword presbits,DWORD dwResSize,BOOL fIcon,DWORD dwVer);
	dword CreateIconFromResourceEx(dword presbits,DWORD dwResSize,BOOL fIcon,
		DWORD dwVer,int cxDesired,int cyDesired,UINT Flags);

#define IMAGE_BITMAP        0
#define IMAGE_ICON          1
#define IMAGE_CURSOR        2
#define IMAGE_ENHMETAFILE   3

#define LR_DEFAULTCOLOR     0x0000
#define LR_MONOCHROME       0x0001
#define LR_COLOR            0x0002
#define LR_COPYRETURNORG    0x0004
#define LR_COPYDELETEORG    0x0008
#define LR_LOADFROMFILE     0x0010
#define LR_LOADTRANSPARENT  0x0020
#define LR_DEFAULTSIZE      0x0040
#define LR_VGACOLOR         0x0080
#define LR_LOADMAP3DCOLORS  0x1000
#define LR_CREATEDIBSECTION 0x2000
#define LR_COPYFROMRESOURCE 0x4000
#define LR_SHARED           0x8000

	dword LoadImageA(HINSTANCE,LPCSTR,UINT,int,int,UINT);
	dword LoadImageW(HINSTANCE,LPCWSTR,UINT,int,int,UINT);
#ifdef UNICODE
#define LoadImage  LoadImageW
#else
#define LoadImage  LoadImageA
#endif // !UNICODE

	HANDLE CopyImage(HANDLE,UINT,int,int,UINT);

#define DI_MASK         0x0001
#define DI_IMAGE        0x0002
#define DI_NORMAL       0x0003
#define DI_COMPAT       0x0004
#define DI_DEFAULTSIZE  0x0008
#define DI_NOMIRROR     0x0010

	BOOL DrawIconEx(HDC hdc,int xLeft,int yTop,HICON hIcon,int cxWidth,int cyWidth,
     UINT istepIfAniCur,HBRUSH hbrFlickerFreeDraw,UINT diFlags);
	dword CreateIconIndirect(dword piconinfo);
	dword CopyIcon(HICON hIcon);
	BOOL GetIconInfo(HICON hIcon,dword piconinfo);

#define RES_ICON    1
#define RES_CURSOR  2

#ifdef OEMRESOURCE

/*
 * OEM Resource Ordinal Numbers
 */
#define OBM_CLOSE           32754
#define OBM_UPARROW         32753
#define OBM_DNARROW         32752
#define OBM_RGARROW         32751
#define OBM_LFARROW         32750
#define OBM_REDUCE          32749
#define OBM_ZOOM            32748
#define OBM_RESTORE         32747
#define OBM_REDUCED         32746
#define OBM_ZOOMD           32745
#define OBM_RESTORED        32744
#define OBM_UPARROWD        32743
#define OBM_DNARROWD        32742
#define OBM_RGARROWD        32741
#define OBM_LFARROWD        32740
#define OBM_MNARROW         32739
#define OBM_COMBO           32738
#define OBM_UPARROWI        32737
#define OBM_DNARROWI        32736
#define OBM_RGARROWI        32735
#define OBM_LFARROWI        32734
#define OBM_OLD_CLOSE       32767
#define OBM_SIZE            32766
#define OBM_OLD_UPARROW     32765
#define OBM_OLD_DNARROW     32764
#define OBM_OLD_RGARROW     32763
#define OBM_OLD_LFARROW     32762
#define OBM_BTSIZE          32761
#define OBM_CHECK           32760
#define OBM_CHECKBOXES      32759
#define OBM_BTNCORNERS      32758
#define OBM_OLD_REDUCE      32757
#define OBM_OLD_ZOOM        32756
#define OBM_OLD_RESTORE     32755
#define OCR_NORMAL          32512
#define OCR_IBEAM           32513
#define OCR_WAIT            32514
#define OCR_CROSS           32515
#define OCR_UP              32516
#define OCR_SIZE            32640   /* OBSOLETE: use OCR_SIZEALL */
#define OCR_ICON            32641   /* OBSOLETE: use OCR_NORMAL */
#define OCR_SIZENWSE        32642
#define OCR_SIZENESW        32643
#define OCR_SIZEWE          32644
#define OCR_SIZENS          32645
#define OCR_SIZEALL         32646
#define OCR_ICOCUR          32647   /* OBSOLETE: use OIC_WINLOGO */
#define OCR_NO              32648
#define OCR_HAND            32649
#define OCR_APPSTARTING     32650

#define OIC_SAMPLE          32512
#define OIC_HAND            32513
#define OIC_QUES            32514
#define OIC_BANG            32515
#define OIC_NOTE            32516
#define OIC_WINLOGO         32517
#define OIC_WARNING         OIC_BANG
#define OIC_ERROR           OIC_HAND
#define OIC_INFORMATION     OIC_NOTE

#endif /* OEMRESOURCE */

#define ORD_LANGDRIVER    1     /* The ordinal number for the entry point of
                                ** language drivers.
                                */
#ifndef NOICONS

/*
 * Standard Icon IDs
 */
#ifdef RC_INVOKED
#define IDI_APPLICATION     32512
#define IDI_HAND            32513
#define IDI_QUESTION        32514
#define IDI_EXCLAMATION     32515
#define IDI_ASTERISK        32516
#define IDI_WINLOGO         32517
#else
#define IDI_APPLICATION     32512
#define IDI_HAND            32513
#define IDI_QUESTION        32514
#define IDI_EXCLAMATION     32515
#define IDI_ASTERISK        32516
#define IDI_WINLOGO         32517
#endif /* RC_INVOKED */

#define IDI_WARNING     IDI_EXCLAMATION
#define IDI_ERROR       IDI_HAND
#define IDI_INFORMATION IDI_ASTERISK

#endif /* !NOICONS */

	int LoadStringA(HINSTANCE hInstance,UINT uID,LPSTR lpBuffer,int nBufferMax);
	int LoadStringW(HINSTANCE hInstance,UINT uID,LPWSTR lpBuffer,int nBufferMax);
#ifdef UNICODE
#define LoadString  LoadStringW
#else
#define LoadString  LoadStringA
#endif // !UNICODE

/*
 * Dialog Box Command IDs
 */
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7
#define IDCLOSE         8
#define IDHELP          9
#define IDTRYAGAIN      10
#define IDCONTINUE      11

#ifndef IDTIMEOUT
#define IDTIMEOUT 32000
#endif

#ifndef NOCTLMGR

/*
 * Control Manager Structures and Definitions
 */
#ifndef NOWINSTYLES

/*
 * Edit Control Styles
 */
#define ES_LEFT             0x0000L
#define ES_CENTER           0x0001L
#define ES_RIGHT            0x0002L
#define ES_MULTILINE        0x0004L
#define ES_UPPERCASE        0x0008L
#define ES_LOWERCASE        0x0010L
#define ES_PASSWORD         0x0020L
#define ES_AUTOVSCROLL      0x0040L
#define ES_AUTOHSCROLL      0x0080L
#define ES_NOHIDESEL        0x0100L
#define ES_OEMCONVERT       0x0400L
#define ES_READONLY         0x0800L
#define ES_WANTRETURN       0x1000L
#define ES_NUMBER           0x2000L

#endif /* !NOWINSTYLES */

/*
 * Edit Control Notification Codes
 */
#define EN_SETFOCUS         0x0100
#define EN_KILLFOCUS        0x0200
#define EN_CHANGE           0x0300
#define EN_UPDATE           0x0400
#define EN_ERRSPACE         0x0500
#define EN_MAXTEXT          0x0501
#define EN_HSCROLL          0x0601
#define EN_VSCROLL          0x0602

#define EN_ALIGN_LTR_EC     0x0700
#define EN_ALIGN_RTL_EC     0x0701

/* Edit control EM_SETMARGIN parameters */
#define EC_LEFTMARGIN       0x0001
#define EC_RIGHTMARGIN      0x0002
#define EC_USEFONTINFO      0xffff

/* wParam of EM_GET/SETIMESTATUS  */
#define EMSIS_COMPOSITIONSTRING        0x0001

/* lParam for EMSIS_COMPOSITIONSTRING  */
#define EIMES_GETCOMPSTRATONCE         0x0001
#define EIMES_CANCELCOMPSTRINFOCUS     0x0002
#define EIMES_COMPLETECOMPSTRKILLFOCUS 0x0004

#ifndef NOWINMESSAGES

/*
 * Edit Control Messages
 */
#define EM_GETSEL               0x00B0
#define EM_SETSEL               0x00B1
#define EM_GETRECT              0x00B2
#define EM_SETRECT              0x00B3
#define EM_SETRECTNP            0x00B4
#define EM_SCROLL               0x00B5
#define EM_LINESCROLL           0x00B6
#define EM_SCROLLCARET          0x00B7
#define EM_GETMODIFY            0x00B8
#define EM_SETMODIFY            0x00B9
#define EM_GETLINECOUNT         0x00BA
#define EM_LINEINDEX            0x00BB
#define EM_SETHANDLE            0x00BC
#define EM_GETHANDLE            0x00BD
#define EM_GETTHUMB             0x00BE
#define EM_LINELENGTH           0x00C1
#define EM_REPLACESEL           0x00C2
#define EM_GETLINE              0x00C4
#define EM_LIMITTEXT            0x00C5
#define EM_CANUNDO              0x00C6
#define EM_UNDO                 0x00C7
#define EM_FMTLINES             0x00C8
#define EM_LINEFROMCHAR         0x00C9
#define EM_SETTABSTOPS          0x00CB
#define EM_SETPASSWORDCHAR      0x00CC
#define EM_EMPTYUNDOBUFFER      0x00CD
#define EM_GETFIRSTVISIBLELINE  0x00CE
#define EM_SETREADONLY          0x00CF
#define EM_SETWORDBREAKPROC     0x00D0
#define EM_GETWORDBREAKPROC     0x00D1
#define EM_GETPASSWORDCHAR      0x00D2
#define EM_SETMARGINS           0x00D3
#define EM_GETMARGINS           0x00D4
#define EM_SETLIMITTEXT         EM_LIMITTEXT   /* ;win40 Name change */
#define EM_GETLIMITTEXT         0x00D5
#define EM_POSFROMCHAR          0x00D6
#define EM_CHARFROMPOS          0x00D7
#define EM_SETIMESTATUS         0x00D8
#define EM_GETIMESTATUS         0x00D9

#endif /* !NOWINMESSAGES */

/*
 * EDITWORDBREAKPROC code values
 */
#define WB_LEFT            0
#define WB_RIGHT           1
#define WB_ISDELIMITER     2

/*
 * Button Control Styles
 */
#define BS_PUSHBUTTON       0x00000000L
#define BS_DEFPUSHBUTTON    0x00000001L
#define BS_CHECKBOX         0x00000002L
#define BS_AUTOCHECKBOX     0x00000003L
#define BS_RADIOBUTTON      0x00000004L
#define BS_3STATE           0x00000005L
#define BS_AUTO3STATE       0x00000006L
#define BS_GROUPBOX         0x00000007L
#define BS_USERBUTTON       0x00000008L
#define BS_AUTORADIOBUTTON  0x00000009L
#define BS_OWNERDRAW        0x0000000BL
#define BS_LEFTTEXT         0x00000020L
#define BS_TEXT             0x00000000L
#define BS_ICON             0x00000040L
#define BS_BITMAP           0x00000080L
#define BS_LEFT             0x00000100L
#define BS_RIGHT            0x00000200L
#define BS_CENTER           0x00000300L
#define BS_TOP              0x00000400L
#define BS_BOTTOM           0x00000800L
#define BS_VCENTER          0x00000C00L
#define BS_PUSHLIKE         0x00001000L
#define BS_MULTILINE        0x00002000L
#define BS_NOTIFY           0x00004000L
#define BS_FLAT             0x00008000L
#define BS_RIGHTBUTTON      BS_LEFTTEXT

/*
 * User Button Notification Codes
 */
#define BN_CLICKED          0
#define BN_PAINT            1
#define BN_HILITE           2
#define BN_UNHILITE         3
#define BN_DISABLE          4
#define BN_DOUBLECLICKED    5
#define BN_PUSHED           BN_HILITE
#define BN_UNPUSHED         BN_UNHILITE
#define BN_DBLCLK           BN_DOUBLECLICKED
#define BN_SETFOCUS         6
#define BN_KILLFOCUS        7

/*
 * Button Control Messages
 */
#define BM_GETCHECK        0x00F0
#define BM_SETCHECK        0x00F1
#define BM_GETSTATE        0x00F2
#define BM_SETSTATE        0x00F3
#define BM_SETSTYLE        0x00F4
#define BM_CLICK           0x00F5
#define BM_GETIMAGE        0x00F6
#define BM_SETIMAGE        0x00F7
#define BST_UNCHECKED      0x0000
#define BST_CHECKED        0x0001
#define BST_INDETERMINATE  0x0002
#define BST_PUSHED         0x0004
#define BST_FOCUS          0x0008

/*
 * Static Control Constants
 */
#define SS_LEFT             0x00000000L
#define SS_CENTER           0x00000001L
#define SS_RIGHT            0x00000002L
#define SS_ICON             0x00000003L
#define SS_BLACKRECT        0x00000004L
#define SS_GRAYRECT         0x00000005L
#define SS_WHITERECT        0x00000006L
#define SS_BLACKFRAME       0x00000007L
#define SS_GRAYFRAME        0x00000008L
#define SS_WHITEFRAME       0x00000009L
#define SS_USERITEM         0x0000000AL
#define SS_SIMPLE           0x0000000BL
#define SS_LEFTNOWORDWRAP   0x0000000CL
#define SS_OWNERDRAW        0x0000000DL
#define SS_BITMAP           0x0000000EL
#define SS_ENHMETAFILE      0x0000000FL
#define SS_ETCHEDHORZ       0x00000010L
#define SS_ETCHEDVERT       0x00000011L
#define SS_ETCHEDFRAME      0x00000012L
#define SS_TYPEMASK         0x0000001FL
#define SS_REALSIZECONTROL  0x00000040L
#define SS_NOPREFIX         0x00000080L /* Don't do "&" character translation */
#define SS_NOTIFY           0x00000100L
#define SS_CENTERIMAGE      0x00000200L
#define SS_RIGHTJUST        0x00000400L
#define SS_REALSIZEIMAGE    0x00000800L
#define SS_SUNKEN           0x00001000L
#define SS_ENDELLIPSIS      0x00004000L
#define SS_PATHELLIPSIS     0x00008000L
#define SS_WORDELLIPSIS     0x0000C000L
#define SS_ELLIPSISMASK     0x0000C000L

#ifndef NOWINMESSAGES
/*
 * Static Control Mesages
 */
#define STM_SETICON         0x0170
#define STM_GETICON         0x0171
#define STM_SETIMAGE        0x0172
#define STM_GETIMAGE        0x0173
#define STN_CLICKED         0
#define STN_DBLCLK          1
#define STN_ENABLE          2
#define STN_DISABLE         3
#define STM_MSGMAX          0x0174
#endif /* !NOWINMESSAGES */

/*
 * Dialog window class
 */
#define WC_DIALOG       MAKEINTATOM(0x8002)

/*
 * Get/SetWindowWord/Long offsets for use with WC_DIALOG windows
 */
#define DWL_MSGRESULT   0
#define DWL_DLGPROC     4
#define DWL_USER        8

#define DWLP_MSGRESULT  0
#define DWLP_DLGPROC    DWLP_MSGRESULT + sizeof(LRESULT)
#define DWLP_USER       DWLP_DLGPROC + sizeof(dword)

/*
 * Dialog Manager Routines
 */

#ifndef NOMSG

	BOOL IsDialogMessageA(dword hDlg,dword lpMsg);
	BOOL IsDialogMessageW(dword hDlg,dword lpMsg);
#ifdef UNICODE
#define IsDialogMessage  IsDialogMessageW
#else
#define IsDialogMessage  IsDialogMessageA
#endif // !UNICODE

#endif /* !NOMSG */

	BOOL MapDialogRect(dword hDlg,dword lpRect);
	int DlgDirListA(dword hDlg,LPSTR lpPathSpec,int nIDListBox,int nIDStaticPath,UINT uFileType);
	int DlgDirListW(dword hDlg,LPWSTR lpPathSpec,int nIDListBox,int nIDStaticPath,UINT uFileType);
#ifdef UNICODE
#define DlgDirList  DlgDirListW
#else
#define DlgDirList  DlgDirListA
#endif // !UNICODE

/*
 * DlgDirList, DlgDirListComboBox flags values
 */
#define DDL_READWRITE       0x0000
#define DDL_READONLY        0x0001
#define DDL_HIDDEN          0x0002
#define DDL_SYSTEM          0x0004
#define DDL_DIRECTORY       0x0010
#define DDL_ARCHIVE         0x0020
#define DDL_POSTMSGS        0x2000
#define DDL_DRIVES          0x4000
#define DDL_EXCLUSIVE       0x8000

	BOOL DlgDirSelectExA(dword hDlg,LPSTR lpString,int nCount,int nIDListBox);
	BOOL DlgDirSelectExW(dword hDlg,LPWSTR lpString,int nCount,int nIDListBox);
#ifdef UNICODE
#define DlgDirSelectEx  DlgDirSelectExW
#else
#define DlgDirSelectEx  DlgDirSelectExA
#endif // !UNICODE

	int DlgDirListComboBoxA(dword hDlg,LPSTR lpPathSpec,int nIDComboBox,int nIDStaticPath,UINT uFiletype);
	int DlgDirListComboBoxW(dword hDlg,LPWSTR lpPathSpec,int nIDComboBox,int nIDStaticPath,UINT uFiletype);
#ifdef UNICODE
#define DlgDirListComboBox  DlgDirListComboBoxW
#else
#define DlgDirListComboBox  DlgDirListComboBoxA
#endif // !UNICODE

	BOOL DlgDirSelectComboBoxExA(dword hDlg,LPSTR lpString,int nCount,int nIDComboBox);
	BOOL DlgDirSelectComboBoxExW(dword hDlg,LPWSTR lpString,int nCount,int nIDComboBox);
#ifdef UNICODE
#define DlgDirSelectComboBoxEx  DlgDirSelectComboBoxExW
#else
#define DlgDirSelectComboBoxEx  DlgDirSelectComboBoxExA
#endif // !UNICODE
}
/*
 * Dialog Styles
 */
#define DS_ABSALIGN         0x01L
#define DS_SYSMODAL         0x02L
#define DS_LOCALEDIT        0x20L   /* Edit items get Local storage. */
#define DS_SETFONT          0x40L   /* User specified font for Dlg controls */
#define DS_MODALFRAME       0x80L   /* Can be combined with WS_CAPTION  */
#define DS_NOIDLEMSG        0x100L  /* WM_ENTERIDLE message will not be sent */
#define DS_SETFOREGROUND    0x200L  /* not in win3.1 */

#define DS_3DLOOK           0x0004L
#define DS_FIXEDSYS         0x0008L
#define DS_NOFAILCREATE     0x0010L
#define DS_CONTROL          0x0400L
#define DS_CENTER           0x0800L
#define DS_CENTERMOUSE      0x1000L
#define DS_CONTEXTHELP      0x2000L
#define DS_SHELLFONT        DS_SETFONT|DS_FIXEDSYS

#define DM_GETDEFID         WM_USER+0
#define DM_SETDEFID         WM_USER+1
#define DM_REPOSITION       WM_USER+2
/*
 * Returned in HIWORD() of DM_GETDEFID result if msg is supported
 */
#define DC_HASDEFID         0x534B

/*
 * Dialog Codes
 */
#define DLGC_WANTARROWS     0x0001      /* Control wants arrow keys         */
#define DLGC_WANTTAB        0x0002      /* Control wants tab keys           */
#define DLGC_WANTALLKEYS    0x0004      /* Control wants all keys           */
#define DLGC_WANTMESSAGE    0x0004      /* Pass message to control          */
#define DLGC_HASSETSEL      0x0008      /* Understands EM_SETSEL message    */
#define DLGC_DEFPUSHBUTTON  0x0010      /* Default pushbutton               */
#define DLGC_UNDEFPUSHBUTTON 0x0020     /* Non-default pushbutton           */
#define DLGC_RADIOBUTTON    0x0040      /* Radio button                     */
#define DLGC_WANTCHARS      0x0080      /* Want WM_CHAR messages            */
#define DLGC_STATIC         0x0100      /* Static item: don't include       */
#define DLGC_BUTTON         0x2000      /* Button item: can be checked      */
#define LB_CTLCODE          0L

/*
 * Listbox Return Values
 */
#define LB_OKAY             0
#define LB_ERR              -1
#define LB_ERRSPACE         -2

/*
**  The idStaticPath parameter to DlgDirList can have the following values
**  ORed if the list box should show other details of the files along with
**  the name of the files;
*/
                                  /* all other details also will be returned */

/*
 * Listbox Notification Codes
 */
#define LBN_ERRSPACE        -2
#define LBN_SELCHANGE       1
#define LBN_DBLCLK          2
#define LBN_SELCANCEL       3
#define LBN_SETFOCUS        4
#define LBN_KILLFOCUS       5

#ifndef NOWINMESSAGES

/*
 * Listbox messages
 */
#define LB_ADDSTRING            0x0180
#define LB_INSERTSTRING         0x0181
#define LB_DELETESTRING         0x0182
#define LB_SELITEMRANGEEX       0x0183
#define LB_RESETCONTENT         0x0184
#define LB_SETSEL               0x0185
#define LB_SETCURSEL            0x0186
#define LB_GETSEL               0x0187
#define LB_GETCURSEL            0x0188
#define LB_GETTEXT              0x0189
#define LB_GETTEXTLEN           0x018A
#define LB_GETCOUNT             0x018B
#define LB_SELECTSTRING         0x018C
#define LB_DIR                  0x018D
#define LB_GETTOPINDEX          0x018E
#define LB_FINDSTRING           0x018F
#define LB_GETSELCOUNT          0x0190
#define LB_GETSELITEMS          0x0191
#define LB_SETTABSTOPS          0x0192
#define LB_GETHORIZONTALEXTENT  0x0193
#define LB_SETHORIZONTALEXTENT  0x0194
#define LB_SETCOLUMNWIDTH       0x0195
#define LB_ADDFILE              0x0196
#define LB_SETTOPINDEX          0x0197
#define LB_GETITEMRECT          0x0198
#define LB_GETITEMDATA          0x0199
#define LB_SETITEMDATA          0x019A
#define LB_SELITEMRANGE         0x019B
#define LB_SETANCHORINDEX       0x019C
#define LB_GETANCHORINDEX       0x019D
#define LB_SETCARETINDEX        0x019E
#define LB_GETCARETINDEX        0x019F
#define LB_SETITEMHEIGHT        0x01A0
#define LB_GETITEMHEIGHT        0x01A1
#define LB_FINDSTRINGEXACT      0x01A2
#define LB_SETLOCALE            0x01A5
#define LB_GETLOCALE            0x01A6
#define LB_SETCOUNT             0x01A7
#define LB_INITSTORAGE          0x01A8
#define LB_ITEMFROMPOINT        0x01A9
#if(_WIN32_WCE >= 0x0400)
#define LB_MULTIPLEADDSTRING    0x01B1
#endif
#define LB_GETLISTBOXINFO       0x01B2

#if(_WIN32_WINNT >= 0x0501)
#define LB_MSGMAX               0x01B3
#elif(_WIN32_WCE >= 0x0400)
#define LB_MSGMAX               0x01B1
#elif(WINVER >= 0x0400)
#define LB_MSGMAX               0x01B0
#else
#define LB_MSGMAX               0x01A8
#endif

#endif /* !NOWINMESSAGES */

#ifndef NOWINSTYLES

/*
 * Listbox Styles
 */
#define LBS_NOTIFY            0x0001L
#define LBS_SORT              0x0002L
#define LBS_NOREDRAW          0x0004L
#define LBS_MULTIPLESEL       0x0008L
#define LBS_OWNERDRAWFIXED    0x0010L
#define LBS_OWNERDRAWVARIABLE 0x0020L
#define LBS_HASSTRINGS        0x0040L
#define LBS_USETABSTOPS       0x0080L
#define LBS_NOINTEGRALHEIGHT  0x0100L
#define LBS_MULTICOLUMN       0x0200L
#define LBS_WANTKEYBOARDINPUT 0x0400L
#define LBS_EXTENDEDSEL       0x0800L
#define LBS_DISABLENOSCROLL   0x1000L
#define LBS_NODATA            0x2000L
#define LBS_NOSEL             0x4000L
#define LBS_STANDARD          LBS_NOTIFY|LBS_SORT|WS_VSCROLL|WS_BORDER

#endif /* !NOWINSTYLES */

/*
 * Combo Box return Values
 */
#define CB_OKAY             0
#define CB_ERR              -1
#define CB_ERRSPACE         -2

/*
 * Combo Box Notification Codes
 */
#define CBN_ERRSPACE        -1
#define CBN_SELCHANGE       1
#define CBN_DBLCLK          2
#define CBN_SETFOCUS        3
#define CBN_KILLFOCUS       4
#define CBN_EDITCHANGE      5
#define CBN_EDITUPDATE      6
#define CBN_DROPDOWN        7
#define CBN_CLOSEUP         8
#define CBN_SELENDOK        9
#define CBN_SELENDCANCEL    10

#ifndef NOWINSTYLES

/*
 * Combo Box styles
 */
#define CBS_SIMPLE            0x0001L
#define CBS_DROPDOWN          0x0002L
#define CBS_DROPDOWNLIST      0x0003L
#define CBS_OWNERDRAWFIXED    0x0010L
#define CBS_OWNERDRAWVARIABLE 0x0020L
#define CBS_AUTOHSCROLL       0x0040L
#define CBS_OEMCONVERT        0x0080L
#define CBS_SORT              0x0100L
#define CBS_HASSTRINGS        0x0200L
#define CBS_NOINTEGRALHEIGHT  0x0400L
#define CBS_DISABLENOSCROLL   0x0800L
#define CBS_UPPERCASE           0x2000L
#define CBS_LOWERCASE           0x4000L

#endif  /* !NOWINSTYLES */

/*
 * Combo Box messages
 */
#ifndef NOWINMESSAGES
#define CB_GETEDITSEL               0x0140
#define CB_LIMITTEXT                0x0141
#define CB_SETEDITSEL               0x0142
#define CB_ADDSTRING                0x0143
#define CB_DELETESTRING             0x0144
#define CB_DIR                      0x0145
#define CB_GETCOUNT                 0x0146
#define CB_GETCURSEL                0x0147
#define CB_GETLBTEXT                0x0148
#define CB_GETLBTEXTLEN             0x0149
#define CB_INSERTSTRING             0x014A
#define CB_RESETCONTENT             0x014B
#define CB_FINDSTRING               0x014C
#define CB_SELECTSTRING             0x014D
#define CB_SETCURSEL                0x014E
#define CB_SHOWDROPDOWN             0x014F
#define CB_GETITEMDATA              0x0150
#define CB_SETITEMDATA              0x0151
#define CB_GETDROPPEDCONTROLRECT    0x0152
#define CB_SETITEMHEIGHT            0x0153
#define CB_GETITEMHEIGHT            0x0154
#define CB_SETEXTENDEDUI            0x0155
#define CB_GETEXTENDEDUI            0x0156
#define CB_GETDROPPEDSTATE          0x0157
#define CB_FINDSTRINGEXACT          0x0158
#define CB_SETLOCALE                0x0159
#define CB_GETLOCALE                0x015A
#define CB_GETTOPINDEX              0x015b
#define CB_SETTOPINDEX              0x015c
#define CB_GETHORIZONTALEXTENT      0x015d
#define CB_SETHORIZONTALEXTENT      0x015e
#define CB_GETDROPPEDWIDTH          0x015f
#define CB_SETDROPPEDWIDTH          0x0160
#define CB_INITSTORAGE              0x0161
#if(_WIN32_WCE >= 0x0400)
#define CB_MULTIPLEADDSTRING        0x0163
#endif
#define CB_GETCOMBOBOXINFO          0x0164
#if(_WIN32_WINNT >= 0x0501)
#define CB_MSGMAX                   0x0165
#elif(_WIN32_WCE >= 0x0400)
#define CB_MSGMAX                   0x0163
#elif(WINVER >= 0x0400)
#define CB_MSGMAX                   0x0162
#else
#define CB_MSGMAX                   0x015B
#endif
#endif  /* !NOWINMESSAGES */

#ifndef NOWINSTYLES

/*
 * Scroll Bar Styles
 */
#define SBS_HORZ                    0x0000L
#define SBS_VERT                    0x0001L
#define SBS_TOPALIGN                0x0002L
#define SBS_LEFTALIGN               0x0002L
#define SBS_BOTTOMALIGN             0x0004L
#define SBS_RIGHTALIGN              0x0004L
#define SBS_SIZEBOXTOPLEFTALIGN     0x0002L
#define SBS_SIZEBOXBOTTOMRIGHTALIGN 0x0004L
#define SBS_SIZEBOX                 0x0008L
#define SBS_SIZEGRIP                0x0010L

#endif /* !NOWINSTYLES */

/*
 * Scroll bar messages
 */
#ifndef NOWINMESSAGES
#define SBM_SETPOS                  0x00E0 /*not in win3.1 */
#define SBM_GETPOS                  0x00E1 /*not in win3.1 */
#define SBM_SETRANGE                0x00E2 /*not in win3.1 */
#define SBM_SETRANGEREDRAW          0x00E6 /*not in win3.1 */
#define SBM_GETRANGE                0x00E3 /*not in win3.1 */
#define SBM_ENABLE_ARROWS           0x00E4 /*not in win3.1 */
#define SBM_SETSCROLLINFO           0x00E9
#define SBM_GETSCROLLINFO           0x00EA
#define SBM_GETSCROLLBARINFO        0x00EB

#define SIF_RANGE           0x0001
#define SIF_PAGE            0x0002
#define SIF_POS             0x0004
#define SIF_DISABLENOSCROLL 0x0008
#define SIF_TRACKPOS        0x0010
#define SIF_ALL             SIF_RANGE|SIF_PAGE|SIF_POS|SIF_TRACKPOS

struct SCROLLINFO
{
  UINT    cbSize;
  UINT    fMask;
  int     nMin;
  int     nMax;
  UINT    nPage;
  int     nPos;
  int     nTrackPos;
};

extern WINAPI "user32.dll"{
	int SetScrollInfo(dword,int,dword,BOOL);
	BOOL GetScrollInfo(dword,int,dword);
}
#endif /* !NOWINMESSAGES */
#endif /* !NOCTLMGR */

#ifndef NOMDI

/*
 * MDI client style bits
 */
#define MDIS_ALLCHILDSTYLES    0x0001

/*
 * wParam Flags for WM_MDITILE and WM_MDICASCADE messages.
 */
#define MDITILE_VERTICAL       0x0000 /*not in win3.1 */
#define MDITILE_HORIZONTAL     0x0001 /*not in win3.1 */
#define MDITILE_SKIPDISABLED   0x0002 /*not in win3.1 */
#define MDITILE_ZORDER         0x0004

struct MDICREATESTRUCT{
  LPCSTR   szClass;
  LPCSTR   szTitle;
  HANDLE hOwner;
  int x;
  int y;
  int cx;
  int cy;
  DWORD style;
  LPARAM lParam;        /* app-defined stuff */
};
#define MDICREATESTRUCTW MDICREATESTRUCT
#define MDICREATESTRUCTA MDICREATESTRUCT

struct CLIENTCREATESTRUCT {
  HANDLE hWindowMenu;
  UINT idFirstChild;
};

extern WINAPI "user32.dll"{
	dword DefFrameProcA(dword hWnd,dword hWndMDIClient,UINT uMsg,WPARAM wParam,LPARAM lParam);
	dword DefFrameProcW(dword hWnd,dword hWndMDIClient,UINT uMsg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define DefFrameProc  DefFrameProcW
#else
#define DefFrameProc  DefFrameProcA
#endif // !UNICODE

	dword DefMDIChildProcA(dword hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	dword DefMDIChildProcW(dword hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
#ifdef UNICODE
#define DefMDIChildProc  DefMDIChildProcW
#else
#define DefMDIChildProc  DefMDIChildProcA
#endif // !UNICODE

#ifndef NOMSG
	BOOL TranslateMDISysAccel(dword hWndClient,dword lpMsg);
#endif /* !NOMSG */

	UINT ArrangeIconicWindows(dword hWnd);
	dword CreateMDIWindowA(LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,
		int X,int Y,int nWidth,int nHeight,dword hWndParent,HINSTANCE hInstance,LPARAM lParam);
	dword CreateMDIWindowW(LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,
		int X,int Y,int nWidth,int nHeight,dword hWndParent,HINSTANCE hInstance,LPARAM lParam);
#ifdef UNICODE
#define CreateMDIWindow  CreateMDIWindowW
#else
#define CreateMDIWindow  CreateMDIWindowA
#endif // !UNICODE

	WORDTileWindows(dword hwndParent,UINT wHow,dword lpRect,UINT cKids,dword lpKids);
	WORDCascadeWindows(dword hwndParent,UINT wHow,dword lpRect,UINT cKids,dword lpKids);
#endif /* !NOMDI */
}
#endif /* !NOUSER */

/****** Help support ********************************************************/

#ifndef NOHELP

#define HELPPOLY dword
struct MULTIKEYHELPA {
#ifndef _MAC
  DWORD  mkSize;
#else
  WORD   mkSize;
#endif
  CHAR   mkKeylist;
  CHAR   szKeyphrase[1];
};
struct MULTIKEYHELPW {
#ifndef _MAC
  DWORD  mkSize;
#else
  WORD   mkSize;
#endif
  WCHAR  mkKeylist;
  WCHAR  szKeyphrase[1];
};
#ifdef UNICODE
#define MULTIKEYHELP MULTIKEYHELPW
#else
#define MULTIKEYHELP MULTIKEYHELPA
#endif // UNICODE

struct HELPWININFOA {
  int  wStructSize;
  int  x;
  int  y;
  int  dx;
  int  dy;
  int  wMax;
  CHAR   rgchMember[2];
};
struct HELPWININFOW {
  int  wStructSize;
  int  x;
  int  y;
  int  dx;
  int  dy;
  int  wMax;
  WCHAR  rgchMember[2];
};
#ifdef UNICODE
#define HELPWININFO HELPWININFOW
#else
#define HELPWININFO HELPWININFOA
#endif // UNICODE

/*
 * Commands to pass to WinHelp()
 */
#define HELP_CONTEXT      0x0001L  /* Display topic in ulTopic */
#define HELP_QUIT         0x0002L  /* Terminate help */
#define HELP_INDEX        0x0003L  /* Display index */
#define HELP_CONTENTS     0x0003L
#define HELP_HELPONHELP   0x0004L  /* Display help on using help */
#define HELP_SETINDEX     0x0005L  /* Set current Index for multi index help */
#define HELP_SETCONTENTS  0x0005L
#define HELP_CONTEXTPOPUP 0x0008L
#define HELP_FORCEFILE    0x0009L
#define HELP_KEY          0x0101L  /* Display topic for keyword in offabData */
#define HELP_COMMAND      0x0102L
#define HELP_PARTIALKEY   0x0105L
#define HELP_MULTIKEY     0x0201L
#define HELP_SETWINPOS    0x0203L
#define HELP_CONTEXTMENU  0x000a
#define HELP_FINDER       0x000b
#define HELP_WM_HELP      0x000c
#define HELP_SETPOPUP_POS 0x000d
#define HELP_TCARD              0x8000
#define HELP_TCARD_DATA         0x0010
#define HELP_TCARD_OTHER_CALLER 0x0011

// These are in winhelp.h in Win95.
#define IDH_NO_HELP                     28440
#define IDH_MISSING_CONTEXT             28441 // Control doesn't have matching help context
#define IDH_GENERIC_HELP_BUTTON         28442 // Property sheet help button
#define IDH_OK                          28443
#define IDH_CANCEL                      28444
#define IDH_HELP                        28445

extern WINAPI "user32.dll"{
	BOOL WinHelpA(dword hWndMain,LPCSTR lpszHelp,UINT uCommand,ULONG_PTR dwData);
	BOOL WinHelpW(dword hWndMain,LPCWSTR lpszHelp,UINT uCommand,ULONG_PTR dwData);
#ifdef UNICODE
#define WinHelp  WinHelpW
#else
#define WinHelp  WinHelpA
#endif // !UNICODE
}
#endif /* !NOHELP */

#define GR_GDIOBJECTS     0       /* Count of GDI objects */
#define GR_USEROBJECTS    1       /* Count of USER objects */

extern WINAPI "user32.dll"{
	DWORD GetGuiResources(HANDLE hProcess,DWORD uiFlags);
}

#ifndef NOSYSPARAMSINFO

/*
 * Parameter for SystemParametersInfo()
 */

#define SPI_GETBEEP                 0x0001
#define SPI_SETBEEP                 0x0002
#define SPI_GETMOUSE                0x0003
#define SPI_SETMOUSE                0x0004
#define SPI_GETBORDER               0x0005
#define SPI_SETBORDER               0x0006
#define SPI_GETKEYBOARDSPEED        0x000A
#define SPI_SETKEYBOARDSPEED        0x000B
#define SPI_LANGDRIVER              0x000C
#define SPI_ICONHORIZONTALSPACING   0x000D
#define SPI_GETSCREENSAVETIMEOUT    0x000E
#define SPI_SETSCREENSAVETIMEOUT    0x000F
#define SPI_GETSCREENSAVEACTIVE     0x0010
#define SPI_SETSCREENSAVEACTIVE     0x0011
#define SPI_GETGRIDGRANULARITY      0x0012
#define SPI_SETGRIDGRANULARITY      0x0013
#define SPI_SETDESKWALLPAPER        0x0014
#define SPI_SETDESKPATTERN          0x0015
#define SPI_GETKEYBOARDDELAY        0x0016
#define SPI_SETKEYBOARDDELAY        0x0017
#define SPI_ICONVERTICALSPACING     0x0018
#define SPI_GETICONTITLEWRAP        0x0019
#define SPI_SETICONTITLEWRAP        0x001A
#define SPI_GETMENUDROPALIGNMENT    0x001B
#define SPI_SETMENUDROPALIGNMENT    0x001C
#define SPI_SETDOUBLECLKWIDTH       0x001D
#define SPI_SETDOUBLECLKHEIGHT      0x001E
#define SPI_GETICONTITLELOGFONT     0x001F
#define SPI_SETDOUBLECLICKTIME      0x0020
#define SPI_SETMOUSEBUTTONSWAP      0x0021
#define SPI_SETICONTITLELOGFONT     0x0022
#define SPI_GETFASTTASKSWITCH       0x0023
#define SPI_SETFASTTASKSWITCH       0x0024
#define SPI_SETDRAGFULLWINDOWS      0x0025
#define SPI_GETDRAGFULLWINDOWS      0x0026
#define SPI_GETNONCLIENTMETRICS     0x0029
#define SPI_SETNONCLIENTMETRICS     0x002A
#define SPI_GETMINIMIZEDMETRICS     0x002B
#define SPI_SETMINIMIZEDMETRICS     0x002C
#define SPI_GETICONMETRICS          0x002D
#define SPI_SETICONMETRICS          0x002E
#define SPI_SETWORKAREA             0x002F
#define SPI_GETWORKAREA             0x0030
#define SPI_SETPENWINDOWS           0x0031
#define SPI_GETHIGHCONTRAST         0x0042
#define SPI_SETHIGHCONTRAST         0x0043
#define SPI_GETKEYBOARDPREF         0x0044
#define SPI_SETKEYBOARDPREF         0x0045
#define SPI_GETSCREENREADER         0x0046
#define SPI_SETSCREENREADER         0x0047
#define SPI_GETANIMATION            0x0048
#define SPI_SETANIMATION            0x0049
#define SPI_GETFONTSMOOTHING        0x004A
#define SPI_SETFONTSMOOTHING        0x004B
#define SPI_SETDRAGWIDTH            0x004C
#define SPI_SETDRAGHEIGHT           0x004D
#define SPI_SETHANDHELD             0x004E
#define SPI_GETLOWPOWERTIMEOUT      0x004F
#define SPI_GETPOWEROFFTIMEOUT      0x0050
#define SPI_SETLOWPOWERTIMEOUT      0x0051
#define SPI_SETPOWEROFFTIMEOUT      0x0052
#define SPI_GETLOWPOWERACTIVE       0x0053
#define SPI_GETPOWEROFFACTIVE       0x0054
#define SPI_SETLOWPOWERACTIVE       0x0055
#define SPI_SETPOWEROFFACTIVE       0x0056
#define SPI_SETCURSORS              0x0057
#define SPI_SETICONS                0x0058
#define SPI_GETDEFAULTINPUTLANG     0x0059
#define SPI_SETDEFAULTINPUTLANG     0x005A
#define SPI_SETLANGTOGGLE           0x005B
#define SPI_GETWINDOWSEXTENSION     0x005C
#define SPI_SETMOUSETRAILS          0x005D
#define SPI_GETMOUSETRAILS          0x005E
#define SPI_SETSCREENSAVERRUNNING   0x0061
#define SPI_SCREENSAVERRUNNING     SPI_SETSCREENSAVERRUNNING
#define SPI_GETFILTERKEYS          0x0032
#define SPI_SETFILTERKEYS          0x0033
#define SPI_GETTOGGLEKEYS          0x0034
#define SPI_SETTOGGLEKEYS          0x0035
#define SPI_GETMOUSEKEYS           0x0036
#define SPI_SETMOUSEKEYS           0x0037
#define SPI_GETSHOWSOUNDS          0x0038
#define SPI_SETSHOWSOUNDS          0x0039
#define SPI_GETSTICKYKEYS          0x003A
#define SPI_SETSTICKYKEYS          0x003B
#define SPI_GETACCESSTIMEOUT       0x003C
#define SPI_SETACCESSTIMEOUT       0x003D
#define SPI_GETSERIALKEYS          0x003E
#define SPI_SETSERIALKEYS          0x003F
#define SPI_GETSOUNDSENTRY         0x0040
#define SPI_SETSOUNDSENTRY         0x0041
#define SPI_GETSNAPTODEFBUTTON     0x005F
#define SPI_SETSNAPTODEFBUTTON     0x0060
#define SPI_GETMOUSEHOVERWIDTH     0x0062
#define SPI_SETMOUSEHOVERWIDTH     0x0063
#define SPI_GETMOUSEHOVERHEIGHT    0x0064
#define SPI_SETMOUSEHOVERHEIGHT    0x0065
#define SPI_GETMOUSEHOVERTIME      0x0066
#define SPI_SETMOUSEHOVERTIME      0x0067
#define SPI_GETWHEELSCROLLLINES    0x0068
#define SPI_SETWHEELSCROLLLINES    0x0069
#define SPI_GETMENUSHOWDELAY       0x006A
#define SPI_SETMENUSHOWDELAY       0x006B
#define SPI_GETSHOWIMEUI          0x006E
#define SPI_SETSHOWIMEUI          0x006F
#define SPI_GETMOUSESPEED         0x0070
#define SPI_SETMOUSESPEED         0x0071
#define SPI_GETSCREENSAVERRUNNING 0x0072
#define SPI_GETDESKWALLPAPER      0x0073

#define SPI_GETACTIVEWINDOWTRACKING         0x1000
#define SPI_SETACTIVEWINDOWTRACKING         0x1001
#define SPI_GETMENUANIMATION                0x1002
#define SPI_SETMENUANIMATION                0x1003
#define SPI_GETCOMBOBOXANIMATION            0x1004
#define SPI_SETCOMBOBOXANIMATION            0x1005
#define SPI_GETLISTBOXSMOOTHSCROLLING       0x1006
#define SPI_SETLISTBOXSMOOTHSCROLLING       0x1007
#define SPI_GETGRADIENTCAPTIONS             0x1008
#define SPI_SETGRADIENTCAPTIONS             0x1009
#define SPI_GETKEYBOARDCUES                 0x100A
#define SPI_SETKEYBOARDCUES                 0x100B
#define SPI_GETMENUUNDERLINES               SPI_GETKEYBOARDCUES
#define SPI_SETMENUUNDERLINES               SPI_SETKEYBOARDCUES
#define SPI_GETACTIVEWNDTRKZORDER           0x100C
#define SPI_SETACTIVEWNDTRKZORDER           0x100D
#define SPI_GETHOTTRACKING                  0x100E
#define SPI_SETHOTTRACKING                  0x100F
#define SPI_GETMENUFADE                     0x1012
#define SPI_SETMENUFADE                     0x1013
#define SPI_GETSELECTIONFADE                0x1014
#define SPI_SETSELECTIONFADE                0x1015
#define SPI_GETTOOLTIPANIMATION             0x1016
#define SPI_SETTOOLTIPANIMATION             0x1017
#define SPI_GETTOOLTIPFADE                  0x1018
#define SPI_SETTOOLTIPFADE                  0x1019
#define SPI_GETCURSORSHADOW                 0x101A
#define SPI_SETCURSORSHADOW                 0x101B
#define SPI_GETMOUSESONAR                   0x101C
#define SPI_SETMOUSESONAR                   0x101D
#define SPI_GETMOUSECLICKLOCK               0x101E
#define SPI_SETMOUSECLICKLOCK               0x101F
#define SPI_GETMOUSEVANISH                  0x1020
#define SPI_SETMOUSEVANISH                  0x1021
#define SPI_GETFLATMENU                     0x1022
#define SPI_SETFLATMENU                     0x1023
#define SPI_GETDROPSHADOW                   0x1024
#define SPI_SETDROPSHADOW                   0x1025

#define SPI_GETUIEFFECTS                    0x103E
#define SPI_SETUIEFFECTS                    0x103F
#define SPI_GETFOREGROUNDLOCKTIMEOUT        0x2000
#define SPI_SETFOREGROUNDLOCKTIMEOUT        0x2001
#define SPI_GETACTIVEWNDTRKTIMEOUT          0x2002
#define SPI_SETACTIVEWNDTRKTIMEOUT          0x2003
#define SPI_GETFOREGROUNDFLASHCOUNT         0x2004
#define SPI_SETFOREGROUNDFLASHCOUNT         0x2005
#define SPI_GETCARETWIDTH                   0x2006
#define SPI_SETCARETWIDTH                   0x2007

#define SPI_GETMOUSECLICKLOCKTIME           0x2008
#define SPI_SETMOUSECLICKLOCKTIME           0x2009
#define SPI_GETFONTSMOOTHINGTYPE            0x200A
#define SPI_SETFONTSMOOTHINGTYPE            0x200B

/* constants for SPI_GETFONTSMOOTHINGTYPE and SPI_SETFONTSMOOTHINGTYPE: */
#define FE_FONTSMOOTHINGSTANDARD            0x0001
#define FE_FONTSMOOTHINGCLEARTYPE           0x0002
#define FE_FONTSMOOTHINGDOCKING             0x8000
#define SPI_GETFONTSMOOTHINGCONTRAST           0x200C
#define SPI_SETFONTSMOOTHINGCONTRAST           0x200D
#define SPI_GETFOCUSBORDERWIDTH             0x200E
#define SPI_SETFOCUSBORDERWIDTH             0x200F
#define SPI_GETFOCUSBORDERHEIGHT            0x2010
#define SPI_SETFOCUSBORDERHEIGHT            0x2011

/*
 * Flags
 */
#define SPIF_UPDATEINIFILE    0x0001
#define SPIF_SENDWININICHANGE 0x0002
#define SPIF_SENDCHANGE       SPIF_SENDWININICHANGE

#define METRICS_USEDEFAULT -1
#ifdef _WINGDI_
#ifndef NOGDI
struct NONCLIENTMETRICS
{
  UINT    cbSize;
  int     iBorderWidth;
  int     iScrollWidth;
  int     iScrollHeight;
  int     iCaptionWidth;
  int     iCaptionHeight;
  LOGFONT lfCaptionFont;
  int     iSmCaptionWidth;
  int     iSmCaptionHeight;
  LOGFONT lfSmCaptionFont;
  int     iMenuWidth;
  int     iMenuHeight;
  LOGFONT lfMenuFont;
  LOGFONT lfStatusFont;
  LOGFONT lfMessageFont;
};
#define NONCLIENTMETRICSW NONCLIENTMETRICS
#define NONCLIENTMETRICSA NONCLIENTMETRICS
#endif /* NOGDI */
#endif /* _WINGDI_ */

#define ARW_BOTTOMLEFT              0x0000L
#define ARW_BOTTOMRIGHT             0x0001L
#define ARW_TOPLEFT                 0x0002L
#define ARW_TOPRIGHT                0x0003L
#define ARW_STARTMASK               0x0003L
#define ARW_STARTRIGHT              0x0001L
#define ARW_STARTTOP                0x0002L

#define ARW_LEFT                    0x0000L
#define ARW_RIGHT                   0x0000L
#define ARW_UP                      0x0004L
#define ARW_DOWN                    0x0004L
#define ARW_HIDE                    0x0008L

struct MINIMIZEDMETRICS
{
  UINT    cbSize;
  int     iWidth;
  int     iHorzGap;
  int     iVertGap;
  int     iArrange;
};

#ifdef _WINGDI_
#ifndef NOGDI
struct ICONMETRICS
{
  UINT    cbSize;
  int     iHorzSpacing;
  int     iVertSpacing;
  int     iTitleWrap;
  LOGFONT lfFont;
};
#define ICONMETRICSW ICONMETRICS
#define ICONMETRICSA ICONMETRICS
#endif /* NOGDI */
#endif /* _WINGDI_ */

struct ANIMATIONINFO
{
  UINT    cbSize;
  int     iMinAnimate;
};

struct SERIALKEYS
{
  UINT    cbSize;
  DWORD   dwFlags;
  LPSTR     lpszActivePort;
  LPSTR     lpszPort;
  UINT    iBaudRate;
  UINT    iPortState;
  UINT    iActive;
};
#define SERIALKEYSW SERIALKEYS
#define SERIALKEYSA SERIALKEYS

/* flags for SERIALKEYS dwFlags field */
#define SERKF_SERIALKEYSON  0x00000001
#define SERKF_AVAILABLE     0x00000002
#define SERKF_INDICATOR     0x00000004

struct HIGHCONTRAST
{
  UINT    cbSize;
  DWORD   dwFlags;
  LPSTR   lpszDefaultScheme;
};
#define HIGHCONTRASTW HIGHCONTRAST
#define HIGHCONTRASTA HIGHCONTRAST

/* flags for HIGHCONTRAST dwFlags field */
#define HCF_HIGHCONTRASTON  0x00000001
#define HCF_AVAILABLE       0x00000002
#define HCF_HOTKEYACTIVE    0x00000004
#define HCF_CONFIRMHOTKEY   0x00000008
#define HCF_HOTKEYSOUND     0x00000010
#define HCF_INDICATOR       0x00000020
#define HCF_HOTKEYAVAILABLE 0x00000040

/* Flags for ChangeDisplaySettings */
#define CDS_UPDATEREGISTRY  0x00000001
#define CDS_TEST            0x00000002
#define CDS_FULLSCREEN      0x00000004
#define CDS_GLOBAL          0x00000008
#define CDS_SET_PRIMARY     0x00000010
#define CDS_VIDEOPARAMETERS 0x00000020
#define CDS_RESET           0x40000000
#define CDS_NORESET         0x10000000

//#include <tvout.h>

/* Return values for ChangeDisplaySettings */
#define DISP_CHANGE_SUCCESSFUL       0
#define DISP_CHANGE_RESTART          1
#define DISP_CHANGE_FAILED          -1
#define DISP_CHANGE_BADMODE         -2
#define DISP_CHANGE_NOTUPDATED      -3
#define DISP_CHANGE_BADFLAGS        -4
#define DISP_CHANGE_BADPARAM        -5
#define DISP_CHANGE_BADDUALVIEW     -6

extern WINAPI "user32.dll"{
#ifdef _WINGDI_
#ifndef NOGDI
	LONG ChangeDisplaySettingsA(dword lpDevMode,DWORD dwFlags);
	LONG ChangeDisplaySettingsW(dword lpDevMode,DWORD dwFlags);
#ifdef UNICODE
#define ChangeDisplaySettings  ChangeDisplaySettingsW
#else
#define ChangeDisplaySettings  ChangeDisplaySettingsA
#endif // !UNICODE

	LONG ChangeDisplaySettingsExA(LPCSTR lpszDeviceName,dword lpDevMode,dword hwnd,
		DWORD dwflags,LPVOID lParam);
	LONG ChangeDisplaySettingsExW(LPCWSTR lpszDeviceName,dword lpDevMode,dword hwnd,
		DWORD dwflags,LPVOID lParam);
#ifdef UNICODE
#define ChangeDisplaySettingsEx  ChangeDisplaySettingsExW
#else
#define ChangeDisplaySettingsEx  ChangeDisplaySettingsExA
#endif // !UNICODE

#define ENUM_CURRENT_SETTINGS       -1
#define ENUM_REGISTRY_SETTINGS      -2

	BOOL EnumDisplaySettingsA(LPCSTR lpszDeviceName,DWORD iModeNum,dword lpDevMode);
	BOOL EnumDisplaySettingsW(LPCWSTR lpszDeviceName,DWORD iModeNum,dword lpDevMode);
#ifdef UNICODE
#define EnumDisplaySettings  EnumDisplaySettingsW
#else
#define EnumDisplaySettings  EnumDisplaySettingsA
#endif // !UNICODE

	BOOL EnumDisplaySettingsExA(LPCSTR lpszDeviceName,DWORD iModeNum,dword lpDevMode,DWORD dwFlags);
	BOOL EnumDisplaySettingsExW(LPCWSTR lpszDeviceName,DWORD iModeNum,dword lpDevMode,DWORD dwFlags);
#ifdef UNICODE
#define EnumDisplaySettingsEx  EnumDisplaySettingsExW
#else
#define EnumDisplaySettingsEx  EnumDisplaySettingsExA
#endif // !UNICODE

/* Flags for EnumDisplaySettingsEx */
#define EDS_RAWMODE                   0x00000002

	BOOL EnumDisplayDevicesA(LPCSTR lpDevice,DWORD iDevNum,dword lpDisplayDevice,DWORD dwFlags);
	BOOL EnumDisplayDevicesW(LPCWSTR lpDevice,DWORD iDevNum,dword lpDisplayDevice,DWORD dwFlags);
#ifdef UNICODE
#define EnumDisplayDevices  EnumDisplayDevicesW
#else
#define EnumDisplayDevices  EnumDisplayDevicesA
#endif // !UNICODE

#endif /* NOGDI */
#endif /* _WINGDI_ */

	BOOL SystemParametersInfoA(UINT uiAction,UINT uiParam,dword pvParam,UINT fWinIni);
	BOOL SystemParametersInfoW(UINT uiAction,UINT uiParam,dword pvParam,UINT fWinIni);
#ifdef UNICODE
#define SystemParametersInfo  SystemParametersInfoW
#else
#define SystemParametersInfo  SystemParametersInfoA
#endif // !UNICODE
}
#endif  /* !NOSYSPARAMSINFO  */

/*
 * Accessibility support
 */
struct FILTERKEYS
{
  UINT  cbSize;
  DWORD dwFlags;
  DWORD iWaitMSec;            // Acceptance Delay
  DWORD iDelayMSec;           // Delay Until Repeat
  DWORD iRepeatMSec;          // Repeat Rate
  DWORD iBounceMSec;          // Debounce Time
};

/*
 * FILTERKEYS dwFlags field
 */
#define FKF_FILTERKEYSON    0x00000001
#define FKF_AVAILABLE       0x00000002
#define FKF_HOTKEYACTIVE    0x00000004
#define FKF_CONFIRMHOTKEY   0x00000008
#define FKF_HOTKEYSOUND     0x00000010
#define FKF_INDICATOR       0x00000020
#define FKF_CLICKON         0x00000040

struct STICKYKEYS
{
  UINT  cbSize;
  DWORD dwFlags;
};

/*
 * STICKYKEYS dwFlags field
 */
#define SKF_STICKYKEYSON    0x00000001
#define SKF_AVAILABLE       0x00000002
#define SKF_HOTKEYACTIVE    0x00000004
#define SKF_CONFIRMHOTKEY   0x00000008
#define SKF_HOTKEYSOUND     0x00000010
#define SKF_INDICATOR       0x00000020
#define SKF_AUDIBLEFEEDBACK 0x00000040
#define SKF_TRISTATE        0x00000080
#define SKF_TWOKEYSOFF      0x00000100
#define SKF_LALTLATCHED       0x10000000
#define SKF_LCTLLATCHED       0x04000000
#define SKF_LSHIFTLATCHED     0x01000000
#define SKF_RALTLATCHED       0x20000000
#define SKF_RCTLLATCHED       0x08000000
#define SKF_RSHIFTLATCHED     0x02000000
#define SKF_LWINLATCHED       0x40000000
#define SKF_RWINLATCHED       0x80000000
#define SKF_LALTLOCKED        0x00100000
#define SKF_LCTLLOCKED        0x00040000
#define SKF_LSHIFTLOCKED      0x00010000
#define SKF_RALTLOCKED        0x00200000
#define SKF_RCTLLOCKED        0x00080000
#define SKF_RSHIFTLOCKED      0x00020000
#define SKF_LWINLOCKED        0x00400000
#define SKF_RWINLOCKED        0x00800000

struct MOUSEKEYS
{
  UINT cbSize;
  DWORD dwFlags;
  DWORD iMaxSpeed;
  DWORD iTimeToMaxSpeed;
  DWORD iCtrlSpeed;
  DWORD dwReserved1;
  DWORD dwReserved2;
};

/*
 * MOUSEKEYS dwFlags field
 */
#define MKF_MOUSEKEYSON     0x00000001
#define MKF_AVAILABLE       0x00000002
#define MKF_HOTKEYACTIVE    0x00000004
#define MKF_CONFIRMHOTKEY   0x00000008
#define MKF_HOTKEYSOUND     0x00000010
#define MKF_INDICATOR       0x00000020
#define MKF_MODIFIERS       0x00000040
#define MKF_REPLACENUMBERS  0x00000080
#define MKF_LEFTBUTTONSEL   0x10000000
#define MKF_RIGHTBUTTONSEL  0x20000000
#define MKF_LEFTBUTTONDOWN  0x01000000
#define MKF_RIGHTBUTTONDOWN 0x02000000
#define MKF_MOUSEMODE       0x80000000

struct ACCESSTIMEOUT
{
  UINT  cbSize;
  DWORD dwFlags;
  DWORD iTimeOutMSec;
};

/*
 * ACCESSTIMEOUT dwFlags field
 */
#define ATF_TIMEOUTON       0x00000001
#define ATF_ONOFFFEEDBACK   0x00000002

/* values for SOUNDSENTRY iFSGrafEffect field */
#define SSGF_NONE       0
#define SSGF_DISPLAY    3

/* values for SOUNDSENTRY iFSTextEffect field */
#define SSTF_NONE       0
#define SSTF_CHARS      1
#define SSTF_BORDER     2
#define SSTF_DISPLAY    3

/* values for SOUNDSENTRY iWindowsEffect field */
#define SSWF_NONE     0
#define SSWF_TITLE    1
#define SSWF_WINDOW   2
#define SSWF_DISPLAY  3
#define SSWF_CUSTOM   4

struct SOUNDSENTRY
{
  UINT cbSize;
  DWORD dwFlags;
  DWORD iFSTextEffect;
  DWORD iFSTextEffectMSec;
  DWORD iFSTextEffectColorBits;
  DWORD iFSGrafEffect;
  DWORD iFSGrafEffectMSec;
  DWORD iFSGrafEffectColor;
  DWORD iWindowsEffect;
  DWORD iWindowsEffectMSec;
  LPSTR   lpszWindowsEffectDLL;
  DWORD iWindowsEffectOrdinal;
};
#define SOUNDSENTRYW SOUNDSENTRY
#define SOUNDSENTRYA SOUNDSENTRY

/*
 * SOUNDSENTRY dwFlags field
 */
#define SSF_SOUNDSENTRYON   0x00000001
#define SSF_AVAILABLE       0x00000002
#define SSF_INDICATOR       0x00000004

struct TOGGLEKEYS
{
  UINT cbSize;
  DWORD dwFlags;
};

/*
 * TOGGLEKEYS dwFlags field
 */
#define TKF_TOGGLEKEYSON    0x00000001
#define TKF_AVAILABLE       0x00000002
#define TKF_HOTKEYACTIVE    0x00000004
#define TKF_CONFIRMHOTKEY   0x00000008
#define TKF_HOTKEYSOUND     0x00000010
#define TKF_INDICATOR       0x00000020

/*
 * Set debug level
 */
#define MONITORINFOF_PRIMARY        0x00000001

#ifndef CCHDEVICENAME
#define CCHDEVICENAME 32
#endif

struct MONITORINFO
{
  DWORD   cbSize;
  RECT    rcMonitor;
  RECT    rcWork;
  DWORD   dwFlags;
};

struct MONITORINFOEXA
{
  DWORD   cbSize;
  RECT    rcMonitor;
  RECT    rcWork;
  DWORD   dwFlags;
  CHAR        szDevice[CCHDEVICENAME];
};
struct MONITORINFOEXW
{
  DWORD   cbSize;
  RECT    rcMonitor;
  RECT    rcWork;
  DWORD   dwFlags;
  WCHAR       szDevice[CCHDEVICENAME];
};
#ifdef UNICODE
#define MONITORINFOEX MONITORINFOEXW
#else
#define MONITORINFOEX MONITORINFOEXA
#endif // UNICODE

extern WINAPI "user32.dll"{
	VOID SetDebugErrorLevel(DWORD dwLevel);

/*
 * SetLastErrorEx() types.
 */
#define SLE_ERROR       0x00000001
#define SLE_MINORERROR  0x00000002
#define SLE_WARNING     0x00000003

	VOID SetLastErrorEx(DWORD dwErrCode,DWORD dwType);

/*
 * Multimonitor API.
 */
#define MONITOR_DEFAULTTONULL       0x00000000
#define MONITOR_DEFAULTTOPRIMARY    0x00000001
#define MONITOR_DEFAULTTONEAREST    0x00000002

	dword MonitorFromPoint(POINT pt,DWORD dwFlags);
	dword MonitorFromRect(dword lprc,DWORD dwFlags);
	dword MonitorFromWindow(dword hwnd,DWORD dwFlags);
	BOOL GetMonitorInfoA(HMONITOR hMonitor,dword lpmi);
	BOOL GetMonitorInfoW(HMONITOR hMonitor,dword lpmi);
#ifdef UNICODE
#define GetMonitorInfo  GetMonitorInfoW
#else
#define GetMonitorInfo  GetMonitorInfoA
#endif // !UNICODE

	BOOL EnumDisplayMonitors(HDC hdc,dword lprcClip,dword lpfnEnum,dword dwData);

#ifndef NOWINABLE

/*
 * WinEvents - Active Accessibility hooks
 */
	VOID NotifyWinEvent(DWORD event,dword hwnd,LONG idObject,LONG idChild);
	dword SetWinEventHook(DWORD eventMin,DWORD eventMax,HMODULE hmodWinEventProc,
		dword pfnWinEventProc,DWORD idProcess,DWORD idThread,DWORD dwFlags);
	BOOL IsWinEventHookInstalled(DWORD event);

/*
 * dwFlags for SetWinEventHook
 */
#define WINEVENT_OUTOFCONTEXT   0x0000  // Events are ASYNC
#define WINEVENT_SKIPOWNTHREAD  0x0001  // Don't call back for events on installer's thread
#define WINEVENT_SKIPOWNPROCESS 0x0002  // Don't call back for events on installer's process
#define WINEVENT_INCONTEXT      0x0004  // Events are SYNC, this causes your dll to be injected into every process

	BOOL UnhookWinEvent(dword hWinEventHook);
}
/*
 * idObject values for WinEventProc and NotifyWinEvent
 */

/*
 * hwnd + idObject can be used with OLEACC.DLL's OleGetObjectFromWindow()
 * to get an interface pointer to the container.  indexChild is the item
 * within the container in question.  Setup a VARIANT with vt VT_I4 and
 * lVal the indexChild and pass that in to all methods.  Then you
 * are raring to go.
 */

/*
 * Common object IDs (cookies, only for sending WM_GETOBJECT to get at the
 * thing in question).  Positive IDs are reserved for apps (app specific),
 * negative IDs are system things and are global, 0 means "just little old
 * me".
 */
#define     CHILDID_SELF        0
#define     INDEXID_OBJECT      0
#define     INDEXID_CONTAINER   0

/*
 * Reserved IDs for system objects
 */
#define     OBJID_WINDOW        0x00000000
#define     OBJID_SYSMENU       0xFFFFFFFF
#define     OBJID_TITLEBAR      0xFFFFFFFE
#define     OBJID_MENU          0xFFFFFFFD
#define     OBJID_CLIENT        0xFFFFFFFC
#define     OBJID_VSCROLL       0xFFFFFFFB
#define     OBJID_HSCROLL       0xFFFFFFFA
#define     OBJID_SIZEGRIP      0xFFFFFFF9
#define     OBJID_CARET         0xFFFFFFF8
#define     OBJID_CURSOR        0xFFFFFFF7
#define     OBJID_ALERT         0xFFFFFFF6
#define     OBJID_SOUND         0xFFFFFFF5
#define     OBJID_QUERYCLASSNAMEIDX 0xFFFFFFF4
#define     OBJID_NATIVEOM      0xFFFFFFF0

/*
 * EVENT DEFINITION
 */
#define EVENT_MIN           0x00000001
#define EVENT_MAX           0x7FFFFFFF

/*
 *  EVENT_SYSTEM_SOUND
 *  Sent when a sound is played.  Currently nothing is generating this, we
 *  this event when a system sound (for menus, etc) is played.  Apps
 *  generate this, if accessible, when a private sound is played.  For
 *  example, if Mail plays a "New Mail" sound.
 *
 *  System Sounds:
 *  (Generated by PlaySoundEvent in USER itself)
 *      hwnd            is NULL
 *      idObject        is OBJID_SOUND
 *      idChild         is sound child ID if one
 *  App Sounds:
 *  (PlaySoundEvent won't generate notification; up to app)
 *      hwnd + idObject gets interface pointer to Sound object
 *      idChild identifies the sound in question
 *  are going to be cleaning up the SOUNDSENTRY feature in the control panel
 *  and will use this at that time.  Applications implementing WinEvents
 *  are perfectly welcome to use it.  Clients of IAccessible* will simply
 *  turn around and get back a non-visual object that describes the sound.
 */
#define EVENT_SYSTEM_SOUND              0x0001

/*
 * EVENT_SYSTEM_ALERT
 * System Alerts:
 * (Generated by MessageBox() calls for example)
 *      hwnd            is hwndMessageBox
 *      idObject        is OBJID_ALERT
 * App Alerts:
 * (Generated whenever)
 *      hwnd+idObject gets interface pointer to Alert
 */
#define EVENT_SYSTEM_ALERT              0x0002

/*
 * EVENT_SYSTEM_FOREGROUND
 * Sent when the foreground (active) window changes, even if it is changing
 * to another window in the same thread as the previous one.
 *      hwnd            is hwndNewForeground
 *      idObject        is OBJID_WINDOW
 *      idChild    is INDEXID_OBJECT
 */
#define EVENT_SYSTEM_FOREGROUND         0x0003

/*
 * Menu
 *      hwnd            is window (top level window or popup menu window)
 *      idObject        is ID of control (OBJID_MENU, OBJID_SYSMENU, OBJID_SELF for popup)
 *      idChild         is CHILDID_SELF
 *
 * EVENT_SYSTEM_MENUSTART
 * EVENT_SYSTEM_MENUEND
 * For MENUSTART, hwnd+idObject+idChild refers to the control with the menu bar,
 *  or the control bringing up the context menu.
 *
 * Sent when entering into and leaving from menu mode (system, app bar, and
 * track popups).
 */
#define EVENT_SYSTEM_MENUSTART          0x0004
#define EVENT_SYSTEM_MENUEND            0x0005

/*
 * EVENT_SYSTEM_MENUPOPUPSTART
 * EVENT_SYSTEM_MENUPOPUPEND
 * Sent when a menu popup comes up and just before it is taken down.  Note
 * that for a call to TrackPopupMenu(), a client will see EVENT_SYSTEM_MENUSTART
 * followed almost immediately by EVENT_SYSTEM_MENUPOPUPSTART for the popup
 * being shown.
 *
 * For MENUPOPUP, hwnd+idObject+idChild refers to the NEW popup coming up, not the
 * parent item which is hierarchical.  You can get the parent menu/popup by
 * asking for the accParent object.
 */
#define EVENT_SYSTEM_MENUPOPUPSTART     0x0006
#define EVENT_SYSTEM_MENUPOPUPEND       0x0007

/*
 * EVENT_SYSTEM_CAPTURESTART
 * EVENT_SYSTEM_CAPTUREEND
 * Sent when a window takes the capture and releases the capture.
 */
#define EVENT_SYSTEM_CAPTURESTART       0x0008
#define EVENT_SYSTEM_CAPTUREEND         0x0009

/*
 * Move Size
 * EVENT_SYSTEM_MOVESIZESTART
 * EVENT_SYSTEM_MOVESIZEEND
 * Sent when a window enters and leaves move-size dragging mode.
 */
#define EVENT_SYSTEM_MOVESIZESTART      0x000A
#define EVENT_SYSTEM_MOVESIZEEND        0x000B

/*
 * Context Help
 * EVENT_SYSTEM_CONTEXTHELPSTART
 * EVENT_SYSTEM_CONTEXTHELPEND
 * Sent when a window enters and leaves context sensitive help mode.
 */
#define EVENT_SYSTEM_CONTEXTHELPSTART   0x000C
#define EVENT_SYSTEM_CONTEXTHELPEND     0x000D

/*
 * Drag & Drop
 * EVENT_SYSTEM_DRAGDROPSTART
 * EVENT_SYSTEM_DRAGDROPEND
 * Send the START notification just before going into drag&drop loop.  Send
 * the END notification just after canceling out.
 * Note that it is up to apps and OLE to generate this, since the system
 * doesn't know.  Like EVENT_SYSTEM_SOUND, it will be a while before this
 * is prevalent.
 */
#define EVENT_SYSTEM_DRAGDROPSTART      0x000E
#define EVENT_SYSTEM_DRAGDROPEND        0x000F

/*
 * Dialog
 * Send the START notification right after the dialog is completely
 *  initialized and visible.  Send the END right before the dialog
 *  is hidden and goes away.
 * EVENT_SYSTEM_DIALOGSTART
 * EVENT_SYSTEM_DIALOGEND
 */
#define EVENT_SYSTEM_DIALOGSTART        0x0010
#define EVENT_SYSTEM_DIALOGEND          0x0011

/*
 * EVENT_SYSTEM_SCROLLING
 * EVENT_SYSTEM_SCROLLINGSTART
 * EVENT_SYSTEM_SCROLLINGEND
 * Sent when beginning and ending the tracking of a scrollbar in a window,
 * and also for scrollbar controls.
 */
#define EVENT_SYSTEM_SCROLLINGSTART     0x0012
#define EVENT_SYSTEM_SCROLLINGEND       0x0013

/*
 * Alt-Tab Window
 * Send the START notification right after the switch window is initialized
 * and visible.  Send the END right before it is hidden and goes away.
 * EVENT_SYSTEM_SWITCHSTART
 * EVENT_SYSTEM_SWITCHEND
 */
#define EVENT_SYSTEM_SWITCHSTART        0x0014
#define EVENT_SYSTEM_SWITCHEND          0x0015

/*
 * EVENT_SYSTEM_MINIMIZESTART
 * EVENT_SYSTEM_MINIMIZEEND
 * Sent when a window minimizes and just before it restores.
 */
#define EVENT_SYSTEM_MINIMIZESTART      0x0016
#define EVENT_SYSTEM_MINIMIZEEND        0x0017

#define EVENT_CONSOLE_CARET             0x4001
#define EVENT_CONSOLE_UPDATE_REGION     0x4002
#define EVENT_CONSOLE_UPDATE_SIMPLE     0x4003
#define EVENT_CONSOLE_UPDATE_SCROLL     0x4004
#define EVENT_CONSOLE_LAYOUT            0x4005
#define EVENT_CONSOLE_START_APPLICATION 0x4006
#define EVENT_CONSOLE_END_APPLICATION   0x4007

/*
 * Flags for EVENT_CONSOLE_START/END_APPLICATION.
 */
#define CONSOLE_APPLICATION_16BIT       0x0001

/*
 * Flags for EVENT_CONSOLE_CARET
 */
#define CONSOLE_CARET_SELECTION         0x0001
#define CONSOLE_CARET_VISIBLE           0x0002

/*
 * Object events
 *
 * The system AND apps generate these.  The system generates these for
 * real windows.  Apps generate these for objects within their window which
 * act like a separate control, e.g. an item in a list view.
 *
 * When the system generate them, dwParam2 is always WMOBJID_SELF.  When
 * apps generate them, apps put the has-meaning-to-the-app-only ID value
 * in dwParam2.
 * For all events, if you want detailed accessibility information, callers
 * should
 *      * Call AccessibleObjectFromWindow() with the hwnd, idObject parameters
 *          of the event, and IID_IAccessible as the REFIID, to get back an
 *          IAccessible* to talk to
 *      * Initialize and fill in a VARIANT as VT_I4 with lVal the idChild
 *          parameter of the event.
 *      * If idChild isn't zero, call get_accChild() in the container to see
 *          if the child is an object in its own right.  If so, you will get
 *          back an IDispatch* object for the child.  You should release the
 *          parent, and call QueryInterface() on the child object to get its
 *          IAccessible*.  Then you talk directly to the child.  Otherwise,
 *          if get_accChild() returns you nothing, you should continue to
 *          use the child VARIANT.  You will ask the container for the properties
 *          of the child identified by the VARIANT.  In other words, the
 *          child in this case is accessible but not a full-blown object.
 *          Like a button on a titlebar which is 'small' and has no children.
 */

/*
 * For all EVENT_OBJECT events,
 *      hwnd is the dude to Send the WM_GETOBJECT message to (unless NULL,
 *          see above for system things)
 *      idObject is the ID of the object that can resolve any queries a
 *          client might have.  It's a way to deal with windowless controls,
 *          controls that are just drawn on the screen in some larger parent
 *          window (like SDM), or standard frame elements of a window.
 *      idChild is the piece inside of the object that is affected.  This
 *          allows clients to access things that are too small to have full
 *          blown objects in their own right.  Like the thumb of a scrollbar.
 *          The hwnd/idObject pair gets you to the container, the dude you
 *          probably want to talk to most of the time anyway.  The idChild
 *          can then be passed into the acc properties to get the name/value
 *          of it as needed.
 *
 * Example #1:
 *      System propagating a listbox selection change
 *      EVENT_OBJECT_SELECTION
 *          hwnd == listbox hwnd
 *          idObject == OBJID_WINDOW
 *          idChild == new selected item, or CHILDID_SELF if
 *              nothing now selected within container.
 *      Word '97 propagating a listbox selection change
 *          hwnd == SDM window
 *          idObject == SDM ID to get at listbox 'control'
 *          idChild == new selected item, or CHILDID_SELF if
 *              nothing
 *
 * Example #2:
 *      System propagating a menu item selection on the menu bar
 *      EVENT_OBJECT_SELECTION
 *          hwnd == top level window
 *          idObject == OBJID_MENU
 *          idChild == ID of child menu bar item selected
 *
 * Example #3:
 *      System propagating a dropdown coming off of said menu bar item
 *      EVENT_OBJECT_CREATE
 *          hwnd == popup item
 *          idObject == OBJID_WINDOW
 *          idChild == CHILDID_SELF
 *
 * Example #4:
 *
 * For EVENT_OBJECT_REORDER, the object referred to by hwnd/idObject is the
 * PARENT container in which the zorder is occurring.  This is because if
 * one child is zordering, all of them are changing their relative zorder.
 */
#define EVENT_OBJECT_CREATE                 0x8000  // hwnd + ID + idChild is created item
#define EVENT_OBJECT_DESTROY                0x8001  // hwnd + ID + idChild is destroyed item
#define EVENT_OBJECT_SHOW                   0x8002  // hwnd + ID + idChild is shown item
#define EVENT_OBJECT_HIDE                   0x8003  // hwnd + ID + idChild is hidden item
#define EVENT_OBJECT_REORDER                0x8004  // hwnd + ID + idChild is parent of zordering children
/*
 * NOTE:
 * Minimize the number of notifications!
 *
 * When you are hiding a parent object, obviously all child objects are no
 * longer visible on screen.  They still have the same "visible" status,
 * but are not truly visible.  Hence do not send HIDE notifications for the
 * children also.  One implies all.  The same goes for SHOW.
 */

#define EVENT_OBJECT_FOCUS                  0x8005  // hwnd + ID + idChild is focused item
#define EVENT_OBJECT_SELECTION              0x8006  // hwnd + ID + idChild is selected item (if only one), or idChild is OBJID_WINDOW if complex
#define EVENT_OBJECT_SELECTIONADD           0x8007  // hwnd + ID + idChild is item added
#define EVENT_OBJECT_SELECTIONREMOVE        0x8008  // hwnd + ID + idChild is item removed
#define EVENT_OBJECT_SELECTIONWITHIN        0x8009  // hwnd + ID + idChild is parent of changed selected items

/*
 * NOTES:
 * There is only one "focused" child item in a parent.  This is the place
 * keystrokes are going at a given moment.  Hence only send a notification
 * about where the NEW focus is going.  A NEW item getting the focus already
 * implies that the OLD item is losing it.
 *
 * SELECTION however can be multiple.  Hence the different SELECTION
 * notifications.  Here's when to use each:
 *
 * (1) Send a SELECTION notification in the simple single selection
 *     case (like the focus) when the item with the selection is
 *     merely moving to a different item within a container.  hwnd + ID
 *     is the container control, idChildItem is the new child with the
 *     selection.
 *
 * (2) Send a SELECTIONADD notification when a new item has simply been added
 *     to the selection within a container.  This is appropriate when the
 *     number of newly selected items is very small.  hwnd + ID is the
 *     container control, idChildItem is the new child added to the selection.
 *
 * (3) Send a SELECTIONREMOVE notification when a new item has simply been
 *     removed from the selection within a container.  This is appropriate
 *     when the number of newly selected items is very small, just like
 *     SELECTIONADD.  hwnd + ID is the container control, idChildItem is the
 *     new child removed from the selection.
 *
 * (4) Send a SELECTIONWITHIN notification when the selected items within a
 *     control have changed substantially.  Rather than propagate a large
 *     number of changes to reflect removal for some items, addition of
 *     others, just tell somebody who cares that a lot happened.  It will
 *     be faster an easier for somebody watching to just turn around and
 *     query the container control what the new bunch of selected items
 *     are.
 */

#define EVENT_OBJECT_STATECHANGE            0x800A  // hwnd + ID + idChild is item w/ state change
/*
 * Examples of when to send an EVENT_OBJECT_STATECHANGE include
 *      * It is being enabled/disabled (USER does for windows)
 *      * It is being pressed/released (USER does for buttons)
 *      * It is being checked/unchecked (USER does for radio/check buttons)
 */
#define EVENT_OBJECT_LOCATIONCHANGE         0x800B  // hwnd + ID + idChild is moved/sized item

/*
 * Note:
 * A LOCATIONCHANGE is not sent for every child object when the parent
 * changes shape/moves.  Send one notification for the topmost object
 * that is changing.  For example, if the user resizes a top level window,
 * USER will generate a LOCATIONCHANGE for it, but not for the menu bar,
 * title bar, scrollbars, etc.  that are also changing shape/moving.
 *
 * In other words, it only generates LOCATIONCHANGE notifications for
 * real windows that are moving/sizing.  It will not generate a LOCATIONCHANGE
 * for every non-floating child window when the parent moves (the children are
 * logically moving also on screen, but not relative to the parent).
 *
 * Now, if the app itself resizes child windows as a result of being
 * sized, USER will generate LOCATIONCHANGEs for those dudes also because
 * it doesn't know better.
 *
 * Note also that USER will generate LOCATIONCHANGE notifications for two
 * non-window sys objects:
 *      (1) System caret
 *      (2) Cursor
 */
#define EVENT_OBJECT_NAMECHANGE             0x800C  // hwnd + ID + idChild is item w/ name change
#define EVENT_OBJECT_DESCRIPTIONCHANGE      0x800D  // hwnd + ID + idChild is item w/ desc change
#define EVENT_OBJECT_VALUECHANGE            0x800E  // hwnd + ID + idChild is item w/ value change
#define EVENT_OBJECT_PARENTCHANGE           0x800F  // hwnd + ID + idChild is item w/ new parent
#define EVENT_OBJECT_HELPCHANGE             0x8010  // hwnd + ID + idChild is item w/ help change
#define EVENT_OBJECT_DEFACTIONCHANGE        0x8011  // hwnd + ID + idChild is item w/ def action change
#define EVENT_OBJECT_ACCELERATORCHANGE      0x8012  // hwnd + ID + idChild is item w/ keybd accel change

/*
 * Child IDs
 */

/*
 * System Sounds (idChild of system SOUND notification)
 */
#define SOUND_SYSTEM_STARTUP            1
#define SOUND_SYSTEM_SHUTDOWN           2
#define SOUND_SYSTEM_BEEP               3
#define SOUND_SYSTEM_ERROR              4
#define SOUND_SYSTEM_QUESTION           5
#define SOUND_SYSTEM_WARNING            6
#define SOUND_SYSTEM_INFORMATION        7
#define SOUND_SYSTEM_MAXIMIZE           8
#define SOUND_SYSTEM_MINIMIZE           9
#define SOUND_SYSTEM_RESTOREUP          10
#define SOUND_SYSTEM_RESTOREDOWN        11
#define SOUND_SYSTEM_APPSTART           12
#define SOUND_SYSTEM_FAULT              13
#define SOUND_SYSTEM_APPEND             14
#define SOUND_SYSTEM_MENUCOMMAND        15
#define SOUND_SYSTEM_MENUPOPUP          16
#define CSOUND_SYSTEM                   16

/*
 * System Alerts (indexChild of system ALERT notification)
 */
#define ALERT_SYSTEM_INFORMATIONAL      1       // MB_INFORMATION
#define ALERT_SYSTEM_WARNING            2       // MB_WARNING
#define ALERT_SYSTEM_ERROR              3       // MB_ERROR
#define ALERT_SYSTEM_QUERY              4       // MB_QUESTION
#define ALERT_SYSTEM_CRITICAL           5       // HardSysErrBox
#define CALERT_SYSTEM                   6

struct GUITHREADINFO
{
  DWORD   cbSize;
  DWORD   flags;
  dword    hwndActive;
  dword    hwndFocus;
  dword    hwndCapture;
  dword    hwndMenuOwner;
  dword    hwndMoveSize;
  dword    hwndCaret;
  RECT    rcCaret;
};

#define GUI_CARETBLINKING   0x00000001
#define GUI_INMOVESIZE      0x00000002
#define GUI_INMENUMODE      0x00000004
#define GUI_SYSTEMMENUMODE  0x00000008
#define GUI_POPUPMENUMODE   0x00000010
#define GUI_16BITTASK       0x00000020

extern WINAPI "user32.dll"{
	BOOL GetGUIThreadInfo(DWORD idThread,dword pgui);
	UINT GetWindowModuleFileNameA(dword hwnd,LPSTR pszFileName,UINT cchFileNameMax);
	UINT GetWindowModuleFileNameW(dword hwnd,LPWSTR pszFileName,UINT cchFileNameMax);
#ifdef UNICODE
#define GetWindowModuleFileName  GetWindowModuleFileNameW
#else
#define GetWindowModuleFileName  GetWindowModuleFileNameA
#endif // !UNICODE
}
#ifndef NO_STATE_FLAGS
#define STATE_SYSTEM_UNAVAILABLE        0x00000001  // Disabled
#define STATE_SYSTEM_SELECTED           0x00000002
#define STATE_SYSTEM_FOCUSED            0x00000004
#define STATE_SYSTEM_PRESSED            0x00000008
#define STATE_SYSTEM_CHECKED            0x00000010
#define STATE_SYSTEM_MIXED              0x00000020  // 3-state checkbox or toolbar button
#define STATE_SYSTEM_INDETERMINATE      STATE_SYSTEM_MIXED
#define STATE_SYSTEM_READONLY           0x00000040
#define STATE_SYSTEM_HOTTRACKED         0x00000080
#define STATE_SYSTEM_DEFAULT            0x00000100
#define STATE_SYSTEM_EXPANDED           0x00000200
#define STATE_SYSTEM_COLLAPSED          0x00000400
#define STATE_SYSTEM_BUSY               0x00000800
#define STATE_SYSTEM_FLOATING           0x00001000  // Children "owned" not "contained" by parent
#define STATE_SYSTEM_MARQUEED           0x00002000
#define STATE_SYSTEM_ANIMATED           0x00004000
#define STATE_SYSTEM_INVISIBLE          0x00008000
#define STATE_SYSTEM_OFFSCREEN          0x00010000
#define STATE_SYSTEM_SIZEABLE           0x00020000
#define STATE_SYSTEM_MOVEABLE           0x00040000
#define STATE_SYSTEM_SELFVOICING        0x00080000
#define STATE_SYSTEM_FOCUSABLE          0x00100000
#define STATE_SYSTEM_SELECTABLE         0x00200000
#define STATE_SYSTEM_LINKED             0x00400000
#define STATE_SYSTEM_TRAVERSED          0x00800000
#define STATE_SYSTEM_MULTISELECTABLE    0x01000000  // Supports multiple selection
#define STATE_SYSTEM_EXTSELECTABLE      0x02000000  // Supports extended selection
#define STATE_SYSTEM_ALERT_LOW          0x04000000  // This information is of low priority
#define STATE_SYSTEM_ALERT_MEDIUM       0x08000000  // This information is of medium priority
#define STATE_SYSTEM_ALERT_HIGH         0x10000000  // This information is of high priority
#define STATE_SYSTEM_PROTECTED          0x20000000  // access to this is restricted
#define STATE_SYSTEM_VALID              0x3FFFFFFF
#endif

#define CCHILDREN_TITLEBAR              5
#define CCHILDREN_SCROLLBAR             5

/*
 * Information about the global cursor.
 */
struct CURSORINFO
{
  DWORD   cbSize;
  DWORD   flags;
  HCURSOR hCursor;
  POINT   ptScreenPos;
};

#define CURSOR_SHOWING     0x00000001
/*
 * Window information snapshot
 */
struct WINDOWINFO
{
  DWORD cbSize;
  RECT  rcWindow;
  RECT  rcClient;
  DWORD dwStyle;
  DWORD dwExStyle;
  DWORD dwWindowStatus;
  UINT  cxWindowBorders;
  UINT  cyWindowBorders;
  ATOM  atomWindowType;
  WORD  wCreatorVersion;
};

#define WS_ACTIVECAPTION    0x0001

/*
 * Titlebar information.
 */
struct TITLEBARINFO
{
  DWORD cbSize;
  RECT  rcTitleBar;
  DWORD rgstate[CCHILDREN_TITLEBAR+1];
};

/*
 * Menubar information
 */
struct MENUBARINFO
{
  DWORD cbSize;
  RECT  rcBar;          // rect of bar, popup, item
  HMENU hMenu;          // real menu handle of bar, popup
  dword  hwndMenu;       // hwnd of item submenu if one
  BOOL  fBarFocused:1;  // bar, popup has the focus
  BOOL  fFocused:1;     // item has the focus
};

/*
 * Scrollbar information
 */
struct SCROLLBARINFO
{
  DWORD cbSize;
  RECT  rcScrollBar;
  int   dxyLineButton;
  int   xyThumbTop;
  int   xyThumbBottom;
  int   reserved;
  DWORD rgstate[CCHILDREN_SCROLLBAR+1];
};

/*
 * Combobox information
 */
struct COMBOBOXINFO
{
  DWORD cbSize;
  RECT  rcItem;
  RECT  rcButton;
  DWORD stateButton;
  dword  hwndCombo;
  dword  hwndItem;
  dword  hwndList;
};

/*
 * Alt-Tab Switch window information.
 */
struct ALTTABINFO
{
  DWORD cbSize;
  int   cItems;
  int   cColumns;
  int   cRows;
  int   iColFocus;
  int   iRowFocus;
  int   cxItem;
  int   cyItem;
  POINT ptStart;
};

extern WINAPI "user32.dll"{
	BOOL GetCursorInfo(dword pci);
	BOOL GetWindowInfo(dword hwnd,dword pwi);
	BOOL GetTitleBarInfo(dword hwnd,dword pti);
	BOOL GetMenuBarInfo(dword hwnd,LONG idObject,LONG idItem,dword pmbi);
	BOOL GetScrollBarInfo(dword hwnd,LONG idObject,dword psbi);
	BOOL GetComboBoxInfo(dword hwndCombo,dword pcbi);

/*
 * The "real" ancestor window
 */
#define     GA_PARENT       1
#define     GA_ROOT         2
#define     GA_ROOTOWNER    3

	dword GetAncestor(dword hwnd,UINT gaFlags);

/*
 * This gets the REAL child window at the point.  If it is in the dead
 * space of a group box, it will try a sibling behind it.  But static
 * fields will get returned.  In other words, it is kind of a cross between
 * ChildWindowFromPointEx and WindowFromPoint.
 */
	dword RealChildWindowFromPoint(dword hwndParent,POINT ptParentClientCoords);

/*
 * This gets the name of the window TYPE, not class.  This allows us to
 * recognize ThunderButton32 et al.
 */
	UINT RealGetWindowClassA(dword hwnd,LPSTR pszType,UINT cchType);
/*
 * This gets the name of the window TYPE, not class.  This allows us to
 * recognize ThunderButton32 et al.
 */
	UINT RealGetWindowClassW(dword hwnd,LPWSTR pszType,UINT cchType);
#ifdef UNICODE
#define RealGetWindowClass  RealGetWindowClassW
#else
#define RealGetWindowClass  RealGetWindowClassA
#endif // !UNICODE

	BOOL GetAltTabInfoA(dword hwnd,int iItem,dword pati,LPSTR pszItemText,UINT cchItemText);
	BOOL GetAltTabInfoW(dword hwnd,int iItem,dword pati,LPWSTR pszItemText,UINT cchItemText);
#ifdef UNICODE
#define GetAltTabInfo  GetAltTabInfoW
#else
#define GetAltTabInfo  GetAltTabInfoA
#endif // !UNICODE

/*
 * Listbox information.
 * Returns the number of items per row.
 */
	DWORD GetListBoxInfo(dword hwnd);
}
#endif /* NOWINABLE */

extern WINAPI "user32.dll"{
	BOOL LockWorkStation(VOID);
	BOOL UserHandleGrantAccess(HANDLE hUserHandle,HANDLE hJob,BOOL bGrant);
}

/*
 * WM_INPUT wParam
 */

/*
 * Use this macro to get the input code from wParam.
 */
#define GET_RAWINPUT_CODE_WPARAM(wParam)    wParam & 0xff

/*
 * The input is in the regular message flow,
 * the app is required to call DefWindowProc
 * so that the system can perform clean ups.
 */
#define RIM_INPUT       0

/*
 * The input is sink only. The app is expected
 * to behave nicely, honoring RIM_FOREGROUND etc.
 */
#define RIM_INPUTSINK   1

/*
 * Raw Input data header
 */
struct RAWINPUTHEADER {
  DWORD dwType;
  DWORD dwSize;
  HANDLE hDevice;
  WPARAM wParam;
};

/*
 * Type of the raw input
 */
#define RIM_TYPEMOUSE       0
#define RIM_TYPEKEYBOARD    1
#define RIM_TYPEHID         2

/*
 * Raw format of the mouse input
 */
struct RAWMOUSE {
  /*
   * Indicator flags.
   */
  USHORT usFlags;
  /*
   * The transition state of the mouse buttons.
   */
  union {
    ULONG ulButtons;
    struct  {
      USHORT  usButtonFlags;
      USHORT  usButtonData;
    };
  };
  /*
   * The raw state of the mouse buttons.
   */
  ULONG ulRawButtons;
  /*
   * The signed relative or absolute motion in the X direction.
   */
  LONG lLastX;
  /*
   * The signed relative or absolute motion in the Y direction.
   */
  LONG lLastY;
  /*
   * Device-specific additional information for the event.
   */
  ULONG ulExtraInformation;
};

/*
 * Define the mouse button state indicators.
 */
#define RI_MOUSE_LEFT_BUTTON_DOWN   0x0001  // Left Button changed to down.
#define RI_MOUSE_LEFT_BUTTON_UP     0x0002  // Left Button changed to up.
#define RI_MOUSE_RIGHT_BUTTON_DOWN  0x0004  // Right Button changed to down.
#define RI_MOUSE_RIGHT_BUTTON_UP    0x0008  // Right Button changed to up.
#define RI_MOUSE_MIDDLE_BUTTON_DOWN 0x0010  // Middle Button changed to down.
#define RI_MOUSE_MIDDLE_BUTTON_UP   0x0020  // Middle Button changed to up.
#define RI_MOUSE_BUTTON_1_DOWN      RI_MOUSE_LEFT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_1_UP        RI_MOUSE_LEFT_BUTTON_UP
#define RI_MOUSE_BUTTON_2_DOWN      RI_MOUSE_RIGHT_BUTTON_DOWN
#define RI_MOUSE_BUTTON_2_UP        RI_MOUSE_RIGHT_BUTTON_UP
#define RI_MOUSE_BUTTON_3_DOWN      RI_MOUSE_MIDDLE_BUTTON_DOWN
#define RI_MOUSE_BUTTON_3_UP        RI_MOUSE_MIDDLE_BUTTON_UP
#define RI_MOUSE_BUTTON_4_DOWN      0x0040
#define RI_MOUSE_BUTTON_4_UP        0x0080
#define RI_MOUSE_BUTTON_5_DOWN      0x0100
#define RI_MOUSE_BUTTON_5_UP        0x0200

/*
 * If usButtonFlags has RI_MOUSE_WHEEL, the wheel delta is stored in usButtonData.
 * Take it as a signed value.
 */
#define RI_MOUSE_WHEEL              0x0400

/*
 * Define the mouse indicator flags.
 */
#define MOUSE_MOVE_RELATIVE         0
#define MOUSE_MOVE_ABSOLUTE         1
#define MOUSE_VIRTUAL_DESKTOP    0x02  // the coordinates are mapped to the virtual desktop
#define MOUSE_ATTRIBUTES_CHANGED 0x04  // requery for mouse attributes

/*
 * Raw format of the keyboard input
 */
struct RAWKEYBOARD {
  /*
   * The "make" scan code (key depression).
   */
  USHORT MakeCode;
  /*
   * The flags field indicates a "break" (key release) and other
   * miscellaneous scan code information defined in ntddkbd.h.
   */
  USHORT Flags;
  USHORT Reserved;
  /*
   * Windows message compatible information
   */
  USHORT VKey;
  UINT   Message;
  /*
   * Device-specific additional information for the event.
   */
  ULONG ExtraInformation;
};

/*
 * Define the keyboard overrun MakeCode.
 */
#define KEYBOARD_OVERRUN_MAKE_CODE    0xFF

/*
 * Define the keyboard input data Flags.
 */
#define RI_KEY_MAKE             0
#define RI_KEY_BREAK            1
#define RI_KEY_E0               2
#define RI_KEY_E1               4
#define RI_KEY_TERMSRV_SET_LED  8
#define RI_KEY_TERMSRV_SHADOW   0x10

/*
 * Raw format of the input from Human Input Devices
 */
struct RAWHID {
  DWORD dwSizeHid;    // byte size of each report
  DWORD dwCount;      // number of input packed
  BYTE bRawData[1];
};

/*
 * RAWINPUT data structure.
 */
struct RAWINPUT {
  RAWINPUTHEADER header;
  union {
    RAWMOUSE    mouse;
    RAWKEYBOARD keyboard;
    RAWHID      hid;
  }data;
};

#define RAWINPUT_ALIGN(x)   x+sizeof(DWORD)-1&-sizeof(DWORD)

/*
 * Flags for GetRawInputData
 */
#define RID_INPUT               0x10000003
#define RID_HEADER              0x10000005

/*
 * Raw Input Device Information
 */
#define RIDI_PREPARSEDDATA      0x20000005
#define RIDI_DEVICENAME         0x20000007  // the return valus is the character length, not the byte size
#define RIDI_DEVICEINFO         0x2000000b

struct RID_DEVICE_INFO_MOUSE {
  DWORD dwId;
  DWORD dwNumberOfButtons;
  DWORD dwSampleRate;
};

struct RID_DEVICE_INFO_KEYBOARD {
  DWORD dwType;
  DWORD dwSubType;
  DWORD dwKeyboardMode;
  DWORD dwNumberOfFunctionKeys;
  DWORD dwNumberOfIndicators;
  DWORD dwNumberOfKeysTotal;
};

struct RID_DEVICE_INFO_HID {
  DWORD dwVendorId;
  DWORD dwProductId;
  DWORD dwVersionNumber;
  /*
   * Top level collection UsagePage and Usage
   */
  USHORT usUsagePage;
  USHORT usUsage;
};

struct RID_DEVICE_INFO {
  DWORD cbSize;
  DWORD dwType;
  union {
    RID_DEVICE_INFO_MOUSE mouse;
    RID_DEVICE_INFO_KEYBOARD keyboard;
    RID_DEVICE_INFO_HID hid;
  };
};

/*
 * Raw Input request APIs
 */
struct RAWINPUTDEVICE {
  USHORT usUsagePage; // Toplevel collection UsagePage
  USHORT usUsage;     // Toplevel collection Usage
  DWORD dwFlags;
  dword hwndTarget;    // Target hwnd. NULL = follows keyboard focus
};

#define RIDEV_REMOVE            0x00000001
#define RIDEV_EXCLUDE           0x00000010
#define RIDEV_PAGEONLY          0x00000020
#define RIDEV_NOLEGACY          0x00000030
#define RIDEV_CAPTUREMOUSE      0x00000200  // effective when mouse nolegacy is specified, otherwise it would be an error
#define RIDEV_NOHOTKEYS         0x00000200  // effective for keyboard.
#define RIDEV_EXMODEMASK        0x000000F0
#define RIDEV_EXMODE(mode)  mode&RIDEV_EXMODEMASK

struct RAWINPUTDEVICELIST {
  HANDLE hDevice;
  DWORD dwType;
};

extern WINAPI "user32.dll"{
	UINT GetRawInputData(dword hRawInput,UINT uiCommand,LPVOID pData,dword pcbSize,UINT cbSizeHeader);
	UINT GetRawInputDeviceInfoA(HANDLE hDevice,UINT uiCommand,LPVOID pData,dword pcbSize);
	UINT GetRawInputDeviceInfoW(HANDLE hDevice,UINT uiCommand,LPVOID pData,dword pcbSize);
#ifdef UNICODE
#define GetRawInputDeviceInfo  GetRawInputDeviceInfoW
#else
#define GetRawInputDeviceInfo  GetRawInputDeviceInfoA
#endif // !UNICODE

/*
 * Raw Input Bulk Read: GetRawInputBuffer
 */
	UINT GetRawInputBuffer(dword pData,dword pcbSize,UINT cbSizeHeader);
	BOOL RegisterRawInputDevices(dword pRawInputDevices,UINT uiNumDevices,UINT cbSize);
	UINT GetRegisteredRawInputDevices(dword pRawInputDevices,dword puiNumDevices,UINT cbSize);
	UINT GetRawInputDeviceList(dword pRawInputDeviceList,dword puiNumDevices,UINT cbSize);
	dword DefRawInputProc(dword paRawInput,INT nInput,UINT cbSizeHeader);
}

#endif /* !_WINUSER_ */
