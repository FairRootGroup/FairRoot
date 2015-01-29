 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
message(STATUS "Looking for ZeroMQ...")

set(ZMQ_H zmq.hpp)
set(ZMQ_UTILS_H zmq_utils.h)
set(LIBZMQ_SHARED libzmq.so)
set(LIBZMQ_STATIC libzmq.a)

find_path(ZMQ_INCLUDE_DIR NAMES ${ZMQ_H} ${ZMQ_UTILS_H}
  PATHS ${ZMQ_DIR}/include
  PATHS ${AlFa_DIR}/include
  PATHS ${SIMPATH}/include
  NO_DEFAULT_PATH
  DOC   "Path to ZeroMQ include header files."
)

find_library(ZMQ_LIBRARY_SHARED NAMES ${LIBZMQ_SHARED}
  PATHS ${ZMQ_DIR}/lib
  PATHS ${AlFa_DIR}/lib
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to ${LIBZMQ_SHARED}."
)

find_library(ZMQ_LIBRARY_STATIC NAMES ${LIBZMQ_STATIC}
  PATHS ${ZMQ_DIR}/lib
  PATHS ${AlFa_DIR}/lib
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to ${LIBZMQ_STATIC}."
)

IF(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)
  SET(ZMQ_FOUND TRUE)
ELSE(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)
  SET(ZMQ_FOUND FALSE)
ENDIF(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)

if(ZMQ_FOUND)
  set(ZMQ_LIBRARIES "${ZMQ_LIBRARY_STATIC};${ZMQ_LIBRARY_SHARED}")
  if(NOT ZMQ_FIND_QUIETLY)
    message(STATUS "Looking for ZeroMQ... - found ${ZMQ_LIBRARIES}")
  endif(NOT ZMQ_FIND_QUIETLY)
else(ZMQ_FOUND)
  if(NOT ZMQ_FIND_QUIETLY)
    if(ZMQ_FIND_REQUIRED)
      message(FATAL_ERROR "Looking for ZeroMQ... - Not found")
    else(ZMQ_FIND_REQUIRED)
      message(STATUS "Looking for ZeroMQ... - Not found")
    endif(ZMQ_FIND_REQUIRED)
  endif(NOT ZMQ_FIND_QUIETLY)
endif(ZMQ_FOUND)

mark_as_advanced(ZMQ_INCLUDE_DIR ZMQ_LIBRARIES ZMQ_LIBRARY_SHARED ZMQ_LIBRARY_STATIC)
