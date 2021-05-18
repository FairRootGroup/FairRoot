# Changelog

All notable changes to FairRoot will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),

## 19.0 (UNRELEAASED) - 2021-XX-XX

### Breaking Changes
* We have moved away from our custom ROOT find module, and now use the native cmake package of ROOT.
  * This means, that all library depedencies of the type `Core` are either not working at all, or might not work as expected. Please upgrade all of them to be like `ROOT::Core` .
  * This also means, that you need to add an `include(ROOTMacros)` after your `find_package2(? ROOT ?)`.
  * `ROOT_VERSION_NUMBER` is gone. Use `ROOT_VERSION` (which is the dotted version number) and VERSION_GREATER/etc now.
* `find_package2` has been externalized into [FairCMakeModules](https://github.com/FairRootGroup/FairCMakeModules) and is not any more installed together with FairRoot
  * Please highly consider installing FairCMakeModules as a dependency of FairRoot and for your own usage. FairSoft will ship it soon.
  * After installation, it should be as easy as this in your own code:
    ```cmake
    find_package(FairCMakeModules 0.2 REQUIRED)
    include(FairFindPackage2)
    ```
  * FairRoot 19 has an internal fallback. We will likely remove that fallback in 19.2.

### Deprecated
* Deprecating MbsAPI
  * This release deprecates MbsAPI. We plan to remove it completely in the next major release.
  * If you need it, speak up NOW.
  * It is disabled by default in this release.
  * It can still be enabled with `-DBUILD_MBS=ON`.

### Example Changes in Experiment Repos
* https://github.com/R3BRootGroup/R3BRoot/pull/413
