GENERATE_ROOT_TEST_SCRIPT(${FAIRROOT_SOURCE_DIR}/example/Tutorial1/macros/run_tutorial1.C)
add_test(run_tutorial1 ${FAIRROOT_BINARY_DIR}/example/Tutorial1/macros/run_tutorial1.sh)
SET_TESTS_PROPERTIES(run_tutorial1 PROPERTIES TIMEOUT "100")
SET_TESTS_PROPERTIES(run_tutorial1 PROPERTIES PASS_REGULAR_EXPRESSION "TestPassed;All ok")
