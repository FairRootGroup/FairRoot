################################################################################
# Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

find_package(Git)
# get_git_version([DEFAULT_VERSION version] [DEFAULT_DATE date] [OUTVAR_PREFIX prefix])
#
# Sets variables #prefix#_VERSION, #prefix#_GIT_VERSION, #prefix#_DATE, #prefix#_GIT_DATE
function(get_git_version)
  cmake_parse_arguments(ARGS "" "DEFAULT_VERSION;DEFAULT_DATE;OUTVAR_PREFIX" "" ${ARGN})

  if(NOT ARGS_OUTVAR_PREFIX)
    set(ARGS_OUTVAR_PREFIX PROJECT)
  endif()

  if(GIT_FOUND AND EXISTS ${CMAKE_SOURCE_DIR}/.git)
    execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
      OUTPUT_VARIABLE ${ARGS_OUTVAR_PREFIX}_GIT_VERSION
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
    if(${ARGS_OUTVAR_PREFIX}_GIT_VERSION)
      # cut first two characters "v-"
      string(SUBSTRING ${${ARGS_OUTVAR_PREFIX}_GIT_VERSION} 1 -1 ${ARGS_OUTVAR_PREFIX}_GIT_VERSION)
    endif()
    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd
      OUTPUT_VARIABLE ${ARGS_OUTVAR_PREFIX}_GIT_DATE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
  endif()

  if(NOT ${ARGS_OUTVAR_PREFIX}_GIT_VERSION)
    if(ARGS_DEFAULT_VERSION)
      set(${ARGS_OUTVAR_PREFIX}_GIT_VERSION ${ARGS_DEFAULT_VERSION})
    else()
      set(${ARGS_OUTVAR_PREFIX}_GIT_VERSION 0.0.0.0)
    endif()
  endif()

  if(NOT ${ARGS_OUTVAR_PREFIX}_GIT_DATE)
    if(ARGS_DEFAULT_DATE)
      set(${ARGS_OUTVAR_PREFIX}_GIT_DATE ${ARGS_DEFAULT_DATE})
    else()
      set(${ARGS_OUTVAR_PREFIX}_GIT_DATE "Thu Jan 1 00:00:00 1970 +0000")
    endif()
  endif()

  string(REGEX MATCH "^([^-]*)" blubb ${${ARGS_OUTVAR_PREFIX}_GIT_VERSION})

  # return values
  set(${ARGS_OUTVAR_PREFIX}_VERSION ${CMAKE_MATCH_0} PARENT_SCOPE)
  set(${ARGS_OUTVAR_PREFIX}_DATE ${${ARGS_OUTVAR_PREFIX}_GIT_DATE} PARENT_SCOPE)
  set(${ARGS_OUTVAR_PREFIX}_GIT_VERSION ${${ARGS_OUTVAR_PREFIX}_GIT_VERSION} PARENT_SCOPE)
  set(${ARGS_OUTVAR_PREFIX}_GIT_DATE ${${ARGS_OUTVAR_PREFIX}_GIT_DATE} PARENT_SCOPE)
endfunction()


