################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExEventDisplay)

set(sources
  FairEveMCTracks.cxx
  FairEveMCTracksEditor.cxx
  FairMCTracksDraw.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# TODO: DELETE ME ONCE USING root targets
target_include_directories(${target} SYSTEM PUBLIC
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::EventDisplay
  FairRoot::TrackBase

  ROOT::Core
  ROOT::Gui
  ROOT::Ged

  FairRoot::ExMCStack

  ROOT::Eve
  ROOT::EG
  ROOT::Physics
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF EventDisplayExampleLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
