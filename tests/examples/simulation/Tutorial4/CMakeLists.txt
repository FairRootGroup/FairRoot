################################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::ExSimulation4` library

set(suite ExSimulation4)
set(exe "${test_prefix}_${suite}")
add_executable(${exe}
  test_FairTutorialDet4Geo.cxx
)
target_link_libraries(${exe} PRIVATE
  FairRoot::ExSimulation4
  FairRoot::GeoBase_checks
  Catch2::Catch2WithMain
)
fairroot_discover_catch2_tests(${exe} SUITE ${suite})
