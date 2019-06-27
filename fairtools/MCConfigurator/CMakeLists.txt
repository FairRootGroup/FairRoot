 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/logger
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/sim/fastsim
  ${CMAKE_SOURCE_DIR}/fairtools/MCConfigurator
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${Geant3_INCLUDE_DIRS}
  ${Geant4_INCLUDE_DIRS}
  ${Geant4VMC_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIR}
)

Include_Directories( ${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Geant3_LIBRARY_DIR}
  ${Geant4_LIBRARY_DIR}
  ${Geant4VMC_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})

Set(HEADERS
FairYamlVMCConfig.h
)
Set(SRCS
FairYamlVMCConfig.cxx
)

Set(LINKDEF MCConfiguratorLinkDef.h)
Set(DEPENDENCIES Base FairTools geant321 geant4vmc Pythia6 FairFastSim yaml-cpp)
Set(LIBRARY_NAME MCConfigurator)

GENERATE_LIBRARY()
