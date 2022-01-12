################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(Geant3_FOUND)
  add_subdirectory(common/passive)
  add_subdirectory(common/mcstack)
  if(TARGET FairRoot::EventDisplay)
    add_subdirectory(common/eventdisplay)
  endif()
  if(TARGET MCConfigurator)
    add_subdirectory(common/gconfig)
  endif()

  if(TARGET FairFastSim)
    add_subdirectory(simulation/Tutorial1)
  endif()
  add_subdirectory(simulation/Tutorial2)
  if(TARGET FairRoot::EventDisplay)
    add_subdirectory(advanced/propagator)
  endif()

  add_subdirectory(simulation/Tutorial4)
  if(FairMQ_FOUND AND Boost_FOUND)
    add_subdirectory(MQ/parameters)
    add_subdirectory(MQ/serialization)
    if(TARGET FairMQ::fairmq-dds-command-ui)
      add_subdirectory(MQ/pixelDetector)
      add_subdirectory(MQ/pixelAlternative)
      add_subdirectory(MQ/pixelSimSplit)
    endif()
    add_subdirectory(advanced/Tutorial3)
  endif()
  add_subdirectory(simulation/rutherford)
endif()

if(FairMQ_FOUND AND Boost_FOUND)
  add_subdirectory(MQ/Lmd)
  add_subdirectory(MQ/histogramServer)
endif()

add_subdirectory(advanced/MbsTutorial)
