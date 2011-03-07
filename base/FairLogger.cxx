/*
 * FairLogger.cxx
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#include "FairLogger.h"

#include "TString.h"
#include "TSystem.h";

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>

using std::cerr;
using std::endl;


FairLogger* FairLogger::instance = NULL;

FairLogger::FairLogger()
  :
  fLogFileName(""),
  fLogToScreen(kTRUE),
  fLogToFile(kTRUE),
  fLogFile(NULL),
  fLogFileLevel(logINFO),
  fLogScreenLevel(logINFO),
  fLogVerbosityLevel(verbosityLOW)
{
}

FairLogger::~FairLogger()
{
  cerr << "FairLooger::Destructor LogFileName" << fLogFileName << endl;
  if (fLogFile) {
    fclose(fLogFile);
    delete fLogFile;
  }
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
  Log(logFATAL, file, line, func, format, ap);
  va_end(ap);
  // Since Fatal indicates a fatal error it is maybe usefull to have
  // system information from the incident. Since the output on the screen
  // does not helt the noraml user, the stderr is redirected into a special
  // core dump file for later usage.
  // Fatal also indicates a problem which is so severe that the process should
  // not go on, so the process is aborted.
  fprintf(stderr, "There was a fatal error !!!\n");
  fprintf(stderr, "We stop the execution of the process at this point.\n");
  if (gSystem) {
    fprintf(stderr, "For later analysis we write a core dump to file\n");
    freopen("core_dump", "w", stderr);
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
  va_list ap;
  va_start(ap, format);
  Log(logERROR, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Warning(const char* file, const char* line, const char* func,
                         const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logWARNING, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Info(const char* file, const char* line, const char* func,
                      const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logINFO, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Debug(const char* file, const char* line, const char* func,
                       const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logDEBUG, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Debug1(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logDEBUG1, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Debug2(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logDEBUG2, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Debug3(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logDEBUG3, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Debug4(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  va_list ap;
  va_start(ap, format);
  Log(logDEBUG4, file, line, func, format, ap);
  va_end(ap);
}

void FairLogger::Log(FairLogLevel level, const char* file, const char* line,
                     const char* func, const char* format, va_list arglist)
{
  TString bla(file);
  Ssiz_t pos = bla.Last('/');
  TString s2(bla(pos+1, bla.Length()));
  TString s3 = s2 + "::" + func + ":" + line;

  const char* loglevel =  ConvertLogLevelToString(level);
  const char* s4 = s3;

  cerr << loglevel << " ";
  //  if (fLogOriginOn) {
  //    cerr<<s3<<" ";
  //  }
  cerr << format << endl;

  // Check if the log mesaage should go to the screen, the file or to
  // both sinks.

  if (fLogToFile && level <= fLogFileLevel) {
    LogToFile(loglevel, s3, format, arglist);
  }
  if (fLogToScreen && level <= fLogScreenLevel) {
    LogToScreen(loglevel, s3, format, arglist);
  }
}

void FairLogger::LogToScreen(const char* loglevel, const char* origin,
                             const char* msg, va_list arglist)
{
  fprintf(stderr, "[%s] ", loglevel);
  if ( fLogVerbosityLevel == verbosityHIGH ) {
    // Add the timestamd
    // TODO(F.U.): Implement some timestamp
    fprintf(stderr, "[12-12-12] ");
  }
  if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
    fprintf(stderr, "[%s] ", origin);
  }
  //  fprintf(fLogFile, msg, arglist);
  //vfprintf(stderr, msg, arglist);
  fprintf(stderr, "\n");
  fflush(stderr);
}

void FairLogger::LogToFile(const char* loglevel, const char* origin,
                           const char* msg, va_list arglist)
{
  // Chek if the log file is open. If not open the logfile
  if (fLogFile == NULL) {
    OpenLogFile();
  }
  fprintf(fLogFile, "[%s] ", loglevel);
  if ( fLogVerbosityLevel == verbosityHIGH ) {
    // Add the timestamd
    // TODO(F.U.): Implement some timestamp
    fprintf(fLogFile, "[12-12-12] ");
  }
  if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
    fprintf(fLogFile, "[%s] ", origin);
  }
  //  fprintf(fLogFile, msg, arglist);
  vfprintf(fLogFile, msg, arglist);
  fprintf(fLogFile, "\n");
  fflush(fLogFile);
}

void FairLogger::CloseLogFile()
{
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

  // Open the log file and check if it is open.
  cerr << "Openning log file: " << logfile << endl;

  fLogFile = fopen(logfile, "w");
  if (fLogFile == NULL) {
    cerr << "Cannot open log file: " << logfile;
  }

  assert(fLogFile != NULL);
}

FairLogLevel FairLogger::ConvertToLogLevel(const char* levelc) const
{
  // Convert string to upper case
  // Return the according log level
  // in case the level is not known return info level
  TString level = levelc;
  level.ToUpper();
  if (level == "FATAL") { return logFATAL; }
  if (level == "ERROR") { return logERROR; }
  if (level == "WARNING") { return logWARNING; }
  if (level == "INFO") { return logINFO; }
  if (level == "DEBUG") { return logDEBUG; }
  if (level == "DEBUG1") { return logDEBUG1; }
  if (level == "DEBUG2") { return logDEBUG2; }
  if (level == "DEBUG3") { return logDEBUG3; }
  if (level == "DEBUG4") { return logDEBUG4; }
  return logINFO;
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
  return verbosityLOW;
}

ClassImp(FairLogger)
