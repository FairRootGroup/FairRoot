# Copyright (C) 2005 Florian Uhlig <f.uhlig@gsi.de>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

INCLUDES		= $(ROOTCFLAGS) -I$(top_srcdir)/base -I$(top_srcdir)/geobase

lib_LTLIBRARIES		= libMCStack.la

libMCStack_la_LDFLAGS 	= -version-info 0:0:0

libMCStack_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) -L$(top_srcdir)/base/ 

include_HEADERS		= CbmStack.h CbmMCTrack.h

noinst_HEADERS		= MCStackLinkDef.h 

libMCStack_la_SOURCES	= CbmStack.cxx CbmMCTrack.cxx   \
                          CbmMCStackDict.cxx

CLEANFILES		= CbmMCStackDict.cxx CbmMCStackDict.h *~ libMCStack.la

CbmMCStackDict.cxx: $(include_HEADERS) MCStackLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
