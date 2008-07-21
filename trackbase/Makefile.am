INCLUDES		= $(ROOTCFLAGS)
INCLUDES               += -I$(top_srcdir)/base 
INCLUDES               += -I$(top_srcdir)/parbase 
INCLUDES               += $(GEANT3INC)

lib_LTLIBRARIES		= libTrkBase.la

libTrkBase_la_LDFLAGS 	= -version-info 0:0:0

libTrkBase_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) -L$(top_srcdir)/base
libTrkBase_la_LIBADD       += -L$(top_srcdir)/parbase
libTrkBase_la_LIBADD       += -L$(top_srcdir)/base

sources                 = CbmTrackPar.cxx  \
 			  CbmTrackParH.cxx  \
 			  CbmTrackParP.cxx  \
			  CbmGeaneUtil.cxx  

			  
include_HEADERS		= $(patsubst %.cxx,%.h,$(sources))

noinst_HEADERS		= TrackBaseLinkDef.h

libTrkBase_la_SOURCES	= $(sources) TrkBaseDict.cxx

CLEANFILES		= TrkBaseDict.cxx TrkBaseDict.h *~ libTrkBase.la

TrkBaseDict.cxx: $(include_HEADERS) TrackBaseLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
