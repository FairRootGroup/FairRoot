/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairLogger.cxx
 *
 *  Created on: Mar 03, 2011
 *      Author: f.uhlig
 */

#include "FairLogger.h"

#include "Riosfwd.h"                    // for ostream, ofstream
#include "TString.h"                    // for TString, operator==, etc
#include "TSystem.h"                    // for gSystem, TSystem

#include <stddef.h>                     // for size_t
#include <stdio.h>                      // for fclose, freopen, remove, etc
#include <sys/select.h>                 // for time_t
#include <time.h>                       // for localtime, strftime, time
#include <cstdlib>                      // for NULL, abort
#include <iomanip>                      // for operator<<, setw
#include <iostream>                     // for cout, cerr

FairLogger* gLogger = FairLogger::GetLogger();

FairLogger* FairLogger::instance = NULL;

FairLogger::FairLogger()
  :
  fLogFileName(""),
  fLogToScreen(kTRUE),
  fLogToFile(kFALSE),
  fLogColored(kFALSE),
  fLogFileLevel(INFO),
  fLogScreenLevel(INFO),
  fLogVerbosityLevel(verbosityLOW),
  fBufferSize(1024),
  fBufferSizeNeeded(-1),
  fDynamicBuffer(fBufferSize),
  fBufferPointer(&fDynamicBuffer[0]),
  fMinLogLevel(INFO),
  fLevel(INFO),
  fScreenStream(&std::cout),
  fFileStream(NULL),
  fNullStream(new std::ostream(0)),
  fLogFileOpen(kFALSE),
  fIsNewLine(kTRUE)
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
  Log(FATAL, file, line, func, format, ap);
  va_end(ap);
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
  if (fFileStream) {
    CloseLogFile();
    delete fFileStream;
    fFileStream = NULL;
    if( remove(fLogFileName) != 0 ) {
      LOG(ERROR)<<"Could not delete log file "<< fLogFileName << "." << FairLogger::endl;
    }
    
  }

  fLogFileName = name;
  OpenLogFile();

}

void FairLogger::CloseLogFile()
{
  std::ofstream* tmp =NULL;
  if (fFileStream) {
    tmp = dynamic_cast<std::ofstream*>(fFileStream);
    if (tmp) {
      tmp->close();
    }
  }
  delete tmp;
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

  if (fFileStream) {
    CloseLogFile();
    delete fFileStream;
    fFileStream = NULL;
  }

  fFileStream = new std::ofstream(logfile.Data());

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
  LOG(ERROR)<<"Log level \""<<level<<"\" not supported. Use default level \"INFO\"."<<FairLogger::endl;
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
  LOG(ERROR)<<"Verbosity level \""<<vlevel<<"\" not supported. Use default level \"LOW\"."<<FairLogger::endl;
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

FairLogger& FairLogger::GetOutputStream(FairLogLevel level, const char* file, const char* line, const char* func)
{

  fLevel = level;

  if (level == FATAL) {
    fLogToScreen = true;
    fLogVerbosityLevel = verbosityHIGH;
    fLogColored = true;
  }


  if (fIsNewLine) {
    if ( (fLogToScreen && level <= fLogScreenLevel) ) {

      if ( fLogColored ) {
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

      *fFileStream << "[" << std::setw(7) << std::left << LogLevelString[level] <<"] ";

      if ( fLogVerbosityLevel == verbosityHIGH ) {
        GetTime();
        *fFileStream << fTimeBuffer;
      }

      if ( fLogVerbosityLevel <= verbosityMEDIUM ) {
        TString bla(file);
        Ssiz_t pos = bla.Last('/');
        TString s2(bla(pos+1, bla.Length()));
        TString s3 = s2 + "::" + func + ":" + line;
        *fFileStream << "[" << s3 <<"] ";
      }
    }
    fIsNewLine = kFALSE;
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
    *(fFileStream) << manip;
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
    *(fFileStream) << manip;
  }

  return *this;
}

std::ostream&  FairLogger::endl(std::ostream& strm)
{

  gLogger->fIsNewLine = kTRUE;
  if ( (gLogger->fLogToScreen && gLogger->fLevel <= gLogger->fLogScreenLevel) ) {
    if (gLogger->fLogColored) {
      // reset format to default 
      *(gLogger->fScreenStream) << "\33[0m" << std::endl;
    } else {
      *(gLogger->fScreenStream) << std::endl;
    }
  }

  if (gLogger->fLogToFile &&
      gLogger->fLevel <= gLogger->fLogFileLevel) {
    *(gLogger->fFileStream) << std::endl;
  }

  if (gLogger->fLevel == FATAL) {
    flush(strm);
    gLogger->LogFatalMessage(strm);
  }

  return strm;
}

std::ostream& FairLogger::flush(std::ostream& strm)
{
  if (gLogger->fLogToScreen) {
    *(gLogger->fScreenStream) << std::flush;
  }
  if (gLogger->fLogToFile) {
    *(gLogger->fFileStream) << std::flush;
  }
  return strm;
}

// coverity[+kill]
void FairLogger::LogFatalMessage(std::ostream& strm)
{
  // Since Fatal indicates a fatal error it is maybe usefull to have
  // system information from the incident. Since the output on the screen
  // does not help the noraml user, the stderr is redirected into a special
  // core dump file for later usage.
  // Fatal also indicates a problem which is so severe that the process should
  // not go on, so the process is aborted.

  *fScreenStream << LogLevelColor[FATAL];

  *fScreenStream << "[" << std::setw(7) << std::left << LogLevelString[FATAL] <<"] ";

  GetTime();
  *fScreenStream << fTimeBuffer;

  *fScreenStream <<  "We stop the execution of the process at this point.\n";

  if ( fLogToFile ) {
    *fFileStream << "[" << std::setw(7) << std::left << LogLevelString[FATAL] <<"] ";

    *fFileStream << fTimeBuffer;
    *fFileStream <<  "We stop the execution of the process at this point.\n";
  }

  if (gSystem) {
    TString corefile = "core_dump_";
    Int_t PID = gSystem->GetPid();
    corefile += PID;


    *fScreenStream << LogLevelColor[FATAL];

    *fScreenStream << "[" << std::setw(7) << std::left << LogLevelString[FATAL] <<"] ";

    GetTime();
    *fScreenStream << fTimeBuffer;

    *fScreenStream << "For later analysis we write a core dump to " <<
                   corefile << " \n";


    if ( fLogToFile ) {
      *fFileStream << "[" << std::setw(7) << std::left << LogLevelString[FATAL] <<"] ";

      *fFileStream << fTimeBuffer;
      *fFileStream << "For later analysis we write a core dump to" <<
                   corefile << "\n";
    }

    // reset format to default before exiting
    *(gLogger->fScreenStream) << "\33[0m" << std::endl; 

    flush(strm);
    freopen(corefile, "w", stderr);
    gSystem->StackTrace();
    fclose(stderr);
    gSystem->Abort(1);
  } else {
    abort();
  }

}

// Needed for the time beeing, since the tests can't work with
// output which goes to cout.
// TODO: Change testst to be able to handle output which goes
//       to cerr.
void FairLogger::SetScreenStreamToCerr(bool errorStream)
{
  if(errorStream) {
    fScreenStream = &std::cerr;
  } else {
    fScreenStream = &std::cout;
  }
}


ClassImp(FairLogger)
