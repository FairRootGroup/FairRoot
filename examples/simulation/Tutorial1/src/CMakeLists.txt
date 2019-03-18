 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libTutorial1" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial1/src
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
  ${CMAKE_SOURCE_DIR}/examples/common/passive
  ${CMAKE_SOURCE_DIR}/generators
  ${CMAKE_SOURCE_DIR}/base/sim/fastsim
  ${FairLogger_INCDIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${SIMPATH}/lib
)

Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
  FairTutorialDet1.cxx
  FairTutorialDet1ContFact.cxx
  FairTutorialDet1Geo.cxx
  FairTutorialDet1GeoPar.cxx
  FairTutorialDet1Point.cxx
  FairSimConfig.cxx
  FairFastSimExample.cxx
  FairFastSimExample2.cxx
)

Set(HEADERS )
Set(LINKDEF Tutorial1LinkDef.h)
Set(LIBRARY_NAME Tutorial1)
Set(DEPENDENCIES MCStack Base FairFastSim
    ${Boost_PROGRAM_OPTIONS_LIBRARY})

GENERATE_LIBRARY()

Set(Exe_Names
  runTutorial1
)

Set(Exe_Source
  runTutorial1.cxx
)

List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/simulation/Tutorial1/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/simulation/Tutorial1")

ForEach(_file RANGE 0 ${_length})
  List(GET Exe_Names ${_file} _name)
  List(GET Exe_Source ${_file} _src)
  Set(EXE_NAME ${_name})
  Set(SRCS ${_src})
  Set(DEPENDENCIES Tutorial1 Passive Gen ${FairLogger_LIBRARIES})
  GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})
