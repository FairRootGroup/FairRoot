 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
Set(CTEST_SOURCE_DIRECTORY $ENV{SOURCEDIR})
Set(CTEST_BINARY_DIRECTORY $ENV{BUILDDIR})
Set(CTEST_SITE $ENV{SITE})
Set(CTEST_BUILD_NAME $ENV{LABEL})
Set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
Set(CTEST_PROJECT_NAME "FAIRROOT")

Find_Program(CTEST_GIT_COMMAND NAMES git)
Set(CTEST_UPDATE_COMMAND "${CTEST_GIT_COMMAND}")

Set(BUILD_COMMAND "make")
Set(CTEST_BUILD_COMMAND "${BUILD_COMMAND} -j$ENV{number_of_processors}")

String(TOUPPER $ENV{ctest_model} _Model)
Set(configure_options "-DCMAKE_BUILD_TYPE=${_Model}")

Set(USE_LAUNCHERS $ENV{USE_LAUNCHERS})
If(USE_LAUNCHERS)
  Set(CTEST_USE_LAUNCHERS 1)
  Set(configure_options "${configure_options};-DCTEST_USE_LAUNCHERS=${CTEST_USE_LAUNCHERS}")
EndIf()

Set(EXTRA_FLAGS $ENV{EXTRA_FLAGS})
If(EXTRA_FLAGS)
  Set(configure_options "${configure_options};${EXTRA_FLAGS}") 
EndIf()

If($ENV{ctest_model} MATCHES Nightly OR $ENV{ctest_model} MATCHES Profile)

  Find_Program(GCOV_COMMAND gcov)
  If(GCOV_COMMAND)
    Message("Found GCOV: ${GCOV_COMMAND}")
    Set(CTEST_COVERAGE_COMMAND ${GCOV_COMMAND})
  EndIf(GCOV_COMMAND)

  Set(ENV{ctest_model} Nightly)

  CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

EndIf()

Configure_File(${CTEST_SOURCE_DIRECTORY}/CTestCustom.cmake
               ${CTEST_BINARY_DIRECTORY}/CTestCustom.cmake
              )

# Copy CTestConfig.cmake to build directory.
# When building with launchers send the results to the alternative cdash server.
File(READ ${CTEST_SOURCE_DIRECTORY}/CTestConfig.cmake f0 )
If(USE_LAUNCHERS)
  String(REGEX REPLACE "cdash.gsi.de" "cdash.test.gsi.de" f1 "${f0}" )
  String(REGEX REPLACE "https" "http" f2 "${f1}" )
  File(WRITE ${CTEST_BINARY_DIRECTORY}/CTestConfig.cmake "${f2}")
Else()
  File(WRITE ${CTEST_BINARY_DIRECTORY}/CTestConfig.cmake "${f0}")
EndIf()

Ctest_Read_Custom_Files("${CTEST_BINARY_DIRECTORY}")

Ctest_Start($ENV{ctest_model})

If(NOT $ENV{ctest_model} MATCHES Experimental)
  Ctest_Update(SOURCE "${CTEST_SOURCE_DIRECTORY}")
EndIf()

Ctest_Configure(BUILD "${CTEST_BINARY_DIRECTORY}"
                OPTIONS "${configure_options}"
               )

Ctest_Build(BUILD "${CTEST_BINARY_DIRECTORY}")

Ctest_Test(BUILD "${CTEST_BINARY_DIRECTORY}" 
           PARALLEL_LEVEL $ENV{number_of_processors}
           RETURN_VALUE _ctest_test_ret_val
          )

If(GCOV_COMMAND)
  Ctest_Coverage(BUILD "${CTEST_BINARY_DIRECTORY}")
EndIf()

Ctest_Submit()
 
if (${CTEST_SITE} MATCHES "Travis")
  if (_ctest_test_ret_val)
    Message(FATAL_ERROR "Some tests failed.")
  endif()
endif()
