 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# - Try to find HEPMC instalation
# Once done this will define
#



#MESSAGE(STATUS "Looking for HepMC ...")

FIND_PATH(HEPMC_INCLUDE_DIR NAMES HepMC/HepMCDefs.h PATHS
  ${HEPMC_DIR}/include
  ${SIMPATH}/include/
)

FIND_PATH(HEPMC_LIB_DIR  NAMES libHepMC.so libHepMC.dylib PATHS
  ${HEPMC_DIR}
  ${SIMPATH}
  PATH_SUFFIXES lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${CMAKE_FIND_PACKAGE_NAME}
     REQUIRED_VARS HEPMC_INCLUDE_DIR HEPMC_LIB_DIR)

if (HEPMC_FOUND)
    SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${HEPMC_LIB_DIR})
endif (HEPMC_FOUND)
