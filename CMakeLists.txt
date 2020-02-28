################################################################################
# Copyright (C) 2014-2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
cmake_policy(VERSION 3.12...3.16)

# Project ######################################################################
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(FairRootLib)

get_git_version()

project(FairRoot VERSION ${PROJECT_VERSION} LANGUAGES C CXX Fortran)
message(STATUS "${BWhite}${PROJECT_NAME}${CR} ${PROJECT_GIT_VERSION} from ${PROJECT_DATE}")

set(PROJECT_MIN_CXX_STANDARD 11)

set_fairroot_defaults()

include(CheckSymbolExists)
include(CTest)
include(FairRootChecks)
include(FairRootFindPackage2)
include(FairRootTargetRootDictionary)
include(FairRootSummary)
include(FairRootUtils)

fairroot_sanity_checks()
################################################################################


# Build options ################################################################
fairroot_build_option(BUILD_TESTING      "Build tests." DEFAULT ON)
fairroot_build_option(BUILD_EXAMPLES     "Build examples." DEFAULT ON)
fairroot_build_option(BUILD_GO_EXAMPLE   "Build Go example." DEFAULT OFF)
fairroot_build_option(BUILD_SIM          "Build simulation components." DEFAULT ON)
fairroot_build_option(BUILD_MQ           "Build message queuing components." DEFAULT ON)
fairroot_build_option(BUILD_MBS          "Build MBS API." DEFAULT ON)
fairroot_build_option(BUILD_EVENTDISPLAY "Build event display." DEFAULT OFF)
fairroot_build_option(BUILD_DOCS         "Generate documentation." DEFAULT OFF)
################################################################################


# Package components ###########################################################
if(BUILD_TESTING)
  list(APPEND PROJECT_PACKAGE_COMPONENTS tests)
endif()
if(BUILD_EXAMPLES)
  list(APPEND PROJECT_PACKAGE_COMPONENTS examples)
endif()
if(BUILD_GO_EXAMPLE)
  list(APPEND PROJECT_PACKAGE_COMPONENTS go_example)
endif()
if(BUILD_SIM)
  list(APPEND PROJECT_PACKAGE_COMPONENTS sim)
endif()
if(BUILD_MQ)
  list(APPEND PROJECT_PACKAGE_COMPONENTS mq)
endif()
if(BUILD_MBS)
  list(APPEND PROJECT_PACKAGE_COMPONENTS mbs)
endif()
if(BUILD_EVENTDISPLAY)
  list(APPEND PROJECT_PACKAGE_COMPONENTS eventdisplay)
endif()

fairroot_summary_components()
################################################################################


# Dependencies #################################################################

# Support legacy SIMPATH search hints
if(DEFINED ENV{SIMPATH})
  set(CMAKE_PREFIX_PATH "$ENV{SIMPATH}" ${CMAKE_PREFIX_PATH})
endif()

if(BUILD_TESTING)
  find_package2(PRIVATE GTest VERSION 1.7.0)
  if(NOT GTest_FOUND)
    build_bundled(GTest extern/googletest)
    find_package2(PRIVATE GTest REQUIRED)
  endif()
endif()

if(BUILD_MQ)
  find_package2(PUBLIC FairMQ REQUIRED
    VERSION 1.4.0
    FIND_DEPENDENCIES EXCEPT "msgpack;Flatbuffers;DDS;Boost;FairLogger")
  find_package2(PUBLIC Protobuf)
  find_package2(PUBLIC msgpack
    ADD_REQUIREMENTS_OF FairMQ)
  find_package2(PUBLIC Flatbuffers
    ADD_REQUIREMENTS_OF FairMQ)
  find_package2(PUBLIC DDS REQUIRED
    ADD_REQUIREMENTS_OF FairMQ)
  set(DDS_Boost_COMPONENTS system log log_setup regex filesystem thread)
  set(DDS_Boost_VERSION 1.67)
endif()

if(BUILD_SIM)
  find_package2(PUBLIC Pythia6 REQUIRED)
  find_package2(PUBLIC Pythia8 REQUIRED)
  find_package2(PUBLIC Geant3 REQUIRED)
  find_package2(PUBLIC Geant4 REQUIRED)
  find_package2(PUBLIC VGM REQUIRED)
  find_package2(PUBLIC Geant4VMC REQUIRED)
endif()

find_package2(PUBLIC IWYU)

find_package2(PUBLIC FairLogger REQUIRED
  VERSION 1.2.0
  ADD_REQUIREMENTS_OF FairMQ
  FIND_DEPENDENCIES EXCEPT "Boost")

