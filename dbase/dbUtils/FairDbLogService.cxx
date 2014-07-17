/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLogService.h"
#include <cstdio>
#include <cassert>
#include <iostream>
extern "C" {
#include <unistd.h> // getpid
}
#include "FairDbLog.h"
#include "FairDbLogFormat.h"
#include "FairDbLogOSStream.h"
#include "FairDbLogStream.h"


using namespace std;

FairDbLogService* FairDbLogService::fInstance = 0;
int FairDbLogService::Init::count = 0;
FairDbLog::LogLevel_t FairDbLogService::fsGlobalLogLevel = FairDbLog::kMinLogLevel;


std::ostream& operator<<(std::ostream& os, const FairDbLogService& m)
{
  int i;
  static const FairDbLogFormat hexfmt("8x");

  os << "-I- FairDb Log  *******************"
     << "************************************\n";
  os << " Defaults:\n";
  os << "  Loglevel: " << (int)m.fDefaultLogLevel << "\n";
  for (i = 0; i<FairDbLog::kNLogLevel; ++i) {
    os << "  OStream : " << m.fDefaultOStream[i]
       << " Format : " << hexfmt((int)m.fDefaultFormat[i]) << "\n";
  }

  os << " Active Streams:\n";
  i = 0;
  map<std::string,FairDbLogStream*>::const_iterator mend(m.fFairDbLogStreamTable.end());
  for (map<std::string,FairDbLogStream*>::const_iterator
       itr = m.fFairDbLogStreamTable.begin();
       itr != mend;
       ++itr) {
    os << "<" << itr->first << ">";
    if (++i%10 == 0) { os << "\n"; }
  }
  os << "\n";


  os << " Concatenated Streams:\n";
  vector<FairDbLogCatStream>::const_iterator vend(m.fFairDbLogCatList.end());
  for (vector<FairDbLogCatStream>::const_iterator
       itrCatStream(m.fFairDbLogCatList.begin());
       itrCatStream != vend;
       ++itrCatStream) {
    os << "  " << (*itrCatStream);
  }
  os << "--------------------------------------"
     << "--------------------------------------\n";
  return os;
}


FairDbLogService::~FairDbLogService()
{
  // Close all output message streams
  map<std::string,FairDbLogStream*>::iterator mend(fFairDbLogStreamTable.end());
  for (map<std::string,FairDbLogStream*>::iterator itr = fFairDbLogStreamTable.begin();
       itr != mend;
       ++itr) {
    itr->second->Close();
    delete itr->second;
  }

  vector<FairDbLogCatStream>::iterator vend(fFairDbLogCatList.end());
  for (vector<FairDbLogCatStream>::iterator iter = fFairDbLogCatList.begin();
       iter != vend;
       ++iter) {
    iter->DoConcatenation();
  }
}

void FairDbLogService::SetDefaultFormat(int fmt, int level)
{
  if ((level>=0) && (level<FairDbLog::kNLogLevel)) {
    if((fmt & FairDbLog::kFgColorMask)) { fDefaultFormat[level] &=(~FairDbLog::kFgColorMask); }
    if((fmt & FairDbLog::kBgColorMask)) { fDefaultFormat[level] &=(~FairDbLog::kBgColorMask); }
    fDefaultFormat[level] |= fmt;
  } else {
    for (int lvl=0; lvl<FairDbLog::kNLogLevel; ++lvl) {
      if((fmt & FairDbLog::kFgColorMask)) { fDefaultFormat[lvl] &=(~FairDbLog::kFgColorMask); }
      if((fmt & FairDbLog::kBgColorMask)) { fDefaultFormat[lvl] &=(~FairDbLog::kBgColorMask); }
      fDefaultFormat[lvl] |= fmt;
    }
  }

}

FairDbLogService* FairDbLogService::Instance()
{

  if (fInstance == 0) {
    fInstance = new FairDbLogService();
    static int nbirth = 0;
    nbirth++;
    if (nbirth>1)
      cout
          << "-I- FairDbLogService::Instance() creating another singleton "
          << endl
          << "first one must have been destructed prematurely"
          << endl;
  }

  // Set Exception if fkFatalAbort has been set previously
  try {if (fInstance->GetkFatalAbort()!=0) { throw DBLOGException(); }}
  catch(DBLOGException) {
    cerr << endl << endl;
    cerr << "***************** FairDb Log Exception *****************" << endl;
    cerr << "***** FairDb Log Exception was thrown for kFatal. ******" << endl;
    cerr << endl;
    cerr << "A FairDb Log Exception has been thrown.  This"  << endl;
    cerr << "occurs when a kFatal FairDb Log statement is activated." << endl;
    cerr << "***************** FairDb Log Exception *****************" << endl;
    cerr << endl;

    throw DBLOGException();
    return fInstance;
  }

// <DB> CHECK ME  !!!!
  static bool activated = false;
  if ( !activated ) {
    activated = true;
    // Set the log level on all current and future FairDbLogStreams
    FairDbLog::LogLevel_t lvl =   FairDbLog::kMinLogLevel;
    map<std::string,FairDbLogStream*>::iterator mend(fInstance->fFairDbLogStreamTable.end());
    for (map<std::string,FairDbLogStream*>::iterator itr = fInstance->fFairDbLogStreamTable.begin(); itr != mend; ++itr)
      if(itr->second) { itr->second->SetLogLevel(lvl); }
  }

  return fInstance;
}

