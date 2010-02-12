SUBDIRS = m4 doc icons po src 


test : $(top_srcdir)/po/Prtsc.pot $(top_builddir)/usr/share/locale/	 
	$(top_builddir)/src/prtsc

$(top_builddir)/usr/share/locale/:
	cd po && $(MAKE) install DESTDIR=..