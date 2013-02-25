#!/bin/bash

##################################################################
# set the source and the build directory for ctest
# change this directories to your needs
# set the SIMPATH to your needs
# LINUX_FLAVOUR should be set to the distribution you are using
# eg Debian, SuSe etc.
# For example
# export SIMPATH=/misc/cbmsoft/Debian3.1/new
# export BUILDDIR=/misc/uhlig/test/mytest2/build_cbmroot
# export SOURCEDIR=/misc/uhlig/test/mytest2/cbmroot
# export LINUX_FLAVOUR=Debian
##################################################################
export PATH=/usr/lib/icecc/bin:$PATH
export SIMPATH=/misc/cbmsoft/Etch64/jan12
export BUILDDIR=/misc/cbmsim/SVN/CONTINUOUS/build_fairbase
export SOURCEDIR=/misc/cbmsim/SVN/CONTINUOUS/fairbase
export LINUX_FLAVOUR=Etch64
export FAIRSOFT_VERSION=jan12
###################################################################

cd $SOURCEDIR


# checks the content of  the queue. The information is stored
# in the file Dispatcher_queue.txt.
# If there is no PID in the file except the own one start
# immediately. If there are already PIDs in the file wait until
# the PID in front of the own pid finishes. 
# This active waiting is done by checking in the /proc filesystem
# if there is a directory for the PID. If not go on with the process.
# If the directory still exists sleep for some time and then check
# again.

OwnPid=$$

# How many jobs are waiting (This is only relevant for the first job)
QueueLength=$(cat Dispatcher_queue.txt | wc -l)

# Get the PID of the last job in the queue. This is the job
# i have to wait for
WaitPid=$(tail -1 Dispatcher_queue.txt)

# Add my own PID at the end of the queue.
echo $OwnPid >> Dispatcher_queue.txt

# wait until the WaitPid isn't any longer in the proc system
echo "QueueLength: $QueueLength"
cat Dispatcher_queue.txt
if [ $QueueLength -eq 0 ]; then
  echo "There is no PID to wait for, so I start immediately."
else
  echo "The PID I have to wait for is $WaitPid. Start after this process has finsihed."
  while [ -d /proc/$WaitPid ]; do
    sleep 30
  done
fi

echo "Start Pid $OwnPid"

export ctest_model=Continuous

export REVISION="-r $1"

# extract information about the system and the machine and set
# environment variables used by ctest
SYSTEM=$(uname -o)-$(uname -m)
if test -z $CXX ; then
  COMPILER=gcc;
  GCC_VERSION=$(gcc -dumpversion)
else
  COMPILER=$CXX;
  GCC_VERSION=$($CXX -dumpversion)
fi
export LABEL1=${LINUX_FLAVOUR}-$SYSTEM-$COMPILER$GCC_VERSION-fairsoft_$FAIRSOFT_VERSION
export LABEL=$(echo $LABEL1 | sed -e 's#/#_#g')
export SITE=$(hostname -f)

echo "************************"
/bin/date
echo "LABEL: " $LABEL
echo "SITE: " $SITE
echo "************************"

# get the number of processors 
export number_of_processors=$(cat /proc/cpuinfo | grep processor | wc -l)
#export number_of_processors=40

/usr/bin/ctest -S $SOURCEDIR/FairBase_test.cmake -V --VV


#Remove process pid from Dispacher_queue.txt
sed "/$OwnPid/d" -i'' Dispatcher_queue.txt

echo "Finish Pid $OwnPid"

# For safety reasons loop over all PIDs in Dispatcher_queue.txt and remove
# all PIDs in the file which doesn't exist any longer.
COUNTER=1
QueueLength=$(cat Dispatcher_queue.txt | wc -l)
let QueueLength=QueueLength+1
while [  $COUNTER -lt $QueueLength ]; do
  CheckPid=$(head -$COUNTER Dispatcher_queue.txt | tail -1)
  if [ ! -d /proc/$CheckPid ]; then
    sed "/$CheckPid/d" -i'' Dispatcher_queue.txt
  fi
  let COUNTER=COUNTER+1
done
            
exit 
