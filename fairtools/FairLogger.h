/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairLogger.h
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#ifndef BASE_FAIRLOGGER_H_
#define BASE_FAIRLOGGER_H_

#include <Logger.h>

#include "Rtypes.h" // for bool, FairLogger::Class, etc

#include <stdarg.h> // for va_list
#include <string>   // for operator<<
#include <vector>   // for vector

class FairLogger;

#define MESSAGE_ORIGIN __FILE__, CONVERTTOSTRING(__LINE__), __FUNCTION__

class FairLogger
{
  public:
    static FairLogger* GetLogger();

    void SetLogToScreen(bool enabled)
    {
        if (enabled)
        {
            fair::Logger::SetConsoleSeverity(fConsoleSeverity);
        }
        else
        {
            fair::Logger::SetConsoleSeverity(fair::Severity::fatal);
        }
    }

    void SetLogScreenLevel(const char* severity)
    {
        fConsoleSeverity = severity;
        fair::Logger::SetConsoleSeverity(fConsoleSeverity);
    }

    void SetLogToFile(bool enabled)
    {
        if (enabled)
        {
            fair::Logger::SetFileSeverity(fLogFileSeverity);
        }
        else
        {
            fair::Logger::SetFileSeverity(fair::Severity::fatal);
        }
    }

    void SetLogFileLevel(const char* severity)
    {
        fLogFileSeverity = severity;
        fair::Logger::SetFileSeverity(fLogFileSeverity);
    }

    void SetLogFileName(const std::string& name)
    {
        fLogFileName = name;
        OpenLogFile();
    }

    void SetColoredLog(bool enabled)
    {
        fair::Logger::SetConsoleColor(enabled);
    }

    void SetLogVerbosityLevel(const char* verbosity)
    {
        fair::Logger::SetVerbosity(verbosity);
    }

    bool IsLogNeeded(fair::Severity severity);

    void Fatal  (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Error  (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Warning(const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Info   (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Debug  (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Debug1 (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Debug2 (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Debug3 (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));
    void Debug4 (const char* file, const char* line, const char* func, const char* format, ...)  __attribute__((deprecated("Use 'LOG(severity) << content;' macro interface instead.")));

    static char const endl;
    static char const flush;

    void SetScreenStreamToCerr(bool /* useCerr */)
    {
    }

  private:
    static FairLogger* instance;

    FairLogger();
    FairLogger(const FairLogger&);
    FairLogger operator=(const FairLogger&);

    ~FairLogger() {}

    void Log(fair::Severity level, const char* file, const char* line, const char*, const char* format, va_list arglist);

    static void LogFatalMessage();

    void OpenLogFile()
    {
        fair::Logger::InitFileSink(fLogFileSeverity, fLogFileName, false);
    }

    void CloseLogFile()
    {
        fair::Logger::RemoveFileSink();
    }

    std::string fLogFileName;
    std::string fLogFileSeverity;
    std::string fConsoleSeverity;

    int fBufferSize;
    int fBufferSizeNeeded;
    std::vector<char> fDynamicBuffer;
    char* fBufferPointer;

    ClassDef(FairLogger, 4)
};

#define gLogger (FairLogger::GetLogger())

#endif  // BASE_FAIRLOGGER_H_
