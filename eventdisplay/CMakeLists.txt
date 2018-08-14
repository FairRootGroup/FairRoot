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
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/geobase 
  ${CMAKE_SOURCE_DIR}/parbase 
  ${CMAKE_SOURCE_DIR}/base 
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/source
  ${CMAKE_SOURCE_DIR}/base/sink
  ${CMAKE_SOURCE_DIR}/trackbase 
  ${CMAKE_SOURCE_DIR}/geane
  ${CMAKE_SOURCE_DIR}/eventdisplay
  ${CMAKE_SOURCE_DIR}/alignment
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR} 
  ${Boost_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})

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
