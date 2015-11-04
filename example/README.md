#Examples

##Tutorial1:

Implement a simple detector using the old ASCII interface to describe the geometry.

##Tutorial2

Reading and writing paramters

##Tutorial3

Detector simulation and digitization event wise and timebased simulation.
Use of FairMQ 

##Tutorial4

ROOT geometry as input for detector description

##Tutorial5 (optional, available only when compiling with FairDB)

Use of FairDB

##MQ/GenericDevices

shows how to use three generic devices, namely a generic sampler, processor and filesink. These three devices are policy based designed classes. These devices all inherit from FairMQDevice and from specific template parameters, 

##MQ/LmdSampler

shows an example of a device (sampler) reading a Lmd file (lmd file provided in Tutorial8), sending the contained sub-event data to an unpacker device. The latter unpack and convert the data to a root object and send it further to a file sink device via a Root TMessage data format.

##Tutorial8

Shows how to use MBS data unpacking with FairRunOnline steering class. FairTut8Unpack implement parsing of MBS subevents and 
creates output in form of array of FairTut8RawItem data objects.

##rutherford

simple simulation of the Rutherford experiment, with event display.

##Flp2epn

Simple example for Message based processing using FairRoot.

