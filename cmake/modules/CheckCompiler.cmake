 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
MACRO ( Check_Compiler )


# Set a default build type for single-configuration
# CMake generators if no build type is set.
if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)


if ((NOT CMAKE_CXX_STANDARD) AND TARGET ROOT::Core)
  get_property(ROOT_CXX_STANDARD TARGET ROOT::Core
               PROPERTY INTERFACE_COMPILE_FEATURES)
  message(VERBOSE "Using ROOT to detect CXX_STANDARD: [${ROOT_CXX_STANDARD}]")
  list(FILTER ROOT_CXX_STANDARD INCLUDE REGEX "^cxx_std_.*")
  list(TRANSFORM ROOT_CXX_STANDARD REPLACE "^cxx_std_" "")
  list(SORT ROOT_CXX_STANDARD ORDER DESCENDING)
  list(GET ROOT_CXX_STANDARD 0 ROOT_CXX_STANDARD)
  if(ROOT_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD ${ROOT_CXX_STANDARD})
    message(VERBOSE "Taking CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} from ROOT")
  endif()
endif()

if (NOT CMAKE_CXX_STANDARD)
  find_program(FAIRSOFT_CONFIG fairsoft-config PATHS $ENV{SIMPATH}/bin $ENV{FAIRSOFT_ROOT}/bin NO_DEFAULT_PATH)

  if(FAIRSOFT_CONFIG)
    message(VERBOSE "fairsoft-config found")
    Execute_Process(COMMAND ${FAIRSOFT_CONFIG} --cxxflags
                    OUTPUT_VARIABLE FAIRSOFT_CXX_FLAGS)
    unset(CMAKE_MATCH_1)
    String(REGEX REPLACE "-std=c\\+\\+(..)" "" FAIRSOFT_CXX_FLAGS "${FAIRSOFT_CXX_FLAGS}")
    if(CMAKE_MATCH_1)
      set(CMAKE_CXX_STANDARD ${CMAKE_MATCH_1})
      message(VERBOSE "Taking CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} from fairsoft-config")
    endif()
  endif()
endif()

if (FairRoot_CXX_STANDARD)
  if ((NOT CMAKE_CXX_STANDARD)
      OR (CMAKE_CXX_STANDARD VERSION_LESS FairRoot_CXX_STANDARD))
    set(CMAKE_CXX_STANDARD "${FairRoot_CXX_STANDARD}")
  endif()
endif()

if (PROJECT_MIN_CXX_STANDARD)
  if ((NOT CMAKE_CXX_STANDARD)
      OR (CMAKE_CXX_STANDARD VERSION_LESS PROJECT_MIN_CXX_STANDARD))
    set(CMAKE_CXX_STANDARD "${PROJECT_MIN_CXX_STANDARD}")
  endif()
endif()


