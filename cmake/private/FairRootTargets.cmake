################################################################################
# Copyright (C) 2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################


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
