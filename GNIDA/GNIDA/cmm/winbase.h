/************************************************************************
*   winbase.h -- This module defines the 32-Bit Windows Base APIs       *
*   Copyright (c) Microsoft Corp. All rights reserved.                  *
************************************************************************/
#ifndef _WINBASE_
#define _WINBASE_

/*
 * Compatibility macros
 */
#define LockSegment(w)                  GlobalFix(w)
#define UnlockSegment(w)                GlobalUnfix(w)
#define GetCurrentTime()                GetTickCount()
#define Yield()
#define INVALID_HANDLE_VALUE -1
#define INVALID_FILE_SIZE 0xFFFFFFFF
#define INVALID_SET_FILE_POINTER -1
#define INVALID_FILE_ATTRIBUTES -1

#define FILE_BEGIN           0
#define FILE_CURRENT         1
#define FILE_END             2

#define TIME_ZONE_ID_INVALID 0xFFFFFFFF

#define WAIT_FAILED 0xFFFFFFFF
#define WAIT_OBJECT_0       STATUS_WAIT_0 

#define WAIT_ABANDONED         STATUS_ABANDONED_WAIT_0 + 0
#define WAIT_ABANDONED_0       STATUS_ABANDONED_WAIT_0 + 0

#define WAIT_IO_COMPLETION                  STATUS_USER_APC
#define STILL_ACTIVE                        STATUS_PENDING
#define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
#define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
#define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
#define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
#define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
#define CONTROL_C_EXIT                      STATUS_CONTROL_C_EXIT

#define MoveMemory RtlMoveMemory
#define CopyMemory RtlMoveMemory
#define FillMemory RtlFillMemory
#define ZeroMemory RtlZeroMemory

// File creation flags must start at the high end since they
// are combined with the attributes
#define FILE_FLAG_WRITE_THROUGH         0x80000000
#define FILE_FLAG_OVERLAPPED            0x40000000
#define FILE_FLAG_NO_BUFFERING          0x20000000
#define FILE_FLAG_RANDOM_ACCESS         0x10000000
#define FILE_FLAG_SEQUENTIAL_SCAN       0x08000000
#define FILE_FLAG_DELETE_ON_CLOSE       0x04000000
#define FILE_FLAG_BACKUP_SEMANTICS      0x02000000
#define FILE_FLAG_POSIX_SEMANTICS       0x01000000
#define FILE_FLAG_OPEN_REPARSE_POINT    0x00200000
#define FILE_FLAG_OPEN_NO_RECALL        0x00100000
#define FILE_FLAG_FIRST_PIPE_INSTANCE   0x00080000

#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

// Define possible return codes from the CopyFileEx callback routine
#define PROGRESS_CONTINUE   0
#define PROGRESS_CANCEL     1
#define PROGRESS_STOP       2
#define PROGRESS_QUIET      3

// Define CopyFileEx callback routine state change values
#define CALLBACK_CHUNK_FINISHED         0x00000000
#define CALLBACK_STREAM_SWITCH          0x00000001

// Define CopyFileEx option flags
#define COPY_FILE_FAIL_IF_EXISTS              0x00000001
#define COPY_FILE_RESTARTABLE                 0x00000002
#define COPY_FILE_OPEN_SOURCE_FOR_WRITE       0x00000004
#define COPY_FILE_ALLOW_DECRYPTED_DESTINATION 0x00000008

// Define ReplaceFile option flags
#define REPLACEFILE_WRITE_THROUGH       0x00000001
#define REPLACEFILE_IGNORE_MERGE_ERRORS 0x00000002

// Define the dwOpenMode values for CreateNamedPipe
#define PIPE_ACCESS_INBOUND         0x00000001
#define PIPE_ACCESS_OUTBOUND        0x00000002
#define PIPE_ACCESS_DUPLEX          0x00000003

// Define the Named Pipe End flags for GetNamedPipeInfo
#define PIPE_CLIENT_END             0x00000000
#define PIPE_SERVER_END             0x00000001

// Define the dwPipeMode values for CreateNamedPipe
#define PIPE_WAIT                   0x00000000
#define PIPE_NOWAIT                 0x00000001
#define PIPE_READMODE_BYTE          0x00000000
#define PIPE_READMODE_MESSAGE       0x00000002
#define PIPE_TYPE_BYTE              0x00000000
#define PIPE_TYPE_MESSAGE           0x00000004

// Define the well known values for CreateNamedPipe nMaxInstances

#define PIPE_UNLIMITED_INSTANCES    255

// Define the Security Quality of Service bits to be passed
// into CreateFile
#define SECURITY_ANONYMOUS          SecurityAnonymous      << 16
#define SECURITY_IDENTIFICATION     SecurityIdentification << 16
#define SECURITY_IMPERSONATION      SecurityImpersonation  << 16
#define SECURITY_DELEGATION         SecurityDelegation     << 16

#define SECURITY_CONTEXT_TRACKING  0x00040000
#define SECURITY_EFFECTIVE_ONLY    0x00080000

#define SECURITY_SQOS_PRESENT      0x00100000
#define SECURITY_VALID_SQOS_FLAGS  0x001F0000

//  File structures
struct OVERLAPPED {
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  union {
    struct {
      DWORD Offset;
      DWORD OffsetHigh;
    };
    PVOID Pointer;
  };
  HANDLE  hEvent;
};

struct SECURITY_ATTRIBUTES {
  DWORD nLength;
  LPVOID lpSecurityDescriptor;
  BOOL bInheritHandle;
};

struct PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD dwProcessId;
  DWORD dwThreadId;
};

//  File System time stamps are represented with the following structure:
struct FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
};

// System time is represented with the following structure:
struct SYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
};

// Serial provider type.
#define SP_SERIALCOMM    0x00000001

// Provider SubTypes
#define PST_UNSPECIFIED      0x00000000
#define PST_RS232            0x00000001
#define PST_PARALLELPORT     0x00000002
#define PST_RS422            0x00000003
#define PST_RS423            0x00000004
#define PST_RS449            0x00000005
#define PST_MODEM            0x00000006
#define PST_FAX              0x00000021
#define PST_SCANNER          0x00000022
#define PST_NETWORK_BRIDGE   0x00000100
#define PST_LAT              0x00000101
#define PST_TCPIP_TELNET     0x00000102
#define PST_X25              0x00000103

// Provider capabilities flags.
#define PCF_DTRDSR        0x0001
#define PCF_RTSCTS        0x0002
#define PCF_RLSD          0x0004
#define PCF_PARITY_CHECK  0x0008
#define PCF_XONXOFF       0x0010
#define PCF_SETXCHAR      0x0020
#define PCF_TOTALTIMEOUTS 0x0040
#define PCF_INTTIMEOUTS   0x0080
#define PCF_SPECIALCHARS  0x0100
#define PCF_16BITMODE     0x0200

// Comm provider settable parameters.
#define SP_PARITY         0x0001
#define SP_BAUD           0x0002
#define SP_DATABITS       0x0004
#define SP_STOPBITS       0x0008
#define SP_HANDSHAKING    0x0010
#define SP_PARITY_CHECK   0x0020
#define SP_RLSD           0x0040

// Settable baud rates in the provider.
#define BAUD_075          0x00000001
#define BAUD_110          0x00000002
#define BAUD_134_5        0x00000004
#define BAUD_150          0x00000008
#define BAUD_300          0x00000010
#define BAUD_600          0x00000020
#define BAUD_1200         0x00000040
#define BAUD_1800         0x00000080
#define BAUD_2400         0x00000100
#define BAUD_4800         0x00000200
#define BAUD_7200         0x00000400
#define BAUD_9600         0x00000800
#define BAUD_14400        0x00001000
#define BAUD_19200        0x00002000
#define BAUD_38400        0x00004000
#define BAUD_56K          0x00008000
#define BAUD_128K         0x00010000
#define BAUD_115200       0x00020000
#define BAUD_57600        0x00040000
#define BAUD_USER         0x10000000

// Settable Data Bits
#define DATABITS_5        0x0001
#define DATABITS_6        0x0002
#define DATABITS_7        0x0004
#define DATABITS_8        0x0008
#define DATABITS_16       0x0010
#define DATABITS_16X      0x0020

// Settable Stop and Parity bits.
#define STOPBITS_10       0x0001
#define STOPBITS_15       0x0002
#define STOPBITS_20       0x0004
#define PARITY_NONE       0x0100
#define PARITY_ODD        0x0200
#define PARITY_EVEN       0x0400
#define PARITY_MARK       0x0800
#define PARITY_SPACE      0x1000

struct COMMPROP {
  WORD wPacketLength;
  WORD wPacketVersion;
  DWORD dwServiceMask;
  DWORD dwReserved1;
  DWORD dwMaxTxQueue;
  DWORD dwMaxRxQueue;
  DWORD dwMaxBaud;
  DWORD dwProvSubType;
  DWORD dwProvCapabilities;
  DWORD dwSettableParams;
  DWORD dwSettableBaud;
  WORD wSettableData;
  WORD wSettableStopParity;
  DWORD dwCurrentTxQueue;
  DWORD dwCurrentRxQueue;
  DWORD dwProvSpec1;
  DWORD dwProvSpec2;
  WCHAR wcProvChar[1];
};

// Set dwProvSpec1 to COMMPROP_INITIALIZED to indicate that wPacketLength
// is valid before a call to GetCommProperties().
#define COMMPROP_INITIALIZED 0xE73CF52E

struct COMSTAT {
  DWORD fCtsHold : 1;
  DWORD fDsrHold : 1;
  DWORD fRlsdHold : 1;
  DWORD fXoffHold : 1;
  DWORD fXoffSent : 1;
  DWORD fEof : 1;
  DWORD fTxim : 1;
  DWORD fReserved : 25;
  DWORD cbInQue;
  DWORD cbOutQue;
};

// DTR Control Flow Values.
#define DTR_CONTROL_DISABLE    0x00
#define DTR_CONTROL_ENABLE     0x01
#define DTR_CONTROL_HANDSHAKE  0x02

// RTS Control Flow Values
#define RTS_CONTROL_DISABLE    0x00
#define RTS_CONTROL_ENABLE     0x01
#define RTS_CONTROL_HANDSHAKE  0x02
#define RTS_CONTROL_TOGGLE     0x03

struct DCB {
  DWORD DCBlength;      /* sizeof(DCB)                     */
  DWORD BaudRate;       /* Baudrate at which running       */
  DWORD fBinary: 1;     /* Binary Mode (skip EOF check)    */
  DWORD fParity: 1;     /* Enable parity checking          */
  DWORD fOutxCtsFlow:1; /* CTS handshaking on output       */
  DWORD fOutxDsrFlow:1; /* DSR handshaking on output       */
  DWORD fDtrControl:2;  /* DTR Flow control                */
  DWORD fDsrSensitivity:1; /* DSR Sensitivity              */
  DWORD fTXContinueOnXoff: 1; /* Continue TX when Xoff sent */
  DWORD fOutX: 1;       /* Enable output X-ON/X-OFF        */
  DWORD fInX: 1;        /* Enable input X-ON/X-OFF         */
  DWORD fErrorChar: 1;  /* Enable Err Replacement          */
  DWORD fNull: 1;       /* Enable Null stripping           */
  DWORD fRtsControl:2;  /* Rts Flow control                */
  DWORD fAbortOnError:1; /* Abort all reads and writes on Error */
  DWORD fDummy2:17;     /* Reserved                        */
  WORD wReserved;       /* Not currently used              */
  WORD XonLim;          /* Transmit X-ON threshold         */
  WORD XoffLim;         /* Transmit X-OFF threshold        */
  BYTE ByteSize;        /* Number of bits/byte, 4-8        */
  BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
  BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
  char XonChar;         /* Tx and Rx X-ON character        */
  char XoffChar;        /* Tx and Rx X-OFF character       */
  char ErrorChar;       /* Error replacement char          */
  char EofChar;         /* End of Input character          */
  char EvtChar;         /* Received Event character        */
  WORD wReserved1;      /* Fill for now.                   */
};

struct COMMTIMEOUTS {
  DWORD ReadIntervalTimeout;          /* Maximum time between read chars. */
  DWORD ReadTotalTimeoutMultiplier;   /* Multiplier of characters.        */
  DWORD ReadTotalTimeoutConstant;     /* Constant in milliseconds.        */
  DWORD WriteTotalTimeoutMultiplier;  /* Multiplier of characters.        */
  DWORD WriteTotalTimeoutConstant;    /* Constant in milliseconds.        */
};

struct COMMCONFIG {
  DWORD dwSize;               /* Size of the entire struct */
  WORD wVersion;              /* version of the structure */
  WORD wReserved;             /* alignment */
  DCB dcb;                    /* device control block */
  DWORD dwProviderSubType;    /* ordinal value for identifying
                                 provider-defined data structure format*/
  DWORD dwProviderOffset;     /* Specifies the offset of provider specific
                                 data field in bytes from the start */
  DWORD dwProviderSize;       /* size of the provider-specific data field */
  WCHAR wcProviderData[1];    /* provider-specific data */
};

struct SYSTEM_INFO {
  union {
    DWORD dwOemId;          // Obsolete field...do not use
    struct {
      WORD wProcessorArchitecture;
      WORD wReserved;
    };
  };
  DWORD dwPageSize;
  LPVOID lpMinimumApplicationAddress;
  LPVOID lpMaximumApplicationAddress;
  DWORD_PTR dwActiveProcessorMask;
  DWORD dwNumberOfProcessors;
  DWORD dwProcessorType;
  DWORD dwAllocationGranularity;
  WORD wProcessorLevel;
  WORD wProcessorRevision;
};

#define FreeModule(hLibModule) FreeLibrary(hLibModule)
#define MakeProcInstance(lpProc,hInstance) lpProc
#define FreeProcInstance(lpProc) lpProc

/* Global Memory Flags */
#define GMEM_FIXED          0x0000
#define GMEM_MOVEABLE       0x0002
#define GMEM_NOCOMPACT      0x0010
#define GMEM_NODISCARD      0x0020
#define GMEM_ZEROINIT       0x0040
#define GMEM_MODIFY         0x0080
#define GMEM_DISCARDABLE    0x0100
#define GMEM_NOT_BANKED     0x1000
#define GMEM_SHARE          0x2000
#define GMEM_DDESHARE       0x2000
#define GMEM_NOTIFY         0x4000
#define GMEM_LOWER          GMEM_NOT_BANKED
#define GMEM_VALID_FLAGS    0x7F72
#define GMEM_INVALID_HANDLE 0x8000

#define GHND                GMEM_MOVEABLE | GMEM_ZEROINIT
#define GPTR                GMEM_FIXED | GMEM_ZEROINIT

#define GlobalDiscard(h)      GlobalReAlloc(h,0,GMEM_MOVEABLE)

/* Flags returned by GlobalFlags (in addition to GMEM_DISCARDABLE) */
#define GMEM_DISCARDED      0x4000
#define GMEM_LOCKCOUNT      0x00FF

struct MEMORYSTATUS {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  SIZE_T dwTotalPhys;
  SIZE_T dwAvailPhys;
  SIZE_T dwTotalPageFile;
  SIZE_T dwAvailPageFile;
  SIZE_T dwTotalVirtual;
  SIZE_T dwAvailVirtual;
};

/* Local Memory Flags */
#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_NOCOMPACT      0x0010
#define LMEM_NODISCARD      0x0020
#define LMEM_ZEROINIT       0x0040
#define LMEM_MODIFY         0x0080
#define LMEM_DISCARDABLE    0x0F00
#define LMEM_VALID_FLAGS    0x0F72
#define LMEM_INVALID_HANDLE 0x8000

#define LHND                LMEM_MOVEABLE | LMEM_ZEROINIT
#define LPTR                LMEM_FIXED | LMEM_ZEROINIT

#define NONZEROLHND         LMEM_MOVEABLE
#define NONZEROLPTR         LMEM_FIXED

#define LocalDiscard(h)   LocalReAlloc(h,0,LMEM_MOVEABLE)

/* Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE) */
#define LMEM_DISCARDED      0x4000
#define LMEM_LOCKCOUNT      0x00FF

// dwCreationFlag values
#define DEBUG_PROCESS                     0x00000001
#define DEBUG_ONLY_THIS_PROCESS           0x00000002
#define CREATE_SUSPENDED                  0x00000004
#define DETACHED_PROCESS                  0x00000008
#define CREATE_NEW_CONSOLE                0x00000010
#define NORMAL_PRIORITY_CLASS             0x00000020
#define IDLE_PRIORITY_CLASS               0x00000040
#define HIGH_PRIORITY_CLASS               0x00000080
#define REALTIME_PRIORITY_CLASS           0x00000100
#define CREATE_NEW_PROCESS_GROUP          0x00000200
#define CREATE_UNICODE_ENVIRONMENT        0x00000400
#define CREATE_SEPARATE_WOW_VDM           0x00000800
#define CREATE_SHARED_WOW_VDM             0x00001000
#define CREATE_FORCEDOS                   0x00002000
#define BELOW_NORMAL_PRIORITY_CLASS       0x00004000
#define ABOVE_NORMAL_PRIORITY_CLASS       0x00008000
#define STACK_SIZE_PARAM_IS_A_RESERVATION 0x00010000
#define CREATE_BREAKAWAY_FROM_JOB         0x01000000
#define CREATE_PRESERVE_CODE_AUTHZ_LEVEL  0x02000000
#define CREATE_DEFAULT_ERROR_MODE         0x04000000
#define CREATE_NO_WINDOW                  0x08000000
#define PROFILE_USER                      0x10000000
#define PROFILE_KERNEL                    0x20000000
#define PROFILE_SERVER                    0x40000000
#define CREATE_IGNORE_SYSTEM_DEFAULT      0x80000000

#define THREAD_PRIORITY_LOWEST          THREAD_BASE_PRIORITY_MIN
#define THREAD_PRIORITY_BELOW_NORMAL    THREAD_PRIORITY_LOWEST+1
#define THREAD_PRIORITY_NORMAL          0
#define THREAD_PRIORITY_HIGHEST         THREAD_BASE_PRIORITY_MAX
#define THREAD_PRIORITY_ABOVE_NORMAL    THREAD_PRIORITY_HIGHEST-1
#define THREAD_PRIORITY_ERROR_RETURN    MAXLONG
#define THREAD_PRIORITY_TIME_CRITICAL   THREAD_BASE_PRIORITY_LOWRT
#define THREAD_PRIORITY_IDLE            THREAD_BASE_PRIORITY_IDLE

// Debug APIs
#define EXCEPTION_DEBUG_EVENT       1
#define CREATE_THREAD_DEBUG_EVENT   2
#define CREATE_PROCESS_DEBUG_EVENT  3
#define EXIT_THREAD_DEBUG_EVENT     4
#define EXIT_PROCESS_DEBUG_EVENT    5
#define LOAD_DLL_DEBUG_EVENT        6
#define UNLOAD_DLL_DEBUG_EVENT      7
#define OUTPUT_DEBUG_STRING_EVENT   8
#define RIP_EVENT                   9

struct EXCEPTION_DEBUG_INFO {
  EXCEPTION_RECORD ExceptionRecord;
  DWORD dwFirstChance;
};

struct CREATE_THREAD_DEBUG_INFO {
  HANDLE hThread;
  LPVOID lpThreadLocalBase;
  dword lpStartAddress;
};

struct CREATE_PROCESS_DEBUG_INFO {
  HANDLE hFile;
  HANDLE hProcess;
  HANDLE hThread;
  LPVOID lpBaseOfImage;
  DWORD dwDebugInfoFileOffset;
  DWORD nDebugInfoSize;
  LPVOID lpThreadLocalBase;
  dword lpStartAddress;
  LPVOID lpImageName;
  WORD fUnicode;
};

struct EXIT_THREAD_DEBUG_INFO {
  DWORD dwExitCode;
};

struct EXIT_PROCESS_DEBUG_INFO {
  DWORD dwExitCode;
};

struct LOAD_DLL_DEBUG_INFO {
  HANDLE hFile;
  LPVOID lpBaseOfDll;
  DWORD dwDebugInfoFileOffset;
  DWORD nDebugInfoSize;
  LPVOID lpImageName;
  WORD fUnicode;
};

struct UNLOAD_DLL_DEBUG_INFO {
  LPVOID lpBaseOfDll;
};

struct OUTPUT_DEBUG_STRING_INFO {
  LPSTR lpDebugStringData;
  WORD fUnicode;
  WORD nDebugStringLength;
};

struct RIP_INFO {
  DWORD dwError;
  DWORD dwType;
};

struct DEBUG_EVENT {
  DWORD dwDebugEventCode;
  DWORD dwProcessId;
  DWORD dwThreadId;
  union {
    EXCEPTION_DEBUG_INFO Exception;
    CREATE_THREAD_DEBUG_INFO CreateThread;
    CREATE_PROCESS_DEBUG_INFO CreateProcessInfo;
    EXIT_THREAD_DEBUG_INFO ExitThread;
    EXIT_PROCESS_DEBUG_INFO ExitProcess;
    LOAD_DLL_DEBUG_INFO LoadDll;
    UNLOAD_DLL_DEBUG_INFO UnloadDll;
    OUTPUT_DEBUG_STRING_INFO DebugString;
    RIP_INFO RipInfo;
  }u;
};

#define DRIVE_UNKNOWN     0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE   2
#define DRIVE_FIXED       3
#define DRIVE_REMOTE      4
#define DRIVE_CDROM       5
#define DRIVE_RAMDISK     6

#define FILE_TYPE_UNKNOWN   0x0000
#define FILE_TYPE_DISK      0x0001
#define FILE_TYPE_CHAR      0x0002
#define FILE_TYPE_PIPE      0x0003
#define FILE_TYPE_REMOTE    0x8000

