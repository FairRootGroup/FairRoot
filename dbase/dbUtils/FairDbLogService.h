/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBLOGSERVICE_H
#define FAIRDBLOGSERVICE_H
#include <iosfwd>
#include <map>
#include <string>
#include <stdexcept>
#include "Rtypes.h"
#include "FairDbLog.h"
#include "FairDbLogStream.h"
#include "FairDbLogOSStream.h"


using namespace std;

class DBLOGException : public std::runtime_error
{
  public:
    DBLOGException() : std::runtime_error("DBLOGException") {}
};

class FairDbLogService
{
    friend std::ostream& operator<<(std::ostream& os, const FairDbLogService& m);
  public:
    ~FairDbLogService();
    static FairDbLogService* Instance();

    // Is this stream active at this level?
    bool IsActive(const char* str_name, FairDbLog::LogLevel_t lvl) {
      //cout << " Is Active ? " << lvl << ":" << fsGlobalLogLevel <<endl;
      if (lvl < fsGlobalLogLevel ) { return false; } // Is ANY stream active at this level?
      if (FairDbLogStream* m = this->GetStream(str_name)) {
        //cout << "-I- FairDbLogService::active  stream created ---> " <<  m->IsActive(lvl) << endl;
        return m->IsActive(lvl);
      }

      return false;
    }

    static void StackTrace(const char* stream, FairDbLog::LogLevel_t lvl, int depth = 100, int ignore = 0);
    static void SetGlobalLevel();
    void       AddCatStream(const char* fileName,
                            const char* streamName, FairDbLog::LogLevel_t lvl);
    FairDbLogStream* GetStream(const char* name) {
      std::string logName(name);
      FairDbLogStream* m;
      if ((m = fFairDbLogStreamTable[logName])!=0) { return m; }
      return this->CreateStream(name);
    }
    void PrintStatistics();
    void PrintStatistics(std::ostream& os);
    void SetDefaultFormat(int fmt, int level=99);
    void SetCurrentRun( int  run) { fCurrentRun = run;};
    void GetCurrentRun( int& run) { run = fCurrentRun;};
    void SetkFatalAbort(int abortflag = 1) {fkFatalAbort = abortflag;}
    int  GetkFatalAbort() {return fkFatalAbort;}

    // Class to handle begin/end initializations of the Log Service
    class Init
    {
      public:
        static int count;
        Init()  { ++count; }
        ~Init() { if (--count==0) { delete fInstance; fInstance=0; } }
    };

  private:
    // FairDbLogService is a singleton
    FairDbLogService();
    const char* GetTmpCatFileName(const char* streamName, int lvl);
    FairDbLogStream*  CreateStream(const char* name);

  private:
    static FairDbLogService* fInstance; // The sole instance of the message service

    FairDbLog::LogLevel_t fDefaultLogLevel;                     // The log level
    char            fDefaultOStream[FairDbLog::kNLogLevel][64]; // Default output
    int             fDefaultFormat[FairDbLog::kNLogLevel];      // Default format
    std::map<std::string,FairDbLogStream*> fFairDbLogStreamTable;     // Streams
    std::vector<FairDbLogCatStream>        fFairDbLogCatList; // Streams to concatenate

    static FairDbLog::LogLevel_t fsGlobalLogLevel; // The lowest log level currently on.
    int fCurrentRun;   // Current run number
    int fkFatalAbort;  // kFatal has set flag to abort job at opportunity
};

#ifdef __APPLE__
static string __SVNID__ = "__SVNID__ undefined";

class SetFairDbLogSVNID
{
  public:
    SetFairDbLogSVNID(const char* svnid) { __SVNID__ = svnid; }
};
#endif



static class FairDbLogService::Init __loginit;

// Utility macros:
// Macro to concatenate two symbols:
#define TOKCAT(x,y) x##y
// Macro to expand preprocessor variables and concatenate:
#define TOKCAT2(x,y) TOKCAT(x,y)
// Macro to concatenate source line with a symbol:
#define LINECAT(x) TOKCAT2(x, __LINE__ )
// Macros to simplify the use of the Message Service
#ifdef __APPLE__
#define SVNID(x) static SetFairDbLogSVNID setlogsvnid(x)
#else
#if (( __GNUC__ >= 3) && !(__CINT__))
#define SVNID(x) static const char* __SVNID__  __attribute__ ((__unused__)) = x
#else
#define SVNID(x) static const char* __SVNID__ = x
#endif
#endif

// Macro __func__ is supposed as a non std
// Protect from exotic coompiler version
#if __GNUC__ >= 2
#define __func__ __FUNCTION__
#else
#define __func__ "<unknown>"
# endif



#ifdef __APPLE__
#define DBLOG(s,l) \
  if ( !FairDbLogService::Instance()->IsActive(s,l) ) {  } else  \
  ((*(FairDbLogService::Instance())->GetStream(s))(l,__FILE__,__func__,__LINE__))
#define DBLOGSTREAM(s,l) \
  ((*(FairDbLogService::Instance())->GetStream(s))(l,__FILE__,__func__,__LINE__))
#else
#define DBLOG(s,l) \
  if ( !FairDbLogService::Instance()->IsActive(s,l) ) {  } else \
  ((*(FairDbLogService::Instance())->GetStream(s))(l,__FILE__,__func__,__LINE__))
#define DBLOGSTREAM(s,l) \
  ((*(FairDbLogService::Instance())->GetStream(s))(l,__FILE__,__func__,__LINE__))
#endif

#define DBLOG_ONLY_COUNT(s,l) \
  if ( !FairDbLogService::Instance()->IsActive(s,l) ) { } else \
   ((FairDbLogService::Instance())->GetStream(s)->LogPrint(l,__FILE__))

#define MAXDBLOG(s,l,c)  \
  static int LINECAT(DBLOGCNT) =0; \
  const char* LINECAT(DBLOGADD) = (++LINECAT(DBLOGCNT)==c)?"..Last Message (counting continues).. ":""; \
  if(LINECAT(DBLOGCNT) > c || LINECAT(DBLOGCNT) < 0) {DBLOG_ONLY_COUNT(s,l);} else DBLOG(s,l) << LINECAT(DBLOGADD)

#endif //
