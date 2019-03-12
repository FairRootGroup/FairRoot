################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
# - Try to find VGM
# Once done this will define
#
#  VGM_FOUND - system has VGM
#  VGM_INCLUDE_DIR - the VGM include directory
#  VGM_LIBRARIES - The libraries needed to use VGM
#  VGM_DEFINITIONS - Compiler switches required for using VGM


#MESSAGE(STATUS "Looking for VGM...")

FIND_PATH(VGM_LIBRARY_DIR NAMES libBaseVGM.so libBaseVGM.dylib PATHS
  ${SIMPATH}/transport/vgm/lib/Linux-g++
  ${SIMPATH}/transport/vgm/lib/Linux-icc
  ${SIMPATH}/transport/vgm/lib
  ${SIMPATH}/lib
  ${VGM_ROOT}/lib
  NO_DEFAULT_PATH
)

SUBDIRLIST (SUBDIRS ${VGM_LIBRARY_DIR})

FOREACH(subdir ${SUBDIRS})
  SET(fullpath_subdir ${VGM_LIBRARY_DIR}/${subdir})
  FIND_PATH(VGM_CONFIG_DIR NAMES VGMConfigVersion.cmake PATHS ${fullpath_subdir})
  if(EXISTS ${VGM_CONFIG_DIR}/VGMConfigVersion.cmake)
      include(${VGM_CONFIG_DIR}/VGMConfig.cmake)
      include(${VGM_CONFIG_DIR}/VGMConfigVersion.cmake)
      set(VGM_VERSION ${PACKAGE_VERSION})
      set(VGM_ROOT ${VGM_LIBRARY_DIR})
   endif()
ENDFOREACH()


if (VGM_LIBRARY_DIR)
  if (NOT VGM_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for VGM... - found  ${VGM_LIBRARY_DIR}")
  endif (NOT VGM_FIND_QUIETLY)
else (VGM_LIBRARY_DIR)
  if (VGM_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for VGM... - Not found ")
  endif (VGM_FIND_REQUIRED)
endif (VGM_LIBRARY_DIR)

Set(VGM_INCLUDE_DIR ${VGM_INCLUDE_DIR})
Set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${VGM_LIBRARY_DIR})
Set(VGM_FOUND TRUE)
