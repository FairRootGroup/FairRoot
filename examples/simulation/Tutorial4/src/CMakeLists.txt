################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExSimulation4)

set(sources
  data/FairTutorialDet4Point.cxx
  data/FairTutorialDet4Hit.cxx

  mc/FairTutorialDet4.cxx
  mc/FairTutorialDet4Geo.cxx

  param/FairTutorialDet4ContFact.cxx
  param/FairTutorialDet4GeoPar.cxx
  param/FairTutorialDet4MisalignPar.cxx

  reco/FairTutorialDet4HitProducerIdealMisalign.cxx
  reco/FairTutorialDet4StraightLineFitter.cxx
  reco/FairTutorialDet4MilleWriter.cxx

  tools/FairTutorialDet4GeoHandler.cxx
  tools/Mille.cc
)

if(${ROOT_HAS_OPENGL})
  list(APPEND sources
    display/FairTutorialDet4PointDraw.cxx
  )
endif()

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/data>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/mc>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/param>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/reco>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/tools>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::Tools # FairLogger
  FairRoot::ExMCStack
  FairRoot::GeoBase
  FairRoot::ParBase
  FairRoot::Gen
  $<$<BOOL:${ROOT_HAS_OPENGL}>:FairRoot::EventDisplay>

  ROOT::Core
  ROOT::Physics
  ROOT::Geom
  ${VMCLIB}
  ROOT::MathCore
  ROOT::Hist
  $<$<BOOL:${ROOT_HAS_OPENGL}>:ROOT::Eve>
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF Tutorial4LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
