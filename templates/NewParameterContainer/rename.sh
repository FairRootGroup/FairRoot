#!/bin/bash

# The rename script exchange all occurence of NewParameterContainer 
# or NEWPARAMETERCONTAINER by the name given by the first parameter. 

#set -xv

if [ $# -ne 1 ]; then
  echo "********"
  echo "Please call the script with one parameter, which is the name of the"
  echo "New parameter container."
  echo "The script will exchange all default names by the new name"
  echo "********"
  exit 1
fi  

ContainerName=$1 
ContainerNameUpper=$(echo $ContainerName | tr [:lower:] [:upper:])

for i in $(ls NewParameterContainer*); do 
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/NewParameterContainer/$ContainerName/")
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

find . -name "*.h" -exec sed -e "s/NewParameterContainer/$ContainerName/g" $sedstring "{}" ";"
find . -name "*.h" -exec sed -e "s/NEWPARAMETERCONTAINER/$ContainerNameUpper/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/NewParameterContainer/$ContainerName/g" $sedstring "{}" ";"
find . -name "*.cxx" -exec sed -e "s/NEWPARAMETERCONTAINER/$ContainerNameUpper/g" $sedstring "{}" ";"

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
echo "Edit the container factory File and add there the new container."
echo "Edit the newly created parameter container header file and define"
echo "a good title in the constructor."
echo "Edit also the CMakeLists.txt and LinkDef files." 
echo "Add in both files the new parameter container."
echo "********"

#set +xvx