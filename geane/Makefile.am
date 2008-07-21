INCLUDES		= $(ROOTCFLAGS)
INCLUDES               += -I$(top_srcdir)/geobase
INCLUDES               += -I$(top_srcdir)/parbase
INCLUDES               += -I$(top_srcdir)/mcstack
INCLUDES               += -I$(top_srcdir)/field
INCLUDES               += -I$(top_srcdir)/base 
INCLUDES               += -I$(top_srcdir)/trackbase
INCLUDES               += $(GEANT3INC)


lib_LTLIBRARIES		= libGeane.la

libGeane_la_LDFLAGS 	= -version-info 0:0:0

libGeane_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) -L$(top_srcdir)/base
libGeane_la_LIBADD       += -L$(top_srcdir)/parbase
libGeane_la_LIBADD       += -L$(top_srcdir)/base

sources                 = CbmGeane.cxx \
			  CbmGeanePro.cxx
			  
include_HEADERS		= $(patsubst %.cxx,%.h,$(sources))

noinst_HEADERS		= GeaneLinkDef.h

libGeane_la_SOURCES	= $(sources) CbmGeaneDict.cxx

CLEANFILES		= CbmGeaneDict.cxx CbmGeaneDict.h *~ libGeane.la

CbmGeaneDict.cxx: $(include_HEADERS) GeaneLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
