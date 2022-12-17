################################################################################
# Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sample_data_2.lmd  ${CMAKE_CURRENT_BINARY_DIR}/sample_data_2.lmd COPYONLY)

set(target ExMbs)

set(sources
  FairMBSUnpack.cxx
  FairMBSRawItem.cxx
  FairMBSTask.cxx
)

fair_change_extensions_if_exists(.cxx .h FILES "${sources}" OUTVAR headers)

add_library(${target} SHARED ${sources} ${headers})
add_library(FairRoot::${target} ALIAS ${target})
set_target_properties(${target} PROPERTIES ${PROJECT_LIBRARY_PROPERTIES})

target_include_directories(${target} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  # TODO: DELETE ME ONCE USING root targets
  ${ROOT_INCLUDE_DIR}
)

target_link_libraries(${target} PUBLIC
  FairRoot::Online
  FairRoot::Tools # FairLogger

  ROOT::Core
)

fairroot_target_root_dictionary(${target}
  HEADERS ${headers}
  LINKDEF MbsTutorialLinkDef.h
  EXTRA_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR}
)

install(TARGETS ${target} LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR})
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES sample_data_2.lmd DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/advanced/MbsTutorial/data)
install(FILES unpack_mbs.C DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/advanced/MbsTutorial/macros)

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/unpack_mbs.C)

add_test(NAME ex_unpack_mbs
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/unpack_mbs.sh)
set_tests_properties(ex_unpack_mbs PROPERTIES
  TIMEOUT "30"
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)
