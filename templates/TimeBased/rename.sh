#!/bin/bash

# The rename script exchange all occurence of My or My
# by the name given by the first parameter. If the detector is for example 
# the Trd of the Cbm experiment and the class should work on the Digi data level
# a good name for the first parameter is CbmTrdDigi. 
# Normaly one should use the naming convention of the experiment.
# Also the filenames any many more things are changed automatically. In the
# end there are only some small changes which have to be done by hand.

#set -xv

if [ $# -ne 1 ]; then
  echo "Please call the script with four parameters. The first one is the"
  echo "name of the detector. The second is the name of the project. This"
  echo "name can be found in the main CMakeLists.txt as argument for"
  echo "Project(<ProjectName>)). The third parameter is the prefix in front"
  echo "the class names. For CBM this is for example Cbm, for Panda Pnd."
  echo "If you're not sure check in already existing detectors."
  echo "The script will exchange all default names by the new name"
  exit 1
fi  

DataLevelName=$1
DataLevelNameUpper=$(echo $DataLevelName | tr [:lower:] [:upper:])

for i in $(ls My*); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/My/$DataLevelName/")
  cp $oldfile $newfile
done 

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

find . -name "*.h" -exec sed -e "s/MyDataClass/$DataLevelName/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/MyDataClass/$DataLevelName/g" $sedstring "{}" ";"
find . -name "*.h" -exec sed -e "s/My/$DataLevelName/g" $sedstring "{}" ";"
find . -name "*.h" -exec sed -e "s/MY/$DataLevelNameUpper/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/My/$DataLevelName/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/MY/$DataLevelNameUpper/g" $sedstring "{}" ";"

#if [ -d .svn ]; then  
  echo "Please copy the newly created files to your directory."
  echo "Add the names of the new source files to the list of files in the CMakeLists.txt and the Linkdef file."
  echo "##"
#fi

#set +xvx