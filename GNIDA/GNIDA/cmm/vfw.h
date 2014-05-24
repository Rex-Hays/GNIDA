/****************************************************************************
 *      VfW.H - Video for windows include file for WIN32
 *      Copyright (c) 1991-1995, Microsoft Corp.  All rights reserved.
 *      This include files defines interfaces to the following
 *      video components
 *          COMPMAN         - Installable Compression Manager.
 *          DRAWDIB         - Routines for drawing to the display.
 *          VIDEO           - Video Capture Driver Interface
 *          AVIFMT          - AVI File Format structure definitions.
 *          MMREG           - FOURCC and other things
 *          AVIFile         - Interface for reading AVI Files and AVI Streams
 *          MCIWND          - MCI/AVI window class
 *          AVICAP          - AVI Capture Window class
 *          MSACM           - Audio compression manager.
 *      The following symbols control inclusion of various parts of this file:
 *          NOCOMPMAN       - dont include COMPMAN
 *          NODRAWDIB       - dont include DRAWDIB
 *          NOVIDEO         - dont include video capture interface
 *          NOAVIFMT        - dont include AVI file format structs
 *          NOMMREG         - dont include MMREG
 *          NOAVIFILE       - dont include AVIFile interface
 *          NOMCIWND        - dont include AVIWnd class.
 *          NOAVICAP        - dont include AVICap class.
 *          NOMSACM         - dont include ACM stuff.
 ****************************************************************************/
#ifndef _INC_VFW
#define _INC_VFW

/****************************************************************************
 *  do we need MMSYSTEM?
 ****************************************************************************/

#if !defined(_INC_MMSYSTEM) && (!defined(NOVIDEO) || !defined(NOAVICAP))
#include <mmsystem.h>
#endif

/****************************************************************************/
/*        Macros                                                            */
/*  should we define this??                                                 */
/****************************************************************************/
#ifndef MKFOURCC
#define MKFOURCC(ch0,ch1,ch2,ch3) ch3<<8|ch2<<8|ch1<<8|ch0                                   \
#endif

#if !defined(_INC_MMSYSTEM)
#define mmioFOURCC MKFOURCC
#endif

/****************************************************************************
 *  COMPMAN - Installable Compression Manager.
 ****************************************************************************/
#ifndef NOCOMPMAN

#define ICVERSION       0x0104

//DECLARE_HANDLE(HIC);     /* Handle to a Installable Compressor */

// this code in biCompression means the DIB must be accesed via
// 48 bit pointers! using *ONLY* the selector given.
#define BI_1632  0x32333631     // '1632'

#ifndef mmioFOURCC
#define mmioFOURCC(ch0,ch1,ch2,ch3) ch3<<8|ch2<<8|ch1<<8|ch0
#endif

#ifndef aviTWOCC
#define aviTWOCC(ch0,ch1) ch1<<8|ch0
#endif

#ifndef ICTYPE_VIDEO
#define ICTYPE_VIDEO    'vidc'
#define ICTYPE_AUDIO    'audc'
#endif

#ifndef ICERR_OK
#define ICERR_OK                0L
#define ICERR_DONTDRAW          1L
#define ICERR_NEWPALETTE        2L
#define ICERR_GOTOKEYFRAME	3L
#define ICERR_STOPDRAWING 	4L

#define ICERR_UNSUPPORTED      -1L
#define ICERR_BADFORMAT        -2L
#define ICERR_MEMORY           -3L
#define ICERR_INTERNAL         -4L
#define ICERR_BADFLAGS         -5L
#define ICERR_BADPARAM         -6L
#define ICERR_BADSIZE          -7L
#define ICERR_BADHANDLE        -8L
#define ICERR_CANTUPDATE       -9L
#define ICERR_ABORT	       -10L
#define ICERR_ERROR            -100L
#define ICERR_BADBITDEPTH      -200L
#define ICERR_BADIMAGESIZE     -201L
#define ICERR_CUSTOM           -400L    // errors less than ICERR_CUSTOM...
#endif

/* Values for dwFlags of ICOpen() */
#ifndef ICMODE_COMPRESS
#define ICMODE_COMPRESS		1
#define ICMODE_DECOMPRESS	2
#define ICMODE_FASTDECOMPRESS   3
#define ICMODE_QUERY            4
#define ICMODE_FASTCOMPRESS     5
#define ICMODE_DRAW             8
#endif
#ifndef _WIN32					// ;Internal
#define ICMODE_INTERNALF_FUNCTION32	0x8000	// ;Internal
#define ICMODE_INTERNALF_MASK		0x8000	// ;Internal
#endif						// ;Internal

/* Flags for AVI file index */
#define AVIIF_LIST	0x00000001L
#define AVIIF_TWOCC	0x00000002L
#define AVIIF_KEYFRAME	0x00000010L

/* quality flags */
#define ICQUALITY_LOW       0
#define ICQUALITY_HIGH      10000
#define ICQUALITY_DEFAULT   -1

/************************************************************************
************************************************************************/

#define ICM_USER          DRV_USER+0x0000

#define ICM_RESERVED      ICM_RESERVED_LOW
#define ICM_RESERVED_LOW  DRV_USER+0x1000
#define ICM_RESERVED_HIGH DRV_USER+0x2000

/************************************************************************

    messages.

************************************************************************/

#define ICM_GETSTATE                ICM_RESERVED+0    // Get compressor state
#define ICM_SETSTATE                ICM_RESERVED+1    // Set compressor state
#define ICM_GETINFO                 ICM_RESERVED+2    // Query info about the compressor

#define ICM_CONFIGURE               ICM_RESERVED+10   // show the configure dialog
#define ICM_ABOUT                   ICM_RESERVED+11   // show the about box

#define ICM_GETERRORTEXT            ICM_RESERVED+12   // get error text TBD ;Internal
#define ICM_GETFORMATNAME	    ICM_RESERVED+20	// get a name for a format ;Internal
#define ICM_ENUMFORMATS		    ICM_RESERVED+21	// cycle through formats ;Internal

#define ICM_GETDEFAULTQUALITY       ICM_RESERVED+30   // get the default value for quality
#define ICM_GETQUALITY              ICM_RESERVED+31   // get the current value for quality
#define ICM_SETQUALITY              ICM_RESERVED+32   // set the default value for quality

#define ICM_SET			    ICM_RESERVED+40	// Tell the driver something
#define ICM_GET			    ICM_RESERVED+41	// Ask the driver something

// Constants for ICM_SET:
#define ICM_FRAMERATE       'FrmR'
#define ICM_KEYFRAMERATE    'KeyR'

/************************************************************************
    ICM specific messages.
************************************************************************/
#define ICM_COMPRESS_GET_FORMAT     ICM_USER+4    // get compress format or size
#define ICM_COMPRESS_GET_SIZE       ICM_USER+5    // get output size
#define ICM_COMPRESS_QUERY          ICM_USER+6    // query support for compress
#define ICM_COMPRESS_BEGIN          ICM_USER+7    // begin a series of compress calls.
#define ICM_COMPRESS                ICM_USER+8    // compress a frame
#define ICM_COMPRESS_END            ICM_USER+9    // end of a series of compress calls.

#define ICM_DECOMPRESS_GET_FORMAT   ICM_USER+10   // get decompress format or size
#define ICM_DECOMPRESS_QUERY        ICM_USER+11   // query support for dempress
#define ICM_DECOMPRESS_BEGIN        ICM_USER+12   // start a series of decompress calls
#define ICM_DECOMPRESS              ICM_USER+13   // decompress a frame
#define ICM_DECOMPRESS_END          ICM_USER+14   // end a series of decompress calls
#define ICM_DECOMPRESS_SET_PALETTE  ICM_USER+29   // fill in the DIB color table
#define ICM_DECOMPRESS_GET_PALETTE  ICM_USER+30   // fill in the DIB color table

#define ICM_DRAW_QUERY              ICM_USER+31   // query support for dempress
#define ICM_DRAW_BEGIN              ICM_USER+15   // start a series of draw calls
#define ICM_DRAW_GET_PALETTE        ICM_USER+16   // get the palette needed for drawing
#define ICM_DRAW_UPDATE             ICM_USER+17   // update screen with current frame ;Internal
#define ICM_DRAW_START              ICM_USER+18   // start decompress clock
#define ICM_DRAW_STOP               ICM_USER+19   // stop decompress clock
#define ICM_DRAW_BITS               ICM_USER+20   // decompress a frame to screen ;Internal
#define ICM_DRAW_END                ICM_USER+21   // end a series of draw calls
#define ICM_DRAW_GETTIME            ICM_USER+32   // get value of decompress clock
#define ICM_DRAW                    ICM_USER+33   // generalized "render" message
#define ICM_DRAW_WINDOW             ICM_USER+34   // drawing window has moved or hidden
#define ICM_DRAW_SETTIME            ICM_USER+35   // set correct value for decompress clock
#define ICM_DRAW_REALIZE            ICM_USER+36   // realize palette for drawing
#define ICM_DRAW_FLUSH	            ICM_USER+37   // clear out buffered frames
#define ICM_DRAW_RENDERBUFFER       ICM_USER+38   // draw undrawn things in queue

#define ICM_DRAW_START_PLAY         ICM_USER+39   // start of a play
#define ICM_DRAW_STOP_PLAY          ICM_USER+40   // end of a play

#define ICM_DRAW_SUGGESTFORMAT      ICM_USER+50   // Like ICGetDisplayFormat
#define ICM_DRAW_CHANGEPALETTE      ICM_USER+51   // for animating palette

#define ICM_DRAW_IDLE               ICM_USER+52   // send each frame time ;Internal

#define ICM_GETBUFFERSWANTED        ICM_USER+41   // ask about prebuffering

#define ICM_GETDEFAULTKEYFRAMERATE  ICM_USER+42   // get the default value for key frames

#define ICM_DECOMPRESSEX_BEGIN      ICM_USER+60   // start a series of decompress calls
#define ICM_DECOMPRESSEX_QUERY      ICM_USER+61   // start a series of decompress calls
#define ICM_DECOMPRESSEX            ICM_USER+62   // decompress a frame
#define ICM_DECOMPRESSEX_END        ICM_USER+63   // end a series of decompress calls

#define ICM_COMPRESS_FRAMES_INFO    ICM_USER+70   // tell about compress to come
#define ICM_COMPRESS_FRAMES         ICM_USER+71   // compress a bunch of frames ;Internal
#define ICM_SET_STATUS_PROC	        ICM_USER+72   // set status callback

/************************************************************************
************************************************************************/
struct ICOPEN{
  DWORD               dwSize;         // sizeof(ICOPEN)
  DWORD               fccType;        // 'vidc'
  DWORD               fccHandler;     //
  DWORD               dwVersion;      // version of compman opening you
  DWORD               dwFlags;        // LOWORD is type specific
  dword             dwError;        // error return.
  LPVOID              pV1Reserved;    // Reserved
  LPVOID              pV2Reserved;    // Reserved
  DWORD               dnDevNode;      // Devnode for PnP devices
};

/************************************************************************
************************************************************************/
struct ICINFO{
  DWORD   dwSize;                 // sizeof(ICINFO)
  DWORD   fccType;                // compressor type     'vidc' 'audc'
  DWORD   fccHandler;             // compressor sub-type 'rle ' 'jpeg' 'pcm '
  DWORD   dwFlags;                // flags LOWORD is type specific
  DWORD   dwVersion;              // version of the driver
  DWORD   dwVersionICM;           // version of the ICM used
  //
  // under Win32, the driver always returns UNICODE strings.
  //
  WCHAR   szName[16];             // short name
  WCHAR   szDescription[128];     // long name
  WCHAR   szDriver[128];          // driver that contains compressor
};

/* Flags for the <dwFlags> field of the <ICINFO> structure. */
#define VIDCF_QUALITY        0x0001  // supports quality
#define VIDCF_CRUNCH         0x0002  // supports crunching to a frame size
#define VIDCF_TEMPORAL       0x0004  // supports inter-frame compress
#define VIDCF_COMPRESSFRAMES 0x0008  // wants the compress all frames message
#define VIDCF_DRAW           0x0010  // supports drawing
#define VIDCF_FASTTEMPORALC  0x0020  // does not need prev frame on compress
#define VIDCF_FASTTEMPORALD  0x0080  // does not need prev frame on decompress
#define VIDCF_QUALITYTIME    0x0040  // supports temporal quality

#define VIDCF_FASTTEMPORAL   VIDCF_FASTTEMPORALC|VIDCF_FASTTEMPORALD

/************************************************************************
************************************************************************/
#define ICCOMPRESS_KEYFRAME	0x00000001L

struct ICCOMPRESS{
  DWORD               dwFlags;        // flags
  dword  lpbiOutput;     // output format
  LPVOID              lpOutput;       // output data
  dword  lpbiInput;      // format of frame to compress
  LPVOID              lpInput;        // frame data to compress
  LPDWORD             lpckid;         // ckid for data in AVI file
  LPDWORD             lpdwFlags;      // flags in the AVI index.
  LONG                lFrameNum;      // frame number of seq.
  DWORD               dwFrameSize;    // reqested size in bytes. (if non zero)
  DWORD               dwQuality;      // quality
  // these are new fields
  dword  lpbiPrev;       // format of previous frame
  LPVOID              lpPrev;         // previous frame
};

/************************************************************************
************************************************************************/
#define ICCOMPRESSFRAMES_PADDING	0x00000001

struct ICCOMPRESSFRAMES{
  DWORD               dwFlags;        // flags
  dword  lpbiOutput;     // output format
  LPARAM              lOutput;        // output identifier
  dword  lpbiInput;      // format of frame to compress
  LPARAM              lInput;         // input identifier
  LONG                lStartFrame;    // start frame
  LONG                lFrameCount;    // # of frames
  LONG                lQuality;       // quality
  LONG                lDataRate;      // data rate
  LONG                lKeyRate;       // key frame rate
  DWORD		dwRate;		// frame rate, as always
  DWORD		dwScale;
  DWORD		dwOverheadPerFrame;
  DWORD		dwReserved2;
  LONG stdcall(*GetData)(LPARAM lInput,LONG lFrame,LPVOID lpBits,LONG len);
  LONG stdcall(*PutData)(LPARAM lOutput,LONG lFrame,LPVOID lpBits,LONG len);
};

// messages for Status callback
#define ICSTATUS_START	    0
#define ICSTATUS_STATUS	    1	    // l == % done
#define ICSTATUS_END	    2
#define ICSTATUS_ERROR	    3	    // l == error string (LPSTR)
#define ICSTATUS_YIELD	    4
struct ICSETSTATUSPROC{
  DWORD		dwFlags;
  LPARAM		lParam;
// return nonzero means abort operation in progress
  LONG stdcall(*Status)(LPARAM lParam,UINT message,LONG l);
};

/************************************************************************
************************************************************************/
#define ICDECOMPRESS_HURRYUP      0x80000000L   // don't draw just buffer (hurry up!)
#define ICDECOMPRESS_UPDATE       0x40000000L   // don't draw just update screen
#define ICDECOMPRESS_PREROLL      0x20000000L   // this frame is before real start
#define ICDECOMPRESS_NULLFRAME    0x10000000L   // repeat last frame
#define ICDECOMPRESS_NOTKEYFRAME  0x08000000L   // this frame is not a key frame
struct ICDECOMPRESS{
  DWORD               dwFlags;    // flags (from AVI index...)
  dword  lpbiInput;  // BITMAPINFO of compressed data
                                 // biSizeImage has the chunk size
  LPVOID              lpInput;    // compressed data
  dword  lpbiOutput; // DIB to decompress to
  LPVOID              lpOutput;
  DWORD		ckid;	    // ckid from AVI file
};

struct ICDECOMPRESSEX{
  //
  // same as ICM_DECOMPRESS
  //
  DWORD               dwFlags;
  dword  lpbiSrc;    // BITMAPINFO of compressed data
  LPVOID              lpSrc;      // compressed data
  dword  lpbiDst;    // DIB to decompress to
  LPVOID              lpDst;      // output data
  //
  // new for ICM_DECOMPRESSEX
  //
  int                 xDst;       // destination rectangle
  int                 yDst;
  int                 dxDst;
  int                 dyDst;
  int                 xSrc;       // source rectangle
  int                 ySrc;
  int                 dxSrc;
  int                 dySrc;
};

/************************************************************************
************************************************************************/
#define ICDRAW_QUERY        0x00000001L   // test for support
#define ICDRAW_FULLSCREEN   0x00000002L   // draw to full screen
#define ICDRAW_HDC          0x00000004L   // draw to a HDC/HWND
#define ICDRAW_ANIMATE	    0x00000008L	  // expect palette animation
#define ICDRAW_CONTINUE	    0x00000010L	  // draw is a continuation of previous draw
#define ICDRAW_MEMORYDC	    0x00000020L	  // DC is offscreen, by the way
#define ICDRAW_UPDATING	    0x00000040L	  // We're updating, as opposed to playing
#define ICDRAW_RENDER       0x00000080L   // used to render data not draw it
#define ICDRAW_BUFFER       0x00000100L   // please buffer this data offscreen, we will need to update it

