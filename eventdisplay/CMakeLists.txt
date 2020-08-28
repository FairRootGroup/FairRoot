################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
# Create a library called "libEventDisplay"
# 06.12.07  M. Al-Turany

set(target EventDisplay)

set(sources
  FairBoxSet.cxx
  FairBoxSetDraw.cxx
  FairBoxSetEditor.cxx
  FairEventManager.cxx
  FairEventManagerEditor.cxx
  FairHitDraw.cxx
  FairHitPointSetDraw.cxx
  FairMCPointDraw.cxx
  FairPointSetDraw.cxx
  FairTimeStampPointDraw.cxx
  FairXMLNode.cxx
  FairEveAnimationButton.cxx
  tracks/FairEveCut.cxx
  tracks/FairEveGeoTracks.cxx
  tracks/FairEveGeoTracksEditor.cxx
  tracks/FairEveRecoTrack.cxx
  tracks/FairEveRecoTrackList.cxx
  tracks/FairEveTrack.cxx
  tracks/FairEveTracks.cxx
  tracks/FairGeoTracksDraw.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/tracks
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base # FairRootManager, FairRunAna, FairTSBufferFunctional, FairTimeStamp, FairEventManager

  Core
  EG          # TDatabasePDG
  Eve         # TEveBoxSet
  Ged         # TGedFrame
  Geom        # TGeoManager, TGeoNode, TGeoVolume
  GeomPainter # TGeoTrack
  Gui         # TGFrame, TGNumberEntry, TGWindow
  MathCore    # TMathBase
  Physics     # TVector3
  RGL         # TGLViewer, TGLCameraOverlay, TGLClip, TGLLightSet
  Tree        # TChain
  XMLIO       # TXMLEngine
  XMLParser   # TXMLNode, TXMLAttr, TDOMParser
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF EventDisplayLinkDef.h
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
