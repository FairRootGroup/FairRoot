 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libParbase" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/fairtools
  ${CMAKE_SOURCE_DIR}/base
  ${CMAKE_SOURCE_DIR}/base/steer
  ${CMAKE_SOURCE_DIR}/base/event
  ${CMAKE_SOURCE_DIR}/base/field
  ${CMAKE_SOURCE_DIR}/base/sim
  ${CMAKE_SOURCE_DIR}/geobase
  ${CMAKE_SOURCE_DIR}/parbase
  ${CMAKE_SOURCE_DIR}/parbase/dbIO
  ${CMAKE_SOURCE_DIR}/dbase/
  ${CMAKE_SOURCE_DIR}/dbase/dbInterface
  ${CMAKE_SOURCE_DIR}/dbase/dbValidation
  ${CMAKE_SOURCE_DIR}/input/db
  ${CMAKE_SOURCE_DIR}/dbase/dbInput
  ${CMAKE_SOURCE_DIR}/dbase/dbUtils
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

set(SRCS
FairContFact.cxx       
FairDetParAsciiFileIo.cxx    
FairDetParIo.cxx         
FairDetParRootFileIo.cxx     
FairGenericParAsciiFileIo.cxx     
FairGenericParRootFileIo.cxx     
FairParAsciiFileIo.cxx   
FairParGenericSet.cxx   
FairParIo.cxx  
FairParRootFileIo.cxx 
FairParSet.cxx 
FairParamList.cxx  
FairRtdbRun.cxx  
FairRuntimeDb.cxx
###### Fair DB IO #######
dbIO/FairParTSQLIo.cxx
dbIO/FairDetParTSQLIo.cxx
dbIO/FairGenericParTSQLIo.cxx
)

Set(HEADERS )
Set(LINKDEF ParBaseLinkDef.h)
Set(LIBRARY_NAME ParBase)
Set(DEPENDENCIES FairTools FairDB RIO Cint Core )

GENERATE_LIBRARY()

