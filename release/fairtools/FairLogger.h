
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
  !(gLogger->IsLogNeeded(level)) ? gLogger->GetNullStream(level) : gLogger->GetOutputStream(level, MESSAGE_ORIGIN)

#define LOG_IF(level, condition) \
  !(condition) ? gLogger->GetNullStream(level) : LOG(level)

#include "Rtypes.h"

#include <ostream>
#include <fstream>
#include <iomanip>

// Definiton of the different log levels
// TODO(F.U): Find bettter names for DEBUG1..4
enum FairLogLevel {FATAL, ERROR, WARNING, INFO,
                   DEBUG, DEBUG1, DEBUG2, DEBUG3, DEBUG4
                  };

static const char* const LogLevelString[] = { "FATAL", "ERROR", "WARNING",
    "INFO", "DEBUG", "DEBUG1",
    "DEBUG2", "DEBUG3", "DEBUG4"
                                            };
enum FairLogColor {
  /* Normal Text */
  Fair_Color_Normal = 0,

  /* Foreground Color */
  Fair_Color_ForegroundBlack   = 0x1,
  Fair_Color_ForegroundRed     = 0x2,
  Fair_Color_ForegroundGreen   = 0x3,
  Fair_Color_ForegroundYellow  = 0x4,
  Fair_Color_ForegroundBlue    = 0x5,
  Fair_Color_ForegroundMagenta = 0x6,
  Fair_Color_ForegroundCyan    = 0x7,
  Fair_Color_ForegroundWhite   = 0x8,
  Fair_Color_ForegroundMask    = 0xF,
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

class FairLogger : public std::ostream
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

    Bool_t IsLogNeeded(FairLogLevel logLevel);

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

    FairLogger& GetOutputStream(FairLogLevel level, const char* file, const char* line, const char* func);

    std::ostream& GetNullStream(FairLogLevel level) {
      fLevel=level;
      return *fNullStream;
    }

    void SetScreenStreamToCerr(bool errorStream);

    /*! \brief Stream an object to the output stream
     */
    template <class T> FairLogger&   operator<<(const T& t) {
      if (fLogToScreen && fLevel <= fLogScreenLevel) {
        *(fScreenStream) << t;
      }
      if (fLogToFile && fLevel <= fLogFileLevel) {
        *(fFileStream) << t;
      }
      return *this;
    }

    /*! \brief Pass the ios_base manipulators
     */
#if (__GNUC__ >= 3)
    FairLogger&                      operator<<(std::ios_base & (*manip) (std::ios_base&));
#endif
    FairLogger&                      operator<<(std::ostream & (*manip) (std::ostream&));

    /*! \brief End of the line
     */
    static std::ostream&        endl(std::ostream&);

    /*! \brief Flush the streams
     */
    static std::ostream&        flush(std::ostream&);

  private:
    static FairLogger* instance;
    FairLogger();
    FairLogger(const FairLogger&);
    FairLogger operator=(const FairLogger&);
    ~FairLogger();


    void Log(FairLogLevel level, const char* file, const char* line,
             const char*, const char* format, va_list  arglist);

    void LogFatalMessage(std::ostream& strm);

    void OpenLogFile();
    void CloseLogFile();

    FairLogLevel ConvertToLogLevel(const char* level) const;
    FairLogVerbosityLevel ConvertToLogVerbosityLevel(const char* level) const;

    void GetTime();

    void SetMinLogLevel();

    const char* ConvertLogLevelToString(FairLogLevel level) const
    { return LogLevelString[level]; }

    const char* fLogFileName;
    Bool_t fLogToScreen;
    Bool_t fLogToFile;
    Bool_t fLogColored;
    FairLogLevel fLogFileLevel;
    FairLogLevel fLogScreenLevel;
    FairLogVerbosityLevel fLogVerbosityLevel;
    Int_t fBufferSize;
    Int_t fBufferSizeNeeded;
    std::vector<char> fDynamicBuffer;
    char* fBufferPointer;

    static const int fgkTimeBufferLength = 80;
    char fTimeBuffer[fgkTimeBufferLength];
    FairLogLevel fMinLogLevel;
    FairLogLevel fLevel;
    std::ostream* fScreenStream;
    std::ostream* fFileStream;
    std::ostream* fNullStream;
    Bool_t fLogFileOpen;
    Bool_t fIsNewLine;
    ClassDef(FairLogger, 3)
};

extern FairLogger* gLogger;

#endif  // BASE_FAIRLOGGER_H_
