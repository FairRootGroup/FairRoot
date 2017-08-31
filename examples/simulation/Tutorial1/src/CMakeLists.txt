################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(Tutorial1
  SOURCES
  FairTutorialDet1.cxx
  FairTutorialDet1ContFact.cxx
  FairTutorialDet1Geo.cxx
  FairTutorialDet1GeoPar.cxx
  FairTutorialDet1Point.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES MCStack GeoBase ParBase Base FairTools
  LINKDEF Tutorial1LinkDef.h
)
