/*==========================================================================;
 *  Copyright (C) 1995-1998 Microsoft Corporation.  All Rights Reserved.
 *  File:   d3dtypes.h
 *  Content:    Direct3D types include file
 ***************************************************************************/
#ifndef _D3DTYPES_H_
#define _D3DTYPES_H_

#include <windows.h>
//#include <float.h>
#include <ddraw.h>

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0700
#endif

#pragma pack(4)

/* D3DVALUE is the fundamental Direct3D fractional data type */

#define D3DVALUE float
#define D3DDivide(a,b)    a/b
#define D3DMultiply(a,b)    a*b

#define D3DFIXED long
#define D3DCOLOR dword

#ifndef RGB_MAKE
/*
 * Format of CI colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    alpha      |         color index           |   fraction    |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define CI_GETALPHA(ci)    ci>>24
#define CI_GETINDEX(ci)    ci>>8&0xffff
#define CI_GETFRACTION(ci) ci&0xff
#define CI_ROUNDINDEX(ci)  CI_GETINDEX(ci+0x80)
#define CI_MASKALPHA(ci)   ci&0xffffff
#define CI_MAKE(a,i,f)    a<<16|i<<8|f

/*
 * Format of RGBA colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    alpha      |      red      |     green     |     blue      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define RGBA_GETALPHA(rgb)      rgb>>24
#define RGBA_GETRED(rgb)        rgb>>16&0xff
#define RGBA_GETGREEN(rgb)      rgb>>8&0xff
#define RGBA_GETBLUE(rgb)       rgb&0xff
#define RGBA_MAKE(r,g,b,a)   a<<8|r<<8|g<<8|b

/* D3DRGB and D3DRGBA may be used as initialisers for D3DCOLORs
 * The float values must be in the range 0..1
 */
//#define D3DRGB(r,g,b) (0xff000000L|( ((long)(r*255))<<16)|(((long)(g*255))<<8) | (long)(b*255))
:dword stdcall D3DRGB(r,g,b)
{
	EAX=r*255<<16;
	ECX=g*255<<8|EAX;
	return b*255|ECX|0xff000000;
}

//#define D3DRGBA(r,g,b,a) ((((long)(a*255))<<24)|(((long)(r*255))<<16)|(((long)(g*255))<<8)|(long)(b*255))
:dword stdcall D3DRGBA(r,g,b,a)
{
	ECX=a*255<<24;
	EAX=r*255<<16|ECX;
	ECX=g*255<<8|EAX;
	return b*255|ECX;
}

/*
 * Format of RGB colors is
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *  |    ignored    |      red      |     green     |     blue      |
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 */
#define RGB_GETRED(rgb)         rgb>>16&0xff
#define RGB_GETGREEN(rgb)       rgb>>8&0xff
#define RGB_GETBLUE(rgb)        rgb&0xff
//#define RGBA_SETALPHA(rgba,x) ((x<<24) | (rgba&0x00ffffff))
:dword stdcall RGBA_SETALPHA(rgba,x)
{
	ECX=rgba&0x00ffffff;
	return x<<24|ECX;
}
#define RGB_MAKE(r,g,b)       r<<8|g<<8|b
#define RGBA_TORGB(rgba)       rgba&0xffffff
#define RGB_TORGBA(rgb)        rgb|0xff000000

#endif

/*
 * Stop the enumeration
 */
#define D3DENUMRET_CANCEL                        DDENUMRET_CANCEL

/*
 * Continue the enumeration
 */
#define D3DENUMRET_OK                            DDENUMRET_OK

//typedef HRESULT (CALLBACK* LPD3DVALIDATECALLBACK)(LPVOID lpUserArg, DWORD dwOffset);
//typedef HRESULT (CALLBACK* LPD3DENUMTEXTUREFORMATSCALLBACK)(LPDDSURFACEDESC lpDdsd, LPVOID lpContext);
//typedef HRESULT (CALLBACK* LPD3DENUMPIXELFORMATSCALLBACK)(LPDDPIXELFORMAT lpDDPixFmt, LPVOID lpContext);

#define D3DMATERIALHANDLE dword
#define D3DTEXTUREHANDLE dword
#define D3DMATRIXHANDLE dword

struct D3DCOLORVALUE{
  union {
  D3DVALUE r;
  D3DVALUE dvR;
  };
  union {
  D3DVALUE g;
  D3DVALUE dvG;
  };
  union {
  D3DVALUE b;
  D3DVALUE dvB;
  };
  union {
  D3DVALUE a;
  D3DVALUE dvA;
  };
};

struct D3DRECT {
  union {
  LONG x1;
  LONG lX1;
  };
  union {
  LONG y1;
  LONG lY1;
  };
  union {
  LONG x2;
  LONG lX2;
  };
  union {
  LONG y2;
  LONG lY2;
  };
};

struct D3DVECTOR {
  union {
  D3DVALUE x;
  D3DVALUE dvX;
  };
  union {
  D3DVALUE y;
  D3DVALUE dvY;
  };
  union {
  D3DVALUE z;
  D3DVALUE dvZ;
  };
};

/*
 * Vertex data types supported in an ExecuteBuffer.
 */

/*
 * Homogeneous vertices
 */

struct D3DHVERTEX {
  DWORD           dwFlags;        /* Homogeneous clipping flags */
  union {
  D3DVALUE    hx;
  D3DVALUE    dvHX;
  };
  union {
  D3DVALUE    hy;
  D3DVALUE    dvHY;
  };
  union {
  D3DVALUE    hz;
  D3DVALUE    dvHZ;
  };
};

/*
 * Transformed/lit vertices
 */
struct D3DTLVERTEX {
  union {
  D3DVALUE    sx;             /* Screen coordinates */
  D3DVALUE    dvSX;
  };
  union {
  D3DVALUE    sy;
  D3DVALUE    dvSY;
  };
  union {
  D3DVALUE    sz;
  D3DVALUE    dvSZ;
  };
  union {
  D3DVALUE    rhw;        /* Reciprocal of homogeneous w */
  D3DVALUE    dvRHW;
  };
  union {
  D3DCOLOR    color;          /* Vertex color */
  D3DCOLOR    dcColor;
  };
  union {
  D3DCOLOR    specular;       /* Specular component of vertex */
  D3DCOLOR    dcSpecular;
  };
  union {
  D3DVALUE    tu;             /* Texture coordinates */
  D3DVALUE    dvTU;
  };
  union {
  D3DVALUE    tv;
  D3DVALUE    dvTV;
  };
};

/*
 * Untransformed/lit vertices
 */
struct D3DLVERTEX {
  union {
  D3DVALUE     x;             /* Homogeneous coordinates */
  D3DVALUE     dvX;
  };
  union {
  D3DVALUE     y;
  D3DVALUE     dvY;
  };
  union {
  D3DVALUE     z;
  D3DVALUE     dvZ;
  };
  DWORD            dwReserved;
  union {
  D3DCOLOR     color;         /* Vertex color */
  D3DCOLOR     dcColor;
  };
  union {
  D3DCOLOR     specular;      /* Specular component of vertex */
  D3DCOLOR     dcSpecular;
  };
  union {
  D3DVALUE     tu;            /* Texture coordinates */
  D3DVALUE     dvTU;
  };
  union {
  D3DVALUE     tv;
  D3DVALUE     dvTV;
  };
};

/*
 * Untransformed/unlit vertices
 */
struct D3DVERTEX {
  union {
  D3DVALUE     x;             /* Homogeneous coordinates */
  D3DVALUE     dvX;
  };
  union {
  D3DVALUE     y;
  D3DVALUE     dvY;
  };
  union {
  D3DVALUE     z;
  D3DVALUE     dvZ;
  };
  union {
  D3DVALUE     nx;            /* Normal */
  D3DVALUE     dvNX;
  };
  union {
  D3DVALUE     ny;
  D3DVALUE     dvNY;
  };
  union {
  D3DVALUE     nz;
  D3DVALUE     dvNZ;
  };
  union {
  D3DVALUE     tu;            /* Texture coordinates */
  D3DVALUE     dvTU;
  };
  union {
  D3DVALUE     tv;
  D3DVALUE     dvTV;
  };
};

/*
 * Matrix, viewport, and tranformation structures and definitions.
 */
struct D3DMATRIX {
  D3DVALUE        _11, _12, _13, _14;
  D3DVALUE        _21, _22, _23, _24;
  D3DVALUE        _31, _32, _33, _34;
  D3DVALUE        _41, _42, _43, _44;
};

