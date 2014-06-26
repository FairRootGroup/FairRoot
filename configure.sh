#!/bin/bash 
#
# CBM package compilation script
# m.al-turany@gsi.de, June 2006
# protopop@jlab.org, June 2006
# update of the script
# include debug version and 
# intel compiler switches
# f.uhlig@gsi.de, July 2007

# debug options on :set -xv
# debug options off:set +xv
# 
set +xv

# unset ROOTSYS. If it is set this can make problems when compiling Geant3
unset ROOTSYS


#Clean the enviroment
unset ROOTBUILD
unset THREAD
unset ZLIB
unset LZMA
unset OPENGL
unset MYSQL
unset ORACLE
unset PGSQL
unset SQLITE
unset QTDIR
unset SAPDB
unset RFIO
unset CASTOR
unset GFAL
unset GSL
unset HDFS
unset PYTHIA6
unset PYTHIA8
unset FFTW3
unset CFITSIO
unset GVIZ
unset PYTHONDIR
unset DCACHE
unset CHIRP
unset DNSSD
unset AVAHI
unset ALIEN
unset ASIMAGE
unset LDAP
unset GLOBUS_LOCATION
unset GLITE
unset MEMSTAT
unset MONALISA
unset SRP
unset SSL
unset AFS
unset ROOFIT
unset MINUIT2
unset TABLE
unset XMLDIR
unset ROOTDICTTYPE

export SIMPATH=$PWD

# define the logfile
datum=$(date +%d%m%y_%H%M%S)
logfile=$PWD/Install_$datum.log
logfile_lib=$PWD/libraries_$datum.log
echo "The build process for the external packages for the FairRoot Project was started at" $datum | tee -a $logfile

source scripts/functions.sh

# check if there was a parameter given to the script.
# if yes then use some standard parameters and don't
# show the menues. Else get some input interactively.
if [ $# == "0" ];
then

  source scripts/menu.sh
 
else
  if [ $1 = "automatic" ];
  then
    compiler=gcc
    debug=yes
    optimize=no
    geant4_download_install_data_automatic=yes
    geant4_install_data_from_dir=no
    build_python=no
    export SIMPATH_INSTALL=$PWD/installation
  elif [ $1 = "grid" ];
  then
    compiler=gcc
    debug=no
    optimize=no
    geant4_download_install_data_automatic=no
    geant4_install_data_from_dir=yes
    build_python=no
    SIMPATH_INSTALL=$PWD/installation
    build_for_grid=yes
  else
    echo "Parameter given to the script is not known."
    echo "The only valid parameter up to now is automatic."
    echo "Stop execution at this point."
    exit 42
  fi   
fi  

if [ "$build_python" = "yes" ]; 
then
  export BUILD_PYTHON=TRUE
else
  export BUILD_PYTHON=FALSE
fi

# check the architecture automatically
# set the compiler options according to architecture, compiler
# debug and optimization options
source scripts/check_system.sh

echo "The following parameters are set." | tee -a $logfile
echo "System              : " $system | tee -a $logfile
echo "C++ compiler        : " $CXX | tee -a $logfile
echo "C compiler          : " $CC | tee -a $logfile
echo "Fortran compiler    : " $FC | tee -a $logfile
echo "CXXFLAGS            : " $CXXFLAGS | tee -a $logfile
echo "CFLAGS              : " $CFLAGS | tee -a $logfile
echo "FFLAGS              : " $FFLAGS | tee -a $logfile
echo "Compiler            : " $compiler | tee -a $logfile
echo "Fortran compiler    : " $FC
echo "Debug               : " $debug | tee -a $logfile
echo "Optimization        : " $optimize | tee -a $logfile
echo "Platform            : " $platform | tee -a $logfile
echo "Architecture        : " $arch | tee -a $logfile
echo "G4System            : " $geant4_system | tee -a $logfile
echo "g4_data_files       : " $geant4_data_files | tee -a $logfile
echo "g4_get_data         : " $geant4_get_data | tee -a $logfile
echo "Number of parallel    " | tee -a $logfile
echo "processes for build : " $number_of_processes | tee -a $logfile
echo "Installation Directory: " $SIMPATH_INSTALL | tee -a $logfile

check=1

# set the versions of packages to be build
source scripts/package_versions.sh

# Now start compilations with checks

######################## CMake ################################
# This is only for safety reasons. If we find a machine where
# cmake is not installed, we install cmake and add the path 
# to the environment variable PATH

if [ "$check" = "1" ];
then
  source scripts/install_cmake.sh
fi

############ Google Test framework ###############################

if [ "$check" = "1" ];
then
  source scripts/install_gtest.sh 
fi

############ GNU scientific library ###############################

if [ "$check" = "1" ];
then
  source scripts/install_gsl.sh 
fi

############ Boost libraries ###############################

if [ "$check" = "1" ];
then
  source scripts/install_boost.sh 
fi

##################### Pythia 6 #############################################

if [ "$check" = "1" ];
then
  source scripts/install_pythia6.sh 
fi

##################### HepMC ## #############################################

if [ "$check" = "1" ];
then
  source scripts/install_hepmc.sh 
fi

##################### Pythia 8 #############################################

if [ "$check" = "1" ];
then
  source scripts/install_pythia8.sh 
fi

##################### XercesC #############################################

if [ "$build_python" = "yes" ]; 
then
  if [ "$check" = "1" ];
  then
    source scripts/install_xercesc.sh
  fi
fi
  
##################### GEANT 4 #############################################

if [ "$check" = "1" ];
then
  source scripts/install_geant4.sh
fi

###################### GEANT 4 Data ########################################

if [ "$check" = "1" -a "$geant4_install_data_from_dir" = "yes" ];
then
  source scripts/install_geant4_data.sh
fi

##################### ROOT #############################################

if [ "$check" = "1" ];
then
  source scripts/install_root.sh
fi

##################### G4Py #############################################

if [ "$build_python" = "yes" ]; 
then
  if [ "$check" = "1" ];
  then
    source scripts/install_g4py.sh
  fi
fi

##################### Pluto #############################################

if [ "$check" = "1" ];
then
  source scripts/install_pluto.sh
fi

##################### Geant 3 VMC #############################################

if [ "$check" = "1" ];
then
  source scripts/install_geant3.sh
fi

##################### VGM #############################################

if [ "$check" = "1" ];
then
    source scripts/install_vgm.sh
fi

##################### Geant 4 VMC #############################################

if [ "$check" = "1" ];
then
  source scripts/install_geant4_vmc.sh
fi

##################### Millepede #############################################

if [ "$check" = "1" ];
then
  source scripts/install_millepede.sh
fi

##################### ZeroMQ ##################################################

if [ "$check" = "1" ];
then
  source scripts/install_zeromq.sh
fi

if [ "$check" = "1" ];
then
    echo "*** End installation of external packages without Errors***"  | tee -a $logfile
    echo ""
    if [ "$install_cmake" = "yes" ]; then
      echo "During the installation a new version of CMake has been installed in $SIMPATH_INSTALL/bin."
      echo "Please add this path to your environment variable PATH to use this new version of CMake."
    fi
    exit 0    
else
    echo "*** End installation of external packages with Errors***"  | tee -a $logfile
    exit 42
fi	
