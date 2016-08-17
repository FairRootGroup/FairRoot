#!/bin/bash
ex7config="/Users/turany/development/FairRoot/build/bin/config/ex7-client.json"
parmqconfig="/Users/turany/development/FairRoot/build/bin/config/parameter-server.json"

SAMPLER="ex7-client"
SAMPLER+=" --id parmq-client"
SAMPLER+=" --mq-config $ex7config"
xterm -geometry 80x23+0+0 -hold -e /Users/turany/development/FairRoot/build/bin/examples/MQ/7-parameters/$SAMPLER &

PARAMETERSERVER="parmq-server"
PARAMETERSERVER+=" --id parmq-server"
PARAMETERSERVER+=" --mq-config $parmqconfig"
PARAMETERSERVER+=" --first-input-name /Users/turany/development/FairRoot/examples/MQ/7-parameters/mqexample7_param.root"
xterm -geometry 80x23+500+0 -hold -e /Users/turany/development/FairRoot/build/bin/$PARAMETERSERVER &
