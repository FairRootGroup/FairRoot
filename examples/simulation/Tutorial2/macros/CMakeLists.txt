 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #              GNU Lesser General Public Licence (LGPL) version 3,             #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

Set(MaxTestTime 60)

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/run_tutorial2.C)
add_test(run_tutorial2 ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/run_tutorial2.sh)
SET_TESTS_PROPERTIES(run_tutorial2 PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(run_tutorial2 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/create_digis.C)
add_test(create_digis ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/create_digis.sh)
SET_TESTS_PROPERTIES(create_digis PROPERTIES DEPENDS run_tutorial2)
SET_TESTS_PROPERTIES(create_digis PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(create_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/read_digis.C)
add_test(read_digis ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/read_digis.sh)
SET_TESTS_PROPERTIES(read_digis PROPERTIES DEPENDS create_digis)
SET_TESTS_PROPERTIES(read_digis PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(read_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")


GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/run_bg.C)
add_test(run_bg ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/run_bg.sh)
SET_TESTS_PROPERTIES(run_bg PROPERTIES DEPENDS read_digis)
SET_TESTS_PROPERTIES(run_bg PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(run_bg PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/run_sg.C)
add_test(run_sg ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/run_sg.sh)
SET_TESTS_PROPERTIES(run_sg PROPERTIES DEPENDS run_bg)
SET_TESTS_PROPERTIES(run_sg PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(run_sg PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/run_sg1.C)
add_test(run_sg1 ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/run_sg1.sh)
SET_TESTS_PROPERTIES(run_sg1 PROPERTIES DEPENDS run_sg)
SET_TESTS_PROPERTIES(run_sg1 PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(run_sg1 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/examples/simulation/Tutorial2/macros/create_digis_mixed.C)
add_test(create_digis_mixed ${CMAKE_BINARY_DIR}/examples/simulation/Tutorial2/macros/create_digis_mixed.sh)
SET_TESTS_PROPERTIES(create_digis_mixed PROPERTIES DEPENDS run_bg)
SET_TESTS_PROPERTIES(create_digis_mixed PROPERTIES DEPENDS run_sg)
SET_TESTS_PROPERTIES(create_digis_mixed PROPERTIES DEPENDS run_sg1)
SET_TESTS_PROPERTIES(create_digis_mixed PROPERTIES TIMEOUT ${MaxTestTime})
SET_TESTS_PROPERTIES(create_digis_mixed PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished successfully")

Install(FILES  run_tutorial2.C create_digis.C read_digis.C run_bg.C run_sg.C run_sg1.C create_digis_mixed.C
        DESTINATION share/fairbase/examples/simulation/Tutorial2
        )
