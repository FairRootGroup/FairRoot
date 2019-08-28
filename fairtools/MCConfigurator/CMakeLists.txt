################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target MCConfigurator)

set(sources
  FairYamlVMCConfig.cxx
)

set(headers
  FairYamlVMCConfig.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: delete me once using targets
  $<BUILD_INTERFACE:${Geant3_INCLUDE_DIRS}>
  $<BUILD_INTERFACE:${Geant4_INCLUDE_DIRS}>
  $<BUILD_INTERFACE:${Geant4VMC_INCLUDE_DIRS}>
  $<BUILD_INTERFACE:${YAML_CPP_INCLUDE_DIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
  ${Geant3_LIBRARY_DIR}
  ${Geant4_LIBRARY_DIR}
  ${Geant4VMC_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairLogger::FairLogger
  FairRoot::Base # FairRunSim
  # TODO: clean the following
  geant321
  geant4vmc
  Pythia6
  FairFastSim
  yaml-cpp
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF MCConfiguratorLinkDef.h
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)

install(FILES ${headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
