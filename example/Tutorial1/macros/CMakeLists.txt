GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial1/macros/run_tutorial1.C)
add_test(run_tutorial1 ${CMAKE_BINARY_DIR}/example/Tutorial1/macros/run_tutorial1.sh)
SET_TESTS_PROPERTIES(run_tutorial1 PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_tutorial1 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

Install(FILES run_tutorial1.C
        DESTINATION share/fairbase/example/Tutorial1
       )


