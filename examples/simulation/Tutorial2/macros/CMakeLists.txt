################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/create_digis_mixed.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/create_digis.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/read_digis.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_background.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_signal.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/run_tutorial2.C)
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/compare_seed_value.C)

set(maxTestTime 60)

add_test(NAME ex_sim_tutorial2
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial2.sh  10 \"TGeant4\" true 333)
set_tests_properties(ex_sim_tutorial2 PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_sim_tutorial2_sim
  RESOURCE_LOCK ex_sim_tutorial2_paramFile
)

add_test(NAME ex_sim_tutorial2_compare_seed_value
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/compare_seed_value.sh \"tutorial2_pions.params_p2.000_t0_n10.root\" 333)
set_tests_properties(ex_sim_tutorial2_compare_seed_value PROPERTIES
  TIMEOUT ${maxTestTime}
  FIXTURES_REQUIRED fixtures.ex_sim_tutorial2_sim
  RESOURCE_LOCK ex_sim_tutorial2_paramFile
)

add_test(NAME ex_sim_tutorial2_create_digis
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/create_digis.sh)
set_tests_properties(ex_sim_tutorial2_create_digis PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_sim_tutorial2_sim
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_sim_tutorial2_digi
  RESOURCE_LOCK ex_sim_tutorial2_paramFile
)

add_test(NAME ex_sim_tutorial2_read_digis
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/read_digis.sh)
set_tests_properties(ex_sim_tutorial2_read_digis PROPERTIES
  FIXTURES_REQUIRED fixtures.ex_sim_tutorial2_digi
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

add_test(NAME ex_sim_tutorial2_run_background
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_background.sh)
set_tests_properties(ex_sim_tutorial2_run_background PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_sim_tutorial2_back
)

add_test(NAME ex_sim_tutorial2_run_signal1
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 1 10)
set_tests_properties(ex_sim_tutorial2_run_signal1 PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_sim_tutorial2_sig1
)

add_test(NAME ex_sim_tutorial2_run_signal2
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 2 20)
set_tests_properties(ex_sim_tutorial2_run_signal2 PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.ex_sim_tutorial2_sig2
)

add_test(NAME ex_sim_tutorial2_create_digis_mixed
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/create_digis_mixed.sh)
set_tests_properties(ex_sim_tutorial2_create_digis_mixed PROPERTIES
  FIXTURES_REQUIRED "fixtures.ex_sim_tutorial2_back;fixtures.ex_sim_tutorial2_sig1;fixtures.ex_sim_tutorial2_sig2"
  TIMEOUT ${maxTestTime}
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
