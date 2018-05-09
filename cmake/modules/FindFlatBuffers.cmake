################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_path(FLATBUFFERS_INCLUDE_DIR 
  NAMES flatbuffers/flatbuffers.h
  
  HINTS
  ${FLATBUFFERS_ROOT}/include
  $ENV{FLATBUFFERS_ROOT}/include
  ${FLATBUFFERS_PATH}/include
  ${SIMPATH}/include
)

find_path(FLATBUFFERS_LIBRARY_DIR
  NAMES libflatbuffers.a

  HINTS
  ${FLATBUFFERS_ROOT}/lib
  $ENV{FLATBUFFERS_ROOT}/lib
  ${FLATBUFFERS_PATH}/lib
  ${SIMPATH}/lib
)

find_library(FLATBUFFERS_STATIC_LIBRARY
  NAMES libflatbuffers.a

  HINTS
  ${FLATBUFFERS_ROOT}/lib
  $ENV{FLATBUFFERS_ROOT}/lib
  ${FLATBUFFERS_PATH}/lib
  ${SIMPATH}/lib
)

find_path(FLATBUFFERS_BINARY_DIR
  NAMES flatc

  HINTS
  ${FLATBUFFERS_ROOT}/bin
  $ENV{FLATBUFFERS_ROOT}/bin
  ${FLATBUFFERS_PATH}/bin
  ${SIMPATH}/bin
)

find_program(FLATBUFFERS_BINARY_FLATC
  NAMES flatc

  HINTS
  ${FLATBUFFERS_ROOT}/bin
  $ENV{FLATBUFFERS_ROOT}/bin
  ${FLATBUFFERS_PATH}/bin
  ${SIMPATH}/bin
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FlatBuffers
  REQUIRED_VARS
  FLATBUFFERS_INCLUDE_DIR
  FLATBUFFERS_LIBRARY_DIR
  FLATBUFFERS_BINARY_DIR
)

# idempotently import targets
if(NOT TARGET FlatBuffers)
  if(FLATBUFFERS_FOUND)
    # import target
    add_library(FlatBuffers STATIC IMPORTED)
    set_target_properties(FlatBuffers PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES ${FLATBUFFERS_INCLUDE_DIR}
      IMPORTED_LOCATION ${FLATBUFFERS_STATIC_LIBRARY}
    )
  endif()
endif()

if(NOT TARGET FlatBuffers::flatc)
  if(FLATBUFFERS_FOUND)
  # import target
  add_executable(FlatBuffers::flatc IMPORTED)
  set_target_properties(FlatBuffers::flatc PROPERTIES
    IMPORTED_LOCATION ${FLATBUFFERS_BINARY_FLATC}
  )
  endif()
endif()

if(FLATBUFFERS_FOUND)
  list(APPEND LD_LIBRARY_PATH ${FLATBUFFERS_LIBRARY_DIR})
endif()