struct ICDRAWBEGIN{
  DWORD               dwFlags;        // flags
  HPALETTE            hpal;           // palette to draw with
  HWND                hwnd;           // window to draw to
  HDC                 hdc;            // HDC to draw to
  int                 xDst;           // destination rectangle
  int                 yDst;
  int                 dxDst;
  int                 dyDst;
  dword  lpbi;           // format of frame to draw
  int                 xSrc;           // source rectangle
  int                 ySrc;
  int                 dxSrc;
  int                 dySrc;
  DWORD               dwRate;         // frames/second = (dwRate/dwScale)
  DWORD               dwScale;
};

/************************************************************************
************************************************************************/
#define ICDRAW_HURRYUP      0x80000000L   // don't draw just buffer (hurry up!)
#define ICDRAW_UPDATE       0x40000000L   // don't draw just update screen
#define ICDRAW_PREROLL	    0x20000000L	  // this frame is before real start
#define ICDRAW_NULLFRAME    0x10000000L	  // repeat last frame
#define ICDRAW_NOTKEYFRAME  0x08000000L   // this frame is not a key frame

struct ICDRAW{
  DWORD               dwFlags;        // flags
  LPVOID		lpFormat;       // format of frame to decompress
  LPVOID              lpData;         // frame data to decompress
  DWORD               cbData;
  LONG                lTime;          // time in drawbegin units (see dwRate and dwScale)
};

struct ICDRAWSUGGEST{
  dword	lpbiIn;		// format to be drawn
  dword	lpbiSuggest;	// location for suggested format (or NULL to get size)
  int			dxSrc;		// source extent or 0
  int			dySrc;
  int			dxDst;		// dest extent or 0
  int			dyDst;
  dword			hicDecompressor;// decompressor you can talk to
};

/************************************************************************
************************************************************************/
struct ICPALETTE{
  DWORD               dwFlags;    // flags (from AVI index...)
  int                 iStart;     // first palette to change
  int                 iLen;       // count of entries to change.
  dword      lppe;       // palette
};

/************************************************************************
    ICM function declarations
************************************************************************/
extern WINAPI "msvfw32.dll"{
	BOOL ICInfo(DWORD fccType,DWORD fccHandler,dword lpicinfo);
	BOOL ICInstall(DWORD fccType,DWORD fccHandler,LPARAM lParam,LPSTR szDesc,UINT wFlags);
	BOOL ICRemove(DWORD fccType,DWORD fccHandler,UINT wFlags);
	dword ICGetInfo(dword hic,dword picinfo,DWORD cb);
	dword ICOpen(DWORD fccType,DWORD fccHandler,UINT wMode);
	dword ICOpenFunction(DWORD fccType,DWORD fccHandler,UINT wMode,dword lpfnHandler);
	dword ICClose(dword hic);
	dword ICSendMessage(dword hic,UINT msg,DWORD_PTR dw1,DWORD_PTR dw2);
}
/* Values for wFlags of ICInstall() */
#define ICINSTALL_UNICODE       0x8000
#define ICINSTALL_FUNCTION      0x0001  // lParam is a DriverProc (function ptr)
#define ICINSTALL_DRIVER        0x0002  // lParam is a driver name (string)
#define ICINSTALL_HDRV          0x0004  // lParam is a HDRVR (driver handle)
#define ICINSTALL_DRIVERW       0x8002  // lParam is a unicode driver name

/************************************************************************
    query macros
************************************************************************/
#define ICMF_CONFIGURE_QUERY     0x00000001
#define ICMF_ABOUT_QUERY         0x00000001

#define ICQueryAbout(hic) (ICSendMessage(hic,ICM_ABOUT,-1,ICMF_ABOUT_QUERY)==ICERR_OK)
#define ICAbout(hic,hwnd) ICSendMessage(hic,ICM_ABOUT,hwnd,0)
#define ICQueryConfigure(hic) (ICSendMessage(hic,ICM_CONFIGURE,-1,ICMF_CONFIGURE_QUERY)==ICERR_OK)
#define ICConfigure(hic,hwnd) ICSendMessage(hic,ICM_CONFIGURE,hwnd,0)

/************************************************************************
    get/set state macros
************************************************************************/
#define ICGetState(hic,pv,cb) ICSendMessage(hic,ICM_GETSTATE,pv,cb)
#define ICSetState(hic,pv,cb) ICSendMessage(hic,ICM_SETSTATE,pv,cb)
#define ICGetStateSize(hic) ICGetState(hic,NULL,0)

/************************************************************************
    get value macros
************************************************************************/
:static DWORD dwICValue;

