plugin_LTLIBRARIES = libgstmpegpsmux.la

libgstmpegpsmux_la_SOURCES = \
	mpegpsmux.c \
	psmux.c \
	psmuxstream.c

libgstmpegpsmux_la_CFLAGS = $(GST_CFLAGS) $(GST_BASE_CLFAGS)
libgstmpegpsmux_la_LIBADD = $(GST_LIBS) $(GST_BASE_LIBS)
libgstmpegpsmux_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmpegpsmux_la_LIBTOOLFLAGS = --tag=disable-static

noinst_HEADERS = \
	mpegpsmux.h \
	psmux.h \
	psmuxstream.h \
	psmuxcommon.h
