# Makefile.am for module PARBASE
# For use of automake
#
# Volker Friese    20-02-2006


INCLUDES		= $(ROOTCFLAGS)


lib_LTLIBRARIES		= libParBase.la

libParBase_la_LDFLAGS 	= -version-info 0:0:0

libParBase_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) 

sources	               := CbmContFact.cxx       \
			  CbmDetParAsciiFileIo.cxx    \
			  CbmDetParIo.cxx         \
			  CbmDetParRootFileIo.cxx     \
			  CbmGenericParAsciiFileIo.cxx     \
			  CbmGenericParRootFileIo.cxx     \
			  CbmParAsciiFileIo.cxx   \
			  CbmParGenericSet.cxx   \
			  CbmParIo.cxx  \
			  CbmParRootFileIo.cxx \
			  CbmParSet.cxx \
			  CbmParamList.cxx  \
			  CbmRtdbRun.cxx  \
			  CbmRuntimeDb.cxx

include_HEADERS		= $(patsubst %.cxx,%.h,$(sources))

noinst_HEADERS		= ParBaseLinkDef.h 

libParBase_la_SOURCES	= $(sources) ParBaseDict.cxx

CLEANFILES		= ParBaseDict.cxx ParBaseDict.h *~ libParBase.la

ParBaseDict.cxx: $(include_HEADERS) ParBaseLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
