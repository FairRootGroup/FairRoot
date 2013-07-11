GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_sim.C)
add_test(run_sim ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_sim.sh)
SET_TESTS_PROPERTIES(run_sim PROPERTIES TIMEOUT "180")
SET_TESTS_PROPERTIES(run_sim PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_digi.C)
add_test(run_digi ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_digi.sh)
SET_TESTS_PROPERTIES(run_digi PROPERTIES DEPENDS run_sim)
SET_TESTS_PROPERTIES(run_digi PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_digi PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_reco.C)
add_test(run_reco ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_reco.sh)
SET_TESTS_PROPERTIES(run_reco PROPERTIES DEPENDS run_digi)
SET_TESTS_PROPERTIES(run_reco PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_reco PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_digi_timebased.C)
add_test(run_digi_timebased ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_digi_timebased.sh)
SET_TESTS_PROPERTIES(run_digi_timebased PROPERTIES DEPENDS run_sim)
SET_TESTS_PROPERTIES(run_digi_timebased PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_digi_timebased PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial3/macro/run_reco_timebased.C)
add_test(run_reco_timebased ${CMAKE_BINARY_DIR}/example/Tutorial3/macro/run_reco_timebased.sh)
SET_TESTS_PROPERTIES(run_reco_timebased PROPERTIES DEPENDS run_digi_timebased)
SET_TESTS_PROPERTIES(run_reco_timebased PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_reco_timebased PROPERTIES PASS_REGULAR_EXPRESSION "Test passed;All ok")

Install(FILES run_sim.C run_digi.C run_reco.C eventDisplay.C
              run_digi_timebased.C run_reco_timebased.C
        DESTINATION share/fairbase/example/Tutorial3
       )