#define STD_INPUT_HANDLE    -10
#define STD_OUTPUT_HANDLE   -11
#define STD_ERROR_HANDLE    -12

#define NOPARITY            0
#define ODDPARITY           1
#define EVENPARITY          2
#define MARKPARITY          3
#define SPACEPARITY         4

#define ONESTOPBIT          0
#define ONE5STOPBITS        1
#define TWOSTOPBITS         2

#define IGNORE              0       // Ignore signal
#define INFINITE            0xFFFFFFFF  // Infinite timeout

// Baud rates at which the communication device operates
#define CBR_110             110
#define CBR_300             300
#define CBR_600             600
#define CBR_1200            1200
#define CBR_2400            2400
#define CBR_4800            4800
#define CBR_9600            9600
#define CBR_14400           14400
#define CBR_19200           19200
#define CBR_38400           38400
#define CBR_56000           56000
#define CBR_57600           57600
#define CBR_115200          115200
#define CBR_128000          128000
#define CBR_256000          256000

// Error Flags
#define CE_RXOVER           0x0001  // Receive Queue overflow
#define CE_OVERRUN          0x0002  // Receive Overrun Error
#define CE_RXPARITY         0x0004  // Receive Parity Error
#define CE_FRAME            0x0008  // Receive Framing error
#define CE_BREAK            0x0010  // Break Detected
#define CE_TXFULL           0x0100  // TX Queue is full
#define CE_PTO              0x0200  // LPTx Timeout
#define CE_IOE              0x0400  // LPTx I/O Error
#define CE_DNS              0x0800  // LPTx Device not selected
#define CE_OOP              0x1000  // LPTx Out-Of-Paper
#define CE_MODE             0x8000  // Requested mode unsupported

#define IE_BADID            -1    // Invalid or unsupported id
#define IE_OPEN             -2    // Device Already Open
#define IE_NOPEN            -3    // Device Not Open
#define IE_MEMORY           -4    // Unable to allocate queues
#define IE_DEFAULT          -5    // Error in default parameters
#define IE_HARDWARE         -10   // Hardware Not Present
#define IE_BYTESIZE         -11   // Illegal Byte Size
#define IE_BAUDRATE         -12   // Unsupported BaudRate

// Events
#define EV_RXCHAR           0x0001  // Any Character received
#define EV_RXFLAG           0x0002  // Received certain character
#define EV_TXEMPTY          0x0004  // Transmitt Queue Empty
#define EV_CTS              0x0008  // CTS changed state
#define EV_DSR              0x0010  // DSR changed state
#define EV_RLSD             0x0020  // RLSD changed state
#define EV_BREAK            0x0040  // BREAK received
#define EV_ERR              0x0080  // Line status error occurred
#define EV_RING             0x0100  // Ring signal detected
#define EV_PERR             0x0200  // Printer error occured
#define EV_RX80FULL         0x0400  // Receive buffer is 80 percent full
#define EV_EVENT1           0x0800  // Provider specific event 1
#define EV_EVENT2           0x1000  // Provider specific event 2

// Escape Functions
#define SETXOFF             1       // Simulate XOFF received
#define SETXON              2       // Simulate XON received
#define SETRTS              3       // Set RTS high
#define CLRRTS              4       // Set RTS low
#define SETDTR              5       // Set DTR high
#define CLRDTR              6       // Set DTR low
#define RESETDEV            7       // Reset device if possible
#define SETBREAK            8       // Set the device break line.
#define CLRBREAK            9       // Clear the device break line.

// PURGE function flags.
#define PURGE_TXABORT       0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT       0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR       0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR       0x0008  // Kill the typeahead buffer if there.

#define LPTx                0x80    // Set if ID is for LPT device

// Modem Status Flags
#define MS_CTS_ON           0x0010
#define MS_DSR_ON           0x0020
#define MS_RING_ON          0x0040
#define MS_RLSD_ON          0x0080

// WaitSoundState() Constants
#define S_QUEUEEMPTY        0
#define S_THRESHOLD         1
#define S_ALLTHRESHOLD      2

// Accent Modes
#define S_NORMAL      0
#define S_LEGATO      1
#define S_STACCATO    2

// SetSoundNoise() Sources
#define S_PERIOD512   0     // Freq = N/512 high pitch, less coarse hiss
#define S_PERIOD1024  1     // Freq = N/1024
#define S_PERIOD2048  2     // Freq = N/2048 low pitch, more coarse hiss
#define S_PERIODVOICE 3     // Source is frequency from voice channel (3)
#define S_WHITE512    4     // Freq = N/512 high pitch, less coarse hiss
#define S_WHITE1024   5     // Freq = N/1024
#define S_WHITE2048   6     // Freq = N/2048 low pitch, more coarse hiss
#define S_WHITEVOICE  7     // Source is frequency from voice channel (3)

#define S_SERDVNA     -1  // Device not available
#define S_SEROFM      -2  // Out of memory
#define S_SERMACT     -3  // Music active
#define S_SERQFUL     -4  // Queue full
#define S_SERBDNT     -5  // Invalid note
#define S_SERDLN      -6  // Invalid note length
#define S_SERDCC      -7  // Invalid note count
#define S_SERDTP      -8  // Invalid tempo
#define S_SERDVL      -9  // Invalid volume
#define S_SERDMD      -10 // Invalid mode
#define S_SERDSH      -11 // Invalid shape
#define S_SERDPT      -12 // Invalid pitch
#define S_SERDFQ      -13 // Invalid frequency
#define S_SERDDR      -14 // Invalid duration
#define S_SERDSR      -15 // Invalid source
#define S_SERDST      -16 // Invalid state

#define NMPWAIT_WAIT_FOREVER            0xffffffff
#define NMPWAIT_NOWAIT                  0x00000001
#define NMPWAIT_USE_DEFAULT_WAIT        0x00000000

#define FS_CASE_IS_PRESERVED            FILE_CASE_PRESERVED_NAMES
#define FS_CASE_SENSITIVE               FILE_CASE_SENSITIVE_SEARCH
#define FS_UNICODE_STORED_ON_DISK       FILE_UNICODE_ON_DISK
#define FS_PERSISTENT_ACLS              FILE_PERSISTENT_ACLS
#define FS_VOL_IS_COMPRESSED            FILE_VOLUME_IS_COMPRESSED
#define FS_FILE_COMPRESSION             FILE_FILE_COMPRESSION
#define FS_FILE_ENCRYPTION              FILE_SUPPORTS_ENCRYPTION

#define FILE_MAP_COPY       SECTION_QUERY
#define FILE_MAP_WRITE      SECTION_MAP_WRITE
#define FILE_MAP_READ       SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS SECTION_ALL_ACCESS

#define OF_READ             0x00000000
#define OF_WRITE            0x00000001
#define OF_READWRITE        0x00000002
#define OF_SHARE_COMPAT     0x00000000
#define OF_SHARE_EXCLUSIVE  0x00000010
#define OF_SHARE_DENY_WRITE 0x00000020
#define OF_SHARE_DENY_READ  0x00000030
#define OF_SHARE_DENY_NONE  0x00000040
#define OF_PARSE            0x00000100
#define OF_DELETE           0x00000200
#define OF_VERIFY           0x00000400
#define OF_CANCEL           0x00000800
#define OF_CREATE           0x00001000
#define OF_PROMPT           0x00002000
#define OF_EXIST            0x00004000
#define OF_REOPEN           0x00008000

#define OFS_MAXPATHNAME 128
struct OFSTRUCT {
  BYTE cBytes;
  BYTE fFixedDisk;
  WORD nErrCode;
  WORD Reserved1;
  WORD Reserved2;
  CHAR szPathName[OFS_MAXPATHNAME];
};

// The Risc compilers support intrinsic functions for interlocked
// increment, decrement, and exchange.

struct MEMORYSTATUSEX {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  DWORDLONG ullTotalPhys;
  DWORDLONG ullAvailPhys;
  DWORDLONG ullTotalPageFile;
  DWORDLONG ullAvailPageFile;
  DWORDLONG ullTotalVirtual;
  DWORDLONG ullAvailVirtual;
  DWORDLONG ullAvailExtendedVirtual;
};
struct PROCESS_HEAP_ENTRY {
  PVOID lpData;
  DWORD cbData;
  BYTE cbOverhead;
  BYTE iRegionIndex;
  WORD wFlags;
  union {
    struct {
      HANDLE hMem;
      DWORD dwReserved[ 3 ];
    } Block;
    struct {
      DWORD dwCommittedSize;
      DWORD dwUnCommittedSize;
      LPVOID lpFirstBlock;
      LPVOID lpLastBlock;
    } Region;
  };
};
struct BY_HANDLE_FILE_INFORMATION {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD dwVolumeSerialNumber;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD nNumberOfLinks;
  DWORD nFileIndexHigh;
  DWORD nFileIndexLow;
};
struct TIME_ZONE_INFORMATION {
  LONG Bias;
  WCHAR StandardName[ 32 ];
  SYSTEMTIME StandardDate;
  LONG StandardBias;
  WCHAR DaylightName[ 32 ];
  SYSTEMTIME DaylightDate;
  LONG DaylightBias;
};
//  Stream id structure
struct WIN32_STREAM_ID{
  DWORD          dwStreamId ;
  DWORD          dwStreamAttributes ;
  LARGE_INTEGER  Size ;
  DWORD          dwStreamNameSize ;
  WCHAR          cStreamName[ ANYSIZE_ARRAY ] ;
};

struct STARTUPINFO{
  DWORD   cb;
  LPSTR   lpReserved;
  LPSTR   lpDesktop;
  LPSTR   lpTitle;
  DWORD   dwX;
  DWORD   dwY;
  DWORD   dwXSize;
  DWORD   dwYSize;
  DWORD   dwXCountChars;
  DWORD   dwYCountChars;
  DWORD   dwFillAttribute;
  DWORD   dwFlags;
  WORD    wShowWindow;
  WORD    cbReserved2;
  LPBYTE  lpReserved2;
  HANDLE  hStdInput;
  HANDLE  hStdOutput;
  HANDLE  hStdError;
};
#define STARTUPINFOW STARTUPINFO
#define STARTUPINFOA STARTUPINFO

#define SHUTDOWN_NORETRY                0x00000001

struct WIN32_FIND_DATAA {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD dwReserved0;
  DWORD dwReserved1;
  CHAR   cFileName[ MAX_PATH ];
  CHAR   cAlternateFileName[ 14 ];
#ifdef _MAC
  DWORD dwFileType;
  DWORD dwCreatorType;
  WORD  wFinderFlags;
#endif
};
struct WIN32_FIND_DATAW {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD dwReserved0;
  DWORD dwReserved1;
  WCHAR  cFileName[ MAX_PATH ];
  WCHAR  cAlternateFileName[ 14 ];
#ifdef _MAC
  DWORD dwFileType;
  DWORD dwCreatorType;
  WORD  wFinderFlags;
#endif
};
#ifdef UNICODE
#define WIN32_FIND_DATA WIN32_FIND_DATAW
#else
#define WIN32_FIND_DATA WIN32_FIND_DATAA
#endif // UNICODE

struct WIN32_FILE_ATTRIBUTE_DATA {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
};

struct EVENTLOG_FULL_INFORMATION
{
  DWORD    dwFull;
};

// Plug-and-Play API's
#define HW_PROFILE_GUIDLEN         39      // 36-characters plus NULL terminator
#define MAX_PROFILE_LEN            80

#define DOCKINFO_UNDOCKED          0x1
#define DOCKINFO_DOCKED            0x2
#define DOCKINFO_USER_SUPPLIED     0x4
#define DOCKINFO_USER_UNDOCKED     DOCKINFO_USER_SUPPLIED | DOCKINFO_UNDOCKED
#define DOCKINFO_USER_DOCKED       DOCKINFO_USER_SUPPLIED | DOCKINFO_DOCKED

struct HW_PROFILE_INFOA{
  DWORD  dwDockInfo;
  CHAR   szHwProfileGuid[HW_PROFILE_GUIDLEN];
  CHAR   szHwProfileName[MAX_PROFILE_LEN];
};
struct HW_PROFILE_INFOW{
  DWORD  dwDockInfo;
  WCHAR  szHwProfileGuid[HW_PROFILE_GUIDLEN];
  WCHAR  szHwProfileName[MAX_PROFILE_LEN];
};
#ifdef UNICODE
#define HW_PROFILE_INFO HW_PROFILE_INFOW
#else
#define HW_PROFILE_INFO HW_PROFILE_INFOA
#endif // UNICODE
#include <winerror.h>

struct SYSTEM_POWER_STATUS {
  BYTE ACLineStatus;
  BYTE BatteryFlag;
  BYTE BatteryLifePercent;
  BYTE Reserved1;
  DWORD BatteryLifeTime;
  DWORD BatteryFullLifeTime;
};

#define ACTCTX_FLAG_PROCESSOR_ARCHITECTURE_VALID    0x00000001
#define ACTCTX_FLAG_LANGID_VALID                    0x00000002
#define ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID        0x00000004
#define ACTCTX_FLAG_RESOURCE_NAME_VALID             0x00000008
#define ACTCTX_FLAG_SET_PROCESS_DEFAULT             0x00000010
#define ACTCTX_FLAG_APPLICATION_NAME_VALID          0x00000020
#define ACTCTX_FLAG_SOURCE_IS_ASSEMBLYREF           0x00000040
#define ACTCTX_FLAG_HMODULE_VALID                   0x00000080

struct ACTCTX{
  ULONG       cbSize;
  DWORD       dwFlags;
  LPCSTR      lpSource;
  USHORT      wProcessorArchitecture;
  LANGID      wLangId;
  LPCSTR      lpAssemblyDirectory;
  LPCSTR      lpResourceName;
  LPCSTR      lpApplicationName;
  HMODULE     hModule;
};
#define ACTCTXW ACTCTX
#define ACTCTXA ACTCTX

struct ACTCTX_SECTION_KEYED_DATA {
  ULONG cbSize;
  ULONG ulDataFormatVersion;
  PVOID lpData;
  ULONG ulLength;
  PVOID lpSectionGlobalData;
  ULONG ulSectionGlobalDataLength;
  PVOID lpSectionBase;
  ULONG ulSectionTotalLength;
  HANDLE hActCtx;
  ULONG ulAssemblyRosterIndex;
};
#define FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX 0x00000001

#if !defined(RC_INVOKED) /* RC complains about long symbols in #ifs */
#if !defined(ACTIVATION_CONTEXT_BASIC_INFORMATION_DEFINED)

struct ACTIVATION_CONTEXT_BASIC_INFORMATION {
  HANDLE  hActCtx;
  DWORD   dwFlags;
};

#define ACTIVATION_CONTEXT_BASIC_INFORMATION_DEFINED 1

#endif // !defined(ACTIVATION_CONTEXT_BASIC_INFORMATION_DEFINED)
#endif

#define QUERY_ACTCTX_FLAG_USE_ACTIVE_ACTCTX 0x00000004
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_HMODULE 0x00000008
#define QUERY_ACTCTX_FLAG_ACTCTX_IS_ADDRESS 0x00000010
#define QUERY_ACTCTX_FLAG_NO_ADDREF         0x80000000

extern WINAPI "kernel32.dll"{
#ifndef NOWINBASEINTERLOCK
#ifndef _NTOS_
	LONG InterlockedIncrement(dword lpAddend);
	LONG InterlockedDecrement(dword lpAddend);
	LONG InterlockedExchange(dword Target,LONG Value);
#define InterlockedExchangePointer(Target,Value) InterlockedExchange(Target,Value)
	LONG InterlockedExchangeAdd(dword Addend,LONG Value);
	LONG InterlockedCompareExchange(dword Destination,LONG Exchange,LONG Comperand);

#define InterlockedCompareExchangePointer(Destination,ExChange,Comperand) \
    InterlockedCompareExchange(Destination,ExChange,Comperand)

#if defined(_SLIST_HEADER_) && !defined(_NTOSP_)
	VOID InitializeSListHead(dword ListHead);
	dword InterlockedPopEntrySList(dword ListHead);
	dword InterlockedPushEntrySList(dword ListHead,dword ListEntry);
	dword InterlockedFlushSList(dword ListHead);
	USHORT QueryDepthSList(dword ListHead);
#endif /* _SLIST_HEADER_ */
#endif /* _NTOS_ */
#endif /* NOWINBASEINTERLOCK */

	BOOL FreeResource(HGLOBAL hResData);
	LPVOID LockResource(HGLOBAL hResData);
#define UnlockResource(hResData) hResData,0
#define MAXINTATOM 0xC000
#define MAKEINTATOM(i)  i
#define INVALID_ATOM 0

	BOOL FreeLibrary(HMODULE hLibModule);
	VOID FreeLibraryAndExitThread(HMODULE hLibModule,DWORD dwExitCode);
	BOOL DisableThreadLibraryCalls(HMODULE hLibModule);
	dword GetProcAddress(HMODULE hModule,LPCSTR lpProcName);
	DWORD GetVersion(VOID);
	HGLOBAL GlobalAlloc(UINT uFlags,SIZE_T dwBytes);
	HGLOBAL GlobalReAlloc(HGLOBAL hMem,SIZE_T dwBytes,UINT uFlags);
	SIZE_T GlobalSize(HGLOBAL hMem);
	UINT GlobalFlags(HGLOBAL hMem);
	LPVOID GlobalLock(HGLOBAL hMem);
	HGLOBAL GlobalHandle(LPCVOID pMem);
	BOOL GlobalUnlock(HGLOBAL hMem);
	HGLOBAL GlobalFree(HGLOBAL hMem);
	SIZE_T GlobalCompact(DWORD dwMinFree);
	VOID GlobalFix(HGLOBAL hMem);
	VOID GlobalUnfix(HGLOBAL hMem);
	LPVOID GlobalWire(HGLOBAL hMem);
	BOOL GlobalUnWire(HGLOBAL hMem);
	VOID GlobalMemoryStatus(dword lpBuffer);
	BOOL GlobalMemoryStatusEx(dword lpBuffer);
	HLOCAL LocalAlloc(UINT uFlags,SIZE_T uBytes);
	HLOCAL LocalReAlloc(HLOCAL hMem,SIZE_T uBytes,UINT uFlags);
	LPVOID LocalLock(HLOCAL hMem);
	HLOCAL LocalHandle(LPCVOID pMem);
	BOOL LocalUnlock(HLOCAL hMem);
	SIZE_T LocalSize(HLOCAL hMem);
	UINT LocalFlags(HLOCAL hMem);
	HLOCAL LocalFree(HLOCAL hMem);
	SIZE_T LocalShrink(HLOCAL hMem,UINT cbNewSize);
	SIZE_T LocalCompact(UINT uMinFree);
	BOOL FlushInstructionCache(HANDLE hProcess,LPCVOID lpBaseAddress,SIZE_T dwSize);
	LPVOID VirtualAlloc(LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect);
	BOOL VirtualFree(LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
	BOOL VirtualProtect(LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);
	SIZE_T VirtualQuery(LPCVOID lpAddress,dword lpBuffer,SIZE_T dwLength);
	LPVOID VirtualAllocEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD flAllocationType,DWORD flProtect);
	UINT GetWriteWatch(DWORD dwFlags,PVOID lpBaseAddress,SIZE_T dwRegionSize,dword lpAddresses,dword lpdwCount,PULONG lpdwGranularity);
	UINT ResetWriteWatch(LPVOID lpBaseAddress,SIZE_T dwRegionSize);
	BOOL VirtualFreeEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD dwFreeType);
	BOOL VirtualProtectEx(HANDLE hProcess,LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);
	SIZE_T VirtualQueryEx(HANDLE hProcess,LPCVOID lpAddress,dword lpBuffer,SIZE_T dwLength);
	HANDLE HeapCreate(DWORD flOptions,SIZE_T dwInitialSize,SIZE_T dwMaximumSize);
	BOOL HeapDestroy(HANDLE hHeap);
	LPVOID HeapAlloc(HANDLE hHeap,DWORD dwFlags,SIZE_T dwBytes);
	LPVOID HeapReAlloc(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem,SIZE_T dwBytes);
	BOOL HeapFree(HANDLE hHeap,DWORD dwFlags,LPVOID lpMem);
	SIZE_T HeapSize(HANDLE hHeap,DWORD dwFlags,LPCVOID lpMem);
	BOOL HeapValidate(HANDLE hHeap,DWORD dwFlags,LPCVOID lpMem);
	SIZE_T HeapCompact(HANDLE hHeap,DWORD dwFlags);
	HANDLE GetProcessHeap(VOID);
	DWORD GetProcessHeaps(DWORD NumberOfHeaps,dword ProcessHeaps);

#define PROCESS_HEAP_REGION             0x0001
#define PROCESS_HEAP_UNCOMMITTED_RANGE  0x0002
#define PROCESS_HEAP_ENTRY_BUSY         0x0004
#define PROCESS_HEAP_ENTRY_MOVEABLE     0x0010
#define PROCESS_HEAP_ENTRY_DDESHARE     0x0020

	BOOL HeapLock(HANDLE hHeap);
	BOOL HeapUnlock(HANDLE hHeap);
	BOOL HeapWalk(HANDLE hHeap,dword lpEntry);
	BOOL HeapSetInformation(PVOID HeapHandle,dword HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength);
	BOOL HeapQueryInformation(PVOID HeapHandle,dword HeapInformationClass,PVOID HeapInformation,SIZE_T HeapInformationLength,dword ReturnLength);

// GetBinaryType return values.

#define SCS_32BIT_BINARY    0
#define SCS_DOS_BINARY      1
#define SCS_WOW_BINARY      2
#define SCS_PIF_BINARY      3
#define SCS_POSIX_BINARY    4
#define SCS_OS216_BINARY    5
#define SCS_64BIT_BINARY    6

