# Tutorial3 {#ex_tutorial3}

This example demonstrate

* Detector simulation
* Event by event digitization
* Time based digitization
* \subpage ex_tutorial3_mq
Message Queue based reconstruction: The Message Queue based reconstruction demonstrates the usage of FairMQ.
Any number of "sampler" processes (FairMQSampler, FairMQSamplerTask, TestDetectorDigiLoader) send the data generated in the digitization step to a number of "processor" processes which do the reconstruction with the data (FairMQProcessor, FairMQProcessorTask, FairTestDetectorMQRecoTask). After the reconstruction task, the processes send the output data to a number of "sink" processes, which write the data to disk (FairTestDetectorFileSink).
All the communication between these processes is done via FairMQ and can be configured to run over network (tcp) or on a local machine with inter-process communication (ipc). Currently, the number of processes and their parameters are configured with bash scripts/command line parameters. The scripts are located in the MQ/run directory, together with README.md for more details on how to configure them.
Event display

* PROOF
PROOF lets you process your data in parallel using standard ROOT tools. Generally PROOF allows you
to use several computers creating your own computing cluster. Much simpler usecase is the usage
of the computing cores available on your local computer - in this case we talk about PROOFLite.

This example lets you see how to use PROOF (the Parallel ROOT Facility) in the data reconstruction using FairRoot framework.
The basic macro is run_digi_reco_proof.C, which uses PROOF to split digitization between cores of your computer.
In contrast, the macro run_digi_reco_local.C performs the same job using single core.

You may test it by simulating a set of data:
