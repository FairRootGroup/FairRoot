#!/bin/bash

transport="zeromq"

if [ "$1" = "nanomsg" ]; then
    transport="nanomsg"
fi

trap 'kill -TERM $PUB_PID; kill -TERM $SUB1_PID; kill -TERM $SUB2_PID; wait $PUB_PID; wait $SUB1_PID; wait $SUB2_PID;' TERM
/Users/turany/development/FairRoot/build/bin/test-fairmq-pub $transport &
PUB_PID=$!
/Users/turany/development/FairRoot/build/bin/test-fairmq-sub $transport &
SUB1_PID=$!
/Users/turany/development/FairRoot/build/bin/test-fairmq-sub $transport &
SUB2_PID=$!
wait $PUB_PID
wait $SUB1_PID
wait $SUB2_PID
