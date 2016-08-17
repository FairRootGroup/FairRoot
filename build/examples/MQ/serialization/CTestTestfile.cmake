# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/examples/MQ/serialization
# Build directory: /Users/turany/development/FairRoot/build/examples/MQ/serialization
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_serialization_ex1 "/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/startTestSerializationEx1.sh")
set_tests_properties(run_serialization_ex1 PROPERTIES  PASS_REGULAR_EXPRESSION "Received 100 messages!" TIMEOUT "30")
add_test(run_serialization_ex2 "/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/startTestSerializationEx2.sh")
set_tests_properties(run_serialization_ex2 PROPERTIES  DEPENDS "run_serialization_ex1" PASS_REGULAR_EXPRESSION "Received 100 messages!" TIMEOUT "30")
