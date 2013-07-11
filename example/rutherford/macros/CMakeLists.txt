GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/rutherford/macros/run_rutherford.C)
add_test(run_rutherford ${CMAKE_BINARY_DIR}/example/rutherford/macros/run_rutherford.sh)
SET_TESTS_PROPERTIES(run_rutherford PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_rutherford PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/rutherford/macros/run_rad.C)
add_test(run_rad ${CMAKE_BINARY_DIR}/example/rutherford/macros/run_rad.sh)
SET_TESTS_PROPERTIES(run_rad PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_rad PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

Install(FILES run_rutherford.C run_rad.C eventDisplay.C
        DESTINATION share/fairbase/example/rutherford
       )