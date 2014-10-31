#!/bin/csh
set linux_flavour=`lsb_release -sd | sed -e 's/^"//' -e 's/"$//'`
set system=`uname -m`
setenv same_system 1

echo "System during compilation: $Linux_Flavour_"
echo "                           $System_"
echo "System now               : $linux_flavour"
echo "                           $system"

if ( "$linux_flavour" != "$Linux_Flavour_" ) then
  echo "You try to run the software on a different"
  echo "linux flavour than it was compiled on."
  echo "This is normaly a serious error, so we stop"
  echo "the execution at this point."
  echo "If you know what you do you can change the"
  echo "config.csh script to bypass this security issue."
  setenv same_system 0
endif
if ( "$system" != "$System_" ) then
  echo "You try to run the software on a different"
  echo "linux architecture than it was compiled on."
  echo "This is normaly a serious error, so we stop"
  echo "the execution at this point."
  echo "If you know what you do you can change the"
  echo "config.csh script to bypass this security issue."
  setenv same_system 0
endif
