# Serialization Examples {#ex_mq_serialization}

## Quick start

### Generate input file
Start the script startSerializationGenerateData.sh (in FairRoot/build/bin/) to generate and store random data.
A file inputGenEx.root will be produce in the directory <build_dir>/examples/MQ/GenericDevices/data_io.
Use the help command line :
```bash
./startSerializationGenerateData.sh --help
```
to see the available command line options (the output file is already set in the startSerializationGenerateData.sh script).
The data structure are basi digi with (x, y, z, t, t_err) as data members. The (x,y,z) digi data members are normally distributed with defined mean and standard deviation. The mean of t is defined by the time index (from 0 to tmax) and the standard deviation is defined by t_err. By default tmax is set to 100 (which will produce tmax=100 messages). Use for example:

```bash
./startSerializationGenerateData.sh --tmax 1000
```

to increase the number of gaussian(x,y,z). For each time index, N event will be generated according to the gaussian(x,y,z) pdf. The number N also fluctuate according to gaussian(N,N_err). Use for example

```bash
./startSerializationGenerateData.sh --Nmean 1000 --Nsigma 10
```

to set the average number and standard deviation of digi per time index (pulse). This will vary the number of digis per message and hence the data size to transport.

### Start the process chain
Start one of the two scripts (the scripts will use the inputGenEx.root as data source).

```bash
# single part transport
./startSerializationEx1.sh
# or multipart transport (header+data)
./startSerializationEx2.sh
```
