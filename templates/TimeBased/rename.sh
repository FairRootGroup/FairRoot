#!/bin/bash

# The rename script exchange all occurence of My or MY and MyDataClass
# by the name given by the first parameter. If the detector is for example 
# the Trd of the Cbm experiment and the class should work on the Digi data level
# a good name for the first parameter is CbmTrdDigi. 
# Normaly one should use the naming convention of the experiment.
# Also the filenames any many more things are changed automatically. In the
# end there are only some small changes which have to be done by hand.

#set -xv

if [ $# -ne 1 ]; then
  echo "Please call the script with one parameter. The parameter should be the"
  echo "complete name of the data level the classes should work on."
  echo "If the tasks should write to the Digi data level of the Trd detector of"
  echo "the Cbm Experiment the correct parameter would be CbmTrdDigi."
  exit 1
fi  

DataLevelName=$1
DataLevelNameUpper=$(echo $DataLevelName | tr [:lower:] [:upper:])

arch=`uname -s | tr '[A-Z]' '[a-z]'`
case "$arch" in
    linux)
        sedstring="-i "
        ;;
    darwin)
        sedstring="-i ''"
        ;;
    *)
        echo "Platform not supported"
        exit 1
        ;;
esac

for i in $(ls My*.cxx); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/My/$DataLevelName/")
  cp $oldfile $newfile
  sed -e "s/MyDataClass/$DataLevelName/g" $sedstring $newfile
  sed -e "s/My/$DataLevelName/g" $sedstring $newfile
  sed -e "s/MY/$DataLevelNameUpper/g" $sedstring  $newfile
done 


for i in $(ls My*.h); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/My/$DataLevelName/")
  cp $oldfile $newfile
  sed -e "s/MyDataClass/$DataLevelName/g" $sedstring $newfile
  sed -e "s/My/$DataLevelName/g" $sedstring $newfile
  sed -e "s/MY/$DataLevelNameUpper/g" $sedstring $newfile
done

echo "Please move the newly created files starting with $DataLevelName to your directory."
echo "Add the names of the new source files to the list of files in the CMakeLists.txt and the Linkdef file."
echo "##"

#set +xvx