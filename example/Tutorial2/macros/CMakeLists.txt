 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             # 
 #         GNU Lesser General Public Licence version 3 (LGPL) version 3,        #  
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################
GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial2/macros/run_tutorial2.C)
add_test(run_tutorial2 ${CMAKE_BINARY_DIR}/example/Tutorial2/macros/run_tutorial2.sh)
SET_TESTS_PROPERTIES(run_tutorial2 PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(run_tutorial2 PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial2/macros/create_digis.C)
add_test(create_digis ${CMAKE_BINARY_DIR}/example/Tutorial2/macros/create_digis.sh)
SET_TESTS_PROPERTIES(create_digis PROPERTIES DEPENDS run_tutorial2)
SET_TESTS_PROPERTIES(create_digis PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(create_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

GENERATE_ROOT_TEST_SCRIPT(${CMAKE_SOURCE_DIR}/example/Tutorial2/macros/read_digis.C)
add_test(read_digis ${CMAKE_BINARY_DIR}/example/Tutorial2/macros/read_digis.sh)
SET_TESTS_PROPERTIES(read_digis PROPERTIES DEPENDS create_digis)
SET_TESTS_PROPERTIES(read_digis PROPERTIES TIMEOUT "30")
SET_TESTS_PROPERTIES(read_digis PROPERTIES PASS_REGULAR_EXPRESSION "Macro finished succesfully")

Install(FILES run_tutorial2.C create_digis.C read_digis.C
        DESTINATION share/fairbase/example/Tutorial2
       )
