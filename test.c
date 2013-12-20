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
#include <GL/glu.h>
#include <gtk/gtk.h>
#include "gdkgl.h"

void
quit_app(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

static void
gl_draw(GdkGL *gl)
{
	static float rot[3] = { 0.0f, 0.0f, 0.0f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glFlush();
	gdk_gl_swap_buffers(gl);

	rot[0] += 0.04f;
	rot[2] += 0.02f;
}

static gboolean
gl_idle(gpointer data)
{
	gl_draw((GdkGL *)data);

	return TRUE;
}

static void
gl_resize(GtkWidget *widget, GtkAllocation *alloc, gpointer data)
{
	GdkGL *gl = (GdkGL *)data;

	gdk_gl_resize(gl, alloc->width, alloc->height);
}

int
main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *viewport;
	GtkWidget *button;
	GdkGL *gl;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(G_OBJECT(window), "delete_event",
	                 G_CALLBACK(quit_app), NULL);

	box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_widget_show(box);

	viewport = gtk_viewport_new(NULL, NULL);
	gtk_box_pack_start(GTK_BOX(box), viewport, TRUE, TRUE, 0);
	gtk_widget_set_usize(viewport, 320, 240);
	gtk_widget_show(viewport);

	button = gtk_button_new_with_label("Quit");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(quit_app), NULL);
	gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_widget_show(window);

	gl = gdk_gl_new(GDK_GL_RGBA | GDK_GL_DOUBLEBUFFER);
	gdk_gl_set_adjust_viewport_on_resize(gl, TRUE);
	gdk_gl_show(gl, viewport->window);

	g_signal_connect(G_OBJECT(viewport), "size-allocate", G_CALLBACK(gl_resize), gl);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glClearDepth(1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 0.05f, 2000.0f);
	glMatrixMode(GL_MODELVIEW);

	g_idle_add(gl_idle, gl);
	gtk_main();
	return 0;
}
