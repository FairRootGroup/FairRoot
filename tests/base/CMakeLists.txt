################################################################################
# Copyright (C) 2023-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::Base` library

set(suite Base)
set(exe "${test_prefix}_${suite}")
add_executable(${exe}
  sim/test_FairVolumeList.cxx
)
target_link_libraries(${exe} PRIVATE FairRoot::Base Catch2::Catch2WithMain)
catch_discover_tests(${exe} TEST_PREFIX "${suite}::")
