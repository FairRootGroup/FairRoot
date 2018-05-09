################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

#############################
# FairRoot Macros/Functions #
#############################

# Defines some variables with console color escape sequences
if(NOT WIN32 AND NOT DISABLE_COLOR)
  string(ASCII 27 Esc)
  set(CR       "${Esc}[m")
  set(CB       "${Esc}[1m")
  set(Red      "${Esc}[31m")
  set(Green    "${Esc}[32m")
  set(Yellow   "${Esc}[33m")
  set(Blue     "${Esc}[34m")
  set(Magenta  "${Esc}[35m")
  set(Cyan     "${Esc}[36m")
  set(White    "${Esc}[37m")
  set(BRed     "${Esc}[1;31m")
  set(BGreen   "${Esc}[1;32m")
  set(BYellow  "${Esc}[1;33m")
  set(BBlue    "${Esc}[1;34m")
  set(BMagenta "${Esc}[1;35m")
  set(BCyan    "${Esc}[1;36m")
  set(BWhite   "${Esc}[1;37m")
endif()

# set_fairroot_cmake_policies()
#
# Sets CMake policies used by FairRoot.
macro(set_fairroot_cmake_policies)
  # Find more details to each policy with cmake --help-policy CMPXXXX
  foreach(policy
    CMP0025 # Compiler id for Apple Clang is now ``AppleClang``.
    CMP0028 # Double colon in target name means ALIAS or IMPORTED target.
    CMP0042 # MACOSX_RPATH is enabled by default.
    CMP0048 # The ``project()`` command manages VERSION variables.
    CMP0054 # Only interpret ``if()`` arguments as variables or keywords when unquoted.
  )
    if(POLICY ${policy})
      cmake_policy(SET ${policy} NEW)
    endif()
  endforeach()
endmacro()

find_package(Git QUIET)
# get_fairroot_version([DEFAULT_VERSION version] [DEFAULT_DATE date])
#
# Sets variables FAIRROOT_VERSION, FAIRROOT_GIT_VERSION, FAIRROOT_DATE, FAIRROOT_GIT_DATE
function(get_fairroot_version)
  cmake_parse_arguments(ARGS "" "DEFAULT_VERSION;DEFAULT_DATE" "" ${ARGN})

  if(GIT_FOUND AND EXISTS ${CMAKE_SOURCE_DIR}/.git)
      execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
      OUTPUT_VARIABLE FAIRROOT_GIT_VERSION
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    if(FAIRROOT_GIT_VERSION)
      # cut first two characters "v-"
      string(SUBSTRING ${FAIRROOT_GIT_VERSION} 1 -1 FAIRROOT_GIT_VERSION)
    endif()
    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd
      OUTPUT_VARIABLE FAIRROOT_GIT_DATE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
  endif()

  if(NOT FAIRROOT_GIT_VERSION)
    if(ARGS_DEFAULT_VERSION)
      set(FAIRROOT_GIT_VERSION ${ARGS_DEFAULT_VERSION})
    else()
      set(FAIRROOT_GIT_VERSION 0.0.0.0)
    endif()
  endif()
  
  if(NOT FAIRROOT_GIT_DATE)
    if(ARGS_DEFAULT_DATE)
      set(FAIRROOT_GIT_DATE ${ARGS_DEFAULT_DATE})
    else()
      set(FAIRROOT_GIT_DATE "Thu Jan 1 00:00:00 1970 +0000")
    endif()
  endif()

  string(REGEX MATCH "^([^-]*)" blubb ${FAIRROOT_GIT_VERSION})

  # return values
  set(FAIRROOT_VERSION ${CMAKE_MATCH_0} PARENT_SCOPE)
  set(FAIRROOT_DATE ${FAIRROOT_GIT_DATE} PARENT_SCOPE)
  set(FAIRROOT_GIT_VERSION ${FAIRROOT_GIT_VERSION} PARENT_SCOPE)
  set(FAIRROOT_GIT_DATE ${FAIRROOT_GIT_DATE} PARENT_SCOPE)
endfunction()
