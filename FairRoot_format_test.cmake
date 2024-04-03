################################################################################
# Copyright (C) 2020-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

cmake_host_system_information(RESULT fqdn QUERY FQDN)

if(NOT CTEST_SOURCE_DIRECTORY)
  set(CTEST_SOURCE_DIRECTORY .)
endif()
if(NOT CTEST_BINARY_DIRECTORY)
  set(CTEST_BINARY_DIRECTORY build)
endif()
Set(CTEST_PROJECT_NAME "FairRoot")
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
set(CTEST_USE_LAUNCHERS ON)

if ("$ENV{CTEST_SITE}" STREQUAL "")
  set(CTEST_SITE "${fqdn}")
else()
  set(CTEST_SITE $ENV{CTEST_SITE})
endif()

if ("$ENV{LABEL}" STREQUAL "")
  set(CTEST_BUILD_NAME "format-check")
else()
  set(CTEST_BUILD_NAME $ENV{LABEL})
endif()

ctest_start(Experimental TRACK Checks)

ctest_configure(OPTIONS "-DDISABLE_COLOR=ON")

ctest_build(TARGET FormatCheck FLAGS "")

ctest_submit()
