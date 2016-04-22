#Move from root to FairMQ

This example uses standard FairRoot analysis chain:

* detector simulation,
* digitization,
* reconstruction (hit finding, tracking, track fitting),

to show how to switch for root single-core processing to FairMQ multi-core pipeline processing.

##MQ Devices

The following MQ devices are implemented:

- FairMQEx9Sampler - reads data branch names specified by AddInputBranchName(string) from the input file(s) set by AddInputFileName(string) via FairSource. Currently one may attach FairFileSource (chains of ROOT files), PixelDigiSource (ascii files with PixelDigis) or PixelDigiBinSource (binary files with PixelDigis);

- template <typename T> FairMQEx9TaskProcessor - runs a task of class T. The class T needs to have the following functions:
void GetParList (TList* parList); - used to get the list of parameter objects needed by class T;
void InitMQ     (TList* parList); - initialization of the class T object using the parameters;
void ExecMQ     (TList* inputList, TList* outputList); - analyze data from inputList and store the result in outputList;

- FairMQEx9FileSink creates output ROOT file set by SetOutputFileName(string) and tree, with the branches specified by AddOutputBranch(string className, string branchName). Currently only two classes (FairEventHeader and TClonesArray of any objects) are allowed:
fileSink.AddOutputBranch(“FairEventHeader”,”EventHeader.”);
fileSink.AddOutputBranch(“TClonesArray(anyclassname)”,”branchname”); 

The above MQ devices sends FairMQParts multi-messages with TMessages inside. This method is not very efficient, but is straighforward and generic to use.

Besides, there are also binary-transport versions of the above devices:

- FairMQEx9SamplerBin
- FairMQEx9TaskProcessorBin
- FairMQEx9FileSinkBin

but only some data classes may be sent (the ones specified in PixelPayload).

FairMQEx9Merger - device to merge different parts of events. The event parts are merged into one object and sent to output.

##Topologies and scripts
Several shell scripts using different topologies are implemented:

#### ./startFairMQEx9New.sh
**topology:**     sampler-5processors-sink
**functions:**    can process different task with (--task-name PixelFindHits, PixelFindTracks, PixelFitTracks)
can limit number of events with --m
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 
#### ./startFairMQEx9_2Levels.sh
**topology:**     sampler-3proc-3proc-sink
**functions:**    can process different task with (-f PixelFindHits -g PixelFindTracks or -f PixelFindTracks -gPixelFitTracks)
can limit number of events with --m
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 
#### ./startFairMQEx9_3Levels.sh
**topology:**     sampler-2proc-2proc-2proc-sink
**functions:**    runs hit finding, track finding, track fitting
can limit number of events with --m
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 
#### ./startFairMQEx9Bin.sh
**topology:**     sampler-5processors-sink
**functions:**    run PixelFindHits
transport binary data between devices
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 
#### ./startFairMQEx9BinProxy.sh
**topology:**     2samplers-proxy-5processors-proxy-2sinks
**functions:**    run PixelFindHits
transport binary data between devices
proxy has several input and output queues
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; 
#### ./startFairMQEx9Merger.sh
**topology:**     3samplers-3processors-merger-sink
**functions:**    data is read by 3 samplers from 3 input files, for each station separately
hit finding is run on processors separately for each station data
merges event data from different stations and sends whole events to the sink
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q run_digiToBin.C;
#### ./startFairMQEx9Merger2Levels.sh
**topology:**     3samplers-6processors-merger-3processors-sink
**functions:**    data is read by 3 samplers from 3 input files, for each station separately
hit finding is run on processors separately for each station data
merges event data from different stations and sends whole events with PixelHits
the second level of processors runs the track finding 
**preparations:** root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q run_digiToBin.C;
