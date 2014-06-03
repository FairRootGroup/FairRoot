/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLogStream.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>
extern "C" {
#include <unistd.h>
}

#include "FairRtdbRun.h"
#include "FairRuntimeDb.h"

#include "FairDbLogFormat.h"
#include "FairDbLogOSStream.h"
#include "FairDbLogService.h"


using namespace std;

// ANSI/Xterm control sequences font color.

const char kColor_Reset[]    = { 0x1B, '[', '0', 'm', 0 };
const char kColor_Bold[]     = { 0x1B, '[', '1', 'm', 0 };
const char kColor_Dim[]      = { 0x1B, '[', '2', 'm', 0 };
const char kColor_Underline[]= { 0x1B, '[', '3', 'm', 0 };
const char kColor_Blink[]    = { 0x1B, '[', '5', 'm', 0 };
const char kColor_Reverse[]  = { 0x1B, '[', '7', 'm', 0 };

const char kColor_Black[]    = { 0x1B, '[', '3', '0', 'm', 0 };
const char kColor_Red[]      = { 0x1B, '[', '3', '1', 'm', 0 };
const char kColor_Green[]    = { 0x1B, '[', '3', '2', 'm', 0 };
const char kColor_Yellow[]   = { 0x1B, '[', '3', '3', 'm', 0 };
const char kColor_Blue[]     = { 0x1B, '[', '3', '4', 'm', 0 };
const char kColor_Magenta[]  = { 0x1B, '[', '3', '5', 'm', 0 };
const char kColor_Cyan[]     = { 0x1B, '[', '3', '6', 'm', 0 };
const char kColor_White[]    = { 0x1B, '[', '3', '7', 'm', 0 };

const char kColor_BgWhite[]    = { 0x1B, '[', '4', '0', 'm', 0 };
const char kColor_BgRed[]      = { 0x1B, '[', '4', '1', 'm', 0 };
const char kColor_BgGreen[]    = { 0x1B, '[', '4', '2', 'm', 0 };
const char kColor_BgYellow[]   = { 0x1B, '[', '4', '3', 'm', 0 };
const char kColor_BgBlue[]     = { 0x1B, '[', '4', '4', 'm', 0 };
const char kColor_BgMagenta[]  = { 0x1B, '[', '4', '5', 'm', 0 };
const char kColor_BgCyan[]     = { 0x1B, '[', '4', '6', 'm', 0 };
const char kColor_BgBlack[]    = { 0x1B, '[', '4', '7', 'm', 0 };


FairDbLogStream::FairDbLogStream()
  :fLogLevel(0)
  ,fCurrentLogLevel(0)
{
  strcpy(fName, "");
  Init();
}

FairDbLogStream::FairDbLogStream(const char* name)
  :fLogLevel(0)
  ,fCurrentLogLevel(0)
{
  if (strlen(name)>kMaxNameSize) {
    strncpy(fName, name, kMaxNameSize);
    fName[kMaxNameSize] = '\0'; // Terminate string
  } else {
    strcpy(fName, name);
  }
  Init();
}


void FairDbLogStream::SetLogLevel(FairDbLog::LogLevel_t lvl)
{
  fLogLevel = lvl;
  FairDbLogService::SetGlobalLevel();
}

void FairDbLogStream::AttachOStream(FairDbLog::LogLevel_t lvl, const char* name)
{
  vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[lvl].end());
  vector<FairDbLogOStream*>::iterator itrOStream = fFairDbLogOStream[lvl].begin();
  for (; itrOStream != vend; ++itrOStream) {
    if (strcmp(name, (*itrOStream)->GetName())==0) { return; }
  }

  FairDbLogOStreamService* oStreamService = FairDbLogOStreamService::Instance();
  FairDbLogOStream*        logOStream     = oStreamService->GetStream(name);
  fFairDbLogOStream[lvl].push_back(logOStream);
}

void FairDbLogStream::DetachOStream(FairDbLog::LogLevel_t lvl, const char* name)
{
  vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[lvl].end());
  vector<FairDbLogOStream*>::iterator itrOStream = fFairDbLogOStream[lvl].begin();
  for (; itrOStream != vend; ++itrOStream) {
    //cout << " STREAM " << (*itrOStream)->GetName() << endl;
    if (strcmp(name, (*itrOStream)->GetName())==0) { break; }
  }
  if (itrOStream != vend) {
    (*itrOStream)->SubtractReference();
    fFairDbLogOStream[lvl].erase(itrOStream);
  }
}


