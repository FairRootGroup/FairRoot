################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

MESSAGE(STATUS "Looking for MessagePack...")

find_path(MSGPACK_INCLUDE_DIR msgpack.hpp PATHS
  ${SIMPATH}/include
  ${MSGPACK_ROOT}/include
  NO_DEFAULT_PATH
)

find_path(MSGPACK_LIBRARY_DIR NAMES libmsgpackc.dylib libmsgpackc.so PATHS
  ${SIMPATH}/lib
  ${MSGPACK_ROOT}/lib
  NO_DEFAULT_PATH
)

find_library(MSGPACK_LIBRARY_SHARED NAMES libmsgpackc.dylib libmsgpackc.so
  PATHS ${SIMPATH}/lib
  ${MSGPACK_ROOT}/lib
  NO_DEFAULT_PATH
)

if(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
  set(MSGPACK_FOUND true)
  add_library(Msgpack SHARED IMPORTED)
  set_target_properties(Msgpack PROPERTIES
    IMPORTED_LOCATION ${MSGPACK_LIBRARY_SHARED}
    INTERFACE_INCLUDE_DIRECTORIES ${MSGPACK_INCLUDE_DIR}
  )
  message(STATUS "Looking for MessagePack ... found at ${MSGPACK_LIBRARY_DIR}")
else(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
  set(MSGPACK_FOUND false)
  message(STATUS "Looking for MessagePack ... not found.")
endif(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
