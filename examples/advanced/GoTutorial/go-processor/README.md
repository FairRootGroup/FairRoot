# go-processor

`go-processor` is a simple `Go` based program using `nanomsg` as a transport facility.
It replicates the basic example from [FairRootMQ example 2](https://github.com/FairRootGroup/FairRoot/tree/master/examples/MQ/2-sampler-processor-sink).

## Build

```sh
$> cd go-processor
$> go build
```

## Usage

- First, you need to run the `C++` `FairRootMQ` `sampler` program:

```sh
$> ex2-sampler --id sampler1 \
  --transport nanomsg \
  --config-json-file /opt/alice/src/fair-root/examples/MQ/2-sampler-processor-sink/ex2-sampler-processor-sink.json --transport nanomsg
[17:04:43][STATE] Entering FairMQ state machine
[17:04:43][INFO] ***************************************************************************************************************************************************
[17:04:43][INFO] **********************************************************     Program options found     **********************************************************
[17:04:43][INFO] ***************************************************************************************************************************************************
[17:04:43][INFO] config-json-file = /opt/alice/src/fair-root/examples/MQ/2-sampler-processor-sink/ex2-sampler-processor-sink.json  [Type=string]  [provided value] *
[17:04:43][INFO] id               = sampler1                                                                                       [Type=string]  [provided value] *
[17:04:43][INFO] io-threads       = 1                                                                                              [Type=int]     [default value]  *
[17:04:43][INFO] log-color        = 1                                                                                              [Type=bool]    [default value]  *
[17:04:43][INFO] text             = Hello                                                                                          [Type=string]  [default value]  *
[17:04:43][INFO] transport        = nanomsg                                                                                        [Type=string]  [provided value] *
[17:04:43][INFO] verbose          = DEBUG                                                                                          [Type=string]  [default value]  *
[17:04:43][INFO] ***************************************************************************************************************************************************
[17:04:43][DEBUG] Found device id 'sampler1' in JSON input
[17:04:43][DEBUG] Found device id 'processor1' in JSON input
[17:04:43][DEBUG] Found device id 'processor2' in JSON input
[17:04:43][DEBUG] Found device id 'sink1' in JSON input
[17:04:43][DEBUG] [node = device]   id = sampler1
[17:04:43][DEBUG] 	 [node = channel]   name = data1
[17:04:43][DEBUG] 	 	 [node = socket]   socket index = 1
[17:04:43][DEBUG] 	 	 	 type        = push
[17:04:43][DEBUG] 	 	 	 method      = bind
[17:04:43][DEBUG] 	 	 	 address     = tcp://*:5555
[17:04:43][DEBUG] 	 	 	 sndBufSize  = 1000
[17:04:43][DEBUG] 	 	 	 rcvBufSize  = 1000
[17:04:43][DEBUG] 	 	 	 rateLogging = 0
[17:04:43][DEBUG] ---- Channel-keys found are :
[17:04:43][DEBUG] data1
[17:04:43][INFO] PID: 168
[17:04:43][INFO] Using nanomsg library
[17:04:43][STATE] Entering INITIALIZING DEVICE state
[17:04:43][INFO] created socket sampler1.device-commands.pub
[17:04:43][INFO] bind socket sampler1.device-commands.pub on inproc://commands
[17:04:43][DEBUG] Validating channel "data1[0]"... VALID
[17:04:43][DEBUG] Initializing channel data1[0] (push)
[17:04:43][INFO] created socket sampler1.data1[0].push
[17:04:43][DEBUG] Binding channel data1[0] on tcp://*:5555
[17:04:43][INFO] bind socket sampler1.data1[0].push on tcp://*:5555
[17:04:43][INFO] created socket internal.device-commands.sub
[17:04:43][INFO] connect socket internal.device-commands.sub to inproc://commands
[17:04:44][STATE] Entering DEVICE READY state
[17:04:44][STATE] Entering INITIALIZING TASK state
[17:04:44][STATE] Entering READY state
[17:04:44][STATE] Entering RUNNING state
[17:04:44][INFO] DEVICE: Running...
[17:04:44][INFO] Use keys to control the state machine:
[17:04:44][INFO] [h] help, [p] pause, [r] run, [s] stop, [t] reset task, [d] reset device, [q] end, [j] init task, [i] init device
[17:04:45][INFO] Sending "Hello"
[17:04:54][INFO] Sending "Hello"
[17:04:55][INFO] Sending "Hello"
[17:04:56][INFO] Sending "Hello"
[...]
[17:06:07][INFO] Sending "Hello"
[17:06:08][INFO] Sending "Hello"
q
[17:06:08][INFO] [q] end
[17:06:08][STATE] Entering EXITING state
[17:06:09][INFO] Sending "Hello"
[17:06:09][DEBUG] unblocked
[17:06:09][DEBUG] Closing sockets...
[17:06:09][DEBUG] Closed all sockets!
[17:06:09][STATE] Exiting FairMQ state machine
```

- Then, in another terminal:

```sh
$> go-processor
2016/03/11 17:04:53 dialing tcp://localhost:5555 ...
2016/03/11 17:04:53 dialing tcp://localhost:5555 ... [done]
2016/03/11 17:04:53 dialing tcp://localhost:5556 ...
2016/03/11 17:04:53 dialing tcp://localhost:5556 ... [done]
2016/03/11 17:04:53 recv: Hello
2016/03/11 17:04:54 recv: Hello
2016/03/11 17:04:55 recv: Hello
2016/03/11 17:04:56 recv: Hello
[...]
2016/03/11 17:06:07 recv: Hello
2016/03/11 17:06:08 recv: Hello
^C
```

- And, in yet another terminal:

```sh
$> ex2-sink --id sink1 --config-json-file /opt/alice/src/fair-root/examples/MQ/2-sampler-processor-sink/ex2-sampler-processor-sink.json --transport nanomsg
[17:05:56][STATE] Entering FairMQ state machine
[17:05:56][INFO] ***************************************************************************************************************************************************
[17:05:56][INFO] **********************************************************     Program options found     **********************************************************
[17:05:56][INFO] ***************************************************************************************************************************************************
[17:05:56][INFO] config-json-file = /opt/alice/src/fair-root/examples/MQ/2-sampler-processor-sink/ex2-sampler-processor-sink.json  [Type=string]  [provided value] *
[17:05:56][INFO] id               = sink1                                                                                          [Type=string]  [provided value] *
[17:05:56][INFO] io-threads       = 1                                                                                              [Type=int]     [default value]  *
[17:05:56][INFO] log-color        = 1                                                                                              [Type=bool]    [default value]  *
[17:05:56][INFO] transport        = nanomsg                                                                                        [Type=string]  [provided value] *
[17:05:56][INFO] verbose          = DEBUG                                                                                          [Type=string]  [default value]  *
[17:05:56][INFO] ***************************************************************************************************************************************************
[17:05:56][DEBUG] Found device id 'sampler1' in JSON input
[17:05:56][DEBUG] Found device id 'processor1' in JSON input
[17:05:56][DEBUG] Found device id 'processor2' in JSON input
[17:05:56][DEBUG] Found device id 'sink1' in JSON input
[17:05:56][DEBUG] [node = device]   id = sink1
[17:05:56][DEBUG] 	 [node = channel]   name = data2
[17:05:56][DEBUG] 	 	 [node = socket]   socket index = 1
[17:05:56][DEBUG] 	 	 	 type        = pull
[17:05:56][DEBUG] 	 	 	 method      = bind
[17:05:56][DEBUG] 	 	 	 address     = tcp://*:5556
[17:05:56][DEBUG] 	 	 	 sndBufSize  = 1000
[17:05:56][DEBUG] 	 	 	 rcvBufSize  = 1000
[17:05:56][DEBUG] 	 	 	 rateLogging = 0
[17:05:56][DEBUG] ---- Channel-keys found are :
[17:05:56][DEBUG] data2
[17:05:56][INFO] PID: 219
[17:05:56][INFO] Using nanomsg library
[17:05:56][STATE] Entering INITIALIZING DEVICE state
[17:05:56][INFO] created socket sink1.device-commands.pub
[17:05:56][INFO] bind socket sink1.device-commands.pub on inproc://commands
[17:05:56][DEBUG] Validating channel "data2[0]"... VALID
[17:05:56][DEBUG] Initializing channel data2[0] (pull)
[17:05:56][INFO] created socket sink1.data2[0].pull
[17:05:56][DEBUG] Binding channel data2[0] on tcp://*:5556
[17:05:56][INFO] bind socket sink1.data2[0].pull on tcp://*:5556
[17:05:56][INFO] created socket internal.device-commands.sub
[17:05:56][INFO] connect socket internal.device-commands.sub to inproc://commands
[17:05:57][STATE] Entering DEVICE READY state
[17:05:57][STATE] Entering INITIALIZING TASK state
[17:05:57][STATE] Entering READY state
[17:05:57][STATE] Entering RUNNING state
[17:05:57][INFO] Use keys to control the state machine:
[17:05:57][INFO] [h] help, [p] pause, [r] run, [s] stop, [t] reset task, [d] reset device, [q] end, [j] init task, [i] init device
[17:05:57][INFO] DEVICE: Running...
[17:05:57][INFO] Received message: "HelloHello"
[17:05:57][INFO] Received message: "HelloHello"
[17:05:57][INFO] Received message: "HelloHello"
[...]
[17:06:04][INFO] Received message: "HelloHello"
[17:06:05][INFO] Received message: "HelloHello"
[17:06:06][INFO] Received message: "HelloHello"
[17:06:07][INFO] Received message: "HelloHello"
[17:06:08][INFO] Received message: "HelloHello"
q
[17:06:12][INFO] [q] end
[17:06:12][STATE] Entering EXITING state
[17:06:12][DEBUG] unblocked
[17:06:12][DEBUG] Closing sockets...
[17:06:12][DEBUG] Closed all sockets!
[17:06:12][STATE] Exiting FairMQ state machine
```
