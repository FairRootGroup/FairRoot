################################################################################
# Copyright (C) 2014-2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
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

set(MaxTestTime 60)

add_test(tutorial2 ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial2.sh)
set_tests_properties(tutorial2 PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_create_digis ${CMAKE_CURRENT_BINARY_DIR}/create_digis.sh)
set_tests_properties(tutorial2_create_digis PROPERTIES DEPENDS tutorial2)
set_tests_properties(tutorial2_create_digis PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_create_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_read_digis ${CMAKE_CURRENT_BINARY_DIR}/read_digis.sh)
set_tests_properties(tutorial2_read_digis PROPERTIES DEPENDS tutorial2_create_digis)
set_tests_properties(tutorial2_read_digis PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_read_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_run_background ${CMAKE_CURRENT_BINARY_DIR}/run_background.sh)
set_tests_properties(tutorial2_run_background PROPERTIES DEPENDS tutorial2_read_digis)
set_tests_properties(tutorial2_run_background PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_run_background PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_run_signal1 ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 1 10)
set_tests_properties(tutorial2_run_signal1 PROPERTIES DEPENDS tutorial2_run_background)
set_tests_properties(tutorial2_run_signal1 PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_run_signal1 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_run_signal2 ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 2 20)
set_tests_properties(tutorial2_run_signal2 PROPERTIES DEPENDS tutorial2_run_signal1)
set_tests_properties(tutorial2_run_signal2 PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_run_signal2 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

add_test(tutorial2_create_digis_mixed ${CMAKE_CURRENT_BINARY_DIR}/create_digis_mixed.sh)
set_tests_properties(tutorial2_create_digis_mixed PROPERTIES DEPENDS tutorial2_run_signal2)
set_tests_properties(tutorial2_create_digis_mixed PROPERTIES TIMEOUT ${MaxTestTime})
set_tests_properties(tutorial2_create_digis_mixed PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

install(FILES
  create_digis_mixed.C
  create_digis.C
  read_digis.C
  run_background.C
  run_signal.C
  run_tutorial2.C
  DESTINATION share/fairbase/examples/simulation/Tutorial2
)
