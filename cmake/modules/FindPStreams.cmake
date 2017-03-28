################################################################################
#    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
#
# Authors:
#
#   Dennis Klein
#
#
# ###############################
# # Locate the PStreams library #
# ###############################
#
#
# Usage:
#
#   find_package(PStreams [<version> [EXACT]] [QUIET] [REQUIRED])
#
#
# Defines the following variables:
#
#   PStreams_FOUND - Found the ZeroMQ library
#   PStreams_INCLUDE_DIRS - Include directories
#   PStreams_VERSION - Full version
#   PStreams_VERSION_MAJOR
#   PStreams_VERSION_MINOR
#   PStreams_VERSION_PATCH
#
#
# Defines the following imported targets:
#
#   PStreams
#
#
# Accepts the following variables as hints for installation(-> ROOT) and
# source(-> SOURCE_DIR) directories:
#
#   PSTREAMS_SOURCE_DIR (CMake var, ENV var)
#   PSTREAMS_ROOT (CMake var, ENV var)
#
#

# find include dir
if(DEFINED ENV{PSTREAMS_ROOT})
    set(PSTREAMS_ROOT $ENV{PSTREAMS_ROOT})
endif()
if(DEFINED ENV{PSTREAMS_SOURCE_DIR})
    set(PSTREAMS_SOURCE_DIR $ENV{PSTREAMS_SOURCE_DIR})
endif()
find_path(PStreams_INCLUDE_DIR NAMES pstream.h
    PATHS ${PSTREAMS_SOURCE_DIR}
          ${PSTREAMS_ROOT_INCLUDE}
    PATH_SUFFIXES include
    DOC "PStreams include directory"
)

# detect version
find_file(PStreams_HEADER_FILE pstream.h
    ${PStreams_INCLUDE_DIR}
    NO_DEFAULT_PATH
)
if(PStreams_HEADER_FILE)
    file(READ "${PStreams_HEADER_FILE}" _PStreams_HEADER_FILE_CONTENT)
    string(REGEX MATCH "#define PSTREAMS_VERSION 0x0([0-9])([0-9])([0-9])" _MATCH "${_PStreams_HEADER_FILE_CONTENT}")
    set(PStreams_VERSION_MAJOR ${CMAKE_MATCH_1})
    set(PStreams_VERSION_MINOR ${CMAKE_MATCH_2})
    set(PStreams_VERSION_PATCH ${CMAKE_MATCH_3})
    set(PStreams_VERSION "${PStreams_VERSION_MAJOR}.${PStreams_VERSION_MINOR}.${PStreams_VERSION_PATCH}")
endif()

# process results
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PStreams
    FOUND_VAR PStreams_FOUND
    REQUIRED_VARS PStreams_INCLUDE_DIR
    VERSION_VAR PStreams_VERSION
)

# define output variables
set(PStreams_INCLUDE_DIRS ${PStream_INCLUDE_DIR})
mark_as_advanced(PStreams_HEADER_FILE)

# idempotently import target
if(TARGET PStreams)
    # nothing to do
else()
    if(DEFINED PStreams_INCLUDE_DIR)
        # import target
        add_library(PStreams INTERFACE IMPORTED)
        set_target_properties(PStreams PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${PStreams_INCLUDE_DIR}
        )
    endif()
endif()