# define SCS_THIS_PLATFORM_BINARY SCS_32BIT_BINARY

	BOOL GetBinaryTypeA(LPCSTR lpApplicationName,LPDWORD lpBinaryType);
	BOOL GetBinaryTypeW(LPCWSTR lpApplicationName,LPDWORD lpBinaryType);
#ifdef UNICODE
#define GetBinaryType  GetBinaryTypeW
#else
#define GetBinaryType  GetBinaryTypeA
#endif // !UNICODE

	DWORD GetShortPathNameA(LPCSTR lpszLongPath,LPSTR lpszShortPath,DWORD cchBuffer);
	DWORD GetShortPathNameW(LPCWSTR lpszLongPath,LPWSTR lpszShortPath,DWORD cchBuffer);
#ifdef UNICODE
#define GetShortPathName  GetShortPathNameW
#else
#define GetShortPathName  GetShortPathNameA
#endif // !UNICODE

	DWORD GetLongPathNameA(LPCSTR lpszShortPath,LPSTR lpszLongPath,DWORD cchBuffer);
	DWORD GetLongPathNameW(LPCWSTR lpszShortPath,LPWSTR lpszLongPath,DWORD cchBuffer);
#ifdef UNICODE
#define GetLongPathName  GetLongPathNameW
#else
#define GetLongPathName  GetLongPathNameA
#endif // !UNICODE

	BOOL GetProcessAffinityMask(HANDLE hProcess,dword lpProcessAffinityMask,dword lpSystemAffinityMask);
	BOOL SetProcessAffinityMask(HANDLE hProcess,DWORD_PTR dwProcessAffinityMask);
	BOOL GetProcessTimes(HANDLE hProcess,dword lpCreationTime,dword lpExitTime,dword lpKernelTime,dword lpUserTime);
	BOOL GetProcessIoCounters(HANDLE hProcess,dword lpIoCounters);
	BOOL GetProcessWorkingSetSize(HANDLE hProcess,dword lpMinimumWorkingSetSize,dword lpMaximumWorkingSetSize);
	BOOL SetProcessWorkingSetSize(HANDLE hProcess,SIZE_T dwMinimumWorkingSetSize,SIZE_T dwMaximumWorkingSetSize);
	HANDLE OpenProcess(DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwProcessId);
	HANDLE GetCurrentProcess(VOID);
	DWORD GetCurrentProcessId(VOID);
	VOID ExitProcess(UINT uExitCode);
	BOOL TerminateProcess(HANDLE hProcess,UINT uExitCode);
	BOOL GetExitCodeProcess(HANDLE hProcess,LPDWORD lpExitCode);
	VOID FatalExit(int ExitCode);
	LPWSTR GetEnvironmentStringsW(VOID);
#ifdef UNICODE
#define GetEnvironmentStrings  GetEnvironmentStringsW
#else
	LPSTR GetEnvironmentStrings(VOID);
#define GetEnvironmentStringsA  GetEnvironmentStrings
#endif // !UNICODE

	BOOL FreeEnvironmentStringsA(LPSTR);
	BOOL FreeEnvironmentStringsW(LPWSTR);
#ifdef UNICODE
#define FreeEnvironmentStrings  FreeEnvironmentStringsW
#else
#define FreeEnvironmentStrings  FreeEnvironmentStringsA
#endif // !UNICODE

	VOID RaiseException(DWORD dwExceptionCode,DWORD dwExceptionFlags,DWORD nNumberOfArguments,dword lpArguments);
	LONG UnhandledExceptionFilter(dword ExceptionInfo);
	dword SetUnhandledExceptionFilter(dword lpTopLevelExceptionFilter);
	LPVOID CreateFiber(SIZE_T dwStackSize,dword lpStartAddress,LPVOID lpParameter);
	LPVOID CreateFiberEx(SIZE_T dwStackCommitSize,SIZE_T dwStackReserveSize,DWORD dwFlags,dword lpStartAddress,LPVOID lpParameter);
	VOID DeleteFiber(LPVOID lpFiber);
	LPVOID ConvertThreadToFiber(LPVOID lpParameter);
	BOOL ConvertFiberToThread(VOID);
	VOID SwitchToFiber(LPVOID lpFiber);
	BOOL SwitchToThread(VOID);
	HANDLE CreateThread(dword lpThreadAttributes,SIZE_T dwStackSize,dword lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId);
	HANDLE CreateRemoteThread(HANDLE hProcess,dword lpThreadAttributes,SIZE_T dwStackSize,dword lpStartAddress,LPVOID lpParameter,DWORD dwCreationFlags,LPDWORD lpThreadId);
	HANDLE GetCurrentThread(VOID);
	DWORD GetCurrentThreadId(VOID);
	DWORD_PTR SetThreadAffinityMask(HANDLE hThread,DWORD_PTR dwThreadAffinityMask);
	DWORD SetThreadIdealProcessor(HANDLE hThread,DWORD dwIdealProcessor);
	BOOL SetProcessPriorityBoost(HANDLE hProcess,BOOL bDisablePriorityBoost);
	BOOL GetProcessPriorityBoost(HANDLE hProcess,PBOOL pDisablePriorityBoost);
	BOOL RequestWakeupLatency(dword latency);
	BOOL IsSystemResumeAutomatic(VOID);
	HANDLE OpenThread(DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwThreadId);
	BOOL SetThreadPriority(HANDLE hThread,int nPriority);
	BOOL SetThreadPriorityBoost(HANDLE hThread,BOOL bDisablePriorityBoost);
	BOOL GetThreadPriorityBoost(HANDLE hThread,PBOOL pDisablePriorityBoost);
	int GetThreadPriority(HANDLE hThread);
	BOOL GetThreadTimes(HANDLE hThread,dword lpCreationTime,dword lpExitTime,dword lpKernelTime,dword lpUserTime);
	VOID ExitThread(DWORD dwExitCode);
	BOOL TerminateThread(HANDLE hThread,DWORD dwExitCode);
	BOOL GetExitCodeThread(HANDLE hThread,LPDWORD lpExitCode);
	BOOL GetThreadSelectorEntry(HANDLE hThread,DWORD dwSelector,dword lpSelectorEntry);
	dword SetThreadExecutionState(dword esFlags);
	DWORD GetLastError(VOID);
	VOID SetLastError(DWORD dwErrCode);

#if !defined(RC_INVOKED) // RC warns because "WINBASE_DECLARE_RESTORE_LAST_ERROR" is a bit long.
#if defined(WINBASE_DECLARE_RESTORE_LAST_ERROR)

	VOID RestoreLastError(DWORD dwErrCode);

#define RESTORE_LAST_ERROR_NAME_A      "RestoreLastError"
#define RESTORE_LAST_ERROR_NAME_W     L"RestoreLastError"
#define RESTORE_LAST_ERROR_NAME   "RestoreLastError"

#endif
#endif

	BOOL GetOverlappedResult(HANDLE hFile,dword lpOverlapped,LPDWORD lpNumberOfBytesTransferred,BOOL bWait);
	HANDLE CreateIoCompletionPort(HANDLE FileHandle,HANDLE ExistingCompletionPort,ULONG_PTR CompletionKey,DWORD NumberOfConcurrentThreads);
	BOOL GetQueuedCompletionStatus(HANDLE CompletionPort,LPDWORD lpNumberOfBytesTransferred,dword lpCompletionKey,dword lpOverlapped,DWORD dwMilliseconds);
	BOOL PostQueuedCompletionStatus(HANDLE CompletionPort,DWORD dwNumberOfBytesTransferred,ULONG_PTR dwCompletionKey,dword lpOverlapped);

#define SEM_FAILCRITICALERRORS      0x0001
#define SEM_NOGPFAULTERRORBOX       0x0002
#define SEM_NOALIGNMENTFAULTEXCEPT  0x0004
#define SEM_NOOPENFILEERRORBOX      0x8000

	UINT SetErrorMode(UINT uMode);
	BOOL ReadProcessMemory(HANDLE hProcess,dword lpBaseAddress,LPVOID lpBuffer,SIZE_T nSize,dword lpNumberOfBytesRead);
	BOOL WriteProcessMemory(HANDLE hProcess,LPVOID lpBaseAddress,LPCVOID lpBuffer,SIZE_T nSize,dword lpNumberOfBytesWritten);

#if !defined(MIDL_PASS)
	BOOL GetThreadContext(HANDLE hThread,dword lpContext);
	BOOL SetThreadContext(HANDLE hThread,dword lpContext);
#endif

	DWORD SuspendThread(HANDLE hThread);
	DWORD ResumeThread(HANDLE hThread);
	DWORD QueueUserAPC(dword pfnAPC,HANDLE hThread,ULONG_PTR dwData);
	BOOL IsDebuggerPresent(VOID);
	VOID DebugBreak(VOID);
	BOOL WaitForDebugEvent(dword lpDebugEvent,DWORD dwMilliseconds);
	BOOL ContinueDebugEvent(DWORD dwProcessId,DWORD dwThreadId,DWORD dwContinueStatus);
	BOOL DebugActiveProcess(DWORD dwProcessId);
	BOOL DebugActiveProcessStop(DWORD dwProcessId);
	BOOL DebugSetProcessKillOnExit(BOOL KillOnExit);
	BOOL DebugBreakProcess(HANDLE Process);
	VOID InitializeCriticalSection(dword lpCriticalSection);
	VOID EnterCriticalSection(dword lpCriticalSection);
	VOID LeaveCriticalSection(dword lpCriticalSection);
	BOOL InitializeCriticalSectionAndSpinCount(dword lpCriticalSection,DWORD dwSpinCount);
	DWORD SetCriticalSectionSpinCount(dword lpCriticalSection,DWORD dwSpinCount);
	BOOL TryEnterCriticalSection(dword lpCriticalSection);
	VOID DeleteCriticalSection(dword lpCriticalSection);
	BOOL SetEvent(HANDLE hEvent);
	BOOL ResetEvent(HANDLE hEvent);
	BOOL PulseEvent(HANDLE hEvent);
	BOOL ReleaseSemaphore(HANDLE hSemaphore,LONG lReleaseCount,LPLONG lpPreviousCount);
	BOOL ReleaseMutex(HANDLE hMutex);
	DWORD WaitForSingleObject(HANDLE hHandle,DWORD dwMilliseconds);
	DWORD WaitForMultipleObjects(DWORD nCount,dword lpHandles,BOOL bWaitAll,DWORD dwMilliseconds);
	VOID Sleep(DWORD dwMilliseconds);
	HGLOBAL LoadResource(HMODULE hModule,HRSRC hResInfo);
	DWORD SizeofResource(HMODULE hModule,HRSRC hResInfo);
	ATOM GlobalDeleteAtom(ATOM nAtom);
	BOOL InitAtomTable(DWORD nSize);
	ATOM DeleteAtom(ATOM nAtom);
	UINT SetHandleCount(UINT uNumber);
	DWORD GetLogicalDrives(VOID);
	BOOL LockFile(HANDLE hFile,DWORD dwFileOffsetLow,DWORD dwFileOffsetHigh,DWORD nNumberOfBytesToLockLow,DWORD nNumberOfBytesToLockHigh);
	BOOL UnlockFile(HANDLE hFile,DWORD dwFileOffsetLow,DWORD dwFileOffsetHigh,DWORD nNumberOfBytesToUnlockLow,DWORD nNumberOfBytesToUnlockHigh);
	BOOL LockFileEx(HANDLE hFile,DWORD dwFlags,DWORD dwReserved,DWORD nNumberOfBytesToLockLow,DWORD nNumberOfBytesToLockHigh,dword lpOverlapped);

#define LOCKFILE_FAIL_IMMEDIATELY   0x00000001
#define LOCKFILE_EXCLUSIVE_LOCK     0x00000002

	BOOL UnlockFileEx(HANDLE hFile,DWORD dwReserved,DWORD nNumberOfBytesToUnlockLow,DWORD nNumberOfBytesToUnlockHigh,dword lpOverlapped);
	BOOL GetFileInformationByHandle(HANDLE hFile,dword lpFileInformation);
	DWORD GetFileType(HANDLE hFile);
	DWORD GetFileSize(HANDLE hFile,LPDWORD lpFileSizeHigh);
	BOOL GetFileSizeEx(HANDLE hFile,dword lpFileSize);
	HANDLE GetStdHandle(DWORD nStdHandle);
	BOOL SetStdHandle(DWORD nStdHandle,HANDLE hHandle);
	BOOL WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,LPDWORD lpNumberOfBytesWritten,dword lpOverlapped);
	BOOL ReadFile(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,dword lpOverlapped);
	BOOL FlushFileBuffers(HANDLE hFile);
	BOOL DeviceIoControl(HANDLE hDevice,DWORD dwIoControlCode,LPVOID lpInBuffer,
    DWORD nInBufferSize,LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesReturned,dword lpOverlapped);
	BOOL RequestDeviceWakeup(HANDLE hDevice);
	BOOL CancelDeviceWakeupRequest(HANDLE hDevice);
	BOOL GetDevicePowerState(HANDLE hDevice,dword pfOn);
	BOOL SetMessageWaitingIndicator(HANDLE hMsgIndicator,ULONG ulMsgCount);
	BOOL SetEndOfFile(HANDLE hFile);
	DWORD SetFilePointer(HANDLE hFile,LONG lDistanceToMove,PLONG lpDistanceToMoveHigh,DWORD dwMoveMethod);
	BOOL SetFilePointerEx(HANDLE hFile,dword liDistanceToMove,dword lpNewFilePointer,DWORD dwMoveMethod);
	BOOL FindClose(HANDLE hFindFile);
	BOOL GetFileTime(HANDLE hFile,dword lpCreationTime,dword lpLastAccessTime,dword lpLastWriteTime);
	BOOL SetFileTime(HANDLE hFile,dword lpCreationTime,dword lpLastAccessTime,dword lpLastWriteTime);
	BOOL SetFileValidData(HANDLE hFile,qword ValidDataLength);
	BOOL SetFileShortNameA(HANDLE hFile,LPCSTR lpShortName);
	BOOL SetFileShortNameW(HANDLE hFile,LPCWSTR lpShortName);
#ifdef UNICODE
#define SetFileShortName  SetFileShortNameW
#else
#define SetFileShortName  SetFileShortNameA
#endif // !UNICODE

	BOOL CloseHandle(HANDLE hObject);
	BOOL DuplicateHandle(HANDLE hSourceProcessHandle,HANDLE hSourceHandle,HANDLE hTargetProcessHandle,
    LPHANDLE lpTargetHandle,DWORD dwDesiredAccess,BOOL bInheritHandle,DWORD dwOptions);
	BOOL GetHandleInformation(HANDLE hObject,LPDWORD lpdwFlags);
	BOOL SetHandleInformation(HANDLE hObject,DWORD dwMask,DWORD dwFlags);

#define HANDLE_FLAG_INHERIT             0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE  0x00000002
#define HINSTANCE_ERROR 32

	DWORD LoadModule(LPCSTR lpModuleName,LPVOID lpParameterBlock);
	UINT WinExec(LPCSTR lpCmdLine,UINT uCmdShow);
	BOOL ClearCommBreak(HANDLE hFile);
	BOOL ClearCommError(HANDLE hFile,LPDWORD lpErrors,dword lpStat);
	BOOL SetupComm(HANDLE hFile,DWORD dwInQueue,DWORD dwOutQueue);
	BOOL EscapeCommFunction(HANDLE hFile,DWORD dwFunc);
	BOOL GetCommConfig(HANDLE hCommDev,dword lpCC,LPDWORD lpdwSize);
	BOOL GetCommMask(HANDLE hFile,LPDWORD lpEvtMask);
	BOOL GetCommProperties(HANDLE hFile,dword lpCommProp);
	BOOL GetCommModemStatus(HANDLE hFile,LPDWORD lpModemStat);
	BOOL GetCommState(HANDLE hFile,dword lpDCB);
	BOOL GetCommTimeouts(HANDLE hFile,dword lpCommTimeouts);
	BOOL PurgeComm(HANDLE hFile,DWORD dwFlags);
	BOOL SetCommBreak(HANDLE hFile);
	BOOL SetCommConfig(HANDLE hCommDev,dword lpCC,DWORD dwSize);
	BOOL SetCommMask(HANDLE hFile,DWORD dwEvtMask);
	BOOL SetCommState(HANDLE hFile,dword lpDCB);
	BOOL SetCommTimeouts(HANDLE hFile,dword lpCommTimeouts);
	BOOL TransmitCommChar(HANDLE hFile,char cChar);
	BOOL WaitCommEvent(HANDLE hFile,LPDWORD lpEvtMask,dword lpOverlapped);
	DWORD SetTapePosition(HANDLE hDevice,DWORD dwPositionMethod,DWORD dwPartition,
    DWORD dwOffsetLow,DWORD dwOffsetHigh,BOOL bImmediate);
	DWORD GetTapePosition(HANDLE hDevice,DWORD dwPositionType,LPDWORD lpdwPartition,
    LPDWORD lpdwOffsetLow,LPDWORD lpdwOffsetHigh);
	DWORD PrepareTape(HANDLE hDevice,DWORD dwOperation,BOOL bImmediate);
	DWORD EraseTape(HANDLE hDevice,DWORD dwEraseType,BOOL bImmediate);
	DWORD CreateTapePartition(HANDLE hDevice,DWORD dwPartitionMethod,DWORD dwCount,DWORD dwSize);
	DWORD WriteTapemark(HANDLE hDevice,DWORD dwTapemarkType,DWORD dwTapemarkCount,BOOL bImmediate);
	DWORD GetTapeStatus(HANDLE hDevice);
	DWORD GetTapeParameters(HANDLE hDevice,DWORD dwOperation,LPDWORD lpdwSize,LPVOID lpTapeInformation);

#define GET_TAPE_MEDIA_INFORMATION 0
#define GET_TAPE_DRIVE_INFORMATION 1

	DWORD SetTapeParameters(HANDLE hDevice,DWORD dwOperation,LPVOID lpTapeInformation);

#define SET_TAPE_MEDIA_INFORMATION 0
#define SET_TAPE_DRIVE_INFORMATION 1

	BOOL Beep(DWORD dwFreq,DWORD dwDuration);
	int MulDiv(int nNumber,int nNumerator,int nDenominator);
	VOID GetSystemTime(dword lpSystemTime);
	VOID GetSystemTimeAsFileTime(dword lpSystemTimeAsFileTime);
	BOOL SetSystemTime(dword lpSystemTime);
	VOID GetLocalTime(dword lpSystemTime);
	BOOL SetLocalTime(dword lpSystemTime);
	VOID GetSystemInfo(dword lpSystemInfo);
	VOID GetNativeSystemInfo(dword lpSystemInfo);
	BOOL IsProcessorFeaturePresent(DWORD ProcessorFeature);
	BOOL SystemTimeToTzSpecificLocalTime(dword lpTimeZoneInformation,dword lpUniversalTime,dword lpLocalTime);
	BOOL TzSpecificLocalTimeToSystemTime(dword lpTimeZoneInformation,dword lpLocalTime,dword lpUniversalTime);
	DWORD GetTimeZoneInformation(dword lpTimeZoneInformation);
	BOOL SetTimeZoneInformation(dword lpTimeZoneInformation);

// Routines to convert back and forth between system time and file time
	BOOL SystemTimeToFileTime(dword lpSystemTime,dword lpFileTime);
	BOOL FileTimeToLocalFileTime(dword lpFileTime,dword lpLocalFileTime);
	BOOL LocalFileTimeToFileTime(dword lpLocalFileTime,dword lpFileTime);
	BOOL FileTimeToSystemTime(dword lpFileTime,dword lpSystemTime);
	LONG CompareFileTime(dword lpFileTime1,dword lpFileTime2);
	BOOL FileTimeToDosDateTime(dword lpFileTime,LPWORD lpFatDate,LPWORD lpFatTime);
	BOOL DosDateTimeToFileTime(WORD wFatDate,WORD wFatTime,dword lpFileTime);
	DWORD GetTickCount(VOID);
	BOOL SetSystemTimeAdjustment(DWORD dwTimeAdjustment,BOOL bTimeAdjustmentDisabled);
	BOOL GetSystemTimeAdjustment(PDWORD lpTimeAdjustment,PDWORD lpTimeIncrement,PBOOL lpTimeAdjustmentDisabled);
#if !defined(MIDL_PASS)
	DWORD FormatMessageA(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,
    LPSTR lpBuffer,DWORD nSize,dword Arguments);
	DWORD FormatMessageW(DWORD dwFlags,LPCVOID lpSource,DWORD dwMessageId,DWORD dwLanguageId,
    LPWSTR lpBuffer,DWORD nSize,dword Arguments);
#ifdef UNICODE
#define FormatMessage  FormatMessageW
#else
#define FormatMessage  FormatMessageA
#endif // !UNICODE
#endif

#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0x00000100
#define FORMAT_MESSAGE_IGNORE_INSERTS  0x00000200
#define FORMAT_MESSAGE_FROM_STRING     0x00000400
#define FORMAT_MESSAGE_FROM_HMODULE    0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM     0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY  0x00002000
#define FORMAT_MESSAGE_MAX_WIDTH_MASK  0x000000FF

	BOOL CreatePipe(dword hReadPipe,dword hWritePipe,dword lpPipeAttributes,DWORD nSize);
	BOOL ConnectNamedPipe(HANDLE hNamedPipe,dword lpOverlapped);
	BOOL DisconnectNamedPipe(HANDLE hNamedPipe);
	BOOL SetNamedPipeHandleState(HANDLE hNamedPipe,LPDWORD lpMode,LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout);
	BOOL GetNamedPipeInfo(HANDLE hNamedPipe,LPDWORD lpFlags,LPDWORD lpOutBufferSize,
    LPDWORD lpInBufferSize,LPDWORD lpMaxInstances);
	BOOL PeekNamedPipe(HANDLE hNamedPipe,LPVOID lpBuffer,DWORD nBufferSize,
    LPDWORD lpBytesRead,LPDWORD lpTotalBytesAvail,LPDWORD lpBytesLeftThisMessage);
	BOOL TransactNamedPipe(HANDLE hNamedPipe,LPVOID lpInBuffer,DWORD nInBufferSize,
    LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,dword lpOverlapped);
	HANDLE CreateMailslotA(LPCSTR lpName,DWORD nMaxMessageSize,DWORD lReadTimeout,dword lpSecurityAttributes);
	HANDLE CreateMailslotW(LPCWSTR lpName,DWORD nMaxMessageSize,DWORD lReadTimeout,dword lpSecurityAttributes);
