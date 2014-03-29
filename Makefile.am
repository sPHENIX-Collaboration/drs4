AUTOMAKE_OPTIONS = foreign


AM_LDFLAGS = -L$(libdir)

WXINCLUDES = $(shell wx-config --cxxflags)

INCLUDES = -I$(includedir) $(WXINCLUDES)


include_HEADERS = DRS.h mxml.h musbstd.h strlcpy.h

lib_LTLIBRARIES =  libdrs.la librcdaqplugin_drs.la

#bin_PROGRAMS = drs_exam
#drs_exam_SOURCES = drs_exam.cc averager.cc
#drs_exam_LDADD = libdrs.la
#drs_exam_LDFLAGS = -lpthread -lutil -lusb -L/usr/lib64  -lwx_gtk2u_richtext-2.8 -lwx_gtk2u_aui-2.8 -lwx_gtk2u_xrc-2.8 -lwx_gtk2u_qa-2.8 -lwx_gtk2u_html-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_core-2.8 -lwx_baseu_xml-2.8 -lwx_baseu_net-2.8 -lwx_baseu-2.8 


libdrs_la_SOURCES = DRS.cc mxml.c musbstd.c strlcpy.c

librcdaqplugin_drs_la_SOURCES = \
	daq_device_drs.cc \
	drsTriggerHandler.cc \
	drs_plugin.cc \
	averager.cc

librcdaqplugin_drs_la_LIBADD = libdrs.la 

libdrs_la_LIBADD = -lpthread -lutil -lusb -lrcdaqutils -L/usr/lib64  -lwx_gtk2u_richtext-2.8 -lwx_gtk2u_aui-2.8 -lwx_gtk2u_xrc-2.8 -lwx_gtk2u_qa-2.8 -lwx_gtk2u_html-2.8 -lwx_gtk2u_adv-2.8 -lwx_gtk2u_core-2.8 -lwx_baseu_xml-2.8 -lwx_baseu_net-2.8 -lwx_baseu-2.8 

#$(WXLIBS)


clean-local:
	rm -f $(BUILT_SOURCES)
