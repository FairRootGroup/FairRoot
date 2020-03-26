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
  FairMCTracks.cxx
  FairMCTracksEditor.cxx
  FairPointSetDraw.cxx
  FairTimeStampPointDraw.cxx
  FairXMLNode.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::FairTools
  FairRoot::Base # FairRootManager, FairRunAna, FairTSBufferFunctional, FairTimeStamp, FairEventManager

  ROOT::Core
  ROOT::EG          # TDatabasePDG
  ROOT::Eve         # TEveBoxSet
  ROOT::Ged         # TGedFrame
  ROOT::Geom        # TGeoManager, TGeoNode, TGeoVolume
  ROOT::GeomPainter # TGeoTrack
  ROOT::Gui         # TGFrame, TGNumberEntry, TGWindow
  ROOT::MathCore    # TMathBase
  ROOT::Physics     # TVector3
  ROOT::RGL         # TGLViewer, TGLCameraOverlay, TGLClip, TGLLightSet
  ROOT::Tree        # TChain
  ROOT::XMLIO       # TXMLEngine
  ROOT::XMLParser   # TXMLNode, TXMLAttr, TDOMParser
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF EventDisplayLinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})
