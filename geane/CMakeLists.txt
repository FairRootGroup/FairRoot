 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libBase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${CMAKE_SOURCE_DIR}/fairtools
${CMAKE_SOURCE_DIR}/geobase 
${CMAKE_SOURCE_DIR}/parbase 
${CMAKE_SOURCE_DIR}/base 
${CMAKE_SOURCE_DIR}/base/steer
${CMAKE_SOURCE_DIR}/base/event
${CMAKE_SOURCE_DIR}/base/field
${CMAKE_SOURCE_DIR}/base/sim
${CMAKE_SOURCE_DIR}/trackbase
${CMAKE_SOURCE_DIR}/base/source
${CMAKE_SOURCE_DIR}/base/sink
${CMAKE_SOURCE_DIR}/geane
${CMAKE_SOURCE_DIR}/alignment
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR} 
  ${GEANT3_INCLUDE_DIR}
  ${Geant3_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})


Set(SRCS
  FairGeane.cxx       
  FairGeanePro.cxx
)

Set(HEADERS )
Set(LINKDEF GeaneLinkDef.h)
Set(LIBRARY_NAME Geane)
Set(DEPENDENCIES Base TrkBase VMC)

GENERATE_LIBRARY()
