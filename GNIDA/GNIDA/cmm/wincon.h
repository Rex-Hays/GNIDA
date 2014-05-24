/*++ BUILD Version: 0002    // Increment this if a change has global effects
Copyright (c) Microsoft Corporation. All rights reserved.
Module Name:
    wincon.h
Abstract:
    This module contains the public data structures, data types,
    and procedures exported by the NT console subsystem.
Created:
    26-Oct-1990
Revision History:
--*/

#ifndef _WINCON_
#define _WINCON_

struct COORD {
  SHORT X;
  SHORT Y;
};

struct SMALL_RECT {
  SHORT Left;
  SHORT Top;
  SHORT Right;
  SHORT Bottom;
};

struct KEY_EVENT_RECORD {
  BOOL bKeyDown;
  WORD wRepeatCount;
  WORD wVirtualKeyCode;
  WORD wVirtualScanCode;
  union {
    WCHAR UnicodeChar;
    CHAR   AsciiChar;
  }uChar;
  DWORD dwControlKeyState;
};

// ControlKeyState flags
#define RIGHT_ALT_PRESSED     0x0001 // the right alt key is pressed.
#define LEFT_ALT_PRESSED      0x0002 // the left alt key is pressed.
#define RIGHT_CTRL_PRESSED    0x0004 // the right ctrl key is pressed.
#define LEFT_CTRL_PRESSED     0x0008 // the left ctrl key is pressed.
#define SHIFT_PRESSED         0x0010 // the shift key is pressed.
#define NUMLOCK_ON            0x0020 // the numlock light is on.
#define SCROLLLOCK_ON         0x0040 // the scrolllock light is on.
#define CAPSLOCK_ON           0x0080 // the capslock light is on.
#define ENHANCED_KEY          0x0100 // the key is enhanced.
#define NLS_DBCSCHAR          0x00010000 // DBCS for JPN: SBCS/DBCS mode.
#define NLS_ALPHANUMERIC      0x00000000 // DBCS for JPN: Alphanumeric mode.
#define NLS_KATAKANA          0x00020000 // DBCS for JPN: Katakana mode.
#define NLS_HIRAGANA          0x00040000 // DBCS for JPN: Hiragana mode.
#define NLS_ROMAN             0x00400000 // DBCS for JPN: Roman/Noroman mode.
#define NLS_IME_CONVERSION    0x00800000 // DBCS for JPN: IME conversion.
#define NLS_IME_DISABLE       0x20000000 // DBCS for JPN: IME enable/disable.

struct MOUSE_EVENT_RECORD {
  COORD dwMousePosition;
  DWORD dwButtonState;
  DWORD dwControlKeyState;
  DWORD dwEventFlags;
};

// ButtonState flags
#define FROM_LEFT_1ST_BUTTON_PRESSED    0x0001
#define RIGHTMOST_BUTTON_PRESSED        0x0002
#define FROM_LEFT_2ND_BUTTON_PRESSED    0x0004
#define FROM_LEFT_3RD_BUTTON_PRESSED    0x0008
#define FROM_LEFT_4TH_BUTTON_PRESSED    0x0010

// EventFlags
#define MOUSE_MOVED   0x0001
#define DOUBLE_CLICK  0x0002
#define MOUSE_WHEELED 0x0004

struct WINDOW_BUFFER_SIZE_RECORD {
  COORD dwSize;
};

struct MENU_EVENT_RECORD {
  UINT dwCommandId;
};

struct FOCUS_EVENT_RECORD {
  BOOL bSetFocus;
};

struct INPUT_RECORD {
  WORD EventType;
  union {
    KEY_EVENT_RECORD KeyEvent;
    MOUSE_EVENT_RECORD MouseEvent;
    WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
    MENU_EVENT_RECORD MenuEvent;
    FOCUS_EVENT_RECORD FocusEvent;
  }Event;
};

//  EventType flags:
#define KEY_EVENT         0x0001 // Event contains key event record
#define MOUSE_EVENT       0x0002 // Event contains mouse event record
#define WINDOW_BUFFER_SIZE_EVENT 0x0004 // Event contains window change event record
#define MENU_EVENT 0x0008 // Event contains menu event record
#define FOCUS_EVENT 0x0010 // event contains focus change

