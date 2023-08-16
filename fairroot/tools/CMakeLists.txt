################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(target Tools)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/FairVersion.h.in ${CMAKE_BINARY_DIR}/FairVersion.h @ONLY)
list(APPEND extra_headers
     ${CMAKE_BINARY_DIR}/FairVersion.h)

set(sources
  FairLogger.cxx
  FairMonitor.cxx
  FairSystemInfo.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

list(APPEND headers
  FairMemory.h
)

add_library(${target} SHARED ${sources} ${headers})
fairroot_library_settings(${target})
# Keep old filesystem name
set_target_properties(${target} PROPERTIES OUTPUT_NAME FairTools)

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${target}
  PUBLIC
  FairLogger::FairLogger
  ROOT::Core

  PRIVATE
  ROOT::Graf
  ROOT::Hist
  ROOT::Gpad
  ROOT::RIO
  ROOT::MathCore
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF LinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

fairroot_install_exported(TARGETS ${target})
install(FILES ${headers} ${extra_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
