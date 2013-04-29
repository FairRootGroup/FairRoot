#!/bin/bash

# small program to check the memory consumption in given intervals
# It uses the information extracted from </proc/pid/status> and stores
# the data in simple text files for later usage.
# Start script with the following parameters
# $1: The pid of the job which should be controlled
# $2: The time in seconds between the action to be done
# $3: Name of the file which is used for the output of the simulation

# Used system infrmation
#VmSize: The size of the virtual memory allocated to the process
#VmSize: Virtual memory size

#VmLck: The amount of locked memory
#VmRSS: The amount of memory mapped in RAM ( instead of swapped out )
#VmData: The size of the Data segment
#VmStk: The stack size
#VmExe: The size of the executable segment
#VmLib: The size of the library code
#VmPTE: Size of the Page Table entry

#VmPeak: Peak virtual memory size.
#        max memory your program seems to take up (counting loaded shared libraries as part of the program)
#        peak of virtual memory

#VmHWM: Peak resident set size ("high water mark").
#       how much ram was actually devoted to your program
#       peak of physical memory.

pid=$1 
sleeptime=$2
filename=$3

check=true

echo -e "Date\t DateInSeconds\t vmPeak\t vmSize\t vmLck\t vmHWM\t vmRSS\t vmData\t vmStk\t vmExe\t vmLib\t vmPTE\t filesize\t CPU\t" > memory_consumption_$pid.txt

while $check; do

  datestring=$(date +%H:%M:%S) 
  dateseconds=$(date +%s)
  
  result=$(cat /proc/$pid/status | grep ^Vm)

  vmPeak=$(echo $result | cut -f 2-3 -d" ")
  vmSize=$(echo $result | cut -f 5-6 -d" ")
  vmLck=$(echo $result | cut -f 8-9 -d" ")
  vmHWM=$(echo $result | cut -f 11-12 -d" ")
  vmRSS=$(echo $result | cut -f 14-15 -d" ")
  vmData=$(echo $result | cut -f 17-18 -d" ")
  vmStk=$(echo $result | cut -f 20-21 -d" ")
  vmExe=$(echo $result | cut -f 23-24 -d" ")
  vmLib=$(echo $result | cut -f 26-27 -d" ")
  vmPTE=$(echo $result | cut -f 29-30 -d" ")

  if [ -e $filename ]; then
    filesize=$(ls -la $filename | cut -f 5 -d" ")
  else
    filesize=0
  fi
  cpu=$(ps -p $pid -o %cpu=)

  echo "$datestring $dateseconds $vmPeak $vmSize $vmLck $vmHWM $vmRSS $vmData $vmStk $vmExe $vmLib $vmPTE $filesize $cpu" >> memory_consumption_$pid.txt

  # if pid does not exist any longer (process ends) leave the loop
  if [ ! -e /proc/$pid/status ]; then
    echo "There is no entry for pid $pid in /proc any longer."
    echo "The program stops now."
    check=false;
  fi

  sleep $sleeptime

done

