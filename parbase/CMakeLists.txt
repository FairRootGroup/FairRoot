################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(ParBase
  SOURCES
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

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES FairTools ROOT::RIO ROOT::Core
  LINKDEF ParBaseLinkDef.h
)
