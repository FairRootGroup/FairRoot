 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairTestDetector" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${ROOT_INCLUDE_DIR}
${ZMQ_INCLUDE_DIR}
${MYSQL_INCLUDE_DIR}
${POSTGRESQL_INCLUDE_DIR}
${SQLITE_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/parbase/dbIO
${CMAKE_SOURCE_DIR}/fairmq
${CMAKE_SOURCE_DIR}/base/MQ
${CMAKE_SOURCE_DIR}/example/mcstack
${CMAKE_SOURCE_DIR}/example/Tutorial6
${CMAKE_SOURCE_DIR}/example/Tutorial6/data
${CMAKE_SOURCE_DIR}/example/Tutorial6/sim
${CMAKE_SOURCE_DIR}/example/Tutorial6/streams
${CMAKE_SOURCE_DIR}/example/Tutorial6/reco
${CMAKE_SOURCE_DIR}/example/Tutorial6/params
)

include_directories(${INCLUDE_DIRECTORIES})

if (Boost_FOUND)
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/run_sps_init.sh.in ${CMAKE_BINARY_DIR}/bin/run_sps_init.sh )
  file(COPY  ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/dbconfig.sh DESTINATION ${CMAKE_BINARY_DIR}/bin/ )
endIf (Boost_FOUND)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
    ${MYSQL_LIBRARY_DIR}
    ${POSTGRESQL_LIBRARY_DIR}
    ${SQLITE_LIBRARY_DIR}
) 

link_directories(${LINK_DIRECTORIES})

set(SRCS
  sim/FairTestDetector.cxx
  sim/FairTestDetectorContFact.cxx
  sim/FairTestDetectorGeo.cxx
  sim/FairTestDetectorGeoPar.cxx
  sim/FairConstField.cxx
  sim/FairConstPar.cxx
  sim/FairMapPar.cxx
  sim/FairTestDetectorPoint.cxx
  sim/FairTestDetectorHit.cxx
  sim/FairTestDetectorDigi.cxx		
  sim/FairTestDetectorDigiTask.cxx		
  reco/FairTestDetectorRecoTask.cxx
  params/FairDbTutPar.cxx
  params/FairDbTutContFact.cxx
)

set(LINKDEF FairTestDetectorLinkDef.h)
set(LIBRARY_NAME FairDbMQ)

if (Boost_FOUND)
  Set(DEPENDENCIES
    Base FairDB ParBase MCStack FairMQ FairMQSampler boost_thread boost_system boost_serialization)
else (Boost_FOUND)
  Set(DEPENDENCIES Base  FairDB ParBase MCStack)
endif (Boost_FOUND)

GENERATE_LIBRARY()



if (Boost_FOUND)
  Set(Exe_Names
    testDetectorSamplerInitBin
    testDetectorProcessorInitBin
    fileSinkInitBin 
  )


 set(Exe_Source
    run/runTestDetectorSamplerBin.cxx
    run/runTestDetectorProcessorBin.cxx
    run/runFileSinkBin.cxx
    )

  list(LENGTH Exe_Names _length)
  math(EXPR _length ${_length}-1)

  foreach(_file RANGE 0 ${_length})
    list(GET Exe_Names ${_file} _name)
    list(GET Exe_Source ${_file} _src)
    set(EXE_NAME ${_name})
    set(SRCS ${_src})
    set(DEPENDENCIES FairDB ParBase FairDbMQ)
    GENERATE_EXECUTABLE()
  endforeach(_file RANGE 0 ${_length})
endif (Boost_FOUND)
