/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include <Logger.h>

#include <iostream>
#include <ostream>
#include <array>
#include <chrono>
#include <ctime> // strftime
#include <iomanip> // setw, setfill

using namespace std;

namespace fair
{

enum class Color : int
{
    fgBlack    = 30,
    fgRed      = 31,
    fgGreen    = 32,
    fgYellow   = 33,
    fgBlue     = 34,
    fgMagenta  = 35,
    fgCyan     = 36,
    fgWhite    = 37,
    fgDefault  = 39,
    bgRed      = 41,
    bgGreen    = 42,
    bgBlue     = 44,
    bgDefault  = 49
};

string startColor(Color color)
{
    ostringstream os;
    os << "\033[01;" << static_cast<int>(color) << "m";
    return os.str();
}

string endColor()
{
    return "\033[0m";
}

class ColorOut
{
  public:
    ColorOut(Color color, const string& str)
        : fColor(color)
        , fStr(str)
    {}

    friend ostream& operator<<(ostream& os, const ColorOut& w)
    {
        return os << "\033[01;" << static_cast<int>(w.fColor) << "m" << w.fStr << "\033[0m";
    }

  private:
    Color fColor;
    const string& fStr;
};

class ColoredSeverityWriter
{
  public:
    ColoredSeverityWriter(Severity severity)
        : fSeverity(severity)
    {}

    friend ostream& operator<<(ostream& os, const ColoredSeverityWriter& w)
    {
        switch (w.fSeverity)
        {
            case Severity::nolog:
                return os << "\033[01;" << static_cast<int>(Color::fgDefault) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::fatal:
                return os << "\033[01;" << static_cast<int>(Color::bgRed) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::error:
                return os << "\033[01;" << static_cast<int>(Color::fgRed) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::warn:
                return os << "\033[01;" << static_cast<int>(Color::fgYellow) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::state:
                return os << "\033[01;" << static_cast<int>(Color::fgMagenta) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::info:
                return os << "\033[01;" << static_cast<int>(Color::fgGreen) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::debug:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::debug1:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::debug2:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::debug3:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::debug4:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Severity::trace:
                return os << "\033[01;" << static_cast<int>(Color::fgCyan) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            default:
                return os << "UNKNOWN";
                break;
        }
    }

  private:
    Severity fSeverity;
};

bool Logger::fColored = false;
fstream Logger::fFileStream;
Verbosity Logger::fVerbosity = Verbosity::low;
Severity Logger::fConsoleSeverity = Severity::info;
Severity Logger::fFileSeverity = Severity::nolog;
Severity Logger::fMinSeverity = Severity::info;
function<void()> Logger::fFatalCallback;
unordered_map<string, pair<Severity, function<void(const string& content, const LogMetaData& metadata)>>> Logger::fCustomSinks;
mutex Logger::fMtx;

#if defined(__APPLE__) || defined(__FreeBSD__)
const string Logger::fProcessName = getprogname();
#elif defined(_GNU_SOURCE)
const string Logger::fProcessName = program_invocation_short_name;
#else
const string Logger::fProcessName = "?";
#endif

const unordered_map<string, Verbosity> Logger::fVerbosityMap =
{
    { "veryhigh", Verbosity::veryhigh },
    { "high",     Verbosity::high     },
    { "medium",   Verbosity::medium   },
    { "low",      Verbosity::low      },
    { "VERYHIGH", Verbosity::veryhigh },
    { "HIGH",     Verbosity::high     },
    { "MEDIUM",   Verbosity::medium   },
    { "LOW",      Verbosity::low      }
};

const unordered_map<string, Severity> Logger::fSeverityMap =
{
    { "nolog",   Severity::nolog   },
    { "NOLOG",   Severity::nolog   },
    { "error",   Severity::error   },
    { "ERROR",   Severity::error   },
    { "warn",    Severity::warn    },
    { "WARN",    Severity::warn    },
    { "warning", Severity::warning },
    { "WARNING", Severity::warning },
    { "state",   Severity::state   },
    { "STATE",   Severity::state   },
    { "info",    Severity::info    },
    { "INFO",    Severity::info    },
    { "debug",   Severity::debug   },
    { "DEBUG",   Severity::debug   },
    { "trace",   Severity::trace   },
    { "TRACE",   Severity::trace   },
    { "debug1",  Severity::debug1  },
    { "DEBUG1",  Severity::debug1  },
    { "debug2",  Severity::debug2  },
    { "DEBUG2",  Severity::debug2  },
    { "debug3",  Severity::debug3  },
    { "DEBUG3",  Severity::debug3  },
    { "debug4",  Severity::debug4  },
    { "DEBUG4",  Severity::debug4  }
};

const array<string, 12> Logger::fSeverityNames =
{
    {
        "NOLOG",
        "FATAL",
        "ERROR",
        "WARN",
        "STATE",
        "INFO",
        "DEBUG",
        "DEBUG1",
        "DEBUG2",
        "DEBUG3",
        "DEBUG4",
        "TRACE"
    }
};

const array<string, 4> Logger::fVerbosityNames =
{
    {
        "low",
        "medium",
        "high",
        "veryhigh"
    }
};

string Logger::SeverityName(Severity severity)
{
    return fSeverityNames.at(static_cast<size_t>(severity));
}

string Logger::VerbosityName(Verbosity verbosity)
{
    return fVerbosityNames.at(static_cast<size_t>(verbosity));
}

Logger::Logger(Severity severity, const string& file, const string& line, const string& func)
{
    chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
    size_t pos = file.rfind("/");

    fMetaData.timestamp = chrono::system_clock::to_time_t(now);
    fMetaData.us = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()) % 1000000;
    fMetaData.process_name = fProcessName;
    fMetaData.file = file.substr(pos + 1);
    fMetaData.line = line;
    fMetaData.func = func;
    fMetaData.severity_name = fSeverityNames.at(static_cast<size_t>(severity));
    fMetaData.severity = severity;
}

