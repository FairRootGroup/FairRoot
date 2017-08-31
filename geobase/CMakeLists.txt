################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(GeoBase
  SOURCES
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

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES ROOT::Geom ROOT::Graf3d ROOT::Core FairTools
  LINKDEF GeoBaseLinkDef.h
)
