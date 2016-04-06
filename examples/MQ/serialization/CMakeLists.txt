 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libGenericMQTuto" 

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/fairmq
    ${CMAKE_SOURCE_DIR}/fairmq/devices
    ${CMAKE_SOURCE_DIR}/fairmq/options
    ${CMAKE_SOURCE_DIR}/fairmq/tools
    ${CMAKE_SOURCE_DIR}/fairmq/nanomsg
    ${CMAKE_SOURCE_DIR}/fairmq/zeromq
    ${CMAKE_SOURCE_DIR}/base/MQ
    ${CMAKE_SOURCE_DIR}/base/MQ/devices
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Sampler
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Serialization
    ${CMAKE_SOURCE_DIR}/base/MQ/policies/Storage
    ${CMAKE_SOURCE_DIR}/base/MQ/baseMQtools
    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization
    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_generator
    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_struct
    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/1-simple/devices
    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/2-multi-part/devices
#    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/2-multi-part/policy
#    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/2-multi-part/policy/serialization
#    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/2-multi-part/policy/task
#    ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/src/2-multi-part/helper_functions
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${ZMQ_INCLUDE_DIR}
)



If(PROTOBUF_FOUND)
   set(INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_BINARY_DIR}
    ${INCLUDE_DIRECTORIES}
  )
  Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
    ${PROTOBUF_INCLUDE_DIR}
  )
EndIf(PROTOBUF_FOUND)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(SCRIPT_ARGS "\${\@:2}")

# Data generator
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_generator/startGenericMQTutoGenerateData.sh.in ${CMAKE_BINARY_DIR}/bin/startSerializationGenerateData.sh )

# start MQ chains
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startGenEx2All.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2All.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startGenEx1All.sh.in ${CMAKE_BINARY_DIR}/bin/startSerializationEx1.sh )
configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startSerializationEx2.sh.in ${CMAKE_BINARY_DIR}/bin/startSerializationEx2.sh )

# start individual devices 
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startGenEx2Sampler.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2Sampler.sh )
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startGenEx2Processor.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2Processor.sh )
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/scripts/startGenEx2Sink.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2Sink.sh )


# config file 
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/options/ConfigGenEx2.cfg.in ${CMAKE_BINARY_DIR}/bin/config/ConfigGenEx2.cfg )

# scripts for CTest
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/test/startGenEx2TestBin.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2TestBin.sh )
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/test/startGenEx2TestBoost.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2TestBoost.sh )
#configure_file( ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/test/startGenEx2TestRoot.sh.in ${CMAKE_BINARY_DIR}/bin/startGenEx2TestRoot.sh )

# Create a default directory that will hold root input/output data file
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_io)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
)

if(DDS_PATH)
  set(LINK_DIRECTORIES
    ${LINK_DIRECTORIES}
    ${DDS_PATH}/lib
  )
endif(DDS_PATH)

link_directories(${LINK_DIRECTORIES})

If(PROTOBUF_FOUND)
    add_custom_command(
        OUTPUT
          ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.h
          ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.cc
        COMMAND
          ${SIMPATH}/bin/protoc -I=. --cpp_out=${CMAKE_CURRENT_BINARY_DIR} Tuto7Payload.proto
        WORKING_DIRECTORY
          ${CMAKE_SOURCE_DIR}/examples/MQ/serialization/data_struct
        )

Set(NO_DICT_SRCS
    ${NO_DICT_SRCS}
    ${CMAKE_CURRENT_BINARY_DIR}/Tuto7Payload.pb.cc
  )
EndIf(PROTOBUF_FOUND)

Set(SRCS
    data_struct/MyDigi.cxx
    data_struct/MyHit.cxx
    data_struct/MyPodData.cxx
)


Set(LINKDEF GenericMQTutoLinkDef.h)
Set(LIBRARY_NAME GenericMQTuto)

