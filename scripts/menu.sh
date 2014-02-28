#!/bin/bash

cache="config.cache"

if test -f $cache; then
   use_cache=y
   clear
   echo
   echo "Use these cached settings: "
   echo
   cat $cache
   echo
   read -p 'Ok [Y/n]: ' use_cache 
   if test ! "x$use_cache" = "xn"; then
      . $cache
      return
   else
      rm -f $cache
   fi
fi

clear
echo
echo "Which compiler you want to use to compile the external packages?"
PS3='Please enter a choice from the above menu: '

select CHOICE in "GCC (Linux, Solaris and Mac OSX)" "Intel Compiler (Linux)" "CC (Solaris)" "Portland Compiler" "Clang" Quit
do
  case "$CHOICE" in
               Quit) exit			
                     ;;
              "GCC (Linux, Solaris and Mac OSX)") 
                     compiler=gcc
                     break
                     ;;
   "Intel Compiler (Linux)") 
                     compiler=intel
                     break
                     ;;
                "CC (Solaris)") 
                     compiler=CC
                     break
                     ;;
                "Portland Compiler") 
                     compiler=PGI
                     break
                     ;;
                "Clang") 
                     compiler=Clang
                     break
                     ;;
                 "") echo This value is not valid. Hit Enter to see menu again!
                     continue
                     ;;
   esac
done

echo compiler=$compiler >> $cache

clear
echo
echo "Do you want to compile the external packages with or without debug"
echo "information or with optimization?"
PS3='Please enter a choice from the above menu: '

select CHOICE in "No Debug Info" "Debug Info" "Optimize" Quit
do
  case "$CHOICE" in
              Quit) exit			
                    ;;
   "No Debug Info") debug=no
                    optimize=no
                    break
                    ;;
      "Debug Info") debug=yes
                    optimize=no
                    break
                    ;;
        "Optimize") debug=no
                    optimize=yes
                    break
                    ;;
                "") echo This value is not valid. Hit Enter to see menu again!
                    continue
                    ;;
   esac
done

echo debug=$debug >> $cache
echo optimize=$optimize >> $cache

clear
echo
echo "Would you like to install the additionally available data files"
echo "the GEANT4 package?"
echo "To do so you need either a internet conection (Internet) or you"
echo "have to provide the files in the transport subdirectory (Directory)."
PS3='Please enter a choice from the above menu: '

select CHOICE in "Don't install" "Internet" "Directory" Quit
do
  case "$CHOICE" in
              Quit) exit			
                    ;;
   "Don't install") geant4_download_install_data_automatic=no 
		    geant4_install_data_from_dir=no   
                    break
                    ;;
      "Internet")   geant4_download_install_data_automatic=yes
                    geant4_install_data_from_dir=no   
                    break
                    ;;
       "Directory") geant4_download_install_data_automatic=no
                    geant4_install_data_from_dir=yes   
                    break
                    ;;
                "") echo This value is not valid. Hit Enter to see menu again!
                    continue
                    ;;
   esac
done

echo geant4_download_install_data_automatic=$geant4_download_install_data_automatic >> $cache
echo geant4_install_data_from_dir=$geant4_install_data_from_dir >> $cache

clear

question=true
writable_dir=true
while $question; do
  clear
  if ! $writable_dir; then
    echo "You don't have write permissions for $SIMPATH_INSTALL"
  fi  
  echo 'Please define a directory for the installation of the external packages.'
  echo 'An installation in the source directory is not possible any longer.'
  echo 'Please enter the full path of the installation directory'     
  echo ''
  read -p 'path: ' SIMPATH_INSTALL 
  clear
    # expand variables, which could be in the filepath. A example is if $PWD is in the path
  eval SIMPATH_INSTALL=$SIMPATH_INSTALL
  echo "Is $SIMPATH_INSTALL the correct path?"
  PS3='Please enter a choice from the above menu: '
  
  select CHOICE in "No" "Yes" Quit                            
  do
  case "$CHOICE" in
      Quit) exit
          ;;
      "No") question=true
          break
          ;;
      "Yes") question=false
          break
          ;;
      "" ) echo This value is not valid. Hit Enter to see menu again!
          continue
          ;;
  esac
  done
    #check if the user can write to the installation path
  mkdir -p $SIMPATH_INSTALL
  if [ $? -ne 0 ]; then
      question=true
      writable_dir=false
  fi  
done                                                                                                                                                                                                                                       
     

echo SIMPATH_INSTALL=$SIMPATH_INSTALL >> $cache

