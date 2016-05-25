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
#  Pythia6_FOUND - system has Pythia6
#  Pythia6_LIBRARY_DIR - The libraries directory for Pythia6
#

if (Pythia6_LIBRARY_DIR)
  SET (Pythia6_LIBRARY_DIR Pythia6_LIBRARY_DIR-NOTFOUND)
endif (Pythia6_LIBRARY_DIR)

MESSAGE(STATUS "Looking for Pythia6...")

FIND_PATH(Pythia6_LIBRARY_DIR NAMES libPythia6.so PATHS
  ${Pythia6_DIR}/lib
  ${AlFa_DIR}/lib
  ${SIMPATH}/lib
  ${SIMPATH}/generators/lib
  NO_DEFAULT_PATH
)

if (Pythia6_LIBRARY_DIR)
  set(Pythia6_FOUND TRUE)
  Set(PYTHIA6_LIBRARY_DIR ${Pythia6_LIBRARY_DIR})
endif(Pythia6_LIBRARY_DIR)

if (Pythia6_FOUND)
  if (NOT Pythia6_FIND_QUIETLY)     
    MESSAGE(STATUS "Looking for Pythia6... - found ${Pythia6_LIBRARY_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${Pythia6_LIBRARY_DIR})
  endif (NOT Pythia6_FIND_QUIETLY)
else (Pythia6_FOUND)
  if (Pythia6_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for Pythia6... - Not found")
  endif (Pythia6_FIND_REQUIRED)
endif (Pythia6_FOUND)

