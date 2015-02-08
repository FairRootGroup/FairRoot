export FAIRROOTPATH=/opt/ocean/FairRootInst
export SIMPATH=/opt/ocean/FairSoftInst
export FAIRSHIP=/opt/ship/FairShip
export FAIRSHIP_BLD=/opt/ship/FairShip/build
export PYTHONPATH+=:$FAIRSHIP/python:$FAIRSHIP_BLD/python:$SIMPATH/lib:$SIMPATH/lib/Geant4

if [ -f $SIMPATH/bin/thisroot.sh ] ; then
  . $SIMPATH/bin/thisroot.sh
fi
