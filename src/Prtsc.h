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
 * Prtsc.h - massive header file
 */

#ifndef PRTSC_H_
#define PRTSC_H_

#include "config.h"

#ifdef ENABLE_NLS
#  include <locale.h>
#  include <libintl.h>
#  define _(x) dgettext(GETTEXT_PACKAGE, x)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  include <locale.h>
#  define N_(String) (String)
#  define _(x) (x)
#  define ngettext(Singular, Plural, Number) ((Number == 1) ? (Singular) : (Plural))
#endif

#ifdef DEBUG
#define textdomain(domian) \
	do { textdomain(domian) ; \
		bindtextdomain(domian, "./usr/share/locale"); \
	}while(0)

#endif


#include <gtk/gtk.h>

void cutscreen(GtkWidget *w, gpointer   data);
void cutactive(GtkWidget *w, gpointer   data);
void getsavefilename( GString ** filename );

#endif /* PRTSC_H_ */
