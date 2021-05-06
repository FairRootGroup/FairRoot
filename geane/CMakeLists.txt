################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Geane)

set(sources
  FairGeane.cxx
  FairGeanePro.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairField, FairTask, FairPropagator
  FairRoot::TrkBase # FairTrackPar

  geant321

  ROOT::Core
  ROOT::EG
  ROOT::Geom
  ${VMCLIB}
  ROOT::Physics
  ROOT::MathCore
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF GeaneLinkDef.h
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
