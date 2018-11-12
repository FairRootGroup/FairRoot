MC Step Logger
========

Virtual Monte Carlo is calling a Stepping function of FairMCApplication while transporting particles through geometry.
MC Step Logger counts individual calls to this Stepping function for each module of the geometry, specified by its name.
The logger prints this information after each event, as well as summed up at the end of the run.

## LD_PRELOAD mechanism

The library **_preload_** mechanism was used in order to eliminate any negative influence on the time performance when running
without the MC Step Logger.

The **_preload_** library catches in the runtime all calls to a specificic function (in this case Stepping function of FairMCApplication)
and executes a specified list of instructions instead (in this case counting of steps _and_ subsequent execution of the original function).

To use the MC Step Logger the user has to **_preload_** the compiled library. It is achieved in one of the following ways:

1. Set the **_preload_** library. Run your code. Unset the library:

```bash
export LD_PRELOAD=/path/to/your/library/libFairMCStepLogger.so
root UserMacro.C
unset LD_PRELOAD
```

2. Run your code with the **_preload_** library:

```bash
LD_PRELOAD=/path/to/your/library/libFairMCStepLogger.so root UserMacro.C
```

The PRELOAD mechanism eliminates any overhead when running without the MC Step Logger.
It also allowed for absolutely no changes in the FairRoot code.

## MAC OS

Since MAC OS has to always be special, then also the **_preload_** looks different here.
On MAC OS the user has to specify DYLD_INSERT_LIBRARIES. Yet again, there are two ways to do it:

1. Set the **_preload_** library. Run your code. Unset the library:

```bash
export DYLD_INSERT_LIBRARIES=/path/to/your/library/libFairMCStepLogger.so
root UserMacro.C
unset DYLD_INSERT_LIBRARIES
```

2. Run your code with the **_preload_** library:

```bash
DYLD_INSERT_LIBRARIES=/path/to/your/library/libFairMCStepLogger.so root UserMacro.C
```
