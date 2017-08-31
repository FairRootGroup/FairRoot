################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(EventDisplay
  SOURCES
  FairEventManager.cxx  
  FairMCTracks.cxx
  FairEventManagerEditor.cxx
  FairMCTracksEditor.cxx
  FairBoxSet.cxx
  FairBoxSetDraw.cxx
  FairBoxSetEditor.cxx
  FairPointSetDraw.cxx
  FairMCPointDraw.cxx
  FairHitDraw.cxx
  FairHitPointSetDraw.cxx
  FairTimeStampPointDraw.cxx
  FairXMLNode.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES Base ROOT::Eve ROOT::XMLIO ROOT::XMLParser
  LINKDEF EventDisplayLinkDef.h
)
