################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::ExSimulation1` library

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
catch_discover_tests(${exe} TEST_PREFIX "${suite}::")
