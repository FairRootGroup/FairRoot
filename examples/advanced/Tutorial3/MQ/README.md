# Tutorial 3 - Message Queue part {#ex_tutorial3_mq}

This part of Tutorial3 demonstrates how to transport data of Tutorial3 (FairTestDetector) via FairMQ.

## Data Format {#ex_tutorial3_mq_dataformat}

Each device in this example implements several serialization approaches:

- binary format
- boost::serialization
- Google FlatBuffers
- Google Protocol Buffers
- ROOT TMessage

To choose specific format when running the device, provide it to the start script (binary is default):

```bash
./start.sh <binary|boost|flatbuffers|protobuf|tmessage>
```

## Topology

The devices are started in the following topology:

sampler -> 2 processors -> sink

Data is distributed round-robin between processors.
