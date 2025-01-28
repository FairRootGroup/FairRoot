# Changelog

All notable changes to FairRoot will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),

## x.x.0 - xxxx-xx-xx

### Breaking Changes

* No streamer is generated for `FairRootManager` any more

## 19.0.0 - 2024-05-17

### Breaking Changes

* CMake
  * Dropped [our custom `FindROOT.cmake`](https://github.com/FairRootGroup/FairRoot/commit/764b2c66432d2e63f765df6f6d328aa4b61dba10)
    * Using the native CMake package of ROOT, see
      https://root.cern/manual/integrate_root_into_my_cmake_project/
    * ROOT targets **MUST BE** prefixed with `ROOT::` now, see
      https://root.cern/manual/integrate_root_into_my_cmake_project/#full-example-event-project
    * Explicitely `include(ROOTMacros)` after your `find_package2(... ROOT ...)`
      now
    * Dropped `ROOT_VERSION_NUMBER`, use `ROOT_VERSION` (which is the dotted
      version number) and [`VERSION_GREATER`/etc](https://cmake.org/cmake/help/latest/command/if.html#version-comparisons)
      instead
    * Dropped `ROOTSYS`, use ROOT CMake targets instead
  * Some CMake macros have been factored out into the
    [FairCMakeModules](https://github.com/FairRootGroup/FairCMakeModules)
    project which is required by FairRoot
    * FairSoft `apr21` and later ship it (see alternative
      [installation methods](https://fairrootgroup.github.io/FairCMakeModules/latest/installation.html))
    * `find_package2` has moved to [`FairFindPackage2`](https://fairrootgroup.github.io/FairCMakeModules/latest/module/FairFindPackage2.html).
      To use it in your code, perform something like this:
      ```cmake
      find_package(FairCMakeModules 1.0 REQUIRED)
      include(FairFindPackage2)
      ```
    * Dropped Color Codes and `pad()`, use [`FairFormattedOutput` from FairCMakeModules](https://fairrootgroup.github.io/FairCMakeModules/latest/module/FairFormattedOutput.html)
      instead
      * Note that [`fair_pad()`](https://fairrootgroup.github.io/FairCMakeModules/latest/module/FairFormattedOutput.html#fair-pad)
        needs the width argument to be incremented by 1, and the `COLOR` option
        takes no argument
  * Dropped `Generate_Exe_Script()`, it was never meant for external use
  * Dropped `GENERATE_TEST_SCRIPT()`, replace it with a locally maintained solution
    * Consider using `source @FairRoot_BINDIR@/FairRootConfig.sh -p`
  * Dropped `Generate_Version_Info()`
    * If you just need to generate some files with your version number in it,
      use the standard [`configure_file`](https://cmake.org/cmake/help/latest/command/configure_file.html)
      CMake command.
    * Alternatively, consider creating a [proper CMake Package](https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#creating-packages)
      with `configure_package_config_file()`, and `write_basic_package_version_file()`.
    * If you need the "git version", use
      [`fair_get_git_version()` from FairCMakeModules](https://fairrootgroup.github.io/FairCMakeModules/latest/module/FairProjectConfig.html#fair-get-git-version)
      in addition.
  * Renamed our `ROOT_GENERATE_DICTIONARY()` to `FAIRROOT_GENERATE_DICTIONARY()`
  * Dropped build switch `BUILD_UNITTESTS`, it was in conflict with the CMake
    standard switch [`BUILD_TESTING` from the CTest module](https://cmake.org/cmake/help/latest/module/CTest.html)

* C++
  * `fEvtHeader` member variable now is a private unique pointer owned by
    `FairRun`. To access the event header, use the public member function
    `GetEventHeader()`.
  * Dropped headers:
    * `basemq/baseMQtools/baseMQtools.h`
    * `basemq/policies/Sampler/FairMQFileSource.h`
    * `basemq/policies/Sampler/FairSourceMQInterface.h`
    * `basemq/policies/Sampler/SimpleTreeReader.h`
    * `basemq/policies/Serialization/BinaryBaseClassSerializer.h`
    * `basemq/policies/Storage/BinaryOutFileManager.h`
    * `basemq/policies/Storage/BoostDataSaver.h`
    * `basemq/policies/Storage/RootOutFileManager.h`
    * `basemq/policies/Storage/TriviallyCopyableDataSaver.h`
    * `basemq/policies/Serialization/IOPolicy.h`
  * The following files/classes have been moved to the example where they are used and renamed:
    * `basemq/devices/FairMQProcessor.h` -> `examples/advanced/Tutorial3/MQ/processor.cxx`
    * `basemq/devices/FairMQSampler.h` -> `examples/advanced/Tutorial3/MQ/sampler.cxx`
    * `basemq/tasks/FairMQProcessorTask.h` -> `examples/advanced/Tutorial3/MQ/processorTask/ProcessorTask.h`
    * `basemq/tasks/FairMQSamplerTask.h` -> `examples/advanced/Tutorial3/MQ/samplerTask/SamplerTask.h`
  * FairTimeStamp
    * `virtual bool operator<(const FairTimeStamp* rValue) const` changed to `bool operator<(const FairTimeStamp& rValue) const`
  * FairModule::svList is gone. This was never intended as a public
    API.
  * Remove calling `Close()`
    * `FairSink::Close()` and `FairSource::Close()` are no longer called in FairRoot.
    * Derived classes from `FairSink` and `FairSource` should close the resources automatically in their destructors.

### Deprecations

If you think you really require a deprecated API, please
[file an issue](https://github.com/FairRootGroup/FairRoot/issues/new).

* Deprecated MbsAPI
  * We plan to remove it completely in the next major release
  * Disabled by default, enable via `-DBUILD_MBS=ON`
* Deprecated Proof related classes
  * [Proof was deprecated in ROOT 6.26](https://github.com/root-project/root/commit/40c3e85970f83b52d6e29bb3c509498bf15fe9e5)
  * Disabled by default, enable via `-DBUILD_PROOF_SUPPORT=ON`
* Deprecated `FairEventBuilder` and `FairEventBuilderManager` (https://github.com/FairRootGroup/FairRoot/pull/1414)
  * Disabled by default, enable via `-DBUILD_EVENT_BUILDER=ON`
* Deprecated `FairRun::SetEventHeader(FairEventHeader*)`, use
  `FairRun::SetEventHeader(std::unique_ptr<FairEventHeader> EvHeader)` instead
  * Clarified ownership semantics
* Deprecated `FairRunAna::Run(Long64_t entry)`, use
  `FairRunAna::RunSingleEntry(Long64_t entry)` instead
  * Semantics were unclear due to dubious `Run(int)` and `Run(long)`

### Other Notable Changes

* Restructured the source tree by moving all public components to the new
  '/fairroot' folder
* Consider calling `fairroot_check_root_cxxstd_compatibility()`
  in your `CMakeLists.txt`
* `fairsoft-config` isn't searched for and not needed any more

### Example Changes in Experiment Repos

* https://github.com/R3BRootGroup/R3BRoot/pull/413

## 18.8.2 - 2024-03-01

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

## 18.8.1 - 2024-02-24

### Breaking Changes
* The output folder name changed from 'folderName_0' to 'folderName'.
  In the MT mode of Geant4 the folder names changed from 'folderName_1' and 'folderName_2' to 'folderName'.
* Removed the FairRunOnline::InitContainers() function.
  It has not been used in FairRoot. Tested with R3BRoot.

### Bug fixes
* Check the return value of `source->InitUnpackers()`/`source->ReinitUnpackers()`
  in `FairRunOnline`. Stop run if `false` returned.
* Remove sink from Tutorial3/MQ/sampler.cxx.
* Fixed broken `StaticContainer` functionality (do not `ReInit`ialize when `RunId` changes) in `FairRunOnline`.

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
