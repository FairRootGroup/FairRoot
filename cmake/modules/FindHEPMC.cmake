 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find HEPMC instalation
# Once done this will define
#



MESSAGE(STATUS "Looking for HepMC ...")

FIND_PATH(HEPMC_INCLUDE_DIR NAMES HepMC/HepMCDefs.h PATHS
  ${HEPMC_DIR}/include
  ${AlFa_DIR}/include
  ${SIMPATH}/include/
  NO_DEFAULT_PATH
)

FIND_PATH(HEPMC_LIB_DIR  NAMES libHepMC.so PATHS
  ${HEPMC_DIR}/lib
  ${AlFa_DIR}/lib
  ${SIMPATH}/lib
  NO_DEFAULT_PATH
)

if (HEPMC_INCLUDE_DIR AND HEPMC_LIB_DIR)
   set(HEPMC_FOUND TRUE)
endif (HEPMC_INCLUDE_DIR AND HEPMC_LIB_DIR)

if (HEPMC_FOUND)
  if (NOT HEPMC_FOUND_QUIETLY)
    MESSAGE(STATUS "Looking for HepMC... - found ${HEPMC_LIB_DIR}")
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${HEPMC_LIB_DIR})
  endif (NOT HEPMC_FOUND_QUIETLY)
else (HEPMC_FOUND)
  if (HEPMC_FOUND_REQUIRED)
    message(FATAL_ERROR "Looking for HepMC... - Not found")
  endif (HEPMC_FOUND_REQUIRED)
endif (HEPMC_FOUND)

