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

#include <GL/gl.h>
#include <gdk/gdk.h>
#include "gdkgl.h"
#include "gdkgl-private.h"

GdkGL *
gdk_gl_new(guint flags)
{
	GdkGL *gl;

	gl = g_object_new(GDK_TYPE_GL, NULL);
	g_return_val_if_fail(gl, NULL);

	gl->flags = flags;
	gl->depth = GDK_GL_DEFAULT_DEPTH;

	return gl;
}

void
gdk_gl_show(GdkGL *gl, GdkWindow *parent_window)
{
	g_return_if_fail(parent_window);

	gl->parent_window = parent_window;
	_gdk_gl_new_window(gl);
}

void
gdk_gl_set_depth(GdkGL *gl, guint depth)
{
	gl->depth = depth;
}

void
gdk_gl_set_adjust_viewport_on_resize(GdkGL *gl, gboolean value)
{
	if(value)
		gl->adjust_viewport_on_resize = 1;
	else
		gl->adjust_viewport_on_resize = 0;
}

void
gdk_gl_resize(GdkGL *gl, gint width, gint height)
{
	_gdk_gl_resize_window(gl, width, height);

	if(gl->adjust_viewport_on_resize)
		glViewport(0, 0, width, height);
}

void
gdk_gl_swap_buffers(GdkGL *gl)
{
	_gdk_gl_swap_buffers(gl);
}

/* object/class stuff from here on out... */

static GObjectClass *parent_class;

static void
gdk_gl_finalize(GObject *object)
{
	parent_class->finalize(object);
}

static void
gdk_gl_class_init(GObjectClass *class)
{
	parent_class = g_type_class_peek_parent(class);

	class->finalize = gdk_gl_finalize;
}

GType
gdk_gl_get_type(void)
{
	static GType type = 0;

	if(!type) {
		static const GTypeInfo typeinfo = {
			sizeof(GdkGLClass),
			(GBaseInitFunc)NULL,
			(GBaseFinalizeFunc)NULL,
			(GClassInitFunc)gdk_gl_class_init,
			(GClassFinalizeFunc)NULL,
			NULL, /* class_data */
			sizeof(GdkGL),
			0, /* n_preallocs */
			(GInstanceInitFunc)NULL,
		};

		type = g_type_register_static(G_TYPE_OBJECT, "GdkGL", &typeinfo, G_TYPE_FLAG_VALUE_ABSTRACT);
	}

	return type;
}
