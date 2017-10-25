GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/advanced/MbsTutorial/macros/unpack_mbs.C)
add_test(unpack_mbs ${CMAKE_BINARY_DIR}/examples/advanced/MbsTutorial/macros/unpack_mbs.sh)
configure_file(${CMAKE_SOURCE_DIR}/examples/advanced/MbsTutorial/data/sample_data_2.lmd  ${CMAKE_BINARY_DIR}/examples/advanced/MbsTutorial/data/sample_data_2.lmd COPYONLY)
SET_TESTS_PROPERTIES(unpack_mbs PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(unpack_mbs PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")
Install(FILES unpack_mbs.C
         DESTINATION share/fairbase/examples/advanced/MbsTutorial/macros
         )