# Set defaults
macro(set_fairroot_defaults)
  string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)
  string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

  set(CMAKE_INSTALL_MESSAGE LAZY)

  # Set a default build type
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
  endif()

  # Handle C++ standard level
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD ${PROJECT_MIN_CXX_STANDARD})
  elseif(${CMAKE_CXX_STANDARD} LESS ${PROJECT_MIN_CXX_STANDARD})
    message(FATAL_ERROR "A minimum CMAKE_CXX_STANDARD of ${PROJECT_MIN_CXX_STANDARD} is required.")
  endif()
  set(CMAKE_CXX_EXTENSIONS OFF)

  if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "Whether to build shared libraries or static archives")
  endif()

  # Set -fPIC as default for all library types
  if(NOT CMAKE_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  endif()

  # Generate compile_commands.json file (https://clang.llvm.org/docs/JSONCompilationDatabase.html)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  # Define CMAKE_INSTALL_*DIR family of variables
  include(GNUInstallDirs)

  # Define install dirs
  set(PROJECT_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
  set(PROJECT_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
  set(PROJECT_INSTALL_INCDIR ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER})
  set(PROJECT_INSTALL_DATADIR ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME_LOWER})
  set(PROJECT_INSTALL_CMAKEMODDIR ${PROJECT_INSTALL_DATADIR}/cmake)

  # https://cmake.org/Wiki/CMake_RPATH_handling
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}" isSystemDir)
  if("${isSystemDir}" STREQUAL "-1")
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
      set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,--enable-new-dtags")
      set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "-Wl,--enable-new-dtags")
      set(CMAKE_INSTALL_RPATH "$ORIGIN/../${PROJECT_INSTALL_LIBDIR}")
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
      set(CMAKE_INSTALL_RPATH "@loader_path/../${PROJECT_INSTALL_LIBDIR}")
    else()
      set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_LIBDIR}")
    endif()
  endif()

  # Define export set, only one for now
  set(PROJECT_EXPORT_SET ${PROJECT_NAME}Targets)

  # Configure build types
  if(CMAKE_SYSTEM_NAME MATCHES Linux)
    if(CMAKE_COMPILER_IS_GNUCXX)
      set(CMAKE_CONFIGURATION_TYPES "RELWITHDEBINFO" "NIGHTLY" "TEST" "RELEASE" "DEBUG" "DEBUGFULL" "PROFILE" "ARRAY_CHECK")

      set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -Wshadow")
      set(CMAKE_CXX_FLAGS_NIGHTLY        "-O0 -g -Wshadow")
      set(CMAKE_CXX_FLAGS_TEST           "-O2 -g -Wshadow")
      set(CMAKE_CXX_FLAGS_RELEASE        "-O2 -Wshadow ")

      set(CMAKE_CXX_FLAGS_DEBUG          "-g -Wshadow ")
      set(CMAKE_CXX_FLAGS_DEBUGFULL      "-g3 -fno-inline -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -Wall -W -Wpointer-arith -Wformat-security -fno-exceptions -fno-check-new -fno-common -fexceptions")
      set(CMAKE_CXX_FLAGS_PROFILE        "-g3 -fno-inline -ftest-coverage -fprofile-arcs -Wshadow -Wall -Wextra -Wunused-variable")
      set(CMAKE_CXX_FLAGS_ARRAY_CHECK    "-g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")

      set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
      set(CMAKE_C_FLAGS_RELEASE          "-O2")
#     set(CMAKE_C_FLAGS_DEBUG            "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
      set(CMAKE_C_FLAGS_DEBUG            "-g")
      set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common -fexceptions")
      set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")
      set(CMAKE_C_FLAGS_ARRAY_CHECK      "-g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")
    endif()

    if(CMAKE_C_COMPILER MATCHES "icc")
      set(CMAKE_CONFIGURATION_TYPES "RELWITHDEBINFO" "RELEASE" "DEBUG" "DEBUGFULL")

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
      Execute_process(COMMAND which icpc OUTPUT_VARIABLE _bla)
      String(REPLACE "bin" "compiler/lib" _intel_lib_dirs ${_bla})
      String(REPLACE "/icpc" "" _intel_lib_dirs ${_intel_lib_dirs})
      String(STRIP ${_intel_lib_dirs} _intel_lib_dirs)
    endif()

    if(CMAKE_C_COMPILER MATCHES "clang")
      set(CMAKE_C_FLAGS_PROFILE           "--coverage -g3")
      set(CMAKE_CXX_FLAGS_PROFILE         "--coverage -g3")
    endif()
  elseif(CMAKE_SYSTEM_NAME MATCHES Darwin)
    EXEC_PROGRAM("sw_vers -productVersion | cut -d . -f 1-2" OUTPUT_VARIABLE MAC_OS_VERSION)
    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
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

