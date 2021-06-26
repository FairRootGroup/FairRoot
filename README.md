# FairRoot [![license](https://alfa-ci.gsi.de/shields/badge/license-LGPL--3.0-orange.svg)](COPYRIGHT)

## The FairRoot framework
A simulation, reconstruction and analysis framework that is based on the ROOT system.
The user can create simulated data and/or perform analysis with the same framework.  Geant3 and Geant4 transport engines are supported, however the user code that creates simulated data do not depend on a particular monte carlo engine. The framework delivers base classes which enable the users to  construct their detectors and /or analysis tasks in a simple way, it also delivers some general functionality like track visualization. Moreover an interface for reading magnetic field maps is also implemented.

## License
FairRoot  is distributed under the terms of the GNU Lesser General Public Licence version 3 (LGPLv3).

## Release information
Please see : https://github.com/FairRootGroup/FairRoot/releases

## Getting started
Please see : http://fairroot.gsi.de/getting_started  for  details.


## Using the Project template

FairRoot deliver meanwhile a project template that can be used as a starting point for anybody who would like to build simulation and reconstruction on FairRoot.  The project Template is in the [FairRoot/template/project_template](https://github.com/FairRootGroup/FairRoot/tree/dev/templates/project_template) directory

The template demonstrate and implement the following:

1.  General structure of the software (cake config files, VMC/Geant configurations, etc ..)
2.  Example detector with sensitive and passive volumes (NewDetector) and data class
3.  Particle Stack for Geant3/4  with filtering infrastructure
4.  Event generators (Pathia6,8) more are available directly from FairRoot
5.  Passive component implementation (Magnet Yoke, Beam Pipe)
6.  Track visualisation tool (Event display)
7.  A rename script which replace all the generic names to user defined ones

### Optional change of output tree name

By default, the name of the tree in output ROOT file is "cbmsim". In case you want to change it for your Project, you need to create "config" folder inside of top source directory of the Project and place there "rootmanager.dat" text file with following single line: "treename=name_you_chose".

```bash
cd PROJECT_TOP_DIR
mkdir config
echo 'treename=name_you_chose' > config/rootmanager.dat
```


### Step by Step installation

1. Install [FairSoft](https://github.com/FairRootGroup/FairSoft)

2. Install [FairRoot](http://fairroot.gsi.de/?q=node/82)

    ```bash
    # Set the shell variable SIMPATH to the FairSoft installation directory
    export SIMPATH=~/fair_install/FairSoftInst
    [setenv SIMPATH ~/fair_install/FairSoftInst]

    cd ~/fair_install
    git clone -b master https://github.com/FairRootGroup/FairRoot.git
    cd FairRoot
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX="~/fair_install/FairRootInst" ..
    make
    make install
    ```

    To run the tests do:

    ```bash
    # To run test: make new shell, do not define SIMPATH
    cd ~/fair_install/FairRoot/build
    make test
    ```

3. Install the template:

   you need to copy the  [project template](https://github.com/FairRootGroup/FairRoot/tree/dev/templates/project_template) to you own directory

    ```bash
    # Set the shell variable FAIRROOTPATH to the FairRoot installation directory
    export FAIRROOTPATH=~/fair_install/FairRootInst
    [setenv FAIRROOTPATH ~/fair_install/FairRootInst]

    cd ~/fair_install
    cp  -rf  FairRoot/templates/project_template   MyTest
    cd MyTest
    ./rename.sh  MyExperiment  PREFIX  MyDetector

    # Please call the script with three parameters. The first one is the
    # name of the project. The second one is the prefix in front of
    # the class names. and some directories. So this second parameter
    # shouldn't be to long. The third parameter is the name of the
    # detector you want to implement.
    # As an example the if you want to create a project for the Panda
    # experiment and you want to implement a Straw Tube Tracker (stt)
    # you would call the script in the following way.
    # ./rename.sh Panda Pnd stt

    cd ..
    mkdir build
    cd build
    cmake ../MyExperiment
      make
    . config.sh    [or source config.csh]
    ```

    Now you can for example simulate some events and run the event display:

    ```bash
    root -q ../MyExperiment/macro/run_sim.C
    root ../MyExperiment/macro/eventDisplay.C
    // Click on "FairEventManager" (in the top-left pane)
    // Click on the "Info" tab (on top of the bottom-left pane)
    // Increase the "Current Event" to >0 to see the events
    root [1] .q
    ```


## Generating Doxygen documentation

If the flage -DBUILD_DOXYGEN=ON is set when calling cmake, the doxygen documentation will be generated when calling make.  The generated html files can then be found in "build/doxygen/doc/html"

Doxygen documantation is also available online [here](http://Fairrootgroup.github.io/FairRoot/)
