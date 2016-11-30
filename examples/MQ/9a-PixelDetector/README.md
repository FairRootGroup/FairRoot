#Move from root to FairMQ continued

This example bases on examples/MQ/9-PixelDetector.

The motivation behind is to get rid of TClonesArrays in the data transport.

For that, PixelAltFindHits class with ExecMQ() function was created that takes array of PixelPayload::Digi
to create an array of PixelPayload::Hit. This eliminates necessity to deal with TClonesArray when
reconstructing data.

Three devices has been created:
- FairMQEx9aTaskProcessorBin: runs the PixelAltFindHits task;
- FairMQEx9aSamplerBin: reads data from the binary file and sends PixelPayload::EventHeader and array of PixelPayload::Digi;
- FairMQEx9aFileSink: stores the EventHeader and Hits in the output binary file;

Preparations:
root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q 'run_digiToBin.C(0)';

Scripts:
- startFairMQEx9aFromRoot.sh - read the data from root file, transport and reconstruct binary, store root file;
- startFairMQEx9aFromBin.sh - read the data from binary file, transport and reconstruct binary, store root file;
- startFairMQEx9aToBin.sh - read the data from binary file, transport and reconstruct binary, store binary file;

MQ/Example9a Development of the	9a MQ example -	introduction of
sampler, sink, running scripts:

Classes:
- FairMQEx9aTaskProcessorBin - runs the PixelAltFindHits;
- FairMQEx9aSamplerBin - reads data from the binary file and sends PixelPayload::EventHeader and ar\
ray of PixelPayload::Digi;
- FairMQEx9aFileSink: stores the EventHeader and Hits in the output binary file;
Executables:
- runEx9FileSinkBin
- runEx9SamplerBin
- runEx9TaskProcessorBin