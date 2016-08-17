# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/examples/advanced/MbsTutorial/macros
# Build directory: /Users/turany/development/FairRoot/build/examples/advanced/MbsTutorial/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unpack_mbs "/Users/turany/development/FairRoot/build/examples/advanced/MbsTutorial/macros/unpack_mbs.sh")
set_tests_properties(unpack_mbs PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "30")
