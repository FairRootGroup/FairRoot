################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Temporarily disabled, see https://github.com/FairRootGroup/FairRoot/issues/1523
# if(TARGET FairRoot::ExSimulation1)
#   add_subdirectory(simulation/Tutorial1)
# endif()
if(TARGET FairRoot::ExSimulation2)
  add_subdirectory(simulation/Tutorial2)
endif()
if(TARGET FairRoot::ExSimulation4)
  add_subdirectory(simulation/Tutorial4)
endif()
if(TARGET FairRoot::ExTestDetector)
  add_subdirectory(advanced/Tutorial3)
endif()
if(TARGET FairRoot::ExPropagator)
  add_subdirectory(advanced/propagator)
endif()
if(TARGET FairRoot::ExPixel)
  add_subdirectory(MQ/pixelDetector)
endif()
