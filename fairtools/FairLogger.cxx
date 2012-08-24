/*
 * FairLogger.cxx
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#include "FairLogger.h"

#include "TString.h"
#include "TSystem.h"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

FairLogger* FairLogger::instance = NULL;

FairLogger::FairLogger()
  :
  fLogFileName(""),
  fLogToScreen(kTRUE),
  fLogToFile(kFALSE),
  fLogColored(kFALSE),
  fLogFileLevel(InfoLog),
  fLogScreenLevel(InfoLog),
  fLogVerbosityLevel(verbosityLOW),
  fBufferSize(1024),
  fBufferSizeNeeded(-1),
  fDynamicBuffer(fBufferSize),
  fBufferPointer(&fDynamicBuffer[0]),
  fMinLogLevel(InfoLog),
  fScreenStream(&std::cerr),
  fNewFileStream(NULL),
  fNullStream(new ostream(0)),
  fLogFileOpen(kFALSE)
{
}

FairLogger::~FairLogger()
{
  CloseLogFile();
}

FairLogger* FairLogger::GetLogger()
{
  if (!instance) {
    instance = new FairLogger();
  }
  return instance;
}

void FairLogger::Fatal(const char* file, const char* line, const char* func,
                       const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(FatalLog, file, line, func, format, ap);
  va_end(ap);

  // Since Fatal indicates a fatal error it is maybe usefull to have
  // system information from the incident. Since the output on the screen
  // does not helt the noraml user, the stderr is redirected into a special
  // core dump file for later usage.
  // Fatal also indicates a problem which is so severe that the process should
  // not go on, so the process is aborted.
  GetNewOutputStream(FatalLog, file, line, func) <<
      "[FATAL  ] We stop the execution of the process at this point." <<
      " " << FairLogger::endl;

  if (gSystem) {
    TString corefile = "core_dump_";
    Int_t PID = gSystem->GetPid();
    corefile += PID;

    GetNewOutputStream(FatalLog, file, line, func) <<
        "[FATAL  ] For later analysis we write a core dump to" << corefile <<
        " " << FairLogger::endl;
    freopen(corefile, "w", stderr);
    gSystem->StackTrace();
    fclose(stderr);
    gSystem->Abort(1);
  } else {
    abort();
  }
}

void FairLogger::Error(const char* file, const char* line, const char* func,
                       const char* format, ...)
{
  if (IsLogNeeded(ErrorLog)) {
    va_list ap;
    va_start(ap, format);
    Log(ErrorLog, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Warning(const char* file, const char* line, const char* func,
                         const char* format, ...)
{
  if (IsLogNeeded(WarningLog)) {
    va_list ap;
    va_start(ap, format);
    Log(WarningLog, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Info(const char* file, const char* line, const char* func,
                      const char* format, ...)
{
  if (IsLogNeeded(InfoLog)) {
    va_list ap;
    va_start(ap, format);
    Log(InfoLog, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug(const char* file, const char* line, const char* func,
                       const char* format, ...)
{
  if (IsLogNeeded(DebugLog)) {
    va_list ap;
    va_start(ap, format);
    Log(DebugLog, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug1(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(Debug1Log)) {
    va_list ap;
    va_start(ap, format);
    Log(Debug1Log, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug2(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(Debug2Log)) {
    va_list ap;
    va_start(ap, format);
    Log(Debug2Log, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug3(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(Debug3Log)) {
    va_list ap;
    va_start(ap, format);
    Log(Debug3Log, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug4(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(Debug4Log)) {
    va_list ap;
    va_start(ap, format);
    Log(Debug4Log, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Log(FairLogLevel level, const char* file, const char* line,
                     const char* func, const char* format, va_list arglist)
{
  // If the format string together with the argument list was used once it can't
  // be used another time. Don't know why but if we do so the arguments are not
  // correct any longer and the program may crash (On Mac OSX). Even if it does
  // not crash it does not work as expected.
  // To vercome the problem the output is written to a buffer which then can be
  // used several times.

  if(fLogToFile && !fLogFileOpen) {
    OpenLogFile();
  }

  fLevel = level;
  while (1) {
    fBufferSizeNeeded = vsnprintf(fBufferPointer, fBufferSize, format, arglist);

    // Try to vsnprintf into our buffer.
    //    int needed = vsnprintf (buf, size, fmt, ap);
    // NB. C99 (which modern Linux and OS X follow) says vsnprintf
    // failure returns the length it would have needed.  But older
    // glibc and current Windows return -1 for failure, i.e., not
    // telling us how much was needed.

    if (fBufferSizeNeeded <= (int)fBufferSize && fBufferSizeNeeded >= 0) {
      // It fit fine so we're done.
      GetNewOutputStream(level, file, line, func) <<
          std::string(fBufferPointer, (size_t) fBufferSizeNeeded)<<
          " " << FairLogger::endl;

      break;
    }

    // vsnprintf reported that it wanted to write more characters
    // than we allotted.  So try again using a dynamic buffer.  This
    // doesn't happen very often if we chose our initial size well.
    fBufferSize = (fBufferSizeNeeded > 0)
                  ? (fBufferSizeNeeded+1) : (fBufferSize*2);

    fDynamicBuffer.resize (fBufferSize);
  }
}

void FairLogger::SetLogFileName(const char* name)
{
  if (fNewFileStream) {
    CloseLogFile();
    delete fNewFileStream;
    fNewFileStream = NULL;
    remove(fLogFileName);
  }

  fLogFileName = name;
  OpenLogFile();

}

void FairLogger::CloseLogFile()
{
  dynamic_cast<ofstream*>(fNewFileStream)->close();
}

void FairLogger::OpenLogFile()
{
  // Check if the log file name is set. If not use a default logfile with
  // the name FairLogfile_<pid>.log. <pid> is the pid of the runing job.
  TString logfile = fLogFileName;
  if (logfile.IsNull()) {
    Int_t PID = gSystem->GetPid();
    logfile = "FairLogfile_";
    logfile += PID;
    logfile += ".log";

  }

  // Check if filename contains a full path. If not create logfile
  // in the current directory.
  // TODO(F.U.): Check if the path exists and is writeable.
  if (!logfile.Contains('/')) {
    logfile = "./" + logfile;
  }

  if (fNewFileStream) {
    CloseLogFile();
    delete fNewFileStream;
    fNewFileStream = NULL;
  }

  fNewFileStream = new std::ofstream(logfile.Data());

  fLogFileOpen = kTRUE;
}

FairLogLevel FairLogger::ConvertToLogLevel(const char* levelc) const
{
  // Convert string to upper case
  // Return the according log level
  // in case the level is not known return info level
  TString level = levelc;
  level.ToUpper();
  if (level == "FATAL") { return FatalLog; }
  if (level == "ERROR") { return ErrorLog; }
  if (level == "WARNING") { return WarningLog; }
  if (level == "INFO") { return InfoLog; }
  if (level == "DEBUG") { return DebugLog; }
  if (level == "DEBUG1") { return Debug1Log; }
  if (level == "DEBUG2") { return Debug2Log; }
  if (level == "DEBUG3") { return Debug3Log; }
  if (level == "DEBUG4") { return Debug4Log; }
  std::cerr<<"Log level \""<<level<<"\" not supported. Use default level \"INFO\"."<<std::endl;
  return InfoLog;
}

FairLogVerbosityLevel FairLogger::ConvertToLogVerbosityLevel(const char* vlevelc) const
{
  // Convert string to upper case
  // Return the according log verbosity level
  // in case the level is not known return low verbosity level
  TString vlevel = vlevelc;
  vlevel.ToUpper();
  if (vlevel == "HIGH") { return verbosityHIGH; }
  if (vlevel == "MEDIUM") { return verbosityMEDIUM; }
  if (vlevel == "LOW") { return verbosityLOW; }
  std::cerr<<"Verbosity level \""<<vlevel<<"\" not supported. Use default level \"LOW\"."<<std::endl;
  return verbosityLOW;
}

void FairLogger::GetTime()
{
  time_t rawtime;
  struct tm* timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(fTimeBuffer, 80, "[%d.%m.%Y %X] ", timeinfo);
}
void FairLogger::SetMinLogLevel()
{
  fMinLogLevel = (fLogScreenLevel <= fLogFileLevel) ? fLogFileLevel : fLogScreenLevel;
}

Bool_t FairLogger::IsLogNeeded(FairLogLevel logLevel)
{
  if (logLevel <= fMinLogLevel) {
    return true;
  } else {
    return false;
  }
}

FairLogger& FairLogger::GetNewOutputStream(FairLogLevel level, const char* file, const char* line, const char* func)
{
  fLevel =level;

  if ( fLogToScreen && level <= fLogScreenLevel ) {
    if (fLogColored) {
      *fScreenStream << LogLevelColor[level];
    }

    *fScreenStream << "[" << std::setw(7) << std::left << LogLevelString[level] <<"] ";

    if ( fLogVerbosityLevel == verbosityHIGH ) {
      GetTime();
      *fScreenStream << fTimeBuffer;
    }

    if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
      TString bla(file);
      Ssiz_t pos = bla.Last('/');
      TString s2(bla(pos+1, bla.Length()));
      TString s3 = s2 + "::" + func + ":" + line;
      *fScreenStream << "[" << s3 <<"] ";
    }
  }

  if ( fLogToFile && level <= fLogFileLevel ) {
    if(!fLogFileOpen) {
      OpenLogFile();
    }

    *fNewFileStream << "[" << std::setw(7) << std::left << LogLevelString[level] <<"] ";

    if ( fLogVerbosityLevel == verbosityHIGH ) {
      GetTime();
      *fNewFileStream << fTimeBuffer;
    }

    if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
      TString bla(file);
      Ssiz_t pos = bla.Last('/');
      TString s2(bla(pos+1, bla.Length()));
      TString s3 = s2 + "::" + func + ":" + line;
      *fNewFileStream << "[" << s3 <<"] ";
    }
  }

  return *this;
}


#if (__GNUC__ >= 3)
FairLogger& FairLogger::operator<<(std::ios_base& (*manip) (std::ios_base&))
{
  if (fLogToScreen && (fLevel <= fLogScreenLevel || fLevel <= fLogFileLevel) ) {
    *(fScreenStream) << manip;
  }

  if (fLogToFile && !fLogToScreen && (fLevel <= fLogScreenLevel || fLevel <= fLogFileLevel) ) {
    *(fNewFileStream) << manip;
  }

  return *this;
}
#endif

FairLogger& FairLogger::operator<<(std::ostream& (*manip) (std::ostream&))
{
  if (fLogToScreen && (fLevel <= fLogScreenLevel || fLevel <= fLogFileLevel) ) {
    *(fScreenStream) << manip;
  }

  if (fLogToFile && !fLogToScreen && (fLevel <= fLogScreenLevel || fLevel <= fLogFileLevel) ) {
    *(fNewFileStream) << manip;
  }

  return *this;
}

std::ostream&  FairLogger::endl(std::ostream& strm)
{
  if (FairLogger::instance->fLogToScreen &&
      FairLogger::instance->fLevel <= FairLogger::instance->fLogScreenLevel) {
    if (FairLogger::instance->fLogColored) {
      *(FairLogger::instance->fScreenStream) << "\33[00;30m" << std::endl;
    } else {
      *(FairLogger::instance->fScreenStream) << std::endl;
    }
  }

  if (FairLogger::instance->fLogToFile &&
      FairLogger::instance->fLevel <= FairLogger::instance->fLogFileLevel) {
    *(FairLogger::instance->fNewFileStream) << std::endl;
  }

  return strm;
}

std::ostream& FairLogger::flush(std::ostream& strm)
{
  if (FairLogger::instance->fLogToScreen) {
    *(FairLogger::instance->fScreenStream) << std::flush;
  }
  if (FairLogger::instance->fLogToFile) {
    *(FairLogger::instance->fNewFileStream) << std::flush;
  }
  return strm;
}


ClassImp(FairLogger)
