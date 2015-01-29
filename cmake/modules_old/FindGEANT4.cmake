 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find GEANT4
# Once done this will define
#
#  GEANT4_FOUND - system has GEANT4
#  GEANT4_INCLUDE_DIR - the GEANT4 include directory
#  GEANT4_LIBRARIES - The libraries needed to use GEANT4
#  GEANT4_DEFINITIONS - Compiler switches required for using GEANT4
#

if (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR)
  SET (GEANT4_INCLUDE_DIR GEANT4_INCLUDE_DIR-NOTFOUND)
  SET (GEANT4_LIB_DIR GEANT4_LIB_DIR-NOTFOUND)
  SET (GEANT4_PLISTS_LIB_DIR GEANT4_PLISTS_LIB_DIR-NOTFOUND)
  SET (GEANT4_DIR GEANT4_DIR-NOTFOUND)
endif (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR)

MESSAGE(STATUS "Looking for GEANT4...")

FIND_PATH(GEANT4_DIR NAMES geant4-config PATHS
  ${SIMPATH}/transport/geant4/bin
  ${SIMPATH}/bin
  NO_DEFAULT_PATH
)

If(GEANT4_DIR)
  Set(PATH ${PATH} ${GEANT4_DIR})
EndIf(GEANT4_DIR)


FIND_PATH(GEANT4_INCLUDE_DIR NAMES G4Event.hh PATHS
  ${SIMPATH}/transport/geant4/include
  ${SIMPATH}/transport/geant4/include/geant4
  ${SIMPATH}/transport/geant4/include/Geant4
  ${SIMPATH}/include/geant4
  ${SIMPATH}/include/Geant4
  NO_DEFAULT_PATH
)

SET(GEANT4_INCLUDE_DIR
  ${GEANT4_INCLUDE_DIR}
  ${SIMPATH}/transport/geant4/source/interfaces/common/include 
  ${SIMPATH}/transport/geant4/physics_lists/hadronic/Packaging/include   
  ${SIMPATH}/transport/geant4/physics_lists/hadronic/QGSP/include
)

FIND_PATH(GEANT4_LIB_DIR NAMES libG3toG4.so PATHS
  ${SIMPATH}/transport/geant4/lib/Linux-g++
  ${SIMPATH}/transport/geant4/lib/Linux-icc
  ${SIMPATH}/transport/geant4/lib
  ${SIMPATH}/lib
  NO_DEFAULT_PATH
)

IF (GEANT4_LIB_DIR)
  SET(GEANT4_LIBRARY_DIR ${GEANT4_LIB_DIR})
ENDIF (GEANT4_LIB_DIR)

if (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR)
   set(GEANT4_FOUND TRUE)
endif (GEANT4_INCLUDE_DIR AND GEANT4_LIBRARY_DIR)


if (GEANT4_FOUND)
  if (NOT GEANT4_FIND_QUIETLY)
    MESSAGE(STATUS "Looking for GEANT4... - found ${GEANT4_LIBRARY_DIR}")
#    message(STATUS "Found ${GEANT4_LIBRARY_DIR}")
  endif (NOT GEANT4_FIND_QUIETLY)
  SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${GEANT4_LIBRARY_DIR})
else (GEANT4_FOUND)
  if (GEANT4_FIND_REQUIRED)
    message(FATAL_ERROR "Looking for GEANT4... - Not found")
  endif (GEANT4_FIND_REQUIRED)
endif (GEANT4_FOUND)

