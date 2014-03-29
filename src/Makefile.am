## Process this file with automake to produce Makefile.in

INCLUDES = \
	@GTK_CFLAGS@

bin_PROGRAMS = notification

notification_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h

notification_LDADD = @GTK_LIBS@ @LIBOBJS@

EXTRA_DIST = strlcpy.c strlcat.c
