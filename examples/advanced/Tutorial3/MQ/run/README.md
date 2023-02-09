# Data Format {#ex_tutorial3_mq_dataformat}

Each device in this example implements several serialization approaches:

- binary format
- boost::serialization
- Google FlatBuffers
- Google Protocol Buffers
- ROOT TMessage

To choose specific format when running the device, provide it to the start script (binary is default):

```bash
./startMQTut3All.sh <binary|boost|flatbuffers|protobuf|tmessage>
```

## Topologies

The devices can be started in different topologies:

- `startMQTut3Three` : sampler -> processor -> sink
- `startMQTut3All` : sampler -> splitter -> 3 processors -> merger -> sink
- `startMQTut3AllProxy` : sampler -> proxy -> 3 processors -> proxy -> sink
- `startMQTut3PushPull` : sampler -> 2 processors -> sink (load-balanced/round robin between processors)
- `startMQTut3ExtraProcessor` : additional processor to plug into PushPull topology
