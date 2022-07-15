################################################################################
# Copyright (C) 2020-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

cmake_host_system_information(RESULT fqdn QUERY FQDN)

set(CTEST_SOURCE_DIRECTORY .)
set(CTEST_BINARY_DIRECTORY build)
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

get_filename_component(test_install_prefix "${CTEST_BINARY_DIRECTORY}/install"
                       ABSOLUTE)
list(APPEND options
  "-DDISABLE_COLOR=ON"
  "-DBUILD_DOXYGEN=ON"
  "-DCMAKE_INSTALL_PREFIX:PATH=${test_install_prefix}"
)
ctest_configure(OPTIONS "${options}")

ctest_build(TARGET DoxygenDoc FLAGS "")

ctest_submit()