#ifdef UNICODE
#define CreateMailslot  CreateMailslotW
#else
#define CreateMailslot  CreateMailslotA
#endif // !UNICODE

	BOOL GetMailslotInfo(HANDLE hMailslot,LPDWORD lpMaxMessageSize,LPDWORD lpNextSize,
    LPDWORD lpMessageCount,LPDWORD lpReadTimeout);
	BOOL SetMailslotInfo(HANDLE hMailslot,DWORD lReadTimeout);
	LPVOID MapViewOfFile(HANDLE hFileMappingObject,DWORD dwDesiredAccess,DWORD dwFileOffsetHigh,
    DWORD dwFileOffsetLow,SIZE_T dwNumberOfBytesToMap);
	BOOL FlushViewOfFile(LPCVOID lpBaseAddress,SIZE_T dwNumberOfBytesToFlush);
	BOOL UnmapViewOfFile(LPCVOID lpBaseAddress);

// File Encryption API
	BOOL EncryptFileA(LPCSTR lpFileName);
	BOOL EncryptFileW(LPCWSTR lpFileName);
#ifdef UNICODE
#define EncryptFile  EncryptFileW
#else
#define EncryptFile  EncryptFileA
#endif // !UNICODE

	BOOL DecryptFileA(LPCSTR lpFileName,DWORD dwReserved);
	BOOL DecryptFileW(LPCWSTR lpFileName,DWORD dwReserved);
#ifdef UNICODE
#define DecryptFile  DecryptFileW
#else
#define DecryptFile  DecryptFileA
#endif // !UNICODE

//  Encryption Status Value
#define FILE_ENCRYPTABLE                0
#define FILE_IS_ENCRYPTED               1
#define FILE_SYSTEM_ATTR                2
#define FILE_ROOT_DIR                   3
#define FILE_SYSTEM_DIR                 4
#define FILE_UNKNOWN                    5
#define FILE_SYSTEM_NOT_SUPPORT         6
#define FILE_USER_DISALLOWED            7
#define FILE_READ_ONLY                  8
#define FILE_DIR_DISALLOWED             9

	BOOL FileEncryptionStatusA(LPCSTR lpFileName,LPDWORD lpStatus);
	BOOL FileEncryptionStatusW(LPCWSTR lpFileName,LPDWORD lpStatus);
#ifdef UNICODE
#define FileEncryptionStatus  FileEncryptionStatusW
#else
#define FileEncryptionStatus  FileEncryptionStatusA
#endif // !UNICODE

// Currently defined recovery flags
#define EFS_USE_RECOVERY_KEYS  0x1

//  OpenRaw flag values

#define CREATE_FOR_IMPORT  1
#define CREATE_FOR_DIR     2
#define OVERWRITE_HIDDEN   4

	DWORD OpenEncryptedFileRawA(LPCSTR lpFileName,ULONG ulFlags,dword pvContext);
	DWORD OpenEncryptedFileRawW(LPCWSTR lpFileName,ULONG ulFlags,dword pvContext);
#ifdef UNICODE
#define OpenEncryptedFileRaw  OpenEncryptedFileRawW
#else
#define OpenEncryptedFileRaw  OpenEncryptedFileRawA
#endif // !UNICODE

	DWORD ReadEncryptedFileRaw(dword pfExportCallback,dword pvCallbackContext,dword pvContext);
	DWORD WriteEncryptedFileRaw(dword pfImportCallback,PVOID pvCallbackContext,PVOID pvContext);
	VOID CloseEncryptedFileRaw(PVOID pvContext);

// _l Compat Functions
	int lstrcmpA(LPCSTR lpString1,LPCSTR lpString2);
	int lstrcmpW(LPCWSTR lpString1,LPCWSTR lpString2);
#ifdef UNICODE
#define lstrcmp  lstrcmpW
#else
#define lstrcmp  lstrcmpA
#endif // !UNICODE

	int lstrcmpiA(LPCSTR lpString1,LPCSTR lpString2);
	int lstrcmpiW(LPCWSTR lpString1,LPCWSTR lpString2);
#ifdef UNICODE
#define lstrcmpi  lstrcmpiW
#else
#define lstrcmpi  lstrcmpiA
#endif // !UNICODE

	LPSTR lstrcpynA(LPSTR lpString1,LPCSTR lpString2,int iMaxLength);
	LPWSTR lstrcpynW(LPWSTR lpString1,LPCWSTR lpString2,int iMaxLength);
#ifdef UNICODE
#define lstrcpyn  lstrcpynW
#else
#define lstrcpyn  lstrcpynA
#endif // !UNICODE

	LPSTR lstrcpyA(LPSTR lpString1,LPCSTR lpString2);
	LPWSTR lstrcpyW(LPWSTR lpString1,LPCWSTR lpString2);
#ifdef UNICODE
#define lstrcpy  lstrcpyW
#else
#define lstrcpy  lstrcpyA
#endif // !UNICODE

	LPSTR lstrcatA(LPSTR lpString1,LPCSTR lpString2);
	LPWSTR lstrcatW(LPWSTR lpString1,LPCWSTR lpString2);
#ifdef UNICODE
#define lstrcat  lstrcatW
#else
#define lstrcat  lstrcatA
#endif // !UNICODE

int	lstrlenA(LPCSTR lpString);
int lstrlenW(LPCWSTR lpString);
#ifdef UNICODE
#define lstrlen  lstrlenW
#else
#define lstrlen  lstrlenA
#endif // !UNICODE

	HFILE OpenFile(LPCSTR lpFileName,dword lpReOpenBuff,UINT uStyle);
	HFILE _lopen(LPCSTR lpPathName,int iReadWrite);
	HFILE _lcreat(LPCSTR lpPathName,int  iAttribute);
	UINT _lread(HFILE hFile,LPVOID lpBuffer,UINT uBytes);
	UINT _lwrite(HFILE hFile,LPCSTR lpBuffer,UINT uBytes);
	long _hread(HFILE hFile,LPVOID lpBuffer,long lBytes);
	long _hwrite(HFILE hFile,LPCSTR lpBuffer,long lBytes);
	HFILE _lclose(HFILE hFile);
	LONG _llseek(HFILE hFile,LONG lOffset,int iOrigin);
	DWORD TlsAlloc(VOID);

#define TLS_OUT_OF_INDEXES ((DWORD)0xFFFFFFFF)

	LPVOID TlsGetValue(DWORD dwTlsIndex);
	BOOL TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue);
	BOOL TlsFree(DWORD dwTlsIndex);
	DWORD SleepEx(DWORD dwMilliseconds,BOOL bAlertable);
	DWORD WaitForSingleObjectEx(HANDLE hHandle,DWORD dwMilliseconds,BOOL bAlertable);
	DWORD WaitForMultipleObjectsEx(DWORD nCount,dword lpHandles,BOOL bWaitAll,
    DWORD dwMilliseconds,BOOL bAlertable);
	DWORD	SignalObjectAndWait(HANDLE hObjectToSignal,HANDLE hObjectToWaitOn,
    DWORD dwMilliseconds,BOOL bAlertable);
	BOOL ReadFileEx(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,
    dword lpOverlapped,dword lpCompletionRoutine);
	BOOL WriteFileEx(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,
    dword lpOverlapped,dword lpCompletionRoutine);
	BOOL BackupRead(HANDLE hFile,LPBYTE lpBuffer,DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,BOOL bAbort,BOOL bProcessSecurity,dword lpContext);
	BOOL BackupSeek(HANDLE hFile,DWORD dwLowBytesToSeek,DWORD dwHighBytesToSeek,
    LPDWORD lpdwLowByteSeeked,LPDWORD lpdwHighByteSeeked,dword lpContext);
	BOOL BackupWrite(HANDLE hFile,LPBYTE lpBuffer,DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,BOOL bAbort,BOOL bProcessSecurity,dword lpContext);

//  Stream Ids
#define BACKUP_INVALID          0x00000000
#define BACKUP_DATA             0x00000001
#define BACKUP_EA_DATA          0x00000002
#define BACKUP_SECURITY_DATA    0x00000003
#define BACKUP_ALTERNATE_DATA   0x00000004
#define BACKUP_LINK             0x00000005
#define BACKUP_PROPERTY_DATA    0x00000006
#define BACKUP_OBJECT_ID        0x00000007
#define BACKUP_REPARSE_DATA     0x00000008
#define BACKUP_SPARSE_BLOCK     0x00000009

//  Stream Attributes
#define STREAM_NORMAL_ATTRIBUTE         0x00000000
#define STREAM_MODIFIED_WHEN_READ       0x00000001
#define STREAM_CONTAINS_SECURITY        0x00000002
#define STREAM_CONTAINS_PROPERTIES      0x00000004
#define STREAM_SPARSE_ATTRIBUTE         0x00000008

	BOOL ReadFileScatter(HANDLE hFile,dword aSegmentArray,DWORD nNumberOfBytesToRead,
    LPDWORD lpReserved,dword lpOverlapped);
	BOOL WriteFileGather(HANDLE hFile,dword aSegmentArray,DWORD nNumberOfBytesToWrite,
    LPDWORD lpReserved,dword lpOverlapped);

// Dual Mode API below this line. Dual Mode Structures also included.
#define STARTF_USESHOWWINDOW    0x00000001
#define STARTF_USESIZE          0x00000002
#define STARTF_USEPOSITION      0x00000004
#define STARTF_USECOUNTCHARS    0x00000008
#define STARTF_USEFILLATTRIBUTE 0x00000010
#define STARTF_RUNFULLSCREEN    0x00000020  // ignored for non-x86 platforms
#define STARTF_FORCEONFEEDBACK  0x00000040
#define STARTF_FORCEOFFFEEDBACK 0x00000080
#define STARTF_USESTDHANDLES    0x00000100
#define STARTF_USEHOTKEY        0x00000200

	HANDLE CreateMutexA(dword lpMutexAttributes,BOOL bInitialOwner,LPCSTR lpName);
	HANDLE CreateMutexW(dword lpMutexAttributes,BOOL bInitialOwner,LPCWSTR lpName);
#ifdef UNICODE
#define CreateMutex  CreateMutexW
#else
#define CreateMutex  CreateMutexA
#endif // !UNICODE

	HANDLE OpenMutexA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpName);
HANDLE OpenMutexW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpName);
#ifdef UNICODE
#define OpenMutex  OpenMutexW
#else
#define OpenMutex  OpenMutexA
#endif // !UNICODE

	HANDLE CreateEventA(dword lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCSTR lpName);
	HANDLE CreateEventW(dword lpEventAttributes,BOOL bManualReset,BOOL bInitialState,LPCWSTR lpName);
#ifdef UNICODE
#define CreateEvent  CreateEventW
#else
#define CreateEvent  CreateEventA
#endif // !UNICODE

	HANDLE OpenEventA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpName);
	HANDLE OpenEventW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpName);
#ifdef UNICODE
#define OpenEvent  OpenEventW
#else
#define OpenEvent  OpenEventA
#endif // !UNICODE

	HANDLE CreateSemaphoreA(dword lpSemaphoreAttributes,LONG lInitialCount,LONG lMaximumCount,LPCSTR lpName);
	HANDLE CreateSemaphoreW(dword lpSemaphoreAttributes,LONG lInitialCount,LONG lMaximumCount,LPCWSTR lpName);
#ifdef UNICODE
#define CreateSemaphore  CreateSemaphoreW
#else
#define CreateSemaphore  CreateSemaphoreA
#endif // !UNICODE

	HANDLE OpenSemaphoreA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpName);
	HANDLE OpenSemaphoreW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpName);
#ifdef UNICODE
#define OpenSemaphore  OpenSemaphoreW
#else
#define OpenSemaphore  OpenSemaphoreA
#endif // !UNICODE

	HANDLE CreateWaitableTimerA(dword lpTimerAttributes,BOOL bManualReset,LPCSTR lpTimerName);
	HANDLE CreateWaitableTimerW(dword lpTimerAttributes,BOOL bManualReset,LPCWSTR lpTimerName);
#ifdef UNICODE
#define CreateWaitableTimer  CreateWaitableTimerW
#else
#define CreateWaitableTimer  CreateWaitableTimerA
#endif // !UNICODE

	HANDLE OpenWaitableTimerA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpTimerName);
	HANDLE OpenWaitableTimerW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpTimerName);
#ifdef UNICODE
#define OpenWaitableTimer  OpenWaitableTimerW
#else
#define OpenWaitableTimer  OpenWaitableTimerA
#endif // !UNICODE

	BOOL SetWaitableTimer(HANDLE hTimer,dword lpDueTime,LONG lPeriod,dword pfnCompletionRoutine,
    LPVOID lpArgToCompletionRoutine,BOOL fResume);
	BOOL CancelWaitableTimer(HANDLE hTimer);
	HANDLE CreateFileMappingA(HANDLE hFile,dword lpFileMappingAttributes,DWORD flProtect,
    DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCSTR lpName);
	HANDLE CreateFileMappingW(HANDLE hFile,dword lpFileMappingAttributes,DWORD flProtect,
    DWORD dwMaximumSizeHigh,DWORD dwMaximumSizeLow,LPCWSTR lpName);
#ifdef UNICODE
#define CreateFileMapping  CreateFileMappingW
#else
#define CreateFileMapping  CreateFileMappingA
#endif // !UNICODE

	HANDLE OpenFileMappingA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpName);
	HANDLE OpenFileMappingW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpName);
#ifdef UNICODE
#define OpenFileMapping  OpenFileMappingW
#else
#define OpenFileMapping  OpenFileMappingA
#endif // !UNICODE

	DWORD GetLogicalDriveStringsA(DWORD nBufferLength,LPSTR lpBuffer);
	DWORD GetLogicalDriveStringsW(DWORD nBufferLength,LPWSTR lpBuffer);
#ifdef UNICODE
#define GetLogicalDriveStrings  GetLogicalDriveStringsW
#else
#define GetLogicalDriveStrings  GetLogicalDriveStringsA
#endif // !UNICODE

enum MEMORY_RESOURCE_NOTIFICATION_TYPE{
  LowMemoryResourceNotification,
  HighMemoryResourceNotification
};
	HANDLE CreateMemoryResourceNotification(dword NotificationType);
	BOOL QueryMemoryResourceNotification(HANDLE ResourceNotificationHandle,PBOOL ResourceState);
	HMODULE LoadLibraryA(LPCSTR lpLibFileName);
	HMODULE LoadLibraryW(LPCWSTR lpLibFileName);
#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#else
#define LoadLibrary  LoadLibraryA
#endif // !UNICODE

	HMODULE LoadLibraryExA(LPCSTR lpLibFileName,HANDLE hFile,DWORD dwFlags);
	HMODULE LoadLibraryExW(LPCWSTR lpLibFileName,HANDLE hFile,DWORD dwFlags);
#ifdef UNICODE
#define LoadLibraryEx  LoadLibraryExW
#else
#define LoadLibraryEx  LoadLibraryExA
#endif // !UNICODE

#define DONT_RESOLVE_DLL_REFERENCES     0x00000001
#define LOAD_LIBRARY_AS_DATAFILE        0x00000002
#define LOAD_WITH_ALTERED_SEARCH_PATH   0x00000008
#define LOAD_IGNORE_CODE_AUTHZ_LEVEL    0x00000010

	DWORD GetModuleFileNameA(HMODULE hModule,LPSTR lpFilename,DWORD nSize);
	DWORD GetModuleFileNameW(HMODULE hModule,LPWSTR lpFilename,DWORD nSize);
#ifdef UNICODE
#define GetModuleFileName  GetModuleFileNameW
#else
#define GetModuleFileName  GetModuleFileNameA
#endif // !UNICODE

	HMODULE GetModuleHandleA(LPCSTR lpModuleName);
	HMODULE GetModuleHandleW(LPCWSTR lpModuleName);
#ifdef UNICODE
#define GetModuleHandle  GetModuleHandleW
#else
#define GetModuleHandle  GetModuleHandleA
#endif // !UNICODE

#if !defined(RC_INVOKED)

#define GET_MODULE_HANDLE_EX_FLAG_PIN                 0x00000001
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT  0x00000002
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS        0x00000004

	BOOL GetModuleHandleExA(DWORD dwFlags,LPCSTR lpModuleName,dword phModule);
	BOOL GetModuleHandleExW(DWORD dwFlags,LPCWSTR lpModuleName,dword phModule);
#ifdef UNICODE
#define GetModuleHandleEx  GetModuleHandleExW
#else
#define GetModuleHandleEx  GetModuleHandleExA
#endif // !UNICODE

#endif

	BOOL CreateProcessA(LPCSTR lpApplicationName,LPSTR lpCommandLine,dword lpProcessAttributes,
    dword lpThreadAttributes,BOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,dword lpStartupInfo,dword lpProcessInformation);
	BOOL CreateProcessW(LPCWSTR lpApplicationName,LPWSTR lpCommandLine,dword lpProcessAttributes,
    dword lpThreadAttributes,BOOL bInheritHandles,DWORD dwCreationFlags,LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,dword lpStartupInfo,dword lpProcessInformation);
#ifdef UNICODE
#define CreateProcess  CreateProcessW
#else
#define CreateProcess  CreateProcessA
#endif // !UNICODE

	BOOL SetProcessShutdownParameters(DWORD dwLevel,DWORD dwFlags);
	BOOL GetProcessShutdownParameters(LPDWORD lpdwLevel,LPDWORD lpdwFlags);
	DWORD GetProcessVersion(DWORD ProcessId);
	VOID FatalAppExitA(UINT uAction,LPCSTR lpMessageText);
	VOID FatalAppExitW(UINT uAction,LPCWSTR lpMessageText);
#ifdef UNICODE
#define FatalAppExit  FatalAppExitW
#else
#define FatalAppExit  FatalAppExitA
#endif // !UNICODE

	VOID GetStartupInfoA(dword lpStartupInfo);
	VOID GetStartupInfoW(dword lpStartupInfo);
#ifdef UNICODE
#define GetStartupInfo  GetStartupInfoW
#else
#define GetStartupInfo  GetStartupInfoA
#endif // !UNICODE

	LPSTR GetCommandLineA(VOID);
	LPWSTR GetCommandLineW(VOID);
#ifdef UNICODE
#define GetCommandLine  GetCommandLineW
#else
#define GetCommandLine  GetCommandLineA
#endif // !UNICODE

	DWORD GetEnvironmentVariableA(LPCSTR lpName,LPSTR lpBuffer,DWORD nSize);
	DWORD GetEnvironmentVariableW(LPCWSTR lpName,LPWSTR lpBuffer,DWORD nSize);
#ifdef UNICODE
#define GetEnvironmentVariable  GetEnvironmentVariableW
#else
#define GetEnvironmentVariable  GetEnvironmentVariableA
#endif // !UNICODE

	BOOL SetEnvironmentVariableA(LPCSTR lpName,LPCSTR lpValue);
	BOOL SetEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpValue);
#ifdef UNICODE
#define SetEnvironmentVariable  SetEnvironmentVariableW
#else
#define SetEnvironmentVariable  SetEnvironmentVariableA
#endif // !UNICODE

	DWORD ExpandEnvironmentStringsA(LPCSTR lpSrc,LPSTR lpDst,DWORD nSize);
	DWORD ExpandEnvironmentStringsW(LPCWSTR lpSrc,LPWSTR lpDst,DWORD nSize);
#ifdef UNICODE
#define ExpandEnvironmentStrings  ExpandEnvironmentStringsW
#else
#define ExpandEnvironmentStrings  ExpandEnvironmentStringsA
#endif // !UNICODE
	DWORD GetFirmwareEnvironmentVariableA(LPCSTR lpName,LPCSTR lpGuid,PVOID pBuffer,DWORD nSize);
	DWORD GetFirmwareEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpGuid,PVOID pBuffer,DWORD nSize);
#ifdef UNICODE
#define GetFirmwareEnvironmentVariable  GetFirmwareEnvironmentVariableW
#else
#define GetFirmwareEnvironmentVariable  GetFirmwareEnvironmentVariableA
#endif // !UNICODE

	BOOL SetFirmwareEnvironmentVariableA(LPCSTR lpName,LPCSTR lpGuid,PVOID pValue,DWORD nSize);
	BOOL SetFirmwareEnvironmentVariableW(LPCWSTR lpName,LPCWSTR lpGuid,PVOID pValue,DWORD nSize);
#ifdef UNICODE
#define SetFirmwareEnvironmentVariable  SetFirmwareEnvironmentVariableW
#else
#define SetFirmwareEnvironmentVariable  SetFirmwareEnvironmentVariableA
#endif // !UNICODE

	VOID OutputDebugStringA(LPCSTR lpOutputString);
	VOID OutputDebugStringW(LPCWSTR lpOutputString);
#ifdef UNICODE
#define OutputDebugString  OutputDebugStringW
#else
#define OutputDebugString  OutputDebugStringA
#endif // !UNICODE

	HRSRC FindResourceA(HMODULE hModule,LPCSTR lpName,LPCSTR lpType);
	HRSRC FindResourceW(HMODULE hModule,LPCWSTR lpName,LPCWSTR lpType);