find_package2(PUBLIC yaml-cpp REQUIRED)
# Workaround missing exported include directories
if(yaml-cpp_FOUND AND TARGET yaml-cpp AND YAML_CPP_INCLUDE_DIR AND yaml-cpp_VERSION VERSION_LESS 0.6.2)
  get_filename_component(YAML_CPP_INCLUDE_DIR "${YAML_CPP_INCLUDE_DIR}" ABSOLUTE)
  set_target_properties(yaml-cpp PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${YAML_CPP_INCLUDE_DIR}")
endif()

if(BUILD_SIM)
  list(APPEND required_root_components pythia6 pythia8)
endif()
if(BUILD_EVENTDISPLAY)
  list(APPEND required_root_components opengl)
else()
  list(APPEND optional_root_components opengl)
endif()
list(APPEND optional_root_components gdml vmc)

find_package2(PUBLIC ROOT REQUIRED
  VERSION 6.18.00
  COMPONENTS ${required_root_components}
  OPTIONAL_COMPONENTS ${optional_root_components})

if(ROOT_VERSION VERSION_LESS 6.18 OR ROOT_vmc_FOUND)
  set(VMC_LIB ROOT::VMC)
else()
  find_package2(PUBLIC VMC REQUIRED)
  set(VMC_LIB VMCLibrary)
endif()

list(APPEND boost_deps filesystem serialization)

if(NOT DEFINED Boost_NO_BOOST_CMAKE AND CMAKE_VERSION VERSION_LESS 3.15)
  # Since Boost 1.70 a CMake package is shipped by default. Unfortunately, it has a number
  # of problems that are only fixed in Boost 1.71 or CMake 3.15. By default we skip the
  # BoostConfig lookup. This can be overridden on the command line via -DBoost_NO_BOOST_CMAKE=OFF
  set(Boost_NO_BOOST_CMAKE ON)
endif()
find_package2(PUBLIC Boost REQUIRED
  VERSION 1.67
  COMPONENTS ${boost_deps}
  ADD_REQUIREMENTS_OF DDS FairLogger FairMQ
)

# Normalize Boost version
if(CMAKE_VERSION VERSION_LESS 3.15)
  set(Boost_VERSION "${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}")
endif()

if(BUILD_DOCS)
  find_package2(PRIVATE Doxygen REQUIRED
    VERSION 1.8.8
    COMPONENTS dot
    OPTIONAL_COMPONENTS mscgen dia)
endif()
################################################################################


# Targets ######################################################################
add_subdirectory(fairtools)
add_subdirectory(alignment)
add_subdirectory(base)
add_subdirectory(geobase)
add_subdirectory(parbase)
add_subdirectory(datamatch)
add_subdirectory(templates)

if(BUILD_SIM)
  add_subdirectory(base/sim/fastsim)
  add_subdirectory(fairtools/MCStepLogger)
  add_subdirectory(fairtools/MCConfigurator)
  add_subdirectory(generators)
  add_subdirectory(geane)
  add_subdirectory(trackbase)
endif()

if(BUILD_EVENTDISPLAY)
  add_subdirectory(eventdisplay)
endif()

if(BUILD_MBS)
  add_subdirectory(MbsAPI)
endif()

if(BUILD_MQ)
  add_subdirectory(base/MQ)
  add_subdirectory(parmq)
endif()

if(BUILD_DOCS)
  add_subdirectory(doxygen)
endif()

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

if(BUILD_TESTING)
  add_subdirectory(test)
endif()
################################################################################


# Configuration ################################################################
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR})

configure_file(FairVersion.h.in
  ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}/FairVersion.h @ONLY)

configure_file(fairroot-config.in
  ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_BINDIR}/fairroot-config @ONLY)

fairroot_generate_config_sh(${CMAKE_BINARY_DIR}/config.sh
  BUILD
  PATH "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_BINDIR}"
       ${ROOT_BINARY_DIR}
  DEPENDENCIES ${PROJECT_PACKAGE_DEPENDENCIES}
  VMCWORKDIR ${CMAKE_SOURCE_DIR}/examples)

fairroot_generate_config_sh(${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_BINDIR}/FairRootConfig.sh_install
  INSTALL
  PATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR}"
       ${ROOT_BINARY_DIR}
  DEPENDENCIES ${PROJECT_PACKAGE_DEPENDENCIES}
  VMCWORKDIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATADIR}")
################################################################################


# Installation #################################################################
if(BUILD_SIM)
  install(FILES
    cmake/FindGeant3.cmake
    cmake/FindGeant4.cmake
    cmake/FindGeant4VMC.cmake
    cmake/FindPythia6.cmake
    cmake/FindPythia8.cmake
    DESTINATION ${PROJECT_INSTALL_CMAKEMODDIR}
  )
endif()

if(BUILD_DOCS)
  install(DIRECTORY ${CMAKE_BINARY_DIR}/doxygen/html
    DESTINATION ${PROJECT_INSTALL_DATADIR}/docs
  )
endif()

if(BUILD_EXAMPLES)
  install(DIRECTORY
    examples/common/gconfig
    examples/common/geometry
    DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/common)
endif(BUILD_EXAMPLES)

install(FILES
  cmake/FairRootChecks.cmake
  cmake/FairRootFindPackage2.cmake
  cmake/FairRootSummary.cmake
  cmake/FairRootTargetRootDictionary.cmake
  cmake/FairRootUtils.cmake
  DESTINATION ${PROJECT_INSTALL_CMAKEMODDIR})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_INCDIR}/FairVersion.h
  DESTINATION ${PROJECT_INSTALL_INCDIR})

install(PROGRAMS ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_BINDIR}/fairroot-config
  DESTINATION ${PROJECT_INSTALL_BINDIR})

install(PROGRAMS ${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_BINDIR}/FairRootConfig.sh_install
  DESTINATION ${PROJECT_INSTALL_BINDIR} RENAME FairRootConfig.sh)

install_cmake_package()
################################################################################


# Summary ######################################################################
fairroot_summary_package_dependencies()
fairroot_summary_build_types()
fairroot_summary_cxx_standard()
fairroot_summary_global_cxx_flags()
fairroot_summary_install_prefix()
fairroot_summary_static_analysis()
fairroot_summary_spacer()
################################################################################
