/*==========================================================================;
 *  Copyright (C) 1995-1998 Microsoft Corporation.  All Rights Reserved.
 *  File:       dsound.h
 *  Content:    DirectSound include file
 **************************************************************************/

#ifndef __DSOUND_INCLUDED__
#define __DSOUND_INCLUDED__

#include <d3dtypes.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#define _FACDS  0x878
#define MAKE_DSHRESULT(code)  0x88780000|code

#ifndef DIRECTSOUND_VERSION
#define DIRECTSOUND_VERSION  0x0700       /* version 7.0 */
#endif /* !DIRECTSOUND_VERSION */

// DirectSound Component GUID {47D4D946-62E8-11cf-93BC-444553540000}
:DEFINE_GUID(CLSID_DirectSound,0x47d4d946,0x62e8,0x11cf,0x93,0xbc,0x44,0x45,0x53,0x54,0x0,0x0);

// DirectSound Capture Component GUID {B0210780-89CD-11d0-AF08-00A0C925CD16}
:DEFINE_GUID(CLSID_DirectSoundCapture,0xb0210780,0x89cd,0x11d0,0xaf,0x8,0x0,0xa0,0xc9,0x25,0xcd,0x16);

// Structures
struct DSCAPS
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwMinSecondarySampleRate;
  DWORD dwMaxSecondarySampleRate;
  DWORD dwPrimaryBuffers;
  DWORD dwMaxHwMixingAllBuffers;
  DWORD dwMaxHwMixingStaticBuffers;
  DWORD dwMaxHwMixingStreamingBuffers;
  DWORD dwFreeHwMixingAllBuffers;
  DWORD dwFreeHwMixingStaticBuffers;
  DWORD dwFreeHwMixingStreamingBuffers;
  DWORD dwMaxHw3DAllBuffers;
  DWORD dwMaxHw3DStaticBuffers;
  DWORD dwMaxHw3DStreamingBuffers;
  DWORD dwFreeHw3DAllBuffers;
  DWORD dwFreeHw3DStaticBuffers;
  DWORD dwFreeHw3DStreamingBuffers;
  DWORD dwTotalHwMemBytes;
  DWORD dwFreeHwMemBytes;
  DWORD dwMaxContigFreeHwMemBytes;
  DWORD dwUnlockTransferRateHwBuffers;
  DWORD dwPlayCpuOverheadSwBuffers;
  DWORD dwReserved1;
  DWORD dwReserved2;
};

struct DSBCAPS
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwBufferBytes;
  DWORD dwUnlockTransferRate;
  DWORD dwPlayCpuOverhead;
};

struct DSBUFFERDESC
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwBufferBytes;
  DWORD dwReserved;
  dword lpwfxFormat;
#if DIRECTSOUND_VERSION >= 0x0700
  GUID  guid3DAlgorithm;
#endif
};

struct DSBUFFERDESC1
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwBufferBytes;
  DWORD dwReserved;
  dword lpwfxFormat;
};

struct DS3DBUFFER
{
  DWORD     dwSize;
  D3DVECTOR vPosition;
  D3DVECTOR vVelocity;
  DWORD     dwInsideConeAngle;
  DWORD     dwOutsideConeAngle;
  D3DVECTOR vConeOrientation;
  LONG      lConeOutsideVolume;
  D3DVALUE  flMinDistance;
  D3DVALUE  flMaxDistance;
  DWORD     dwMode;
};

struct DS3DLISTENER
{
  DWORD     dwSize;
  D3DVECTOR vPosition;
  D3DVECTOR vVelocity;
  D3DVECTOR vOrientFront;
  D3DVECTOR vOrientTop;
  D3DVALUE  flDistanceFactor;
  D3DVALUE  flRolloffFactor;
  D3DVALUE  flDopplerFactor;
};

struct DSCCAPS
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwFormats;
  DWORD dwChannels;
};

struct DSCBUFFERDESC
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwBufferBytes;
  DWORD dwReserved;
  dword lpwfxFormat;
};

struct DSCBCAPS
{
  DWORD dwSize;
  DWORD dwFlags;
  DWORD dwBufferBytes;
  DWORD dwReserved;
};

struct DSBPOSITIONNOTIFY
{
  DWORD  dwOffset;
  HANDLE hEventNotify;
};

// DirectSound API
extern WINAPI "DSOUND.DLL"{
	dword DirectSoundCreate(dword,dword,dword);
	dword DirectSoundEnumerateA(dword,dword);
	dword DirectSoundEnumerateW(dword,dword);
	dword DirectSoundCaptureCreate(dword,dword,dword);
	dword DirectSoundCaptureEnumerateA(dword,dword);
	dword DirectSoundCaptureEnumerateW(dword,dword);
#ifdef UNICODE
#define DirectSoundEnumerate        DirectSoundEnumerateW
#define DirectSoundCaptureEnumerate DirectSoundCaptureEnumerateW
#else // UNICODE
#define DirectSoundEnumerate        DirectSoundEnumerateA
#define DirectSoundCaptureEnumerate DirectSoundCaptureEnumerateA
#endif // UNICODE
}

