# CMake generated Testfile for 
# Source directory: /Users/turany/development/FairRoot/fairmq/test
# Build directory: /Users/turany/development/FairRoot/build/fairmq/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_fairmq_push_pull_zmq "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-push-pull.sh" "zeromq")
set_tests_properties(run_fairmq_push_pull_zmq PROPERTIES  PASS_REGULAR_EXPRESSION "PUSH-PULL test successfull" TIMEOUT "30")
add_test(run_fairmq_pub_sub_zmq "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-pub-sub.sh" "zeromq")
set_tests_properties(run_fairmq_pub_sub_zmq PROPERTIES  PASS_REGULAR_EXPRESSION "PUB-SUB test successfull" TIMEOUT "30")
add_test(run_fairmq_req_rep_zmq "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-req-rep.sh" "zeromq")
set_tests_properties(run_fairmq_req_rep_zmq PROPERTIES  PASS_REGULAR_EXPRESSION "REQ-REP test successfull" TIMEOUT "30")
add_test(run_fairmq_transfer_timeout_zmq "/Users/turany/development/FairRoot/build/bin/test-fairmq-transfer-timeout" "zeromq")
set_tests_properties(run_fairmq_transfer_timeout_zmq PROPERTIES  PASS_REGULAR_EXPRESSION "Transfer timeout test successfull" TIMEOUT "30")
add_test(run_fairmq_push_pull_nn "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-push-pull.sh" "nanomsg")
set_tests_properties(run_fairmq_push_pull_nn PROPERTIES  PASS_REGULAR_EXPRESSION "PUSH-PULL test successfull" TIMEOUT "30")
add_test(run_fairmq_pub_sub_nn "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-pub-sub.sh" "nanomsg")
set_tests_properties(run_fairmq_pub_sub_nn PROPERTIES  PASS_REGULAR_EXPRESSION "PUB-SUB test successfull" TIMEOUT "30")
add_test(run_fairmq_req_rep_nn "/Users/turany/development/FairRoot/build/fairmq/test/test-fairmq-req-rep.sh" "nanomsg")
set_tests_properties(run_fairmq_req_rep_nn PROPERTIES  PASS_REGULAR_EXPRESSION "REQ-REP test successfull" TIMEOUT "30")
add_test(run_fairmq_transfer_timeout_nn "/Users/turany/development/FairRoot/build/bin/test-fairmq-transfer-timeout" "nanomsg")
set_tests_properties(run_fairmq_transfer_timeout_nn PROPERTIES  PASS_REGULAR_EXPRESSION "Transfer timeout test successfull" TIMEOUT "30")
