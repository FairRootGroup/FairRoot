################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# COmpile TIme REducer helper
include(cotire)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
  # Define Linux build profiles
  set(FAIRROOT_SYSTEM Linux)
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(FAIRROOT_COMPILER "GCC")

    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -Wshadow")
    set(CMAKE_CXX_FLAGS_NIGHTLY        "-O0 -g -Wshadow")
    set(CMAKE_CXX_FLAGS_TEST           "-O2 -g -Wshadow")
    set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -Wshadow ")
    set(CMAKE_CXX_FLAGS_DEBUG          "-g -Wshadow ")
    set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline  -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-exceptions -fno-check-new -fno-common -fexceptions")
    set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs -Wshadow -Wall -Wextra -Wunused-variable")
    set(CMAKE_CXX_FLAGS_ARRAY_CHECK    "-g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
    set(CMAKE_C_FLAGS_RELEASE          "-O2")
    set(CMAKE_C_FLAGS_DEBUG            "-g")
    set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common -fexceptions")
    set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")
    set(CMAKE_C_FLAGS_ARRAY_CHECK      "-g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")

  elseif(CMAKE_C_COMPILER MATCHES icc)
    set(FAIRROOT_COMPILER "ICC")

    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g ")
    set(CMAKE_CXX_FLAGS_RELEASE        "-O2")
    set(CMAKE_CXX_FLAGS_DEBUG          "-O2 -g -0b0 -noalign")
    set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g -Ob0 -noalign -W")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
    set(CMAKE_C_FLAGS_RELEASE          "-O2")
    set(CMAKE_C_FLAGS_DEBUG            "-O2 -g -Ob0 -noalign")
    set(CMAKE_C_FLAGS_DEBUGFULL        "-g -Ob0 -noalign -W")

    # Get the directory where to find libimf. The only way I found is to get the install dir from icpc and
    # from there one knows where the the libraries are installed
    execute_process(COMMAND which icpc OUTPUT_VARIABLE _bla)
    string(REPLACE "bin" "compiler/lib" _intel_lib_dirs ${_bla})
    string(REPLACE "/icpc" "" _intel_lib_dirs ${_intel_lib_dirs})
    string(STRIP ${_intel_lib_dirs} _intel_lib_dirs)

  elseif(CMAKE_C_COMPILER MATCHES clang)
    set(FAIRROOT_COMPILER "Clang")

    set(CMAKE_C_FLAGS_PROFILE          "--coverage -g3")
    set(CMAKE_CXX_FLAGS_PROFILE        "--coverage -g3")
  else()
    message("CXX Compiler: ${CMAKE_CXX_COMPILER}")
    message("CXX Compiler ABI: ${CMAKE_CXX_COMPILER_ABI}")
    message("CXX Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    message(FATAL_ERROR "This compiler is not supported.")   
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
  # Define MacOS build profiles
  execute_process(COMMAND "sw_vers -productVersion | cut -d . -f 1-2" OUTPUT_VARIABLE MAC_OS_VERSION)
  set(FAIRROOT_SYSTEM "MacOS ${MAC_OS_VERSION}")
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(FAIRROOT_COMPILER "Apple Clang, GFortran")

    STRING(COMPARE EQUAL "10.5" "${MAC_OS_VERSION}" MAC_OS_10_5)
    STRING(COMPARE EQUAL "10.6" "${MAC_OS_VERSION}" MAC_OS_10_6)
    STRING(COMPARE EQUAL "10.7" "${MAC_OS_VERSION}" MAC_OS_10_7)
    IF(MAC_OS_10_5 OR MAC_OS_10_6 OR MAC_OS_10_7)
      SET(CMAKE_CXX_FLAGS "-m64")
      SET(CMAKE_C_FLAGS "-m64")
      SET(CMAKE_Fortran_FLAGS "-m64")
    ENDIF(MAC_OS_10_5 OR MAC_OS_10_6 OR MAC_OS_10_7)

    # Check for Xcode version 7.3.0
    SET(CLANG_730 -1)
    IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      EXEC_PROGRAM("clang --version | grep \"version 7.3.0\"" OUTPUT_VARIABLE CLANG_VERSION)
      IF(CLANG_VERSION)
        STRING(FIND ${CLANG_VERSION} "version 7.3.0" CLANG_730)
      ENDIF(CLANG_VERSION)
    ENDIF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    SET(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -single_module -undefined dynamic_lookup")
    SET(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -single_module -undefined dynamic_lookup")

    # Do not use -flat_namespace flag for Xcode 7.3.0
    IF(CLANG_730 LESS 0)
      SET(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -flat_namespace")
      SET(CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS} -flat_namespace")
    ENDIF(CLANG_730 LESS 0)

    Execute_Process(COMMAND gfortran -print-file-name=libgfortran.dylib
      OUTPUT_VARIABLE FORTRAN_LIBDIR
    )
    Get_Filename_Component(FORTRAN_LIBDIR ${FORTRAN_LIBDIR} PATH)
    Message("-- Fortran libraries found in ${FORTRAN_LIBDIR}")
    SET(CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -flat_namespace -single_module -undefined dynamic_lookup")

    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -Wshadow ")
    set(CMAKE_CXX_FLAGS_NIGHTLY        "-O2 -g -Wshadow -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -Wshadow ")
    set(CMAKE_CXX_FLAGS_DEBUG          "-g -Wshadow  -fno-inline")
    set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-exceptions -fno-check-new -fno-common")
    set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs -Wall -Wextra")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
    set(CMAKE_C_FLAGS_RELEASE          "-O2")
    set(CMAKE_C_FLAGS_DEBUG            "-g -fno-inline")
    set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common")
    set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")

  else()
    message("CXX Compiler: ${CMAKE_CXX_COMPILER}")
    message("CXX Compiler ABI: ${CMAKE_CXX_COMPILER_ABI}")
    message("CXX Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
    message(FATAL_ERROR "This compiler is not supported.")   
  endif()
else()
  message("")
endif()

# Set default build profile
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

# Disable compiler specific extensions (e.g. will cause --std=c++11 instead of --std=gnu++11 for gcc)
set(CMAKE_CXX_EXTENSIONS OFF)

# Check if the compiler supports specific C++11 features
set(CheckSrcDir "${CMAKE_SOURCE_DIR}/cmake/checks")
include(CheckCXX11Features)

# These target properties should be added to all library and executable targets in this project
set(FAIRROOT_LIBRARY_PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION}"
  CXX_STANDARD 11
)
set(FAIRROOT_EXECUTABLE_PROPERTIES
  CXX_STANDARD 11
)

# Configure RPATH entries on macOS
# https://cmake.org/Wiki/CMake_RPATH_handling#Always_full_RPATH
if(APPLE)
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  endif()
endif()

# Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
# Rationale in https://github.com/ninja-build/ninja/issues/814
if(CMAKE_GENERATOR STREQUAL "Ninja" AND
  ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

