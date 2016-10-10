 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
# Create a library called "libFairXML" which includes the simplified parser to XML files
# The extension is already found.  Any number of sources could be listed here.

Set(INCLUDE_DIRECTORIES
 ${CMAKE_SOURCE_DIR}/fairtools
 ${CMAKE_SOURCE_DIR}/fairxml
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

# List of source files
set(SRCS
   FairXMLNode.cxx
   FairXMLAttrib.cxx
   FairXMLParser.cxx
)

Set(HEADERS )
Set(LINKDEF FairXMLLinkDef.h)
Set(LIBRARY_NAME FairXML)
Set(DEPENDENCIES Core RIO Net Rint XMLParser XMLIO)

GENERATE_LIBRARY()





