################################################################################
# Copyright (C) 2020-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

list(PREPEND CMAKE_MODULE_PATH "cmake/private")
include(Testlib)

fairroot_ctest_setup()

if ("$ENV{LABEL}" STREQUAL "")
  set(CTEST_BUILD_NAME "format-check")
else()
  set(CTEST_BUILD_NAME $ENV{LABEL})
endif()

show_jenkins_info()

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
