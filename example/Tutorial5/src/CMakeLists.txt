 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "FairDbTut" 

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
${CMAKE_SOURCE_DIR}/example/Tutorial5/src
${CMAKE_SOURCE_DIR}/example/mcstack
)

include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
)
 
link_directories( ${LINK_DIRECTORIES})

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
Set(DEPENDENCIES Base)

GENERATE_LIBRARY()



