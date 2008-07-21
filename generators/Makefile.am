# Copyright (C) 2005 Florian Uhlig <f.uhlig@gsi.de>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

INCLUDES		= $(ROOTCFLAGS)
INCLUDES               += $(PLUTOINC)
INCLUDES               += -I$(top_srcdir)/base
INCLUDES               += -I$(top_srcdir)/geobase
INCLUDES               += -I$(top_srcdir)/field

lib_LTLIBRARIES		= libGen.la

libGen_la_LDFLAGS 	= -version-info 0:0:0

libGen_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) -L$(top_srcdir)/base/ 

sources                 = CbmAsciiGenerator.cxx    \
			  CbmBoxGenerator.cxx      \
			  CbmIonGenerator.cxx      \
			  CbmParticleGenerator.cxx \
			  CbmShieldGenerator.cxx   \
			  CbmPlutoGenerator.cxx    \
			  CbmUrqmdGenerator.cxx    \
			  CbmEvtGenGenerator.cxx

include_HEADERS		= $(patsubst %.cxx,%.h,$(sources))
	
noinst_HEADERS		= GenLinkDef.h 

libGen_la_SOURCES	= $(sources) CbmGenDict.cxx

CLEANFILES		= CbmGenDict.cxx CbmGenDict.h *~ lib.la

CbmGenDict.cxx: $(include_HEADERS) GenLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
