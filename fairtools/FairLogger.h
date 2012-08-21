
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
#define LOG(level)        \
  GetOutputStream(level, MESSAGE_ORIGIN)

#define LEND() \
  fLogger->LineEnd();

#include "TObject.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FairTeeStream.h"

// Definiton of the different log levels
// TODO(F.U): Find bettter names for DEBUG1..4
enum FairLogLevel {FATAL, ERROR, WARNING, INFO,
                   DEBUG, DEBUG1, DEBUG2, DEBUG3, DEBUG4
                  };

static const char* const LogLevelString[] = { "FATAL", "ERROR", "WARNING",
    "INFO", "DEBUG", "DEBUG1",
    "DEBUG2", "DEBUG3", "DEBUG4"
                                            };

static const char* const LogLevelColor[] = { "\33[01;31m", "\33[01;33m",
    "\33[00;33m", "\33[01;33m",
    "\33[01;32m", "\33[01;32m",
    "\33[01;32m", "\33[01;32m",
    "\33[01;32m"
                                           };

// Definition of the different verbosity levels of the output
// With the level HIGH the output contains a time stamp, the location from
// which the message commes (File, Function and Line) toegether with the
// log level and the mesage to be printed.
// The verbosity level MEDIUM has the above information without the time stamp
// The LOW verbosity level prints only the log level together with the message
enum FairLogVerbosityLevel {verbosityHIGH, verbosityMEDIUM, verbosityLOW};
static const char* const LogVerbosityString[] = { "HIGH", "MEDIUM", "LOW" };

class FairLogger //: public TObject
{
  public:
    static FairLogger* GetLogger();

    void SetLogFileName(const char* name);

    void SetLogToScreen(Bool_t log1) {
      fLogToScreen = log1;
      if (!fLogToScreen) {
        SetLogScreenLevel("FATAL");
      }
    }

    void SetLogToFile(Bool_t log1) {
      fLogToFile = log1;
      if (!fLogToFile) {
        SetLogFileLevel("FATAL");
      }
    }

    void SetColoredLog(Bool_t log1) { fLogColored = log1; }

    void SetLogFileLevel(const char* level) {
      fLogFileLevel = ConvertToLogLevel(level);
      SetMinLogLevel();
    }

    void SetLogScreenLevel(const char* level) {
      fLogScreenLevel = ConvertToLogLevel(level);
      SetMinLogLevel();
    }

    void SetLogVerbosityLevel(const char* vlevel) {
      fLogVerbosityLevel = ConvertToLogVerbosityLevel(vlevel);
    }

    void SetNewStyle(Bool_t newstyle) { fNewStyle = newstyle;}
    Bool_t GetNewStyle() { return fNewStyle;}

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

    std::ostream& GetOutputStream(FairLogLevel level, const char* file, const char* line, const char* func);

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

    void LogTo(FILE* out, const char* loglevel, const char* origin);

    FairLogLevel ConvertToLogLevel(const char* level) const;
    FairLogVerbosityLevel ConvertToLogVerbosityLevel(const char* level) const;

    void GetTime();

    Bool_t IsLogNeeded(FairLogLevel logLevel);

    void SetMinLogLevel();

    const char* ConvertLogLevelToString(FairLogLevel level) const
    { return LogLevelString[level]; }

    const char* fLogFileName;
    Bool_t fLogToScreen;
    Bool_t fLogToFile;
    Bool_t fLogColored;
    FILE*  fLogFile;
    FairLogLevel fLogFileLevel;
    FairLogLevel fLogScreenLevel;
    FairLogVerbosityLevel fLogVerbosityLevel;
    static const int fgkBufferLength = 10024;
    Int_t fBufferSize;
    Int_t fBufferSizeNeeded;
    std::vector<char> fDynamicBuffer;
    char* fBufferPointer;

    char fBuffer[fgkBufferLength];
    static const int fgkTimeBufferLength = 80;
    char fTimeBuffer[fgkTimeBufferLength];
    FairLogLevel fMinLogLevel;
    FairLogLevel fLevel;
    std::ostream* fScreenStream;
    std::ostream* fNullStream;
    std::ostream* fTeeStream;
    std::ostream* fReturnStream;
    std::ofstream fFileStream;
    FairTeeStream  fTee;
    Bool_t fNewStyle;
    Bool_t fLogFileOpen;
    ClassDef(FairLogger, 1)
};

#endif  // BASE_FAIRLOGGER_H_
