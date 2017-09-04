## Tutorial3

This example demonstrate

* Detector simulation
* Event by event digitization
* Time based digitization
* Message Queue based reconstruction: The Message Queue based reconstruction demonstrates the usage of FairMQ.
Any number of "sampler" processes (FairMQSampler, FairMQSamplerTask, TestDetectorDigiLoader) send the data generated in the digitization step to a number of "processor" processes which do the reconstruction with the data (FairMQProcessor, FairMQProcessorTask, FairTestDetectorMQRecoTask). After the reconstruction task, the processes send the output data to a number of "sink" processes, which write the data to disk (FairTestDetectorFileSink).
All the communication between these processes is done via FairMQ and can be configured to run over network (tcp) or on a local machine with inter-process communication (ipc). Currently, the number of processes and their parameters are configured with bash scripts/command line parameters. The scripts are located in the MQ/run directory, together with README.md for more details on how to configure them.
Event display
