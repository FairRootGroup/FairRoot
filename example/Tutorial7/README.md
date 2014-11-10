#Tutorial 7


## Quick start

### Generate input file
Start the script startTuto7GenerateData.sh (in FairRoot/build/bin/) to generate and store random data. 
A file Tuto7InputFile.root will be produce in the directory FairRoot/example/Tutorial7/macro/datasource.

### Start the process chain
Start the script startTuto7All.sh to use the Tuto7InputFile.root as data source. 
The implemented serialization formats are boost, binary, Root (TMessage). 
To enable a specific format use e.g.

```bash
./startTuto7All.sh bin
./startTuto7All.sh boost
./startTuto7All.sh root
```

Alternatively you can start the script startTuto7AllTuto3.sh to use the testdigi.root from tutorial3 as data source.
See tutorial 3 for more details.

## Introduction
The Tutorial 7 show how to use three generic devices, namely a generic sampler, processor and filesink.
These three devices are policy based designed classes. These devices all inherit from FairMQDevice and from specific template parameters, namely :
* The sampler inherit from 
 * a sampler policy (e.g a file reader) 
 * an output policy (serialize)
* The processor inherit from 
 * an input policy (deserialize) 
 * an output policy (serialize)
 * a task policy (process data)
* The filesink inherit from 
 * an input policy (deserialize)
 * a storage policy.

Some policy examples (c.f. e.g. BoostSerializer.h) are available in Base/MQ.
