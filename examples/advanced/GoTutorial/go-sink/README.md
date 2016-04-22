# go-sink

`go-sink` is a simple `Go` based program using `nanomsg` as a transport facility.
It replicates the basic example from [FairRootMQ example 1](https://github.com/FairRootGroup/FairRoot/tree/master/examples/MQ/1-sampler-sink).

## Build

```sh
$> cd go-sink
$> go build
```

## Usage

- First, you need to run the `C++` `FairRootMQ` `sampler` program:

```sh
$> ex1-sampler --id sampler1 \
  --transport nanomsg \
  --config-json-file /opt/alice/src/fair-root/examples/MQ/1-sampler-sink/ex1-sampler-sink.json
[14:36:48][STATE] Entering FairMQ state machine
[14:36:48][INFO] *******************************************************************************************************************************
[14:36:48][INFO] ************************************************     Program options found     ************************************************
[14:36:48][INFO] *******************************************************************************************************************************
[14:36:48][INFO] config-json-file = /opt/alice/src/fair-root/examples/MQ/1-sampler-sink/ex1-sampler-sink.json  [Type=string]  [provided value] *
[14:36:48][INFO] id               = sampler1                                                                   [Type=string]  [provided value] *
[14:36:48][INFO] io-threads       = 1                                                                          [Type=int]     [default value]  *
[14:36:48][INFO] log-color        = 1                                                                          [Type=bool]    [default value]  *
[14:36:48][INFO] text             = Hello                                                                      [Type=string]  [default value]  *
[14:36:48][INFO] transport        = nanomsg                                                                    [Type=string]  [provided value] *
[14:36:48][INFO] verbose          = DEBUG                                                                      [Type=string]  [default value]  *
[14:36:48][INFO] *******************************************************************************************************************************
[14:36:48][DEBUG] Found device id 'sampler1' in JSON input
[14:36:48][DEBUG] Found device id 'sink1' in JSON input
[14:36:48][DEBUG] [node = device]   id = sampler1
[14:36:48][DEBUG] 	 [node = channel]   name = data
[14:36:48][DEBUG] 	 	 [node = socket]   socket index = 1
[14:36:48][DEBUG] 	 	 	 type        = push
[14:36:48][DEBUG] 	 	 	 method      = bind
[14:36:48][DEBUG] 	 	 	 address     = tcp://*:5555
[14:36:48][DEBUG] 	 	 	 sndBufSize  = 1000
[14:36:48][DEBUG] 	 	 	 rcvBufSize  = 1000
[14:36:48][DEBUG] 	 	 	 rateLogging = 0
[14:36:48][DEBUG] ---- Channel-keys found are :
[14:36:48][DEBUG] data
[14:36:48][INFO] PID: 143
[14:36:48][INFO] Using nanomsg library
[14:36:48][STATE] Entering INITIALIZING DEVICE state
[14:36:48][INFO] created socket sampler1.device-commands.pub
[14:36:48][INFO] bind socket sampler1.device-commands.pub on inproc://commands
[14:36:48][DEBUG] Validating channel "data[0]"... VALID
[14:36:48][DEBUG] Initializing channel data[0] (push)
[14:36:48][INFO] created socket sampler1.data[0].push
[14:36:48][DEBUG] Binding channel data[0] on tcp://*:5555
[14:36:48][INFO] bind socket sampler1.data[0].push on tcp://*:5555
[14:36:48][INFO] created socket internal.device-commands.sub
[14:36:48][INFO] connect socket internal.device-commands.sub to inproc://commands
[14:36:49][STATE] Entering DEVICE READY state
[14:36:49][STATE] Entering INITIALIZING TASK state
[14:36:49][STATE] Entering READY state
[14:36:49][STATE] Entering RUNNING state
[14:36:49][INFO] DEVICE: Running...
[14:36:49][INFO] Use keys to control the state machine:
[14:36:49][INFO] [h] help, [p] pause, [r] run, [s] stop, [t] reset task, [d] reset device, [q] end, [j] init task, [i] init device
[14:36:50][INFO] Sending "Hello"
[14:37:29][INFO] Sending "Hello"
[14:37:30][INFO] Sending "Hello"
[14:37:31][INFO] Sending "Hello"
[14:37:32][INFO] Sending "Hello"
[14:37:33][INFO] Sending "Hello"
[14:37:34][INFO] Sending "Hello"
[14:37:35][INFO] Sending "Hello"
q
[14:37:36][INFO] [q] end
[14:37:36][STATE] Entering EXITING state
[14:37:36][DEBUG] unblocked
[14:37:36][DEBUG] Closing sockets...
[14:37:36][DEBUG] Closed all sockets!
[14:37:36][STATE] Exiting FairMQ state machine
```

- Then, in another terminal:

```sh
$> go-sink
2016/03/11 14:37:28 dialing tcp://localhost:5555 ...
2016/03/11 14:37:28 dialing tcp://localhost:5555 ... [done]
2016/03/11 14:37:28 recv: Hello
2016/03/11 14:37:29 recv: Hello
2016/03/11 14:37:30 recv: Hello
2016/03/11 14:37:31 recv: Hello
2016/03/11 14:37:32 recv: Hello
2016/03/11 14:37:33 recv: Hello
2016/03/11 14:37:34 recv: Hello
^C
$>
```
