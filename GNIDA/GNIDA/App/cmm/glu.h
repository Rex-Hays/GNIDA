/*++ BUILD Version: 0004    // Increment this if a change has global effects
Copyright (c) 1985-95, Microsoft Corporation
Module Name:
    glu.h
Abstract:
    Procedure declarations, constant definitions and macros for the OpenGL
    Utility Library.
--*/

#ifndef __glu_h__
#ifndef __GLU_H__

#define __glu_h__
#define __GLU_H__

#include <gl.h>

/*
** Copyright 1991-1993, Silicon Graphics, Inc.
** All Rights Reserved.
**
** This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
** the contents of this file may not be disclosed to third parties, copied or
** duplicated in any form, in whole or in part, without the prior written
** permission of Silicon Graphics, Inc.
**
** RESTRICTED RIGHTS LEGEND:
** Use, duplication or disclosure by the Government is subject to restrictions
** as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
** and Computer Software clause at DFARS 252.227-7013, and/or in similar or
** successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
** rights reserved under the Copyright Laws of the United States.
*/

/*
** Return the error string associated with a particular error code.
** This will return 0 for an invalid error code.
**
** The generic function prototype that can be compiled for ANSI or Unicode
** is defined as follows:
**
** LPCTSTR APIENTRY gluErrorStringWIN (GLenum errCode);
*/
#ifdef UNICODE
#define gluErrorStringWIN(errCode) gluErrorUnicodeStringEXT(errCode)
#else
#define gluErrorStringWIN(errCode) gluErrorString(errCode)
#endif

extern WINAPI "GLU32.DLL"{
	dword gluErrorString(GLenum errCode);
	dword gluErrorUnicodeStringEXT(GLenum errCode);
	dword gluGetString(GLenum name);
	void gluOrtho2D(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top);
	void gluPerspective(GLdouble fovy,GLdouble aspect,GLdouble zNear,GLdouble zFar);
//	void gluPickMatrix(GLdouble x,GLdouble y,GLdouble width,GLdouble height,GLint viewport[4]);
	void gluLookAt(GLdouble eyex,GLdouble eyey,GLdouble eyez,GLdouble centerx,GLdouble centery,
		GLdouble centerz,GLdouble upx,GLdouble upy,GLdouble upz);
/*	int gluProject(GLdouble objx,GLdouble objy,GLdouble objz,GLdouble modelMatrix[16],
		GLdouble projMatrix[16],GLint viewport[4],dword winx,dword winy,dword winz);
	int gluUnProject(GLdouble winx,GLdouble winy,GLdouble winz,GLdouble modelMatrix[16],
		GLdouble projMatrix[16],GLint viewport[4],dword objx,dword objy,dword objz);
*/
	int gluScaleImage(GLenum format,GLint widthin,GLint heightin,GLenum typein,
		dword datain,GLint widthout,GLint heightout,GLenum typeout,dword dataout);
	int gluBuild1DMipmaps(GLenum target,GLint components,GLint width,GLenum format,
		GLenum type,dword data);
	int gluBuild2DMipmaps(GLenum target,GLint components,GLint width,GLint height,
		GLenum format,GLenum type,dword data);
	dword gluNewQuadric(void);
	void gluDeleteQuadric(dword state);
	void gluQuadricNormals(dword quadObject,GLenum normals);
	void gluQuadricTexture(dword quadObject,GLboolean textureCoords);
	void gluQuadricOrientation(dword quadObject,GLenum orientation);
	void gluQuadricDrawStyle(dword quadObject,GLenum drawStyle);
	void gluCylinder(dword qobj,GLdouble baseRadius,GLdouble topRadius,GLdouble height,
		GLint slices,GLint stacks);
	void gluDisk(dword qobj,GLdouble innerRadius,GLdouble outerRadius,GLint slices,GLint loops);
	void gluPartialDisk(dword qobj,GLdouble innerRadius,GLdouble outerRadius,
		GLint slices,GLint loops,GLdouble startAngle,GLdouble sweepAngle);
	void gluSphere(dword qobj,GLdouble radius,GLint slices,GLint stacks);
	void gluQuadricCallback(dword qobj,GLenum which,dword fn);
	dword gluNewTess(void);
	void gluDeleteTess(dword tess);
	void gluTessBeginPolygon(dword tess,dword polygon_data);
	void gluTessBeginContour(dword tess);
//	void gluTessVertex(dword tess,GLdouble coords[3],dword data);
	void gluTessEndContour(dword tess);
	void gluTessEndPolygon(dword tess);
	void gluTessProperty(dword tess,GLenum which,GLdouble value );
	void gluTessNormal(dword tess,GLdouble x,GLdouble y,GLdouble z);
	void gluTessCallback(dword tess,GLenum which,dword fn);
	void gluGetTessProperty(dword tess,GLenum which,dword value);
	dword gluNewNurbsRenderer(void);
	void gluDeleteNurbsRenderer(dword nobj);
	void gluBeginSurface(dword nobj);
	void gluBeginCurve(dword nobj);
	void gluEndCurve(dword nobj);
	void gluEndSurface(dword nobj);
	void gluBeginTrim(dword nobj);
	void gluEndTrim(dword nobj);
	void gluPwlCurve(dword nobj,GLint count,dword array,GLint stride,GLenum type);
	void gluNurbsCurve(dword nobj,GLint nknots,dword knot,GLint stride,dword ctlarray,
		GLint order,GLenum type);
	void gluNurbsSurface(dword nobj,GLint sknot_count,dword sknot,GLint tknot_count,
		dword tknot,GLint s_stride,GLint t_stride,dword ctlarray,GLint sorder,
		GLint torder,GLenum type);
//	void gluLoadSamplingMatrices(dword nobj,GLfloat modelMatrix[16],GLfloat projMatrix[16],GLint viewport[4]);
	void gluNurbsProperty(dword nobj,GLenum property,GLfloat value);
	void gluGetNurbsProperty(dword nobj,GLenum property,dword value);
	void gluNurbsCallback(dword nobj,GLenum which,dword fn);
	void gluBeginPolygon(dword tess);
	void gluNextContour(dword tess,GLenum type);
	void gluEndPolygon(dword tess);
}

