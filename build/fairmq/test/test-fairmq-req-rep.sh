#!/bin/bash

transport="zeromq"

if [ "$1" = "nanomsg" ]; then
    transport="nanomsg"
fi

trap 'kill -TERM $REQ1_PID; kill -TERM $REQ2_PID; kill -TERM $REP_PID; wait $REQ1_PID; wait $REQ2_PID; wait $REP_PID;' TERM
/Users/turany/development/FairRoot/build/bin/test-fairmq-req $transport &
REQ1_PID=$!
/Users/turany/development/FairRoot/build/bin/test-fairmq-req $transport &
REQ2_PID=$!
/Users/turany/development/FairRoot/build/bin/test-fairmq-rep $transport &
REP_PID=$!
wait $REQ1_PID
wait $REQ2_PID
wait $REP_PID