struct D3DVIEWPORT {
  DWORD       dwSize;
  DWORD       dwX;
  DWORD       dwY;        /* Top left */
  DWORD       dwWidth;
  DWORD       dwHeight;   /* Dimensions */
  D3DVALUE    dvScaleX;   /* Scale homogeneous to screen */
  D3DVALUE    dvScaleY;   /* Scale homogeneous to screen */
  D3DVALUE    dvMaxX;     /* Min/max homogeneous x coord */
  D3DVALUE    dvMaxY;     /* Min/max homogeneous y coord */
  D3DVALUE    dvMinZ;
  D3DVALUE    dvMaxZ;     /* Min/max homogeneous z coord */
};

#if(DIRECT3D_VERSION >= 0x0500)
struct D3DVIEWPORT2 {
  DWORD       dwSize;
  DWORD       dwX;
  DWORD       dwY;        /* Viewport Top left */
  DWORD       dwWidth;
  DWORD       dwHeight;   /* Viewport Dimensions */
  D3DVALUE    dvClipX;        /* Top left of clip volume */
  D3DVALUE    dvClipY;
  D3DVALUE    dvClipWidth;    /* Clip Volume Dimensions */
  D3DVALUE    dvClipHeight;
  D3DVALUE    dvMinZ;         /* Min/max of clip Volume */
  D3DVALUE    dvMaxZ;
};
#endif /* DIRECT3D_VERSION >= 0x0500 */

#if(DIRECT3D_VERSION >= 0x0700)
struct D3DVIEWPORT7 {
  DWORD       dwX;
  DWORD       dwY;            /* Viewport Top left */
  DWORD       dwWidth;
  DWORD       dwHeight;       /* Viewport Dimensions */
  D3DVALUE    dvMinZ;         /* Min/max of clip Volume */
  D3DVALUE    dvMaxZ;
};
#endif /* DIRECT3D_VERSION >= 0x0700 */

/*
 * Values for clip fields.
 */
#if(DIRECT3D_VERSION >= 0x0700)

// Max number of user clipping planes, supported in D3D.
#define D3DMAXUSERCLIPPLANES 32

// These bits could be ORed together to use with D3DRENDERSTATE_CLIPPLANEENABLE
#define D3DCLIPPLANE0 1
#define D3DCLIPPLANE1 2
#define D3DCLIPPLANE2 4
#define D3DCLIPPLANE3 8
#define D3DCLIPPLANE4 16
#define D3DCLIPPLANE5 32

#endif /* DIRECT3D_VERSION >= 0x0700 */

#define D3DCLIP_LEFT                0x00000001L
#define D3DCLIP_RIGHT               0x00000002L
#define D3DCLIP_TOP             0x00000004L
#define D3DCLIP_BOTTOM              0x00000008L
#define D3DCLIP_FRONT               0x00000010L
#define D3DCLIP_BACK                0x00000020L
#define D3DCLIP_GEN0                0x00000040L
#define D3DCLIP_GEN1                0x00000080L
#define D3DCLIP_GEN2                0x00000100L
#define D3DCLIP_GEN3                0x00000200L
#define D3DCLIP_GEN4                0x00000400L
#define D3DCLIP_GEN5                0x00000800L

/*
 * Values for d3d status.
 */
#define D3DSTATUS_CLIPUNIONLEFT         D3DCLIP_LEFT
#define D3DSTATUS_CLIPUNIONRIGHT        D3DCLIP_RIGHT
#define D3DSTATUS_CLIPUNIONTOP          D3DCLIP_TOP
#define D3DSTATUS_CLIPUNIONBOTTOM       D3DCLIP_BOTTOM
#define D3DSTATUS_CLIPUNIONFRONT        D3DCLIP_FRONT
#define D3DSTATUS_CLIPUNIONBACK         D3DCLIP_BACK
#define D3DSTATUS_CLIPUNIONGEN0         D3DCLIP_GEN0
#define D3DSTATUS_CLIPUNIONGEN1         D3DCLIP_GEN1
#define D3DSTATUS_CLIPUNIONGEN2         D3DCLIP_GEN2
#define D3DSTATUS_CLIPUNIONGEN3         D3DCLIP_GEN3
#define D3DSTATUS_CLIPUNIONGEN4         D3DCLIP_GEN4
#define D3DSTATUS_CLIPUNIONGEN5         D3DCLIP_GEN5

#define D3DSTATUS_CLIPINTERSECTIONLEFT      0x00001000L
#define D3DSTATUS_CLIPINTERSECTIONRIGHT     0x00002000L
#define D3DSTATUS_CLIPINTERSECTIONTOP       0x00004000L
#define D3DSTATUS_CLIPINTERSECTIONBOTTOM    0x00008000L
#define D3DSTATUS_CLIPINTERSECTIONFRONT     0x00010000L
#define D3DSTATUS_CLIPINTERSECTIONBACK      0x00020000L
#define D3DSTATUS_CLIPINTERSECTIONGEN0      0x00040000L
#define D3DSTATUS_CLIPINTERSECTIONGEN1      0x00080000L
#define D3DSTATUS_CLIPINTERSECTIONGEN2      0x00100000L
#define D3DSTATUS_CLIPINTERSECTIONGEN3      0x00200000L
#define D3DSTATUS_CLIPINTERSECTIONGEN4      0x00400000L
#define D3DSTATUS_CLIPINTERSECTIONGEN5      0x00800000L
#define D3DSTATUS_ZNOTVISIBLE               0x01000000L
/* Do not use 0x80000000 for any status flags in future as it is reserved */

#define D3DSTATUS_CLIPUNIONALL D3DSTATUS_CLIPUNIONLEFT|D3DSTATUS_CLIPUNIONRIGHT|\
        D3DSTATUS_CLIPUNIONTOP  | D3DSTATUS_CLIPUNIONBOTTOM|   \
        D3DSTATUS_CLIPUNIONFRONT| D3DSTATUS_CLIPUNIONBACK |   \
        D3DSTATUS_CLIPUNIONGEN0 | D3DSTATUS_CLIPUNIONGEN1 |   \
        D3DSTATUS_CLIPUNIONGEN2 | D3DSTATUS_CLIPUNIONGEN3 |   \
        D3DSTATUS_CLIPUNIONGEN4 | D3DSTATUS_CLIPUNIONGEN5

#define D3DSTATUS_CLIPINTERSECTIONALL D3DSTATUS_CLIPINTERSECTIONLEFT  |   \
        D3DSTATUS_CLIPINTERSECTIONRIGHT | D3DSTATUS_CLIPINTERSECTIONTOP   |   \
        D3DSTATUS_CLIPINTERSECTIONBOTTOM| D3DSTATUS_CLIPINTERSECTIONFRONT |   \
        D3DSTATUS_CLIPINTERSECTIONBACK  | D3DSTATUS_CLIPINTERSECTIONGEN0  |   \
        D3DSTATUS_CLIPINTERSECTIONGEN1  | D3DSTATUS_CLIPINTERSECTIONGEN2  |   \
        D3DSTATUS_CLIPINTERSECTIONGEN3  | D3DSTATUS_CLIPINTERSECTIONGEN4  |   \
        D3DSTATUS_CLIPINTERSECTIONGEN5

#define D3DSTATUS_DEFAULT D3DSTATUS_CLIPINTERSECTIONALL | D3DSTATUS_ZNOTVISIBLE

/*
 * Options for direct transform calls
 */
#define D3DTRANSFORM_CLIPPED       0x00000001l
#define D3DTRANSFORM_UNCLIPPED     0x00000002l

struct D3DTRANSFORMDATA {
  DWORD           dwSize;
  LPVOID      lpIn;           /* Input vertices */
  DWORD           dwInSize;       /* Stride of input vertices */
  LPVOID      lpOut;          /* Output vertices */
  DWORD           dwOutSize;      /* Stride of output vertices */
  dword    lpHOut;         /* Output homogeneous vertices */
  DWORD           dwClip;         /* Clipping hint */
  DWORD           dwClipIntersection;
  DWORD           dwClipUnion;    /* Union of all clip flags */
  D3DRECT         drExtent;       /* Extent of transformed vertices */
};

/*
 * Structure defining position and direction properties for lighting.
 */
struct D3DLIGHTINGELEMENT {
  D3DVECTOR dvPosition;           /* Lightable point in model space */
  D3DVECTOR dvNormal;             /* Normalised unit vector */
};

/*
 * Structure defining material properties for lighting.
 */
struct D3DMATERIAL {
  DWORD           dwSize;
  union {
  D3DCOLORVALUE   diffuse;        /* Diffuse color RGBA */
  D3DCOLORVALUE   dcvDiffuse;
  };
  union {
  D3DCOLORVALUE   ambient;        /* Ambient color RGB */
  D3DCOLORVALUE   dcvAmbient;
  };
  union {
  D3DCOLORVALUE   specular;       /* Specular 'shininess' */
  D3DCOLORVALUE   dcvSpecular;
  };
  union {
  D3DCOLORVALUE   emissive;       /* Emissive color RGB */
  D3DCOLORVALUE   dcvEmissive;
  };
  union {
  D3DVALUE        power;          /* Sharpness if specular highlight */
  D3DVALUE        dvPower;
  };
  D3DTEXTUREHANDLE    hTexture;       /* Handle to texture map */
  DWORD           dwRampSize;
};