#if defined(__APPLE__)

# include <TSystem.h>
void FairDbLogService::StackTrace(const char* stream, FairDbLog::LogLevel_t lvl, int, int)
{
  if(!FairDbLogService::Instance()->IsActive(stream,lvl)) { return; }
  gSystem->StackTrace();
}
#else

# include <stdio.h>
# include <stdlib.h>
# include <execinfo.h>
# include <dlfcn.h>
# include <string.h>

void FairDbLogService::StackTrace(const char* stream, FairDbLog::LogLevel_t lvl, int depth, int ignore)
{
  if(!FairDbLogService::Instance()->IsActive(stream,lvl)) { return; }
  FairDbLogStream& s = *((FairDbLogService::Instance())->GetStream(stream));

  void* trace[10];
  size_t size;

  size_t i;
  char cmd[512];

  size = backtrace (trace, 10);
  size_t start = 1 + ignore;
  size_t end   = depth + start;
  if(end>size) { end=size; }

  for (i = start; i < end; i++) {
    // printf("going(%02d) [%s]\n",i-2,strings[i]);
    unsigned long addr = (unsigned long) trace[i];
    Dl_info info;
    if(dladdr(trace[i], &info) && info.dli_fname && info.dli_fname[0]) {
      const char*   libname = info.dli_fname;
      const char*   symname = (info.dli_sname && info.dli_sname[0]) ? info.dli_sname : "unknown";
      unsigned long libaddr = (unsigned long) info.dli_fbase;
      //unsigned long symaddr = (unsigned long) info.dli_saddr;
      unsigned long offset = (addr >= libaddr) ? addr - libaddr :
                             libaddr - addr;

      char linestr[1024];
      sprintf(linestr,"addr:0x%lx",addr); // Default: dump the address raw.

      sprintf(cmd,"addr2line -e %s 0x%016lx 2> /dev/null", libname, offset);
      if (FILE* pf = ::popen(cmd, "r")) {
        if (fgets(linestr, 1024, pf)) {
          linestr[strlen(linestr)-1] = 0;  // remove trailing \n
        }
        ::pclose(pf);
      }

      char funcname[1024];
      strcpy(funcname,symname);
      sprintf(cmd,"c++filt %s 2>/dev/null",  symname);
      if (FILE* pf = ::popen(cmd, "r")) {
        if (fgets(funcname, 1024, pf)) {
          funcname[strlen(funcname)-1] = 0;  // remove trailing \n
        }
        ::pclose(pf);
      }

      // Strip off most of the path.
      int slashes = 0;
      for(char* c = linestr+strlen(linestr)-1; c>linestr; c--) {
        if( (*c) == '/' ) { slashes++; }
        if(slashes==2) {
          char tmp[1024];
          strcpy(tmp,c+1);
          strcpy(linestr,tmp);
          break;
        }
      }

      // Write out the line.
      s << "  [" << i-start << "] " << funcname << " @ " << linestr << endl;
    }

  }
}
#endif

void FairDbLogService::AddCatStream(const char* fileName,
                                    const char* streamName,
                                    FairDbLog::LogLevel_t lvl)
{

  const char* tmpFileName = GetTmpCatFileName(streamName, lvl);
  this->GetStream(streamName)->AttachOStream(lvl, tmpFileName);


  FairDbLogCatStream* catStream = 0;
  for (vector<FairDbLogCatStream>::iterator iter = fFairDbLogCatList.begin();
       iter != fFairDbLogCatList.end();
       ++iter) {
    if (strcmp((*iter).GetOutputFileName(), fileName)==0) {
      catStream = &(*iter);
      break;
    }
  }
  if (catStream == 0) {
    catStream = new FairDbLogCatStream(fileName);
    catStream->AddFileToList(tmpFileName);
    fFairDbLogCatList.push_back(*catStream);
    delete catStream;
  } else {
    catStream->AddFileToList(tmpFileName);
  }
}

