################################################################################
# Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

set(prefix ex_sim_tutorial2)

set(macrofiles
        compare_seed_value.C
        create_digis.C
        create_digis_mixed.C
        read_digis.C
        run_background.C
        run_signal.C
        run_tutorial2.C)

foreach(macro IN LISTS macrofiles)
    GENERATE_ROOT_TEST_SCRIPT(${CMAKE_CURRENT_SOURCE_DIR}/${macro})
endforeach()

# Try to compile the macros as normal files
add_library(${prefix}_check_compile OBJECT ${macrofiles})
target_link_libraries(${prefix}_check_compile PRIVATE
    FairRoot::ExSimulation2
    FairRoot::ExPassive
    FairRoot::Generators)

set(maxTestTime 60)

add_test(NAME ${prefix}
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_tutorial2.sh  10 \"TGeant4\" true 333)
set_tests_properties(${prefix} PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.${prefix}_sim
  RESOURCE_LOCK ${prefix}_paramFile
)

add_test(NAME ${prefix}_compare_seed_value
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/compare_seed_value.sh \"tutorial2_pions.params_p2.000_t0_n10.root\" 333)
set_tests_properties(${prefix}_compare_seed_value PROPERTIES
  TIMEOUT ${maxTestTime}
  FIXTURES_REQUIRED fixtures.${prefix}_sim
  RESOURCE_LOCK ${prefix}_paramFile
)

add_test(NAME ${prefix}_create_digis
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/create_digis.sh)
set_tests_properties(${prefix}_create_digis PROPERTIES
  FIXTURES_REQUIRED fixtures.${prefix}_sim
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.${prefix}_digi
  RESOURCE_LOCK ${prefix}_paramFile
)

add_test(NAME ${prefix}_read_digis
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/read_digis.sh)
set_tests_properties(${prefix}_read_digis PROPERTIES
  FIXTURES_REQUIRED fixtures.${prefix}_digi
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
)

add_test(NAME ${prefix}_run_background
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_background.sh)
set_tests_properties(${prefix}_run_background PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.${prefix}_back
)

add_test(NAME ${prefix}_run_signal1
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 1 10)
set_tests_properties(${prefix}_run_signal1 PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.${prefix}_sig1
)

add_test(NAME ${prefix}_run_signal2
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_signal.sh 2 20)
set_tests_properties(${prefix}_run_signal2 PROPERTIES
  TIMEOUT ${maxTestTime}
  PASS_REGULAR_EXPRESSION "Macro finished successfully"
  FIXTURES_SETUP fixtures.${prefix}_sig2
)

add_test(NAME ${prefix}_create_digis_mixed
         COMMAND ${CMAKE_CURRENT_BINARY_DIR}/create_digis_mixed.sh)
set_tests_properties(${prefix}_create_digis_mixed PROPERTIES
  FIXTURES_REQUIRED "fixtures.${prefix}_back;fixtures.${prefix}_sig1;fixtures.${prefix}_sig2"
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
