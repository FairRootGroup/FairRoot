################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(Passive
  SOURCES
  FairCave.cxx            
  FairGeoCave.cxx        
  FairGeoMagnet.cxx      
  FairGeoPassivePar.cxx  
  FairGeoPipe.cxx        
  FairGeoTarget.cxx      
  FairMagnet.cxx         
  FairPassiveContFact.cxx
  FairPipe.cxx           
  FairTarget.cxx 

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES Base GeoBase ParBase FairTools ROOT::Geom ROOT::Core
  LINKDEF PassiveLinkDef.h
)
