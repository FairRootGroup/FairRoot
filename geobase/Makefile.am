# Copyright (C) 2005 Florian Uhlig <f.uhlig@gsi.de>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


if COMP_GEANT3
  G3_SOURCE_FILE=CbmGeoG3Builder.cxx
  G3_INC_FILE=CbmGeoG3Builder.h
  LINK_DEF=GeoBase_withg3_LinkDef.h
else
  LINK_DEF=GeoBaseLinkDef.h
endif


INCLUDES		= $(ROOTCFLAGS) $(GEANT3INC)

lib_LTLIBRARIES		= libGeoBase.la 

libGeoBase_la_LDFLAGS 	= -version-info 0:0:0

libGeoBase_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) 

include_HEADERS		= CbmGeoCone.h	CbmGeoCons.h \
			  CbmGeoEltu.h CbmGeoBuilder.h  \
			  CbmGeoInterface.h  CbmGeoIo.h  \
			  CbmGeoLoader.h  CbmGeoMatrix.h \
			  CbmGeoMedia.h	 CbmGeoMedium.h \
			  CbmGeoNode.h CbmGeoOldAsciiIo.h \
			  CbmGeoPcon.h  CbmGeoPgon.h \
			  CbmGeoRootBuilder.h  CbmGeoRotation.h \
			  CbmGeoSet.h  CbmGeoShapes.h \
			  CbmGeoSphe.h  CbmGeoTransform.h \
			  CbmGeoTrap.h	CbmGeoTrd1.h \
			  CbmGeoTube.h  CbmGeoTubs.h  CbmGeoTorus.h \
			  CbmGeoVector.h  CbmGeoVolume.h \
                          CbmGeoCompositeVolume.h CbmGeoAsciiIo.h	\
			  CbmGeoBrik.h CbmGeoBasicShape.h $(G3_INC_FILE)

noinst_HEADERS		= GeoBase_withg3_LinkDef.h  GeoBaseLinkDef.h

libGeoBase_la_SOURCES	= CbmGeoCone.cxx  CbmGeoCons.cxx \
			  CbmGeoEltu.cxx  CbmGeoBuilder.cxx  \
			  CbmGeoInterface.cxx  CbmGeoIo.cxx  \
			  CbmGeoLoader.cxx  CbmGeoMatrix.cxx \
			  CbmGeoMedia.cxx	 CbmGeoMedium.cxx \
			  CbmGeoNode.cxx CbmGeoOldAsciiIo.cxx \
			  CbmGeoPcon.cxx  CbmGeoPgon.cxx \
			  CbmGeoRootBuilder.cxx  CbmGeoRotation.cxx \
			  CbmGeoSet.cxx  CbmGeoShapes.cxx \
			  CbmGeoSphe.cxx  CbmGeoTransform.cxx \
			  CbmGeoTrap.cxx	CbmGeoTrd1.cxx \
			  CbmGeoTube.cxx  CbmGeoTubs.cxx   CbmGeoTorus.cxx \
			  CbmGeoVector.cxx  CbmGeoVolume.cxx	\
			  $(G3_SOURCE_FILE) \
                          CbmGeoCompositeVolume.cxx CbmGeoAsciiIo.cxx \
                          CbmGeoBrik.cxx CbmGeoBasicShape.cxx CbmGeoDict.cxx

CLEANFILES		= CbmGeoDict.cxx CbmGeoDict.h *~ libGeoBase.la

CbmGeoDict.cxx: $(include_HEADERS) $(LINK_DEF)
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^
