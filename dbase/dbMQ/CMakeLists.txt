 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Date: 13.08.14 D.Bertini
# Create a library called "libFairDbMQ" 
#
# All SQL drivers "includes" and "libraries" are not imeediately set 
# because of the problem i have with CMAKE and variable set to not-found
# Instead  those are added only if they have been previously set  


set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${ROOT_INCLUDE_DIR}
${ZMQ_INCLUDE_DIR}
${CMAKE_SOURCE_DIR}/parbase/dbIO
${CMAKE_SOURCE_DIR}/fairmq
${CMAKE_SOURCE_DIR}/base/MQ
${CMAKE_SOURCE_DIR}/dbase/dbMQ/utils
${CMAKE_SOURCE_DIR}/dbase/dbMQ/procs
${CMAKE_SOURCE_DIR}/dbase/dbMQ/actors
)

include_directories(${INCLUDE_DIRECTORIES})

#if (Boost_FOUND)
#  configure_file( ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/run_sps_init.sh.in ${CMAKE_BINARY_DIR}/bin/run_sps_init.sh )
#  file(COPY  ${CMAKE_SOURCE_DIR}/example/Tutorial6/macros/dbconfig.sh DESTINATION ${CMAKE_BINARY_DIR}/bin/ )
#endIf (Boost_FOUND)

set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
    ${Boost_LIBRARY_DIRS}
) 

link_directories(${LINK_DIRECTORIES})

set(SRCS
  utils/FairDbMQ.cxx
  utils/FairDbMQError.cxx
  actors/FairDbMQWorker.cxx
  actors/FairDbMQDispatcher.cxx
  actors/FairDbMQClient.cxx
  actors/FairDbMQParMgr.cxx
)

#set(LINKDEF  )
set(LIBRARY_NAME FairDbMQ)

if (Boost_FOUND)
  set(DEPENDENCIES
    Base FairDB ParBase FairMQ boost_thread boost_system boost_serialization)
else (Boost_FOUND)
  set(DEPENDENCIES Base  FairDB ParBase)
endif (Boost_FOUND)

GENERATE_LIBRARY()

if (Boost_FOUND)
  set(Exe_Names
    db_dispatcher
    db_client 
    db_worker
  )


  set(Exe_Source
    procs/db_dispatcher.cxx		
    procs/db_client.cxx
    procs/db_worker.cxx
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
