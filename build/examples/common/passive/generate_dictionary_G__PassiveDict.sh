#!/bin/bash

# This macro is used to generate the ROOT dictionaries
# To use the ctest launchers one needs some environment variables which
# are only present when running CMake. To have the same environment at
# the time the dictionary is build this script is used which is build
# at the time cmake runs.

# Setup the needed environment
export LD_LIBRARY_PATH=/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib
export DYLD_LIBRARY_PATH=/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/FairRoot/build/lib:/Users/turany/development/install/RC_may16_R6/lib/root:/Users/turany/development/install/RC_may16_R6/lib
export ROOTSYS=/Users/turany/development/install/RC_may16_R6

/Users/turany/development/install/RC_may16_R6/bin/rootcint -f /Users/turany/development/FairRoot/build/examples/common/passive/G__PassiveDict.cxx -inlineInputHeader -rmf /Users/turany/development/FairRoot/build/lib/libPassive.rootmap -rml Passive.dylib -c   -I/Users/turany/development/FairRoot/fairtools -I/Users/turany/development/FairRoot/geobase -I/Users/turany/development/FairRoot/parbase -I/Users/turany/development/FairRoot/base -I/Users/turany/development/FairRoot/base/steer -I/Users/turany/development/FairRoot/base/event -I/Users/turany/development/FairRoot/base/field -I/Users/turany/development/FairRoot/base/sim -I/Users/turany/development/FairRoot/base/source -I/Users/turany/development/FairRoot/dbase -I/Users/turany/development/FairRoot/dbase/dbInterface -I/Users/turany/development/FairRoot/dbase/dbValidation -I/Users/turany/development/FairRoot/dbase/dbUtils -I/Users/turany/development/FairRoot/input/db -I/Users/turany/development/FairRoot/dbase/dbInput -I/Users/turany/development/FairRoot/dbase/dbIO -I/Users/turany/development/FairRoot/examples/common/passive -I/Users/turany/development/install/RC_may16_R6/include/root -I/Users/turany/development/install/RC_may16_R6/include FairCave.h FairGeoCave.h FairGeoMagnet.h FairGeoPassivePar.h FairGeoPipe.h FairGeoTarget.h FairMagnet.h FairPassiveContFact.h FairPipe.h FairTarget.h PassiveLinkDef.h
