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

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/fairmq/tools
  ${CMAKE_SOURCE_DIR}/base/MQ
  ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
  ${CMAKE_SOURCE_DIR}/base/MQ/devices
  ${CMAKE_SOURCE_DIR}/base/MQ/tasks
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/data
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/simulation
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/digitization
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/reconstruction
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/timeBasedSimulation
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/samplerTask
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/processorTask
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/fileSink
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/data
  ${CMAKE_CURRENT_BINARY_DIR}
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${SYSTEM_INCLUDE_DIRECTORIES}
  ${ZMQ_INCLUDE_DIR}
)

If(PROTOBUF_FOUND)
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${PROTOBUF_INCLUDE_DIR}
  )
EndIf(PROTOBUF_FOUND)

If(MSGPACK_FOUND)
  add_definitions(-DMSGPACK)
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${MSGPACK_INCLUDE_DIR}
  )
EndIf(MSGPACK_FOUND)

If(FLATBUFFERS_FOUND)
  add_definitions(-DFLATBUFFERS)
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${FLATBUFFERS_INCLUDE_DIR}
  )
EndIf(FLATBUFFERS_FOUND)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

If (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run/startThree.sh.in          ${CMAKE_BINARY_DIR}/bin/startThree.sh)
  configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run/startAll.sh.in            ${CMAKE_BINARY_DIR}/bin/startAll.sh)
  configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run/startAllProxy.sh.in       ${CMAKE_BINARY_DIR}/bin/startAllProxy.sh)
  configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run/startPushPull.sh.in       ${CMAKE_BINARY_DIR}/bin/startPushPull.sh)
  configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/run/startExtraProcessor.sh.in ${CMAKE_BINARY_DIR}/bin/startExtraProcessor.sh)
EndIf (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
  ${Boost_LIBRARY_DIRS}
)

If(MSGPACK_FOUND)
  Set(LINK_DIRECTORIES
    ${LINK_DIRECTORIES}
    ${MSGPACK_LIBRARY_DIR}
  )
EndIf(MSGPACK_FOUND)

Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
  simulation/FairTestDetector.cxx
  simulation/FairTestDetectorContFact.cxx
  simulation/FairTestDetectorGeo.cxx
  simulation/FairTestDetectorGeoPar.cxx
  simulation/FairConstField.cxx
  simulation/FairConstPar.cxx
  simulation/FairMapPar.cxx

  data/FairTestDetectorPoint.cxx
  data/FairTestDetectorHit.cxx
  digitization/FairTestDetectorHitProducerSmearing.cxx
  digitization/FairTestDetectorDigiTask.cxx
  reconstruction/FairTestDetectorRecoTask.cxx
  timeBasedSimulation/FairTestDetectorDigiRingSorter.cxx
  timeBasedSimulation/FairTestDetectorDigiSorterTask.cxx
  timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.cxx
  timeBasedSimulation/FairTestDetectorTimeDigiTask.cxx
  timeBasedSimulation/FairTestDetectorTimeRecoTask.cxx
)

If (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  Set(SRCS
    ${SRCS}
    data/FairTestDetectorDigi.cxx
  )

  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.h
      ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc
    COMMAND
      ${SIMPATH}/bin/protoc -I=. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayload.proto
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/data
    )

  If(FLATBUFFERS_FOUND)
    add_custom_command(
      OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h
      COMMAND
        ${FLATBUFFERS_BINARY_DIR}/flatc -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadDigi.fbs
      WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/data
      )
    add_custom_command(
      OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h
      COMMAND
        ${FLATBUFFERS_BINARY_DIR}/flatc -c -o ${CMAKE_CURRENT_BINARY_DIR} FairTestDetectorPayloadHit.fbs
      WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial3/MQ/data
      )
  EndIf(FLATBUFFERS_FOUND)

  Set(NO_DICT_SRCS
    ${NO_DICT_SRCS}
    ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayload.pb.cc
  )

  If(FLATBUFFERS_FOUND)
    Set(NO_DICT_SRCS
      ${NO_DICT_SRCS}
      ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadDigi_generated.h
      ${CMAKE_CURRENT_BINARY_DIR}/FairTestDetectorPayloadHit_generated.h
    )
  EndIf(FLATBUFFERS_FOUND)
EndIf (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)

Set(LINKDEF FairTestDetectorLinkDef.h)
Set(LIBRARY_NAME FairTestDetector)

If (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  Set(DEPENDENCIES
    Base MCStack FairMQ BaseMQ boost_thread boost_system boost_serialization boost_program_options)
  If(PROTOBUF_FOUND)
    Set(DEPENDENCIES
      ${DEPENDENCIES}
      ${PROTOBUF_LIBRARY}
    )
  Endif(PROTOBUF_FOUND)
Else (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  Set(DEPENDENCIES
    Base
    MCStack
  )
EndIf (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)

if(MSGPACK_FOUND)
  Set(DEPENDENCIES
    ${DEPENDENCIES}
    msgpackc
  )
endif(MSGPACK_FOUND)

GENERATE_LIBRARY()

Add_Subdirectory(macro)

If (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
  Set(Exe_Names
    testDetectorSampler
    testDetectorProcessor
    testDetectorFileSink
  )

  set(Exe_Source
    MQ/run/runTestDetectorSampler.cxx
    MQ/run/runTestDetectorProcessor.cxx
    MQ/run/runTestDetectorFileSink.cxx
    )

  List(LENGTH Exe_Names _length)
  Math(EXPR _length ${_length}-1)

  ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES FairTestDetector)
    GENERATE_EXECUTABLE()
  EndForEach(_file RANGE 0 ${_length})
EndIf (Boost_FOUND AND POS_C++11 AND ZMQ_FOUND)
