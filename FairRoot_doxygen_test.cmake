################################################################################
# Copyright (C) 2020-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# Specific Input Parameters:
set(WEB_PATH "/shared/alfaci/web")
set(WEB_URL_BASE "http://lxci001.gsi.de/ci")
if (DEFINED ENV{WEB_PATH})
  set(WEB_PATH "$ENV{WEB_PATH}")
endif()
if (DEFINED ENV{WEB_URL_BASE})
  set(WEB_URL_BASE "$ENV{WEB_URL_BASE}")
endif()

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

ctest_build(TARGET DoxygenDoc FLAGS ""
            NUMBER_ERRORS _ctest_build_num_errs
            RETURN_VALUE _ctest_build_ret_val)

if(_ctest_build_ret_val OR _ctest_build_num_errs)
  message(STATUS "Skipping Publishing, because build failed"
          " (return value: ${_ctest_build_ret_val},"
          " number of errors: ${_ctest_build_num_errs})")
else()
  if (DEFINED ENV{CHANGE_ID} AND NOT ("$ENV{BUILD_TAG}" STREQUAL ""))
    # This is a Pull Request (CHANGE_ID set at all)
    # and we have a unique id for the build to create a directory from
    set(midpart "tmp/$ENV{BUILD_TAG}")
  elseif(NOT ("$ENV{BRANCH_NAME}" STREQUAL ""))
    # Branch Build, we need a value for the branch name
    set(midpart "${CTEST_PROJECT_NAME}/$ENV{BRANCH_NAME}")
  endif()
  # midpart is the middle part of the directory for publishing
  if (midpart AND IS_DIRECTORY "${WEB_PATH}")
    get_filename_component(parent "${WEB_PATH}/${midpart}" DIRECTORY)
    file(MAKE_DIRECTORY "${parent}")
    # Just in case, remove the target directory
    file(REMOVE_RECURSE "${WEB_PATH}/${midpart}")
    # In theory we should "install with component Doxygen".
    # Copying a few thousand files via NFS isn't fun.
    # We run on the same FS anyhow. Let's move.
    file(RENAME "${CTEST_BINARY_DIRECTORY}/doxygen/doc/html"
                "${WEB_PATH}/${midpart}")
    message(STATUS " See: ${WEB_PATH}/tmp/$ENV{BUILD_TAG}")
    set(web_url "${WEB_URL_BASE}/${midpart}")
  endif()
endif()

ctest_submit()

if (web_url)
  file(WRITE "build/generated-doxygen.url" "${web_url}")
  message(STATUS " Created Doxygen URL ..: ${web_url}")
endif()
