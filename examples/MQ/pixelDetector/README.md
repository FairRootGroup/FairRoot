# Move from root to FairMQ {#ex_mq_pixel_detector}

This example uses standard FairRoot analysis chain:

* detector simulation,
* digitization,
* reconstruction (hit finding, tracking, track fitting),

to show how to switch for root single-core processing to FairMQ multi-core pipeline processing.

## MQ Devices

The following MQ devices are implemented:

- FairMQPixelSampler - reads data branch names specified by AddInputBranchName(string) from the input file(s) set by AddInputFileName(string) via FairSource. Currently one may attach FairFileSource (chains of ROOT files), PixelDigiSource (ascii files with PixelDigis) or PixelDigiBinSource (binary files with PixelDigis);

- template <typename T> FairMQPixelTaskProcessor - runs a task of class T. The class T needs to have the following functions:
void GetParList (TList* parList); - used to get the list of parameter objects needed by class T;
void InitMQ     (TList* parList); - initialization of the class T object using the parameters;
void ExecMQ     (TList* inputList, TList* outputList); - analyze data from inputList and store the result in outputList;

- FairMQPixelFileSink creates output ROOT file set by SetOutputFileName(string) and tree, with the branches specified by AddOutputBranch(string className, string branchName). Currently only two classes (FairEventHeader and TClonesArray of any objects) are allowed:
fileSink.AddOutputBranch(“FairEventHeader”,”EventHeader.”);
fileSink.AddOutputBranch(“TClonesArray(anyclassname)”,”branchname”); 

The above MQ devices sends FairMQParts multi-messages with TMessages inside. This method is not very efficient, but is straighforward and generic to use.

Besides, there are also binary-transport versions of the above devices:

- FairMQPixelSamplerBin
- FairMQPixelTaskProcessorBin
- FairMQPixelFileSinkBin

but only some data classes may be sent (the ones specified in PixelPayload).

FairMQPixelMerger - device to merge different parts of events. The event parts are merged into one object and sent to output.

## Executables

Separate executables for the different devices have been created:

- **pixel-sampler** ( **ex-samplerBin**),
- **pixel-processor** ( **ex-processorBin**),
- **pixel-sink** ( **ex-sinkBin**),

which run given devices and allow setting of the different parameters from the command line. These devices may run in different control modes:
- interactive - waiting for the keyboard input to change states;
- static - changes states automatically;
- dds - react to the commands sent via dds_intercom.

## Topologies and scripts
Several shell scripts using different topologies are implemented:

#### ./startFairMQPixel.sh
- **topology:**     sampler-3processors-sink
- **functions:**    can process different task with (--task-name PixelFindHits, PixelFindTracks, PixelFitTracks),
can set the number of processors tasks with -p, can limit number of events with -m,
can change running mode with --command (interactive or static)
- **preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 

#### ./startFairMQPixel_3Levels.sh
- **topology:**     sampler-2proc-2proc-2proc-sink
- **functions:**    runs hit finding, track finding, track fitting
can limit number of events with --m
- **preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 

#### ./startFairMQPixelBin.sh
- **topology:**     sampler-5processors-sink
- **functions:**    run PixelFindHits
transport binary data between devices
- **preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 

#### ./startFairMQPixelBinProxy.sh
- **topology:**     2samplers-proxy-5processors-proxy-2sinks
- **functions:**    run PixelFindHits
transport binary data between devices
proxy has several input and output queues
- **preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 

#### ./startFairMQPixelMerger.sh
- **topology:**     3samplers-3processors-merger-sink
- **functions:**    data is read by 3 samplers from 3 input files, for each station separately
hit finding is run on processors separately for each station data
merges event data from different stations and sends whole events to the sink
- **preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q run_digiToBin.C;

#### ./startFairMQPixelSimulation.sh
- **topology:**     3samplers-sink
- **functions:**    samplers are producing Monte Carlo data, one can set
the number of events produced by each sampler using --nof-events, the default
TGeant3 can be changed to --transport-name TGeant4

## Running with DDS
To run the example in the DDS, please check http://dds.gsi.de for the installation instructions.
The next step, you have to configure fairroot with -DDDS_PATH="/path/to/dds/install/dir/" and rebuild it.

These programs are started with the pixel-dds-topology.xml topology, that can be started in the following way:

```bash
dds-server start -s
dds-submit --rms localhost -n 10
dds-topology --activate bin/examples/MQ/pixelDetector/pixel-dds-topology.xml
```

One can check the status or control the devices using:

```bash
./bin/fairmq-dds-command-ui
```

There is also a interactive shell script created to ease the devices' state control. Different states are marked with different colors, and by pressing appropriate keys it is possible to control the devices:

```bash
user@host:build$ ./bin/examples/MQ/pixelDetector/controlDDS.sh
RUNNING->s->READY->t->DEVICE_READY->d->IDLE->q  /x-Exit
[parmq-server][processor_0][processor_1][processor_2][   sampler][      sink]
```

Once the sampler finishes stops running, the DDS server may be stopped:

```bash
dds-server stop
```