FairDbLogStream* FairDbLogService::CreateStream(const char* name)
{
  std::string logName(name);
  FairDbLogStream* logStream;

  if ((logStream = fFairDbLogStreamTable[logName]) != 0) {
    return logStream;
  }

  logStream = new FairDbLogStream(name); //
  assert(logStream);

  logStream->SetLogLevel(fDefaultLogLevel);
  for (FairDbLog::LogLevel_t lvl=0; lvl<FairDbLog::kNLogLevel; ++lvl) {
    logStream->AttachOStream(lvl, fDefaultOStream[lvl]);
    logStream->SetFormat(lvl, fDefaultFormat[lvl]);
  }
  fFairDbLogStreamTable[logName] = logStream;

  FairDbLogService::SetGlobalLevel(); //

  return logStream;
}

FairDbLogService::FairDbLogService() :
  fkFatalAbort(0)
{
  // Set the default log level for all streams
  fDefaultLogLevel = FairDbLog::kInfo;

  // Set the default output streams
  strcpy(fDefaultOStream[FairDbLog::kVerbose], "cerr");
  strcpy(fDefaultOStream[FairDbLog::kDebug],   "cerr");
  strcpy(fDefaultOStream[FairDbLog::kSynopsis],"cout");
  strcpy(fDefaultOStream[FairDbLog::kInfo],    "cout");
  strcpy(fDefaultOStream[4],             "cout");  // not yet used.
  strcpy(fDefaultOStream[FairDbLog::kWarning], "cerr");
  strcpy(fDefaultOStream[FairDbLog::kError],   "cerr");
  strcpy(fDefaultOStream[FairDbLog::kFatal],   "cerr");

  // Set the default formats
  fDefaultFormat[FairDbLog::kVerbose] =
    FairDbLog::kPriority + FairDbLog::kName +
    FairDbLog::kFile     + FairDbLog::kLine;
  fDefaultFormat[FairDbLog::kDebug] =
    FairDbLog::kPriority + FairDbLog::kName +
    FairDbLog::kFile     + FairDbLog::kLine;
  fDefaultFormat[FairDbLog::kSynopsis] = 0;
  fDefaultFormat[FairDbLog::kInfo] =
    FairDbLog::kPriority + FairDbLog::kName +
    FairDbLog::kFile     + FairDbLog::kLine;
  fDefaultFormat[FairDbLog::kWarning] =
    FairDbLog::kPriority + FairDbLog::kName  +
    FairDbLog::kFile     + FairDbLog::kSVNId + FairDbLog::kLine;
  fDefaultFormat[FairDbLog::kError]   =
    FairDbLog::kPriority + FairDbLog::kName  + FairDbLog::kTime +
    FairDbLog::kFile     + FairDbLog::kSVNId + FairDbLog::kLine;
  fDefaultFormat[FairDbLog::kFatal]   =
    FairDbLog::kPriority + FairDbLog::kName  + FairDbLog::kTime +
    FairDbLog::kFile     + FairDbLog::kSVNId + FairDbLog::kLine;

  fsGlobalLogLevel = fDefaultLogLevel;

  fCurrentRun   = -1;
}

const char* FairDbLogService::GetTmpCatFileName(const char* streamName,
    int lvl)
{
  static char fileName[256];
  sprintf(fileName, ".%s.%d.%d", streamName, lvl, getpid());
  return fileName;
}

void FairDbLogService::PrintStatistics()
{
  this->PrintStatistics(cerr);
}

void FairDbLogService::PrintStatistics(std::ostream& os)
{
  // Copy the map to a container we can sort
  list<pair<std::string, FairDbLogStream*> > streamList;
  map<std::string, FairDbLogStream*>::iterator mend(fFairDbLogStreamTable.end());
  for (map<std::string, FairDbLogStream*>::iterator itr = fFairDbLogStreamTable.begin();
       itr != mend;
       ++itr) {
    streamList.push_back(*itr);
  }
  streamList.sort();

  os << "======================= "
     << "-I- FAIRDB Usage Statistics"
     << " ===========================\n";
  os << " Stream "
     << "File                     "
     << "Print Counts\n";
  os << " ------ "
     << "------------------------ "
     << "-----------------------------------------------\n";

  list<pair<std::string, FairDbLogStream*> >::iterator lend(streamList.end());
  for (list<pair<std::string, FairDbLogStream*> >::iterator itr = streamList.begin();
       itr != lend;
       ++itr) {
    itr->second->PrintStatistics(os);
  }

  os << "========================"
     << "================================"
     << "========================\n";
}


void FairDbLogService::SetGlobalLevel()
{
  fsGlobalLogLevel = FairDbLog::kFatal;
  FairDbLogService* self = FairDbLogService::Instance();
  std::map<std::string,FairDbLogStream*>::iterator it = self->fFairDbLogStreamTable.begin();
  for(it = self->fFairDbLogStreamTable.begin(); it != self->fFairDbLogStreamTable.end(); it++ ) {
    FairDbLogStream* s = it->second;
    if(s) {
      if(s->GetLogLevel() < fsGlobalLogLevel) { fsGlobalLogLevel = s->GetLogLevel(); }
    }

  }
}
