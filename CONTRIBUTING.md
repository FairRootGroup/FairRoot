# Contributing

## Bug reports, feature request, questions etc

Create a [Github Issue](https://github.com/FairRootGroup/FairRoot/issues/new/choose).

## Contributing code

Create a [Github Pull Request](https://github.com/FairRootGroup/FairRoot/compare):

1. By default, develop against the [`dev`](https://github.com/FairRootGroup/FairRoot/tree/dev)
   branch and base your PR against it.
   * In rare cases (e.g. backports, some hotfixes) base against the appropriate
     branch.
2. If you are a first time contributor, add a separate commit in your PR which
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
     enough) to a reader in the future!
   * Utilize [reference keywords](https://docs.github.com/en/issues/tracking-your-work-with-issues/linking-a-pull-request-to-an-issue#linking-a-pull-request-to-an-issue-using-a-keyword)
     both in commit messages as well as in PR comments if applicable.

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
