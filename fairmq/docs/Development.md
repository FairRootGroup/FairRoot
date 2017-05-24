← [Back](../README.md)

# 3. Development

# 3.1 Testing

TODO

# 3.2 Implementation details

## 3.2.1 Shared memory monitor

The shared memory monitor tool, supplied with the shared memory transport can be used to monitor shared memory use and automatically cleanup shared memory in case of device crashes.

With default arguments the monitor will run indefinitely with no output, and clean up shared memory segment if it is open and no heartbeats from devices arrive within a timeout period. It can be further customized with following parameters: 

  `--segment-name <arg>`: customize the name of the shared memory segment (default is "fairmq_shmem_main").
  `--cleanup`: start monitor, perform cleanup of the memory and quit.
  `--self-destruct`: run until the memory segment is closed (either naturally via cleanup performed by devices or in case of a crash (no heartbeats within timeout)).
  `--interactive`: run interactively, with detailed segment details and user input for various shmem operations.
  `--timeout <arg>`: specifiy the timeout for the heartbeats from shmem transports in milliseconds (default 5000).

The options can be combined, with the exception of `--cleanup` option, which will invoke the described behaviour independent of other options.
Without the `--self-destruct` option, the monitor will run continously, moitoring (and cleaning up if needed) consecutive topologies.

Possible further implementation would be to run the monitor with `--self-destruct` with each topology.

The FairMQShmMonitor class can also be used independently from the supplied executable (built from `runFairMQShmMonitor.cxx`), allowing integration on any level. For example invoking the monitor could be a functionality that a device offers.

← [Back](../README.md)
