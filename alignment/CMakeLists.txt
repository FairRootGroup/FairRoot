 ################################################################################
 # Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

set(target Alignment)

set(sources
  FairAlignmentHandler.cxx
)

set(headers
  FairAlignmentHandler.h
)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE US ONCE MODERNIZED TARGETS
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/fairtools>
  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_directories(${target} PUBLIC
  ${ROOT_LIBRARY_DIR}
)

target_link_libraries(${target} PUBLIC
  FairLogger::FairLogger
  # TODO: clean the following
  Geom
  Matrix
)

install(TARGETS ${target}
  LIBRARY DESTINATION lib
  # TODO: change to?:
  # LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
)

install(FILES ${headers}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
