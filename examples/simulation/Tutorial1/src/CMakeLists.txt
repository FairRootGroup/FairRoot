################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target ExSimulation1)

set(sources
  FairFastSimExample.cxx
  FairFastSimExample2.cxx
  FairSimConfig.cxx
  FairTutorialDet1.cxx
  FairTutorialDet1ContFact.cxx
  FairTutorialDet1Geo.cxx
  FairTutorialDet1GeoPar.cxx
  FairTutorialDet1Point.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::Tools # FairLogger
  FairRoot::FairFastSim
  FairRoot::ParBase
  FairRoot::ExPassive
  FairRoot::ExMCStack
  FairRoot::Gen

  Boost::program_options

  ROOT::Core
  ROOT::Physics
  ROOT::Geom
  ${VMCLIB}
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF Tutorial1LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_executable(tut1 runTutorial1.cxx)
target_link_libraries(tut1 PRIVATE ExSimulation1)

install(TARGETS tut1
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial1/bin
)
