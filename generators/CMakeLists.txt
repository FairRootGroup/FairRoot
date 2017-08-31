################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             # 
#              GNU Lesser General Public Licence (LGPL) version 3,             #  
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_fairroot_library(Gen
  SOURCES
  FairAsciiGenerator.cxx    
  FairBoxGenerator.cxx      
  FairIonGenerator.cxx      
  FairParticleGenerator.cxx 
  FairShieldGenerator.cxx
  FairUrqmdGenerator.cxx
  FairEvtGenGenerator.cxx

  INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDENCIES Base ROOT::EG ROOT::MathCore ROOT::Physics ROOT::RIO ROOT::Core
  LINKDEF GenLinkDef.h
)
