#!/bin/bash


CONFIGFILE="/Users/turany/development/FairRoot/examples/MQ/LmdSampler/options/LmdHeaderConfig.INI"
MQCONFIGFILE="/Users/turany/development/FairRoot/examples/MQ/LmdSampler/options/LmdMQConfig.json"
LMDFILE="/Users/turany/development/FairRoot/examples/advanced/MbsTutorial/data/sample_data_2.lmd"
VERBOSE="DEBUG"

########################## start SAMPLER
SAMPLER="runLmdSampler"
SAMPLER+=" --id LmdSampler -c $CONFIGFILE --mq-config $MQCONFIGFILE"
SAMPLER+=" --input-file-name $LMDFILE --verbose $VERBOSE"
xterm +aw -geometry 120x27+0+0 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/$SAMPLER &



########################## start Unpacker
UNPACKER="runTut8MQUnpacker"
UNPACKER+=" --id unpacker1 -c $CONFIGFILE --mq-config $MQCONFIGFILE"
UNPACKER+=" --verbose $VERBOSE"
xterm +aw -geometry 120x27+800+500 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/$UNPACKER &


########################## start FILESINK
FILESINK="runTut8Sink"
FILESINK+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK+=" --output-file-name /Users/turany/development/FairRoot/examples/MQ/LmdSampler/datasource/MQLmdOutput.root"
FILESINK+=" --verbose $VERBOSE"
xterm +aw -geometry 120x27+0+500 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/LmdSampler/$FILESINK &
