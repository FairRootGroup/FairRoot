################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# CDash client
include(Dart)

# Check if the user wants to build the project in the source directory
CHECK_OUT_OF_SOURCE_BUILD()
# Check if the install directory is different from the build directory
CHECK_INSTALL_DIRECTORY()

# generate compile_commands.json file (https://clang.llvm.org/docs/JSONCompilationDatabase.html)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")

# Initialize output directories which are used as defaults for the per target output dirs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

if(WITH_DBASE)
  add_definitions(-DWITH_DBASE)
endif()

if(USE_PATH_INFO)
  set(PATH $ENV{PATH})
  if (APPLE)
    set(LD_LIBRARY_PATH $ENV{DYLD_LIBRARY_PATH})
  else (APPLE)
    set(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
  endif (APPLE)
endif(USE_PATH_INFO)
