################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

MESSAGE(STATUS "Looking for MessagePack...")

find_path(MSGPACK_INCLUDE_DIR msgpack.hpp PATHS
  /usr/include
  /usr/include/msgpack
  /usr/local/include
  /usr/local/include/msgpack
)

find_path(MSGPACK_LIBRARY_DIR NAMES libmsgpackc.dylib libmsgpackc.so PATHS
  /usr/lib
  /usr/local/lib
  /usr/local/lib/msgpack
)

if(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
  set(MSGPACK_FOUND true)
  message(STATUS "Looking for MessagePack ... found at ${MSGPACK_LIBRARY_DIR}")
else(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
  set(MSGPACK_FOUND false)
  message(STATUS "Looking for MessagePack ... not found.")
endif(MSGPACK_INCLUDE_DIR AND MSGPACK_LIBRARY_DIR)
