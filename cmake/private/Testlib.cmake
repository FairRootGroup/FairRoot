################################################################################
# Copyright (C) 2020-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

macro(fairroot_ctest_setup)
  cmake_host_system_information(RESULT fqdn QUERY FQDN)

  if(NOT CTEST_SOURCE_DIRECTORY)
    set(CTEST_SOURCE_DIRECTORY .)
  endif()
  if(NOT CTEST_BINARY_DIRECTORY)
    set(CTEST_BINARY_DIRECTORY build)
  endif()
  set(CTEST_PROJECT_NAME "FairRoot")
  set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
  set(CTEST_USE_LAUNCHERS ON)

  if ("$ENV{CTEST_SITE}" STREQUAL "")
    set(CTEST_SITE "${fqdn}")
  else()
    set(CTEST_SITE $ENV{CTEST_SITE})
  endif()
endmacro()

macro(get_NCPUS)
  if(NOT NCPUS)
    if(DEFINED ENV{SLURM_CPUS_PER_TASK})
      set(NCPUS $ENV{SLURM_CPUS_PER_TASK})
      set(NCPUS_SOURCE "SLURM_CPUS_PER_TASK")
    elseif(DEFINED ENV{SLURM_JOB_CPUS_PER_NODE})
      set(NCPUS $ENV{SLURM_JOB_CPUS_PER_NODE})
      set(NCPUS_SOURCE "SLURM_JOB_CPUS_PER_NODE")
    else()
      include(ProcessorCount)
      ProcessorCount(NCPUS)
      if(NCPUS EQUAL 0)
        set(NCPUS 1)
      endif()
      set(NCPUS_SOURCE "ProcessorCount()")
    endif()
  else()
    set(NCPUS_SOURCE "Already-Set")
  endif()
  message(STATUS " NCPUS ................: ${NCPUS} (from ${NCPUS_SOURCE})")
endmacro()

macro(get_os_name_release)
  find_program(LSB_RELEASE_EXEC lsb_release)
  if(NOT LSB_RELEASE_EXEC)
    # message(WARNING "lsb_release not found")
    cmake_host_system_information(RESULT os_name QUERY OS_NAME)
    cmake_host_system_information(RESULT os_release QUERY OS_RELEASE)
  else()
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -si
      OUTPUT_VARIABLE os_name
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -sr
      OUTPUT_VARIABLE os_release
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -sd
      OUTPUT_VARIABLE os_description
      OUTPUT_STRIP_TRAILING_WHITESPACE)
  endif()
  if(NOT os_description)
    set(os_description "${os_name}-${os_release}")
  endif()
  message(STATUS " OS Description .......: ${os_description}")
endmacro()

macro(show_jenkins_info)
    if(DEFINED ENV{CHANGE_URL})
        message(STATUS " Pull / Merge Request .: $ENV{CHANGE_URL}")
    endif()
    if(DEFINED ENV{BRANCH_NAME})
        message(STATUS " BRANCH_NAME ..........: $ENV{BRANCH_NAME}")
        # For a Pull Request, this usually is some identifier of the PR
        # Otherwise the branch being built
    endif()
    if(DEFINED ENV{CHANGE_ID})
        message(STATUS " CHANGE_ID ............: $ENV{CHANGE_ID}")
        # If set at all, then this is a Pull Request
    endif()
    if(DEFINED ENV{CHANGE_TARGET})
        message(STATUS " CHANGE_TARGET ........: $ENV{CHANGE_TARGET}")
    endif()
    if(DEFINED ENV{JOB_NAME})
        message(STATUS " JOB_NAME .............: $ENV{JOB_NAME}")
    endif()
    if(DEFINED ENV{BUILD_TAG})
        message(STATUS " BUILD_TAG ............: $ENV{BUILD_TAG}")
        # Mostly used as a unique id to create directories
    endif()
endmacro()

function(fairroot_ctest_submit)
    cmake_parse_arguments(PARSE_ARGV 0 ARGS "FINAL" "" "")
    foreach(env_var IN ITEMS http_proxy HTTP_PROXY https_proxy HTTPS_PROXY)
        if("$ENV{${env_var}}" MATCHES ".*proxy.gsi[.]de.*")
            set(old_${env_var} "$ENV{${env_var}}")
            set(ENV{${env_var}})
            message(STATUS "safed ${env_var}: ${old_${env_var}}")
        endif()
    endforeach()
    if(ARGS_FINAL)
        ctest_submit(RETURN_VALUE _ctest_submit_ret_val
                     BUILD_ID cdash_build_id)
        set(cdash_build_id "${cdash_build_id}" PARENT_SCOPE)
    else()
        ctest_submit(RETURN_VALUE _ctest_submit_ret_val)
    endif()
    foreach(env_var IN ITEMS http_proxy HTTP_PROXY https_proxy HTTPS_PROXY)
        if(DEFINED old_${env_var})
            set(ENV{${env_var}} "${old_${env_var}}")
            message(STATUS "(restored ${env_var}: $ENV{${env_var}})")
        endif()
    endforeach()

    if(_ctest_submit_ret_val)
        message(WARNING " ctest_submit() failed. Continueing")
    endif()
endfunction()

function(fairroot_summary_cdash)
    if(cdash_build_id)
        message(STATUS " CDash Build Summary ..: "
                "${CTEST_DROP_METHOD}://${CTEST_DROP_SITE}/buildSummary.php?buildid=${cdash_build_id}")
        message(STATUS " CDash Test List ......: "
                "${CTEST_DROP_METHOD}://${CTEST_DROP_SITE}/viewTest.php?buildid=${cdash_build_id}")
    else()
        message(STATUS "  /!\\  CDash submit likely failed")
    endif()
    message(STATUS " ")
endfunction()