#ifdef UNICODE
#define FindResource  FindResourceW
#else
#define FindResource  FindResourceA
#endif // !UNICODE

	HRSRC FindResourceExA(HMODULE hModule,LPCSTR lpType,LPCSTR lpName,WORD wLanguage);
	HRSRC FindResourceExW(HMODULE hModule,LPCWSTR lpType,LPCWSTR lpName,WORD wLanguage);
#ifdef UNICODE
#define FindResourceEx  FindResourceExW
#else
#define FindResourceEx  FindResourceExA
#endif // !UNICODE

	BOOL EnumResourceTypesA(HMODULE hModule,dword lpEnumFunc,dword lParam);
	BOOL EnumResourceTypesW(HMODULE hModule,dword lpEnumFunc,dword lParam);
#ifdef UNICODE
#define EnumResourceTypes  EnumResourceTypesW
#else
#define EnumResourceTypes  EnumResourceTypesA
#endif // !UNICODE

	BOOL EnumResourceNamesA(HMODULE hModule,LPCSTR lpType,dword lpEnumFunc,dword lParam);
	BOOL EnumResourceNamesW(HMODULE hModule,LPCWSTR lpType,dword lpEnumFunc,dword lParam);
#ifdef UNICODE
#define EnumResourceNames  EnumResourceNamesW
#else
#define EnumResourceNames  EnumResourceNamesA
#endif // !UNICODE

	BOOL EnumResourceLanguagesA(HMODULE hModule,LPCSTR lpType,LPCSTR lpName,dword lpEnumFunc,dword lParam);
	BOOL EnumResourceLanguagesW(HMODULE hModule,LPCWSTR lpType,LPCWSTR lpName,dword lpEnumFunc,dword lParam);
#ifdef UNICODE
#define EnumResourceLanguages  EnumResourceLanguagesW
#else
#define EnumResourceLanguages  EnumResourceLanguagesA
#endif // !UNICODE

	HANDLE BeginUpdateResourceA(LPCSTR pFileName,BOOL bDeleteExistingResources);
	HANDLE BeginUpdateResourceW(LPCWSTR pFileName,BOOL bDeleteExistingResources);
#ifdef UNICODE
#define BeginUpdateResource  BeginUpdateResourceW
#else
#define BeginUpdateResource  BeginUpdateResourceA
#endif // !UNICODE

	BOOL UpdateResourceA(HANDLE hUpdate,LPCSTR lpType,LPCSTR lpName,WORD wLanguage,LPVOID lpData,DWORD cbData);
	BOOL UpdateResourceW(HANDLE hUpdate,LPCWSTR lpType,LPCWSTR lpName,WORD wLanguage,LPVOID lpData,DWORD cbData);
#ifdef UNICODE
#define UpdateResource  UpdateResourceW
#else
#define UpdateResource  UpdateResourceA
#endif // !UNICODE

	BOOL EndUpdateResourceA(HANDLE hUpdate,BOOL fDiscard);
	BOOL EndUpdateResourceW(HANDLE hUpdate,BOOL fDiscard);
#ifdef UNICODE
#define EndUpdateResource  EndUpdateResourceW
#else
#define EndUpdateResource  EndUpdateResourceA
#endif // !UNICODE

	ATOM GlobalAddAtomA(LPCSTR lpString);
	ATOM GlobalAddAtomW(LPCWSTR lpString);
#ifdef UNICODE
#define GlobalAddAtom  GlobalAddAtomW
#else
#define GlobalAddAtom  GlobalAddAtomA
#endif // !UNICODE

	ATOM GlobalFindAtomA(LPCSTR lpString);
	ATOM GlobalFindAtomW(LPCWSTR lpString);
#ifdef UNICODE
#define GlobalFindAtom  GlobalFindAtomW
#else
#define GlobalFindAtom  GlobalFindAtomA
#endif // !UNICODE

	UINT GlobalGetAtomNameA(ATOM nAtom,LPSTR lpBuffer,int nSize);
	UINT GlobalGetAtomNameW(ATOM nAtom,LPWSTR lpBuffer,int nSize);
#ifdef UNICODE
#define GlobalGetAtomName  GlobalGetAtomNameW
#else
#define GlobalGetAtomName  GlobalGetAtomNameA
#endif // !UNICODE

	ATOM AddAtomA(LPCSTR lpString);
	ATOM AddAtomW(LPCWSTR lpString);
#ifdef UNICODE
#define AddAtom  AddAtomW
#else
#define AddAtom  AddAtomA
#endif // !UNICODE

	ATOM FindAtomA(LPCSTR lpString);
	ATOM FindAtomW(LPCWSTR lpString);
#ifdef UNICODE
#define FindAtom  FindAtomW
#else
#define FindAtom  FindAtomA
#endif // !UNICODE

	UINT GetAtomNameA(ATOM nAtom,LPSTR lpBuffer,int nSize);
	UINT GetAtomNameW(ATOM nAtom,LPWSTR lpBuffer,int nSize);
#ifdef UNICODE
#define GetAtomName  GetAtomNameW
#else
#define GetAtomName  GetAtomNameA
#endif // !UNICODE

	UINT GetProfileIntA(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault);
	UINT GetProfileIntW(LPCWSTR lpAppName,LPCWSTR lpKeyName,INT nDefault);
#ifdef UNICODE
#define GetProfileInt  GetProfileIntW
#else
#define GetProfileInt  GetProfileIntA
#endif // !UNICODE

	DWORD GetProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR lpReturnedString,DWORD nSize);
	DWORD GetProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpDefault,LPWSTR lpReturnedString,DWORD nSize);
#ifdef UNICODE
#define GetProfileString  GetProfileStringW
#else
#define GetProfileString  GetProfileStringA
#endif // !UNICODE

	BOOL WriteProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString);
	BOOL WriteProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpString);
#ifdef UNICODE
#define WriteProfileString  WriteProfileStringW
#else
#define WriteProfileString  WriteProfileStringA
#endif // !UNICODE

	DWORD GetProfileSectionA(LPCSTR lpAppName,LPSTR lpReturnedString,DWORD nSize);
	DWORD GetProfileSectionW(LPCWSTR lpAppName,LPWSTR lpReturnedString,DWORD nSize);
#ifdef UNICODE
#define GetProfileSection  GetProfileSectionW
#else
#define GetProfileSection  GetProfileSectionA
#endif // !UNICODE

	BOOL WriteProfileSectionA(LPCSTR lpAppName,LPCSTR lpString);
	BOOL WriteProfileSectionW(LPCWSTR lpAppName,LPCWSTR lpString);
#ifdef UNICODE
#define WriteProfileSection  WriteProfileSectionW
#else
#define WriteProfileSection  WriteProfileSectionA
#endif // !UNICODE

	UINT GetPrivateProfileIntA(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault,LPCSTR lpFileName);
	UINT GetPrivateProfileIntW(LPCWSTR lpAppName,LPCWSTR lpKeyName,INT nDefault,LPCWSTR lpFileName);
#ifdef UNICODE
#define GetPrivateProfileInt  GetPrivateProfileIntW
#else
#define GetPrivateProfileInt  GetPrivateProfileIntA
#endif // !UNICODE

	DWORD GetPrivateProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,
    LPSTR lpReturnedString,DWORD nSize,LPCSTR lpFileName);
	DWORD GetPrivateProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpDefault,
    LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName);
#ifdef UNICODE
#define GetPrivateProfileString  GetPrivateProfileStringW
#else
#define GetPrivateProfileString  GetPrivateProfileStringA
#endif // !UNICODE

	BOOL WritePrivateProfileStringA(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString,LPCSTR lpFileName);
	BOOL WritePrivateProfileStringW(LPCWSTR lpAppName,LPCWSTR lpKeyName,LPCWSTR lpString,LPCWSTR lpFileName);
#ifdef UNICODE
#define WritePrivateProfileString  WritePrivateProfileStringW
#else
#define WritePrivateProfileString  WritePrivateProfileStringA
#endif // !UNICODE

	DWORD GetPrivateProfileSectionA(LPCSTR lpAppName,LPSTR lpReturnedString,DWORD nSize,LPCSTR lpFileName);
	DWORD GetPrivateProfileSectionW(LPCWSTR lpAppName,LPWSTR lpReturnedString,DWORD nSize,LPCWSTR lpFileName);
#ifdef UNICODE
#define GetPrivateProfileSection  GetPrivateProfileSectionW
#else
#define GetPrivateProfileSection  GetPrivateProfileSectionA
#endif // !UNICODE

	BOOL WritePrivateProfileSectionA(LPCSTR lpAppName,LPCSTR lpString,LPCSTR lpFileName);
	BOOL WritePrivateProfileSectionW(LPCWSTR lpAppName,LPCWSTR lpString,LPCWSTR lpFileName);
#ifdef UNICODE
#define WritePrivateProfileSection  WritePrivateProfileSectionW
#else
#define WritePrivateProfileSection  WritePrivateProfileSectionA
#endif // !UNICODE

	DWORD GetPrivateProfileSectionNamesA(LPSTR lpszReturnBuffer,DWORD nSize,LPCSTR lpFileName);
	DWORD GetPrivateProfileSectionNamesW(LPWSTR lpszReturnBuffer,DWORD nSize,LPCWSTR lpFileName);
#ifdef UNICODE
#define GetPrivateProfileSectionNames  GetPrivateProfileSectionNamesW
#else
#define GetPrivateProfileSectionNames  GetPrivateProfileSectionNamesA
#endif // !UNICODE

	BOOL GetPrivateProfileStructA(LPCSTR lpszSection,LPCSTR lpszKey,LPVOID lpStruct,
    UINT uSizeStruct,LPCSTR szFile);
	BOOL GetPrivateProfileStructW(LPCWSTR lpszSection,LPCWSTR lpszKey,
    LPVOID lpStruct,UINT uSizeStruct,LPCWSTR szFile);
#ifdef UNICODE
#define GetPrivateProfileStruct  GetPrivateProfileStructW
#else
#define GetPrivateProfileStruct  GetPrivateProfileStructA
#endif // !UNICODE

	BOOL WritePrivateProfileStructA(LPCSTR lpszSection,LPCSTR lpszKey,LPVOID lpStruct,
    UINT uSizeStruct,LPCSTR szFile);
	BOOL WritePrivateProfileStructW(LPCWSTR lpszSection,LPCWSTR lpszKey,
    LPVOID lpStruct,UINT uSizeStruct,LPCWSTR szFile);
#ifdef UNICODE
#define WritePrivateProfileStruct  WritePrivateProfileStructW
#else
#define WritePrivateProfileStruct  WritePrivateProfileStructA
#endif // !UNICODE

	UINT GetDriveTypeA(LPCSTR lpRootPathName);
	UINT GetDriveTypeW(LPCWSTR lpRootPathName);
#ifdef UNICODE
#define GetDriveType  GetDriveTypeW
#else
#define GetDriveType  GetDriveTypeA
	#endif // !UNICODE

	UINT GetSystemDirectoryA(LPSTR lpBuffer,UINT uSize);
	UINT GetSystemDirectoryW(LPWSTR lpBuffer,UINT uSize);
#ifdef UNICODE
#define GetSystemDirectory  GetSystemDirectoryW
#else
#define GetSystemDirectory  GetSystemDirectoryA
#endif // !UNICODE

	DWORD GetTempPathA(DWORD nBufferLength,LPSTR lpBuffer);
	DWORD GetTempPathW(DWORD nBufferLength,LPWSTR lpBuffer);
#ifdef UNICODE
#define GetTempPath  GetTempPathW
#else
#define GetTempPath  GetTempPathA
#endif // !UNICODE

	UINT GetTempFileNameA(LPCSTR lpPathName,LPCSTR lpPrefixString,UINT uUnique,LPSTR lpTempFileName);
	UINT GetTempFileNameW(LPCWSTR lpPathName,LPCWSTR lpPrefixString,UINT uUnique,LPWSTR lpTempFileName);
#ifdef UNICODE
#define GetTempFileName  GetTempFileNameW
#else
#define GetTempFileName  GetTempFileNameA
#endif // !UNICODE

	UINT GetWindowsDirectoryA(LPSTR lpBuffer,UINT uSize);
	UINT GetWindowsDirectoryW(LPWSTR lpBuffer,UINT uSize);
#ifdef UNICODE
#define GetWindowsDirectory  GetWindowsDirectoryW
#else
#define GetWindowsDirectory  GetWindowsDirectoryA
#endif // !UNICODE

	UINT GetSystemWindowsDirectoryA(LPSTR lpBuffer,UINT uSize);
	UINT GetSystemWindowsDirectoryW(LPWSTR lpBuffer,UINT uSize);
#ifdef UNICODE
#define GetSystemWindowsDirectory  GetSystemWindowsDirectoryW
#else
#define GetSystemWindowsDirectory  GetSystemWindowsDirectoryA
#endif // !UNICODE

#if !defined(RC_INVOKED) // RC warns because "WINBASE_DECLARE_GET_SYSTEM_WOW64_DIRECTORY" is a bit long.
	UINT GetSystemWow64DirectoryA(LPSTR lpBuffer,UINT uSize);
	UINT GetSystemWow64DirectoryW(LPWSTR lpBuffer,UINT uSize);
#ifdef UNICODE
#define GetSystemWow64Directory  GetSystemWow64DirectoryW
#else
#define GetSystemWow64Directory  GetSystemWow64DirectoryA
#endif // !UNICODE

// GetProcAddress only accepts GET_SYSTEM_WOW64_DIRECTORY_NAME_A_A,
// GET_SYSTEM_WOW64_DIRECTORY_NAME_W_A, GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A.
// The others are if you want to use the strings in some other way.
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_A      "GetSystemWow64DirectoryA"
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_W     L"GetSystemWow64DirectoryA"
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_A_T "GetSystemWow64DirectoryA"
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_A      "GetSystemWow64DirectoryW"
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_W     L"GetSystemWow64DirectoryW"
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_W_T "GetSystemWow64DirectoryW"

#ifdef UNICODE
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A GET_SYSTEM_WOW64_DIRECTORY_NAME_W_A
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_W GET_SYSTEM_WOW64_DIRECTORY_NAME_W_W
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_T GET_SYSTEM_WOW64_DIRECTORY_NAME_W_T
#else
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_A GET_SYSTEM_WOW64_DIRECTORY_NAME_A_A
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_W GET_SYSTEM_WOW64_DIRECTORY_NAME_A_W
#define GET_SYSTEM_WOW64_DIRECTORY_NAME_T_T GET_SYSTEM_WOW64_DIRECTORY_NAME_A_T
#endif

#endif

	BOOL SetCurrentDirectoryA(LPCSTR lpPathName);
	BOOL SetCurrentDirectoryW(LPCWSTR lpPathName);
#ifdef UNICODE
#define SetCurrentDirectory  SetCurrentDirectoryW
#else
#define SetCurrentDirectory  SetCurrentDirectoryA
#endif // !UNICODE

	DWORD GetCurrentDirectoryA(DWORD nBufferLength,LPSTR lpBuffer);
	DWORD GetCurrentDirectoryW(DWORD nBufferLength,LPWSTR lpBuffer);
#ifdef UNICODE
#define GetCurrentDirectory  GetCurrentDirectoryW
#else
#define GetCurrentDirectory  GetCurrentDirectoryA
#endif // !UNICODE

	BOOL GetDiskFreeSpaceA(LPCSTR lpRootPathName,LPDWORD lpSectorsPerCluster,
    LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
	BOOL GetDiskFreeSpaceW(LPCWSTR lpRootPathName,LPDWORD lpSectorsPerCluster,
    LPDWORD lpBytesPerSector,LPDWORD lpNumberOfFreeClusters,LPDWORD lpTotalNumberOfClusters);
#ifdef UNICODE
#define GetDiskFreeSpace  GetDiskFreeSpaceW
#else
#define GetDiskFreeSpace  GetDiskFreeSpaceA
#endif // !UNICODE

	BOOL GetDiskFreeSpaceExA(LPCSTR lpDirectoryName,dword lpFreeBytesAvailableToCaller,
    dword lpTotalNumberOfBytes,dword lpTotalNumberOfFreeBytes);
	BOOL GetDiskFreeSpaceExW(LPCWSTR lpDirectoryName,dword lpFreeBytesAvailableToCaller,
    dword lpTotalNumberOfBytes,dword lpTotalNumberOfFreeBytes);
#ifdef UNICODE
#define GetDiskFreeSpaceEx  GetDiskFreeSpaceExW
#else
#define GetDiskFreeSpaceEx  GetDiskFreeSpaceExA
#endif // !UNICODE

	BOOL CreateDirectoryA(LPCSTR lpPathName,dword lpSecurityAttributes);
	BOOL CreateDirectoryW(LPCWSTR lpPathName,dword lpSecurityAttributes);
#ifdef UNICODE
#define CreateDirectory  CreateDirectoryW
#else
#define CreateDirectory  CreateDirectoryA
#endif // !UNICODE

	BOOL CreateDirectoryExA(LPCSTR lpTemplateDirectory,LPCSTR lpNewDirectory,dword lpSecurityAttributes);
	BOOL CreateDirectoryExW(LPCWSTR lpTemplateDirectory,LPCWSTR lpNewDirectory,dword lpSecurityAttributes);
#ifdef UNICODE
#define CreateDirectoryEx  CreateDirectoryExW
#else
#define CreateDirectoryEx  CreateDirectoryExA
#endif // !UNICODE

	BOOL RemoveDirectoryA(LPCSTR lpPathName);
	BOOL RemoveDirectoryW(LPCWSTR lpPathName);
#ifdef UNICODE
#define RemoveDirectory  RemoveDirectoryW
#else
#define RemoveDirectory  RemoveDirectoryA
#endif // !UNICODE

	DWORD GetFullPathNameA(LPCSTR lpFileName,DWORD nBufferLength,LPSTR lpBuffer,dword lpFilePart);
	DWORD GetFullPathNameW(LPCWSTR lpFileName,DWORD nBufferLength,LPWSTR lpBuffer,dword lpFilePart);
#ifdef UNICODE
#define GetFullPathName  GetFullPathNameW
#else
#define GetFullPathName  GetFullPathNameA
#endif // !UNICODE

#define DDD_RAW_TARGET_PATH         0x00000001
#define DDD_REMOVE_DEFINITION       0x00000002
#define DDD_EXACT_MATCH_ON_REMOVE   0x00000004
#define DDD_NO_BROADCAST_SYSTEM     0x00000008
#define DDD_LUID_BROADCAST_DRIVE    0x00000010

	BOOL DefineDosDeviceA(DWORD dwFlags,LPCSTR lpDeviceName,LPCSTR lpTargetPath);
	BOOL DefineDosDeviceW(DWORD dwFlags,LPCWSTR lpDeviceName,LPCWSTR lpTargetPath);
#ifdef UNICODE
#define DefineDosDevice  DefineDosDeviceW
#else
#define DefineDosDevice  DefineDosDeviceA
#endif // !UNICODE

	DWORD QueryDosDeviceA(LPCSTR lpDeviceName,LPSTR lpTargetPath,DWORD ucchMax);
	DWORD QueryDosDeviceW(LPCWSTR lpDeviceName,LPWSTR lpTargetPath,DWORD ucchMax);
#ifdef UNICODE
#define QueryDosDevice  QueryDosDeviceW
#else
#define QueryDosDevice  QueryDosDeviceA
#endif // !UNICODE

#define EXPAND_LOCAL_DRIVES

	HANDLE CreateFileA(LPCSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
    dword lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
	HANDLE CreateFileW(LPCWSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
    dword lpSecurityAttributes,DWORD dwCreationDisposition,DWORD dwFlagsAndAttributes,HANDLE hTemplateFile);
#ifdef UNICODE
#define CreateFile  CreateFileW
#else
#define CreateFile  CreateFileA
#endif // !UNICODE

	BOOL SetFileAttributesA(LPCSTR lpFileName,DWORD dwFileAttributes);
	BOOL SetFileAttributesW(LPCWSTR lpFileName,DWORD dwFileAttributes);
#ifdef UNICODE
#define SetFileAttributes  SetFileAttributesW
#else
#define SetFileAttributes  SetFileAttributesA
#endif // !UNICODE

	DWORD GetFileAttributesA(LPCSTR lpFileName);
	DWORD GetFileAttributesW(LPCWSTR lpFileName);
#ifdef UNICODE
#define GetFileAttributes  GetFileAttributesW
#else
#define GetFileAttributes  GetFileAttributesA
#endif // !UNICODE

enum GET_FILEEX_INFO_LEVELS{
  GetFileExInfoStandard,
  GetFileExMaxInfoLevel
};
	BOOL GetFileAttributesExA(LPCSTR lpFileName,dword fInfoLevelId,LPVOID lpFileInformation);
	BOOL GetFileAttributesExW(LPCWSTR lpFileName,dword fInfoLevelId,LPVOID lpFileInformation);
#ifdef UNICODE
#define GetFileAttributesEx  GetFileAttributesExW
#else
#define GetFileAttributesEx  GetFileAttributesExA
#endif // !UNICODE

	DWORD GetCompressedFileSizeA(LPCSTR lpFileName,LPDWORD lpFileSizeHigh);
	DWORD GetCompressedFileSizeW(LPCWSTR lpFileName,LPDWORD lpFileSizeHigh);
#ifdef UNICODE
#define GetCompressedFileSize  GetCompressedFileSizeW
#else
#define GetCompressedFileSize  GetCompressedFileSizeA
#endif // !UNICODE

	BOOL DeleteFileA(LPCSTR lpFileName);
	BOOL DeleteFileW(LPCWSTR lpFileName);
#ifdef UNICODE
#define DeleteFile  DeleteFileW
#else
#define DeleteFile  DeleteFileA
#endif // !UNICODE

enum FINDEX_INFO_LEVELS{
  FindExInfoStandard,
  FindExInfoMaxInfoLevel
};

enum FINDEX_SEARCH_OPS{
  FindExSearchNameMatch,
  FindExSearchLimitToDirectories,
  FindExSearchLimitToDevices,
  FindExSearchMaxSearchOp
};
#define FIND_FIRST_EX_CASE_SENSITIVE   0x00000001
	HANDLE FindFirstFileExA(LPCSTR lpFileName,dword fInfoLevelId,LPVOID lpFindFileData,
    dword fSearchOp,LPVOID lpSearchFilter,DWORD dwAdditionalFlags);
	HANDLE FindFirstFileExW(LPCWSTR lpFileName,dword fInfoLevelId,LPVOID lpFindFileData,
    dword fSearchOp,LPVOID lpSearchFilter,DWORD dwAdditionalFlags);
#ifdef UNICODE
#define FindFirstFileEx  FindFirstFileExW
#else
#define FindFirstFileEx  FindFirstFileExA
#endif // !UNICODE

	HANDLE FindFirstFileA(LPCSTR lpFileName,dword lpFindFileData);
	HANDLE FindFirstFileW(LPCWSTR lpFileName,dword lpFindFileData);
#ifdef UNICODE
#define FindFirstFile  FindFirstFileW
#else
#define FindFirstFile  FindFirstFileA
#endif // !UNICODE

	BOOL FindNextFileA(HANDLE hFindFile,dword lpFindFileData);
	BOOL FindNextFileW(HANDLE hFindFile,dword lpFindFileData);
#ifdef UNICODE
#define FindNextFile  FindNextFileW
#else
#define FindNextFile  FindNextFileA
#endif // !UNICODE

	DWORD SearchPathA(LPCSTR lpPath,LPCSTR lpFileName,LPCSTR lpExtension,
    DWORD nBufferLength,LPSTR lpBuffer,dword lpFilePart);
	DWORD SearchPathW(LPCWSTR lpPath,LPCWSTR lpFileName,LPCWSTR lpExtension,
    DWORD nBufferLength,LPWSTR lpBuffer,dword pFilePart);
#ifdef UNICODE
#define SearchPath  SearchPathW
#else
#define SearchPath  SearchPathA
#endif // !UNICODE

	BOOL CopyFileA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,BOOL bFailIfExists);
	BOOL CopyFileW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,BOOL bFailIfExists);
