 ################################################################################
 # Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
cmake_policy(VERSION 3.15...3.23)

set(PROJECT_MIN_CXX_STANDARD 17)

project(FairRoot VERSION 19.0.0)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/private")

# Generate compile_commands.json file (https://clang.llvm.org/docs/JSONCompilationDatabase.html)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define CMAKE_INSTALL_*DIR family of variables
include(GNUInstallDirs)
include(CTest)
include(FairRootTargetRootDictionary)

# Define install dirs
set(PROJECT_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(PROJECT_INSTALL_DATADIR ${CMAKE_INSTALL_DATADIR}/fairbase) # TODO: change 'fairbase' to ${PROJECT_NAME_LOWER}

# https://cmake.org/Wiki/CMake_RPATH_handling
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
  if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../${PROJECT_INSTALL_LIBDIR}")
  elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_INSTALL_RPATH "@loader_path/../${PROJECT_INSTALL_LIBDIR}")
  else()
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}")
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,--enable-new-dtags")
  set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--enable-new-dtags")
  set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -z defs")
  set(CMAKE_MODULE_LINKER_FLAGS  "${CMAKE_MODULE_LINKER_FLAGS} -z defs")
  set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -z defs")
endif()

if(CMAKE_GENERATOR STREQUAL "Ninja" AND
  ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
  # Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
  # Rationale in https://github.com/ninja-build/ninja/issues/814
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif()

# Set a default if not specified by the user
if(NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()
if(NOT DEFINED CMAKE_INSTALL_MESSAGE)
  set(CMAKE_INSTALL_MESSAGE LAZY)
endif()

SET(VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

include(CheckSymbolExists)


if(DEFINED ENV{SIMPATH})
  set(SIMPATH $ENV{SIMPATH})
  list(PREPEND CMAKE_PREFIX_PATH ${SIMPATH})
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${SIMPATH}/lib)
endif()

# Load some basic macros which are needed later on
find_package(FairCMakeModules 0.2 QUIET REQUIRED)
include(FairFindPackage2)
include(FairFormattedOutput)
include(FairSummary)
if(FairCMakeModules_VERSION VERSION_GREATER_EQUAL 1.0.0)
  include(FairProjectConfig)
endif()

include(FairRootTargets)
include(FairRootPackage)
include(FairRootSummary)
include(FairMacros)
include(WriteConfigFile)
include(CheckCompiler)

if(FairCMakeModules_VERSION VERSION_GREATER_EQUAL 1.0.0)
  fair_get_git_version()
endif()

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")


# Check if the user wants to build the project in the source
# directory and if the install directory is different from the build
# directory
CHECK_OUT_OF_SOURCE_BUILD()
CHECK_INSTALL_DIRECTORY()

# Check if we are on an UNIX system. If not stop with an error
# message
IF(NOT UNIX)
  MESSAGE(FATAL_ERROR "You're not on an UNIX system. The project was up to now only tested on UNIX systems, so we break here. If you want to go on please edit the CMakeLists.txt in the source directory.")
ENDIF(NOT UNIX)


# Set option(s)
option(ENABLE_GEANT3_TESTING "Enable tests utilizing Geant3" OFF)
option(BUILD_PROOF_SUPPORT "Support ROOT::Proof (deprecated)" OFF)
option(BUILD_EVENT_BUILDER "Build FairEventBuild" OFF)

option(BUILD_ONLINE "Build the online library" ON)
option(BUILD_MBS "Build MBS" OFF)
if (BUILD_MBS)
  set(BUILD_ONLINE ON)
endif()
option(BUILD_BASEMQ "Build the 'FairRoot::BaseMQ' library" ON)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

# FairRoot only supports ROOT6, so check which version is available
list(APPEND required_root_components RIO)
if(BUILD_SIM)
  list(APPEND required_root_components pythia6 pythia8)
endif()
list(APPEND optional_root_components opengl)
list(APPEND optional_root_components gdml vmc)
find_package2(PUBLIC ROOT REQUIRED
  VERSION 6.18.00
  COMPONENTS ${required_root_components}
  OPTIONAL_COMPONENTS ${optional_root_components})
include(ROOTMacros)

#Check the compiler and set the compile and link flags
Check_Compiler()

if(CMAKE_CXX_CLANG_TIDY)
  # Force clang-tidy to the same C++ Standard
  list(APPEND CMAKE_CXX_CLANG_TIDY
       "--extra-arg=-std=c++${CMAKE_CXX_STANDARD}")
endif()

fairroot_check_root_cxxstd_compatibility()

if(ROOT_vmc_FOUND)
  set(VMCLIB ROOT::VMC)
else()
  find_package2(PUBLIC VMC REQUIRED)
  set(VMCLIB VMCLibrary)
endif()
find_package2(PUBLIC Pythia6)
find_package2(PUBLIC Pythia8)
# Protobuf https://github.com/protocolbuffers/protobuf/releases/tag/v22.0
# added a new dependency to abseil which is not handled yet by CMake's
# FindProtobuf.cmake.
# https://github.com/protocolbuffers/protobuf/issues/12292 - Let's try to
# find a Protobuf CMake pkg first and fall back to find module if not found.
find_package2(PUBLIC Protobuf CONFIG)
if(NOT Protobuf_FOUND)
  unset(Protobuf_FOUND CACHE)
  find_package2(PUBLIC Protobuf)
  if(    Protobuf_FOUND
     AND Protobuf_VERSION VERSION_GREATER_EQUAL 4.22
     AND NOT TARGET absl::raw_logging_internal)
    set(Protobuf_FOUND NOTFOUND CACHE FORCE)
  endif()
endif()
find_package2(PUBLIC Flatbuffers)

find_package2(PUBLIC Geant3)
find_package2(PUBLIC Geant4)

Find_Package2(PUBLIC VGM)

find_package2(PUBLIC Geant4VMC)

find_package2(PUBLIC IWYU)

find_package2(PUBLIC GSL)

if(BUILD_BASEMQ)
  find_package2(PUBLIC FairMQ VERSION 1.4.0 REQUIRED)
endif()

find_package2(PUBLIC DDS)
find_package2(PUBLIC FairLogger VERSION 1.2.0 REQUIRED)

if(BUILD_BASEMQ OR BUILD_EXAMPLES)
  if(NOT DEFINED Boost_NO_SYSTEM_PATHS)
    Set(Boost_NO_SYSTEM_PATHS TRUE)
  endif()
  if(Boost_NO_BOOST_CMAKE)
    # If an older version of boost is found both of the variables below are
    # cached and in a second cmake run, a good boost version is found even
    # if the version is to old.
    # To overcome this problem both variables are cleared before checking
    # for boost.
    Unset(Boost_INCLUDE_DIR CACHE)
    Unset(Boost_LIBRARY_DIRS CACHE)
  endif()

  set(boost_dependencies)
  if(BUILD_BASEMQ)
    list(APPEND boost_dependencies filesystem serialization program_options)
  endif()
  if(BUILD_EXAMPLES)
    list(APPEND boost_dependencies program_options)
  endif()

  find_package2(PUBLIC Boost
    VERSION 1.67
    COMPONENTS ${boost_dependencies}
    REQUIRED
  )
endif()

If (Boost_FOUND)
  Set(Boost_Avail 1)
Else (Boost_FOUND)
  Set(Boost_Avail 0)
EndIf (Boost_FOUND)

set(PROJECT_LIBRARY_PROPERTIES ${PROJECT_LIBRARY_PROPERTIES}
  VERSION "${PROJECT_VERSION}"
)

find_package2(PUBLIC yaml-cpp)
# Workaround missing exported include directories
# Upstream has fixed this in https://github.com/jbeder/yaml-cpp/commit/ab5f9259a4e67d3fe0e4832bd407a9e596e2d884 (since 0.6.3)
if(yaml-cpp_FOUND)
  get_filename_component(YAML_CPP_INCLUDE_DIR "${YAML_CPP_INCLUDE_DIR}" REALPATH BASE_DIR "/")
endif()
if(    yaml-cpp_FOUND
   AND TARGET yaml-cpp
   AND EXISTS YAML_CPP_INCLUDE_DIR
   AND yaml-cpp_VERSION VERSION_LESS 0.6.3
)
  set_target_properties(yaml-cpp PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${YAML_CPP_INCLUDE_DIR}"
  )
endif()

if(BUILD_TESTING)
  Include(FetchContent)

  FetchContent_Declare(
    Catch2
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/Catch2_v3.4.0
    # GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    # GIT_TAG        v3.4.0
  )

  FetchContent_MakeAvailable(Catch2)
endif()

# Set some useful variables
SetBasicVariables()

# All the main / public components
add_subdirectory(fairroot)

add_subdirectory(templates)

Option(BUILD_DOXYGEN "Build Doxygen" OFF)
if(BUILD_DOXYGEN)
  find_package2(PRIVATE Doxygen COMPONENTS dot)
  if (Doxygen_FOUND)
    if (NOT Doxygen_VERSION AND DOXYGEN_VERSION)
      set(Doxygen_VERSION "${DOXYGEN_VERSION}")
    endif()
    add_subdirectory(doxygen)
  else()
    message(WARNING "BUILD_DOXYGEN requested, but Doxygen not found")
  endif()
endif(BUILD_DOXYGEN)

Option(BUILD_EXAMPLES "Build Examples" ON)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(IWYU_FOUND)
  add_custom_target(checkHEADERS DEPENDS $ENV{ALL_HEADER_RULES})
endif(IWYU_FOUND)

find_package2(PRIVATE ClangFormat)
if(ClangFormat_FOUND)
  add_custom_target(FormatCheck
    ${CMAKE_COMMAND} -E env
      FAIRROOT_GIT_CLANG_FORMAT_BIN=${GIT_CLANG_FORMAT_BIN}
      FAIRROOT_CLANG_FORMAT_BIN=${CLANG_FORMAT_BIN}
      ${CMAKE_SOURCE_DIR}/check-format.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif()

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

find_package2_implicit_dependencies()

add_subdirectory(cmake)

install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.sh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.csh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)

Configure_File(${CMAKE_SOURCE_DIR}/cmake/scripts/fairroot-config.in ${CMAKE_BINARY_DIR}/fairroot-config @ONLY)

install(PROGRAMS ${CMAKE_BINARY_DIR}/fairroot-config
  DESTINATION bin
)


WRITE_CONFIG_FILE(config.sh)
WRITE_CONFIG_FILE(config.csh)
SET(VMCWORKDIR ${CMAKE_INSTALL_PREFIX}/share/fairbase/examples)
SET(ROOT_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
WRITE_CONFIG_FILE(config.sh_install)
WRITE_CONFIG_FILE(config.csh_install)

install_cmake_package()

# Summary ######################################################################
fairroot_summary_header()
fairroot_summary_install_prefix()
fair_summary_global_cxx_flags_standard()
fair_summary_build_types()
fairroot_summary_package_dependencies()
fairroot_summary_components()

message(STATUS "  ")
################################################################################
