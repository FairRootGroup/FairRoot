################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

MESSAGE(STATUS "Looking for FlatBuffers...")

find_path(FLATBUFFERS_INCLUDE_DIR NAMES flatbuffers/flatbuffers.h PATHS
  ${FLATBUFFERS_PATH}/include
  ${SIMPATH}/include
  NO_DEFAULT_PATH
)

find_path(FLATBUFFERS_LIBRARY_DIR NAMES libflatbuffers.a
  PATHS ${FLATBUFFERS_PATH}/
  ${SIMPATH}/lib
  NO_DEFAULT_PATH
)

find_path(FLATBUFFERS_BINARY_DIR NAMES flatc
  PATHS ${FLATBUFFERS_PATH}/
  ${SIMPATH}/bin
  NO_DEFAULT_PATH
)

if(FLATBUFFERS_INCLUDE_DIR AND FLATBUFFERS_LIBRARY_DIR AND FLATBUFFERS_BINARY_DIR)
  set(FLATBUFFERS_FOUND true)
  message(STATUS "Looking for FlatBuffers ... found at ${FLATBUFFERS_INCLUDE_DIR}")
else(FLATBUFFERS_INCLUDE_DIR AND FLATBUFFERS_LIBRARY_DIR AND FLATBUFFERS_BINARY_DIR)
  set(FLATBUFFERS_FOUND false)
  message(STATUS "Looking for FlatBuffers ... not found.")
endif(FLATBUFFERS_INCLUDE_DIR AND FLATBUFFERS_LIBRARY_DIR AND FLATBUFFERS_BINARY_DIR)

