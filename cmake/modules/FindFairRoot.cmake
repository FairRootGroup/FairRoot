################################################################################
# Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
# Find FairRoot installation
# Check the environment variable "FAIRROOTPATH"

include(FindPackageHandleStandardArgs)

if(NOT FAIRROOTPATH)
  set(FAIRROOTPATH "$ENV{FAIRROOTPATH}")
endif()

if(FAIRROOTPATH)
  list(PREPEND CMAKE_PREFIX_PATH "${FAIRROOTPATH}")
else()
  message(STATUS "INFO: FAIRROOTPATH not set, CMAKE_PREFIX_PATH should have the needed entries")
endif()

# recursive config mode find_package to
# find the new main config mode package
find_package(FairRoot CONFIG)

if(NOT FairRoot_FOUND)
  message(STATUS "FairRoot not found in config mode. Why?")
  message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
  find_package_handle_standard_args(FairRoot CONFIG_MODE)
  return()
endif()
set(FAIRROOTPATH "${FairRoot_PREFIX}")

MESSAGE(STATUS "Setting FairRoot environment:")
message(STATUS "  FairRoot Version           : ${FairRoot_VERSION}")
message(STATUS "  FairRoot CXX Standard      : ${FairRoot_CXX_STANDARD}")
message(STATUS "  FairRoot prefix            : ${FairRoot_PREFIX}")

FIND_PATH(FAIRROOT_INCLUDE_DIR NAMES FairRun.h PATHS
  ${FAIRROOTPATH}/include
)

FIND_PATH(FAIRROOT_LIBRARY_DIR NAMES libBase.so libBase.dylib PATHS
   ${FAIRROOTPATH}/lib
   ${FAIRROOTPATH}/lib64
)

if(FairRoot_CMAKE_MODULES_DIR)
  set(FAIRROOT_CMAKEMOD_DIR "${FairRoot_CMAKE_MODULES_DIR}"
    CACHE PATH "FairRoot CMake Modules Directory"
  )
else()
  FIND_PATH(FAIRROOT_CMAKEMOD_DIR
    NAMES modules/FindFairRoot.cmake modules/ROOTMacros.cmake
    PATHS ${FAIRROOTPATH}/share/fairbase/cmake
  )
endif()

find_package_handle_standard_args(FairRoot CONFIG_MODE
                                  REQUIRED_VARS FAIRROOT_INCLUDE_DIR
                                                FAIRROOT_LIBRARY_DIR)
if(FairRoot_FOUND)
   set(FAIRROOT_FOUND TRUE)
   MESSAGE(STATUS "  FairRoot Library directory : ${FAIRROOT_LIBRARY_DIR}")
   MESSAGE(STATUS "  FairRoot Include path      : ${FAIRROOT_INCLUDE_DIR}")
   MESSAGE(STATUS "  FairRoot Cmake Modules     : ${FAIRROOT_CMAKEMOD_DIR}")
else()
   set(FAIRROOT_FOUND FALSE)
endif()