/* Version */
#define GLU_VERSION_1_1                 1
#define GLU_VERSION_1_2                 1

/* Errors: (return value 0 = no error) */
#define GLU_INVALID_ENUM        100900
#define GLU_INVALID_VALUE       100901
#define GLU_OUT_OF_MEMORY       100902
#define GLU_INCOMPATIBLE_GL_VERSION     100903

/* StringName */
#define GLU_VERSION             100800
#define GLU_EXTENSIONS          100801

/* Boolean */
#define GLU_TRUE                GL_TRUE
#define GLU_FALSE               GL_FALSE

/****           Quadric constants               ****/

/* QuadricNormal */
#define GLU_SMOOTH              100000
#define GLU_FLAT                100001
#define GLU_NONE                100002

/* QuadricDrawStyle */
#define GLU_POINT               100010
#define GLU_LINE                100011
#define GLU_FILL                100012
#define GLU_SILHOUETTE          100013

/* QuadricOrientation */
#define GLU_OUTSIDE             100020
#define GLU_INSIDE              100021

/****           Tesselation constants           ****/

#define GLU_TESS_MAX_COORD              1.0e150

/* TessProperty */
#define GLU_TESS_WINDING_RULE           100140
#define GLU_TESS_BOUNDARY_ONLY          100141
#define GLU_TESS_TOLERANCE              100142

/* TessWinding */
#define GLU_TESS_WINDING_ODD            100130
#define GLU_TESS_WINDING_NONZERO        100131
#define GLU_TESS_WINDING_POSITIVE       100132
#define GLU_TESS_WINDING_NEGATIVE       100133
#define GLU_TESS_WINDING_ABS_GEQ_TWO    100134

/* TessCallback */
#define GLU_TESS_BEGIN          100100  /* void (CALLBACK*)(GLenum    type)  */
#define GLU_TESS_VERTEX         100101  /* void (CALLBACK*)(void      *data) */
#define GLU_TESS_END            100102  /* void (CALLBACK*)(void)            */
#define GLU_TESS_ERROR          100103  /* void (CALLBACK*)(GLenum    errno) */
#define GLU_TESS_EDGE_FLAG      100104  /* void (CALLBACK*)(GLboolean boundaryEdge)  */
#define GLU_TESS_COMBINE        100105  /* void (CALLBACK*)(GLdouble  coords[3],
                                                            void      *data[4],
                                                            GLfloat   weight[4],
                                                            void      **dataOut)     */
#define GLU_TESS_BEGIN_DATA     100106  /* void (CALLBACK*)(GLenum    type,
                                                            void      *polygon_data) */
#define GLU_TESS_VERTEX_DATA    100107  /* void (CALLBACK*)(void      *data,
                                                            void      *polygon_data) */
#define GLU_TESS_END_DATA       100108  /* void (CALLBACK*)(void      *polygon_data) */
#define GLU_TESS_ERROR_DATA     100109  /* void (CALLBACK*)(GLenum    errno,
                                                            void      *polygon_data) */
#define GLU_TESS_EDGE_FLAG_DATA 100110  /* void (CALLBACK*)(GLboolean boundaryEdge,
                                                            void      *polygon_data) */
