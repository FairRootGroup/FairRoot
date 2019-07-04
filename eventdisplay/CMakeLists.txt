 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libEventDisplay" 
# 06.12.07  M. Al-Turany

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/trackbase 
  ${CMAKE_SOURCE_DIR}/geane
  ${CMAKE_SOURCE_DIR}/eventdisplay
)

Include_Directories(${INCLUDE_DIRECTORIES})

set(SRCS
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
)

Set(HEADERS )
Set(LINKDEF EventDisplayLinkDef.h)
Set(LIBRARY_NAME EventDisplay)
Set(DEPENDENCIES Base Eve XMLIO XMLParser)

GENERATE_LIBRARY()
