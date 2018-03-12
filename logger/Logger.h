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
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <utility> // pair
#include <time.h> // time_t

namespace fair
{

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
// high:     [process name][HH:MM:SS:µS][severity] message
// veryhigh: [process name][HH:MM:SS:µS][severity][file:line:function] message
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

struct LogMetaData
{
    std::time_t timestamp;
    std::chrono::microseconds us;
    std::string process_name;
    std::string file;
    std::string line;
    std::string func;
    std::string severity_name;
    fair::Severity severity;
};

class Logger
{
  public:
    Logger(Severity severity, const std::string& file, const std::string& line, const std::string& func);

    static void SetConsoleSeverity(const Severity severity);
    static void SetConsoleSeverity(const std::string& severityStr);

    static void SetFileSeverity(const Severity severity);
    static void SetFileSeverity(const std::string& severityStr);

    static void SetCustomSeverity(const std::string& key, const Severity severity);
    static void SetCustomSeverity(const std::string& key, const std::string& severityStr);

    static bool Logging(const Severity severity);

    static void SetVerbosity(const Verbosity verbosity);
    static void SetVerbosity(const std::string& verbosityStr);

    static void SetConsoleColor(const bool colored = true);

    static void InitFileSink(const Severity severity, const std::string& filename, bool customizeName = true);
    static void InitFileSink(const std::string& severityStr, const std::string& filename, bool customizeName = true);

    static void RemoveFileSink();

    static std::string SeverityName(Severity);
    static std::string VerbosityName(Verbosity);

    static void OnFatal(std::function<void()> func);

    static void AddCustomSink(const std::string& key, Severity severity, std::function<void(const std::string& content, const LogMetaData& metadata)> sink);
    static void AddCustomSink(const std::string& key, const std::string& severityStr, std::function<void(const std::string& content, const LogMetaData& metadata)> sink);
    static void RemoveCustomSink(const std::string& key);

    Logger& Log();

    template<typename T>
    Logger& operator<<(const T& t)
    {
        fContent << t;
        return *this;
    }

    // overload for char* to make sure it is not nullptr
    Logger& operator<<(const char* cptr)
    {
        if (cptr != nullptr) {
            fContent << cptr;
        }
        return *this;
    }

    // overload for char* to make sure it is not nullptr
    Logger& operator<<(char* cptr)
    {
        if (cptr != nullptr) {
            fContent << cptr;
        }
        return *this;
    }

    Logger& operator<<(std::ios_base& (*manip) (std::ios_base&));
    Logger& operator<<(std::ostream& (*manip) (std::ostream&));

    static const std::unordered_map<std::string, Verbosity> fVerbosityMap;
    static const std::unordered_map<std::string, Severity> fSeverityMap;
    static const std::array<std::string, 12> fSeverityNames;
    static const std::array<std::string, 4> fVerbosityNames;

    virtual ~Logger() noexcept(false);

  private:
    LogMetaData fMetaData;

    std::ostringstream fContent;
    std::ostringstream fColorOut;
    std::ostringstream fBWOut;
    static const std::string fProcessName;
    static bool fColored;
    static std::fstream fFileStream;

    static Severity fConsoleSeverity;
    static Severity fFileSeverity;
    static Severity fMinSeverity;

    static Verbosity fVerbosity;

    static std::function<void()> fFatalCallback;
    static std::unordered_map<std::string, std::pair<Severity, std::function<void(const std::string& content, const LogMetaData& metadata)>>> fCustomSinks;
    static std::mutex fMtx;

    bool LoggingToConsole() const;
    bool LoggingToFile() const;
    bool LoggingCustom(const Severity) const;

    static void UpdateMinSeverity();
};

} // namespace fair

#define IMP_CONVERTTOSTRING(s) # s
#define CONVERTTOSTRING(s) IMP_CONVERTTOSTRING(s)

#define LOG(severity) \
    for (bool fairLOggerunLikelyvariable = false; fair::Logger::Logging(fair::Severity::severity) && !fairLOggerunLikelyvariable; fairLOggerunLikelyvariable = true) \
        fair::Logger(fair::Severity::severity, __FILE__, CONVERTTOSTRING(__LINE__), __FUNCTION__).Log()

// with custom file, line, function
#define LOGD(severity, file, line, function) \
    for (bool fairLOggerunLikelyvariable = false; fair::Logger::Logging(severity) && !fairLOggerunLikelyvariable; fairLOggerunLikelyvariable = true) \
        fair::Logger(severity, file, line, function).Log()

#define LOG_IF(severity, condition) \
    for (bool fairLOggerunLikelyvariable2 = false; condition && !fairLOggerunLikelyvariable2; fairLOggerunLikelyvariable2 = true) \
        LOG(severity)

#endif // FAIR_LOGGER_H