Set(DEPENDENCIES
    Base 
    FairMQ 
    BaseMQ 
    boost_thread 
    boost_system 
    boost_serialization 
    boost_program_options
    Minuit
    XMLIO
    MathMore
    gsl
    gslcblas
)

If(PROTOBUF_FOUND)
    Set(DEPENDENCIES
      ${DEPENDENCIES}
      ${PROTOBUF_LIBRARY}
    )
Endif(PROTOBUF_FOUND)

GENERATE_LIBRARY()


Set(Exe_Names
    #genExSplitter
    #genExMerger
    
    #genericMQTutoFairTestDetectorSampler
    #genericMQTutoFairTestDetectorProcessor
    #genericMQTutoFairTestDetectorFileSink

    genEx1Sampler
    genEx1Processor
    genEx1Sink

    serialization-Ex2Sampler
    serialization-Ex2Processor
    serialization-Ex2Sink
    #genEx2Sampler
    #genEx2Processor
    #genEx2Sink

    #genericMQTutoSamplerTest
    #genericMQTutoProcessorTest
    #genericMQTutoSinkTest
)

set(Exe_Source
    #src/2-multi-part/run/runSplitterT7.cxx
    #src/2-multi-part/run/runMergerT7.cxx

    #run/FairTestDetector/runSamplerT7b.cxx
    #run/FairTestDetector/runProcessorT7b.cxx
    #run/FairTestDetector/runFileSinkT7b.cxx

    src/1-simple/run/runSamplerGenEx1.cxx
    src/1-simple/run/runProcessorGenEx1.cxx
    src/1-simple/run/runSinkGenEx1.cxx

    src/2-multi-part/run/runSamplerEx2.cxx
    src/2-multi-part/run/runProcessorEx2.cxx
    src/2-multi-part/run/runSinkEx2.cxx
    
    #part2/run/runSamplerT7.cxx
    #part2/run/runProcessorT7.cxx
    #part2/run/runFileSinkT7.cxx

    #test/runSamplerT7Test.cxx
    #test/runProcessorT7Test.cxx
    #test/runFileSinkT7Test.cxx
)

############################################################
# Check if we run on Ubuntu version>=11 and if it is the case
# add --no-as-needed flag to the linker.
# it is needed on Ubuntu xx>=11 to load Ttree in executables
# see : https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=14064
# Alternative is to instantiate a TApplication or load manually with gSystem->Load("libTree.so") in main file
set(UBUNTU_GREATERTHAN_v11_LINKER_FLAG )

if(NOT CMAKE_SYSTEM_NAME MATCHES Darwin)
    # use the LSB stuff if possible 
    EXECUTE_PROCESS(
       COMMAND cat /etc/lsb-release
       COMMAND grep DISTRIB_ID
       COMMAND awk -F= "{ print $2 }"
       COMMAND tr "\n" " "
       COMMAND sed "s/ //"
       OUTPUT_VARIABLE LSB_ID
       RESULT_VARIABLE LSB_ID_RESULT
    )
    EXECUTE_PROCESS(
       COMMAND cat /etc/lsb-release
       COMMAND grep DISTRIB_RELEASE
       COMMAND awk -F= "{ print $2 }"
       COMMAND tr "\n" " "
       COMMAND sed "s/ //"
       OUTPUT_VARIABLE LSB_VER
       RESULT_VARIABLE LSB_VER_RESULT
    )
    
    #message("LSB output: ${LSB_ID_RESULT}:${LSB_ID} ${LSB_VER_RESULT}:${LSB_VER}")
    if(NOT ${LSB_ID} STREQUAL "")
        # found some, use it :D
        set(INSTALLER_PLATFORM "${LSB_ID}-${LSB_VER}" CACHE PATH "Installer chosen platform")
        if(${LSB_ID} STREQUAL "Ubuntu" AND ${LSB_VER} VERSION_GREATER "10.0")
            #message(STATUS "Running on ${INSTALLER_PLATFORM} which is more recent than Ubuntu 11.0")
            #message(STATUS "--no-as-needed flag is added to the linker of GenericMQTuto executables")
            set(UBUNTU_GREATERTHAN_v11_LINKER_FLAG "-Wl,--no-as-needed")
        endif()
    else(NOT ${LSB_ID} STREQUAL "")
       set(INSTALLER_PLATFORM "linux-generic" CACHE PATH "Installer chosen platform")
    endif(NOT ${LSB_ID} STREQUAL "")