#      MESSAGE("C_FLAGS: ${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS}")
#      MESSAGE("CXX_FLAGS: ${CMAKE_SHARED_LIBRARY_CREATE_CXX_FLAGS}")
      Execute_Process(COMMAND gfortran -print-file-name=libgfortran.dylib
                      OUTPUT_VARIABLE FORTRAN_LIBDIR
                     )
      Get_Filename_Component(FORTRAN_LIBDIR ${FORTRAN_LIBDIR}
                             PATH
                            )
      Message("-- Fortran libraries found in ${FORTRAN_LIBDIR}")
      SET(CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_Fortran_FLAGS} -flat_namespace -single_module -undefined dynamic_lookup")

      # Configure build types
      set(CMAKE_CONFIGURATION_TYPES "RELWITHDEBINFO" "NIGHTLY" "RELEASE" "DEBUG" "DEBUGFULL" "PROFILE")
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
        Message("CXX Compiler: ${CMAKE_CXX_COMPILER}")
        Message("CXX Compiler ABI: ${CMAKE_CXX_COMPILER_ABI}")
        Message("CXX Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
        MESSAGE(FATAL_ERROR "This compiler is not known.")
    endif()
  endif()

  get_filename_component (Fortran_COMPILER_NAME ${CMAKE_Fortran_COMPILER} NAME)
  if(Fortran_COMPILER_NAME STREQUAL "gfortran")
    # gfortran
    set (Fortran_UseLib "gfortran")
  elseif(Fortran_COMPILER_NAME STREQUAL "f95")
    # gfortran
    message("f95 found -> gfortran")
    set (Fortran_UseLib "gfortran")
  elseif(Fortran_COMPILER_NAME STREQUAL "g77")
    # g77
    set (Fortran_UseLib "g2c")
  elseif(Fortran_COMPILER_NAME STREQUAL "f77")
    # g77
    message("f77 found -> g77")
    set (Fortran_UseLib "g2c")
  else()
    message ("Fortran compiler not known/tested")
  endif()

  if(CMAKE_GENERATOR STREQUAL "Ninja" AND
     ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9) OR
      (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)))
    # Force colored warnings in Ninja's output, if the compiler has -fdiagnostics-color support.
    # Rationale in https://github.com/ninja-build/ninja/issues/814
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
  endif()

  if(NOT PROJECT_VERSION_TWEAK)
    set(PROJECT_VERSION_HOTFIX 0)
  else()
    set(PROJECT_VERSION_HOTFIX ${PROJECT_VERSION_TWEAK})
  endif()

  if(NOT DEFINED RUN_STATIC_ANALYSIS)
    set(RUN_STATIC_ANALYSIS OFF)
  endif()

  unset(PROJECT_STATIC_ANALYSERS)
  if(RUN_STATIC_ANALYSIS)
    set(analyser "clang-tidy")
    find_program(${analyser}_FOUND "${analyser}")
    if(${analyser}_FOUND)
      set(CMAKE_CXX_CLANG_TIDY "${${analyser}_FOUND}")
    endif()
    list(APPEND PROJECT_STATIC_ANALYSERS "${analyser}")

    set(analyser "iwyu")
    find_program(${analyser}_FOUND "${analyser}")
    if(${analyser}_FOUND)
      set(CMAKE_CXX_IWYU "${${analyser}_FOUND}")
    endif()
    list(APPEND PROJECT_STATIC_ANALYSERS "${analyser}")

    set(analyser "cpplint")
    find_program(${analyser}_FOUND "${analyser}")
    if(${analyser}_FOUND)
      set(CMAKE_CXX_CPPLINT "${${analyser}_FOUND}")
    endif()
    list(APPEND PROJECT_STATIC_ANALYSERS "${analyser}")
  endif()

  if(CMAKE_GENERATOR STREQUAL Ninja AND ENABLE_CCACHE)
    find_program(CCACHE ccache)
    if(CCACHE)
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE})
    endif()
  endif()

  set(VMCWORKDIR ${PROJECT_INSTALL_DATADIR}/examples)
endmacro()

function(fairroot_add_standard_library_properties target)
  string(TOLOWER ${target} __libname__)
  set_target_properties(${target} PROPERTIES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
    LIBRARY_OUTPUT_NAME ${PROJECT_NAME_LOWER}-${__libname__}
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_INSTALL_LIBDIR}")
endfunction()

