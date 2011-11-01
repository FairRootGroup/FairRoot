#!/bin/bash

# The relocate script exchange all occurence of NewDetector or NEWDETECTOR
# by the name given by the first parameter. If the detector is for example 
# the Trd of the Cbm experiment a good name is CbmTrd. Normaly one should
# use the naming convention of the experiment.

#set -xv

if [ $# -ne 1 ]; then
  echo "Please call the script with the name of the detector."
  echo "The script will exchange all default names by the new name"
  exit 1
fi  

DetectorName=$1 
DetectorNameUpper=$(echo $DetectorName | tr [:lower:] [:upper:])

for i in $(ls NewDetector*); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/NewDetector/$DetectorName/")
  mv $oldfile $newfile
done 

find . -name "*" -exec sed -e "s/NewDetector/$DetectorName/g" -i "{}" ";"
find . -name "*" -exec sed -e "s/NEWDETECTOR/$DetectorNameUpper/g" -i "{}" ";"

#set +xv