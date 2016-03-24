#GenericDevices


## Quick start

### Generate input file
Start the script startGenericMQTutoGenerateData.sh (in FairRoot/build/bin/) to generate and store random data. 
A file GenericMQTutoInputFile.root will be produce in the directory FairRoot/examples/MQ/GenericDevices/data_io.
Use the help command line : 
```bash
./startGenericMQTutoGenerateData.sh --help 
```
to see the available command line options (the output file is already set in the startGenericMQTutoGenerateData.sh script).
The data structure are basi digi with (x, y, z, t, t_err) as data members. The (x,y,z) digi data members are normally distributed with defined mean and standard deviation. The mean of t is defined by the time index (from 0 to tmax) and the standard deviation is defined by t_err. By default tmax is set to 100 (which will produce tmax=100 messages). Use for example :

```bash
./startGenericMQTutoGenerateData.sh --tmax 1000
```

to increase the number of gaussian(x,y,z). For each time index, N event will be generated according to the gaussian(x,y,z) pdf. The number N also fluctuate according to gaussian(N,N_err). Use for example

```bash
./startGenericMQTutoGenerateData.sh --Nmean 1000 --Nsigma 10
```

to set the average number and standard deviation of digi per time index (pulse). This will vary the number of digis a message contains. For example on ubuntu 14.04.3 LTS and with gcc 4.8.4, the MyDigi class has a size of about 104 bytes (the serialized data members however have a size of 28 bytes). Therefore, with this setting, the approximated size of the generated file will be about Nmean x tmax x 104 bytes.

### Start the process chain
Start the script startGenericMQTutoAll.sh to use the GenericMQTutoInputFile.root as data source. 
In this example, the implemented serialization formats are boost, binary, and Root (TMessage). 
To enable a specific format use e.g.

```bash
./startGenericMQTutoAll.sh bin
./startGenericMQTutoAll.sh boost
./startGenericMQTutoAll.sh root
```

Alternatively you can start the script startGenericMQTutoAllTuto3.sh to use the testdigi.root from tutorial3 as data source.
See tutorial 3 for more details.

### How does it work?
This tutorial shows how to use the [policy based design](https://en.wikipedia.org/wiki/Policy-based_design) of the generic MQ-devices. See [here](https://github.com/FairRootGroup/FairRoot/tree/dev/fairmq/devices) for more information.