function(join VALUES GLUE OUTPUT)
  string(REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")
  string(REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping
  set(${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)
endfunction()

function(generate_package_dependencies)
  join("${PROJECT_INTERFACE_PACKAGE_DEPENDENCIES}" " " DEPS)
  set(PACKAGE_DEPENDENCIES "\
####### Expanded from @PACKAGE_DEPENDENCIES@ by configure_package_config_file() #######

set(${PROJECT_NAME}_PACKAGE_DEPENDENCIES ${DEPS})

")
  foreach(dep IN LISTS PROJECT_INTERFACE_PACKAGE_DEPENDENCIES)
    join("${PROJECT_INTERFACE_${dep}_COMPONENTS}" " " COMPS)
    if(COMPS)
      string(CONCAT PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} "\
set(${PROJECT_NAME}_${dep}_COMPONENTS ${COMPS})
")
    endif()
    join("${PROJECT_INTERFACE_${dep}_OPTIONAL_COMPONENTS}" " " OPT_COMPS)
    if(OPT_COMPS)
      string(CONCAT PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} "\
set(${PROJECT_NAME}_${dep}_OPTIONAL_COMPONENTS ${OPT_COMPS})
")
    endif()
    if(PROJECT_INTERFACE_${dep}_VERSION)
      string(CONCAT PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} "\
set(${PROJECT_NAME}_${dep}_VERSION ${PROJECT_INTERFACE_${dep}_VERSION})
")
    endif()
  endforeach()
  string(CONCAT PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} "\

#######################################################################################
")
set(PACKAGE_DEPENDENCIES ${PACKAGE_DEPENDENCIES} PARENT_SCOPE)
endfunction()

function(generate_package_components)
  join("${PROJECT_PACKAGE_COMPONENTS}" " " COMPS)
  set(PACKAGE_COMPONENTS "\
####### Expanded from @PACKAGE_COMPONENTS@ by configure_package_config_file() #########

set(${PROJECT_NAME}_PACKAGE_COMPONENTS ${COMPS})

")
  foreach(comp IN LISTS PROJECT_PACKAGE_COMPONENTS)
    string(CONCAT PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} "\
set(${PROJECT_NAME}_${comp}_FOUND TRUE)
")
  endforeach()
  string(CONCAT PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} "\

check_required_components(${PROJECT_NAME})
")
set(PACKAGE_COMPONENTS ${PACKAGE_COMPONENTS} PARENT_SCOPE)
endfunction()

# Configure/Install CMake package
macro(install_cmake_package)
  list(SORT PROJECT_PACKAGE_DEPENDENCIES)
  list(SORT PROJECT_INTERFACE_PACKAGE_DEPENDENCIES)
  include(CMakePackageConfigHelpers)
  set(PACKAGE_INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}-${PROJECT_VERSION}
  )
  install(EXPORT ${PROJECT_EXPORT_SET}
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${PACKAGE_INSTALL_DESTINATION}
    EXPORT_LINK_INTERFACE_LIBRARIES
  )
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
  )
  generate_package_dependencies() # fills ${PACKAGE_DEPENDENCIES}
  generate_package_components() # fills ${PACKAGE_COMPONENTS}
  string(TOUPPER ${CMAKE_BUILD_TYPE} PROJECT_BUILD_TYPE_UPPER)
  set(PROJECT_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${PROJECT_BUILD_TYPE_UPPER}})
  configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${PACKAGE_INSTALL_DESTINATION}
    PATH_VARS CMAKE_INSTALL_PREFIX
  )
  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${PACKAGE_INSTALL_DESTINATION}
  )
endmacro()

macro(fairroot_build_option option description)
  cmake_parse_arguments(ARGS "" "DEFAULT" "REQUIRES" ${ARGN})

  if(ARGS_DEFAULT)
    set(__default__ ON)
  else()
    set(__default__ OFF)
  endif()

  if(ARGS_REQUIRES)
    include(CMakeDependentOption)
    set(__requires__ ${ARGS_REQUIRES})
    foreach(d ${__requires__})
      string(REGEX REPLACE " +" ";" __requires_condition__ "${d}")
      if(${__requires_condition__})
      else()
        if(${option})
          message(FATAL_ERROR "Cannot enable build option ${option}, depending option is not set: ${__requires_condition__}")
        endif()
      endif()
    endforeach()
  else()
    set(__requires__)
  endif()

  if(__requires__)
    cmake_dependent_option(${option} ${description} ${__default__} "${__requires__}" OFF)
  else()
    option(${option} ${description} ${__default__})
  endif()

  set(__default__)
  set(__requires__)
  set(__requires_condition__)
  set(ARGS_DEFAULT)
  set(ARGS_REQUIRES)
  set(option)
  set(description)
endmacro()

macro(exec cmd)
  join("${ARGN}" " " args)
  file(APPEND ${${package}_BUILD_LOGFILE} ">>> ${cmd} ${args}\n")

  execute_process(COMMAND ${cmd} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_VARIABLE log
    ERROR_VARIABLE log
    RESULT_VARIABLE res
  )
  file(APPEND ${${package}_BUILD_LOGFILE} ${log})

  if(res)
    message(FATAL_ERROR "${res} \nSee also \"${${package}_BUILD_LOGFILE}\"")
  endif()
endmacro()

