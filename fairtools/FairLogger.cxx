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

using std::cerr;
using std::endl;
using std::setw;
using std::right;
using std::left;


FairLogger* FairLogger::instance = NULL;

FairLogger::FairLogger()
  :
  fLogFileName(""),
  fLogToScreen(kTRUE),
  fLogToFile(kFALSE),
  fLogColored(kFALSE),
  fLogFile(NULL),
  fLogFileLevel(INFO),
  fLogScreenLevel(INFO),
  fLogVerbosityLevel(verbosityLOW),
  fBufferSize(1024),
  fBufferSizeNeeded(-1),
  fDynamicBuffer(fBufferSize),
  fBufferPointer(&fDynamicBuffer[0]),
  fBuffer(),
  fMinLogLevel(INFO),
  fScreenStream(&std::cerr),
  fNullStream(new ostream(0)),
  fTeeStream(),
  fTee(),
  fNewStyle(kTRUE),
  fFileStream(),
  fLogFileOpen(kFALSE)
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
  Log(FATAL, file, line, func, format, ap);
  va_end(ap);
  // Since Fatal indicates a fatal error it is maybe usefull to have
  // system information from the incident. Since the output on the screen
  // does not helt the noraml user, the stderr is redirected into a special
  // core dump file for later usage.
  // Fatal also indicates a problem which is so severe that the process should
  // not go on, so the process is aborted.
  fprintf(stderr, "[FATAL  ] We stop the execution of the process at this point.\n");
  if (gSystem) {
    TString corefile = "core_dump_";
    Int_t PID = gSystem->GetPid();
    corefile += PID;

    fprintf(stderr, "[FATAL  ] For later analysis we write a core dump to %s\n",
            (const char*)corefile);
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
  if (IsLogNeeded(ERROR)) {
    va_list ap;
    va_start(ap, format);
    Log(ERROR, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Warning(const char* file, const char* line, const char* func,
                         const char* format, ...)
{
  if (IsLogNeeded(WARNING)) {
    va_list ap;
    va_start(ap, format);
    Log(WARNING, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Info(const char* file, const char* line, const char* func,
                      const char* format, ...)
{
  if (IsLogNeeded(INFO)) {
    va_list ap;
    va_start(ap, format);
    Log(INFO, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug(const char* file, const char* line, const char* func,
                       const char* format, ...)
{
  if (IsLogNeeded(DEBUG)) {
    va_list ap;
    va_start(ap, format);
    Log(DEBUG, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug1(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(DEBUG1)) {
    va_list ap;
    va_start(ap, format);
    Log(DEBUG1, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug2(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(DEBUG2)) {
    va_list ap;
    va_start(ap, format);
    Log(DEBUG2, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug3(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(DEBUG3)) {
    va_list ap;
    va_start(ap, format);
    Log(DEBUG3, file, line, func, format, ap);
    va_end(ap);
  }
}

void FairLogger::Debug4(const char* file, const char* line, const char* func,
                        const char* format, ...)
{
  if (IsLogNeeded(DEBUG4)) {
    va_list ap;
    va_start(ap, format);
    Log(DEBUG4, file, line, func, format, ap);
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

  if (fNewStyle == kTRUE) {

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
        GetOutputStream(level, file, line, func) <<
            std::string(fBufferPointer, (size_t) fBufferSizeNeeded)<<" "<<std::endl;
        break;
      }

      // vsnprintf reported that it wanted to write more characters
      // than we allotted.  So try again using a dynamic buffer.  This
      // doesn't happen very often if we chose our initial size well.
      fBufferSize = (fBufferSizeNeeded > 0)
                    ? (fBufferSizeNeeded+1) : (fBufferSize*2);

      fDynamicBuffer.resize (fBufferSize);
    }
  } else {

    vsprintf(fBuffer, format, arglist);

    // Don't print the full path to the source file but only the file name.
    // Create a string containing the information about the file name, the
    // function name and the line number from which the log message originates
    TString bla(file);
    Ssiz_t pos = bla.Last('/');
    TString s2(bla(pos+1, bla.Length()));
    TString s3 = s2 + "::" + func + ":" + line;

    // Convert to const char*
    const char* loglevel =  ConvertLogLevelToString(level);
    const char* s4 = s3;

    // Check if the log mesaage should go to the screen, the file or to
    // both sinks.

    if (fLogToFile && level <= fLogFileLevel) {
      // Chek if the log file is open. If not open the logfile
      LogTo(fLogFile, loglevel, s4);
    }
    if (fLogToScreen && level <= fLogScreenLevel) {
      LogTo(stderr, loglevel, s4);
    }
  }
}

void FairLogger::SetLogFileName(const char* name)
{
  if (fLogFile != NULL) {
    CloseLogFile();
    remove(fLogFileName);
  }
  fLogFileName = name;
  OpenLogFile();

}

void FairLogger::LogTo(FILE* out, const char* loglevel, const char* origin)
{
  if ( loglevel == "FATAL") {
    fLogVerbosityLevel = verbosityHIGH;
  }
  fprintf(out, "[%-7s] ", loglevel);
  if ( fLogVerbosityLevel == verbosityHIGH ) {
    GetTime();
    fprintf(out, "%s", fTimeBuffer);
  }
  if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
    fprintf(out, "[%s] ", origin);
  }
  fprintf(out, "%s ", fBuffer);
  fprintf(out, "\n");
  fflush(out);
}


void FairLogger::CloseLogFile()
{

  if (fNewStyle == kTRUE) {
    fFileStream.close();
    fTee.SetInputToCerr();
    fTeeStream = fTee.GetTeeStream();
  } else {
    fclose(fLogFile);
  }

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
  //  std::cout<<"LogFile: "<<logfile<<std::endl;
  if (fNewStyle == kTRUE) {
    fFileStream.close();
    fFileStream.open(logfile.Data());
    fTee.SetInput(std::cerr, fFileStream);
    fTeeStream = fTee.GetTeeStream();
  } else {
    // Open the log file and check if it is open.

    fLogFile = fopen(logfile, "w");
    if (fLogFile == NULL) {
      cerr << "Cannot open log file: " << logfile;
    }
    cerr << "[INFO   ] Openning log file: " << logfile << endl;
    cerr << " " << endl;

    assert(fLogFile != NULL);
  }
  fLogFileOpen = kTRUE;
}

FairLogLevel FairLogger::ConvertToLogLevel(const char* levelc) const
{
  // Convert string to upper case
  // Return the according log level
  // in case the level is not known return info level
  TString level = levelc;
  level.ToUpper();
  if (level == "FATAL") { return FATAL; }
  if (level == "ERROR") { return ERROR; }
  if (level == "WARNING") { return WARNING; }
  if (level == "INFO") { return INFO; }
  if (level == "DEBUG") { return DEBUG; }
  if (level == "DEBUG1") { return DEBUG1; }
  if (level == "DEBUG2") { return DEBUG2; }
  if (level == "DEBUG3") { return DEBUG3; }
  if (level == "DEBUG4") { return DEBUG4; }
  cerr<<"Log level \""<<level<<"\" not supported. Use default level \"INFO\"."<<endl;
  return INFO;
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
  cerr<<"Verbosity level \""<<vlevel<<"\" not supported. Use default level \"LOW\"."<<endl;
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

std::ostream& FairLogger::GetOutputStream(FairLogLevel level, const char* file, const char* line, const char* func)
{

  // here we need 4 cases
  // level > flogScreenLevel && level > fLogFileLevel : don't write
  // level <= flogScreenLevel && level <= fLogFileLevel : write both
  // level <= flogScreenLevel && level > fLogFileLevel : write Screen
  // level > flogScreenLevel && level <= fLogFileLevel : write File
  //  std::cout<<"Level: "<< ConvertLogLevelToString(level) <<std::endl;

  if( ( !fLogToFile && !fLogToScreen) || level > fMinLogLevel  ) {
    return *fNullStream;
  } else {
    if ( (fLogToScreen && level <= fLogScreenLevel) &&
         (fLogToFile && level <= fLogFileLevel) ) {
      fReturnStream = fTeeStream;
    } else if ( fLogToScreen && level <= fLogScreenLevel ) {
      fReturnStream = fScreenStream;
    } else if ( fLogToFile && level <= fLogFileLevel ) {
      fReturnStream = &fFileStream;
    } else {
      return *fNullStream;
    }
  }

  *fReturnStream << "[" << setw(7) << left << LogLevelString[level] <<"] ";

  if ( fLogVerbosityLevel == verbosityHIGH ) {
    GetTime();
    *fReturnStream << fTimeBuffer;
  }
  if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
    TString bla(file);
    Ssiz_t pos = bla.Last('/');
    TString s2(bla(pos+1, bla.Length()));
    TString s3 = s2 + "::" + func + ":" + line;
    *fReturnStream << "[" << s3 <<"] ";
  }
  return *fReturnStream;
}

ClassImp(FairLogger)
