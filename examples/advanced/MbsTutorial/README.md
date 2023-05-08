# MBS Tutorial {#ex_mbstut}


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
steering class. FairMBSUnpack implements parsing of MBS subevents
and creates output in form of array of FairMBSRawItem data objects.
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
fRunOnline.AddObject(h1);
where h1 is of type TH1F* or TH2F*
~~~~~~~~~~~~~~~~~~

In addition, one can publish a canvas by using the same AddObject method. The canvas can be divided into multiple pads.
~~~~~~~~~~~~~~~~~~
TCanvas *c1 = new TCanvas("c1", "Title", 10, 10, 500, 500);
h1->Draw();
fRunOnline.AddObject(c1);
~~~~~~~~~~~~~~~~~~

In case of large amount of histogram objects for multiple detectors, the histograms can be organized in folder structure.
~~~~~~~~~~~~~~~~~~
TFolder *f1 = new TFolder("myfolder", "Title");
f1->Add(h1);
fRunOnline.AddObject(f1);
~~~~~~~~~~~~~~~~~~

Analysis task can also register a command, which can be executed on
a histogram object:
~~~~~~~~~~~~~~~~~~
fRunOnline.RegisterHttpCommand("/Reset_h1", "/h1/->Reset()");
In this case the command will reset the histogram with name "h1"
~~~~~~~~~~~~~~~~~~

During the execution of the macro, histogram server can be accessed
by typing "hostname:8080" in any web-browser window on a remote machine,
hostname - is the name or IP address of the host running the analysis.

