################################################################################
# Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

macro(fairroot_check_out_of_source_build)
  if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not supported!")
  endif()
endmacro()

macro(fairroot_check_install_prefix)
  if(CMAKE_INSTALL_PREFIX STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Cannot install into the build directory!")
  endif()
endmacro()

macro(fairroot_check_platform)
  if(NOT UNIX)
    message(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
  endif()
endmacro()

macro(fairroot_sanity_checks)
  fairroot_check_out_of_source_build()
  fairroot_check_install_prefix()
  fairroot_check_platform()
endmacro()
