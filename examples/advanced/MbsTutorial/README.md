# MBS Tutorial


## Quick start

Enter FairRoot build directory and configure your shell:

~~~~~~~~~~~~~~~~~~
. ./config.sh
~~~~~~~~~~~~~~~~~~

Enter MbsTutorial macro directory and execute the ROOT macro:

~~~~~~~~~~~~~~~~~~
root -l unpack_mbs.C
~~~~~~~~~~~~~~~~~~

## Introduction
The MbsTutorial shows how to use MBS data unpacking with FairRunOnline
steering class. FairTut8Unpack implements parsing of MBS subevents
and creates output in form of array of FairTut8RawItem data objects.
This example also demonstrates usage of ROOT histogram online server
with possibility to view 1D and 2D histograms, with monitorring option
and pre-defined user commands.

## HTTP Server
Start of a ROOT Histogram Server can be done by calling the following method
of FairRunOnline in the steering macro, before the call to Init()
~~~~~~~~~~~~~~~~~~
ActivateHttpServer()
~~~~~~~~~~~~~~~~~~

Histograms to be published can be added from an analysis task by:
~~~~~~~~~~~~~~~~~~
FairRunOnline::Instance()->AddObject(h1);
where h1 is of type TH1F* or TH2F*
~~~~~~~~~~~~~~~~~~

Analysis task can also register a command, which can be executed on
a histogram object:
~~~~~~~~~~~~~~~~~~
FairRunOnline::Instance()->RegisterHttpCommand("/Reset_h1", "/h1/->Reset()");
In this case the command will reset the histogram with name "h1"
~~~~~~~~~~~~~~~~~~

During the execution of the macro, histogram server can be accessed
by typing "hostname:8080" in any web-browser window on a remote machine,
hostname - is the name or IP address of the host running the analysis.

