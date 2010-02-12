/*
 * Prtsc - screen cut program written for my wife
 *
 * Copyright (c) 2010-2010 microcai  <microcai@fedoraproject.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * cutwindow.c - cut widget or screen
 *
 */


#include "Prtsc.h"

void cutscreen(GtkWidget *w, gpointer   data)
{
	gulong m;


	GTimer * gt = g_timer_new();

	puts(__func__);

	g_timer_start(gt);
	GError	* err = NULL;

//	err = g_error_new()

	//截取全部的屏幕
	GdkScreen * scr = gdk_screen_get_default();
//	scr = gtk_window_get_screen(w);

	guint width = gdk_screen_get_width(scr);

	guint height = gdk_screen_get_height(scr);


	GdkWindow *  gw = gdk_screen_get_root_window(scr);

	GdkPixbuf  * pixbuf = gdk_pixbuf_get_from_drawable(NULL,gw,NULL,0,0,0,0,width,height);

	GString * file = g_string_new("");

	getsavefilename(&file);

//	gdk_pixbuf_save(pixbuf,"CUT.bmp","bmp",&err,NULL);
	gdk_pixbuf_save(pixbuf,file->str,"png",&err,NULL);

	g_string_free(file,TRUE);

//	gdk_pixbuf_save(pixbuf,"CUT.jpg","jpeg",&err,NULL);
	g_object_unref(pixbuf);

	g_timer_stop(gt);

	g_print("capture image use time %lfs\n",g_timer_elapsed(gt,&m));
}


void cutactive(GtkWidget *w, gpointer   data)
{
	gulong m;

	GTimer * gt = g_timer_new();

	puts(__func__);

	g_timer_start(gt);

	GError	* err = NULL;

//	err = g_error_new()

	//截取全部的屏幕
	GdkScreen * scr = gdk_screen_get_default();
//	scr = gtk_window_get_screen(w);

	guint width ;

	guint height ;

	GdkWindow *  gw = gdk_screen_get_active_window(scr);

	gdk_drawable_get_size(gw,&width,&height);

	GdkPixbuf  * pixbuf = gdk_pixbuf_get_from_drawable(NULL,gw,NULL,0,0,0,0,width,height);

	GString * file = g_string_new("");

	getsavefilename(&file);

//	gdk_pixbuf_save(pixbuf,"CUT.bmp","bmp",&err,NULL);
	gdk_pixbuf_save(pixbuf,file->str,"png",&err,NULL);

	g_string_free(file,TRUE);

//	gdk_pixbuf_save(pixbuf,"CUT.jpg","jpeg",&err,NULL);
	g_object_unref(pixbuf);

	g_timer_stop(gt);

	g_print("capture image use time %lfs\n",g_timer_elapsed(gt,&m));
}

