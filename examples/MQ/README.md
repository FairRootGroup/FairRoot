# FairMQ Examples {#ex_mq}

Set of FairMQ examples.


- Lmd: (GSI List Mode Data format) Lmd Sampler
  <br/>
  \subpage ex_mq_lmd

  In this tutorial a sampler read an lmd file (the one in /examples/advanced/tutorial8) and send the binary data to an unpacker device.


- \subpage ex_mq_parameters

  This example shows how to communicate with the ParameterMQServer, that retrieves parameters from FairRuntimeDb.


- pixelDetector: Transport FairRoot data between devices, analyze the data using existing instances of FairTask
  <br/>
  \subpage ex_mq_pixel_simsplit
  <br/>
  \subpage ex_mq_pixel_detector

  This example shows how to send a multipart message from one device to the other. (two parts message parts - header and body).


- pixelAlternative: Transport FairRoot data between devices, implement special devices to analyze data
  <br/>
  \subpage ex_mq_pixel_alternative

  This example shows how to send a multipart message from one device to the other. (two parts message parts - header and body).

- histogramServer

  TODO: fill me.

- \subpage ex_mq_serialization
