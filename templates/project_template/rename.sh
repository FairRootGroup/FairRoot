#!/bin/bash

# The script will rename all files and the code accoringly to the given
# parameters. 

if [ $# -ne 3 ]; then
  echo "Please call the script with three parameters. The first one is the"
  echo "name of the project. The second one is the prefix in front of"
  echo "the class names. and some directories. So this second parameter"
  echo "shouldn't be to long. The third parameter is the name of the"
  echo "detector you want to implement."
  echo "As an example the if you want to create a project for the Panda"
  echo "experiment and you want to implement a Straw Tube Tracker (stt)"
  echo "you would call the script in the following way."
  echo "./rename.sh Panda Pnd stt" 
  exit 1
fi  

ProjectName=$1
ProjectNameUpper=$(echo $ProjectName | tr [:lower:] [:upper:])

Prefix=$2
PrefixLower=$(echo $Prefix | tr [:upper:] [:lower:])
Prefix=$(echo ${PrefixLower:0:1} | tr  '[a-z]' '[A-Z]')${PrefixLower:1}

DetectorName=$3
DetectorNameUpper=$(echo $DetectorName | tr [:lower:] [:upper:])
DetectorNameLower=$(echo $DetectorName | tr [:upper:] [:lower:])
DetectorName=$(echo ${DetectorNameLower:0:1} | tr  '[a-z]' '[A-Z]')${DetectorNameLower:1}

arch=`uname -s | tr '[A-Z]' '[a-z]'`
case "$arch" in
    linux)
        sedstring="-i "
        ;;
    darwin)
        sedstring="-i.bak"
        ;;
    *)
        echo "Platform not supported"
        exit 1
        ;;
esac

# Rename directories
for i in $(find . -type d -name "MyProj*"); do
   olddir=$i
   newdir=$(echo $olddir | sed "s/MyProj/$Prefix/")
   mv $olddir $newdir
done

for i in $(find . -type d -name NewDetector); do
  olddir=$i
  newdir=$(echo $olddir | sed "s/NewDetector/$DetectorNameLower/")
  mv $olddir $newdir
done

# Change CMakeLists.txt accordingly
sed -e "s/MyProj/$Prefix/g" $sedstring CMakeLists.txt
sed -e "s/MYPROJ/$ProjectNameUpper/g" $sedstring CMakeLists.txt
sed -e "s/NewDetector/$DetectorNameLower/g" $sedstring CMakeLists.txt

for i in $(find . -type f -name CMakeLists.txt); do
  sed -e "s/MyProj/$Prefix/g" $sedstring $i
  sed -e "s/MYPROJ/$ProjectNameUpper/g" $sedstring $i
  sed -e "s#/NewDetector#/$DetectorNameLower#g" $sedstring $i
  sed -e "s/NewDetector/$Prefix$DetectorName/g" $sedstring $i
  sed -e "s/My/$Prefix/g" $sedstring $i
done

# Change file names
for i in $(find . -type f -name "MyProj*"); do
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/MyProj/$Prefix/")
  mv $oldfile $newfile
  sed -e "s/MyProj/$Prefix/g" $sedstring $newfile
  sed -e "s/NewDetector/$Prefix$DetectorName/g" $sedstring $newfile
done

for i in $(find . -type f -name "NewDetector*"); do
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/NewDetector/$Prefix$DetectorName/")
  mv $oldfile $newfile
  sed -e "s/NewDetector/$Prefix$DetectorName/g" $sedstring $newfile
  sed -e "s/MyProj/$Prefix/g" $sedstring $newfile
done

for i in $(find . -type f -name "My*"); do
  oldfile=$i
  newfile=$(echo $oldfile | sed "s/My/$Prefix/")
  mv $oldfile $newfile
  sed -e "s/My/$Prefix/g" $sedstring $newfile
done

sed -e "s/MyProj/$Prefix/g" $sedstring ${Prefix}Data/MCStackLinkDef.h
sed -e "s/My/$Prefix/g" $sedstring passive/PassiveLinkDef.h
sed -e "s/My/$Prefix/g" $sedstring field/FieldLinkDef.h

sed -e "s/My/$Prefix/g" $sedstring macro/run_sim.C
sed -e "s/NewDetector/$Prefix$DetectorName/g" $sedstring macro/run_sim.C

sed -e "s/MyProj/$Prefix/g" $sedstring gconfig/g3Config.C
sed -e "s/MyProj/$Prefix/g" $sedstring gconfig/g4Config.C

find . -name "*.bak" -delete