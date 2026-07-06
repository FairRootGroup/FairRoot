################################################################################
# Copyright (C) 2014-2025 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target MCConfigurator)

set(sources
  FairYamlVMCConfig.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Set compile definition
if(Geant3_FOUND)
    target_compile_definitions(${target} PUBLIC FAIRROOT_HAS_GEANT3)
endif()
if(Geant4VMC_FOUND)
    target_compile_definitions(${target} PUBLIC FAIRROOT_HAS_GEANT4)
endif()
if(TARGET FairRoot::FastSim)
    target_compile_definitions(${target} PUBLIC FAIRROOT_HAS_FASTSIM)
endif()

target_link_libraries(${target}
  PUBLIC
  FairRoot::Base # FairGenericVMCConfig
  yaml-cpp::yaml-cpp

  PRIVATE
  FairRoot::Tools

  ROOT::Core
  ${VMCLIB}
)

if(Geant3_FOUND)
  target_link_libraries(${target}
    PUBLIC
      geant321
  )
endif()

if(Geant4VMC_FOUND)
  target_link_libraries(${target}
    PUBLIC
      geant4vmc
      $<IF:$<TARGET_EXISTS:FairRoot::FastSim>,FairRoot::FastSim,>  # FairFastSimRunConfiguration
  )
endif()

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
