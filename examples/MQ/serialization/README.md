# Serialization Examples {#ex_mq_serialization}

## Quick start

### Generate input file
Start the script startDataGenerator.sh to generate and store random data.
A file `input.root` will be produced in the directory `<build_dir>/examples/MQ/serialization/data_io`.
Use the help command line :
```bash
./startDataGenerator.sh --help
```
to see the available command line options (the output file is already set in the startDataGenerator.sh script).
The data structure are basi digi with (x, y, z, t, t_err) as data members. The (x,y,z) digi data members are normally distributed with defined mean and standard deviation. The mean of t is defined by the time index (from 0 to tmax) and the standard deviation is defined by t_err. By default tmax is set to 100 (which will produce tmax=100 messages). Use for example:

```bash
./startDataGenerator.sh --tmax 1000
```

to increase the number of gaussian(x,y,z). For each time index, N event will be generated according to the gaussian(x,y,z) pdf. The number N also fluctuate according to gaussian(N,N_err). Use for example

```bash
./startDataGenerator.sh --Nmean 1000 --Nsigma 10
```

to set the average number and standard deviation of digi per time index (pulse). This will vary the number of digis per message and hence the data size to transport.

### Start the processing chain

Start the script (the script will use the input.root as data source):

```bash
./startSerializationEx.sh
```

This launches a topology of 4 devices:
- Sampler device reads the input data and serializes it with ROOT serializer, adding another msg part with a header serialized with Boost and sends these 2 parts out.
- 2 Processors receive and deserialize the data, do some processing on it and serialize the result with Boost, sending it further.
- Sink receives and deserializes the data sent by the processor and writes it to a ROOT file.