// IDirectSound
:DEFINE_GUID(IID_IDirectSound,0x279AFA83,0x4981,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60);

struct IDirectSound
{
// IUnknown methods
  DWORD QueryInterface;
  DWORD AddRef;
  DWORD Release;
// IDirectSound methods
  dword CreateSoundBuffer;
  dword GetCaps;
  dword DuplicateSoundBuffer;
  dword SetCooperativeLevel;
  dword Compact;
  dword GetSpeakerConfig;
  dword SetSpeakerConfig;
  dword Initialize;
};

// IDirectSoundBuffer
:DEFINE_GUID(IID_IDirectSoundBuffer,0x279AFA85,0x4981,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60);

struct IDirectSoundBuffer
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// methods
  dword GetCaps;
  dword GetCurrentPosition;
  dword GetFormat;
  dword GetVolume;
  dword GetPan;
  dword GetFrequency;
  dword GetStatus;
  dword Initialize;
  dword Lock;
  dword Play;
  dword SetCurrentPosition;
  dword SetFormat;
  dword SetVolume;
  dword SetPan;
  dword SetFrequency;
  dword Stop;
  dword Unlock;
  dword Restore;
};

// IDirectSound3DListener
:DEFINE_GUID(IID_IDirectSound3DListener,0x279AFA84,0x4981,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60);

struct IDirectSound3DListener
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDirectSound3DListener methods
  dword GetAllParameters;
  dword GetDistanceFactor;
  dword GetDopplerFactor;
  dword GetOrientation;
  dword GetPosition;
  dword GetRolloffFactor;
  dword GetVelocity;
  dword SetAllParameters;
  dword SetDistanceFactor;
  dword SetDopplerFactor;
  dword SetOrientation;
  dword SetPosition;
  dword SetRolloffFactor;
  dword SetVelocity;
  dword CommitDeferredSettings;
};

// IDirectSound3DBuffer
:DEFINE_GUID(IID_IDirectSound3DBuffer,0x279AFA86,0x4981,0x11CE,0xA5,0x21,0x00,0x20,0xAF,0x0B,0xE5,0x60);

struct IDirectSound3DBuffer
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDirectSound3DBuffer methods
  dword GetAllParameters;
  dword GetConeAngles;
  dword GetConeOrientation;
  dword GetConeOutsideVolume;
  dword GetMaxDistance;
  dword GetMinDistance;
  dword GetMode;
  dword GetPosition;
  dword GetVelocity;
  dword SetAllParameters;
  dword SetConeAngles;
  dword SetConeOrientation;
  dword SetConeOutsideVolume;
  dword SetMaxDistance;
  dword SetMinDistance;
  dword SetMode;
  dword SetPosition;
  dword SetVelocity;
};

// IDirectSoundCapture
:DEFINE_GUID(IID_IDirectSoundCapture,0xb0210781,0x89cd,0x11d0,0xaf,0x8,0x0,0xa0,0xc9,0x25,0xcd,0x16);

struct IDirectSoundCapture
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDirectSoundCapture methods
  dword CreateCaptureBuffer;
  dword GetCaps;
  dword Initialize;
};

// IDirectSoundCaptureBuffer

:DEFINE_GUID(IID_IDirectSoundCaptureBuffer,0xb0210782,0x89cd,0x11d0,0xaf,0x8,0x0,0xa0,0xc9,0x25,0xcd,0x16);

struct IDirectSoundCaptureBuffer
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDirectSoundCaptureBuffer methods
  dword GetCaps;
  dword GetCurrentPosition;
  dword GetFormat;
  dword GetStatus;
  dword Initialize;
  dword Lock;
  dword Start;
  dword Stop;
  dword Unlock;
};

// IDirectSoundNotify

:DEFINE_GUID(IID_IDirectSoundNotify,0xb0210783,0x89cd,0x11d0,0xaf,0x8,0x0,0xa0,0xc9,0x25,0xcd,0x16);

struct IDirectSoundNotify
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IDirectSoundNotify methods
  dword SetNotificationPositions;
};

// IKsPropertySet
#ifndef _IKsPropertySet_
#define _IKsPropertySet_

#define KSPROPERTY_SUPPORT_GET  0x00000001
#define KSPROPERTY_SUPPORT_SET  0x00000002

:DEFINE_GUID(IID_IKsPropertySet,0x31efac30,0x515c,0x11d0,0xa9,0xaa,0x00,0xaa,0x00,0x61,0xbe,0x93);

