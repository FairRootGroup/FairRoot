# MC simulations in FairMQ {#ex_mq_pixel_simsplit}

The example shows the possibility to separate the generation of the MC events from their transport in Geant engines.

### FairMQPrimaryGeneratorDevice
Generates MC events and sends them. It can also split events into smaller chunks.
The size (in the number of particles) of the maximal chunk is specified via chunk-size program option.
The default option is to transport whole events (the value is set to 0):
```
./pixel-sim-gen --chunk-size 10 
```

### FairMQTransportDevice
Receives events (or chunks of them) and transports them through a given geometry.
The detector geometry may be specified:
- statically: in the executable program that starts the device:
```
Pixel*  det = new Pixel("PixelDetector", kTRUE);
     det->SetGeometryFileName("pixel.geo");
     detArray->Add(det);
     run->SetDetectorArray   (detArray);
     run->SetStoreTraj       (false);
```
- dynamically, via the extern C libraries loading mechanism through program options:
```
./pixel-sim-transport --detector-library libTutorial1.dylib --detector-library libPixel.dylib
```
The latter option requires implementation of the extern C function ExternCreateDetector, fe.:
```
extern "C" void ExternCreateDetector() {
    FairRunSim* run = FairRunSim::Instance();
    Pixel*  det = new Pixel("PixelDetector", kTRUE);
    det->SetGeometryFileName("pixel.geo");
    run->AddModule(det);
}
```

### FairMQChunkMerger
Merges chunks back into full events.

# Running

The generator and transporter may run in one of two modes:
- request-reply: the generator waits for the requests from the transporter(s) before
generating new events. This mode is optimal for large detector setups, where transporter
CPU cost is large and the number of simulated events is typically low.
- push-pull: the generator pushes the events, and the transporter(s) is pulling. This running mode
is useful for small detector setups with small CPU cost, where plenty of events are generated.

# Tests

Currently two comparable automatic tests are provided, one running in pure MQ, the other using DDS.

