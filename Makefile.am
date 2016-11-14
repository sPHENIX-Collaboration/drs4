AUTOMAKE_OPTIONS = foreign


AM_LDFLAGS = -L$(libdir)

INCLUDES = -I$(includedir) $(WXINCLUDES)


include_HEADERS = DRS.h mxml.h musbstd.h strlcpy.h averager.h

lib_LTLIBRARIES =  libdrs.la librcdaqplugin_drs.la

bin_PROGRAMS = list_drs4boards
list_drs4boards_SOURCES = list_drs4boards.cc
list_drs4boards_LDADD = libdrs.la
list_drs4boards_LDFLAGS = -lpthread -lutil -lusb -L/usr/lib64 $(WXLIBS)


libdrs_la_SOURCES = DRS.cc mxml.c musbstd.c strlcpy.c averager.cc

librcdaqplugin_drs_la_SOURCES = \
	daq_device_drs.cc \
	drsTriggerHandler.cc \
	drs_plugin.cc

librcdaqplugin_drs_la_LIBADD = libdrs.la 

libdrs_la_LIBADD = -lpthread -lutil -lusb -lrcdaqutils $(WXLIBS)


clean-local:
	rm -f $(BUILT_SOURCES)
