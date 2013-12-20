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

#ifndef __GDKGL_PRIVATE_H__
#define __GDKGL_PRIVATE_H__

#include "gdkgl.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void _gdk_gl_new_window(GdkGL *gl);
void _gdk_gl_swap_buffers(GdkGL *gl);
void _gdk_gl_resize_window(GdkGL *gl, gint width, gint height);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GDKGL_PRIVATE_H__ */