endif(NOT CMAKE_SYSTEM_NAME MATCHES Darwin)
############################################################



List(LENGTH Exe_Names _length)
Math(EXPR _length ${_length}-1)

ForEach(_file RANGE 0 ${_length})
    List(GET Exe_Names ${_file} _name)
    List(GET Exe_Source ${_file} _src)
    Set(EXE_NAME ${_name})
    Set(SRCS ${_src})
    Set(DEPENDENCIES GenericMQTuto ${UBUNTU_GREATERTHAN_v11_LINKER_FLAG})
    GENERATE_EXECUTABLE()
EndForEach(_file RANGE 0 ${_length})



Set(EXE_NAME genericMQTutoGenerateData)
Set(SRCS data_generator/runGenerateData.cxx)
Set(DEPENDENCIES GenericMQTuto RooFitCore RooFit Foam )
GENERATE_EXECUTABLE()




#add_test(NAME run_GenericMQ_Tuto_Bin_Test_ALL COMMAND ${CMAKE_BINARY_DIR}/bin/startGenEx2TestBin.sh)
#set_tests_properties(run_GenericMQ_Tuto_Bin_Test_ALL PROPERTIES TIMEOUT "30")
#set_tests_properties(run_GenericMQ_Tuto_Bin_Test_ALL PROPERTIES 
#    PASS_REGULAR_EXPRESSION "Data generation successful"
#    PASS_REGULAR_EXPRESSION "Sent 100 messages!" 
#    PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
#    PASS_REGULAR_EXPRESSION "Received 100 messages!"
#    )

#add_test(NAME run_GenericMQ_Tuto_Boost_Test_ALL COMMAND ${CMAKE_BINARY_DIR}/bin/startGenEx2TestBoost.sh)
#set_tests_properties(run_GenericMQ_Tuto_Boost_Test_ALL PROPERTIES TIMEOUT "30")
#set_tests_properties(run_GenericMQ_Tuto_Boost_Test_ALL PROPERTIES 
#    PASS_REGULAR_EXPRESSION "Data generation successful"
#    PASS_REGULAR_EXPRESSION "Sent 100 messages!" 
#    PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
#    PASS_REGULAR_EXPRESSION "Received 100 messages!"
#    )
#set_tests_properties(run_GenericMQ_Tuto_Boost_Test_ALL PROPERTIES 
#    DEPENDS run_GenericMQ_Tuto_Bin_Test_ALL
#    )

#add_test(NAME run_GenericMQ_Tuto_Root_Test_ALL COMMAND ${CMAKE_BINARY_DIR}/bin/startGenEx2TestRoot.sh)
#set_tests_properties(run_GenericMQ_Tuto_Root_Test_ALL PROPERTIES TIMEOUT "30")
#set_tests_properties(run_GenericMQ_Tuto_Root_Test_ALL PROPERTIES 
#    PASS_REGULAR_EXPRESSION "Data generation successful"
#    PASS_REGULAR_EXPRESSION "Sent 100 messages!" 
#    PASS_REGULAR_EXPRESSION "Received 100 and sent 100 messages!"
#    PASS_REGULAR_EXPRESSION "Received 100 messages!"
#    )
#set_tests_properties(run_GenericMQ_Tuto_Root_Test_ALL PROPERTIES 
#    DEPENDS run_GenericMQ_Tuto_Boost_Test_ALL
#    )


