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
 * main.c - main source file
 */

#include "Prtsc.h"
#include <X11/Xlib.h>
#include <gdk/gdkx.h>
#include "hotkeys.h"

#include <../icons/Prtsc.svg.h>

enum{
	PRTSC_HOTKEY_CUTFULLSCREEN,
	PRTSC_HOTKEY_CUTACTIVE,
	PRTSC_HOTKEY_CUTREGION,
	PRTSC_HOTKEY_NUMBER
};

static HotkeyEntry	hotkeys[PRTSC_HOTKEY_NUMBER] ;

static void popmenu(GtkStatusIcon *status_icon, guint button, guint activate_time,	gpointer user_data)
{
	gtk_menu_popup(user_data,0,0,0,0,0,activate_time);
}

static GdkFilterReturn FilterFunc(XEvent *xevent, GdkEvent *event,gpointer data)
{
	static int t;

	if(xevent->type == KeyPress)
	{
		prase_hotkey((XKeyEvent*)xevent,hotkeys,PRTSC_HOTKEY_NUMBER);
	}

	return GDK_FILTER_CONTINUE;
}

int main(int argc, char * argv[])
{
	GtkStatusIcon * main_icon;

	GdkPixbuf * icon_pixbuf;

	GtkItemFactory * item_factory;

	GError	* err;

	gtk_init(&argc, &argv);
	setlocale(LC_ALL, "");
	gtk_set_locale();
	textdomain(GETTEXT_PACKAGE);

	puts(_("Prtsc start up\n"));

	//主程序其实就是为了显示个图标，吼吼

	icon_pixbuf = gdk_pixbuf_new_from_inline(sizeof(prtsc_icon),prtsc_icon,FALSE,FALSE);

	main_icon = gtk_status_icon_new_from_pixbuf(icon_pixbuf);

	gtk_status_icon_set_title(main_icon,PACKAGE_NAME);

	gtk_status_icon_set_visible(main_icon,TRUE);

	GtkItemFactoryEntry entry[] = {
			{  _("/CutScreen") , NULL, cutscreen, 0 , "<Item>" , NULL },
			{  _("/CutActive") , NULL, cutactive, 0 , "<Item>" , NULL },
	};

	item_factory = gtk_item_factory_new(GTK_TYPE_MENU,"<main>",0);

	gtk_item_factory_create_items(item_factory,2,entry,0);

	hotkeys[PRTSC_HOTKEY_CUTFULLSCREEN].hotkeyfunc = (GFreeFunc)(cutscreen);
	hotkeys[PRTSC_HOTKEY_CUTFULLSCREEN].user_data = 0;
	hotkeys[PRTSC_HOTKEY_CUTFULLSCREEN].mod = 0;
	hotkeys[PRTSC_HOTKEY_CUTFULLSCREEN].code = XK_Print;

	hotkeys[PRTSC_HOTKEY_CUTACTIVE].hotkeyfunc = (GFreeFunc)(cutactive);
	hotkeys[PRTSC_HOTKEY_CUTACTIVE].user_data = 0;
	hotkeys[PRTSC_HOTKEY_CUTACTIVE].mod = ShiftMask;
	hotkeys[PRTSC_HOTKEY_CUTACTIVE].code = XK_Print;


	register_hotkey(hotkeys,PRTSC_HOTKEY_NUMBER);

	gdk_window_add_filter(NULL,(GdkFilterFunc)FilterFunc,0);

	g_signal_connect(G_OBJECT(main_icon),"popup-menu",G_CALLBACK(popmenu),gtk_item_factory_get_widget (item_factory, "<main>"));

	gtk_main();

	return 0;
}
