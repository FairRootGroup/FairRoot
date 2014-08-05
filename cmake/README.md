cmake
========

Steering classes for the `cmake` software that manages the build processes of the FairRoot software.

* *modules* directory stores the functions responsible for the identification of the packages that FairRoot depends on;
* *scripts* folder stores the functions that are checking the system requirements;
* *cuda* contains cmake modules to find the CUDA Toolkit (http://www.nvidia.com/object/cuda_home_new.html) enabling parallel computations on the NVIDIA GPUs;
* *checks* to test the cxx11 compatibility.