struct CHAR_INFO {
  union {
    WCHAR UnicodeChar;
    CHAR   AsciiChar;
  }Char;
  WORD Attributes;
};

// Attributes flags:
#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#define COMMON_LVB_LEADING_BYTE    0x0100 // Leading Byte of DBCS
#define COMMON_LVB_TRAILING_BYTE   0x0200 // Trailing Byte of DBCS
#define COMMON_LVB_GRID_HORIZONTAL 0x0400 // DBCS: Grid attribute: top horizontal.
#define COMMON_LVB_GRID_LVERTICAL  0x0800 // DBCS: Grid attribute: left vertical.
#define COMMON_LVB_GRID_RVERTICAL  0x1000 // DBCS: Grid attribute: right vertical.
#define COMMON_LVB_REVERSE_VIDEO   0x4000 // DBCS: Reverse fore/back ground attribute.
#define COMMON_LVB_UNDERSCORE      0x8000 // DBCS: Underscore.

#define COMMON_LVB_SBCSDBCS        0x0300 // SBCS or DBCS flag.

struct CONSOLE_SCREEN_BUFFER_INFO {
  COORD dwSize;
  COORD dwCursorPosition;
  WORD  wAttributes;
  SMALL_RECT srWindow;
  COORD dwMaximumWindowSize;
};

struct CONSOLE_CURSOR_INFO {
  DWORD  dwSize;
  BOOL   bVisible;
};

struct CONSOLE_FONT_INFO {
  DWORD  nFont;
  COORD  dwFontSize;
};

struct CONSOLE_SELECTION_INFO {
  DWORD dwFlags;
  COORD dwSelectionAnchor;
  SMALL_RECT srSelection;
};

// Selection flags
#define CONSOLE_NO_SELECTION            0x0000
#define CONSOLE_SELECTION_IN_PROGRESS   0x0001   // selection has begun
#define CONSOLE_SELECTION_NOT_EMPTY     0x0002   // non-null select rectangle
#define CONSOLE_MOUSE_SELECTION         0x0004   // selecting with mouse
#define CONSOLE_MOUSE_DOWN              0x0008   // mouse is down

// typedef for ctrl-c handler routines
#define CTRL_C_EVENT        0
#define CTRL_BREAK_EVENT    1
#define CTRL_CLOSE_EVENT    2
// 3 is reserved!
// 4 is reserved!
#define CTRL_LOGOFF_EVENT   5
#define CTRL_SHUTDOWN_EVENT 6

//  Input Mode flags:
#define ENABLE_PROCESSED_INPUT 0x0001
#define ENABLE_LINE_INPUT      0x0002
#define ENABLE_ECHO_INPUT      0x0004
#define ENABLE_WINDOW_INPUT    0x0008
#define ENABLE_MOUSE_INPUT     0x0010

// Output Mode flags:
#define ENABLE_PROCESSED_OUTPUT    0x0001
#define ENABLE_WRAP_AT_EOL_OUTPUT  0x0002

