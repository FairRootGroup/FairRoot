# Move from root to FairMQ continued {#ex_mq_pixel_alternative}

This example bases on examples/MQ/pixelDetector.

The motivation behind is to get rid of TClonesArrays in the data transport.

For that, PixelAltFindHits class with ExecMQ() function was created that takes array of PixelPayload::Digi
to create an array of PixelPayload::Hit. This eliminates necessity to deal with TClonesArray when
reconstructing data.

Three devices has been created:
- FairMQPixAltSamplerBin: reads data from the binary file and sends PixelPayload::EventHeader and array of PixelPayload::Digi;
- FairMQPixAltTaskProcessorBin: runs the PixelAltFindHits task;
- FairMQPixAltFileSink: stores the EventHeader and Hits in the output binary file;

Preparations:
root -l -q 'run_sim.C(100000)' &> sim_100k.dat; root -l -q run_digi.C; root -l -q 'run_digiToBin.C(0)';

Script startFairMQPixAlt.sh:
- reads the data from binary file (can read root file with "--input-type root" option);
- transports and reconstructs binary;
- stores root file (can store binary file with "--output-type dat" option);
