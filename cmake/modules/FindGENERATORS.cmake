 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find PLUTO instalation
# Once done this will define
#
#  GENERATORS_FOUND - system has PYTHIA6
#  GENERATORS_LIBRARY_DIR - The libraries directory for PYTHIA6
#

if (GENERATORS_LIBRARY_DIR)
  SET (GENERATORS_LIBRARY_DIR GENERATORS_LIBRARY_DIR-NOTFOUND)
endif (GENERATORS_LIBRARY_DIR)

MESSAGE(STATUS "Looking for Pythia6...")

FIND_PATH(PYTHIA6_LIBRARY_DIR NAMES libPythia6.so PATHS
  ${SIMPATH}/lib
  ${SIMPATH}/generators/lib
  NO_DEFAULT_PATH
)

if (PYTHIA6_LIBRARY_DIR)
  set(GENERATORS_FOUND TRUE)
  set(GENERATORS_LIBRARY_DIR ${PYTHIA6_LIBRARY_DIR})
endif(PYTHIA6_LIBRARY_DIR)

if (GENERATORS_FOUND)
  if (NOT GENERATORS_FIND_QUIETLY)     
    MESSAGE(STATUS "Looking for Pythia6... - found ${GENERATORS_LIBRARY_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GENERATORS_LIBRARY_DIR})
  endif (NOT GENERATORS_FIND_QUIETLY)
else (GENERATORS_FOUND)
  if (GENERATORS_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for Pythia6... - Not found")
  endif (GENERATORS_FIND_REQUIRED)
endif (GENERATORS_FOUND)

