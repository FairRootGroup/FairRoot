################################################################################
#    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

# @author Sandro Wenzel

set(target MCStepLogger)

set(sources
  MCStepInterceptor.cxx
  MCStepLoggerImpl.cxx
)

add_library(${target} SHARED ${sources})
fairroot_library_settings(${target})

target_link_libraries(${target} PUBLIC
  FairRoot::Base

  ROOT::Core
  ROOT::Tree
  ROOT::Hist
  ROOT::RIO
  ${VMCLIB}

  ${CMAKE_DL_LIBS}
)

fairroot_install_exported(TARGETS ${target})
