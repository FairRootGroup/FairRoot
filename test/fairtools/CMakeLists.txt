 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTools" which includes the source files
# given in
# the array .
# The extension is already found.  Any number of sources could be listed
# here.

Set(INCLUDE_DIRECTORIES
 ${CMAKE_SOURCE_DIR}/fairtools
 ${CMAKE_SOURCE_DIR}/test/testlib
)

Include_Directories(${INCLUDE_DIRECTORIES})

Set(SYSTEM_INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
 ${GTEST_INCLUDE_DIRS}
)

Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

Set(Exe_Names
  _FairLoggerDeathTest1
  _FairLoggerDeathTest2
  _FairLoggerCheckDefaultSettings
  _FairLoggerCheckVerbosityLevelSetting
  _FairLoggerCheckOutputOnlytoFile
  _FairLoggerCheckWrongLogLevelSettings
  _FairLoggerTestScreenAndFileOutputWithoutArgument
  _FairLoggerTestAllLogLevelsToScreenAndFile
  _FairLoggerTestAllVerbosityLevelsToScreenAndFile

  _FairLoggerNewDeathTest1
  _FairLoggerNewDeathTest2
  _FairLoggerNewCheckDefaultSettings
  _FairLoggerNewCheckVerbosityLevelSetting
  _FairLoggerNewCheckOutputOnlytoFile
  _FairLoggerNewCheckWrongLogLevelSettings
  _FairLoggerNewTestScreenAndFileOutputWithoutArgument
  _FairLoggerNewTestAllLogLevelsToScreenAndFile
  _FairLoggerNewTestAllVerbosityLevelsToScreenAndFile
  _FairLoggerNewTestManipToScreen
  _FairLoggerNewTestManipToFile
)

Set(Exe_Source
  _FairLoggerDeathTest1.cxx
  _FairLoggerDeathTest2.cxx
  _FairLoggerCheckDefaultSettings.cxx
  _FairLoggerCheckVerbosityLevelSettings.cxx
  _FairLoggerCheckOutputOnlytoFile.cxx
  _FairLoggerCheckWrongLogLevelSettings.cxx
  _FairLoggerTestScreenAndFileOutputWithoutArgument.cxx
  _FairLoggerTestAllLogLevelsToScreenAndFile.cxx
  _FairLoggerTestAllVerbosityLevelsToScreenAndFile.cxx

  _FairLoggerNewDeathTest1.cxx
  _FairLoggerNewDeathTest2.cxx
  _FairLoggerNewCheckDefaultSettings.cxx
  _FairLoggerNewCheckVerbosityLevelSettings.cxx
  _FairLoggerNewCheckOutputOnlytoFile.cxx
  _FairLoggerNewCheckWrongLogLevelSettings.cxx
  _FairLoggerNewTestScreenAndFileOutputWithoutArgument.cxx
  _FairLoggerNewTestAllLogLevelsToScreenAndFile.cxx
  _FairLoggerNewTestAllVerbosityLevelsToScreenAndFile.cxx
  _FairLoggerNewTestManipToScreen.cxx
  _FairLoggerNewTestManipToFile.cxx
)

List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

ForEach(_file RANGE 0 ${_length})
  List(GET Exe_Names ${_file} _name)
  List(GET Exe_Source ${_file} _src)
  Set(EXE_NAME ${_name})
  Set(SRCS ${_src})
  Set(DEPENDENCIES ${ROOT_LIBRARIES} ${GTEST_BOTH_LIBRARIES} FairTools FairTest)
  GENERATE_EXECUTABLE()
  add_test(${_name} ${CMAKE_BINARY_DIR}/bin/${_name})
EndForEach(_file RANGE 0 ${_length})

#  Set(Exe_Names
#    _CoverageFairLoggerFatal
#  )

#  Set(Exe_Source
#    _CoverageFairLoggerFatal.cxx
#  )

#  List(LENGTH Exe_Names _length)
#  Math(EXPR _length ${_length}-1)

#  ForEach(_file RANGE 0 ${_length})
#    List(GET Exe_Names ${_file} _name)
#    List(GET Exe_Source ${_file} _src)
#    Set(EXE_NAME ${_name})
#    Set(SRCS ${_src})
#    Set(DEPENDENCIES ${ROOT_LIBRARIES} FairTools)
#    GENERATE_EXECUTABLE()
#    add_test(${_name} ${CMAKE_BINARY_DIR}/bin/${_name})
#  EndForEach(_file RANGE 0 ${_length})
