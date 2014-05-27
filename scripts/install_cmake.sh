#!/bin/bash
# Script checks if the installed version of cmake is up-to-data

cmake_required_major_version=$(echo $CMAKEVERSION_REQUIRED | cut -d- -f2 | cut -d. -f1)
cmake_required_minor_version=$(echo $CMAKEVERSION_REQUIRED  | cut -d- -f2 |cut -d. -f2)
cmake_required_patch_version=$(echo $CMAKEVERSION_REQUIRED  | cut -d- -f2 |cut -d. -f3)
cmake_required_version=$(echo $CMAKEVERSION_REQUIRED  | cut -d- -f2)

cmake_version_string=$(cmake --version | sed -n 1p)
cmake_installed_major_version=$(echo $cmake_version_string | cut -d' '  -f3 | cut -d. -f1)
cmake_installed_minor_version=$(echo $cmake_version_string | cut -d. -f2)
cmake_installed_patch_version=$(echo $cmake_version_string | cut -d. -f3)
cmake_version=$(echo $cmake_version_string | cut -c15-)

if [ "$cmake_installed_patch_version" == "" ]; then
  # output of cmake 2.8 is 'cmake version 2.8.2'
  # output of cmake 2.6 is 'cmake version 2.6-patch 0'
  cmake_installed_patch_version=$(cmake --version | cut -c19)
fi

if [ $cmake_installed_major_version -gt $cmake_required_major_version ]; then
  install_cmake=no       
  echo "Found cmake version $cmake_version which is newer than the"| tee -a $logfile
  echo "required version $cmake_required_version in PATH"| tee -a $logfile
  echo "This version is okay. Don't install cmake as external package."| tee -a $logfile
elif [ "$cmake_installed_major_version" -eq "$cmake_required_major_version" -a  \
    "$cmake_installed_minor_version" -ge "$cmake_required_minor_version" ]; then
  if [ "$cmake_installed_patch_version" -ge "$cmake_required_patch_version" -o \
      "$cmake_installed_minor_version" -gt "$cmake_required_minor_version" ]; then
    install_cmake=no       
    echo "Found cmake version $cmake_version which is newer than the"| tee -a $logfile
    echo "required version $cmake_required_version in PATH"| tee -a $logfile
    echo "This version is okay. Don't install cmake as external package."| tee -a $logfile
  else
      install_cmake=yes    
      echo "Found cmake version $cmake_version which is older than the"| tee -a $logfile  
      echo "required version $cmake_required_version in PATH"| tee -a $logfile
      echo "This version is to old"| tee -a $logfile
      echo "install cmake as external package"| tee -a $logfile
  fi
else
  install_cmake=yes    
  echo "Found cmake version older than $cmake_required_version PATH"| tee -a $logfile
  echo "This version is to old"| tee -a $logfile
  echo "install cmake as external package"| tee -a $logfile
fi

if [ "$install_cmake" = "yes" ];
then
  if [ ! -d  $SIMPATH/basics/cmake ];
  then 
    cd $SIMPATH/basics
    if [ ! -e $CMAKEVERSION.tar.gz ];
    then
      echo "*** Downloading cmake sources ***"
      download_file $CMAKE_LOCATION/$CMAKEVERSION.tar.gz
    fi
    untar cmake $CMAKEVERSION.tar.gz
    if [ -d  $CMAKEVERSION ]; 
    then
      ln -s $CMAKEVERSION cmake
    fi
  fi 

  install_prefix=$SIMPATH_INSTALL

  checkfile=$install_prefix/bin/cmake    
  export PATH=$install_prefix/bin:$PATH:

  if (not_there CMake $checkfile)   
  then
    cd $SIMPATH/basics
    untar CMake $CMAKEVERSION.tar.gz
    ln -s $CMAKEVERSION cmake
    cd cmake
    ./bootstrap --prefix=$install_prefix --docdir=/share/doc/CMake --mandir=/share/man
    $MAKE_command -j $number_of_processes
    $MAKE_command install -j $number_of_processes
    check_success CMake $checkfile

    check=$? 
  fi
fi

if [ "$check" = "1" ];
then
  export PATH=$install_prefix/bin:$PATH
else
  echo "There was a problem installing cmake"
  echo "Stop the script at this point"    
  exit
fi

cd $SIMPATH

return 1
