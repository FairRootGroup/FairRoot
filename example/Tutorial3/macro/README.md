## Help on configuring devices

Currently, the configuration of topologies and devices is done via bash scripts. In the future, this will be handled by the [DDS](https://github.com/FairRootGroup/DDS) and a dedicated web interface.

Here is a brief description of the script arguments and their possible values.

Further details for available device options can be queried for any executable when called with `--help` command line option.

### Common for all devices

**--id**: device ID. Just something to identify the device, currently used only in logger output.

**--io-threads**: Optional parameter, to change the number of i/o threads ZeroMQ should use. Default value is 1 i/o thread. According to [ZeroMQ documentation](http://zguide.zeromq.org/page:all#I-O-Threads), using more than one thread only becomes relevant at 1GB/s and above.

**--output-socket-type**: output pattern. Possible values: "push"/"pub".

**--output-buff-size**: size of the ZeroMQ output queue in number of messages. For nanomsg transport, the size is in bytes.

**--output-method**: output method - "bind"/"connect". One side should bind and other should connect. The order doesn't matter, but for some topologies chosing the right combination can simplify the configuration.

**--output-address**: output interface, address and port.

**--input-socket-type**: same as above, but for input. Possible values: pull/sub.

**--input-buff-size**: same as above, but for input.

**--input-method**: same as above, but for input.

**--input-address**: same as above, but for input.

### Sampler specific

**--input-file**: input file  (specific to sampler task).

**--parameter-file**: parameter file (specific to sampler task).

**--branch**: sampler task. Default for Tutorial3 is "FairTestDetectorDigi".

### Processor specific

**--processor-task**: processor task. Default for Tutorial3 is "FairTestDetectorMQRecoTask".

### Data format definition

Currently, there is a separate binary for each data format (binary, boost serialized, protocol buffer). This choice is likely to become another parameter in the future, but for now, the data format can be given to the bash script as a command line argument, as follows:

```bash
./startAll.sh bin
./startAll.sh boost
./startAll.sh proto
```

The script will then start the corresponding executable. If no or incorrect parameters are provided, binary method will be used! Protobuf method currently works only if the library is available on the system, otherwise it is not compiled.

## Example

The following bash script will start a topology consisting of three devices - *Sampler*, *Processor* and *FileSink*:

```bash
#!/bin/bash

if(@NANOMSG_FOUND@); then
    buffSize="50000000" # nanomsg buffer size is in bytes
else
    buffSize="1000" # zeromq high-water mark is in messages
fi

dataFormat="Bin"
if [ "$1" = "bin" ]; then
    echo "attempting to use pure binary data format"
elif [ "$1" = "boost" ]; then
    dataFormat="Boost"
    echo "attempting to use Boost serialized data format"
elif [ "$1" = "proto" ]; then
    dataFormat="Proto"
    echo "attempting to use Google Protocol Buffers data format"
elif [ "$1" = "root" ]; then
    dataFormat="Root"
    echo "attempting to use Root TMessage data format"
else
    echo "none or incorrect data formats provided."
    echo "(available data format options are: bin, boost, proto, root)"
    echo "binary data format will be used."
fi

SAMPLER="testDetectorSampler$dataFormat"
SAMPLER+=" --id 101"
SAMPLER+=" --input-file @CMAKE_SOURCE_DIR@/example/Tutorial3/macro/data/testdigi.root"
SAMPLER+=" --parameter-file @CMAKE_SOURCE_DIR@/example/Tutorial3/macro/data/testparams.root"
SAMPLER+=" --output-socket-type push --output-buff-size $buffSize --output-method bind --output-address tcp://*:5565"
xterm -e @CMAKE_BINARY_DIR@/bin/$SAMPLER &

PROCESSOR="testDetectorProcessor$dataFormat"
PROCESSOR+=" --id 201"
PROCESSOR+=" --input-socket-type pull --input-buff-size $buffSize --input-method connect --input-address tcp://localhost:5565"
PROCESSOR+=" --output-socket-type push --output-buff-size $buffSize --output-method connect --output-address tcp://localhost:5570"
xterm -e @CMAKE_BINARY_DIR@/bin/$PROCESSOR &

FILESINK="fileSink$dataFormat"
FILESINK+=" --id 301"
FILESINK+=" --input-socket-type pull --input-buff-size $buffSize --input-method bind --input-address tcp://*:5570"
xterm -e @CMAKE_BINARY_DIR@/bin/$FILESINK &

```