#if(DIRECT3D_VERSION >= 0x0700)

struct D3DMATERIAL7 {
  union {
  D3DCOLORVALUE   diffuse;        /* Diffuse color RGBA */
  D3DCOLORVALUE   dcvDiffuse;
  };
  union {
  D3DCOLORVALUE   ambient;        /* Ambient color RGB */
  D3DCOLORVALUE   dcvAmbient;
  };
  union {
  D3DCOLORVALUE   specular;       /* Specular 'shininess' */
  D3DCOLORVALUE   dcvSpecular;
  };
  union {
  D3DCOLORVALUE   emissive;       /* Emissive color RGB */
  D3DCOLORVALUE   dcvEmissive;
  };
  union {
  D3DVALUE        power;          /* Sharpness if specular highlight */
  D3DVALUE        dvPower;
  };
};

#endif /* DIRECT3D_VERSION >= 0x0700 */

enum D3DLIGHTTYPE{
  D3DLIGHT_POINT          = 1,
  D3DLIGHT_SPOT           = 2,
  D3DLIGHT_DIRECTIONAL    = 3,
// Note: The following light type (D3DLIGHT_PARALLELPOINT)
// is no longer supported from D3D for DX7 onwards.
  D3DLIGHT_PARALLELPOINT  = 4,
  D3DLIGHT_GLSPOT         = 5,
  D3DLIGHT_FORCE_DWORD    = 0x7fffffff, /* force 32-bit size enum */
};

/*
 * Structure defining a light source and its properties.
 */
struct D3DLIGHT {
  DWORD           dwSize;
  dword    dltType;            /* Type of light source */
  D3DCOLORVALUE   dcvColor;           /* Color of light */
  D3DVECTOR       dvPosition;         /* Position in world space */
  D3DVECTOR       dvDirection;        /* Direction in world space */
  D3DVALUE        dvRange;            /* Cutoff range */
  D3DVALUE        dvFalloff;          /* Falloff */
  D3DVALUE        dvAttenuation0;     /* Constant attenuation */
  D3DVALUE        dvAttenuation1;     /* Linear attenuation */
  D3DVALUE        dvAttenuation2;     /* Quadratic attenuation */
  D3DVALUE        dvTheta;            /* Inner angle of spotlight cone */
  D3DVALUE        dvPhi;              /* Outer angle of spotlight cone */
};

#if(DIRECT3D_VERSION >= 0x0700)

struct D3DLIGHT7 {
  dword    dltType;            /* Type of light source */
  D3DCOLORVALUE   dcvDiffuse;         /* Diffuse color of light */
  D3DCOLORVALUE   dcvSpecular;        /* Specular color of light */
  D3DCOLORVALUE   dcvAmbient;         /* Ambient color of light */
  D3DVECTOR       dvPosition;         /* Position in world space */
  D3DVECTOR       dvDirection;        /* Direction in world space */
  D3DVALUE        dvRange;            /* Cutoff range */
  D3DVALUE        dvFalloff;          /* Falloff */
  D3DVALUE        dvAttenuation0;     /* Constant attenuation */
  D3DVALUE        dvAttenuation1;     /* Linear attenuation */
  D3DVALUE        dvAttenuation2;     /* Quadratic attenuation */
  D3DVALUE        dvTheta;            /* Inner angle of spotlight cone */
  D3DVALUE        dvPhi;              /* Outer angle of spotlight cone */
};

#endif /* DIRECT3D_VERSION >= 0x0700 */

#if(DIRECT3D_VERSION >= 0x0500)
/*
 * Structure defining a light source and its properties.
 */

/* flags bits */
#define D3DLIGHT_ACTIVE         0x00000001
#define D3DLIGHT_NO_SPECULAR    0x00000002
#define D3DLIGHT_ALL D3DLIGHT_ACTIVE | D3DLIGHT_NO_SPECULAR

struct D3DLIGHT2 {
  DWORD           dwSize;
  dword    dltType;        /* Type of light source */
  D3DCOLORVALUE   dcvColor;       /* Color of light */
  D3DVECTOR       dvPosition;     /* Position in world space */
  D3DVECTOR       dvDirection;    /* Direction in world space */
  D3DVALUE        dvRange;        /* Cutoff range */
  D3DVALUE        dvFalloff;      /* Falloff */
  D3DVALUE        dvAttenuation0; /* Constant attenuation */
  D3DVALUE        dvAttenuation1; /* Linear attenuation */
  D3DVALUE        dvAttenuation2; /* Quadratic attenuation */
  D3DVALUE        dvTheta;        /* Inner angle of spotlight cone */
  D3DVALUE        dvPhi;          /* Outer angle of spotlight cone */
  DWORD           dwFlags;
};

#endif /* DIRECT3D_VERSION >= 0x0500 */
struct D3DLIGHTDATA {
  DWORD                dwSize;
  dword lpIn;      /* Input positions and normals */
  DWORD                dwInSize;  /* Stride of input elements */
  dword        lpOut;     /* Output colors */
  DWORD                dwOutSize; /* Stride of output colors */
};

#if(DIRECT3D_VERSION >= 0x0500)
/*
 * Before DX5, these values were in an enum called
 * D3DCOLORMODEL. This was not correct, since they are
 * bit flags. A driver can surface either or both flags
 * in the dcmColorModel member of D3DDEVICEDESC.
 */
#define D3DCOLOR_MONO   1
#define D3DCOLOR_RGB    2

#define D3DCOLORMODEL dword
#endif /* DIRECT3D_VERSION >= 0x0500 */

/*
 * Options for clearing
 */
#define D3DCLEAR_TARGET            0x00000001l  /* Clear target surface */
#define D3DCLEAR_ZBUFFER           0x00000002l  /* Clear target z buffer */
#define D3DCLEAR_STENCIL           0x00000004l  /* Clear stencil planes */

/*
 * Execute buffers are allocated via Direct3D.  These buffers may then
 * be filled by the application with instructions to execute along with
 * vertex data.
 */

/*
 * Supported op codes for execute instructions.
 */
enum D3DOPCODE{
  D3DOP_POINT                 = 1,
  D3DOP_LINE                  = 2,
  D3DOP_TRIANGLE      = 3,
  D3DOP_MATRIXLOAD        = 4,
  D3DOP_MATRIXMULTIPLY    = 5,
  D3DOP_STATETRANSFORM        = 6,
  D3DOP_STATELIGHT        = 7,
  D3DOP_STATERENDER       = 8,
  D3DOP_PROCESSVERTICES       = 9,
  D3DOP_TEXTURELOAD       = 10,
  D3DOP_EXIT                  = 11,
  D3DOP_BRANCHFORWARD     = 12,
  D3DOP_SPAN          = 13,
  D3DOP_SETSTATUS     = 14,
  D3DOP_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
};

struct D3DINSTRUCTION {
  BYTE bOpcode;   /* Instruction opcode */
  BYTE bSize;     /* Size of each instruction data unit */
  WORD wCount;    /* Count of instruction data units to follow */
};

/*
 * Structure for texture loads
 */
struct D3DTEXTURELOAD {
  D3DTEXTUREHANDLE hDestTexture;
  D3DTEXTUREHANDLE hSrcTexture;
};

/*
 * Structure for picking
 */
struct D3DPICKRECORD {
  BYTE     bOpcode;
  BYTE     bPad;
  DWORD    dwOffset;
  D3DVALUE dvZ;
};

/*
 * The following defines the rendering states which can be set in the
 * execute buffer.
 */
