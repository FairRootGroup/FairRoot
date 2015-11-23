FairMQ Examples
===============

Set of FairMQ examples.

Example 1: Sampler -> Sink
--------------------------
A simple topology of two devices - **Sampler** and **Sink**. **Sampler** sends data to **Sink** with the **PUSH-PULL** pattern.


Example 2: Sampler -> Processor -> Sink
---------------------------------------
A simple topology of three devices - **Sampler**, **Processor** and **Sink**. **Sampler** sends data to one or more **Processor**s, who modify the data and send it to one **Sink**. Transport with the **PUSH-PULL** pattern.


Example 3: DDS
--------------
This example demonstrates usage of the Dynamic Deployment System ([DDS](http://dds.gsi.de/)) to dynamically deploy and configure a topology of devices. The topology is similar to those of Example 2, but now it can be easily distributed on different computing nodes without the need for manual reconfiguration of the devices.


Example 4: Copy & Push
----------------------
A topology consisting of one **Sampler** and two **Sink**s. The **Sampler** uses the `Copy` method to send the same data to both sinks with the **PUSH_PULL** pattern. In countrary to the **PUB-PATTERN** pattern, this insures that all receivers are connected and no data is lost, but requires additional sockets.


Example 5: Request & Reply
--------------------------
This topology contains two devices that communicate with each other via the **REQUEST-REPLY** pettern. Bidirectional communication via a single socket.


Example 6: Multiple Channels
----------------------------
This example demonstrates how to work with multiple channels and multiplex between them.


Example 7: Communicating with ParameterMQServer
----------------------------
This example shows how to communicate with the ParameterMQServer, that retrieves parameters from FairRuntimeDb.


Example 8: Sending Multipart messages
----------------------------
This example shows how to send a multipart message from one device to the other. (two parts message parts - header and body).



GenericDevices:   Generic devices example
----------------------------
This example shows how to use the [policy based design](https://en.wikipedia.org/wiki/Policy-based_design) of the generic MQ-devices. See [here](https://github.com/FairRootGroup/FairRoot/tree/dev/fairmq/devices) for more information.


LmdSampler: (GSI List Mode Data format) Lmd Sampler
----------------------------
In this tutorial a sampler read an lmd file (the one in /examples/advanced/tutorial8) and send the binary data to an unpacker device. 





