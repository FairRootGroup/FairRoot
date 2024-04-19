################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::ExSimulation1` library

# Linking transitively against FairRoot::FastSim fails on some Linux systems due
# to missing RUNPATH entries in various dependencies, workaround by setting
# $LD_LIBRARY_PATH, see https://github.com/FairRootGroup/FairRoot/issues/1523
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(workaround ENABLE_LD_LIBRARY_PATH_WORKAROUND)
else()
  set(workaround)
endif()

set(suite ExSimulation1)
set(exe "${test_prefix}_${suite}")
add_executable(${exe}
  test_FairTutorialDet1Geo.cxx
)
target_link_libraries(${exe} PRIVATE
  FairRoot::ExSimulation1
  FairRoot::GeoBase_checks
  Catch2::Catch2WithMain
)
fairroot_discover_catch2_tests(${exe} SUITE ${suite} ${workaround})
