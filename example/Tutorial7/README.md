#Tutorial 7


## Quick start

### Generate input file
Start the script startTuto7GenerateData.sh (in FairRoot/build/bin/) to generate and store random data. 
A file Tuto7InputFile.root will be produce in the directory FairRoot/example/Tutorial7/macro/datasource.
Use the help command line : 
```bash
./startTuto7GenerateData.sh --help 
```
to see the available command line options (the output file is already set in the startTuto7GenerateData.sh script).
The data structure are basically digi with (x, y, z, t, t_err) as data members. These variables are normally distributed with defined mean and standard deviation. The mean of t is defined by the time index (from 0 to tmax) and the standard deviation is defined by t_err. By default tmax is set to 100. Use for example :

```bash
./startTuto7GenerateData.sh --tmax 1000
```

To increase the number of gaussian(x,y,z). For each time index, N event will be generated according to the gaussian(x,y,z) pdf. The number N also fluctuate according to gaussian(N,N_err). Use for example

```bash
./startTuto7GenerateData.sh --Nmean 1000 --Nsigma 10
```

to set the average number and standard deviation of digi per time index (pulse). For example on ubuntu 14.04.3 LTS and with gcc 4.8.4, the MyDigi class has a size of about 104 bytes (the serialized data members however have a size of 28 bytes). Therefore, with this setting, the approximated size of the generated file will be about Nmean x tmax x 104 bytes.

### Start the process chain
Start the script startTuto7All.sh to use the Tuto7InputFile.root as data source. 
In this tutorial7 example, the implemented serialization formats are boost, binary, Root (TMessage). 
To enable a specific format use e.g.

```bash
./startTuto7All.sh bin
./startTuto7All.sh boost
./startTuto7All.sh root
```

Alternatively you can start the script startTuto7AllTuto3.sh to use the testdigi.root from tutorial3 as data source.
See tutorial 3 for more details.