void Logger::SetConsoleSeverity(const Severity severity)
{
    fConsoleSeverity = severity;
    UpdateMinSeverity();
}

void Logger::SetConsoleSeverity(const string& severityStr)
{
    if (fSeverityMap.count(severityStr))
    {
        SetConsoleSeverity(fSeverityMap.at(severityStr));
    }
    else
    {
        LOG(error) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
        SetConsoleSeverity(Severity::info);
    }
}

void Logger::SetFileSeverity(const Severity severity)
{
    fFileSeverity = severity;
    UpdateMinSeverity();
}

void Logger::SetFileSeverity(const string& severityStr)
{
    if (fSeverityMap.count(severityStr))
    {
        SetFileSeverity(fSeverityMap.at(severityStr));
    }
    else
    {
        LOG(error) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
        SetFileSeverity(Severity::info);
    }
}

void Logger::SetCustomSeverity(const string& key, const Severity severity)
{
    fCustomSinks.at(key).first = severity; // TODO: range checks
    UpdateMinSeverity();
}

void Logger::SetCustomSeverity(const string& key, const string& severityStr)
{
    if (fSeverityMap.count(severityStr))
    {
        SetCustomSeverity(key, fSeverityMap.at(severityStr));
    }
    else
    {
        LOG(error) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
        SetCustomSeverity(key, Severity::info);
    }
}

void Logger::UpdateMinSeverity()
{
    fMinSeverity = (fConsoleSeverity <= fFileSeverity) ? fFileSeverity : fConsoleSeverity;

    for (auto& it : fCustomSinks)
    {
        if (fMinSeverity <= it.second.first)
        {
            fMinSeverity = it.second.first;
        }
    }
}

