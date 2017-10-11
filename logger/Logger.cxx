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
#include <iomanip> // put_time

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
    ColoredSeverityWriter(Logger::Severity severity)
        : fSeverity(severity)
    {}

    friend ostream& operator<<(ostream& os, const ColoredSeverityWriter& w)
    {
        switch (w.fSeverity)
        {
            case Logger::Severity::nolog:
                return os << "\033[01;" << static_cast<int>(Color::fgDefault) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::fatal:
                return os << "\033[01;" << static_cast<int>(Color::bgRed) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::error:
                return os << "\033[01;" << static_cast<int>(Color::fgRed) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::warn:
                return os << "\033[01;" << static_cast<int>(Color::fgYellow) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::state:
                return os << "\033[01;" << static_cast<int>(Color::fgMagenta) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::info:
                return os << "\033[01;" << static_cast<int>(Color::fgGreen) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::debug:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::debug1:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::debug2:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::debug3:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::debug4:
                return os << "\033[01;" << static_cast<int>(Color::fgBlue) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            case Logger::Severity::trace:
                return os << "\033[01;" << static_cast<int>(Color::fgCyan) << "m" << Logger::SeverityName(w.fSeverity) << "\033[0m";
                break;
            default:
                return os << "UNKNOWN";
                break;
        }
    }

  private:
    Logger::Severity fSeverity;
};

bool Logger::fColored = false;
bool Logger::fCerrOnly = false;
fstream Logger::fFileStream;
Logger::Verbosity Logger::fVerbosity = Logger::Verbosity::low;
Logger::Severity Logger::fConsoleSeverity = Logger::Severity::info;
Logger::Severity Logger::fFileSeverity = Logger::Severity::nolog;
Logger::Severity Logger::fMinSeverity = Logger::Severity::info;
std::function<void()> Logger::fFatalCallback;

#if defined(__APPLE__) || defined(__FreeBSD__)
const string Logger::fProcessName = getprogname();
#elif defined(_GNU_SOURCE)
const string Logger::fProcessName = program_invocation_short_name;
#else
const string Logger::fProcessName = "?";
#endif

const unordered_map<string, Logger::Verbosity> Logger::fVerbosityMap =
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

const unordered_map<string, Logger::Severity> Logger::fSeverityMap =
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

Logger::Logger(Severity severity)
    : fCurrentSeverity(severity)
{}

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
        LOG(ERROR) << "Unknown severity setting: '" << severityStr << "', setting to default 'info'.";
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

void Logger::UpdateMinSeverity()
{
    fMinSeverity = (fConsoleSeverity <= fFileSeverity) ? fFileSeverity : fConsoleSeverity;
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
        ss << "_" << put_time(localtime(&now), "%Y-%m-%d_%H_%M_%S") << ".log";
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
    if (fFileStream.is_open())
    {
        fFileStream.close();
    }
}

bool Logger::LoggingToConsole() const
{
    return (fCurrentSeverity <= fConsoleSeverity &&
           fCurrentSeverity > Severity::nolog) ||
           fCurrentSeverity == Severity::fatal;
}

bool Logger::LoggingToFile() const
{
    return (fCurrentSeverity <= fFileSeverity &&
           fCurrentSeverity > Severity::nolog) ||
           fCurrentSeverity == Severity::fatal;
}

ostringstream& Logger::Log(const string& file, const string& line, const string& func)
{
    size_t pos = file.rfind("/");
    auto now = chrono::system_clock::now();
    auto now_c = chrono::system_clock::to_time_t(now);
    auto ns = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch()) % 1000000;

    if ((!fColored && LoggingToConsole()) || (fFileStream.is_open() && LoggingToFile()))
    {
        if (fVerbosity >= Verbosity::high)
        {
            fBWOut << "[" << fProcessName << "]"
                   << "[" << put_time(localtime(&now_c), "%H:%M:%S") << "." << setw(6) << setfill('0') << ns.count() << "]";
        }
        else if (fVerbosity == Verbosity::medium)
        {
            fBWOut << "[" << put_time(localtime(&now_c), "%H:%M:%S") << "]";
        }

        fBWOut << "[" << fSeverityNames.at(static_cast<size_t>(fCurrentSeverity)) << "]";

        if (fVerbosity == Verbosity::veryhigh)
        {
            fBWOut << "[" << file.substr(pos + 1) << ":" << line << ":" << func << "]";
        }

        fBWOut << " ";
    }

    if (fColored && (LoggingToConsole()))
    {
        if (fVerbosity >= Verbosity::high)
        {
            fColorOut << "[" << ColorOut(Color::fgBlue, fProcessName) << "]"
                      << "[" << startColor(Color::fgCyan) << put_time(localtime(&now_c), "%H:%M:%S") << "." << setw(6) << setfill('0') << ns.count() << endColor() << "]";
        }
        else if (fVerbosity == Verbosity::medium)
        {
            fColorOut << "[" << startColor(Color::fgCyan) << put_time(localtime(&now_c), "%H:%M:%S") << endColor() << "]";
        }

        fColorOut << "[" << ColoredSeverityWriter(fCurrentSeverity) << "]";

        if (fVerbosity == Verbosity::veryhigh)
        {
            fColorOut << "[" << ColorOut(Color::fgBlue, file.substr(pos + 1)) << ":" << ColorOut(Color::fgYellow, line) << ":" << ColorOut(Color::fgBlue, func) << "]";
        }

        fColorOut << " ";
    }

    return fContent;
}

void Logger::OnFatal(std::function<void()> func)
{
    fFatalCallback = func;
}

void Logger::SetCerrOnly(bool cerrOnly)
{
    fCerrOnly = cerrOnly;
}

Logger::~Logger() noexcept(false)
{
    fContent << "\n"; // "\n" + flush instead of endl makes output thread safe.

    fBWOut << fContent.str();

    if (LoggingToConsole())
    {
        if (fColored)
        {
            fColorOut << fContent.str();
            if (fCurrentSeverity == Severity::fatal || fCurrentSeverity == Severity::error || fCerrOnly)
            {
                cerr << fColorOut.str() << flush;
            }
            else
            {
                cout << fColorOut.str() << flush;
            }
        }
        else
        {
            if (fCurrentSeverity == Severity::fatal || fCurrentSeverity == Severity::error || fCerrOnly)
            {
                cerr << fBWOut.str() << flush;
            }
            else
            {
                cout << fBWOut.str() << flush;
            }
        }
    }

    if (LoggingToFile())
    {
        if (fFileStream.is_open())
        {
            fFileStream << fBWOut.str() << flush;
        }
    }

    if (fCurrentSeverity == Severity::fatal)
    {
        if (fFatalCallback)
        {
            fFatalCallback();
        }
    }
}

} // namespace fair
