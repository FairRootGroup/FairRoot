################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Tutorial1)

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

fairroot_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)
fairroot_copy(HEADERS ${headers} TO ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
fairroot_add_standard_library_properties(${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}>
  $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCDIR}>
)

target_link_libraries(${target} PUBLIC
  FairRoot::Base # FairRunIdGenerator
  FairRoot::FairTools # FairLogger
  FairRoot::MCStack
  FairRoot::FairFastSim
  FairRoot::ParBase
  FairRoot::Passive
  FairRoot::Gen

  Boost::program_options

  ROOT::Core
  ROOT::Physics
  ROOT::Geom
  ${VMC_LIB} # TVirtualMC
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF Tutorial1LinkDef.h
)

install(TARGETS ${target}
  EXPORT ${PROJECT_EXPORT_SET}
  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers}
  DESTINATION ${PROJECT_INSTALL_INCDIR})

add_executable(tut1 runTutorial1.cxx)
target_link_libraries(tut1 PRIVATE Tutorial1)

install(TARGETS tut1
  RUNTIME DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial1/bin
)
