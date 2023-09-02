################################################################################
#    Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

if(BUILD_TESTING)
  Include(FetchContent)

  FetchContent_Declare(
    Catch2
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/Catch2_v3.4.0
    # GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    # GIT_TAG        v3.4.0
  )

  FetchContent_MakeAvailable(Catch2)

  # Include `Catch` module for the `catch_discover_tests` command, see
  # https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md#customization
  list(PREPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
  set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" PARENT_SCOPE)
  include(Catch)
endif()
