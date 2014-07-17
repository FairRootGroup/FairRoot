## Help on configuring devices

Currently, the configuration of topologies and devices is done via bash scripts. In the future, this will be handled by the [DDS](https://github.com/FairRootGroup/DDS) and a dedicated web interface.

Here is a brief description of the script arguments and their possible values.

### Common for all devices

**ID**: device ID. Just something to identify the device, currently used only in logger output.

**numIoThreads**: number of IO threads ZeroMQ should use. According to [ZeroMQ documentation](http://zguide.zeromq.org/page:all#I-O-Threads), using more than one thread only becomes relevant at 1GB/s and above.

**outputSocketType**: output pattern. Possible values: "push"/"pub".

**outputBufSize**: size of the ZeroMQ output queue (in # of messages). For nanomsg transport, the size is in bytes.

**outputMethod**: output method - "bind"/"connect". One side should bind and other should connect. The order doesn't matter, but for some topologies chosing the right combination can simplify the configuration.

**outputAddress**: output address and port.

**inputSocketType**: same as above, but for input. Possible values: pull/sub.

**inputRcvBufSize**: same as above, but for input.

**inputMethod**: same as above, but for input.

**inputAddress**: same as above, but for input.

### Sampler specific

**inputFile**: input file  (specific to sampler task)

**parameterFile**: parameter file (specific to sampler task)

**branch**: define the sampler task (this is likely to be removed in future version)

**eventRate**: optional limit for number of events/second, e.g. 1000 - up to 1000 events per second. Value 0 means no limit.

### Processor specific

**processorTask**: define the processor task (this is likely to be removed in future version)

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

ID="101"
inputFile="@CMAKE_SOURCE_DIR@/example/Tutorial3/macro/data/testdigi.root"
parameterFile="@CMAKE_SOURCE_DIR@/example/Tutorial3/macro/data/testparams.root"
branch="FairTestDetectorDigi"
eventRate="0"
numIoThreads="1"
outputSocketType="push"
outputBufSize=$buffSize
outputMethod="bind"
outputAddress="tcp://*:5565"
xterm -e @CMAKE_BINARY_DIR@/bin/testDetectorSampler$dataFormat $ID $inputFile $parameterFile $branch $eventRate $numIoThreads $outputSocketType $outputBufSize $outputMethod $outputAddress &

ID="201"
processorTask="FairTestDetectorMQRecoTask"
numIoThreads="1"
inputSocketType="pull"
inputRcvBufSize=$buffSize
inputMethod="connect"
inputAddress="tcp://localhost:5565"
outputSocketType="push"
outputSndBufSize=$buffSize
outputMethod="connect"
outputAddress="tcp://localhost:5570"
xterm -e @CMAKE_BINARY_DIR@/bin/testDetectorProcessor$dataFormat $ID $processorTask $numIoThreads $inputSocketType $inputRcvBufSize $inputMethod $inputAddress $outputSocketType $outputSndBufSize $outputMethod $outputAddress &

ID="301"
numIoThreads="1"
inputSocketType="pull"
inputRcvBufSize=$buffSize
inputMethod="bind"
inputAddress="tcp://*:5570"
xterm -e @CMAKE_BINARY_DIR@/bin/fileSink$dataFormat $ID $numIoThreads $inputSocketType $inputRcvBufSize $inputMethod $inputAddress &
```