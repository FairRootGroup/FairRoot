# FairRoot

[![license](https://alfa-ci.gsi.de/shields/badge/license-LGPL--3.0-orange.svg)](COPYRIGHT) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.3896282.svg)](https://doi.org/10.5281/zenodo.3896282) [![OpenSSF Best Practices](https://bestpractices.coreinfrastructure.org/projects/7131/badge)](https://bestpractices.coreinfrastructure.org/projects/7131) [![fair-software.eu](https://img.shields.io/badge/fair--software.eu-%E2%97%8F%20%20%E2%97%8F%20%20%E2%97%8B%20%20%E2%97%8F%20%20%E2%97%8F-yellow)](https://fair-software.eu)

## The FairRoot framework
A simulation, reconstruction and analysis framework that is based on the ROOT system.
The user can create simulated data and/or perform analysis with the same framework.  Geant3 and Geant4 transport engines are supported, however the user code that creates simulated data do not depend on a particular Monte Carlo engine. The framework delivers base classes which enable the users to  construct their detectors and /or analysis tasks in a simple way, it also delivers some general functionality like track visualization. Moreover an interface for reading magnetic field maps is also implemented.

## License
FairRoot  is distributed under the terms of the GNU Lesser General Public Licence version 3 (LGPLv3).

## Release information
Please see : https://github.com/FairRootGroup/FairRoot/releases

## Getting started
Please see : [fairroot.gsi.de](https://fairroot.gsi.de/index.html%3Fq=Getting_started.html)  for  details.


## Using the Project template

FairRoot delivers various project templates that can be used as a starting point for anybody who would like to build simulation and reconstruction with FairRoot.  The project Templates are located in the [FairRoot/templates](templates) directory.


## Optional change of output tree name

By default, the name of the tree in output ROOT file is "cbmsim". In case you want to change it for your Project, you need to create "config" folder inside of top source directory of the Project and place there "rootmanager.dat" text file with following single line: "treename=name_you_chose":

```bash
cd PROJECT_TOP_DIR
mkdir config
echo 'treename=name_you_chose' > config/rootmanager.dat
```

It is also possible to set the folder/tree names using corresponding (`SetFolderName()`/`SetTreeName()`) methods of the FairRootManager.

## Step by Step installation

1. Install [FairSoft](https://github.com/FairRootGroup/FairSoft)

2. Install [FairRoot](http://fairroot.gsi.de)

    ```bash
    # Set the shell variable SIMPATH to the FairSoft installation directory
    export SIMPATH=~/fair_install/FairSoft/install
    [setenv SIMPATH ~/fair_install/FairSoft/install]

    cd ~/fair_install
    git clone -b dev https://github.com/FairRootGroup/FairRoot.git
    cd FairRoot
    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX="~/fair_install/FairRoot/install" ..
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

   you need to copy the  [project template](templates/project_root_containers) to you own directory

    ```bash
    # Set the shell variable FAIRROOTPATH to the FairRoot installation directory
    export SIMPATH=~/fair_install/FairSoft/install
    [setenv SIMPATH ~/fair_install/FairSoft/install]
    export FAIRROOTPATH=~/fair_install/FairRoot/install
    [setenv FAIRROOTPATH ~/fair_install/FairRoot/install]

    cd ~/fair_install
    cp  -rf  FairRoot/templates/project_root_containers   MyTest
    cd MyTest
    ./rename.sh  MyExperiment MyExp det

    # Please call the script with three parameters. The first one is the
    # name of the project. The second one is the prefix in front of
    # the class names. and some directories. So this second parameter
    # shouldn't be to long. The third parameter is the name of the
    # detector you want to implement.
    # As an example the if you want to create a project for the Panda
    # experiment and you want to implement a Straw Tube Tracker (stt)
    # you would call the script in the following way.
    # ./rename.sh Panda Pnd stt

    mkdir build
    cd build
    cmake ../MyExperiment
    make
    . ./config.sh    [or source config.csh]
    ```

    Now you can for example simulate some events and run the event display:

    ```bash
    root -q ../macro/run_sim.C
    root ../macro/eventDisplay.C
    // Click on "FairEventManager" (in the top-left pane)
    // Click on the "Info" tab (on top of the bottom-left pane)
    // Increase the "Current Event" to >0 to see the events
    root [1] .q
    ```


## Generating Doxygen documentation

If the flage -DBUILD_DOXYGEN=ON is set when calling cmake, the doxygen documentation will be generated when calling make.  The generated html files can then be found in "build/doxygen/doc/html"

Doxygen documantation is also available online [here](http://fairrootgroup.github.io/FairRoot/html/index.html)
