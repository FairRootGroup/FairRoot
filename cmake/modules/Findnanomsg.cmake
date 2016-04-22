 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

MESSAGE(STATUS "Looking for nanomsg...")

find_path(NANOMSG_INCLUDE_DIR NAMES nn.h
  PATHS ${SIMPATH}/include/nanomsg
  NO_DEFAULT_PATH
  DOC   "Path to nanomsg include header files."
)

find_library(NANOMSG_LIBRARY_SHARED NAMES libnanomsg.dylib libnanomsg.so
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to libnanomsg.dylib libnanomsg.so."
)

find_library(NANOMSG_LIBRARY_STATIC NAMES libnanomsg.a
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to libnanomsg.a."
)

if(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)
  set(NANOMSG_FOUND true)
else(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)
  set(NANOMSG_FOUND false)
endif(NANOMSG_INCLUDE_DIR AND NANOMSG_LIBRARY_SHARED AND NANOMSG_LIBRARY_STATIC)

if(NANOMSG_FOUND)
  set(NANOMSG_LIBRARIES "${NANOMSG_LIBRARY_STATIC};${NANOMSG_LIBRARY_SHARED}")
  if(NOT NANOMSG_FIND_QUIETLY)
    message(STATUS "Looking for nanomsg... - found ${NANOMSG_LIBRARIES}")
  endif(NOT NANOMSG_FIND_QUIETLY)
else(NANOMSG_FOUND)
  if(NOT NANOMSG_FIND_QUIETLY)
    if(NANOMSG_FIND_REQUIRED)
      message(FATAL_ERROR "Looking for nanomsg... - Not found")
    else(NANOMSG_FIND_REQUIRED)
      message(STATUS "Looking for nanomsg... - Not found")
    endif(NANOMSG_FIND_REQUIRED)
  endif(NOT NANOMSG_FIND_QUIETLY)
endif(NANOMSG_FOUND)

mark_as_advanced(NANOMSG_INCLUDE_DIR NANOMSG_LIBRARIES NANOMSG_LIBRARY_SHARED NANOMSG_LIBRARY_STATIC)
