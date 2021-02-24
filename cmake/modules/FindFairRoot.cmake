 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Find FairRoot installation 
# Check the environment variable "FAIRROOTPATH"

if(FairRoot_DIR)
  set(FAIRROOTPATH ${FairRoot_DIR})
else()
  if(NOT DEFINED ENV{FAIRROOTPATH})
    set(user_message "You did not define the environment variable FAIRROOTPATH which is needed to find FairRoot.\
         Please set this variable and execute cmake again." )
    if(FairRoot_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR ${user_message})
    else(FairRoot_FIND_REQUIRED)
      MESSAGE(WARNING ${user_message})
      return()
    endif(FairRoot_FIND_REQUIRED)
  endif(NOT DEFINED ENV{FAIRROOTPATH})

  set(FAIRROOTPATH $ENV{FAIRROOTPATH})
endif()

MESSAGE(STATUS "Setting FairRoot environment:")

FIND_PATH(FAIRROOT_INCLUDE_DIR NAMES FairRun.h PATHS
  ${FAIRROOTPATH}/include
  NO_DEFAULT_PATH
)

FIND_PATH(FAIRROOT_LIBRARY_DIR NAMES libBase.so libBase.dylib PATHS
   ${FAIRROOTPATH}/lib
   ${FAIRROOTPATH}/lib64
  NO_DEFAULT_PATH
)

FIND_PATH(FAIRROOT_CMAKEMOD_DIR NAMES CMakeLists.txt  PATHS
   ${FAIRROOTPATH}/share/fairbase/cmake
  NO_DEFAULT_PATH
)

# look for exported FairMQ targets and include them
find_file(_fairroot_fairmq_cmake
    NAMES FairMQ.cmake
    HINTS ${FAIRROOTPATH}/include/cmake
)
if(_fairroot_fairmq_cmake)
    include(${_fairroot_fairmq_cmake})
endif()

if(FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)
   set(FAIRROOT_FOUND TRUE)
   MESSAGE(STATUS "  FairRoot prefix            : ${FAIRROOTPATH}")
   MESSAGE(STATUS "  FairRoot Library directory : ${FAIRROOT_LIBRARY_DIR}")
   MESSAGE(STATUS "  FairRoot Include path      : ${FAIRROOT_INCLUDE_DIR}")
   MESSAGE(STATUS "  FairRoot Cmake Modules     : ${FAIRROOT_CMAKEMOD_DIR}")

else(FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)
   set(FAIRROOT_FOUND FALSE)
   MESSAGE(FATAL_ERROR "FairRoot installation not found")
endif (FAIRROOT_INCLUDE_DIR AND FAIRROOT_LIBRARY_DIR)

