#!/bin/bash


opt=""

if [ "$#" -gt 0 ]; then
        opt=" $*"
fi

GENERATE="serialization-Ex-generate-data$opt"
GENERATE+=" --output-file /Users/turany/development/FairRoot/examples/MQ/serialization/data_io/inputEx.root"
GENERATE+=" --tree cbmsim"
# output file -> InputFile of sampler

/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/$GENERATE 