if (CMAKE_SYSTEM_NAME MATCHES Linux)
   MESSAGE("--- Found a Linux system")
   if (CMAKE_COMPILER_IS_GNUCXX)
     MESSAGE("--- Found GNU compiler collection")

     # Configure build types
     set(CMAKE_CONFIGURATION_TYPES "RELWITHDEBINFO" "NIGHTLY" "TEST" "RELEASE" "DEBUG" "DEBUGFULL" "PROFILE" "ARRAY_CHECK")
     set(_FR_COMMON_CXX_FLAGS "-Wshadow -Wall")

     set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${_FR_COMMON_CXX_FLAGS} -O2 -g")
     set(CMAKE_CXX_FLAGS_NIGHTLY        "${_FR_COMMON_CXX_FLAGS} -O0 -g")
     set(CMAKE_CXX_FLAGS_TEST           "${_FR_COMMON_CXX_FLAGS} -O2 -g")
     set(CMAKE_CXX_FLAGS_RELEASE        "${_FR_COMMON_CXX_FLAGS} -O2")

     set(CMAKE_CXX_FLAGS_DEBUG          "${_FR_COMMON_CXX_FLAGS} -g")
     set(CMAKE_CXX_FLAGS_DEBUGFULL      "${_FR_COMMON_CXX_FLAGS} -g3 -fno-inline -Wnon-virtual-dtor -Wno-long-long -ansi -Wundef -Wcast-align -Wchar-subscripts -W -Wpointer-arith -Wformat-security -fno-exceptions -fno-check-new -fno-common -fexceptions")
     set(CMAKE_CXX_FLAGS_PROFILE        "${_FR_COMMON_CXX_FLAGS} -g3 -fno-inline -ftest-coverage -fprofile-arcs -Wextra -Wunused-variable")
     set(CMAKE_CXX_FLAGS_ARRAY_CHECK    "${_FR_COMMON_CXX_FLAGS} -g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")

     set(CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g")
     set(CMAKE_C_FLAGS_RELEASE          "-O2")
#     set(CMAKE_C_FLAGS_DEBUG            "-g -O2 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
     set(CMAKE_C_FLAGS_DEBUG            "-g")
     set(CMAKE_C_FLAGS_DEBUGFULL        "-g3 -fno-inline -Wno-long-long -std=iso9899:1990 -Wundef -Wcast-align -Werror-implicit-function-declaration -Wchar-subscripts -Wall -W -Wpointer-arith -Wwrite-strings -Wformat-security -Wmissing-format-attribute -fno-common -fexceptions")
     set(CMAKE_C_FLAGS_PROFILE          "-g3 -fno-inline -ftest-coverage -fprofile-arcs")
     set(CMAKE_C_FLAGS_ARRAY_CHECK      "-g3 -fno-inline -ftest-coverage -fprofile-arcs -fstack-protector")

   endif (CMAKE_COMPILER_IS_GNUCXX)

   if (CMAKE_C_COMPILER MATCHES "icc")
      MESSAGE("--- Found Intel compiler collection")
   # Select flags.
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

   endif (CMAKE_C_COMPILER MATCHES "icc")

   if (CMAKE_C_COMPILER MATCHES "clang")
      MESSAGE("-- Clang compiler")

    # Select flags.
      set(CMAKE_C_FLAGS_PROFILE           "--coverage -g3")
      set(CMAKE_CXX_FLAGS_PROFILE         "--coverage -g3")

   endif (CMAKE_C_COMPILER MATCHES "clang")
endif (CMAKE_SYSTEM_NAME MATCHES Linux)


if (CMAKE_SYSTEM_NAME MATCHES Darwin)
   EXEC_PROGRAM("sw_vers -productVersion | cut -d . -f 1-2" OUTPUT_VARIABLE MAC_OS_VERSION)
   MESSAGE("-- Found a Mac OS X System ${MAC_OS_VERSION}")
   if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      MESSAGE("-- Found GNU compiler collection")

      STRING(COMPARE EQUAL "10.5" "${MAC_OS_VERSION}" MAC_OS_10_5)
      STRING(COMPARE EQUAL "10.6" "${MAC_OS_VERSION}" MAC_OS_10_6)
      STRING(COMPARE EQUAL "10.7" "${MAC_OS_VERSION}" MAC_OS_10_7)
      IF(MAC_OS_10_5 OR MAC_OS_10_6 OR MAC_OS_10_7)
        SET(CMAKE_CXX_FLAGS "-m64")
        SET(CMAKE_C_FLAGS "-m64")
        SET(CMAKE_Fortran_FLAGS "-m64")
      ENDIF(MAC_OS_10_5 OR MAC_OS_10_6 OR MAC_OS_10_7)

      Execute_Process(COMMAND gfortran -print-file-name=libgfortran.dylib
                      OUTPUT_VARIABLE FORTRAN_LIBDIR
                     )
      Get_Filename_Component(FORTRAN_LIBDIR ${FORTRAN_LIBDIR}
                             PATH
                            )
      Message("-- Fortran libraries found in ${FORTRAN_LIBDIR}")

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


   else (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        Message("CXX Compiler: ${CMAKE_CXX_COMPILER}")
        Message("CXX Compiler ABI: ${CMAKE_CXX_COMPILER_ABI}")
        Message("CXX Compiler ID: ${CMAKE_CXX_COMPILER_ID}")
        MESSAGE(FATAL_ERROR "This compiler is not known.")
   endif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")


endif (CMAKE_SYSTEM_NAME MATCHES Darwin)


if (CMAKE_BUILD_TYPE)
  STRING(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UPPER)
  SET(CMAKE_BUILD_TYPE_CXXFLAGS_KEY CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE_UPPER})
endif ()

#MESSAGE("--- Build Type: ${CMAKE_BUILD_TYPE}")
#MESSAGE("--- Compiler Flags: ${CMAKE_CXX_FLAGS}  ${${CMAKE_BUILD_TYPE_CXXFLAGS_KEY}}")

ENDMACRO ( Check_Compiler )
