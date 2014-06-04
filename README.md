FairSoft
========

Repository for installation routines of the external software needed to use FairRoot.
To simplify the installation procedure of all the needed software packages we provide 
a set of scripts which will automatically download the source code and build all the 
needed packages.

As a first step it is checked that the needed development environment (e.g. compilers)
is present on the computer to be able to build the software packages.

To start the installation procedure one has to run the configure.sh script which is
found in the main directory of FairSoft from this directory.

FairSoft> ./configure.sh

In the first menu one has to define the compiler which should be used for
installation. This compiler has to be present on the system. If one choose
a compiler which can't be found the installation procedure will stop when checking
for the development environment with an error message.

In the second menu one has to decide if the packages should be installed in
debug, normal or optimization mode. If one choose the optimization mode one
should also  define the optimization flags in the appropriate part of the file
scripts/check_system.sh, even if there are some default settings.
If unsure don't use this option.

In the third menu one has to define how to handle the geant4 data files. These files
have a file size of approximately 450 MB. If you don't intent to use Geant4 at all
you must not need to download the files. 

If the data files should be installed it is normally save to choose the
option Internet which will download the files and does the installation
automatically when installing Geant4. 
Only if your system cannot download the files choose the Directory option. 
In this case one has to put the files into the transport directory so that they can be 
installed. One can download the files from the following webpage.

http://geant4.cern.ch/support/download.shtml

In the last menu one has to define the installation directory. All the programs will be
installed into this directory. One shouldn't use as installation directory a directory with 
is used by the system (e.g. /usr or /usr/local). Since it is possible to install several
version of "FairSoft" in parallel it is advisable to use a name tag in the ropository 
name (e.g. <install_dir>/fairsoft_dec13)

After answering all the questions above the installation process starts which can take a 
long time. If there are errors one can start the script safely again. It will check which 
parts have been already compilled and installed and will skip this parts.

Packages included:
boost_1_54_0
cmake 2.8.12.2
G4VMC 2.15
Geant321+_vmc.1.15a
Geant4.10.00
gsl-1.16
gtest  1.7.0
HepMC  2.06.09
MILLEPEDE  V04-01-01
pythia6
Pythia8 183
ROOT  v5.34.17
Pluto v5.37
VGM  v3-06
ZeroMQ 3.2.4





