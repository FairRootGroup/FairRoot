# Contributing

## Bug reports, feature request, questions etc

Create a [Github Issue](https://github.com/FairRootGroup/FairRoot/issues/new/choose).

## Contributing code

Create a [Github Pull Request](https://github.com/FairRootGroup/FairRoot/compare):

1. By default, develop against the [`dev`](https://github.com/FairRootGroup/FairRoot/tree/dev)
   branch and base your PR against it.
   * In rare cases (e.g. backports, some hotfixes) base against the appropriate
     branch.
2. If you are a first-time contributor, add a separate commit in your PR which
   adds your name to the [`CONTRIBUTORS`](CONTRIBUTORS) file.
3. Follow our [Coding Guidelines](#coding-guidelines).
4. Expect that a reviewer will ask you for restructuring your commits! This
   usually happens towards the end of the lifetime of a PR when it matured
   enough for merging.

# Coding Guidelines

These guidelines are horribly incomplete at this point in time, but one has to
start somewhere ;) Exactly because these guidelines are relatively new, do not be
alarmed if large parts of this repo do not follow them (yet). The idea is to
apply them incrementally on new code and when existing code is modified. These
guidelines will also evolve as time passes.

How to reference a rule in an issue or PR discussion:
```
// reference to our guideline
[G.2](https://github.com/FairRootGroup/FairRoot/blob/master/CONTRIBUTING.md#g.2-adopted-c++-core-guidelines)
// reference to c++ core guideline with prefix CPPCG::
[CPPCG::I.11](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#i11-never-transfer-ownership-by-a-raw-pointer-t-or-reference-t)
```

## G - General

### G.1 Our CI runs [`clang-tidy`](https://clang.llvm.org/extra/clang-tidy/)

**Config**: [`.clang-tidy`](.clang-tidy)

We currently do not strictly enforce *clang-tidy* checks, but the author
should try to address any warnings. The set of enabled checks will evolve over
time.

### G.2 Adopted C++ Core Guidelines

This shall be an evolving list of explicitely adopted C++ Core Guidelines:

* [CPPCG::I.11: Never transfer ownership by a raw pointer (`T*`) or reference (`T&`)](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#i11-never-transfer-ownership-by-a-raw-pointer-t-or-reference-t)
   * If an owning raw pointer cannot be avoided for legacy reasons,
     **you must add a comment documenting the ownership semantics!**

### G.3 Write a good Git history

* Follow [the seven rules of a great Git commit message](https://cbea.ms/git-commit/#seven-rules)!
* Use a meaningful commit granularity, e.g. do not mix
  unrelated changes in a single commit and vice verse squash related commits
  into one.
* Utilize [the commit message body to explain *what* and *why* and not *how*](https://cbea.ms/git-commit/#why-not-how).
  Aim your message to be meaningful (concise, but complete
  enough) to a reader in the future! See also G.4!
* Utilize [reference keywords](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue#linking-a-pull-request-to-an-issue-using-a-keyword)
  both in commit messages as well as in PR comments if applicable.

### G.4 Conventional Commits

* Follow the [Conventional Commits Specification](https://www.conventionalcommits.org/en/v1.0.0/)
* Adopted `type`s: `fix:`, `feat:`, `build:`, `chore:`, `ci:`, `docs:`,
  `style:`, `refactor:`, `perf:`, `test:`
* If a `scope` is used, prefer the library name (first directory level below
  `fairroot/`), e.g. `fix(base):` or `feat(geobase):`

### G.5 Signed Commits and Tags

You may use any signature format Git and Github support (SSH e.g. may be more
convenient, if one does not have a GPG key yet).

* [Github - Setup](https://docs.github.com/en/authentication/managing-commit-signature-verification/telling-git-about-your-signing-key)
* [Github - Signing Commits](https://docs.github.com/en/authentication/managing-commit-signature-verification/signing-commits)
* [Github - Signing Tags](https://docs.github.com/en/authentication/managing-commit-signature-verification/signing-tags)
* [Git - Signing Your Work](https://git-scm.com/book/en/v2/Git-Tools-Signing-Your-Work)
  Make sure to consider `git config [--local|--global] commit.gpgsign true`
  (scroll down to the bottom)

## D - Documentation

### D.1 Use [doxygen-style comments](https://www.doxygen.nl/manual/commands.html)

## S - Style

### S.1 Our CI enforces formatting with [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html)

**Config**: [`.clang-format`](.clang-format)

Rarely, it is needed to opt-out of *clang-format* for certain code sections
because it would just make things worse.

**Example**:
```cpp
// clang-format off
fDescription.add_options()
    ("help",                                        "Print this message")
    ("nevents",        po::value<int>(),            "Number of events to simulate")
    ("engine",         po::value<vector<string>>(), "Monte Carlo engine")
    ("multi-threaded",                              "Geant4 multi threaded")
    ("output-file",    po::value<vector<string>>(), "Output file")
    ("parameter-file", po::value<vector<string>>(), "Parameter file")
    ("random-seed",    po::value<int>(),            "Seed for the random number generator");
// clang-format on
```

### S.2 Prefer variable names describing *what* they contain

Avoid repeating just the typename.

**Reason**: Readability

**Example**:
```cpp
TList* list = module->GetList();                // avoid
TList* volList = module->GetListOfVolumes();    // acceptable
TList* volumes = module->GetVolumes();          // ✓ prefer

for (auto const& listEntry : *list) { /*...*/ } // avoid
for (auto const& aVol : *volList) { /*...*/ }   // acceptable
for (auto const& volume : *volumes) { /*...*/ } // ✓ prefer
```


# Creating a new Release

(This is basically for the release manager.
So that we don't forget anything.)

## Control the status

* Take a look at the
  [Milestone](https://github.com/FairRootGroup/FairRoot/milestones)
  for the release

  Consider moving still open items to another milestone

## Check the CI Coverage

* Remind/ask myself what platforms the release is targeting (I roughly
  target the last two years of releases for ubuntu/fedora, debian
  stable/oldstable + anything older, if relevant in GSI still)
* Then I compare what is currently tested via CI and decide whether it
  needs an updates, e.g.
   * regenerate/update existing images (cover new FairSoft releases? get
     latest os updates to test closer to what a user may use)
   * add new images (new os releases? which ship new compiler major versions
     perhaps)
   * remove old images
   * For macs it involves similar steps, updating homebrew, perhaps the os
     or the command line tools
* Fix issues resulting from previous step

## Create a commit

On the `v{x.y}_patches` branch with comment `Bump v{x.y.z}`:

* Double check that the version number on the `project`
  line in [CMakeLists.txt](CMakeLists.txt) is correct

* Apply some final editorial changes to the
  [CHANGELOG](CHANGELOG.md) for the upcoming release
  * Remove the `(UNRELEASED)` tag on the header
  * Add the correct date
  * Go over the list and re-order things/etc (classical
    editorial changes)

* Apply editorial changes to [README](README.md)

* (Soon)
  * Check that `codemeta.json` and friends have been
    updated.
  * Get a zenodo entry ready

## Push the patch to the repository:

* ```sh
  git push origin v{x.y}_patches
  ```

* Check the CI so that all checks pass for the branch

## Create, control and push the new tag to the repository:

```sh
git tag v{x.y.z} -a -s
git show v{x.y.z}
git push origin v{x.y.z}
```

## Create a new release on GitHub.

## In certain cases the tag should be merged onto master:

```sh
git checkout master
git merge origin/v{x.y}_patches
git push mainrepo origin
```

The message, when prompted, should be `Merge v{x.y.z}`.
The merge and push should not be forced.