struct IKsPropertySet
{
// IUnknown methods
  dword QueryInterface;
  dword AddRef;
  dword Release;
// IKsPropertySet methods
  dword Get;
  dword Set;
  dword QuerySupport;
};

#endif // _IKsPropertySet_

// Return Codes
// The function completed successfully
#define DS_OK                           S_OK
// The function completed successfully, but we had to substitute the 3D algorithm
#define DS_NO_VIRTUALIZATION            0x878000A
// The call failed because resources (such as a priority level)
// were already being used by another caller
#define DSERR_ALLOCATED                 0x8878000A
// The control (vol,pan,etc.) requested by the caller is not available
#define DSERR_CONTROLUNAVAIL            0x8878001E
// An invalid parameter was passed to the returning function
#define DSERR_INVALIDPARAM              E_INVALIDARG
// This call is not valid for the current state of this object
#define DSERR_INVALIDCALL               0x88780032
// An undetermined error occured inside the DirectSound subsystem
#define DSERR_GENERIC                   E_FAIL
// The caller does not have the priority level required for the function to
// succeed
#define DSERR_PRIOLEVELNEEDED           0x88780046
// Not enough free memory is available to complete the operation
#define DSERR_OUTOFMEMORY               E_OUTOFMEMORY
// The specified WAVE format is not supported
#define DSERR_BADFORMAT                 0x88780064
// The function called is not supported at this time
#define DSERR_UNSUPPORTED               E_NOTIMPL
// No sound driver is available for use
#define DSERR_NODRIVER                  0x88780078
// This object is already initialized
#define DSERR_ALREADYINITIALIZED        0x88780082
// This object does not support aggregation
#define DSERR_NOAGGREGATION             CLASS_E_NOAGGREGATION
// The buffer memory has been lost, and must be restored
#define DSERR_BUFFERLOST                0x88780096
// Another app has a higher priority level, preventing this call from
// succeeding
#define DSERR_OTHERAPPHASPRIO           0x887800A0
// This object has not been initialized
#define DSERR_UNINITIALIZED             0x887800AA
// The requested COM interface is not available
#define DSERR_NOINTERFACE               E_NOINTERFACE
// Access is denied
#define DSERR_ACCESSDENIED              E_ACCESSDENIED

// Flags
#define DSCAPS_PRIMARYMONO          0x00000001
#define DSCAPS_PRIMARYSTEREO        0x00000002
#define DSCAPS_PRIMARY8BIT          0x00000004
#define DSCAPS_PRIMARY16BIT         0x00000008
#define DSCAPS_CONTINUOUSRATE       0x00000010
#define DSCAPS_EMULDRIVER           0x00000020
#define DSCAPS_CERTIFIED            0x00000040
#define DSCAPS_SECONDARYMONO        0x00000100
#define DSCAPS_SECONDARYSTEREO      0x00000200
#define DSCAPS_SECONDARY8BIT        0x00000400
#define DSCAPS_SECONDARY16BIT       0x00000800
#define DSSCL_NORMAL                0x00000001
#define DSSCL_PRIORITY              0x00000002
#define DSSCL_EXCLUSIVE             0x00000003
#define DSSCL_WRITEPRIMARY          0x00000004
#define DSSPEAKER_HEADPHONE         0x00000001
#define DSSPEAKER_MONO              0x00000002
#define DSSPEAKER_QUAD              0x00000003
#define DSSPEAKER_STEREO            0x00000004
#define DSSPEAKER_SURROUND          0x00000005
#define DSSPEAKER_5POINT1           0x00000006
#define DSSPEAKER_GEOMETRY_MIN      0x00000005  //   5 degrees
#define DSSPEAKER_GEOMETRY_NARROW   0x0000000A  //  10 degrees
#define DSSPEAKER_GEOMETRY_WIDE     0x00000014  //  20 degrees
#define DSSPEAKER_GEOMETRY_MAX      0x000000B4  // 180 degrees

#define DSSPEAKER_COMBINED(c, g)    g<<16|c
#define DSSPEAKER_CONFIG(a)         a&0xFF
#define DSSPEAKER_GEOMETRY(a)       a>>16&0x00FF

