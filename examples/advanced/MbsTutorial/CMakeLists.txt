 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libMbsTutorial" 

set(INCLUDE_DIRECTORIES
    ${BASE_INCLUDE_DIRECTORIES}
    ${CMAKE_SOURCE_DIR}/base/source
    ${CMAKE_SOURCE_DIR}/examples/advanced/MbsTutorial
    ${CMAKE_SOURCE_DIR}/examples/advanced/MbsTutorial/src
)

Set(SYSTEM_INCLUDE_DIRECTORIES
    ${SYSTEM_INCLUDE_DIRECTORIES}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})


set(LINK_DIRECTORIES
    ${ROOT_LIBRARY_DIR}
) 

link_directories(${LINK_DIRECTORIES})

Set(SRCS
    src/FairTut8Unpack.cxx
    src/FairTut8RawItem.cxx
    src/FairTut8Task.cxx
)

CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF MbsTutorialLinkDef.h)
Set(LIBRARY_NAME MbsTutorial)

Set(DEPENDENCIES
    Base MbsAPI
)

GENERATE_LIBRARY()

add_subdirectory(macros)