#ifdef UNICODE
#define CopyFile  CopyFileW
#else
#define CopyFile  CopyFileA
#endif // !UNICODE

	BOOL CopyFileExA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,
    dword lpProgressRoutine,LPVOID lpData,LPBOOL pbCancel,DWORD dwCopyFlags);
	BOOL CopyFileExW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,
    dword lpProgressRoutine,LPVOID lpData,LPBOOL pbCancel,DWORD dwCopyFlags);
#ifdef UNICODE
#define CopyFileEx  CopyFileExW
#else
#define CopyFileEx  CopyFileExA
#endif // !UNICODE

	BOOL MoveFileA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName);
	BOOL MoveFileW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName);
#ifdef UNICODE
#define MoveFile  MoveFileW
#else
#define MoveFile  MoveFileA
#endif // !UNICODE

	BOOL MoveFileExA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,DWORD dwFlags);
	BOOL MoveFileExW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,DWORD dwFlags);
#ifdef UNICODE
#define MoveFileEx  MoveFileExW
#else
#define MoveFileEx  MoveFileExA
#endif // !UNICODE

	BOOL MoveFileWithProgressA(LPCSTR lpExistingFileName,LPCSTR lpNewFileName,
    dword lpProgressRoutine,LPVOID lpData,DWORD dwFlags);
	BOOL MoveFileWithProgressW(LPCWSTR lpExistingFileName,LPCWSTR lpNewFileName,
    dword lpProgressRoutine,LPVOID lpData,DWORD dwFlags);
#ifdef UNICODE
#define MoveFileWithProgress  MoveFileWithProgressW
#else
#define MoveFileWithProgress  MoveFileWithProgressA
#endif // !UNICODE

#define MOVEFILE_REPLACE_EXISTING       0x00000001
#define MOVEFILE_COPY_ALLOWED           0x00000002
#define MOVEFILE_DELAY_UNTIL_REBOOT     0x00000004
#define MOVEFILE_WRITE_THROUGH          0x00000008
#define MOVEFILE_CREATE_HARDLINK        0x00000010
#define MOVEFILE_FAIL_IF_NOT_TRACKABLE  0x00000020

	BOOL ReplaceFileA(LPCSTR lpReplacedFileName,LPCSTR lpReplacementFileName,
    LPCSTR lpBackupFileName,DWORD dwReplaceFlags,LPVOID lpExclude,LPVOID lpReserved);
	BOOL ReplaceFileW(LPCWSTR lpReplacedFileName,LPCWSTR lpReplacementFileName,
    LPCWSTR lpBackupFileName,DWORD dwReplaceFlags,LPVOID lpExclude,LPVOID lpReserved);
#ifdef UNICODE
#define ReplaceFile  ReplaceFileW
#else
#define ReplaceFile  ReplaceFileA
#endif // !UNICODE

// API call to create hard links.
	BOOL CreateHardLinkA(LPCSTR lpFileName,LPCSTR lpExistingFileName,dword lpSecurityAttributes);
	BOOL CreateHardLinkW(LPCWSTR lpFileName,LPCWSTR lpExistingFileName,dword lpSecurityAttributes);
#ifdef UNICODE
#define CreateHardLink  CreateHardLinkW
#else
#define CreateHardLink  CreateHardLinkA
#endif // !UNICODE

	HANDLE CreateNamedPipeA(LPCSTR lpName,DWORD dwOpenMode,DWORD dwPipeMode,DWORD nMaxInstances,
    DWORD nOutBufferSize,DWORD nInBufferSize,DWORD nDefaultTimeOut,dword lpSecurityAttributes);
	HANDLE CreateNamedPipeW(LPCWSTR lpName,DWORD dwOpenMode,DWORD dwPipeMode,DWORD nMaxInstances,
    DWORD nOutBufferSize,DWORD nInBufferSize,DWORD nDefaultTimeOut,dword lpSecurityAttributes);
#ifdef UNICODE
#define CreateNamedPipe  CreateNamedPipeW
#else
#define CreateNamedPipe  CreateNamedPipeA
#endif // !UNICODE

	BOOL GetNamedPipeHandleStateA(HANDLE hNamedPipe,LPDWORD lpState,LPDWORD lpCurInstances,
    LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout,LPSTR lpUserName,DWORD nMaxUserNameSize);
	BOOL GetNamedPipeHandleStateW(HANDLE hNamedPipe,LPDWORD lpState,LPDWORD lpCurInstances,
    LPDWORD lpMaxCollectionCount,LPDWORD lpCollectDataTimeout,LPWSTR lpUserName,DWORD nMaxUserNameSize);
#ifdef UNICODE
#define GetNamedPipeHandleState  GetNamedPipeHandleStateW
#else
#define GetNamedPipeHandleState  GetNamedPipeHandleStateA
#endif // !UNICODE

	BOOL CallNamedPipeA(LPCSTR lpNamedPipeName,LPVOID lpInBuffer,DWORD nInBufferSize,
    LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,DWORD nTimeOut);
	BOOL CallNamedPipeW(LPCWSTR lpNamedPipeName,LPVOID lpInBuffer,DWORD nInBufferSize,
    LPVOID lpOutBuffer,DWORD nOutBufferSize,LPDWORD lpBytesRead,DWORD nTimeOut);
#ifdef UNICODE
#define CallNamedPipe  CallNamedPipeW
#else
#define CallNamedPipe  CallNamedPipeA
#endif // !UNICODE

	BOOL WaitNamedPipeA(LPCSTR lpNamedPipeName,DWORD nTimeOut);
	BOOL WaitNamedPipeW(LPCWSTR lpNamedPipeName,DWORD nTimeOut);
#ifdef UNICODE
#define WaitNamedPipe  WaitNamedPipeW
#else
#define WaitNamedPipe  WaitNamedPipeA
#endif // !UNICODE

	BOOL SetVolumeLabelA(LPCSTR lpRootPathName,LPCSTR lpVolumeName);
	BOOL SetVolumeLabelW(LPCWSTR lpRootPathName,LPCWSTR lpVolumeName);
#ifdef UNICODE
#define SetVolumeLabel  SetVolumeLabelW
#else
#define SetVolumeLabel  SetVolumeLabelA
#endif // !UNICODE

	VOID SetFileApisToOEM(VOID);
	VOID SetFileApisToANSI(VOID);
	BOOL AreFileApisANSI(VOID);
	BOOL GetVolumeInformationA(LPCSTR lpRootPathName,LPSTR lpVolumeNameBuffer,
    DWORD nVolumeNameSize,LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,LPSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize);
	BOOL GetVolumeInformationW(LPCWSTR lpRootPathName,LPWSTR lpVolumeNameBuffer,
    DWORD nVolumeNameSize,LPDWORD lpVolumeSerialNumber,LPDWORD lpMaximumComponentLength,
    LPDWORD lpFileSystemFlags,LPWSTR lpFileSystemNameBuffer,DWORD nFileSystemNameSize);
#ifdef UNICODE
#define GetVolumeInformation  GetVolumeInformationW
#else
#define GetVolumeInformation  GetVolumeInformationA
#endif // !UNICODE

	BOOL CancelIo(HANDLE hFile);

	HANDLE FindFirstChangeNotificationA(LPCSTR lpPathName,BOOL bWatchSubtree,DWORD dwNotifyFilter);
	HANDLE FindFirstChangeNotificationW(LPCWSTR lpPathName,BOOL bWatchSubtree,DWORD dwNotifyFilter);
#ifdef UNICODE
#define FindFirstChangeNotification  FindFirstChangeNotificationW
#else
#define FindFirstChangeNotification  FindFirstChangeNotificationA
#endif // !UNICODE

	BOOL FindNextChangeNotification(HANDLE hChangeHandle);
	BOOL FindCloseChangeNotification(HANDLE hChangeHandle);
	BOOL ReadDirectoryChangesW(HANDLE hDirectory,LPVOID lpBuffer,DWORD nBufferLength,
	  BOOL bWatchSubtree,DWORD dwNotifyFilter,LPDWORD lpBytesReturned,dword lpOverlapped,dword lpCompletionRoutine);
	BOOL VirtualLock(LPVOID lpAddress,SIZE_T dwSize);
	BOOL VirtualUnlock(LPVOID lpAddress,SIZE_T dwSize);
	LPVOID MapViewOfFileEx(HANDLE hFileMappingObject,DWORD dwDesiredAccess,
    DWORD dwFileOffsetHigh,DWORD dwFileOffsetLow,SIZE_T dwNumberOfBytesToMap,LPVOID lpBaseAddress);
	BOOL SetPriorityClass(HANDLE hProcess,DWORD dwPriorityClass);
	DWORD GetPriorityClass(HANDLE hProcess);
	BOOL IsBadReadPtr(dword lp,dword ucb);
	BOOL IsBadWritePtr(LPVOID lp,dword ucb);
	BOOL IsBadHugeReadPtr(dword lp,dword ucb);
	BOOL IsBadHugeWritePtr(LPVOID lp,dword ucb);
	BOOL IsBadCodePtr(dword lpfn);
	BOOL IsBadStringPtrA(LPCSTR lpsz,dword ucchMax);
	BOOL IsBadStringPtrW(LPCWSTR lpsz,dword ucchMax);
#ifdef UNICODE
#define IsBadStringPtr  IsBadStringPtrW
#else
#define IsBadStringPtr  IsBadStringPtrA
#endif // !UNICODE


	BOOL BuildCommDCBA(LPCSTR lpDef,dword lpDCB);
	BOOL BuildCommDCBW(LPCWSTR lpDef,dword lpDCB);
#ifdef UNICODE
#define BuildCommDCB  BuildCommDCBW
#else
#define BuildCommDCB  BuildCommDCBA
#endif // !UNICODE

	BOOL BuildCommDCBAndTimeoutsA(LPCSTR lpDef,dword lpDCB,dword lpCommTimeouts);
	BOOL BuildCommDCBAndTimeoutsW(LPCWSTR lpDef,dword lpDCB,dword lpCommTimeouts);
#ifdef UNICODE
#define BuildCommDCBAndTimeouts  BuildCommDCBAndTimeoutsW
#else
#define BuildCommDCBAndTimeouts  BuildCommDCBAndTimeoutsA
#endif // !UNICODE

	BOOL CommConfigDialogA(LPCSTR lpszName,dword hWnd,dword lpCC);
	BOOL CommConfigDialogW(LPCWSTR lpszName,dword hWnd,dword lpCC);
#ifdef UNICODE
#define CommConfigDialog  CommConfigDialogW
#else
#define CommConfigDialog  CommConfigDialogA
#endif // !UNICODE

	BOOL GetDefaultCommConfigA(LPCSTR lpszName,dword lpCC,LPDWORD lpdwSize);
	BOOL GetDefaultCommConfigW(LPCWSTR lpszName,dword lpCC,LPDWORD lpdwSize);
#ifdef UNICODE
#define GetDefaultCommConfig  GetDefaultCommConfigW
#else
#define GetDefaultCommConfig  GetDefaultCommConfigA
#endif // !UNICODE

	BOOL SetDefaultCommConfigA(LPCSTR lpszName,dword lpCC,DWORD dwSize);
	BOOL SetDefaultCommConfigW(LPCWSTR lpszName,dword lpCC,DWORD dwSize);
#ifdef UNICODE
#define SetDefaultCommConfig  SetDefaultCommConfigW
#else
#define SetDefaultCommConfig  SetDefaultCommConfigA
#endif // !UNICODE

#ifndef _MAC
#define MAX_COMPUTERNAME_LENGTH 15
#else
#define MAX_COMPUTERNAME_LENGTH 31
#endif

	BOOL GetComputerNameA(LPSTR lpBuffer,LPDWORD nSize);
	BOOL GetComputerNameW(LPWSTR lpBuffer,LPDWORD nSize);
#ifdef UNICODE
#define GetComputerName  GetComputerNameW
#else
#define GetComputerName  GetComputerNameA
#endif // !UNICODE

	BOOL SetComputerNameA(LPCSTR lpComputerName);
	BOOL SetComputerNameW(LPCWSTR lpComputerName);
#ifdef UNICODE
#define SetComputerName  SetComputerNameW
#else
#define SetComputerName  SetComputerNameA
#endif // !UNICODE

	BOOL GetComputerNameExA(dword NameType,LPSTR lpBuffer,LPDWORD nSize);
	BOOL GetComputerNameExW(dword NameType,LPWSTR lpBuffer,LPDWORD nSize);
#ifdef UNICODE
#define GetComputerNameEx  GetComputerNameExW
#else
#define GetComputerNameEx  GetComputerNameExA
#endif // !UNICODE

	BOOL SetComputerNameExA(dword NameType,LPCSTR lpBuffer);
	BOOL SetComputerNameExW(dword NameType,LPCWSTR lpBuffer);
#ifdef UNICODE
#define SetComputerNameEx  SetComputerNameExW
#else
#define SetComputerNameEx  SetComputerNameExA
#endif // !UNICODE

	DWORD AddLocalAlternateComputerNameA(LPCSTR lpDnsFQHostname,ULONG ulFlags);
	DWORD AddLocalAlternateComputerNameW(LPCWSTR lpDnsFQHostname,ULONG ulFlags);
#ifdef UNICODE
#define AddLocalAlternateComputerName  AddLocalAlternateComputerNameW
#else
#define AddLocalAlternateComputerName  AddLocalAlternateComputerNameA
#endif // !UNICODE

	DWORD RemoveLocalAlternateComputerNameA(LPCSTR lpAltDnsFQHostname,ULONG ulFlags);
	DWORD RemoveLocalAlternateComputerNameW(LPCWSTR lpAltDnsFQHostname,ULONG ulFlags);
#ifdef UNICODE
#define RemoveLocalAlternateComputerName  RemoveLocalAlternateComputerNameW
#else
#define RemoveLocalAlternateComputerName  RemoveLocalAlternateComputerNameA
#endif // !UNICODE

	DWORD SetLocalPrimaryComputerNameA(LPCSTR lpAltDnsFQHostname,ULONG ulFlags);
	DWORD SetLocalPrimaryComputerNameW(LPCWSTR lpAltDnsFQHostname,ULONG ulFlags);
#ifdef UNICODE
#define SetLocalPrimaryComputerName  SetLocalPrimaryComputerNameW
#else
#define SetLocalPrimaryComputerName  SetLocalPrimaryComputerNameA
#endif // !UNICODE

enum COMPUTER_NAME_TYPE{
  PrimaryComputerName,
  AlternateComputerNames,
  AllComputerNames,
  ComputerNameTypeMax
};
	DWORD EnumerateLocalComputerNamesA(dword NameType,ULONG ulFlags,LPSTR lpDnsFQHostname,LPDWORD nSize);
	DWORD EnumerateLocalComputerNamesW(dword NameType,ULONG ulFlags,LPWSTR lpDnsFQHostname,LPDWORD nSize);
#ifdef UNICODE
#define EnumerateLocalComputerNames  EnumerateLocalComputerNamesW
#else
#define EnumerateLocalComputerNames  EnumerateLocalComputerNamesA
#endif // !UNICODE

	BOOL DnsHostnameToComputerNameA(LPCSTR Hostname,LPSTR ComputerName,LPDWORD nSize);
	BOOL DnsHostnameToComputerNameW(LPCWSTR Hostname,LPWSTR ComputerName,LPDWORD nSize);
#ifdef UNICODE
#define DnsHostnameToComputerName  DnsHostnameToComputerNameW
#else
#define DnsHostnameToComputerName  DnsHostnameToComputerNameA
#endif // !UNICODE

	BOOL LogonUserExA(LPSTR lpszUsername,LPSTR lpszDomain,LPSTR lpszPassword,
    DWORD dwLogonType,DWORD dwLogonProvider,dword phToken,dword ppLogonSid,
    dword ppProfileBuffer,LPDWORD pdwProfileLength,dword pQuotaLimits);
	BOOL LogonUserExW(LPWSTR lpszUsername,LPWSTR lpszDomain,LPWSTR lpszPassword,
    DWORD dwLogonType,DWORD dwLogonProvider,dword phToken,dword ppLogonSid,
    dword ppProfileBuffer,LPDWORD pdwProfileLength,dword pQuotaLimits);
#ifdef UNICODE
#define LogonUserEx  LogonUserExW
#else
#define LogonUserEx  LogonUserExA
#endif // !UNICODE

// LogonFlags
#define LOGON_WITH_PROFILE              0x00000001
#define LOGON_NETCREDENTIALS_ONLY       0x00000002

	BOOL CreateProcessWithLogonW(LPCWSTR lpUsername,LPCWSTR lpDomain,LPCWSTR lpPassword,
    DWORD dwLogonFlags,LPCWSTR lpApplicationName,LPWSTR lpCommandLine,DWORD dwCreationFlags,
    LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,dword lpStartupInfo,dword lpProcessInformation);
	BOOL ImpersonateAnonymousToken(HANDLE ThreadHandle);
	BOOL DuplicateTokenEx(HANDLE hExistingToken,DWORD dwDesiredAccess,dword lpTokenAttributes,
    dword ImpersonationLevel,dword TokenType,dword phNewToken);
	BOOL CreateRestrictedToken(HANDLE ExistingTokenHandle,DWORD Flags,DWORD DisableSidCount,
    dword SidsToDisable,DWORD DeletePrivilegeCount,dword PrivilegesToDelete,
    DWORD RestrictedSidCount,dword SidsToRestrict,dword NewTokenHandle);
	BOOL IsTokenRestricted(HANDLE TokenHandle);
	BOOL IsTokenUntrusted(HANDLE TokenHandle);
	BOOL CheckTokenMembership(HANDLE TokenHandle,dword SidToCheck,PBOOL IsMember);

// Thread pool API's
	BOOL RegisterWaitForSingleObject(dword phNewWaitObject,HANDLE hObject,
    dword Callback,PVOID Context,ULONG dwMilliseconds,ULONG dwFlags);
	HANDLE RegisterWaitForSingleObjectEx(HANDLE hObject,dword Callback,
    PVOID Context,ULONG dwMilliseconds,ULONG dwFlags);
	BOOL UnregisterWait(HANDLE WaitHandle);
	BOOL UnregisterWaitEx(HANDLE WaitHandle,HANDLE CompletionEvent);
	BOOL QueueUserWorkItem(dword Function,PVOID Context,ULONG Flags);
	BOOL BindIoCompletionCallback(HANDLE FileHandle,dword Function,ULONG Flags);
	HANDLE CreateTimerQueue(VOID);
	BOOL CreateTimerQueueTimer(dword phNewTimer,HANDLE TimerQueue,dword Callback,
    PVOID Parameter,DWORD DueTime,DWORD Period,ULONG Flags) ;
	BOOL ChangeTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer,ULONG DueTime,ULONG Period);
	BOOL DeleteTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer,HANDLE CompletionEvent);
	BOOL DeleteTimerQueueEx(HANDLE TimerQueue,HANDLE CompletionEvent);
	HANDLE SetTimerQueueTimer(HANDLE TimerQueue,dword Callback,PVOID Parameter,
    DWORD DueTime,DWORD Period,BOOL PreferIo);
	BOOL CancelTimerQueueTimer(HANDLE TimerQueue,HANDLE Timer);
	BOOL DeleteTimerQueue(HANDLE TimerQueue);

// Performance counter API's
	BOOL QueryPerformanceCounter(dword lpPerformanceCount);
	BOOL QueryPerformanceFrequency(dword lpFrequency);
	BOOL GetVersionExA(dword lpVersionInformation);
	BOOL GetVersionExW(dword lpVersionInformation);
