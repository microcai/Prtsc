
AM_CFLAGS = @RSVG_CFLAGS@ @GTK2_CFLAGS@ -DPKGDATADIR=\"$(pkgdatadir)\" -DPREFIX=\"$(prefix)\"

AM_LDFLAGS =   @RSVG_LIBS@ @GTK2_LIBS@

bin_PROGRAMS = prtsc

HEADERFILES  = Prtsc.h hotkeys.h


prtsc_SOURCES = hotkeys.c main.c cutwindow.c savefile.c  $(HEADERFILES)

