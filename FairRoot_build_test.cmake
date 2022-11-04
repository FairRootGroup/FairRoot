################################################################################
# Copyright (C) 2021-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

list(PREPEND CMAKE_MODULE_PATH "cmake/private")
include(Testlib)

fairroot_ctest_setup()

set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 102400)
set(CTEST_CONFIGURATION_TYPE "RelWithDebInfo")

if(NOT NCPUS)
  if(DEFINED ENV{SLURM_CPUS_PER_TASK})
    set(NCPUS $ENV{SLURM_CPUS_PER_TASK})
  elseif(DEFINED ENV{SLURM_JOB_CPUS_PER_NODE})
    set(NCPUS $ENV{SLURM_JOB_CPUS_PER_NODE})
  else()
    include(ProcessorCount)
    ProcessorCount(NCPUS)
    if(NCPUS EQUAL 0)
      set(NCPUS 1)
    endif()
  endif()
endif()

if ("$ENV{LABEL}" STREQUAL "")
  set(CTEST_BUILD_NAME "build")
else()
  set(CTEST_BUILD_NAME $ENV{LABEL})
endif()

show_jenkins_info()

ctest_start(Continuous)

get_filename_component(test_install_prefix "${CTEST_BINARY_DIRECTORY}/install"
                       ABSOLUTE)
list(APPEND options
  "-DDISABLE_COLOR=ON"
  "-DCMAKE_INSTALL_PREFIX:PATH=${test_install_prefix}"
)
if ((NOT DEFINED BUILD_MBS) OR BUILD_MBS)
  list(APPEND options "-DBUILD_MBS=ON")
endif()
if ((NOT DEFINED BUILD_PROOF_SUPPORT) OR BUILD_PROOF_SUPPORT)
  list(APPEND options "-DBUILD_PROOF_SUPPORT=ON")
endif()
if (USE_CLANG_TIDY)
  list(APPEND options "-DCMAKE_CXX_CLANG_TIDY=clang-tidy")
endif()
if ("$ENV{CHANGE_ID}" STREQUAL "")
  # Branch build
  list(APPEND options "-DENABLE_GEANT3_TESTING:BOOL=ON")
endif()
ctest_configure(OPTIONS "${options}")

ctest_build(FLAGS "-j${NCPUS}" TARGET install
            NUMBER_ERRORS _ctest_build_num_errs
            RETURN_VALUE _ctest_build_ret_val)

unset(repeat)
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.17)
  if ("$ENV{CHANGE_ID}" STREQUAL "")
    # Branch build
    set(repeat REPEAT UNTIL_PASS:7)
  endif()
endif()
if(_ctest_build_ret_val OR _ctest_build_num_errs)
  message(STATUS "Skipping tests, because build failed"
          " (return value: ${_ctest_build_ret_val},"
          " number of errors: ${_ctest_build_num_errs})")
  set(_ctest_test_ret_val -1)
else()
  ctest_test(BUILD "${CTEST_BINARY_DIRECTORY}"
             PARALLEL_LEVEL 4
             SCHEDULE_RANDOM ON
             ${repeat}
             RETURN_VALUE _ctest_test_ret_val)
endif()

fairroot_ctest_submit(FINAL)
fairroot_summary_cdash()

if(_ctest_test_ret_val)
  Message(FATAL_ERROR "Some tests failed.")
endif()
