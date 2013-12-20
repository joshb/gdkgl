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

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <gdk/gdkx.h>
#include "gdkgl-x11.h"
#include "gdkgl-private.h"

#define NEW_ATTRIB(x) \
	do { \
		if((i + 1) >= max_attribs) { \
			attribs[i] = None; \
			return; \
		} \
		attribs[i++] = (x); \
	} while(0)

static void
gdk_gl_x11_set_attribs(GdkGL *gl, int *attribs, int max_attribs)
{
	int i = 0;

	if(max_attribs <= 0)
		return;

	NEW_ATTRIB(GLX_DEPTH_SIZE);
	NEW_ATTRIB(gl->depth);

	if(gl->flags & GDK_GL_RGBA)
		NEW_ATTRIB(GLX_RGBA);
	if(gl->flags & GDK_GL_DOUBLEBUFFER)
		NEW_ATTRIB(GLX_DOUBLEBUFFER);

	NEW_ATTRIB(None);
}

#undef NEW_ATTRIB

void
_gdk_gl_new_window(GdkGL *gl)
{
	GdkGL_X11_Context *context;
	int attribs[128];
	GdkWindow *parent_window = gl->parent_window;
	GdkDrawable *parent_drawable;
	XID parent_xid;
	XVisualInfo *xvisinfo;
	Display *dpy;
	XID xid;
	GLXContext glxcontext;
	int width, height;

	g_return_if_fail(gl);
	g_return_if_fail(parent_window);

	gl->context = g_try_malloc(sizeof(GdkGL_X11_Context));
	g_return_if_fail(gl->context);
	context = (GdkGL_X11_Context *)gl->context;

	gdk_gl_x11_set_attribs(gl, attribs, sizeof(attribs) / sizeof(attribs[0]));

	parent_drawable = GDK_DRAWABLE(parent_window);
	dpy = gdk_x11_drawable_get_xdisplay(parent_drawable);
	parent_xid = gdk_x11_drawable_get_xid(parent_drawable);
	gdk_drawable_get_size(parent_drawable, &width, &height);

	xvisinfo = glXChooseVisual(dpy, DefaultScreen(dpy), attribs);
	g_return_if_fail(xvisinfo);

	/* now create and map the window... */
	xid = XCreateWindow(dpy, parent_xid, 0, 0, width, height, 0, xvisinfo->depth, 0, NULL, 0, NULL);
	XMapWindow(dpy, xid);

	/* set the current glx context and drawable */
	glxcontext = glXCreateContext(dpy, xvisinfo, 0, GL_TRUE);
	glXMakeCurrent(dpy, xid, glxcontext);

	XFree(xvisinfo);

	context->dpy = dpy;
	context->xid = xid;
	context->glxcontext = glxcontext;
}

static void
gdk_gl_x11_make_current(GdkGL *gl)
{
	GdkGL_X11_Context *context = (GdkGL_X11_Context *)gl->context;

	glXMakeCurrent(context->dpy, context->xid, context->glxcontext);
}

void
_gdk_gl_swap_buffers(GdkGL *gl)
{
	GdkGL_X11_Context *context;
	GLXDrawable glxdrawable;

	g_return_if_fail(gl);

	context = (GdkGL_X11_Context *)gl->context;

	gdk_gl_x11_make_current(gl);
	glxdrawable = glXGetCurrentDrawable();
	glXSwapBuffers(context->dpy, glxdrawable);
}

void
_gdk_gl_resize_window(GdkGL *gl, gint width, gint height)
{
	GdkGL_X11_Context *context;

	g_return_if_fail(gl);

	context = (GdkGL_X11_Context *)gl->context;

	XResizeWindow(context->dpy, context->xid, width, height);
}
