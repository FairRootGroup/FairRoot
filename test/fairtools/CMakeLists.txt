################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(dependencies
  FairRoot::FairTools
  FairRoot::FairTest
  GTest::GTest
  GTest::Main
)

list(APPEND tests
  _FairLoggerCheckDefaultSettings
  _FairLoggerCheckOutputOnlytoFile
  _FairLoggerCheckVerbosityLevelSettings
  _FairLoggerCheckWrongLogLevelSettings
  _FairLoggerDeathTest1
  _FairLoggerDeathTest2
  _FairLoggerTestAllLogLevelsToScreenAndFile
  _FairLoggerTestAllVerbosityLevelsToScreenAndFile
  _FairLoggerTestScreenAndFileOutputWithoutArgument

  _FairLoggerNewCheckDefaultSettings
  _FairLoggerNewCheckOutputOnlytoFile
  _FairLoggerNewCheckVerbosityLevelSettings
  _FairLoggerNewCheckWrongLogLevelSettings
  _FairLoggerNewDeathTest1
  _FairLoggerNewDeathTest2
  _FairLoggerNewTestAllLogLevelsToScreenAndFile
  _FairLoggerNewTestAllVerbosityLevelsToScreenAndFile
  _FairLoggerNewTestManipToFile
  _FairLoggerNewTestManipToScreen
  _FairLoggerNewTestScreenAndFileOutputWithoutArgument
)

foreach(test IN LISTS tests)
  add_executable(${test} ${test}.cxx)
  target_link_libraries(${test} ${dependencies})
  add_test(NAME ${test}
           COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${test})
endforeach()