macro(exec_source cmd)
  join("${ARGN}" " " args)
  file(APPEND ${${package}_BUILD_LOGFILE} ">>> ${cmd} ${args}\n")

  execute_process(COMMAND ${cmd} ${ARGN}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE log
    ERROR_VARIABLE log
    RESULT_VARIABLE res
  )
  file(APPEND ${${package}_BUILD_LOGFILE} ${log})

  if(res)
    message(FATAL_ERROR "${res} \nSee also \"${${package}_BUILD_LOGFILE}\"")
  endif()
endmacro()

function(build_bundled package bundle)
  message(STATUS "Building bundled ${package}")

  set(${package}_SOURCE_DIR ${CMAKE_SOURCE_DIR}/${bundle})
  set(${package}_BINARY_DIR ${CMAKE_BINARY_DIR}/${bundle})
  file(MAKE_DIRECTORY ${${package}_BINARY_DIR})
  set(${package}_BUILD_LOGFILE ${${package}_BINARY_DIR}/build.log)
  file(REMOVE ${${package}_BUILD_LOGFILE})

  if(Git_FOUND)
    exec_source(${GIT_EXECUTABLE} submodule update --init -- ${${package}_SOURCE_DIR})
  endif()

  if(${package} STREQUAL GTest)
    set(${package}_INSTALL_DIR ${CMAKE_BINARY_DIR}/${bundle}_install)
    file(MAKE_DIRECTORY ${${package}_INSTALL_DIR})
    set(${package}_ROOT ${${package}_INSTALL_DIR})

    exec(${CMAKE_COMMAND} -S ${${package}_SOURCE_DIR} -B ${${package}_BINARY_DIR} -G ${CMAKE_GENERATOR}
      -DCMAKE_INSTALL_PREFIX=${${package}_INSTALL_DIR} -DBUILD_GMOCK=OFF -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
    )
    exec(${CMAKE_COMMAND} --build ${${package}_BINARY_DIR})
    exec(${CMAKE_COMMAND} --build ${${package}_BINARY_DIR} --target install)
  endif()

  string(TOUPPER ${package} package_upper)
  set(${package_upper}_ROOT "${${package}_ROOT}" CACHE PATH "Bundled ${package} install prefix search hint")
  set(${package}_BUNDLED ON CACHE BOOL "Whether bundled ${package} was used")

  message(STATUS "Building bundled ${package} - done")
endfunction()

macro(fairroot_summary_components)
  fairroot_summary_spacer()
  message(STATUS "  ${Cyan}COMPONENT           BUILT?  INFO${CR}")
  if(BUILD_SIM)
    set(sim_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_SIM=OFF${CR})")
  else()
    set(sim_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBBUILD_SIM=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}sim${CR}                  ${sim_summary}")
  if(BUILD_MQ)
    set(mq_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_MQ=OFF${CR})")
  else()
    set(mq_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBBUILD_MQ=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}mq${CR}                   ${mq_summary}")
  if(BUILD_MBS)
    set(mbs_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_MBS=OFF${CR})")
  else()
    set(mbs_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBBUILD_MBS=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}mbs${CR}                  ${mbs_summary}")
  if(BUILD_EVENTDISPLAY)
    set(ev_summary "${BGreen}YES${CR}    (disable with ${BMagenta}-DBUILD_EVENTDISPLAY=OFF${CR})")
  else()
    set(ev_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBBUILD_EVENTDISPLAY=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}eventdisplay${CR}         ${ev_summary}")
  if(BUILD_EXAMPLES)
    set(examples_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_EXAMPLES=OFF${CR})")
  else()
    set(examples_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBBUILD_EXAMPLES=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}examples${CR}             ${examples_summary}")
  if(BUILD_TESTING)
    set(tests_summary "${BGreen} YES${CR}    (default, disable with ${BMagenta}-DBUILD_TESTING=OFF${CR})")
  else()
    set(tests_summary "${BRed} NO${CR}     (enable with ${BMagenta}-DBUILD_TESTING=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}tests${CR}               ${tests_summary}")
  if(BUILD_GO_EXAMPLE)
    set(go_summary "${BGreen} YES${CR}    (disable with ${BMagenta}-DBUILD_GO_EXAMPLE=OFF${CR})")
  else()
    set(go_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBUILD_GO_EXAMPLE=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}go_example${CR}           ${go_summary}")
  if(BUILD_DOCS)
    set(docs_summary "${BGreen}YES${CR}    (disable with ${BMagenta}-DBUILD_DOCS=OFF${CR})")
  else()
    set(docs_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBUILD_DOCS=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}docs${CR}                 ${docs_summary}")
  fairroot_summary_spacer()
endmacro()
