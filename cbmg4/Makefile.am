# Copyright (C) 2005 Florian Uhlig <f.uhlig@gsi.de>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

INCLUDES		= $(ROOTCFLAGS) $(GEANT4VMCINC) $(GEANT4INC)	\
			  $(CLHEPINC)

lib_LTLIBRARIES		= libCbmG4.la

libCbmG4_la_LDFLAGS 	= -version-info 0:0:0

libCbmG4_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) 

include_HEADERS		= CbmRunConfiguration.h  CbmSpecialStackingAction.h	\
			  RichTbPhysicsList.h

noinst_HEADERS		= CbmG4LinkDef.h 

libCbmG4_la_SOURCES	= CbmRunConfiguration.cxx CbmSpecialStackingAction.cxx	\
			  RichTbPhysicsList.cxx CbmG4Dict.cxx

CLEANFILES		= CbmG4Dict.cxx CbmG4Dict.h *~ libCbmG4.la

CbmG4Dict.cxx:  CbmRunConfiguration.h CbmG4LinkDef.h
	$(ROOTCINT) -f $@  -c -DHAVE_CONFIG_H $(CPPFLAGS) $(INCLUDES) $^
