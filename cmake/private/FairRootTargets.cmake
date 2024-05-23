################################################################################
# Copyright (C) 2021-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

include_guard(GLOBAL)

# Set the C++ language level on exported targets
#
# This is only meaningful on targets that later on are
# exported.
# It sets the C++ language level to CMAKE_CXX_STANDARD /
# PROJECT_MIN_CXX_STANDARD, so that projects that import the
# target use at least that language level to compile
# things.
function(fairroot_compile_features target)
  if (DEFINED CMAKE_CXX_STANDARD)
    set(standard ${CMAKE_CXX_STANDARD})
  elseif(DEFINED PROJECT_MIN_CXX_STANDARD)
    set(standard ${PROJECT_MIN_CXX_STANDARD})
  else()
    set(standard 11)
  endif()
  target_compile_features("${target}" INTERFACE cxx_std_${standard})
endfunction()


# Set some generic / general settings on exported targets
# - Export C++ language level
# - Set namespaced ALIAS to allow consistent target use
# - Set some generic PROPERTIES (VERSION, SOVERSION)
function(fairroot_library_settings target)
  fairroot_compile_features("${target}")
  add_library(FairRoot::${target} ALIAS ${target})
  get_target_property(target_type ${target} TYPE)
  if(NOT target_type STREQUAL "INTERFACE_LIBRARY")
    set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})
  endif()
endfunction()


set(PROJECT_EXPORT_SET FairRootTargets)


function(fairroot_install_exported)
  cmake_parse_arguments(PARSE_ARGV 0 ARGS "" "" "TARGETS")
  install(TARGETS ${ARGS_TARGETS}
    EXPORT ${PROJECT_EXPORT_SET}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${PROJECT_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
endfunction()


function(fairroot_discover_catch2_tests target)
  cmake_parse_arguments(PARSE_ARGV 1 ARGS "ENABLE_LD_LIBRARY_PATH_WORKAROUND" "SUITE" "")

  set(test_prefix "")
  if(ARGS_SUITE)
    set(test_prefix "${ARGS_SUITE}::")
  endif()

  set(dl_paths "")
  set(req_version 3.22)
  if(ARGS_ENABLE_LD_LIBRARY_PATH_WORKAROUND)
    set(dl_paths ${LD_LIBRARY_PATH})
  endif()

  if(dl_paths)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL ${req_version})
      catch_discover_tests(${target} TEST_PREFIX "${test_prefix}" DL_PATHS ${dl_paths})
    else()
      message(VERBOSE "Skipping tests discovery for target \"${target}\" "
                      "because CMake ${req_version} is required "
                      "(current: ${CMAKE_VERSION}).")
    endif()
  else()
    catch_discover_tests(${target} TEST_PREFIX "${test_prefix}")
  endif()
endfunction()


function(fairroot_add_catch2_test_suite suite)
  cmake_parse_arguments(PARSE_ARGV 1 ARGS
    "ENABLE_LD_LIBRARY_PATH_WORKAROUND" "" "SOURCES;DEPENDENCIES")

  if(NOT suite)
    message(AUTHOR_WARNING "First positional parameter <suite> required. Skipping.")
    return()
  endif()
  if(NOT ARGS_SOURCES)
    message(AUTHOR_WARNING "Parameter SOURCES required. Skipping.")
    return()
  endif()

  set(exe "test_${suite}")
  add_executable(${exe})
  target_sources(${exe} PRIVATE ${ARGS_SOURCES})
  target_link_libraries(${exe} PRIVATE Catch2::Catch2WithMain)
  if(ARGS_DEPENDENCIES)
    target_link_libraries(${exe} PRIVATE ${ARGS_DEPENDENCIES})
  endif()
  if(ARGS_ENABLE_LD_LIBRARY_PATH_WORKAROUND)
    fairroot_discover_catch2_tests(${exe} SUITE ${suite} ENABLE_LD_LIBRARY_PATH_WORKAROUND)
  else()
    fairroot_discover_catch2_tests(${exe} SUITE ${suite})
  endif()
endfunction()
