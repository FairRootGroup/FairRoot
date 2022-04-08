################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_subdirectory(common/passive)
add_subdirectory(common/mcstack)

set(mcEngine_list TGeant4)

if(Geant3_FOUND)
  if(ENABLE_GEANT3_TESTING)
    list(APPEND mcEngine_list TGeant3)
  endif()
  if(TARGET FairRoot::EventDisplay)
    add_subdirectory(common/eventdisplay)
  endif()
  if(TARGET MCConfigurator)
    add_subdirectory(common/gconfig)
  endif()

  if(TARGET FairFastSim)
    add_subdirectory(simulation/Tutorial1)
  endif()
  if(TARGET FairRoot::EventDisplay)
    add_subdirectory(advanced/propagator)
  endif()

  add_subdirectory(simulation/Tutorial4)
  if(FairMQ_FOUND AND Boost_FOUND)
    add_subdirectory(MQ/parameters)
    add_subdirectory(MQ/serialization)
    add_subdirectory(advanced/Tutorial3)
  endif()
  add_subdirectory(simulation/rutherford)
endif()

add_subdirectory(simulation/Tutorial2)

if(BUILD_MBS)
  add_subdirectory(advanced/MbsTutorial)
endif()

if(FairMQ_FOUND AND Boost_FOUND)
  set(pixel_simulation_engine "TGeant4")
  add_subdirectory(MQ/pixelDetector)
  add_subdirectory(MQ/pixelAlternative)
  add_subdirectory(MQ/pixelSimSplit)
  if(BUILD_MBS)
    add_subdirectory(MQ/Lmd)
  endif()
  add_subdirectory(MQ/histogramServer)
endif()

install(DIRECTORY
  common/gconfig
  common/geometry
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/common
)
