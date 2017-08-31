################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(MbsTutorial
  SOURCES
  src/FairMBSUnpack.cxx
  src/FairMBSRawItem.cxx
  src/FairMBSTask.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src
  DEPENDENCIES Base MbsAPI
  LINKDEF MbsTutorialLinkDef.h
)

install(DIRECTORY data
  DESTINATION share/fairbase/examples/advanced/MbsTutorial
)

add_subdirectory(macros)
