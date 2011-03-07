/*
 * FairLogger.h
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#ifndef BASE_FAIRLOGGER_H_
#define BASE_FAIRLOGGER_H_


#define IMP_CONVERTTOSTRING(s)  # s
#define CONVERTTOSTRING(s)      IMP_CONVERTTOSTRING(s)
#define MESSAGE_ORIGIN          __FILE__, CONVERTTOSTRING(__LINE__), __FUNCTION__

#include "TObject.h"

// Definiton of the different log levels
// TODO(F.U): Find bettter names for DEBUG1..4
enum FairLogLevel {logFATAL, logERROR, logWARNING, logINFO,
                   logDEBUG, logDEBUG1, logDEBUG2, logDEBUG3, logDEBUG4
                  };
static const char* const LogLevelString[] = { "FATAL", "ERROR", "WARNING",
    "INFO", "DEBUG", "DEBUG1",
    "DEBUG2", "DEBUG3", "DEBUG4"
                                            };

// Definition of the different verbosity levels of the output
// With the level HIGH the output contains a time stamp, the location from
// which the message commes (File, Function and Line) toegether with the
// log level and the mesage to be printed.
// The verbosity level MEDIUM has the above information without the time stamp
// The LOW verbosity level prints only the log level together with the message
enum FairLogVerbosityLevel {verbosityHIGH, verbosityMEDIUM, verbosityLOW};
static const char* const LogVerbosityString[] = { "HIGH", "MEDIUM", "LOW" };

class FairLogger : public TObject
{
  public:
    static FairLogger* GetLogger();

    void SetLogFileName(const char* name) { fLogFileName = name; }

    void SetLogToScreen(Bool_t log1) { fLogToScreen = log1; }

    void SetLogToFile(Bool_t log1) { fLogToFile = log1; }

    void SetLogFileLevel(const char* level) {
      fLogFileLevel = ConvertToLogLevel(level);
    }

    void SetLogScreenLevel(const char* level) {
      fLogScreenLevel = ConvertToLogLevel(level);
    }

    void SetLogVerbosityLevel(const char* vlevel) {
      fLogVerbosityLevel = ConvertToLogVerbosityLevel(vlevel);
    }

    void Fatal(const char* file, const char* line, const char* func,
               const char* format, ...);

    void Error(const char* file, const char* line, const char* func,
               const char* format, ...);

    void Warning(const char* file, const char* line, const char* func,
                 const char* format, ...);

    void Info(const char* file, const char* line, const char* func,
              const char* format, ...);

    void Debug(const char* file, const char* line, const char* func,
               const char* format, ...);
    void Debug1(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug2(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug3(const char* file, const char* line, const char* func,
                const char* format, ...);
    void Debug4(const char* file, const char* line, const char* func,
                const char* format, ...);

  private:
    static FairLogger* instance;
    FairLogger();
    FairLogger(const FairLogger&);
    FairLogger operator=(const FairLogger&);
    ~FairLogger();

    void Log(FairLogLevel level, const char* file, const char* line,
             const char*, const char* format, va_list  arglist);

    void OpenLogFile();
    void CloseLogFile();
    void LogToScreen(const char* loglevel, const char* origin, const char* msg,
                     va_list arglist);
    void LogToFile(const char* loglevel, const char* origin, const char* msg,
                   va_list arglist);

    FairLogLevel ConvertToLogLevel(const char* level) const;
    FairLogVerbosityLevel ConvertToLogVerbosityLevel(const char* level) const;

    const char* ConvertLogLevelToString(FairLogLevel level) const
    { return LogLevelString[level]; }

    const char* fLogFileName;
    Bool_t fLogToScreen;
    Bool_t fLogToFile;
    FILE*  fLogFile;
    FairLogLevel fLogFileLevel;
    FairLogLevel fLogScreenLevel;
    FairLogVerbosityLevel fLogVerbosityLevel;
    ClassDef(FairLogger, 1)
};

#endif  // BASE_FAIRLOGGER_H_
