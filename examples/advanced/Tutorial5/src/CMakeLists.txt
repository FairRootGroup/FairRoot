 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "FairDbTut" 

Set(INCLUDE_DIRECTORIES
  ${BASE_INCLUDE_DIRECTORIES}
  ${CMAKE_SOURCE_DIR}/examples/advanced/Tutorial5/src
  ${CMAKE_SOURCE_DIR}/examples/common/mcstack
)

Include_Directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

Set(LINK_DIRECTORIES
  ${ROOT_LIBRARY_DIR}
)
 
Link_Directories(${LINK_DIRECTORIES})

set(SRCS
FairDbTutPar.cxx
FairDbTutParBin.cxx
FairDbTutContFact.cxx
FairDbTutAccessRtdbTask.cxx
)

set(HEADERS
FairDbTutPar.h
FairDbTutParBin.h
FairDbTutContFact.h
FairDbTutAccessRtdbTask.h
${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbReader.h
${CMAKE_SOURCE_DIR}/dbase/dbInterface/FairDbWriter.h
)



set(LINKDEF FairDbTutLinkDef.h)
Set(LIBRARY_NAME Tutorial5)
Set(DEPENDENCIES Base ParBase FairDB)

GENERATE_LIBRARY()