void FairDbLogStream::AddFormat(FairDbLog::LogLevel_t lvl, int fmt)
{
  if((fmt & FairDbLog::kFgColorMask)) { fFormat[lvl] &=(~FairDbLog::kFgColorMask); }
  if((fmt & FairDbLog::kBgColorMask)) { fFormat[lvl] &=(~FairDbLog::kBgColorMask); }
  fFormat[lvl] |= fmt;
}

void FairDbLogStream::Close()
{
  for (int i=fLogLevel; i<FairDbLog::kNLogLevel; ++i) {
    vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[i].end());
    for (vector<FairDbLogOStream*>::iterator itrOStreamPtr = fFairDbLogOStream[i].begin();
         itrOStreamPtr != vend;
         ++itrOStreamPtr) {
      (*itrOStreamPtr)->Close();
    }
  }
}

void FairDbLogStream::Flush()
{
  for (int i=fLogLevel; i<FairDbLog::kNLogLevel; ++i) {
    vector<FairDbLogOStream*>::iterator vend(fFairDbLogOStream[i].end());
    for (vector<FairDbLogOStream*>::iterator itrOStreamPtr = fFairDbLogOStream[i].begin();
         itrOStreamPtr != vend;
         ++itrOStreamPtr) {
      (*itrOStreamPtr)->Flush();
    }
  }
}


