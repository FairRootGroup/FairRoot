 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Date: 13.08.14 D.Bertini
# Create a library called "libDbMQ" 
#
# All SQL drivers "includes" and "libraries" are not imeediately set 
# because of the problem i have with CMAKE and variable set to not-found
# Instead  those are added only if they have been previously set  


Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/parbase/dbIO
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/base/MQ
  ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
  ${CMAKE_SOURCE_DIR}/base/MQ/devices
  ${CMAKE_SOURCE_DIR}/base/MQ/tasks
  ${CMAKE_SOURCE_DIR}/dbase/dbMQ/utils
  ${CMAKE_SOURCE_DIR}/dbase/dbMQ/actors
  ${CMAKE_SOURCE_DIR}/example/mcstack
  ${CMAKE_SOURCE_DIR}/example/Tutorial6
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/data
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/sim
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/streams
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/reco
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/params
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/param
  ${CMAKE_SOURCE_DIR}/example/Tutorial6/db
  ${CMAKE_SOURCE_DIR}/example/Tutorial3/data
)


Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
  ${ZMQ_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

if (Boost_FOUND)
  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/run_sps_init.sh.in ${CMAKE_BINARY_DIR}/bin/run_sps_init.sh )
  file(COPY  ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/dbconfig.sh DESTINATION ${CMAKE_BINARY_DIR}/bin/ )
endIf (Boost_FOUND)

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
) 

Link_Directories(${LINK_DIRECTORIES})

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
  params/FairDbTutPar2.cxx
  params/FairDbTutContFact2.cxx
)

Set(NO_DICT_SRCS
  db/FairDbMQTutWorker.cxx  
)

  If(PROTOBUF_FOUND)
    add_custom_command( 
      OUTPUT
        ${CMAKE_SOURCE_DIR}/example/Tutorial6/streams/FairTestDetectorPayload.pb.h
        ${CMAKE_SOURCE_DIR}/example/Tutorial6/streams/FairTestDetectorPayload.pb.cc
      COMMAND
        ${SIMPATH}/bin/protoc -I=. --cpp_out=. FairTestDetectorPayload.proto
      WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/example/Tutorial6/streams
      )

    Set(NO_DICT_SRCS
      ${NO_DICT_SRCS}
      streams/FairTestDetectorPayload.pb.cc
    )
  Endif(PROTOBUF_FOUND)


set(LINKDEF FairTestDetectorLinkDef.h)
set(LIBRARY_NAME TutFairDbMQ)

if (Boost_FOUND)
  Set(DEPENDENCIES
    Base FairDB ParBase MCStack FairMQ BaseMQ FairDbMQ boost_thread boost_system boost_serialization)
else (Boost_FOUND)
  Set(DEPENDENCIES Base  FairDB ParBase MCStack)
endif (Boost_FOUND)

GENERATE_LIBRARY()

Add_Subdirectory(macros)

if (Boost_FOUND)
  Set(Exe_Names
    testDetectorSamplerInitBin
    testDetectorProcessorInitBin
    fileSinkInitBin 
    db_tut6worker
  )


 set(Exe_Source
    run/runTestDetectorSamplerBin.cxx
    run/runTestDetectorProcessorBin.cxx
    run/runFileSinkBin.cxx
    run/db_tut6worker.cxx		
    )

  list(LENGTH Exe_Names _length)
  math(EXPR _length ${_length}-1)

  foreach(_file RANGE 0 ${_length})
    list(GET Exe_Names ${_file} _name)
    list(GET Exe_Source ${_file} _src)
    set(EXE_NAME ${_name})
    set(SRCS ${_src})
    set(DEPENDENCIES FairDB ParBase FairDbMQ TutFairDbMQ)
    GENERATE_EXECUTABLE()
  endforeach(_file RANGE 0 ${_length})
endif (Boost_FOUND)
