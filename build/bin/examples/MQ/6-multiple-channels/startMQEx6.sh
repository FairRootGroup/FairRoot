#!/bin/bash
ex6config="/Users/turany/development/FairRoot/build/bin/config/ex6-multiple-channels.json"

SAMPLER="ex6-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --mq-config $ex6config"
xterm -geometry 80x23+0+0 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/6-multiple-channels/$SAMPLER &

SINK="ex6-sink"
SINK+=" --id sink1"
SINK+=" --mq-config $ex6config"
xterm -geometry 80x23+500+0 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/6-multiple-channels/$SINK &

BROADCASTER="ex6-broadcaster"
BROADCASTER+=" --id broadcaster1"
BROADCASTER+=" --mq-config $ex6config"
xterm -geometry 80x23+250+330 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/6-multiple-channels/$BROADCASTER &