FairDbLogStream& FairDbLogStream::operator()(FairDbLog::LogLevel_t priority,
    const char* file,
    const char* svnid,
    int line)
{

  //  cout << "-I- ***************  FairDbLogStream  ********  entering " << " priority# " << priority << " file: "
  //     << file << " svnid#" << svnid << " line#" << line <<  endl;

  fCurrentLogLevel = priority;

  if (fCurrentLogLevel>=fLogLevel ) {
    int fmt = fFormat[fCurrentLogLevel];

    // Strip Off the file name
    int lena = strlen(file);
    file += lena;
    for (; lena>0 && *(file-1)!='/'; --lena) { --file; }

    this->LogPrint(fCurrentLogLevel,file);

    // Configure format flags
    if (fmt) {

      static bool sSomeoneUsedColor = false;
      if(sSomeoneUsedColor) {
        (*this) << kColor_Reset;
      }

      if ((fmt & FairDbLog::kFontMask )) {
        sSomeoneUsedColor = true;
        if((fmt & FairDbLog::kBold      )) { (*this) << kColor_Bold; }
        if((fmt & FairDbLog::kDim       )) { (*this) << kColor_Dim; }
        if((fmt & FairDbLog::kUnderline )) { (*this) << kColor_Underline; }
        if((fmt & FairDbLog::kBlink     )) { (*this) << kColor_Blink; }
        if((fmt & FairDbLog::kReverse   )) { (*this) << kColor_Reverse; }

        int color = fmt & FairDbLog::kFgColorMask;
        switch(color) {
        case FairDbLog::kBlack:
          (*this) << kColor_Black;
          break;
        case FairDbLog::kRed:
          (*this) << kColor_Red;
          break;
        case FairDbLog::kGreen:
          (*this) << kColor_Green;
          break;
        case FairDbLog::kYellow:
          (*this) << kColor_Yellow;
          break;
        case FairDbLog::kBlue:
          (*this) << kColor_Blue;
          break;
        case FairDbLog::kMagenta:
          (*this) << kColor_Magenta;
          break;
        case FairDbLog::kCyan:
          (*this) << kColor_Cyan;
          break;
        case FairDbLog::kWhite:
          (*this) << kColor_White;
          break;
        default:
          break;
        }

        color = fmt & FairDbLog::kBgColorMask;
        switch(color) {
        case FairDbLog::kBgBlack:
          (*this) << kColor_BgBlack;
          break;
        case FairDbLog::kBgRed:
          (*this) << kColor_BgRed;
          break;
        case FairDbLog::kBgGreen:
          (*this) << kColor_BgGreen;
          break;
        case FairDbLog::kBgYellow:
          (*this) << kColor_BgYellow;
          break;
        case FairDbLog::kBgBlue:
          (*this) << kColor_BgBlue;
          break;
        case FairDbLog::kBgMagenta:
          (*this) << kColor_BgMagenta;
          break;
        case FairDbLog::kBgCyan:
          (*this) << kColor_BgCyan;
          break;
        case FairDbLog::kBgWhite:
          (*this) << kColor_BgWhite;
          break;
        default:
          break;
        }
      }

      if ((fmt && (Bool_t)FairDbLog::kRunId )) {
        //UInt_t rid = 0;  FairRuntimeDb::instance()->getCurrentRun()->getRunId();
        this->SetCurrentDateString();
        (*this) << " [" << fCurrentDate << "]";
      }

      if ((fmt & FairDbLog::kPriority)) {
        switch(fCurrentLogLevel) {
        case FairDbLog::kVerbose:
          (*this) << " -V-";
          break;
        case FairDbLog::kDebug:
          (*this) << " -D-";
          break;
        case FairDbLog::kSynopsis:
          (*this) << " -S-";
          break;
        case FairDbLog::kInfo:
          (*this) << " -I-";
          break;
        case FairDbLog::kWarning:
          (*this) << " -W-";
          break;
        case FairDbLog::kError:
          (*this) << " -E-";
          break;
        case FairDbLog::kFatal:
          (*this) << " -F-";
          break;
        default :
          abort();
        }
      }
      if ((fmt & FairDbLog::kName)) { (*this) << " " << fName<<":"; }
      if ((fmt & FairDbLog::kHost)) {
        static const int len = 256;
        char host[len];
        int err = gethostname(host,len);
        if (err==0) { (*this) << " " << host; }
        else { (*this) << " /host?/"; }
        if ((fmt & FairDbLog::kPID)) {
          (*this) << ":" << getpid();
        }
      } else {
        if ((fmt & FairDbLog::kPID)) {
          (*this) << " pid=" << getpid();
        }
      }
      if ((fmt & FairDbLog::kTime)) {
        this->SetCurrentDateString();
        //(*this) << " " << fCurrentDate;
      }

      /*
        if ((fmt & FairDbLog::kSVNId)) {
      if (strlen(svnid)<8) {
        // If the svnid string is less than 8 characters long
        // assume it hasn't been filled yet -- use the file name
        (*this) << " " << file;
      }
      else {
        // This prints file name and version number
        this->SetSVNVersion(svnid);
        (*this) << " " << fSVNVersion;
      }
        }
        else {
      // This prints just the file name
      if ((fmt & FairDbLog::kFile)) (*this) << " " << file << "::" << svnid << "(...)";
        }
      */

      // This prints just the file name
      if ((fmt & FairDbLog::kFile)) { (*this) << " " << file << "::" << svnid << "()"; }

      if ((fmt & FairDbLog::kLine)) { (*this) << ":[" << line << "]"; }
      (*this) << " $ ";

      if ((fmt & FairDbLog::kStackTrace)) {
        (*this) << "Stack Trace: " << endl;
        FairDbLogService::StackTrace(fName,fCurrentLogLevel,4,1);
        (*this) << "... Message: ";
      }

      if ((fmt & FairDbLog::kFontMask )) {
        if((fmt & FairDbLog::kColorAll)) {
        } else {
          (*this) << kColor_Reset;
        }
      }

    }
  }

  if (fCurrentLogLevel == FairDbLog::kFatal) {
    FairDbLogService::Instance()->SetkFatalAbort();
    cerr << endl << endl;
    cerr << "***************** DBLOGException *****************" << endl;
    cerr << "**** DBLOGException has been thrown for kFatal. ***" << endl;
    cerr << endl;
    cerr << "A FairDbLogService::DBLOGException is  thrown at"   << endl;
    cerr << "the next entry to FairDbLogService.  This is triggered" << endl;
    cerr << "when a kFatal DBLOG statement is activated."        << endl;
    cerr << endl;
    cerr << "To investigate the cause without aborting the"    << endl;
    cerr << "job, replace the following statement on line " << line;
    cerr << endl << "of file " << file << ":" << endl;
    cerr << endl;
    cerr << "DBLOG(" << fName << ", FairDbLog::kFatal) << [...] << endl;"<< endl;
    cerr << endl;
    cerr << "with:" << endl;
    cerr << endl;
    cerr << "FairDbLogService::Instance()->SetkFatalAbort(0);" << endl;
    cerr << "DBLOG(" << fName << ", FairDbLog::kError) << [...] << endl;"<< endl;
    cerr << "// [Add diagnostic code here.]" << endl;
    cerr << "***************** DBLOGException *****************" << endl;
    cerr << endl;

    return *this;
  }

  return *this;
}

