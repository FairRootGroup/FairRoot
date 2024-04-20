################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Linking transitively against FairRoot::FastSim fails on some Linux systems due
# to missing RUNPATH entries in various dependencies, workaround by setting
# $LD_LIBRARY_PATH, see https://github.com/FairRootGroup/FairRoot/issues/1523
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(workaround ENABLE_LD_LIBRARY_PATH_WORKAROUND)
else()
  set(workaround)
endif()

fairroot_add_catch2_test_suite(ExSimulation1
  SOURCES
  test_FairTutorialDet1Geo.cxx

  DEPENDENCIES
  FairRoot::ExSimulation1
  FairRoot::GeoBase_checks

  ${workaround}
)
