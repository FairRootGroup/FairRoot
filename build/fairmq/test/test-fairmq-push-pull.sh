#!/bin/bash

transport="zeromq"

if [ "$1" = "nanomsg" ]; then
    transport="nanomsg"
fi

trap 'kill -TERM $PUSH_PID; kill -TERM $PULL_PID; wait $PUSH_PID; wait $PULL_PID;' TERM
/Users/turany/development/FairRoot/build/bin/test-fairmq-push $transport &
PUSH_PID=$!
/Users/turany/development/FairRoot/build/bin/test-fairmq-pull $transport &
PULL_PID=$!
wait $PUSH_PID
wait $PULL_PID
