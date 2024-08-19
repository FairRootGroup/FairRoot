 ################################################################################
 # Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
cmake_minimum_required(VERSION 3.15...3.30 FATAL_ERROR)

set(PROJECT_MIN_CXX_STANDARD 17)

project(FairRoot VERSION 18.8.2)

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

# Load some basic macros which are needed later on
include(FairRootTargets)
include(FairRootPackage)
include(FairRootSummary)
include(FairMacros)
include(WriteConfigFile)
include(CheckCompiler)
include(FairRootCodemeta)

get_codemeta_version()
if (PROJECT_CODEMETA_VERSION
    AND NOT "${PROJECT_CODEMETA_VERSION}" STREQUAL "${PROJECT_VERSION}")
  message(AUTHOR_WARNING "Project Version (${PROJECT_VERSION}) and "
          "CodeMeta Version (${PROJECT_CODEMETA_VERSION}) do not match!")
endif()

#Check the compiler and set the compile and link flags
Check_Compiler()

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


#Check if necessary environment variables are set
#If not stop execution unless modular build is activated
#Option(FAIRROOT_MODULAR_BUILD "Modular build without environment variables" OFF)
#IF(NOT FAIRROOT_MODULAR_BUILD)
If(FAIRSOFT_CONFIG)
  IF(NOT DEFINED ENV{SIMPATH})
    MESSAGE(FATAL_ERROR "You did not define the environment variable SIMPATH which is nedded to find the external packages. Please set this variable and execute cmake again.")
  ENDIF(NOT DEFINED ENV{SIMPATH})
  STRING(REGEX MATCHALL "[^:]+" PATH $ENV{PATH})
  SET(SIMPATH $ENV{SIMPATH})
endif()

# Set option(s)
option(BUILD_UNITTESTS "Build all unittests and add them as new tests" OFF)
option(ENABLE_GEANT3_TESTING "Enable tests utilizing Geant3" OFF)
option(BUILD_ONLINE "Build the online library" ON)
option(BUILD_MBS "Build MBS" ON)
if (BUILD_MBS)
  set(BUILD_ONLINE ON)
endif()
option(BUILD_BASEMQ "Build the 'FairRoot::BaseMQ' library" ON)

# searches for needed packages
# REQUIRED means that cmake will stop if this packages are not found
# For example the framework can run without GEANT4, but ROOT is
# mandatory

if(SIMPATH)
  set(CMAKE_PREFIX_PATH ${SIMPATH} ${CMAKE_PREFIX_PATH})
  set(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${SIMPATH}/lib)
endif()

if(CMAKE_CXX_CLANG_TIDY)
  # Force clang-tidy to the same C++ Standard
  list(APPEND CMAKE_CXX_CLANG_TIDY
       "--extra-arg=-std=c++${CMAKE_CXX_STANDARD}")
endif()

# FairRoot only supports ROOT6, so check which version is available
find_package2(PUBLIC ROOT  VERSION 6.10.00  REQUIRED)
if(ROOT_vmc_FOUND)
  set(VMCLIB ROOT::VMC)
else()
  find_package2(PUBLIC VMC REQUIRED)
  set(VMCLIB VMCLibrary)
endif()
if(ROOT_VERSION VERSION_GREATER_EQUAL 6.32)
  set(_build_proof_support_default OFF)
else()
  set(_build_proof_support_default ON)
endif()
option(BUILD_PROOF_SUPPORT "Support ROOT::Proof (deprecated)" ${_build_proof_support_default})
if(ROOT_VERSION VERSION_GREATER_EQUAL 6.32 AND BUILD_PROOF_SUPPORT)
   message(FATAL_ERROR "ROOT::Proof support is not buildable, it was removed in ROOT 6.32+")
endif()
find_package2(PUBLIC FairLogger  VERSION 1.2.0 REQUIRED)

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
find_package2(PUBLIC msgpack)
find_package2(PUBLIC Flatbuffers)

find_package2(PUBLIC Geant3)
find_package2(PUBLIC Geant4)

Find_Package2(PUBLIC VGM)

find_package2(PUBLIC Geant4VMC)

find_package2(PUBLIC IWYU)

find_package2(PUBLIC GSL)
if(NOT DEFINED GTEST_ROOT)
  set(GTEST_ROOT ${SIMPATH})
endif()

if(BUILD_BASEMQ)
  find_package2(PUBLIC FairMQ VERSION 1.4.0 REQUIRED)
