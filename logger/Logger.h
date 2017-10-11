/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_LOGGER_H
#define FAIR_LOGGER_H

#ifdef DEBUG
#undef DEBUG
#warning "The symbol 'DEBUG' is used in FairRoot Logger. undefining..."
#endif

#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>

namespace fair
{

// non-std exception to avoid undesirable catches - fatal should exit in a way we want.
class FatalException
{
  public:
    FatalException()
        : fWhat()
    {}

    FatalException(std::string what)
        : fWhat(what)
    {}

    std::string What()
    {
        return fWhat;
    }

  private:
    std::string fWhat;
};

class Logger
{
  public:
    enum class Severity : int
    {
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
        // backwards-compatibility:
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
    };

    // verbosity levels:
    // low:      [severity] message
    // medium:   [HH:MM:SS][severity] message
    // high:     [process name][HH:MM:SS:NS][severity] message
    // veryhigh: [process name][HH:MM:SS:NS][severity][file:line:function] message
    enum class Verbosity : int
    {
        low,
        medium,
        high,
        veryhigh,
        // backwards-compatibility:
        LOW = low,
        MEDIUM = medium,
        HIGH = high,
        VERYHIGH = veryhigh
    };

    Logger(Severity severity);

    static void SetConsoleSeverity(const Severity severity);
    static void SetConsoleSeverity(const std::string& severityStr);

    static void SetFileSeverity(const Severity severity);
    static void SetFileSeverity(const std::string& severityStr);

    static bool Logging(const Severity severity);

    static void SetVerbosity(const Verbosity verbosity);
    static void SetVerbosity(const std::string& verbosityStr);

    static void SetConsoleColor(const bool colored = true);

    static void InitFileSink(const Severity severity, const std::string& filename, bool customizeName = true);
    static void InitFileSink(const std::string& severityStr, const std::string& filename, bool customizeName = true);

    static void RemoveFileSink();

    static std::string SeverityName(Severity);
    static std::string VerbosityName(Verbosity);

    std::ostringstream& Log(const std::string& file, const std::string& line, const std::string& func);

    static const std::unordered_map<std::string, Verbosity> fVerbosityMap;
    static const std::unordered_map<std::string, Severity> fSeverityMap;
    static const std::array<std::string, 12> fSeverityNames;
    static const std::array<std::string, 4> fVerbosityNames;

    static void OnFatal(std::function<void()> func);

    static void SetCerrOnly(bool cerrOnly);

    virtual ~Logger() noexcept(false);

  private:
    Severity fCurrentSeverity;

    std::ostringstream fContent;
    std::ostringstream fColorOut;
    std::ostringstream fBWOut;
    static const std::string fProcessName;
    static bool fColored;
    static bool fCerrOnly;
    static std::fstream fFileStream;

    static Severity fConsoleSeverity;
    static Severity fFileSeverity;
    static Severity fMinSeverity;

    static Verbosity fVerbosity;

    static std::function<void()> fFatalCallback;

    bool LoggingToConsole() const;
    bool LoggingToFile() const;

    static void UpdateMinSeverity();
};

} // namespace fair

#define IMP_CONVERTTOSTRING(s) # s
#define CONVERTTOSTRING(s) IMP_CONVERTTOSTRING(s)

#define LOG(severity) \
    for (bool fairLOggerunLikelyvariable = false; fair::Logger::Logging(fair::Logger::Severity::severity) && !fairLOggerunLikelyvariable; fairLOggerunLikelyvariable = true) \
        fair::Logger(fair::Logger::Severity::severity).Log(__FILE__, CONVERTTOSTRING(__LINE__), __FUNCTION__)

// with custom file, line, function
#define LOGD(severity, file, line, function) \
    for (bool fairLOggerunLikelyvariable = false; fair::Logger::Logging(severity) && !fairLOggerunLikelyvariable; fairLOggerunLikelyvariable = true) \
        fair::Logger(severity).Log(file, line, function)

#define LOG_IF(severity, condition) \
    for (bool fairLOggerunLikelyvariable2 = false; condition && !fairLOggerunLikelyvariable2; fairLOggerunLikelyvariable2 = true) \
        LOG(severity)

#endif // FAIR_LOGGER_H
