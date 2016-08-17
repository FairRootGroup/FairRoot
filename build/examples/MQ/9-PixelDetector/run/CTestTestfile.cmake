# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/run
# Build directory: /Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/run
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ex9_static "/Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/run/startFairMQEx9_Static.sh" "--work-dir" "/Users/turany/development/FairRoot/build")
set_tests_properties(ex9_static PROPERTIES  DEPENDS "ex9_digi_TGeant3" PASS_REGULAR_EXPRESSION "Shell script finished successfully" TIMEOUT "30")
