################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(FairRutherford
  SOURCES
  FairRutherford.cxx
  FairRutherfordContFact.cxx
  FairRutherfordGeo.cxx
  FairRutherfordGeoPar.cxx
  FairRutherfordPoint.cxx

  DEPENDENCIES
  Base
  MCStack
  GeoBase
  ParBase
  FairTools
  ROOT::VMC
  ROOT::Physics
  ROOT::Core

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  LINKDEF FairRutherfordLinkDef.h
)
