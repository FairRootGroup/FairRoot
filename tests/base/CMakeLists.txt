################################################################################
#   Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Test suite for the `FairRoot::Base` library

set(suite Base)
set(exe "${test_prefix}_${suite}")
add_executable(${exe}
  dummy_example.cxx # remove me once first real tests are added
  # add more test files if appropriate
)
target_link_libraries(${exe} PRIVATE Catch2::Catch2WithMain)
fairroot_discover_catch2_tests(${exe} SUITE ${suite})
