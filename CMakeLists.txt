################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

cmake_minimum_required(VERSION 3.9.4 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
include(FairRootInit)

set_fairroot_cmake_policies()
get_fairroot_version()

project(FairRoot VERSION ${FAIRROOT_VERSION} LANGUAGES C CXX)
message("${BWhite}${PROJECT_NAME}${CR} ${PROJECT_VERSION} (${FAIRROOT_GIT_VERSION}) from ${FAIRROOT_DATE}")

include(FairRootMacros)

# Build options
include(${CMAKE_SOURCE_DIR}/cmake/BuildOptions.cmake)

# Check/configure compiler and build profiles
include(${CMAKE_SOURCE_DIR}/cmake/Compiler.cmake)
message("Compiling on ${BWhite}${FAIRROOT_SYSTEM}/${FAIRROOT_COMPILER}${CR} with build profile ${BWhite}${CMAKE_BUILD_TYPE}${CR}")

# Misc config
include(${CMAKE_SOURCE_DIR}/cmake/Misc.cmake)

# Package dependencies
include(${CMAKE_SOURCE_DIR}/cmake/Dependencies.cmake)

# Sources
include(${CMAKE_SOURCE_DIR}/cmake/Sources.cmake)

# Setup ROOT Macro Runtime
include(${CMAKE_SOURCE_DIR}/cmake/Runtime.cmake)

# Installation
include(${CMAKE_SOURCE_DIR}/cmake/Installation.cmake)