bool Logger::Logging(Severity severity)
{
    if (Severity::fatal == severity)
    {
        return true;
    }
    if (severity <= fMinSeverity && severity > Severity::nolog)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Logger::SetVerbosity(const Verbosity verbosity)
{
    fVerbosity = verbosity;
}

void Logger::SetVerbosity(const string& verbosityStr)
{
    if (fVerbosityMap.count(verbosityStr))
    {
        fVerbosity = fVerbosityMap.at(verbosityStr);
    }
    else
    {
        LOG(error) << "Unknown verbosity setting: '" << verbosityStr << "', setting to default 'low'.";
        fVerbosity = Verbosity::low;
    }
}

void Logger::SetConsoleColor(const bool colored)
{
    fColored = colored;
}

void Logger::InitFileSink(const Severity severity, const string& filename, bool customizeName)
{
    lock_guard<mutex> lock(fMtx);
    if (fFileStream.is_open())
    {
        fFileStream.close();
    }

    string fullName = filename;

    if (customizeName)
    {
        // TODO: customize file name
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        stringstream ss;
        ss << "_";
        char tsstr[32];
        if (strftime(tsstr, sizeof(tsstr), "%Y-%m-%d_%H_%M_%S", localtime(&now)))
        {
            ss << tsstr;
        }
        ss << ".log";
        fullName += ss.str();
    }

    fFileStream.open(fullName, fstream::out | fstream::app);

    if (fFileStream.is_open())
    {
        fFileSeverity = severity;
        UpdateMinSeverity();
    }
    else
    {
        cout << "Error opening file: " << fullName;
    }

}

void Logger::InitFileSink(const string& severityStr, const string& filename, bool customizeName)
{
    if (fSeverityMap.count(severityStr))
    {
        InitFileSink(fSeverityMap.at(severityStr), filename, customizeName);
    }
    else
    {
        LOG(error) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
        InitFileSink(Severity::info, filename);
    }
}

void Logger::RemoveFileSink()
{
    lock_guard<mutex> lock(fMtx);
    if (fFileStream.is_open())
    {
        fFileStream.close();
    }
}

bool Logger::LoggingToConsole() const
{
    return (fMetaData.severity <= fConsoleSeverity &&
           fMetaData.severity > Severity::nolog) ||
           fMetaData.severity == Severity::fatal;
}

bool Logger::LoggingToFile() const
{
    return (fMetaData.severity <= fFileSeverity &&
           fMetaData.severity > Severity::nolog) ||
           fMetaData.severity == Severity::fatal;
}

bool Logger::LoggingCustom(const Severity severity) const
{
    return (fMetaData.severity <= severity &&
           fMetaData.severity > Severity::nolog) ||
           fMetaData.severity == Severity::fatal;
}

void Logger::OnFatal(function<void()> func)
{
    fFatalCallback = func;
}

void Logger::AddCustomSink(const string& key, Severity severity, function<void(const string& content, const LogMetaData& metadata)> func)
{
    lock_guard<mutex> lock(fMtx);
    if (fCustomSinks.count(key) == 0)
    {
        fCustomSinks.insert(make_pair(key, make_pair(severity, func)));
        UpdateMinSeverity();
    }
    else
    {
        cout << "Logger::AddCustomSink: sink '" << key << "' already exists, will not add again. Remove first with Logger::RemoveCustomSink(const string& key)" << endl;
    }
}

void Logger::AddCustomSink(const string& key, const string& severityStr, function<void(const string& content, const LogMetaData& metadata)> func)
{
    if (fSeverityMap.count(severityStr))
    {
        AddCustomSink(key, fSeverityMap.at(severityStr), func);
    }
    else
    {
        LOG(error) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
        AddCustomSink(key, Severity::info, func);
    }
}

void Logger::RemoveCustomSink(const string& key)
{
    if (fCustomSinks.count(key) > 0)
    {
        fCustomSinks.erase(key);
        UpdateMinSeverity();
    }
    else
    {
        cout << "Logger::RemoveCustomSink: sink '" << key << "' doesn't exists, will not remove." << endl;
    }
}

Logger& Logger::Log()
{
    char tsstr[32];
    if (!strftime(tsstr, sizeof(tsstr), "%H:%M:%S", localtime(&(fMetaData.timestamp))))
    {
        tsstr[0] = 'u';
    }

    if ((!fColored && LoggingToConsole()) || LoggingToFile())
    {
        if (fVerbosity >= Verbosity::high)
        {
            fBWOut << "[" << fMetaData.process_name << "]"
                   << "[" << tsstr << "." << setw(6) << setfill('0') << fMetaData.us.count() << "]";
        }
        else if (fVerbosity == Verbosity::medium)
        {
            fBWOut << "[" << tsstr << "]";
        }

        fBWOut << "[" << fMetaData.severity_name << "]";

        if (fVerbosity == Verbosity::veryhigh)
        {
            fBWOut << "[" << fMetaData.file << ":" << fMetaData.line << ":" << fMetaData.func << "]";
        }

        fBWOut << " ";
    }

    if (fColored && (LoggingToConsole()))
    {
        if (fVerbosity >= Verbosity::high)
        {
            fColorOut << "[" << ColorOut(Color::fgBlue, fMetaData.process_name) << "]"
                      << "[" << startColor(Color::fgCyan) << tsstr << "." << setw(6) << setfill('0') << fMetaData.us.count() << endColor() << "]";
        }
        else if (fVerbosity == Verbosity::medium)
        {
            fColorOut << "[" << startColor(Color::fgCyan) << tsstr << endColor() << "]";
        }

        fColorOut << "[" << ColoredSeverityWriter(fMetaData.severity) << "]";

        if (fVerbosity == Verbosity::veryhigh)
        {
            fColorOut << "[" << ColorOut(Color::fgBlue, fMetaData.file) << ":" << ColorOut(Color::fgYellow, fMetaData.line) << ":" << ColorOut(Color::fgBlue, fMetaData.func) << "]";
        }

        fColorOut << " ";
    }

    return *this;
}

Logger& Logger::operator<<(ios_base& (*manip) (ios_base&))
{
    fContent << manip;
    return *this;
}

Logger& Logger::operator<<(ostream& (*manip) (ostream&))
{
    fContent << manip;
    return *this;
}

Logger::~Logger() noexcept(false)
{
    for (auto& it : fCustomSinks)
    {
        if (LoggingCustom(it.second.first))
        {
            lock_guard<mutex> lock(fMtx);
            it.second.second(fContent.str(), fMetaData);
        }
    }

    fContent << "\n"; // "\n" + flush instead of endl makes output thread safe.

    fBWOut << fContent.str();

    if (LoggingToConsole())
    {
        if (fColored)
        {
            fColorOut << fContent.str();
            cout << fColorOut.str() << flush;
        }
        else
        {
            cout << fBWOut.str() << flush;
        }
    }

    if (LoggingToFile())
    {
        lock_guard<mutex> lock(fMtx);
        if (fFileStream.is_open())
        {
            fFileStream << fBWOut.str() << flush;
        }
    }

    if (fMetaData.severity == Severity::fatal)
    {
        if (fFatalCallback)
        {
            fFatalCallback();
        }
    }
}

} // namespace fair
