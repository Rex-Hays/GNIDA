//+---------------------------------------------------------------------------
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation.  All rights reserved.
//  File:       guiddef.h
//  Contents:   GUID definition
//----------------------------------------------------------------------------

#ifndef GUID_DEFINED
#define GUID_DEFINED
struct GUID {
  unsigned long  Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char  Data4[8];
};
#endif

#ifdef DEFINE_GUID
#undef DEFINE_GUID
#endif

#define CLSID GUID

//#ifdef INITGUID
#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) GUID name={l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8}
//#else
//#define DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) GUID name
//#endif // INITGUID

#define DEFINE_OLEGUID(name,l,w1,w2) DEFINE_GUID(name,l,w1,w2,0xC0,0,0,0,0,0,0,0x46)
