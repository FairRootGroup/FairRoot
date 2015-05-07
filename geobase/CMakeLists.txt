 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/geobase
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR} 
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR} 
)
 
Link_Directories(${LINK_DIRECTORIES})


set(SRCS

FairGeoAssembly.cxx
FairGeoCone.cxx	
FairGeoCons.cxx 
FairGeoEltu.cxx 
FairGeoBuilder.cxx  
FairGeoInterface.cxx  
FairGeoIo.cxx  
FairGeoLoader.cxx  
FairGeoMatrix.cxx 
FairGeoMedia.cxx	 
FairGeoMedium.cxx 
FairGeoNode.cxx 
FairGeoOldAsciiIo.cxx 
FairGeoPcon.cxx  
FairGeoPgon.cxx 
FairGeoRootBuilder.cxx  
FairGeoRotation.cxx 
FairGeoSet.cxx  
FairGeoShapes.cxx 
FairGeoSphe.cxx  
FairGeoTransform.cxx 
FairGeoTrap.cxx	
FairGeoTrd1.cxx 
FairGeoTube.cxx  
FairGeoTubs.cxx  
FairGeoTorus.cxx 
FairGeoVector.cxx  
FairGeoVolume.cxx 
FairGeoCompositeVolume.cxx 
FairGeoAsciiIo.cxx	
FairGeoBrik.cxx 
FairGeoBasicShape.cxx 
 
)

Set(HEADERS )
Set(LINKDEF GeoBaseLinkDef.h)
Set(LIBRARY_NAME GeoBase)
Set(DEPENDENCIES Geom Graf3d Core FairTools)

GENERATE_LIBRARY()

