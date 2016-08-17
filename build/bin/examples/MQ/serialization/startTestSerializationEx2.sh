#!/bin/bash

trap 'kill -TERM $GENERATE_PID; kill -TERM $SAMPLER_PID; kill -TERM $PROCESSOR1_PID; kill -TERM $FILESINK_PID; wait $GENERATE_PID; wait $SAMPLER_PID; wait $PROCESSOR1_PID; wait $FILESINK_PID;' TERM


########################## some def

VERBOSITY="DEBUG"
INPUTFILE="/Users/turany/development/FairRoot/examples/MQ/serialization/data_io/testinput2.root"
OUTPUTFILE="/Users/turany/development/FairRoot/examples/MQ/serialization/data_io/outputEx2Test.root"
#JSONCONFIGFILE="/Users/turany/development/FairRoot/examples/MQ/serialization/options/MQConfig.json"
JSONCONFIGFILE="/Users/turany/development/FairRoot/examples/MQ/serialization/test/testSerializationEx2Config.json"


########################## start dummy data generator
GENERATE="serialization-Ex-generate-data"
GENERATE+=" --output-file $INPUTFILE"
GENERATE+=" --tree cbmsim --log-color false"
/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/$GENERATE &
GENERATE_PID=$!
wait $GENERATE_PID

########################## start SAMPLER
SAMPLER="serialization-Ex2-Sampler"
SAMPLER+=" --id sampler1 --mq-config $JSONCONFIGFILE --verbose $VERBOSITY"
SAMPLER+=" --input-file $INPUTFILE --log-color false --control static"
/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/$SAMPLER &
SAMPLER_PID=$!

########################## start PROCESSOR
PROCESSOR1="test-serialization-Ex2-Processor"
PROCESSOR1+=" --id processor1 --mq-config $JSONCONFIGFILE --verbose $VERBOSITY --log-color false --control static"
/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/$PROCESSOR1 &
PROCESSOR1_PID=$!

########################## start FILESINK
FILESINK="test-serialization-Ex2-sink"
FILESINK+=" --id sink1 --mq-config $JSONCONFIGFILE --verbose $VERBOSITY --log-color false --control static"
FILESINK+=" --output-file $OUTPUTFILE"
/Users/turany/development/FairRoot/build/bin/examples/MQ/serialization/$FILESINK &
FILESINK_PID=$!

wait $SAMPLER_PID
wait $PROCESSOR1_PID
wait $FILESINK_PID
