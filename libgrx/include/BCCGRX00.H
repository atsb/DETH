/*
 * BCC2GRX  -  Interfacing Borland based graphics programs to LIBGRX
 * Copyright (C) 1993-96 by Hartmut Schirmer
 *
 * This library is copyrighted (see above). It might be used and
 * distributed freely as long as all copyright notices are left
 * intact.
 *
 * You may not distribute any changed versions of BCC2GRX without
 * written permission by Hartmut Schirmer.
 *
 * You are permitted to distribute an application linked with BCC2GRX
 * in binary only, provided that the documentation of the program:
 *
 *    a)   informs the user that BCC2GRX is used in the program, AND
 *
 *    b)   provides the user with the necessary information about
 *         how to obtain BCC2GRX. (i.e. ftp site, etc..)
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact :                Hartmut Schirmer
 *                          Feldstrasse 118
 *                  D-24105 Kiel
 *                          Germany
 *
 * e-mail : hsc@techfak.uni-kiel.d400.de
 */

#ifndef __BCCGRX00_H
#define __BCCGRX00_H

#define HOLD_GR_DEFS

#include <stddef.h>
#include <malloc.h>
#include <string.h>

#ifdef GRX20
  #include <grx20.h>
#else
  #include <grx.h>
#endif
#include <grdriver.h>
#include "../include/libbcc.h"

/* --- from grx/genellipse (LIBGRX 1.02+ only) : */

#if !defined(GR_DRV_VER_GRD) && !defined(GRX_VERSION)
extern int _grx_arc_xc, _grx_arc_yc,
	   _grx_arc_xs, _grx_arc_ys,
	   _grx_arc_xe, _grx_arc_ye;
#endif

/* --- from bccgrx.c : */

extern GrLineOption          __gr_Line;
extern short                *__gr_modeindx;
extern GrContext            *__gr_viewport;
extern char                  __gr_BGICHR[];
extern GrPattern             __gr_fillpattern;

/* --- some things require GRX v2 */
#ifdef GRX_VERSION
extern int                   __gr_BGI_p;
extern int                   __gr_Y_page_offs;
#endif

/* ------------------------------ */

/* internal graphics modes */
typedef struct GraphicsMode {
	  int  width, height;
	  long colors;
	  struct GraphicsMode *next;
} GraphicsMode;
extern GraphicsMode *__gr_Modes;

/* ------------------------- */

#define ERR    __gr_Result
#define MM     __gr_MaxMode
#define X      __gr_X
#define Y      __gr_Y
#define LNE    __gr_Line
#define LNEP   __gr_LineP
#define COL    __gr_color
#define COLBG  __gr_colorbg
#define FILL   __gr_colorfill
#define WR     __gr_WR
#define FPATT  __gr_fpatno
#define FILLP  __gr_fillpattern
#define VL     __gr_vpl
#define VR     __gr_vpr
#define VT     __gr_vpt
#define VB     __gr_vpb
#ifdef GRX_VERSION
#define PY     __gr_Y_page_offs
#else
#define PY     (0)
#endif

#define SWAP(a,b) ({typeof(a) tmp; tmp = a; a = b; b = tmp;})

#define _DO_INIT_CHECK ({if (!__gr_INIT) {__gr_Result=grNoInitGraph;return;}})
#define _DO_INIT_CHECK_RV(rv) ({if (!__gr_INIT) { __gr_Result = grNoInitGraph;\
						  return (rv);}})

#define IMAGE_CONTEXT_SIZE      (((sizeof(GrContext)+15)&~15)+4)

/* ----------------------------------------------------------------- */
__inline__ static void __gr_Reset_ClipBox(void)
{
  if (__gr_clip) GrSetClipBox( VL, VT+PY, VR, VB+PY);
  else
#ifdef GRX_VERSION
       GrSetClipBox( 0, PY, getmaxx(), getmaxy()+PY);
#else
       GrResetClipBox();
#endif
}

/* ----------------------------------------------------------------- */

extern int __gr_getmode_whc(int idx, int *width, int *height, long *colors);
extern int __gr_adaptcnv(int grx);

#ifdef GRX_VERSION
/* disable unimplemented (or buggy) GRX functions */
#include "grx20fix.h"
#endif

#ifndef GRX_VERSION
/* Some usefull GRX 2.0 functions for 1.0x libraries */
#define MMSK                    (GrXOR|GrOR|GrAND)
#define GrWriteModeColor(c)     (((c)&MMSK) | GrWRITE)
#define GrXorModeColor(c)       (((c)&MMSK) | GrXOR)
#define GrOrModeColor(c)        (((c)&MMSK) | GrOR)
#define GrAndModeColor(c)       (((c)&MMSK) | GrAND)
#endif

#endif

