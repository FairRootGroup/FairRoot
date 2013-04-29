#!/bin/bash

# The rename script exchange all occurence of NewDetector or NEWDETECTOR
# by the name given by the first parameter. If the detector is for example 
# the Trd of the Cbm experiment a good name is CbmTrd. Normaly one should
# use the naming convention of the experiment.
# Also the filenames any many more things are changed automatically. In the
# end there are only some small changes which have to be done by hand.

#set -xv

if [ $# -ne 1 ]; then
  echo "********"
  echo "Please call the script with one parameter, which is the name of the task."
  echo "The script will exchange all default names by the new name"
  echo "********"
  exit 1
fi  

TaskName=$1 
TaskNameUpper=$(echo $TaskName | tr [:lower:] [:upper:])

#ProjectName=$(echo $2 | tr [:lower:] [:upper:])
#ProjectSourceDir=${ProjectName}_SOURCE_DIR
#RelativeDir=$(basename $PWD)
#Prefix=$3

for i in $(ls NewTask*); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/NewTask/$TaskName/")
  mv $oldfile $newfile
done 

arch=`uname -s | tr '[A-Z]' '[a-z]'`
case "$arch" in
    linux)
        sedstring="-i "
        ;;
    darwin)
        sedstring="-i .bak"
        ;;
    *)
        echo "Platform not supported"
        exit 1
        ;;
esac

find . -name "*.h" -exec sed -e "s/NewTask/$TaskName/g" $sedstring "{}" ";"
find . -name "*.h" -exec sed -e "s/NEWTASK/$TaskNameUpper/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/NewTask/$TaskName/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/NEWTASK/$TaskNameUpper/g" $sedstring "{}" ";"

case "$arch" in
    darwin)
      rm *.bak           
      ;;
    *)
      echo "Platform not supported"
      exit 1  
      ;;
esac
                                                
echo "********"
echo "Edit the CMakeLists.txt and the LinkDef file in the directory."
echo "Add in both files the new task."
echo "********"

#set +xvx