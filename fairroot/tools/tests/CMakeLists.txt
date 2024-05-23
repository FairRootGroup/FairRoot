################################################################################
#    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(suite "${target}")
set(exe "${test_prefix}_${suite}")
add_executable(${exe}
  maybe_owning.cxx
)
target_link_libraries(${exe}
  PRIVATE
    FairRoot::Tools
    Catch2::Catch2WithMain
)
catch_discover_tests(${exe} TEST_PREFIX "${suite}::")
