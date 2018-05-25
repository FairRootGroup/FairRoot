# Move from root to FairMQ continued

This example bases on examples/MQ/pixelDetector.

The motivation behind is to get rid of TClonesArrays in the data transport.

For that, PixelAltFindHits class with ExecMQ() function was created that takes array of PixelPayload::Digi
to create an array of PixelPayload::Hit. This eliminates necessity to deal with TClonesArray when
reconstructing data.

Three devices has been created:
- FairMQPixAltTaskProcessorBin: runs the PixelAltFindHits task;
- FairMQPixAltSamplerBin: reads data from the binary file and sends PixelPayload::EventHeader and array of PixelPayload::Digi;
- FairMQPixAltFileSink: stores the EventHeader and Hits in the output binary file;

Preparations:
root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q 'run_digiToBin.C(0)';

Scripts:
- startFairMQPixAltFromRoot.sh - read the data from root file, transport and reconstruct binary, store root file;
- startFairMQPixAltFromBin.sh - read the data from binary file, transport and reconstruct binary, store root file;
- startFairMQPixAltToBin.sh - read the data from binary file, transport and reconstruct binary, store binary file;
