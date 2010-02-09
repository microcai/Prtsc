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

int main(int argc, char * argv[])
{
	GtkStatusIcon * main_icon;


	gtk_init(&argc, &argv);
	setlocale(LC_ALL, "");
	gtk_set_locale();
	textdomain(GETTEXT_PACKAGE);

	//主程序其实就是为了显示个图标，吼吼

	main_icon = gtk_status_icon_new_from_file("/usr/share/icons/hicolor/scalable/apps/Prtsc.svg");
	gtk_status_icon_get_visible(main_icon,TRUE);


	return 0;
}
