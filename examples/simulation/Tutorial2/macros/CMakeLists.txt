################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
set(tut2 "ex_sim_tutorial2")
set(root "source ${CMAKE_BINARY_DIR}/config.sh && root -b -q -l ${CMAKE_CURRENT_SOURCE_DIR}")

add_test(NAME ${tut2} COMMAND bash -c "${root}/run_tutorial2.C")

add_test(NAME ${tut2}_create_digis COMMAND bash -c "${root}/create_digis.C")
set_tests_properties(${tut2}_create_digis PROPERTIES DEPENDS ${tut2})

add_test(NAME ${tut2}_read_digis COMMAND bash -c "${root}/read_digis.C")
set_tests_properties(${tut2}_read_digis PROPERTIES DEPENDS ${tut2}_create_digis)

add_test(NAME ${tut2}_run_background COMMAND bash -c "${root}/run_background.C")
set_tests_properties(${tut2}_run_background PROPERTIES DEPENDS ${tut2}_read_digis)

add_test(NAME ${tut2}_run_signal1 COMMAND bash -c "${root}/run_signal.C\\(1,10\\)")
set_tests_properties(${tut2}_run_signal1 PROPERTIES DEPENDS ${tut2}_run_background)

add_test(NAME ${tut2}_run_signal2 COMMAND bash -c "${root}/run_signal.C\\(2,20\\)")
set_tests_properties(${tut2}_run_signal2 PROPERTIES DEPENDS ${tut2}_run_signal1)

add_test(NAME ${tut2}_create_digis_mixed COMMAND bash -c "${root}/create_digis_mixed.C")
set_tests_properties(${tut2}_create_digis_mixed PROPERTIES DEPENDS ${tut2}_run_signal2)

set_tests_properties(
  ${tut2}
  ${tut2}_create_digis
  ${tut2}_read_digis
  ${tut2}_run_background
  ${tut2}_run_signal1
  ${tut2}_run_signal2
  ${tut2}_create_digis_mixed

  PROPERTIES
  TIMEOUT 60
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

install(FILES
  create_digis_mixed.C
  create_digis.C
  read_digis.C
  run_background.C
  run_signal.C
  run_tutorial2.C
  DESTINATION ${PROJECT_INSTALL_DATADIR}/examples/simulation/Tutorial2
)
