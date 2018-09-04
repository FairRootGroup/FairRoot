fairtools
========

Tools used by FairRoot:

- `FairLogger` allows writing to the log.

FairLogger interface of FairRoot uses [FairLogger](https://github.com/FairRootGroup/FairLogger) library underneath. Refer to it for more documentation.

This implementation is available since FairSoft may18 and FairRoot v18. Some notable changes that are available since these versions are:

- No longer need to add `FairLogger::endl` to get end of line - each LOG macro call will add endl() automatically. `FairLogger::endl` only adds a space character to your output. Also worth mentioning is that if you for some reason **do not** want to have a line break in certain LOG calls, you need to refactor your code to accumulate data in a stringstream instead of LOG calls and only give stringstream's `str()` to the LOG macro for the final line break.
- All severity names are now available in lower case. We recommend using lower case to avoid confusion with MACRO NAMES. Uppercase variants will be deprecated and finally removed at some point. The new severity names are:

```C++
    nolog,
    fatal,
    error,
    warn,
    state,
    info,
    debug,
    debug1,
    debug2,
    debug3,
    debug4,
    trace,
    // backwards-compatibility (to be removed in the future):
    NOLOG = nolog,
    FATAL = fatal,
    ERROR = error,
    WARN = warn,
    warning = warn,
    WARNING = warn,
    STATE = state,
    INFO = info,
    DEBUG = debug,
    DEBUG1 = debug1,
    DEBUG2 = debug2,
    DEBUG3 = debug3,
    DEBUG4 = debug4,
    TRACE = trace
```

If your FairSoft/FairRoot is older than may18/v18, you have to use the uppercase severity levels and you need to add FairLogger::endl if you need a line break. E.g.: `LOG(INFO) << "This is an infomercial message" << FaitLogger::endl;`.
