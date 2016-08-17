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

/Users/turany/development/install/RC_may16_R6/bin/rootcint -f /Users/turany/development/FairRoot/build/eventdisplay/G__EventDisplayDict.cxx -inlineInputHeader -rmf /Users/turany/development/FairRoot/build/lib/libEventDisplay.rootmap -rml EventDisplay.dylib -c   -I/Users/turany/development/FairRoot/fairtools -I/Users/turany/development/FairRoot/geobase -I/Users/turany/development/FairRoot/parbase -I/Users/turany/development/FairRoot/base -I/Users/turany/development/FairRoot/base/steer -I/Users/turany/development/FairRoot/base/event -I/Users/turany/development/FairRoot/base/field -I/Users/turany/development/FairRoot/base/sim -I/Users/turany/development/FairRoot/base/source -I/Users/turany/development/FairRoot/trackbase -I/Users/turany/development/FairRoot/geane -I/Users/turany/development/FairRoot/eventdisplay -I/Users/turany/development/install/RC_may16_R6/include/root -I/Users/turany/development/install/RC_may16_R6/include -I/Users/turany/development/install/RC_may16_R6/include/TGeant3 FairEventManager.h FairMCTracks.h FairEventManagerEditor.h FairMCTracksEditor.h FairBoxSet.h FairBoxSetDraw.h FairBoxSetEditor.h FairPointSetDraw.h FairMCPointDraw.h FairHitDraw.h FairHitPointSetDraw.h FairTimeStampPointDraw.h EventDisplayLinkDef.h
