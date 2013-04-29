#!/bin/bash
#linux_flavour=$(head -n 1 /etc/issue|tr '\\' ' '|awk '{gsub("\"","",$0);print $0}')
linux_flavour=$(sed '/^$/d' /etc/issue | head -n 1 | tr  '\\' ' '|awk '{gsub("\"","",$0);print $0}')
system=$(uname -m)
same_system=1

echo "System during compilation: $Linux_Flavour_"
echo "                           $System_"
echo "System now               : $linux_flavour"
echo "                           $system"

if [ ! "$linux_flavour" = "$Linux_Flavour_" ]; then
  echo "You try to run the software on a different"
  echo "linux flavour than it was compuiled on."
  echo "This is normaly a serious error, so we stop"
  echo "the execution at this point."
  echo "If you know what you do you can change the"
  echo "config.sh script to bypass this security issue."
  same_system=0
fi
if [ ! "$system" = "$System_" ]; then
  echo "You try to run the software on a different"
  echo "linux flavour than it was compuiled on."
  echo "This is normaly a serious error, so we stop"
  echo "the execution at this point."
  echo "If you know what you do you can change the"
  echo "config.sh script to bypass this security issue."
  same_system=0
fi

export same_system
