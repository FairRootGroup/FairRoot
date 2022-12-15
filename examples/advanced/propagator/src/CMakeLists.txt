 ################################################################################
 # Copyright (C) 2019-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(target ExPropagator)

set(sources
  FairTutPropContFact.cxx
  FairTutPropDet.cxx
  FairTutPropGeo.cxx
  FairTutPropGeoPar.cxx
  FairTutPropPoint.cxx
  FairTutPropTr.cxx
  FairTutPropHit.cxx
  FairTutPropHitProducer.cxx
  FairTutPropTrack.cxx
  FairTutPropTrackFinder.cxx
  FairEveRecoTracksExample.cxx
  FairEveRecoTracksExampleEditor.cxx
  FairRecoTracksDraw.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_compile_definitions(${target} PUBLIC ${defs})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::GeoBase # FairGeoSet
  FairRoot::ParBase # FairRuntimeDb, FairContFact, FairParamList
  FairRoot::TrackBase # FairPropagator
  FairRoot::EventDisplay

  Boost::serialization

  ROOT::Core # Rtypes
  ROOT::Physics # TVector3, TLorentzVector
  ROOT::Gui # TGFrame.
  ROOT::Ged # TGedFrame

  PRIVATE
  FairRoot::Tools # FairLogger
  FairRoot::ExMCStack

  ROOT::MathCore # TRandom
  ROOT::EG
  ROOT::Eve
  ROOT::Geom
#  ROOT::RGL
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF TutPropLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
