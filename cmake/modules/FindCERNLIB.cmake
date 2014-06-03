 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find CERNLIB
# Once done this will define
#
#  CERNLIB_FOUND - system has CERNLIB
#### (not needed)  CERNLIB_INCLUDE_DIR - the CERNLIB include directory
#  CERNLIB_LIBRARIES - The libraries needed to use CERNLIB
#### (not needed)  CERNLIB_DEFINITIONS - Compiler switches required for using CERNLIB
#

if (CERNLIB_INCLUDE_DIR AND CERNLIB_LIBRARY_DIR)
  SET (CERNLIB_INCLUDE_DIR CERNLIB_INCLUDE_DIR-NOTFOUND)
  SET (CERNLIB_LIB_DIR CERNLIB_LIB_DIR-NOTFOUND)
  SET (CERNLIB_PLISTS_LIB_DIR CERNLIB_PLISTS_LIB_DIR-NOTFOUND)
endif (CERNLIB_INCLUDE_DIR AND CERNLIB_LIBRARY_DIR)

MESSAGE(STATUS "Looking for CERNLIB...")

FIND_PATH(CERNLIB_INCLUDE_DIR NAMES CERNLIB PATHS
  ${SIMPATH}/cern/include
  $ENV{CERN_ROOT}/include
  NO_DEFAULT_PATH
)

FIND_PATH(CERNLIB_LIBRARY_DIR NAMES libgeant.a libmathlib.a PATHS
  ${SIMPATH}/cern/lib
  $ENV{CERN_ROOT}/lib
  NO_DEFAULT_PATH
)

if (CERNLIB_LIBRARY_DIR)
   set(CERNLIB_FOUND TRUE)
endif (CERNLIB_LIBRARY_DIR)

if (CERNLIB_FOUND)
  if (NOT CERNLIB_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for CERNLIB... - found ${CERNLIB_LIBRARY_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${CERNLIB_LIBRARY_DIR})
  endif (NOT CERNLIB_FIND_QUIETLY)
else (CERNLIB_FOUND)
  if (CERNLIB_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for CERNLIB... - Not found")
  endif (CERNLIB_FIND_REQUIRED)
endif (CERNLIB_FOUND)

