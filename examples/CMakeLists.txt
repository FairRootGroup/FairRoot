################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(BUILD_MBS)
  add_subdirectory(advanced/MbsTutorial)
endif()

if(BUILD_SIM)
  add_subdirectory(common/passive)
  add_subdirectory(common/mcstack)
  add_subdirectory(common/gconfig)
  add_subdirectory(simulation/Tutorial1)
  add_subdirectory(simulation/Tutorial2)
  add_subdirectory(simulation/Tutorial4)
  add_subdirectory(simulation/rutherford)
  add_subdirectory(advanced/propagator)
endif()

if(BUILD_MQ)
  add_subdirectory(MQ/Lmd)
  add_subdirectory(MQ/histogramServer)
endif()

if(BUILD_SIM AND BUILD_MQ)
  add_subdirectory(MQ/parameters)
  add_subdirectory(MQ/serialization)
  add_subdirectory(MQ/pixelDetector)
  add_subdirectory(MQ/pixelAlternative)
  add_subdirectory(MQ/pixelSimSplit)
  add_subdirectory(advanced/Tutorial3)
endif()
