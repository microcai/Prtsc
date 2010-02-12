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
 * savefile.c - let user choose the file to save
 */

#include "Prtsc.h"

void getsavefilename( GString ** filename )
{
	GtkFileChooserDialog * cd;
	char * file ;
	cd = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new(_("Kiki,my wife, save it!"),NULL,GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,NULL));

	gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(cd),TRUE);

	gtk_dialog_run(GTK_DIALOG(cd));

	file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(cd));

	*filename  = g_string_assign(*filename,file);

	g_free (file);

	if (strncasecmp((*filename)->str + (*filename)->len - 3, "png"))
		*filename = g_string_append(*filename, ".png");

	gtk_widget_destroy(GTK_WIDGET(cd));

}