#define ICGetDefaultQuality(hic) \
    (ICSendMessage(hic,ICM_GETDEFAULTQUALITY,#dwICValue,sizeof(DWORD)),dwICValue)

#define ICGetDefaultKeyFrameRate(hic) \
    (ICSendMessage(hic,ICM_GETDEFAULTKEYFRAMERATE,#dwICValue,sizeof(DWORD)),dwICValue)

/************************************************************************
    draw window macro
************************************************************************/
#define ICDrawWindow(hic,prc) ICSendMessage(hic,ICM_DRAW_WINDOW,prc,sizeof(RECT))

/************************************************************************
    compression functions
************************************************************************/
/*
 *  ICCompress()
 *  compress a single frame
 */
extern WINAPI "msvfw32.dll"{
	DWORD ICCompress(dword hic,DWORD dwFlags,dword pbiOutput,LPVOID lpData,
		dword lpbiInput,LPVOID lpBits,LPDWORD lpckid,LPDWORD lpdwFlags,LONG lFrameNum,
		DWORD dwFrameSize,DWORD dwQuality,dword lpbiPrev,LPVOID lpPrev);
}
/*
 *  ICCompressBegin()
 *  start compression from a source format (lpbiInput) to a dest
 *  format (lpbiOuput) is supported.
 */
#define ICCompressBegin(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_COMPRESS_BEGIN,lpbiInput,lpbiOutput)

/*
 *  ICCompressQuery()
 *  determines if compression from a source format (lpbiInput) to a dest
 *  format (lpbiOuput) is supported.
 */
#define ICCompressQuery(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_COMPRESS_QUERY,lpbiInput,lpbiOutput)

/*
 *  ICCompressGetFormat()
 *  get the output format, (format of compressed data)
 *  if lpbiOutput is NULL return the size in bytes needed for format.
 */
#define ICCompressGetFormat(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_COMPRESS_GET_FORMAT,lpbiInput,lpbiOutput)
#define ICCompressGetFormatSize(hic,lpbi) ICCompressGetFormat(hic,lpbi,NULL)

/*
 *  ICCompressSize()
 *  return the maximal size of a compressed frame
 */
#define ICCompressGetSize(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_COMPRESS_GET_SIZE,lpbiInput,lpbiOutput)
#define ICCompressEnd(hic) ICSendMessage(hic,ICM_COMPRESS_END,0,0)

/************************************************************************
    decompression functions
************************************************************************/
/*
 *  ICDecompress()
 *  decompress a single frame
 */
#define ICDECOMPRESS_HURRYUP    0x80000000L     // don't draw just buffer (hurry up!)

extern WINAPI "msvfw32.dll"{
	DWORD ICDecompress(dword hic,DWORD dwFlags,dword lpbiFormat,LPVOID lpData,dword lpbi,LPVOID lpBits);
}
/*
 *  ICDecompressBegin()
 *  start compression from a source format (lpbiInput) to a dest
 *  format (lpbiOutput) is supported.
 */
#define ICDecompressBegin(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_DECOMPRESS_BEGIN,lpbiInput,lpbiOutput)

/*
 *  ICDecompressQuery()
 *  determines if compression from a source format (lpbiInput) to a dest
 *  format (lpbiOutput) is supported.
 */
#define ICDecompressQuery(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_DECOMPRESS_QUERY,lpbiInput,lpbiOutput)

/*
 *  ICDecompressGetFormat()
 *  get the output format, (format of un-compressed data)
 *  if lpbiOutput is NULL return the size in bytes needed for format.
 */
#define ICDecompressGetFormat(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_DECOMPRESS_GET_FORMAT,lpbiInput,lpbiOutput)
#define ICDecompressGetFormatSize(hic,lpbi) ICDecompressGetFormat(hic,lpbi,NULL)

/*
 *  ICDecompressGetPalette()
 *  get the output palette
 */
#define ICDecompressGetPalette(hic,lpbiInput,lpbiOutput) ICSendMessage(hic,ICM_DECOMPRESS_GET_PALETTE,lpbiInput,lpbiOutput)
#define ICDecompressSetPalette(hic,lpbiPalette) ICSendMessage(hic,ICM_DECOMPRESS_SET_PALETTE,lpbiPalette,0)
#define ICDecompressEnd(hic) ICSendMessage(hic,ICM_DECOMPRESS_END,0,0)

/************************************************************************
    decompression (ex) functions
************************************************************************/
// on Win16 these functions are macros that call ICMessage. ICMessage will
// not work on NT. rather than add new entrypoints we have given
// them as static inline functions

/*
 *  ICDecompressEx()
 *  decompress a single frame
 */
dword ICDecompressEx(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst);
:dword ICDecompressEx(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst)
{
ICDECOMPRESSEX ic;
  ic.dwFlags = dwFlags;
  ic.lpbiSrc = lpbiSrc;
  ic.lpSrc = lpSrc;
  ic.xSrc = xSrc;
  ic.ySrc = ySrc;
  ic.dxSrc = dxSrc;
  ic.dySrc = dySrc;
  ic.lpbiDst = lpbiDst;
  ic.lpDst = lpDst;
  ic.xDst = xDst;
  ic.yDst = yDst;
  ic.dxDst = dxDst;
  ic.dyDst = dyDst;
  // note that ICM swaps round the length and pointer
  // length in lparam2, pointer in lparam1
  return ICSendMessage(hic,ICM_DECOMPRESSEX,#ic,sizeof(ic));
}

/*
 *  ICDecompressExBegin()
 *  start compression from a source format (lpbiInput) to a dest
 *  format (lpbiOutput) is supported.
 */
dword ICDecompressExBegin(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst);
:dword ICDecompressExBegin(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst)
{
ICDECOMPRESSEX ic;
  ic.dwFlags = dwFlags;
  ic.lpbiSrc = lpbiSrc;
  ic.lpSrc = lpSrc;
  ic.xSrc = xSrc;
  ic.ySrc = ySrc;
  ic.dxSrc = dxSrc;
  ic.dySrc = dySrc;
  ic.lpbiDst = lpbiDst;
  ic.lpDst = lpDst;
  ic.xDst = xDst;
  ic.yDst = yDst;
  ic.dxDst = dxDst;
  ic.dyDst = dyDst;
  // note that ICM swaps round the length and pointer
  // length in lparam2, pointer in lparam1
  return ICSendMessage(hic,ICM_DECOMPRESSEX_BEGIN,#ic,sizeof(ic));
}

/*
 *  ICDecompressExQuery()
 */
dword ICDecompressExQuery(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst);
:dword ICDecompressExQuery(dword hic,DWORD dwFlags,dword lpbiSrc,LPVOID lpSrc,
	int xSrc,int ySrc,int dxSrc,int dySrc,dword lpbiDst,LPVOID lpDst,int xDst,
	int yDst,int dxDst,int dyDst)
{
ICDECOMPRESSEX ic;
  ic.dwFlags = dwFlags;
  ic.lpbiSrc = lpbiSrc;
  ic.lpSrc = lpSrc;
  ic.xSrc = xSrc;
  ic.ySrc = ySrc;
  ic.dxSrc = dxSrc;
  ic.dySrc = dySrc;
  ic.lpbiDst = lpbiDst;
  ic.lpDst = lpDst;
  ic.xDst = xDst;
  ic.yDst = yDst;
  ic.dxDst = dxDst;
  ic.dyDst = dyDst;

  // note that ICM swaps round the length and pointer
  // length in lparam2, pointer in lparam1
  return ICSendMessage(hic,ICM_DECOMPRESSEX_QUERY,#ic,sizeof(ic));
}

#define ICDecompressExEnd(hic) ICSendMessage(hic,ICM_DECOMPRESSEX_END,0,0)

/************************************************************************
    drawing functions
************************************************************************/

/*
 *  ICDrawBegin()
 *  start decompressing data with format (lpbiInput) directly to the screen
 *  return zero if the decompressor supports drawing.
 */

#define ICDRAW_QUERY        0x00000001L   // test for support
#define ICDRAW_FULLSCREEN   0x00000002L   // draw to full screen
#define ICDRAW_HDC          0x00000004L   // draw to a HDC/HWND

extern WINAPI "msvfw32.dll"{
	DWORD ICDrawBegin(dword hic,DWORD dwFlags,HPALETTE hpal,HWND hwnd,HDC hdc,
		int xDst,int yDst,int dxDst,int dyDst,dword lpbi,int xSrc,int ySrc,int dxSrc,
		int dySrc,DWORD dwRate,DWORD dwScale);
}
/*
 *  ICDraw()
 *  decompress data directly to the screen
 */

#define ICDRAW_HURRYUP      0x80000000L   // don't draw just buffer (hurry up!)
#define ICDRAW_UPDATE       0x40000000L   // don't draw just update screen

extern WINAPI "msvfw32.dll"{
	DWORD ICDraw(dword hic,DWORD dwFlags,LPVOID lpFormat,LPVOID lpData,DWORD cbData,LONG lTime);
}
// ICMessage is not supported on Win32, so provide a static inline function
// to do the same job
dword ICDrawSuggestFormat(dword hic,dword lpbiIn,dword lpbiOut,int dxSrc,
	int dySrc,int dxDst,int dyDst,dword hicDecomp);
:dword ICDrawSuggestFormat(dword hic,dword lpbiIn,dword lpbiOut,int dxSrc,
	int dySrc,int dxDst,int dyDst,dword hicDecomp)
{
ICDRAWSUGGEST ic;
  ic.lpbiIn = lpbiIn;
  ic.lpbiSuggest = lpbiOut;
  ic.dxSrc = dxSrc;
  ic.dySrc = dySrc;
  ic.dxDst = dxDst;
  ic.dyDst = dyDst;
  ic.hicDecompressor = hicDecomp;
  // note that ICM swaps round the length and pointer
  // length in lparam2, pointer in lparam1
  return ICSendMessage(hic,ICM_DRAW_SUGGESTFORMAT,#ic,sizeof(ic));
}

/*
 *  ICDrawQuery()
 *  determines if the compressor is willing to render the specified format.
 */
#define ICDrawQuery(hic,lpbiInput) ICSendMessage(hic,ICM_DRAW_QUERY,lpbiInput,0)
#define ICDrawChangePalette(hic,lpbiInput) ICSendMessage(hic,ICM_DRAW_CHANGEPALETTE,lpbiInput,0)
#define ICGetBuffersWanted(hic,lpdwBuffers) ICSendMessage(hic,ICM_GETBUFFERSWANTED,lpdwBuffers,0)
#define ICDrawEnd(hic) ICSendMessage(hic,ICM_DRAW_END,0,0)
#define ICDrawStart(hic) ICSendMessage(hic,ICM_DRAW_START,0,0)
#define ICDrawStartPlay(hic,lFrom,lTo) ICSendMessage(hic,ICM_DRAW_START_PLAY,lFrom,lTo)
#define ICDrawStop(hic) ICSendMessage(hic,ICM_DRAW_STOP,0,0)
#define ICDrawStopPlay(hic) ICSendMessage(hic,ICM_DRAW_STOP_PLAY,0,0)
#define ICDrawGetTime(hic,lplTime) ICSendMessage(hic,ICM_DRAW_GETTIME,lplTime,0)
#define ICDrawSetTime(hic,lTime) ICSendMessage(hic,ICM_DRAW_SETTIME,lTime,0)
#define ICDrawRealize(hic,hdc,fBackground) ICSendMessage(hic,ICM_DRAW_REALIZE,hdc,fBackground)
#define ICDrawFlush(hic) ICSendMessage(hic,ICM_DRAW_FLUSH,0,0)
#define ICDrawRenderBuffer(hic) ICSendMessage(hic,ICM_DRAW_RENDERBUFFER,0,0)

/************************************************************************
    Status callback functions
************************************************************************/
/*
 *  ICSetStatusProc()
 *  Set the status callback function
 */

// ICMessage is not supported on NT
dword ICSetStatusProc(dword hic,DWORD dwFlags,dword lParam,LONG fpfnStatus);
:dword ICSetStatusProc(dword hic,DWORD dwFlags,dword lParam,LONG fpfnStatus)
{
ICSETSTATUSPROC ic;
  ic.dwFlags = dwFlags;
  ic.lParam = lParam;
  ic.Status = fpfnStatus;
  // note that ICM swaps round the length and pointer
  // length in lparam2, pointer in lparam1
  return ICSendMessage(hic,ICM_SET_STATUS_PROC,#ic,sizeof(ic));
}

/************************************************************************
helper routines for DrawDib and MCIAVI...
************************************************************************/
#define ICDecompressOpen(fccType,fccHandler,lpbiIn,lpbiOut) \
    ICLocate(fccType,fccHandler,lpbiIn,lpbiOut,ICMODE_DECOMPRESS)
#define ICDrawOpen(fccType,fccHandler,lpbiIn) ICLocate(fccType,fccHandler,lpbiIn,NULL,ICMODE_DRAW)

extern WINAPI "msvfw32.dll"{
	dword ICLocate(DWORD fccType,DWORD fccHandler,dword lpbiIn,dword lpbiOut,WORD wFlags);
	dword ICGetDisplayFormat(dword hic,dword lpbiIn,dword lpbiOut,int BitDepth,int dx,int dy);
/************************************************************************
Higher level functions
************************************************************************/
	HANDLE ICImageCompress(dword hic,UINT uiFlags,dword lpbiIn,LPVOID lpBits,
		dword lpbiOut,LONG lQuality,dword plSize);
	HANDLE ICImageDecompress(dword hic,UINT uiFlags,dword lpbiIn,LPVOID lpBits,dword lpbiOut);
}
// Structure used by ICSeqCompressFrame and ICCompressorChoose routines
// Make sure this matches the autodoc in icm.c!
struct COMPVARS{
  LONG		cbSize;		// set to sizeof(COMPVARS) before
				// calling ICCompressorChoose
  DWORD		dwFlags;	// see below...
  dword			hic;		// dword of chosen compressor
  DWORD               fccType;	// basically ICTYPE_VIDEO
  DWORD               fccHandler;	// handler of chosen compressor or
				// "" or "DIB "
  dword	lpbiIn;		// input format
  dword	lpbiOut;	// output format - will compress to this
  LPVOID		lpBitsOut;
  LPVOID		lpBitsPrev;
  LONG		lFrame;
  LONG		lKey;		// key frames how often?
  LONG		lDataRate;	// desired data rate KB/Sec
  LONG		lQ;		// desired quality
  LONG		lKeyCount;
  LPVOID		lpState;	// state of compressor
  LONG		cbState;	// size of the state
};

// FLAGS for dwFlags element of COMPVARS structure:
// set this flag if you initialize COMPVARS before calling ICCompressorChoose
#define ICMF_COMPVARS_VALID	0x00000001	// COMPVARS contains valid data
extern WINAPI "msvfw32.dll"{
//  allows user to choose compressor, quality etc...
	BOOL ICCompressorChoose(HWND hwnd,UINT uiFlags,LPVOID pvIn,LPVOID lpData,dword pc,LPSTR lpszTitle);

// defines for uiFlags
#define ICMF_CHOOSE_KEYFRAME	0x0001	// show KeyFrame Every box
#define ICMF_CHOOSE_DATARATE	0x0002	// show DataRate box
#define ICMF_CHOOSE_PREVIEW	0x0004	// allow expanded preview dialog
#define ICMF_CHOOSE_ALLCOMPRESSORS	0x0008	// don't only show those that
						// can handle the input format
						// or input data
	BOOL ICSeqCompressFrameStart(dword pc,dword lpbiIn);
	void ICSeqCompressFrameEnd(dword pc);
	LPVOID ICSeqCompressFrame(dword pc,UINT uiFlags,LPVOID lpBits,dword pfKey,dword plSize);
	void ICCompressorFree(dword pc);
}
#endif  /* NOCOMPMAN */

/**************************************************************************
 *  DRAWDIB - Routines for drawing to the display.
 *************************************************************************/
#ifndef NODRAWDIB
#define HDRAWDIB dword /* hdd */

/*********************************************************************
  DrawDib Flags
**********************************************************************/
#define DDF_0001            0x0001          /* ;Internal */
#define DDF_UPDATE          0x0002          /* re-draw the last DIB */
#define DDF_SAME_HDC        0x0004          /* HDC same as last call (all setup) */
#define DDF_SAME_DRAW       0x0008          /* draw params are the same */
#define DDF_DONTDRAW        0x0010          /* dont draw frame, just decompress */
#define DDF_ANIMATE         0x0020          /* allow palette animation */
#define DDF_BUFFER          0x0040          /* always buffer image */
#define DDF_JUSTDRAWIT      0x0080          /* just draw it with GDI */
#define DDF_FULLSCREEN      0x0100          /* use DisplayDib */
#define DDF_BACKGROUNDPAL   0x0200	    /* Realize palette in background */
#define DDF_NOTKEYFRAME     0x0400          /* this is a partial frame update, hint */
#define DDF_HURRYUP         0x0800          /* hurry up please! */
#define DDF_HALFTONE        0x1000          /* always halftone */
#define DDF_2000            0x2000          /* ;Internal */
#define DDF_PREROLL         DDF_DONTDRAW    /* Builing up a non-keyframe */
#define DDF_SAME_DIB        DDF_SAME_DRAW
#define DDF_SAME_SIZE       DDF_SAME_DRAW

struct DRAWDIBTIME{
  LONG timeCount;
  LONG timeDraw;
  LONG timeDecompress;
  LONG timeDither;
  LONG timeStretch;
  LONG timeBlt;
  LONG timeSetDIBits;
};

/*********************************************************************
    DrawDib functions
*********************************************************************/
extern WINAPI "msvfw32.dll"{
	HDRAWDIB DrawDibOpen(void);
	BOOL DrawDibClose(HDRAWDIB hdd);
	LPVOID DrawDibGetBuffer(HDRAWDIB hdd,dword lpbi,DWORD dwSize,DWORD dwFlags);
	HPALETTE DrawDibGetPalette(HDRAWDIB hdd);
	BOOL DrawDibSetPalette(HDRAWDIB hdd,HPALETTE hpal);
	BOOL DrawDibChangePalette(HDRAWDIB hdd,int iStart,int iLen,dword lppe);
	UINT DrawDibRealize(HDRAWDIB hdd,HDC hdc,BOOL fBackground);
	BOOL DrawDibStart(HDRAWDIB hdd,DWORD rate);
	BOOL DrawDibStop(HDRAWDIB hdd);
	BOOL DrawDibBegin(HDRAWDIB hdd,HDC hdc,int dxDst,int dyDst,dword lpbi,int dxSrc,int dySrc,UINT wFlags);
	BOOL DrawDibDraw(HDRAWDIB hdd,HDC hdc,int xDst,int yDst,int dxDst,int dyDst,
		dword lpbi,LPVOID lpBits,int xSrc,int ySrc,int dxSrc,int dySrc,UINT wFlags);
#define DrawDibUpdate(hdd,hdc,x,y) DrawDibDraw(hdd,hdc,x,y,0,0,NULL,NULL,0,0,0,0,DDF_UPDATE)
	BOOL DrawDibEnd(HDRAWDIB hdd);
	BOOL DrawDibTime(HDRAWDIB hdd,dword lpddtime);

/* display profiling */
#define PD_CAN_DRAW_DIB         0x0001      /* if you can draw at all */
#define PD_CAN_STRETCHDIB       0x0002      /* basicly RC_STRETCHDIB */
#define PD_STRETCHDIB_1_1_OK    0x0004      /* is it fast? */
#define PD_STRETCHDIB_1_2_OK    0x0008      /* ... */
#define PD_STRETCHDIB_1_N_OK    0x0010      /* ... */

	dword DrawDibProfileDisplay(dword lpbi);
}
#endif  /* NODRAWDIB */

/****************************************************************************
 *  AVIFMT - AVI file format definitions
 ****************************************************************************/

#ifndef NOAVIFMT
#ifndef _INC_MMSYSTEM
#define FOURCC dword
#endif

/* The following is a short description of the AVI file format.  Please
 * see the accompanying documentation for a full explanation.
 * An AVI file is the following RIFF form:
 *	RIFF('AVI'
 *	      LIST('hdrl'
 *		    avih(<MainAVIHeader>)
 *                  LIST ('strl'
 *                      strh(<Stream header>)
 *                      strf(<Stream format>)
 *                      ... additional header data
 *            LIST('movi'
 *      	  { LIST('rec'
 *      		      SubChunk...
 *      		   )
 *      	      | SubChunk } ....
 *            )
 *            [ <AVIIndex> ]
 *      )
 *	The main file header specifies how many streams are present.  For
 *	each one, there must be a stream header chunk and a stream format
 *	chunk, enlosed in a 'strl' LIST chunk.  The 'strf' chunk contains
 *	type-specific format information; for a video stream, this should
 *	be a BITMAPINFO structure, including palette.  For an audio stream,
 *	this should be a WAVEFORMAT (or PCMWAVEFORMAT) structure.
 *	The actual data is contained in subchunks within the 'movi' LIST
 *	chunk.  The first two characters of each data chunk are the
 *	stream number with which that data is associated.
 *	Some defined chunk types:
 *           Video Streams:
 *                  ##db:	RGB DIB bits
 *                  ##dc:	RLE8 compressed DIB bits
 *                  ##pc:	Palette Change
 *           Audio Streams:
 *                  ##wb:	waveform audio bytes
 * The grouping into LIST 'rec' chunks implies only that the contents of
 *   the chunk should be read into memory at the same time.  This
 *   grouping is used for files specifically intended to be played from
 *   CD-ROM.
 * The index chunk at the end of the file should contain one entry for
 *   each data chunk in the file.
 * Limitations for the current software:
 *	Only one video stream and one audio stream are allowed.
 *	The streams must start at the beginning of the file.
 * To register codec types please obtain a copy of the Multimedia
 * Developer Registration Kit from:
 *  Microsoft Corporation
 *  Multimedia Systems Group
 *  Product Marketing
 *  One Microsoft Way
 *  Redmond, WA 98052-6399
 */
/* Macro to make a TWOCC out of two characters */
#ifndef aviTWOCC
#define aviTWOCC(ch0,ch1) ch1<<8|ch0
#endif

#define TWOCC word

/* form types, list types, and chunk types */
#define formtypeAVI             'AVI '
#define listtypeAVIHEADER       'hdrl'
#define ckidAVIMAINHDR          'avih'
#define listtypeSTREAMHEADER    'strl'
#define ckidSTREAMHEADER        'strh'
#define ckidSTREAMFORMAT        'strf'
#define ckidSTREAMHANDLERDATA   'strd'
#define ckidSTREAMNAME		'strn'
#define listtypeAVIMOVIE        'movi'
#define listtypeAVIRECORD       'rec '
#define ckidAVINEWINDEX         'idx1'

/*
** Stream types for the <fccType> field of the stream header.
*/
#define streamtypeVIDEO         'vids'
#define streamtypeAUDIO         'auds'
#define streamtypeMIDI		'mids'
#define streamtypeTEXT          'txts'

/* Basic chunk types */
#define cktypeDIBbits           'db'
#define cktypeDIBcompressed     'dc'
#define cktypePALchange         'pc'
#define cktypeWAVEbytes         'wb'

/* Chunk id to use for extra chunks for padding. */
#define ckidAVIPADDING          'JUNK'

/*
** Main AVI File Header
*/

/* flags for use in <dwFlags> in AVIFileHdr */
#define AVIF_HASINDEX		0x00000010	// Index at end of file?
#define AVIF_MUSTUSEINDEX	0x00000020
#define AVIF_ISINTERLEAVED	0x00000100
#define AVIF_WASCAPTUREFILE	0x00010000
#define AVIF_COPYRIGHTED	0x00020000

/* The AVI File Header LIST chunk should be padded to this size */
#define AVI_HEADERSIZE  2048                    // size of AVI header list

struct MainAVIHeader
{
  DWORD		dwMicroSecPerFrame;	// frame display rate (or 0L)
  DWORD		dwMaxBytesPerSec;	// max. transfer rate
  DWORD		dwPaddingGranularity;	// pad to multiples of this
                               // size; normally 2K.
  DWORD		dwFlags;		// the ever-present flags
  DWORD		dwTotalFrames;		// # frames in file
  DWORD		dwInitialFrames;
  DWORD		dwStreams;
  DWORD		dwSuggestedBufferSize;
  DWORD		dwWidth;
  DWORD		dwHeight;
  DWORD		dwReserved[4];
};

/*
** Stream header
*/

#define AVISF_DISABLED			0x00000001
#define AVISF_VIDEO_PALCHANGES		0x00010000

struct AVIStreamHeader{
  FOURCC		fccType;
  FOURCC		fccHandler;
  DWORD		dwFlags;	/* Contains AVITF_* flags */
  WORD		wPriority;
  WORD		wLanguage;
  DWORD		dwInitialFrames;
  DWORD		dwScale;
  DWORD		dwRate;	/* dwRate / dwScale == samples/second */
  DWORD		dwStart;
  DWORD		dwLength; /* In units above... */
  DWORD		dwSuggestedBufferSize;
  DWORD		dwQuality;
  DWORD		dwSampleSize;
  RECT		rcFrame;
};

/* Flags for index */
#define AVIIF_LIST          0x00000001L // chunk is a 'LIST'
#define AVIIF_KEYFRAME      0x00000010L // this frame is a key frame.
#define AVIIF_FIRSTPART     0x00000020L // this frame is the start of a partial frame.
#define AVIIF_LASTPART      0x00000040L // this frame is the end of a partial frame.
#define AVIIF_MIDPART       AVIIF_LASTPART|AVIIF_FIRSTPART
#define AVIIF_NOTIME	    0x00000100L // this frame doesn't take any time
#define AVIIF_COMPUSE       0x0FFF0000L // these bits are for compressor use

struct AVIINDEXENTRY
{
  DWORD		ckid;
  DWORD		dwFlags;
  DWORD		dwChunkOffset;		// Position of chunk
  DWORD		dwChunkLength;		// Length of chunk
};

/*
** Palette change chunk
** Used in video streams.
*/
struct AVIPALCHANGE
{
  BYTE		bFirstEntry;	/* first entry to change */
  BYTE		bNumEntries;	/* # entries to change (0 if 256) */
  WORD		wFlags;		/* Mostly to preserve alignment... */
  PALETTEENTRY	peNew/*[]*/;	/* New color specifications */
};

#endif /* NOAVIFMT */

/****************************************************************************
 *  MMREG.H (standard include file for MM defines, like FOURCC and things)
 ***************************************************************************/
#ifndef RC_INVOKED
#pragma pack(push,8)
#endif
/*#ifndef NOMMREG
#include <mmreg.h>
#endif
	*/
/****************************************************************************
 *  AVIFile - routines for reading/writing standard AVI files
 ***************************************************************************/
#ifndef NOAVIFILE

/*
 * Ansi - Unicode thunking.
 * Unicode or Ansi-only apps can call the avifile APIs.
 * any Win32 app who wants to use
 * any of the AVI COM interfaces must be UNICODE - the AVISTREAMINFO and
 * AVIFILEINFO structures used in the Info methods of these interfaces are
 * the unicode variants, and no thunking to or from ansi takes place
 * except in the AVIFILE api entrypoints.
 * For Ansi/Unicode thunking: for each entrypoint or structure that
 * uses chars or strings, two versions are declared in the Win32 version,
 * ApiNameW and ApiNameA. The default name ApiName is #defined to one or
 * other of these depending on whether UNICODE is defined (during
 * compilation of the app that is including this header). The source will
 * contain ApiName and ApiNameA (with ApiName being the Win16 implementation,
 * and also #defined to ApiNameW, and ApiNameA being the thunk entrypoint).
 *
 */

#ifndef streamtypeVIDEO
#define streamtypeVIDEO		'vids'
#define streamtypeAUDIO		'auds'
#define streamtypeMIDI		'mids'
#define streamtypeTEXT		'txts'
#endif

#ifndef AVIIF_KEYFRAME
#define AVIIF_KEYFRAME      0x00000010L // this frame is a key frame.
#endif

// For GetFrame::SetFormat - use the best format for the display
#define AVIGETFRAMEF_BESTDISPLAYFMT	1

// Structures used by AVIStreamInfo & AVIFileInfo.
// These are related to, but not identical to, the header chunks
// in an AVI file.

/*
 * --- AVISTREAMINFO ------------------------------------------------
 * for Unicode/Ansi thunking we need to declare three versions of this!
 */
struct AVISTREAMINFOW {
  DWORD		fccType;
  DWORD               fccHandler;
  DWORD               dwFlags;        /* Contains AVITF_* flags */
  DWORD		dwCaps;
  WORD		wPriority;
  WORD		wLanguage;
  DWORD               dwScale;
  DWORD               dwRate; /* dwRate / dwScale == samples/second */
  DWORD               dwStart;
  DWORD               dwLength; /* In units above... */
  DWORD		dwInitialFrames;
  DWORD               dwSuggestedBufferSize;
  DWORD               dwQuality;
  DWORD               dwSampleSize;
  RECT                rcFrame;
  DWORD		dwEditCount;
  DWORD		dwFormatChangeCount;
  WCHAR		szName[64];
};

struct AVISTREAMINFOA {
  DWORD		fccType;
  DWORD               fccHandler;
  DWORD               dwFlags;        /* Contains AVITF_* flags */
  DWORD		dwCaps;
  WORD		wPriority;
  WORD		wLanguage;
  DWORD               dwScale;
  DWORD               dwRate; /* dwRate / dwScale == samples/second */
  DWORD               dwStart;
  DWORD               dwLength; /* In units above... */
  DWORD		dwInitialFrames;
  DWORD               dwSuggestedBufferSize;
  DWORD               dwQuality;
  DWORD               dwSampleSize;
  RECT                rcFrame;
  DWORD		dwEditCount;
  DWORD		dwFormatChangeCount;
  char		szName[64];
};

#ifdef UNICODE
#define AVISTREAMINFO	AVISTREAMINFOW
#else
#define AVISTREAMINFO	AVISTREAMINFOA
#endif

#define AVISTREAMINFO_DISABLED			0x00000001
#define AVISTREAMINFO_FORMATCHANGES		0x00010000

/*
 * --- AVIFILEINFO ----------------------------------------------------
 */
struct AVIFILEINFOW {
  DWORD		dwMaxBytesPerSec;	// max. transfer rate
  DWORD		dwFlags;		// the ever-present flags
  DWORD		dwCaps;
  DWORD		dwStreams;
  DWORD		dwSuggestedBufferSize;
  DWORD		dwWidth;
  DWORD		dwHeight;
  DWORD		dwScale;
  DWORD		dwRate;	/* dwRate / dwScale == samples/second */
  DWORD		dwLength;
  DWORD		dwEditCount;
  WCHAR		szFileType[64];		// descriptive string for file type?
};

struct AVIFILEINFOA {
  DWORD		dwMaxBytesPerSec;	// max. transfer rate
  DWORD		dwFlags;		// the ever-present flags
  DWORD		dwCaps;
  DWORD		dwStreams;
  DWORD		dwSuggestedBufferSize;
  DWORD		dwWidth;
  DWORD		dwHeight;
  DWORD		dwScale;
  DWORD		dwRate;	/* dwRate / dwScale == samples/second */
  DWORD		dwLength;
  DWORD		dwEditCount;
  char		szFileType[64];		// descriptive string for file type?
};

#ifdef UNICODE
#define AVIFILEINFO	AVIFILEINFOW
#else
#define AVIFILEINFO	AVIFILEINFOA
#endif

// Flags for dwFlags
#define AVIFILEINFO_HASINDEX		0x00000010
#define AVIFILEINFO_MUSTUSEINDEX	0x00000020
#define AVIFILEINFO_ISINTERLEAVED	0x00000100
#define AVIFILEINFO_WASCAPTUREFILE	0x00010000
#define AVIFILEINFO_COPYRIGHTED		0x00020000

// Flags for dwCaps
#define AVIFILECAPS_CANREAD		0x00000001
#define AVIFILECAPS_CANWRITE		0x00000002
#define AVIFILECAPS_ALLKEYFRAMES	0x00000010
#define AVIFILECAPS_NOCOMPRESSION	0x00000020

/************************************************************************/
/* Declaration for the AVICOMPRESSOPTIONS structure.  Make sure it 	*/
/* matches the AutoDoc in avisave.c !!!                            	*/
/************************************************************************/
struct AVICOMPRESSOPTIONS{
  DWORD	fccType;		    /* stream type, for consistency */
  DWORD       fccHandler;                 /* compressor */
  DWORD       dwKeyFrameEvery;            /* keyframe rate */
  DWORD       dwQuality;                  /* compress quality 0-10,000 */
  DWORD       dwBytesPerSecond;           /* bytes per second */
  DWORD       dwFlags;                    /* flags... see below */
  LPVOID      lpFormat;                   /* save format */
  DWORD       cbFormat;
  LPVOID      lpParms;                    /* compressor options */
  DWORD       cbParms;
  DWORD       dwInterleaveEvery;          /* for non-video streams only */
};

// Defines for the dwFlags field of the AVICOMPRESSOPTIONS struct
// Each of these flags determines if the appropriate field in the structure
// (dwInterleaveEvery, dwBytesPerSecond, and dwKeyFrameEvery) is payed
// attention to.  See the autodoc in avisave.c for details.
#define AVICOMPRESSF_INTERLEAVE		0x00000001    // interleave
#define AVICOMPRESSF_DATARATE		0x00000002    // use a data rate
#define AVICOMPRESSF_KEYFRAMES		0x00000004    // use keyframes
#define AVICOMPRESSF_VALID		0x00000008    // has valid data?

//#include <ole2.h>

/****** AVI Stream Interface *******************************************/
struct IAVIStream
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IAVIStream methods ***
  dword Create;
  dword Info;
  dword FindSample;
  dword ReadFormat;
  dword SetFormat;
  dword Read;
  dword Write;
  dword Delete;
  dword ReadData;
  dword WriteData;
#ifdef _WIN32
  dword SetInfo;
#else
  dword Reserved1;
  dword Reserved2;
  dword Reserved3;
  dword Reserved4;
  dword Reserved5;
#endif
};

struct IAVIStreaming
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IAVIStreaming methods ***
  dword Begin;
  dword End;
};

struct IAVIEditStream
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** IAVIEditStream methods ***
  dword Cut;
  dword Copy;
  dword Paste;
  dword Clone;
  dword SetInfo;
};

/****** AVI File Interface *******************************************/
struct IAVIFile
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
  // *** IAVIFile methods ***
  dword Info;
  dword GetStream;
  dword CreateStream;
  dword WriteData;
  dword ReadData;
  dword EndRecord;
  dword DeleteStream;
};

/****** GetFrame Interface *******************************************/
struct IGetFrame
{
// *** IUnknown methods ***
  dword QueryInterface;
  dword AddRef;
  dword Release;
// *** IGetFrame methods ***
  dword GetFrame;
  dword Begin;
  dword End;
  dword SetFormat;
};

/****** GUIDs *******************************************/
#define DEFINE_AVIGUID(name,l,w1,w2) DEFINE_GUID(name,l,w1,w2,0xC0,0,0,0,0,0,0,0x46)
:DEFINE_AVIGUID(IID_IAVIFile,      0x00020020,0,0);
:DEFINE_AVIGUID(IID_IAVIStream,    0x00020021,0,0);
:DEFINE_AVIGUID(IID_IAVIStreaming, 0x00020022,0,0);
:DEFINE_AVIGUID(IID_IGetFrame,     0x00020023,0,0);
:DEFINE_AVIGUID(IID_IAVIEditStream,0x00020024,0,0);
#ifndef UNICODE
:DEFINE_AVIGUID(CLSID_AVISimpleUnMarshal,0x00020009,0,0);
#endif

:DEFINE_AVIGUID(CLSID_AVIFile,0x00020000,0,0);

#define	AVIFILEHANDLER_CANREAD		0x0001
#define	AVIFILEHANDLER_CANWRITE		0x0002
#define	AVIFILEHANDLER_CANACCEPTNONRGB	0x0004

// functions
extern WINAPI "avifil32.dll"{
	void AVIFileInit(void);   // Call this first!
	void AVIFileExit(void);
	ULONG AVIFileAddRef(dword pfile);
	ULONG AVIFileRelease(dword pfile);

#ifdef _WIN32
	dword AVIFileOpenA(dword ppfile,LPCSTR szFile,UINT uMode,dword lpHandler);
	dword AVIFileOpenW(dword ppfile,LPCWSTR szFile,UINT uMode,dword lpHandler);
#ifdef UNICODE
#define AVIFileOpen	  AVIFileOpenW
#else
#define AVIFileOpen	  AVIFileOpenA
#endif
#else // win16
	dword AVIFileOpen(dword ppfile,LPCSTR szFile,UINT uMode,dword lpHandler);
#define AVIFileOpenW	AVIFileOpen	    /* ;Internal */
#endif

#ifdef _WIN32
	dword AVIFileInfoW(dword pfile,dword pfi,LONG lSize);
	dword AVIFileInfoA(dword pfile,dword pfi,LONG lSize);
#ifdef UNICODE
#define AVIFileInfo	AVIFileInfoW
#else
#define AVIFileInfo	AVIFileInfoA
#endif
#else //win16 version
	dword AVIFileInfo(dword pfile,dword pfi,LONG lSize);
#define AVIFileInfoW AVIFileInfo	    /* ;Internal */
#endif

	dword AVIFileGetStream(dword pfile,dword ppavi,DWORD fccType,LONG lParam);

#ifdef _WIN32
	dword AVIFileCreateStreamW(dword pfile,dword ppavi,dword psi);
	dword AVIFileCreateStreamA(dword pfile,dword ppavi,dword psi);
#ifdef UNICODE
#define AVIFileCreateStream	AVIFileCreateStreamW
#else
#define AVIFileCreateStream	AVIFileCreateStreamA
#endif
#else //win16 version
	dword AVIFileCreateStream(dword pfile,dword ppavi,dword psi);
#define AVIFileCreateStreamW AVIFileCreateStream	    /* ;Internal */
#endif

	dword AVIFileWriteData(dword pfile,DWORD ckid,LPVOID lpData,LONG cbData);
	dword AVIFileReadData(dword pfile,DWORD ckid,LPVOID lpData,dword lpcbData);
	dword AVIFileEndRecord(dword pfile);
	ULONG AVIStreamAddRef(dword pavi);
	ULONG AVIStreamRelease(dword pavi);
	dword AVIStreamInfoW(dword pavi,dword psi,LONG lSize);
	dword AVIStreamInfoA(dword pavi,dword psi,LONG lSize);
#ifdef UNICODE
#define AVIStreamInfo	AVIStreamInfoW
#else
#define AVIStreamInfo	AVIStreamInfoA
#endif

	LONG AVIStreamFindSample(dword pavi,LONG lPos,LONG lFlags);
	dword AVIStreamReadFormat(dword pavi,LONG lPos,LPVOID lpFormat,dword lpcbFormat);
	dword AVIStreamSetFormat(dword pavi,LONG lPos,LPVOID lpFormat,LONG cbFormat);
	dword AVIStreamReadData(dword pavi,DWORD fcc,LPVOID lp,dword lpcb);
	dword AVIStreamWriteData(dword pavi,DWORD fcc,LPVOID lp,LONG cb);
	dword AVIStreamRead(dword pavi,LONG lStart,LONG lSamples,LPVOID lpBuffer,
		LONG cbBuffer,dword plBytes,dword plSamples);
#define AVISTREAMREAD_CONVENIENT	-1L

	dword AVIStreamWrite(dword pavi,LONG lStart,LONG lSamples,LPVOID lpBuffer,
		LONG cbBuffer,DWORD dwFlags,dword plSampWritten,dword plBytesWritten);

// Right now, these just use AVIStreamInfo() to get information, then
// return some of it.  Can they be more efficient?
	LONG AVIStreamStart(dword pavi);
	LONG AVIStreamLength(dword pavi);
	LONG AVIStreamTimeToSample(dword pavi,LONG lTime);
	LONG AVIStreamSampleToTime(dword pavi,LONG lSample);
	dword AVIStreamBeginStreaming(dword pavi,LONG lStart,LONG lEnd,LONG lRate);
	dword AVIStreamEndStreaming(dword pavi);

// helper functions for using IGetFrame
	dword AVIStreamGetFrameOpen(dword pavi,dword lpbiWanted);
	LPVOID AVIStreamGetFrame(dword pg,LONG lPos);
	dword AVIStreamGetFrameClose(dword pg);

// !!! We need some way to place an advise on a stream....
// STDAPI AVIStreamHasChanged   (dword pavi);

// Shortcut function
	dword AVIStreamOpenFromFileA(dword ppavi,LPCSTR szFile,DWORD fccType,
		LONG lParam,UINT mode,dword pclsidHandler);
	dword AVIStreamOpenFromFileW(dword ppavi,LPCWSTR szFile,DWORD fccType,
		LONG lParam,UINT mode,dword pclsidHandler);
#ifdef UNICODE
#define AVIStreamOpenFromFile	AVIStreamOpenFromFileW
#else
#define AVIStreamOpenFromFile	AVIStreamOpenFromFileA
#endif

// Use to create disembodied streams
	dword AVIStreamCreate(dword ppavi,LONG lParam1,LONG lParam2,dword pclsidHandler);
}
// PHANDLER    AVIAPI AVIGetHandler         (dword pavi, PAVISTREAMHANDLER psh);
// dword  AVIAPI AVIGetStream          (PHANDLER p);

// flags for AVIStreamFindSample
#define FIND_DIR        0x0000000FL     // direction
#define FIND_NEXT       0x00000001L     // go forward
#define FIND_PREV       0x00000004L     // go backward
#define FIND_FROM_START 0x00000008L     // start at the logical beginning
#define FIND_TYPE       0x000000F0L     // type mask
#define FIND_KEY        0x00000010L     // find key frame.
#define FIND_ANY        0x00000020L     // find any (non-empty) sample
#define FIND_FORMAT     0x00000040L     // find format change
#define FIND_RET        0x0000F000L     // return mask
#define FIND_POS        0x00000000L     // return logical position
#define FIND_LENGTH     0x00001000L     // return logical size
#define FIND_OFFSET     0x00002000L     // return physical position
#define FIND_SIZE       0x00003000L     // return physical size
#define FIND_INDEX      0x00004000L     // return physical index position

//  stuff to support backward compat.
#define AVIStreamFindKeyFrame AVIStreamFindSample
#define FindKeyFrame	FindSample
#define AVIStreamClose AVIStreamRelease
#define AVIFileClose   AVIFileRelease
#define AVIStreamInit  AVIFileInit
#define AVIStreamExit  AVIFileExit
#define SEARCH_NEAREST  FIND_PREV
#define SEARCH_BACKWARD FIND_PREV
#define SEARCH_FORWARD  FIND_NEXT
#define SEARCH_KEY      FIND_KEY
#define SEARCH_ANY      FIND_ANY

//  helper macros.
#define AVIStreamSampleToSample(pavi1,pavi2,l) AVIStreamTimeToSample(pavi1,AVIStreamSampleToTime(pavi2,l))
#define AVIStreamNextSample(pavi,l) AVIStreamFindSample(pavi,l+1,FIND_NEXT|FIND_ANY)
#define AVIStreamPrevSample(pavi,l) AVIStreamFindSample(pavi,l-1,FIND_PREV|FIND_ANY)
#define AVIStreamNearestSample(pavi,l) AVIStreamFindSample(pavi,l,FIND_PREV|FIND_ANY)
#define AVIStreamNextKeyFrame(pavi,l) AVIStreamFindSample(pavi,l+1,FIND_NEXT|FIND_KEY)
#define AVIStreamPrevKeyFrame(pavi,l) AVIStreamFindSample(pavi,l-1,FIND_PREV|FIND_KEY)
#define AVIStreamNearestKeyFrame(pavi,l) AVIStreamFindSample(pavi,l,FIND_PREV|FIND_KEY)
#define AVIStreamIsKeyFrame(pavi,l) (AVIStreamNearestKeyFrame(pavi,l) == l)
#define AVIStreamPrevSampleTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamPrevSample(pavi,AVIStreamTimeToSample(pavi,t)))
#define AVIStreamNextSampleTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamNextSample(pavi,AVIStreamTimeToSample(pavi,t)))
#define AVIStreamNearestSampleTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamNearestSample(pavi,AVIStreamTimeToSample(pavi,t)))
#define AVIStreamNextKeyFrameTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamNextKeyFrame(pavi,AVIStreamTimeToSample(pavi, t)))
#define AVIStreamPrevKeyFrameTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamPrevKeyFrame(pavi,AVIStreamTimeToSample(pavi, t)))
#define AVIStreamNearestKeyFrameTime(pavi,t) AVIStreamSampleToTime(pavi,AVIStreamNearestKeyFrame(pavi,AVIStreamTimeToSample(pavi, t)))
#define AVIStreamStartTime(pavi) AVIStreamSampleToTime(pavi,AVIStreamStart(pavi))
#define AVIStreamLengthTime(pavi) AVIStreamSampleToTime(pavi,AVIStreamLength(pavi))
#define AVIStreamEnd(pavi) AVIStreamStart(pavi)+AVIStreamLength(pavi)
#define AVIStreamEndTime(pavi) AVIStreamSampleToTime(pavi,AVIStreamEnd(pavi))
#define AVIStreamSampleSize(pavi,lPos,plSize) AVIStreamRead(pavi,lPos,1,NULL,0,plSize,NULL)
#define AVIStreamFormatSize(pavi,lPos,plSize) AVIStreamReadFormat(pavi,lPos,NULL,plSize)
#define AVIStreamDataSize(pavi,fcc,plSize) AVIStreamReadData(pavi,fcc,NULL,plSize)

/****************************************************************************
 *  AVISave routines and structures
 ***************************************************************************/
#ifndef comptypeDIB
#define comptypeDIB         'DIB '
#endif

extern WINAPI "avifil32.dll"{
	dword AVIMakeCompressedStream(dword ppsCompressed,dword ppsSource,
		dword lpOptions,dword pclsidHandler);
	cdecl dword AVISaveA(LPCSTR szFile,dword pclsidHandler,dword lpfnCallback,
		int nStreams,dword pfile,dword lpOptions,...);
	dword AVISaveVA(LPCSTR szFile,dword pclsidHandler,dword lpfnCallback,
		int nStreams,dword ppavi,dword plpOptions);
	cdecl dword AVISaveW(LPCWSTR szFile,dword pclsidHandler,dword lpfnCallback,
		int nStreams,dword pfile,dword lpOptions,...);
	dword AVISaveVW(LPCWSTR szFile,dword pclsidHandler,dword lpfnCallback,
		int nStreams,dword ppavi,dword plpOptions);
#ifdef UNICODE
#define AVISave		AVISaveW
#define AVISaveV	AVISaveVW
#else
#define AVISave		AVISaveA
#define AVISaveV	AVISaveVA
#endif

	dword AVISaveOptions(HWND hwnd,UINT	uiFlags,int	nStreams,dword ppavi,dword plpOptions);
	dword AVISaveOptionsFree(int nStreams,dword plpOptions);

// FLAGS FOR uiFlags:
// Same as the flags for ICCompressorChoose (see compman.h)
// These determine what the compression options dialog for video streams
// will look like.
	dword AVIBuildFilterW(LPWSTR lpszFilter,LONG cbFilter,BOOL fSaving);
	dword AVIBuildFilterA(LPSTR lpszFilter,LONG cbFilter,BOOL fSaving);
#ifdef UNICODE
#define AVIBuildFilter	AVIBuildFilterW
#else
#define AVIBuildFilter	AVIBuildFilterA
#endif
	dword AVIMakeFileFromStreams(dword ppfile,int	nStreams,dword papStreams);
	dword AVIMakeStreamFromClipboard(UINT cfFormat,HANDLE hGlobal,dword ppstream);

/****************************************************************************
 *  Clipboard routines
 ***************************************************************************/
	dword AVIPutFileOnClipboard(dword pf);
	dword AVIGetFromClipboard(dword lppf);
	dword AVIClearClipboard(void);

/****************************************************************************
 *  Editing routines
 ***************************************************************************/
	dword CreateEditableStream(dword ppsEditable,dword psSource);
	dword EditStreamCut(dword pavi,dword plStart,dword plLength,dword ppResult);
	dword EditStreamCopy(dword pavi,dword plStart,dword plLength,dword ppResult);
	dword EditStreamPaste(dword pavi,dword plPos,dword plLength,dword pstream,LONG lStart,LONG lEnd);
	dword EditStreamClone(dword pavi,dword ppResult);
	dword EditStreamSetNameA(dword pavi,LPCSTR lpszName);
	dword EditStreamSetNameW(dword pavi,LPCWSTR lpszName);
	dword EditStreamSetInfoW(dword pavi,dword lpInfo,LONG cbInfo);
	dword EditStreamSetInfoA(dword pavi,dword lpInfo,LONG cbInfo);
#ifdef UNICODE
#define EditStreamSetInfo	EditStreamSetInfoW
#define EditStreamSetName	EditStreamSetNameW
#else
#define EditStreamSetInfo	EditStreamSetInfoA
#define EditStreamSetName	EditStreamSetNameA
#endif
}
/*	-	-	-	-	-	-	-	-	*/
#ifndef AVIERR_OK
#define AVIERR_OK               0L

#define MAKE_AVIERR(error) MAKE_SCODE(SEVERITY_ERROR,FACILITY_ITF,0x4000+error)

// !!! Questions to be answered:
// How can you get a string form of these errors?
// Which of these errors should be replaced by errors in SCODE.H?
#define AVIERR_UNSUPPORTED      0x80044065
#define AVIERR_BADFORMAT        0x80044066
#define AVIERR_MEMORY           0x80044067
#define AVIERR_INTERNAL         0x80044068
#define AVIERR_BADFLAGS         0x80044069
#define AVIERR_BADPARAM         0x8004406A
#define AVIERR_BADSIZE          0x8004406B
#define AVIERR_BADHANDLE        0x8004406C
#define AVIERR_FILEREAD         0x8004406D
#define AVIERR_FILEWRITE        0x8004406E
#define AVIERR_FILEOPEN         0x8004406F
#define AVIERR_COMPRESSOR       0x80044070
#define AVIERR_NOCOMPRESSOR     0x80044071
#define AVIERR_READONLY		0x80044072
#define AVIERR_NODATA		0x80044073
#define AVIERR_BUFFERTOOSMALL	0x80044074
#define AVIERR_CANTCOMPRESS	0x80044075
#define AVIERR_USERABORT        0x800440C6
#define AVIERR_ERROR            0x800440C7
#endif
#endif  /* NOAVIFILE */

/****************************************************************************
 *  MCIWnd - Window class for MCI objects
 ***************************************************************************/

#ifndef NOMCIWND
/*----------------------------------------------------------------------------*\
 *  MCIWnd
 *    MCIWnd window class header file.
 *    the MCIWnd window class is a window class for controling MCI devices
 *    MCI devices include, wave files, midi files, AVI Video, cd audio,
 *    vcr, video disc, and others..
 *    to learn more about MCI and mci command sets see the
 *    "Microsoft Multimedia Programmers's guide" in the Win31 SDK
 *    the easiest use of the MCIWnd class is like so:
 *          hwnd = MCIWndCreate(hwndParent, hInstance, 0, "chimes.wav");
 *          ...
 *          MCIWndPlay(hwnd);
 *          MCIWndStop(hwnd);
 *          MCIWndPause(hwnd);
 *          ....
 *          MCIWndDestroy(hwnd);
 *    this will create a window with a play/pause, stop and a playbar
 *    and start the wave file playing.
 *    mciwnd.h defines macros for all the most common MCI commands, but
 *    any string command can be used if needed.
 *    Note: unlike the mciSendString() API, no alias or file name needs
 *    to be specifed, since the device to use is implied by the window handle.
 *          MCIWndSendString(hwnd, "setaudio stream to 2");
 *    (C) Copyright Microsoft Corp. 1991-1995.  All rights reserved.
 *    You have a royalty-free right to use, modify, reproduce and
 *    distribute the Sample Files (and/or any modified version) in
 *    any way you find useful, provided that you agree that
 *    Microsoft has no warranty obligations or liability for any
 *    Sample Application Files.
 *    If you did not get this from Microsoft Sources, then it may not be the
 *    most current version.  This sample code in particular will be updated
 *    and include more documentation.
 *    Sources are:
 *       CompuServe: WINSDK forum, MDK section.
 *       Anonymous FTP from ftp.uu.net vendor\microsoft\multimedia
 * WIN32:
 *    MCIWnd supports both ansi and unicode interfaces. For any message that
 *    takes or returns a text string, two versions of the message are defined,
 *    appended with A or W for Ansi or Wide Char. The message or api itself
 *    is defined to be one or other of these depending on whether you have
 *    UNICODE defined in your application.
 *    Thus for the api MCIWndCreate, there are in fact two apis,
 *    MCIWndCreateA and MCIWndCreateW. If you call MCIWndCreate, this will be
 *    re-routed to MCIWndCreateA unless UNICODE is defined when building your
 *    application. In any one application, you can mix calls to the
 *    Ansi and Unicode entrypoints.
 *    If you use SendMessage instead of the macros below such as MCIWndOpen(),
 *    you will see that the messages have changed for WIN32, to support Ansi
 *    and Unicode entrypoints. In particular, MCI_OPEN has been replaced by
 *    MCWNDM_OPENA, or MCIWNDM_OPENW (MCIWNDM_OPEN is defined to be one or
 *    other of these).
 *    Also, note that the WIN32 implementation of MCIWnd uses UNICODE
 *    so all apis and messages supporting ANSI strings do so by mapping them
 *    UNICODE strings and then calling the corresponding UNICODE entrypoint.
 *----------------------------------------------------------------------------*/

#define MCIWndSM SendMessage    /* SendMessage in C */
#define MCIWND_WINDOW_CLASS "MCIWndClass"
extern WINAPI "msvfw32.dll"{
	HWND MCIWndCreateA(HWND hwndParent,HINSTANCE hInstance,DWORD dwStyle,LPCSTR szFile);
	HWND MCIWndCreateW(HWND hwndParent,HINSTANCE hInstance,DWORD dwStyle,LPCWSTR szFile);
#ifdef UNICODE
#define MCIWndCreate    MCIWndCreateW
#else
#define MCIWndCreate    MCIWndCreateA
#endif
	BOOL MCIWndRegisterClass(void);
}
// Flags for the MCIWndOpen command
#define MCIWNDOPENF_NEW	            0x0001  // open a new file

// window styles
#define MCIWNDF_NOAUTOSIZEWINDOW   0x0001  // when movie size changes
#define MCIWNDF_NOPLAYBAR          0x0002  // no toolbar
#define MCIWNDF_NOAUTOSIZEMOVIE    0x0004  // when window size changes
#define MCIWNDF_NOMENU             0x0008  // no popup menu from RBUTTONDOWN
#define MCIWNDF_SHOWNAME           0x0010  // show name in caption
#define MCIWNDF_SHOWPOS            0x0020  // show position in caption
#define MCIWNDF_SHOWMODE           0x0040  // show mode in caption
#define MCIWNDF_SHOWALL            0x0070  // show all
#define MCIWNDF_NOTIFYMODE         0x0100  // tell parent of mode change
#define MCIWNDF_NOTIFYPOS          0x0200  // tell parent of pos change
#define MCIWNDF_NOTIFYSIZE         0x0400  // tell parent of size change
#define MCIWNDF_NOTIFYERROR        0x1000  // tell parent of an error
#define MCIWNDF_NOTIFYALL          0x1F00  // tell all
#define MCIWNDF_NOTIFYANSI	   0x0080

// The MEDIA notification includes a text string.
// To receive notifications in ANSI instead of unicode set the
// MCIWNDF_NOTIFYANSI style bit. The macro below includes this bit
// by default unless you define UNICODE in your application.
#define MCIWNDF_NOTIFYMEDIAA       0x0880  // tell parent of media change
#define MCIWNDF_NOTIFYMEDIAW       0x0800  // tell parent of media change
#ifdef UNICODE
#define MCIWNDF_NOTIFYMEDIA         MCIWNDF_NOTIFYMEDIAW
#else
#define MCIWNDF_NOTIFYMEDIA         MCIWNDF_NOTIFYMEDIAA
#endif

#define MCIWNDF_RECORD              0x2000  // Give a record button
#define MCIWNDF_NOERRORDLG          0x4000  // Show Error Dlgs for MCI cmds?
#define MCIWNDF_NOOPEN		    0x8000  // Don't allow user to open things

// can macros
#define MCIWndCanPlay(hwnd)         MCIWndSM(hwnd,MCIWNDM_CAN_PLAY,0,0)
#define MCIWndCanRecord(hwnd)       MCIWndSM(hwnd,MCIWNDM_CAN_RECORD,0,0)
#define MCIWndCanSave(hwnd)         MCIWndSM(hwnd,MCIWNDM_CAN_SAVE,0,0)
#define MCIWndCanWindow(hwnd)       MCIWndSM(hwnd,MCIWNDM_CAN_WINDOW,0,0)
#define MCIWndCanEject(hwnd)        MCIWndSM(hwnd,MCIWNDM_CAN_EJECT,0,0)
#define MCIWndCanConfig(hwnd)       MCIWndSM(hwnd,MCIWNDM_CAN_CONFIG,0,0)
#define MCIWndPaletteKick(hwnd)     MCIWndSM(hwnd,MCIWNDM_PALETTEKICK,0,0)
#define MCIWndSave(hwnd,szFile)     MCIWndSM(hwnd,MCI_SAVE,0,szFile)
#define MCIWndSaveDialog(hwnd)      MCIWndSave(hwnd,-1)

// if you dont give a device it will use the current device....
#define MCIWndNew(hwnd,lp)         MCIWndSM(hwnd,MCIWNDM_NEW,0,lp)
#define MCIWndRecord(hwnd)          MCIWndSM(hwnd,MCI_RECORD,0,0)
#define MCIWndOpen(hwnd,sz,f)     MCIWndSM(hwnd,MCIWNDM_OPEN,f,sz)
#define MCIWndOpenDialog(hwnd)      MCIWndOpen(hwnd,-1,0)
#define MCIWndClose(hwnd)           MCIWndSM(hwnd,MCI_CLOSE,0,0)
#define MCIWndPlay(hwnd)            MCIWndSM(hwnd,MCI_PLAY,0,0)
#define MCIWndStop(hwnd)            MCIWndSM(hwnd,MCI_STOP,0,0)
#define MCIWndPause(hwnd)           MCIWndSM(hwnd,MCI_PAUSE,0,0)
#define MCIWndResume(hwnd)          MCIWndSM(hwnd,MCI_RESUME,0,0)
#define MCIWndSeek(hwnd,lPos)      MCIWndSM(hwnd,MCI_SEEK, 0,lPos)
#define MCIWndEject(hwnd)           MCIWndSM(hwnd,MCIWNDM_EJECT,0,0)
#define MCIWndHome(hwnd)            MCIWndSeek(hwnd,MCIWND_START)
#define MCIWndEnd(hwnd)             MCIWndSeek(hwnd,MCIWND_END)
#define MCIWndGetSource(hwnd,prc)  MCIWndSM(hwnd,MCIWNDM_GET_SOURCE,0,prc)
#define MCIWndPutSource(hwnd,prc)  MCIWndSM(hwnd,MCIWNDM_PUT_SOURCE,0,prc)
#define MCIWndGetDest(hwnd,prc)    MCIWndSM(hwnd,MCIWNDM_GET_DEST,0,prc)
#define MCIWndPutDest(hwnd,prc)    MCIWndSM(hwnd,MCIWNDM_PUT_DEST,0,prc)
#define MCIWndPlayReverse(hwnd)    MCIWndSM(hwnd,MCIWNDM_PLAYREVERSE,0,0)
#define MCIWndPlayFrom(hwnd,lPos)  MCIWndSM(hwnd,MCIWNDM_PLAYFROM,0,lPos)
#define MCIWndPlayTo(hwnd,lPos)    MCIWndSM(hwnd,MCIWNDM_PLAYTO,0,lPos)
#define MCIWndPlayFromTo(hwnd,lStart,lEnd) (MCIWndSeek(hwnd,lStart),MCIWndPlayTo(hwnd,lEnd))
#define MCIWndGetDeviceID(hwnd)     MCIWndSM(hwnd,MCIWNDM_GETDEVICEID,0,0)
#define MCIWndGetAlias(hwnd)        MCIWndSM(hwnd,MCIWNDM_GETALIAS,0,0)
#define MCIWndGetMode(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_GETMODE,len,lp)
#define MCIWndGetPosition(hwnd)     MCIWndSM(hwnd,MCIWNDM_GETPOSITION,0,0)
#define MCIWndGetPositionString(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_GETPOSITION,len,lp)
#define MCIWndGetStart(hwnd)        MCIWndSM(hwnd,MCIWNDM_GETSTART,0,0)
#define MCIWndGetLength(hwnd)       MCIWndSM(hwnd,MCIWNDM_GETLENGTH,0,0)
#define MCIWndGetEnd(hwnd)          MCIWndSM(hwnd,MCIWNDM_GETEND,0,0)
#define MCIWndStep(hwnd, n)         MCIWndSM(hwnd,MCI_STEP,0,n)
#define MCIWndDestroy(hwnd)         MCIWndSM(hwnd,WM_CLOSE,0,0)
#define MCIWndSetZoom(hwnd,iZoom)   MCIWndSM(hwnd,MCIWNDM_SETZOOM,0,iZoom)
#define MCIWndGetZoom(hwnd)         MCIWndSM(hwnd,MCIWNDM_GETZOOM,0,0)
#define MCIWndSetVolume(hwnd,iVol)  MCIWndSM(hwnd,MCIWNDM_SETVOLUME,0,iVol)
#define MCIWndGetVolume(hwnd)       MCIWndSM(hwnd,MCIWNDM_GETVOLUME,0,0)
#define MCIWndSetSpeed(hwnd,iSpeed) MCIWndSM(hwnd,MCIWNDM_SETSPEED,0,iSpeed)
#define MCIWndGetSpeed(hwnd)        MCIWndSM(hwnd,MCIWNDM_GETSPEED,0,0)
#define MCIWndSetTimeFormat(hwnd,lp) MCIWndSM(hwnd,MCIWNDM_SETTIMEFORMAT,0,lp)
#define MCIWndGetTimeFormat(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_GETTIMEFORMAT,len,lp)
#define MCIWndValidateMedia(hwnd)   MCIWndSM(hwnd,MCIWNDM_VALIDATEMEDIA,0,0)
#define MCIWndSetRepeat(hwnd,f)     MCIWndSM(hwnd,MCIWNDM_SETREPEAT,0,f)
#define MCIWndGetRepeat(hwnd)       MCIWndSM(hwnd,MCIWNDM_GETREPEAT,0,0)
#define MCIWndUseFrames(hwnd)       MCIWndSetTimeFormat(hwnd,"frames")
#define MCIWndUseTime(hwnd)         MCIWndSetTimeFormat(hwnd,"ms")
#define MCIWndSetActiveTimer(hwnd,active)	MCIWndSM(hwnd,MCIWNDM_SETACTIVETIMER,active,0)
#define MCIWndSetInactiveTimer(hwnd,inactive)	MCIWndSM(hwnd,MCIWNDM_SETINACTIVETIMER,inactive,0)
#define MCIWndSetTimers(hwnd,active,inactive)	MCIWndSM(hwnd,MCIWNDM_SETTIMERS,active,inactive)
#define MCIWndGetActiveTimer(hwnd) MCIWndSM(hwnd,MCIWNDM_GETACTIVETIMER,0,0);
#define MCIWndGetInactiveTimer(hwnd) MCIWndSM(hwnd,MCIWNDM_GETINACTIVETIMER,0,0);
#define MCIWndRealize(hwnd,fBkgnd) MCIWndSM(hwnd,MCIWNDM_REALIZE,fBkgnd,0)
#define MCIWndSendString(hwnd,sz)  MCIWndSM(hwnd,MCIWNDM_SENDSTRING,0,sz)
#define MCIWndReturnString(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_RETURNSTRING,len,lp)
#define MCIWndGetError(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_GETERROR,len,lp)
#define MCIWndActivate(hwnd,f)     MCIWndSM(hwnd,WM_ACTIVATE,f,0)
#define MCIWndGetPalette(hwnd)      MCIWndSM(hwnd,MCIWNDM_GETPALETTE,0,0)
#define MCIWndSetPalette(hwnd,hpal) MCIWndSM(hwnd,MCIWNDM_SETPALETTE,hpal,0)
#define MCIWndGetFileName(hwnd,lp,len) MCIWndSM(hwnd,MCIWNDM_GETFILENAME,len,lp)
#define MCIWndGetDevice(hwnd,lp,len)   MCIWndSM(hwnd,MCIWNDM_GETDEVICE,len,lp)
#define MCIWndGetStyles(hwnd) MCIWndSM(hwnd,MCIWNDM_GETSTYLES,0,0)
#define MCIWndChangeStyles(hwnd,mask,value) MCIWndSM(hwnd,MCIWNDM_CHANGESTYLES,mask,value)
#define MCIWndOpenInterface(hwnd,pUnk)  MCIWndSM(hwnd,MCIWNDM_OPENINTERFACE,0,pUnk)
#define MCIWndSetOwner(hwnd,hwndP)  MCIWndSM(hwnd,MCIWNDM_SETOWNER,hwndP,0)

// Messages an app will send to MCIWND
// all the text-related messages are defined out of order above (they need
// to be defined before the MCIWndOpen() macros
#define MCIWNDM_GETDEVICEID	WM_USER + 100
#define MCIWNDM_GETSTART	WM_USER + 103
#define MCIWNDM_GETLENGTH	WM_USER + 104
#define MCIWNDM_GETEND		WM_USER + 105
#define MCIWNDM_EJECT		WM_USER + 107
#define MCIWNDM_SETZOOM		WM_USER + 108
#define MCIWNDM_GETZOOM         WM_USER + 109
#define MCIWNDM_SETVOLUME	WM_USER + 110
#define MCIWNDM_GETVOLUME	WM_USER + 111
#define MCIWNDM_SETSPEED	WM_USER + 112
#define MCIWNDM_GETSPEED	WM_USER + 113
#define MCIWNDM_SETREPEAT	WM_USER + 114
#define MCIWNDM_GETREPEAT	WM_USER + 115
#define MCIWNDM_REALIZE         WM_USER + 118
#define MCIWNDM_VALIDATEMEDIA   WM_USER + 121
#define MCIWNDM_PLAYFROM	WM_USER + 122
#define MCIWNDM_PLAYTO          WM_USER + 123
#define MCIWNDM_GETPALETTE      WM_USER + 126
#define MCIWNDM_SETPALETTE      WM_USER + 127
#define MCIWNDM_SETTIMERS	WM_USER + 129
#define MCIWNDM_SETACTIVETIMER	WM_USER + 130
#define MCIWNDM_SETINACTIVETIMER WM_USER + 131
#define MCIWNDM_GETACTIVETIMER	WM_USER + 132
#define MCIWNDM_GETINACTIVETIMER WM_USER + 133
#define MCIWNDM_CHANGESTYLES	WM_USER + 135
#define MCIWNDM_GETSTYLES	WM_USER + 136
#define MCIWNDM_GETALIAS	WM_USER + 137
#define MCIWNDM_PLAYREVERSE	WM_USER + 139
#define MCIWNDM_GET_SOURCE      WM_USER + 140
#define MCIWNDM_PUT_SOURCE      WM_USER + 141
#define MCIWNDM_GET_DEST        WM_USER + 142
#define MCIWNDM_PUT_DEST        WM_USER + 143
#define MCIWNDM_CAN_PLAY        WM_USER + 144
#define MCIWNDM_CAN_WINDOW      WM_USER + 145
#define MCIWNDM_CAN_RECORD      WM_USER + 146
#define MCIWNDM_CAN_SAVE        WM_USER + 147
#define MCIWNDM_CAN_EJECT       WM_USER + 148
#define MCIWNDM_CAN_CONFIG      WM_USER + 149
#define MCIWNDM_PALETTEKICK     WM_USER + 150
#define MCIWNDM_OPENINTERFACE	WM_USER + 151
#define MCIWNDM_SETOWNER	WM_USER + 152

//define both A and W messages
#define MCIWNDM_SENDSTRINGA	WM_USER + 101
#define MCIWNDM_GETPOSITIONA	WM_USER + 102
#define MCIWNDM_GETMODEA	WM_USER + 106
#define MCIWNDM_SETTIMEFORMATA  WM_USER + 119
#define MCIWNDM_GETTIMEFORMATA  WM_USER + 120
#define MCIWNDM_GETFILENAMEA    WM_USER + 124
#define MCIWNDM_GETDEVICEA      WM_USER + 125
#define MCIWNDM_GETERRORA       WM_USER + 128
#define MCIWNDM_NEWA		WM_USER + 134
#define MCIWNDM_RETURNSTRINGA	WM_USER + 138
#define MCIWNDM_OPENA		WM_USER + 153
#define MCIWNDM_SENDSTRINGW	WM_USER + 201
#define MCIWNDM_GETPOSITIONW	WM_USER + 202
#define MCIWNDM_GETMODEW	WM_USER + 206
#define MCIWNDM_SETTIMEFORMATW  WM_USER + 219
#define MCIWNDM_GETTIMEFORMATW  WM_USER + 220
#define MCIWNDM_GETFILENAMEW    WM_USER + 224
#define MCIWNDM_GETDEVICEW      WM_USER + 225
#define MCIWNDM_GETERRORW       WM_USER + 228
#define MCIWNDM_NEWW		WM_USER + 234
#define MCIWNDM_RETURNSTRINGW	WM_USER + 238
#define MCIWNDM_OPENW		WM_USER + 252

// map defaults to A or W depending on app's UNICODE setting
#ifdef UNICODE
#define MCIWNDM_SENDSTRING      MCIWNDM_SENDSTRINGW
#define MCIWNDM_GETPOSITION     MCIWNDM_GETPOSITIONW
#define MCIWNDM_GETMODE         MCIWNDM_GETMODEW
#define MCIWNDM_SETTIMEFORMAT   MCIWNDM_SETTIMEFORMATW
#define MCIWNDM_GETTIMEFORMAT   MCIWNDM_GETTIMEFORMATW
#define MCIWNDM_GETFILENAME     MCIWNDM_GETFILENAMEW
#define MCIWNDM_GETDEVICE       MCIWNDM_GETDEVICEW
#define MCIWNDM_GETERROR        MCIWNDM_GETERRORW
#define MCIWNDM_NEW             MCIWNDM_NEWW
#define MCIWNDM_RETURNSTRING    MCIWNDM_RETURNSTRINGW
#define MCIWNDM_OPEN		MCIWNDM_OPENW
#else
#define MCIWNDM_SENDSTRING      MCIWNDM_SENDSTRINGA
#define MCIWNDM_GETPOSITION     MCIWNDM_GETPOSITIONA
#define MCIWNDM_GETMODE         MCIWNDM_GETMODEA
#define MCIWNDM_SETTIMEFORMAT   MCIWNDM_SETTIMEFORMATA
#define MCIWNDM_GETTIMEFORMAT   MCIWNDM_GETTIMEFORMATA
#define MCIWNDM_GETFILENAME     MCIWNDM_GETFILENAMEA
#define MCIWNDM_GETDEVICE       MCIWNDM_GETDEVICEA
#define MCIWNDM_GETERROR        MCIWNDM_GETERRORA
#define MCIWNDM_NEW             MCIWNDM_NEWA
#define MCIWNDM_RETURNSTRING    MCIWNDM_RETURNSTRINGA
#define MCIWNDM_OPEN		MCIWNDM_OPENA
#endif

// note that the source text for MCIWND will thus contain
// support for eg MCIWNDM_SENDSTRING (both the 16-bit entrypoint and
// in win32 mapped to MCIWNDM_SENDSTRINGW), and MCIWNDM_SENDSTRINGA (the
// win32 ansi thunk).

// Messages MCIWND will send to an app
// !!! Use less messages and use a code instead to indicate the type of notify? /* ;Internal */
#define MCIWNDM_NOTIFYMODE      WM_USER + 200  // wp = hwnd, lp = mode
#define MCIWNDM_NOTIFYPOS	WM_USER + 201  // wp = hwnd, lp = pos
#define MCIWNDM_NOTIFYSIZE	WM_USER + 202  // wp = hwnd
#define MCIWNDM_NOTIFYMEDIA     WM_USER + 203  // wp = hwnd, lp = fn
#define MCIWNDM_NOTIFYERROR     WM_USER + 205  // wp = hwnd, lp = error

// special seek values for START and END
#define MCIWND_START                -1
#define MCIWND_END                  -2

#ifndef MCI_PLAY
    /* MCI command message identifiers */
#ifndef _WIN32
    // win32 apps send MCIWNDM_OPEN
    #define MCI_OPEN                        0x0803
#endif
    #define MCI_CLOSE                       0x0804
    #define MCI_PLAY                        0x0806
    #define MCI_SEEK                        0x0807
    #define MCI_STOP                        0x0808
    #define MCI_PAUSE                       0x0809
    #define MCI_STEP                        0x080E
    #define MCI_RECORD                      0x080F
    #define MCI_SAVE                        0x0813
    #define MCI_CUT                         0x0851
    #define MCI_COPY                        0x0852
    #define MCI_PASTE                       0x0853
    #define MCI_RESUME                      0x0855
    #define MCI_DELETE                      0x0856
#endif

#ifndef MCI_MODE_NOT_READY
    /* return values for 'status mode' command */
    #define MCI_MODE_NOT_READY      524
    #define MCI_MODE_STOP           525
    #define MCI_MODE_PLAY           526
    #define MCI_MODE_RECORD         527
    #define MCI_MODE_SEEK           528
    #define MCI_MODE_PAUSE          529
    #define MCI_MODE_OPEN           530
#endif

#endif  /* NOAVIFILE */

/****************************************************************************
 *  VIDEO - Video Capture Driver Interface
 ****************************************************************************/
/****************************************************************************
                        version api
****************************************************************************/
extern WINAPI "msvfw32.dll"{
	DWORD VideoForWindowsVersion(void);
}

/****************************************************************************
                             Error Return Values
 ****************************************************************************/
#define DV_ERR_OK               0                  /* No error */
#define DV_ERR_BASE             1                  /* Error Base */
#define DV_ERR_NONSPECIFIC      DV_ERR_BASE
#define DV_ERR_BADFORMAT        DV_ERR_BASE + 1
				/* unsupported video format */
#define DV_ERR_STILLPLAYING     DV_ERR_BASE + 2
				/* still something playing */
#define DV_ERR_UNPREPARED       DV_ERR_BASE + 3
				/* header not prepared */
#define DV_ERR_SYNC             DV_ERR_BASE + 4
				/* device is synchronous */
#define DV_ERR_TOOMANYCHANNELS  DV_ERR_BASE + 5
				/* number of channels exceeded */
#define DV_ERR_NOTDETECTED	DV_ERR_BASE + 6    /* HW not detected */
#define DV_ERR_BADINSTALL	DV_ERR_BASE + 7    /* Can not get Profile */
#define DV_ERR_CREATEPALETTE	DV_ERR_BASE + 8
#define DV_ERR_SIZEFIELD	DV_ERR_BASE + 9
#define DV_ERR_PARAM1		DV_ERR_BASE + 10
#define DV_ERR_PARAM2		DV_ERR_BASE + 11
#define DV_ERR_CONFIG1		DV_ERR_BASE + 12
#define DV_ERR_CONFIG2		DV_ERR_BASE + 13
#define DV_ERR_FLAGS		DV_ERR_BASE + 14
#define DV_ERR_13		DV_ERR_BASE + 15
#define DV_ERR_NOTSUPPORTED     DV_ERR_BASE + 16   /* function not suported */
#define DV_ERR_NOMEM            DV_ERR_BASE + 17   /* out of memory */
#define DV_ERR_ALLOCATED        DV_ERR_BASE + 18   /* device is allocated */
#define DV_ERR_BADDEVICEID      DV_ERR_BASE + 19
#define DV_ERR_INVALHANDLE      DV_ERR_BASE + 20
#define DV_ERR_BADERRNUM        DV_ERR_BASE + 21
#define DV_ERR_NO_BUFFERS       DV_ERR_BASE + 22   /* out of buffers */
#define DV_ERR_MEM_CONFLICT     DV_ERR_BASE + 23   /* Mem conflict detected */
#define DV_ERR_IO_CONFLICT      DV_ERR_BASE + 24   /* I/O conflict detected */
#define DV_ERR_DMA_CONFLICT     DV_ERR_BASE + 25   /* DMA conflict detected */
#define DV_ERR_INT_CONFLICT     DV_ERR_BASE + 26   /* Interrupt conflict detected */
#define DV_ERR_PROTECT_ONLY     DV_ERR_BASE + 27   /* Can not run in standard mode */
#define DV_ERR_LASTERROR        DV_ERR_BASE + 27
#define DV_IDS_PROFILING        DV_ERR_BASE + 900
#define DV_IDS_LISTBOX          DV_ERR_BASE + 901
#define DV_ERR_USER_MSG         DV_ERR_BASE + 1000 /* Hardware specific errors */

/****************************************************************************
                         Callback Messages
Note that the values for all installable driver callback messages are
identical, (ie. MM_DRVM_DATA has the same value for capture drivers,
installable video codecs, and the audio compression manager).
****************************************************************************/
#ifndef _RCINVOKED
#ifndef MM_DRVM_OPEN
#define MM_DRVM_OPEN       0x3D0
#define MM_DRVM_CLOSE      0x3D1
#define MM_DRVM_DATA       0x3D2
#define MM_DRVM_ERROR      0x3D3
#endif
#define DV_VM_OPEN         MM_DRVM_OPEN         // Obsolete messages
#define DV_VM_CLOSE        MM_DRVM_CLOSE
#define DV_VM_DATA         MM_DRVM_DATA
#define DV_VM_ERROR        MM_DRVM_ERROR

/****************************************************************************
                         Structures
****************************************************************************/
/* video data block header */
struct VIDEOHDR{
  LPBYTE      lpData;                 /* pointer to locked data buffer */
  DWORD       dwBufferLength;         /* Length of data buffer */
  DWORD       dwBytesUsed;            /* Bytes actually used */
  DWORD       dwTimeCaptured;         /* Milliseconds from start of stream */
  DWORD_PTR   dwUser;                 /* for client's use */
  DWORD       dwFlags;                /* assorted flags (see defines) */
  DWORD_PTR   dwReserved[4];          /* reserved for driver */
};

/* dwFlags field of VIDEOHDR */
#define VHDR_DONE       0x00000001  /* Done bit */
#define VHDR_PREPARED   0x00000002  /* Set if this header has been prepared */
#define VHDR_INQUEUE    0x00000004  /* Reserved for driver */
#define VHDR_KEYFRAME   0x00000008  /* Key Frame */
#define VHDR_VALID      0x0000000F  /* valid flags */     /* ;Internal */

/* Channel capabilities structure */
struct CHANNEL_CAPS{
  DWORD       dwFlags;                /* Capability flags*/
  DWORD       dwSrcRectXMod;          /* Granularity of src rect in x */
  DWORD       dwSrcRectYMod;          /* Granularity of src rect in y */
  DWORD       dwSrcRectWidthMod;      /* Granularity of src rect width */
  DWORD       dwSrcRectHeightMod;     /* Granularity of src rect height */
  DWORD       dwDstRectXMod;          /* Granularity of dst rect in x */
  DWORD       dwDstRectYMod;          /* Granularity of dst rect in y */
  DWORD       dwDstRectWidthMod;      /* Granularity of dst rect width */
  DWORD       dwDstRectHeightMod;     /* Granularity of dst rect height */
};

/* dwFlags of CHANNEL_CAPS */
#define VCAPS_OVERLAY       0x00000001      /* overlay channel */
#define VCAPS_SRC_CAN_CLIP  0x00000002      /* src rect can clip */
#define VCAPS_DST_CAN_CLIP  0x00000004      /* dst rect can clip */
#define VCAPS_CAN_SCALE     0x00000008      /* allows src != dst */

/****************************************************************************
			API Flags
****************************************************************************/
// Types of channels to open with the videoOpen function
#define VIDEO_EXTERNALIN		0x0001
#define VIDEO_EXTERNALOUT		0x0002
#define VIDEO_IN			0x0004
#define VIDEO_OUT			0x0008
// Is a driver dialog available for this channel?
#define VIDEO_DLG_QUERY			0x0010
// videoConfigure (both GET and SET)
#define VIDEO_CONFIGURE_QUERY   	0x8000
// videoConfigure (SET only)
#define VIDEO_CONFIGURE_SET		0x1000
// videoConfigure (GET only)
#define VIDEO_CONFIGURE_GET		0x2000
#define VIDEO_CONFIGURE_QUERYSIZE	0x0001
#define VIDEO_CONFIGURE_CURRENT		0x0010
#define VIDEO_CONFIGURE_NOMINAL		0x0020
#define VIDEO_CONFIGURE_MIN		0x0040
#define VIDEO_CONFIGURE_MAX		0x0080

/****************************************************************************
			CONFIGURE MESSAGES
****************************************************************************/
#define DVM_USER                        0X4000
#define DVM_CONFIGURE_START		0x1000
#define DVM_CONFIGURE_END		0x1FFF
#define DVM_PALETTE			DVM_CONFIGURE_START + 1
#define DVM_FORMAT			DVM_CONFIGURE_START + 2
#define DVM_PALETTERGB555		DVM_CONFIGURE_START + 3
#define DVM_SRC_RECT    		DVM_CONFIGURE_START + 4
#define DVM_DST_RECT    		DVM_CONFIGURE_START + 5
#endif  /* ifndef _RCINVOKED */
#endif  /* NOVIDEO */

/****************************************************************************
 *  AVICAP - Window class for AVI capture
 ***************************************************************************/
#ifndef NOAVICAP
:dword AVICapSM(dword hwnd,m,w,l)
{
	IF(IsWindow(hwnd))SendMessage(hwnd,m,w,l)
	ELSE EAX=0;
}
#ifndef RC_INVOKED

// ------------------------------------------------------------------
//  Window Messages  WM_CAP... which can be sent to an AVICAP window
// ------------------------------------------------------------------
// UNICODE
// The Win32 version of AVICAP on NT supports UNICODE applications:
// for each API or message that takes a char or string parameter, there are
// two versions, ApiNameA and ApiNameW. The default name ApiName is #defined
// to one or other depending on whether UNICODE is defined. Apps can call
// the A and W apis directly, and mix them.
// The 32-bit AVICAP on NT uses unicode exclusively internally.
// ApiNameA() will be implemented as a call to ApiNameW() together with
// translation of strings.

// Defines start of the message range
#define WM_CAP_START                    WM_USER

// start of unicode messages
#define WM_CAP_UNICODE_START            WM_USER+100

#define WM_CAP_GET_CAPSTREAMPTR         WM_CAP_START+  1

#define WM_CAP_SET_CALLBACK_ERRORW     WM_CAP_UNICODE_START+  2
#define WM_CAP_SET_CALLBACK_STATUSW    WM_CAP_UNICODE_START+  3
#define WM_CAP_SET_CALLBACK_ERRORA     WM_CAP_START+  2
#define WM_CAP_SET_CALLBACK_STATUSA    WM_CAP_START+  3
#ifdef UNICODE
#define WM_CAP_SET_CALLBACK_ERROR      WM_CAP_SET_CALLBACK_ERRORW
#define WM_CAP_SET_CALLBACK_STATUS     WM_CAP_SET_CALLBACK_STATUSW
#else
#define WM_CAP_SET_CALLBACK_ERROR      WM_CAP_SET_CALLBACK_ERRORA
#define WM_CAP_SET_CALLBACK_STATUS     WM_CAP_SET_CALLBACK_STATUSA
#endif

#define WM_CAP_SET_CALLBACK_YIELD       WM_CAP_START+  4
#define WM_CAP_SET_CALLBACK_FRAME       WM_CAP_START+  5
#define WM_CAP_SET_CALLBACK_VIDEOSTREAM WM_CAP_START+  6
#define WM_CAP_SET_CALLBACK_WAVESTREAM  WM_CAP_START+  7
#define WM_CAP_GET_USER_DATA		WM_CAP_START+  8
#define WM_CAP_SET_USER_DATA		WM_CAP_START+  9
#define WM_CAP_DRIVER_CONNECT           WM_CAP_START+  10
#define WM_CAP_DRIVER_DISCONNECT        WM_CAP_START+  11
#define WM_CAP_DRIVER_GET_NAMEA        WM_CAP_START+  12
#define WM_CAP_DRIVER_GET_VERSIONA     WM_CAP_START+  13
#define WM_CAP_DRIVER_GET_NAMEW        WM_CAP_UNICODE_START+  12
#define WM_CAP_DRIVER_GET_VERSIONW     WM_CAP_UNICODE_START+  13
#ifdef UNICODE
#define WM_CAP_DRIVER_GET_NAME          WM_CAP_DRIVER_GET_NAMEW
#define WM_CAP_DRIVER_GET_VERSION       WM_CAP_DRIVER_GET_VERSIONW
#else
#define WM_CAP_DRIVER_GET_NAME          WM_CAP_DRIVER_GET_NAMEA
#define WM_CAP_DRIVER_GET_VERSION       WM_CAP_DRIVER_GET_VERSIONA
#endif

#define WM_CAP_DRIVER_GET_CAPS          WM_CAP_START+  14
#define WM_CAP_FILE_SET_CAPTURE_FILEA  WM_CAP_START+  20
#define WM_CAP_FILE_GET_CAPTURE_FILEA  WM_CAP_START+  21
#define WM_CAP_FILE_SAVEASA            WM_CAP_START+  23
#define WM_CAP_FILE_SAVEDIBA           WM_CAP_START+  25
#define WM_CAP_FILE_SET_CAPTURE_FILEW  WM_CAP_UNICODE_START+  20
#define WM_CAP_FILE_GET_CAPTURE_FILEW  WM_CAP_UNICODE_START+  21
#define WM_CAP_FILE_SAVEASW            WM_CAP_UNICODE_START+  23
#define WM_CAP_FILE_SAVEDIBW           WM_CAP_UNICODE_START+  25
#ifdef UNICODE
#define WM_CAP_FILE_SET_CAPTURE_FILE    WM_CAP_FILE_SET_CAPTURE_FILEW
#define WM_CAP_FILE_GET_CAPTURE_FILE    WM_CAP_FILE_GET_CAPTURE_FILEW
#define WM_CAP_FILE_SAVEAS              WM_CAP_FILE_SAVEASW
#define WM_CAP_FILE_SAVEDIB             WM_CAP_FILE_SAVEDIBW
#else
#define WM_CAP_FILE_SET_CAPTURE_FILE    WM_CAP_FILE_SET_CAPTURE_FILEA
#define WM_CAP_FILE_GET_CAPTURE_FILE    WM_CAP_FILE_GET_CAPTURE_FILEA
#define WM_CAP_FILE_SAVEAS              WM_CAP_FILE_SAVEASA
#define WM_CAP_FILE_SAVEDIB             WM_CAP_FILE_SAVEDIBA
#endif

// out of order to save on ifdefs
#define WM_CAP_FILE_ALLOCATE            WM_CAP_START+  22
#define WM_CAP_FILE_SET_INFOCHUNK       WM_CAP_START+  24
#define WM_CAP_EDIT_COPY                WM_CAP_START+  30
#define WM_CAP_SET_AUDIOFORMAT          WM_CAP_START+  35
#define WM_CAP_GET_AUDIOFORMAT          WM_CAP_START+  36
#define WM_CAP_DLG_VIDEOFORMAT          WM_CAP_START+  41
#define WM_CAP_DLG_VIDEOSOURCE          WM_CAP_START+  42
#define WM_CAP_DLG_VIDEODISPLAY         WM_CAP_START+  43
#define WM_CAP_GET_VIDEOFORMAT          WM_CAP_START+  44
#define WM_CAP_SET_VIDEOFORMAT          WM_CAP_START+  45
#define WM_CAP_DLG_VIDEOCOMPRESSION     WM_CAP_START+  46
#define WM_CAP_SET_PREVIEW              WM_CAP_START+  50
#define WM_CAP_SET_OVERLAY              WM_CAP_START+  51
#define WM_CAP_SET_PREVIEWRATE          WM_CAP_START+  52
#define WM_CAP_SET_SCALE                WM_CAP_START+  53
#define WM_CAP_GET_STATUS               WM_CAP_START+  54
#define WM_CAP_SET_SCROLL               WM_CAP_START+  55
#define WM_CAP_GRAB_FRAME               WM_CAP_START+  60
#define WM_CAP_GRAB_FRAME_NOSTOP        WM_CAP_START+  61
#define WM_CAP_SEQUENCE                 WM_CAP_START+  62
#define WM_CAP_SEQUENCE_NOFILE          WM_CAP_START+  63
#define WM_CAP_SET_SEQUENCE_SETUP       WM_CAP_START+  64
#define WM_CAP_GET_SEQUENCE_SETUP       WM_CAP_START+  65
#define WM_CAP_SET_MCI_DEVICEA         WM_CAP_START+  66
#define WM_CAP_GET_MCI_DEVICEA         WM_CAP_START+  67
#define WM_CAP_SET_MCI_DEVICEW         WM_CAP_UNICODE_START+  66
#define WM_CAP_GET_MCI_DEVICEW         WM_CAP_UNICODE_START+  67
#ifdef UNICODE
#define WM_CAP_SET_MCI_DEVICE           WM_CAP_SET_MCI_DEVICEW
#define WM_CAP_GET_MCI_DEVICE           WM_CAP_GET_MCI_DEVICEW
#else
#define WM_CAP_SET_MCI_DEVICE           WM_CAP_SET_MCI_DEVICEA
#define WM_CAP_GET_MCI_DEVICE           WM_CAP_GET_MCI_DEVICEA
#endif

#define WM_CAP_STOP                     WM_CAP_START+  68
#define WM_CAP_ABORT                    WM_CAP_START+  69
#define WM_CAP_SINGLE_FRAME_OPEN        WM_CAP_START+  70
#define WM_CAP_SINGLE_FRAME_CLOSE       WM_CAP_START+  71
#define WM_CAP_SINGLE_FRAME             WM_CAP_START+  72
#define WM_CAP_PAL_OPENA               WM_CAP_START+  80
#define WM_CAP_PAL_SAVEA               WM_CAP_START+  81
#define WM_CAP_PAL_OPENW               WM_CAP_UNICODE_START+  80
#define WM_CAP_PAL_SAVEW               WM_CAP_UNICODE_START+  81
#ifdef UNICODE
#define WM_CAP_PAL_OPEN                 WM_CAP_PAL_OPENW
#define WM_CAP_PAL_SAVE                 WM_CAP_PAL_SAVEW
#else
#define WM_CAP_PAL_OPEN                 WM_CAP_PAL_OPENA
#define WM_CAP_PAL_SAVE                 WM_CAP_PAL_SAVEA
#endif

#define WM_CAP_PAL_PASTE                WM_CAP_START+  82
#define WM_CAP_PAL_AUTOCREATE           WM_CAP_START+  83
#define WM_CAP_PAL_MANUALCREATE         WM_CAP_START+  84
// Following added post VFW 1.1
#define WM_CAP_SET_CALLBACK_CAPCONTROL  WM_CAP_START+  85
// Defines end of the message range
#define WM_CAP_UNICODE_END              WM_CAP_PAL_SAVEW
#define WM_CAP_END                      WM_CAP_UNICODE_END

// ------------------------------------------------------------------
//  Message crackers for above
// ------------------------------------------------------------------
// message wrapper macros are defined for the default messages only. Apps
// that wish to mix Ansi and UNICODE message sending will have to
// reference the _A and _W messages directly
#define capSetCallbackOnError(hwnd,fpProc)       AVICapSM(hwnd,WM_CAP_SET_CALLBACK_ERROR,0,fpProc)
#define capSetCallbackOnStatus(hwnd,fpProc)      AVICapSM(hwnd,WM_CAP_SET_CALLBACK_STATUS,0,fpProc)
#define capSetCallbackOnYield(hwnd,fpProc)       AVICapSM(hwnd,WM_CAP_SET_CALLBACK_YIELD,0,fpProc)
#define capSetCallbackOnFrame(hwnd,fpProc)       AVICapSM(hwnd,WM_CAP_SET_CALLBACK_FRAME,0,fpProc)
#define capSetCallbackOnVideoStream(hwnd,fpProc) AVICapSM(hwnd,WM_CAP_SET_CALLBACK_VIDEOSTREAM,0,fpProc)
#define capSetCallbackOnWaveStream(hwnd,fpProc)  AVICapSM(hwnd,WM_CAP_SET_CALLBACK_WAVESTREAM,0,fpProc)
#define capSetCallbackOnCapControl(hwnd,fpProc)  AVICapSM(hwnd,WM_CAP_SET_CALLBACK_CAPCONTROL,0,fpProc)
#define capSetUserData(hwnd,lUser)        AVICapSM(hwnd,WM_CAP_SET_USER_DATA,0,lUser)
#define capGetUserData(hwnd)               AVICapSM(hwnd,WM_CAP_GET_USER_DATA,0,0)
#define capDriverConnect(hwnd,i)                  AVICapSM(hwnd,WM_CAP_DRIVER_CONNECT,i,0)
#define capDriverDisconnect(hwnd)                  AVICapSM(hwnd,WM_CAP_DRIVER_DISCONNECT,0,0)
#define capDriverGetName(hwnd,szName,wSize)      AVICapSM(hwnd,WM_CAP_DRIVER_GET_NAME,wSize,szName)
#define capDriverGetVersion(hwnd,szVer,wSize)    AVICapSM(hwnd,WM_CAP_DRIVER_GET_VERSION,wSize,szVer)
#define capDriverGetCaps(hwnd,s,wSize)           AVICapSM(hwnd,WM_CAP_DRIVER_GET_CAPS,wSize,s)
#define capFileSetCaptureFile(hwnd,szName)        AVICapSM(hwnd,WM_CAP_FILE_SET_CAPTURE_FILE,0,szName)
#define capFileGetCaptureFile(hwnd,szName,wSize) AVICapSM(hwnd,WM_CAP_FILE_GET_CAPTURE_FILE,wSize,szName)
#define capFileAlloc(hwnd,dwSize)                 AVICapSM(hwnd,WM_CAP_FILE_ALLOCATE,0,dwSize)
#define capFileSaveAs(hwnd,szName)                AVICapSM(hwnd,WM_CAP_FILE_SAVEAS,0,szName)
#define capFileSetInfoChunk(hwnd,lpInfoChunk)     AVICapSM(hwnd,WM_CAP_FILE_SET_INFOCHUNK,0,lpInfoChunk)
#define capFileSaveDIB(hwnd,szName)               AVICapSM(hwnd,WM_CAP_FILE_SAVEDIB,0,szName)
#define capEditCopy(hwnd)                          AVICapSM(hwnd,WM_CAP_EDIT_COPY,0,0)
#define capSetAudioFormat(hwnd,s,wSize)          AVICapSM(hwnd,WM_CAP_SET_AUDIOFORMAT,wSize,s)
#define capGetAudioFormat(hwnd,s,wSize)          AVICapSM(hwnd,WM_CAP_GET_AUDIOFORMAT,wSize,s)
#define capGetAudioFormatSize(hwnd)              AVICapSM(hwnd,WM_CAP_GET_AUDIOFORMAT,0,0)
#define capDlgVideoFormat(hwnd)                    AVICapSM(hwnd,WM_CAP_DLG_VIDEOFORMAT,0,0)
#define capDlgVideoSource(hwnd)                    AVICapSM(hwnd,WM_CAP_DLG_VIDEOSOURCE,0,0)
#define capDlgVideoDisplay(hwnd)                   AVICapSM(hwnd,WM_CAP_DLG_VIDEODISPLAY,0,0)
#define capDlgVideoCompression(hwnd)               AVICapSM(hwnd,WM_CAP_DLG_VIDEOCOMPRESSION,0,0)
#define capGetVideoFormat(hwnd,s,wSize)        AVICapSM(hwnd,WM_CAP_GET_VIDEOFORMAT,wSize,s)
#define capGetVideoFormatSize(hwnd)            AVICapSM(hwnd,WM_CAP_GET_VIDEOFORMAT,0,0)
#define capSetVideoFormat(hwnd,s,wSize)        AVICapSM(hwnd,WM_CAP_SET_VIDEOFORMAT,wSize,s)
#define capPreview(hwnd,f)                       AVICapSM(hwnd,WM_CAP_SET_PREVIEW,f,0)
#define capPreviewRate(hwnd,wMS)                 AVICapSM(hwnd,WM_CAP_SET_PREVIEWRATE,wMS,0)
#define capOverlay(hwnd,f)                       AVICapSM(hwnd,WM_CAP_SET_OVERLAY,f,0)
#define capPreviewScale(hwnd,f)                  AVICapSM(hwnd,WM_CAP_SET_SCALE,f,0)
#define capGetStatus(hwnd,s,wSize)               AVICapSM(hwnd,WM_CAP_GET_STATUS,wSize,s)
#define capSetScrollPos(hwnd,lpP)                AVICapSM(hwnd,WM_CAP_SET_SCROLL,0,lpP)
#define capGrabFrame(hwnd)                         AVICapSM(hwnd,WM_CAP_GRAB_FRAME,0,0)
#define capGrabFrameNoStop(hwnd)                   AVICapSM(hwnd,WM_CAP_GRAB_FRAME_NOSTOP,0,0)
#define capCaptureSequence(hwnd)                   AVICapSM(hwnd,WM_CAP_SEQUENCE,0,0)
#define capCaptureSequenceNoFile(hwnd)             AVICapSM(hwnd,WM_CAP_SEQUENCE_NOFILE,0,0)
#define capCaptureStop(hwnd)                       AVICapSM(hwnd,WM_CAP_STOP,0,0)
#define capCaptureAbort(hwnd)                      AVICapSM(hwnd,WM_CAP_ABORT,0,0)
#define capCaptureSingleFrameOpen(hwnd)            AVICapSM(hwnd,WM_CAP_SINGLE_FRAME_OPEN,0,0)
#define capCaptureSingleFrameClose(hwnd)           AVICapSM(hwnd,WM_CAP_SINGLE_FRAME_CLOSE,0,0)
#define capCaptureSingleFrame(hwnd)                AVICapSM(hwnd,WM_CAP_SINGLE_FRAME,0,0)
#define capCaptureGetSetup(hwnd,s,wSize)         AVICapSM(hwnd,WM_CAP_GET_SEQUENCE_SETUP,wSize,s)
#define capCaptureSetSetup(hwnd,s,wSize)         AVICapSM(hwnd,WM_CAP_SET_SEQUENCE_SETUP,wSize,s)
#define capSetMCIDeviceName(hwnd,szName)          AVICapSM(hwnd,WM_CAP_SET_MCI_DEVICE,0,szName)
#define capGetMCIDeviceName(hwnd,szName,wSize)   AVICapSM(hwnd,WM_CAP_GET_MCI_DEVICE,wSize,szName)
#define capPaletteOpen(hwnd,szName)               AVICapSM(hwnd,WM_CAP_PAL_OPEN,0,szName)
#define capPaletteSave(hwnd,szName)               AVICapSM(hwnd,WM_CAP_PAL_SAVE,0,szName)
#define capPalettePaste(hwnd)                      AVICapSM(hwnd,WM_CAP_PAL_PASTE,0,0)
#define capPaletteAuto(hwnd,iFrames,iColors)     AVICapSM(hwnd,WM_CAP_PAL_AUTOCREATE,iFrames,iColors)
#define capPaletteManual(hwnd,fGrab,iColors)     AVICapSM(hwnd,WM_CAP_PAL_MANUALCREATE,fGrab,iColors)

// ------------------------------------------------------------------
//  Structures
// ------------------------------------------------------------------
struct CAPDRIVERCAPS {
  UINT        wDeviceIndex;               // Driver index in system.ini
  BOOL        fHasOverlay;                // Can device overlay?
  BOOL        fHasDlgVideoSource;         // Has Video source dlg?
  BOOL        fHasDlgVideoFormat;         // Has Format dlg?
  BOOL        fHasDlgVideoDisplay;        // Has External out dlg?
  BOOL        fCaptureInitialized;        // Driver ready to capture?
  BOOL        fDriverSuppliesPalettes;    // Can driver make palettes?
// following always NULL on Win32.
  HANDLE      hVideoIn;                   // Driver In channel
  HANDLE      hVideoOut;                  // Driver Out channel
  HANDLE      hVideoExtIn;                // Driver Ext In channel
  HANDLE      hVideoExtOut;               // Driver Ext Out channel
};

struct CAPSTATUS{
  UINT        uiImageWidth;               // Width of the image
  UINT        uiImageHeight;              // Height of the image
  BOOL        fLiveWindow;                // Now Previewing video?
  BOOL        fOverlayWindow;             // Now Overlaying video?
  BOOL        fScale;                     // Scale image to client?
  POINT       ptScroll;                   // Scroll position
  BOOL        fUsingDefaultPalette;       // Using default driver palette?
  BOOL        fAudioHardware;             // Audio hardware present?
  BOOL        fCapFileExists;             // Does capture file exist?
  DWORD       dwCurrentVideoFrame;        // # of video frames cap'td
  DWORD       dwCurrentVideoFramesDropped;// # of video frames dropped
  DWORD       dwCurrentWaveSamples;       // # of wave samples cap'td
  DWORD       dwCurrentTimeElapsedMS;     // Elapsed capture duration
  HPALETTE    hPalCurrent;                // Current palette in use
  BOOL        fCapturingNow;              // Capture in progress?
  DWORD       dwReturn;                   // Error value after any operation
  UINT        wNumVideoAllocated;         // Actual number of video buffers
  UINT        wNumAudioAllocated;         // Actual number of audio buffers
};
                                            // Default values in parenthesis
struct CAPTUREPARMS{
  DWORD       dwRequestMicroSecPerFrame;  // Requested capture rate
  BOOL        fMakeUserHitOKToCapture;    // Show "Hit OK to cap" dlg?
  UINT        wPercentDropForError;       // Give error msg if > (10%)
  BOOL        fYield;                     // Capture via background task?
  DWORD       dwIndexSize;                // Max index size in frames (32K)
  UINT        wChunkGranularity;          // Junk chunk granularity (2K)
  BOOL        fUsingDOSMemory;            // Use DOS buffers?
  UINT        wNumVideoRequested;         // # video buffers, If 0, autocalc
  BOOL        fCaptureAudio;              // Capture audio?
  UINT        wNumAudioRequested;         // # audio buffers, If 0, autocalc
  UINT        vKeyAbort;                  // Virtual key causing abort
  BOOL        fAbortLeftMouse;            // Abort on left mouse?
  BOOL        fAbortRightMouse;           // Abort on right mouse?
  BOOL        fLimitEnabled;              // Use wTimeLimit?
  UINT        wTimeLimit;                 // Seconds to capture
  BOOL        fMCIControl;                // Use MCI video source?
  BOOL        fStepMCIDevice;             // Step MCI device?
  DWORD       dwMCIStartTime;             // Time to start in MS
  DWORD       dwMCIStopTime;              // Time to stop in MS
  BOOL        fStepCaptureAt2x;           // Perform spatial averaging 2x
  UINT        wStepCaptureAverageFrames;  // Temporal average n Frames
  DWORD       dwAudioBufferSize;          // Size of audio bufs (0 = default)
  BOOL        fDisableWriteCache;         // Attempt to disable write cache
  UINT        AVStreamMaster;             // Which stream controls length?
};

// ------------------------------------------------------------------
//  AVStreamMaster
//  Since Audio and Video streams generally use non-synchronized capture
//  clocks, this flag determines whether the audio stream is to be considered
//  the master or controlling clock when writing the AVI file:
//  AVSTREAMMASTER_AUDIO  - Audio is master, video frame duration is forced
//                          to match audio duration (VFW 1.0, 1.1 default)
//  AVSTREAMMASTER_NONE   - No master, audio and video streams may be of
//                          different lengths
// ------------------------------------------------------------------
#define AVSTREAMMASTER_AUDIO            0 /* Audio master (VFW 1.0, 1.1) */
#define AVSTREAMMASTER_NONE             1 /* No master */

struct CAPINFOCHUNK {
  FOURCC      fccInfoID;                  // Chunk ID, "ICOP" for copyright
  LPVOID      lpData;                     // pointer to data
  LONG        cbData;                     // size of lpData
};

// ------------------------------------------------------------------
//  CapControlCallback states
// ------------------------------------------------------------------
#define CONTROLCALLBACK_PREROLL         1 /* Waiting to start capture */
#define CONTROLCALLBACK_CAPTURING       2 /* Now capturing */

// ------------------------------------------------------------------
//  The only exported functions from AVICAP.DLL
// ------------------------------------------------------------------
extern WINAPI "avicap32.dll"{
	HWND capCreateCaptureWindowA(LPCSTR lpszWindowName,DWORD dwStyle,int x,
		int y,int nWidth,int nHeight,HWND hwndParent,int nID);
	BOOL capGetDriverDescriptionA(UINT wDriverIndex,LPSTR lpszName,int cbName,
		LPSTR lpszVer,int cbVer);
	HWND capCreateCaptureWindowW(LPCWSTR lpszWindowName,DWORD dwStyle,int x,
		int y,int nWidth,int nHeight,HWND hwndParent,int nID);
	BOOL capGetDriverDescriptionW(UINT wDriverIndex,LPWSTR lpszName,int cbName,
		LPWSTR lpszVer,int cbVer);
}
#ifdef UNICODE
#define capCreateCaptureWindow  capCreateCaptureWindowW
#define capGetDriverDescription capGetDriverDescriptionW
#else
#define capCreateCaptureWindow  capCreateCaptureWindowA
#define capGetDriverDescription capGetDriverDescriptionA
#endif

#endif  /* RC_INVOKED */

// ------------------------------------------------------------------
// New Information chunk IDs
// ------------------------------------------------------------------
#define infotypeDIGITIZATION_TIME  'IDIT'
#define infotypeSMPTE_TIME         'ISMP'

// ------------------------------------------------------------------
// String IDs from status and error callbacks
// ------------------------------------------------------------------
#define IDS_CAP_BEGIN               300  /* "Capture Start" */
#define IDS_CAP_END                 301  /* "Capture End" */
#define IDS_CAP_INFO                401  /* "%s" */
#define IDS_CAP_OUTOFMEM            402  /* "Out of memory" */
#define IDS_CAP_FILEEXISTS          403  /* "File '%s' exists -- overwrite it?" */
#define IDS_CAP_ERRORPALOPEN        404  /* "Error opening palette '%s'" */
#define IDS_CAP_ERRORPALSAVE        405  /* "Error saving palette '%s'" */
#define IDS_CAP_ERRORDIBSAVE        406  /* "Error saving frame '%s'" */
#define IDS_CAP_DEFAVIEXT           407  /* "avi" */
#define IDS_CAP_DEFPALEXT           408  /* "pal" */
#define IDS_CAP_CANTOPEN            409  /* "Cannot open '%s'" */
#define IDS_CAP_SEQ_MSGSTART        410  /* "Select OK to start capture\nof video sequence\nto %s." */
#define IDS_CAP_SEQ_MSGSTOP         411  /* "Hit ESCAPE or click to end capture" */
#define IDS_CAP_VIDEDITERR          412  /* "An error occurred while trying to run VidEdit." */
#define IDS_CAP_READONLYFILE        413  /* "The file '%s' is a read-only file." */
#define IDS_CAP_WRITEERROR          414  /* "Unable to write to file '%s'.\nDisk may be full." */
#define IDS_CAP_NODISKSPACE         415  /* "There is no space to create a capture file on the specified device." */
#define IDS_CAP_SETFILESIZE         416  /* "Set File Size" */
#define IDS_CAP_SAVEASPERCENT       417  /* "SaveAs: %2ld%%  Hit Escape to abort." */
#define IDS_CAP_DRIVER_ERROR        418  /* Driver specific error message */
#define IDS_CAP_WAVE_OPEN_ERROR     419  /* "Error: Cannot open the wave input device.\nCheck sample size, frequency, and channels." */
#define IDS_CAP_WAVE_ALLOC_ERROR    420  /* "Error: Out of memory for wave buffers." */
#define IDS_CAP_WAVE_PREPARE_ERROR  421  /* "Error: Cannot prepare wave buffers." */
#define IDS_CAP_WAVE_ADD_ERROR      422  /* "Error: Cannot add wave buffers." */
#define IDS_CAP_WAVE_SIZE_ERROR     423  /* "Error: Bad wave size." */
#define IDS_CAP_VIDEO_OPEN_ERROR    424  /* "Error: Cannot open the video input device." */
#define IDS_CAP_VIDEO_ALLOC_ERROR   425  /* "Error: Out of memory for video buffers." */
#define IDS_CAP_VIDEO_PREPARE_ERROR 426  /* "Error: Cannot prepare video buffers." */
#define IDS_CAP_VIDEO_ADD_ERROR     427  /* "Error: Cannot add video buffers." */
#define IDS_CAP_VIDEO_SIZE_ERROR    428  /* "Error: Bad video size." */
#define IDS_CAP_FILE_OPEN_ERROR     429  /* "Error: Cannot open capture file." */
#define IDS_CAP_FILE_WRITE_ERROR    430  /* "Error: Cannot write to capture file.  Disk may be full." */
#define IDS_CAP_RECORDING_ERROR     431  /* "Error: Cannot write to capture file.  Data rate too high or disk full." */
#define IDS_CAP_RECORDING_ERROR2    432  /* "Error while recording" */
#define IDS_CAP_AVI_INIT_ERROR      433  /* "Error: Unable to initialize for capture." */
#define IDS_CAP_NO_FRAME_CAP_ERROR  434  /* "Warning: No frames captured.\nConfirm that vertical sync interrupts\nare configured and enabled." */
#define IDS_CAP_NO_PALETTE_WARN     435  /* "Warning: Using default palette." */
#define IDS_CAP_MCI_CONTROL_ERROR   436  /* "Error: Unable to access MCI device." */
#define IDS_CAP_MCI_CANT_STEP_ERROR 437  /* "Error: Unable to step MCI device." */
#define IDS_CAP_NO_AUDIO_CAP_ERROR  438  /* "Error: No audio data captured.\nCheck audio card settings." */
#define IDS_CAP_AVI_DRAWDIB_ERROR   439  /* "Error: Unable to draw this data format." */
#define IDS_CAP_COMPRESSOR_ERROR    440  /* "Error: Unable to initialize compressor." */
#define IDS_CAP_AUDIO_DROP_ERROR    441  /* "Error: Audio data was lost during capture, reduce capture rate." */
#define IDS_CAP_AUDIO_DROP_COMPERROR 442  /* "Error: Audio data was lost during capture.  Try capturing without compressing." */

/* status string IDs */
#define IDS_CAP_STAT_LIVE_MODE      500  /* "Live window" */
#define IDS_CAP_STAT_OVERLAY_MODE   501  /* "Overlay window" */
#define IDS_CAP_STAT_CAP_INIT       502  /* "Setting up for capture - Please wait" */
#define IDS_CAP_STAT_CAP_FINI       503  /* "Finished capture, now writing frame %ld" */
#define IDS_CAP_STAT_PALETTE_BUILD  504  /* "Building palette map" */
#define IDS_CAP_STAT_OPTPAL_BUILD   505  /* "Computing optimal palette" */
#define IDS_CAP_STAT_I_FRAMES       506  /* "%d frames" */
#define IDS_CAP_STAT_L_FRAMES       507  /* "%ld frames" */
#define IDS_CAP_STAT_CAP_L_FRAMES   508  /* "Captured %ld frames" */
#define IDS_CAP_STAT_CAP_AUDIO      509  /* "Capturing audio" */
#define IDS_CAP_STAT_VIDEOCURRENT   510  /* "Captured %ld frames (%ld dropped) %d.%03d sec." */
#define IDS_CAP_STAT_VIDEOAUDIO     511  /* "Captured %d.%03d sec.  %ld frames (%ld dropped) (%d.%03d fps).  %ld audio bytes (%d,%03d sps)" */
#define IDS_CAP_STAT_VIDEOONLY      512  /* "Captured %d.%03d sec.  %ld frames (%ld dropped) (%d.%03d fps)" */
#define IDS_CAP_STAT_FRAMESDROPPED  513  /* "Dropped %ld of %ld frames (%d.%02d%%) during capture." */
#endif  /* NOAVIFILE */

/****************************************************************************
 *  ACM (Audio compression manager)
 ***************************************************************************/
/*#ifndef NOMSACM
#include <msacm.h>
#endif
	*/
/****************************************************************************
 *  FilePreview dialog.
 ***************************************************************************/
#ifdef OFN_READONLY
extern WINAPI "msvfw32.dll"{
	BOOL GetOpenFileNamePreviewA(dword lpofn);
	BOOL GetSaveFileNamePreviewA(dword lpofn);
	BOOL GetOpenFileNamePreviewW(dword lpofn);
	BOOL GetSaveFileNamePreviewW(dword lpofn);
}
#ifdef UNICODE
#define GetOpenFileNamePreview          GetOpenFileNamePreviewW
#define GetSaveFileNamePreview          GetSaveFileNamePreviewW
#else
#define GetOpenFileNamePreview          GetOpenFileNamePreviewA
#define GetSaveFileNamePreview          GetSaveFileNamePreviewA
#endif

#endif // OFN_READONLY

#ifndef RC_INVOKED
#pragma pack(pop)
#endif

#endif  /* _INC_VFW */