ostream& operator<<(ostream& os, const FairDbLogStream& s)
{
  os << "-I-  FairDbLogStream::" << s.fName
     << " LogLevel = " << (int)s.fLogLevel << "\n";
  for (int i=0; i<FairDbLog::kNLogLevel; ++i) {
    os << "(" << i << ") ";
    if (s.fFormat[i]&FairDbLog::kPriority) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kName) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kTime) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kFile) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kSVNId) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kLine) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kHost) { os << "x"; }
    else { os << "-"; }
    if (s.fFormat[i]&FairDbLog::kPID) { os << "x"; }
    else { os << "-"; }
    vector<FairDbLogOStream*>::const_iterator iter(s.fFairDbLogOStream[i].begin());
    vector<FairDbLogOStream*>::const_iterator iterEnd(s.fFairDbLogOStream[i].end());
    for (; iter != iterEnd; ++iter) {
      os << " " << (*iter)->GetName();
    }
    os << "\n";
  }
  os << "***\n";
  return os;
}

void FairDbLogStream::Init()
{
  fLogLevel = FairDbLog::kInfo;
  for (int i=0; i<FairDbLog::kNLogLevel; ++i) {
    fFormat[i]     = 0;
  }
  fCurrentLogLevel = fLogLevel;
}

void FairDbLogStream:: LogPrint(FairDbLog::LogLevel_t priority, const char* file)
{
  int len = strlen(file);
  file += len;
  for (; len>0 && *(file-1)!='/'; --len) { --file; }
  fFileStat[string(file)].LogPrint(priority);
}

void FairDbLogStream::SetCurrentDateString()
{

  time_t tt;
  struct tm* tp;
  tt = time(NULL);
  tp = localtime(&tt);
  sprintf(fCurrentDate, "%.4d/%.2d/%.2d %.2d:%.2d:%.2d",
          tp->tm_year+1900,
          tp->tm_mon+1,
          tp->tm_mday,
          tp->tm_hour,
          tp->tm_min,
          tp->tm_sec);
}

void FairDbLogStream::SetSVNVersion(const char* SVNId)
{
  int nsegment = 0;
  register int j = 0;
  for (unsigned int i=1; (i<strlen(SVNId)) && (i<127); ++i) {
    if (SVNId[i] != ' ' && SVNId[i-1] == ' ') {
      if (++nsegment == 3) { break; }
    }
    if (SVNId[i]!=' ' && nsegment>0) {
      fSVNVersion[j++] = SVNId[i];
    }
  }
  fSVNVersion[j] = '\0';
}

void FairDbLogStream::StatPrint(ostream& os, const char* label, int n) const
{
  if (n>0) {
    FairDbLogFormat ifmt("%-5i");
    os << label << ifmt(n);
  } else {
    os << "        ";
  }
}

void FairDbLogStream::PrintStatistics(ostream& os)
{
  map<string,FairDbLogStat>::iterator mend(fFileStat.end());
  for (map<string,FairDbLogStat>::iterator itrFileStat = fFileStat.begin();
       itrFileStat != mend;
       ++itrFileStat) {

    // Flag streams with error conditions
    if (itrFileStat->second.GetPrintCount(FairDbLog::kFatal) +
        itrFileStat->second.GetPrintCount(FairDbLog::kError)>0) {
      os << "*";
    } else { os << " "; }

    os << fName;
    for (int i=strlen(fName); i<7; ++i) { os << " "; }

    os << itrFileStat->first;
    for (int i=strlen((*itrFileStat).first.c_str()); i<24; ++i) { os << " "; }

    this->StatPrint(os, " F=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kFatal));
    this->StatPrint(os, " E=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kError));
    this->StatPrint(os, " W=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kWarning));
    this->StatPrint(os, " I=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kInfo));
    this->StatPrint(os, " S=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kSynopsis));
    this->StatPrint(os, " D=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kDebug));
    this->StatPrint(os, " V=",
                    itrFileStat->second.GetPrintCount(FairDbLog::kVerbose));
    os << endl;
  }
}
