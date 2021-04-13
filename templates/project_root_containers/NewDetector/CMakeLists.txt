 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libNewDetector" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(INCLUDE_DIRECTORIES
${BASE_INCLUDE_DIRECTORIES}
#put here all directories where header files are located
${CMAKE_SOURCE_DIR}/MyProjData
${CMAKE_SOURCE_DIR}/NewDetector

)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${FAIRROOT_LIBRARY_DIR}

) 

link_directories( ${LINK_DIRECTORIES})

set(SRCS
#Put here your sourcefiles
NewDetector.cxx
NewDetectorContFact.cxx
NewDetectorGeo.cxx
NewDetectorGeoPar.cxx
NewDetectorPoint.cxx
)

Set(LINKDEF NewDetectorLinkDef.h)
Set(LIBRARY_NAME NewDetector)
Set(DEPENDENCIES
    MyProjData
    Base GeoBase ParBase
    FairLogger::FairLogger
    ${VMCLIB}
)

GENERATE_LIBRARY()
