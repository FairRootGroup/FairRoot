CMake {#cmake}
=====

CMake for Consuming Projects
----------------------------

Most of the typical usage of the CMake related APIs
of FairRoot can be seen in 
`templates/project_stl_containers/CMakeLists.txt`.

Also many CMake related tooling that was shipped in
earlier releases is (or will) be available via
[FairCMakeModules](https://github.com/FairRootGroup/FairCMakeModules),
and is documented there.

### fairroot_check_root_cxxstd_compatibility()

This CMake function checks whether the C++ level of the
calling project matches with the level that ROOT was configured.
If it doesn't match, a warning is generated.
It it part of `ROOTMacros.cmake`.

Typical usage:

```cmake
find_package2(PUBLIC ROOT REQUIRED)
include(ROOTMacros)
fairroot_check_root_cxxstd_compatibility()
```

cmake Directory Structure
=========================

Steering classes for the `cmake` software that manages the build processes of the FairRoot software.

* *modules* directory stores the functions responsible for the identification of the packages that FairRoot depends on;
* *scripts* folder stores the functions that are checking the system requirements;
