/*
 * Copyright (C) 2003 Josh A. Beam
 *
 * Authors: Josh A. Beam <josh@joshbeam.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GDKGL_X11_H__
#define __GDKGL_X11_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include "gdkgl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _GdkGL_X11_Context GdkGL_X11_Context;

struct _GdkGL_X11_Context {
	Display *dpy;
	XID xid;
	GLXContext glxcontext;
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GDKGL_X11_H__ */
