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

#ifndef __GDKGL_H__
#define __GDKGL_H__

#include <gdk/gdktypes.h>
#include <gdk/gdkpixmap.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GDK_GL_DEFAULT_DEPTH		16

#define GDK_GL_RGBA					(1 << 0)
#define GDK_GL_DOUBLEBUFFER			(1 << 1)

typedef struct _GdkGL GdkGL;
typedef struct _GdkGLClass GdkGLClass;

#define GDK_TYPE_GL						(gdk_gl_get_type())

struct _GdkGL {
	GObject parent_class;

	GdkWindow *parent_window;

	guint flags;
	guint depth;

	guint adjust_viewport_on_resize : 1;

	/* platform-dependent context pointer (gdkgl-x11 code uses this for a
	   GdkGL_X11_Context, for example) */
	gpointer context;
};

struct _GdkGLClass {
	GObjectClass parent_class;
};

GdkGL *gdk_gl_new(guint flags);
void gdk_gl_show(GdkGL *gl, GdkWindow *parent_window);
void gdk_gl_set_depth(GdkGL *gl, guint depth);
void gdk_gl_set_adjust_viewport_on_resize(GdkGL *gl, gboolean value);
void gdk_gl_resize(GdkGL *gl, gint width, gint height);

void gdk_gl_swap_buffers(GdkGL *gl);

GType gdk_gl_get_type(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GDKGL_H__ */
