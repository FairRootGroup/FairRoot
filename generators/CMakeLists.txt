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

EXEC_PROGRAM( gcc ARGS "-dumpversion" OUTPUT_VARIABLE GCC_VERSION )
STRING(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]" "\\1" req_gcc_major_vers "${GCC_VERSION}")
STRING(REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]" "\\1" req_gcc_minor_vers "${GCC_VERSION}")
IF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")
ENDIF(${req_gcc_major_vers} MATCHES "4" AND NOT ${req_gcc_minor_vers} MATCHES "0")



Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/geobase 
  ${CMAKE_SOURCE_DIR}/field 
  ${CMAKE_SOURCE_DIR}/base 
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/base/sink
  ${CMAKE_SOURCE_DIR}/base/source
  ${CMAKE_SOURCE_DIR}/generators
  ${CMAKE_SOURCE_DIR}/alignment
)

Set(SYSTEM_INCLUDE_DIRECTORIES
  ${ROOT_INCLUDE_DIR}
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})

Set(SRCS
  FairAsciiGenerator.cxx    
  FairBoxGenerator.cxx      
  FairIonGenerator.cxx      
  FairParticleGenerator.cxx 
  FairShieldGenerator.cxx
  FairUrqmdGenerator.cxx
  FairEvtGenGenerator.cxx
)

Set(HEADERS )
Set(LINKDEF GenLinkDef.h)
Set(LIBRARY_NAME Gen)
Set(DEPENDENCIES Base EG MathCore Physics RIO Core)

GENERATE_LIBRARY()
