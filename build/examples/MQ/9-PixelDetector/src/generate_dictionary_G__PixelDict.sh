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

/Users/turany/development/install/RC_may16_R6/bin/rootcint -f /Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/src/G__PixelDict.cxx -inlineInputHeader -rmf /Users/turany/development/FairRoot/build/lib/libPixel.rootmap -rml Pixel.dylib -c   -I/Users/turany/development/FairRoot/fairtools -I/Users/turany/development/FairRoot/geobase -I/Users/turany/development/FairRoot/parbase -I/Users/turany/development/FairRoot/base -I/Users/turany/development/FairRoot/base/steer -I/Users/turany/development/FairRoot/base/event -I/Users/turany/development/FairRoot/base/field -I/Users/turany/development/FairRoot/base/sim -I/Users/turany/development/FairRoot/base/source -I/Users/turany/development/FairRoot/dbase -I/Users/turany/development/FairRoot/dbase/dbInterface -I/Users/turany/development/FairRoot/dbase/dbValidation -I/Users/turany/development/FairRoot/dbase/dbUtils -I/Users/turany/development/FairRoot/input/db -I/Users/turany/development/FairRoot/dbase/dbInput -I/Users/turany/development/FairRoot/dbase/dbIO -I/Users/turany/development/FairRoot/fairmq -I/Users/turany/development/FairRoot/base/MQ/policies/Serialization -I/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src -I/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices -I/Users/turany/development/FairRoot/examples/common/mcstack -I/Users/turany/development/install/RC_may16_R6/include/root -I/Users/turany/development/install/RC_may16_R6/include -I/Users/turany/development/install/RC_may16_R6/include Pixel.h PixelContFact.h PixelDigitize.h PixelDigiPar.h PixelDigiSource.h PixelDigiBinSource.h PixelDigiWriteToFile.h PixelDigiWriteToBinFile.h PixelFindHits.h PixelFindTracks.h PixelFitTracks.h PixelGeo.h PixelGeoPar.h PixelEventHeader.h PixelPoint.h PixelDigi.h PixelHit.h PixelTrack.h PixelPayload.h PixelLinkDef.h
