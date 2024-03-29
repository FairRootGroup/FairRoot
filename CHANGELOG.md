# Changelog

All notable changes to FairRoot will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),

## 18.8.2 - 2023-03-01

### Bug fixes
* Fix wrong init order in eventdisplay.
* Fix GeoAssembly bounding box after alignment:
  * Use ROOT expert patch.
* Fix to obtain initial random seed from TRandom::GetSeed():
  * Replace TRandom3::GetSeed() with the GetSeed() from base class.
* Adopt new software versions:
  * Fix FindROOT.cmake to work with ROOT v6.30.00.
  * Adopt CMake policies up to 3.27.
  * Support yaml-cpp 0.8+.
  * Fix runtime error with XCode 13.3+.

### Other Notable Changes
* Software recongnition:
  * Implement fair-software.eu badges
  * Add codemeta.json in accordance with ESCAPE
  * Add config for zenodo.org

## 18.8.1 - 2023-02-24

### Breaking Changes
* The output folder name changed from 'folderName_0' to 'folderName'.
In the MT mode of Geant4 the folder names changed from 'folderName_1' and 'folderName_2' to 'folderName'.

### Bug fixes
* Check the return value of `source->InitUnpackers()`/`source->ReinitUnpackers()`
  in `FairRunOnline`. Stop run if `false` returned.
* Remove sink from Tutorial3/MQ/sampler.cxx.

### Other Notable Changes
* Allow running without output sink. In this case even persistent branches would not be stored anywhere.

## 18.8.0 - 2022-12-16

### Breaking Changes
* Move online related code into the new Online library
  * The special steering class FairRunOnline was moved from
    the Base into the Online library.
  * Also the MBS/LMD related source classes were moved to
    the new Online library.
  * If one of these classes are used in your code, you need
    to link against new target `FairRoot::Online`.
* Dropped `CheckCXX11Features` (This was also released in 18.6.8 and 18.4.8)
  * FairRoot assumes a recent compiler that fully supports C++17.
  * Remove the following things from your `CMakeLists.txt`:
    * ```cmake
      Set(CheckSrcDir "${FAIRROOTPATH}/share/fairbase/cmake/checks")`
      ```
    * ```cmake
      include(CheckCXX11Features)
      ```
    * ```cmake
      IF(HAS_CXX11_SHAREDPOINTER)
        Add_Definitions(-DHAS_SHAREDPOINTER)
      ENDIF(HAS_CXX11_SHAREDPOINTER)
      ```
  * If your C++ code depends on `HAS_SHAREDPOINTER` being set, rewrite it accordingly.
  * If any of your CMake code depends on `HAS_CXX11_*` being set, rewrite it accordingly.
  * If your code has specific C++ needs, consider CMake's `target_compile_features()`.
* Dropped `CHECK_EXTERNAL_PACKAGE_INSTALL_DIR`
  * Just remove it from your `CMakeLists.txt`.
* Dropped `USE_PATH_INFO` CMake option. It was an anti-pattern. Don't use it!
* Dropped `ROOT_GENERATE_ROOTMAP`. It was used on ROOT 5.x.
  * Rewrite your build system, if you still use it.
* `FairRootManager::Get{Tree,Folder}Name()` now return `const char *`.
  Do NOT `delete` the returned pointer!
* `FairRunSim::SetSimulationConfig()` now takes a
  `unique_ptr` instead of a raw pointer with unknown
  ownership.
* Some headers were cleaned up and now `#include` fewer
  other headers. You might have to add some `#includes`s
  in your code.
* Added a new build switch `BUILD_BASEMQ` for controlling whether `FairRoot::BaseMQ` and
  dependent targets are built (`FairRoot::FairMQ` and `FairRoot::ParMQ`). It is enabled
  by default and will now **require** its external package dependencies FairMQ and Boost.
* Boost serialization support for `FairTimeStamp`, `FairHit`, and `FairMCPoint` has been
  moved to the `FairRoot::BaseMQ` target to have `FairRoot::Base` no longer depend on
  Boost.Serialization. The user must opt-in to the previously baseline Boost serialization
  support by including one of the new headers, e.g. for `FairHit`:
  ```cpp
  #include <FairHit.h>
  #include <FairHitBoostSerializationSupport.h>
  ```
  There is also a convenience header `<FairBoostSerializationSupport.h>` which includes all
  class-based support headers currently offered.


### Deprecations

This release of FairRoot deprecates many APIs for various
reasons. If you think you really require some API, please
file an issue, so that we can see how to handle this.

* Deprecating MbsAPI
  * This release deprecates MbsAPI.
    * It will be disabled by default in FairRoot 19.
    * We plan to remove it completely in FairRoot 20.
  * If you need it, speak up NOW.
* Deprecate some singleton-like APIs:
  * `FairRunAnaProof::Instance()` - keep a pointer to the
    object after instantiating it in your code.
  * `FairRadGridManager::Instance()` - Consider using the
    `GetRadGridMan()` method on `FairMCApplcation`.
  * `FairRadMapManager::Instance`, `FairRadLenManager::Instance`
  * `FairGeaneApplication::Instance`
* Deprecated some other APIs
  * `FairGeoVector::round` was nonfunctional and never did anything.
  * `FairTask::*InputPersistance`:
    There's no getter for `fInputPersistance`,
    no other code in FairRoot uses the setters,
    we're not aware of anyone using it.
  * `FairFieldFactory::fCreator` points to `this`.
  * `FairRootManager::FillEventHeader` is only a wrapper around
    `FairSource::FillEventHeader`.
  * `FairModule::ConstructASCIIGeometry(T*, TString, U*)`, use
    `FairModule::ConstructASCIIGeometry(TString)` instead.
* Many items were already deprecated in prior versions.
  Marked them with proper C++14 deprecation warnings.
  Scheduled them for removal in v20.
* Deprecated DataMatch library
  * Contact the developers should you need it.
  * Scheduled to remove without replacement in a future major release of FairRoot.

### Other Notable Changes
* CMake [targets](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)
  for libraries are now exported.
  Some have names different from the filesystem library name.

  | Old Library Name | Target Name              |
  | ---              | ---                      |
  | TrkBase          | `FairRoot::TrackBase`    |
  | FairDataMatch    | `FairRoot::DataMatch`    |
  | FairTools        | `FairRoot::Tools`        |
  | FairFastSim      | `FairRoot::FastSim`      |
  | FairMCStepLogger | `FairRoot::MCStepLogger` |

  All those not listed here have the library name prefixed
  with `FairRoot::` as the target name.
* Note that the library filesystem name is scheduled to be
  changed in 19.2 to a `fairroot-trackbase` style naming.
  For those using the targets this change will not be visible.
* Tests using Geant3 have been disabled by default, because
  those tests have a probability > 0 for failing.
  If you want to run them anyways, pass
  `-DENABLE_GEANT3_TESTING=ON` to CMake.
* Undeprecate `FairRootManager::GetOut{File,Tree}`
  It has been deprecated since 18.0.0.
