ParameterMQServer
===============

The ParameterMQServer device sends out parameter objects (serialized with TMessage) for incoming requests (parameter name & run ID). The communication is via REQ-REP pattern.

The device executable has to be started with the following command line parameters:

- `--id <device id>` device id (has to match one in the json file).
- `--mq-config <path/to/device-config>` location of the transport config file.
- `--first-input-name` location of the first input file for the FairRuntimeDb.

Optional options are:

- `--first-input-type arg (="ROOT")` first input file type (ROOT/ASCII).
- `--second-input-name arg (="")` location of the second input file.
- `--second-input-type arg (="ROOT")` second input file type (ROOT/ASCII).
- `--output-name arg (="")` location of the output file.
- `--output-type arg (="ROOT")` output file type (ROOT).
- `--channel-name arg (="data")` output channel name.

When both inputs are provided, and a parameter exists in both, first input will be taken.

For further documentation of parameter system check [parameter section in FairRoot webpage](https://fairroot.gsi.de/?q=node/28).

The request for parameters is a string in this form: `"ParameterName,RunID"`.

For an example client device that retrieves the parameters from the ParameterMQServer, take a look at [../examples/MQ/7-parameters/](`../examples/MQ/7-parameters/`).
