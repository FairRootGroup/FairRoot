 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Find FairRoot installation 
# Check the environment variable "FAIRROOTPATH"

if(FairRoot_DIR)
  SET(FAIRROOTPATH ${FairRoot_DIR})
else()
  IF(NOT DEFINED ENV{FAIRROOTPATH})
        MESSAGE(FATAL_ERROR "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot. Please set this variable and execute cmake again.")
    ENDIF(NOT DEFINED ENV{FAIRROOTPATH})
 
    SET(FAIRROOTPATH $ENV{FAIRROOTPATH})
endif()

MESSAGE(STATUS "Setting FairRoot environment…")

FIND_PATH(FAIRROOT_INCLUDE_DIR NAMES FairRun.h  PATHS
  ${FAIRROOTPATH}/include
  NO_DEFAULT_PATH
)

FIND_PATH(FAIRROOT_LIBRARY_DIR NAMES libBase.so libBase.dylib PATHS
   ${FAIRROOTPATH}/lib
  NO_DEFAULT_PATH
)

FIND_PATH(FAIRROOT_CMAKEMOD_DIR NAMES CMakeLists.txt  PATHS
   ${FAIRROOTPATH}/share/fairbase/cmake
  NO_DEFAULT_PATH
)


if(FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)
   set(FAIRROOT_FOUND TRUE)
   MESSAGE(STATUS "FairRoot ... - found ${FAIRROOTPATH}")
   MESSAGE(STATUS "FairRoot Library directory  :     ${FAIRROOT_LIBRARY_DIR}")
   MESSAGE(STATUS "FairRoot Include path…      :     ${FAIRROOT_INCLUDE_DIR}")
   MESSAGE(STATUS "FairRoot Cmake Modules      :     ${FAIRROOT_CMAKEMOD_DIR}")

else(FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)
   set(FAIRROOT_FOUND FALSE)
   MESSAGE(FATAL_ERROR "FairRoot installation not found")
endif (FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)

