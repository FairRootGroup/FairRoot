 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

if(NOT ZeroMQ_FIND_QUIETLY)
  message(STATUS "Looking for ZeroMQ...")
endif(NOT ZeroMQ_FIND_QUIETLY)

find_path(ZMQ_INCLUDE_DIR NAMES zmq.hpp zmq_utils.h
  PATHS ${ZMQ_DIR}/include
  PATHS ${AlFa_DIR}/include
  PATHS ${SIMPATH}/include
  NO_DEFAULT_PATH
  DOC   "Path to ZeroMQ include header files."
)

find_path(ZMQ_INCLUDE_DIR NAMES zmq.hpp zmq_utils.h
  DOC   "Path to ZeroMQ include header files."
)

find_library(ZMQ_LIBRARY_SHARED NAMES libzmq.dylib libzmq.so
  PATHS ${ZMQ_DIR}/lib
  PATHS ${AlFa_DIR}/lib
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to libzmq.dylib libzmq.so."
)

find_library(ZMQ_LIBRARY_SHARED NAMES libzmq.dylib libzmq.so
  DOC   "Path to libzmq.dylib libzmq.so."
)

find_library(ZMQ_LIBRARY_STATIC NAMES libzmq.a
  PATHS ${ZMQ_DIR}/lib
  PATHS ${AlFa_DIR}/lib
  PATHS ${SIMPATH}/lib
  NO_DEFAULT_PATH
  DOC   "Path to libzmq.a."
)

find_library(ZMQ_LIBRARY_STATIC NAMES libzmq.a
  DOC   "Path to libzmq.a."
)


IF(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)
  SET(ZMQ_FOUND TRUE)
ELSE(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)
  SET(ZMQ_FOUND FALSE)
ENDIF(ZMQ_INCLUDE_DIR AND ZMQ_LIBRARY_SHARED AND ZMQ_LIBRARY_STATIC)

set(ERROR_STRING "Looking for ZeroMQ... - Not found")

if(ZMQ_FOUND)
  FIND_FILE(ZMQ_HEADER_FILE zmq.h
    ${ZMQ_INCLUDE_DIR}
    NO_DEFAULT_PATH
    )
  IF (DEFINED ZMQ_HEADER_FILE)
    FILE(READ "${ZMQ_HEADER_FILE}" _ZMQ_HEADER_FILE_CONTENT)
    STRING(REGEX MATCH "#define ZMQ_VERSION_MAJOR ([0-9])" _MATCH "${_ZMQ_HEADER_FILE_CONTENT}")
    SET(ZMQ_VERSION_MAJOR ${CMAKE_MATCH_1})
    STRING(REGEX MATCH "#define ZMQ_VERSION_MINOR ([0-9])" _MATCH "${_ZMQ_HEADER_FILE_CONTENT}")
    SET(ZMQ_VERSION_MINOR ${CMAKE_MATCH_1})
    STRING(REGEX MATCH "#define ZMQ_VERSION_PATCH ([0-9])" _MATCH "${_ZMQ_HEADER_FILE_CONTENT}")
    SET(ZMQ_VERSION_PATCH ${CMAKE_MATCH_1})
    set (ZMQ_VERSION "${ZMQ_VERSION_MAJOR}.${ZMQ_VERSION_MINOR}.${ZMQ_VERSION_PATCH}")
    IF (DEFINED ZeroMQ_FIND_VERSION AND ZMQ_VERSION VERSION_LESS ZeroMQ_FIND_VERSION)
      SET(ZMQ_FOUND FALSE)
      SET(ERROR_STRING "Installed version ${ZMQ_VERSION} of ZeroMQ does not meet the minimum required version ${ZeroMQ_FIND_VERSION}")
    endif ()
  endif ()
endif()

if(ZMQ_FOUND)
  set(ZMQ_LIBRARIES "${ZMQ_LIBRARY_STATIC};${ZMQ_LIBRARY_SHARED}")
  if(NOT ZeroMQ_FIND_QUIETLY)
    message(STATUS "Looking for ZeroMQ... - found ${ZMQ_LIBRARIES} ${ZMQ_VERSION}")
  endif(NOT ZeroMQ_FIND_QUIETLY)
else(ZMQ_FOUND)
  unset(ZMQ_INCLUDE_DIR)
  unset(ZMQ_LIBRARY_SHARED)
  unset(ZMQ_LIBRARY_STATIC)
  if(ZeroMQ_FIND_REQUIRED)
    message(FATAL_ERROR "${ERROR_STRING}")
  else(ZeroMQ_FIND_REQUIRED)
    if(NOT ZeroMQ_FIND_QUIETLY)
      message(STATUS "${ERROR_STRING}")
    endif(NOT ZeroMQ_FIND_QUIETLY)
  endif(ZeroMQ_FIND_REQUIRED)
endif(ZMQ_FOUND)

mark_as_advanced(ZMQ_INCLUDE_DIR ZMQ_LIBRARIES ZMQ_LIBRARY_SHARED ZMQ_LIBRARY_STATIC)
