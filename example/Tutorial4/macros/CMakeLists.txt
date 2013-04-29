GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial4/macros/run_tutorial4.C)
add_test(run_tutorial4 ${CMAKE_BINARY_DIR}/example/Tutorial4/macros/run_tutorial4.sh)
SET_TESTS_PROPERTIES(run_tutorial4 PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_tutorial4 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial4/macros/run_reco.C)
add_test(run_reco_tut4 ${CMAKE_BINARY_DIR}/example/Tutorial4/macros/run_reco.sh)
SET_TESTS_PROPERTIES(run_reco_tut4 PROPERTIES DEPENDS run_tutorial4)
SET_TESTS_PROPERTIES(run_reco_tut4 PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_reco_tut4 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