#ifdef UNICODE
#define GetVersionEx  GetVersionExW
#else
#define GetVersionEx  GetVersionExA
#endif // !UNICODE
	BOOL VerifyVersionInfoA(dword lpVersionInformation,DWORD dwTypeMask,DWORDLONG dwlConditionMask);
	BOOL VerifyVersionInfoW(dword lpVersionInformation,DWORD dwTypeMask,DWORDLONG dwlConditionMask);
#ifdef UNICODE
#define VerifyVersionInfo  VerifyVersionInfoW
#else
#define VerifyVersionInfo  VerifyVersionInfoA
#endif // !UNICODE

// DOS and OS/2 Compatible Error Code definitions returned by the Win32 Base
// API functions.

/* Abnormal termination codes */
#define TC_NORMAL       0
#define TC_HARDERR      1
#define TC_GP_TRAP      2
#define TC_SIGNAL       3

// Power Management APIs
#define AC_LINE_OFFLINE                 0x00
#define AC_LINE_ONLINE                  0x01
#define AC_LINE_BACKUP_POWER            0x02
#define AC_LINE_UNKNOWN                 0xFF

#define BATTERY_FLAG_HIGH               0x01
#define BATTERY_FLAG_LOW                0x02
#define BATTERY_FLAG_CRITICAL           0x04
#define BATTERY_FLAG_CHARGING           0x08
#define BATTERY_FLAG_NO_BATTERY         0x80
#define BATTERY_FLAG_UNKNOWN            0xFF

#define BATTERY_PERCENTAGE_UNKNOWN      0xFF

#define BATTERY_LIFE_UNKNOWN        0xFFFFFFFF

	BOOL GetSystemPowerStatus(dword lpSystemPowerStatus);
	BOOL SetSystemPowerState(BOOL fSuspend,BOOL fForce);

// Very Large Memory API Subset
	BOOL AllocateUserPhysicalPages(HANDLE hProcess,dword NumberOfPages,dword PageArray);
	BOOL FreeUserPhysicalPages(HANDLE hProcess,dword NumberOfPages,dword PageArray);
	BOOL MapUserPhysicalPages(PVOID VirtualAddress,ULONG_PTR NumberOfPages,dword PageArray);
	BOOL MapUserPhysicalPagesScatter(dword VirtualAddresses,dword NumberOfPages,dword PageArray);
	HANDLE CreateJobObjectA(dword lpJobAttributes,LPCSTR lpName);
	HANDLE CreateJobObjectW(dword lpJobAttributes,LPCWSTR lpName);
#ifdef UNICODE
#define CreateJobObject  CreateJobObjectW
#else
#define CreateJobObject  CreateJobObjectA
#endif // !UNICODE

	HANDLE OpenJobObjectA(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCSTR lpName);
	HANDLE OpenJobObjectW(DWORD dwDesiredAccess,BOOL bInheritHandle,LPCWSTR lpName);
#ifdef UNICODE
#define OpenJobObject  OpenJobObjectW
#else
#define OpenJobObject  OpenJobObjectA
#endif // !UNICODE

	BOOL AssignProcessToJobObject(HANDLE hJob,HANDLE hProcess);
	BOOL TerminateJobObject(HANDLE hJob,UINT uExitCode);
	BOOL QueryInformationJobObject(HANDLE hJob,dword JobObjectInformationClass,
    LPVOID lpJobObjectInformation,DWORD cbJobObjectInformationLength,LPDWORD lpReturnLength);
	BOOL SetInformationJobObject(HANDLE hJob,dword JobObjectInformationClass,
    LPVOID lpJobObjectInformation,DWORD cbJobObjectInformationLength);
	BOOL IsProcessInJob(HANDLE ProcessHandle,HANDLE JobHandle,PBOOL Result);
	BOOL CreateJobSet(ULONG NumJob,dword UserJobSet,ULONG Flags);
	PVOID AddVectoredExceptionHandler(ULONG FirstHandler,dword VectoredHandler);
	ULONG RemoveVectoredExceptionHandler(PVOID VectoredHandlerHandle);

// New Volume Mount Point API.
	HANDLE FindFirstVolumeA(LPSTR lpszVolumeName,DWORD cchBufferLength);
	HANDLE FindFirstVolumeW(LPWSTR lpszVolumeName,DWORD cchBufferLength);
#ifdef UNICODE
#define FindFirstVolume FindFirstVolumeW
#else
#define FindFirstVolume FindFirstVolumeA
#endif // !UNICODE

	BOOL FindNextVolumeA(HANDLE hFindVolume,LPSTR lpszVolumeName,DWORD cchBufferLength);
	BOOL FindNextVolumeW(HANDLE hFindVolume,LPWSTR lpszVolumeName,DWORD cchBufferLength);
#ifdef UNICODE
#define FindNextVolume FindNextVolumeW
#else
#define FindNextVolume FindNextVolumeA
#endif // !UNICODE

	BOOL FindVolumeClose(HANDLE hFindVolume);
	HANDLE FindFirstVolumeMountPointA(LPCSTR lpszRootPathName,LPSTR lpszVolumeMountPoint,DWORD cchBufferLength);
	HANDLE FindFirstVolumeMountPointW(LPCWSTR lpszRootPathName,LPWSTR lpszVolumeMountPoint,DWORD cchBufferLength);
#ifdef UNICODE
#define FindFirstVolumeMountPoint FindFirstVolumeMountPointW
#else
#define FindFirstVolumeMountPoint FindFirstVolumeMountPointA
#endif // !UNICODE

	BOOL FindNextVolumeMountPointA(HANDLE hFindVolumeMountPoint,LPSTR lpszVolumeMountPoint,DWORD cchBufferLength);
	BOOL FindNextVolumeMountPointW(HANDLE hFindVolumeMountPoint,LPWSTR lpszVolumeMountPoint,DWORD cchBufferLength);
#ifdef UNICODE
#define FindNextVolumeMountPoint FindNextVolumeMountPointW
#else
#define FindNextVolumeMountPoint FindNextVolumeMountPointA
#endif // !UNICODE

	BOOL FindVolumeMountPointClose(HANDLE hFindVolumeMountPoint);
	BOOL SetVolumeMountPointA(LPCSTR lpszVolumeMountPoint,LPCSTR lpszVolumeName);
	BOOL SetVolumeMountPointW(LPCWSTR lpszVolumeMountPoint,LPCWSTR lpszVolumeName);
#ifdef UNICODE
#define SetVolumeMountPoint  SetVolumeMountPointW
#else
#define SetVolumeMountPoint  SetVolumeMountPointA
#endif // !UNICODE

	BOOL DeleteVolumeMountPointA(LPCSTR lpszVolumeMountPoint);
	BOOL DeleteVolumeMountPointW(LPCWSTR lpszVolumeMountPoint);
#ifdef UNICODE
#define DeleteVolumeMountPoint  DeleteVolumeMountPointW
#else
#define DeleteVolumeMountPoint  DeleteVolumeMountPointA
#endif // !UNICODE

	BOOL GetVolumeNameForVolumeMountPointA(LPCSTR lpszVolumeMountPoint,LPSTR lpszVolumeName,DWORD cchBufferLength);
	BOOL GetVolumeNameForVolumeMountPointW(LPCWSTR lpszVolumeMountPoint,LPWSTR lpszVolumeName,DWORD cchBufferLength);
#ifdef UNICODE
#define GetVolumeNameForVolumeMountPoint  GetVolumeNameForVolumeMountPointW
#else
#define GetVolumeNameForVolumeMountPoint  GetVolumeNameForVolumeMountPointA
#endif // !UNICODE

	BOOL GetVolumePathNameA(LPCSTR lpszFileName,LPSTR lpszVolumePathName,DWORD cchBufferLength);
	BOOL GetVolumePathNameW(LPCWSTR lpszFileName,LPWSTR lpszVolumePathName,DWORD cchBufferLength);
#ifdef UNICODE
#define GetVolumePathName  GetVolumePathNameW
#else
#define GetVolumePathName  GetVolumePathNameA
#endif // !UNICODE

	BOOL GetVolumePathNamesForVolumeNameA(LPCSTR lpszVolumeName,LPSTR lpszVolumePathNames,
    DWORD cchBufferLength,PDWORD lpcchReturnLength);
	BOOL GetVolumePathNamesForVolumeNameW(LPCWSTR lpszVolumeName,LPWSTR lpszVolumePathNames,
    DWORD cchBufferLength,PDWORD lpcchReturnLength);
#ifdef UNICODE
#define GetVolumePathNamesForVolumeName  GetVolumePathNamesForVolumeNameW
#else
#define GetVolumePathNamesForVolumeName  GetVolumePathNamesForVolumeNameA
#endif // !UNICODE

	HANDLE CreateActCtxA(dword pActCtx);
	HANDLE CreateActCtxW(dword pActCtx);
#ifdef UNICODE
#define CreateActCtx  CreateActCtxW
#else
#define CreateActCtx  CreateActCtxA
#endif // !UNICODE

	VOID AddRefActCtx(HANDLE hActCtx);
	VOID ReleaseActCtx(HANDLE hActCtx);
	BOOL ZombifyActCtx(HANDLE hActCtx);
	BOOL ActivateActCtx(HANDLE hActCtx,dword lpCookie);

#define DEACTIVATE_ACTCTX_FLAG_FORCE_EARLY_DEACTIVATION 0x00000001

	BOOL DeactivateActCtx(DWORD dwFlags,dword ulCookie);
	BOOL GetCurrentActCtx(dword lphActCtx);

	BOOL FindActCtxSectionStringA(DWORD dwFlags,dword lpExtensionGuid,
    ULONG ulSectionId,LPCSTR lpStringToFind,dword ReturnedData);
	BOOL FindActCtxSectionStringW(DWORD dwFlags,dword lpExtensionGuid,
    ULONG ulSectionId,LPCWSTR lpStringToFind,dword ReturnedData);
#ifdef UNICODE
#define FindActCtxSectionString  FindActCtxSectionStringW
#else
#define FindActCtxSectionString  FindActCtxSectionStringA
#endif // !UNICODE

	BOOL FindActCtxSectionGuid(DWORD dwFlags,dword lpExtensionGuid,
    ULONG ulSectionId,dword lpGuidToFind,dword ReturnedData);

// switch (ulInfoClass)
//  case ActivationContextBasicInformation:
//    pvSubInstance == NULL
//    pvBuffer is of type PACTIVATION_CONTEXT_BASIC_INFORMATION
//  case ActivationContextDetailedInformation:
//    pvSubInstance == NULL
//    pvBuffer is of type PACTIVATION_CONTEXT_DETAILED_INFORMATION
//  case AssemblyDetailedInformationInActivationContext:
//    pvSubInstance is of type PULONG
//      *pvSubInstance < ACTIVATION_CONTEXT_DETAILED_INFORMATION::ulAssemblyCount
//    pvBuffer is of type PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION
//  case FileInformationInAssemblyOfAssemblyInActivationContext:
//    pvSubInstance is of type PACTIVATION_CONTEXT_QUERY_INDEX
//      pvSubInstance->ulAssemblyIndex < ACTIVATION_CONTEXT_DETAILED_INFORMATION::ulAssemblyCount
//      pvSubInstance->ulFileIndexInAssembly < ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION::ulFileCount
//    pvBuffer is of type PASSEMBLY_FILE_DETAILED_INFORMATION
// String are placed after the structs.
	BOOL QueryActCtxW(DWORD dwFlags,HANDLE hActCtx,PVOID pvSubInstance,ULONG ulInfoClass,
    PVOID pvBuffer,SIZE_T cbBuffer,dword pcbWrittenOrRequired);
	BOOL ProcessIdToSessionId(DWORD dwProcessId,dword pSessionId);
	DWORD WTSGetActiveConsoleSessionId();
	BOOL IsWow64Process(HANDLE hProcess,PBOOL Wow64Process);

// NUMA Information routines.
	BOOL GetNumaHighestNodeNumber(PULONG HighestNodeNumber);
	BOOL GetNumaProcessorNode(UCHAR Processor,PUCHAR NodeNumber);
	BOOL GetNumaNodeProcessorMask(UCHAR Node,PULONGLONG ProcessorMask);
	BOOL GetNumaProcessorMap(dword Map,ULONG Length,PULONG ReturnedLength);
	BOOL GetNumaAvailableMemory(dword Memory,ULONG Length,PULONG ReturnedLength);
	BOOL GetNumaAvailableMemoryNode(UCHAR Node,PULONGLONG AvailableBytes);
	ULONGLONG NumaVirtualQueryNode(ULONG NumberOfRanges,dword RangeList,
    dword VirtualPageAndNode,SIZE_T MaximumOutputLength);
}

extern WINAPI "advapi32.dll"{
	BOOL OpenProcessToken(HANDLE ProcessHandle,DWORD DesiredAccess,dword TokenHandle);
	BOOL AccessCheck(dword pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,
    dword GenericMapping,dword PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccess,LPBOOL AccessStatus);
	BOOL AccessCheckByType(dword pSecurityDescriptor,dword PrincipalSelfSid,
    HANDLE ClientToken,DWORD DesiredAccess,dword ObjectTypeList,DWORD ObjectTypeListLength,
    dword GenericMapping,dword PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccess,LPBOOL AccessStatus);
	BOOL AccessCheckByTypeResultList(dword pSecurityDescriptor,dword PrincipalSelfSid,
    HANDLE ClientToken,DWORD DesiredAccess,dword ObjectTypeList,DWORD ObjectTypeListLength,
    dword GenericMapping,dword PrivilegeSet,LPDWORD PrivilegeSetLength,LPDWORD GrantedAccessList,LPDWORD AccessStatusList);
	BOOL AccessCheckAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPSTR ObjectTypeName,
    LPSTR ObjectName,dword SecurityDescriptor,DWORD DesiredAccess,dword GenericMapping,
    BOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
	BOOL AccessCheckAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPWSTR ObjectTypeName,
    LPWSTR ObjectName,dword SecurityDescriptor,DWORD DesiredAccess,dword GenericMapping,
    BOOL ObjectCreation,LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
#ifdef UNICODE
#define AccessCheckAndAuditAlarm  AccessCheckAndAuditAlarmW
#else
#define AccessCheckAndAuditAlarm  AccessCheckAndAuditAlarmA
#endif // !UNICODE

	BOOL AccessCheckByTypeAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,
    LPCSTR ObjectTypeName,LPCSTR ObjectName,dword SecurityDescriptor,dword PrincipalSelfSid,
    DWORD DesiredAccess,dword AuditType,DWORD Flags,dword ObjectTypeList,
    DWORD ObjectTypeListLength,dword GenericMapping,BOOL ObjectCreation,
    LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
	BOOL AccessCheckByTypeAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,
    LPCWSTR ObjectTypeName,LPCWSTR ObjectName,dword SecurityDescriptor,dword PrincipalSelfSid,
    DWORD DesiredAccess,dword AuditType,DWORD Flags,dword ObjectTypeList,
    DWORD ObjectTypeListLength,dword GenericMapping,BOOL ObjectCreation,
    LPDWORD GrantedAccess,LPBOOL AccessStatus,LPBOOL pfGenerateOnClose);
#ifdef UNICODE
#define AccessCheckByTypeAndAuditAlarm  AccessCheckByTypeAndAuditAlarmW
#else
#define AccessCheckByTypeAndAuditAlarm  AccessCheckByTypeAndAuditAlarmA
#endif // !UNICODE

	BOOL AccessCheckByTypeResultListAndAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,
    LPCSTR ObjectTypeName,LPCSTR ObjectName,dword SecurityDescriptor,dword PrincipalSelfSid,
    DWORD DesiredAccess,dword AuditType,DWORD Flags,dword ObjectTypeList,
    DWORD ObjectTypeListLength,dword GenericMapping,BOOL ObjectCreation,
    LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
	BOOL AccessCheckByTypeResultListAndAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,
    LPCWSTR ObjectTypeName,LPCWSTR ObjectName,dword SecurityDescriptor,dword PrincipalSelfSid,
    DWORD DesiredAccess,dword AuditType,DWORD Flags,dword ObjectTypeList,
    DWORD ObjectTypeListLength,dword GenericMapping,BOOL ObjectCreation,
    LPDWORD GrantedAccess,LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