enum D3DSHADEMODE{
  D3DSHADE_FLAT              = 1,
  D3DSHADE_GOURAUD           = 2,
  D3DSHADE_PHONG             = 3,
  D3DSHADE_FORCE_DWORD       = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DFILLMODE{
  D3DFILL_POINT          = 1,
  D3DFILL_WIREFRAME          = 2,
  D3DFILL_SOLID          = 3,
  D3DFILL_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

struct D3DLINEPATTERN {
  WORD    wRepeatFactor;
  WORD    wLinePattern;
};

enum D3DTEXTUREFILTER{
  D3DFILTER_NEAREST          = 1,
  D3DFILTER_LINEAR           = 2,
  D3DFILTER_MIPNEAREST       = 3,
  D3DFILTER_MIPLINEAR        = 4,
  D3DFILTER_LINEARMIPNEAREST = 5,
  D3DFILTER_LINEARMIPLINEAR  = 6,
  D3DFILTER_FORCE_DWORD      = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DBLEND{
  D3DBLEND_ZERO              = 1,
  D3DBLEND_ONE               = 2,
  D3DBLEND_SRCCOLOR          = 3,
  D3DBLEND_INVSRCCOLOR       = 4,
  D3DBLEND_SRCALPHA          = 5,
  D3DBLEND_INVSRCALPHA       = 6,
  D3DBLEND_DESTALPHA         = 7,
  D3DBLEND_INVDESTALPHA      = 8,
  D3DBLEND_DESTCOLOR         = 9,
  D3DBLEND_INVDESTCOLOR      = 10,
  D3DBLEND_SRCALPHASAT       = 11,
  D3DBLEND_BOTHSRCALPHA      = 12,
  D3DBLEND_BOTHINVSRCALPHA   = 13,
  D3DBLEND_FORCE_DWORD       = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DTEXTUREBLEND{
  D3DTBLEND_DECAL            = 1,
  D3DTBLEND_MODULATE         = 2,
  D3DTBLEND_DECALALPHA       = 3,
  D3DTBLEND_MODULATEALPHA    = 4,
  D3DTBLEND_DECALMASK        = 5,
  D3DTBLEND_MODULATEMASK     = 6,
  D3DTBLEND_COPY             = 7,
  D3DTBLEND_ADD              = 8,
  D3DTBLEND_FORCE_DWORD      = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DTEXTUREADDRESS{
  D3DTADDRESS_WRAP           = 1,
  D3DTADDRESS_MIRROR         = 2,
  D3DTADDRESS_CLAMP          = 3,
  D3DTADDRESS_BORDER         = 4,
  D3DTADDRESS_FORCE_DWORD    = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DCULL{
  D3DCULL_NONE               = 1,
  D3DCULL_CW                 = 2,
  D3DCULL_CCW                = 3,
  D3DCULL_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DCMPFUNC{
  D3DCMP_NEVER               = 1,
  D3DCMP_LESS                = 2,
  D3DCMP_EQUAL               = 3,
  D3DCMP_LESSEQUAL           = 4,
  D3DCMP_GREATER             = 5,
  D3DCMP_NOTEQUAL            = 6,
  D3DCMP_GREATEREQUAL        = 7,
  D3DCMP_ALWAYS              = 8,
  D3DCMP_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DSTENCILOP{
  D3DSTENCILOP_KEEP           = 1,
  D3DSTENCILOP_ZERO           = 2,
  D3DSTENCILOP_REPLACE        = 3,
  D3DSTENCILOP_INCRSAT        = 4,
  D3DSTENCILOP_DECRSAT        = 5,
  D3DSTENCILOP_INVERT         = 6,
  D3DSTENCILOP_INCR           = 7,
  D3DSTENCILOP_DECR           = 8,
  D3DSTENCILOP_FORCE_DWORD    = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DFOGMODE{
  D3DFOG_NONE                = 0,
  D3DFOG_EXP                 = 1,
  D3DFOG_EXP2                = 2,
  D3DFOG_LINEAR              = 3,
  D3DFOG_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DZBUFFERTYPE{
  D3DZB_FALSE                 = 0,
  D3DZB_TRUE                  = 1, // Z buffering
  D3DZB_USEW                  = 2, // W buffering
  D3DZB_FORCE_DWORD           = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DANTIALIASMODE{
  D3DANTIALIAS_NONE          = 0,
  D3DANTIALIAS_SORTDEPENDENT = 1,
  D3DANTIALIAS_SORTINDEPENDENT = 2,
  D3DANTIALIAS_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

// Vertex types supported by Direct3D
enum D3DVERTEXTYPE{
  D3DVT_VERTEX        = 1,
  D3DVT_LVERTEX       = 2,
  D3DVT_TLVERTEX      = 3,
  D3DVT_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

// Primitives supported by draw-primitive API
enum D3DPRIMITIVETYPE{
  D3DPT_POINTLIST     = 1,
  D3DPT_LINELIST      = 2,
  D3DPT_LINESTRIP     = 3,
  D3DPT_TRIANGLELIST  = 4,
  D3DPT_TRIANGLESTRIP = 5,
  D3DPT_TRIANGLEFAN   = 6,
  D3DPT_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

/*
 * Amount to add to a state to generate the override for that state.
 */
#define D3DSTATE_OVERRIDE_BIAS      256

/*
 * A state which sets the override flag for the specified state type.
 */
#define D3DSTATE_OVERRIDE(type) type+D3DSTATE_OVERRIDE_BIAS

enum D3DTRANSFORMSTATETYPE{
  D3DTRANSFORMSTATE_WORLD         = 1,
  D3DTRANSFORMSTATE_VIEW          = 2,
  D3DTRANSFORMSTATE_PROJECTION    = 3,
  D3DTRANSFORMSTATE_WORLD1        = 4,  // 2nd matrix to blend
  D3DTRANSFORMSTATE_WORLD2        = 5,  // 3rd matrix to blend
  D3DTRANSFORMSTATE_WORLD3        = 6,  // 4th matrix to blend
  D3DTRANSFORMSTATE_TEXTURE0      = 16,
  D3DTRANSFORMSTATE_TEXTURE1      = 17,
  D3DTRANSFORMSTATE_TEXTURE2      = 18,
  D3DTRANSFORMSTATE_TEXTURE3      = 19,
  D3DTRANSFORMSTATE_TEXTURE4      = 20,
  D3DTRANSFORMSTATE_TEXTURE5      = 21,
  D3DTRANSFORMSTATE_TEXTURE6      = 22,
  D3DTRANSFORMSTATE_TEXTURE7      = 23,
  D3DTRANSFORMSTATE_FORCE_DWORD     = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DLIGHTSTATETYPE{
  D3DLIGHTSTATE_MATERIAL          = 1,
  D3DLIGHTSTATE_AMBIENT           = 2,
  D3DLIGHTSTATE_COLORMODEL        = 3,
  D3DLIGHTSTATE_FOGMODE           = 4,
  D3DLIGHTSTATE_FOGSTART          = 5,
  D3DLIGHTSTATE_FOGEND            = 6,
  D3DLIGHTSTATE_FOGDENSITY        = 7,
  D3DLIGHTSTATE_COLORVERTEX       = 8,
  D3DLIGHTSTATE_FORCE_DWORD         = 0x7fffffff, /* force 32-bit size enum */
};

enum D3DRENDERSTATETYPE{
  D3DRENDERSTATE_ANTIALIAS          = 2,    /* D3DANTIALIASMODE */
  D3DRENDERSTATE_TEXTUREPERSPECTIVE = 4,    /* TRUE for perspective correction */
  D3DRENDERSTATE_ZENABLE            = 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
  D3DRENDERSTATE_FILLMODE           = 8,    /* D3DFILL_MODE        */
  D3DRENDERSTATE_SHADEMODE          = 9,    /* D3DSHADEMODE */
  D3DRENDERSTATE_LINEPATTERN        = 10,   /* D3DLINEPATTERN */
  D3DRENDERSTATE_ZWRITEENABLE       = 14,   /* TRUE to enable z writes */
  D3DRENDERSTATE_ALPHATESTENABLE    = 15,   /* TRUE to enable alpha tests */
  D3DRENDERSTATE_LASTPIXEL          = 16,   /* TRUE for last-pixel on lines */
  D3DRENDERSTATE_SRCBLEND           = 19,   /* D3DBLEND */
  D3DRENDERSTATE_DESTBLEND          = 20,   /* D3DBLEND */
  D3DRENDERSTATE_CULLMODE           = 22,   /* D3DCULL */
  D3DRENDERSTATE_ZFUNC              = 23,   /* D3DCMPFUNC */
  D3DRENDERSTATE_ALPHAREF           = 24,   /* D3DFIXED */
  D3DRENDERSTATE_ALPHAFUNC          = 25,   /* D3DCMPFUNC */
  D3DRENDERSTATE_DITHERENABLE       = 26,   /* TRUE to enable dithering */
  D3DRENDERSTATE_ALPHABLENDENABLE   = 27,   /* TRUE to enable alpha blending */
  D3DRENDERSTATE_FOGENABLE          = 28,   /* TRUE to enable fog blending */
  D3DRENDERSTATE_SPECULARENABLE     = 29,   /* TRUE to enable specular */
  D3DRENDERSTATE_ZVISIBLE           = 30,   /* TRUE to enable z checking */
  D3DRENDERSTATE_STIPPLEDALPHA      = 33,   /* TRUE to enable stippled alpha (RGB device only) */
  D3DRENDERSTATE_FOGCOLOR           = 34,   /* D3DCOLOR */
  D3DRENDERSTATE_FOGTABLEMODE       = 35,   /* D3DFOGMODE */
  D3DRENDERSTATE_FOGSTART           = 36,   /* Fog start (for both vertex and pixel fog) */
  D3DRENDERSTATE_FOGEND             = 37,   /* Fog end      */
  D3DRENDERSTATE_FOGDENSITY         = 38,   /* Fog density  */
  D3DRENDERSTATE_EDGEANTIALIAS      = 40,   /* TRUE to enable edge antialiasing */
  D3DRENDERSTATE_COLORKEYENABLE     = 41,   /* TRUE to enable source colorkeyed textures */
  D3DRENDERSTATE_ZBIAS              = 47,   /* LONG Z bias */
  D3DRENDERSTATE_RANGEFOGENABLE     = 48,   /* Enables range-based fog */
  D3DRENDERSTATE_STENCILENABLE      = 52,   /* BOOL enable/disable stenciling */
  D3DRENDERSTATE_STENCILFAIL        = 53,   /* D3DSTENCILOP to do if stencil test fails */
  D3DRENDERSTATE_STENCILZFAIL       = 54,   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
  D3DRENDERSTATE_STENCILPASS        = 55,   /* D3DSTENCILOP to do if both stencil and Z tests pass */
  D3DRENDERSTATE_STENCILFUNC        = 56,   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
  D3DRENDERSTATE_STENCILREF         = 57,   /* Reference value used in stencil test */
  D3DRENDERSTATE_STENCILMASK        = 58,   /* Mask value used in stencil test */
  D3DRENDERSTATE_STENCILWRITEMASK   = 59,   /* Write mask applied to values written to stencil buffer */
  D3DRENDERSTATE_TEXTUREFACTOR      = 60,   /* D3DCOLOR used for multi-texture blend */
/*
 * 128 values [128, 255] are reserved for texture coordinate wrap flags.
 * These are constructed with the D3DWRAP_U and D3DWRAP_V macros. Using
 * a flags word preserves forward compatibility with texture coordinates
 * that are >2D.
 */
  D3DRENDERSTATE_WRAP0              = 128,  /* wrap for 1st texture coord. set */
  D3DRENDERSTATE_WRAP1              = 129,  /* wrap for 2nd texture coord. set */
  D3DRENDERSTATE_WRAP2              = 130,  /* wrap for 3rd texture coord. set */
  D3DRENDERSTATE_WRAP3              = 131,  /* wrap for 4th texture coord. set */
  D3DRENDERSTATE_WRAP4              = 132,  /* wrap for 5th texture coord. set */
  D3DRENDERSTATE_WRAP5              = 133,  /* wrap for 6th texture coord. set */
  D3DRENDERSTATE_WRAP6              = 134,  /* wrap for 7th texture coord. set */
  D3DRENDERSTATE_WRAP7              = 135,  /* wrap for 8th texture coord. set */
  D3DRENDERSTATE_CLIPPING            = 136,
  D3DRENDERSTATE_LIGHTING            = 137,
  D3DRENDERSTATE_EXTENTS             = 138,
  D3DRENDERSTATE_AMBIENT             = 139,
  D3DRENDERSTATE_FOGVERTEXMODE       = 140,
  D3DRENDERSTATE_COLORVERTEX         = 141,
  D3DRENDERSTATE_LOCALVIEWER         = 142,
  D3DRENDERSTATE_NORMALIZENORMALS    = 143,
  D3DRENDERSTATE_COLORKEYBLENDENABLE = 144,
  D3DRENDERSTATE_DIFFUSEMATERIALSOURCE    = 145,
  D3DRENDERSTATE_SPECULARMATERIALSOURCE   = 146,
  D3DRENDERSTATE_AMBIENTMATERIALSOURCE    = 147,
  D3DRENDERSTATE_EMISSIVEMATERIALSOURCE   = 148,
  D3DRENDERSTATE_VERTEXBLEND              = 151,
  D3DRENDERSTATE_CLIPPLANEENABLE          = 152,
// retired renderstates - not supported for DX7 interfaces
  D3DRENDERSTATE_TEXTUREHANDLE      = 1,    /* Texture handle for legacy interfaces (Texture,Texture2) */
  D3DRENDERSTATE_TEXTUREADDRESS     = 3,    /* D3DTEXTUREADDRESS  */
  D3DRENDERSTATE_WRAPU              = 5,    /* TRUE for wrapping in u */
  D3DRENDERSTATE_WRAPV              = 6,    /* TRUE for wrapping in v */
  D3DRENDERSTATE_MONOENABLE         = 11,   /* TRUE to enable mono rasterization */
  D3DRENDERSTATE_ROP2               = 12,   /* ROP2 */
  D3DRENDERSTATE_PLANEMASK          = 13,   /* DWORD physical plane mask */
  D3DRENDERSTATE_TEXTUREMAG         = 17,   /* D3DTEXTUREFILTER */
  D3DRENDERSTATE_TEXTUREMIN         = 18,   /* D3DTEXTUREFILTER */
  D3DRENDERSTATE_TEXTUREMAPBLEND    = 21,   /* D3DTEXTUREBLEND */
  D3DRENDERSTATE_SUBPIXEL           = 31,   /* TRUE to enable subpixel correction */
  D3DRENDERSTATE_SUBPIXELX          = 32,   /* TRUE to enable correction in X only */
  D3DRENDERSTATE_STIPPLEENABLE      = 39,   /* TRUE to enable stippling */
  D3DRENDERSTATE_BORDERCOLOR        = 43,   /* Border color for texturing w/border */
  D3DRENDERSTATE_TEXTUREADDRESSU    = 44,   /* Texture addressing mode for U coordinate */
  D3DRENDERSTATE_TEXTUREADDRESSV    = 45,   /* Texture addressing mode for V coordinate */
  D3DRENDERSTATE_MIPMAPLODBIAS      = 46,   /* D3DVALUE Mipmap LOD bias */
  D3DRENDERSTATE_ANISOTROPY         = 49,   /* Max. anisotropy. 1 = no anisotropy */
  D3DRENDERSTATE_FLUSHBATCH         = 50,   /* Explicit flush for DP batching (DX5 Only) */
  D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT=51, /* BOOL enable sort-independent transparency */
  D3DRENDERSTATE_STIPPLEPATTERN00   = 64,   /* Stipple pattern 01...  */
  D3DRENDERSTATE_STIPPLEPATTERN01   = 65,
  D3DRENDERSTATE_STIPPLEPATTERN02   = 66,
  D3DRENDERSTATE_STIPPLEPATTERN03   = 67,
  D3DRENDERSTATE_STIPPLEPATTERN04   = 68,
  D3DRENDERSTATE_STIPPLEPATTERN05   = 69,
  D3DRENDERSTATE_STIPPLEPATTERN06   = 70,
  D3DRENDERSTATE_STIPPLEPATTERN07   = 71,
  D3DRENDERSTATE_STIPPLEPATTERN08   = 72,
  D3DRENDERSTATE_STIPPLEPATTERN09   = 73,
  D3DRENDERSTATE_STIPPLEPATTERN10   = 74,
  D3DRENDERSTATE_STIPPLEPATTERN11   = 75,
  D3DRENDERSTATE_STIPPLEPATTERN12   = 76,
  D3DRENDERSTATE_STIPPLEPATTERN13   = 77,
  D3DRENDERSTATE_STIPPLEPATTERN14   = 78,
  D3DRENDERSTATE_STIPPLEPATTERN15   = 79,
  D3DRENDERSTATE_STIPPLEPATTERN16   = 80,
  D3DRENDERSTATE_STIPPLEPATTERN17   = 81,
  D3DRENDERSTATE_STIPPLEPATTERN18   = 82,
  D3DRENDERSTATE_STIPPLEPATTERN19   = 83,
  D3DRENDERSTATE_STIPPLEPATTERN20   = 84,
  D3DRENDERSTATE_STIPPLEPATTERN21   = 85,
  D3DRENDERSTATE_STIPPLEPATTERN22   = 86,
  D3DRENDERSTATE_STIPPLEPATTERN23   = 87,
  D3DRENDERSTATE_STIPPLEPATTERN24   = 88,
  D3DRENDERSTATE_STIPPLEPATTERN25   = 89,
  D3DRENDERSTATE_STIPPLEPATTERN26   = 90,
  D3DRENDERSTATE_STIPPLEPATTERN27   = 91,
  D3DRENDERSTATE_STIPPLEPATTERN28   = 92,
  D3DRENDERSTATE_STIPPLEPATTERN29   = 93,
  D3DRENDERSTATE_STIPPLEPATTERN30   = 94,
  D3DRENDERSTATE_STIPPLEPATTERN31   = 95,
// retired renderstate names - the values are still used under new naming conventions
  D3DRENDERSTATE_FOGTABLESTART      = 36,   /* Fog table start    */
  D3DRENDERSTATE_FOGTABLEEND        = 37,   /* Fog table end      */
  D3DRENDERSTATE_FOGTABLEDENSITY    = 38,   /* Fog table density  */
  D3DRENDERSTATE_FORCE_DWORD        = 0x7fffffff, /* force 32-bit size enum */
};

// Values for material source
enum D3DMATERIALCOLORSOURCE{
  D3DMCS_MATERIAL = 0,                // Color from material is used
  D3DMCS_COLOR1   = 1,                // Diffuse vertex color is used
  D3DMCS_COLOR2   = 2,                // Specular vertex color is used
  D3DMCS_FORCE_DWORD = 0x7fffffff,    // force 32-bit size enum
};

// For back-compatibility with legacy compilations
#define D3DRENDERSTATE_BLENDENABLE      D3DRENDERSTATE_ALPHABLENDENABLE

// Bias to apply to the texture coordinate set to apply a wrap to.
#define D3DRENDERSTATE_WRAPBIAS                 128UL

/* Flags to construct the WRAP render states */
#define D3DWRAP_U   0x00000001L
#define D3DWRAP_V   0x00000002L

/* Flags to construct the WRAP render states for 1D thru 4D texture coordinates */
#define D3DWRAPCOORD_0   0x00000001L    // same as D3DWRAP_U
#define D3DWRAPCOORD_1   0x00000002L    // same as D3DWRAP_V
#define D3DWRAPCOORD_2   0x00000004L
#define D3DWRAPCOORD_3   0x00000008L

#define D3DRENDERSTATE_STIPPLEPATTERN(y) D3DRENDERSTATE_STIPPLEPATTERN00+y

struct D3DSTATE {
  union {
    dword   dtstTransformStateType;
    dword   dlstLightStateType;
    dword  drstRenderStateType;
  };
  union {
    DWORD           dwArg[1];
    D3DVALUE        dvArg[1];
  };
};

/*
 * Operation used to load matrices
 * hDstMat = hSrcMat
 */
struct D3DMATRIXLOAD {
  D3DMATRIXHANDLE hDestMatrix;   /* Destination matrix */
  D3DMATRIXHANDLE hSrcMatrix;   /* Source matrix */
};

/*
 * Operation used to multiply matrices
 * hDstMat = hSrcMat1 * hSrcMat2
 */
struct D3DMATRIXMULTIPLY {
  D3DMATRIXHANDLE hDestMatrix;   /* Destination matrix */
  D3DMATRIXHANDLE hSrcMatrix1;  /* First source matrix */
  D3DMATRIXHANDLE hSrcMatrix2;  /* Second source matrix */
};

/*
 * Operation used to transform and light vertices.
 */
struct D3DPROCESSVERTICES {
  DWORD        dwFlags;    /* Do we transform or light or just copy? */
  WORD         wStart;     /* Index to first vertex in source */
  WORD         wDest;      /* Index to first vertex in local buffer */
  DWORD        dwCount;    /* Number of vertices to be processed */
  DWORD    dwReserved; /* Must be zero */
};

#define D3DPROCESSVERTICES_TRANSFORMLIGHT   0x00000000L
#define D3DPROCESSVERTICES_TRANSFORM        0x00000001L
#define D3DPROCESSVERTICES_COPY         0x00000002L
#define D3DPROCESSVERTICES_OPMASK       0x00000007L
#define D3DPROCESSVERTICES_UPDATEEXTENTS    0x00000008L
#define D3DPROCESSVERTICES_NOCOLOR      0x00000010L

#if(DIRECT3D_VERSION >= 0x0600)

/*
 * State enumerants for per-stage texture processing.
 */
enum D3DTEXTURESTAGESTATETYPE{
  D3DTSS_COLOROP        =  1, /* D3DTEXTUREOP - per-stage blending controls for color channels */
  D3DTSS_COLORARG1      =  2, /* D3DTA_* (texture arg) */
  D3DTSS_COLORARG2      =  3, /* D3DTA_* (texture arg) */
  D3DTSS_ALPHAOP        =  4, /* D3DTEXTUREOP - per-stage blending controls for alpha channel */
  D3DTSS_ALPHAARG1      =  5, /* D3DTA_* (texture arg) */
  D3DTSS_ALPHAARG2      =  6, /* D3DTA_* (texture arg) */
  D3DTSS_BUMPENVMAT00   =  7, /* D3DVALUE (bump mapping matrix) */
  D3DTSS_BUMPENVMAT01   =  8, /* D3DVALUE (bump mapping matrix) */
  D3DTSS_BUMPENVMAT10   =  9, /* D3DVALUE (bump mapping matrix) */
  D3DTSS_BUMPENVMAT11   = 10, /* D3DVALUE (bump mapping matrix) */
  D3DTSS_TEXCOORDINDEX  = 11, /* identifies which set of texture coordinates index this texture */
  D3DTSS_ADDRESS        = 12, /* D3DTEXTUREADDRESS for both coordinates */
  D3DTSS_ADDRESSU       = 13, /* D3DTEXTUREADDRESS for U coordinate */
  D3DTSS_ADDRESSV       = 14, /* D3DTEXTUREADDRESS for V coordinate */
  D3DTSS_BORDERCOLOR    = 15, /* D3DCOLOR */
  D3DTSS_MAGFILTER      = 16, /* D3DTEXTUREMAGFILTER filter to use for magnification */
  D3DTSS_MINFILTER      = 17, /* D3DTEXTUREMINFILTER filter to use for minification */
  D3DTSS_MIPFILTER      = 18, /* D3DTEXTUREMIPFILTER filter to use between mipmaps during minification */
  D3DTSS_MIPMAPLODBIAS  = 19, /* D3DVALUE Mipmap LOD bias */
  D3DTSS_MAXMIPLEVEL    = 20, /* DWORD 0..(n-1) LOD index of largest map to use (0 == largest) */
  D3DTSS_MAXANISOTROPY  = 21, /* DWORD maximum anisotropy */
  D3DTSS_BUMPENVLSCALE  = 22, /* D3DVALUE scale for bump map luminance */
  D3DTSS_BUMPENVLOFFSET = 23, /* D3DVALUE offset for bump map luminance */
  D3DTSS_TEXTURETRANSFORMFLAGS = 24, /* D3DTEXTURETRANSFORMFLAGS controls texture transform */
  D3DTSS_FORCE_DWORD   = 0x7fffffff, /* force 32-bit size enum */
};

// Values, used with D3DTSS_TEXCOORDINDEX, to specify that the vertex data(position
// and normal in the camera space) should be taken as texture coordinates
// Low 16 bits are used to specify texture coordinate index, to take the WRAP mode from
#define D3DTSS_TCI_PASSTHRU                             0x00000000
#define D3DTSS_TCI_CAMERASPACENORMAL                    0x00010000
#define D3DTSS_TCI_CAMERASPACEPOSITION                  0x00020000
#define D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR          0x00030000

/*
 * Enumerations for COLOROP and ALPHAOP texture blending operations set in
 * texture processing stage controls in D3DRENDERSTATE.
 */
enum D3DTEXTUREOP{
// Control
  D3DTOP_DISABLE    = 1,      // disables stage
  D3DTOP_SELECTARG1 = 2,      // the default
  D3DTOP_SELECTARG2 = 3,
// Modulate
  D3DTOP_MODULATE   = 4,      // multiply args together
  D3DTOP_MODULATE2X = 5,      // multiply and  1 bit
  D3DTOP_MODULATE4X = 6,      // multiply and  2 bits
// Add
  D3DTOP_ADD          =  7,   // add arguments together
  D3DTOP_ADDSIGNED    =  8,   // add with -0.5 bias
  D3DTOP_ADDSIGNED2X  =  9,   // as above but left  1 bit
  D3DTOP_SUBTRACT     = 10,   // Arg1 - Arg2, with no saturation
  D3DTOP_ADDSMOOTH    = 11,   // add 2 args, subtract product
                              // Arg1 + Arg2 - Arg1*Arg2
                              // = Arg1 + (1-Arg1)*Arg2
// Linear alpha blend: Arg1*(Alpha) + Arg2*(1-Alpha)
  D3DTOP_BLENDDIFFUSEALPHA    = 12, // iterated alpha
  D3DTOP_BLENDTEXTUREALPHA    = 13, // texture alpha
  D3DTOP_BLENDFACTORALPHA     = 14, // alpha from D3DRENDERSTATE_TEXTUREFACTOR
  // Linear alpha blend with pre-multiplied arg1 input: Arg1 + Arg2*(1-Alpha)
  D3DTOP_BLENDTEXTUREALPHAPM  = 15, // texture alpha
  D3DTOP_BLENDCURRENTALPHA    = 16, // by alpha of current color
// Specular mapping
  D3DTOP_PREMODULATE            = 17,     // modulate with next texture before use
  D3DTOP_MODULATEALPHA_ADDCOLOR = 18,     // Arg1.RGB + Arg1.A*Arg2.RGB
                                          // COLOROP only
  D3DTOP_MODULATECOLOR_ADDALPHA = 19,     // Arg1.RGB*Arg2.RGB + Arg1.A
                                          // COLOROP only
  D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,  // (1-Arg1.A)*Arg2.RGB + Arg1.RGB
                                          // COLOROP only
  D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,  // (1-Arg1.RGB)*Arg2.RGB + Arg1.A
                                          // COLOROP only
// Bump mapping
  D3DTOP_BUMPENVMAP           = 22, // per pixel env map perturbation
  D3DTOP_BUMPENVMAPLUMINANCE  = 23, // with luminance channel
  // This can do either diffuse or specular bump mapping with correct input.
  // Performs the function (Arg1.R*Arg2.R + Arg1.G*Arg2.G + Arg1.B*Arg2.B)
  // where each component has been scaled and offset to make it signed.
  // The result is replicated into all four (including alpha) channels.
  // This is a valid COLOROP only.
  D3DTOP_DOTPRODUCT3          = 24,
  D3DTOP_FORCE_DWORD = 0x7fffffff,
};

/*
 * Values for COLORARG1,2 and ALPHAARG1,2 texture blending operations
 * set in texture processing stage controls in D3DRENDERSTATE.
 */
#define D3DTA_SELECTMASK        0x0000000f  // mask for arg selector
#define D3DTA_DIFFUSE           0x00000000  // select diffuse color
#define D3DTA_CURRENT           0x00000001  // select result of previous stage
#define D3DTA_TEXTURE           0x00000002  // select texture color
#define D3DTA_TFACTOR           0x00000003  // select RENDERSTATE_TEXTUREFACTOR
#define D3DTA_SPECULAR          0x00000004  // select specular color
#define D3DTA_COMPLEMENT        0x00000010  // take 1.0 - x
#define D3DTA_ALPHAREPLICATE    0x00000020  // replicate alpha to color components

/*
 *  IDirect3DTexture2 State Filter Types
 */
enum D3DTEXTUREMAGFILTER{
  D3DTFG_POINT        = 1,    // nearest
  D3DTFG_LINEAR       = 2,    // linear interpolation
  D3DTFG_FLATCUBIC    = 3,    // cubic
  D3DTFG_GAUSSIANCUBIC = 4,   // different cubic kernel
  D3DTFG_ANISOTROPIC  = 5,    //
  D3DTFG_FORCE_DWORD  = 0x7fffffff,   // force 32-bit size enum
};

enum D3DTEXTUREMINFILTER
{
  D3DTFN_POINT        = 1,    // nearest
  D3DTFN_LINEAR       = 2,    // linear interpolation
  D3DTFN_ANISOTROPIC  = 3,    //
  D3DTFN_FORCE_DWORD  = 0x7fffffff,   // force 32-bit size enum
};

enum D3DTEXTUREMIPFILTER
{
  D3DTFP_NONE         = 1,    // mipmapping disabled (use MAG filter)
  D3DTFP_POINT        = 2,    // nearest
  D3DTFP_LINEAR       = 3,    // linear interpolation
  D3DTFP_FORCE_DWORD  = 0x7fffffff,   // force 32-bit size enum
};

#endif /* DIRECT3D_VERSION >= 0x0600 */

/*
 * Triangle flags
 */

/*
 * Tri strip and fan flags.
 * START loads all three vertices
 * EVEN and ODD load just v3 with even or odd culling
 * START_FLAT contains a count from 0 to 29 that allows the
 * whole strip or fan to be culled in one hit.
 * e.g. for a quad len = 1
 */
#define D3DTRIFLAG_START            0x00000000L
#define D3DTRIFLAG_STARTFLAT(len) len     /* 0 < len < 30 */
#define D3DTRIFLAG_ODD              0x0000001eL
#define D3DTRIFLAG_EVEN             0x0000001fL

/*
 * Triangle edge flags
 * enable edges for wireframe or antialiasing
 */
#define D3DTRIFLAG_EDGEENABLE1          0x00000100L /* v0-v1 edge */
#define D3DTRIFLAG_EDGEENABLE2          0x00000200L /* v1-v2 edge */
#define D3DTRIFLAG_EDGEENABLE3          0x00000400L /* v2-v0 edge */
#define D3DTRIFLAG_EDGEENABLETRIANGLE \
        D3DTRIFLAG_EDGEENABLE1|D3DTRIFLAG_EDGEENABLE2|D3DTRIFLAG_EDGEENABLE3

/*
 * Primitive structures and related defines.  Vertex offsets are to types
 * D3DVERTEX, D3DLVERTEX, or D3DTLVERTEX.
 */

/*
 * Triangle list primitive structure
 */
struct D3DTRIANGLE {
  union {
    WORD    v1;            /* Vertex indices */
    WORD    wV1;
  };
  union {
    WORD    v2;
    WORD    wV2;
  };
  union {
    WORD    v3;
    WORD    wV3;
  };
    WORD        wFlags;       /* Edge (and other) flags */
};

/*
 * Line list structure.
 * The instruction count defines the number of line segments.
 */
struct D3DLINE {
  union {
    WORD    v1;            /* Vertex indices */
    WORD    wV1;
  };
  union {
    WORD    v2;
    WORD    wV2;
  };
};

/*
 * Span structure
 * Spans join a list of points with the same y value.
 * If the y value changes, a new span is started.
 */
struct D3DSPAN {
  WORD    wCount; /* Number of spans */
  WORD    wFirst; /* Index to first vertex */
};

/*
 * Point structure
 */
struct D3DPOINT {
  WORD    wCount;     /* number of points     */
  WORD    wFirst;     /* index to first vertex    */
};

/*
 * Forward branch structure.
 * Mask is logically anded with the driver status mask
 * if the result equals 'value', the branch is taken.
 */
struct D3DBRANCH {
  DWORD   dwMask;     /* Bitmask against D3D status */
  DWORD   dwValue;
  BOOL    bNegate;        /* TRUE to negate comparison */
  DWORD   dwOffset;   /* How far to branch forward (0 for exit)*/
};

/*
 * Status used for set status instruction.
 * The D3D status is initialised on device creation
 * and is modified by all execute calls.
 */
struct D3DSTATUS {
  DWORD       dwFlags;    /* Do we set extents or status */
  DWORD   dwStatus;   /* D3D status */
  D3DRECT drExtent;
};

#define D3DSETSTATUS_STATUS     0x00000001L
#define D3DSETSTATUS_EXTENTS        0x00000002L
#define D3DSETSTATUS_ALL    D3DSETSTATUS_STATUS | D3DSETSTATUS_EXTENTS

#if(DIRECT3D_VERSION >= 0x0500)
struct D3DCLIPSTATUS {
  DWORD dwFlags; /* Do we set 2d extents, 3D extents or status */
  DWORD dwStatus; /* Clip status */
  float minx, maxx; /* X extents */
  float miny, maxy; /* Y extents */
  float minz, maxz; /* Z extents */
};

#define D3DCLIPSTATUS_STATUS        0x00000001L
#define D3DCLIPSTATUS_EXTENTS2      0x00000002L
#define D3DCLIPSTATUS_EXTENTS3      0x00000004L

#endif /* DIRECT3D_VERSION >= 0x0500 */
/*
 * Statistics structure
 */
struct D3DSTATS {
  DWORD        dwSize;
  DWORD        dwTrianglesDrawn;
  DWORD        dwLinesDrawn;
  DWORD        dwPointsDrawn;
  DWORD        dwSpansDrawn;
  DWORD        dwVerticesProcessed;
};

/*
 * Execute options.
 * When calling using D3DEXECUTE_UNCLIPPED all the primitives
 * inside the buffer must be contained within the viewport.
 */
#define D3DEXECUTE_CLIPPED       0x00000001l
#define D3DEXECUTE_UNCLIPPED     0x00000002l

struct D3DEXECUTEDATA {
  DWORD       dwSize;
  DWORD       dwVertexOffset;
  DWORD       dwVertexCount;
  DWORD       dwInstructionOffset;
  DWORD       dwInstructionLength;
  DWORD       dwHVertexOffset;
  D3DSTATUS   dsStatus;   /* Status after execute */
};

/*
 * Palette flags.
 * This are or'ed with the peFlags in the PALETTEENTRYs passed to DirectDraw.
 */
#define D3DPAL_FREE 0x00    /* Renderer may use this entry freely */
#define D3DPAL_READONLY 0x40    /* Renderer may not set this entry */
#define D3DPAL_RESERVED 0x80    /* Renderer may not use this entry */

#if(DIRECT3D_VERSION >= 0x0600)

struct D3DVERTEXBUFFERDESC {
  DWORD dwSize;
  DWORD dwCaps;
  DWORD dwFVF;
  DWORD dwNumVertices;
};

#define D3DVBCAPS_SYSTEMMEMORY      0x00000800l
#define D3DVBCAPS_WRITEONLY         0x00010000l
#define D3DVBCAPS_OPTIMIZED         0x80000000l
#define D3DVBCAPS_DONOTCLIP         0x00000001l

/* Vertex Operations for ProcessVertices */
#define D3DVOP_LIGHT       1 << 10
#define D3DVOP_TRANSFORM   1
#define D3DVOP_CLIP        4
#define D3DVOP_EXTENTS     8

/* The maximum number of vertices user can pass to any d3d
   drawing function or to create vertex buffer with
*/
#define D3DMAXNUMVERTICES    1<<16-1
/* The maximum number of primitives user can pass to any d3d
   drawing function.
*/
#define D3DMAXNUMPRIMITIVES  1<<16-1

/* Bits for dwFlags in ProcessVertices call */
#define D3DPV_DONOTCOPYDATA 1
//-------------------------------------------------------------------

// Flexible vertex format bits
#define D3DFVF_RESERVED0        0x001
#define D3DFVF_POSITION_MASK    0x00E
#define D3DFVF_XYZ              0x002
#define D3DFVF_XYZRHW           0x004
#define D3DFVF_XYZB1            0x006
#define D3DFVF_XYZB2            0x008
#define D3DFVF_XYZB3            0x00a
#define D3DFVF_XYZB4            0x00c
#define D3DFVF_XYZB5            0x00e
#define D3DFVF_NORMAL           0x010
#define D3DFVF_RESERVED1        0x020
#define D3DFVF_DIFFUSE          0x040
#define D3DFVF_SPECULAR         0x080

#define D3DFVF_TEXCOUNT_MASK    0xf00
#define D3DFVF_TEXCOUNT_SHIFT   8
#define D3DFVF_TEX0             0x000
#define D3DFVF_TEX1             0x100
#define D3DFVF_TEX2             0x200
#define D3DFVF_TEX3             0x300
#define D3DFVF_TEX4             0x400
#define D3DFVF_TEX5             0x500
#define D3DFVF_TEX6             0x600
#define D3DFVF_TEX7             0x700
#define D3DFVF_TEX8             0x800

#define D3DFVF_RESERVED2        0xf000  // 4 reserved bits

#define D3DFVF_VERTEX D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1
#define D3DFVF_LVERTEX D3DFVF_XYZ|D3DFVF_RESERVED1|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEX1
#define D3DFVF_TLVERTEX D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_SPECULAR|D3DFVF_TEX1

struct D3DDP_PTRSTRIDE
{
  LPVOID lpvData;
  DWORD  dwStride;
};

#define D3DDP_MAXTEXCOORD 8

struct D3DDRAWPRIMITIVESTRIDEDDATA
{
  D3DDP_PTRSTRIDE position;
  D3DDP_PTRSTRIDE normal;
  D3DDP_PTRSTRIDE diffuse;
  D3DDP_PTRSTRIDE specular;
  D3DDP_PTRSTRIDE textureCoords[D3DDP_MAXTEXCOORD];
};
//---------------------------------------------------------------------
// ComputeSphereVisibility return values
#define D3DVIS_INSIDE_FRUSTUM       0
#define D3DVIS_INTERSECT_FRUSTUM    1
#define D3DVIS_OUTSIDE_FRUSTUM      2
#define D3DVIS_INSIDE_LEFT          0
#define D3DVIS_INTERSECT_LEFT       1 << 2
#define D3DVIS_OUTSIDE_LEFT         2 << 2
#define D3DVIS_INSIDE_RIGHT         0
#define D3DVIS_INTERSECT_RIGHT      1 << 4
#define D3DVIS_OUTSIDE_RIGHT        2 << 4
#define D3DVIS_INSIDE_TOP           0
#define D3DVIS_INTERSECT_TOP        1 << 6
#define D3DVIS_OUTSIDE_TOP          2 << 6
#define D3DVIS_INSIDE_BOTTOM        0
#define D3DVIS_INTERSECT_BOTTOM     1 << 8
#define D3DVIS_OUTSIDE_BOTTOM       2 << 8
#define D3DVIS_INSIDE_NEAR          0
#define D3DVIS_INTERSECT_NEAR       1 << 10
#define D3DVIS_OUTSIDE_NEAR         2 << 10
#define D3DVIS_INSIDE_FAR           0
#define D3DVIS_INTERSECT_FAR        1 << 12
#define D3DVIS_OUTSIDE_FAR          2 << 12

#define D3DVIS_MASK_FRUSTUM         3 << 0
#define D3DVIS_MASK_LEFT            3 << 2
#define D3DVIS_MASK_RIGHT           3 << 4
#define D3DVIS_MASK_TOP             3 << 6
#define D3DVIS_MASK_BOTTOM          3 << 8
#define D3DVIS_MASK_NEAR            3 << 10
#define D3DVIS_MASK_FAR             3 << 12

#endif /* DIRECT3D_VERSION >= 0x0600 */

#if(DIRECT3D_VERSION >= 0x0700)

// To be used with GetInfo()
#define D3DDEVINFOID_TEXTUREMANAGER    1
#define D3DDEVINFOID_D3DTEXTUREMANAGER 2
#define D3DDEVINFOID_TEXTURING         3

enum D3DSTATEBLOCKTYPE{
  D3DSBT_ALL           = 1, // capture all state
  D3DSBT_PIXELSTATE    = 2, // capture pixel state
  D3DSBT_VERTEXSTATE   = 3, // capture vertex state
  D3DSBT_FORCE_DWORD   = 0xffffffff
};

// The D3DVERTEXBLENDFLAGS type is used with D3DRENDERSTATE_VERTEXBLEND state.
enum D3DVERTEXBLENDFLAGS{
  D3DVBLEND_DISABLE  = 0, // Disable vertex blending
  D3DVBLEND_1WEIGHT  = 1, // blend between 2 matrices
  D3DVBLEND_2WEIGHTS = 2, // blend between 3 matrices
  D3DVBLEND_3WEIGHTS = 3, // blend between 4 matrices
};

enum D3DTEXTURETRANSFORMFLAGS{
  D3DTTFF_DISABLE         = 0,    // texture coordinates are passed directly
  D3DTTFF_COUNT1          = 1,    // rasterizer should expect 1-D texture coords
  D3DTTFF_COUNT2          = 2,    // rasterizer should expect 2-D texture coords
  D3DTTFF_COUNT3          = 3,    // rasterizer should expect 3-D texture coords
  D3DTTFF_COUNT4          = 4,    // rasterizer should expect 4-D texture coords
  D3DTTFF_PROJECTED       = 256,  // texcoords to be divided by COUNTth element
  D3DTTFF_FORCE_DWORD     = 0x7fffffff,
};

// Macros to set texture coordinate format bits in the FVF id

#define D3DFVF_TEXTUREFORMAT2 0         // Two floating point values
#define D3DFVF_TEXTUREFORMAT1 3         // One floating point value
#define D3DFVF_TEXTUREFORMAT3 1         // Three floating point values
#define D3DFVF_TEXTUREFORMAT4 2         // Four floating point values

//#define D3DFVF_TEXCOORDSIZE3(CoordIndex) D3DFVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16))
:dword D3DFVF_TEXCOORDSIZE3(ECX)
{
	ECX=ECX*2+16;
	return D3DFVF_TEXTUREFORMAT3<<ECX;
}
#define D3DFVF_TEXCOORDSIZE2(CoordIndex) D3DFVF_TEXTUREFORMAT2
//#define D3DFVF_TEXCOORDSIZE4(CoordIndex) D3DFVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16))
:dword D3DFVF_TEXCOORDSIZE4(ECX)
{
	ECX=ECX*2+16;
	return D3DFVF_TEXTUREFORMAT4<<ECX;
}
//#define D3DFVF_TEXCOORDSIZE1(CoordIndex) D3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16))
:dword D3DFVF_TEXCOORDSIZE1(ECX)
{
	ECX=ECX*2+16;
	return D3DFVF_TEXTUREFORMAT1<<ECX;
}

#endif /* DIRECT3D_VERSION >= 0x0700 */

#pragma pack()

#endif /* _D3DTYPES_H_ */
