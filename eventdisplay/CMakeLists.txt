################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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
  FairGetEventTime.cxx
  datasource/FairDataSourceI.cxx
  datasource/FairTCASource.cxx
  datasource/FairTimebasedSource.cxx
  datasource/FairTimebasedMCSource.cxx
  datasource/FairTimebasedMCHitSource.cxx
  datasource/FairTimebasedDataHandlerT.cxx
  FairXMLNode.cxx
  gui/FairEveAnimationControl.cxx
  gui/FairEveCut.cxx
  gui/FairEveTransparencyControl.cxx
  tracks/FairEveGeoTracks.cxx
  tracks/FairEveGeoTracksEditor.cxx
  tracks/FairEveRecoTrack.cxx
  tracks/FairEveRecoTrackList.cxx
  tracks/FairEveTrack.cxx
  tracks/FairEveTracks.cxx
  tracks/FairGeoTracksDraw.cxx
  tracks/FairGeoTrackHandler.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tracks>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gui>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/datasource>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairRootManager, FairRunAna, FairTSBufferFunctional, FairTimeStamp, FairEventManager

  FairLogger::FairLogger

  ROOT::Core
  ROOT::Eve         # TEveBoxSet
  ROOT::Ged         # TGedFrame
  ROOT::GeomPainter # TGeoTrack
  ROOT::XMLIO       # TXMLEngine

  PRIVATE
  ROOT::Graf3d
  ROOT::EG          # TDatabasePDG
  ROOT::Geom        # TGeoManager, TGeoNode, TGeoVolume
  ROOT::Gui         # TGFrame, TGNumberEntry, TGWindow
  ROOT::MathCore    # TMathBase
  ROOT::Physics     # TVector3
  ROOT::RGL         # TGLViewer, TGLCameraOverlay, TGLClip, TGLLightSet
  ROOT::Tree        # TChain
  ROOT::RIO
  ROOT::XMLParser   # TXMLNode, TXMLAttr, TDOMParser
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF EventDisplayLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
