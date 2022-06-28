Example 7: Communicating with ParameterMQServer {#ex_mq_parameters}
===============

This example shows how to communicate with the ParameterMQServer, that retrieves parameters from FairRuntimeDb.

The `fill_parameters.C` ROOT macro can be used to generate the parameter file for the server to read from. The generated file will contain paramters with the name `FairMQExParamsParOne` for run IDs 2000-2099.

FairMQExample7Client device requests parameter data from ParameterMQServer via REQ-REP pattern. The request contains parameter name and run ID.

The parameter name can be configured via command line (`--parameter-name`, default is `FairMQExParamsParOne`) and the run ID is hardcoded for this example.
