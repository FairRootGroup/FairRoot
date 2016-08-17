# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/examples/simulation/Tutorial4/macros
# Build directory: /Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_tutorial4_TGeant3 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/macros/run_tutorial4.sh" "10" "\"TGeant3\"")
set_tests_properties(run_tutorial4_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_tut4_TGeant3 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/macros/run_reco.sh" "\"TGeant3\"")
set_tests_properties(run_reco_tut4_TGeant3 PROPERTIES  DEPENDS "run_tutorial4_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial4_TGeant4 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/macros/run_tutorial4.sh" "10" "\"TGeant4\"")
set_tests_properties(run_tutorial4_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_tut4_TGeant4 "/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/macros/run_reco.sh" "\"TGeant4\"")
set_tests_properties(run_reco_tut4_TGeant4 PROPERTIES  DEPENDS "run_tutorial4_TGeant4" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