// direct API definitions.
extern WINAPI "kernel32.dll"{
	BOOL PeekConsoleInputA(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
	BOOL PeekConsoleInputW(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
#ifdef UNICODE
#define PeekConsoleInput  PeekConsoleInputW
#else
#define PeekConsoleInput  PeekConsoleInputA
#endif // !UNICODE

	BOOL ReadConsoleInputA(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
	BOOL ReadConsoleInputW(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsRead);
#ifdef UNICODE
#define ReadConsoleInput  ReadConsoleInputW
#else
#define ReadConsoleInput  ReadConsoleInputA
#endif // !UNICODE

	BOOL WriteConsoleInputA(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsWritten);
	BOOL WriteConsoleInputW(HANDLE hConsoleInput,dword lpBuffer,DWORD nLength,LPDWORD lpNumberOfEventsWritten);
#ifdef UNICODE
#define WriteConsoleInput  WriteConsoleInputW
#else
#define WriteConsoleInput  WriteConsoleInputA
#endif // !UNICODE

	BOOL ReadConsoleOutputA(HANDLE hConsoleOutput,dword lpBuffer,COORD dwBufferSize,
    COORD dwBufferCoord,dword lpReadRegion);
	BOOL ReadConsoleOutputW(HANDLE hConsoleOutput,dword lpBuffer,
    COORD dwBufferSize,COORD dwBufferCoord,dword lpReadRegion);
#ifdef UNICODE
#define ReadConsoleOutput  ReadConsoleOutputW
#else
#define ReadConsoleOutput  ReadConsoleOutputA
#endif // !UNICODE

	BOOL WriteConsoleOutputA(HANDLE hConsoleOutput,dword lpBuffer,COORD dwBufferSize,
    COORD dwBufferCoord,dword lpWriteRegion);
	BOOL WriteConsoleOutputW(HANDLE hConsoleOutput,dword lpBuffer,
    COORD dwBufferSize,COORD dwBufferCoord,dword lpWriteRegion);
#ifdef UNICODE
#define WriteConsoleOutput  WriteConsoleOutputW
#else
#define WriteConsoleOutput  WriteConsoleOutputA
#endif // !UNICODE

	BOOL ReadConsoleOutputCharacterA(HANDLE hConsoleOutput,LPSTR lpCharacter,
    DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfCharsRead);
	BOOL ReadConsoleOutputCharacterW(HANDLE hConsoleOutput,LPWSTR lpCharacter,
    DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfCharsRead);
#ifdef UNICODE
#define ReadConsoleOutputCharacter  ReadConsoleOutputCharacterW
#else
#define ReadConsoleOutputCharacter  ReadConsoleOutputCharacterA
#endif // !UNICODE

	BOOL ReadConsoleOutputAttribute(HANDLE hConsoleOutput,LPWORD lpAttribute,
    DWORD nLength,COORD dwReadCoord,LPDWORD lpNumberOfAttrsRead);
	BOOL WriteConsoleOutputCharacterA(HANDLE hConsoleOutput,LPCSTR lpCharacter,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
	BOOL WriteConsoleOutputCharacterW(HANDLE hConsoleOutput,LPCWSTR lpCharacter,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
#ifdef UNICODE
#define WriteConsoleOutputCharacter  WriteConsoleOutputCharacterW
#else
#define WriteConsoleOutputCharacter  WriteConsoleOutputCharacterA
#endif // !UNICODE

	BOOL WriteConsoleOutputAttribute(HANDLE hConsoleOutput,dword lpAttribute,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfAttrsWritten);
	BOOL FillConsoleOutputCharacterA(HANDLE hConsoleOutput,CHAR cCharacter,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
	BOOL FillConsoleOutputCharacterW(HANDLE hConsoleOutput,WCHAR cCharacter,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfCharsWritten);
#ifdef UNICODE
#define FillConsoleOutputCharacter  FillConsoleOutputCharacterW
#else
#define FillConsoleOutputCharacter  FillConsoleOutputCharacterA
#endif // !UNICODE

	BOOL FillConsoleOutputAttribute(HANDLE hConsoleOutput,WORD wAttribute,
    DWORD nLength,COORD dwWriteCoord,LPDWORD lpNumberOfAttrsWritten);
	BOOL GetConsoleMode(HANDLE hConsoleHandle,LPDWORD lpMode);
	BOOL GetNumberOfConsoleInputEvents(HANDLE hConsoleInput,LPDWORD lpNumberOfEvents);
	BOOL GetConsoleScreenBufferInfo(HANDLE hConsoleOutput,dword lpConsoleScreenBufferInfo);
	dword /*COORD*/ GetLargestConsoleWindowSize(HANDLE hConsoleOutput);
	BOOL GetConsoleCursorInfo(HANDLE hConsoleOutput,dword lpConsoleCursorInfo);
	BOOL GetCurrentConsoleFont(HANDLE hConsoleOutput,BOOL bMaximumWindow,dword lpConsoleCurrentFont);
	dword/*COORD*/ GetConsoleFontSize(HANDLE hConsoleOutput,DWORD nFont);
	BOOL GetConsoleSelectionInfo(dword lpConsoleSelectionInfo);
	BOOL GetNumberOfConsoleMouseButtons(LPDWORD lpNumberOfMouseButtons);
	BOOL SetConsoleMode(HANDLE hConsoleHandle,DWORD dwMode);
	BOOL SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput);
	BOOL FlushConsoleInputBuffer(HANDLE hConsoleInput);
	BOOL SetConsoleScreenBufferSize(HANDLE hConsoleOutput,COORD dwSize);
	BOOL SetConsoleCursorPosition(HANDLE hConsoleOutput,COORD dwCursorPosition);
	BOOL SetConsoleCursorInfo(HANDLE hConsoleOutput,dword lpConsoleCursorInfo);
	BOOL ScrollConsoleScreenBufferA(HANDLE hConsoleOutput,dword lpScrollRectangle,
    dword lpClipRectangle,COORD dwDestinationOrigin,dword lpFill);
	BOOL ScrollConsoleScreenBufferW(HANDLE hConsoleOutput,dword lpScrollRectangle,
    dword lpClipRectangle,COORD dwDestinationOrigin,dword lpFill);
#ifdef UNICODE
#define ScrollConsoleScreenBuffer  ScrollConsoleScreenBufferW
#else
#define ScrollConsoleScreenBuffer  ScrollConsoleScreenBufferA
#endif // !UNICODE

	BOOL SetConsoleWindowInfo(HANDLE hConsoleOutput,BOOL bAbsolute,dword lpConsoleWindow);
	BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput,WORD wAttributes);
	BOOL SetConsoleCtrlHandler(dword HandlerRoutine,BOOL Add);
	BOOL GenerateConsoleCtrlEvent(DWORD dwCtrlEvent,DWORD dwProcessGroupId);
	BOOL AllocConsole(VOID);
	BOOL FreeConsole(VOID);
	BOOL AttachConsole(DWORD dwProcessId);
	DWORD GetConsoleTitleA(LPSTR lpConsoleTitle,DWORD nSize);
	DWORD GetConsoleTitleW(LPWSTR lpConsoleTitle,DWORD nSize);
#ifdef UNICODE
#define GetConsoleTitle  GetConsoleTitleW
#else
#define GetConsoleTitle  GetConsoleTitleA
#endif // !UNICODE

	BOOL SetConsoleTitleA(LPCSTR lpConsoleTitle);
	BOOL SetConsoleTitleW(LPCWSTR lpConsoleTitle);
#ifdef UNICODE
#define SetConsoleTitle  SetConsoleTitleW
#else
#define SetConsoleTitle  SetConsoleTitleA
#endif // !UNICODE

	BOOL ReadConsoleA(HANDLE hConsoleInput,LPVOID lpBuffer,DWORD nNumberOfCharsToRead,
    LPDWORD lpNumberOfCharsRead,LPVOID lpReserved);
	BOOL ReadConsoleW(HANDLE hConsoleInput,LPVOID lpBuffer,DWORD nNumberOfCharsToRead,
    LPDWORD lpNumberOfCharsRead,LPVOID lpReserved);
#ifdef UNICODE
#define ReadConsole  ReadConsoleW
#else
#define ReadConsole  ReadConsoleA
#endif // !UNICODE

	BOOL WriteConsoleA(HANDLE hConsoleOutput,dword lpBuffer,DWORD nNumberOfCharsToWrite,
    LPDWORD lpNumberOfCharsWritten,LPVOID lpReserved);
	BOOL WriteConsoleW(HANDLE hConsoleOutput,dword lpBuffer,DWORD nNumberOfCharsToWrite,
    LPDWORD lpNumberOfCharsWritten,LPVOID lpReserved);
#ifdef UNICODE
#define WriteConsole  WriteConsoleW
#else
#define WriteConsole  WriteConsoleA
#endif // !UNICODE

#define CONSOLE_TEXTMODE_BUFFER  1

	HANDLE CreateConsoleScreenBuffer(DWORD dwDesiredAccess,DWORD dwShareMode,
    dword lpSecurityAttributes,DWORD dwFlags,LPVOID lpScreenBufferData);
	UINT GetConsoleCP(VOID);
	BOOL SetConsoleCP(UINT wCodePageID);
	UINT GetConsoleOutputCP(VOID);
	BOOL SetConsoleOutputCP(UINT wCodePageID);

#define CONSOLE_FULLSCREEN 1            // fullscreen console
#define CONSOLE_FULLSCREEN_HARDWARE 2   // console owns the hardware

	BOOL GetConsoleDisplayMode(LPDWORD lpModeFlags);
	dword GetConsoleWindow(VOID);
	DWORD GetConsoleProcessList(LPDWORD lpdwProcessList,DWORD dwProcessCount);
}
#endif // _WINCON_
