#!/bin/bash

# The script compares files with the same name from two different directories.
# The names of the files are defined in the scripts, the names of the two different
# directories are passed as parameters when executing the script.
# The listed files are produced when executing the test suite of FairRoot
# The script immediately fails if a difference between files is found
# The actaul comparison is done using a ROOT macro which comapares the leaves of
# the ROOT tree ony by one.

if [[ "$#" -ne 2 ]]; then
  echo "Wrong number of arguments"
  echo "The script expects two directories as arguments" 
  exit 1 
fi

dir1=$1
dir2=$2

files=( 
simulation/Tutorial1/macros/tutorial1_TGeant4_pions.mc_p2.000_t0_n1.root
simulation/Tutorial1/macros/tutorial1_TGeant4_pions.mc_p2.000_t0_n10.root
simulation/Tutorial1/macros/tutorial1_pythia8_TGeant4_pions.mc_p2.000_t0_n10.root
simulation/Tutorial1/macros/tutorial1_pythia6_TGeant4_pions.mc_p2.000_t0_n10.root
simulation/Tutorial1/macros/tutorial1_urqmd_TGeant4.mc.root

simulation/Tutorial2/macros/tutorial2_pions.mc_p2.000_t0_n10.root
simulation/Tutorial2/macros/tutorial2_pions.mc_p2.000_t0_n10.sg1.root
simulation/Tutorial2/macros/tutorial2_pions.mc_p2.000_t0_n20.sg2.root
simulation/Tutorial2/macros/tutorial2_pions.mc_p2.000_t0_n130.bg.root
#simulation/Tutorial2/macros/digis.mc.root
#simulation/Tutorial2/macros/digis.mix.mc.root

simulation/Tutorial4/macros/data/testrun_align_TGeant4.root
simulation/Tutorial4/macros/data/testreco_align_TGeant4.root
#simulation/Tutorial4/macros/data/test.ana.root

simulation/rutherford/macros/data/test_TGeant4.mc.root
simulation/rutherford/macros/data/test1_TGeant4.mc.root

advanced/propagator/macros/prop.mc.root
#advanced/propagator/macros/prop.rk.cal.root

advanced/Tutorial3/macro/data/testrun_TGeant4.root
advanced/Tutorial3/macro/data/testdigi_TGeant4.root
advanced/Tutorial3/macro/data/testreco_TGeant4.root
advanced/Tutorial3/macro/data/testDiRePr_TGeant4.root
#advanced/Tutorial3/macro/data/testrecotimebased_TGeant4.root

#MQ/serialization/data_io/testinput1.root
#MQ/serialization/data_io/outputEx1Test.root
#MQ/serialization/data_io/testinput2.root
#MQ/serialization/data_io/outputEx2Test.root
#MQ/pixelDetector/macros/pixel_TGeant4.mc.root
#MQ/pixelDetector/macros/pixel_TGeant4.digi.root
#MQ/pixelDetector/macros/pixel_TGeant4.digiToBin.root
#MQ/pixelDetector/macros/MQ.pixel_TGeant4.hits.root
#MQ/pixelSimSplit/run/MQ.simulation_TGeant4.data.root
)

for i in "${files[@]}"; do
  file1=$dir1/$i
  file2=$dir2/$i

  root -l -b -q "$VMCWORKDIR/scripts/TreeCompareAuto.C(\"$file1\", \"$file2\")"
  bla=$?
  if [ "$bla" != "0" ]; then
    echo "Files $file1 and $file2 are different"
    exit 1
  else
    echo "Files $file1 and $file2 are identical"
  fi
done