#define GLU_TESS_COMBINE_DATA   100111  /* void (CALLBACK*)(GLdouble  coords[3],
                                                            void      *data[4],
                                                            GLfloat   weight[4],
                                                            void      **dataOut,
                                                            void      *polygon_data) */

/* TessError */
#define GLU_TESS_ERROR1     100151
#define GLU_TESS_ERROR2     100152
#define GLU_TESS_ERROR3     100153
#define GLU_TESS_ERROR4     100154
#define GLU_TESS_ERROR5     100155
#define GLU_TESS_ERROR6     100156
#define GLU_TESS_ERROR7     100157
#define GLU_TESS_ERROR8     100158

#define GLU_TESS_MISSING_BEGIN_POLYGON  GLU_TESS_ERROR1
#define GLU_TESS_MISSING_BEGIN_CONTOUR  GLU_TESS_ERROR2
#define GLU_TESS_MISSING_END_POLYGON    GLU_TESS_ERROR3
#define GLU_TESS_MISSING_END_CONTOUR    GLU_TESS_ERROR4
#define GLU_TESS_COORD_TOO_LARGE        GLU_TESS_ERROR5
#define GLU_TESS_NEED_COMBINE_CALLBACK  GLU_TESS_ERROR6

/****           NURBS constants                 ****/

/* NurbsProperty */
#define GLU_AUTO_LOAD_MATRIX    100200
#define GLU_CULLING             100201
#define GLU_SAMPLING_TOLERANCE  100203
#define GLU_DISPLAY_MODE        100204
#define GLU_PARAMETRIC_TOLERANCE        100202
#define GLU_SAMPLING_METHOD             100205
#define GLU_U_STEP                      100206
#define GLU_V_STEP                      100207

/* NurbsSampling */
#define GLU_PATH_LENGTH                 100215
#define GLU_PARAMETRIC_ERROR            100216
#define GLU_DOMAIN_DISTANCE             100217

/* NurbsTrim */
#define GLU_MAP1_TRIM_2         100210
#define GLU_MAP1_TRIM_3         100211

/* NurbsDisplay */
#define GLU_OUTLINE_POLYGON     100240
#define GLU_OUTLINE_PATCH       100241

/* NurbsErrors */
#define GLU_NURBS_ERROR1        100251
#define GLU_NURBS_ERROR2        100252
#define GLU_NURBS_ERROR3        100253
#define GLU_NURBS_ERROR4        100254
#define GLU_NURBS_ERROR5        100255
#define GLU_NURBS_ERROR6        100256
#define GLU_NURBS_ERROR7        100257
#define GLU_NURBS_ERROR8        100258
#define GLU_NURBS_ERROR9        100259
#define GLU_NURBS_ERROR10       100260
#define GLU_NURBS_ERROR11       100261
#define GLU_NURBS_ERROR12       100262
#define GLU_NURBS_ERROR13       100263
#define GLU_NURBS_ERROR14       100264
#define GLU_NURBS_ERROR15       100265
#define GLU_NURBS_ERROR16       100266
#define GLU_NURBS_ERROR17       100267
#define GLU_NURBS_ERROR18       100268
#define GLU_NURBS_ERROR19       100269
#define GLU_NURBS_ERROR20       100270
#define GLU_NURBS_ERROR21       100271
#define GLU_NURBS_ERROR22       100272
#define GLU_NURBS_ERROR23       100273
#define GLU_NURBS_ERROR24       100274
#define GLU_NURBS_ERROR25       100275
#define GLU_NURBS_ERROR26       100276
#define GLU_NURBS_ERROR27       100277
#define GLU_NURBS_ERROR28       100278
#define GLU_NURBS_ERROR29       100279
#define GLU_NURBS_ERROR30       100280
#define GLU_NURBS_ERROR31       100281
#define GLU_NURBS_ERROR32       100282
#define GLU_NURBS_ERROR33       100283
#define GLU_NURBS_ERROR34       100284
#define GLU_NURBS_ERROR35       100285
#define GLU_NURBS_ERROR36       100286
#define GLU_NURBS_ERROR37       100287

/****           Backwards compatibility for old tesselator           ****/

/* Contours types -- obsolete! */
#define GLU_CW          100120
#define GLU_CCW         100121
#define GLU_INTERIOR    100122
#define GLU_EXTERIOR    100123
#define GLU_UNKNOWN     100124

/* Names without "TESS_" prefix */
#define GLU_BEGIN       GLU_TESS_BEGIN
#define GLU_VERTEX      GLU_TESS_VERTEX
#define GLU_END         GLU_TESS_END
#define GLU_ERROR       GLU_TESS_ERROR
#define GLU_EDGE_FLAG   GLU_TESS_EDGE_FLAG

#endif /* __GLU_H__ */
#endif /* __glu_h__ */
