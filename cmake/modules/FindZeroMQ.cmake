################################################################################
# Copyright (C) 2012-2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################
#
# Authors:
#
#   Mohammad Al-Turany
#   Dario Berzano
#   Dennis Klein
#   Matthias Richter
#   Alexey Rybalchenko
#   Florian Uhlig
#
#
# #############################
# # Locate the ZeroMQ library #
# #############################
#
#
# Usage:
#
#   find_package(ZeroMQ [version] [QUIET] [REQUIRED])
#
#
# Defines the following variables:
#
#   ZeroMQ_FOUND - Found the ZeroMQ library
#   ZeroMQ_INCLUDE_DIR (CMake cache) - Include directory
#   ZeroMQ_LIBRARY_SHARED (CMake cache) - Path to shared libzmq
#   ZeroMQ_LIBRARY_STATIC (CMake cache) - Path to static libzmq
#   ZeroMQ_VERSION - full version string
#   ZeroMQ_VERSION_MAJOR - major version component
#   ZeroMQ_VERSION_MINOR - minor version component
#   ZeroMQ_VERSION_PATCH - patch version component
#
#
# Accepts the following variables as hints for installation directories:
#
#   ZMQ_DIR (CMake var)
#   AlFa_DIR (CMake var)
#   SIMPATH (CMake var)
#   ZEROMQ_ROOT (CMake var, ENV var)
#
#
# If the above variables are not defined, or if ZeroMQ could not be found there,
# it will look for it in the system directories. Custom ZeroMQ installations
# will always have priority over system ones.
#

if(NOT ZeroMQ_FIND_QUIETLY)
    message(STATUS "Looking for ZeroMQ")
endif()

if(DEFINED ENV{ZEROMQ_ROOT})
    set(ZEROMQ_ROOT $ENV{ZEROMQ_ROOT})
endif()

find_path(ZeroMQ_INCLUDE_DIR NAMES "zmq.h" "zmq_utils.h"
    HINTS "${ZMQ_DIR}/include"
          "${AlFa_DIR}/include"
          "${SIMPATH}/include"
          "${ZEROMQ_ROOT}/include"
    DOC "ZeroMQ include directories"
)
set(ZMQ_INCLUDE_DIR ${ZeroMQ_INCLUDE_DIR}
    CACHE PATH "ZeroMQ include directories (DEPRECATED)")

find_library(ZeroMQ_LIBRARY_SHARED NAMES "libzmq.dylib" "libzmq.so"
    HINTS "${ZMQ_DIR}/lib"
          "${AlFa_DIR}/lib"
          "${SIMPATH}/lib"
          "${ZEROMQ_ROOT}/lib"
    DOC "Path to libzmq.dylib or libzmq.so"
)
set(ZMQ_LIBRARY_SHARED ${ZeroMQ_LIBRARY_SHARED}
    CACHE FILEPATH "Path to libzmq.dylib or libzmq.so (DEPRECATED)")

find_library(ZeroMQ_LIBRARY_STATIC NAMES "libzmq.a"
    HINTS "${ZMQ_DIR}/lib"
          "${AlFa_DIR}/lib"
          "${SIMPATH}/lib"
          "${ZEROMQ_ROOT}/lib"
    DOC "Path to libzmq.a"
)
set(ZMQ_LIBRARY_STATIC ${ZeroMQ_LIBRARY_STATIC}
    CACHE FILEPATH "Path to libzmq.a (DEPRECATED)")

if(ZeroMQ_INCLUDE_DIR AND ZeroMQ_LIBRARY_SHARED AND ZeroMQ_LIBRARY_STATIC)
    set(ZeroMQ_FOUND TRUE)
    set(ZMQ_FOUND TRUE) # DEPRECATED
else()
    set(ZeroMQ_FOUND FALSE)
    set(ZMQ_FOUND FALSE) # DEPRECATED
endif()

set(ERROR_STRING "Looking for ZeroMQ - NOT FOUND")