#ifdef UNICODE
#define AccessCheckByTypeResultListAndAuditAlarm  AccessCheckByTypeResultListAndAuditAlarmW
#else
#define AccessCheckByTypeResultListAndAuditAlarm  AccessCheckByTypeResultListAndAuditAlarmA
#endif // !UNICODE

	BOOL AccessCheckByTypeResultListAndAuditAlarmByHandleA(LPCSTR SubsystemName,
    LPVOID HandleId,HANDLE ClientToken,LPCSTR ObjectTypeName,LPCSTR ObjectName,
    dword SecurityDescriptor,dword PrincipalSelfSid,DWORD DesiredAccess,
    dword AuditType,DWORD Flags,dword ObjectTypeList,DWORD ObjectTypeListLength,
    dword GenericMapping,BOOL ObjectCreation,LPDWORD GrantedAccess,
    LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
	BOOL AccessCheckByTypeResultListAndAuditAlarmByHandleW(LPCWSTR SubsystemName,
    LPVOID HandleId,HANDLE ClientToken,LPCWSTR ObjectTypeName,LPCWSTR ObjectName,
    dword SecurityDescriptor,dword PrincipalSelfSid,DWORD DesiredAccess,
    dword AuditType,DWORD Flags,dword ObjectTypeList,DWORD ObjectTypeListLength,
    dword GenericMapping,BOOL ObjectCreation,LPDWORD GrantedAccess,
    LPDWORD AccessStatusList,LPBOOL pfGenerateOnClose);
#ifdef UNICODE
#define AccessCheckByTypeResultListAndAuditAlarmByHandle  AccessCheckByTypeResultListAndAuditAlarmByHandleW
#else
#define AccessCheckByTypeResultListAndAuditAlarmByHandle  AccessCheckByTypeResultListAndAuditAlarmByHandleA
#endif // !UNICODE
	BOOL AddAccessAllowedAce(dword pAcl,DWORD dwAceRevision,DWORD AccessMask,dword pSid);
	BOOL AddAccessAllowedAceEx(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,dword pSid);
	BOOL AddAccessDeniedAce(dword pAcl,DWORD dwAceRevision,DWORD AccessMask,dword pSid);
	BOOL AddAccessDeniedAceEx(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD AccessMask,dword pSid);
	BOOL AddAce(dword pAcl,DWORD dwAceRevision,DWORD dwStartingAceIndex,LPVOID pAceList,DWORD nAceListLength);
	BOOL DeleteAce(dword pAcl,DWORD dwAceIndex);
	BOOL GetAce(dword pAcl,DWORD dwAceIndex,dword pAce);
	BOOL AddAuditAccessAce(dword pAcl,DWORD dwAceRevision,DWORD dwAccessMask,dword pSid,
    BOOL bAuditSuccess,BOOL bAuditFailure);
	BOOL AddAuditAccessAceEx(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,DWORD dwAccessMask,
    dword pSid,BOOL bAuditSuccess,BOOL bAuditFailure);
	BOOL AddAccessAllowedObjectAce(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,
    DWORD AccessMask,dword dObjectTypeGuid,dword InheritedObjectTypeGuid,dword pSid);
	BOOL AddAccessDeniedObjectAce(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,
    DWORD AccessMask,dword ObjectTypeGuid,dword InheritedObjectTypeGuid,dword pSid);
	BOOL AddAuditAccessObjectAce(dword pAcl,DWORD dwAceRevision,DWORD AceFlags,
    DWORD AccessMask,dword ObjectTypeGuid,dword InheritedObjectTypeGuid,dword pSid,
    BOOL bAuditSuccess,BOOL bAuditFailure);
	BOOL FindFirstFreeAce(dword pAcl,dword pAce);
	BOOL AdjustTokenPrivileges(HANDLE TokenHandle,BOOL DisableAllPrivileges,
    dword NewState,DWORD BufferLength,dword PreviousState,PDWORD ReturnLength);
	BOOL AdjustTokenGroups(HANDLE TokenHandle,BOOL ResetToDefault,dword NewState,
    DWORD BufferLength,dword PreviousState,PDWORD ReturnLength);
	BOOL AllocateAndInitializeSid(dword pIdentifierAuthority,BYTE nSubAuthorityCount,
    DWORD nSubAuthority0,DWORD nSubAuthority1,DWORD nSubAuthority2,DWORD nSubAuthority3,
    DWORD nSubAuthority4,DWORD nSubAuthority5,DWORD nSubAuthority6,DWORD nSubAuthority7,dword pSid);
	BOOL AllocateLocallyUniqueId(dword Luid);
	BOOL AreAllAccessesGranted(DWORD GrantedAccess,DWORD DesiredAccess);
	BOOL AreAnyAccessesGranted(DWORD GrantedAccess,DWORD DesiredAccess);
	BOOL BackupEventLogA(HANDLE hEventLog,LPCSTR lpBackupFileName);
	BOOL BackupEventLogW(HANDLE hEventLog,LPCWSTR lpBackupFileName);
#ifdef UNICODE
#define BackupEventLog  BackupEventLogW
#else
#define BackupEventLog  BackupEventLogA
#endif // !UNICODE
	HANDLE OpenBackupEventLogA(LPCSTR lpUNCServerName,LPCSTR lpFileName);
	HANDLE OpenBackupEventLogW(LPCWSTR lpUNCServerName,LPCWSTR lpFileName);
#ifdef UNICODE
#define OpenBackupEventLog  OpenBackupEventLogW
#else
#define OpenBackupEventLog  OpenBackupEventLogA
#endif // !UNICODE
// Event logging APIs
	BOOL ClearEventLogA(HANDLE hEventLog,LPCSTR lpBackupFileName);
	BOOL ClearEventLogW(HANDLE hEventLog,LPCWSTR lpBackupFileName);
#ifdef UNICODE
#define ClearEventLog  ClearEventLogW
#else
#define ClearEventLog  ClearEventLogA
#endif // !UNICODE

	BOOL CloseEventLog(HANDLE hEventLog);
	BOOL CopySid(DWORD nDestinationSidLength,dword pDestinationSid,dword pSourceSid);
	BOOL CreatePrivateObjectSecurity(dword ParentDescriptor,dword CreatorDescriptor,
    dword NewDescriptor,BOOL IsDirectoryObject,HANDLE Token,dword GenericMapping);
	BOOL ConvertToAutoInheritPrivateObjectSecurity(dword ParentDescriptor,dword CurrentSecurityDescriptor,
    dword NewSecurityDescriptor,dword ObjectType,BOOLEAN IsDirectoryObject,dword GenericMapping);
	BOOL CreatePrivateObjectSecurityEx(dword ParentDescriptor,dword CreatorDescriptor,
    dword NewDescriptor,dword ObjectType,BOOL IsContainerObject,ULONG AutoInheritFlags,
    HANDLE Token,dword GenericMapping);
	BOOL CreatePrivateObjectSecurityWithMultipleInheritance(dword ParentDescriptor,
    dword CreatorDescriptor,dword NewDescriptor,dword ObjectTypes,ULONG GuidCount,
    BOOL IsContainerObject,ULONG AutoInheritFlags,HANDLE Token,dword GenericMapping);
	BOOL CreateProcessAsUserA(HANDLE hToken,LPCSTR lpApplicationName,LPSTR lpCommandLine,
    dword lpProcessAttributes,dword lpThreadAttributes,BOOL bInheritHandles,
    DWORD dwCreationFlags,LPVOID lpEnvironment,LPCSTR lpCurrentDirectory,
    dword lpStartupInfo,dword lpProcessInformation);
	BOOL CreateProcessAsUserW(HANDLE hToken,LPCWSTR lpApplicationName,LPWSTR lpCommandLine,
    dword lpProcessAttributes,dword lpThreadAttributes,BOOL bInheritHandles,
    DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,
    dword lpStartupInfo,dword lpProcessInformation);
#ifdef UNICODE
#define CreateProcessAsUser  CreateProcessAsUserW
#else
#define CreateProcessAsUser  CreateProcessAsUserA
#endif // !UNICODE
	BOOL DeregisterEventSource(HANDLE hEventLog);
	BOOL DestroyPrivateObjectSecurity(dword ObjectDescriptor);
	BOOL DuplicateToken(HANDLE ExistingTokenHandle,dword ImpersonationLevel,dword DuplicateTokenHandle);
	BOOL IsWellKnownSid(dword pSid,dword WellKnownSidType);
	BOOL CreateWellKnownSid(dword WellKnownSidType,dword DomainSid,dword pSid,dword cbSid);
	BOOL EqualDomainSid(dword pSid1,dword pSid2,dword pfEqual);
	BOOL GetWindowsAccountDomainSid(dword pSid,dword ppDomainSid,dword cbSid);
	BOOL IsValidSid(dword pSid);
	BOOL EqualSid(dword pSid1,dword pSid2);
	BOOL EqualPrefixSid(dword pSid1,dword pSid2);
	DWORD GetSidLengthRequired(UCHAR nSubAuthorityCount);
	PVOID FreeSid(dword pSid);
	BOOL InitializeSid(dword Sid,dword pIdentifierAuthority,BYTE nSubAuthorityCount);
	dword GetSidIdentifierAuthority(dword pSid);
	PDWORD GetSidSubAuthority(dword pSid,DWORD nSubAuthority);
	PUCHAR GetSidSubAuthorityCount(dword pSid);
	DWORD GetLengthSid(dword pSid);
	BOOL IsValidAcl(dword pAcl);
	BOOL InitializeAcl(dword pAcl,DWORD nAclLength,DWORD dwAclRevision);
	BOOL GetAclInformation(dword pAcl,LPVOID pAclInformation,DWORD nAclInformationLength,dword dwAclInformationClass);
	BOOL SetAclInformation(dword pAcl,LPVOID pAclInformation,DWORD nAclInformationLength,dword dwAclInformationClass);
	BOOL GetCurrentHwProfileA(dword lpHwProfileInfo);
	BOOL GetCurrentHwProfileW(dword lpHwProfileInfo);
#ifdef UNICODE
#define GetCurrentHwProfile  GetCurrentHwProfileW
#else
#define GetCurrentHwProfile  GetCurrentHwProfileA
#endif // !UNICODE
	BOOL GetFileSecurityA(LPCSTR lpFileName,dword RequestedInformation,
    dword pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
	BOOL GetFileSecurityW(LPCWSTR lpFileName,dword RequestedInformation,
    dword pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
#ifdef UNICODE
#define GetFileSecurity  GetFileSecurityW
#else
#define GetFileSecurity  GetFileSecurityA
#endif // !UNICODE
	BOOL GetKernelObjectSecurity(HANDLE Handle,dword RequestedInformation,
    dword pSecurityDescriptor,DWORD nLength,LPDWORD lpnLengthNeeded);
	BOOL NotifyChangeEventLog(HANDLE hEventLog,HANDLE hEvent);
	BOOL GetNumberOfEventLogRecords(HANDLE hEventLog,PDWORD NumberOfRecords);
	BOOL GetOldestEventLogRecord(HANDLE hEventLog,PDWORD OldestRecord);
	HANDLE OpenEventLogA(LPCSTR lpUNCServerName,LPCSTR lpSourceName);
	HANDLE OpenEventLogW(LPCWSTR lpUNCServerName,LPCWSTR lpSourceName);
#ifdef UNICODE
#define OpenEventLog  OpenEventLogW
#else
#define OpenEventLog  OpenEventLogA
#endif // !UNICODE
	BOOL InitializeSecurityDescriptor(dword pSecurityDescriptor,DWORD dwRevision);
	BOOL IsValidSecurityDescriptor(dword pSecurityDescriptor);
	DWORD GetSecurityDescriptorLength(dword pSecurityDescriptor);
	BOOL GetSecurityDescriptorControl(dword pSecurityDescriptor,dword pControl,LPDWORD lpdwRevision);
	BOOL SetSecurityDescriptorControl(dword pSecurityDescriptor,dword ControlBitsOfInterest,
    dword ControlBitsToSet);
	BOOL SetSecurityDescriptorDacl(dword pSecurityDescriptor,BOOL bDaclPresent,
    dword pDacl,BOOL bDaclDefaulted);
	BOOL GetSecurityDescriptorDacl(dword pSecurityDescriptor,LPBOOL lpbDaclPresent,
    dword pDacl,LPBOOL lpbDaclDefaulted);
	BOOL SetSecurityDescriptorSacl(dword pSecurityDescriptor,BOOL bSaclPresent,
    dword pSacl,BOOL bSaclDefaulted);
	BOOL GetSecurityDescriptorSacl(dword pSecurityDescriptor,LPBOOL lpbSaclPresent,
    dword pSacl,LPBOOL lpbSaclDefaulted);
	BOOL SetSecurityDescriptorOwner(dword pSecurityDescriptor,dword pOwner,BOOL bOwnerDefaulted);
	BOOL GetSecurityDescriptorOwner(dword pSecurityDescriptor,dword pOwner,LPBOOL lpbOwnerDefaulted);
	BOOL SetSecurityDescriptorGroup(dword pSecurityDescriptor,dword pGroup,BOOL bGroupDefaulted);
	BOOL GetSecurityDescriptorGroup(dword pSecurityDescriptor,dword pGroup,LPBOOL lpbGroupDefaulted);
	DWORD SetSecurityDescriptorRMControl(dword SecurityDescriptor,PUCHAR RMControl);
	DWORD GetSecurityDescriptorRMControl(dword SecurityDescriptor,PUCHAR RMControl);
	BOOL SetPrivateObjectSecurityEx(dword SecurityInformation,dword ModificationDescriptor,
    dword ObjectsSecurityDescriptor,ULONG AutoInheritFlags,dword GenericMapping,HANDLE Token);
	BOOL SetPrivateObjectSecurity(dword SecurityInformation,dword ModificationDescriptor,
    dword ObjectsSecurityDescriptor,dword GenericMapping,HANDLE Token);
	BOOL GetPrivateObjectSecurity(dword ObjectDescriptor,dword SecurityInformation,
    dword ResultantDescriptor,DWORD DescriptorLength,PDWORD ReturnLength);
	BOOL SetThreadToken(dword Thread,HANDLE Token);
	BOOL OpenThreadToken(HANDLE ThreadHandle,DWORD DesiredAccess,BOOL OpenAsSelf,dword TokenHandle);
	BOOL GetTokenInformation(HANDLE TokenHandle,dword TokenInformationClass,
    LPVOID TokenInformation,DWORD TokenInformationLength,PDWORD ReturnLength);
	BOOL SetTokenInformation(HANDLE TokenHandle,dword TokenInformationClass,
    LPVOID TokenInformation,DWORD TokenInformationLength);
	BOOL PrivilegeCheck(HANDLE ClientToken,dword RequiredPrivileges,LPBOOL pfResult);
	BOOL ImpersonateLoggedOnUser(HANDLE hToken);
	BOOL ImpersonateNamedPipeClient(HANDLE hNamedPipe);
	BOOL ImpersonateSelf(dword ImpersonationLevel);
	BOOL IsTextUnicode(dword lpBuffer,int cb,LPINT lpi);
	BOOL LookupAccountNameA(LPCSTR lpSystemName,LPCSTR lpAccountName,dword Sid,
    LPDWORD cbSid,LPSTR ReferencedDomainName,LPDWORD cbReferencedDomainName,dword peUse);
	BOOL LookupAccountNameW(LPCWSTR lpSystemName,LPCWSTR lpAccountName,dword Sid,
    LPDWORD cbSid,LPWSTR ReferencedDomainName,LPDWORD cbReferencedDomainName,dword peUse);
#ifdef UNICODE
#define LookupAccountName  LookupAccountNameW
#else
#define LookupAccountName  LookupAccountNameA
#endif // !UNICODE
	BOOL LookupAccountSidA(LPCSTR lpSystemName,dword Sid,LPSTR Name,LPDWORD cbName,
    LPSTR ReferencedDomainName,LPDWORD cbReferencedDomainName,dword peUse);
	BOOL LookupAccountSidW(LPCWSTR lpSystemName,dword Sid,LPWSTR Name,LPDWORD cbName,
    LPWSTR ReferencedDomainName,LPDWORD cbReferencedDomainName,dword peUse);
#ifdef UNICODE
#define LookupAccountSid  LookupAccountSidW
#else
#define LookupAccountSid  LookupAccountSidA
#endif // !UNICODE
	BOOL LookupPrivilegeDisplayNameA(LPCSTR lpSystemName,LPCSTR lpName,
    LPSTR lpDisplayName,LPDWORD cbDisplayName,LPDWORD lpLanguageId);
	BOOL LookupPrivilegeDisplayNameW(LPCWSTR lpSystemName,LPCWSTR lpName,
    LPWSTR lpDisplayName,LPDWORD cbDisplayName,LPDWORD lpLanguageId);
#ifdef UNICODE
#define LookupPrivilegeDisplayName  LookupPrivilegeDisplayNameW
#else
#define LookupPrivilegeDisplayName  LookupPrivilegeDisplayNameA
#endif // !UNICODE
	BOOL LookupPrivilegeValueA(LPCSTR lpSystemName,LPCSTR lpName,dword lpLuid);
	BOOL LookupPrivilegeValueW(LPCWSTR lpSystemName,LPCWSTR lpName,dword lpLuid);
#ifdef UNICODE
#define LookupPrivilegeValue  LookupPrivilegeValueW
#else
#define LookupPrivilegeValue  LookupPrivilegeValueA
#endif // !UNICODE
	BOOL LookupPrivilegeNameA(LPCSTR lpSystemName,dword lpLuid,LPSTR lpName,LPDWORD cbName);
	BOOL LookupPrivilegeNameW(LPCWSTR lpSystemName,dword lpLuid,LPWSTR lpName,LPDWORD cbName);
#ifdef UNICODE
#define LookupPrivilegeName  LookupPrivilegeNameW
#else
#define LookupPrivilegeName  LookupPrivilegeNameA
#endif // !UNICODE
	BOOL MakeSelfRelativeSD(dword pAbsoluteSecurityDescriptor,dword pSelfRelativeSecurityDescriptor,LPDWORD lpdwBufferLength);
	BOOL MakeAbsoluteSD(dword pSelfRelativeSecurityDescriptor,dword pAbsoluteSecurityDescriptor,
    LPDWORD lpdwAbsoluteSecurityDescriptorSize,dword pDacl,LPDWORD lpdwDaclSize,
    dword pSacl,LPDWORD lpdwSaclSize,dword pOwner,LPDWORD lpdwOwnerSize,dword pPrimaryGroup,LPDWORD lpdwPrimaryGroupSize);
	BOOL MakeAbsoluteSD2(dword pSelfRelativeSecurityDescriptor,LPDWORD lpdwBufferSize);
	VOID MapGenericMask(PDWORD AccessMask,dword GenericMapping);
	BOOL ObjectOpenAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,LPSTR ObjectTypeName,
    LPSTR ObjectName,dword pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,
    DWORD GrantedAccess,dword Privileges,BOOL ObjectCreation,BOOL AccessGranted,LPBOOL GenerateOnClose);
	BOOL ObjectOpenAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,LPWSTR ObjectTypeName,
    LPWSTR ObjectName,dword pSecurityDescriptor,HANDLE ClientToken,DWORD DesiredAccess,
    DWORD GrantedAccess,dword Privileges,BOOL ObjectCreation,BOOL AccessGranted,LPBOOL GenerateOnClose);
#ifdef UNICODE
#define ObjectOpenAuditAlarm  ObjectOpenAuditAlarmW
#else
#define ObjectOpenAuditAlarm  ObjectOpenAuditAlarmA
#endif // !UNICODE

	BOOL ObjectPrivilegeAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,
    DWORD DesiredAccess,dword Privileges,BOOL AccessGranted);
	BOOL ObjectPrivilegeAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,HANDLE ClientToken,
    DWORD DesiredAccess,dword Privileges,BOOL AccessGranted);
#ifdef UNICODE
#define ObjectPrivilegeAuditAlarm  ObjectPrivilegeAuditAlarmW
#else
#define ObjectPrivilegeAuditAlarm  ObjectPrivilegeAuditAlarmA
#endif // !UNICODE

	BOOL ObjectCloseAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,BOOL GenerateOnClose);
	BOOL ObjectCloseAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,BOOL GenerateOnClose);
#ifdef UNICODE
#define ObjectCloseAuditAlarm  ObjectCloseAuditAlarmW
#else
#define ObjectCloseAuditAlarm  ObjectCloseAuditAlarmA
#endif // !UNICODE

	BOOL ObjectDeleteAuditAlarmA(LPCSTR SubsystemName,LPVOID HandleId,BOOL GenerateOnClose);
	BOOL ObjectDeleteAuditAlarmW(LPCWSTR SubsystemName,LPVOID HandleId,BOOL GenerateOnClose);
#ifdef UNICODE
#define ObjectDeleteAuditAlarm  ObjectDeleteAuditAlarmW
#else
#define ObjectDeleteAuditAlarm  ObjectDeleteAuditAlarmA
#endif // !UNICODE
	BOOL PrivilegedServiceAuditAlarmA(LPCSTR SubsystemName,LPCSTR ServiceName,
    HANDLE ClientToken,dword Privileges,BOOL AccessGranted);
	BOOL PrivilegedServiceAuditAlarmW(LPCWSTR SubsystemName,LPCWSTR ServiceName,
    HANDLE ClientToken,dword Privileges,BOOL AccessGranted);
#ifdef UNICODE
#define PrivilegedServiceAuditAlarm  PrivilegedServiceAuditAlarmW
#else
#define PrivilegedServiceAuditAlarm  PrivilegedServiceAuditAlarmA
#endif // !UNICODE
	HANDLE RegisterEventSourceA(LPCSTR lpUNCServerName,LPCSTR lpSourceName);
	HANDLE RegisterEventSourceW(LPCWSTR lpUNCServerName,LPCWSTR lpSourceName);
#ifdef UNICODE
#define RegisterEventSource  RegisterEventSourceW
#else
#define RegisterEventSource  RegisterEventSourceA
#endif // !UNICODE

	BOOL ReadEventLogA(HANDLE hEventLog,DWORD dwReadFlags,DWORD dwRecordOffset,
     LPVOID lpBuffer,DWORD nNumberOfBytesToRead,dword pnBytesRead,dword pnMinNumberOfBytesNeeded);
	BOOL ReadEventLogW(HANDLE hEventLog,DWORD dwReadFlags,DWORD dwRecordOffset,
     LPVOID lpBuffer,DWORD nNumberOfBytesToRead,dword pnBytesRead,dword pnMinNumberOfBytesNeeded);
#ifdef UNICODE
#define ReadEventLog  ReadEventLogW
#else
#define ReadEventLog  ReadEventLogA
#endif // !UNICODE

	BOOL ReportEventA(HANDLE hEventLog,WORD wType,WORD wCategory,DWORD dwEventID,
     dword lpUserSid,WORD wNumStrings,DWORD dwDataSize,dword lpStrings,LPVOID lpRawData);
	BOOL ReportEventW(HANDLE hEventLog,WORD wType,WORD wCategory,DWORD dwEventID,
     dword lpUserSid,WORD wNumStrings,DWORD dwDataSize,dword lpStrings,LPVOID lpRawData);
#ifdef UNICODE
#define ReportEvent  ReportEventW
#else
#define ReportEvent  ReportEventA
#endif // !UNICODE

#define EVENTLOG_FULL_INFO      0

	BOOL GetEventLogInformation(HANDLE hEventLog,DWORD dwInfoLevel,LPVOID lpBuffer,
     DWORD cbBufSize,LPDWORD pcbBytesNeeded);
	BOOL RevertToSelf(VOID);
// Security APIs
	BOOL SetFileSecurityA(LPCSTR lpFileName,dword SecurityInformation,dword pSecurityDescriptor);
	BOOL SetFileSecurityW(LPCWSTR lpFileName,dword SecurityInformation,dword pSecurityDescriptor);
#ifdef UNICODE
#define SetFileSecurity  SetFileSecurityW
#else
#define SetFileSecurity  SetFileSecurityA
#endif // !UNICODE
	BOOL SetKernelObjectSecurity(HANDLE Handle,dword SecurityInformation,dword SecurityDescriptor);












}
enum WELL_KNOWN_SID_TYPE{
  WinNullSid                                  = 0,
  WinWorldSid                                 = 1,
  WinLocalSid                                 = 2,
  WinCreatorOwnerSid                          = 3,
  WinCreatorGroupSid                          = 4,
  WinCreatorOwnerServerSid                    = 5,
  WinCreatorGroupServerSid                    = 6,
  WinNtAuthoritySid                           = 7,
  WinDialupSid                                = 8,
  WinNetworkSid                               = 9,
  WinBatchSid                                 = 10,
  WinInteractiveSid                           = 11,
  WinServiceSid                               = 12,
  WinAnonymousSid                             = 13,
  WinProxySid                                 = 14,
  WinEnterpriseControllersSid                 = 15,
  WinSelfSid                                  = 16,
  WinAuthenticatedUserSid                     = 17,
  WinRestrictedCodeSid                        = 18,
  WinTerminalServerSid                        = 19,
  WinRemoteLogonIdSid                         = 20,
  WinLogonIdsSid                              = 21,
  WinLocalSystemSid                           = 22,
  WinLocalServiceSid                          = 23,
  WinNetworkServiceSid                        = 24,
  WinBuiltinDomainSid                         = 25,
  WinBuiltinAdministratorsSid                 = 26,
  WinBuiltinUsersSid                          = 27,
  WinBuiltinGuestsSid                         = 28,
  WinBuiltinPowerUsersSid                     = 29,
  WinBuiltinAccountOperatorsSid               = 30,
  WinBuiltinSystemOperatorsSid                = 31,
  WinBuiltinPrintOperatorsSid                 = 32,
  WinBuiltinBackupOperatorsSid                = 33,
  WinBuiltinReplicatorSid                     = 34,
  WinBuiltinPreWindows2000CompatibleAccessSid = 35,
  WinBuiltinRemoteDesktopUsersSid             = 36,
  WinBuiltinNetworkConfigurationOperatorsSid  = 37,
  WinAccountAdministratorSid                  = 38,
  WinAccountGuestSid                          = 39,
  WinAccountKrbtgtSid                         = 40,
  WinAccountDomainAdminsSid                   = 41,
  WinAccountDomainUsersSid                    = 42,
  WinAccountDomainGuestsSid                   = 43,
  WinAccountComputersSid                      = 44,
  WinAccountControllersSid                    = 45,
  WinAccountCertAdminsSid                     = 46,
  WinAccountSchemaAdminsSid                   = 47,
  WinAccountEnterpriseAdminsSid               = 48,
  WinAccountPolicyAdminsSid                   = 49,
  WinAccountRasAndIasServersSid               = 50,
};

enum COMPUTER_NAME_FORMAT{
  ComputerNameNetBIOS,
  ComputerNameDnsHostname,
  ComputerNameDnsDomain,
  ComputerNameDnsFullyQualified,
  ComputerNamePhysicalNetBIOS,
  ComputerNamePhysicalDnsHostname,
  ComputerNamePhysicalDnsDomain,
  ComputerNamePhysicalDnsFullyQualified,
  ComputerNameMax
};

#endif // _WINBASE_
