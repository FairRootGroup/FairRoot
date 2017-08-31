################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(Tutorial4
  SOURCES
  mc/FairTutorialDet4.cxx
  mc/FairTutorialDet4Geo.cxx

  param/FairTutorialDet4ContFact.cxx
  param/FairTutorialDet4GeoPar.cxx
  param/FairTutorialDet4MisalignPar.cxx

  data/FairTutorialDet4Point.cxx
  data/FairTutorialDet4Hit.cxx

  reco/FairTutorialDet4HitProducerIdealMisalign.cxx
  reco/FairTutorialDet4StraightLineFitter.cxx
  reco/FairTutorialDet4MilleWriter.cxx

  tools/FairTutorialDet4GeoHandler.cxx

  display/FairTutorialDet4PointDraw.cxx

  INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/mc
  ${CMAKE_CURRENT_SOURCE_DIR}/param
  ${CMAKE_CURRENT_SOURCE_DIR}/data
  ${CMAKE_CURRENT_SOURCE_DIR}/reco
  ${CMAKE_CURRENT_SOURCE_DIR}/tools
  
  DEPENDENCIES
  Base
  MCStack
  GeoBase
  ParBase
  FairTools
  EventDisplay
  ROOT::VMC
  ROOT::Physics
  ROOT::Core
  ROOT::Eve

  LINKDEF Tutorial4LinkDef.h
  NO_DICT_SRCS tools/Mille.cc
)
