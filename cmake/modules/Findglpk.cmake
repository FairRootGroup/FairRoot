 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find GLPK instalation
# Once done this will define
#

MESSAGE(STATUS "Looking for GLPK ...")

FIND_PATH(GLPK_INCLUDE_DIR NAMES glpk.h PATHS
  ${SIMPATH}/basics/glpk/include 
  ${SIMPATH}/include 
  NO_DEFAULT_PATH
)

FIND_PATH(GLPK_LIB_DIR  NAMES libglpk.so PATHS
  ${SIMPATH}/basics/glpk/lib
  ${SIMPATH}/lib
  NO_DEFAULT_PATH
)

if (GLPK_INCLUDE_DIR AND GLPK_LIB_DIR)
   set(GLPK_FOUND TRUE)
endif (GLPK_INCLUDE_DIR AND GLPK_LIB_DIR)

if (GLPK_FOUND)
  if (NOT GLPK_FOUND_QUIETLY)
    MESSAGE(STATUS "Looking for GLPK... - found ${GLPK_LIB_DIR}")
#    message(STATUS "Found PLUTO: ${PLUTO_LIBRARY_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GLPK_LIB_DIR})
  endif (NOT GLPK_FOUND_QUIETLY)
else (GLPK_FOUND)
  if (GLPK_FOUND_REQUIRED)
    message(FATAL_ERROR "Looking for GLPK... - Not found")
  endif (GLPK_FOUND_REQUIRED)
endif (GLPK_FOUND)