endif()

find_package2(PUBLIC DDS)

if(BUILD_BASEMQ OR BUILD_UNITTESTS OR BUILD_EXAMPLES)
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
  if(BUILD_UNITTESTS)
    list(APPEND boost_dependencies unit_test_framework)
  endif()
  if(BUILD_EXAMPLES)
    list(APPEND boost_dependencies program_options)
  endif()

  find_package2(PUBLIC Boost
    VERSION 1.67
    COMPONENTS ${boost_dependencies}
    ADD_REQUIREMENTS_OF FairMQ FairLogger
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
# Workaround to fix a problem with the imported target name
# The target name includes the namespace yaml-cpp begining
# from version 0.8.0. So the new exported target is now
# yaml-cpp::yaml-cpp.
if(yaml-cpp_FOUND)
  if(TARGET yaml-cpp::yaml-cpp)
    set(YAMLCPPLIB yaml-cpp::yaml-cpp)
  else()
    set(YAMLCPPLIB yaml-cpp)
  endif()
endif()

configure_file(${CMAKE_SOURCE_DIR}/cmake/private/FairRootConfigVersion.cmake.in "${CMAKE_BINARY_DIR}/FairRootConfigVersion.cmake" @ONLY)

# Load the macro to generate the needed version info at compile time
Generate_Version_Info()

# Set some useful variables
SetBasicVariables()

find_package2_implicit_dependencies()

# Recurse into the given subdirectories.  This does not actually
# cause another cmake executable to run.  The same process will walk through
# the project's entire directory structure.
add_subdirectory(fairtools)
add_subdirectory(alignment)
add_subdirectory(base)
add_subdirectory(geobase)
add_subdirectory(parbase)
add_subdirectory(generators)

if(BUILD_MBS)
  add_subdirectory(MbsAPI)
endif()
if(BUILD_ONLINE)
  add_subdirectory(online)
endif()

If(Geant3_FOUND)
 add_subdirectory(geane)
 add_subdirectory(trackbase)
EndIf ()

execute_process(COMMAND ${ROOT_CONFIG_EXECUTABLE} --has-opengl OUTPUT_VARIABLE
    ROOT_HAS_OPENGL_VAR)
if(${ROOT_HAS_OPENGL_VAR} MATCHES "yes")
  add_subdirectory(eventdisplay)
  Set(ROOT_HAS_OPENGL TRUE)
else()
  message(STATUS "eventdisplay will not be built, because ROOT has no opengl support.")
  Set(ROOT_HAS_OPENGL FALSE)
endif()

add_subdirectory(datamatch)

add_subdirectory(templates)

if(BUILD_BASEMQ)
  add_subdirectory(fairmq)
  add_subdirectory(basemq)
  add_subdirectory(parmq)
endif()

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

if(${CMAKE_BUILD_TYPE} MATCHES PROFILE)
  set(BUILD_UNITTESTS ON)
endif()
if(BUILD_UNITTESTS)
  find_package2(PRIVATE GTest REQUIRED VERSION 1.7.0)
  message(STATUS "Building the unit tests.")
  add_subdirectory(test)
endif()
add_subdirectory(test/tgeo)


add_subdirectory(cmake)

install(FILES ${CMAKE_BINARY_DIR}/config.sh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.sh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.sh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)
install(FILES ${CMAKE_BINARY_DIR}/FairVersion.h
  DESTINATION include
)
install(FILES ${CMAKE_BINARY_DIR}/config.csh_install
  DESTINATION ${CMAKE_INSTALL_BINDIR}
  RENAME FairRootConfig.csh
)
install(FILES ${CMAKE_BINARY_DIR}/check_system.csh
  DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)

find_package(Git)
set (Git_VERSION ${GIT_VERSION_STRING})
string(REPLACE "git" " " Git_ROOT ${GIT_EXECUTABLE} )
If(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
  Execute_Process(COMMAND ${GIT_EXECUTABLE} describe --tags
                  OUTPUT_VARIABLE PROJECT_GIT_VERSION
                  OUTPUT_STRIP_TRAILING_WHITESPACE
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                 )
Else()
  set(PROJECT_GIT_VERSION "v${PROJECT_VERSION}")
EndIf()
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
fairroot_summary_global_cxx_flags_standard()
fairroot_summary_build_types()
fairroot_summary_package_dependencies()
fairroot_summary_components()

message(STATUS "  ")
################################################################################
