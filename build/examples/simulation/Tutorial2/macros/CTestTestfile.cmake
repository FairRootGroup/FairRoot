# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/examples/simulation/Tutorial2/macros
# Build directory: /Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_tutorial2 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/run_tutorial2.sh")
set_tests_properties(run_tutorial2 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_bg "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/run_bg.sh")
set_tests_properties(run_bg PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_sg "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/run_sg.sh")
set_tests_properties(run_sg PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_sg1 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/run_sg1.sh")
set_tests_properties(run_sg1 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(create_digis_mixed "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/create_digis_mixed.sh")
set_tests_properties(create_digis_mixed PROPERTIES  DEPENDS "run_sg1" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(create_digis "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/create_digis.sh")
set_tests_properties(create_digis PROPERTIES  DEPENDS "run_tutorial2" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(read_digis "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/macros/read_digis.sh")
set_tests_properties(read_digis PROPERTIES  DEPENDS "create_digis" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