if(ZeroMQ_FOUND)
    find_file(ZeroMQ_HEADER_FILE "zmq.h"
        ${ZeroMQ_INCLUDE_DIR}
        NO_DEFAULT_PATH
    )
    if (DEFINED ZeroMQ_HEADER_FILE)
        file(READ "${ZeroMQ_HEADER_FILE}" _ZeroMQ_HEADER_FILE_CONTENT)
        string(REGEX MATCH "#define ZMQ_VERSION_MAJOR ([0-9])" _MATCH "${_ZeroMQ_HEADER_FILE_CONTENT}")
        set(ZeroMQ_VERSION_MAJOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define ZMQ_VERSION_MINOR ([0-9])" _MATCH "${_ZeroMQ_HEADER_FILE_CONTENT}")
        set(ZeroMQ_VERSION_MINOR ${CMAKE_MATCH_1})
        string(REGEX MATCH "#define ZMQ_VERSION_PATCH ([0-9])" _MATCH "${_ZeroMQ_HEADER_FILE_CONTENT}")
        set(ZeroMQ_VERSION_PATCH ${CMAKE_MATCH_1})
        set(ZeroMQ_VERSION "${ZeroMQ_VERSION_MAJOR}.${ZeroMQ_VERSION_MINOR}.${ZeroMQ_VERSION_PATCH}")
        if(DEFINED ZeroMQ_FIND_VERSION AND ZeroMQ_VERSION VERSION_LESS ZeroMQ_FIND_VERSION)
            set(ZeroMQ_FOUND FALSE)
            set(ERROR_STRING "Looking for ZeroMQ - Installed version ${ZeroMQ_VERSION} does not meet the minimum required version ${ZeroMQ_FIND_VERSION}")
        endif ()
        unset(ZeroMQ_HEADER_FILE CACHE)
    endif ()

    add_library(ZeroMQ SHARED IMPORTED)
    set_target_properties(ZeroMQ PROPERTIES
        # TODO switch to ZeroMQ_ vars here once deprecated vars are removed
        IMPORTED_LOCATION ${ZMQ_LIBRARY_SHARED}
        INTERFACE_INCLUDE_DIRECTORIES ${ZMQ_INCLUDE_DIR}
    )
endif()

if(ZeroMQ_FOUND)
    set(ZeroMQ_LIBRARIES "${ZeroMQ_LIBRARY_STATIC};${ZeroMQ_LIBRARY_SHARED}")
    if(NOT ZeroMQ_FIND_QUIETLY)
        message(STATUS "Looking for ZeroMQ - Found ${ZeroMQ_INCLUDE_DIR}")
        message(STATUS "Looking for ZeroMQ - Found version ${ZeroMQ_VERSION}")
    endif(NOT ZeroMQ_FIND_QUIETLY)
else()
    if(ZeroMQ_FIND_REQUIRED)
        message(FATAL_ERROR "${ERROR_STRING}")
    else()
        if(NOT ZeroMQ_FIND_QUIETLY)
            message(STATUS "${ERROR_STRING}")
        endif(NOT ZeroMQ_FIND_QUIETLY)
    endif()
endif()

if(NOT ZeroMQ_NO_DEPRECATED)
    message(DEPRECATION
"ZMQ_FOUND, ZMQ_INCLUDE_DIR, ZMQ_LIBRARY_STATIC|SHARED, ZMQ_* variables are DEPRECATED.
Use ZeroMQ_FOUND, ZeroMQ_INCLUDE_DIR, ZeroMQ_LIBRARY_STATIC|SHARED, ZeroMQ_* instead.
Use '-Wno-deprecated' or '-DZeroMQ_NO_DEPRECATED=ON' to suppress this message.")
endif()

unset(ERROR_STRING)
unset(ZEROMQ_ROOT)

mark_as_advanced(
    ZeroMQ_LIBRARIES
    ZeroMQ_LIBRARY_SHARED
    ZMQ_LIBRARY_SHARED
    ZeroMQ_LIBRARY_STATIC
    ZMQ_LIBRARY_STATIC
    ZeroMQ_VERSION_MAJOR
    ZeroMQ_VERSION_MINOR
    ZeroMQ_VERSION_PATCH
)