#define DSBCAPS_PRIMARYBUFFER       0x00000001
#define DSBCAPS_STATIC              0x00000002
#define DSBCAPS_LOCHARDWARE         0x00000004
#define DSBCAPS_LOCSOFTWARE         0x00000008
#define DSBCAPS_CTRL3D              0x00000010
#define DSBCAPS_CTRLFREQUENCY       0x00000020
#define DSBCAPS_CTRLPAN             0x00000040
#define DSBCAPS_CTRLVOLUME          0x00000080
#define DSBCAPS_CTRLPOSITIONNOTIFY  0x00000100
#define DSBCAPS_STICKYFOCUS         0x00004000
#define DSBCAPS_GLOBALFOCUS         0x00008000
#define DSBCAPS_GETCURRENTPOSITION2 0x00010000
#define DSBCAPS_MUTE3DATMAXDISTANCE 0x00020000
#define DSBCAPS_LOCDEFER            0x00040000
#define DSBPLAY_LOOPING             0x00000001
#define DSBPLAY_LOCHARDWARE         0x00000002
#define DSBPLAY_LOCSOFTWARE         0x00000004
#define DSBPLAY_TERMINATEBY_TIME    0x00000008
#define DSBPLAY_TERMINATEBY_DISTANCE    0x000000010
#define DSBPLAY_TERMINATEBY_PRIORITY    0x000000020
#define DSBSTATUS_PLAYING           0x00000001
#define DSBSTATUS_BUFFERLOST        0x00000002
#define DSBSTATUS_LOOPING           0x00000004
#define DSBSTATUS_LOCHARDWARE       0x00000008
#define DSBSTATUS_LOCSOFTWARE       0x00000010
#define DSBSTATUS_TERMINATED        0x00000020
#define DSBLOCK_FROMWRITECURSOR     0x00000001
#define DSBLOCK_ENTIREBUFFER        0x00000002
#define DSBFREQUENCY_MIN            100
#define DSBFREQUENCY_MAX            100000
#define DSBFREQUENCY_ORIGINAL       0
#define DSBPAN_LEFT                 -10000
#define DSBPAN_CENTER               0
#define DSBPAN_RIGHT                10000
#define DSBVOLUME_MIN               -10000
#define DSBVOLUME_MAX               0
#define DSBSIZE_MIN                 4
#define DSBSIZE_MAX                 0x0FFFFFFF
#define DS3DMODE_NORMAL             0x00000000
#define DS3DMODE_HEADRELATIVE       0x00000001
#define DS3DMODE_DISABLE            0x00000002
#define DS3D_IMMEDIATE              0x00000000
#define DS3D_DEFERRED               0x00000001
#define DS3D_MINDISTANCEFACTOR      FLT_MIN
#define DS3D_MAXDISTANCEFACTOR      FLT_MAX
#define DS3D_DEFAULTDISTANCEFACTOR  1.0f
#define DS3D_MINROLLOFFFACTOR       0.0f
#define DS3D_MAXROLLOFFFACTOR       10.0f
#define DS3D_DEFAULTROLLOFFFACTOR   1.0f
#define DS3D_MINDOPPLERFACTOR       0.0f
#define DS3D_MAXDOPPLERFACTOR       10.0f
#define DS3D_DEFAULTDOPPLERFACTOR   1.0f
#define DS3D_DEFAULTMINDISTANCE     1.0f
#define DS3D_DEFAULTMAXDISTANCE     1000000000.0f
#define DS3D_MINCONEANGLE           0
#define DS3D_MAXCONEANGLE           360
#define DS3D_DEFAULTCONEANGLE       360
#define DS3D_DEFAULTCONEOUTSIDEVOLUME DSBVOLUME_MAX
#define DSCCAPS_EMULDRIVER          DSCAPS_EMULDRIVER
#define DSCCAPS_CERTIFIED           DSCAPS_CERTIFIED
#define DSCBCAPS_WAVEMAPPED         0x80000000
#define DSCBLOCK_ENTIREBUFFER       0x00000001
#define DSCBSTATUS_CAPTURING        0x00000001
#define DSCBSTATUS_LOOPING          0x00000002
#define DSCBSTART_LOOPING           0x00000001
#define DSBPN_OFFSETSTOP            0xFFFFFFFF

// DirectSound3D Algorithms

// Default DirectSound3D algorithm {00000000-0000-0000-0000-000000000000}
#define DS3DALG_DEFAULT GUID_NULL

// No virtualization {C241333F-1C1B-11d2-94F5-00C04FC28ACA}
:DEFINE_GUID(DS3DALG_NO_VIRTUALIZATION,0xc241333f,0x1c1b,0x11d2,0x94,0xf5,0x0,0xc0,0x4f,0xc2,0x8a,0xca);

// High-quality HRTF algorithm {C2413340-1C1B-11d2-94F5-00C04FC28ACA}
:DEFINE_GUID(DS3DALG_HRTF_FULL,0xc2413340,0x1c1b,0x11d2,0x94,0xf5,0x0,0xc0,0x4f,0xc2,0x8a,0xca);

// Lower-quality HRTF algorithm {C2413342-1C1B-11d2-94F5-00C04FC28ACA}
:DEFINE_GUID(DS3DALG_HRTF_LIGHT,0xc2413342,0x1c1b,0x11d2,0x94,0xf5,0x0,0xc0,0x4f,0xc2,0x8a,0xca);

#endif  // __DSOUND_INCLUDED__
