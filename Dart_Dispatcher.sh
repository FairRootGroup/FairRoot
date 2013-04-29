#!/bin/bash

REV=$1

# Start the process in the background
/misc/cbmsim/SVN/CONTINUOUS/fairbase/Dart_Continuous.sh $REV > $HOME/FairBase_Continuous.log 2>&1 &
