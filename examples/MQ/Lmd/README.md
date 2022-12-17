# MQ tutorial : Lmd Sampler {#ex_mq_lmd}

## Introduction
In this tutorial a sampler read an lmd file (the one in /examples/advanced/MbsTutorial) and send the binary data to an unpacker device. The unpacker device unpack the binary data and serialize the data (using TMessage data format) and send the data to a FileSink device.

To start the demo, go to the FairRoot/build/bin directory and do:
```bash
./startMQExLmd.sh
```
